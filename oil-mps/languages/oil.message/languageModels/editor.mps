<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:16477d22-507d-423d-acea-7bc706a6d9d8(oil.message.editor)">
  <persistence version="9" />
  <languages>
    <use id="18bc6592-03a6-4e29-a83a-7ff23bde13ba" name="jetbrains.mps.lang.editor" version="3" />
    <devkit ref="fbc25dd2-5da4-483a-8b19-70928e1b62d7(jetbrains.mps.devkit.general-purpose)" />
  </languages>
  <imports>
    <import index="qx8g" ref="r:264779d5-6695-4b5b-ba0a-eb616299242f(oil.message.structure)" implicit="true" />
    <import index="tpck" ref="r:00000000-0000-4000-0000-011c89590288(jetbrains.mps.lang.core.structure)" implicit="true" />
  </imports>
  <registry>
    <language id="18bc6592-03a6-4e29-a83a-7ff23bde13ba" name="jetbrains.mps.lang.editor">
      <concept id="1071666914219" name="jetbrains.mps.lang.editor.structure.ConceptEditorDeclaration" flags="ig" index="24kQdi" />
      <concept id="1237303669825" name="jetbrains.mps.lang.editor.structure.CellLayout_Indent" flags="nn" index="l2Vlx" />
      <concept id="1080736578640" name="jetbrains.mps.lang.editor.structure.BaseEditorComponent" flags="ig" index="2wURMF">
        <child id="1080736633877" name="cellModel" index="2wV5jI" />
      </concept>
      <concept id="1088013125922" name="jetbrains.mps.lang.editor.structure.CellModel_RefCell" flags="sg" stub="730538219795941030" index="1iCGBv">
        <child id="1088186146602" name="editorComponent" index="1sWHZn" />
      </concept>
      <concept id="1088185857835" name="jetbrains.mps.lang.editor.structure.InlineEditorComponent" flags="ig" index="1sVBvm" />
      <concept id="1139848536355" name="jetbrains.mps.lang.editor.structure.CellModel_WithRole" flags="ng" index="1$h60E">
        <property id="1140017977771" name="readOnly" index="1Intyy" />
        <reference id="1140103550593" name="relationDeclaration" index="1NtTu8" />
      </concept>
      <concept id="1073389446423" name="jetbrains.mps.lang.editor.structure.CellModel_Collection" flags="sn" stub="3013115976261988961" index="3EZMnI">
        <child id="1106270802874" name="cellLayout" index="2iSdaV" />
        <child id="1073389446424" name="childCellModel" index="3EZMnx" />
      </concept>
      <concept id="1073389577006" name="jetbrains.mps.lang.editor.structure.CellModel_Constant" flags="sn" stub="3610246225209162225" index="3F0ifn">
        <property id="1073389577007" name="text" index="3F0ifm" />
      </concept>
      <concept id="1073389658414" name="jetbrains.mps.lang.editor.structure.CellModel_Property" flags="sg" stub="730538219796134133" index="3F0A7n" />
      <concept id="1166049232041" name="jetbrains.mps.lang.editor.structure.AbstractComponent" flags="ng" index="1XWOmA">
        <reference id="1166049300910" name="conceptDeclaration" index="1XX52x" />
      </concept>
    </language>
  </registry>
  <node concept="24kQdi" id="2q8YB8RhyUf">
    <ref role="1XX52x" to="qx8g:1x4fgD956$h" resolve="MessageType" />
    <node concept="3EZMnI" id="2q8YB8RhyUh" role="2wV5jI">
      <node concept="3F0ifn" id="2q8YB8RhyUo" role="3EZMnx">
        <property role="3F0ifm" value="(M)" />
      </node>
      <node concept="1iCGBv" id="2q8YB8RhyUy" role="3EZMnx">
        <ref role="1NtTu8" to="qx8g:1x4fgD956$i" />
        <node concept="1sVBvm" id="2q8YB8RhyU$" role="1sWHZn">
          <node concept="3F0A7n" id="2q8YB8RhyUJ" role="2wV5jI">
            <property role="1Intyy" value="true" />
            <ref role="1NtTu8" to="tpck:h0TrG11" resolve="name" />
          </node>
        </node>
      </node>
      <node concept="l2Vlx" id="2q8YB8RhyUk" role="2iSdaV" />
    </node>
  </node>
  <node concept="24kQdi" id="1eGaHOMvqOe">
    <ref role="1XX52x" to="qx8g:1x4fgD956kb" resolve="Message" />
    <node concept="3EZMnI" id="1eGaHOMvqOg" role="2wV5jI">
      <node concept="3F0ifn" id="1eGaHOMvqOn" role="3EZMnx">
        <property role="3F0ifm" value="Message" />
      </node>
      <node concept="3F0A7n" id="1eGaHOMvqOx" role="3EZMnx">
        <ref role="1NtTu8" to="tpck:h0TrG11" resolve="name" />
      </node>
      <node concept="l2Vlx" id="1eGaHOMvqOj" role="2iSdaV" />
    </node>
  </node>
</model>

