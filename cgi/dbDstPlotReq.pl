#! /opt/star/bin/perl -w
#
# $Id:
#
# $Log:  
#
# dbDstPlotReq.pl
#
# L.Didenko
#
# Interactive box for production plots query
# 
#############################################################################


require "/afs/rhic/star/packages/DEV/mgr/dbDstProdSetup.pl";
#require "dbDstProdSetup.pl";


use Class::Struct;
use CGI;
use CGI::Carp qw(fatalsToBrowser);

my $debugOn = 0;


my @prodSet = ( "prod4", "prod5"); 
my @mchain;
my @eachain;
my $nchain = 0;
my @evtType;
my $nevtType = 0;
my @eachEvtType;
my @mrun;
my $nmRun = 0;
my @eachRun;
my @libVer;
my $nlibVer = 0;
my @eachlibVer;

my $ii = 0;


&StDbDstProdConnect();
 
struct  JOptAttr =>  {
         prodSer  => '$',
          evType  => '$',  
          chaOpt  => '$',
         lib_Ver  => '$', 
 };
my $nseries = scalar(@prodSet);

# for ($ii=0; $ii<nseries; $i++) {

$sql="SELECT prodSeries, eventType, libVersion, chainOpt  FROM $ProdOptionsT where prodSeries = '$prodSet[$ii]' ";

  $cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
   $cursor->execute;
 
 while(@fields = $cursor->fetchrow) {
   my $cols=$cursor->{NUM_OF_FIELDS};
       $jObAdr = \(JOptAttr->new()); 

  for($i=0;$i<$cols;$i++) {
   my $fvalue=$fields[$i];
     my $fname=$cursor->{NAME}->[$i];
    print "$fname = $fvalue\n" if $debugOn;

        ($$jObAdr)->prodSer($fvalue)   if( $fname eq 'prodSeries');
        ($$jObAdr)->evType($fvalue)    if( $fname eq 'eventType');
        ($$jObAdr)->chaOpt($fvalue)    if( $fname eq 'chainOpt');
        ($$jObAdr)->lib_Ver($fvalue)    if( $fname eq 'libVersion'); 
 }
        $evtType[$nevtType] =  ($$jObAdr)->evType;
        $mchain[$nchain]    =  ($$jObAdr)->chaOpt;
        $libVer[$nlibVer]   =  ($$jObAdr)->lib_Ver;
#    print $evtType[$nevtType], $mchain[$nchain], $libVer[$nlibVer], "\n";
        $nevtType++;
        $nchain++;
        $nlibVer++;   
      }

#}

 $ii = 0;

# for ($ii=0; $ii<nseries; $i++) {

  $sql="SELECT nrun FROM $DstProductionT where prodSeries = '$prodSet[$ii]'";

 
$cursor =$dbh->prepare($sql)
  || die "Cannot prepare statement: $DBI::errstr\n";
 $cursor->execute;
 
 while(@fields = $cursor->fetchrow) {
   my $cols=$cursor->{NUM_OF_FIELDS};

  for($i=0;$i<$cols;$i++) {
   my $fvalue=$fields[$i];
    print "$fname = $fvalue\n" if $debugOn;
   
        $mrun[$nmRun] = $fvalue;
        $nmRun++;
  }
 }
#}

&StDbDstProdDisconnect();

#==============================================
##get list of run numbers

 my $lk = 2;
       $eachrun[0] = "all";
       $eachrun[1] = $mrun[0]; 
  for( $ll=1; $ll< $nmRun; $ll++) {
       if( !($mrun[$ll] eq $mrun[$ll-1])) {
       $eachrun[$lk] = $mrun[$ll];  
         $lk++;
	   }
	}

##get list of event type

my $ik = 2;
        $eachEvtType[0] = "all";
        $eachEvtType[1] = $evtType[0];
     for( $ll=1; $ll< $nevtType; $ll++) {
       if( !($evtType[$ll] eq $evtType[$ll-1]))  {
             $eachEvtType[$ik] = $evtType[$ll];
              $ik++;
	   }
     }

          
##get list of chain options

my $knext = 0;
my $nkchain = 1;

     $eachain[0] = "all";
  for ($ll = 0; $ll<$nchain; $ll++)  {
    if($ll ne ($nchain - 1)) {
          $knext = $ll + 1;
       for ($kk = $knext; $kk<$nchain; $kk++) {
            if(($mchain[$ll] eq $mchain[$kk]) and ($mchain[$ll] ne "no"))  {
                     $mchain[$kk] = "no";
           }                  
	  }
	}
   }

    for ($ll = 0; $ll<$nchain; $ll++)  {
      if( $mchain[$ll] ne "no") {
          $eachain[$nkchain] =  $mchain[$ll];
           $nkchain++;
     }
  } 
      

my @myplot =   (
                 "Memory_Size",
                 "CPU_Event",
                 "Avg_No_Tracks",
                 "Avg_No_Vertexes"
                );   

$query = new CGI;

print $query->header;
print $query->start_html('dbDstPlots');
print $query->startform(-action=>"GifDstPlots.pl");  

  print "<html>\n";
  print " <head>\n";

print <<END;
<META Name="Production plotes" CONTENT="This site demonstrates plots for production operation">
<META HTTP-EQUIV="Expires" CONTENT="0">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
END

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
print "Select production series";
print $query->popup_menu(-name=>'set1',
                   -values=>\@prodSet,
                   ); 


print <<END;
</SELECT><br>
<p>
<br>
END

 print "<p>";
 print "Select event type:";
 print $query->popup_menu(-name=>'EvType',
                    -values=>\@eachEvtType,
                    ); 

print <<END;
</SELECT><br>
<p>
<br>
END

 print "<p>";
 print "Select run number:";
 print $query->popup_menu(-name=>'numRun',
                    -values=>\@eachrun,
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
  GifDstPlots($query);
}
print $query->delete_all;
print $query->end_html; 







