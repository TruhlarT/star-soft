#!/usr/bin/env perl
#
# AutoCalibDB.pm
#   Author: M. Elnimr (Wayne State Univ.)
#   Purpose: Interface to databases of
#     AutoCalib states used to determine
#     the FastOffline chain
#
# $Id: AutoCalibDB.pm,v 1.1 2009/01/27 17:57:33 genevb Exp $
#
# $Log: AutoCalibDB.pm,v $
# Revision 1.1  2009/01/27 17:57:33  genevb
# Introduction of AutoCalib codes
#
#
###########################################################

package AutoCalibDB;
use DBI;
require Exporter;
#use Date::Manip();

@ISA=qw(Exporter);

@EXPORT=qw(Connect_AutoCalibDB fetch_AutoCalibDB  fetch_DetChain_AutoCalibDB fetch_BaseChain_AutoCalibDB fetch_validityTime_BaseChain_AutoCalibDB fetch_test_AutoCalibDB fetch_FullChain fetch_available_states insert_AutoCalibDB insert_BaseChain_AutoCalibDB insert_DetChain_AutoCalibDB cleanInt_DB cleanStrict_DB cleanStrictChar_DB);



$TARGET  = "/star/u/melnimr/";       


$SUBMIT="JobSubmit.pl";
$servername="duvall.star.bnl.gov";
$DB="AutoCalib";
$DDBPORT=3306;





sub Connect_AutoCalibDB
{
    my ($servername,$port,$DB)=@_;
    $db_handler=DBI->connect("DBI:mysql:$DB:$servername","root","",{RaiseError=>1,AutoCommit=>1}) || die "Couldn't connect to the database ". DBI->errstr;
    return $db_handler;
}


sub fetch_AutoCalibDB
{
    my ($column1,$NOW)=@_;
    my $Cond2="entryTime";
    my $Cond="entryTime<$NOW";
    my $dbtable="state";
    
    my $db_handler=Connect_AutoCalibDB($servername,$DDBPORT,$DB);
    #my $sql=qq(SELECT $column1  FROM $dbtable WHERE $Cond ORDER BY beginTime DESC LIMIT 1 );
    #print "$sql\n";
   
    my $sth=$db_handler->prepare("SELECT $column1  FROM $dbtable"." WHERE $Cond ORDER BY $Cond2 DESC LIMIT 1");
    $sth->execute();

    $row=$sth->fetchrow_array;
    $sth->finish();
    return $row;

}


sub fetch_DetChain_AutoCalibDB
{
    my ($Cond,$dbtable)=@_;
    my $Cond2="beginTime,entryTime";
    my $column1="chain";

    my $db_handler=Connect_AutoCalibDB($servername,$DDBPORT,$DB);
    #my $sql=qq(SELECT $column1  FROM $dbtable WHERE $Cond ORDER BY beginTime DESC LIMIT 1 );
    #print "$sql\n";
   
    my $sth=$db_handler->prepare("SELECT $column1  FROM $dbtable"." WHERE $Cond ORDER BY $Cond2 DESC LIMIT 1");
    $sth->execute();

    $row=$sth->fetchrow_array;
    $sth->finish();
    return $row;

}


sub fetch_FullChain
{
    my $coll_=@_;
    
    $NOW="NOW()";
    $coll_="'".$coll_."'";
    $CHAIN=fetch_BaseChain_AutoCalibDB($coll_,$NOW).",";
    $qaState=fetch_AutoCalibDB("QA",$NOW);
    $CHAIN=$CHAIN.fetch_DetChain_AutoCalibDB("qaState='$qaState'","qaChain").",";
    $tpcState=fetch_AutoCalibDB("TPC",$NOW);
    $CHAIN=$CHAIN.fetch_DetChain_AutoCalibDB("tpcState='$tpcState'","tpcChain").",";
    $emcState=fetch_AutoCalibDB("EMC",$NOW);
    $CHAIN=$CHAIN.fetch_DetChain_AutoCalibDB("emcState='$emcState'","emcChain");
    return $CHAIN;
}



