#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:  
#
# dbPlotReq.pl
#
# Interactive box for production plots query
# 
#
#############################################################################


use CGI;
require "dbOperaSetup.pl";

my $debugOn = 0;

my @prod_set = (
                  "auau100/venus412/default/b0_3/year_1s/hadronic_on",
                  "auau100/venus412/default/b3_6/year_1s/hadronic_on",
                  "auau100/venus412/default/b6_9/year_1s/hadronic_on",
                  "auau200/venus412/default/b0_3/year_1b/hadronic_on",
                  "auau200/hijing135/jetq_off/b0_3/year_1b/hadronic_on",
                  "auau200/hijing135/jetq_on/b0_3/year_1b/hadronic_on"
                  );
 
my @sets_name;
my @subset;
 
my $qq = new CGI;
my $sets = $qq->param("sets");

&StDbOperaConnect();


my $sql = "SELECT SetName FROM $OperationT WHERE SetName = '$sets'"; 
   $cursor =$dbh->prepare($sql)
        || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute;
while(my ($subset) = $cursor->fetchrow_array) {
      push (@subset, $sets_name);
    }

&StDbOperaDisconnect();

for( $ll=0; $ll<scalar(@prod_set); $ll++) {
   if( !(defined($sets_name[$ll]))) {  
 $sets_name[$ll] = $prod_set[$ll] ;
 } 
}  

my @setp_name;
   $setp_name[0] = "no";

for( $ll=0; $ll<scalar(@sets_name); $ll++) {
    $setp_name[$ll+1] = $sets_name[$ll];
 } 

my @chainOpt = (
                  
                  "tfs_y1b_eval_fzin_xout",
                  "tfs_y1b_eval_allevent_fzin_xout"
               );

my @libTag =   ( 
                 "all",
                 "SL99f_7",
                 "SL99g_4"
               ); 

my @lib2Tag =  (
                 "no",
                 "SL99f_7",
                 "SL99g_4"
               ); 
                      
$query = new CGI;

print $query->header;
print $query->start_html('dbPlotReq');
  

  print "<html>\n";
  print " <head>\n";
  print " <title>Select query for plot</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "  <h1>Select query for plot </h1>\n";
  print " </head>\n";
  print " <body>";


print <<END;
<form action="http://duvall.star.bnl.gov/cgi-bin/didenko/dbPlotReq.pl?" method="post"><br>
Select name of set: 
<SELECT NAME="set1">
END


for( $ll=0; $ll<scalar(@sets_name); $ll++) {
print <<END;
<OPTION VALUE=$sets_name[$ll]>$sets_name[$ll]
END
}


print <<END;
</SELECT><br>
<form action="http://duvall.star.bnl.gov/cgi-bin/didenko/dbPlotReq.pl?" method="post"><br>
Select name of set: 
<SELECT NAME="set2">
END


for( $ll=0; $ll<scalar(@setp_name); $ll++) {
print <<END;
<OPTION VALUE=$setp_name[$ll]>$setp_name[$ll]
END
}



print <<END;
</SELECT><br>
<p>
<br>
END
print$query->start_form;
print "<p>";
print "Select chain option:";
print $query->popup_menu(-name=>'chain',
                   -values=>\@chainOpt,
                   ); 


print <<END;
 </SELECT><br>
<p>
<br>
END

print "<p>";
print "Select library tag:";
print $query->popup_menu(-name=>'libTag1',
                   -values=>\@libTag,
                   -default=>'all'
                   ); 

print <<END;
 </SELECT><br>
END
print "<p>";
print "Select library tag:";
print $query->popup_menu(-name=>'libTag2',
                   -values=>\@lib2Tag,
                   -default=>'no'
                   ); 


print <<END;
</SELECT><br>
<p>
<br>
Enter date of production yyyy-mm-dd:<br>       <input type="text" size=12 name="datProd"><br>
Enter second date of production if needed yyyy-mm-dd:  <br><input type="text" size=12 name="dat2Prod"><br>
<p>
<br>
<input type="submit" size=10 name=""><br>
</form>
END


 print $query->endform;

  print "</body>";
  print "</html>";
  print $query->end_html;


 $set1 =  $query->param('set1');
 $set2 =  $query->param('set2');
 $chain = $query->param('chain');
 $libTag1 = $query->param('libtag1');
 $libTag2 = $query->param('libtag2');
 $datProd = $query->param('datProd');
 
 
