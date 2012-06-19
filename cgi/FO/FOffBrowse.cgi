#!/usr/bin/env perl
#
# This cgi will allow users to browse the FastOffline database
# Methods will eventually be added to the RunDAQ.pm
#
BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


use lib "/afs/rhic.bnl.gov/star/packages/scripts";
use RunDAQ;
use CGI qw(:standard);
use Date::Manip;

$query = new CGI;
$this_script= $query->url();

$author   = "Jerome Lauret (c) 2004-2011";
$title    = "Fast Offline Browser";
#$title   .= "&nbsp;<BLINK><FONT COLOR=\"#FF0000\">UNDER WORK</FONT></BLINK>";
$BGCOLOR  = "whitesmoke"; # Body color fields
$TEXTCOL  = "black";
$LINKCOL  = "navy";

$color[0] = "#ffffff"; # Alternate color 1 (table color 1)
$color[1] = "#eeeeee"; # Alternate color 1 (table color 2)
$color[2] = "#dddddd"; # Alternate color 2 (table color 3)

$ocol[0]  = "#9999cc"; # Table BGColor for query form + title
$ocol[1]  = "#ffffff"; # Main Query form letters color
$ocol[2]  = "#ff1111"; # color for some writeup


# Associative array of field name vs title we want to
# have displayed and selected.
#
# The value of the fields is a positioning in the table
# a semi-column and the field name. Added in 2007 so we
# could re-arrange. Anything with only the positioning is
# intepreted as a header of the next selectors
#
$FIELDS{"00;"}            = "Run selector";
$FIELDS{"11;BeamE"}       = "Beam Energy";
$FIELDS{"21;Collision"}   = "Collision";
$FIELDS{"31;scaleFactor"} = "Field Scale";
$FIELDS{"41;runNumber"}   = "Run Number";

$FIELDS{"12;TrgMask"}     = "Trigger Labels";
$FIELDS{"22;TrgSetup"}    = "Trigger Setup";
$FIELDS{"32;DetSetMask"}  = "Detectors";
$FIELDS{"42;ftype"}       = "File type";


$FIELDS{"50;"}            = "Processing selectors";
$FIELDS{"51;Status"}      = "Status";
$FIELDS{"52;XStatus1"}    = "Transfer"; #"ezTree";


$FIELDS{"60;"}            = "Record range";

# Conversion routine if any
$CONVERT{"Status"}    = "rdaq_status_string";
$CONVERT{"XStatus1"}  = "rdaq_status_string";
$CONVERT{"TrgSetup"}  = "rdaq_trgs2string";
$CONVERT{"ftype"}     = "rdaq_ftype2string";

# Could be icon or text
# $BBACK = "[<A HREF=\"$this_script\">Back</A>]";
# $BTOP  = "[<A HREF=\"#Top\">Top</A>]";
# $BBOT  = "[<A HREF=\"#Bottom\">Bottom</A>]";
$BBACK = "<A HREF=\"$this_script\"><IMG BORDER=\"0\" SRC=\"/icons/back.gif\" ALT=\"Back\"></A>";
$BTOP  = "<A HREF=\"#Top\"><IMG BORDER=\"0\" SRC=\"/icons/up.gif\" ALT=\"Top\"></A>";
$BBOT  = "<A HREF=\"#Bottom\"><IMG BORDER=\"0\" SRC=\"/icons/down.gif\" ALT=\"Top\"></A>";
$DLOG  = "<A HREF=\"$this_script?Trace=1\"><IMG BORDER=\"0\" SRC=\"/icons/text.gif\" ALT=\"Show Trace\"></A>\n";

# Link reference to the run browser
#$TARGET  = "RunLog2001";
#$LINKREF = "http://online.star.bnl.gov/$TARGET/Summary.php3?run=";
#$TARGET  = "RunLog2003";
#$LINKREF = "http://online.star.bnl.gov/$TARGET/Summary.php3?run=";
$TARGET  = "RunLog";
$LINKREF = "http://online.star.bnl.gov/$TARGET/Summary.php?run=";
$ESLREF  = "http://online.star.bnl.gov/apps/shiftLog/logForFullTextSearch.jsp?text=";

