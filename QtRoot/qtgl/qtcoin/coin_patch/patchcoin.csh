cd $IVROOT
cd ../srcDir/Coin-2/src
patch -p0 <gl.c.2.4.5.diff
patch -p0 <SoGLClipPlaneElement.cpp.2.4.5.diff
patch -p0 <SoGLLightIdElement.cpp.2.4.5.diff
patch -p0 <SoGLModelMatrixElement.cpp.2.4.5.diff
patch -p0 <SoGLRenderAction.cpp.2.4.5.diff
patch -p0 <soshape_bumprender.cpp.2.4.5.diff
