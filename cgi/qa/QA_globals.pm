#! /usr/bin/perl

package QA_globals;


use Exporter ();
@ISA = qw(Exporter);

@EXPORT = qw(
	     @topdir_data $topdir_report $scratch
	     @topdir_data_WWW $topdir_report_WWW
	     $control_dir_WWW

	     $script_name

	     $batch_dir $batch_dir_WWW $update_dir $control_dir $cron_dir

	     $global_logfile $global_root_dst_file $global_root_hist_file $global_root_event_file
	     $global_dst_xdf_file $global_analysis_report_filename

	     $global_input_data_type $global_filename

	     $global_creation_time

	     %QA_object_hash @QA_key_list @selected_key_list $global_expert_page

	     $query $QA_object_hash_scratch_file
);

#=====================================================================================

@topdir_data = (
		"/star/rcf/disk00000/star/test/dev/",
		"/star/rcf/disk00000/star/test/new/"
	       );
@topdir_data_WWW = (
		    "http://duvall.star.bnl.gov/data/disk00000_star/test/dev/",
		    "http://duvall.star.bnl.gov/data/disk00000_star/test/new/",
	       );

$topdir_report = "/star/data1/jacobs/qa/reports";

$scratch = "/star/data1/jacobs/qa/scratch";

# for browser access, use soft links in /star/u2/jacobs/WWW

$topdir_WWW = "http://duvall.star.bnl.gov/~jacobs";
$topdir_report_WWW = "$topdir_WWW/report_dir";
$control_dir_WWW = "$topdir_WWW/control_dir";
$batch_dir_WWW = "$topdir_WWW/batch_dir";


$batch_dir = "/star/data1/jacobs/qa/batch";
$control_dir = "/star/data1/jacobs/qa/control_and_test";

$update_dir = "/star/data1/jacobs/qa/update";

$cron_dir = "/star/data1/jacobs/qa/batch/cronjob_logs";

#------------------------------------------------------------------------------------
1;