$CACHES  = 120;
$MLIMIT  = 20;


$obj   = rdaq_open_odatabase();
print $query->header();
print $query->start_html(-title=>$title,
                         #-AUTHOR=>$author,
                         -BGCOLOR=>$BGCOLOR,
                         -TEXT=>$TEXTCOL,
                         -LINK=>$LINKCOL),"\n";


print $query->h1($title),"\n";
if ( ! $obj ){
    print "Error: Could not connect to the database\n";
    print $query->end_html(),"\n";
    exit;
}

# If any field is defined, this means the cgi is in
# active querry mode.
$flag   = 0;
$limit  = -1;
$display= 0;
foreach $field (keys %FIELDS){
    ($pos,$name) = split(";",$field);
    if( defined(param($name)) ){
	$flag = 1;

	if ( lc(param($name)) ne "all"){
	    if ($name eq "runNumber"){
		@all = param($name);
		if($#all > 0){
		    $SEL{$name} = join("\|",@all);
		} else {
		    # if any additional args after a space, strip
		    $SEL{$name} = (split(" ",$all[0]))[0];
		}
		#print "<!-- @all -->\n";
	    } else {
		# if any additional args after a space, strip
		$SEL{$name} = (split(" ",param($name)))[0];
	    }
	}
    }
}

$trace = undef;
$trace = (split(" ",param("Trace")))[0] if ( defined(param("Trace")) );

