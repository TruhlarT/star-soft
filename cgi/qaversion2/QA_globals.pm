#! /usr/bin/perl

package QA_globals;

use Exporter ();
@ISA = qw(Exporter);

@EXPORT = qw(

	     $gCGIquery 
	     $gBrowser_object 
	     $gServer_object
	     
	     $gDataClass_object
	     $data_class_default 

	     $gTimer_object

	     %QA_message_hash
	     %QA_object_hash 
	     %Button_object_hash
);

#================default topdir =============================================
#$data_class_default = "offline_MC" ;
$data_class_default = "nightly_MC" ;
#$data_class_default = "debug" ;
#----------------------------------------------------------------------------
1;
#=========================================================================
# pmj 2/6/00 taken out of global namespace
#	     $data_class
#	     $topdir            
#	     $topdir_report    
#	     $topdir_report_WWW
#	     $topdir_report_old
#	     $batch_dir_WWW     
#	     $batch_dir         
#	     $control_dir_WWW   
#	     $control_dir      
#	     $update_dir        
#	     $cron_dir          
#	     $scratch           
#	     $backup_dir        
#	     $compare_dir       
#	     $message_dir
#	     $deleted_message_dir 
#	     $Logreport_obj 
#	     $KeyList_obj
#	     $home 
#	     $Save_object_hash_scratch_file
#	     @QA_key_list 
#	     @selected_key_list 
#	     $new_QA_object $new_Button_object $new_Message
#	     $offline_selection_file $nightly_selection_file
#	     $time_start $time_last_call $sys_time_start $sys_time_last_call
#	     $wall_clock_start $wall_clock_last_call $count_print_timing

# $dbFile 
# $FileCatalog 
# $JobStatus 
# $ProdOptions
# $JobRelations
# $dbQA
# $QASummaryTable 
# $QAMacrosTable

#$serverHost = 'duvall.star.bnl.gov';
#============= database globals =============================================
#$dbName = 'test_ops';

#==============================================================================
# removed pmj 1/6/00
#$offline_selection_file = "$scratch_offline/offline_selection.obj";
#$nightly_selection_file = "$scratch_nightly/nightly_selection.obj";
#==============================================================================
