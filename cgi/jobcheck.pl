#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:
######################################################################
#
# jobcheck.pl
#
# Wensheng Deng 9/99
#
# Check daily test logfiles and present to the web page
#
# Usage: http://duvall.star.bnl.gov/devcgi/jobcheck.pl
#


use CGI;

$newHomeDir = "/disk00000/star/test/new";
$devHomeDir = "/disk00000/star/test/dev";

@tpcOsChoice = (
		"tfs_Linux",
		"tfs_Solaris", 
		"trs_Linux",
		"trs_Solaris" 
	       );

@wday =        (
		"Mon", 
		"Tue",
		"Wed",
		"Thu",
		"Fri"
	       );

@yearChoice = (
	       "year_1b",
	       "year_2a"
	      );

@month = ("Jan",  "Feb", "March", "April", "May", "June",
	  "July", "Aug", "Sep",   "Oct",   "Nov", "Dec"  );

my $logfileDir;
my $logfile;
my $status; # (1).crash  (2).done event number (3) hangup (4) working?
my $date;


##
&header();
&newCheck();
&devCheck("tfs_Linux",1);
&devCheck("tfs_Solaris",1);
#&devCheck("tss_Linux",1);
#&devCheck("tss_Solaris",1);
#&devCheck("trs_Linux",1);
#&devCheck("trs_Solaris",1);

## footer
print <<END;
</TABLE>
</BODY>
</HTML>
END

## end of main 

############
sub header {
print <<END;
Content-type: text/html

<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1252">
<META NAME="Generator" CONTENT="Microsoft Word 97">
<TITLE>Status of library</TITLE>
<META NAME="Template" CONTENT="C:\Program Files\Microsoft Office\Office\html.dot">
</HEAD>
<BODY TEXT="#000000" LINK="#0000ff" VLINK="#800080" BGCOLOR="#ccffff">
<DIR>
<DIR>
<DIR>
<DIR>
<DIR>
<DIR>

<B><FONT SIZE=5 COLOR="#000080"><P>Test files location and availability</P>
</B></FONT><P>&nbsp;</P></DIR>
</DIR>
</DIR>
</DIR>
</DIR>
END
}

############
sub newCheck {

#<P><IMG SRC="Bullet1.gif" WIDTH=13 HEIGHT=13><B><FONT SIZE=5>&nbsp;</FONT><FONT SIZE=4>/disk00000/star/test/new/</B></FONT></P>

print <<END;
<P><B><FONT SIZE=5>&nbsp;</FONT><FONT SIZE=4>/disk00000/star/test/new/</B></FONT></P>
 <h4>
<TABLE BORDER=1 CELLSPACING=0 CELLPADDING=0 >
<TR>

<TR ALIGN=CENTER VALIGN=CENTER>


<TD WIDTH=110 HEIGHT=50><B>year</B></TD>
<TD WIDTH=110 HEIGHT=50><B>tfs_Linux/</B></TD>
<TD WIDTH=110 HEIGHT=50><B>tfs_Solaris/</B></TD>
<TD WIDTH=110 HEIGHT=50><B>trs_Linux/</B></TD>
<TD WIDTH=110 HEIGHT=50><B>trs_Solaris/</B></TD>
</TR>
END

  for( $lv1=0; $lv1<scalar(@yearChoice); $lv1++ ) { 

print <<END;
<TR ALIGN=CENTER VALIGN=CENTER>
<TD><B>$yearChoice[$lv1]</B></TD>
END

  for( $lv2=0; $lv2<scalar(@tpcOsChoice); $lv2++ ) { 
    $logfileDir = "$newHomeDir/$tpcOsChoice[$lv2]/$yearChoice[$lv1]";
    
    $logfile = "1111"; # For the checking of existence of logfile 
    &getLogfile($logfileDir, $logfile);

    if ( $logfile eq "1111") {
    
print <<END;
<TD><B>no logfile<br></B></TD>
END

    } else {
    &getStatus($logfile, $status, $date);
    
print <<END;
<TD><B>$status<br>$date</B></TD>
END

  }
  }

print <<END;
</TR>
END
  
  }
}

################
  sub devCheck {
    ($tpcOs, $useless) = @_;
    $useless = 1;

print <<END;
 <h4>
</TABLE>
<P><B><FONT SIZE=5>&nbsp;</FONT><FONT SIZE=4>/disk00000/star/test/dev/$tpcOs/</B></FONT></P>
 <h4>
<TABLE BORDER=1 CELLSPACING=0 CELLPADDING=0 >
<TR>

<TR ALIGN=CENTER VALIGN=CENTER>

<TD WIDTH=110 HEIGHT=50><B>year</B></TD>
<TD WIDTH=110 HEIGHT=50><B>Mon/</B></TD>
<TD WIDTH=110 HEIGHT=50><B>Tue/</B></TD>
<TD WIDTH=110 HEIGHT=50><B>Wed/</B></TD>
<TD WIDTH=110 HEIGHT=50><B>Thu/</B></TD>
<TD WIDTH=110 HEIGHT=50><B>Fri/</B></TD>
</TR>
END


  for( $lv1=0; $lv1<scalar(@yearChoice); $lv1++ ) { 

print <<END;
<TR ALIGN=CENTER VALIGN=CENTER>
<TD><B>$yearChoice[$lv1]</B></TD>
END

  for( $lv2=0; $lv2<scalar(@wday); $lv2++ ) { 
    $logfileDir = "$devHomeDir/$tpcOs/$wday[$lv2]/$yearChoice[$lv1]";
   
    $logfile = "1111"; # For the checking of existence of logfile 
    &getLogfile($logfileDir, $logfile);
    if ( $logfile eq "1111") {
    
print <<END;
<TD><B>no logfile<br></B></TD>
END

    } else {
    &getStatus($logfile, $status, $date);

print <<END;
<TD><B>$status<br>$date</B></TD>
END


     }
  }

print <<END;
</TR>
END
  
  }
  }

################
  sub getLogfile {
    ($dir, $logfile) = @_;

    opendir(DIR, $dir) or die "can't opendir $dir: $!";
    while( defined($filename = readdir(DIR)) ) {
      next if $filename =~ /^\.\.?$/;
      next if ( !($filename =~ /.log$/) );

      $logfilename = $filename;
      $logfile = "$dir/$logfilename";

      last;
    }

    closedir DIR;
  }

################
  sub getStatus {
    ($logfile, $status, $date) = @_;
    
    $mTime = (stat($logfile))[9];
    ($dy,$mo) = (localtime($mTime))[3,4,5];
    $mo = $month[$mo];

    $date = "$mo $dy";

    @completed = `grep 'Run completed' $logfile;`;
    @segviol = `grep 'segmentation violation' $logfile;`;
    @buserr = `grep 'bus error' $logfile;`;

    if ( scalar(@segviol)>=1 || scalar(@buserr)>=1  ) {
      $status = "crashed"; 
    } elsif ( scalar(@completed)>=1 ) {
      @events = `grep 'Done with Event' $logfile;`;
      $nEvts = scalar(@events);
      $status = "done $nEvts evts"; 
    } else {
      $timeNow = time();
      $timeDiff = ($timeNow - $mTime)/ (60.*60.);
      if ( $timeDiff > 2.0 ) {
	$status = "hungup";
      } else {
	$status = "running?";
      }
    }
  
  }
