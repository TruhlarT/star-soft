#! /usr/bin/perl

package QA_globals;


use Exporter ();
@ISA = qw(Exporter);

@EXPORT = qw(
	     @topdir_data @topdir_data_WWW

	     $topdir  $topdir_report $topdir_report_old    
	     $topdir_report_WWW  $control_dir_WWW  $batch_dir_WWW
	     $batch_dir  $control_dir $update_dir $cron_dir 
	     $compare_dir $backup_dir $scratch  
	     
	     $topdir_default $home @topdir_array
	    
	     $topdir_dev            
	     $topdir_report_dev    
	     $batch_dir_dev         
	     $control_dir_dev      
	     $update_dir_dev        
	     $cron_dir_dev          
	     $scratch_dev           
	     $topdir_report_WWW_dev 
	     $control_dir_WWW_dev   
	     $batch_dir_WWW_dev     
	     $backup_dir_dev        
	     $compare_dir_dev       

	     $topdir_new          
	     $topdir_report_new   
	     $batch_dir_new       
	     $control_dir_new     
	     $update_dir_new      
	     $cron_dir_new        
	     $scratch_new         
	     $topdir_report_WWW_new 
	     $control_dir_WWW_new   
	     $batch_dir_WWW_new     
	     $backup_dir_new       
	     $compare_dir_new      
	     
	     $topdir_debug         
	     $topdir_report_debug  
	     $batch_dir_debug      
	     $control_dir_debug    
	     $update_dir_debug     
	     $cron_dir_debug       
	     $scratch_debug        
	     $topdir_report_WWW_debug
	     $control_dir_WWW_debug  
	     $batch_dir_WWW_debug    
	     $compare_dir_debug      

     	     $topdir_cosmics
             $topdir_report_cosmics
             $batch_dir_cosmics
             $control_dir_cosmics
             $update_dir_cosmics
             $cron_dir_cosmics
             $scratch_cosmics
             $topdir_report_WWW_cosmics
             $control_dir_WWW_cosmics
             $batch_dir_WWW_cosmics
             $compare_dir_cosmics
	    

	     $message_dir $deleted_message_dir %QA_message_hash

	     $script_name

	     $global_logfile $global_root_dst_file $global_root_hist_file 
	     $global_root_event_file
	     $global_dst_xdf_file $global_analysis_report_filename
	     $global_input_data_type $global_filename
	     $global_creation_time

	     %QA_object_hash 
	     %Button_object_hash
	     $Save_object_hash_scratch_file
	     @QA_key_list @selected_key_list $global_expert_page

	     $query

	     $time_start $time_last_call $sys_time_start $sys_time_last_call
	     $wall_clock_start $wall_clock_last_call $count_print_timing
	     $new_QA_object $new_Button_object $new_Message
);
#============================================================================

@topdir_data = (
		"/star/rcf/test/dev/",
		"/star/rcf/test/new/",
		"/star/rcf/test/dst/"
	       );

@topdir_data_WWW = (
		    "http://duvall.star.bnl.gov/data/test/dev/",
		    "http://duvall.star.bnl.gov/data/test/new/",
		    "http://duvall.star.bnl.gov/data/test/dst/"
	       );

#================for browser access, use soft links==========================
$topdir_WWW = "http://duvall.star.bnl.gov/~starqa/qa";

#================disk location  =============================================
$home = "/star/data1/starqa";
#================default topdir =============================================
$topdir_default = "$home/dev" ;
#================old reports ================================================
$topdir_report_old = "$home/reports_old";
#===========messages=========================================================
$message_dir = "$home/messages";
$deleted_message_dir = "$message_dir/deleted_messages";
%QA_message_hash = undef;

#note: dev, new, cosmics share the same control, batch, update dirs
#=====================dev===================================================
$topdir_dev            = "$home/dev";
$topdir_report_dev     = "$topdir_dev/reports";
$batch_dir_dev         = "$home/batch";
$control_dir_dev       = "$home/control_and_test";
$update_dir_dev        = "$home/update";
$backup_dir_dev        = "$topdir_dev/backups";
$cron_dir_dev          = "$batch_dir_dev/cronjob_logs";
$scratch_dev           = "$topdir_dev/scratch";
$topdir_report_WWW_dev = "$topdir_WWW/report_dir_dev";
$control_dir_WWW_dev   = "$topdir_WWW/control_dir";
$batch_dir_WWW_dev     = "$topdir_WWW/batch_dir";
$compare_dir_dev       = "$topdir_dev/compare_runs";

