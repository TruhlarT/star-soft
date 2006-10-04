setenv IVROOT  $ROOT/5.99.99/Coin2/installDir
setenv PATH `dropit Coin`
setenv LD_LIBRARY_PATH `dropit Coin -p $LD_LIBRARY_PATH`
setenv PATH $IVROOT/bin:$PATH
setenv LD_LIBRARY_PATH $IVROOT/lib:$LD_LIBRARY_PATH
