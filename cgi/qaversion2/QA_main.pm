#! /opt/star/bin/perl

# pmj & bjc 1/6/00
#=========================================================
#use CGI qw/:standard :html3 -no_debug/;
use CGI qw/:standard :html3/;
use CGI::Carp qw(fatalsToBrowser);

use QA_utilities;
use Browser_object;
use Server_object;

use Timer_object;

use QA_globals;
use QA_db_utilities;
use QA_object;

use DataClass_object;

use Db_update_utilities;

use strict;
#=========================================================

# BEN(6jun2000): CGI.pm gets confused if we instantiate a CGI object
# in batch mode because the batch script inherits the environment
# (PATH_INFO, etc) of
# the parent GUI-based instance of QA_main.  The batch-mode QA_main
# tries to instantiate the parent's persistant hash, which causes
# problems.  
#
# We indicate that the script is running as a batch job if the first
# command line argument is "batch_job"; see DoBatch for details on
# other args.

if ($ARGV[0] eq "batch_job"){
    DoBatch();
    exit;
}

$gCGIquery = new CGI; # query is a global
print $gCGIquery->header;

#-----------------------------------------------------------
my $path_info  = $gCGIquery->path_info;
my $first_call = $path_info ? 0 : 1;  
my $title      = 'STAR Software QA';

# If no path information is provided, then create frame set
# N.B. Do not print anything to screen prior to this statement, or frames 
# will not get set up!
  
$first_call and do {
    PrintFrameset($title); 
    exit 0;
};

#---------------------------------------------------------
# initialize timer for global timing
$gTimer_object = new Timer_object("Global");
#---------------------------------------------------------
# global
$gServer_object = new Server_object;
my $server_type = $gServer_object->ServerType;
#---------------------------------------------------------
# set data class
my $offline_default = "nightly_MC";
my $online_default  = "online_raw";

my $data_class;
if ( $server_type eq 'offline' ){
  $data_class = $gCGIquery->param('data_class') || $offline_default;
}
elsif( $server_type eq 'online' ){
  $data_class = $gCGIquery->param('data_class') || $online_default;
}
else{
  $data_class = "unknown";
}

# global
# this class sets all the variables which depend on the data class
$gDataClass_object = new DataClass_object($data_class);

#print Dumper $gDataClass_object;
#---------------------------------------------------------

# connect to db
# need to call this after the server object

QA_db_utilities::db_connect();

# browser object is a global
$gBrowser_object = new Browser_object($title, $server_type);

$gBrowser_object->StartHtml();

#useful for debugging:
#print "path_info = $path_info, script_name = $script_name<br>\n";
#foreach my $string( @INC){print "string = $string <br>\n";}

$gBrowser_object->UpperDisplay() if $path_info =~ /upper_display/;
$gBrowser_object->LowerDisplay() if $path_info =~ /lower_display/;

$gBrowser_object->Hidden->Store(); # store objects

# disconnect from db
QA_db_utilities::db_disconnect();

#print $gCGIquery->dump;

$gBrowser_object->EndHtml();

#==========================================================================
sub PrintFrameset{

  my $script_name = $gCGIquery->script_name;
  
  print title($title), frameset( {-rows=>'60%,40%'}, 
	frame( {-name=>'list',    -src=>"$script_name/upper_display"} ),
	frame( {-name=>'display', -src=>"$script_name/lower_display"} ));
}

#=========================================================
# BEN (3jun2000): merging in QA_main_batch functionality
# The interface to QA_main in batch mode is defined as follows:
# QA_main.pm batch_job <data class> <action> [report key]
#
# batch_job indicates a batch job is being run
# action is one of 'update', 'do_qa', 'redo_qa', 'update_and_qa'
# data_class should be the class of data, as defined in DataClass_object.pm
# report_key, if given, specifies a single report key for doing qa

sub DoBatch
{
    # read params
    my $data_class = $ARGV[1];
print("data_class='$data_class'\n");
    my $action = $ARGV[2];
print("action='$action'\n");
    my $report_key = $ARGV[3];
print("report_key='$report_key'\n");


    # initialize timer for global timing
print("creating gTimer_object....\n");
    $gTimer_object = new Timer_object("Global");
print("....done creating gTimer_object\n");

    # sets the global directories as well
print("creating gServer_object....\n");
    $gServer_object = new Server_object;
    my $server_type = $gServer_object->ServerType;
print("....done creating gServer_object\n");

    # set global data class - BEN
    $gDataClass_object = new DataClass_object($data_class);

    # connect to db
    # need to call this after the server & dataclass objects
print("connecting to db....\n");
    QA_db_utilities::db_connect();
print("....done connecting to db\n");



    # update everything in the data class
    ($action eq 'update' or $action eq 'update_and_qa') and do{
print("update-ing....\n");
        QA_utilities::doUpdate();
print("....done update-ing\n");
    };
    
    # do qa on jobs in the database
    ($action eq 'do_qa' or $action eq 'redo_qa' or $action eq 'update_and_qa')  and do{
print("do_qa-ing....\n");
	# do qa on all new jobs if none specified
	my @key_list;
	if (!$report_key){
	    # BUM 000625 - getting to do keys depends on the dataclass 
	    no strict 'refs';
	    my $sub = $gDataClass_object->ToDoKeys;
	    @key_list = &$sub;
	    use strict 'refs';
	} else {
	    @key_list = ($report_key);
	}

	my $key;
	foreach $key (@key_list){
	    # make sure they're on disk
	    my $qa = $gDataClass_object->QA_obj->new($key);
	    next if ($qa->QADone and $action ne 'redo_qa');
	    next unless $qa->OnDisk;
	    $qa->DoQA('no_tables');
	}
print("....done do_qa-ing\n");
    };

    # disconnect from db
    QA_db_utilities::db_disconnect();
    
}






