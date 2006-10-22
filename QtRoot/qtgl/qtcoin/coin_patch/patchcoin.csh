#!/usr/local/bin/tcsh
cd $IVROOT
cd ../srcDir/Coin-2/src
setenv  COINPATCHDIR $STAR/QtRoot/qtgl/qtcoin/coin_patch
echo Patch the Coin  $IVROOT from ${COINPATCHDIR}
patch -b -p0 <${COINPATCHDIR}/gl.c.2.4.5.diff
patch -b -p0 <${COINPATCHDIR}/SoGLClipPlaneElement.cpp.2.4.5.diff
patch -b -p0 <${COINPATCHDIR}/SoGLLightIdElement.cpp.2.4.5.diff
patch -b -p0 <${COINPATCHDIR}/SoGLModelMatrixElement.cpp.2.4.5.diff
patch -b -p0 <${COINPATCHDIR}/SoGLRenderAction.cpp.2.4.5.diff
patch -b -p0 <${COINPATCHDIR}/soshape_bumprender.cpp.2.4.5.diff
