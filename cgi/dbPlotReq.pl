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


require "dbOperaSetup.pl";
use CGI;
use CGI::Carp qw(fatalsToBrowser);

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
my $nsets = 0;

&StDbOperaConnect();
 
 my $sql = "SELECT SetName FROM $OperationT";
   $cursor =$dbh->prepare($sql)
        || die "Cannot prepare statement: $DBI::errstr\n";
    $cursor->execute;

while(@fields = $cursor->fetchrow) {
   my $cols=$cursor->{NUM_OF_FIELDS};
     for($i=0;$i<$cols;$i++) {
    my $fvalue=$fields[$i];
     $sets_prod[$nsets] = $fvalue;
     $nsets++;    
  }
 }
 my $lk = 1;
       $sets_name[0] = $sets_prod[0]; 
  for( $ll=1; $ll< $nsets; $ll++) {
       if( !($sets_prod[$ll] eq $sets_prod[$ll-1])) {
       $sets_name[$lk] = $sets_prod[$ll];  
         $lk++;
	   }
	}

&StDbOperaDisconnect();

#for( $ll=0; $ll<scalar(@prod_set); $ll++) {
#   if( !(defined($sets_name[$ll]))) {  
# $sets_name[$ll] = $prod_set[$ll] ;
# } 
#}  

my @chainOpt = (
                  "tfs_y1b_eval_fzin_xout",
                  "tfs_y1b_-emc_eval_fzin_xout",
                  "tfs_y1b_eval_allevent_fzin_xout"
               );

my @libTag =   ( 
                 "SL99f_7",
                 "SL99g_4"
               ); 
                      
my @myplot =   (
                 "Memory_Size",
                 "CPU_Event",
                 "Avg_No_Tracks",
                 "Avg_No_Vertexes"
                );   

$query = new CGI;

print $query->header;
print $query->start_html('dbPlots');
print $query->startform(-action=>"GifPlots.pl");  

  print "<html>\n";
  print " <head>\n";

print <<END;
<META Name="Production plotes" CONTENT="This site demonstrates plots for production operation">
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END

#<META HTTP-equiv="Refresh" content="10; URL-HTTP://duvall.star.bnl.gov/cgi-bin#/didenko/GifPlots.pl">

  print " <title>Select query for plot</title>";
  print "  </head>\n";
  print "  <body bgcolor=\"#ffdc9f\"> \n";
  print "  <h1>Select query for plot </h1>\n";
  print " </head>\n";
  print " <body>";


print <<END;
</SELECT><br>
<p>
<br>
END

print "<p>";
print "Select name of set:";
print $query->popup_menu(-name=>'set1',
                   -values=>\@sets_name,
                   ); 

 
print <<END;
</SELECT><br>
<p>
<br>
END

print "<p>";
print "Select chain option:";
print $query->popup_menu(-name=>'mchain',
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
                    -values=>\@libTag,sar
                    ); 


print <<END;
</SELECT><br>
<p>
<br>
Enter date of production yyyy-mm-dd:    <input type="text" size=12 name="datProd"><br>
<p>
END

print <<END;
</SELECT><br>
<p>
END

print "Select plots:";
print $query->popup_menu(-name=>'plotVal',
                   -values=>\@myplot,
                   ); 

 print "<p>";
 print "<p><br>"; 
 print $query->submit;
 print "<P><br>", $query->reset;
 print $query->endform;
 print "  <address><a href=\"mailto:didenko\@bnl.gov\">Lidia Didenko</a></address>\n";

 print "</body>";
 print "</html>";
  

#=======================================================================

if($query->param) {
  GifPlots($query);
}
print $query->delete_all;
print $query->end_html; 






