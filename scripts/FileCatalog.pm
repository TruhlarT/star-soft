# FileCatalog.pm
#
# Written by Adam Kisiel, November-December 2001
# Written and/or Modified by J.Lauret, 2002
#
# Methods of class FileCatalog:
#
#        ->new             : create new object FileCatalog
#        ->connect         : connect to the database FilaCatalog
#        ->destroy         : destroy object and disconnect database FileCatalog
#        ->set_context()   : set one of the context keywords to the given
#                            operator and value
#        ->get_context()   : get a context value connected to a given keyword
#        ->clear_context() : clear/reset the context
#        ->get_keyword_list() : get the list of valid keywords
#        ->get_delimeter() : get the current delimiting string
#        ->set_delimeter() : set the current delimiting string
#
# the following methods require connect to dbtable and are meant to be used
# outside the module
#
#        -> check_ID_for_params() : returns the database row ID from the
#                          dictionary table connected to this keyword
#
#        -> insert_dictionary_value() : inserts the value from the context
#                          into the dictionary table
#        -> get_current_detector_configuration() : gets the ID of a detector
#                          configuration described by the current context
#        -> insert_run_param_info() : insert the run param record taking data
#                          from the current context
#        -> get_current_run_param() : get the ID of a run params corresponding
#                          to the current context
#        -> insert_file_data() : inserts file data record taking data from
#                          the current context
#        -> get_current_file_data() : gets the ID of a file data corresponding
#                          to the current context
#        -> insert_simulation_params() : insert the simulation parameters
#                          taking data from the current context
#        -> get_current_simulation_params : gets the ID of a simulation params
#                          corresponding to the current contex
#        -> insert_file_location() : insert the file location data taking
#                          data from the current context
#
#        -> get_file_location()
#                          returns the FileLocations info in an array context.
#                          The return value can be used as-is in a
#                          set_context() statement.
#        -> get_file_data()
#                          returns the FileData info in an array context.
#                          The return value can be used as-is in a
#                          set_context() statement.
#        -> clone_location()
#                          actually create an instance for FileData and a
#                          copy of FileLocations the latest to be modified
#                          with set_context() keywords.
#
#
#        -> run_query()   : get entries from dbtable FileCatalog according to
#                          query string defined by set_context you also give a
#                          list of fields to select form
#
#        -> delete_records() : deletes the current file locations based on
#                          context. If it finds that the current file data has
#                          no file locations left, it deletes it too
#        -> update_record() : modifies the data in the database. The field
#                          corresponding to the given keyword changes it
#                          value from the one in the current context to the
#                          one specified as an argument
#
#        -> bootstrap() : database maintenance procedure. Looks at the dictionary table
#                          and find all the records that are not referenced by the child
#                          table. It offers an option of deleting this records.
#
#        -> set_delayed()  turn database operation in delay mode. A stack is built
#                          and execute later. This may be used in case of several
#                          non-correlated updates. Warning : no checks made on delayed
#                          commands.
#        -> flush_delayed() flush out i.e. execute all delayed commands.
#        -> print_delayed() print out on screen all delayed commands.
#
#
# NOT YET DOCUMENTED
#
#        ->add_trigger_composition()
#


package  FileCatalog;
require  5.000;


require  Exporter;
@ISA   = qw(Exporter);
@EXPORT= qw( connect destroy
	     set_context get_context clear_context
	     get_keyword_list
	     set_delimeter get_delimeter
	     set_delayed flush_delayed print_delayed
	     add_trigger_composition

	     run_query
	     close_location
	     delete_records update_location update_record

	     check_ID_for_params insert_dictionary_value

	     debug_on debug_off
	     );

#@EXPORT_OK = qw(%operset %valuset);


use vars qw($VERSION);
$VERSION   =   1.25;

# The hashes that hold a current context
my %operset;
my %valuset;


use DBI;
#use Digest::MD5;
use strict;
no strict "refs";

# define to print debug information
my $NCTRY     =  6;
my $NCSLP     = 10;
my $DEBUG     =  0;
my $DELAY     =  0;
my $SILENT    =  0;
my @DCMD;

# db information
my $dbname    =   "FileCatalog_BNL";
my $dbhost    =   "duvall.star.bnl.gov";
my $dbport    =   "";
my $dbuser    =   "FC_user";
my $dbpass    =   "FCatalog";
my $DBH;
my $sth;

# hash of keywords
my %keywrds;
my %ksimilar;

# hash of obsolete keywords
my %obsolete;


# Arrays to treat triggers
$FC::IDX     = -1;
@FC::TRGNAME = undef;
@FC::TRGWORD = undef;
@FC::TRGVERS = undef;
@FC::TRGDEFS = undef;
@FC::TRGCNTS = undef;


# $keys{keyword} meaning of the parts of the field:
# k - parameter name as entered by the user
# 0 - field name in the database
# 1 - table name in the database for the given field
# 2 - critical for data insertion into the specified table
# 3 - type of the field (text,num,date)
# 4 - if 0, is not returned by the FileTableContent() routine (used in cloning)
# 5 - if 1, displays as a user usable keywords, skip otherwise.
#     This field cannot be a null string.
# only the keywords in this table are accepted in set_context sub

# Those are for private use only but require a keyword for access.
# DO NOT DOCUMENT THEM !!!
$keywrds{"flid"          }    =   "fileLocationID"            .",FileLocations"          .",0" .",num"  .",0" .",0" .",0";
$keywrds{"fdid"          }    =   "fileDataID"                .",FileData"               .",0" .",num"  .",0" .",0" .",0";
$keywrds{"rfdid"         }    =   "fileDataID"                .",FileLocations"          .",0" .",num"  .",0" .",1" .",0";
$keywrds{"pcid"          }    =   "productionConditionID"     .",ProductionConditions"   .",0" .",num"  .",0" .",0" .",0";
$keywrds{"rpcid"         }    =   "productionConditionID"     .",FileData"               .",0" .",num"  .",0" .",1" .",0";
$keywrds{"rpid"          }    =   "runParamID"                .",RunParams"              .",0" .",num"  .",0" .",0" .",0";
$keywrds{"rrpid"         }    =   "runParamID"                .",FileData"               .",0" .",num"  .",0" .",1" .",0";
$keywrds{"trgid"         }    =   "triggerSetupID"            .",TriggerSetups"          .",0" .",num"  .",0" .",0" .",0";
$keywrds{"rtrgid"        }    =   "triggerSetupID"            .",Runparams"              .",0" .",num"  .",0" .",1" .",0";
$keywrds{"ftid"          }    =   "fileTypeID"                .",FileTypes"              .",0" .",num"  .",0" .",0" .",0";
$keywrds{"rftid"         }    =   "fileTypeID"                .",FileData"               .",0" .",num"  .",0" .",1" .",0";
$keywrds{"stid"          }    =   "storageTypeID"             .",StorageTypes"           .",0" .",num"  .",0" .",0" .",0";
$keywrds{"rstid"         }    =   "storageTypeID"             .",FileLocations"          .",0" .",num"  .",0" .",0" .",0";
$keywrds{"ssid"          }    =   "storageSiteID"             .",StorageSites"           .",0" .",num"  .",0" .",0" .",0";
$keywrds{"rssid"         }    =   "storageSiteID"             .",FileLocations"          .",0" .",num"  .",0" .",1" .",0";

# *** Those should be documented
$keywrds{"filetype"      }    =   "fileTypeName"              .",FileTypes"              .",1" .",text" .",0" .",1" .",1";
$keywrds{"extension"     }    =   "fileTypeExtension"         .",FileTypes"              .",1" .",text" .",0" .",1" .",1";
$keywrds{"storage"       }    =   "storageTypeName"           .",StorageTypes"           .",1" .",text" .",0" .",1" .",1";
$keywrds{"site"          }    =   "storageSiteName"           .",StorageSites"           .",1" .",text" .",0" .",1" .",1";
$keywrds{"siteloc"       }    =   "storageSiteLocation"       .",StorageSites"           .",1" .",text" .",0" .",1" .",1";
$keywrds{"sitecmt"       }    =   "storageComment"            .",StorageSites"           .",1" .",text" .",0" .",1" .",1";
$keywrds{"production"    }    =   "productionTag"             .",ProductionConditions"   .",1" .",text" .",0" .",1" .",1";
$keywrds{"prodcomment"   }    =   "productionComments"        .",ProductionConditions"   .",0" .",text" .",0" .",1" .",1";
$keywrds{"library"       }    =   "libraryVersion"            .",ProductionConditions"   .",1" .",text" .",0" .",1" .",1";


# Trigger related keywords. Reshaped and cleaned on Dec 1st 2002
$obsolete{"triggersetup"}= "trgsetupname";
$obsolete{"triggername"} = "trgsetupname";  # not a 1 to 1 mapping but this is what we initially meant
$obsolete{"triggerword"} = "trgword";

$keywrds{"trgsetupname"  }    =   "triggerSetupName"          .",TriggerSetups"          .",1" .",text" .",0" .",1" .",1";

# The count of individual triggers, the FileData index access in TriggerCompositions and
# the trigger word ID in the TriggerComposition table
$keywrds{"tcfdid"        }    =   "fileDataID"                .",TriggerCompositions"    .",0" .",num"  .",0" .",0" .",0";
$keywrds{"tctwid"        }    =   "triggerWordID"             .",TriggerCompositions"    .",0" .",text" .",0" .",1" .",0";
$keywrds{"trgcount"      }    =   "triggerCount"              .",TriggerCompositions"    .",0" .",text" .",0" .",1" .",1";

$keywrds{"twid"          }    =   "triggerWordID"             .",TriggerWords"           .",0" .",text" .",0" .",1" .",0";
$keywrds{"trgname"       }    =   "triggerName"               .",TriggerWords"           .",0" .",text" .",0" .",1" .",1";
$keywrds{"trgversion"    }    =   "triggerVersion"            .",TriggerWords"           .",0" .",text" .",0" .",1" .",1";
$keywrds{"trgword"       }    =   "triggerWord"               .",TriggerWords"           .",0" .",text" .",0" .",1" .",1";
$keywrds{"trgdefinition" }    =   "triggerDefinition"         .",TriggerWords"           .",0" .",text" .",0" .",1" .",1";


# This keyword is a special keyword which will be used to enter
# a list of triggers/count in the database. It is an agregate
# keyword only used in INSERT mode.
#$keywrds{"triggerevents" }    =   ",,,,,,0";
$obsolete{"triggerevents" }    = "method add_trigger_composition()";




$keywrds{"runtype"       }    =   "runTypeName"               .",RunTypes"               .",1" .",text" .",0" .",1" .",1";
$keywrds{"configuration" }    =   "detectorConfigurationName" .",DetectorConfigurations" .",1" .",text" .",0" .",1" .",1";
$keywrds{"geometry"      }    =   "detectorConfigurationName" .",DetectorConfigurations" .",0" .",text" .",0" .",1" .",1";
$keywrds{"runnumber"     }    =   "runNumber"                 .",RunParams"              .",1" .",num"  .",0" .",1" .",1";
$keywrds{"runcomments"   }    =   "runComments"               .",RunParams"              .",0" .",text" .",0" .",1" .",1";
$keywrds{"collision"     }    =   "collisionEnergy"           .",CollisionTypes"         .",1" .",text" .",0" .",1" .",1";
$keywrds{"datetaken"     }    =   "dataTakingStart"           .",RunParams"              .",0" .",date" .",0" .",1" .",1";
$keywrds{"magscale"      }    =   "magFieldScale"             .",RunParams"              .",1" .",text" .",0" .",1" .",1";
$keywrds{"magvalue"      }    =   "magFieldValue"             .",RunParams"              .",0" .",num"  .",0" .",1" .",1";
$keywrds{"filename"      }    =   "filename"                  .",FileData"               .",1" .",text" .",0" .",1" .",1";
$keywrds{"fileseq"       }    =   "fileSeq"                   .",FileData"               .",1" .",num"  .",0" .",1" .",1";
$keywrds{"stream"        }    =   "fileStream"                .",FileData"               .",1" .",num"  .",0" .",1" .",1";
$keywrds{"filecomment"   }    =   "fileDataComments"          .",FileData"               .",0" .",text" .",0" .",1" .",1";
$keywrds{"events"        }    =   "numEntries"                .",FileData"               .",1" .",num"  .",0" .",1" .",1";
$keywrds{"md5sum"        }    =   "md5sum"                    .",FileData"               .",1" .",text" .",0" .",1" .",1";
$keywrds{"size"          }    =   "fsize"                     .",FileLocations"          .",1" .",num"  .",0" .",1" .",1";
$keywrds{"owner"         }    =   "owner"                     .",FileLocations"          .",0" .",text" .",0" .",1" .",1";
$keywrds{"protection"    }    =   "protection"                .",FileLocations"          .",0" .",text" .",0" .",1" .",1";
$keywrds{"node"          }    =   "nodeName"                  .",FileLocations"          .",0" .",text" .",0" .",1" .",1";
$keywrds{"available"     }    =   "availability"              .",FileLocations"          .",0" .",num"  .",0" .",1" .",1";
$keywrds{"persistent"    }    =   "persistent"                .",FileLocations"          .",0" .",num"  .",0" .",1" .",1";
$keywrds{"sanity"        }    =   "sanity"                    .",FileLocations"          .",0" .",num"  .",0" .",1" .",1";
$keywrds{"createtime"    }    =   "createTime"                .",FileLocations"          .",0" .",date" .",0" .",1" .",1";
$keywrds{"inserttime"    }    =   "insertTime"                .",FileLocations"          .",0" .",date" .",0" .",1" .",1";
$keywrds{"path"          }    =   "filePath"                  .",FileLocations"          .",1" .",text" .",0" .",1" .",1";
$keywrds{"simcomment"    }    =   "simulationParamComments"   .",SimulationParams"       .",0" .",text" .",0" .",1" .",1";
$keywrds{"generator"     }    =   "eventGeneratorName"        .",EventGenerators"        .",1" .",text" .",0" .",1" .",1";
$keywrds{"genversion"    }    =   "eventGeneratorVersion"     .",EventGenerators"        .",1" .",text" .",0" .",1" .",1";
$keywrds{"gencomment"    }    =   "eventGeneratorComment"     .",EventGenerators"        .",0" .",text" .",0" .",1" .",1";
$keywrds{"genparams"     }    =   "eventGeneratorParams"      .",EventGenerators"        .",1" .",text" .",0" .",1" .",1";

# The detector configuration can be extended as needed
# > alter table DetectorConfigurations ADD dEEMC TINYINT AFTER dEMC;
# > update DetectorConfigurations SET dEEMC=0;
#
# + definition here and insert_detector_configuration()
# and we are Ready to go for a new column
#
$keywrds{"tpc"           }    =   "dTPC"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"svt"           }    =   "dSVT"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"tof"           }    =   "dTOF"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"emc"           }    =   "dEMC"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"eemc"          }    =   "dEEMC"                     .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"fpd"           }    =   "dFPD"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"ftpc"          }    =   "dFTPC"                     .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"pmd"           }    =   "dPMD"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"rich"          }    =   "dRICH"                     .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"ssd"           }    =   "dSSD"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";
$keywrds{"bbc"           }    =   "dBBC"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1" .",1";

# Special keywords
$keywrds{"simulation"    }    =   ",,,,,,1";
$keywrds{"nounique"      }    =   ",,,,,,1";
$keywrds{"noround"       }    =   ",,,,,,1";
$keywrds{"startrecord"   }    =   ",,,,,,1";
$keywrds{"limit"         }    =   ",,,,,,1";
$keywrds{"all"           }    =   ",,,,,,1";

# Keyword aliasing or keyword aggregate
$keywrds{"lgnm"          }    =   ",,,,,,1";
$keywrds{"lgpth"         }    =   ",,,,,,1";
$keywrds{"fulld"         }    =   ",,,,,,1";  # pseudo-full information agregate for real data
$keywrds{"fulls"         }    =   ",,,,,,1";  # pseudo-full information agregate for simulation data
#$keywrds{"md5n"          }    =   ",,,,,,1";
#$keywrds{"md5p"          }    =   ",,,,,,1";

$ksimilar{"lgnm"         }    =   "logical_name;production library runnumber runtype filename trgsetupname configuration";
$ksimilar{"lgpth"        }    =   "logical_path;site node storage path";
$ksimilar{"fulld"        }    =   ";production library runnumber runtype site node storage path filename events trgsetupname";
$ksimilar{"fulls"        }    =   ";production library runnumber runtype site node storage path filename events configuration generator genversion genparams";
#$ksimilar{"md5n"         }    =   "md5_name;production library trgsetupname runnumber filename";
#$ksimilar{"md5p"         }    =   "md5_path;site node storage path";


# Fields that need to be rounded when selecting from the database
my $roundfields = "magFieldValue,2 collisionEnergy,0";

# The delimeter to sperate fields at output
my $delimeter = "::";


# The list of connections between tables in the database
# needed to build queries with joins
# fields:
# 1 - Table being linked to
# 2 - Table that links the given table
# 3 - Name of the linking field in both tables
# 4 - "Level" of the table in the DB structure
#     The table is at level 1, if it not directly referenced by any other table
#     The table is at level 2 if it is directly referenced by a table at level 1
#     etc.
# 5 - 1 if table is a dictionary table, 0 otherwise
#
# FileLocations is considered as being at level 1
#
# CollisionTypes is NOT a dictionary because the usable returned value
# is subject to a merging combo of several field with truncation. This
# is a collection' table.
#

