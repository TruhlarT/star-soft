#!/usr/local/bin/perl
#!/usr/local/bin/perl

# Why a cgi instead of Embeded ?
# ... because I want to make it readable to users i.e. convert
# cryptic fields to a human-readable-value.
#

# OK. I'll use both ...
use CGI;
use DBI;
use GD::Graph::bars;
use GD::Graph::area;
use Date::Manip;
require 'cgi-lib.pl';

BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}


$DDBREF = "DBI:mysql:database=DataCarousel;host=duvall.star.bnl.gov";
$DDBUSR = "star_c_user";
$DDBPAS = "VoyonsVoir";
$title  = "Content of the AccntGlobal table ...";
$author = "jlauret\@mail.chem.sunysb.edu";
$DOC    = "http://nucwww.chem.sunysb.edu/pad/offline/carousel/carousel.html#DateFormat";

# Style to include. DISABLED by default in distribution ; see lines below
# for more information on how to enable it (pretty straight forward)
$Style  = "style.css";

# Color settings
if($DDBUSR eq "star_c_user"){
    $BGCOLOR  = "cornsilk"; # Body color fields
    $TEXTCOL  = "black";
    $LINKCOL  = "navy";

    $color[0] = "#eeeeee"; # Alternate color 1 (table color 1)
    $color[1] = "#ffffff"; # Alternate color 2 (table color 2)
    $ocol[0]  = "#AA1111"; # Table BGColor for query form + title
    $ocol[1]  = "#ffffff"; # Main Query form letters color
    $ocol[2]  = "#ff1111"; # color for some writeup 

} else {
    # Support for initial Phenix color
    $BGCOLOR  = "#aaaaff";
    $TEXTCOL  = "#000000";
    $LINKCOL  = "#474aff";

    $color[0] = "#ddeeff";
    $color[1] = "#ffffff";
    $ocol[0]  = "#113377";
    $ocol[1]  = "#ffffff";
    $ocol[2]  = "#ffffff";
}


# Default date and field length/
$Date = &DateCalc("today","-20 days");
$namlen = 15;

