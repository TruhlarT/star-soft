#!/usr/bin/perl 
#
# $Id: dbNewStoreTable.pl,v 1.1 2003/01/09 20:35:02 porter Exp $
#
# Author: R. Jeff Porter
#
#***************************************************************************
#
# Description: loads a new storage table into the db
#  
#****************************************************************************
# 
# $Log: dbNewStoreTable.pl,v $
# Revision 1.1  2003/01/09 20:35:02  porter
# some additional script to complete the upgrade
#
#
#
###########################################################

use DBI;

$DbScripts=$ENV{"STDB_ADMIN"};
if(!$DbScripts){ $DbScripts=$ENV{"STAR"}."/scripts"; };

require "$DbScripts/dbSubs/defineTableSQL.pl";
require "$DbScripts/dbSubs/prepSQLElement.pl";

sub dbNewStoreTable() {


  my %args = (
              dbHostName => '',
              dbName     => '',
              nodeName   => '',
              versionKey => '',
              storeTable => '',
              beginTime  => '',
              endTime    => '',
              DEBUG      => '',
              PassWord   => '',
              @_,
              );


  if($args{DEBUG}){
      print "Host        = ",$args{dbHostName},"\n";
      print "DB          = ",$args{dbName},"\n";
      print "Node        = ",$args{nodeName},"\n";
      print "Version     = ",$args{versionKey},"\n";
      print "storeTable  = ",$args{storeTable},"\n";
      print "beginTime   = ",$args{beginTime},"\n";
      print "endTime     = ",$args{endTime},"\n";
  }

########################################################
#
# check if node catalog exists & get struct definition
#
#######################################################

 my  $dbname = $args{dbName};
 my  $dbhostname = $args{dbHostName};
 my  $nodeName   = $args{nodeName};
 my  $version    = $args{versionKey};
 my  $dbpass     = $args{PassWord};

 my $dbh = DBI->connect("DBI:mysql:$dbname:$dbhostname",$dbuser,$dbpass)
    || die "Cannot connect to server $DBI::errstr\n";
 
 my $nodeQuery = qq { select structName, ID from Nodes } .
                 qq { where name='$nodeName' and versionKey='$version'};

  if($args{DEBUG}) { print $nodeQuery,"\n";};
  my $sth=$dbh->prepare($nodeQuery);
  $sth->execute;
  my ($cstruct, $nodeID);
  if(! (($cstruct, $nodeID)=$sth->fetchrow_array)){
     $dbh->disconnect;
     die "Cannot find node $nodeName\n";
   }
  $sth->finish;

#################
# initial table
#################

  my $beginSQL=defineTableSQL($args{storeTable},0,$nodeID);
  if($args{DEBUG}){  print $beginSQL;};

  my $sidQuery = qq{ select lastSchemaID from structure where name='$cstruct'};
  $sth=$dbh->prepare($sidQuery);
  $sth->execute;
  my $mlastSchemaID;
  if( !(($mlastSchemaID)=$sth->fetchrow)){ die "No structure defined for $cstruct\n";};
  $sth->finish;

  my $schemaQuery = qq { select schema.name, schema.type, schema.storeType, } .
         qq { schema.length, schema.position from schema } .
         qq { left join structure on structure.name=schema.structName } .
         qq { where structure.name='$cstruct' } .
         qq { and schema.schemaID=$mlastSchemaID Order by schema.position } ;

  $sth=$dbh->prepare($schemaQuery);
  $sth->execute;

  my @edescription;
  my $elementList='';
  while((@edescription)=$sth->fetchrow_array){
      my $sqlElement = prepSQLElement(@edescription);
      $elementList = $elementList.",".$sqlElement; 
  };
  $sth->finish;

  if($args{DEBUG}){  print $elementList;};
  my $endSQL=defineTableSQL($args{storeTable},1,0);
  if($args{DEBUG}){  print $endSQL;};


  my $createTable=qq { $beginSQL $elementList , $endSQL };
#  if($args{DEBUG}){ print $createTable,"\n"; }

  $dbh->do($createTable);

###################################################
#
# store timestamp reference in the tableCatalog
#
###################################################  


my $catInsert=qq{ insert into tableCatalog set }.
    qq{ nodeName='$nodeName', }.
    qq{ nodeID='$nodeID', }.
    qq{ tableName='$args{storeTable}', }.
    qq{ beginTime=$args{beginTime}};
    my $endTime='';
    if($args{endTime}) { 
        $endTime= qq {, endTime='$args{endTime}'};
    }
    
    $catInsert=$catInsert.$endTime;
    $dbh->do($catInsert);

$dbh->disconnect;

}

1;









