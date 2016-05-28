/**
 * \file Grlib_demo.c
 *
 * \brief Sample application for graphics library
 *
*/

/*
* Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/ 
*
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "raster.h"
#include "psc.h"
#include "interrupt.h"
#include "soc_AM1808.h"
#include "hw_psc_AM1808.h"
#include "evmAM1808.h"
#include "Touch.h"
#include "i2c.h"
#include "image.h"
#include "grlib.h"
#include "widget.h"
#include "canvas.h"
#include "pushbutton.h"
#include "checkbox.h"
#include "radiobutton.h"
#include "container.h"
#include "slider.h"
#include "cbc.h"
#include "cbu.h"
#include "rbc.h"
#include "rbu.h"
#include "pbc.h"
#include "pbu.h"
#include "Grlib_demo.h"
#include "ustdlib.h"
#include "images.h"

#include "codecif.h"
#include "toneRaw.h"

#define LCD_SIZE 261156
#define LCD_CLK  150000000

#define X_OFFSET    80
#define Y_OFFSET    16

#define PALETTE_OFFSET	4
#define FRAME_BUFFER_0	0
#define FRAME_BUFFER_1	1

#define I2C_SLAVE_PMIC_ADDR 0x48
/* Interrupt channels to map in AINTC */
#define INT_CHANNEL_I2C                       (2u)
#define INT_CHANNEL_MCASP                     (2u)
#define INT_CHANNEL_EDMACC                    (2u)
/* AIC3106 codec address */
#define I2C_SLAVE_CODEC_AIC31                 (0x18u) 

#define NUM_PUSH_BUTTONS        (sizeof(g_psPushButtons)/sizeof(g_psPushButtons[0]))
unsigned int g_ulButtonState;


extern void SoundInit(void);
extern void SoundClickPlay(unsigned char* toneBase, unsigned int toneSize);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
// Memory that is used as the local frame buffer.
#if defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=4
unsigned char g_pucBuffer[GrOffScreen16BPPSize(LCD_WIDTH, LCD_HEIGHT)];
#elif defined __TMS470__ || defined _TMS320C6X
#pragma DATA_ALIGN(g_pucBuffer, 4);
unsigned char g_pucBuffer[GrOffScreen16BPPSize(LCD_WIDTH, LCD_HEIGHT)];
#else
unsigned char g_pucBuffer[GrOffScreen16BPPSize(LCD_WIDTH, LCD_HEIGHT)]__attribute__ ((aligned (4)));
#endif

// The graphics library display structure.
tDisplay g_sSHARP480x272x16Display;

// 32 byte Palette.
unsigned short palette_32b[PALETTE_SIZE/2] = 
            {0x4000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u,
             0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u};


tContext sContext;

unsigned int timerIsrFlag = FALSE;
extern void (*I2CpFunc)(void);

//*****************************************************************************
//
// The sound effect that is played when a key is pressed.
//
//*****************************************************************************
//static const unsigned short g_pusKeyClick[] =
//{
//    0, 784,
//    25, 40000
//};

//*****************************************************************************
//
// Forward declarations for the globals required to define the widgets at
// compile-time.
//
//*****************************************************************************
void OnPrevious(tWidget *pWidget);
void OnNext(tWidget *pWidget);
void OnIntroPaint(tWidget *pWidget, tContext *pContext);
void OnPrimitivePaint(tWidget *pWidget, tContext *pContext);
void OnCanvasPaint(tWidget *pWidget, tContext *pContext);
void OnCheckChange(tWidget *pWidget, unsigned int bSelected);
void OnButtonPress(tWidget *pWidget);
void OnRadioChange(tWidget *pWidget, unsigned int bSelected);
void OnSliderChange(tWidget *pWidget, int lValue);
void ClickPlay(void);

extern tCanvasWidget g_psPanels[];

//*****************************************************************************
//
// The first panel, which contains introductory text explaining the
// application.
//
//*****************************************************************************
Canvas(g_sIntroduction, g_psPanels, 0, 0, &g_sSHARP480x272x16Display, 0+X_OFFSET, 
        24+Y_OFFSET, 320, 166, CANVAS_STYLE_APP_DRAWN, 0, 0, 0, 0, 0, 0, OnIntroPaint);

//*****************************************************************************
//
// The second panel, which demonstrates the graphics primitives.
//
//*****************************************************************************
Canvas(g_sPrimitives, g_psPanels + 1, 0, 0, &g_sSHARP480x272x16Display, 0+X_OFFSET,
       24+Y_OFFSET, 320, 166, CANVAS_STYLE_APP_DRAWN, 0, 0, 0, 0, 0, 0,
       OnPrimitivePaint);

//*****************************************************************************
//
// The third panel, which demonstrates the canvas widget.
//
//*****************************************************************************
Canvas(g_sCanvas3, g_psPanels + 2, 0, 0, &g_sSHARP480x272x16Display, 205+X_OFFSET,
       27+Y_OFFSET, 110, 158, CANVAS_STYLE_OUTLINE | CANVAS_STYLE_APP_DRAWN, 0, ClrGray,
       0, 0, 0, 0, OnCanvasPaint);
Canvas(g_sCanvas2, g_psPanels + 2, &g_sCanvas3, 0,
       &g_sSHARP480x272x16Display, 5+X_OFFSET, 109+Y_OFFSET, 195, 76,
       CANVAS_STYLE_OUTLINE | CANVAS_STYLE_IMG, 0, ClrGray, 0, 0, 0, g_TILogo,
       0);
Canvas(g_sCanvas1, g_psPanels + 2, &g_sCanvas2, 0,
       &g_sSHARP480x272x16Display, 5+X_OFFSET, 27+Y_OFFSET, 195, 76,
       CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE | CANVAS_STYLE_TEXT,
       ClrMidnightBlue, ClrGray, ClrSilver, &g_sFontCm22, "Text", 0, 0);

