#!/opt/star/bin/perl -w
#
# $Id: dbTableCheck.pl,v 1.1 2000/04/28 14:08:21 porter Exp $
#
# Author: R. Jeff Porter
#
#***************************************************************************
#
# Description: requests table-schema from database for use in other scripts
#
#****************************************************************************
# 
# $Log: dbTableCheck.pl,v $
# Revision 1.1  2000/04/28 14:08:21  porter
# management perl scripts for db-structure accessible from StDbLib
#
#
#####################################

use DBI;

$DbScripts=$ENV{"STDB_ADMIN"};
if(!$DbScripts){ $DbScripts=$ENV{"STAR"}."/scripts"; }
require "$DbScripts/dbSubs/evalSchema.pl";

sub dbTableCheck(){

  my %args = (
              TableName => '',
              SchemaID => '',
              UserName => '',
              dbHostName => '',
              dbName => '',
              PassWord => '',
              DEBUG => '',
              MakeIDL => '',
              OnlIDL => '',
              MakeHeader => '',
              dbHostName => '',
              @_,
              );

  @tableComments=();
  @tableNames=();

 if($args{DEBUG}){
    print "TableName = ", $args{TableName}, "\n";
    print "SchemaID = ", $args{SchemaID}, "\n";
    print "UserName = ", $args{UserName}, "\n";
    print "Database Name = ", $args{dbName}, "\n";
    print "Host Name = ", $args{dbHostName}, "\n";
    print "IdlDir = ", $args{MakeIDL}, "\n";
    print "HeaderDir = ", $args{MakeHeader}, "\n";
    print "OnlIdl = ",$args{OnlIDL},"\n";
 }

  $dbname          = $args{dbName};
  $dbhostname      = $args{dbHostName};
  $tableName       = $args{TableName};
  $requestSchemaID = $args{SchemaID};

  $mkIdl           = $args{MakeIDL};
  $mkH             = $args{MakeHeader};
  
  $dbuser          = $args{UserName};
  $dbpass          = $args{PassWord};

#---------------------------------------------------------------------
#-> connect to DB
#---------------------------------------------------------------------

$dbh = DBI->connect("DBI:mysql:$dbname:$dbhostname",$dbuser,$dbpass)
    || die "Cannot connect to server $DBI::errstr\n";

#---------------------------------------------------------------------
#-> prepare Query for Schema
# Check whether this structure "name" exists
#---------------------------------------------------------------------
  @tableNames=();

if(!$tableName && ($mkIdl || $mkH)){
     # then requesting all tables in database
     $ssrQuery=qq{Select structure.name from structure};
     $sth=$dbh->prepare($ssrQuery);
     $sth->execute;
     while(((@row)=$sth->fetchrow_array)){
         $#tableNames++;
         $tableNames[$#tableNames]=$row[0];
     }
     $sth->finish;
} elsif ($tableName) {
     $#tableNames=0;
     $tableNames[$#tableNames]=$tableName;
} else {
     die " Cannot request all tables without output to either idl or header";
}        

#
# ------ loop over all tableNames 
#   
for($jj=0;$jj<=$#tableNames;$jj++){
      $tableName=$tableNames[$jj];
      if($args{DEBUG}){print "Will request ", $tableName,"\n";}

 if($tableName){
   $ssrQuery= qq{ SELECT structure.Comment } .
              qq{ FROM structure WHERE structure.name='$tableName' };
   $sth=$dbh->prepare($ssrQuery);
   $sth->execute;

   if(!(($tableComment)=$sth->fetchrow_array)){      # it is new
      $mes=qq{\n This Table [$tableName] is not defined in Database [$dbname]};
      print $mes;
      $sth->finish;
   } else {    
      print " Will evaluate table = ", $tableName, "\n";
      if($args{DEBUG}){print "TableComment = ",$tableComment,"\n";}
      $sth->finish;
      evalSchema(MakeIDL=>$mkIdl, MakeHeader=>$mkH, OnlIDL=>$args{OnlIDL},DEBUG=>$args{DEBUG});
   }

 } # tablename check

} #loop over all tablenames

}
1;













