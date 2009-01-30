#!/usr/bin/env perl 
#
# AutoCalib_webInterface_insert.pl
#   Author: M. Elnimr (Wayne State Univ.)
#   Purpose: Control information on
#     AutoCalib states and chains
#
# $Id: AutoCalib_insert.pl,v 1.5 2009/01/30 21:01:01 jeromel Exp $
#
# $Log: AutoCalib_insert.pl,v $
# Revision 1.5  2009/01/30 21:01:01  jeromel
# Changes by ME
#
# Revision 1.4  2009/01/30 20:38:38  jeromel
# Removed use lib (pm moved)
#
# Revision 1.3  2009/01/30 19:31:40  jeromel
# Add use lib
#
# Revision 1.2  2009/01/30 17:24:44  jeromel
# Fixed ^M and changed some names
#
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
use DBI;
use AutoCalibDB;

my @coll=("PPPP","AuAu","dAu");
my $textfield;
###############################################################
###############################################################
###############################################################
###############################################################
$query2 = new CGI;
$query = new CGI;

print $query2->header;
print $query2->start_html('AutoCalib_insert.pl');
print $query2->startform();
my $qaState;
my $emcState;
my $tpcState;


#######
$CHAIN="";
my $tpcState;
my $emcState;
my $qaState;
my $InsertionStatus;

if($query2->param('button2'))
{
    my @spl=();
    my @spl2=();
    my @spl3=();
    my @spl4=();

    $db_query_2=$query2->param('tpc');
    my $db_query_3=$query2->param('emc');
    my $db_query_4=$query2->param('qa');

    my $radio_query_2=$query2->param('StateInsertion');

    @spl_2=split("---",$db_query_2);
    @spl_3=split("---",$db_query_3);
    @spl_4=split("---",$db_query_4);

    #&cgiSetup();

    if($db_query_2 eq "")
    {
        print "******************No CHAIN/STATE to insert**********************";
    }
    else
    {

        if($db_query_2 ne "")
        {
            # my $tmp1=fetch_AutoCalibDB("TPC","NOW()");
            #	my $tmp2=fetch_AutoCalibDB("EMC","NOW()");
            #   $tmp1="'".$tmp1."'";
            #  $tmp2="'".$tmp2."'";
            $InsertionStatus=insert_DetChain_AutoCalibDB($spl_4[0],$spl_2[0],$spl_3[0],"state");
            # print "<br>The QA state inserted is :  <BR> ";
            # print "<br>$spl_2[0] <br>";

            #else {print "<br>----------No QA state to insert------------<br>";}

            #if($radio_query_2 eq 'TPC state'){
            #my $tmp1=fetch_AutoCalibDB("QA","NOW()");
            #my $tmp2=fetch_AutoCalibDB("EMC","NOW()");
            #$tmp1="'".$tmp1."'";
            #$tmp2="'".$tmp2."'";
            #insert_DetChain_AutoCalibDB($tmp1,$spl_2[0],$tmp2,"state");
            # print "<br>The TPC state inserted is :  <BR> ";
            #print "<br>$spl_2[0] <br>";
            #}
            #else {print "<br>----------No TPC state to insert------------<br>";}

            #if($radio_query_2 eq 'EMC state'){
            #   my $tmp1=fetch_AutoCalibDB("QA","NOW()");
            #    my $tmp2=fetch_AutoCalibDB("TPC","NOW()");
            #    $tmp1="'".$tmp1."'";
            #    $tmp2="'".$tmp2."'";
            #    insert_DetChain_AutoCalibDB($tmp1,$tmp2,$spl_2[0],"state");
            #    print "<br>The EMC state inserted is :  <BR> ";
            #    print "<br>$spl_2[0] <br>";
            #}
            #else {print "<br>----------No EMC state to insert------------<br>";}
        }


    }



}
######



#print $query->header;
print $query->start_html('AutoCalib_webInterface_insert.pl');
print $query->startform();

# print "<html>\n";
# print " <head>\n";

#print " <title>Chain Query</title>";
# print "  </head>\n";
print "  <body bgcolor=\"#ccffff\"> \n";
# print "<a href=\"http://www.star.bnl.gov/STAR/comp/prod\"><h5>Production </h5></a>\n";
# print "  <h1 align=center>Chain Query </h1>\n";
# print " </head>\n";
print " <body>";

print <<END;
<hr>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "</td><td>";
print "</td><td>";
print "<i>Please use the textfield below for inserting new chains for a subsystem or the basechain and the time when the chain is valid:</i>";
print "<h3 align=center>Chain insertion : (i.e. <font color=red>Base Chain </font>'2008-08-17 02:00:00','AuAu','pp2009a')<p> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(i.e. <font color=red>Any other Chain </font>'2008-08-17 02:00:00','state','required chain')  </h3>";
print "<h3 align=center>";
print $query->textfield(-name=>'Set1',
-size=>50,
-maxlength=>100);