sub fetch_BaseChain_AutoCalibDB
{
    my $column1="chain";
    my $Cond2="entryTime";
    my $dbtable="baseChain";
    my ($CollisionType,$validityTime)=@_;
    
		
    
    my $Cond="collision=$CollisionType AND beginTime<$validityTime";
    my $db_handler=Connect_AutoCalibDB($servername,$DDBPORT,$DB);
    #my $sql=qq(SELECT $column1  FROM $dbtable WHERE $Cond ORDER BY beginTime DESC LIMIT 1 );
    #print "$sql\n";
   
    my $sth=$db_handler->prepare("SELECT $column1  FROM $dbtable"." WHERE $Cond ORDER BY $Cond2 DESC LIMIT 1");
    $sth->execute();

    $row=$sth->fetchrow_array;
    $sth->finish();
    return $row;

}

sub fetch_validityTime_BaseChain_AutoCalibDB
{
    my $column1="beginTime";
    my $Cond2="entryTime";
    my $dbtable="baseChain";
    my ($CollisionType,$validityTime)=@_;
    
    
    
    my $Cond="collision=$CollisionType AND beginTime<$validityTime";
    my $db_handler=Connect_AutoCalibDB($servername,$DDBPORT,$DB);
    #my $sql=qq(SELECT $column1  FROM $dbtable WHERE $Cond ORDER BY beginTime DESC LIMIT 1 );
    #print "$sql\n";
    
    my $sth=$db_handler->prepare("SELECT $column1  FROM $dbtable"." WHERE $Cond ORDER BY $Cond2 DESC LIMIT 1");
    $sth->execute();
    
    $row=$sth->fetchrow_array;
    $sth->finish();
    return $row;
    
}


sub fetch_available_states
{
	my ($State,$Chain)=@_;
	my $db_handler=Connect_AutoCalibDB($servername,$DDBPORT,$DB);
	my $sth=$db_handler->prepare("select $State from $Chain group by $State order by $State");
	$sth->execute();
	my @AvailStatesTMP;
	my @AvailStates;
	for($count=0;@AvailStates=$sth->fetchrow_array();$count++)
	{
		
		@AvailStatesTMP[$count]=@AvailStates[0];
		
	}
	
	return @AvailStatesTMP;
	
}


sub insert_AutoCalibDB
{
   
    my $db_handler=Connect_AutoCalibDB($servername,$DDBPORT,$DB);		
    my ($col1,$col2,$col3,$dbtable)=@_;
    my $sth=$db_handler->prepare("INSERT INTO $dbtable VALUES(NOW(),$col1,$col2,$col3)");
    if(!$sth->execute()){ print "failed to insert....\n";}
    else {print "<br>success.... $dbtable was inserted...\n";}
    
}

sub insert_BaseChain_AutoCalibDB
{
   my $dbtable="baseChain";
    my $db_handler=Connect_AutoCalibDB($servername,$DDBPORT,$DB);		
    my ($col1,$col2,$col3)=@_;
    my $sth=$db_handler->prepare("INSERT INTO $dbtable VALUES(NOW(),$col1,$col2,$col3)");
    if(!$sth->execute()){ print "failed to insert....\n";}
    else {print "<br>success....$dbtable was inserted\n";}
    
}
sub insert_DetChain_AutoCalibDB
{
   
    my $db_handler=Connect_AutoCalibDB($servername,$DDBPORT,$DB);		
    my ($col1,$col2,$col3,$dbtable)=@_;
    my $sth=$db_handler->prepare("INSERT INTO $dbtable VALUES(NOW(),$col1,$col2,$col3)");
    if(!$sth->execute()){ return 0;}
    else { return 1;}
    
}

sub fetch_test_AutoCalibDB
{
    my($db_handler,$dbtable)=@_;
    my $sth=$db_handler->prepare("SELECT * FROM $dbtable ORDER BY entryTime DESC LIMIT 1");
    $sth->execute();
    
    @row=$sth->fetchrow_array;
    $sth->finish();

    return @row;


}


sub cleanStrict_DB
{
    my @temp=@_;
    #print "-------$temp[0]\n";
    if($temp[0] =~ m/'\d{4}(-\d\d){2} \d\d(:\d\d){2}'/)
    {
	return 1;
    }
    return 0;
}

sub cleanStrictChar_DB
{
    my @temp=@_;
    #print "++++++++$temp[0]\n";
    if($temp[0] =~ m/'\w{1,}'/)
    
    {
	return 1;
    }
    return 0;
}

sub cleanInt_DB
{
    my @temp=@_;
    #if($temp[0] =~ m/^1/ || $temp[0] =~ m/^0/)
    if($temp[0] =~ m/[0-9]/ )
    {
	
	return 1;
    }
    return 0;
}



