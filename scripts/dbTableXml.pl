#!/opt/star/bin/perl 
#
# $Id: dbTableXml.pl,v 1.1 2000/04/28 14:08:04 porter Exp $
#
# Author: R. Jeff Porter
#***************************************************************************
#
# Description: script to produce an XML file from  
#              a header file containing a c-struct
#              Calls subroutine in 'dbSubs/defineTable.pl'
#
#****************************************************************************
# 
# $Log: dbTableXml.pl,v $
# Revision 1.1  2000/04/28 14:08:04  porter
# management perl scripts for db-structure accessible from StDbLib
#
#
#####################################

use Getopt::Std;

$DbScripts=$ENV{"STDB_ADMIN"};

if(!$DbScripts){ $DbScripts=$ENV{"STAR"}."/scripts"; }
require "$DbScripts/dbSubs/defineTableXml.pl";

getopts('f:d:n:o:hg');

$inputFile=$opt_f;
$outfile=$opt_o;
$inputDbName=$opt_d;
$debug=$opt_g;
$helpout=$opt_h;
#$namedReference=$opt_n;

if($helpout or (!$inputFile or !$inputDbName )){ Usage();}
if(!$outfile){
    $outfile=$inputFile;
    $outfile=~s/include/xml/;
    $outfile=~s/\.h/\.xml/;
}


print " inputfile= ",$inputFile,"\n input database =", $inputDbName, " \n";

##########################################
# Some Global Variables
##########################################
#$outfile='';
$dbName='';
$tableName='';
@elements=();
@elengths=();
@etypes=();
@erelationID=();
@emask=();
@edone=();
@eID=();
@eposition=();
@oelements=();
@orelationID=();
@omask=();
@oID=();
@oposition=();


print "******************************\n";
print "*\n* Running dbTableXML.pl \n*\n"; 

##########################################
#
# Read Header File & create XML version of
# database definition Table writen to $outfile
#
##########################################
#print "outputfile = ",$outfile,"\n";

defineTableXml(InputFileName=>$inputFile,DataBaseName=>$inputDbName,DEBUG=>$debug,OutputFileName=>$outfile);

print " outputfile = ",$outfile,"\n\n";
print "******************************\n";


sub Usage() {

    print "\n";
print "****  Usage   :: dbTableXML.pl -f headerfile -d database [-o outputfile] [-g|-h]\n";
print "****  Purpose :: reads c-struct in headerfile & writes db-Xml representation including the database\n";
    print "                 -o outputfile overrides default which replaces\n";
print "                    include/DataBase/*.h with xml/DataBase/*.xml\n";
print "                 -g for debug output, -h for this message \n\n";

print "****  Requires  **** Nothing \n";
exit;
}