#=====================new===================================================
$topdir_new            = "$home/new";
$topdir_report_new     = "$topdir_new/reports";
$batch_dir_new         = "$home/batch";
$control_dir_new       = "$home/control_and_test";
$update_dir_new        = "$home/update";
$backup_dir_new        = "$topdir_new/backups";
$cron_dir_new          = "$batch_dir_new/cronjob_logs";
$scratch_new           = "$topdir_new/scratch";
$topdir_report_WWW_new = "$topdir_WWW/report_dir_new";
$control_dir_WWW_new   = "$topdir_WWW/control_dir";
$batch_dir_WWW_new     = "$topdir_WWW/batch_dir";
$compare_dir_new       = "$topdir_new/compare_runs";

#=====================test===================================================
$topdir_test            = "$home/test";
$topdir_report_test     = "$topdir_test/reports";
$batch_dir_test         = "$topdir_test/batch";
$control_dir_test       = "$topdir_test/control_and_test";
$update_dir_test        = "$topdir_test/update";
$backup_dir_test        = "$topdir_test/backups";
$cron_dir_test          = "$batch_dir_test/cronjob_logs";
$scratch_test           = "$topdir_test/scratch";
$topdir_report_WWW_test = "$topdir_WWW/report_dir_test";
$control_dir_WWW_test   = "$topdir_WWW/control_dir_test";
$batch_dir_WWW_test     = "$topdir_WWW/batch_dir_test";
$compare_dir_test       = "$topdir_test/compare_runs";

#====================debug===================================================
$topdir_debug            = "$home/debug";
$topdir_report_debug     = "$topdir_debug/reports";
$batch_dir_debug         = "$topdir_debug/batch";
$control_dir_debug       = "$topdir_debug/control_and_test";
$update_dir_debug        = "$topdir_debug/update";
$backup_dir_debug        = "$topdir_debug/backups";
$cron_dir_debug          = "$batch_dir_debug/cronjob_logs";
$scratch_debug           = "$topdir_debug/scratch";
$topdir_report_WWW_debug = "$topdir_WWW/report_dir_debug";
$control_dir_WWW_debug   = "$topdir_WWW/control_dir_debug";
$batch_dir_WWW_debug     = "$topdir_WWW/batch_dir_debug";
$compare_dir_debug       = "$topdir_debug/compare_runs";

#====================cosmics===================================================
$topdir_cosmics            = "$home/cosmics";
$topdir_report_cosmics     = "$topdir_cosmics/reports";
$batch_dir_cosmics         = "$home/batch";
$control_dir_cosmics       = "$home/control_and_test";
$update_dir_cosmics        = "$home/update";
$backup_dir_cosmics        = "$topdir_cosmics/backups";
$cron_dir_cosmics          = "$batch_dir_cosmics/cronjob_logs";
$scratch_cosmics           = "$topdir_cosmics/scratch";
$topdir_report_WWW_cosmics = "$topdir_WWW/report_dir_cosmics";
$control_dir_WWW_cosmics   = "$topdir_WWW/control_dir";
$batch_dir_WWW_cosmics     = "$topdir_WWW/batch_dir";
$compare_dir_cosmics       = "$topdir_cosmics/compare_runs";

#============================================================================
$topdir                = undef;
$topdir_report         = undef;
$scratch               = undef;
$topdir_report_WWW     = undef;
$control_dir_WWW       = undef;
$batch_dir_WWW         = undef;
$batch_dir             = undef;
$control_dir           = undef;
$update_dir            = undef;
$cron_dir              = undef;
$backup_dir            = undef;
$compare_dir           = undef;

#=====================used for update_and_qa ================================
# these are the directories we want to update_and_qa in QA_main_batch.pm

@topdir_array = ($topdir_dev, $topdir_new, $topdir_cosmics);

#============= database globals =============================================
$dbName = 'test_ops';
$serverHost = 'duvall.star.bnl.gov';

#----------------------------------------------------------------------------
1;
