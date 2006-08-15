#!/usr/local/bin/perl -I/usr/lib/perl5/5.00503 -I/usr/lib/perl5/site_perl/5.005 -I/usr/lib/perl5/site_perl/5.005/i386-linux/ -I/afs/rhic.bnl.gov/star/starqa/qa01/libRCAS/lib/site_perl 

use DataClass_object;
use Server_object;
use QA_globals;
use QA_db_utilities qw(:db_globals);
use Db_KeyList_utilities;
use KeyList_object_offline;
use IO_object;
use KeyList_object_nightly;
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
  my $menuRef = $gDataClass_object->KeyList_obj->new()->GetSelectionOptionsFromDb();
  my $stop     = timelocal(localtime());
  print "time - ",$stop-$start," sec\n";
  
  my $storable = IO_object->new("MenuStorable")->Name();
  print "storing to $storable... ";
  eval {store($menuRef,$storable)};
  if ($@){
    print "CANNOT STORE : $@\n";
  } else {
    print "done\n";
  }
  QA_db_utilities::db_disconnect();
}
exit 0;

