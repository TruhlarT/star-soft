# FileCat.pm
#
# Written by Adam Kisiel, November-December 2001
#
# Methods of class FileCatalog:
#
#        ->new           : create new object FileCatalog
#        ->connect       : connect to the database FilaCatalog
#        ->destroy       : destroy object and disconnect database FileCatalog
#        ->set_context() : set one of the context keywords to the given operator and value
#        ->get_context() : get a context value connected to a given keyword
#        ->clear_context(): clear/reset the context
#        ->get_keyword_list() : get the list of valid keywords
#        ->get_delimeter() : get the current delimiting string
#        ->set_delimeter() : set the current delimiting string
#
# the following methods require connect to dbtable and are meant to be used outside the module
#
#        -> check_ID_for_params() : returns the database row ID from the dictionary table
#                          connected to this keyword
#        -> insert_dictionary_value() : inserts the value from the context into the dictionary table
#        -> insert_detector_configuration() : inserts the detector configuration from current context
#        -> get_current_detector_configuration() : gets the ID of a detector configuration
#           described by the current context
#        -> insert_run_param_info() : insert the run param record taking data from the current context
#        -> get_current_run_param() : get the ID of a run params corresponding to the current context
#        -> insert_file_data() : inserts file data record taking data from the current context
#        -> get_current_file_data() : gets the ID of a file data corresponding to the current context
#        -> insert_simulation_params() : insert the simulation parameters taking data from the
#           current context
#        -> get_current_simulation_params : gets the ID of a simulation params corresponding
#           to the current contex
#        -> insert_file_location() : insert the file location data taking data from the
#           current context
#        -> run_query()   : get entries from dbtable FileCatalog according to query string
#           defined by set_context you also give a list of fields to select form
#        -> delete_record() : deletes the current file location. If it finds that the current
#           file data has no file locations left, it deletes it too
#        -> update_record() : modifies the data in the database. The field corresponding
#           to the given keyword changes it value from the one in the current context to the
#           one specified as an argument
#        -> bootstrap() : database maintenance procedure. Looks at the dictionary table and
#           find all the records that are not referenced by the child table. It offers an option
#           of deleting this records.
#


package FileCatalog;

use vars qw($VERSION);
$VERSION   =   0.01;

use DBI;
use strict;

# define to print debug information
my $DEBUG     = 0;

# db information
my $dbname    =   "FileCatalog";
my $dbhost    =   "duvall.star.bnl.gov";
my $dbuser    =   "FC_user";
my $dbsource  =   "DBI:mysql:$dbname:$dbhost";
my $DBH;
my $sth;

# hash of keywords
my %keywrds;
# $keys{keyword} meaning of the parts of the field:
# 1 - parameter name as entered by the user
# 2 - field name in the database
# 3 - table name in the database for the given field
# 4 - critical for data insertion into the specified table
# 5 - type of the field (text,num,date)
# 6 - not used
# 7 - not used
# only the keywords in this table are accepted in set_context sub

$keywrds{"filetype"      }    =   "fileTypeName"              .",FileTypes"              .",1" .",text" .",0" .",1";
$keywrds{"extension"     }    =   "fileTypeExtension"         .",FileTypes"              .",1" .",text" .",0" .",1";
$keywrds{"storage"       }    =   "storageTypeName"           .",StorageTypes"           .",1" .",text" .",0" .",1";
$keywrds{"site"          }    =   "storageSiteName"           .",StorageSites"           .",1" .",text" .",0" .",1";
$keywrds{"production"    }    =   "productionTag"             .",ProductionConditions"   .",1" .",text" .",0" .",1";
$keywrds{"prodcomment"   }    =   "productionComments"        .",ProductionConditions"   .",1" .",text" .",0" .",1";
$keywrds{"library"       }    =   "libraryVersion"            .",ProductionConditions"   .",1" .",text" .",0" .",1";
$keywrds{"triggername"   }    =   "triggerName"               .",TriggerWords"           .",1" .",text" .",0" .",1";
$keywrds{"triggerword"   }    =   "triggerWord"               .",TriggerWords"           .",1" .",text" .",0" .",1";
$keywrds{"triggersetup"  }    =   "triggerSetupName"          .",TriggerSetups"          .",1" .",text" .",0" .",1";
$keywrds{"runtype"       }    =   "runTypeName"               .",RunTypes"               .",1" .",text" .",0" .",1";
$keywrds{"configuration" }    =   "detectorConfigurationName" .",DetectorConfigurations" .",1" .",text" .",0" .",1";
$keywrds{"geometry"      }    =   "detectorConfigurationName" .",DetectorConfigurations" .",0" .",text" .",0" .",1";
$keywrds{"runnumber"     }    =   "runNumber"                 .",RunParams"              .",1" .",num"  .",0" .",1";
$keywrds{"runcomments"   }    =   "runComments"               .",RunParams"              .",0" .",text" .",0" .",1";
$keywrds{"collision"     }    =   "collisionEnergy"           .",CollisionTypes"         .",1" .",text" .",0" .",1";
$keywrds{"datetaken"     }    =   "dataTakingStart"           .",RunParams"              .",0" .",date" .",0" .",1";
$keywrds{"magscale"      }    =   "magFieldScale"             .",RunParams"              .",1" .",text" .",0" .",1";
$keywrds{"magvalue"      }    =   "magFieldValue"             .",RunParams"              .",0" .",num"  .",0" .",1";
$keywrds{"filename"      }    =   "filename"                  .",FileData"               .",1" .",text" .",0" .",1";
$keywrds{"size"          }    =   "size"                      .",FileData"               .",1" .",num"  .",0" .",1";
$keywrds{"fileseq"       }    =   "fileSeq"                   .",FileData"               .",1" .",num"  .",0" .",1";
$keywrds{"filecomment"   }    =   "fileDataComments"          .",FileData"               .",0" .",text" .",0" .",1";
$keywrds{"owner"         }    =   "owner"                     .",FileLocations"          .",0" .",text" .",0" .",1";
$keywrds{"protection"    }    =   "protection"                .",FileLocations"          .",0" .",text" .",0" .",1";
$keywrds{"node"          }    =   "nodeName"                  .",FileLocations"          .",0" .",text" .",0" .",1";
$keywrds{"available"     }    =   "availability"              .",FileLocations"          .",0" .",text" .",0" .",1";
$keywrds{"persistent"    }    =   "persistent"                .",FileLocations"          .",0" .",text" .",0" .",1";
$keywrds{"sanity"        }    =   "sanity"                    .",FileLocations"          .",0" .",num"  .",0" .",1";
$keywrds{"createtime"    }    =   "createTime"                .",FileLocations"          .",0" .",date" .",0" .",1";
$keywrds{"inserttime"    }    =   "insertTime"                .",FileLocations"          .",0" .",date" .",0" .",1";
$keywrds{"path"          }    =   "filePath"                  .",FileLocations"          .",1" .",text" .",0" .",1";
$keywrds{"simcomment"    }    =   "simulationParamComments"   .",SimulationParams"       .",0" .",text" .",0" .",1";
$keywrds{"generator"     }    =   "eventGeneratorName"        .",EventGenerators"        .",1" .",text" .",0" .",1";
$keywrds{"genversion"    }    =   "eventGeneratorVersion"     .",EventGenerators"        .",1" .",text" .",0" .",1";
$keywrds{"gencomment"    }    =   "eventGeneratorComment"     .",EventGenerators"        .",0" .",text" .",0" .",1";
$keywrds{"genparams"     }    =   "eventGeneratorParams"      .",EventGenerators"        .",1" .",text" .",0" .",1";
$keywrds{"tpc"           }    =   "dTPC"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1";
$keywrds{"svt"           }    =   "dSVT"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1";
$keywrds{"tof"           }    =   "dTOF"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1";
$keywrds{"emc"           }    =   "dEMC"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1";
$keywrds{"fpd"           }    =   "dFPD"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1";
$keywrds{"ftpc"          }    =   "dFTPC"                     .",DetectorConfigurations" .",1" .",num"  .",0" .",1";
$keywrds{"pmd"           }    =   "dPMD"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1";
$keywrds{"rich"          }    =   "dRICH"                     .",DetectorConfigurations" .",1" .",num"  .",0" .",1";
$keywrds{"ssd"           }    =   "dSSD"                      .",DetectorConfigurations" .",1" .",num"  .",0" .",1";
$keywrds{"triggerevents" }    =   "numberOfEvents"            .",TriggerCompositions"    .",1" .",text" .",0" .",1";
$keywrds{"events"        }    =   "numberOfEvents"            .",TriggerCompositions"    .",1" .",num"  .",0" .",1";
$keywrds{"simulation"    }    =   ",,,,,";
$keywrds{"nounique"      }    =   ",,,,,";
$keywrds{"noround"       }    =   ",,,,,";
$keywrds{"startrecord"   }    =   ",,,,,";
$keywrds{"limit"         }    =   ",,,,,";
$keywrds{"all"           }    =   ",,,,,";

