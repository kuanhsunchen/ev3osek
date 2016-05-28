<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:6080ec09-c756-4f2a-9d90-7695b076e53c(de.whz.osek.behavior)">
  <persistence version="9" />
  <languages>
    <use id="af65afd8-f0dd-4942-87d9-63a55f2a9db1" name="jetbrains.mps.lang.behavior" version="0" />
    <use id="f3061a53-9226-4cc5-a443-f952ceaf5816" name="jetbrains.mps.baseLanguage" version="4" />
    <use id="7866978e-a0f0-4cc7-81bc-4d213d9375e1" name="jetbrains.mps.lang.smodel" version="2" />
    <use id="83888646-71ce-4f1c-9c53-c54016f6ad4f" name="jetbrains.mps.baseLanguage.collections" version="0" />
    <devkit ref="fbc25dd2-5da4-483a-8b19-70928e1b62d7(jetbrains.mps.devkit.general-purpose)" />
  </languages>
  <imports>
    <import index="bwbq" ref="r:aa04fc7a-6e20-48c4-b6ac-7c1ce8638ec4(de.whz.osek.structure)" />
    <import index="hwgx" ref="r:fd2980c8-676c-4b19-b524-18c70e02f8b7(com.mbeddr.core.base.behavior)" />
    <import index="ywuz" ref="r:c6ce92e7-5a98-4a6f-866a-ec8b9e945dd8(com.mbeddr.core.expressions.behavior)" />
    <import index="tpck" ref="r:00000000-0000-4000-0000-011c89590288(jetbrains.mps.lang.core.structure)" />
    <import index="x27k" ref="r:75ecab8a-8931-4140-afc6-4b46398710fc(com.mbeddr.core.modules.structure)" />
    <import index="vs0r" ref="r:f7764ca4-8c75-4049-922b-08516400a727(com.mbeddr.core.base.structure)" />
    <import index="mj1l" ref="r:c371cf98-dcc8-4a43-8eb8-8a8096de18b2(com.mbeddr.core.expressions.structure)" />
    <import index="wyt6" ref="6354ebe7-c22a-4a0f-ac54-50b52ab9b065/java:java.lang(JDK/)" implicit="true" />
  </imports>
  <registry>
    <language id="af65afd8-f0dd-4942-87d9-63a55f2a9db1" name="jetbrains.mps.lang.behavior">
      <concept id="1225194240794" name="jetbrains.mps.lang.behavior.structure.ConceptBehavior" flags="ng" index="13h7C7">
        <reference id="1225194240799" name="concept" index="13h7C2" />
        <child id="1225194240805" name="method" index="13h7CS" />
        <child id="1225194240801" name="constructor" index="13h7CW" />
      </concept>
      <concept id="1225194413805" name="jetbrains.mps.lang.behavior.structure.ConceptConstructorDeclaration" flags="in" index="13hLZK" />
      <concept id="1225194472830" name="jetbrains.mps.lang.behavior.structure.ConceptMethodDeclaration" flags="ng" index="13i0hz">
        <property id="1225194472832" name="isVirtual" index="13i0it" />
        <property id="1225194472834" name="isAbstract" index="13i0iv" />
        <reference id="1225194472831" name="overriddenMethod" index="13i0hy" />
      </concept>
      <concept id="1225194691553" name="jetbrains.mps.lang.behavior.structure.ThisNodeExpression" flags="nn" index="13iPFW" />
    </language>
    <language id="f3061a53-9226-4cc5-a443-f952ceaf5816" name="jetbrains.mps.baseLanguage">
      <concept id="1215693861676" name="jetbrains.mps.baseLanguage.structure.BaseAssignmentExpression" flags="nn" index="d038R">
        <child id="1068498886297" name="rValue" index="37vLTx" />
        <child id="1068498886295" name="lValue" index="37vLTJ" />
      </concept>
      <concept id="1197027756228" name="jetbrains.mps.baseLanguage.structure.DotExpression" flags="nn" index="2OqwBi">
        <child id="1197027771414" name="operand" index="2Oq$k0" />
        <child id="1197027833540" name="operation" index="2OqNvi" />
      </concept>
      <concept id="1145552977093" name="jetbrains.mps.baseLanguage.structure.GenericNewExpression" flags="nn" index="2ShNRf">
        <child id="1145553007750" name="creator" index="2ShVmc" />
      </concept>
      <concept id="1137021947720" name="jetbrains.mps.baseLanguage.structure.ConceptFunction" flags="in" index="2VMwT0">
        <child id="1137022507850" name="body" index="2VODD2" />
      </concept>
      <concept id="1070475926800" name="jetbrains.mps.baseLanguage.structure.StringLiteral" flags="nn" index="Xl_RD">
        <property id="1070475926801" name="value" index="Xl_RC" />
      </concept>
      <concept id="1070534644030" name="jetbrains.mps.baseLanguage.structure.BooleanType" flags="in" index="10P_77" />
      <concept id="1068431474542" name="jetbrains.mps.baseLanguage.structure.VariableDeclaration" flags="ng" index="33uBYm">
        <child id="1068431790190" name="initializer" index="33vP2m" />
      </concept>
      <concept id="1068498886296" name="jetbrains.mps.baseLanguage.structure.VariableReference" flags="nn" index="37vLTw">
        <reference id="1068581517664" name="variableDeclaration" index="3cqZAo" />
      </concept>
      <concept id="1068498886292" name="jetbrains.mps.baseLanguage.structure.ParameterDeclaration" flags="ir" index="37vLTG" />
      <concept id="1068498886294" name="jetbrains.mps.baseLanguage.structure.AssignmentExpression" flags="nn" index="37vLTI" />
      <concept id="1225271177708" name="jetbrains.mps.baseLanguage.structure.StringType" flags="in" index="17QB3L" />
      <concept id="4972933694980447171" name="jetbrains.mps.baseLanguage.structure.BaseVariableDeclaration" flags="ng" index="19Szcq">
        <child id="5680397130376446158" name="type" index="1tU5fm" />
      </concept>
      <concept id="1068580123132" name="jetbrains.mps.baseLanguage.structure.BaseMethodDeclaration" flags="ng" index="3clF44">
        <child id="1068580123133" name="returnType" index="3clF45" />
        <child id="1068580123134" name="parameter" index="3clF46" />
        <child id="1068580123135" name="body" index="3clF47" />
      </concept>
      <concept id="1068580123155" name="jetbrains.mps.baseLanguage.structure.ExpressionStatement" flags="nn" index="3clFbF">
        <child id="1068580123156" name="expression" index="3clFbG" />
      </concept>
      <concept id="1068580123136" name="jetbrains.mps.baseLanguage.structure.StatementList" flags="sn" stub="5293379017992965193" index="3clFbS">
        <child id="1068581517665" name="statement" index="3cqZAp" />
      </concept>
      <concept id="1068580123137" name="jetbrains.mps.baseLanguage.structure.BooleanConstant" flags="nn" index="3clFbT">
        <property id="1068580123138" name="value" index="3clFbU" />
      </concept>
      <concept id="1068580320020" name="jetbrains.mps.baseLanguage.structure.IntegerConstant" flags="nn" index="3cmrfG">
        <property id="1068580320021" name="value" index="3cmrfH" />
      </concept>
      <concept id="1068581242864" name="jetbrains.mps.baseLanguage.structure.LocalVariableDeclarationStatement" flags="nn" index="3cpWs8">
        <child id="1068581242865" name="localVariableDeclaration" index="3cpWs9" />
      </concept>
      <concept id="1068581242863" name="jetbrains.mps.baseLanguage.structure.LocalVariableDeclaration" flags="nr" index="3cpWsn" />
      <concept id="1068581517677" name="jetbrains.mps.baseLanguage.structure.VoidType" flags="in" index="3cqZAl" />
      <concept id="1107535904670" name="jetbrains.mps.baseLanguage.structure.ClassifierType" flags="in" index="3uibUv">
        <reference id="1107535924139" name="classifier" index="3uigEE" />
      </concept>
      <concept id="1178549954367" name="jetbrains.mps.baseLanguage.structure.IVisible" flags="ng" index="1B3ioH">
        <child id="1178549979242" name="visibility" index="1B3o_S" />
      </concept>
      <concept id="1146644602865" name="jetbrains.mps.baseLanguage.structure.PublicVisibility" flags="nn" index="3Tm1VV" />
    </language>
    <language id="7866978e-a0f0-4cc7-81bc-4d213d9375e1" name="jetbrains.mps.lang.smodel">
      <concept id="1138661924179" name="jetbrains.mps.lang.smodel.structure.Property_SetOperation" flags="nn" index="tyxLq">
        <child id="1138662048170" name="value" index="tz02z" />
      </concept>
      <concept id="1145383075378" name="jetbrains.mps.lang.smodel.structure.SNodeListType" flags="in" index="2I9FWS" />
      <concept id="1145567426890" name="jetbrains.mps.lang.smodel.structure.SNodeListCreator" flags="nn" index="2T8Vx0">
        <child id="1145567471833" name="createdType" index="2T96Bj" />
      </concept>
      <concept id="1140137987495" name="jetbrains.mps.lang.smodel.structure.SNodeTypeCastExpression" flags="nn" index="1PxgMI">
        <reference id="1140138128738" name="concept" index="1PxNhF" />
        <child id="1140138123956" name="leftExpression" index="1PxMeX" />
      </concept>
      <concept id="1138055754698" name="jetbrains.mps.lang.smodel.structure.SNodeType" flags="in" index="3Tqbb2">
        <reference id="1138405853777" name="concept" index="ehGHo" />
      </concept>
      <concept id="1138056022639" name="jetbrains.mps.lang.smodel.structure.SPropertyAccess" flags="nn" index="3TrcHB">
        <reference id="1138056395725" name="property" index="3TsBF5" />
      </concept>
      <concept id="1138056143562" name="jetbrains.mps.lang.smodel.structure.SLinkAccess" flags="nn" index="3TrEf2">
        <reference id="1138056516764" name="link" index="3Tt5mk" />
      </concept>
    </language>
    <language id="ceab5195-25ea-4f22-9b92-103b95ca8c0c" name="jetbrains.mps.lang.core">
      <concept id="1133920641626" name="jetbrains.mps.lang.core.structure.BaseConcept" flags="ng" index="2VYdi">
        <property id="1193676396447" name="virtualPackage" index="3GE5qa" />
      </concept>
      <concept id="1169194658468" name="jetbrains.mps.lang.core.structure.INamedConcept" flags="ng" index="TrEIO">
        <property id="1169194664001" name="name" index="TrG5h" />
      </concept>
    </language>
    <language id="83888646-71ce-4f1c-9c53-c54016f6ad4f" name="jetbrains.mps.baseLanguage.collections">
      <concept id="540871147943773365" name="jetbrains.mps.baseLanguage.collections.structure.SingleArgumentSequenceOperation" flags="nn" index="25WWJ4">
        <child id="540871147943773366" name="argument" index="25WWJ7" />
      </concept>
      <concept id="1151689724996" name="jetbrains.mps.baseLanguage.collections.structure.SequenceType" flags="in" index="A3Dl8">
        <child id="1151689745422" name="elementType" index="A3Ik2" />
      </concept>
      <concept id="1160612413312" name="jetbrains.mps.baseLanguage.collections.structure.AddElementOperation" flags="nn" index="TSZUe" />
    </language>
  </registry>
  <node concept="13h7C7" id="2UjW4IkGDFE">
    <ref role="13h7C2" to="bwbq:2UjW4IkGBZG" resolve="User1msIsrType2" />
    <node concept="13hLZK" id="2UjW4IkGDFF" role="13h7CW">
      <node concept="3clFbS" id="2UjW4IkGDFG" role="2VODD2">
        <node concept="3clFbF" id="2UjW4IkGDFI" role="3cqZAp">
          <node concept="2OqwBi" id="2UjW4IkGEh9" role="3clFbG">
            <node concept="2OqwBi" id="2UjW4IkGDPt" role="2Oq$k0">
              <node concept="13iPFW" id="2UjW4IkGDFH" role="2Oq$k0" />
              <node concept="3TrcHB" id="2UjW4IkGEf8" role="2OqNvi">
                <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
              </node>
            </node>
            <node concept="tyxLq" id="2UjW4IkGEmI" role="2OqNvi">
              <node concept="Xl_RD" id="2UjW4IkGEn9" role="tz02z">
                <property role="Xl_RC" value="User1msIsrType2" />
              </node>
            </node>
          </node>
        </node>
      </node>
    </node>
  </node>
  <node concept="13h7C7" id="4B0n6H258gT">
    <ref role="13h7C2" to="bwbq:4B0n6H25803" resolve="OilObjectRef" />
    <node concept="13i0hz" id="2JIP8cA02dc" role="13h7CS">
      <property role="TrG5h" value="renderReadable" />
      <ref role="13i0hy" to="ywuz:1VQvajLb13M" resolve="renderReadable" />
      <node concept="3clFbS" id="2JIP8cA02dd" role="3clF47">
        <node concept="3clFbF" id="2JIP8cA02dg" role="3cqZAp">
          <node concept="2OqwBi" id="2JIP8cA02eQ" role="3clFbG">
            <node concept="2OqwBi" id="2JIP8cA02dA" role="2Oq$k0">
              <node concept="13iPFW" id="2JIP8cA02dh" role="2Oq$k0" />
              <node concept="3TrEf2" id="4B0n6H258B8" role="2OqNvi">
                <ref role="3Tt5mk" to="bwbq:4B0n6H258gR" />
              </node>
            </node>
            <node concept="3TrcHB" id="2JIP8cA02eV" role="2OqNvi">
              <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
            </node>
          </node>
        </node>
      </node>
      <node concept="17QB3L" id="2JIP8cA02de" role="3clF45" />
      <node concept="3Tm1VV" id="2JIP8cA02df" role="1B3o_S" />
    </node>
    <node concept="13i0hz" id="1Y5JHpRxEw3" role="13h7CS">
      <property role="13i0iv" value="false" />
      <property role="13i0it" value="false" />
      <property role="TrG5h" value="rebindToProxy" />
      <ref role="13i0hy" to="hwgx:7jSUHHvkApb" resolve="rebindToProxy" />
      <node concept="3Tm1VV" id="1Y5JHpRxEw4" role="1B3o_S" />
      <node concept="3clFbS" id="1Y5JHpRxEw9" role="3clF47">
        <node concept="3clFbF" id="1Y5JHpRxEVh" role="3cqZAp">
          <node concept="37vLTI" id="1Y5JHpRxFuz" role="3clFbG">
            <node concept="1PxgMI" id="1Y5JHpRxFzm" role="37vLTx">
              <ref role="1PxNhF" to="x27k:5_l8w1EmTdf" resolve="IModuleContent" />
              <node concept="37vLTw" id="1Y5JHpRxFws" role="1PxMeX">
                <ref role="3cqZAo" node="1Y5JHpRxEwa" resolve="proxyElement" />
              </node>
            </node>
            <node concept="2OqwBi" id="1Y5JHpRxEZ1" role="37vLTJ">
              <node concept="13iPFW" id="1Y5JHpRxEVg" role="2Oq$k0" />
              <node concept="3TrEf2" id="4B0n6H258XQ" role="2OqNvi">
                <ref role="3Tt5mk" to="bwbq:4B0n6H258gR" />
              </node>
            </node>
          </node>
        </node>
      </node>
      <node concept="37vLTG" id="1Y5JHpRxEwa" role="3clF46">
        <property role="TrG5h" value="proxyElement" />
        <node concept="3Tqbb2" id="1Y5JHpRxEwb" role="1tU5fm" />
      </node>
      <node concept="3cqZAl" id="1Y5JHpRxEwc" role="3clF45" />
    </node>
    <node concept="13i0hz" id="1Y5JHpRxEwD" role="13h7CS">
      <property role="13i0iv" value="false" />
      <property role="13i0it" value="false" />
      <property role="TrG5h" value="referencedModuleContent" />
      <ref role="13i0hy" to="hwgx:7jSUHHvkAph" resolve="referencedModuleContent" />
      <node concept="3Tm1VV" id="1Y5JHpRxEwE" role="1B3o_S" />
      <node concept="3clFbS" id="1Y5JHpRxEwH" role="3clF47">
        <node concept="3clFbF" id="1Y5JHpRxEz3" role="3cqZAp">
          <node concept="2OqwBi" id="1Y5JHpRxEAV" role="3clFbG">
            <node concept="13iPFW" id="1Y5JHpRxEz2" role="2Oq$k0" />
            <node concept="3TrEf2" id="4B0n6H259mK" role="2OqNvi">
              <ref role="3Tt5mk" to="bwbq:4B0n6H258gR" />
            </node>
          </node>
        </node>
      </node>
      <node concept="3Tqbb2" id="1Y5JHpRxEwI" role="3clF45" />
    </node>
    <node concept="13hLZK" id="4B0n6H258gU" role="13h7CW">
      <node concept="3clFbS" id="4B0n6H258gV" role="2VODD2" />
    </node>
  </node>
  <node concept="13h7C7" id="3biQP485jAl">
    <ref role="13h7C2" to="bwbq:6Jey9O34sBE" resolve="OilFileRef" />
    <node concept="13hLZK" id="3biQP485jAm" role="13h7CW">
      <node concept="3clFbS" id="3biQP485jAn" role="2VODD2" />
    </node>
    <node concept="13i0hz" id="3biQP485jAo" role="13h7CS">
      <property role="13i0iv" value="false" />
      <property role="13i0it" value="false" />
      <property role="TrG5h" value="getNodesToImportNodes" />
      <ref role="13i0hy" to="hwgx:7P$_wJpwTgl" resolve="getNodesToImportNodes" />
      <node concept="3Tm1VV" id="3biQP485jAp" role="1B3o_S" />
      <node concept="3clFbS" id="3biQP485jAv" role="3clF47">
        <node concept="3cpWs8" id="3biQP485jAL" role="3cqZAp">
          <node concept="3cpWsn" id="3biQP485jAO" role="3cpWs9">
            <property role="TrG5h" value="s" />
            <node concept="2I9FWS" id="3biQP485jAJ" role="1tU5fm" />
            <node concept="2ShNRf" id="3biQP485jBa" role="33vP2m">
              <node concept="2T8Vx0" id="3biQP485k_5" role="2ShVmc">
                <node concept="2I9FWS" id="3biQP485k_7" role="2T96Bj" />
              </node>
            </node>
          </node>
        </node>
        <node concept="3clFbF" id="3biQP485k_t" role="3cqZAp">
          <node concept="2OqwBi" id="3biQP485kLC" role="3clFbG">
            <node concept="37vLTw" id="3biQP485k_r" role="2Oq$k0">
              <ref role="3cqZAo" node="3biQP485jAO" resolve="s" />
            </node>
            <node concept="TSZUe" id="3biQP485lO2" role="2OqNvi">
              <node concept="2OqwBi" id="3biQP485lWq" role="25WWJ7">
                <node concept="13iPFW" id="3biQP485lRe" role="2Oq$k0" />
                <node concept="3TrEf2" id="3biQP485m62" role="2OqNvi">
                  <ref role="3Tt5mk" to="bwbq:6Jey9O34sBH" />
                </node>
              </node>
            </node>
          </node>
        </node>
        <node concept="3clFbF" id="3biQP485mdS" role="3cqZAp">
          <node concept="37vLTw" id="3biQP485mdQ" role="3clFbG">
            <ref role="3cqZAo" node="3biQP485jAO" resolve="s" />
          </node>
        </node>
      </node>
      <node concept="37vLTG" id="3biQP485jAw" role="3clF46">
        <property role="TrG5h" value="configContainer" />
        <node concept="3Tqbb2" id="3biQP485jAx" role="1tU5fm">
          <ref role="ehGHo" to="vs0r:3R$6B6bKw0D" resolve="IConfigurationContainer" />
        </node>
      </node>
      <node concept="A3Dl8" id="3biQP485jAy" role="3clF45">
        <node concept="3Tqbb2" id="3biQP485jAz" role="A3Ik2" />
      </node>
    </node>
  </node>
  <node concept="13h7C7" id="6g77ZYUpBSJ">
    <property role="3GE5qa" value="Resource" />
    <ref role="13h7C2" to="bwbq:6g77ZYUpzaO" resolve="ResourceLiteral" />
    <node concept="13i0hz" id="4B0n6H26Jye" role="13h7CS">
      <property role="TrG5h" value="isStaticallyEvaluatable" />
      <property role="13i0it" value="false" />
      <property role="13i0iv" value="false" />
      <ref role="13i0hy" to="ywuz:3ilck8Kr3zN" resolve="isStaticallyEvaluatable" />
      <node concept="3Tm1VV" id="4B0n6H26Jyf" role="1B3o_S" />
      <node concept="3clFbS" id="4B0n6H26Jyk" role="3clF47">
        <node concept="3clFbF" id="4B0n6H26J$S" role="3cqZAp">
          <node concept="3clFbT" id="4B0n6H26J$R" role="3clFbG">
            <property role="3clFbU" value="true" />
          </node>
        </node>
      </node>
      <node concept="10P_77" id="4B0n6H26Jyl" role="3clF45" />
    </node>
    <node concept="13i0hz" id="4B0n6H26J_r" role="13h7CS">
      <property role="TrG5h" value="evaluateStatically" />
      <property role="13i0it" value="false" />
      <property role="13i0iv" value="false" />
      <ref role="13i0hy" to="ywuz:6OxpEKG0KPv" resolve="evaluateStatically" />
      <node concept="3Tm1VV" id="4B0n6H26J_s" role="1B3o_S" />
      <node concept="3clFbS" id="4B0n6H26JMW" role="3clF47">
        <node concept="3clFbF" id="4B0n6H26JPm" role="3cqZAp">
          <node concept="3cmrfG" id="6g77ZYUpv1a" role="3clFbG">
            <property role="3cmrfH" value="0" />
          </node>
        </node>
      </node>
      <node concept="3uibUv" id="4B0n6H26JMX" role="3clF45">
        <ref role="3uigEE" to="wyt6:~Object" resolve="Object" />
      </node>
    </node>
    <node concept="13hLZK" id="6g77ZYUpBSK" role="13h7CW">
      <node concept="3clFbS" id="6g77ZYUpBSL" role="2VODD2">
        <node concept="3clFbF" id="1Y5JHpRxO21" role="3cqZAp">
          <node concept="37vLTI" id="1Y5JHpRxOYy" role="3clFbG">
            <node concept="Xl_RD" id="1Y5JHpRxP2t" role="37vLTx">
              <property role="Xl_RC" value="0" />
            </node>
            <node concept="2OqwBi" id="1Y5JHpRxO8I" role="37vLTJ">
              <node concept="13iPFW" id="1Y5JHpRxO20" role="2Oq$k0" />
              <node concept="3TrcHB" id="1Y5JHpRxOFl" role="2OqNvi">
                <ref role="3TsBF5" to="mj1l:1UQ4qqfV3yK" resolve="value" />
              </node>
            </node>
          </node>
        </node>
      </node>
    </node>
  </node>
</model>