//*****************************************************************************
//
// The fourth panel, which demonstrates the checkbox widget.
//
//*****************************************************************************
tCanvasWidget g_psCheckBoxIndicators[] =
{
    CanvasStruct(g_psPanels + 3, g_psCheckBoxIndicators + 1, 0,
                 &g_sSHARP480x272x16Display, 230+X_OFFSET, 30+Y_OFFSET, 50, 42,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psPanels + 3, g_psCheckBoxIndicators + 2, 0,
                 &g_sSHARP480x272x16Display, 230+X_OFFSET, 82+Y_OFFSET, 50, 48,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psPanels + 3, 0, 0,
                 &g_sSHARP480x272x16Display, 230+X_OFFSET, 134+Y_OFFSET, 50, 42,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0)
};
tCheckBoxWidget g_psCheckBoxes[] =
{
    CheckBoxStruct(g_psPanels + 3, g_psCheckBoxes + 1, 0,
                   &g_sSHARP480x272x16Display, 40+X_OFFSET, 30+Y_OFFSET, 185, 42,
                   CB_STYLE_OUTLINE | CB_STYLE_FILL | CB_STYLE_TEXT, 16,
                   ClrMidnightBlue, ClrGray, ClrSilver, &g_sFontCm22, "Select",
                   0, OnCheckChange),
    CheckBoxStruct(g_psPanels + 3, g_psCheckBoxes + 2, 0,
                   &g_sSHARP480x272x16Display, 40+X_OFFSET, 82+Y_OFFSET, 185, 48,
                   CB_STYLE_IMG, 16, 0, ClrGray, 0, 0, 0,
                   g_TILogo, OnCheckChange),
    CheckBoxStruct(g_psPanels + 3, g_psCheckBoxIndicators, 0,
                   &g_sSHARP480x272x16Display, 40+X_OFFSET, 134+Y_OFFSET, 189, 42,
                   CB_STYLE_OUTLINE | CB_STYLE_TEXT, 16,
                   0, ClrGray, ClrGreen, &g_sFontCm20, "Select",
                   0, OnCheckChange),
};
#define NUM_CHECK_BOXES         (sizeof(g_psCheckBoxes)/sizeof(g_psCheckBoxes[0]))

//*****************************************************************************
//
// The fifth panel, which demonstrates the container widget.
//
//*****************************************************************************
Container(g_sContainer3, g_psPanels + 4, 0, 0, &g_sSHARP480x272x16Display,
          210+X_OFFSET, 47+Y_OFFSET, 105, 118, CTR_STYLE_OUTLINE | CTR_STYLE_FILL,
          ClrMidnightBlue, ClrGray, 0, 0, 0);
Container(g_sContainer2, g_psPanels + 4, &g_sContainer3, 0,
          &g_sSHARP480x272x16Display, 5+X_OFFSET, 109+Y_OFFSET, 200, 76,
          (CTR_STYLE_OUTLINE | CTR_STYLE_FILL | CTR_STYLE_TEXT |
           CTR_STYLE_TEXT_CENTER), ClrMidnightBlue, ClrGray, ClrSilver,
          &g_sFontCm22, "Group2");
Container(g_sContainer1, g_psPanels + 4, &g_sContainer2, 0,
          &g_sSHARP480x272x16Display, 5+X_OFFSET, 27+Y_OFFSET, 200, 76,
          CTR_STYLE_OUTLINE | CTR_STYLE_FILL | CTR_STYLE_TEXT, ClrMidnightBlue,
          ClrGray, ClrSilver, &g_sFontCm22, "Group1");

//*****************************************************************************
//
// The sixth panel, which contains a selection of push buttons.
//
//*****************************************************************************
tCanvasWidget g_psPushButtonIndicators[] =
{
    CanvasStruct(g_psPanels + 5, g_psPushButtonIndicators + 1, 0,
                 &g_sSHARP480x272x16Display, 40+X_OFFSET, 85+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psPanels + 5, g_psPushButtonIndicators + 2, 0,
                 &g_sSHARP480x272x16Display, 90+X_OFFSET, 85+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psPanels + 5, g_psPushButtonIndicators + 3, 0,
                 &g_sSHARP480x272x16Display, 145+X_OFFSET, 85+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psPanels + 5, g_psPushButtonIndicators + 4, 0,
                 &g_sSHARP480x272x16Display, 40+X_OFFSET, 165+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psPanels + 5, g_psPushButtonIndicators + 5, 0,
                 &g_sSHARP480x272x16Display, 90+X_OFFSET, 165+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psPanels + 5, g_psPushButtonIndicators + 6, 0,
                 &g_sSHARP480x272x16Display, 145+X_OFFSET, 165+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psPanels + 5, g_psPushButtonIndicators + 7, 0,
                 &g_sSHARP480x272x16Display, 190+X_OFFSET, 35+Y_OFFSET, 110, 24,
                 CANVAS_STYLE_TEXT, 0, 0, ClrSilver, &g_sFontCm20, "Non-auto",
                 0, 0),
    CanvasStruct(g_psPanels + 5, g_psPushButtonIndicators + 8, 0,
                 &g_sSHARP480x272x16Display, 190+X_OFFSET, 55+Y_OFFSET, 110, 24,
                 CANVAS_STYLE_TEXT, 0, 0, ClrSilver, &g_sFontCm20, "repeat",
                 0, 0),
    CanvasStruct(g_psPanels + 5, g_psPushButtonIndicators + 9, 0,
                 &g_sSHARP480x272x16Display, 190+X_OFFSET, 115+Y_OFFSET, 110, 24,
                 CANVAS_STYLE_TEXT, 0, 0, ClrSilver, &g_sFontCm20, "Auto",
                 0, 0),
    CanvasStruct(g_psPanels + 5, 0, 0,
                 &g_sSHARP480x272x16Display, 190+X_OFFSET, 135+Y_OFFSET, 110, 24,
                 CANVAS_STYLE_TEXT, 0, 0, ClrSilver, &g_sFontCm20, "repeat",
                 0, 0),
};
tPushButtonWidget g_psPushButtons[] =
{
    RectangularButtonStruct(g_psPanels + 5, g_psPushButtons + 1, 0,
                            &g_sSHARP480x272x16Display, 30+X_OFFSET, 35+Y_OFFSET, 40, 40,
                            PB_STYLE_FILL | PB_STYLE_OUTLINE | PB_STYLE_TEXT,
                            ClrMidnightBlue, ClrBlack, ClrGray, ClrSilver,
                            &g_sFontCm22, "1", 0, 0, 0, 0, OnButtonPress),
    CircularButtonStruct(g_psPanels + 5, g_psPushButtons + 2, 0,
                         &g_sSHARP480x272x16Display, 100+X_OFFSET, 55+Y_OFFSET, 20,
                         PB_STYLE_FILL | PB_STYLE_OUTLINE | PB_STYLE_TEXT,
                         ClrMidnightBlue, ClrBlack, ClrGray, ClrSilver,
                         &g_sFontCm22, "3", 0, 0, 0, 0, OnButtonPress),
    RectangularButtonStruct(g_psPanels + 5, g_psPushButtons + 3, 0,
                            &g_sSHARP480x272x16Display, 140+X_OFFSET, 40+Y_OFFSET, 37, 37,
                            PB_STYLE_IMG | PB_STYLE_TEXT, 0, 0, 0, ClrSilver,
                            &g_sFontCm22, "5", g_pucBlue37x37,
                            g_pucBlue37x37Press, 0, 0, OnButtonPress),
    RectangularButtonStruct(g_psPanels + 5, g_psPushButtons + 4, 0,
                            &g_sSHARP480x272x16Display, 30+X_OFFSET, 115+Y_OFFSET, 40, 40,
                            (PB_STYLE_FILL | PB_STYLE_OUTLINE | PB_STYLE_TEXT |
                             PB_STYLE_AUTO_REPEAT), ClrMidnightBlue, ClrBlack,
                            ClrGray, ClrSilver, &g_sFontCm22, "2", 0, 0, 125,
                            25, OnButtonPress),
    CircularButtonStruct(g_psPanels + 5, g_psPushButtons + 5, 0,
                         &g_sSHARP480x272x16Display, 100+X_OFFSET, 135+Y_OFFSET, 20,
                         (PB_STYLE_FILL | PB_STYLE_OUTLINE | PB_STYLE_TEXT |
                          PB_STYLE_AUTO_REPEAT), ClrMidnightBlue, ClrBlack,
                         ClrGray, ClrSilver, &g_sFontCm22, "4", 0, 0, 125, 25,
                         OnButtonPress),
    RectangularButtonStruct(g_psPanels + 5, g_psPushButtonIndicators, 0,
                            &g_sSHARP480x272x16Display, 140+X_OFFSET, 120+Y_OFFSET, 37, 37,
                            (PB_STYLE_IMG | PB_STYLE_TEXT |
                             PB_STYLE_AUTO_REPEAT), 0, 0, 0, ClrSilver,
                            &g_sFontCm22, "6", g_pucBlue37x37,
                            g_pucBlue37x37Press, 125, 25, OnButtonPress),
};