# Fields that need to be rounded when selecting from the database
my $roundfields = "magFieldValue,2 collisionEnergy,0";

# The delimeter to sperate fields at output
my $delimeter = "::";

# The hashes that hold a current context
my %operset;
my %valuset;

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

my @datastruct;
$datastruct[0]  = ( "StorageTypes"           . ",FileLocations"       . ",storageTypeID"           . ",2");
$datastruct[1]  = ( "StorageSites"           . ",FileLocations"       . ",storageSiteID"           . ",2");
$datastruct[2]  = ( "FileData"               . ",FileLocations"       . ",fileDataID"              . ",2");
$datastruct[3]  = ( "ProductionConditions"   . ",FileData"            . ",productionConditionID"   . ",3");
$datastruct[4]  = ( "FileTypes"              . ",FileData"            . ",fileTypeID"              . ",3");
$datastruct[5]  = ( "TriggerWords"           . ",TriggerCompositions" . ",triggerWordID"           . ",2");
$datastruct[6]  = ( "FileData"               . ",TriggerCompositions" . ",fileDataID"              . ",2");
$datastruct[7]  = ( "RunParams"              . ",FileData"            . ",runParamID"              . ",3");
$datastruct[8]  = ( "RunTypes"               . ",RunParams"           . ",runTypeID"               . ",4");
$datastruct[9]  = ( "DetectorConfigurations" . ",RunParams"           . ",detectorConfigurationID" . ",4");
$datastruct[10] = ( "CollisionTypes"         . ",RunParams"           . ",collisionTypeID"         . ",4");
$datastruct[11] = ( "TriggerSetups"          . ",RunParams"           . ",triggerSetupID"          . ",4");
$datastruct[12] = ( "SimulationParams"       . ",RunParams"           . ",simulationParamsID"      . ",4");
$datastruct[13] = ( "EventGenerators"        . ",SimulationParams"    . ",eventGeneratorID"        . ",5");
$datastruct[14] = ( "FileLocations"          . ","                    . ","                        . ",1");
$datastruct[15] = ( "TriggerCompositions"    . ","                    . ","                        . ",1");


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
$aggregates[1] = "avg";
$aggregates[2] = "min";
$aggregates[3] = "max";
$aggregates[4] = "grp";
$aggregates[5] = "orda";
$aggregates[6] = "ordd";

# A table holding the number of records in each table
my %rowcounts;
$rowcounts{"StorageTypes"} = 0;
$rowcounts{"StorageSites"} = 0;
$rowcounts{"FileData"} = 0;
$rowcounts{"ProductionConditions"} = 0;
$rowcounts{"FileTypes"} = 0;
$rowcounts{"TriggerWords"} = 0;
$rowcounts{"FileData"} = 0;
$rowcounts{"RunParams"} = 0;
$rowcounts{"RunTypes"} = 0;
$rowcounts{"DetectorConfigurations"} = 0;
$rowcounts{"CollisionTypes"} = 0;
$rowcounts{"TriggerSetups"} = 0;
$rowcounts{"SimulationParams"} = 0;
$rowcounts{"EventGenerators"} = 0;
$rowcounts{"FileLocations"} = 0;
$rowcounts{"TriggerCompositions"} = 0;

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

  if (exists $keywrds{$mykey})
    {
      ($a,$tabname,$b) = split(",",$keywrds{$mykey});
    }
  else
    {
      print "Using non-existent key: $mykey !!!!!!!\n";
    }
  return $tabname;

}