my @datastruct;
$datastruct[0]  = ( "StorageTypes"           . ",FileLocations"       . ",storageTypeID"           . ",2" . ",1");
$datastruct[1]  = ( "StorageSites"           . ",FileLocations"       . ",storageSiteID"           . ",2" . ",1");
$datastruct[2]  = ( "FileData"               . ",FileLocations"       . ",fileDataID"              . ",2" . ",0");
$datastruct[3]  = ( "ProductionConditions"   . ",FileData"            . ",productionConditionID"   . ",3" . ",1");
$datastruct[4]  = ( "FileTypes"              . ",FileData"            . ",fileTypeID"              . ",3" . ",1");
$datastruct[5]  = ( "TriggerWords"           . ",TriggerCompositions" . ",triggerWordID"           . ",2" . ",1");
$datastruct[6]  = ( "FileData"               . ",TriggerCompositions" . ",fileDataID"              . ",2" . ",1");
$datastruct[7]  = ( "RunParams"              . ",FileData"            . ",runParamID"              . ",3" . ",0");
$datastruct[13] = ( "EventGenerators"        . ",SimulationParams"    . ",eventGeneratorID"        . ",5" . ",1");
$datastruct[8]  = ( "RunTypes"               . ",RunParams"           . ",runTypeID"               . ",4" . ",1");
$datastruct[9]  = ( "DetectorConfigurations" . ",RunParams"           . ",detectorConfigurationID" . ",4" . ",0");
$datastruct[10] = ( "CollisionTypes"         . ",RunParams"           . ",collisionTypeID"         . ",4" . ",0");
$datastruct[11] = ( "TriggerSetups"          . ",RunParams"           . ",triggerSetupID"          . ",4" . ",1");
$datastruct[12] = ( "SimulationParams"       . ",RunParams"           . ",simulationParamsID"      . ",4" . ",0");
$datastruct[14] = ( "FileLocations"          . ","                    . ","                        . ",1" . ",0");
$datastruct[15] = ( "TriggerCompositions"    . ","                    . ","                        . ",1" . ",0");

#%FC::FLRELATED;
#%FC::FDRELATED;
#%FC::ISDICT;


# The operators allowed in set_context query - two-characters operators first
my @operators;
$operators[0] = "<=";
$operators[1] = ">=";
$operators[2] = "<>";
$operators[3] = "!=";
$operators[4] = "==";
$operators[5] = "!~";
$operators[6] = "=";
$operators[7] = ">";
$operators[8] = "<";
$operators[9] = "~";

# The possible aggregate values
my @aggregates;
$aggregates[0] = "sum";
$aggregates[0] = "count";
$aggregates[1] = "avg";
$aggregates[2] = "min";
$aggregates[3] = "max";
$aggregates[4] = "grp";
$aggregates[5] = "orda";
$aggregates[6] = "ordd";

# A table holding the number of records in each table
#my %rowcounts;
#$rowcounts{"StorageTypes"} = 0;
#$rowcounts{"StorageSites"} = 0;
#$rowcounts{"FileData"} = 0;
#$rowcounts{"ProductionConditions"} = 0;
#$rowcounts{"FileTypes"} = 0;
#$rowcounts{"TriggerWords"} = 0;
#$rowcounts{"FileData"} = 0;
#$rowcounts{"RunParams"} = 0;
#$rowcounts{"RunTypes"} = 0;
#$rowcounts{"DetectorConfigurations"} = 0;
#$rowcounts{"CollisionTypes"} = 0;
#$rowcounts{"TriggerSetups"} = 0;
#$rowcounts{"SimulationParams"} = 0;
#$rowcounts{"EventGenerators"} = 0;
#$rowcounts{"FileLocations"} = 0;
#$rowcounts{"TriggerCompositions"} = 0;


# Those variables will be used internally
my @FDKWD;
my @FLKWD;

#============================================
# parse keywrds - get the field name for the given keyword
# Parameters:
# keyword to get the field name for
# Returns:
# field name for a given context keyword
sub get_field_name {
  my @params = @_;

  my ($fieldname, $tabname, $rest) = split(",",$keywrds{$params[0]});
  return $fieldname;
}

#============================================
# parse keywrds - get the table name for the given keyword
# Parameters:
# keyword to get the table name for
# Returns:
# table name for a given context keyword
sub get_table_name {
  my ($mykey) = (@_);
  my ($tabname, $a, $b);

  if( ! defined($mykey) ){ return;}

  if (exists $keywrds{$mykey}){
      ($a,$tabname,$b) = split(",",$keywrds{$mykey});
  } else {
      &die_message("get_table_name","Internal error ; Using non-existent key $mykey");
  }
  return $tabname;

}

#============================================
# get the list of valid keywords
# Returns:
# the list of valid keywords to use in FileCatalog queries
sub get_keyword_list {
    my($val,$kwd);
    my(@items,@kwds);

    foreach $val (sort { $a cmp $b } keys %keywrds){
	@items = split(",",$keywrds{$val});
	if ($items[6] == 1){ push(@kwds,$val);}
	else { &print_debug("Rejecting $items[0]"); }
    }
  return @kwds;
}

#============================================
# change the deleimiting string between output fields
# Parameters:
# new deliemiting string
sub set_delimeter {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  }
  my @params = @_;

  $delimeter = $params[0];
}

#============================================
# get the current delimiting string
# Returns:
# current delimiting string
sub get_delimeter {
  return $delimeter;
}

#============================================
# parse keywrds - get the field type
# Parameters:
# keyword to get the type for
# Returns:
# type of the field for a given keyword
sub get_field_type {
  my @params = @_;

  my ($fieldname, $tabname, $req, $type, $rest) = split(",",$keywrds{$params[0]});
  return $type;
}

#============================================
# parse keywrds - see if the field is required in insert statement
# Parameters:
# keyword to check
# Returns:
#  0 if field is not needed
#  1 if field is mandatory for inserts
sub is_critical {
  my @params = @_;

  my ($fieldname, $tabname, $req, $type, $rest) = split(",",$keywrds{$params[0]});
  # nolimt, all etc ... will lead to empty string, not numeric
  if($req eq ""){  $req = 0;}
  return $req;
}


#sub is_dictionary
#{
#    my();
#}

#============================================
sub new {

  my $proto = shift;
  my $class = ref($proto) || $proto;
  my $self  = {};

  bless ($self , $class);
  $self->_initialize();

  return $self;
}

sub _initialize
{
    my ($self) = shift;

    # Only way to bless it is to declare them inside
    # new(). See also use Symbol; and usage of my $bla = gensym;
    $valuset{"all"} = 0;
    $delimeter = "::";

    #print "self is $self \n";


    #foreach my $el (sort keys %FileCatalog::){
    #	print "$el has for value $FileCatalog::{$el}\n";
    #}

    # Fill this associative arrays automatically
    my (@items);
    foreach (@datastruct){
	@items = split(",",$_);
	if    ( $items[1] eq "FileLocations"){  $FC::FLRELATED{$items[0]} = $items[2];} # save relat table
	elsif ( $items[1] eq "FileData"){       $FC::FDRELATED{$items[0]} = $items[2];} # save relat table
	if ( $items[4] eq "1"){                 $FC::ISDICT{$items[0]}    = $items[3]; # save level
						# BTW : we can only get this printed by outside-hack var() setup
						&print_debug("Dictionary $items[0] $FC::ISDICT{$items[0]}");
					    }
    }

}

#
# Read configuration file if any
# This routine is internal.
#
sub _ReadConfig
{
    my($intent)=@_;
    my($config,$line,$ok,$scope);
    my(%EL);                        # ($host,$db,$port,$user,$passwd);
    $config = "";

    foreach $scope ( (".",
		      $ENV{HOME},
		      $ENV{SCATALOG},
		      $ENV{STAR}."StDb/servers",
		      ) ){
	if ( -e $scope."/Catalog.xml" ){ 
	    $config = $scope."/Catalog.xml";
	    last;
	}
    }


    if ($config ne ""){
	&print_message("ReadConfig","Searching for $intent in $config");
	open(FI,$config);

	#
	# This is low-key XML parsing. Already a better parsing
	# would be to regexp =~ s/blablafound// to allow one
	# line. Better even to use XML::Parser but this module
	# is meant to be as indenpendant as possible from extraneous
	# perl layers. We skip entireley the header ...
	#
	while( defined($line = <FI>) ){
	    chomp($line); 
	    if ($line =~ /\<SCATALOG.*\>/i){           $ok = 1;}
	    if ($line =~ /\<\/SCATALOG\>/i){           $ok = 0;}
	    if ($line =~ /(\<SERVER)(.*\>)/i && $ok ){
		$scope = $2;
		if ($scope =~ m/$intent/){            
		    $ok |= 0x2;
		}
	    }

	    if ($line =~ /\<\/SERVER\>/i){            
		if (! ($ok && 0x2) ){
		    &print_message("ReadConfig","Parsing error. Check syntax");
		} else {
		    $ok &= 0x1; # i.e. remove bit 2
		}
	    }

	    if ($ok && 0x2){
		# Parsing of the block of interrest
		# Host specific information. Note that we do not
		# assemble things as a tree so, one value possible
		# so far ... and the latest/
		if ($line =~ /\<HOST/i){
		    &print_debug("XML :: $line");
		    if ( $line=~ m/(NAME=)(.*)(DBNAME=)(.* )(.*)/){
			$EL{HOST} = $2;
			$EL{DB}   = $4;
			$EL{PORT} = $5;
			if ($EL{PORT} =~ m/(PORT=)(.*)/){
			    $EL{PORT} = $2;
			}
		    }
		}
		if ( $line =~ m/\<ACCESS/){
		    if ( $line =~ m/(USER=)(.*)(PASS=)(.*)/ ){
			$EL{USER} = $2;
			$EL{PASS} = $4;
		    }
		}
	    }
	}
	close(FI);
	foreach $ok (keys %EL){
	    $EL{$ok} =~ s/[\"\/\>]//g;
	    $EL{$ok} =~ s/^(.*?)\s*$/$1/;
	    &print_debug("XML :: Got $ok [$EL{$ok}]\n");
	    if ($EL{$ok} eq ""){ $EL{$ok} = undef;}
	}
    }
    return ($EL{HOST},$EL{DB},$EL{PORT},$EL{USER},$EL{PASS});
}



#=================================================
# This routine has been added later and interfaces
# with the XML description.
sub connect_as
{
    my($self)= shift;
    my($intent)= @_;
    my($host,$db,$port,$user,$passwd);

    # We will read a configuration file in XML if
    # any
    ($host,$db,$port,$user,$passwd) = &_ReadConfig($intent);
    return &connect("FileCatalog",$user,$passwd,$port,$host,$db);
}


sub connect {
  my $self  = shift;
  my ($user,$passwd,$port,$host,$db) = @_;
  my ($sth,$count);
  my ($tries);
  my ($dbref);

  if( ! defined($user) )   { $user   = $dbuser;}
  if( ! defined($passwd) ) { $passwd = $dbpass;}
  if( ! defined($port) )   { $port   = $dbport;}
  if( ! defined($host) )   { $host   = $dbhost;}
  if( ! defined($db) )     { $db     = $dbname;}

  # Build connect
  $dbref  =   "DBI:mysql:$db:$host";
  if ( $port ne ""){ $dbref .= ":$port";}

  # Make it more permissive. Simultaneous connections
  # may make this fail.
  $tries = 0;
 CONNECT_TRY:
  $tries++;

  $DBH = DBI->connect($dbref,$user,$passwd,
		      { PrintError => 0,
			RaiseError => 0, AutoCommit => 1 }
		      );
  if (! $DBH ){ 
      &die_message("connect","Incorrect password") if ($DBI::err == 1045);
      if ( $tries < $NCTRY ){
	  &print_message("connect","Connection failed $DBI::errstr . Retry in $NCSLP secondes");
	  sleep($NCSLP);
	  goto CONNECT_TRY;
      } else {
	  &die_message("connect","cannot connect to $dbname : $DBI::errstr");
      }
  }



  # Set/Unset global variables here
  $FC::IDX = -1;


  #foreach (keys(%rowcounts)){
  #    my $sqlquery = "SELECT count(*) FROM $_";
  #    &print_debug("Executing: $sqlquery");
  #    $sth = $DBH->prepare($sqlquery);
  #
  #    if( ! $sth){
  # 	&print_debug("FileCatalog:: connect : Failed to prepare [$sqlquery]");
  #
  #    } else {
  #	$sth->execute();
  #	$sth->bind_columns( \$count );
  #
  #	if ( $sth->fetch() ) {
  #	  $rowcounts{$_} = $count;
  #	}
  #	$sth->finish();
  #    }
  #}

  if ( ! defined($DBH) ) {
      return 0;
  } else {
      return 1;
  }
}

#============================================
# disentangle keyowrd, operator and value from a context string
# Params:
# the context string
# Returns:
# keyword - the keyword used
# operator - the operator used
# value - the value assigned to the keyword
sub disentangle_param {

  if ($_[0] =~ m/FileCatalog/) {
      shift @_;
  };

  my ($params) = @_;
  my $keyword;
  my $operator;
  my $value;

 OPS: foreach (@operators )
    {
	if ($params =~ m/(.*)($_)(.*)/){
	    ($keyword, $operator, $value) = ($1,$2,$3);
	    last if (defined $keyword and defined $value);
	    $operator = "";
	}
    }

  if ($DEBUG > 0 && defined($keyword) ) {
      &print_debug(" Keyword: |".$keyword."|",
		   " Value: |".$value."|");
  }
  return ($keyword, $operator, $value);
}

#============================================
# Set the context variable
# Params:
# context string in the form of:
# <context variable> <operator> <value>
sub set_context {

  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  };

  my $params;
  my $keyw;
  my $oper;
  my $valu;

  foreach $params (@_){
      #  print ("Setting context for: $params \n");
      ($keyw, $oper, $valu) = &disentangle_param($params);

      if ( ! defined($keyw) ){
	  &print_message("set_context","Sorry, but I don't understand ".
		       "[$params] in your query.");
	  &die_message("set_context","May be a missing operator ?");
      }

      #&print_debug("$keyw $oper $valu");

      # Chop spaces from the key name and value;
      $keyw =~ y/ //d;
      if ($valu =~ m/.*[\"\'].*[\"\'].*/) {
	  $valu =~ s/.*[\"\'](.*)[\"\'].*/$1/;
      } else {
	  $valu =~ s/ //g;
      }

      if ( exists $keywrds{$keyw}) {
	  if ($DEBUG > 0) {
	      &print_debug("Query accepted $DEBUG: ".$keyw."=".$valu);
	  }
	  $operset{$keyw} = $oper;
	  $valuset{$keyw} = $valu;
      } else {
	  if ( defined($obsolete{$keyw}) ){
	      &die_message("set_context",
			   "[$keyw] is obsolete. Use $obsolete{$keyw} instead\n");
	  } else {
	      my (@kwd);
	      @kwd = &get_keyword_list();
	      &die_message("set_context",
			   "[$keyw] IS NOT a valid keyword. Choose one of\n".
			   join(" ",@kwd));
	  }
      }
  }
}

#============================================
# Clears the context deleting all the values
# form the context hashes
sub clear_context {
  foreach my $key (keys %valuset) {
    delete $valuset{$key};
  }
  foreach my $key (keys %operset) {
    delete $operset{$key};
  }
}

#============================================
# Get an ID for a record with a given name
# from a dictionary table
# NOTE: Field values in dictionary tables are CaSe insensitive
# Params:
# table name
# field name
# field value
# Returns:
# ID of record form a database or 0 if there is no such record
sub get_id_from_dictionary {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  }
  if( ! defined($DBH)){
      &print_message("get_id_from_dictionary","Not connected/connecting");
      return 0;
  }

  my @params = @_;
  my $idname = $params[0];
  my $sth;
  my $id;
  my $sqlquery;

  $idname = &IDize($idname);
  $id     = 0;

  $sqlquery = "SELECT $idname FROM $params[0] WHERE UPPER($params[1]) = UPPER(\"$params[2]\")";
  if ($DEBUG > 0) {  &print_debug("Executing: $sqlquery");}
  $sth = $DBH->prepare($sqlquery);

  if( ! $sth){
      &print_debug("FileCatalog:: get_id_from_dictionary : Failed to prepare [$sqlquery]");
  } else {
      my( $val );

      if ( $sth->execute() ){
	  $sth->bind_columns( \$val );

	  if ( $sth->fetch() ) {
	      $sth->finish();
	      $id = $val;
	  }
      }
  }
  return $id;
}

# Used several places so, made a utility routine
sub IDize
{
    my($idname)=@_;
    chop($idname);
    $idname = lcfirst($idname);
    $idname.="ID";
    $idname;
}

#============================================
# Check if there is a record with a given value
# in a corresponding dictionary table
# Parameters:
# the keyword to check for
# Returns:
# The ID value for a given keyword value
# or 0 if no such record exists
sub check_ID_for_params
{

    if ($_[0] =~ m/FileCatalog/) {  shift @_;}

    my @params = @_;
    my $retid;

    if (defined $valuset{$params[0]}) {
	my $fieldname;
	my $tabname;
	my $rest;

	($fieldname, $tabname, $rest) = split(",",$keywrds{$params[0]});
	$retid = &get_id_from_dictionary($tabname, $fieldname, $valuset{$params[0]});
	if ($retid == 0) {
	    # *** THIS NEEDS TO BE LATER FIXED
	    if ( $FC::ISDICT{$tabname} ) {
		&print_debug("Since $tabname is a dict, we will auto-insert");
		$retid = &insert_dictionary_value($params[0]);

	    } else {
		&print_debug("Returning 0 since there are no $params[0] with value ".
			     $valuset{$params[0]});
		$retid = 0;
	    }

	}
    } else {
	#&print_debug("check_ID_for_params::ERROR: No $params[0] defined");
	&print_message("check_ID","$params[0] is required but no value defined");
	$retid = 0;
    }
    &print_debug("Returning from check_ID_params: $retid");

    return $retid;
}

#============================================
# inserts a value into a table corresponding to a given keyword
# Paramters:
# A keyword to use
# Returns:
# The ID of an inserted value
# or 0 if such insertion was not possible
sub insert_dictionary_value {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  }
  if( ! defined($DBH) ){
      &print_message("insert_dictionary_value","Not connected");
      return 0;
  }

  my ($keyname) = @_;
  my @additional;
  if (! defined $valuset{$keyname}) {
    if ($DEBUG > 0) {
	&print_debug("ERROR: No value for keyword $keyname.",
		     "Cannot add record to dictionary table.");
    }
    return 0;
  }

  # Check if there are other fields from this table set
  foreach my $kwrd (keys(%keywrds)) {
    my ($fieldnameo, $tabnameo, $resto) = split(",",$keywrds{$keyname});
    my ($fieldnamet, $tabnamet, $restt) = split(",",$keywrds{$kwrd});

    if ($tabnameo eq $tabnamet && $keyname ne $kwrd) {
      if ($DEBUG > 0) {
	  &print_debug("The field $fieldnamet $tabnamet is from the same table as $fieldnameo $tabnameo");
      }
      if (defined $valuset{$kwrd}) {
	  push @additional, ($kwrd);
      }
    }
  }

  my ($fieldname, $tabname, $rest) = split(",",$keywrds{$keyname});
  my $dtfields = "";
  my $dtvalues = "";
  my $dtinsert;

  foreach my $kwrd (@additional) {
    my ($fieldnamea, $tabnamea, $resta) = split(",",$keywrds{$kwrd});

    # Skip special Count-er keyword
    if ($fieldnamea !~ /Count/){
	$dtfields .= " , $fieldnamea";
	$dtvalues .= " , '".$valuset{$kwrd}."'";
    }
  }

  if ( $tabname eq "FileLocations"){
      $dtinsert   = "INSERT DELAYED IGNORE INTO $tabname ";
  } else {
      $dtinsert   = "INSERT IGNORE INTO $tabname ";
  }
  $dtinsert  .= "($fieldname $dtfields)";
  $dtinsert  .= " VALUES ('".$valuset{$keyname}."' $dtvalues)";
  if ($DEBUG > 0) {    &print_debug("Execute $dtinsert");}


  my $sth;
  my $retid=0;

  $sth = $DBH->prepare( $dtinsert );
  if( ! $sth ){
      &print_debug("FileCatalog::insert_dictionary_value : Failed to prepare [$dtinsert]");
  } else {
      if ( $sth->execute() ) {
	  $retid = &get_last_id();
	  if ($DEBUG > 0) { &print_debug("Returning: $retid");}
	  $sth->finish();
      }
  }
  return $retid;
}


