#!/usr/local/bin/perl
#!/usr/bin/env perl 
#
# $Id:
#
# L.Didenko
#
#
##########################################################


BEGIN {
 use CGI::Carp qw(fatalsToBrowser carpout);
}

use DBI;
use CGI;
use Mysql;
use Class::Struct;


$dbhost="duvall.star.bnl.gov";
$dbuser="starreco";
$dbpass="";
$dbname="GridJobs";


 my @prodyear = ("2006","2007","2008","2009");

 my $qq = new CGI;

 my $scriptname = $qq->url(-relative=>1);

 my $pryear =  $qq->param('ryear');

 if( $pryear eq "" ) {

print $qq->header;
print $qq->start_html('Grid Jobs status Query');
print <<END;
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END
print $qq->startform(-action=>"$scriptname");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Year of Production</u></h1>\n";
print "<br>";
print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END


print "<p>";
print "</td><td>";
print "<h3 align=center> Select year</h3>";
print "<h4 align=center>";
print  $qq->scrolling_list(-name=>'ryear',
                             -values=>\@prodyear,
                             -default=>2009,
			      -size =>1);

print "<p>";
print "</td> </tr> </table><hr><center>";
print "</h4>";
print "<br>";
print "<br>";
print "<br>";
print $qq->submit,"<p>";
print $qq->reset;
print $qq->endform;
print "<br>";
print "<br>";
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

print $qq->end_html;

  }else{

my $dyear = $pryear - 2000;
if($dyear < 10) { $dyear = "0".$dyear };

# Tables
$JobStatusT = "JobStatus"."_".$dyear;


my @ardays = ();
my @arsites = ( );
my @sites = ( );
my $mydate;
my $nd = 0;
my $nsite = 0;
my $maxday = "0000-00-00";

my @viewopt = ("jobs_browser","efficiency");

  &GRdbConnect();

  $sql="SELECT DISTINCT testday  FROM $JobStatusT order by testday ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

     while($mydate = $cursor->fetchrow) {
         
        $ardays[$nd] = $mydate;
        $nd++;    
    }
      $cursor->finish;

 
  $maxday = $ardays[$nd-1];

  $sql="SELECT DISTINCT site   FROM $JobStatusT ";

   $cursor =$dbh->prepare($sql)
      || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;

    while($mysite = $cursor->fetchrow) {
        $arsites[$nsite] = $mysite;
        $nsite++;
      }

   $cursor->finish; 

  push @sites, @arsites;
  push @arsites, "ALL";
   
    &GRdbDisconnect();


 my $query = new CGI;

#my $scriptname = $query->url(-relative=>1);

 my $qdate  =  $query->param('testdate');
 my $qsite  =  $query->param('testsite');
 my $qview  =  $query->param('voption');

 if( $qdate eq "" and $qsite eq "" and $qview eq "" ) {


print $query->header;
print $query->start_html('Grid Jobs status');
print $query->startform(-action=>"gridJobStatusBrows.pl");

print "<body bgcolor=\"cornsilk\">\n";
print "<h1 align=center><u>Grid Jobs Status</u></h1>\n";
print "<br>";
print <<END;

<hr>
<table BORDER=0 align=center width=99% cellspacing=3>
<tr ALIGN=center VALIGN=CENTER NOSAVE>
<td>
END

print "<p>";
print "</td><td>";  
print "<h3 align=center> Date of Test</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'testdate',
                             -values=>\@ardays,
                             -default=>$maxday,
                             -size =>1); 


print "<p>";
print "</td><td>"; 
print "</td><td>"; 
print "</td><td>"; 
print "</td><td>"; 
print "</td><td>"; 
print "<h3 align=right> Test Site</h3>";
print "<h4 align=right>";
print  $query->scrolling_list(-name=>'testsite',
                             -values=>\@arsites,
                             -default=>ALL,
                             -size =>1); 

print "<p>";
print "</td><td>"; 
print "</td><td>";
print "</td><td>";
print "<h3 align=center> How do you like to view</h3>";
print "<h4 align=center>";
print  $query->scrolling_list(-name=>'voption',
                             -values=>\@viewopt,
                             -default=>jobs_browser,
                             -size =>1); 


print "</td><td>";
print "<h4 align=center>";
print  $query->hidden(-name=>'ryear',        
                      -values=>\@prodyear,
                     ); 
   
print "<p>";
print "</td> </tr> </table><hr><center>";
print "</h4>";
print "<br>";
print "<br>";
print "<br>";
print $query->submit,"<p>";
print $query->reset;
print $query->endform;
print "<br>";
print "<br>";
print "<address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

print $query->end_html;

  }

}
######################
sub GRdbConnect {
    $dbh = DBI->connect("dbi:mysql:$dbname:$dbhost", $dbuser, $dbpass)
        || die "Cannot connect to db server $DBI::errstr\n";
}

######################
sub GRdbDisconnect {
    $dbh = $dbh->disconnect() || die "Disconnect failure $DBI::errstr\n";
}

