#! /usr/local/bin/tcsh -f
         #SNiFF+
switch ($STAR_SYS)
	    case "sun4*":
#     ====================
	setenv SNIFF_DIR /star/sol/packages/sniff
	set path = ( $path $SNIFF_DIR/bin )
	breaksw 
	    case "i386_*":
#     ====================
	setenv SNIFF_DIR /star/sol/packages/sniff
        set path = ( $path $SNIFF_DIR/bin )
	breaksw
    default:
endsw 
 
