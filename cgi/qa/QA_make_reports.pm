#! /usr/bin/perl

# first try at a QA object
# pmj 29/7/99
#========================================================
package QA_make_reports;
#========================================================

use File::Basename;
use File::Find;
use File::stat;

use QA_globals;

#--------------------------------------------------------
1;
#================================================================================
sub get_report_key{

  my $dir_string = shift (@_);

  #----------------------------------------------------------------------
  # cosmics or simulation run?


  if ( $dir_string =~ /\/dst\// ){

    ($filename = $dir_string) =~ s?/star/rcf/test/dst/?cosmics\.?;
    $filename =~ s/\///g;
    $filename .= '.';

  }

  else{
    
    @names = split /\//, $dir_string;
    
    # protect against junk in directory string pmj 13/10/99
    $#names < 4 and return "unknown";
    
    # make flexible to handle hadronic cocktail files
    # pmj 2/11/99
    
    $i_count = -4;
    for ($i = -$#names; $i < 0 ; $i++ ){
      $names[$i] =~ /^(dotdev|dev|new|pro|old)$/ and do{
	$i_count = $i;
	last;
      };
    }
    
    $filename = "";
    for ($i = $i_count; $i < 0 ; $i++ ){
      $filename .= $names[$i].".";
    }
    
    # shorten name if hadronic cocktail
    
    $filename =~ s/density//;
    $filename =~ s/standard/std/;

  }
    
  # get creation time of logfile in directory
  find( \&QA_cgi_utilities::get_logfile, $dir_string);
    
  if ( -e $global_logfile ){

    $temp = stat($global_logfile)->mtime; 
    @time = localtime($temp);
    
    $day = $time[3];
    $month = $time[4] + 1;
    $year = $time[5];

    $year > 99 and $year = $year - 100;
    
    $day < 10 and $day = "0".$day;
    $month < 10 and $month = "0".$month;
    $year < 10 and $year = "0".$year;
    
    $filename .= $day.$month.$year;
    
    return $filename;
  }
  else{
    return "unknown";
  }
}

#===================================================================
sub check_file_made {

  my $report_key = shift;
  my $macro_name = shift;
  my $filename = shift;

  #-------------------------------------------------------------------
  # special check for doEvents

  $macro_name eq 'doEvents' and check_doEvents_output($filename);

  #-------------------------------------------------------------------

  -e  $filename and do {
    print "<h4> ...done </h4> \n";
    return;
  };

  #-------------------------------------------------------------------
  # Trouble: generate filename to dump root session into

  my $report_dir = $QA_object_hash{$report_key}->ReportDirectory;
#  my $time_string = QA_cgi_utilities::yymmddhhmmss;

  my $logfile = "$report_dir/$macro_name.rootcrashlog";

  open ROOTCRASH, ">$logfile" or die "Cannot open Root Crash Logfile $logfile: $! ";
  #-------------------------------------------------------------------
  print "<h4> File $filename not created. </h4> \n";
  print "<h4> Something went wrong. Here is root session: </h4> \n";

  print "<pre> \n";
  foreach $line (@_){
    print $line;
    print ROOTCRASH $line;
  }
  print "</pre> \n";
  #-------------------------------------------------------------------

  close ROOTCRASH;
}
#===========================================================================
sub make_report_directory{

  my $report_key = shift;
  my $report_dirname = $topdir_report."/".$report_key;

  -d $report_dirname or do{ 
    print "Making directory: $report_dirname <br> \n";
    mkdir $report_dirname, 0775;
  };

}
#=======================================================================
sub check_doEvents_output{
  $filename = shift;

  open FILE, $filename or die "check_doEvents_output: Cannot open file $filename: $! \n";
  @lines = <FILE>;
  close FILE;

  $crash = 0;

 CHECKCRASH: {
    while( $line = pop @lines ){
      last CHECKCRASH if $line =~ /Event\s+\d+\s+finish/;
    }
    $crash = 1;
  }

  # if finish string not found, delete file
  $crash and unlink $filename;
}
#=======================================================================
sub log_report_name{

  my $report_key = shift;
  my $report_dirname = report_directory($report_key);
  
  # if existing ascii file present, use that. Otherwise, generate "Storable" object pmj 13/11/99
  my $name = "logfile_report";

  if (-e $report_dirname."/$name\.obj"){
    $name .= "\.obj";
  }
  elsif (-e $report_dirname."/$name\.txt"){
    $name .= "\.txt";
  }
  else{
    $name .= "\.obj";
  }

  return "$report_dirname/$name";
}
#=======================================================================
sub report_directory{
  $report_key = shift;
  return $topdir_report."/".$report_key;
}
#=======================================================================
sub report_directory_www{
  $report_key = shift;
  return $topdir_report_WWW."/".$report_key;
}
