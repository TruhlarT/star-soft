#!/opt/star/bin/perl 
#
# $Id: dbDefTable.pl,v 1.1 2000/04/28 14:08:03 porter Exp $
#
# Author: R. Jeff Porter
#
#***************************************************************************
#
# Description: script to parse an XML version of a c-struct  
#              & load schema into the database
#              Calls subroutines in 
#                  'dbSubs/parseXmlTable.pl'
#                  'dbSubs/dbTableCreate.pl'
#
#****************************************************************************
# 
# $Log: dbDefTable.pl,v $
# Revision 1.1  2000/04/28 14:08:03  porter
# management perl scripts for db-structure accessible from StDbLib
#
#
#####################################

use Getopt::Std;

$DbScripts=$ENV{"STDB_ADMIN"};

if(!$DbScripts){ $DbScripts=$ENV{"STAR"}."/scripts"; }

require "$DbScripts/dbSubs/parseXmlTable.pl";
require "$DbScripts/dbSubs/dbTableCreate.pl";

getopts('f:d:s:p:gh');

 $inputFile=$opt_f;
 $dbName=$opt_d;
 $debug=$opt_g;
 $helpout=$opt_h;
 $serverHost=$opt_s;
 $passwd=$opt_p;

if($helpout or (!$inputFile or !$serverHost)){ Usage();};

if($debug){print $inputFile," \n";}

##########################################
# Some Global Variables
##########################################

$outfile='';
$tableName='';
$tableComment='';
$namedRef='';
@elements=();
@elengths=();
@ecomments=();
@atypes=();
@amysqltypes=();
@mysqltypes=();
@etypes=();
@erelationID=();
@emask=();
@edone=();
@eID=();
@eposition=();
@oelements=();
@ocomments=();
@orelationID=();
@omask=();
@oID=();
@oposition=();


#########################################
#
# Parse the XML db-Definition to load into
# memory
#
#########################################

parse_table(fileName=>$inputFile,DEBUG=>$debug,DataBase=>$dbName);

print "******************************\n";
print "*\n* Running dbDefTable.pl \n*\n"; 
  print "Defining TableName= ",$tableName,"\n";
  print "In DataBase = ",$dbName,"\n";

#  for($i=0; $i<=$#elements;$i++){
#      print $etypes[$i]," ",$elements[$i],"[",$elengths[$i],"]\n";
#  }

########################################
#
# Set some variables in case of 
# schema evolution
#
########################################

$#eID=$#emask=$#relationID=$#eposition=$#edone=$#elements;

for($i=0;$i<=$#elements;$i++){
    $edone[$i]=0;
    $emask[$i]=1;
}

dbTableCreate(dbHostName=>$serverHost, DEBUG=>$debug, TableName=>$tableName, dbName=>$dbName, NameRef=>$namedRef, PassWord=>$passwd);

#print "*\n* End of dbDefTable.pl \n*\n";
print "**************************************************************\n";


#########################################################################
#
#
##########################################################################
sub Usage() {

    print "\n";
print "****  Usage   :: dbDefTable.pl -f xmlfile -s server [-p passwd] [-d database]  [-g|-h]\n";
print "****  Purpose :: Loads schema for a single table stored in an XML file\n";
    print "                 -f xml-file\n";
    print "                 -s server has the form 'hostname:portnumber' or simply\n";
    print "                 'hostname' if portnumber=3306\n";
    print "                 -p passwd option if one is needed to write to specified db \n";
print "                 -d database option overides database in the xml-file\n";
print "                 -g for debug output\n";
print "                 -h for this message \n\n";

print "****  Requires  **** Write-Access to database\n";

exit;
}