print "</td><td>";
print "</td><td>";
print "<h3 align=center>";
print $query->radio_group(-name=>'ChainInsertion',
-values=>['emcChain','tpcChain','qaChain','baseChain'],
-linebreak=>'true');
print "<p>";
#print "<p><br><br>";
#print "<p>";
#print "<p><br><br>";

$NOW="'2011-12-22 16:40:34'"; ################################# LOL
#$NOW="NOW()";
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
    $chain[$a]=$chain[$a]."--------------".fetch_validityTime_BaseChain_AutoCalibDB($coll[$a],$NOW);
}

print "The current full chains are (with the validity time for the base chain):  <BR> <BR><BR><BR>";
print "PPPP: \"$chain[0]\" <BR><BR><BR>";
print "AuAu: \"$chain[1]\" <BR><BR><BR>";
print "dAu: \"$chain[2]\" <BR><BR><BR>";
print "PbPb: \"$chain[3]\" <BR><BR><BR>";
print "<p>";
print "<p><br><br>";
print $query->submit(-name=>'button1',-value=>'submit');
print "<p><br>", $query->reset;
print $query->endform;
if($query->param('button1'))
{
	my $db_query=$query->param('Set1');
	my $radio_query=$query->param('ChainInsertion');
	@spl=split(",",$db_query);
	if($spl[3] ne "")
    {
        print "<b><font color=red>-------------Not valid input----------------</font></b>";
		exit;
    }
	if((!cleanStrictChar_DB($spl[1])&&($spl[1] ne ""))||(!cleanStrictChar_DB($spl[2])&&($spl[2] ne ""))||(!cleanStrict_DB($spl[0])&&($spl[0] ne "")))
	{
		print "<b><font color=red>-------------Not valid input----------------</font></b>";
		exit;
	}

	#if((!cleanStrict_DB($spl_2[0])&&($spl_2[1] ne ""))||(!cleanInt_DB($spl_2[0])&&($spl_2[1] ne "")))
	#{
	#print "-------------Not valid input----------------";
	#exit;
	#}

	my $CollisionType = $spl[1];
	my $BeginTime=$spl[0];
	my $chain=$spl[2];
	if($db_query eq "" && $db_query_2 eq "")
	{
		print "<b><font color=red>******************   No CHAIN/STATE to insert  **********************</font></b>";
	}
	else {
		if($db_query ne "")
		{
			if( $radio_query eq'baseChain') {insert_BaseChain_AutoCalibDB($BeginTime,$CollisionType,$chain);
							 print "<br><font color=red>The chain was inserted   </font><BR> ";
				#print "<br>$BeginTime,$CollisionType,$chain <br>";
			}
			#else {print "<br>--------No baseChain to insert ---------- <br>";}

			if($radio_query eq'tpcChain') {insert_DetChain_AutoCalibDB($spl[0],$spl[1],$spl[2],"tpcChain");
						       print "<br><font color=red> The chain was inserted </font> <br>";

				#print "<br>$spl2[0],$spl2[1],$spl2[2] <br>";
			}
			#else {print "<br>----------No tpcChain to insert----------<br>";}

			if($radio_query eq'emcChain'){insert_DetChain_AutoCalibDB($spl[0],$spl[1],$spl[2],"emcChain");
						   print "<br><font color=red>The chain was inserted </font> <br>";}
			#else {print "<br>----------No emcChain to insert------------<br>";}


			if($radio_query eq'qaChain'){insert_DetChain_AutoCalibDB($spl[0],$spl[1],$spl[2],"qaChain");
						  print "<br><font color=red>The chain was inserted </font> <br>";}
			#else {print "<br>----------No qaChain to insert------------<br>";}

		}
	}

}

print <<END;
<hr>

<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

$now="'2010-12-22 16:40:34'"; #temporarily solution
$tpcState__=fetch_AutoCalibDB("TPC",$now);
$qaState__=fetch_AutoCalibDB("QA",$now);
$emcState__=fetch_AutoCalibDB("EMC",$now);
$tpcState__=$tpcState__."---".fetch_DetChain_AutoCalibDB("tpcState='$tpcState__'","tpcChain");
$emcState__=$emcState__."---".fetch_DetChain_AutoCalibDB("emcState='$emcState__'","emcChain");
$qaState__=$qaState__."---".fetch_DetChain_AutoCalibDB("qaState='$qaState__'","qaChain");


print "</td><td>";
print "</td>";
print "<i>Please use the menus below for changing the state of a subsystem:</i>";

print "<h3 align=center>";

my @ALLstate=fetch_available_states("tpcState","tpcChain");
for($count=0;@ALLstate[$count] ne "";$count++)
{
    my $temp=@ALLstate[$count];
    @ALLstate[$count]=$temp."---".fetch_DetChain_AutoCalibDB("tpcState='$temp'","tpcChain");

}


%attributes=("$tpcState__"=>{'style'=>'color:red'});
print "<font color=red><b> ";
print $query2->popup_menu(-name=>'tpc',
                     -values=>\@ALLstate,
                     -default=>"$tpcState__",
                    -attributes=>\%attributes);