#============================================
# get the ID for the current run number
# Returns:
#   the ID of a runParams record,
#   or 0 if no such record exists
sub get_current_detector_configuration {

  my ($detConfiguration,$cmd,$sth,$val);
  my ($tabname)="DetectorConfigurations";
  my ($field)="detectorConfigurationName";
  my ($index)=&IDize($tabname);

  if( ! $DBH){
      &print_message("insert_detector_configuration","Not connected");
      return 0;
  }

  # May be one or the other
  if ( defined($valuset{"geometry"}) ){
      $val = $valuset{"geometry"};
  } else {
      $val = $valuset{"configuration"};
  }

  # This routine introduces caching
  if ( ($detConfiguration = &cached_value($tabname,$val)) == 0){
      $cmd = "SELECT $tabname.$index from $tabname WHERE $tabname.$field='$val'";

      $sth = $DBH->prepare($cmd);
      if( ! $sth ){
	  &die_message("get_current_detector_configuration",
		       "Cannot prepare ddb sentence");
      } else {
	  if ( $sth->execute() ){
	      $sth->bind_columns( \$val );

	      if ( $sth->fetch() ) {
		  $detConfiguration = $val;
	      }
	  }
	  $sth->finish();
      }


      if ($detConfiguration == 0) {
	  # There is no detector configuration with this name
	  # we have to add it
	  $detConfiguration = &insert_detector_configuration();
      }
  }
  return $detConfiguration;
}


# inserts a value into a table of Detector Configurations
# Returns:
#   The ID of an inserted value
#   or 0 if such insertion was not possible
# This routine is for INTERNAL USE ONLY AND MAY BE MERGED
# WITH THE PRECEEDING ONE.
#
sub insert_detector_configuration {

  if( ! $DBH){
      &print_message("insert_detector_configuration","Not connected");
      return 0;
  }

  my ($config);
  my ($tpcon, $svton, $emcon, $eemcon, $ftpcon, $richon, $fpdon, $tofon);
  my ($pmdon, $ssdon, $bbcon);
  my (@dets) =("tpc","svt","emc","eemc","ftpc","rich","fpd","tof","pmd","ssd","bbc");
  my ($el);

  if ( defined($valuset{"geometry"}) ){
      $config = $valuset{"geometry"};
  } else {
      if (! defined $valuset{"configuration"}) {
	  &print_debug("ERROR: No detector configuration/geometry name given.",
		       "Cannot add record to the table.");
	  return 0;
      } else {
	  $config = $valuset{"configuration"};
      }
  }

  #
  # Try to guess the setup if unspecified
  #
  if ( defined($valuset{"configuration"}) ){
      #print "Trying to split ".$valuset{"configuration"}."\n";
      my @items = split(/\./,$valuset{"configuration"});
      foreach $el (@items){
	  if ( defined($keywrds{$el}) ){
	      if ( ! defined($valuset{$el}) ){
		  &print_debug("$el appears in configuration but not explicitly set. Auto-set");
		  $valuset{$el} = 1;
	      }
	  }
      }
  }


  # Be sure of this being initialized for schema evolution
  foreach $el (@dets){
      if ( ! defined($valuset{$el}) ){
	  $valuset{$el} = 0;
      }
  }

  $tpcon = ($valuset{"tpc"} == 1)  ? "1" : "0";
  $svton = ($valuset{"svt"} == 1)  ? "1" : "0";
  $emcon = ($valuset{"emc"} == 1)  ? "1" : "0";
  $eemcon= ($valuset{"eemc"} == 1) ? "1" : "0";
  $ftpcon= ($valuset{"ftpc"} == 1) ? "1" : "0";
  $richon= ($valuset{"rich"} == 1) ? "1" : "0";
  $fpdon = ($valuset{"fpd"} == 1)  ? "1" : "0";
  $tofon = ($valuset{"tof"} == 1)  ? "1" : "0";
  $pmdon = ($valuset{"pmd"} == 1)  ? "1" : "0";
  $ssdon = ($valuset{"ssd"} == 1)  ? "1" : "0";
  $bbcon = ($valuset{"bbc"} == 1)  ? "1" : "0";


  my $dtinsert = "INSERT IGNORE INTO DetectorConfigurations ";
  $dtinsert   .= "(detectorConfigurationName, dTPC, dSVT, dTOF, dEMC, dEEMC, dFPD, dFTPC, dPMD, dRICH, dSSD, dBBC)";
  $dtinsert   .= " VALUES ('".$config."', $tpcon , $svton , $tofon , $emcon , $eemcon, $fpdon , $ftpcon , $pmdon , $richon , $ssdon, $bbcon)";
  if ($DEBUG > 0) {  &print_debug("Execute $dtinsert");}

  my $sth;
  my $retid=0;

  $sth = $DBH->prepare( $dtinsert );
  if( ! $sth ){
      &print_debug("insert_detector_configuration : Failed to prepare [$dtinsert]");
  } else {
      if ( $sth->execute() ) {
	  $retid = &get_last_id();
	  &new_value("insert_detector_configuration",$retid,$config,"DetectorConfigurations");
      }
      $sth->finish();
  }
  return $retid;
}



#============================================
# disentangle collision type parameters from the collsion type name
# Params:
# The collsion type
# Returns:
#   first particle name
#   second particle name
#   collision energy
sub disentangle_collision_type {

  my ($colstring) = @_;
  my ($firstParticle,$secondParticle,$el);
  my (@particles) = ("proton", "gas", "au", "ga", "si", "p", "d", "s");

  $firstParticle = $secondParticle = "";

  if (($colstring =~ m/cosmic/) > 0){
      # Special case for cosmic
      $firstParticle  = "cosmic";
      $secondParticle = "cosmic";
      $colstring = "0.0";
  } elsif (($colstring =~ m/unknown/) > 0){
      # Allow this as well
      $firstParticle  = "unknwon";
      $secondParticle = "unknwon";
      $colstring = "0.0";

  } else {
      # Otherwise, cut in first/second
      foreach $el (@particles){
	  if (($colstring =~ m/(^$el)(.*)/) > 0) {
	      &print_debug("Found first particle  = $el in $colstring");
	      $firstParticle = $el;
	      $colstring =~ s/($el)(.*)/$2/;
	      last;
	  }
      }
      foreach $el (@particles){
	  if (($colstring =~ m/(^.*)($el)/) > 0) {
	      &print_debug("Found second particle = $el in $colstring");
	      $secondParticle = $el;
	      $colstring =~ s/(.*)($el)(.*)/$1$3/;
	      # be sure to get the numerical value only
	      $colstring =~ m/(\d+\.\d+|\d+)/;
	      $colstring =  $1;
	      last;
	  }
      }
  }
  return ($firstParticle, $secondParticle, $colstring);
}

#============================================
# disentangle collision type parameters from the collsion type name
# Params:
# The collsion type to find
# Returns:
#   The id of a collision type in DB or 0 if there is no such collsion type
#
# METHOD IS FOR INTERNAL USE ONLY.
# A query may return several values since there is a truncation done.
#
sub get_collision_type
{
    my(@tab) = &get_collision_collection(@_);

    if( @tab ){
	return $tab[0];
    } else {
	return;
    }
}
sub get_collision_collection {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  };
  if( ! defined($DBH) ){
      &print_message("get_collision_collection","Not connected/connecting");
      return 0;
  }


  my ($colstring) = @_;
  my $retid;
  my $firstParticle;
  my $secondParticle;
  my $energy;

  if( $colstring eq ""){
      &die_message("get_collision_collection","received empty argument");
  }

  $colstring = lc($colstring);

  ($firstParticle, $secondParticle, $energy) = &disentangle_collision_type($colstring);

  my $sqlquery = "SELECT collisionTypeID FROM CollisionTypes WHERE UPPER(firstParticle) = UPPER(\"$firstParticle\") AND UPPER(secondParticle) = UPPER(\"$secondParticle\") AND ROUND(collisionEnergy) = ROUND($energy)";

  if ($DEBUG > 0) {
      &print_debug("First particle : $firstParticle",
		   "Second particle: $secondParticle",
		   "Energy         : $colstring",
		   "Executing      : $sqlquery");
  }


  my @retv;
  my $id;

  my $sth = $DBH->prepare($sqlquery);
  if( ! $sth){
      &print_debug("FileCatalog::get_collision_collection : Failed to prepare [$sqlquery]");
  } else {
      if( ! $sth->execute() ){
	  &die_message("get_collision_collection","Could not execute [$sqlquery]");
      } else {
	  $sth->bind_columns( \$id );

	  if ( $sth->fetch() ) {
	      push(@retv,$id);
	  }
	  if($#retv == -1){
	      $id = &insert_collision_type();
	      &print_message("get_collision_collection","Inserting new CollisionTypes value [$colstring]");
	      push(@retv,$id);
	  }

	  $sth->finish();
      }
  }

  return @retv;

}

#============================================
# insert a given collision tye into the database
# Returns:
# the id of a collision type in DB
# or 0 if the insertion was not possible
sub insert_collision_type {

  my $colstring = $valuset{"collision"};
  my $firstParticle;
  my $secondParticle;
  my $energy;

  if( ! defined($DBH) ){
      &print_message("insert_collision_type","Not connected");
      return 0;
  }




  $colstring = lc($colstring);

  ($firstParticle, $secondParticle, $energy) = &disentangle_collision_type($colstring);



  my $ctinsert   = "INSERT IGNORE INTO CollisionTypes ";
  $ctinsert  .= "(firstParticle, secondParticle, collisionEnergy)";
  $ctinsert  .= " VALUES ('$firstParticle' , '$secondParticle' , $energy)";

  &print_debug("Execute $ctinsert");

  my $sth;
  my $retid=0;

  $sth = $DBH->prepare( $ctinsert );
  if( ! $sth){
      &print_debug("insert_collision_type : Failed to prepare [$ctinsert]");
  } else {
      if ( $sth->execute() ) {
	  $retid = &get_last_id();
	  &print_debug("Returning: $retid");
      }
      $sth->finish();
  }
  return $retid;
}

#============================================
# Get the ID of a last inserted record from the database
# Returns:
# The ID of a most recently successfully added record
sub get_last_id
{
    my $sqlquery = "SELECT LAST_INSERT_ID()";
    my $id;
    my $retv=0;

    if( ! defined($DBH) ){
	&print_message("get_last_id","Not connected");
	return 0;
    }

    $sth = $DBH->prepare($sqlquery);
    if( $sth ){
	if ( $sth->execute() ){
	    $sth->bind_columns( \$id );

	    if ( $sth->fetch() ) {
		$retv = $id;
	    } else {
		&print_message("get_last_id","ERROR: Cannot find the last inserted ID");
	    }
	}
	$sth->finish();
    } else {
	&print_debug("FileCatalog::get_last_id : Arghhh !!! Cannot prepare [$sqlquery]");
    }
    return $retv;
}

#============================================
# Check for the availability of all parameters
# and execute run param info insert query
# Return:
# The id of the inserted run params
# 0 if there is insufficient data to insert run params
sub insert_run_param_info {

  my $triggerSetup;
  my $collisionType;
  my $runType;
  my $detConfiguration;
  my $comment;
  my $start;
  my $end;
  my $collision;
  my $simulation;
  my $magvalue;

  if( ! defined($DBH) ){
      &print_message("insert_run_param_info","Not connected");
      return 0;
  }


  $triggerSetup     = &check_ID_for_params("trgsetupname");
  $runType          = &check_ID_for_params("runtype");
  $detConfiguration = &get_current_detector_configuration();


  #
  # Those values may fix some side effect of closing
  #
  if (! defined $valuset{"runnumber"}) {
      if ( defined( $valuset{"rrpid"}) ){
	  # rpid is set in clone_location() mode
	  return $valuset{"rrpid"};
      } else {
	  &print_message("insert_run_param_info","runnumber not defined.");
	  return 0;
      }
  }

  #
  # Those values will be re-tested but may be auto-set at this stage
  #
  if (defined $valuset{"collision"}) {
      # only one value matters
      $collision = &get_collision_type($valuset{"collision"});
      if ($DEBUG > 0) {
	  &print_debug("Collision      : $collision");
      }
  } else {
      &print_debug("ERROR: collision not defined");
  }



  #
  # Now, there is nothing else we can do apart from rejecting insertion
  # if invalid. There are therefore last-resort mandatory values.
  #
  if (($triggerSetup == 0) || ($runType == 0) || ($detConfiguration == 0) || ($collision == 0)) {
      &print_message("insert_run_param_info","Missing trgsetupname, runtype or configuration",
		     "Aborting file insertion query");
      &die_message("insert_run_param_info","trgsetupname detected as missing") if ($triggerSetup == 0);
      &die_message("insert_run_param_info","runtype      detected as missing") if ($runType == 0);
      &die_message("insert_run_param_info","collision    detected as missing") if ($collision == 0);
  }
  if (! defined $valuset{"magscale"}) {
      &die_message("insert_run_param_info","magscale not defined.");
  }


  #
  # None of the above are mandatory and are subject to default values
  #
  if (! defined $valuset{"runcomments"}) {
    $comment = "NULL";
  } else {
    $comment = "\"".$comment."\"";
  }
  if (! defined $valuset{"magvalue"}) {
    $magvalue = "NULL";
  } else {
    $magvalue = $valuset{"magvalue"};
  }
  if (! defined $valuset{"datetaken"}) {
    $start = "NULL";
    $end   = "NULL";
  } else {
    $start = "\"".$valuset{"datetaken"}."\"";
    $end   = "\"".$valuset{"datetaken"}."\"";
  }
  if ((defined $valuset{"simulation"}) && (! ($valuset{"simulation"} eq '0') ) ) {
      &print_debug("Adding simulation data.");
      $simulation = &get_current_simulation_params();
  } else {
      $simulation = "NULL";
  }


  my $rpinsert;

  $rpinsert   = "INSERT IGNORE INTO RunParams ";
  $rpinsert  .= "(runNumber, dataTakingStart, dataTakingEnd, triggerSetupID, collisionTypeID, simulationParamsID, runTypeID, detectorConfigurationID, runComments, magFieldScale, magFieldValue)";
  $rpinsert  .= " VALUES (".$valuset{"runnumber"}.",$start,$end,$triggerSetup,$collision,$simulation,$runType,$detConfiguration,$comment,'".$valuset{"magscale"}."',$magvalue)";
  if ($DEBUG > 0) {  &print_debug("Execute $rpinsert");}


  my $sth;
  my $retid=0;

  $sth = $DBH->prepare( $rpinsert );
  if( ! $sth ){
      &print_debug("FileCatalog::insert_run_param_info : Failed to prepare [$rpinsert]");
  } else {
      # Insert the event counts for a given FileData
      if ( $sth->execute() ) {
	  $retid = &get_last_id();
	  if ($DEBUG > 0) { &print_debug("Returning: $retid");}
      }
      $sth->finish();
  }
  return $retid;
}

#============================================
# get the ID for the current run number
# Returns:
# the ID of a runParams record,
# or 0 if no such record exists
sub get_current_run_param {
  my $runNumber;

  $runNumber = &check_ID_for_params("runnumber");
  if ($runNumber == 0) {
    # There is no run with this run number
    # we have to add it
    $runNumber = &insert_run_param_info();
  }
  return $runNumber;
}

