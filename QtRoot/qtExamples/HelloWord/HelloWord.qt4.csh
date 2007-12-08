g++ `root-config  --cflags --glibs` -I$QTDIR/include  -DQT_GUI_LIB -DQT_CORE_LIB  -I$QTDIR/include/QtGui -L$QTDIR/lib -lQtCore -lQtGui HelloWord.cxx -o HelloWord