//*****************************************************************************
//
// The seventh panel, which contains a selection of radio buttons.
//
//*****************************************************************************
tContainerWidget g_psRadioContainers[];
tCanvasWidget g_psRadioButtonIndicators[] =
{
    CanvasStruct(g_psRadioContainers, g_psRadioButtonIndicators + 1, 0,
                 &g_sSHARP480x272x16Display, 95+X_OFFSET, 62+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psRadioContainers, g_psRadioButtonIndicators + 2, 0,
                 &g_sSHARP480x272x16Display, 95+X_OFFSET, 107+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psRadioContainers, 0, 0,
                 &g_sSHARP480x272x16Display, 95+X_OFFSET, 152+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psRadioContainers + 1, g_psRadioButtonIndicators + 4, 0,
                 &g_sSHARP480x272x16Display, 260+X_OFFSET, 62+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psRadioContainers + 1, g_psRadioButtonIndicators + 5, 0,
                 &g_sSHARP480x272x16Display, 260+X_OFFSET, 107+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
    CanvasStruct(g_psRadioContainers + 1, 0, 0,
                 &g_sSHARP480x272x16Display, 260+X_OFFSET, 152+Y_OFFSET, 20, 20,
                 CANVAS_STYLE_IMG, 0, 0, 0, 0, 0, g_ledOFF, 0),
};
tRadioButtonWidget g_psRadioButtons1[] =
{
    RadioButtonStruct(g_psRadioContainers, g_psRadioButtons1 + 1, 0,
                      &g_sSHARP480x272x16Display, 10+X_OFFSET, 50+Y_OFFSET, 80, 45,
                      RB_STYLE_TEXT, 16, 0, ClrSilver, ClrSilver, &g_sFontCm20,
                      "One", 0, OnRadioChange),
    RadioButtonStruct(g_psRadioContainers, g_psRadioButtons1 + 2, 0,
                      &g_sSHARP480x272x16Display, 10+X_OFFSET, 95+Y_OFFSET, 80, 45,
                      RB_STYLE_TEXT, 16, 0, ClrSilver, ClrSilver, &g_sFontCm20,
                      "Two", 0, OnRadioChange),
    RadioButtonStruct(g_psRadioContainers, g_psRadioButtonIndicators, 0,
                      &g_sSHARP480x272x16Display, 10+X_OFFSET, 140+Y_OFFSET, 80, 45,
                      RB_STYLE_TEXT, 24, 0, ClrSilver, ClrSilver, &g_sFontCm20,
                      "Three", 0, OnRadioChange)
};
#define NUM_RADIO1_BUTTONS      (sizeof(g_psRadioButtons1) / sizeof(g_psRadioButtons1[0]))
tRadioButtonWidget g_psRadioButtons2[] =
{
    RadioButtonStruct(g_psRadioContainers + 1, g_psRadioButtons2 + 1, 0,
                      &g_sSHARP480x272x16Display, 175+X_OFFSET, 50+Y_OFFSET, 80, 45,
                      RB_STYLE_IMG, 16, 0, ClrSilver, 0, 0, 0, g_pucLogo,
                      OnRadioChange),
    RadioButtonStruct(g_psRadioContainers + 1, g_psRadioButtons2 + 2, 0,
                      &g_sSHARP480x272x16Display, 175+X_OFFSET, 95+Y_OFFSET, 80, 45,
                      RB_STYLE_IMG, 24, 0, ClrSilver, 0, 0, 0, g_pucLogo,
                      OnRadioChange),
    RadioButtonStruct(g_psRadioContainers + 1, g_psRadioButtonIndicators + 3,
                      0, &g_sSHARP480x272x16Display, 175+X_OFFSET, 140+Y_OFFSET, 80, 45,
                      RB_STYLE_IMG, 24, 0, ClrSilver, 0, 0, 0, g_pucLogo,
                      OnRadioChange)
};
#define NUM_RADIO2_BUTTONS      (sizeof(g_psRadioButtons2) / sizeof(g_psRadioButtons2[0]))
tContainerWidget g_psRadioContainers[] =
{
    ContainerStruct(g_psPanels + 6, g_psRadioContainers + 1, g_psRadioButtons1,
                    &g_sSHARP480x272x16Display, 5+X_OFFSET, 27+Y_OFFSET, 148, 160,
                    CTR_STYLE_OUTLINE | CTR_STYLE_TEXT, 0, ClrGray, ClrSilver,
                    &g_sFontCm20, "Group One"),
    ContainerStruct(g_psPanels + 6, 0, g_psRadioButtons2,
                    &g_sSHARP480x272x16Display, 167+X_OFFSET, 27+Y_OFFSET, 148, 160,
                    CTR_STYLE_OUTLINE | CTR_STYLE_TEXT, 0, ClrGray, ClrSilver,
                    &g_sFontCm20, "Group Two")
};

//*****************************************************************************
//
// The eighth panel, which demonstrates the slider widget.
//
//*****************************************************************************
Canvas(g_sSliderValueCanvas, g_psPanels + 7, 0, 0,
       &g_sSHARP480x272x16Display, 210+X_OFFSET, 30+Y_OFFSET, 60, 40,
       CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_OPAQUE, ClrBlack, 0, ClrSilver,
       &g_sFontCm24, "50%",
       0, 0);

tSliderWidget g_psSliders[] =
{
    SliderStruct(g_psPanels + 7, g_psSliders + 1, 0,
                 &g_sSHARP480x272x16Display, 5+X_OFFSET, 115+Y_OFFSET, 220, 30, 0, 100, 25,
                 (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
                  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
                 ClrGray, ClrBlack, ClrSilver, ClrWhite, ClrWhite,
                 &g_sFontCm20, "25%", 0, 0, OnSliderChange),
    SliderStruct(g_psPanels + 7, g_psSliders + 2, 0,
                 &g_sSHARP480x272x16Display, 5+X_OFFSET, 155+Y_OFFSET, 220, 25, 0, 100, 25,
                 (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
                  SL_STYLE_TEXT),
                 ClrWhite, ClrBlueViolet, ClrSilver, ClrBlack, 0,
                 &g_sFontCm18, "Foreground Text Only", 0, 0, OnSliderChange),
    SliderStruct(g_psPanels + 7, g_psSliders + 3, 0,
                 &g_sSHARP480x272x16Display, 240+X_OFFSET, 70+Y_OFFSET, 26, 110, 0, 100, 50,
                 (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_VERTICAL |
                  SL_STYLE_OUTLINE | SL_STYLE_LOCKED), ClrDarkGreen,
                  ClrDarkRed, ClrSilver, 0, 0, 0, 0, 0, 0, 0),
    SliderStruct(g_psPanels + 7, g_psSliders + 4, 0,
                 &g_sSHARP480x272x16Display, 280+X_OFFSET, 30+Y_OFFSET, 30, 150, 0, 100, 75,
                 (SL_STYLE_IMG | SL_STYLE_BACKG_IMG | SL_STYLE_VERTICAL |
                 SL_STYLE_OUTLINE), 0, ClrBlack, ClrSilver, 0, 0, 0,
                 0, g_pucGettingHotter28x148, g_pucGettingHotter28x148Mono,
                 OnSliderChange),
    SliderStruct(g_psPanels + 7, g_psSliders + 5, 0,
                 &g_sSHARP480x272x16Display, 5+X_OFFSET, 30+Y_OFFSET, 195, 37, 0, 100, 50,
                 SL_STYLE_IMG | SL_STYLE_BACKG_IMG, 0, 0, 0, 0, 0, 0,
                 0, g_pucGreenSlider195x37, g_pucRedSlider195x37,
                 OnSliderChange),
    SliderStruct(g_psPanels + 7, &g_sSliderValueCanvas, 0,
                 &g_sSHARP480x272x16Display, 5+X_OFFSET, 80+Y_OFFSET, 220, 25, 0, 100, 50,
                 (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_TEXT |
                  SL_STYLE_BACKG_TEXT | SL_STYLE_TEXT_OPAQUE |
                  SL_STYLE_BACKG_TEXT_OPAQUE),
                 ClrBlue, ClrYellow, ClrSilver, ClrYellow, ClrBlue,
                 &g_sFontCm18, "Text in both areas", 0, 0,
                 OnSliderChange),
};

#define SLIDER_TEXT_VAL_INDEX   0
#define SLIDER_LOCKED_INDEX     2
#define SLIDER_CANVAS_VAL_INDEX 4

#define NUM_SLIDERS (sizeof(g_psSliders) / sizeof(g_psSliders[0]))

//*****************************************************************************
//
// An array of canvas widgets, one per panel.  Each canvas is filled with
// black, overwriting the contents of the previous panel.
//
//*****************************************************************************
tCanvasWidget g_psPanels[] =
{
    CanvasStruct(0, 0, &g_sIntroduction, &g_sSHARP480x272x16Display, 0+X_OFFSET, 
                 24+Y_OFFSET, 320, 166, CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0),
    CanvasStruct(0, 0, &g_sPrimitives, &g_sSHARP480x272x16Display, 0+X_OFFSET, 
                 24+Y_OFFSET, 320, 166, CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0),
    CanvasStruct(0, 0, &g_sCanvas1, &g_sSHARP480x272x16Display, 0+X_OFFSET, 24+Y_OFFSET, 
                 320, 166, CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0),
    CanvasStruct(0, 0, g_psCheckBoxes, &g_sSHARP480x272x16Display, 0+X_OFFSET, 
                 24+Y_OFFSET, 320, 166, CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0),
    CanvasStruct(0, 0, &g_sContainer1, &g_sSHARP480x272x16Display, 0+X_OFFSET, 
                 24+Y_OFFSET, 320, 166, CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0),
    CanvasStruct(0, 0, g_psPushButtons, &g_sSHARP480x272x16Display, 0+X_OFFSET, 
                 24+Y_OFFSET, 320, 166, CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0),
    CanvasStruct(0, 0, g_psRadioContainers, &g_sSHARP480x272x16Display, 0+X_OFFSET,
                 24+Y_OFFSET, 320, 166, CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0),
    CanvasStruct(0, 0, g_psSliders, &g_sSHARP480x272x16Display, 0+X_OFFSET, 24+Y_OFFSET,
                 320, 166, CANVAS_STYLE_FILL, ClrBlack, 0, 0, 0, 0, 0, 0),
};

//*****************************************************************************
//
// The number of panels.
//
//*****************************************************************************
#define NUM_PANELS              (sizeof(g_psPanels) / sizeof(g_psPanels[0]))

//*****************************************************************************
//
// The names for each of the panels, which is displayed at the bottom of the
// screen.
//
//*****************************************************************************
char *g_pcPanelNames[] =
{
    "     Introduction     ",
    "     Primitives     ",
    "     Canvas     ",
    "     Checkbox     ",
    "     Container     ",
    "     Push Buttons     ",
    "     Radio Buttons     ",
    "     Sliders     ",
    "     S/W Update    "
};

//*****************************************************************************
//
// The buttons and text across the bottom of the screen.
//
//*****************************************************************************
RectangularButton(g_sPrevious, 0, 0, 0, &g_sSHARP480x272x16Display, 0+X_OFFSET, 190+Y_OFFSET,
                  50, 50, PB_STYLE_FILL, ClrBlack, ClrBlack, 0, ClrSilver,
                  &g_sFontCm20, "-", g_prev50x50, g_prev50x50, 0, 0,
                  OnPrevious);
Canvas(g_sTitle, 0, 0, 0, &g_sSHARP480x272x16Display, 50+X_OFFSET, 190+Y_OFFSET, 220, 50,
                  CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_OPAQUE, 0, 0, ClrSilver,
                  &g_sFontCm20, 0, 0, 0);
RectangularButton(g_sNext, 0, 0, 0, &g_sSHARP480x272x16Display, 270+X_OFFSET, 190+Y_OFFSET,
                  50, 50, PB_STYLE_IMG | PB_STYLE_TEXT, ClrBlack, ClrBlack, 0,
                  ClrSilver, &g_sFontCm20, "+", g_next50x50,
                  g_next50x50, 0, 0, OnNext);

//*****************************************************************************
//
// The panel that is currently being displayed.
//
//*****************************************************************************
unsigned int g_ulPanel;

//*****************************************************************************
//
// Handles presses of the previous panel button.
//
//*****************************************************************************
void
OnPrevious(tWidget *pWidget)
{
    //
    // There is nothing to be done if the first panel is already being
    // displayed.
    //
    if(g_ulPanel == 0)
    {
        return;
    }

    //
    // Remove the current panel.
    //
    WidgetRemove((tWidget *)(g_psPanels + g_ulPanel));

    //
    // Decrement the panel index.
    //
    g_ulPanel--;

    //
    // Add and draw the new panel.
    //
    WidgetAdd(WIDGET_ROOT, (tWidget *)(g_psPanels + g_ulPanel));
    WidgetPaint((tWidget *)(g_psPanels + g_ulPanel));

    //
    // Set the title of this panel.
    //
    CanvasTextSet(&g_sTitle, g_pcPanelNames[g_ulPanel]);
    WidgetPaint((tWidget *)&g_sTitle);

    //
    // See if this is the first panel.
    //
    if(g_ulPanel == 0)
    {
        //
        // Clear the previous button from the display since the first panel is
        // being displayed.
        //
        PushButtonImageOff(&g_sPrevious);
        PushButtonTextOff(&g_sPrevious);
        PushButtonFillOn(&g_sPrevious);
        WidgetPaint((tWidget *)&g_sPrevious);
    }

    //
    // See if the previous panel was the last panel.
    //
    if(g_ulPanel == (NUM_PANELS - 2))
    {
        //
        // Display the next button.
        //
        PushButtonImageOn(&g_sNext);
        PushButtonTextOn(&g_sNext);
        PushButtonFillOff(&g_sNext);
        WidgetPaint((tWidget *)&g_sNext);
    }

    //
    // Play the key click sound.
    //
    //SoundPlay(g_pusKeyClick, sizeof(g_pusKeyClick) / 2);
	ClickPlay();
}

//*****************************************************************************
//
// Handles presses of the next panel button.
//
//*****************************************************************************
void
OnNext(tWidget *pWidget)
{
    //
    // There is nothing to be done if the last panel is already being
    // displayed.
    //
    if(g_ulPanel == (NUM_PANELS - 1))
    {
        return;
    }

    //
    // Remove the current panel.
    //
    WidgetRemove((tWidget *)(g_psPanels + g_ulPanel));

    //
    // Increment the panel index.
    //
    g_ulPanel++;

    //
    // Add and draw the new panel.
    //
    WidgetAdd(WIDGET_ROOT, (tWidget *)(g_psPanels + g_ulPanel));
    WidgetPaint((tWidget *)(g_psPanels + g_ulPanel));

    //
    // Set the title of this panel.
    //
    CanvasTextSet(&g_sTitle, g_pcPanelNames[g_ulPanel]);
    WidgetPaint((tWidget *)&g_sTitle);

    //
    // See if the previous panel was the first panel.
    //
    if(g_ulPanel == 1)
    {
        //
        // Display the previous button.
        //
        PushButtonImageOn(&g_sPrevious);
        PushButtonTextOn(&g_sPrevious);
        PushButtonFillOff(&g_sPrevious);
        WidgetPaint((tWidget *)&g_sPrevious);
    }

    //
    // See if this is the last panel.
    //
    if(g_ulPanel == (NUM_PANELS - 1))
    {
        //
        // Clear the next button from the display since the last panel is being
        // displayed.
        //
        PushButtonImageOff(&g_sNext);
        PushButtonTextOff(&g_sNext);
        PushButtonFillOn(&g_sNext);
        WidgetPaint((tWidget *)&g_sNext);
    }

    //
    // Play the key click sound.
    //
    //SoundPlay(g_pusKeyClick, sizeof(g_pusKeyClick) / 2);
	ClickPlay();
}

//*****************************************************************************
//
// Handles paint requests for the introduction canvas widget.
//
//*****************************************************************************
void
OnIntroPaint(tWidget *pWidget, tContext *pContext)
{
    //
    // Display the introduction text in the canvas.
    //
    GrContextFontSet(pContext, &g_sFontCm18);
    GrContextForegroundSet(pContext, ClrSilver);
    GrStringDraw(pContext, "This application demonstrates the Stellaris", -1,
                 0+X_OFFSET, 32+Y_OFFSET, 0);
    GrStringDraw(pContext, "Graphics Library.", -1, 0+X_OFFSET, 50+Y_OFFSET, 0);
    GrStringDraw(pContext, "Each panel shows a different feature of", -1, 0+X_OFFSET,
                 74+Y_OFFSET, 0);
    GrStringDraw(pContext, "the graphics library. Widgets on the panels", -1, 0+X_OFFSET,
                 92+Y_OFFSET, 0);
    GrStringDraw(pContext, "are fully operational; pressing them will", -1, 0+X_OFFSET,
                 110+Y_OFFSET, 0);
    GrStringDraw(pContext, "result in visible feedback of some kind.", -1, 0+X_OFFSET,
                 128+Y_OFFSET, 0);
    GrStringDraw(pContext, "Press the + and - buttons at the bottom", -1, 0+X_OFFSET,
                 146+Y_OFFSET, 0);
    GrStringDraw(pContext, "of the screen to move between the panels.", -1, 0+X_OFFSET,
                 164+Y_OFFSET, 0);
}

//*****************************************************************************
//
// Handles paint requests for the primitives canvas widget.
//
//*****************************************************************************
void
OnPrimitivePaint(tWidget *pWidget, tContext *pContext)
{
    unsigned int ulIdx;
    tRectangle sRect;

    //
    // Draw a vertical sweep of lines from red to green.
    //
    for(ulIdx = 0; ulIdx <= 8; ulIdx++)
    {
        GrContextForegroundSet(pContext,
                               (((((10 - ulIdx) * 255) / 10) << ClrRedShift) |
                                (((ulIdx * 255) / 10) << ClrGreenShift)));
        GrLineDraw(pContext, 115+X_OFFSET, 120+Y_OFFSET, 5+X_OFFSET, 120+Y_OFFSET - (11 * ulIdx));
    }

    //
    // Draw a horizontal sweep of lines from green to blue.
    //
    for(ulIdx = 1; ulIdx <= 10; ulIdx++)
    {
        GrContextForegroundSet(pContext,
                               (((((10 - ulIdx) * 255) / 10) <<
                                 ClrGreenShift) |
                                (((ulIdx * 255) / 10) << ClrBlueShift)));
        GrLineDraw(pContext, 115+X_OFFSET, 120+Y_OFFSET, 5 + (ulIdx * 11)+X_OFFSET, 29+Y_OFFSET);
    }

    //
    // Draw a filled circle with an overlapping circle.
    //
    GrContextForegroundSet(pContext, ClrBrown);
    GrCircleFill(pContext, 185+X_OFFSET, 69+Y_OFFSET, 40);
    GrContextForegroundSet(pContext, ClrSkyBlue);
    GrCircleDraw(pContext, 205+X_OFFSET, 99+Y_OFFSET, 30);

    //
    // Draw a filled rectangle with an overlapping rectangle.
    //
    GrContextForegroundSet(pContext, ClrSlateGray);
    sRect.sXMin = 20+X_OFFSET;
    sRect.sYMin = 100+Y_OFFSET;
    sRect.sXMax = 75+X_OFFSET;
    sRect.sYMax = 160+Y_OFFSET;
    GrRectFill(pContext, &sRect);
    GrContextForegroundSet(pContext, ClrSlateBlue);
    sRect.sXMin += 40;
    sRect.sYMin += 40;
    sRect.sXMax += 30;
    sRect.sYMax += 28;
    GrRectDraw(pContext, &sRect);

    //
    // Draw a piece of text in fonts of increasing size.
    //
    GrContextForegroundSet(pContext, ClrSilver);
    GrContextFontSet(pContext, &g_sFontCm14);
    GrStringDraw(pContext, "Strings", -1, 125+X_OFFSET, 110+Y_OFFSET, 0);
    GrContextFontSet(pContext, &g_sFontCm18);
    GrStringDraw(pContext, "Strings", -1, 145+X_OFFSET, 124+Y_OFFSET, 0);
    GrContextFontSet(pContext, &g_sFontCm22);
    GrStringDraw(pContext, "Strings", -1, 165+X_OFFSET, 142+Y_OFFSET, 0);
    GrContextFontSet(pContext, &g_sFontCm24);
    GrStringDraw(pContext, "Strings", -1, 185+X_OFFSET, 162+Y_OFFSET, 0);

    //
    // Draw an image.
    //
    GrImageDraw(pContext, g_TILogo, 240+X_OFFSET, 60+Y_OFFSET);
}

//*****************************************************************************
//
// Handles paint requests for the canvas demonstration widget.
//
//*****************************************************************************
void
OnCanvasPaint(tWidget *pWidget, tContext *pContext)
{
    unsigned int ulIdx;

    //
    // Draw a set of radiating lines.
    //
    GrContextForegroundSet(pContext, ClrGoldenrod);
    for(ulIdx = 50; ulIdx <= 180; ulIdx += 10)
    {
        GrLineDraw(pContext, 210+X_OFFSET, ulIdx+Y_OFFSET, 310+X_OFFSET, 230 - ulIdx+Y_OFFSET);
    }

    //
    // Indicate that the contents of this canvas were drawn by the application.
    //
    GrContextFontSet(pContext, &g_sFontCm12);
    GrStringDrawCentered(pContext, "App Drawn", -1, 260+X_OFFSET, 50+Y_OFFSET, 1);
}

//*****************************************************************************
//
// Handles change notifications for the check box widgets.
//
//*****************************************************************************
void
OnCheckChange(tWidget *pWidget, unsigned int bSelected)
{
    unsigned int ulIdx;

    //
    // Find the index of this check box.
    //
    for(ulIdx = 0; ulIdx < NUM_CHECK_BOXES; ulIdx++)
    {
        if(pWidget == (tWidget *)(g_psCheckBoxes + ulIdx))
        {
            break;
        }
    }

    //
    // Return if the check box could not be found.
    //
    if(ulIdx == NUM_CHECK_BOXES)
    {
        return;
    }

    //
    // Set the matching indicator based on the selected state of the check box.
    //
    CanvasImageSet(g_psCheckBoxIndicators + ulIdx,
                   bSelected ? g_ledON : g_ledOFF);
    WidgetPaint((tWidget *)(g_psCheckBoxIndicators + ulIdx));

    //
    // Play the key click sound.
    //
    //SoundPlay(g_pusKeyClick, sizeof(g_pusKeyClick) / 2);
	ClickPlay();
}

//*****************************************************************************
//
// Handles press notifications for the push button widgets.
//
//*****************************************************************************
void
OnButtonPress(tWidget *pWidget)
{
    unsigned int ulIdx;

    //
    // Find the index of this push button.
    //
    for(ulIdx = 0; ulIdx < NUM_PUSH_BUTTONS; ulIdx++)
    {
        if(pWidget == (tWidget *)(g_psPushButtons + ulIdx))
        {
            break;
        }
    }

    //
    // Return if the push button could not be found.
    //
    if(ulIdx == NUM_PUSH_BUTTONS)
    {
        return;
    }

    //
    // Toggle the state of this push button indicator.
    //
    g_ulButtonState ^= 1 << ulIdx;

    //
    // Set the matching indicator based on the selected state of the check box.
    //
    CanvasImageSet(g_psPushButtonIndicators + ulIdx,
                   (g_ulButtonState & (1 << ulIdx)) ? g_ledON :
                   g_ledOFF);
    WidgetPaint((tWidget *)(g_psPushButtonIndicators + ulIdx));

    //
    // Play the key click sound.
    //
    //SoundPlay(g_pusKeyClick, sizeof(g_pusKeyClick) / 2);
	ClickPlay();
}

//*****************************************************************************
//
// Handles notifications from the slider controls.
//
//*****************************************************************************
void
OnSliderChange(tWidget *pWidget, int lValue)
{
    static char pcCanvasText[5];
    static char pcSliderText[5];

    //
    // Is this the widget whose value we mirror in the canvas widget and the
    // locked slider?
    //
    if(pWidget == (tWidget *)&g_psSliders[SLIDER_CANVAS_VAL_INDEX])
    {
        //
        // Yes - update the canvas to show the slider value.
        //
        usprintf(pcCanvasText, "%3d%%", lValue);
        CanvasTextSet(&g_sSliderValueCanvas, pcCanvasText);
        WidgetPaint((tWidget *)&g_sSliderValueCanvas);

        //
        // Also update the value of the locked slider to reflect this one.
        //
        SliderValueSet(&g_psSliders[SLIDER_LOCKED_INDEX], lValue);
        WidgetPaint((tWidget *)&g_psSliders[SLIDER_LOCKED_INDEX]);
    }

    if(pWidget == (tWidget *)&g_psSliders[SLIDER_TEXT_VAL_INDEX])
    {
        //
        // Yes - update the canvas to show the slider value.
        //
        usprintf(pcSliderText, "%3d%%", lValue);
        SliderTextSet(&g_psSliders[SLIDER_TEXT_VAL_INDEX], pcSliderText);
        WidgetPaint((tWidget *)&g_psSliders[SLIDER_TEXT_VAL_INDEX]);
    }
}

//*****************************************************************************
//
// Handles change notifications for the radio button widgets.
//
//*****************************************************************************
void
OnRadioChange(tWidget *pWidget, unsigned int bSelected)
{
    unsigned int ulIdx;

    //
    // Find the index of this radio button in the first group.
    //
    for(ulIdx = 0; ulIdx < NUM_RADIO1_BUTTONS; ulIdx++)
    {
        if(pWidget == (tWidget *)(g_psRadioButtons1 + ulIdx))
        {
            break;
        }
    }

    //
    // See if the radio button was found.
    //
    if(ulIdx == NUM_RADIO1_BUTTONS)
    {
        //
        // Find the index of this radio button in the second group.
        //
        for(ulIdx = 0; ulIdx < NUM_RADIO2_BUTTONS; ulIdx++)
        {
            if(pWidget == (tWidget *)(g_psRadioButtons2 + ulIdx))
            {
                break;
            }
        }

        //
        // Return if the radio button could not be found.
        //
        if(ulIdx == NUM_RADIO2_BUTTONS)
        {
            return;
        }

        //
        // Sind the radio button is in the second group, offset the index to
        // the indicators associated with the second group.
        //
        ulIdx += NUM_RADIO1_BUTTONS;
    }

    //
    // Set the matching indicator based on the selected state of the radio
    // button.
    //
    CanvasImageSet(g_psRadioButtonIndicators + ulIdx,
                   bSelected ? g_ledON : g_ledOFF);
    WidgetPaint((tWidget *)(g_psRadioButtonIndicators + ulIdx));

    //
    // Play the key click sound.
    //
    //SoundPlay(g_pusKeyClick, sizeof(g_pusKeyClick) / 2);
	ClickPlay();
}

void delay(volatile unsigned int value)
{
	while(value--);
}

int main(void)
{
    int xCoOd = 0, yCoOd = 0;
    char pressure = 0, touched = 0;
    unsigned int i = 0;
    unsigned char *dest;
    unsigned char *src;

    SetupIntc();

    SetUpLCD();
  
    /* configuring the base ceiling */
    RasterDMAFBConfig(SOC_LCDC_0_REGS, 
                      (unsigned int)(g_pucBuffer+PALETTE_OFFSET),
                      (unsigned int)(g_pucBuffer+PALETTE_OFFSET) + sizeof(g_pucBuffer) - 2 -
					  PALETTE_OFFSET, FRAME_BUFFER_0);

    RasterDMAFBConfig(SOC_LCDC_0_REGS, 
                      (unsigned int)(g_pucBuffer+PALETTE_OFFSET),
                      (unsigned int)(g_pucBuffer+PALETTE_OFFSET) + sizeof(g_pucBuffer) - 2 - 
					  PALETTE_OFFSET, FRAME_BUFFER_1);

    src = (unsigned char *) palette_32b;
    dest = (unsigned char *) (g_pucBuffer+PALETTE_OFFSET);

    // Copy palette info into buffer
    for( i = PALETTE_OFFSET; i < (PALETTE_SIZE+PALETTE_OFFSET); i++)
	{
		*dest++ = *src++;
	}

	// copy splash screen
	/*src = (unsigned char *)&splash[40];
	for(; i < LCD_SIZE; i++)
	{
		*dest++ = *src++;
	}*/
		
	GrOffScreen16BPPInit(&g_sSHARP480x272x16Display, g_pucBuffer, LCD_WIDTH, LCD_HEIGHT);
	
	// Initialize a drawing context.
	GrContextInit(&sContext, &g_sSHARP480x272x16Display);

    /* enable End of frame interrupt */
    RasterEndOfFrameIntEnable(SOC_LCDC_0_REGS);

    /* enable raster */
    RasterEnable(SOC_LCDC_0_REGS);

    /* Enable display panel backlight and power */
    ConfigRasterDisplayEnable();

    DisplayGR();
	
	SoundInit();

    // TS init
    PeripheralsSetup();
    InitTouchScreen();
	
    // Loop forever handling widget messages.    
    while(1)
	{
		while(!touched)
		{
			ReadAxis(2, &pressure, &touched);
		}
		
        /* Resolving the coordinates of the touched location.*/
        ResolveCoordinates(&xCoOd, &yCoOd);
		
		do
		{
			WidgetPointerMessage(WIDGET_MSG_PTR_DOWN, xCoOd, yCoOd);
			
			// Process any messages in the widget message queue.
			WidgetMessageQueueProcess();

            ResolveCoordinates(&xCoOd, &yCoOd);
			ReadAxis(2, &pressure, &touched);
        }while(touched);
		
		WidgetPointerMessage(WIDGET_MSG_PTR_UP, xCoOd, yCoOd);
		WidgetMessageQueueProcess();
	}
	
}

/*
** Configures raster to display image 
*/
static void SetUpLCD(void)
{
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_LCDC, PSC_POWERDOMAIN_ALWAYS_ON,
             PSC_MDCTL_NEXT_ENABLE);

    LCDPinMuxSetup();

    /* disable raster */
    RasterDisable(SOC_LCDC_0_REGS);
    
    /* configure the pclk */
    RasterClkConfig(SOC_LCDC_0_REGS, 7833600, LCD_CLK);

    /* configuring DMA of LCD controller */ 
    RasterDMAConfig(SOC_LCDC_0_REGS, RASTER_DOUBLE_FRAME_BUFFER,
                    RASTER_BURST_SIZE_16, RASTER_FIFO_THRESHOLD_8,
                    RASTER_BIG_ENDIAN_DISABLE);

    /* configuring modes(ex:tft or stn,color or monochrome etc) for raster controller */
    RasterModeConfig(SOC_LCDC_0_REGS, RASTER_DISPLAY_MODE_TFT,
                     RASTER_PALETTE_DATA, RASTER_COLOR, RASTER_RIGHT_ALIGNED);

    /* frame buffer data is ordered from least to Most significant bye */
    RasterLSBDataOrderSelect(SOC_LCDC_0_REGS);
    
    /* disable nibble mode */
    RasterNibbleModeDisable(SOC_LCDC_0_REGS);
   
     /* configuring the polarity of timing parameters of raster controller */
    RasterTiming2Configure(SOC_LCDC_0_REGS, RASTER_FRAME_CLOCK_LOW |
                                            RASTER_LINE_CLOCK_LOW  |
                                            RASTER_PIXEL_CLOCK_LOW |
                                            RASTER_SYNC_EDGE_RISING|
                                            RASTER_SYNC_CTRL_ACTIVE|
                                            RASTER_AC_BIAS_HIGH     , 0, 255);

    /* configuring horizontal timing parameter */
   RasterHparamConfig(SOC_LCDC_0_REGS, 480, 41, 2, 2);

    /* configuring vertical timing parameters */
   RasterVparamConfig(SOC_LCDC_0_REGS, 272, 10, 3, 3);

   /* configuring fifo delay to */
   RasterFIFODMADelayConfig(SOC_LCDC_0_REGS, (17647058/8823529));
}

/*
** configures arm interrupt controller to generate raster interrupt 
*/
static void SetupIntc(void)
{
    /* Initialize the ARM Interrupt Controller.*/
    IntAINTCInit();

    /* Register the ISR in the Interrupt Vector Table.*/
    IntRegister(SYS_INT_LCDINT, LCDIsr);

    /* Set the channnel number 2 of AINTC for LCD system interrupt.
     */
    IntChannelSet(SYS_INT_LCDINT, 2);

    /* Enable the System Interrupts for AINTC.*/
    IntSystemEnable(SYS_INT_LCDINT);

    /* Enable IRQ in CPSR.*/
    IntMasterIRQEnable();

    /* Enable the interrupts in GER of AINTC.*/
    IntGlobalEnable();

    /* Enable the interrupts in HIER of AINTC.*/
    IntIRQEnable();
}

/*
** For each end of frame interrupt base and ceiling is reconfigured 
*/
static void LCDIsr(void)
{
    unsigned int  status;

    IntSystemStatusClear(SYS_INT_LCDINT);

    status = RasterIntStatus(SOC_LCDC_0_REGS,RASTER_END_OF_FRAME0_INT_STAT |
                                             RASTER_END_OF_FRAME1_INT_STAT );

    status = RasterClearGetIntStatus(SOC_LCDC_0_REGS, status);   

    if (status & RASTER_END_OF_FRAME0_INT_STAT)
    {
        /* configuring the base ceiling */
        RasterDMAFBConfig(SOC_LCDC_0_REGS, 
                          (unsigned int)(g_pucBuffer+4),
                          (unsigned int)(g_pucBuffer+4) + sizeof(g_pucBuffer) - 2 - 4,
                          0);
    }

    if(status & RASTER_END_OF_FRAME1_INT_STAT)
    {

        RasterDMAFBConfig(SOC_LCDC_0_REGS,
                          (unsigned int)(g_pucBuffer+4),
                          (unsigned int)(g_pucBuffer+4) + sizeof(g_pucBuffer) - 2 - 4,
                          1);
    }
}


static void DisplayGR(void)
{
    tRectangle sRect;

    // Fill the top 24 rows of the screen with blue to create the banner.
    sRect.sXMin = 0;
    sRect.sYMin = 0;
    sRect.sXMax = GrContextDpyWidthGet(&sContext) - 1;
    sRect.sYMax = 23;
    GrContextForegroundSet(&sContext, ClrDarkBlue);
    GrRectFill(&sContext, &sRect);

    // Put a white box around the banner.
    GrContextForegroundSet(&sContext, ClrWhite);
    GrRectDraw(&sContext, &sRect);

    // Put the application name in the middle of the banner.
    GrContextFontSet(&sContext, &g_sFontCm20);
    GrStringDrawCentered(&sContext, "grlib demo", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 8, 0);
						 
	GrStringDrawCentered(&sContext, "Touch here to proceed ", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 140, 0);
						 

    // Initialize the sound driver.

    // Add the title block and the previous and next buttons to the widget tree.
    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sPrevious);
    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sTitle);
    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sNext);

    // Add the first panel to the widget tree.
    g_ulPanel = 0;
    WidgetAdd(WIDGET_ROOT, (tWidget *)g_psPanels);
    CanvasTextSet(&g_sTitle, g_pcPanelNames[0]);

    // Issue the initial paint request to the widgets.
    //WidgetPaint(WIDGET_ROOT);
	WidgetMessageQueueAdd(WIDGET_ROOT, WIDGET_MSG_PAINT, 0, 0, 0, 0);

}