#============================================
# Execute the query to insert the file data
# Check if we have all the information
# Returns:
# The id of a lastly inserted file data
# or 0 is there is insufficient data to insert a record
#
# NOT EXPORTED
#
sub insert_file_data {
  my @params = @_;
  # Get the ID's of the dictionary tales
  my $production;
  my $library;
  my $fileType;
  my $runNumber;
  my $nevents;
  my $fileComment;
  my $fileSeq;
  my $filestream;
  my @triggerWords;
  my @eventCounts;
  my @triggerIDs;
  my $count;

  if( ! defined($DBH) ){
      &print_message("insert_file_data","Not connected");
      return 0;
  }

  $production = &check_ID_for_params("production");
  $library    = &check_ID_for_params("library");
  $fileType   = &check_ID_for_params("filetype");

  # cloning has side effects. we must delete the content if replaced
  if ( defined($valuset{"rpcid"}) ){
      # library because later check assigns prod = lib
      if ( $library == 0 ){     $library = $valuset{"rpcid"};}
      delete($valuset{"rpcid"});
  }
  if ( defined($valuset{"rftid"}) ){
      if ( $fileType == 0  ){   $fileType = $valuset{"rftid"};}
      delete($valuset{"rftid"});
  }
  return 0 if ((($production == 0 ) && ($library == 0)) || $fileType == 0);

  if ($production == 0) {       $production = $library;}


  $runNumber = &get_current_run_param();

  if ($runNumber == 0) {
      &print_message("insert_file_data","Could not add run data");
      return 0;
  }
  if (! defined $valuset{"filename"}) {
      &print_message("insert_file_data","filename not defined.");
      return 0;
  }

  if (! defined $valuset{"filecomment"}) {
      $fileComment = "NULL";
  } else {
      $fileComment = "\"".$valuset{"filecomment"}."\"";
  }
  if (! defined $valuset{"fileseq"}) {
      $fileSeq = "NULL";
  } else {
      $fileSeq = "\"".$valuset{"fileseq"}."\"";
  }
  if (! defined $valuset{"stream"}) {
      $filestream = 0;
  } else {
      $filestream = "\"".$valuset{"stream"}."\"";
  }
  if (! defined $valuset{"events"}) {
      $nevents = 0;
  } else {
      $nevents = $valuset{"events"};
  }


  # Prepare the SQL query and execute it
  my $fdinsert   = "INSERT IGNORE INTO FileData ";
  $fdinsert  .= "(runParamID, fileName, productionConditionID, numEntries, fileTypeID, fileDataComments, fileSeq, fileStream)";
  $fdinsert  .= " VALUES ($runNumber, \"".$valuset{"filename"}."\",$production, $nevents, $fileType,$fileComment,$fileSeq,$filestream)";
  if ($DEBUG > 0) { &print_debug("Execute $fdinsert");}


  my $sth;
  my $retid;
  $sth = $DBH->prepare( $fdinsert );
  if( $sth ){
      if ($DELAY){
	  push(@DCMD,
	       "# Delayed mode chosen but operation is not 'flush'-able. ".
	       "Use direct update for ".$fdinsert);
	  $retid = 0;
      } else {
	  if ( $sth->execute() ) {
	      $retid = &get_last_id();
	      $sth->finish();
	      &print_debug("Returning: $retid");

	  } else {
	      $sth->finish();
	      return 0;
	  }
      }
  } else {
      &print_debug("insert_file_data : Failed to prepare [$fdinsert]");
  }

  # TriggerComposition and TriggerWords are now handled by a single routine
  &set_trigger_composition($retid) if ($retid != 0);

  return $retid;
}







#============================================
#
# This internal routine was added to handle insertion
# of the trigger information.
# It is developped for handling updates as well.
#

#
# Add a new individual trigger to the collection
# The internal arrays are flushed by any calls to add_file_data() through
# a call to set_trigger_composition()
#
# Arguments are obvious ...
#
sub add_trigger_composition
{
    if ($_[0] =~ m/FileCatalog/) {  shift @_;}
    my($triggerName,$triggerWord,$triggerVersion,$triggerDefinition,$triggerCount) = @_;

    # Store it in internal arrays
    $FC::IDX++;
    $FC::TRGNAME[$FC::IDX] = &get_value($triggerName,"unknown",0);
    $FC::TRGWORD[$FC::IDX] = &get_value($triggerWord,"000000",0);
    $FC::TRGVERS[$FC::IDX] = &get_value($triggerVersion,"V0.0",1);
    $FC::TRGDEFS[$FC::IDX] = &get_value($triggerDefinition,"unspecified",0);
    $FC::TRGCNTS[$FC::IDX] = &get_value($triggerCount,0,0);

}

#
# This really enters it (or updates) in the database
#
# Arg1 : a fdid
# Arg2 : an insert/update flag (0 insert, 1 update)
#
sub set_trigger_composition
{
    my($tcfdid,$update)=@_;

    if( ! defined($DBH)){
	&print_message("set_trigger_compositio",
		       "Not connected/connecting");
	return;
    }
    if ( $FC::IDX == -1 ) {
	if ( defined($valuset{"simulation"}) ){
	    if ( $valuset{"simulation"} eq '0'){
		&print_message("set_trigger_composition",
			       "No trigger composition set");
	    }
	}
	return;
    }
    if( ! defined($tcfdid) ){
	&die_message("set_trigger_composition",
		     "Mandatory first argument undefined");
    }

    if( $tcfdid == 0){
	&print_message("set_trigger_composition",
		       "Preceeding operation prevents current execution");
	return;
    }


    my($i,$el,$cnt);
    my($cmd1,$sth1,$cmd2,$sth2);
    my($cmdd,$sthd);
    my(@all);
    my(@TrgID,@TrgCnt);



    #
    # Insert first all entries in TriggerWords in INSERT mode
    #
    $cmd1 = "SELECT triggerWordID, triggerDefinition FROM TriggerWords ".
	" WHERE triggerName=? AND triggerWord=?  AND triggerVersion=?";
    $cmd2 = "INSERT INTO TriggerWords values(NULL, ?, ?, ?, ?)";

    $sth1 = $DBH->prepare($cmd1);
    $sth2 = $DBH->prepare($cmd2);

    if ( ! $sth1 || ! $sth2 ){  &die_message("set_trigger_composition","Prepare statements 1 failed");}

    # Loop over and check/insert
    $cnt = -1;
    for ($i=0 ; $i <= $#FC::TRGNAME ; $i++){
	print "Should insert $FC::TRGNAME[$i] $FC::TRGWORD[$i] $FC::TRGVERS[$i] $FC::TRGDEFS[$i] $FC::TRGCNTS[$i]\n";
	if ( $sth1->execute($FC::TRGNAME[$i],$FC::TRGWORD[$i],$FC::TRGVERS[$i]) ){
	    if ( @all = $sth1->fetchrow() ){
		# Already in, fetch
		&print_debug("Fetched 1 triggerWordID $all[0]");
		$TrgID[++$cnt] = $all[0];
		$TrgCnt[$cnt]  = $FC::TRGCNTS[$i];
	    } else {
		# Not in, Insert
		if ( $sth2->execute($FC::TRGNAME[$i],$FC::TRGWORD[$i],$FC::TRGVERS[$i],$FC::TRGDEFS[$i]) ){
		    $TrgID[++$cnt] = &get_last_id();
		    $TrgCnt[$cnt]  = $FC::TRGCNTS[$i];
		    &print_debug("Fecthed 2 triggerWordID $TrgID[$cnt]");
		} else {
		    &die_message("set_trigger_composition",
				 "Failed to insert $FC::TRGNAME[$i],$FC::TRGWORD[$i],$FC::TRGVERS[$i],$FC::TRGDEFS[$i]");
		}
	    }
	} else {
	    &die_message("set_trigger_composition",
			 "Failed to execute for $FC::TRGNAME[$i],$FC::TRGWORD[$i],$FC::TRGVERS[$i]");
	}
    }
    $sth1->finish;
    $sth2->finish;



    #
    # Enter entries in TriggerCompositions
    #
    $cmd1 = "SELECT triggerWordID FROM TriggerCompositions WHERE fileDataID=?";
    $cmd2 = "INSERT DELAYED INTO TriggerCompositions values(?,?,?)";
    $sth1 = $DBH->prepare($cmd1);
    $sth2 = $DBH->prepare($cmd2);

    if ( ! $sth1 || ! $sth2 ){  &die_message("set_trigger_composition","Prepare statements 2 failed");}

    if ( ! $sth1->execute($tcfdid) ){
	&print_message("set_trigger_composition","Could not execute [$cmd1 , $tcfdid]");
    } else {
	@all = $sth1->fetchrow();
	if ($#all != -1){
	    # There are entries for this tcfdid already
	    if ($update){
		# We can drop them all from TriggerCompositions. We cannot delay this ...
		# The entries in the TriggerWords table may be used in other records
		# (will do a bootstrap routine).
		#
		# Here, we deleted only the fully-specified records because we envision
		# this routine to be used in update of perticular triggerWord (leaving
		# the rest of the list unmodified).
		#
		$cmdd = "DELETE LOW_PRIORITY FROM TriggerCompositions WHERE fileDataID=? AND triggerWord=?";
		$sthd = $DBH->prepare($cmdd);
		foreach $el (@all){
		    &print_debug("$cmdd , $tcfdid, $el");
		    $sthd->execute($tcfdid,$el);
		}
		$sthd->finish;

	    } else {
		&print_message("set_trigger_composition","Update not yet implemented");
		return;
	    }
	} else {
	    # The table is empty. We can now insert the triggerWordIDs recovered
	    # preceedingly. Note that we MUST die() here if it fails since we
	    # have already checked the existence of $tcfdid entries ... and there
	    # none.
	    for ( $i=0 ; $i <= $#TrgID ; $i++){
		if ( ! $sth2->execute($tcfdid,$TrgID[$i],$TrgCnt[$i]) ){
		    &die_message("set_trigger_composition",
				 "Insertion of ($tcfdid,$TrgID[$i],$TrgCnt[$i]) failed");
		}
	    }

	}
    }
    $sth1->finish;
    $sth2->finish;


    # Entries are NOT re-usable (would be too dangerous)
    $FC::IDX=-1;
    undef(@FC::TRGNAME);
    undef(@FC::TRGWORD);
    undef(@FC::TRGVERS);
    undef(@FC::TRGDEFS);
}



# This is an internal routine
sub del_trigger_composition
{
    my($tcfdid,$doit)=@_;
    my($cmd,$sth);

    if ($doit){
	if ( $DELAY ){
	    push(@DCMD,
		 "DELETE LOW_PRIORITY FROM TriggerCompositions WHERE fileDataID=$tcfdid");
	} else {
	    # a complete different story
	    $cmd = "DELETE LOW_PRIORITY FROM TriggerCompositions WHERE fileDataID=?";
	    $sth = $DBH->prepare($cmd);

	    if ( ! $sth ){
		&print_message("del_trigger_composition",
			       "Prepare failed. Bootstrap TRGC needed.");
		return;
	    }
	    &print_debug("Execute $cmd , $tcfdid");

	    if ( ! $sth->execute($tcfdid) ){
		&print_message("del_trigger_composition",
			       "Execute failed. Bootstrap TRGC needed.");
	    }
	    $sth->finish;
	}
    } else {
	&print_message("del_trigger_composition",
		       "[$tcfdid] from TriggerCompositions would be deleted");
    }
}




#============================================
# get the ID for the current file data, or create it
# if not found.
# Returns:
#  the ID of a fileData record
#  or 0 if no such fielData, cannot create it, or more than one record exists for a given context.
sub get_current_file_data {
  my $runParam;
  my $fileName;
  my $production;
  my $library;
  my $fileType;
  my $fileSeq;
  my $filestream;
  my $sqlquery;

  if( ! defined($DBH) ){
      &print_message("get_current_file_data","Not connected");
      return 0;
  }

  # cloned
  if ( defined( $valuset{"rfdid"}) ){ return $valuset{"rfdid"};}

  # Otherwise, must search for the ID
  $runParam   = &get_current_run_param();
  $production = &check_ID_for_params("production");
  $library    = &check_ID_for_params("library");
  $fileType   = &check_ID_for_params("filetype");

  #print "In get_current_file_data $runParam $production $library $fileType\n";

  if ($production == 0) {
      $production = $library;
  }
  if ( $runParam != 0) {
      $sqlquery .= " runParamID = $runParam AND ";
  }
  if (defined $valuset{"filename"}) {
      $sqlquery .= " fileName = '".$valuset{"filename"}."' AND ";
  }
  if (defined $valuset{"fileseq"}) {
      $sqlquery .= " fileSeq = '".$valuset{"fileseq"}."' AND ";
  }
  if (defined $valuset{"stream"}) {
      $sqlquery .= " fileStream = '".$valuset{"stream"}."' AND ";
  }
  if ( $production != 0) {
      $sqlquery .= " productionConditionID = $production AND ";
  }
  if ( $fileType != 0) {
      $sqlquery .= " fileTypeID = $fileType AND ";
  }
  if ( defined($sqlquery) ){
      $sqlquery =~ s/(.*)AND $/$1/g;
  } else {
      &print_message("get_current_file_data","No parameters set to identify File Data");
      #print "Zobi1 ...\n";
      return 0;
  }
  $sqlquery = "SELECT fileDataID FROM FileData WHERE $sqlquery";
  if ($DEBUG > 0) {
      &print_debug("Executing query: $sqlquery");
  }

  my($sth,$id);

  $sth = $DBH->prepare($sqlquery);

  if( ! $sth ){
      &print_message("get_current_file_data","Failed to prepare [$sqlquery]");
      #print "Zobi2 [$sqlquery] ...\n";
      return 0;
  }

  #print "Zobi 3 (execute)\n";
  my $retv=0;
  if ( $sth->execute() ){
      $sth->bind_columns( \$id );

      if ($sth->rows == 0) {
	  $retv = &insert_file_data();

      } elsif ($sth->rows > 1) {
	  &print_message("get_current_file_data","More than one file data matches the query criteria",
			 "Add more data to unambiguously identify file data");

      } elsif ( $sth->fetch() ) {
	  if ($DEBUG > 0) { &print_debug("Returning: $id");}

	  $retv = $id;
      }
  }
  $sth->finish();

  #print "Return $retv\n";
  return $retv;
}


#============================================
# inserts the file location data and the file and run data
# if neccessary.
# Returns: The ID of a newly created File Location
# or 0 if the insert fails
sub insert_simulation_params {
  my $simComments;
  my $evgenComments;
  my $eventGenerator;

  if( ! defined($DBH) ){
      &print_message("insert_simulation_params","Not connected");
      return 0;
  }

  if (! (defined $valuset{"generator"}  &&
	 defined $valuset{"genversion"} &&
	 defined $valuset{"genparams"})) {
      &die_message("insert_simulation_params",
		   "Not enough parameters to insert event generator data",
		   "Define generator, genversion and genparams");
      return 0;
  }
  if (! defined $valuset{"gencomment"}) {
      &print_debug("WARNING: gencomment not defined. Using NULL");
      $evgenComments = "NULL";
  } else {
      $evgenComments = '"'.$valuset{"gencomment"}.'"';
  }
  if (! defined $valuset{"simcomment"}) {
      &print_debug("WARNING: simcomment not defined. Using NULL");
      $simComments = "NULL";
  } else {
      $simComments = '"'.$valuset{"simcomment"}.'"';
  }

  my $sqlquery = "SELECT eventGeneratorID FROM EventGenerators WHERE eventGeneratorName = '".$valuset{"generator"}."' AND eventGeneratorVersion = '".$valuset{"genversion"}."' AND eventGeneratorParams = '".$valuset{"genparams"}."'";
  if ($DEBUG > 0) {
      &print_debug("Executing query: $sqlquery");
  }


  my $sth;
  $sth = $DBH->prepare($sqlquery);
  if( ! $sth ){
      &print_debug("FileCatalog::insert_simulation_params : Failed to prepare [$sqlquery]");
      return 0;
  }

  my( $id );
  if ( ! $sth->execute() ){  return 0;}

  $sth->bind_columns( \$id );

  if ($sth->rows == 0) {
      my $eginsert   = "INSERT IGNORE INTO EventGenerators ";
      $eginsert  .= "(eventGeneratorName, eventGeneratorVersion, eventGeneratorComment, eventGeneratorParams)";
      $eginsert  .= " VALUES ('".$valuset{"generator"}."', '".$valuset{"genversion"}."', $evgenComments, '".$valuset{"genparams"}."')";
      if ($DEBUG > 0) {
	  &print_debug("Execute $eginsert");
      }
      my $sth = $DBH->prepare( $eginsert );

      if ( $sth->execute() ) {
	  $eventGenerator = &get_last_id();
	  if ($DEBUG > 0) {
	      &print_debug("Returning: $eventGenerator");
	  }
      } else {
	  &print_debug("Could not add event gerator data.",
		       "Aborting simulation data insertion query");
      }
  } else {
      $sth->fetch;
      if ($DEBUG > 0) {
	  &print_debug("Got eventGenerator: $id");
      }
      $eventGenerator = $id;
  }

  my $spinsert   = "INSERT IGNORE INTO SimulationParams ";
  $spinsert  .= "(eventGeneratorID, simulationParamComments)";
  $spinsert  .= " VALUES ($eventGenerator, $simComments)";
  if ($DEBUG > 0) {
      &print_debug("Execute $spinsert");
  }

  $sth = $DBH->prepare( $spinsert );
  if( ! $sth){
      &print_debug("FileCatalog::insert_simulation_params : Failed to prepare [$spinsert]");
      return 0;
  }
  if ( $sth->execute() ) {
      my $retid = &get_last_id();
      if ($DEBUG > 0) {
	  &print_debug("Returning: $retid");
      }
  } else {
      &print_debug("Could not add simulation data.",
		   "Aborting simulation data insertion query.");
      $sth->finish();
      return 0;
  }

  $sth->finish();

}

#============================================
# get the ID for the current simulation parameters, or create them
# if not found.
# Returns:
# the ID of a SimulationParams record
# or 0 if no such record and cannot create it
sub get_current_simulation_params {
  my $simComment;
  my $generator;
  my $generatorVer;
  my $generatorParams;
  my $generatorComment;
  my $sqlquery;

  if( ! defined($DBH) ){
      &print_message("get_current_simulation_params","Not connected");
      return 0;
  }

  if (! (defined $valuset{"generator"}  &&
	 defined $valuset{"genversion"} &&
	 defined $valuset{"genparams"})) {
      &die_message("get_current_simulation_params",
		   "Not enough parameters to find event generator data",
		   "Define generator, genversion and genparams");
      return 0;
  }
  $sqlquery = "SELECT simulationParamsID FROM SimulationParams, EventGenerators WHERE eventGeneratorName = '".$valuset{"generator"}."' AND eventGeneratorVersion = '".$valuset{"genversion"}."' AND eventGeneratorParams = '".$valuset{"genparams"}."' AND SimulationParams.eventGeneratorID = EventGenerators.eventGeneratorID";
  if ($DEBUG > 0) {
      &print_debug("Executing query: $sqlquery");
  }

  my ($sth);
  $sth = $DBH->prepare($sqlquery);
  if ( ! $sth){
      &print_debug("FileCatalog::get_current_simulation_params : Failed to prepare [$sqlquery]");
      return 0;
  }

  my ($id);

  if ( $sth->execute() ){
      $sth->bind_columns( \$id );

      if ($sth->rows == 0) {
	  my $newid;
	  $newid = &insert_simulation_params();
	  $sth->finish();
	  return $newid;
      } else {
	  if ( $sth->fetch() ) {
	      if ($DEBUG > 0) { &print_debug("Returning: $id");}
	      $sth->finish();
	      return $id;
	  }
      }
  }
  $sth->finish();
  return 0;

}

