#!/opt/star/bin/perl 
#
# $Id: dbDeleteData.pl,v 1.1 2000/04/28 14:08:03 porter Exp $
#
# Author: R. Jeff Porter
#***************************************************************************
#
# Description: Script used to delete a data entry  
#              name,version,timestamp,[elementID],dataID become
#
#              Use for mistakes during data entries that are not 
#              used during reconstruction
#              Use 'dbDeActivateData.pl' for all other cases.
#
#****************************************************************************
# 
# $Log: dbDeleteData.pl,v $
# Revision 1.1  2000/04/28 14:08:03  porter
# management perl scripts for db-structure accessible from StDbLib
#
#
#####################################

use Getopt::Std;
use DBI;

$DbScripts=$ENV{"STDB_ADMIN"};
if(!$DbScripts){ $DbScripts=$ENV{"STAR"}."/scripts"; }


getopts('n:v:e:t:d:s:c:hg');

my ($dbh, $sth1, $sth2, $sth3, $sth4);
my ($name, $version, $elementID, $timeStamp, $dbName, $serverHost);
my ($nodeID, $cstructName );
my ($nodeList, $otherNodeIDs, $otherRefs );
my ($countID, $dataID); 


$name=$opt_n;
$version=$opt_v;
$elementID=$opt_e;
$timeStamp=$opt_t;
$dbName=$opt_d;
$serverHost=$opt_s;
$comment=$opt_c;

my $debug=$opt_g;
my $helpout=$opt_h;

if($helpout or !$name or !$version or !$timeStamp or !$dbName or !$serverHost) { Usage(); }

if($debug){
    print "Name=",$name,"\n";
    print "version=",$version,"\n";
    print "elementID=",$elementID,"\n";
    print "timeStamp=",$timeStamp,"\n";
    print "dbName=",$dbName,"\n";
    print "serverHost=",$serverHost,"\n";
}

  print "DataBase = ",$dbName,"\n";
#
#-> connect to DB
#
$dbh = DBI->connect("DBI:mysql:$dbName:$serverHost",$dbuser,$dbpass)
    || die "Cannot connect to server $DBI::errstr\n";


#--- get nodeID for query into dataIndex 
$query = qq{select id, elementID, cstructName from Nodes}.
         qq{ where Nodes.name='$name' and Nodes.versionKey='$version'};

if($debug) {print $query,"\n";}
$sth1=$dbh->prepare($query);
$sth1->execute;

if(!(($nodeID, $dbElementID, $cstructName )=$sth1->fetchrow)){ die "Couldn't find Node=".$name." of version=".$version."\n";}
$sth1->finish;
    
if($debug){print $nodeID," & ",$dbElementID," & ",$cstructName,"\n";}

$query2 = qq{ select id from Nodes where cstructName='$cstructName'};
$sth2=$dbh->prepare($query);
$sth2->execute;

$nodeList='';

while(($otherNodeIDs)=$sth2->fetchrow){
    $nodeList=joint(",",$nodeList,$otherNodeIDs);
}


my $done=0;
my $doneCommas=0;
#------- evaluate elementID as string=n1,n2,n3,...
#  --- even though it may be entered as string=n1-n3,n6,n7,n8-n9....
if(!$elementID){
    if($dbElementID=~m/None/){ $elementID=0;}
    while(!$done){
     if($dbElementID=~m/\-/){
         @tmp=split /\-/, $dbElementID, 2;        # split at -
         $emin=$tmp[0];
         $emax=$tmp[1];

         if($tmp[0]=~m/\,/){                      #--> is 1st a comma'd list?
             $loopList=$tmp[0];
             $doneCommas=0;
             while(!$doneCommas){                 #--> find last entry in list
                 @tmpCommas=split /\,/, $loopList, 2;
                 if($tmpCommas[1]=~m/\,/){
                     $loopList=$tmpCommas[1];
                 } else {
                     $emin=$tmpCommas[1];
                     $doneCommas=1;
                 }
             }
         } else { #--> not a comma'd list
             $emin=$tmp[0];
         }
         if($tmp[1]=~m/\,/){                      #--> is 2nd  a comma'd list?
             $loopList=$tmp[1];
             @tmpCommas=split /\,/, $loopList, 2; #--> find 1st entry in list
             $emax=$tmpCommas[0];
         } else {                                 # --> not a comma'd list
             $emax=$tmp[1];
         }
     

         $elementID=join(",",$elementID,$tmp[0]);
         for($i=$emin+1;$i<$emax;$i++){           #--> load into comma'd list
                $elementID= join(",",$elementID,$i);
            }
         $elementID=join(",",$elementID,$tmp[1]);
         $dbElementID=$elementID;            

     } else {                                     #--> All -'s removed
       $done=1;
       $elementID=$dbElementID;
     }
 }

}


#--- check that dataIndex rows exist 
$qIndex = qq{ select count, dataID from dataIndex} .
    qq{ where nodeID=$nodeID and version='$version'} .
    qq{ and elementID In($elementID) and beginTime='$timeStamp'};


if($debug) { print $qIndex,"\n"};

$sth1=$dbh->prepare($qIndex);
$sth1->execute;

$qMod=qq{delete dataIndex where count=?};
$sth2=$dbh->prepare($qMod);

$dDel=qq{delete $cstructName where dataID=?};
$sth3=$dbh->prepare($dDel);

$qCheck = qq{ select COUNT(dataIndex) from dataIndex} .
          qq{ where nodeID In($nodeList) and dataID=? Group by dataID };

$sth4=$dbh->prepare($qCheck);

my $done=0;

while(!$done){

($countID, $dataID)=$sth1->fetchrow;
 
 if($countID and $dataID){   
    $sth2->execute($countID);
#--> check for other references to data & if none; delete data
    $sth4->execute($dataID);
    if( !(($otherRefs)=$sth4->fetchrow)){ $sth3->execute($dataID); }
  } else {
    $done=1;
  }

}
       
$sth1->finish;
$sth2->finish;
$sth3->finish;
$sth4->finish;

$dbh->disconnect;


############################################################################
#
#  usage subroutine
#
############################################################################

sub Usage() {

    print "\n";
print "****  Usage   :: dbDeleteData.pl -n name -v version -t timestamp [-e elementID] -d database -s server [-c comment] [-g|-h]\n";
print "****  Purpose :: delete data & reference to data \n";
    print "                 -n name of data reference\n";
    print "                 -v version of data reference\n";
    print "                 -t timestamp of data reference\n";
    print "                 -e elementID list: default is that in DB-Nodes table\n";
    print "                 -d database containing reference \n";
    print "                 -s server has the form 'hostname:portnumber' or simply\n";
    print "                 'hostname' if portnumber=3306\n";
print "                 -c comment for logging this action\n";
print "                 -g for debug output\n";
print "                 -h for this message \n\n";
print "****  Requires  **** Write-Access to database\n";

exit;

}



