<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:5212abd4-4a43-4236-b735-4bf4165f7444(de.whz.make.structure)">
  <persistence version="9" />
  <languages>
    <use id="c72da2b9-7cce-4447-8389-f407dc1158b7" name="jetbrains.mps.lang.structure" version="1" />
    <devkit ref="fbc25dd2-5da4-483a-8b19-70928e1b62d7(jetbrains.mps.devkit.general-purpose)" />
  </languages>
  <imports>
    <import index="x27k" ref="r:75ecab8a-8931-4140-afc6-4b46398710fc(com.mbeddr.core.modules.structure)" />
    <import index="i2y7" ref="r:098cbe90-1cfd-414a-b5e8-aca28752df17(com.mbeddr.core.make.structure)" />
  </imports>
  <registry>
    <language id="c72da2b9-7cce-4447-8389-f407dc1158b7" name="jetbrains.mps.lang.structure">
      <concept id="1169125787135" name="jetbrains.mps.lang.structure.structure.AbstractConceptDeclaration" flags="ig" index="PkWjJ">
        <property id="4628067390765907488" name="conceptShortDescription" index="R4oN_" />
        <property id="5092175715804935370" name="conceptAlias" index="34LRSv" />
        <property id="1587916991969465369" name="conceptId" index="1pbfSe" />
        <child id="1071489727083" name="linkDeclaration" index="1TKVEi" />
      </concept>
      <concept id="1071489090640" name="jetbrains.mps.lang.structure.structure.ConceptDeclaration" flags="ig" index="1TIwiD">
        <reference id="1071489389519" name="extends" index="1TJDcQ" />
      </concept>
      <concept id="1071489288298" name="jetbrains.mps.lang.structure.structure.LinkDeclaration" flags="ig" index="1TJgyj">
        <property id="1071599776563" name="role" index="20kJfa" />
        <property id="1071599893252" name="sourceCardinality" index="20lbJX" />
        <property id="1071599937831" name="metaClass" index="20lmBu" />
        <reference id="1071599976176" name="target" index="20lvS9" />
      </concept>
    </language>
    <language id="ceab5195-25ea-4f22-9b92-103b95ca8c0c" name="jetbrains.mps.lang.core">
      <concept id="1169194658468" name="jetbrains.mps.lang.core.structure.INamedConcept" flags="ng" index="TrEIO">
        <property id="1169194664001" name="name" index="TrG5h" />
      </concept>
    </language>
  </registry>
  <node concept="1TIwiD" id="1wzo07AoCmx">
    <property role="1pbfSe" value="24779358" />
    <property role="TrG5h" value="ParameterCommandItem" />
    <property role="34LRSv" value="-" />
    <ref role="1TJDcQ" to="i2y7:2Vizpn2Mx$z" resolve="TextCommandItem" />
  </node>
  <node concept="1TIwiD" id="1wzo07ApVfa">
    <property role="1pbfSe" value="24439861" />
    <property role="TrG5h" value="MakeCommandItem" />
    <property role="34LRSv" value="m" />
    <property role="R4oN_" value="make" />
    <ref role="1TJDcQ" node="1wzo07Aq8O0" resolve="CommandItem" />
  </node>
  <node concept="1TIwiD" id="1wzo07ApWnj">
    <property role="1pbfSe" value="24435244" />
    <property role="TrG5h" value="MakeAllCommandItem" />
    <property role="34LRSv" value="ma" />
    <property role="R4oN_" value="make all" />
    <ref role="1TJDcQ" node="1wzo07Aq8O0" resolve="CommandItem" />
  </node>
  <node concept="1TIwiD" id="1wzo07Aq6fu">
    <property role="1pbfSe" value="24394785" />
    <property role="TrG5h" value="EchoCommandItem" />
    <property role="34LRSv" value="e" />
    <property role="R4oN_" value="echo" />
    <ref role="1TJDcQ" node="1wzo07Aq8O0" resolve="CommandItem" />
  </node>
  <node concept="1TIwiD" id="1wzo07Aq70g">
    <property role="1pbfSe" value="24391663" />
    <property role="TrG5h" value="AtEchoCommandItem" />
    <property role="34LRSv" value="ae" />
    <property role="R4oN_" value="@echo" />
    <ref role="1TJDcQ" node="1wzo07Aq8O0" resolve="CommandItem" />
  </node>
  <node concept="1TIwiD" id="1wzo07Aq8O0">
    <property role="1pbfSe" value="24384255" />
    <property role="TrG5h" value="CommandItem" />
    <property role="34LRSv" value="c" />
    <property role="R4oN_" value="Command" />
    <ref role="1TJDcQ" to="i2y7:2Vizpn2Mx$z" resolve="TextCommandItem" />
    <node concept="1TJgyj" id="1wzo07Aq9R4" role="1TKVEi">
      <property role="20lmBu" value="aggregation" />
      <property role="20kJfa" value="arguments" />
      <property role="20lbJX" value="0..n" />
      <ref role="20lvS9" to="i2y7:2Vizpn2Mx$w" resolve="CommandItem" />
    </node>
  </node>
  <node concept="1TIwiD" id="1wzo07AqayQ">
    <property role="1pbfSe" value="24377161" />
    <property role="TrG5h" value="RemoveCommandItem" />
    <property role="34LRSv" value="rm" />
    <ref role="1TJDcQ" node="1wzo07Aq8O0" resolve="CommandItem" />
  </node>
  <node concept="1TIwiD" id="1wzo07AqaSV">
    <property role="1pbfSe" value="24375748" />
    <property role="TrG5h" value="CopyCommandItem" />
    <property role="34LRSv" value="cp" />
    <ref role="1TJDcQ" node="1wzo07Aq8O0" resolve="CommandItem" />
  </node>
  <node concept="1TIwiD" id="1wzo07AqbeK">
    <property role="1pbfSe" value="24374351" />
    <property role="TrG5h" value="SudoCommandItem" />
    <property role="34LRSv" value="sudo" />
    <ref role="1TJDcQ" node="1wzo07Aq8O0" resolve="CommandItem" />
  </node>
  <node concept="1TIwiD" id="1I2SOvk9_iQ">
    <property role="1pbfSe" value="274122755" />
    <property role="TrG5h" value="ChangeDirectoryCommandItem" />
    <property role="34LRSv" value="cd" />
    <ref role="1TJDcQ" node="1wzo07Aq8O0" resolve="CommandItem" />
  </node>
</model>

