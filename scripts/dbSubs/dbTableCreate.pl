#!/opt/star/bin/perl -w
#
# $Id: dbTableCreate.pl,v 1.1 2000/04/28 14:08:21 porter Exp $
#
# Author: R. Jeff Porter
#
#***************************************************************************
#
# Description: checks table-structure in database to select whether
#              to create a new table or evolve current table
#
#****************************************************************************
# 
# $Log: dbTableCreate.pl,v $
# Revision 1.1  2000/04/28 14:08:21  porter
# management perl scripts for db-structure accessible from StDbLib
#
#
#####################################

use DBI;

$DbScripts=$ENV{"STDB_ADMIN"};

if(!$DbScripts){ $DbScripts=$ENV{"STAR"}."/scripts"; }

require "$DbScripts/dbSubs/newTable.pl";
require "$DbScripts/dbSubs/evolveTable.pl";

sub dbTableCreate(){

  my %args = (
              TableName => '',
              UserName => '',
              dbName => '',
              PassWord => '',
              DEBUG => '',
              dbHostName => '',
              NameRef=>'',
              @_,
              );

  if($args{DEBUG}){
  print $args{TableName}, "\n";
  print $args{UserName}, "\n";
  print $args{dbName}, "\n";
  print $args{dbHostName}, "\n";
  print $args{NameRef}, "\n";
}

  $structTableName="structure";
  $schemaTableName="schema";
  $relationTableName="relation";
  $namedRef = $args{NameRef};

  $dbname = $args{dbName};
  $dbhostname = $args{dbHostName};
  $tableName =  $args{TableName};
  $indexTableName = join("",$args{TableName},"Index");
  $dbuser = $args{UserName};
  $dbpass = $args{PassWord};

########################################################
#
# 5 tables need to accessed, all in the same DataBase
#   Steps:
#    1. connect to Db
#    2. request Schema that exist for "tableName" from
#       Structures,Schema, & Relations Tables.
#    3.a. If 2=null (tableName is new) then
#        create Table in S,S, & R. 
#        create indexTable (version & timestamp access:
#        create dataTable (id + data)
#
#    3.b. If 2=exists check schema for compatibility:
#          if(identical) check if index & data Tables exists
#          and create if need be.
#          if(!identical) update S,S,&R
#                         update dataTable
#
########################################################

#
#-> connect to DB
#

$dbh = DBI->connect("DBI:mysql:$dbname:$dbhostname",$dbuser,$dbpass)
    || die "Cannot connect to server $DBI::errstr\n";

#
#-> prepare Query for Schema
#
#
# Check whether this structure "name" exists
#

  $ssrQuery="SELECT structure.lastSchemaID FROM structure WHERE structure.name='".$tableName."'";
  if($debug){ print $ssrQuery, "\n";}

  $sth=$dbh->prepare($ssrQuery);
  $sth->execute;
  if(!((@row)=$sth->fetchrow_array)){      # it is new
  
      newTable();
 
  } else {    

      evolveTable();
  }

}

1;