# ------------------------------------------------------------------------

 # That's a cgi-lib stuff
 &ReadParse();

 # that's an object to make my life easy ...

 $query = new CGI;
 $this_script= $query->url();


 print $query->header();

 # Now we can print the header as in CGI.pm ...
 print $query->start_html(-title=>$title,
			  -AUTHOR=>$author,
			  -BGCOLOR=>$BGCOLOR,
			  -TEXT=>$TEXTCOL,
			  -LINK=>$LINKCOL),"\n";
                          # for style sheet, comment the above and uncomment +2
			  #-LINK=>$LINKCOL,
			  #-STYLE=>{"src"=>$Style}),"\n";

 print "<!-- $this_script -->\n";
     
 if ( ! defined($in{'User'}) ) {
     # Script is called and considered an 'empty' call i.e. a
     # a cgi reset.
     print 
         $query->h1($title),"\n",       
	 "<HR>\n",
	 # I had to revert to the end written stuff because the cgi handler
	 # passes things as METHOD="POST" regardless of what I have tried and
	 # this method passes the arguments silently. I then used some ugly
	 # tricks using a 'First' variable and some refreshing ... Sounds
	 # better to just write the line by hand ...
	 #$query->startform(-action=>$this_script),
	 "<FORM ACTION=\"$this_script\">\n",
	 "<TABLE BORDER=\"0\">\n",
	 "<TR bgcolor=\"$ocol[0]\"><TD>",
	 "<FONT COLOR=\"$ocol[1]\" SIZE=\"+1\">User name (Default *)</FONT>",
	 "</TD>\n\t<TD>",
	 $query->textfield(-size=>($namlen+1),-name=>"User",-default=>"*"),
	 "</TD></TR>\n";
     
     $Date = &UnixDate($Date,"%b %e %Y");
     $Date =~ s/ /_/g;
     print 
	 "<TR bgcolor=\"$ocol[0]\"><TD>",
	 "<FONT COLOR=\"$ocol[1]\" SIZE=\"+1\">Date Minimum</FONT>",
	 "</TD>\n\t<TD>",
	 $query->textfield(-size=>($namlen+1),-name=>"MDate",-default=>"$Date"),
	 "</TD></TR>\n";

     print 
	 "<TR bgcolor=\"$ocol[0]\">",
	 "<TD><FONT COLOR=\"$ocol[1]\" SIZE=\"+1\">Date Maximum</FONT>",
	 "</TD>\n\t<TD>";
     print 
	 $query->textfield(-size=>($namlen+1),-name=>"XDate",-default=>"today"),
	 "</TD></TR>\n";
     

     print 
	 "<TR bgcolor=\"$ocol[0]\">",
	 "<TD><FONT COLOR=\"$ocol[1]\" SIZE=\"+1\">Max Records</FONT>",
	 "</TD>\n\t<TD>";
     print	
	 $query->textfield(-size=>($namlen+1),-name=>"Limit",-default=>200),
	 "</TD></TR>\n";

     #print $query->hidden(-name=>"First",-default=>"1");
     
     print 
	 "</TABLE>",
	 $query->checkbox(-name=>"SList",-on=>1,-value=>1,-label=>"Show list"),"<BR>\n",
	 $query->checkbox(-name=>"SServ",-on=>1,-value=>1,-label=>"Show Server"),"<BR>\n",
	 $query->checkbox(-name=>"SGraf",-on=>0,-value=>1,-label=>"Show Graph"),"<BR>\n",
	 $query->submit(),"\n",$query->endform(),"\n<HR>\n",
	 "<I>Note</I> : Date format should be as described in ",
	 "<A HREF=\"$DOC\">User Manual</A>\n";

 } else {
     $User = $in{'User'};
     $Xval = $in{'XDate'}; 
     $Mval = $in{'MDate'}; 
     $Expd = $in{'Expand'};
     $Fail = $in{'Failed'};
     $Limi = $in{'Limit'};
     $SPrcs= $in{'SPrcs'};
     $ShowL= $in{'SList'};
     $ShowS= $in{'SServ'};
     $ShowG= $in{'SGraf'};
     $Nbin = $in{'Bin'};
     
     # Still, use default values if not defined
     $User = (split(" ",$User))[0];
     if( ! defined($Xval) ){  $Xval = "today";}
     if( ! defined($Mval) ){  $Mval = $Date;}
     if( ! defined($Expd) ){  $Expd = 0;}
     if( ! defined($Fail) ){  $Fail = -1;}
     if( ! defined($Limi) ){  $Limi = 0;}
     if( ! defined($SPrcs)){  $SPrcs= 0;}
     if( ! defined($ShowL)){  $ShowL= 0;}
     if( ! defined($ShowS)){  $ShowS= 0;}
     if( ! defined($ShowG)){  $ShowG= 0;}
     
     if ( $ShowL==1 ){
	 print 
	   $query->h1($title),"\n",
	   "<FONT SIZE=\"+1\">",
	   "<A HREF=\"$this_script\">New Selection</A><BR>\n",
	   "</FONT>";
     }
     

     # small debugging as a comment line.
     # print "<!-- [$ShowL] [$User] [$Mval] [$Xval] [$Limi] [$Expd] [$SPrcs] -->\n";
     
     # Manipulate date for display
     $Xval =~ s/_//g;
     $Mval =~ s/_//g;
     $Xval = &ParseDate($Xval);
     $Mval = &ParseDate($Mval);
     if( ! $Xval ){
	 # Small warning. Revert to default
	 print "<B>Bogus format.</B> Using default date for MAX Date...<BR>\n";
	 $Xval = "today";
     } 
     if( ! $Mval ){
	 print "<B>Bogus format.</B> Using default date for Min Date...<BR>\n";
	 $Mval = $Date;
     } 
     $Xval =~ s/://g;
     $Mval =~ s/://g;
     $d1   = &UnixDate($Mval,"%b %e %Y at %T");
     $d2   = &UnixDate($Xval,"%b %e %Y at %T");
     
     # Add comments
     $cref = $tmp = &GetURLReference(($User ne "*")?$User:"*");
     if($Expd == 1){ 
	 $banner= "Destinations";
	 if ($tmp =~ m/Expand/){  $tmp =~ s/\&Expand=\d//;}
	 $tmp .= "\&Expand=0";
	 $extra = "<A HREF=\"$tmp\">Click here to Compact</A> $banner<BR>";
     } elsif($Expd == 2){ 
	 $banner= "Sources";
	 if ($tmp =~ m/Expand/){  $tmp =~ s/\&Expand=\d//;}
	 $tmp .= "\&Expand=0";
	 $extra = "<A HREF=\"$tmp\">Click here to Compact</A> $banner<BR>";
     } else {
	 $banner= "File ID";
	 if ($tmp =~ /Expand/){  $tmp  =~ s/\&Expand=\d//;}
	 $extra  = "<A HREF=\"$tmp\&Expand=1\">Click here to Expand Destinations</A> $banner<BR>";
	 $extra .= "<A HREF=\"$tmp\&Expand=2\">Click here to Expand Sources</A> $banner<BR>";
     }

     $tmp = $cref;
     if($SPrcs == 1){ 
	 if ($tmp =~ m/SPrcs/){  $tmp =~ s/\&SPrcs=\d//;}
	 $tmp .= "\&SPrcs=0";
	 $extra.= "<A HREF=\"$tmp\">Click here to hide stat on </A> files being processed<BR>";
     } else {
	 if ($tmp =~ m/SPrcs/){  $tmp =~ s/\&SPrcs=\d//;}
	 $tmp .= "\&SPrcs=1";
	 $extra.= "<A HREF=\"$tmp\">Click here to show stat on </A> files being processed<BR>";
     }



     $outag = "Use values in 'User' field ";
     if($User ne "*"){
	 # xcmd is used afterward. There is no need for redundant 
	 # tests so I group everything here.
	 $xcmd   = " WHERE User='$User' AND ";
	 $allu   = 1==1;
	 $outag .= "to revert to all users";
     } else {
	 $xcmd   = " WHERE ";
	 $allu   = 1==0;
	 $outag .= "to select a specific user";
     }
     if( $Fail == -1){
	 $ftag = "Select failure/success ";
     } else {
	 $ftag = "Display files without 'Bytes' selection ";
     }
     $ftag .= "by clicking 'Bytes' field items";
     
     if ( $ShowL==1 ){
	 print 
	   "<U>Current selection is</U> :<BR>",
	   $query->blockquote("<FONT COLOR=\"$ocol[2]\" SIZE=\"+1\">User&nbsp;&nbsp;</FONT>",
	                      "$User<BR>\n",
	                      "<FONT COLOR=\"$ocol[2]\" SIZE=\"+1\">Dates</FONT>",
			      "$d1 &lt; d &lt; $d2<P>\n");

	 print 
	   "<U>Possible Options are</U> : ",
	   $query->blockquote("$extra",
	                      "$outag<BR>",
			      $ftag);
     }


     # Connect to database
     $dbh  = DBI->connect($DDBREF,$DDBUSR,$DDBPAS);

     if( $dbh){
         if ($ShowS){
	     # Display some informative stuff (2002 new and dependent on if Server
	     # is allowed to pass information or not)
	     undef(@status);
	     $cmd = "SELECT EntryDate,Status from RunStatus ORDER BY id DESC LIMIT 20";
	     $sth = $dbh->prepare($cmd);
	     if ( $sth->execute() ){ 
		 while( @res = $sth->fetchrow_array() ){
		     push(@status,join("::",@res));	
		 }
		 if ($#status == -1){
		     print "<BLOCKQUOTE>Server is A-OK</BLOCKQUOTE>\n";
		 } else {
		     print 
			 "<U>Server Process status information available</U> : <br>",
			 "<BLOCKQUOTE>\n",
			 "This section indicates problems eventually encountered ",
			 "by the Carousel server.<br>\n",
			 "Below is the information and action recovery stack.<br>",
			 "Times are in DD HH:MM:SS ago format.\n",
			 "<TABLE BORDER=\"0\" cellspacing=\"0\">\n";

		     my($year,$month,$week,$day,$hour,$min,$sec);
		     foreach $sts (@status){
			 @items = split("::",$sts);
			 if (! defined($PRINTED{$items[1]}) ){
			     $PRINTED{$items[1]} = 1;

			     # YY:MM:WK:DD:HH:MM:S
			     $delta = &DateCalc($items[0]." GMT","now",,1);
			     print "<!-- $items[0] -->\n";
			     print "<!-- $delta -->\n";
			     ($year,$month,$week,$day,$hour,$min,$sec) = split(":",$delta);
			     print 
				 "<TR><TD bgcolor=\"$color[0]\"><I>".
				 sprintf("%2.2d %02.2d:%02.2d:%02.2d",$day,$hour,$min,$sec).
				 "</I> </TD><TD bgcolor=\"$color[1]\">$items[1]</TD></TR>\n";
			 }
		     }
		     print 
			 "</TABLE>\n<P>\n",
			 "</BLOCKQUOTE>\n";
		 }
	     } else {
		 print "<B>Problem accessing RunStatus [$sth->errstr]</B><BR>\n";
	     }
	     $sth->finish();
	 }

	 if($SPrcs == 1){ 
	    if($User ne "*"){
		$tmp = "AND User=".$dbh->quote($User);
		$allu= 0;
            } else {
		$tmp = "";
		$allu= 1;
            }

	    # this may change but for the moment, we keep it the same
	    $cmd2 = "SELECT COUNT(User),Retries,User FROM Entries WHERE Status=1 $tmp GROUP BY User,Retries";
	    $cmd3 = "SELECT CUsers_old.COUNT,CUsers_old.User FROM CUsers_old";
	    $sth2 = $dbh->prepare($cmd2);
	    $sth3 = $dbh->prepare($cmd3);
	    if ($sth2 && $sth3){
		if ( $sth2->execute() && $sth3->execute() ){
		   while( @res = $sth3->fetchrow_array() ){
			print "<!-- $res[1] -->\n";
			$TOT{$res[1]} = $res[0];
		   }
		   while( @res = $sth2->fetchrow_array() ){
			$CNT{$res[2]} = $res[0];
			$RET{$res[2]} = $res[1];
                   }
		   foreach $user (keys %TOT){
			if ( $res[1] == 0){
			     $tmp = $TOT{$user};
			     $ur  = &GetURLReference(($allu?"*":$user));
			     $ur  = "<A HREF=\"$ur\">$user</A>";
			} else {
			     $tmp = "&nbsp;";
			     $ur  = "&nbsp;";
			}
			if ( ! defined($RET{$user}) ){$RET{$user} = 0;}
			if ( ! defined($CNT{$user}) ){$CNT{$user} = 0;}

			push(@LIGNES,sprintf
				"<TR><TD>%s</TD><TD>%d</TD><TD>%d</TD><TD>%s</TD></TR>\n",
				$ur,$RET{$user},$CNT{$user},$tmp);

		   }
		   undef(%CNT);
		   undef(%RET);
		   undef(%TOT);
		   if ($#LIGNES == -1){
			print "<b>No submission detected on ".localtime()."</b>\n";
                   } else {
			   print 
				"<BLOCKQUOTE>\n",
				"<TABLE border=\"0\" cellspacing=\"0\" cellpadding=\"4\">\n",
				"<TR>\n",
				"<TD><FONT size=\"+1\">User</FONT></TD>\n",
				"<TD><FONT size=\"+1\">Retries</FONT></TD>\n",
				"<TD><FONT size=\"+1\"># in fill</FONT></TD>\n",

				"<TD><FONT size=\"+1\">Still to go</FONT></TD>\n",
				"</TR>\n";
			   foreach $line (@LIGNES){ print "$line\n";}
			   print 
				"</TABLE>\n",
				"</BLOCKQUOTE>\n";
		   }
		} else {
		    print "<BLOCKQUOTE><I>No info</I></BLOCKQUOTE><BR>\n";
                }
            } else {
		print "<BLOCKQUOTE><B>Prepare statement on Entries failed $dbh</B></BLOCKQUOTE><BR>\n";
            }
	    print "<P>\n";
	    $sth2->finish();
	    $sth3->finish();
	 }


	 # Prepare main statement
	 $cmd  = "SELECT * FROM AccntGlobal $xcmd";
	 $cmd .= "PDate > ? AND PDate < ?";
	 if( $Fail == 0){
	     $cmd .= " AND Bytes <> 0";
	 } elsif ( $Fail == 1){
	     $cmd .= " AND Bytes = 0";
	 }
         # print "<!-- $cmd -->\n";
	 # Final sorting
	 $cmd .= " ORDER BY PDate DESC";
	 if($Limi != 0){
	     $cmd .= " LIMIT ".int($Limi);
	 }		
	 $sth = $dbh->prepare($cmd);

         $sth->execute(int($Mval),int($Xval));
	 if(!$sth){
	     print "<B>Could not get Accounting data from MySql table</B><BR>\n";
	 } else {
	     if ($ShowL){
		 $TDS="<TD ALIGN=\"center\">".
		     "<FONT color=\"$ocol[1]\" size=\"+1\">%s</FONT></TD>\n\t";
	     
		 print 
		     "<TABLE border=\"0\" cellspacing=\"0\" cellpadding=\"4\">\n",
		     "<TR bgcolor=\"$ocol[0]\">",
		     sprintf($TDS,$banner),
		     sprintf($TDS,"User"),
		     sprintf($TDS,"Processed"),
		     sprintf($TDS,"Bytes"),
		     sprintf($TDS,"Status"),
		     "</TR>\n";
	     }

	     $i= 0 ;
	     while( @res = $sth->fetchrow_array() ){
		 $date= &UnixDate($res[2],"%b %e %Y at %T");
		 
		 push(@XValues,&UnixDate($res[2],"%s"));
		 push(@YValues,$res[3]);

                 if ($ShowL){
		     # Can massage file-id as well ...
		     # BUT ONLY IF ENTRIES with Status=3 DOES NOT DISAPPEAR !!!
		     # Patch while waiting for new format ...
		     if( !defined($date) ){ 
			 $date = &UnixDate($res[1],"%b %e %Y at %T");
			 if( !defined($date) ){ 
			     $date = "?";
			 } else {
			     # User name not present
			     $res[1] = "?";
			 }
		     }
		     if( !defined($res[4])){ 
			 # Shifted by one ...
			 $res[4] = $res[3];
			 $res[3] = $res[2];
		     }

		     # prepare some links to expand/shorten list.
		     # User ...
		     $ur = &GetURLReference(($allu?"*":$res[1]));

		     # file ID or expanded field
		     $tmp = $res[0];
		     if($Expd != 0){
			 #print "<!-- Checking id=$res[0] -->\n";
			 if( $sthx = $dbh->prepare("SELECT * FROM Entries WHERE id=".int($res[0])) ){
			     $sthx->execute();
			     my($tblsel)=($Expd==1?"Destinations":"Sources");
			     
			     if( @items = $sthx->fetchrow_array() ){
				 #print "<!-- Checking Destination $items[2] -->\n";
				 $tmp = $Expd==1?$items[2]:$items[1];
				 if($sthxx = 
				    $dbh->prepare("SELECT * FROM $tblsel WHERE id=".int($tmp)) ){
				     $sthxx->execute();
				     if( @items = $sthxx->fetchrow_array() ){
					 $tmp = $items[2]." (Id=$tmp)";
				     } else {
					 $tmp = "No info on $tblsel  $items[2] fid=$res[0]";
				     }
				     $sthxx->finish();
				 } else {
				     $tmp = "Failed to locate $tblsel $items[2]";
				 }
			     } else {
				 $tmp = "No info on fid=$res[0]";
			     }
			     $sthx->finish();
			 } else {
			     $tmp = "Failed to scan Entries with id=$res[0]";
			 }
		     } 

		     # Bytes twicking
		     $bt = &GetURLReference(($User ne "*")?$User:"*");
		     if( $Fail == -1){
			 # Only when all records requested
			 if( $res[3] == 0){
			     # if 0, enable failure
			     $bt .= "&Failed=1";
			 } else {
			     # if <> 0, enable no-failure
			     $bt .= "&Failed=0";
			 }
		     } else {
			 $bt =~ s/&Failed=\d//;
		     } 
		     # else, re-enable all
		     $bt = "<A HREF=\"$bt\">$res[3]</A>";

		     # Print result
		     print 
			 "<TR BGCOLOR=\"$color[$i]\">",
			 "<TD>$tmp</TD>",
			 "<TD><A HREF=\"$ur\">$res[1]</A></TD>",
			 "<TD>$date</TD>",
			 "<TD ALIGN=\"center\">$bt</TD>",
			 "<TD>$res[4]</TD></TR>\n";

		     # Color rotation
		     $i++; if ($i > $#color){ $i = 0;}	
		 }
	     }
		 
	     print "</TABLE>" if ($ShowL);
	     $sth->finish();
	 }
	 $dbh->disconnect();

	 if ( $ShowG ){
	     $unit  = 1/1024/1024;  # MB
	     $GSum  = $sum   = $first = 0;
	     $nbin  = $check = 0;
	     $avgsep= $avgn  = 0;

	     # startup values
	     $IBIN  = $BIN   = 30;
	     
	     # full range of what we will display
	     $width = abs($XValues[0]-$XValues[$#XValues]);

	     if ( defined($Nbin) ){
		 # we want Nbin bins or so
		 $BIN   = int($width / $Nbin);
		 if ( $BIN < 1){  $BIN = 1;}
	     } else {
		 # we weill use thde fault value
		 $Nbin  = "(auto)";
	     }

	     
	     $first = $XValues[0];
	     $ii    = 0;
             
	     # print "Starting from $XValues[0] to $XValues[$#XValues]<BR>\n";
	     for ( $X=$first ; $X > $XValues[$#XValues] ; $X -= $BIN){
	     	 # build equidistant bins
	     	 $sum = 0;
		 while ( defined($XValues[$ii]) && $XValues[$ii] > $X-$BIN){
	     	     # print "$XValues[$ii] < $X+$BIN<BR>\n";
	     	     $GSum  += $YValues[$ii];
	     	     $sum   += $YValues[$ii];
	     	     $ii++;
		     
		     # just for checking
		     $avgsep+= $XValues[$ii-1]-$XValues[$ii] if ( defined($XValues[$ii]) );
		     $avgn++;
	     	 } 
	     	 unshift(@XVal,int($X-$BIN/2));
	     	 unshift(@YVal,$sum/$BIN*$unit);
		 print "<!-- ".int($X-$BIN/2)." ".$sum/$BIN*$unit." -->\n";
	      	 $nbin++;
	     	 $check += $YVal[0]*$BIN;
             
	     	 # There may be some distance before we get to the next 
	     	 # bin in XValues i.e. if 
	      	 # while ( $XValues[$ii+1]  - $X
             
	     }

	     # calculate average separation between beens
	     $avgsep = $avgsep/$avgn if ($avgn != 0);
	     
	     # Prepare for +/- scalink in binning
	     $tmp = $tmp1 = $tmp2 = $tmp3 = $tmp4 = &GetURLReference(($User ne "*")?$User:"*");
	     if ( $tmp1 =~ m/Bin=/ ){
		 if ($tmp1 =~ /(.*Bin=)(\d+)(.*)/){  $l = $2*2;
		                                     $tmp1  = $1.int($l).$3;
		                                     $tmp3  = $1.int($l*2).$3;
		 }
		 if ($tmp2 =~ /(.*Bin=)(\d+)(.*)/){  $l = $2*0.6; if ($l < 2){ $l = 2;}
		                                     $tmp2  = $1.int($l).$3;
		                                     $l = $l*0.6; if ($l < 1){ $l = 1;}
		                                     $tmp4  = $1.int($l).$3;
		 }
	     } else {
		 $tmp1 .= "&Bin=".int($nbin*1.2); $tmp3 .= "&Bin=".int($nbin*2.5);
		 $tmp2 .= "&Bin=".int($nbin*0.8); $tmp4 .= "&Bin=".int($nbin*0.4);
	     }

	     $SaveM = $in{'MDate'};
	     $SaveX = $in{'XDate'};
	     $SaveL = $in{'Limit'};
	     $in{'SList'} = 0 if ( defined($in{'SList'}) );
	     $in{'SPrcs'} = 0 if ( defined($in{'SPrcs'}) );	     
	     
	     print 
		 "<P>\n",
	         # "<B>Experimental Graph, Please ignore</B><BR>\n",
		 "<BLOCKQUOTE>",
	         "<A NAME=\"G\"></A>\n",
		 "Binning is N Bin_Default=$IBIN ; NBin param = $Nbin leads to BIN size in X=$BIN, nbin real=$nbin full X width=$width<BR>\n",
		 "Consistency check 1 Average  ",
	                       sprintf("YVal %.2f",$GSum*$unit/($XValues[0]-$XValues[$#XValues]))." &nbsp; ",
	                       sprintf("Xsep %.2f",$avgsep).(($avgsep*1.1>$BIN)?" <B>Decrease Nbin</B> (Graph Y values meaningless)":" (OK)")."<BR>\n",
	                       # 1.5 is inconrrect but calculating sigma would be a pain ...
		 "Consistency check 2 Integral ".sprintf("%.2f",$check)." &nbsp; Intervals $XValues[0] (idx0) > $XValues[$#XValues] (idx$#XValues)<BR>\n",
	         "[<A HREF=\"$tmp4\">--</A>|<A HREF=\"$tmp2\">-</A>] &nbsp; [<A HREF=\"$this_script\">Zoom</A>] &nbsp; [<A HREF=\"$tmp1\">+</A>|<A HREF=\"$tmp3\">++</A>]\n";

	     # print ($BIN from $XVal[0] to $XVal[$ii])<BR>\n";
	     
	     $in{'Limit'} = $in{'Limit'}/2;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "&nbsp; [<A HREF=\"$tmp\">v</A> Limit ";
	     $in{'Limit'} = $in{'Limit'}*4;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "<A HREF=\"$tmp\">^</A> ] &nbsp; &nbsp;\n";
	     
	     $in{'Limit'} = $SaveL;
	     
	     $in{'MDate'} =  &DateCalc("Jan 1, 1970  00:00:00 GMT",int($XValues[$#XValues] - $width));
	     $in{'MDate'} =~ s/://g;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "[<A HREF=\"$tmp\">&lt;&lt;</A> | ";
	     $in{'MDate'} =  &DateCalc("Jan 1, 1970  00:00:00 GMT",int($XValues[$#XValues] - $width/2));
	     $in{'MDate'} =~ s/://g;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "<A HREF=\"$tmp\">&lt;</A>] MDate ";
	     $in{'MDate'} =  &DateCalc("Jan 1, 1970  00:00:00 GMT",int($XValues[$#XValues] + $width/4));
	     $in{'MDate'} =~ s/://g;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "[ <A HREF=\"$tmp\">&gt;</A> | ";
	     $in{'MDate'} =  &DateCalc("Jan 1, 1970  00:00:00 GMT",int($XValues[$#XValues] + $width/2));
	     $in{'MDate'} =~ s/://g;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "<A HREF=\"$tmp\">&gt;&gt;</A> ] \n";
	     
	     $in{'MDate'} = $SaveM;
	     
	     $in{'XDate'} =  &DateCalc("Jan 1, 1970  00:00:00 GMT",int($XValues[0] - $width/2));
	     $in{'XDate'} =~ s/://g;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "[<A HREF=\"$tmp\">&lt;&lt;</A> | ";
	     $in{'XDate'} =  &DateCalc("Jan 1, 1970  00:00:00 GMT",int($XValues[0] - $width/4));
	     $in{'XDate'} =~ s/://g;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "<A HREF=\"$tmp\">&lt;</A>] XDate ";
	     $in{'XDate'} =  &DateCalc("Jan 1, 1970  00:00:00 GMT",int($XValues[0] + $width/2));
	     $in{'XDate'} =~ s/://g;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "[ <A HREF=\"$tmp\">&gt;</A> | ";
	     $in{'XDate'} =  &DateCalc("Jan 1, 1970  00:00:00 GMT",int($XValues[0] + $width));
	     $in{'XDate'} =~ s/://g;
	     $tmp = &GetURLReference(($User ne "*")?$User:"*");
	     print "<A HREF=\"$tmp\">&gt;&gt;</A> ]\n";
	     

	     
	     
	     print "</BLOCKQUOTE>";

	     # clean mem
	     undef(@XValues);
	     undef(@YValues);

	     # Dataset
	     @data=(\@XVal,\@YVal);
	     
	     $WIDTH = 1000; $HEIGHT= 500;


	     $graph  = new GD::Graph::bars($WIDTH,$HEIGHT); # area is 10% bigger than other style
	     $graph->set(
		         # x_label         => 'seconds since Jan 1, 1970  00:00:00 GMT',
		         x_label         => 'Date/Time',
			 y_label         => 'IO rate (MB/sec)',
			 title           => 'DataCarousel Performance graph',
		         line_types      => 2,
			 x_max_value     => $XVal[$#XVal],
		         x_tick_number   => 10,
		         x_number_format => \&x_format,
		         y_min_value     => 0,
		         y_max_value     => 150,
			 # y_max_value     => int($max_y + $max_y*0.01),
			 overwrite       => 1
			 ) or die $graph->error;

	    #$graph->set_title_font(['verdana','arial',gdMediumBoldFont],24);
	    #$graph->set_x_axis_font(gdMediumNormalFont,14);
	    #$graph->set_y_axis_font(gdMediumNormalFont,14);
	    #$graph->set_x_label_font(gdMediumBoldFont,14);
	    #$graph->set_y_label_font(gdMediumBoldFont,14);
	     
	     
	     my $gd = $graph->plot(\@data) or die $graph->error;

	     # ONLY the sub-directory should be writeable
	     $PATH = "/afs/rhic.bnl.gov/star/doc/www/html/tmp/pub";
	     if (! -d "$PATH/DataCarousel"){ 
		 if ( ! mkdir("$PATH/DataCarousel",0775) ){
		     print "Dcould not create temp directory\n";
		     goto GRAPH_DONE;
		 }
	     }

	     $tries =0;
	   AGAIN:
	     $tries++;
	     $jj = 0;
	     while ( -e "$PATH/DataCarousel/bla_$jj.png" && $jj < 10){
		 $jj++;
	     }
	     if ($jj == 10){  
		 unlink(glob("$PATH/DataCarousel/bla_*.png")); 
		 goto AGAIN if ( $tries < 5);
	     }

	     if ( open(GDG,">$PATH/DataCarousel/bla_$jj.png") ){
		 binmode(GDG);
		 print GDG $gd->png();
		 close(GDG);
		 print "<IMG WIDTH=$WIDTH  HEIGHT=$HEIGHT SRC=\"/webdata/pub/DataCarousel/bla_$jj.png\">\n";
	     } else {
		print "Cannot open file with index $jj. Graph is not working.\n";
	     }
	 }
       GRAPH_DONE:

     } else {
	 print 
	     "<H1>DataBase connection failed</H1>\n",
	     "Reference is $DDBREF\n";
     }
 }
 print 
    "<H5><b><i>Written 1998-2007, J.Lauret</i></b></H5>\n",
    $query->end_html(),"\n";



sub x_format
{
    my($val)=shift;
    my($date);
    
    $date = &DateCalc("Jan 1, 1970  00:00:00 GMT",int($val)); 
    $date =~ s/://g;
    
    return $date;
}


#
# %in is global. Returns the URL reference suitable for the request.
#
sub GetURLReference
{
    my($user,$sts) = @_;
    my(@items);

    if( defined($user) ){
	print "<!-- Received with $user -->\n";
	push(@items,"User=$user");
    } else {
	#push(@items,"User=".$in{'User'})   if (defined($in{'User'}));
	#print "<!-- Not received $in{'User'} -->\n";
    }
    if( ! defined($sts) && defined($in{'Failed'}) ){
	push(@items,"Failed=".$in{'Failed'});
    }
    push(@items,"MDate=" .$in{'MDate'})   if (defined($in{'MDate'}));
    push(@items,"XDate=" .$in{'XDate'})   if (defined($in{'XDate'}));
    push(@items,"Expand=".$in{'Expand'})  if (defined($in{'Expand'}));
    push(@items,"SPrcs=" .$in{'SPrcs'})   if (defined($in{'SPrcs'}));
    push(@items,"Limit=" .$in{'Limit'})   if (defined($in{'Limit'}));
    push(@items,"SList=" .$in{'SList'})   if (defined($in{'SList'}));
    push(@items,"SServ=" .$in{'SServ'})   if (defined($in{'SServ'}));
    push(@items,"SGraf=" .$in{'SGraf'})   if (defined($in{'SGraf'}));    
    push(@items,"Bin="   .$in{'Bin'})     if (defined($in{'Bin'}));        


    "$this_script?".join("&",@items); 

}
