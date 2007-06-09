setenv QT_VERSION 4.3.0
setenv QT_SRC_VERSION 
setenv QTDIR /afs/rhic.bnl.gov/star/users/fine/scratch/public/QT/Qt4/qt-x11-opensource-src-${QT_VERSION}/.${STAR_HOST_SYS}/${QT_VERSION}/debug
setenv QT_X11_NO_FONTCONFIG 1
setenv LD_LIBRARY_PATH $QTDIR/lib:`dropit qt -p $LD_LIBRARY_PATH`

# setenv QT4CPPDIR -I$QTDIR/Qt         -I$QTDIR/QtCore    -I$QTDIR/QtGui       \
#                  -I$QTDIR/Qt3Support -I$QTDIR/QtOpenGL  -I$QTDIR/QtNetwork \
#                  -I$QTDIR/QtSvg      -I$QTDIR/QtUiTools -I$QTDIR/QtXml     \
#                  -I$QTDIR/QtSql
                 
setenv PATH $QTDIR/bin:`dropit qt`
