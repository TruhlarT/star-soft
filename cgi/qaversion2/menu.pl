#!/usr/bin/perl

use DataClass_object;
use Server_object;
use QA_globals;
use QA_db_utilities qw(:db_globals);
use Db_KeyList_utilities;
use IO_object;
use Time::Local;
use Storable;

use strict 'vars';
#----------------------
# writes the menu options to disk as a perl storable
#----------------------

$gServer_object = new Server_object;

# data classes
my @classes = qw(offline_real offline_MC nightly_real nightly_MC debug);

for my $class (@classes){
  my $time = localtime();
  print "$time - $class : ";
  
  $gDataClass_object = new DataClass_object($class);
  QA_db_utilities::db_connect();

  my $start    = timelocal(localtime());
  my $menuRef  = &{$gDataClass_object->GetSelectionOptions};
  my $stop     = timelocal(localtime());
  print "time - ",$stop-$start," sec\n";
  
  my $storable = IO_object->new("MenuStorable")->Name();
  print "storing to $storable... ";
  store($menuRef,$storable) or print "CANNOT STORE\n";
  print "done\n";
  QA_db_utilities::db_disconnect();
}
exit 0;

