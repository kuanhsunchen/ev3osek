<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:703dd69d-4931-439f-b49d-a41adb7f0f89(oil.event.textGen)">
  <persistence version="9" />
  <languages>
    <use id="b83431fe-5c8f-40bc-8a36-65e25f4dd253" name="jetbrains.mps.lang.textGen" version="0" />
    <use id="7866978e-a0f0-4cc7-81bc-4d213d9375e1" name="jetbrains.mps.lang.smodel" version="2" />
    <use id="f3061a53-9226-4cc5-a443-f952ceaf5816" name="jetbrains.mps.baseLanguage" version="4" />
    <devkit ref="fbc25dd2-5da4-483a-8b19-70928e1b62d7(jetbrains.mps.devkit.general-purpose)" />
  </languages>
  <imports>
    <import index="tpck" ref="r:00000000-0000-4000-0000-011c89590288(jetbrains.mps.lang.core.structure)" />
    <import index="rx5q" ref="r:8e560f65-464b-43d8-97bf-faadc37f178e(oil.event.structure)" implicit="true" />
    <import index="x27k" ref="r:75ecab8a-8931-4140-afc6-4b46398710fc(com.mbeddr.core.modules.structure)" implicit="true" />
  </imports>
  <registry>
    <language id="f3061a53-9226-4cc5-a443-f952ceaf5816" name="jetbrains.mps.baseLanguage">
      <concept id="1197027756228" name="jetbrains.mps.baseLanguage.structure.DotExpression" flags="nn" index="2OqwBi">
        <child id="1197027771414" name="operand" index="2Oq$k0" />
        <child id="1197027833540" name="operation" index="2OqNvi" />
      </concept>
      <concept id="1137021947720" name="jetbrains.mps.baseLanguage.structure.ConceptFunction" flags="in" index="2VMwT0">
        <child id="1137022507850" name="body" index="2VODD2" />
      </concept>
      <concept id="1068580123136" name="jetbrains.mps.baseLanguage.structure.StatementList" flags="sn" stub="5293379017992965193" index="3clFbS">
        <child id="1068581517665" name="statement" index="3cqZAp" />
      </concept>
    </language>
    <language id="b83431fe-5c8f-40bc-8a36-65e25f4dd253" name="jetbrains.mps.lang.textGen">
      <concept id="1237305208784" name="jetbrains.mps.lang.textGen.structure.NewLineAppendPart" flags="ng" index="l8MVK" />
      <concept id="1237305334312" name="jetbrains.mps.lang.textGen.structure.NodeAppendPart" flags="ng" index="l9hG8">
        <child id="1237305790512" name="value" index="lb14g" />
      </concept>
      <concept id="1237305557638" name="jetbrains.mps.lang.textGen.structure.ConstantStringAppendPart" flags="ng" index="la8eA">
        <property id="1237305576108" name="value" index="lacIc" />
        <property id="1237306361677" name="withIndent" index="ldcpH" />
      </concept>
      <concept id="1237306079178" name="jetbrains.mps.lang.textGen.structure.AppendOperation" flags="nn" index="lc7rE">
        <child id="1237306115446" name="part" index="lcghm" />
      </concept>
      <concept id="4357423944233036906" name="jetbrains.mps.lang.textGen.structure.IndentPart" flags="ng" index="2BGw6n" />
      <concept id="1233670071145" name="jetbrains.mps.lang.textGen.structure.ConceptTextGenDeclaration" flags="ig" index="WtQ9Q">
        <reference id="1233670257997" name="conceptDeclaration" index="WuzLi" />
        <child id="1233749296504" name="textGenBlock" index="11c4hB" />
      </concept>
      <concept id="1233748055915" name="jetbrains.mps.lang.textGen.structure.NodeParameter" flags="nn" index="117lpO" />
      <concept id="1233749247888" name="jetbrains.mps.lang.textGen.structure.GenerateTextDeclaration" flags="in" index="11bSqf" />
    </language>
    <language id="7866978e-a0f0-4cc7-81bc-4d213d9375e1" name="jetbrains.mps.lang.smodel">
      <concept id="1138056022639" name="jetbrains.mps.lang.smodel.structure.SPropertyAccess" flags="nn" index="3TrcHB">
        <reference id="1138056395725" name="property" index="3TsBF5" />
      </concept>
      <concept id="1138056143562" name="jetbrains.mps.lang.smodel.structure.SLinkAccess" flags="nn" index="3TrEf2">
        <reference id="1138056516764" name="link" index="3Tt5mk" />
      </concept>
    </language>
  </registry>
  <node concept="WtQ9Q" id="1Y5JHpRzrdh">
    <ref role="WuzLi" to="rx5q:1x4fgD956ve" resolve="EventRef" />
    <node concept="11bSqf" id="1Y5JHpRzrdi" role="11c4hB">
      <node concept="3clFbS" id="1Y5JHpRzrdj" role="2VODD2">
        <node concept="lc7rE" id="1Y5JHpRzrdv" role="3cqZAp">
          <node concept="la8eA" id="4B0n6H27T1a" role="lcghm">
            <property role="lacIc" value="EVENT = " />
            <property role="ldcpH" value="true" />
          </node>
          <node concept="l9hG8" id="1Y5JHpRzrPc" role="lcghm">
            <node concept="2OqwBi" id="1Y5JHpRzsjL" role="lb14g">
              <node concept="2OqwBi" id="1Y5JHpRzrU6" role="2Oq$k0">
                <node concept="117lpO" id="1Y5JHpRzrPW" role="2Oq$k0" />
                <node concept="3TrEf2" id="1Y5JHpRzs4i" role="2OqNvi">
                  <ref role="3Tt5mk" to="rx5q:1x4fgD956y9" />
                </node>
              </node>
              <node concept="3TrcHB" id="1Y5JHpRzsyh" role="2OqNvi">
                <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
              </node>
            </node>
          </node>
          <node concept="la8eA" id="4B0n6H27TcT" role="lcghm">
            <property role="lacIc" value=";" />
          </node>
          <node concept="l8MVK" id="4B0n6H27Tgp" role="lcghm" />
        </node>
      </node>
    </node>
  </node>
  <node concept="WtQ9Q" id="4osOqZkmveU">
    <ref role="WuzLi" to="rx5q:1x4fgD956iF" resolve="EventLiteral" />
    <node concept="11bSqf" id="4osOqZkmveV" role="11c4hB">
      <node concept="3clFbS" id="4osOqZkmveW" role="2VODD2">
        <node concept="lc7rE" id="3QwuWjHkYtA" role="3cqZAp">
          <node concept="2BGw6n" id="7_fwX8D8JFa" role="lcghm" />
          <node concept="la8eA" id="3QwuWjHkYtO" role="lcghm">
            <property role="lacIc" value="EVENT " />
          </node>
          <node concept="l9hG8" id="3QwuWjHkYuv" role="lcghm">
            <node concept="2OqwBi" id="3QwuWjHkYxk" role="lb14g">
              <node concept="117lpO" id="3QwuWjHkYvg" role="2Oq$k0" />
              <node concept="3TrcHB" id="3QwuWjHkY_G" role="2OqNvi">
                <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
              </node>
            </node>
          </node>
          <node concept="la8eA" id="3QwuWjHkYE2" role="lcghm">
            <property role="lacIc" value="{ MASK = " />
          </node>
          <node concept="l9hG8" id="4osOqZkmvoM" role="lcghm">
            <node concept="2OqwBi" id="4osOqZkmvwF" role="lb14g">
              <node concept="117lpO" id="4osOqZkmvrh" role="2Oq$k0" />
              <node concept="3TrEf2" id="4osOqZkmvTQ" role="2OqNvi">
                <ref role="3Tt5mk" to="rx5q:78S7ngm5xPO" />
              </node>
            </node>
          </node>
          <node concept="la8eA" id="4osOqZkmvYN" role="lcghm">
            <property role="lacIc" value="; };" />
          </node>
          <node concept="l8MVK" id="4osOqZkmG2_" role="lcghm" />
        </node>
      </node>
    </node>
  </node>
  <node concept="WtQ9Q" id="4B0n6H27mLj">
    <ref role="WuzLi" to="rx5q:4B0n6H25BL_" resolve="EventDeclaration" />
    <node concept="11bSqf" id="4B0n6H27mLk" role="11c4hB">
      <node concept="3clFbS" id="4B0n6H27mLl" role="2VODD2">
        <node concept="lc7rE" id="4B0n6H27mLx" role="3cqZAp">
          <node concept="l9hG8" id="4B0n6H27mLJ" role="lcghm">
            <node concept="2OqwBi" id="4B0n6H27mUC" role="lb14g">
              <node concept="117lpO" id="4B0n6H27mMv" role="2Oq$k0" />
              <node concept="3TrEf2" id="4B0n6H27nyL" role="2OqNvi">
                <ref role="3Tt5mk" to="x27k:2VsHNE717Q8" />
              </node>
            </node>
          </node>
        </node>
      </node>
    </node>
  </node>
</model>

