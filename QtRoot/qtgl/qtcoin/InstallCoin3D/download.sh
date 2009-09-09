#!/bin/bash 
# stop at the first error.
# --trap  "echo ; echo SOME FATAL ERROR DURING Coin3D downloading, SORRY... ; echo ; exit;" ERR

svn co https://svn.coin3d.org/repos/simacros/trunk/src simacros/src
svn co https://svn.coin3d.org/repos/Coin-2/trunk Coin-2
wget http://ftp.coin3d.org/coin/src/all/Coin-3.1.0.tar.gz
tar -xzf Coin-3.1.0.tar.gz
svn co https://svn.coin3d.org/repos/SoQt/trunk SoQt
svn co https://svn.coin3d.org/repos/SoGuiExamples/trunk SoGuiExamples
svn co https://svn.coin3d.org/repos/simage/trunk simage
svn co https://svn.coin3d.org/repos/SmallChange/trunk  -r 1083 SmallChange
svn co https://svn.coin3d.org/repos/Quarter/trunk Quarter
echo " =========== Coin3d has been checked out ================ "
#wget http://ftp.coin3d.org/coin/src/all/Coin-2.4.6.tar.gz
#wget http://ftp.coin3d.org/coin/src/all/SoQt-1.4.1.tar.gz