print "</b></font>";
print "   TPC status";
print "<p><br>";
@ALLstate=fetch_available_states("emcState","emcChain");
for($count=0;@ALLstate[$count] ne "";$count++)
{
    my $temp=@ALLstate[$count];
    @ALLstate[$count]=$temp."---".fetch_DetChain_AutoCalibDB("emcState='$temp'","emcChain");

}
%attributes=("$emcState__"=>{'style'=>'color:red'});
print $query2->popup_menu(-name=>'emc',
                  -values=>\@ALLstate,
                  -default=>"$emcState__",
                  -attributes=>\%attributes);
print "  EMC status";
print "<p><br>";
@ALLstate=fetch_available_states("qaState","qaChain");
for($count=0;@ALLstate[$count] ne "";$count++)
{
    my $temp=@ALLstate[$count];
    @ALLstate[$count]=$temp."---".fetch_DetChain_AutoCalibDB("qaState='$temp'","qaChain");

}
%attributes=("$qaState__"=>{'style'=>'color:red'});
print $query2->popup_menu(-name=>'qa',
                       -values=>\@ALLstate,
                       -default=>"$qaState__",
                       -attributes=>\%attributes);
print "  QA status";
print "</td><td>";
print "</td><td>";
print "<h3 align=center>";
#print $query2->radio_group(-name=>'StateInsertion',
#-values=>['QA state','TPC state','EMC state'],
#-linebreak=>'true');

print "<p>";
print "<p><br><br>";
print $query2->submit(-name=>'button2',-value=>'submit');
print "<P><br>", $query2->reset;
print $query2->endform;


print " <p> \n";
print "</body>";
print "</html>";

#if($query2->param eq "")
#{
#&beginHtml_table();
#$now="'2010-12-22 16:40:34'"; #temporarily solution
#$tpcState_=fetch_AutoCalibDB("TPC",$now);
#$qaState_=fetch_AutoCalibDB("QA",$now);
#$emcState_=fetch_AutoCalibDB("EMC",$now);
#print <<END;
#<TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
#<td HEIGHT=80><h3>$tpcState_</h3></td>
#<td HEIGHT=80><h3>$emcState_</h3></td>
#<td HEIGHT=80><h3>$qaState_</h3></td>
#</TR>
#END
#}
print $query2->end_html;
###################################################################################################################################################
###################################################################################################################################################
###################################################################################################################################################
###################################################################################################################################################

if($query2->param('button2'))
{
    if ($InsertionStatus)
    { print"<br>success....$dbtable was inserted\n";}
    else
    {print "<br> Failed to insert.......\n";}

    #$now="NOW()";
    $now="'2010-12-22 16:40:34'"; #temporariy solution

	$tpcState_=fetch_AutoCalibDB("TPC",$now);
	$qaState_=fetch_AutoCalibDB("QA",$now);
	$emcState_=fetch_AutoCalibDB("EMC",$now);

	#&bginHtml_table();
	#&printState();
	&endHtml();

}

####################

sub printState {

    print "
    <TR ALIGN=CENTER HEIGHT=80 bgcolor=lightblue>
    <td HEIGHT=80><h3>$tpcState_</h3></td>
    <td HEIGHT=80><h3>$emcState_</h3></td>
    <td HEIGHT=80><h3>$qaState_</h3></td>

    </TR>
    ";
}
####################

sub beginHtml {

    print <<END;

    <html>
    <head>
    <title>Web interface for FO</title>
        </head>
        <body BGCOLOR=\"#ccffff\">

        <TR>
        </TR>
        </head>
        <body>
        END
        }

        sub beginHtml_table{

        print
        "<html>
        <head>
        <title>Web interface for FO</title>
            </head>
            <body BGCOLOR=\"#ccffff\">
            <h2 align=center>The current subdetectors status: </h2>
            <TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
            <TR>
            <TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>TPC </B></TD>
            <TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>EMC<br></B></TD>
            <TD ALIGN=CENTER WIDTH=\"20%\" HEIGHT=100><B>QA<br></B></TD>
            </TR>
            </head>
            <body>";
END
}

####################

sub begin2Html {

    print <<END;

    <html>
    <head>
    <title>Production Summary by Trigger</title>
    </head>
    <body BGCOLOR=\"#ccffff\">
    <TABLE ALIGN=CENTER BORDER=5 CELLSPACING=1 CELLPADDING=2 >
    <TR>
    <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Events<br> with primary vertex</B></TD>
    <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Hadronic MinBias</B></TD>
    <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Hadronic Central</B></TD>
    <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Hi-mult</B></TD>
    <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>Hi-mult & ZDC </B></TD>
    <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>UPC MinBias</B></TD>
    <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>TOPO</B></TD>
    <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>TOPO & ZDC</B></TD>
    <TD ALIGN=CENTER WIDTH=\"10%\" HEIGHT=100><B>TOPOeff</B></TD>
    </TR>

    </head>
    <body>
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
