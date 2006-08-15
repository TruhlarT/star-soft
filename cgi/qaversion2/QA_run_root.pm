#! /opt/star/bin/perl -w

#==================================================================
package QA_run_root;
#==================================================================
1;
#==================================================================

sub run_root{

#-------------------------------------------------------------------
# runs root with arbitrary commands. Invoked like:
#
# $star_level = "new";
# $scratch = "/afs/rhic.bnl.gov/star/data1/jacobs/qa";
# @root_commands = ("gSystem->Getenv(\"STAR_LEVEL\")", 
#		  ".L read_bfc_hist_list.C",
#		  "Example_pmj()",
#		  ".q");
# run_root($starlib_version, $scratch, @root_commands);

#-------------------------------------------------------------------

  my $starlib_version = shift (@_);
  my $scratch = shift (@_);

  my @commands = @_;

  # create temporary csh script, use process pid ($$) to make unique name
  $script = $scratch."/"."temp".$$."\.csh";
  
  # make sure it disappears at the end...
#  END { unlink($script) };
  
  open (SCRIPT, "> $script") or die "Cannot open $script: $!\n";

  # write to script
  print SCRIPT "#! /usr/local/bin/tcsh -f\n",
  "setenv GROUP_DIR /afs/rhic.bnl.gov/rhstar/group\n",
  "setenv CERN_ROOT /cern/pro\n",
  "setenv HOME /star/u2e/starqa\n";

#---

# pmj 9/2/00: There is currently a problem setting any environment other than 
# dev in the batch jobs. The batch job env variables are not under good control,
# and it is not clear to me what is wrong. As an emergency measure, run all scripts 
# under dev, but this needs immediate attention.


# pmj 11/9/00: Yuri thinks that the PATH was too long in the setup, causing script to crahs. 
# Try again with new...

  if ($starlib_version eq "dev" ){
      print SCRIPT "source /afs/rhic.bnl.gov/rhstar/group/.stardev \n";
  }
  elsif ($starlib_version eq "new" ){
      print SCRIPT "source /afs/rhic.bnl.gov/rhstar/group/.starnew \n";
  }
  elsif ($starlib_version eq "pro" ){
      print SCRIPT "source /afs/rhic.bnl.gov/rhstar/group/.starpro \n";
  }
  else{
      print SCRIPT "source /afs/rhic.bnl.gov/rhstar/group/.starver ".$starlib_version."\n";
  }

#    print SCRIPT "source /afs/rhic.bnl.gov/rhstar/group/.stardev \n";

#----
  #
  # bum 04/16/02 - just use 'root4star'.  
  #
   print SCRIPT "root4star -b <<END\n";
#  print SCRIPT "/afs/rhic.bnl.gov/star/packages/dev/.i386_redhat61/bin/root4star -b<<END \n";
#>>& /tmp/starlib/biteme \n";

  foreach $command (@commands){
    print SCRIPT $command."\n";
  }

  print SCRIPT ".q\nEND\n";
  
  close SCRIPT;
  
  chmod 0755, $script;

  # pipe both STDOUT and STDERR (see PERL Cookbook 16.7)
  open ROOTLOG, "$script 2>&1 |"  or die "can't fork: $!";

  @root_log = ();
  while ($line = <ROOTLOG>){
    push @root_log, $line;
  }
  
  close ROOTLOG;

#  $root_log = `$script  2>&1`;

#  print "root_log = [$root_log]\n";
#  return split("\n",$root_log);
  return @root_log;
}