#
# Gets the entry associated to a context and reset
# the context with the exact full value list required
# for a new entry.
#
sub clone_location {
    my(@allfd,@allfl,$tmp);

    @allfd = &FileTableContent("FileData","FDKWD");
    @allfl = &FileTableContent("FileLocation","FLKWD");

    if ($#allfd != -1 && $#allfl != -1){
	&clear_context();
	&set_context(@allfd);
	&set_context(@allfl);

	&print_debug("clone_location :: What was queried\n",
		     "\t".join(",",@allfd),
		     "\t".join(",",@allfl));
	1;
    } else {
	&print_message("clone_location","FileData/FileLocation cloning failed");
	0;

    }
}

sub get_file_location(){
    return &FileTableContent("FileLocation","FLKWD");
}
sub get_file_data(){
    return &FileTableContent("FileData","FDKWD");
}

sub FileTableContent {

    my($table,$TABREF)=@_;

    my($i,@itab,$iref,@query,@items);

    #print "Checking for $table\n";

    eval("@itab = @$TABREF");

    #print "Evaluating for $table\n";
    foreach ( keys %keywrds ){
	@items = split(",",$keywrds{$_});
	if ( $items[1] =~ m/$table/ && $items[5] == 1 ){
	    push(@itab,$_);
	    #} else {
	    #print "Rejecting $_ $keywrds{$_}\n";
	}
    }
    #print "-->".join(",",@itab)."\n";


    my @all;
    my $delim;

    $delim = &get_delimeter();
    &set_delimeter("::");                     # set to known one
    @all = &run_query("FileCatalog",@itab);
    &set_delimeter($delim);                   # restore delim


    &print_debug("+","Run with ".join("/",@itab));


    undef(@query);
    if ($#all != -1){
	@all = split("::",$all[0]);                # Only one instance

	for ( $i=0 ; $i <= $#itab ; $i++){
	    #&print_debug("Return value for $itab[$i] is $all[$i]");
	    &print_debug("-->","Return value for $itab[$i] is $all[$i]");
	    if( $all[$i] ne ""){
		push(@query,"$itab[$i] = $all[$i]");
	    }
	}
    }
    return @query;
}




#============================================
# inserts the file location data and the file and run data
# if neccessary.
# Returns: The ID of a newly created File Location
#          or 0 if the insert fails
sub insert_file_location {
  my $fileData;
  my $storageType;
  my $storageSite;
  my $filePath;
  my $createTime;
  my $owner;
  my $fsize;
  my $protection;
  my $nodeName;
  my $availability;
  my $persistent;
  my $sanity;

  if( ! defined($DBH) ){
      &print_message("insert_file_location","Not connected");
      return 0;
  }

  $fileData = &get_current_file_data();
  if ($fileData == 0) {
      if ($DELAY){
	  &print_message("insert_file_location","Proceeding for debugging purposes only");

      } else {
	  &print_message("insert_file_location","No file data available",
			 "Aborting file insertion query");
	  return 0;
      }
  }


  $storageType = &check_ID_for_params("storage");
  $storageSite = &check_ID_for_params("site");
  if ( $storageType == 0 ) {
      &print_message("insert_file_location","Aborting file location insertion query. storage mandatory");
      return 0;
  }
  if( defined($valuset{"rssid"}) ){
      if ($storageSite == 0){  $storageSite = $valuset{"rssid"};}
      delete($valuset{"rssid"});
  }


  if (! defined $valuset{"path"} ) {
      &print_message("insert_file_location",
		     "ERROR: file path not defined. Cannot add file location",
		     "Aborting File Location");
      return 0;
  } else {
      $filePath = "'".$valuset{"path"}."'";
  }
  if (! defined $valuset{"createtime"}) {
      &print_debug("WARNING: createtime not defined. Using a default value");
      $createTime = "NULL";
  } else {
      $createTime = $valuset{"createtime"};
  }

  if (! defined $valuset{"owner"}) {
      &print_debug("WARNING: owner not defined. Using a default value");
      $owner = "''";
  } else {
      $owner = '"'.$valuset{"owner"}.'"';
  }
  if (! defined $valuset{"protection"}) {
      &print_debug("WARNING: protection not defined. Using a default value");
      $protection = '" "';
  } else {
      $protection = '"'.$valuset{"protection"}.'"';
  }
  if (! defined $valuset{"node"}) {
      &print_debug("WARNING: node not defined. Using a default value");
      $nodeName = "'localhost'";      # Cannot be NULL because of check
  } else {
      $valuset{"node"} =~ s/\s+//g;
      if ( $valuset{"node"} ne ""){
	  $nodeName = '"'.$valuset{"node"}.'"';
      } else {
	  $nodeName = "'localhost'";  # Cannot be NULL because of check
      }

  }
  if (! defined $valuset{"available"}) {
      &print_debug("WARNING: available not defined. Using a default value");
      $availability = 1 ;
  } else {
      $availability = $valuset{"available"};
  }
  if (! defined $valuset{"persistent"}) {
      &print_debug("WARNING: persistent not defined. Using a default value");
      $persistent = 0 ;
  } else {
      $persistent = $valuset{"persistent"};
  }
  if (! defined $valuset{"sanity"}) {
      &print_debug("WARNING: sanity not defined. Using a default value");
      $sanity = 0;
  } else {
      $sanity = $valuset{"sanity"};
  }

  if (! defined $valuset{"size"}) {
      $fsize = 0;
  } else {
      $fsize = $valuset{"size"};
  }


  # This table is exponentially growing with an INSERT IGNORE or INSERT
  # Changed May 31st 2002.

  my $flinchk    = "SELECT fileLocationID from FileLocations WHERE ";
  my $flinsert   = "INSERT IGNORE INTO FileLocations ";

  $flinsert  .= "(fileLocationID, fileDataID, storageTypeID, filePath, createTime, insertTime, owner, fsize, storageSiteID, protection, nodeName, availability, persistent, sanity)";
  $flinsert  .= " VALUES (NULL, $fileData, $storageType, $filePath, $createTime, NULL, $owner, $fsize, $storageSite, $protection, $nodeName, $availability, $persistent, $sanity)";

  # NONE of the NULL value should appear below otherwise, one keeps adding
  # entry over and over ... protection and woner are irrelevant here and
  # requires an UPDATE instead of a new insert.
  $flinchk   .= " fileDataID=$fileData AND storageTypeID=$storageType AND filePath=$filePath AND storageSiteID=$storageSite AND nodeName=$nodeName";




  my $sth;
  my $retid=0;

  &print_debug("Execute $flinchk");
  #print "Executing $flinchk\n";
  $sth = $DBH->prepare( $flinchk );
  if ( ! $sth ){
      &print_debug("FileCatalog::insert_file_location : Failed to prepare [$flinchk]");
  } else {
      if ( $sth->execute() ){
	  my ($val);
	  if ( defined($val = $sth->fetchrow()) ){
	      &print_message("insert","Record already in as $val (may want to update)\n");
	      $retid = $val;
	  }
      }
  }
  $sth->finish();

  if( $retid == 0){
      &print_debug("Execute $flinsert");
      $sth = $DBH->prepare( $flinsert );
      #print "++ $flinsert ++";
      if( ! $sth ){
	  &print_debug("FileCatalog::insert_file_location : Failed to prepare [$flinsert]");
      } else {
	  if ($DELAY ){
	      push(@DCMD,$flinsert);
	      $retid = 0;
	  } else {
	      if ( $sth->execute() ) {
		  $retid = &get_last_id();
		  &print_debug("Returning: $retid");
		  $sth->finish();
	      }
	  }
      }
  }
  return $retid;

}