#
# Now really start things up ...
#
if( $flag && ! $trace ){
    # Extra parameters needed by this block
    $limit  = int(param("Limit"))    if ( defined(param("Limit")) );
    $display= int(param("Display"))  if ( defined(param("Display")));

    if ( defined($flag = param("EntryDate")) ){
	if($flag != 0){
	    $SEL{"EntryDate"} = ">$flag";
	}
    }
    if ( defined($flag = param("DiskLoc")) ){
	if($flag ne ">0"){
	    if (  flag !~ m/union/i){
		# one union injection check although it will
		# never pass get_orecords() internal treatment
		$SEL{"DiskLoc"}  = $flag;
	    }
	}
    }

    # Fix default values
    if(lc($limit) eq "all"){ $limit = -1;}



    # Get the selected records from database.
    #rdaq_toggle_debug(1);
    @all = rdaq_get_orecords($obj,\%SEL,$limit,1);
    #rdaq_toggle_debug(0);




    # If there is something ...
    if($#all != -1){
	# display it.
	# Small header.
	print
	    "<A NAME=\"Top\"></A>\n",
	    "$BBACK $DLOG $BBOT &nbsp;\n";
	if($limit == -1){
  	    print "You have asked for all ".($#all+1)." records matching criteria\n";
	} else {
	    print "You have selected the last $limit records<br>\n";
	}


	# We will save what we need to display in an array
	# and display later. We need to do that because in some
	# modes, we actually know the results after parsing.
	if($display < 2){
	    # Average or high level of details
	    $TD = "<TD ALIGN=\"center\"><FONT COLOR=\"$ocol[1]\" SIZE=\"+1\">";
	    $ETD= "</FONT></TD>";
	    push(@RECORD,
		 "<TABLE BORDER=\"0\">\n",
		 "<TR BGCOLOR=\"$ocol[0]\">$TD ".($display==0?"File":"Run").
		 " $ETD$TD NumEvt$ETD",
		 "$TD Scale$ETD$TD Beam Energy$ETD$TD Collision$ETD$TD Detectors$ETD",
		 "$TD Trigger Setup $ETD$TD Triggers$ETD",
		 "$TD ".$FIELDS{"52;XStatus1"}."$ETD $TD Status $ETD </TR>\n");
	} else {
	    # Low level
	    push(@RECORD,"<blockquote>\n");
	    foreach $el (keys %SEL){
		push(@RECORD,"<u>$el</u> : $SEL{$el}<br>\n");
	    }
	    push(@RECORD,"</blockquote>\n");
	}


	$i    =-1;
	$srun ="";
	$prun ="";

	$ftot = $tot  = 0;
	$ftots= $tots = 0;
	$ftotp= $totp = 0;
	$fqaed= $qaed = 0;
	$ftrej= $trej = 0;
	$ftext= $text = 0;

	foreach $line (@all){
	    #print "<!-- $line -->\n";

	    # WARNING -- The apperance of date formats returned with space
	    # will "add" a fake entry after date. The array will be scaled
	    # by one for EACH timestamp.
	    @items = split(" ",$line);


	    if($items[1] ne $prun){
		$srun = $prun;
		$prun = $items[1];
		$i++; if($i > $#color){ $i = 0;}
		$dol = 1;
	    } else {
		$dol = 0;
	    }

	    # **** THIS SPLICING MUST BE MODIFIED IF NEW FIELDS APPEAR IN THE DDB ***
	    #splice(@items,12,3);# entry date, disk location, ftype
	    #splice(@items,3,3); # start, end endevent and Current
	    #splice(@items,1,1); # run number


	    $tot  += $items[2]; $ftot++;
	    if ($items[$#items] >= 1){ $tots += $items[2];  $ftots++;}
	    if($items[$#items] >= 2){  $totp += $items[2];  $ftotp++;}
	    if($items[$#items] == 3){  $qaed += $items[2];  $fqaed++;}
	    if($items[$#items] == 7){  $text += $items[2];  $ftext++;}
	    if($items[$#items-2] == 8){$trej += $items[2];  $ftrej++;}


	    if($display == 0 ){
		# add a record as-is
		push(@RECORD,&FormatLine($i,$prun,$dol,@items));

	    } elsif ($display == 1){
		if($dol && defined(@prcdt) ){
		    # a preceeding run has been completed
		    push(@RECORD,&FormatLine($i,$srun,$dol,@prcdt));
		    undef(@prcdt);
		}
		# we need to save info for that run
		# prcdt array will accumulate things up.
		if( ! defined(@prcdt) ){
		    push(@prcdt,@items);
		    $prcdt[0]        = $prun;
		} else {
		    $prcdt[2]       += $items[2];      # sum the number of events
		                                       # update status with the highest
		    $prcdt[$#items-0]  = $items[$#items-0] if ($items[$#items-0] > $prcdt[$#items-0]);
		    $prcdt[$#items-1]  = $items[$#items-1] if ($items[$#items-1] > $prcdt[$#items-1]);
		    $prcdt[$#items-2]  = $items[$#items-2] if ($items[$#items-2] > $prcdt[$#items-2]);
		}
	    }
	}
	undef(@all);
	if($display ==1){    push(@RECORD,&FormatLine($i,$srun,1,@prcdt));}
	if($display < 2){    push(@RECORD,"</TABLE>\n");}


	# Dump it all now
	foreach $line (@RECORD){
	    print $line;
	}
	undef(@RECORD);

	# Finish with a summary
	print
	    "$BTOP $DLOG<P>\n",
	    "<A NAME=\"Bottom\"><FONT COLOR=\"#000080\"><b>Summary</b></FONT></A>\n",
	    "<TABLE BORDER=\"0\" CELLSPACING=\"0\">\n",
	    "<TR><TD BGCOLOR=\"#e0e0ff\">&nbsp</TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;<b>Events</b></TD><TD BGCOLOR=\"#e6e6e6\" ALIGN=\"right\">&nbsp;</TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;<b>Files </b></TD><TD BGCOLOR=\"#e6e6e6\" ALIGN=\"right\">&nbsp;</TD>\n",
	    "</TR>\n",
	    "<TR><TD BGCOLOR=\"#e0e0ff\"><FONT COLOR=\"#0000FF\">Available</FONT></TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$tot </TD><TD BGCOLOR=\"#e6e6e6\" ALIGN=\"right\">&nbsp;</TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$ftot</TD><TD BGCOLOR=\"#e6e6e6\" ALIGN=\"right\">&nbsp;</TD>\n",
	    "</TR>\n",
	    "<TR><TD BGCOLOR=\"#e0e0ff\"><FONT COLOR=\"#0000FF\">Submitted</FONT></TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$tots </TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$tots /$tot*100) ."\%</TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$ftots</TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$ftots/$ftot*100)."\%</TD>\n",
	    "</TR>\n",
	    "<TR><TD BGCOLOR=\"#e0e0ff\"><FONT COLOR=\"#0000FF\">Processed</FONT></TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$totp </TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$totp /$tot*100) ."\%</TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$ftotp</TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$ftotp/$ftot*100)."\%</TD>\n",
	    "</TR>\n",
	    "<TR><TD BGCOLOR=\"#e0e0ff\"><FONT COLOR=\"#0000FF\">With QA</FONT></TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$qaed </TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$qaed /$tot*100) ."\%</TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$fqaed</TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$fqaed/$ftot*100)."\%</TD>\n",
	    "</TR>\n",
	    "<TR><TD BGCOLOR=\"#e0e0ff\"><FONT COLOR=\"#0000FF\"><i>Not Exter.</i></FONT></TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$trej </TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$trej /$tot*100) ."\%</TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$ftrej</TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$ftrej/$ftot*100)."\%</TD>\n",
	    "</TR>\n",
	    "<TR><TD BGCOLOR=\"#e0e0ff\"><FONT COLOR=\"#0000FF\"><i>External</i></FONT></TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$text </TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$text /$tot*100) ."\%</TD>\n",
	    "    <TD BGCOLOR=\"#e6e6ff\" ALIGN=\"right\">&nbsp;$ftext</TD><TD ALIGN=\"right\" BGCOLOR=\"#e6e6e6\">&nbsp;".
	    sprintf("%2.2d",$ftext/$ftot*100)."\%</TD>\n",
	    "</TR>\n",
	    "</TABLE><P>\n";


    } else {
	# There were no records within this selection.
	print
	    "Nothing was returned for the following selection<br>\n",
	    "To return, click $BBACK, see the log $DLOG\n",
	    "<blockquote>\n";
	foreach $field (keys %SEL){
	    print "<u>$field</u> : $SEL{$field}<br>\n";
	    if ($field eq "runNumber"){
		my($lrun)= rdaq_last_run($obj);
		if ( $SEL{$field} > $lrun){
		    print
			"<BLOCKQUOTE>\n",
			"This run number is in transit. Latest valid one is $lrun\n",
			"</BLOCKQUOTE>";
		} else {
		    # add helper links
		    print
			"<BLOCKQUOTE>\n",
			"Check the RunLog for <A HREF=\"$LINKREF$SEL{$field}\" TARGET=\"$TARGET\">$SEL{$field}</A><br>\n",
			"Check the ShiftLog for <A HREF=\"$ESLREF$SEL{$field}\" TARGET=\"ESL\">$SEL{$field}</A><br>\n",
			"</BLOCKQUOTE>";

		    print "<B>Below is a trace from FastOffline</B><BR>\n";
		    $obj2 = rdaq_open_rdatabase();
		    rdaq_toggle_debug();
		    rdaq_set_dlevel(1);
		    rdaq_html_mode();
		    my(@all)=rdaq_raw_files($obj2,"=".$SEL{$field},1);
		    rdaq_close_rdatabase();
		}
	    }
	}
	print "</blockquote>\n";
    }



} else {
    # This part simply shows all fields in a table format for selection
    # i.e. build a form etc ...
    if ( ! $trace ){
	my(@info)=stat("/tmp/FOPage.html");
	if ( (time()-$info[10]) > $CACHES || ! -e "/tmp/FOPage.html" ){
	    if (open(FF,">/tmp/FOPage.html")){
		# try a second form
		print FF
		    "<FORM ACTION=\"$this_script\">\n",
		    "Enter a specific runNumber\n",
		    $query->textfield(-size=>(12),-name=>"runNumber",-default=>0),"\n",
		    $query->submit(),"\n",
		    $query->endform(),"or use the full selection below ...\n<HR>\n";

		print FF
		    "<FORM ACTION=\"$this_script\">\n",
		    "<TABLE WIDTH=800 BORDER=\"0\">\n";

		$STDK  = "<TD WIDTH=100 BGCOLOR=\"#e6e6e6\">";
		$STDV  = "<TD WIDTH=300 BGCOLOR=\"#e6e6ff\">";
		$ETD   = "</TD>";
		$SFONT = "<FONT FACE=\"Lucida Sans, sans-serif\"><FONT SIZE=\"3\">";
		$EFONT = "</FONT></FONT>";

		$ii    = 0;

		foreach $field (sort keys %FIELDS){
		    %labels=();

		    ($pos,$name) = split(";",$field);

		    if ($name eq ""){
			# This is some kind of header
			print FF
			    "<TR>\n",
			    "    <TD COLSPAN=4 BGCOLOR=\"#9999cc\">\n",
			    "         <FONT COLOR=\"#000080\"><FONT FACE=\"Arial, sans-serif\"><FONT SIZE=4>\n",
			    "            <B>$FIELDS{$field}</B>\n",
			    "         </FONT>\n",
			    "    </TD>\n";
			next;
		    }

		    # else
		    $ii++;

		    @values = rdaq_list_field($obj,$name,undef,$CACHES);
		    if( defined($CONVERT{$name}) && $#values != -1){
			# A conversion was requested
			foreach $val (@values){
			    my($fval);
			    $cmd = "\$fval = $CONVERT{$name}($val)";
			    eval($cmd);
			    $labels{$val} = $fval;
			}
		    }

		    # @values = sort  {$b cmp $a} @values;
		    if($name eq "TrgMask")   { push(@values,"0:unknown");}
		    # if($name eq "TrgSetup")  { push(@values,"0:unknown");}
		    if($name eq "DetSetMask"){ push(@values,"0:unknown");}
		    unshift(@values,"All");

		    if ($ii%2){  print FF "<TR>\n";}

		    print FF
			"    $STDK $SFONT $FIELDS{$field} $EFONT $ETD\n",
			"    $STDV ";
		    if ($name eq "runNumber"){
			print FF $query->scrolling_list(-name=>$name,
							-values=>\@values,
							-labels=>\%labels,
							-size=>5,
							-multiple=>'true',
							-default=>"All"
							);
		    } else {
			print FF $query->popup_menu(-name=>$name,
						    -values=>\@values,
						    -labels=>\%labels
						    );
		    }
		    print FF "$ETD\n";
		    if (! $ii%2){  print FF "</TR>\n";}
		}


		# Put a number of records limit
		%labels = ();
		@values = (20,50,100,200,500,1000,2000,"All");
		foreach $val ( @values ){
		    $labels{$val} = " $val ";
		}
		print FF
		    "<TR>\n",
		    "    $STDK $SFONT Only the last (entries) $EFONT $ETD\n",
		    "    $STDV",
		    $query->radio_group(-name=>"Limit",
					-values=>\@values,
					-labels=>\%labels,
					-default=>200),
		    "$ETD\n";


		# Put a time limit
		%labels = ();
		@values=(" 24 hours "," 2 days "," 3 days "," 4 days "," 7 days ",
			 " 14 days "," 21 days "," 28 days ");
		for($i=0 ; $i <= $#values ; $i++){
		    $val = &DateCalc("now","-$values[$i]");
		    $val =~ s/://g;
		    $labels{$val} = $values[$i];
		    $values[$i]   = $val;
		}
		unshift(@values,0);
		$labels{0} = "All";
		print FF
		    "    $STDK $SFONT Limit by last (time sel) $EFONT $ETD\n",
		    "    $STDV",
		    $query->radio_group(-name=>"EntryDate",
					-values=>\@values,
					-labels=>\%labels,
					-default=>0),
		    "$ETD\n</TR>\n";


		# Put a detail level choice
		print FF
		    "<TR>\n",
		    "    <TD COLSPAN=4 BGCOLOR=\"#9999cc\">\n",
		    "         <FONT COLOR=\"#000080\"><FONT FACE=\"Arial, sans-serif\"><FONT SIZE=4>\n",
		    "            <B>Display and verbosity</B>\n",
		    "         </FONT>\n",
		    "    </TD>\n";

		%labels = ();
		$labels{0} = " Full ";
		$labels{1} = " Medium ";
		$labels{2} = " Low ";
		@values = keys %labels;
		print FF
		    "<TR>\n",
		    "    $STDK $SFONT Detail level $EFONT $ETD\n",
		    "    $STDV",
		    $query->radio_group(-name=>"Display",
					-values=>\@values,
					-labels=>\%labels,
					-default=>0),
		    "$ETD\n";



		# Give the on-disk/not-on disk choice
		%labels=();
		@values=(">0","!0");
		$labels{"!0"} = " On disk ";
		$labels{">0"} = " All ";
		print FF
		    "    $STDK $SFONT Availability $EFONT $ETD\n",
		    "    $STDV",
		    $query->radio_group(-name=>"DiskLoc",
					-values=>\@values,
					-labels=>\%labels,
					-default=>">0"),
		    "$ETD\n",
		    "</TR>\n";


		print FF
		    "</TABLE>\n",
		    $query->submit(),"\n",
		    $query->endform(),"\n<HR>\n";

		print FF $DLOG;
		close(FF);
	    }
	}
	open(FF,"/tmp/FOPage.html");
	while ( defined($line = <FF>)){ print $line;}
	close(FF);

    } else {
	# TRACE ENABLED - Showed in both mode
	# Now for some debug info
	$MLIMIT= param("MLimit")  if ( defined(param("MLimit")) );
	#print "Mlimit = $MLIMIT\n";

	if ( $trace eq "1" ){
	    # print "eq 1";
	    $dsel  = 1;
	    @all   = rdaq_get_message($MLIMIT);
	} else {
	    # print "ne 1 / selector";
	    $dsel  = 0;
	    @items = split("-",$trace);
	    $key   = shift(@items);
	    @all   = rdaq_get_message($MLIMIT,$key,join("-",@items));
	}

	print
          "$BBACK $DLOG\n",
	  "[<A HREF=\"$this_script?Trace=$trace&MLimit=".($MLIMIT*2)."\">+</A>]\n",
	  "<FONT SIZE=\"-1\">\n",
	  "<TABLE WIDTH=800 BORDER=\"1\" CELLSPACING=\"0\">\n";
	foreach $mess (@all){
	    @items = split(";",$mess);
	    $mess = $items[1];

	    # Go from GMT to EST
	    $time = $items[0];
	    $time = &ParseDate($items[0]." GMT");
	    $time = &UnixDate($time,"%Y-%m-%d %H:%M:%S");

	    # Highlight errors
	    if ($mess =~ m/warning/i ){   $mess = "<FONT COLOR=\"#1111FF\">$mess</FONT>";}
	    if ($mess =~ m/error/i ){     $mess = "<FONT COLOR=\"#EE1111\">$mess</FONT>";}
	    if ($mess =~ m/bogus/i ){     $mess = "<FONT COLOR=\"#FF0000\">$mess</FONT>";}

	    print
	      "<TR><TD BGCOLOR=\"#e6e6ff\" ALIGN=\"center\">$time</TD>\n",
	      "    <TD BGCOLOR=\"#e1e1e1\">&nbsp;".&RefString(1,$mess)."</TD>\n",
	      "    <TD BGCOLOR=\"#e6e6e6\">&nbsp;".&RefString(2,$items[2])."</TD>\n",
	      "    <TD BGCOLOR=\"#eeeeee\">&nbsp;$items[3]</TD>\n",
	      "</TR>\n";
	}
	print
	  "</TABLE>\n",
	  "&nbsp;\n",
	  "</FONT>\n",
	  "<HR>\n";

	# get all field 1
	print "<TABLE BORDER=\"0\">\n";
	foreach $c (("1","2")){
	    @all   = rdaq_get_message(0,undef,undef,$c);
	    if ($#all != -1){
		# should not be but at startup
		print "<TR><TD><I>".(split(";",$all[0]))[0]."</I></TD><TD>";

		foreach $mess (@all){
		    @items    = split(";",$mess);
		    $ref = $items[1]; $ref =~ s/ /-/g;
		    print "[<A HREF=\"$this_script?Trace=$c-$ref\">$items[1]</A>] ";
		}
		print "</TD></TR>\n";
	    }
	}
	print "</TABLE>\n";
    }
}


print $query->h5($author);
print $query->end_html(),"\n";



#
# Since 2006, no shift in indexes.
#
sub FormatLine
{
    my($i,$run,$dol,@vals)=@_;
    my($j,$el,$eli);
    my(@lines);

    #print "<!-- DEBUG, we have $#vals values -->\n";
    push(@lines,"<TR BGCOLOR=\"$color[$i]\">");
    for($j=0 ; $j <= ($#vals) ; $j++){
	$eli = $el  = $vals[$j];
	if($j == 0 && $dol){
	    $el = "<A HREF=\"$LINKREF$run\" TARGET=\"$TARGET\">$el</A>&nbsp;<FONT SIZE=\"-2\">[<A HREF=\"$ESLREF$run\">ESL</A>]</FONT>";
	} elsif($j == 1){
	    # skip runnmuber
	    next;
	} elsif ( $j == 2){
	    if ($display == 1){
		# display runnumber and link to this script detail
		# about this run number
		$el = "<A HREF=\"$this_script?runNumber=$run\">$el</A>";
	    }
	} elsif ($j == 3 || $j == 4 || $j == 5){
	    # being, end, current event
	    next;

	    # 6, 7, 8 will be displayed AS-IS
	} elsif($j == 9){
	    $el = rdaq_bits2string("DetSetMask",$el);
	    $el =~ s/\./ /g;

	} elsif($j == 10){
	    $el =  rdaq_trgs2string($el); #rdaq_bits2string("TrgSetup",$el);
	} elsif($j == 11){
	    #rdaq_toggle_debug(1);
	    $el = rdaq_bits2string("TrgMask",$el);
	    $el =~ s/\./ /g;
	    if ( length($el) > 45){
		#$el = substr($el,0,40)."...";
		$el = "<FONT SIZE=\"-1\">$el</FONT>";
	    }
	    #rdaq_toggle_debug(0);

	    # SKIPPED 12, 13+1 (see comment), 14+2, 15+3,16+3, 17+3
	} elsif ($j>= 12 && $j <= 17+3){
	    # ftype, EntryDate, D,D, DiskLoc, Chain
	    next;

	} elsif($j == 18+3) {
	    # should be ezTree field
	    $el = rdaq_status_string($el);

	    # UNUSED - SKIP
	} elsif ($j >= 19+3 && $j < $#vals){
	    next;

	} elsif($j == $#vals) {
	    # should be status fields
	    $el = rdaq_status_string($el);
	}

	push(@lines,"\n\t<TD ALIGN=\"center\">$el</TD><!-- $j [$eli] -->");
    }
    push(@lines,"</TR>\n");
    @lines;
}

# dependingif selector is on/off, use back link or sel
sub RefString
{
    my($pos,$st)=@_;
    my($arg)=$st;
    $arg =~ s/\s/-/g;

    # ($dsel?"<A HREF=\"$this_script?Trace=$pos-$arg\">":"<A HREF=\"$this_script?Trace=1\">")."$st</A>";
    "<A HREF=\"$this_script?Trace=$pos-$arg\">$st</A>";
}