#============================================
# get the list o valid keywords
# Returns:
# the list of valid keyowrds to use in FileCatalog queries
sub get_keyword_list {

  return (keys %keywrds);
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
# 0 if field is not needed
# 1 if field is mandatory for inserts
sub is_critical {
  my @params = @_;

  my ($fieldname, $tabname, $req, $type, $rest) = split(",",$keywrds{$params[0]});
  return $req;
}

#============================================
sub new {
  my $class= shift;
  my $self  = {};
  $self->{values} = [];
  $self->{entries} = undef;

  $delimeter = "::";
  $valuset{"all"} = 0;

  # Only way to bless it is to declare them inside
  # new(). See also use Symbol; and usage of my $bla = gensym;
  #my %operset=
  #my %valuset=

  bless($self);
  bless(\%valuset, "FileCatalog");
  bless(\%operset, "FileCatalog");

  return $self;
}

#============================================
sub connect {
  my $self  = shift;
  my ($user,$passwd) = @_;

  if( ! defined($user) )  { $user   = $dbuser;}
  if( ! defined($passwd) ){ $passwd = "FCatalog";}


  $DBH = DBI->connect($dbsource,$user,$passwd) ||
      die "cannot connect to $dbname : $DBI::errstr\n";

  foreach (keys(%rowcounts)){
      my $sqlquery = "SELECT count(*) FROM $_";
      &print_debug("Executing: $sqlquery");
      $sth = $DBH->prepare($sqlquery);
      if( ! $sth){
   	&print_debug("FileCatalog:: connect : Failed to prepare [$sqlquery]");
      } else {
	$sth->execute();
	my( $count );
	$sth->bind_columns( \$count );
	
	if ( $sth->fetch() ) {
	  $rowcounts{$_} = $count;
	}
      }
  }

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
      ($keyword, $value) = $params =~ m/(.*)$_(.*)/;
      $operator = $_;
      last if (defined $keyword and defined $value);
      $operator = "";
    }

  if ($DEBUG > 0) {
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
      ($keyw, $oper, $valu) = disentangle_param($params);

      # Chop spaces from the key name and value;
      $keyw =~ y/ //d;
      if ($valu =~ m/.*[\"\'].*[\"\'].*/) {
	  $valu =~ s/.*[\"\'](.*)[\"\'].*/$1/;
      } else {
	  $valu =~ s/ //g;
      }

      if (exists $keywrds{$keyw}) {
	  if ($DEBUG > 0) {
	      &print_debug("Query accepted $DEBUG: ".$keyw."=".$valu);
	  }
	  $operset{$keyw} = $oper;
	  $valuset{$keyw} = $valu;
      } else {
	  if ($DEBUG > 0){
	      &print_debug("ERROR: $keyw is not a valid keyword.",
			   "Cannot set context.");
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
  my $sqlquery;

  chop($idname);
  $idname = lcfirst($idname);
  $idname.="ID";

  $sqlquery = "SELECT $idname FROM $params[0] WHERE UPPER($params[1]) = UPPER(\"$params[2]\")";
  if ($DEBUG > 0) {  &print_debug("Executing: $sqlquery");}
  $sth = $DBH->prepare($sqlquery);

  if( ! $sth){
      &print_debug("FileCatalog:: get_id_from_dictionary : Failed to prepare [$sqlquery]");
  } else {
      $sth->execute();
      my( $id );
      $sth->bind_columns( \$id );

      if ( $sth->fetch() ) {
	  return $id;
      }
  }

}

#============================================
# Check if there is a record with a given value
# in a corresponding dictionary table
# Parameters:
# the keyword to check for
# Returns:
# The ID value for a given keyword value
# or 0 if no such record exists
sub check_ID_for_params {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  }
  ;
  my @params = @_;
  my $retid;

  if (defined $valuset{$params[0]}) {
    my $fieldname;
    my $tabname;
    my $rest;

    ($fieldname, $tabname, $rest) = split(",",$keywrds{$params[0]});
    $retid = get_id_from_dictionary($tabname, $fieldname, $valuset{$params[0]});
    if ($retid == 0) {
      if ($DEBUG > 0) {
	  &print_debug("ERROR: No $params[0] with name: ".$valuset{$params[0]});
      }
      $retid = 0;
    }
  } else {
    if ($DEBUG > 0) {
	&print_debug("ERROR: No $params[0] defined");
    }
    $retid = 0;
  }
  if ($DEBUG > 0) {
      &print_debug("Returning: $retid");
  }
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
  foreach (keys(%keywrds)) {
    my ($fieldnameo, $tabnameo, $resto) = split(",",$keywrds{$keyname});
    my ($fieldnamet, $tabnamet, $restt) = split(",",$keywrds{$_});

    if ($tabnameo eq $tabnamet && $keyname ne $_) {
      if ($DEBUG > 0) {
	  &print_debug("The field $fieldnamet $tabnamet is from the same table as $fieldnameo $tabnameo");
      }
      if (defined $valuset{$_}) {
	  push @additional, ($_);
      }
    }
  }

  my ($fieldname, $tabname, $rest) = split(",",$keywrds{$keyname});
  my $dtfields = "";
  my $dtvalues = "";
  my $dtinsert;

  foreach (@additional) {
    my ($fieldnamea, $tabnamea, $resta) = split(",",$keywrds{$_});

    $dtfields .= " , $fieldnamea";
    $dtvalues .= " , '".$valuset{$_}."'";
  }

  $dtinsert   = "INSERT IGNORE INTO $tabname ";
  $dtinsert  .= "($fieldname $dtfields)";
  $dtinsert  .= " VALUES ('".$valuset{$keyname}."' $dtvalues)";
  if ($DEBUG > 0) {    &print_debug("Execute $dtinsert");}


  my $sth;

  $sth = $DBH->prepare( $dtinsert );
  if( ! $sth ){
      &print_debug("FileCatalog::insert_dictionary_value : Failed to prepare [$dtinsert]");
  } else {
      if ( $sth->execute() ) {
	  my $retid = get_last_id();
	  if ($DEBUG > 0) { &print_debug("Returning: $retid");}
	  return $retid;
      }
  }
  return 0;
}

#============================================
# inserts a value into a table of Detector Configurations
# Returns:
# The ID of an inserted value
# or 0 if such insertion was not possible
sub insert_detector_configuration {

  if( ! $DBH){
      &print_message("insert_detector_configuration","Not connected");
      return 0;
  }


  my ($tpcon, $svton, $emcon, $ftpcon, $richon, $fpdon, $tofon, $pmdon, $ssdon);
  if (! defined $valuset{"configuration"}) {
      &print_debug("ERROR: No detector configuration/geometry name given.",
		   "Cannot add record to the table.");
    return 0;
  }
  $tpcon = ($valuset{"tpc"} == 1) ? "1" : "0";
  $svton = ($valuset{"svt"} == 1) ? "1" : "0";
  $emcon = ($valuset{"emc"} == 1) ? "1" : "0";
  $ftpcon = ($valuset{"ftpc"} == 1) ? "1" : "0";
  $richon = ($valuset{"rich"} == 1) ? "1" : "0";
  $fpdon = ($valuset{"fpd"} == 1) ? "1" : "0";
  $tofon = ($valuset{"tof"} == 1) ? "1" : "0";
  $pmdon = ($valuset{"pmd"} == 1) ? "1" : "0";
  $ssdon = ($valuset{"ssd"} == 1) ? "1" : "0";


  my $dtinsert   = "INSERT IGNORE INTO DetectorConfigurations";
  $dtinsert  .= "(detectorConfigurationName, dTPC, dSVT, dTOF, dEMC, dFPD, dFTPC, dPMD, dRICH, dSSD)";
  $dtinsert  .= " VALUES ('".$valuset{"configuration"}."', $tpcon , $svton , $tofon , $emcon , $fpdon , $ftpcon , $pmdon , $richon , $ssdon)";
  if ($DEBUG > 0) {  &print_debug("Execute $dtinsert");}


  my $sth;

  $sth = $DBH->prepare( $dtinsert );
  if( ! $sth ){
      &print_debug("FileCatalog::insert_detector_configuration : Failed to prepare [$dtinsert]");
  } else {
      if ( $sth->execute() ) {
	  my $retid = get_last_id();
	  if ($DEBUG > 0) { &print_debug("Returning: $retid");}
	  return $retid;
      }
  }
  return 0;
}


#============================================
# get the ID for the current run number
# Returns:
# the ID of a runParams record,
# or 0 if no such record exists
sub get_current_detector_configuration {

  my $detConfiguration;

  $detConfiguration = check_ID_for_params("configuration");
  if ($detConfiguration == 0) {
    # There is no detector configuration with this name
    # we have to add it
    $detConfiguration = insert_detector_configuration();
  }
  return $detConfiguration;
}

#============================================
# disentangle collision type parameters from the collsion type name
# Params:
# The collsion type
# Returns:
# first particle name
# second particle name
# collision energy
sub disentangle_collision_type {

  my ($colstring) = @_;
  my $firstParticle = "";
  my $secondParticle = "";

  my @particles = ("proton", "gas", "au", "ga", "si", "p", "s");


  if (($colstring =~ m/cosmic/) > 0)
    {
      $firstParticle = "cosmic";
      $secondParticle = "cosmic";
      $colstring = "0.0";
    }
  else
    {
      foreach (@particles)
	{
	  if (($colstring =~ m/$_/) > 0) {
	    $firstParticle = $_;
	    $colstring =~ s/$_(.*)/$1/;
	    last;
	  }
	}
      foreach (@particles)
	{
	  if (($colstring =~ m/$_/) > 0) {
	    $secondParticle = $_;
	    $colstring =~ s/(.*)$_(.*)/$1$2/;
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
# the id of a collision type in DB or 0 if there is no such collsion type
sub get_collision_type {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  };
  if( ! defined($DBH) ){
      &print_message("get_collision_type","Not connected/connecting");
      return 0;
  }


  my ($colstring) = @_;
  my $retid;
  my $firstParticle;
  my $secondParticle;
  my $energy;

  if( $colstring eq ""){
      die "FileCatalog::get_collision_type : received empty argument\n";
  }

  $colstring = lc($colstring);

  ($firstParticle, $secondParticle, $energy) = disentangle_collision_type($colstring);


  my $sqlquery = "SELECT collisionTypeID FROM CollisionTypes WHERE UPPER(firstParticle) = UPPER(\"$firstParticle\") AND UPPER(secondParticle) = UPPER(\"$secondParticle\") AND ROUND(collisionEnergy) = ROUND($energy)";

  if ($DEBUG > 0) {
      &print_debug("First particle : $firstParticle",
		   "Second particle: $secondParticle",
		   "Energy         : $colstring",
		   "Executing: $sqlquery");
  }

  my $sth = $DBH->prepare($sqlquery);
  if( ! $sth){
      &print_debug("FileCatalog::get_collision_type : Failed to prepare [$sqlquery]");
  } else {
      if( ! $sth->execute() ){ die "Could not execute [$sqlquery]";}
      my( $id );
      $sth->bind_columns( \$id );

      if ( $sth->fetch() ) {
	  #    print "Returning: $id\n";
	  return $id;
      }
      &print_debug("ERROR: No such collision type");
  }

  return 0;

}

#============================================
# insert a given collision tye into the database
# Returns:
# the id of a collision type in DB
# or 0 if the insertion was not possible
sub insert_collision_type {

  my $colstring = $valuset{"collision"};
  my $retid;
  my $firstParticle;
  my $secondParticle;
  my $energy;

  if( ! defined($DBH) ){
      &print_message("insert_collision_type","Not connected");
      return 0;
  }


  $colstring = lc($colstring);

  ($firstParticle, $secondParticle, $energy) = disentangle_collision_type($colstring);

  my $ctinsert   = "INSERT IGNORE INTO CollisionTypes ";
  $ctinsert  .= "(firstParticle, secondParticle, collisionEnergy)";
  $ctinsert  .= " VALUES ('$firstParticle' , '$secondParticle' , $energy)";

  &print_debug("Execute $ctinsert");

  my $sth;
  $sth = $DBH->prepare( $ctinsert );
  if( ! $sth){
      &print_debug("FileCatalog::insert_collision_type : Failed to prepare [$ctinsert]");
  } else {
      if ( $sth->execute() ) {
	  my $retid = get_last_id();
	  &print_debug("Returning: $retid");
	  return $retid;
      }
  }
  return 0;
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
	$sth->execute();
	$sth->bind_columns( \$id );

	if ( $sth->fetch() ) {
	    $retv = $id;
	} else {
	    &print_debug("ERROR: Cannot find the last inserted ID");
	}
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


  $triggerSetup     = check_ID_for_params("triggersetup");
  $runType          = check_ID_for_params("runtype");
  $detConfiguration = check_ID_for_params("configuration");

  if (! defined $valuset{"runnumber"}) {
      &print_debug("ERROR: Cannot add runtype","runnumber not defined.");
      return 0;
  }
  if (defined $valuset{"collision"}) {
      $collision = get_collision_type($valuset{"collision"});
      if ($DEBUG > 0) {
	  &print_debug("Collsion: $collision");
      }
  } else {
      &print_debug("ERROR: collsion not defined");
  }
  if (($triggerSetup == 0) || ($runType == 0) || ($detConfiguration == 0) || ($collision == 0)) {
      &print_debug("ERROR: Cannot add run","Aborting file insertion query");
      return 0;
  }
  if (! defined $valuset{"runcomments"}) {
    $comment = "NULL";
  } else {
    $comment = "\"".$comment."\"";
  }
  if (! defined $valuset{"magscale"}) {
      &print_debug("ERROR: Cannot add runtype","magscale not defined.");
      return 0;
  }
  if (! defined $valuset{"magvalue"}) {
    $magvalue = "NULL";
  } else {
    $magvalue = $valuset{"magvalue"};
  }
  if (! defined $valuset{"datetaken"}) {
    $start = "NULL";
    $end = "NULL";
  } else {
    $start = "\"".$valuset{"datetaken"}."\"";
    $end = "\"".$valuset{"datetaken"}."\"";
  }
  if ((defined $valuset{"simulation"}) && (! ($valuset{"simulation"} eq '0') ) ) {
      &print_debug("Adding simulation data.");
      $simulation = get_current_simulation_params();
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
	  $retid = get_last_id();
	  if ($DEBUG > 0) { &print_debug("Returning: $retid");}
      }
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

  $runNumber = check_ID_for_params("runnumber");
  if ($runNumber == 0) {
    # There is no run with this run number
    # we have to add it
    $runNumber = insert_run_param_info();
  }
  return $runNumber;
}

#============================================
# Execute the query to insert the file data
# Check if we have all the information
# Returns:
# The id of a lastly inserted file data
# or 0 is there is insufficient data to insert a record
sub insert_file_data {
  my @params = @_;
  # Get the ID's of the dictionary tales
  my $production;
  my $library;
  my $fileType;
  my $runNumber;
  my $size;
  my $fileComment;
  my $fileSeq;
  my @triggerWords;
  my @eventCounts;
  my @triggerIDs;
  my $count;

  if( ! defined($DBH) ){
      &print_message("insert_file_data","Not connected");
      return 0;
  }

  $production = check_ID_for_params("production");
  $library = check_ID_for_params("library");
  $fileType= check_ID_for_params("filetype");

  return 0 if ((($production == 0 ) && ($library == 0)) || $fileType == 0);

  if ($production == 0) {
    $production = $library;
  }
  $runNumber = get_current_run_param();
  if ($runNumber == 0) {
      &print_debug("Could not add run data","Aborting file insertion query");
      return 0;
  }
  if (! defined $valuset{"filename"}) {
      &print_debug("ERROR: Cannot add file data","filename not defined.");
      return 0;
  }
  if (! defined $valuset{"size"}) {
    $size = "NULL";
  } else {
    $size = $valuset{"size"};
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
  # Try to disentangle the triggerword / event count combinations
  # tom the triggerevents string. It should have a format:
  # '<triggerword> <number of events> [ ; <triggerword> <number of events> ]'
  if (! defined $valuset{"triggerevents"}) {
      &print_debug("ERROR: Cannot add runtype",
		   "events for triggerWords not defined.");
      return 0;
  } else {
    my @splitted;
    my $count = 0;
    (@splitted) = split(";",$valuset{"triggerevents"});
    foreach (@splitted) {
      ($triggerWords[$count], $eventCounts[$count]) = split(" ");
      if ($DEBUG > 0) {
	  &print_debug("Added triggerword ".$triggerWords[$count].
		       " with event count ".$eventCounts[$count]);
      }
      $triggerIDs[$count] = get_id_from_dictionary("TriggerWords","triggerName",$triggerWords[$count]);
      if ($triggerIDs[$count] == 0) {
	if ($DEBUG > 0) {
	    &print_debug("Warning: no triggerID for triggerword $triggerWords[$count]");
	}
      }
      $count++;
    }
  }

  # Prepare the SQL query and execute it
  my $fdinsert   = "INSERT IGNORE INTO FileData ";
  $fdinsert  .= "(runParamID, fileName, productionConditionID, fileTypeID, size, fileDataComments, fileSeq)";
  $fdinsert  .= " VALUES ($runNumber, \"".$valuset{"filename"}."\",$production,$fileType,$size,$fileComment,$fileSeq)";
  if ($DEBUG > 0) { &print_debug("Execute $fdinsert");}


  my $sth;
  my $retid;
  $sth = $DBH->prepare( $fdinsert );
  if( $sth ){
      if ( $sth->execute() ) {
	  $retid = get_last_id();
	  if ($DEBUG > 0) { &print_debug("Returning: $retid");}
      } else {
	  return 0;
      }
  } else {
      &print_debug("FileCatalog::insert_file_data : Failed to prepare [$fdinsert]");
  }

  # Add the triggerword / event count combinations for this FileData
  if ($DEBUG > 0) { &print_debug("Adding triggerWords $#triggerWords");}

  for ($count = 0; $count < ($#triggerWords+1); $count++) {
      if ($DEBUG > 0) {
	  &print_debug("Adding triggerWord $count");
      }
      my $tcinsert   = "INSERT IGNORE INTO TriggerCompositions ";
      $tcinsert  .= "(fileDataID, triggerWordID, numberOfEvents)";
      $tcinsert  .= " VALUES ( $retid , ".$triggerIDs[$count]." , ".$eventCounts[$count].")";
      if ($DEBUG > 0) { &print_debug("Execute $tcinsert");}


      my $sth;
      $sth = $DBH->prepare( $tcinsert );
      if( $sth ){
	  if ( ! $sth->execute() ) {
	      if ($DEBUG > 0) {
		  &print_debug("ERROR: did not add the ".
			       "event count for triggerword $triggerWords[$count]");
	      }
	  }
      } else {
	  &print_debug("FileCatalog::insert_file_data : Failed to prepare [$tcinsert]");
      }
  }
  return $retid;
}

#============================================
# get the ID for the current file data, or create it
# if not found.
# Returns:
# the ID of a fileData record
# or 0 if no such fielData, cannot create it, or more than one record exists for a given context.
sub get_current_file_data {
  my $runParam;
  my $fileName;
  my $production;
  my $library;
  my $fileType;
  my $fileSeq;
  my $sqlquery;

  if( ! defined($DBH) ){
      &print_message("get_current_file_data","Not connected");
      return 0;
  }

  $runParam   = get_current_run_param();
  $production = check_ID_for_params("production");
  $library    = check_ID_for_params("library");
  $fileType   = check_ID_for_params("filetype");

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
  if ( $production != 0) {
      $sqlquery .= " productionConditionID = $production AND ";
  }
  if ( $fileType != 0) {
      $sqlquery .= " fileTypeID = $fileType AND ";
  }
  if (defined $sqlquery) {
      $sqlquery =~ s/(.*)AND $/$1/g;
  } else {
      &print_debug("No parameters set to identify File Data");
      return 0;
  }
  $sqlquery = "SELECT fileDataID FROM FileData WHERE $sqlquery";
  if ($DEBUG > 0) {
      &print_debug("Executing query: $sqlquery");
  }

  my($sth,$id);

  $sth = $DBH->prepare($sqlquery);

  if( ! $sth ){
      &print_debug("FileCatalog::get_current_file_data : Failed to prepare [$sqlquery]");
      return 0;
  }

  $sth->execute();
  $sth->bind_columns( \$id );

  if ($sth->rows == 0) {
    my $newid;
    $newid = insert_file_data();
    return $newid;
  }
  if ($sth->rows > 1) {
      &print_debug("More than one file data matches the query criteria",
		   "Add more data to unambiguously identify file data");
      return 0;
  }

  if ( $sth->fetch() ) {
    if ($DEBUG > 0) {
	&print_debug("Returning: $id");
    }
    return $id;
  }
  return 0;


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
      &print_debug("Not enough parameters to insert event generator data",
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
  $sth->execute();
  my( $id );
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
      $eventGenerator = get_last_id();
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
    my $retid = get_last_id();
    if ($DEBUG > 0) {
	&print_debug("Returning: $retid");
    }
  } else {
      &print_debug("Could not add simulation data.",
		   "Aborting simulation data insertion query.");
      return 0;
  }

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
      &print_debug("Not enough parameters to find event generator data",
		   "Define generator, genversion and genparams");
      return 0;
  }
  $sqlquery = "SELECT simulationParamsID FROM SimulationParams, EventGenerators WHERE eventGeneratorName = '".$valuset{"generator"}."' AND eventGeneratorVersion = '".$valuset{"genversion"}."' AND eventGeneratorParams = '".$valuset{"genparams"}."' AND SimulationParams.eventGeneratorID = EventGenerators.eventGeneratorID";
  if ($DEBUG > 0) {
      &print_debug("Executing query: $sqlquery");
  }

  my $sth;
  $sth = $DBH->prepare($sqlquery);
  if ( ! $sth){
      &print_debug("FileCatalog::get_current_simulation_params : Failed to prepare [$sqlquery]");
      return 0;
  }
  $sth->execute();
  my( $id );
  $sth->bind_columns( \$id );

  if ($sth->rows == 0) {
      my $newid;
      $newid = insert_simulation_params();
      return $newid;
  } else {
      if ( $sth->fetch() ) {
	  if ($DEBUG > 0) { &print_debug("Returning: $id");}
	  return $id;
      }
  }
  return 0;

}

#============================================
# inserts the file location data and the file and run data
# if neccessary.
# Returns: The ID of a newly created File Location
# or 0 if the insert fails
sub insert_file_location {
  my $fileData;
  my $storageType;
  my $storageSite;
  my $filePath;
  my $createTime;
  my $owner;
  my $protection;
  my $nodeName;
  my $availability;
  my $persistent;
  my $sanity;

  if( ! defined($DBH) ){
      &print_message("insert_file_location","Not connected");
      return 0;
  }

  $fileData = get_current_file_data();
  if ($fileData == 0) {
      &print_debug("No file data available",
		   "Aborting file insertion query");
      return 0;
  }
  $storageType = check_ID_for_params("storage");
  $storageSite = check_ID_for_params("site");
  if (($storageType == 0 ) || ($storageSite == 0)) {
      &print_debug("Aborting file location insertion query");
      return 0;
  }
  if (! defined $valuset{"path"}) {
      &print_debug("ERROR: file path not defined. Cannot add file location",
		   "Aborting File Location a");
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
      $owner = "NULL";
  } else {
      $owner = '"'.$valuset{"owner"}.'"';
  }
  if (! defined $valuset{"protection"}) {
      &print_debug("WARNING: protection not defined. Using a default value");
      $protection = "NULL";
  } else {
      $protection = '"'.$valuset{"protection"}.'"';
  }
  if (! defined $valuset{"node"}) {
      &print_debug("WARNING:  not defined. Using a default value");
      $nodeName = "NULL";
  } else {
      $nodeName = '"'.$valuset{"node"}.'"';
  }
  if (! defined $valuset{"availability"}) {
      &print_debug("WARNING:  not defined. Using a default value");
      $availability = 1 ;
  } else {
      $availability = $valuset{"availability"};
  }
  if (! defined $valuset{"persistent"}) {
      &print_debug("WARNING:  not defined. Using a default value");
      $persistent = 0 ;
  } else {
      $persistent = $valuset{"persistent"};
  }
  if (! defined $valuset{"sanity"}) {
      &print_debug("WARNING:  not defined. Using a default value");
      $sanity = 0;
  } else {
      $sanity = $valuset{"sanity"};
  }


  my $flinsert   = "INSERT IGNORE INTO FileLocations ";
  $flinsert  .= "(fileLocationID, fileDataID, storageTypeID, filePath, createTime, insertTime, owner, storageSiteID, protection, nodeName, availability, persistent, sanity)";
  $flinsert  .= " VALUES (NULL, $fileData, $storageType, $filePath, $createTime, NULL, $owner, $storageSite, $protection, $nodeName, $availability, '$persistent', $sanity)";
  if ($DEBUG > 0) {
      &print_debug("Execute $flinsert");
  }
  my $sth;

  $sth = $DBH->prepare( $flinsert );
  #print "++ $flinsert ++";
  if( ! $sth ){
      &print_debug("FileCatalog::insert_file_location : Failed to prepare [$flinsert]");
  } else {
      if ( $sth->execute() ) {
	  my $retid = get_last_id();
	  if ($DEBUG > 0) { &print_debug("Returning: $retid");}
	  return $retid;
      }
  }
  return 0;


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
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  }

  my ($begkeyword, $endkeyword) = (@_);
  my ($begtable, $begfield, $endtable, $endfield, $blevel, $elevel);
  my ($ftable, $stable, $flevel, $slevel);
  my (@connections, $connum);


  if ($DEBUG > 0) {
      &print_debug("Looking for connection between fields: $begkeyword, $endkeyword");
  }

  $begtable = get_table_name($begkeyword);
  $begfield = get_field_name($begkeyword);
  $endtable = get_table_name($endkeyword);
  $endfield = get_field_name($endkeyword);
  $blevel   = get_struct_level($begtable);
  $elevel   = get_struct_level($endtable);
  if ($blevel > $elevel) {
    ($ftable, $stable, $flevel, $slevel) =
      ($begtable, $endtable, $blevel, $elevel)
    } else {
      ($stable, $ftable, $slevel, $flevel) =
	($begtable, $endtable, $blevel, $elevel)
      }
  if ($DEBUG > 0) {
      &print_debug("First: $ftable , $flevel",
		   "Second: $stable , $slevel");
  }
  # Get to the fields on the same level in tree hierarchy
  while ($slevel < $flevel) {
    my ($ttable, $tlevel, $connum) = get_lower_level($ftable);
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
      my ($ttable, $tlevel, $connum) = get_lower_level($stable);
      push(@upconnections, $connum);
      $slevel = $tlevel;
      $stable = $ttable;
      ($ttable, $tlevel, $connum) = get_lower_level($ftable);
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
      ($findex, $sindex) = get_intersect($#flevelfields, @flevelfields, @slevelfields);
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
	  (@flower) = get_all_upper($flevelfields[$fcount]);
	  if ($DEBUG > 0) {
	      &print_debug("All first descendants: ".join(" ",(@flower)));
	  }
	  for (my $cflow = 0; $cflow <= $#flower; $cflow++) {
	      # Add a road going from the tree root to this field
	      if( defined($froads{$flower[$cflow]}) ){
		  $froads{$flower[$cflow]} = $froads{$flevelfields[$fcount]}." ".
		      get_connection($flower[$cflow], $flevelfields[$fcount]);
	      } else {
		  $froads{$flower[$cflow]} = " ".
		      get_connection($flower[$cflow], $flevelfields[$fcount]);
	      }
	      if ($DEBUG > 0) {
		  &print_debug("Added road $froads{$flower[$cflow]}");
	      }
	  }
	}
	for ($scount=0; $scount <= $#slevelfields ; $scount++) {
	  # Get all the fields that are connected to this one
	  # and one level up
	  (@slower) = get_all_upper($slevelfields[$scount]);
	  if ($DEBUG > 0) {
	      &print_debug("All second descendants: ".join(" ",(@slower)));
	  }
	  for (my $cslow = 0; $cslow < $#slower+1; $cslow++) {
	    # Add a road going from the tree root to this field
	      if( defined($sroads{$slower[$cslow]}) ){
		  $sroads{$slower[$cslow]} = $sroads{$slevelfields[$scount]}." ".
		      get_connection($slower[$cslow], $slevelfields[$scount]);
	      } else {
		  $sroads{$slower[$cslow]} = " ".
		      get_connection($slower[$cslow], $slevelfields[$scount]);
	      }

	    if ($DEBUG > 0) {
		&print_debug("Added road $sroads{$slower[$cslow]}");
	    }
	  }
	}
	@flevelfields = @flower;
	@slevelfields = @slower;
	($findex, $sindex) = get_intersect($#flevelfields, @flevelfields, @slevelfields);
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
sub run_query {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  };


  if( ! defined($DBH) ){
      &print_message("run_query","Not connected");
      return;
  }

  my %functions;
  my $count;
  my $grouping = "";
  my $flkey;

  # Protect against bogus query
  if( ! defined($_[0]) ){
      &print_message("run_query()","method called without arguments");
      return;
  }

  # An ugly hack to get FileLocation id number from within the module
  if ($_[0] eq "id")
    {
      $flkey = 1;
      shift @_;
    };

  my (@keywords)  = (@_);

  if($DEBUG > 0){
      &print_debug("By the way ...");
      foreach (keys(%rowcounts))
      {
	  &print_debug("\t$_ count is ".$rowcounts{$_}."\n");
      }
  }


  $count = 0;
  # Check the validity of the keywords
  foreach(@keywords)
    {
      #First check if it is a request for an agregate value
      my $afun;
      my ($aggr, $keyw);

      $_ =~ y/ //d;

      foreach $afun (@aggregates)
	{
	  ($aggr, $keyw) = $_ =~ m/($afun)\((.*)\)/;
	  last if (defined $aggr and defined $keyw);
	}
      if (defined $keyw){
	  if ($DEBUG > 0) {
	      &print_debug("Found aggregate function |$aggr| on keyword |$keyw|");
	  }
	  # If it is - save the function, and store only the bare keyword
	  $functions{$keyw} = $aggr;
	  $keywords[$count] = $keyw;
	}
      if (not defined ($keywrds{$_})){
	  &print_message("run_query()","Wrong keyword: $_");
	  return;
      }
      $count++;
    }

  # Do the constraint pre-check (for query optimization)
  # check if a given costraint produces a single record ID
  # If so remove the constraint and use this ID directly instead
  my @constraint;
  my @from;
  my @connections;

  foreach (keys(%valuset)) {
    my $tabname = get_table_name($_);
    # Check if the table name is one of the dictionary ones
    if (($tabname ne "FileData") && 
	($tabname ne "FileLocations") && 
	($tabname ne "RunParams") && 
	($tabname ne "SimulationParams") &&
	($tabname ne "TriggerCompositions") && 
	($tabname ne ""))
      {
	my $fieldname = get_field_name($_);
	my $idname = $tabname;
	my $addedconstr = "";

	chop($idname);
	$idname = lcfirst($idname);
	$idname.="ID";
	
	# Find which table this one is connecting to
	my $parent_tabname;
	foreach (@datastruct){
	    if (($_ =~ m/$idname/) > 0){
		# We found the right row - get the table name
		my ($stab,$fld);
		($stab,$parent_tabname,$fld) = split(",");
	    }
	}


	my $sqlquery = "SELECT $idname FROM $tabname WHERE ";
 	if ((($roundfields =~ m/$fieldname/) > 0) && (! defined $valuset{"noround"})){
	    #&print_debug("1 Inspecting [$roundfields] [$fieldname]");
	    my ($nround) = $roundfields =~ m/$fieldname,([0-9]*)/;
	    #&print_debug("1 Rounding to [$roundfields] [$fieldname] [$nround]");
	    $sqlquery .= "ROUND($fieldname, $nround) ".$operset{$_}." ";
	    if( $valuset{$_} =~ m/^\d+/){
		$sqlquery .= $valuset{$_};
	    } else {
		$sqlquery .= "'$valuset{$_}'";
	    }

	    #&print_debug("1 Rounding Query will be [$sqlquery]");

	} elsif ($operset{$_} eq "~"){
	    $sqlquery .= "$fieldname LIKE '%".$valuset{$_}."%'";

	} elsif ($operset{$_} eq "!~"){
	    $sqlquery .= "$fieldname NOT LIKE '%".$valuset{$_}."%'";
	} else {
	    if (get_field_type($_) eq "text"){
		$sqlquery .= "$fieldname ".$operset{$_}." '".$valuset{$_}."'"; 
	    } else {
		$sqlquery .= "$fieldname ".$operset{$_}." ".$valuset{$_}; 
	    }
	}
	if ($DEBUG > 0) {  &print_debug("Executing special: $sqlquery");}
	$sth = $DBH->prepare($sqlquery);


	if( ! $sth){
	  &print_debug("FileCatalog:: get id's : Failed to prepare [$sqlquery]");
	} else {
	  $sth->execute();
	  my( $id );
	  $sth->bind_columns( \$id );

	  if ( $sth->rows < 5) {
	    # Create a new constraint
	    $addedconstr = " ( ";
	    while ( $sth->fetch() ) {
	      if ($addedconstr ne " ( ")
		{
		  $addedconstr .= " OR $parent_tabname.$idname = $id "; 
		}
	      else
		{
		  $addedconstr .= " $parent_tabname.$idname = $id ";
		}
	      &print_debug("Added constraints now $addedconstr");
	    }
	    $addedconstr .= " ) ";
	    # Add a newly constructed keyword
	    push (@constraint, $addedconstr) if ($addedconstr !~ m/\(\s+\)/);
	    # Remove the condition - we already take care of it
	    delete $valuset{$_};
	    # But remember to add the the parent table
#	    push (@connections, (connect_fields($keywords[0], $_)));
	    push (@from, $parent_tabname);
	  }
	}
	
      }
  }
  

  push (@from, get_table_name($keywords[0]));
  for ($count=1; $count<$#keywords+1; $count++) {
    push (@connections, (connect_fields($keywords[0], $keywords[$count])));
    push (@from, get_table_name($keywords[$count]));
  }

  # Also add to the FROM tables the tables for each set keyword
  foreach my $key (keys %valuset)
    {
      if (get_table_name($key) ne "")
	{
	  push (@connections, (connect_fields($keywords[0], $key)));
	  push (@from, get_table_name($key));
	}
    }

  if ($DEBUG > 0) {
      &print_debug("Connections to build the query: ".join(" ",@connections));
  }

  if (defined $valuset{"simulation"})
    {
      push (@connections, (connect_fields($keywords[0], "runnumber")));
      push (@from, "RunParams");
    }

  # Fill the table of connections
  my $connections = join(" ",(@connections));
  my @toquery;
  foreach (sort (split(" ",$connections))) {
    if ((not $toquery[$#toquery]) || ($toquery[$#toquery] != $_)) {
      push (@toquery, $_);
    }
  }

  if ($DEBUG > 0) {
      &print_debug("Connections to build the query: ".join(" ",@toquery));
  }
  # Get the select fields
  my @select;
  foreach (@keywords) {
    if ($DEBUG > 0) {
	&print_debug("Adding keyword: $_");
    }
    if (defined $functions{$_})
      {
	if ($functions{$_} eq "grp")
	  {
	      if (($grouping =~ m/GROUP BY/) == 0){
		  $grouping .= " GROUP BY ".get_field_name($_)." ";
		  push (@select, get_field_name($_));
	      }
	  }
	elsif ($functions{$_} eq "orda")
	  {
	    $grouping .= " ORDER BY ".get_field_name($_)." ASC ";
	    push (@select, get_field_name($_));
	  }
	elsif ($functions{$_} eq "ordd")
	  {
	    $grouping .= " ORDER BY ".get_field_name($_)." DESC ";
	    push (@select, get_field_name($_));
	  }
	else
	  {
	    push (@select, $functions{$_}."(".get_field_name($_).")");
	  }
      }
    elsif ($_ ne "collision") {
      push (@select, get_field_name($_));
    }
    else
    {
      push (@select, "CONCAT( firstParticle, secondParticle, collisionEnergy )");
    }
  }

  # Build the FROM and WHERE parts of the query
  # using thew connection list
  my  ($where);
  foreach (@toquery) {
    my ($mtable, $stable, $field, $level) = split(",",$datastruct[$_]);
    if (($mtable eq "FileData") && ($stable eq "FileLocations"))
      {
	next;
      }
    push (@from, $mtable);
    push (@from, $stable);
    if (not $where) {
      $where .= " $mtable.$field = $stable.$field ";
    } else {
      $where .= " AND $mtable.$field = $stable.$field ";
    }
  }
  my $toquery = join(" ",(@from));
  if ($DEBUG > 0) {
      &print_debug("Table list $toquery");
  }
  # Get only the unique table names
  my @fromunique;
  foreach (sort {$a cmp $b} split(" ",$toquery)) {
    if ($DEBUG > 0) {
	&print_debug("Adding $_");
    }
    if ((not $fromunique[$#fromunique]) || ($fromunique[$#fromunique] ne $_)) {
      push (@fromunique, $_);
    }
  }

  # Extra debug line
  #if($DEBUG){
  #    &print_debug("--> order is --> ".join(" ",@select));
  #}

  # Get only the unique field names
  my @selectunique;
  #foreach (sort {$a cmp $b} (@select)) {
  foreach ( @select ) {
      if ($DEBUG > 0) {
	  &print_debug("Adding $_");
      }
      if ((not $selectunique[$#selectunique]) || ($selectunique[$#selectunique] ne $_)) {
	  push (@selectunique, $_);
      }
  }


  # See if we have any constaint parameters
  foreach (keys(%valuset)) {
    my $fromlist = join(" " , (@fromunique));
    my $tabname = get_table_name($_);
    if ((($fromlist =~ m/$tabname/) > 0) && ($tabname ne "")) {
      my $fieldname = get_field_name($_);
      if ((($roundfields =~ m/$fieldname/) > 0) && (! defined $valuset{"noround"}))
	{
	  my ($nround) = $roundfields =~ m/$fieldname,([0-9]*)/;
	  my ($roundv)="ROUND($fieldname, $nround) ".$operset{$_}." ";

	  if( $valuset{$_} =~ m/^\d+/){
	      $roundv .= $valuset{$_};
	  } else {
	      $roundv  .= "'$valuset{$_}'";
	  }
	  push(@constraint,$roundv);

	}
      elsif ($operset{$_} eq "~")
	{
	  push( @constraint, "$fieldname LIKE '%".$valuset{$_}."%'" );
	}
      elsif ($operset{$_} eq "!~")
	{
	  push( @constraint, "$fieldname NOT LIKE '%".$valuset{$_}."%'" );
	}
      else
	{
	  if (get_field_type($_) eq "text")
	    { push( @constraint, "$fieldname ".$operset{$_}." '".$valuset{$_}."'" ); }
	  else
	    { push( @constraint, "$fieldname ".$operset{$_}." ".$valuset{$_} ); }
	}
    }
  }

  if (defined $valuset{"simulation"})
    {
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

  if ($DEBUG > 0){
      &print_debug("Checking for FileLocations ".(join(" ",@fromunique))." $floc");
  }

  if (($floc > 0) && defined ($valuset{"all"}) && ($valuset{"all"} == 0 )){
      push ( @constraint, "FileLocations.availability > 0");
  }

  my $constraint = join(" AND ",@constraint);

  # Build the actual query string
  my $sqlquery;
  $sqlquery = "SELECT ";
  if (! defined $valuset{"nounique"})
    { $sqlquery .= " DISTINCT "; }
  # An ugly hack to return FileLocationID from within the module
  if (((join(" ",(@fromunique)) =~ m/FileLocations/) > 0) and defined $flkey){
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
  }
  &print_debug("After the natural: ".join(" ",@fromunique));

  $sqlquery .= join(" , ",(@selectunique))." FROM ".join(" , ",(@fromunique));

  &print_debug("where clause [$where] constraint [$constraint]");
  if ( defined($where) ) {
    $sqlquery .=" WHERE $where";
    if ($constraint ne "") {
      $sqlquery .= " AND $constraint";
    }
  } elsif ($constraint ne "") {
    $sqlquery .= " WHERE $constraint";
  }

  $sqlquery .= $grouping;

  my ($offset, $limit);

  if (defined $valuset{"startrecord"})
    {
      $offset = $valuset{"startrecord"};
    }
  else
    { $offset = 0 };
  if (defined $valuset{"limit"})
    {
      $limit = $valuset{"limit"};
      if($limit <= 0){ $limit = 1000000000;}
    }
  else
    { $limit = 100 };

  $sqlquery .= " LIMIT $offset, $limit";

  &print_debug("Using query: $sqlquery");

  my $sth;

  $sth = $DBH->prepare($sqlquery);
  if ( ! $sth ){
      &print_debug("FileCatalog::run_query : Failed to prepare [$sqlquery]");
      return;
  } else {
      $sth->execute();
      my (@result);
      my (@cols);
      my $rescount = 0;

      while ( @cols = $sth->fetchrow_array() ) {
	  # if field is empty, fetchrow_array() returns undef()
	  # fix it by empty string instead.
	  for (my $i=0 ; $i <= $#cols ; $i++){
	      if( ! defined($cols[$i]) ){ $cols[$i] = "";}
	  }
	  $result[$rescount++] = join($delimeter, (@cols));
      }
      return (@result);
  }
}

#============================================
# deletes the record that matches the current
# context. First it deletes it from the file
# locations. If this makes the current file
# data have no location, it deletes the file
# data too.
# Returns:
# 1 if delete was successfull
# 0 if delete failed
sub delete_record {
  # first delete the file location
  my @deletes;

  if( ! defined($DBH) ){
      &print_message("delete_record","Not connected");
      return 0;
  }

  foreach my $key (keys %keywrds)
    {
      my $field = get_field_name($key);
      my $table = get_table_name($key);

      if ((is_critical($key) == 1) && ($table eq "FileLocations"))
	{
	  if (defined $valuset{$key}){
	      if (get_field_type($key) eq "text")
		{ push (@deletes, "$field = '".$valuset{$key}."'"); }
	      else
		{ push (@deletes, "$field = ".$valuset{$key}); }
	  } else {
	      if ($DEBUG > 0) {
		  &print_debug("ERROR: Cannot delete record.\n".$key." not defined");
	      }
	      return 0;
	  }
	}
      if ((is_critical($key) == 0) && ($table eq "FileLocations"))
	{
	  if (defined($valuset{$key}))
	    {
	      if (get_field_type($key) eq "text")
		{ push (@deletes, "$field = '".$valuset{$key}."'"); }
	      else
		{ push (@deletes, "$field = ".$valuset{$key}); }
	    }
	}
    }

  my $storage = check_ID_for_params("storage");
  if ($storage == 0){
      &print_debug("ERROR: Cannot delete record.","storage not defined");
      return 0;
  } else {
      push (@deletes, "storageTypeID = $storage");
  }
  my $site = check_ID_for_params("site");
  if ($site == 0){
      &print_debug("ERROR: Cannot delete record.","site not defined");
      return 0;
    }
      else { push (@deletes, "storageSiteID = $site"); }
  my $fdata = get_current_file_data();
  if ($fdata == 0)
    {
      &print_debug("ERROR: Cannot delete record.","filedata not defined");
      return 0;
    }
  else { push (@deletes, "fileDataID = $fdata"); }

  my $wheredelete = join(" AND ", (@deletes));

  my $fldelete;
  $fldelete = "DELETE FROM FileLocations WHERE $wheredelete";
  if ($DEBUG > 0){ &print_debug("Executing delete: $fldelete");}

  my $sth;
  $sth = $DBH->prepare( $fldelete );
  if ( ! $sth ){
      &print_debug("FileCatalog::delete_record : Failed to prepare [$fldelete]");
      return 0;
  }
  if ( $sth->execute() )
    {
      # Checking if the given file data has any file locations attached to it
      my $fdquery;
      $fdquery = "SELECT fileLocationID from FileLocations, FileData WHERE FileLocations.fileDataID = FileData.fileDataID AND FileData.fileDataID = $fdata";

      my $stq;
      $stq = $DBH->prepare( $fdquery );
      if ( ! $sth ){
	  &print_debug("FileCatalog::delete_record : Failed to preapre [$fdquery]");
	  return 0;
      }
      $stq->execute();
      if ($stq->rows == 0)
	{
	  # This file data has no file locations - delete it (and its trigger compositions)
	  my $fddelete;
	  $fddelete = "DELETE FROM FileData WHERE fileDataID = $fdata";
	  if ($DEBUG > 0) { &print_debug("Executing $fddelete"); }
	  my $stfdd = $DBH->prepare($fddelete);
	  $stfdd->execute();
	  my $tcdelete = "DELETE FROM TriggerCompositions WHERE fileDataID = $fdata";
	  if ($DEBUG > 0) { &print_debug("Executing $tcdelete"); }
	  my $sttcd = $DBH->prepare($tcdelete);
	  $sttcd->execute();
	}
      return 1;
  } else {
      return 0;
  }
}

#============================================
# Bootstraps a table - meaning it checks if all
# the records in this table are connected to some
# child table
# Prams:
# keyowrd - keword for which to check the table
# dodelete - set to 1 to automaticaly delete the offending records
# Returns
# List of records that are not connected
# or 0 if there were errors or no unconnected records
sub bootstrap {
  if ($_[0] =~ m/FileCatalog/) {
    shift @_;
  }

  if( ! defined($DBH) ){
      &print_message("bootstrap","Not connected");
      return 0;
  }

  my ($keyword, $delete) = (@_);
  my $table = get_table_name($keyword);
  if ($table eq "")
    { return 0; }

  my ( $childtable, $linkfield );
  # Check if this really is a dictionary table
  my $refcount = 0;
  foreach (@datastruct)
    {
      my ($mtable, $ctable, $lfield) = split(",");
      if ($ctable eq $table){
	  # This table is referencing another one - it is not a dictianry!
	  &print_message("bootstrap","$table is not a dictionary table !");
	  return 0;
      }
      if ($mtable eq $table)
	{
	  $childtable = $ctable;
	  $linkfield = $lfield;
	  $refcount++;
	}
    }
  if ($refcount != 1){
      # This table is not refernced by any other table or referenced
      # by more than one - it is not a proper dictionary
      &print_message("bootstrap","$table is not a dictionary table !");
      return 0;
  }

  my $dcquery;
  $dcquery = "select $table.$linkfield FROM $table LEFT OUTER JOIN $childtable ON $table.$linkfield = $childtable.$linkfield WHERE $childtable.runTypeID IS NULL";

  my $stq;
  $stq = $DBH->prepare( $dcquery );
  if( ! $stq ){
      &print_debug("FileCatalog::bootstarp : Failed to prepare [$dcquery]");
      return 0;
  }
  $stq->execute();
  if ($stq->rows > 0)
    {
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
	  $dcdelete = "DELETE FROM $table WHERE $linkfield IN (".join(" , ",(@rows)).")";
	  if ($DEBUG > 0) { &print_debug("Executing $dcdelete"); }
	  my $stfdd = $DBH->prepare($dcdelete);
	  if ($stfdd){
	      $stfdd->execute();
	  } else {
	      &print_debug("FileCatalog::bootstrap : Failed to prepare [$dcdelete]",
			   " Record in $table will not be deleted");
	  }
      }
      return (@rows);
    }
  return 0;
}

#============================================
# Updates the field coresponding to a given keyowrd
# with a new value, replaces the value in the current
# context.The value of the keyword to be modified,
# MUST appear in a previous set_context() statement.
# This is a limitation which has been chosen in
# order to also treat changing values in dictionaries.
#
# Params:
# keyword - the keyword which data is to be updated
# value - new value that should be put into the database
#         instead of the current one
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

  my @updates;

  my ($ukeyword, $newvalue) = (@_);

  my $utable = get_table_name($ukeyword);
  my $ufield = get_field_name($ukeyword);

  foreach my $key (keys %keywrds)
    {
      my $field = get_field_name($key);
      my $table = get_table_name($key);

      # grab keywords which belongs to the same table
      # This will be used as the selection WHERE clause.
      # The ufield is excluded because we use it by default
      # in the SET xxx= WHERE xxx= as an extra MANDATORY
      # clause.
      if (($table eq $utable) && ($field ne $ufield))
	{
	  if (defined($valuset{$key}))
	    {
	      if (get_field_type($key) eq "text")
		{ push (@updates, "$field = '".$valuset{$key}."'"); }
	      else
		{ push (@updates, "$field = ".$valuset{$key}); }
	    }
	}
    }
  my $whereclause = join(" AND ",(@updates));

  if ($utable eq ""){
      &print_debug("ERROR: $ukeyword does not have an associated table","Cannot update");
      return 0;
  }


  my $qupdate;
  if (get_field_type($ukeyword) eq "text"){
      $qupdate = "UPDATE $utable SET $ufield = '$newvalue' WHERE $ufield = '".
	  $valuset{$ukeyword}."'";
  } else {
      $qupdate = "UPDATE $utable SET $ufield = $newvalue WHERE $ufield = ".
	  $valuset{$ukeyword};
  }
  if ($whereclause ne "")
    { $qupdate .= " AND $whereclause"; }
  if ($DEBUG > 0){
      &print_debug("Executing update: $qupdate\n");
  }

  my $sth;
  $sth = $DBH->prepare( $qupdate );
  if (!$sth){
      &print_debug("FileCatalog::update_record : Failed to prepare [$qupdate]");
      return 0;
  } else {
      if ( $sth->execute() ){
	  return 1;
      } else {
	  return 0;
      }
  }
}

#============================================
# Updates the fields in FileLocations table - mainly
# used for updating availability and persistency
#
# Params:
# keyword - the keyword which data is to be updated
# value - new value that should be put into the database
#         instead of the current one
sub update_location {
  if ($_[0] =~ m/FileCatalog/) {
    my $self = shift;
  }
  if( ! defined($DBH) ){
      &print_message("update_location","Not connected");
      return 0;
  }


  my @updates;

  my ($ukeyword, $newvalue) = (@_);

  my $utable = get_table_name($ukeyword);
  my $ufield = get_field_name($ukeyword);

  my @files;

  my $delim;

  $delim  = get_delimeter();

  # Get the list of the files to be updated
  set_delimeter("::");
  set_context("all=1");
  @files = run_query("id","filename","path");
  # Bring back the previous delimeter
  set_delimeter($delim);

  delete $valuset{"path"};

  foreach my $key (keys %keywrds)
    {
      my $field = get_field_name($key);
      my $table = get_table_name($key);

      # grab keywords which belongs to the same table
      # This will be used as the selection WHERE clause.
      # The ufield is excluded because we use it by default
      # in the SET xxx= WHERE xxx= as an extra MANDATORY
      # clause.
      if (($table eq $utable) && ($field ne $ufield))
	{
	  if (defined($valuset{$key}))
	    {
	      if (get_field_type($key) eq "text")
		{ push (@updates, "$field = '".$valuset{$key}."'"); }
	      else
		{ push (@updates, "$field = ".$valuset{$key}); }
	    }
	}
    }
  my $whereclause = join(" AND ",(@updates));

  if ($utable eq ""){
      &print_debug("ERROR: $ukeyword does not have an associated table",
		   "Cannot update");
      return 0;
  }


  foreach my $line (@files) {
      print "Returned line: $line\n";
      my $qupdate;

      my ($flid, $fname, $path) = split("::",$line);

      if (get_field_type($ukeyword) eq "text")
      { $qupdate = "UPDATE $utable SET $ufield = '$newvalue' WHERE $ufield = '".$valuset{$ukeyword}."'"; }
      else
      { $qupdate = "UPDATE $utable SET $ufield = $newvalue WHERE $ufield = ".$valuset{$ukeyword}; }
      $qupdate .= " AND fileLocationID = $flid";
      if ($DEBUG > 0){
	  &print_debug("Executing update: $qupdate");
      }

      my $sth;
      $sth = $DBH->prepare( $qupdate );
      if ( ! $sth ){
	  &print_debug("FileCatalog::update_location : Failed to prepare [$qupdate]");
      } else {
	  if ( $sth->execute() ){
	      &print_debug("Update succeded");
	  } else {
	      &print_debug("Update failed");
	  }
      }
  }
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
sub set_field {
}

#============================================
sub debug_on
{
    if ($_[0] =~ m/FileCatalog/) {
	shift @_;
    }
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
	    print "$line\n";
	}
    }
}


#============================================

sub print_message
{
    my($routine,@lines)=@_;
    my($line);
    foreach $line (@lines){
	chomp($line);
	print "$dbname :: $routine : $line\n";
    }
    return;
}


#============================================

sub destroy {
  my $self = shift;
  clear_context();
  if ( defined($DBH) ) {
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