#====================================================
# Helper subroutines needed for the generic query building
#====================================================
# Gets the 'level' of a database table
# The table is at level 1, if it not directly referenced by any other table
# The table is at level 2 if it is directly referenced by a table at level 1 etc.
sub get_struct_level {
  my $count;
  my ($paramtable) = @_;

  if( ! defined($paramtable) ){  return 0;}

  for ($count = 0; $count<($#datastruct+1); $count++) {
    my ($mtable, $stable, $cfield, $level) = split(",",$datastruct[$count]);
    if ($mtable eq $paramtable) {
      return $level;
    }
  }
  return 0;
}

#====================================================
# Get all the tables at the lower level connnected to this table
sub get_lower_level {
  my $count;
  my ($paramtable) = @_;

  if( ! defined($paramtable) ){  return 0;}

  for ($count = 0; $count<($#datastruct+1); $count++) {
    my ($mtable, $stable, $cfield, $level) = split(",",$datastruct[$count]);
    if (($mtable eq $paramtable) && ($stable ne "")) {
      return ($stable, $level-1, $count);
    }
  }
  return 0;
}

#===================================================
# Get all the tables at the upper level connected to this table
sub get_all_upper {
  my $count;
  my ($paramtable) = @_;
  my @lower;

  if( ! defined($paramtable) ){  return 0;}

  for ($count = 0; $count<($#datastruct+1); $count++) {
    my ($mtable, $stable, $cfield, $level) = split(",",$datastruct[$count]);
    if ($stable eq $paramtable) {
      push(@lower, $mtable);
    }
  }
  return (@lower);
}

#===================================================
# Return the connection description index from a @datastruct table
# describing the connection between two tables
sub get_connection {
  my ($amtable, $astable) = (@_);

  for (my $count = 0; $count<($#datastruct+1); $count++) {
    my ($mtable, $stable, $cfield, $level) = split(",",$datastruct[$count]);
    if (($stable eq $astable) && ($mtable eq $amtable)) {
      return $count;
    }
  }
  return -1;
}

#==================================================
# check if thwo sets of numbers have any common part
# Params:
# number of elements in the first collection
# first collection (a list)
# second collection
sub get_intersect {
  my @params = @_;
  my ($count, $cf, $cs);
  my (@first, @second);

  for ($count = 1; $count<$params[0]+2; $count++) {
    $first[$count-1] = $params[$count];
  }
  for ($count=$params[0]+2; $count < $#params+1; $count++) {
    $second[$count-$params[0]-2] = $params[$count];
  }
  if ($DEBUG > 0) {
      &print_debug("First set: ".join(" ", (@first)),
		   "Second set: ".join(" ", (@second)));
  }
  for ($cf=0; $cf<$#first+1; $cf++) {
    for ($cs=0; $cs<$#second+1; $cs++) {
      if ($first[$cf] eq $second[$cs]) {
	if ($DEBUG > 0) {
	    &print_debug("Got intersect: $cf, $cs");
	}
	return ($cf, $cs);
      }
    }
  }
  return -1;
}

#============================================
# Get the DB table connection path from a field to field
# as a list of connection indexes from @datastruct table
# Params:
# keywords for fields to connect
# Returns:
# list of the numbers of the connections
sub connect_fields {
  if ($_[0] =~ m/FileCatalog/) {  shift @_;}

  my ($begkeyword, $endkeyword) = (@_);
  my ($begtable, $begfield, $endtable, $endfield, $blevel, $elevel);
  my ($ftable, $stable, $flevel, $slevel);
  my (@connections, $connum);


  &print_debug("Looking for connection between fields: $begkeyword, $endkeyword");


  $begtable = &get_table_name($begkeyword);
  $begfield = &get_field_name($begkeyword);
  $endtable = &get_table_name($endkeyword);
  $endfield = &get_field_name($endkeyword);
  $blevel   = &get_struct_level($begtable);
  $elevel   = &get_struct_level($endtable);
  if ($blevel > $elevel) {
    ($ftable, $stable, $flevel, $slevel) =
      ($begtable, $endtable, $blevel, $elevel)
    } else {
      ($stable, $ftable, $slevel, $flevel) =
	($begtable, $endtable, $blevel, $elevel)
      }
  if ($DEBUG > 0) {
      &print_debug("\tFirst: $ftable , $flevel",
		   "\tSecond: $stable , $slevel");
  }
  # Get to the fields on the same level in tree hierarchy
  while ($slevel < $flevel) {
    my ($ttable, $tlevel, $connum) = &get_lower_level($ftable);
    push(@connections, $connum);
    $flevel = $tlevel;
    $ftable = $ttable;
  }

  # If not the same table - look again
  if ( $stable ne $ftable) {
    &print_debug("Looking for downward connections");
    my @upconnections;
    # look upward in table structure
    while (($stable ne $ftable) && ($slevel != 1)) {
      my ($ttable, $tlevel, $connum) = &get_lower_level($stable);
      push(@upconnections, $connum);
      $slevel = $tlevel;
      $stable = $ttable;
      ($ttable, $tlevel, $connum) = &get_lower_level($ftable);
      push(@upconnections, $connum);
      $flevel = $tlevel;
      $ftable = $ttable;
    }
    push (@connections, @upconnections);
    if ( $stable ne $ftable) {
      &print_debug("Looking for upward connections");

      # Go up from the tree root searching for the link between tables
      my (%froads, %sroads);
      my (@flevelfields, @slevelfields);
      my ($findex, $sindex);

      @flevelfields = $ftable;
      @slevelfields = $stable;
      ($findex, $sindex) = &get_intersect($#flevelfields, @flevelfields, @slevelfields);
      while ($findex == -1) {
	if ($DEBUG > 0) {
	    &print_debug("First fields: ".join(" ",(@flevelfields)),
			 "Second fields: ".join(" ",(@slevelfields)));
	}
	my ($fcount, $scount);
	my (@flower, @slower);
	for ($fcount=0; $fcount<$#flevelfields+1; $fcount++) {
	  # Get all the fields that are connected to this one
	  # and one level up
	  (@flower) = &get_all_upper($flevelfields[$fcount]);
	  if ($DEBUG > 0) {
	      &print_debug("All first descendants: ".join(" ",(@flower)));
	  }
	  for (my $cflow = 0; $cflow <= $#flower; $cflow++) {
	      # Add a road going from the tree root to this field
	      if( defined($froads{$flower[$cflow]}) ){
		  $froads{$flower[$cflow]} = $froads{$flevelfields[$fcount]}." ".
		      &get_connection($flower[$cflow], $flevelfields[$fcount]);
	      } else {
		  $froads{$flower[$cflow]} = " ".
		      &get_connection($flower[$cflow], $flevelfields[$fcount]);
	      }
	      if ($DEBUG > 0) {
		  &print_debug("Added road $froads{$flower[$cflow]}");
	      }
	  }
	}
	for ($scount=0; $scount <= $#slevelfields ; $scount++) {
	  # Get all the fields that are connected to this one
	  # and one level up
	  (@slower) = &get_all_upper($slevelfields[$scount]);
	  if ($DEBUG > 0) {
	      &print_debug("All second descendants: ".join(" ",(@slower)));
	  }
	  for (my $cslow = 0; $cslow < $#slower+1; $cslow++) {
	    # Add a road going from the tree root to this field
	      if( defined($sroads{$slower[$cslow]}) ){
		  $sroads{$slower[$cslow]} = $sroads{$slevelfields[$scount]}." ".
		      &get_connection($slower[$cslow], $slevelfields[$scount]);
	      } else {
		  $sroads{$slower[$cslow]} = " ".
		      &get_connection($slower[$cslow], $slevelfields[$scount]);
	      }

	    if ($DEBUG > 0) {
		&print_debug("Added road $sroads{$slower[$cslow]}");
	    }
	  }
	}
	@flevelfields = @flower;
	@slevelfields = @slower;
	($findex, $sindex) = &get_intersect($#flevelfields, @flevelfields, @slevelfields);
      }
      push (@connections, $froads{$flevelfields[$findex]});
      push (@connections, $sroads{$slevelfields[$sindex]});
    }
  }
  return join(" ",@connections);
}



#============================================
# Runs the query to get the data from the database
# Params: list of keyowrds determining the data
# fields to get:
# Returns:
# list of rows matching the query build on the current context
# in each row the fileds are separated by ::
sub run_query_st {
    my (@tab)=&run_query(@_);
    if ( @tab ){
	return join("\n",@tab);
    } else {
	return undef;
    }
}

sub run_query {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  };

  # Do not run if not DB
  if( ! defined($DBH) ){
      &print_message("run_query","Not connected");
      return;
  }
  # Protect against bogus empty or undefined query
  if( ! defined($_[0]) ){
      &print_message("run_query()","method called without arguments");
      return;
  }
  # Treatment for ugly hack to get FileLocation id number from
  # within the module
  my $flkey;
  if ($_[0] eq "id"){
      $flkey = 1;
      shift @_;
  }

  my (@keywords)  = (@_);
  my (%functions);
  my ($dele,$i);
  my ($keyw,$count);
  my (%keyset,%xkeys);

  my $grouping = "";



  # Transfer into associative array for easier handling
  foreach (@keywords){  $keyset{$_} =$_ ;}


  # Little debugging of the table size. This information was
  # taken during the call to connect(). This information may
  # be used later to improve queries.
  #if($DEBUG > 0){
  #    &print_debug("By the way ...");
  #    foreach (keys(%rowcounts)){
  #        &print_debug("\t$_ count is ".$rowcounts{$_}."\n");
  #    }
  #}


  #+
  # Check the validity of the keywords
  #-
  $i = 0;
  for ($i = 0 ; $i <= $#keywords ; $i++){
      #First check if it is a request for an agregate value
      my ($aggr,$afun);

      $_ = $keywords[$i]; # too lazzy to change it all but to be cleaned
      $_ =~ y/ //d;

      foreach $afun (@aggregates){
	  ($aggr, $keyw) = $_ =~ m/($afun)\((.*)\)/;
	  last if (defined $aggr and defined $keyw);
      }
      if ( defined($keyw) ){
	  &print_debug("Found aggregate function |$aggr| on keyword |$keyw|");

	  # If it is - save the function, and store only the bare keyword
	  $functions{$keyw} = $aggr;
	  $_ = $keywords[$i]= $keyw;
	  $keyset{$keyw}    = 1;

	  if ( defined($ksimilar{$keyw}) ){
	      &print_message("run_query()",
			     "Nested agrregate function '$aggr' on ".
			     "aggregate keyword '$keyw' not supported and ignored.");
	  }
      }

      if ( ! defined ($keywrds{$_})){
	  if ( defined($obsolete{$_}) ){
	      &print_message("run_query()","Keyword $_ is obsolete ; use $obsolete{$_} instead");
	  } else {
	      &print_message("run_query()","Wrong keyword: $_");
	  }
	  return;
      } else {
	  $keyw = $_;
	  if ( defined($afun = $ksimilar{$keyw}) ){
	      &print_debug("Found aggregate option $keyw = $afun");
	      my ($func,$list) = split(";",$afun);

	      foreach my $el ( (split(" ",$list)) ){
		  if ( defined($keyset{$el}) ){
		      &print_message("run_query()","$el specified with $keyw containing it ...");
		      delete($keyset{$el});
		  }
		  #print "Adding  $el\n";
	      }
	      $xkeys{$keyw}  = $list;
	      $keyset{$keyw} = "_$func";
	  } else {
	      $afun = &get_table_name($keyw);
	      if ( &get_table_name($keyw) eq ""){
		  &die_message("runquery()",
			       "[$keyw] is a special condition or input keyword and does not return a value ");
	      }
	  }
      }
  }

  # Re-transfer clean list of keys. An associated array is NOT sorted
  # so we have to revert to a rather ugly (but fast) trick. We will
  # use the %keyset later
  my ($j,@temp,@items,@setkeys);

  for ($j=$i=0 ; $i <= $#keywords ; $i++){
      $keyw = $keywords[$i];
      &print_debug("... Checking $keyw");
      if ( defined($keyset{$keyw}) ){
	  if ( defined($xkeys{$keyw}) ){
	      push(@setkeys,$keyw);   # keep ordered track for later use
	      &print_debug("    Pushing in >> ".$xkeys{$keyw}." <<");
	      @items = split(" ",$xkeys{$keyw});
	      push(@temp,@items);
	      $keyset{$keyw} .= "($j,$#items";
	      &print_debug("    Defined as xkeys with function ".$keyset{$keyw});
	      #$j += ($#items+1);
	  } else {
	      delete($keyset{$keyw});
	      &print_debug("    Selected as a valid key");
	      push(@temp,$keyw);
	      #$j++;
	  }
	  $j++; # <-- not a bug
      }
  }
  @keywords = @temp;
  undef(%xkeys);
  undef(@items);
  undef(@temp);
  undef($j);
  &print_debug("Ordered list is [".join(" ",@keywords)."]");



  #
  # THIS NEXT BLOCK IS FLAKY AND SHOULD BE HANDLED WITH CARE. IT
  # WOULD PREVENT SINGLE TABLE QUERY WITH DEPENDENCE CONDITION ON
  # SIMPLE CODING ERROR.
  #
  # Introduced at version 1.14 . Need to be revisited.
  # Idea of this block was to eliminate parts of
  # where X.Id=Y.Id AND X.String=' '  and just use
  # where X.Id=value
  #
  # Was restored to a working version at version 1.31
  #
  # Do the constraint pre-check (for query optimization)
  # check if a given constraint produces a single record ID
  # If so remove the constraint and use this ID directly instead
  #
  my @constraint;
  my @from;
  my @connections;
  my %threaded;

  if(1==1){
      &print_debug("Scanning valuset ".join(",",keys %valuset));
      foreach $keyw (keys(%valuset)) {
	  my ($tabname) = &get_table_name($keyw);

	  # Check if the table name is one of the dictionary ones (or
	  # check that it is not a dictionary to be more precise)
	  if ( defined($FC::ISDICT{$tabname}) ){
	      my ($fieldname,$idname,$addedconstr) =
		  (&get_field_name($keyw),$tabname,"");

	      &print_debug("Table $tabname is a dictionary");
	      $idname = &IDize($idname);

	      # Find which table this one is connecting to
	      my $parent_tabname;
	      foreach my $el (@datastruct){
		  if (($el =~ m/$idname/) > 0){
		      # We found the right row - get the table name
		      my ($stab,$fld);
		      ($stab,$parent_tabname,$fld) = split(",",$el);
		  }
	      }


	      my $sqlquery = "SELECT $idname FROM $tabname WHERE ";

	      if ((($roundfields =~ m/$fieldname/) > 0) && (! defined $valuset{"noround"})){
		  #&print_debug("1 Inspecting [$roundfields] [$fieldname]");
		  my ($nround) = $roundfields =~ m/$fieldname,([0-9]*)/;
		  #&print_debug("1 Rounding to [$roundfields] [$fieldname] [$nround]");


		  $sqlquery .= "ROUND($fieldname, $nround) ".$operset{$keyw}." ";
		  if( $valuset{$keyw} =~ m/^\d+/){
		      $sqlquery .= $valuset{$keyw};
		  } else {
		      $sqlquery .= "'$valuset{$keyw}'";
		  }

		  #&print_debug("1 Rounding Query will be [$sqlquery]");

	      } elsif ($operset{$keyw} eq "~"){
		  $sqlquery .= &TreatLOps("$fieldname",
					  "LIKE",
					  $valuset{$keyw},
					  3);
		  #$sqlquery .= "$fieldname LIKE '%".$valuset{$keyw}."%'";

	      } elsif ($operset{$keyw} eq "!~"){
		  $sqlquery .= &TreatLOps("$fieldname",
					  "NOT LIKE",
					  $valuset{$keyw},
					  3);
		  #$sqlquery .= "$fieldname NOT LIKE '%".$valuset{$keyw}."%'";

	      } else {
		  $sqlquery .= &TreatLOps($fieldname,
					  $operset{$keyw},
					  $valuset{$keyw},
					  (&get_field_type($keyw) eq "text")?2:undef);

		  #if (&get_field_type($keyw) eq "text"){
		  #$sqlquery .= "$fieldname ".$operset{$keyw}." '".$valuset{$keyw}."'";
		  #} else {
		  #$sqlquery .= "$fieldname ".$operset{$keyw}." ".$valuset{$keyw};
		  #}
	      }
	      if ($DEBUG > 0) {  &print_debug("\tExecuting special: $sqlquery");}
	      $sth = $DBH->prepare($sqlquery);


	      if( ! $sth){
		  &print_debug("\tFileCatalog:: get id's : Failed to prepare [$sqlquery]");

	      } else {
		  my( $id );

		  if ( $sth->execute() ){
		      $sth->bind_columns( \$id );

		      if (( $sth->rows < 5) && ($sth->rows>0)) {
			  # Create a new constraint
			  $addedconstr = " ";
			  while ( $sth->fetch() ) {
			      if ($addedconstr ne " "){
				  $addedconstr .= " OR $parent_tabname.$idname = $id ";
			      } else {
				  $addedconstr .= " $parent_tabname.$idname = $id ";
			      }
			      &print_debug("\tAdded constraints now $addedconstr");
			  }
			  #$addedconstr .= " ) ";
			  if( index($addedconstr,"OR") != -1){
			      $addedconstr = " ($addedconstr)";
			  }


			  # Add a newly constructed keyword
			  push (@constraint, $addedconstr);

			  # Missing backward constraint for more-than-one table
			  # relation keyword. Adding it by hand for now (dirty)
			  # **** NEED TO BE CHANGED AND MADE AUTOMATIC AND USE LEVELS ***
			  # This does not happen if the field is specified
			  # as a returned keyword.
			  if ($parent_tabname eq "TriggerCompositions" ){
			      $addedconstr = " $parent_tabname.fileDataID = FileData.fileDataID";
			      push(@constraint,$addedconstr);
			  }



			  # Remove the condition - we already take care of it
			  &print_debug("\tDeleting $keyw=$valuset{$keyw}");
			  #delete $valuset{$keyw};
			  $threaded{$keyw}=1;

			  # But remember to add the the parent table
			  # push (@connections, (connect_fields($keywords[0], $keyw)));
			  push (@from, $parent_tabname);
		      }
		  }
		  $sth->finish();
	      }

	  } else {
	      &print_debug("Table $tabname is NOT a dictionary ...");

	      if ($tabname eq "CollisionTypes"){
		  # A special case - the collision type
		  my $fieldname   = &get_field_name($keyw);
		  my $idname      = $tabname;
		  my $addedconstr = "";

		  chop($idname);
		  $idname = lcfirst($idname);
		  $idname.="ID";

		  # Find which table this one is connecting to
		  my $parent_tabname;
		  my @retcollisions;
		  foreach my $el (@datastruct){
		      if (($el =~ m/$idname/) > 0){
			  # We found the right row - get the table name
			  my ($stab,$fld);
			  ($stab,$parent_tabname,$fld) = split(",",$el);
		      }
		  }

		  (@retcollisions) = &get_collision_collection($valuset{$keyw});
		  &print_debug("Returned ".join(" ",(@retcollisions))." $#retcollisions\n");
		  if (( $#retcollisions+1 < 5) && ($#retcollisions+1 > 0)) {
		      # Create a new constraint
		      $addedconstr = " ( ";
		      foreach my $collisionid (@retcollisions){
			  if ($addedconstr ne " ( "){
			      $addedconstr .= " OR $parent_tabname.$idname = $collisionid ";
			  } else {
			      $addedconstr .= " $parent_tabname.$idname = $collisionid ";
			  }
			  &print_debug("Added constraints now $addedconstr");
		      }
		      $addedconstr .= " ) ";
		      # Add a newly constructed keyword
		      push (@constraint, $addedconstr);
		      #
		      # Remove the condition - we already take care of it
		      #delete $valuset{$keyw};
		      $threaded{$keyw}=1;

		      # But remember to add the the parent table
		      #	    push (@connections, (connect_fields($keywords[0], $keyw)));
		      push (@from, $parent_tabname);
		  }
	      }
	  }
      }
  }

  #&print_debug("Pushing in FROM ".&get_table_name($keywords[0])." $#keywords ");
  push (@from, &get_table_name($keywords[0]));

  for ($count=1; $count<$#keywords+1; $count++) {
      #&print_debug("\t. Connecting $keywords[0] $keywords[$count] ".
      #&connect_fields($keywords[0], $keywords[$count]));
      push (@connections, (&connect_fields($keywords[0], $keywords[$count])));
      push (@from, &get_table_name($keywords[$count]));
  }

  # Also add to the FROM array the tables for each set keyword
  foreach my $key (keys %valuset){
      if (&get_table_name($key) ne ""){
	  #&print_debug("\t. Connect ".&connect_fields($keywords[0], $key)." From < ".
	  #&get_table_name($key));
	  push (@connections, (&connect_fields($keywords[0], $key)));
	  push (@from, &get_table_name($key));
      }
  }
  &print_debug("Connections to build the query (1): ".join(" ",@connections));


  if (defined $valuset{"simulation"}){
      push (@connections, (&connect_fields($keywords[0], "runnumber")));
      push (@from, "RunParams");
  }

  # Fill the table of connections
  my $connections = join(" ",(@connections));
  my @toquery;
  foreach my $el (sort (split(" ",$connections))) {
    if ((not $toquery[$#toquery]) || ($toquery[$#toquery] != $el)) {
      push (@toquery, $el);
    }
  }
  &print_debug("Connections to build the query (2): ".join(" ",@toquery));



  # Get the select fields
  my @select;
  foreach $keyw (@keywords) {
      &print_debug("Adding keyword: $keyw");
      if (defined $functions{$keyw}){
	  if ($functions{$keyw} eq "grp"){
	      if (($grouping =~ m/GROUP BY/) == 0){
		  $grouping .= " GROUP BY ".&get_table_name($keyw).".".&get_field_name($keyw)." ";
		  push (@select, &get_table_name($keyw).".".&get_field_name($keyw));
	      }

	  } elsif ($functions{$keyw} eq "orda"){
	      $grouping .= " ORDER BY ".&get_table_name($keyw).".".&get_field_name($keyw)." ASC ";
	      push (@select, &get_table_name($keyw).".".&get_field_name($keyw));

	  } elsif ($functions{$keyw} eq "ordd"){
	      $grouping .= " ORDER BY ".&get_table_name($keyw).".".&get_field_name($keyw)." DESC ";
	      push (@select, &get_table_name($keyw).".".&get_field_name($keyw));

	  } else {
	      push (@select, uc($functions{$keyw})."(".&get_table_name($keyw).".".&get_field_name($keyw).")");
	  }


      } elsif ($keyw eq "collision") {
	  my $tab = &get_table_name($keyw);
	  push (@select, "CONCAT( $tab.firstParticle, $tab.secondParticle, $tab.collisionEnergy )");


      } else {
	  push (@select, &get_table_name($keyw).".".&get_field_name($keyw));

      }
  }


  # Build the FROM and WHERE parts of the query
  # using thew connection list
  my $where="";
  &print_debug("Toquery table contains idx ".join("/",@toquery));
  foreach my $el (@toquery) {
      my ($mtable, $stable, $field, $level) = split(",",$datastruct[$el]);
      &print_debug("\tGot $mtable/$stable/$field/$level from $datastruct[$el]");
      if (($mtable eq "FileData") && ($stable eq "FileLocations")){
	  next;
      }
      &print_debug("\tTable $mtable is not one of FileData/FileLocations");
      push (@from, $mtable);
      push (@from, $stable);
      if (not $where) {
	  $where .= " $mtable.$field = $stable.$field ";
      } else {
	  $where .= " AND $mtable.$field = $stable.$field ";
      }
  }
  my $toquery = join(" ",(@from));
  &print_debug("Table list $toquery ; [$where]");



  # Get only the unique table names
  my @fromunique;
  foreach my $el (sort {$a cmp $b} split(" ",$toquery)) {
      &print_debug("Adding $el");
      if ((not $fromunique[$#fromunique]) || ($fromunique[$#fromunique] ne $el)) {
	  push (@fromunique, $el);
      }
  }

  # Extra debug line
  #if($DEBUG){
  #    &print_debug("--> order is --> ".join(" ",@select));
  #}

  # Get only the unique field names
  my @selectunique;
  #foreach (sort {$a cmp $b} (@select)) {
  foreach my $el ( @select ) {
      if ($DEBUG > 0) {
	  &print_debug("Adding $el");
      }
      if ((not $selectunique[$#selectunique]) || ($selectunique[$#selectunique] ne $el)) {
	  push (@selectunique, $el);
      }
  }



  # See if we have any constaint parameters
  foreach $keyw (keys(%valuset)) {
      if ( defined($threaded{$keyw})) { next;}
      my $fromlist = join(" " , (@fromunique));
      my $tabname = &get_table_name($keyw);



      if ((($fromlist =~ m/$tabname/) > 0) && ($tabname ne "")  ) {
	  my $fieldname = &get_field_name($keyw);
	  if ((($roundfields =~ m/$fieldname/) > 0) && (! defined $valuset{"noround"})){
	      my ($nround) = $roundfields =~ m/$fieldname,([0-9]*)/;
	      my ($roundv) = "ROUND($tabname.$fieldname, $nround) ".$operset{$keyw}." ";

	      if( $valuset{$keyw} =~ m/^\d+/){
		  $roundv .= $valuset{$keyw};
	      } else {
		  $roundv  .= "'$valuset{$keyw}'";
	      }
	      push(@constraint,$roundv);

	  }  elsif ($operset{$keyw} eq "~"){
	      push( @constraint, &TreatLOps("$tabname.$fieldname",
					    "LIKE",
					    $valuset{$keyw},
					    3));
	      #push( @constraint, "$tabname.$fieldname LIKE '%".$valuset{$keyw}."%'" );

	  }  elsif ($operset{$keyw} eq "!~"){
	      push( @constraint, &TreatLOps("$tabname.$fieldname",
					    "NOT LIKE",
					    $valuset{$keyw},
					    3));
	      #push( @constraint, "$tabname.$fieldname NOT LIKE '%".$valuset{$keyw}."%'" );

	  } else {
	      push(@constraint,&TreatLOps("$tabname.$fieldname",
					  $operset{$keyw},
					  $valuset{$keyw},
					  (&get_field_type($keyw) eq "text")?2:undef));
	  }
      }
  }


  #
  # This drastic change between simulation and real data prevents
  # the definition of a consistent logical name. Logical name must
  # depend on  $valuset{"simulation"}
  #
  if (defined $valuset{"simulation"}){
      if ($valuset{"simulation"} eq "1"){
	  push ( @constraint, "RunParams.simulationParamsID IS NOT NULL");
      } else {
	  push ( @constraint, "RunParams.simulationParamsID IS NULL");
      }
  }


  # Check to see if we are getting info from the FileLocations table
  # if so, and "all" keyword is not set - get only the records
  # with non-zero availability
  my $floc = join(" ",(@fromunique)) =~ m/FileLocations/;


  &print_debug("Checking for FileLocations ".(join(" ",@fromunique))." $floc");


  if ( $floc > 0 && defined($valuset{"all"}) ){
    if ( $valuset{"all"} == 0 && ! defined($valuset{"available"}) ){
	push ( @constraint, "FileLocations.availability > 0");
    }
  }

  my $constraint = join(" AND ",@constraint);

  # Build the actual query string
  my $sqlquery;
  $sqlquery = "SELECT ";
  if (! defined($valuset{"nounique"}) ){  $valuset{"nounique"} = 0;}
  if (! $valuset{"nounique"} ){           $sqlquery .= " DISTINCT ";}


  # An ugly hack to return FileLocationID from within the module
  if (((join(" ",(@fromunique)) =~ m/FileLocations/) > 0) && defined($flkey) ){
      $sqlquery .= " FileLocationID , ";
  }



  # Ugly hack to test the natural join
  # (but it's the only way to treat this special case)
  my $fdat = join(" ",(@fromunique)) =~ m/FileData/;
  &print_debug("Before the natural: ".join(" ",@fromunique));
  if (($floc > 0) && ($fdat >0)){
      my $i;
      #Find the FileLocations and FileData and delete it
      for ($i=0; $i <= $#fromunique; ){
	  #&print_debug("Considering splicing of $i $#fromunique [$fromunique[$i]]");
	  if ($fromunique[$i] eq "FileLocations"){
	      #&print_debug("Splicing FileLocations [$fromunique[$i]]");
	      splice(@fromunique, $i, 1);
	  } elsif ($fromunique[$i] eq "FileData"){
	      #&print_debug("Splicing FileData $#fromunique [$fromunique[$i]]");
	      splice(@fromunique, $i, 1);
	  } else {
	      $i++;
	  }
      }
      # Add a natural join instead
      push (@fromunique, "FileData NATURAL JOIN FileLocations");
      #push (@fromunique, "FileData JOIN FileLocations");
  }
  &print_debug("After the natural: ".join(" ",@fromunique));




  &print_debug("Selector ".join(" , ",@selectunique)." FROM ".join(" , ",(@fromunique)));




  $sqlquery .= join(" , ",(@selectunique))." FROM ".join(" , ",(@fromunique));

  # Small stupidity check
  if ( $#selectunique >= 1             &&
       ($sqlquery =~ /SUM\(.*\)/ ||
	$sqlquery =~ /MIN\(.*\)/ ||
	$sqlquery =~ /MAX\(.*\)/ ||
	$sqlquery =~ /COUNT\(.*\)/ )  &&
       $sqlquery !~ /GROUP BY/){
      $sqlquery =~ m/( .*\()(.*)/;
      &print_message("run_query()","$1) without GRP() will not lead to any result");
      return;
  }



  if ( $where ne "" ) {
      &print_debug("where clause [$where] constraint [$constraint]");
      $sqlquery .=" WHERE $where";
      if ($constraint ne "") {
	  $sqlquery .= " AND $constraint";
      }
  } elsif ($constraint ne "") {
      &print_debug("no where clause but constrained");
      $sqlquery .= " WHERE $constraint";
  }
  $sqlquery .= $grouping;




  #
  # Sort out if a limiting number of records or range
  # has been asked
  #
  my ($offset, $limit);
  if (defined $valuset{"startrecord"}){
      $offset = $valuset{"startrecord"};
  } else {
      $offset = 0;
  }
  if (defined $valuset{"limit"}){
      $limit = $valuset{"limit"};
      if($limit <= 0){
	  $limit = 1000000000;
      }
  } else {
      $limit = 100;
  }

  $sqlquery .= " LIMIT $offset, $limit";



  &print_debug("Using query: $sqlquery");

  my $sth;

  $sth = $DBH->prepare($sqlquery);
  if ( ! $sth ){
      &print_debug("FileCatalog::run_query : Failed to prepare [$sqlquery]");
      return;
  } else {
      my (@result,$res,$rescount);
      my (@cols);

      $count = 0;
      if ( $sth->execute() ){
	  while ( @cols = $sth->fetchrow_array() ) {
	      # if field is empty, fetchrow_array() returns undef()
	      # fix it by empty string instead.
	      for ($i=0 ; $i <= $#cols ; $i++){
		  if( ! defined($cols[$i]) ){ $cols[$i] = "";}
	      }


	      # We are not done ...
	      foreach $flkey (@setkeys){
		  $res = "\@cols = $keyset{$flkey}";
		  foreach my $el (@cols){  $res .= ",\"$el\"";}
		  $res .= ");";
		  &print_debug("eval() $res");
		  eval("\@cols = $res;");
	      }

	      $result[$count++] = join($delimeter,@cols);

	  }
	  $sth->finish();
      }
      return (@result);
  }
}


# 2 examples of eval() routines
sub _logical_name
{
    my($start,$num,@cols)=@_;
    my($lstr);

    $lstr    = $cols[$start]."&&".join("&&",splice(@cols,$start+1,$num));
    $cols[$start] = $lstr;
    @cols;
}

#sub _md5_name
#{
#    my($start,$num,@cols)=@_;
#    my($lstr,$md5);
#
#    $md5     =  Digest::MD5->new;
#    $md5->add($cols[$start]."&&".join("&&",splice(@cols,$start+1,$num)));
#    $lstr    = $md5->hexdigest();
#
#    $cols[$start] = $lstr;
#    @cols;
#}

sub _logical_path { return &_logical_name(@_);}
#sub _md5_path     { return &_md5_name(@_);}



#
# Routine to treat Logical, Bitwise, string vs integer
# values in one does it all.
# Flag is used as follow
#   1  get the $val 'as-is' i.e. do not check for string/number
#   2  explicit string value 'as-is'
#   3  explicit APPROXIMATE string matching
#
# Note thate && makes no sens whatsoever. Left for
# documentary / test purposes.
#
sub TreatLOps
{
    my($fldnam,$op,$ival,$flag)=@_;
    my(@Val,$val,$qq,$connect);

    $flag = 0 if ( ! defined($flag) );


    if ( index($ival,"||") != -1 ){
	@Val = split(/\|\|/,$ival);
	$connect = "OR";
    } elsif ( index($ival,"&&") != -1 ){
	@Val = split("&&",$ival);
	$connect = "AND";
    } else {
	push(@Val,$ival);
	$connect = "";
    }

    #print "$ival -> $#Val\n";

    # initialize
    foreach $val (@Val){
	#print "Start $val\n";
	if($flag == 0){
	    if ($val !~ m/^\d+/){
		$val = "'$val'";
	    }
	} elsif ($flag == 2){
	    $val = "'$val'";
	} elsif ($flag == 3){
	    $val = "'%$val%'";
	} else {
	    &die_message("TreatLOps","Internal error ; unknown flag $flag");
	}
	#print "Now   $val\n";

	if ( defined($qq) ){
	    $qq .= " $connect $fldnam $op $val";
	} else {
	    $qq = "$fldnam $op $val";
	}
    }

    # OR and AND should be re-grouped by ()
    if ($#Val > 0){
	$qq = "( $qq )";
    }

    $qq;
}



#============================================
# deletes the record that matches the current
# context. Actually calls run_query() so it is
# easier to see what we select
#
# First it deletes it from the file
# locations. If this makes the current file
# data have no location, it deletes the file
# data too.
#
# Returns:
#  1 if delete was successfull
#  0 if delete failed
#
# Argument : 1/0 doit or not, default doit=1
#
sub delete_records {
  # first delete the file location
  my @deletes;

  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  }
  if( ! defined($DBH) ){
      &print_message("delete_record","Not connected");
      return 0;
  }


  my $doit = shift @_;
  if( ! defined($doit) ){  $doit = 0;}

  # Since the context is defined, we will rely on run_query()
  # to return the list of records to be deleted. This will be
  # less programming support and easier check of what we will
  # be deleting btw (one can run a regular query first and delete
  # after ensuring the same things will be removed) ...
  my $delim = &get_delimeter();
  my @all   = &run_query("FileCatalog","flid","rfdid","path","filename");

  &set_delimeter("::");


  my($count,$cmd);
  my($sth,$sth2,$stq);
  my(@ids,$status,$rc);
  my($rows);

  $status = 0;
  foreach (@all){
      # We now have a pair flid/rfdid. Only flid can be deleted
      # rfdid is the logical grouping and may be associated with
      # more than one location.
      @ids = split("::",$_);

      $cmd = "DELETE LOW_PRIORITY FROM FileLocations WHERE fileLocationID=$ids[0]";
      $sth = $DBH->prepare( $cmd );

      if( $doit ){
	  if( $DELAY ){
	      $rc = 1;
	      push(@DCMD,$cmd);
	  } else {
	      $rc = $sth->execute();
	  }
      } else {
	  &print_message("delete_record","id=$ids[0] from FileLocation would be deleted");
	  $rc = 1;
      }

      if ( $rc ){
	  &print_debug("FileLocation ID=$ids[0] operation done. Checking FileData");

	  $cmd  = "SELECT FileLocations.fileLocationID from FileLocations, FileData ".
		  " WHERE FileLocations.fileDataID = FileData.fileDataID AND FileData.fileDataID = $ids[1] ";
	  $stq     = $DBH->prepare( $cmd );


	  if ( ! $stq->execute() ){
	      &print_debug("Execution failed [$cmd]");
	  }

	  $rows = $stq->rows;
	  $stq->finish();

	  if ($rows == 0 || ($DELAY && $rows == 1) ){
	      # This file data has no file "other" locations
	      $cmd  = "DELETE LOW_PRIORITY FROM FileData WHERE fileDataID = $ids[1]";
	      $sth2 = $DBH->prepare($cmd);

	      if ($doit){
		  if ( $DELAY ){
		      push(@DCMD,$cmd);
		  } else {
		      $sth2->execute();
		  }
		  &del_trigger_composition($ids[1],$doit);
	      } else {
		  &print_message("delete_record","id=$ids[1] from FileData would be deleted");
	      }
	      $sth2->finish();
	  }

      }
      $sth->finish();
  }
  &set_delimeter($delim);

  return @all;
}



#============================================
# Bootstraps a table - meaning it checks if all
# the records in this table are connected to some
# child table
#
# Params:
#   keyword - keword from the table, which is to be checked
#   dodelete - set to 1 to automaticaly delete the offending records
#
# Returns
#  List of records that are not connected or 0 if there were errors
#  or no unconnected records
#
# This routine is the top routine
#
sub bootstrap {
    if ($_[0] =~ m/FileCatalog/) {  shift @_;}

    if( ! defined($DBH) ){
	&print_message("bootstrap","Not connected");
	return 0;
    }

    my($keyword, $delete) = (@_);

    my($table);


    $table = &get_table_name($keyword);
    if ($table eq ""){ return 0; }
    &print_debug("bootstrap :: $keyword in table $table");

    # Now, pipe it to other routines
    if ($table eq "FileData" || $table eq "FileLocations"){
	return &bootstrap_data($keyword, $delete);

    } elsif ($table eq "TriggerWords" || $table eq "TriggerCompositions"){
	return &bootstrap_trgc($delete);

    } else {
	return &bootstrap_general($keyword, $table, $delete);
    }
}


#
# Bootstrap all no-special tables (dictionaries, FileData and
# FileLocations).
#
sub bootstrap_general
{
    my($keyword, $table, $delete) = @_;

    my($refcount);
    my($childtable, $linkfield);
    my($mtable, $ctable, $lfield);
    my($dcquery,$stq);
    my(@rows, $id, $el);
    my($dcdelete,$stfdd);

    # Check if this really is a dictionary table
    $refcount = 0;
    if ($table eq "RunParams"){
	$childtable = "FileData";
	$linkfield  = "RunParamID";
    } else {
	foreach $el (@datastruct){
	    #print "$el\n";
	    ($mtable, $ctable, $lfield) = split(",",$el);
	    if ($ctable eq $table){
		# This table is referencing another one - it is not a dictionary!
		&print_message("bootstrap","$table is not a dictionary table !");
		return 0;
	    }
	    if ($mtable eq $table){
		$childtable = $ctable;
		$linkfield = $lfield;
		$refcount++;
	    }
	}
	if ($refcount != 1){
	    # This table is not referenced by any other table or referenced
	    # by more than one - it is not a proper dictionary
	    &print_message("bootstrap","$table is not a dictionary table !");
	    return 0;
	}
    }


    $dcquery = "select $table.$linkfield FROM $table LEFT OUTER JOIN $childtable ON $table.$linkfield = $childtable.$linkfield WHERE $childtable.$linkfield IS NULL";

    $stq = $DBH->prepare( $dcquery );
    if( ! $stq ){
	&print_debug("FileCatalog::bootstrap : Failed to prepare [$dcquery]");
	return 0;
    }

    &print_debug("Running [$dcquery]");
    if ( $stq->execute() ){
	$stq->bind_columns( \$id );

	while ( $stq->fetch() ) { push ( @rows, $id );}
	if ($delete == 1){
	    # We do a bootstapping with delete
	    $dcdelete = "DELETE LOW_PRIORITY FROM $table WHERE $linkfield IN (".join(" , ",(@rows)).")";
	    if ( $DELAY ){
		push(@DCMD,$dcdelete);
	    } else {
		&print_debug("Executing $dcdelete");

		$stfdd = $DBH->prepare($dcdelete);
		if ($stfdd){
		    $stfdd->execute();
		    $stfdd->finish();
		} else {
		    &print_debug("FileCatalog::bootstrap : Failed to prepare [$dcdelete]",
				 " Record in $table will not be deleted");
		}
	    }
	}
	return (@rows);
    }
    return 0;
}

#
# Bootstraps TrigerCompositions and TriggerWords
# **** BOTH BLOCK CAN BE MERGED ****
#
sub bootstrap_trgc {
    my($delete) = (@_);

    my($tab1,$tab2,$field1,$field2);
    my($cmd1,$cmd2,$sth1,$sth2);
    my(@rows,@rows1,@rows2,$id);
    my($cmdd,$sthd);


    $tab1  = "TriggerCompositions";  $field1 = "fileDataID";
    $tab2  = "TriggerWords";         $field2 = "triggerWordID";

    $cmd1  = "SELECT $tab1.$field1 FROM $tab1 LEFT OUTER JOIN FileData ON $tab1.$field1 = FileData.$field1 WHERE FileData.$field1 IS NULL";
    $cmd2  = "SELECT $tab2.$field2 FROM $tab2 LEFT OUTER JOIN $tab1 ON $tab2.$field2 = $tab1.$field2 WHERE $tab1.$field2 IS NULL";


    $sth1 = $DBH->prepare( $cmd1 );
    $sth2 = $DBH->prepare( $cmd2 );

    if( ! $sth1 || ! $sth2 ){ &die_message("bootstrap_trgc"," Failed to prepare statements");}



    #
    # Run the first sth on $tab1 since it may leave further
    # holes sth2 would pick up.
    #
    &print_debug("Running [$sth1]");
    if ( ! $sth1->execute() ){  &die_message("bootstrap_trgc","Execute 1 failed");}

    $sth1->bind_columns( \$id );

    while ( $sth1->fetch() ) {  push ( @rows1, $id );}

    if ($delete == 1){
	$cmdd = "DELETE LOW_PRIORITY FROM $tab1 WHERE $field1 IN (".join(" , ",(@rows1)).")";
	if ( $DELAY ){
	    push(@DCMD,$cmdd);
	} else {
	    &print_debug("Executing $cmdd");
	    $sthd = $DBH->prepare($cmdd);
	    if ($sthd){
		$sthd->execute();
		$sthd->finish();
	    } else {
		&print_debug("FileCatalog::bootstrap_data : Failed to prepare [$cmdd]",
			     " Records in $tab1 will not be deleted");
	    }
	}
    }
    $sth1->finish();



    &print_debug("Running [$sth2]");
    if ( ! $sth2->execute() ){  &die_message("bootstrap_trgc","Execute 2 failed");}

    $sth2->bind_columns( \$id );

    while ( $sth2->fetch() ) {  push ( @rows2, $id );}

    if ($delete == 1){
	$cmdd = "DELETE LOW_PRIORITY FROM $tab2 WHERE $field2 IN (".join(" , ",(@rows2)).")";
	if ( $DELAY ){
	    push(@DCMD,$cmdd);
	} else {
	    &print_debug("Executing $cmdd");
	    $sthd = $DBH->prepare($cmdd);
	    if ($sthd){
		$sthd->execute();
		$sthd->finish();
	    } else {
		&print_debug("FileCatalog::bootstrap_data : Failed to prepare [$cmdd]",
			     " Records in $tab2 will not be deleted");
	    }
	}
    }
    $sth2->finish();

    # Return value
    if ( $#rows1 != -1){ foreach $id (@rows1){ push(@rows,"TC-$id");}}
    if ( $#rows2 != -1){ foreach $id (@rows2){ push(@rows,"TW-$id");}}

    if ( $#rows != -1){ return @rows; }
    else {              return 0;}

}



sub bootstrap_data
{
    if ($_[0] =~ m/FileCatalog/) { shift @_;}

    if( ! defined($DBH) ){
	&print_message("bootstrap_data","Not connected");
	return 0;
    }

    my ($keyword, $delete) = (@_);
    my $table = &get_table_name($keyword);

    if (($table ne "FileData") && ($table ne "FileLocations")){
	&print_message("bootstrap_data","Wrong usage of routine. Use bootstrap()");
	return 0;
    }

  my $dcquery;
  if ($table eq "FileData")
    {
      $dcquery = "select FileData.fileDataID FROM FileData LEFT OUTER JOIN FileLocations ON FileData.fileDataID = FileLocations.fileDataID WHERE FileLocations.fileLocationID IS NULL";
    }
  elsif ($table eq "FileLocations")
    {
      $dcquery = "select FileLocations.fileLocationID FROM FileLocations LEFT OUTER JOIN FileData ON FileData.fileDataID = FileLocations.fileDataID WHERE FileData.fileDataID IS NULL";
    }

  my $stq;
  $stq = $DBH->prepare( $dcquery );
  if( ! $stq ){
      &print_debug("FileCatalog::bootstrap_data : Failed to prepare [$dcquery]");
      return 0;
  }
  &print_debug("Running [$dcquery]");

  if ( $stq->execute() ){
      my @rows;
      my( $id );
      $stq->bind_columns( \$id );

      while ( $stq->fetch() ) {
	push ( @rows, $id );
      }
      if ($delete == 1)
      {
	  # We do a bootstapping with delete
	  my $dcdelete;
	  if ($table eq "FileData")
	  {
	      $dcdelete = "DELETE LOW_PRIORITY FROM $table WHERE $table.fileDataID IN (".join(" , ",(@rows)).")";
	  }
	  elsif ($table eq "FileLocations")
	  {
	      $dcdelete = "DELETE LOW_PRIORITY FROM $table WHERE $table.fileLocationID IN (".join(" , ",(@rows)).")";
	  }
	  if ( $DELAY ){
	      push(@DCMD,$dcdelete);
	  } else {
	      if ($DEBUG > 0) { &print_debug("Executing $dcdelete"); }
	      my $stfdd = $DBH->prepare($dcdelete);
	      if ($stfdd){
		  $stfdd->execute();
		  $stfdd->finish();
	      } else {
		  &print_debug("FileCatalog::bootstrap_data : Failed to prepare [$dcdelete]",
			       " Records in $table will not be deleted");
	      }
	  }
      }
      $stq->finish();
      return (@rows);
    }
  $stq->finish();
  return 0;
}



#============================================
# Updates the field coresponding to a given keyword
# with a new value, replaces the value in the current
# context.The value of the keyword to be modified,
# MUST appear in a previous set_context() statement.
# This is a limitation which has been chosen in
# order to also treat changing values in dictionaries.
#
# Params:
# keyword - the keyword which data is to be updated
# value   - new value that should be put into the database
#           instead of the current one
# doit    - an extra non-mandatory value 0/1
#
# Returns:
# 1 if update was successfull
# 0 if delete failed
sub update_record {
  if ($_[0] =~ m/FileCatalog/) {
    my $self = shift;
  }
  if( ! defined($DBH) ){
      &print_message("update_record","Not connected");
      return 0;
  }

  my ($ukeyword, $newvalue, $doit) = (@_);
  my @updates;
  my $xcond;

  my $utable = &get_table_name($ukeyword);
  my $ufield = &get_field_name($ukeyword);

  # There is bunch of exclusion preventing catastrophe
  # ALL Id's associated to their main tables should be
  # eliminated
  if ( $ufield =~ m/(.*)(ID)/ ){
      my $idnm=$1;
      if ( index(lc($utable),lc($idnm)) != -1 ){
	  &print_message("update_record","Changing $ufield in $utable not allowed\n");
	  # btw, if you do this, you are screwed big time ... because you
	  # lose the cross table associations.
	  return 0;
      }
  }


  if( ! defined($doit) ){  $doit = 1;}

  foreach my $key (keys %keywrds){
      my $field = &get_field_name($key);
      my $table = &get_table_name($key);

      # grab keywords which belongs to the same table
      # This will be used as the selection WHERE clause.
      # The ufield is excluded because we use it by default
      # in the SET xxx= WHERE xxx= as an extra MANDATORY
      # clause.
      if (($table eq $utable) && ($field ne $ufield)){
	  if (defined($valuset{$key})){
	      if (&get_field_type($key) eq "text"){
		  push (@updates, "$table.$field = '".$valuset{$key}."'");
	      } else {
		  push (@updates, "$table.$field = ".$valuset{$key});
	      }
	  }
      } else {
	  # Otherkeywords may make the context more specific if there is
	  # a relation. The only relation we will support if through
	  # the fdid and tables containing this field.
	  # **** NEED TO WRITE A ROUTINE SORTING OUT THE RELATION ****
	  if ( $key eq "fdid" &&
	      ( $utable eq "TriggerCompositions" ||
		$utable eq "FileLocations") ){
	      if ( defined($valuset{$key}) ){
		  #print "Found fdid = $valuset{$key}\n";
		  $xcond = " $utable.fileDataID = $valuset{$key}" if ( ! defined($xcond) );
	      }
	  }

      }
  }
  if ( defined($xcond) ){ push(@updates,$xcond);}
  my $whereclause="";
  $whereclause = join(" AND ",(@updates)) if ( $#updates != -1);



  if ($utable eq ""){
      &print_debug("ERROR: $ukeyword does not have an associated table",
		   "Cannot update");
      return 0;
  }

  # Prevent disaster by checking this out
  my ($qupdate,$qselect);
  if (&get_field_type($ukeyword) eq "text"){
      $qselect = "SELECT $utable.$ufield FROM $utable WHERE $utable.$ufield = '$newvalue'";
      $qupdate = "UPDATE LOW_PRIORITY $utable SET $utable.$ufield = '$newvalue' ";
      if( defined($valuset{$ukeyword}) ){
	  $qupdate .= " WHERE $utable.$ufield = '$valuset{$ukeyword}'";
      } else {
	  &print_message("update_record",
			 "$ukeyword not set with an initial value (giving up)");
	  return 0;
      }

  } else {
      $qselect = "SELECT $utable.$ufield FROM $utable WHERE $utable.$ufield = $newvalue";
      $qupdate = "UPDATE LOW_PRIORITY $utable SET $utable.$ufield = $newvalue ";
      if( defined($valuset{$ukeyword}) ){
	  $qupdate .= " WHERE $utable.$ufield = $valuset{$ukeyword}";
      } else {
	  &print_message("update_record",
			 "$ukeyword not set with an initial value (giving up)");
	  return 0;
      }

  }


  if ($whereclause ne ""){
      $qselect .= " AND $whereclause";
      $qupdate .= " AND $whereclause";
  }

  &print_debug("Executing update: $qupdate\n");


  # We may be missing a 'WHERE'
  # This is a provision in case we decide to allow
  # updating records without having the keyword in.
  # In principle, we can't since this routine also
  # updates dictionaries.
  if ( $qupdate !~ /WHERE/){
      $qupdate =~ s/AND//;  # strip one AND
      $qupdate = "WHERE ".$qupdate;
  }


  if( ! $doit ){
      &print_message("update_record","$qupdate");
      return 0;
  } else {
      my ($sth,$retv,$val);

      $retv=0;

      # The warning is displayed for information only and mainly
      # for dictionaries where changing values may be a real
      # disaster.
      if ($utable ne "FileLocations"){
	  $sth = $DBH->prepare($qselect);
	  if ($sth){
	      if ( $sth->execute() ){
		  $sth->bind_columns(\$val);
		  if ( $sth->fetch() ){
		      &print_message("update_record",
				     "Warning ! $ukeyword=$newvalue exists ".
				     "in table $utable");
		  }
	      }
	      $sth->finish();
	  }
      }

      if($DELAY){
	  # Delayed mode
	  push(@DCMD,$qupdate );
	  return 1;
      } else {
	  $sth = $DBH->prepare( $qupdate );
	  if (!$sth){
	      &print_debug("FileCatalog::update_record : Failed to prepare [$qupdate]");
	  } else {
	      if ( $sth->execute() ){  $retv = 1;}
	      $sth->finish();
	  }


      }
      return $retv;
  }
}

#============================================
#
# The 3 following method are argument-less.
#
# Set operation in delay mode.
#
sub set_delayed
{
    if ($_[0] =~ m/FileCatalog/) {
	my $self = shift;
    }
    $DELAY = 1;
}



#
# Quick and dirty stack command execution
# Dirty because a do() statement has only little
# handle on what can be done ... whatever is in the
# stack may succeed or not without error bootstraping.
# However, this will be fine/adequate in any major record
# update.
# Possible argument {0|1} (default 0)
#   1 means it will display a message  time/#of updates
#
sub flush_delayed
{
    if ($_[0] =~ m/FileCatalog/) {
	my $self = shift;
    }
    my($flag)=@_;
    my($cmd,$sth);

    if( ! defined($flag) ){ $flag = 0;}
    if( ! $DBH){  return;}

    if( $flag){
	&print_message("flush_delayed","Flushing ".($#DCMD+1)." commands on ".localtime());
    }

    foreach $cmd (@DCMD){
	&print_debug("Executing $cmd");
	if ( ! $DBH->do($cmd) ){
	    &print_message("flush_delayed","Failed $cmd");
	}
    }
    undef(@DCMD);
    $DELAY = 0;
}


sub print_delayed
{
    if ($_[0] =~ m/FileCatalog/) { my $self = shift;}

    my($flag)=@_;
    my($cmd);

    if( $flag){
	&print_message("print_delayed","Printing ".($#DCMD+1)." commands on ".localtime());
    }

    foreach $cmd (@DCMD){
	# ready for a piping to cmdline mysql
	print "$cmd;\n";
    }
    undef(@DCMD);
    $DELAY = 0;
}


#============================================
# Updates the fields in FileLocations table - mainly
# used for updating availability and persistency
#
# Params:
# keyword - the keyword which data is to be updated
# value   - new value that should be put into the database
#           instead of the current one
# doit    - do it or not, default is 1
#
sub update_location {
  if ($_[0] =~ m/FileCatalog/) { my $self = shift;}

  if( ! defined($DBH) ){
      &print_message("update_location","Not connected");
      return 0;
  }


  my @updates;

  my ($ukeyword, $newvalue, $doit, $delete) = (@_);

  my $mtable;
  my $utable = &get_table_name($ukeyword);
  my $ufield = &get_field_name($ukeyword);


  # Change this out to dictionary search and revert keyword
  # application to the location table for tables immediatly
  # related to the FileLocations table.
  if ( defined($FC::FLRELATED{$utable}) ){
      $mtable = "FileLocations";
  } else {
      $mtable = $utable;
  }

  if ( $mtable ne "FileLocations"){
      &print_message("update_location","Improper method called for keyword $ukeyword");
      return 0;
  }



  my @files;

  my $delim;

  if( ! defined($doit) ){    $doit    = 1;}
  if( ! defined($delete) ){  $delete  = 0;}

  $delim  = &get_delimeter();

  # Get the list of the files to be updated
  # Note that this is additional to what has been
  # required in a call to set_context() so we
  # can restrict to any field in addition of the id.
  # 'id' is for internal use only and is NOT an
  # external keyword.
  &set_delimeter("::");
  &set_context("all=1");                  # all availability
  &set_context("nounique=1");             # do not run with DISTINCT

  @files = &run_query("id","available");

  # Bring back the previous delimeter
  &set_delimeter($delim);

  #delete($valuset{"path"});


  if ($#files == -1){
      &print_message("update_location","The context did not return any candidate");
      return 0;
  }



  foreach my $key (keys %keywrds){
      my $field = &get_field_name($key);
      my $table = &get_table_name($key);

      # grab keywords which belongs to the same table
      # This will be used as the selection WHERE clause.
      # The ufield is excluded because we use it by default
      # in the SET xxx= WHERE xxx= as an extra MANDATORY
      # clause.
      #print "+ $table + \n";
      if (($table eq $mtable) && ($field ne $ufield)){
	  if (defined($valuset{$key})){
	      if (&get_field_type($key) eq "text"){
		  push (@updates, "$field = '".$valuset{$key}."'");
	      } else {
		  push (@updates, "$field = ".$valuset{$key});
	      }
	  }
      }
  }
  my $whereclause = join(" AND ",(@updates));

  if ($utable eq ""){
      &print_debug("ERROR: $ukeyword does not have an associated table",
		   "Cannot update");
      return 0;
  }

  #
  # Sort out sth
  #
  my($qupdate,$qselect,$qdelete);
  my($sth1,$sth2,$sth3);

  if ( defined($FC::FLRELATED{$utable}) ){
      # Patch ... The above logic is true only for
      # tables like FileData/FileLocation but not true for others
      my $uid    = &get_id_from_dictionary($utable,$ufield,$newvalue);
      $ukeyword  = &IDize($utable);
      #$qselect = "SELECT $ukeyword FROM $mtable WHERE $ukeyword=$uid";
      $qdelete = "DELETE LOW_PRIORITY FROM $mtable " ;
      $qupdate = "UPDATE LOW_PRIORITY $mtable SET $ukeyword=$uid ";
      
      if ($whereclause ne ""){
	  $qupdate .= " AND $whereclause";
      }

      # THOSE ONLY UPDATES VALUES
  } elsif (&get_field_type($ukeyword) eq "text"){
      #$qselect = "SELECT $ukeyword FROM $mtable WHERE $ufield='$newvalue'";
      $qdelete = "DELETE LOW_PRIORITY FROM $mtable" ;
      $qupdate = "UPDATE LOW_PRIORITY $mtable SET $ufield = '$newvalue' ";
      if( defined($valuset{$ukeyword}) ){
	  $qupdate .= " WHERE $ufield = '$valuset{$ukeyword}'";
      } else {
	  #&print_message("update_location","$ukeyword ($ufield) not set with an initial value");
	  #return 0;
      }
  } else {
      #$qselect = "SELECT $ufield FROM $mtable WHERE $ufield=$newvalue" ;
      $qdelete = "DELETE LOW_PRIORITY FROM $mtable" ;
      $qupdate = "UPDATE LOW_PRIORITY $mtable SET $ufield = $newvalue ";
      if( defined($valuset{$ukeyword}) ){
	  $qupdate .= " WHERE $ufield = $valuset{$ukeyword}";
      } else {
	  #&print_message("update_location","$ukeyword ($ufield) not set with an initial value");
	  #return 0;
      }
  }
  if ($qupdate =~ /WHERE/){
      $qupdate .= " AND fileLocationID = ?";
  } else {
      $qupdate .= " WHERE fileLocationID = ?";
  }
  #$qselect .= " AND fileLocationID = ?";
  $qdelete .= " WHERE fileLocationID = ?";


  #$sth1 = $DBH->prepare( $qselect );
  $sth2 = $DBH->prepare( $qdelete );
  $sth3 = $DBH->prepare( $qupdate );
  #if ( ! $sth1 || ! $sth2 || ! $sth3){
  if (  ! $sth3){
      #$sth1->finish() if ($sth1);
      $sth2->finish() if ($sth2);
      $sth3->finish() if ($sth3);
      &print_debug("update_location : Failed to prepare [$qupdate] [$qselect] [$qdelete]");
      return 0;
  }
	
  #
  # Now, loop over records with an already prepared sth
  #
  my($tmp,$failed,$count);
  
  $failed = $count = 0;
  &print_debug("Ready to scan filelist now ".($#files+1)."\n");

  foreach my $line (@files) {
      &print_debug("Returned line ($ukeyword): $line\n");

      my($flid, $trash) = split("::",$line);

      #&print_debug("Executing update: $qupdate");

      if (! $doit){
	  #$tmp = $qselect; $tmp =~ s/\?/$flid/;  &print_message("update_location","$tmp");
	  $tmp = $qupdate; $tmp =~ s/\?/$flid/;  &print_message("update_location","$tmp");
	  $tmp = $qdelete; $tmp =~ s/\?/$flid/;  &print_message("update_location","($tmp)");

      } else {
	  if( $DELAY){
	      # Delay mode
	      $tmp = $qupdate; $tmp =~ s/\?/$flid/;  push(@DCMD,"$tmp");
	      #$tmp = $qdelete; $tmp =~ s/\?/$flid/;  push(@DCMD,"$tmp");
	      $count++;
	  } else {
	      #if ( $sth1->execute($flid) ){
	      #	  my(@all);
	      #	  if ( @all = $sth1->fetchrow() ){  
	      #	      &print_message("update_location","Deleting similar records for $flid");
	      #	      $sth2->execute($flid); 
	      #	  }
	      #}
	      if ( $sth3->execute($flid) ){
		  &print_debug("Update of $mtable succeeded");
		  $count++;
	      } else {
		  $failed++;
		  if ($DBH->err == 1062){
		      # Duplicate entry being replaced
		      #&print_debug("Duplicate entry is being replaced");
		      if ( $delete){
			  if ( $sth2->execute($flid) ){
			      &print_message("update_location",
					     "selected flid=$flid deleted as update would ".
					     "lead to duplicate key)");
			      # This counts as a success because it moves records
			      # as well.
			      $count++;
			  }
		      } else {
			  &print_message("update_location",
					 "selected flid=$flid cannot be updated ".
					 "(would lead to duplicate)");
		      }
		  } else {
		      &print_debug("Update of $mtable failed ".$DBH->err." ".$DBH->errstr);
		  }
	      }
	  }
      }
      
  }
  #$sth1->finish();
  $sth2->finish();
  $sth3->finish();

  return ($count);
}

#============================================
# Returns the context value assigned to the current field
# Params:
# keyowrd - which context keyword to get
# Return:
# context value for keyword
sub get_context {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  }

  my ($param) = @_;
  return $valuset{$param};
}

#============================================
#
# Set default value if necessary. Returns it
#  Arg1   the variable to set (passed by value)
#  Arg2   the default value
#  Arg3   a flag : 1  upperCase
#                  2  lowercase
#
sub get_value
{
    my($var,$dval,$flag)=@_;

    # If undef, use default value
    if ( ! defined($var) ){ $var = $dval;}

    # If null, use default as well. Do not allow \s+ or "" in ddb (sorry)
    if ( $var =~ m/^\s*$/){ $var = $dval;}

    # Now treat special cases
    if($flag == 1){      $var = uc($var);}
    elsif($flag == 2){   $var = lc($var);}

    # Return that value
    $var;
}


#============================================
sub debug_on
{
    if ($_[0] =~ m/FileCatalog/) {  shift @_;}

    my($mode)=@_;

    #print "Debug is $mode\n";
    $DEBUG  = 1;
    if( defined($mode) ){
	if(    $mode =~ m/html/i){ $DEBUG = 2;}  # html, display as text
	elsif( $mode =~ m/cmth/i){ $DEBUG = 3;}  # comments in html
	else {                     $DEBUG = 1;}  # revert to default, plain text
    }
}

#============================================
sub debug_off {
    $DEBUG = 0;
}

#============================================

sub print_debug
{
    my(@lines)=@_;
    my($line);

    return if ($DEBUG==0);

    foreach $line (@lines){
	chomp($line);
	if($DEBUG==2){
	    print "<tt>$line<tt><br>\n";
	} elsif($DEBUG==3) {
	    print "<!-- $line -->\n";
	} else {
	    print "FC-DBG :: $line\n";
	}
    }
}

sub set_silent
{
    if ($_[0] =~ m/FileCatalog/) {
	shift @_;
    }
    my($mode)=@_;

    $SILENT = $mode & 1;
    $SILENT;
}


#============================================

sub new_value
{
    my($routine,$id,$val,$table)=@_;

    &print_message($routine,"Inserting new value [$val] in $table") if ($id != 0);
    $FC::KNOWNV{$table." ".$val} = $id;
}

sub cached_value
{
    my($tab,$val)=@_;
    my($rv);

    if ( defined($rv = $FC::KNOWNV{$tab." ".$val}) ){
	return $rv;
    } else {
	return 0;
    }
}


#============================================

sub die_message
{
    &print_message(@_);
    die "\n";
}

sub print_message
{
    my($routine,@lines)=@_;
    my($line);

    if ( $SILENT ){ return;}
    foreach $line (@lines){
	chomp($line);
	printf "FileCatalog :: %15.15s : %s\n",$routine,$line;
    }
    return;
}


#============================================

sub destroy {
  my $self = shift;
  &clear_context();
  if ( ! defined($DBH) ) { return 0;}

  if ( $DBH){
      if ( $DBH->disconnect ) {
	  return 1;
      } else {
	  return 0;
      }
  } else {
      return 0;
  }
}

#============================================
1;