void I2CIsr(void)
{
    (*I2CpFunc)();
}

void ConfigureAINTCIntI2C(void)
{
    /* Register the ISR in the Interrupt Vector Table.*/
    IntRegister(SYS_INT_I2CINT0, I2CIsr);

    IntChannelSet(SYS_INT_I2CINT0, 3);

    /* Enable the System Interrupts for AINTC.*/
    IntSystemEnable(SYS_INT_I2CINT0);
}

void I2CSetup(void)
{
    I2CPinMuxSetup(0);

    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2C_0_REGS);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk(SOC_I2C_0_REGS, 24000000, 8000000, 100000);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2C_0_REGS, 0x48);
    ConfigureAINTCIntI2C();
}

static void PeripheralsSetup(void)
{
    I2CSetup();
}

/*
** Initializes the I2C interface for a slave
*/
void I2C0IfConfig(unsigned int slaveAddr, unsigned int speed)
{
    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2C_0_REGS);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk(SOC_I2C_0_REGS, 24000000, 8000000, speed);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2C_0_REGS, slaveAddr);

    I2CMasterEnable(SOC_I2C_0_REGS);
}

void ClickPlay(void)
{
	// I2C in Codec mode
	I2CCodecIfInit(SOC_I2C_0_REGS, INT_CHANNEL_I2C, I2C_SLAVE_CODEC_AIC31);
	
	// play sound
	SoundClickPlay((unsigned char*)toneRaw, sizeof(toneRaw));
	
	// I2C in TS mode
	I2C0IfConfig(I2C_SLAVE_PMIC_ADDR, 50000);
	ConfigureAINTCIntI2C();
	
	delay(0x9FFFF);
}
