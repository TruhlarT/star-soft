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

&cgiSetup();
 

my $set = $q->param("set");


&beginHtml();

 &printRow(); 

&endHtml();


#################
sub beginHtml {

print <<END;
<html>
  <head>
          <title>Chain used for test</title>
  </head>
  <body BGCOLOR=\"#ccffff\"> 
     <h3>set = $set </h3>
<TABLE BORDER=5 CELLSPACING=1 CELLPADDING=2 >
<TR>
<TR ALIGN=CENTER VALIGN=CENTER>
<TD WIDTH=\"50%\" HEIGHT=50><B>Chain options</B></TD>
</TR>

END
}

###############
sub printRow {

print <<END;
<TR ALIGN=CENTER VALIGN=CENTER>
<td>$set</td>
</tr>
END

}

###############
sub endHtml {
my $Date = `date`;

print <<END;
</TABLE>
      <h5>
      <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>
<!-- Created: Tue Set 10  05:29:25 MET 1999 -->
<!-- hhmts start -->
Last modified: $Date
<!-- hhmts end -->
  </body>
</html>
END

}

##############
sub cgiSetup {
    $q=new CGI;
    if ( exists($ENV{'QUERY_STRING'}) ) { print $q->header };
}
