#! /usr/bin/perl 
#
# collection of swap reports
#
# pmj 31/7/00
#
#=========================================================
package Report_collection;
#=========================================================
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

use Cwd;

use File::stat;
use File::Path;

use File::Copy;
use File::Find;
use File::Basename;

use Data::Dumper;

use strict;

#=========================================================
1.;
#=========================================================

sub new{
  my $classname = shift;
  my $self = {};
  bless ($self, $classname);

  # initialize
  $self->_init(@_);

  return $self;
}
#========================================================
sub _init{

  my $self = shift;
  my $name = shift;
  my $report_dir = shift;

  $self->CollectionName($name);
  $self->ReportDir($report_dir);

  #---------------------------------------------------------------------------

  opendir DIR, $report_dir or die "Cannot open directory $report_dir<br>\n";

  my $file;

  while (defined ($file = readdir(DIR) ) ){
    
    $file =~ /\.txt$/ or next;

    my $full_file = "$report_dir/$file";

    my $report = new Report_object($full_file);
    $self->Add($report);
  
  }

  closedir(DIR);

}
#========================================================
sub CollectionName{
  my $self = shift;
  @_ and $self->{CollectionName} = shift;
  return $self->{CollectionName};
}
#========================================================
sub ReportDir{
  my $self = shift;
  @_ and $self->{ReportDir} = shift;
  return $self->{ReportDir};
}
#========================================================
sub Add{
  my $self = shift;

  #------------------------------------------------------

  # adds report to collection
  @_ and do{
    my $report = shift;
    push @{ $self->{Reports} }, $report;

    # give process a pointer to this chain object
    $report->Collection($self);

  };

  return;
}
#========================================================
sub Display{

  my $self = shift;
#---------------------------------------------------------------------------
  $self->PrintIntro();
#---------------------------------------------------------------------------
  $self->PrintIndex();
#---------------------------------------------------------------------------
  my @reports = @{ $self->{Reports} };

  foreach my $report ( @reports){
    $report->Display();
  }
#---------------------------------------------------------------------------
  $self->PrintContacts();
#---------------------------------------------------------------------------
}

#==========================================================================
sub PrintIntro{

  my $self = shift;

  print<<EOF;
<p>This page is intended to provide a central location for results related
to the understanding of common issues underlying STAR Data Analysis. There
is a large and growing variety of work being done on STAR data by many
people (not just the SWAT Team) and it has become impossible even for the
full-time experts to keep track of all the important discussions. We will
attempt to keep this page current with the various discussion streams,
providing a summary for non-experts, along with links to a limited number
of important plots. More detail can be found in the email archives, principally
starsoft-l.
<p>First try at mechanism to maintain this page: if you have a contribution,
please email it to one of&nbsp; <a href="#Contacts">us</a> and we will
edit and insert the text.<br>
EOF

}
#==========================================================================
sub PrintContacts{

  my $self = shift;
 
  print "<hr>";
 
  print<<EOF;
<br><a NAME="Contacts"></a>Contacts: <i>
<a href="mailto:pmjacobs\@lbl.gov, ullrich\@star.physics.yale.edu,margetis\@faisun.kent.edu">
pmjacobs\@lbl.gov,ullrich\@star.physics.yale.edu,margetis\@faisun.kent.edu</a></i>
EOF

}
#==========================================================================
sub PrintIndex{

  my $self = shift;

  print "<hr>";
 
  print h3("Index");

#---------------------------------------------------------------------------

  print "<ol>";

  my @reports = @{ $self->{Reports} };

  foreach my $report ( @reports){
    my $title = $report->Title();
    my $tag = $report->Tag();

    print "<li><a href=\"\#$tag\">$title</a>";
  }

  print "</ol>\n";
}

