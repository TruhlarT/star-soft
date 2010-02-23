#! /usr/local/bin/perl -w
#
#  $Id:
#
#  L. Didneko
#
###############################################################################

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use CGI;

# &cgiSetup();

 my $q=new CGI;

 if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };


my $set = $q->param("set");


&beginHtml();

#################
sub beginHtml {

print <<END;
<html>
  <head>
          <title>Chain used for test</title>
  </head>
  <body BGCOLOR=\"cornsilk\"> 
<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TD  ALIGN=CENTER WIDTH=\"100%\" HEIGHT=50><h3>Chain options</h3></TD>
</TR><TR>
<TD  ALIGN=CENTER WIDTH=\"100%\" HEIGHT=50><h3>$set</h3></TD>
</TR>

</TABLE>
   </body>
</html>
END
}

###############
sub endHtml {
my $Date = `date`;

print <<END;
</TABLE>
   </body>
</html>
END

}

##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}
