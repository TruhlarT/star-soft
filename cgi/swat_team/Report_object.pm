#! /usr/bin/perl 
#
# general object to wrap swat report
#
# pmj 31/7/00
#
#=========================================================
package Report_object;
#=========================================================
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

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

  my $report_name = shift;  
  my @args = @_;

  #-------------------------------------------------

  $self->ReportName($report_name);
  $self->ReportArgs(@args);

  my $last_mod = (stat($report_name))[9];
  $self->LastModified($last_mod);

  #-------------------------------------------------
  # get random tag

  my $tag = int( rand(10000) ) + 1;
  $self->Tag($tag);

  #-------------------------------------------------

  $self->ParseReport();

}
#========================================================
sub Collection{
  my $self = shift;
  @_ and $self->{Collection} = shift;
  return $self->{Collection};
}
#========================================================
sub ReportName{
  my $self = shift;
  @_ and $self->{ReportName} = shift;
  return $self->{ReportName};
}
#========================================================
sub LastModified{
  my $self = shift;
  @_ and $self->{LastModified} = shift;
  return $self->{LastModified};
}
#========================================================
sub ReportArgs{
  my $self = shift;
  @_ and $self->{ReportArgs} = shift;
  return $self->{ReportArgs};
}
#========================================================
sub Tag{
  my $self = shift;
  @_ and $self->{Tag} = shift;
  return $self->{Tag};
}
#========================================================
sub Title{
  my $self = shift;
  @_ and $self->{Title} = shift;
  return $self->{Title};
}
#========================================================
sub Author{
  my $self = shift;
  @_ and $self->{Author} = shift;
  return $self->{Author};
}
#========================================================
sub Issue{
  my $self = shift;
  @_ and $self->{Issue} = shift;
  return $self->{Issue};
}
#========================================================
sub Physics{
  my $self = shift;
  @_ and $self->{Physics} = shift;
  return $self->{Physics};
}
#========================================================
sub Status{
  my $self = shift;
  @_ and $self->{Status} = shift;
  return $self->{Status};
}
#========================================================
sub Links{
  my $self = shift;
  @_ and $self->{Links} = shift;
  return $self->{Links};
}
#========================================================
sub Display{
  my $self = shift;

  print "<hr>";

  my $title = $self->Title();
  my $tag = $self->Tag();

  print h3("<a name=$tag>$title</a>");

  print "<strong>Authors:</strong>", $self->Author(),"<br>\n";
  
  my $last_mod = $self->LastModified();
  my $last_mod_time = localtime($last_mod);
  print "Last modified: $last_mod_time<br>\n";

  print "<br><strong>Issue:</strong>", $self->Issue(),"<br>\n";

  print "<br><strong>Physics:</strong>", $self->Physics(),"<br>\n";

  print "<br><strong>Status:</strong>", $self->Status(),"<br>\n";

  print "<br><strong>Links:</strong>", $self->Links(),"<br>\n";
}
#========================================================
sub ParseReport{
  my $self = shift;

  my $file = $self->ReportName();

  #---------------------------------------------------------

  open FILE, $file or die "Cannot open file $file<br>\n";

  my $string;

  while ( my $line = <FILE> ) {

    $line =~ /^\#/ and next;
    $line =~ /^$/ and do{
      $self->ParseString($string);
      $string = "";
      next;
    };

    $string .= $line;
    
  }

  close FILE;
}
#========================================================
sub ParseString{
  my $self = shift;
  my $string = shift;

  #-------------------------------------------------------
  # clean up string
  $string =~ s/\s/ /g;
  #-------------------------------------------------------
  my $message;

  ($message = $string) =~ s/<title>|<author>|<issue>|<physics>|<status>|<links>//;

  if ( $string =~ /<title>/ ){
    $self->Title($message);
  }
  elsif ( $string =~ /<author>/ ){
    $self->Author($message);
  }
  elsif ( $string =~ /<issue>/ ){
    $self->Issue($message);
  }
  elsif ( $string =~ /<physics>/ ){
    $self->Physics($message);
  }
  elsif ( $string =~ /<status>/ ){
    $self->Status($message);
  }
  elsif ( $string =~ /<links>/ ){
    $self->Links($message);
  }
}
