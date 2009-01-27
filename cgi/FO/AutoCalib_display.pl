#!/usr/bin/env perl -w
#
# AutoCalib_webInterface_display.pl
#   Author: M. Elnimr (Wayne State Univ.)
#   Purpose: Display information on
#     AutoCalib states and chains
#
# $Id: AutoCalib_display.pl,v 1.1 2009/01/27 17:57:34 genevb Exp $
#
# $Log: AutoCalib_display.pl,v $
# Revision 1.1  2009/01/27 17:57:34  genevb
# Introduction of AutoCalib codes
#
#
###########################################################

 

BEGIN {
    use CGI::Carp qw(fatalsToBrowser carpout);
}

use Class::Struct;
use CGI;

use AutoCalibDB;
use DBI;


my @coll=('PPPP','AuAu','dAu','All');
my $textfield;


$query = new CGI;

print $query->header;
print $query->start_html('AutoCalib_webInterface_display');
print $query->startform();  

print "<html>\n";
print " <head>\n";

print " <title>Chain Query</title>";

print "  </head>\n";
print "  <body bgcolor=\"#ccffff\"> \n";

print "  <h1 align=center>Chain Query </h1>\n";
print " </head>\n";
print " <body>";
print "<i>This form is used to display the autocalibration full chain (baseChain+tpcChain+emcChain+qaChain) by choosing the collision system and entering the validity time for the data.</i>";
print <<END;
<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "</td><td>";
print "<h3 align=center>Collision System :</h3>";
print "<h3 align=center>";
print $query->popup_menu(-name=>'SetC',  
-values=>\@coll,
-default=>'AuAu'

);  

print "</td><td>";
print "<h3 align=center> Validity Time: (i.e. 2008-08-17 02:00:00, default :NOW())</h3>";
print "<h3 align=center>";
print $query->textfield(-name=>'SetA',  
-size=>50,
-maxlength=>100);  

print "<p>";
print "<p><br><br>"; 
print $query->submit;
print "<P><br>", $query->reset;
print $query->endform;
#print "  <address><a href=\"mailto:blah\@bnl.gov\">Muhammad Elnimr</a></address>\n";
print "<P>";
print "</body>";
print "</html>";
print $query->end_html; 

################################################################################################

my $tpcState;
my $emcState;
my $qaState;

if($query->param){
    #$NOW="'2008-09-17 02:00:00'";
    $CHAIN="";
    
    $ChainToInsert="'ITTF,ezTree'";
    
    my $CollisionType_template=$query->param('SetC');
    my @spl = ();
    my $NOW=$query->param('SetA');
    #my $NOW="$now%";
    if(!$NOW) {$NOW="NOW()";
    $NOW="'".$NOW."'";}
    else {$NOW="'".$NOW."'";}
    
	@spll=split(" ",$coll[0]);
    @spl = split(" ", $CollisionType_template);
    my $CollisionType = $spl[0];
    $CollisionType="'".$CollisionType."'";
    
    if($CollisionType eq "'All'")
	{
		
		for($a=0 ; $a<4;$a++)
		{
			$coll[$a]="'".$coll[$a]."'";
			$chain[$a]=fetch_BaseChain_AutoCalibDB($coll[$a],$NOW).",";
			$qaState=fetch_AutoCalibDB("QA",$NOW);
			$chain[$a]=$chain[$a].fetch_DetChain_AutoCalibDB("qaState='$qaState'","qaChain").",";
			$tpcState=fetch_AutoCalibDB("TPC",$NOW);
			$chain[$a]=$chain[$a].fetch_DetChain_AutoCalibDB("tpcState='$tpcState'","tpcChain").",";
			$emcState=fetch_AutoCalibDB("EMC",$NOW);
			$chain[$a]=$chain[$a].fetch_DetChain_AutoCalibDB("emcState='$emcState'","emcChain");
		}
	}
    else
    {		
        
        $CHAIN=fetch_BaseChain_AutoCalibDB($CollisionType,$NOW).",";
        $qaState=fetch_AutoCalibDB("QA",$NOW);
        $CHAIN=$CHAIN.fetch_DetChain_AutoCalibDB("qaState='$qaState'","qaChain").",";
        $tpcState=fetch_AutoCalibDB("TPC",$NOW);
        $CHAIN=$CHAIN.fetch_DetChain_AutoCalibDB("tpcState='$tpcState'","tpcChain").",";
        $emcState=fetch_AutoCalibDB("EMC",$NOW);
        $CHAIN=$CHAIN.fetch_DetChain_AutoCalibDB("emcState='$emcState'","emcChain");
    }
	
	if($CollisionType eq "'All'")
	{
		print "The chains are :  <BR> ";
		print "PPPP: \"$chain[0]\" <BR><BR><BR>";
		print "AuAu:\"$chain[1]\" <BR><BR><BR>";
		print "dAu: \"$chain[2]\" <BR><BR><BR>";
		print "PbPb: \"$chain[3]\" <BR><BR><BR>";
        
	}
	else
	{
		print "The full chain is :  <BR> ";
		print "\"$CHAIN\" <BR><BR><BR>";
	}
	
    #beginHtml();
    #printState(); 
    endHtml();
}    

sub beginHtml{
    print 
    "<html>
	<head>
	<title>Web interface for FO</title>
	</head>
	<body BGCOLOR=\"#ccffff\"> 
	<h2 align=center>Subdetectors status: </h2>
	<TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
	<TR>
	<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>TPC </B></TD>
	<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>EMC<br></B></TD>
	<TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>QA<br></B></TD>
	</TR> 
	</head>
	<body>";
    
}
sub printState {
	print <<END;
	<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
    <td HEIGHT=80><h3>$tpcState</h3></td>
    <td HEIGHT=80><h3>$emcState</h3></td>
    <td HEIGHT=80><h3>$qaState</h3></td>
    </TR>
    END
}

#####################
sub endHtml {
    my $Date = `/bin/date`;
    
    print <<END;
    </TABLE>
    <h5>
    <address><a href=\"mailto:blah\@bnl.gov\">Muhammad Elnimr</a></address>
    <!-- Created: Wed July 26  05:29:25 MET 2000 -->
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
    
