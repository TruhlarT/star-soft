#! /usr/bin/perl

# class for doing timing

# pmj 2/6/00

#========================================================
package Timer_object;
#========================================================
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

use Time::Local;

use strict;
#--------------------------------------------------------
1;
#========================================================
sub new{
  my $classname = shift;
  my $self = {};
  bless ($self, $classname);

  my ($package, $filename, $line) = caller;

  # initialize
  $self->_init($package, $filename, $line, @_);

  return $self;
}
#========================================================
sub _init{

  my $self = shift;

  my $package = shift; 
  my $filename = shift;
  my $line = shift;

  @_ and $self->{_label} = shift;

  $self->{_time_start} = 0;
  $self->{_time_last_call} = 0;

  $self->{_sys_time_start} = 0;
  $self->{_sys_time_last_call} = 0;
  $self->{_wall_clock_start} = time;
  $self->{_wall_clock_last_call} = time;
  $self->{_count_print_timing} = 0;
  
  my $label = $self->{_label};

  # don't print initializing string if called from QA_main: screws up frames
  $filename !~ /QA_main/ and
    print "$label: print_timing initialized from $package::$filename, line $line <br> \n";

}

#===========================================================
sub PrintTiming{

  my $self = shift;

  #-----------------------------------------------------------

  $self->{_count_print_timing}++;

  my ($package, $filename, $line) = caller;
  my $label = $self->{_label};
  
  my $count_print_timing = $self->{_count_print_timing};
  print "$label: timing call $count_print_timing: print_timing called from $package::$filename, line $line <br> \n";

  # get elapsed time
  my $wall_clock = time;

  # for batch jobs, initialization doesn't seem to work right- here's a quick fix
  # pmj 10/5/00

  my $do_printing = 1;
  $self->{_wall_clock_start} or do{
    $self->{_wall_clock_start} = time;
    $do_printing = 0;
  };

  $self->{_wall_clock_last_call} or do{
    $self->{_wall_clock_last_call} = time;
    $do_printing = 0;
  };

  # end of fix

  my $now;
  my $sys_now;

  $do_printing and do{

    # get cpu time
    $now = (times)[0];
    $$sys_now = (times)[1];
    
    printf "<font color=red>$label: user cpu time since start = %.3f sec; user cpu time since last call= %.3f sec </font><br>\n",
    $now-$self->{_time_start},$now-$self->{_time_last_call};
    
    printf "<font color=blue>$label: system cpu time since start = %.3f sec; system cpu time since last call= %.3f sec </font><br>\n",
    $sys_now-$self->{_sys_time_start},$sys_now-$self->{_sys_time_last_call};
    
    printf "<font color=green>$label: elapsed time since start = %d sec; elapsed time since last call= %d sec </font><br>\n",
    $wall_clock-$self->{_wall_clock_start},$wall_clock-$self->{_wall_clock_last_call};
    
  };
    
  $self->{_time_last_call} = $now;
  $self->{_sys_time_last_call} = $sys_now;
  $self->{_wall_clock_last_call} = $wall_clock;
}
