#
# $Id: BaseTables.sql,v 1.2 2000/05/03 19:00:09 porter Exp $
#
# Author: R. Jeff Porter
#***************************************************************************
#
# Description:  SQL for installing base set of tables for STAR-API
#               These tables exist in each database
#
#****************************************************************************
# 
# $Log: BaseTables.sql,v $
# Revision 1.2  2000/05/03 19:00:09  porter
# fixed header file output option
#
# Revision 1.1  2000/04/28 14:09:03  porter
# Base tables definition is SQL form
#
#
############################################################
############################################################
#
#  schema & schema-evolution tables:  'schema' & 'structure'
#
############################################################

#
# Table structure for table 'schema'
#
DROP TABLE IF EXISTS schema;
CREATE TABLE schema (
  name char(80) DEFAULT '' NOT NULL,
  type char(18) DEFAULT '' NOT NULL,
  storeType enum('ascii','bin') DEFAULT 'ascii' NOT NULL,
  length char(18) DEFAULT '1',
  schemaID int(11) DEFAULT '1' NOT NULL,
  ID int(11) DEFAULT '0' NOT NULL auto_increment,
  structName char(80) DEFAULT '' NOT NULL,
  structID smallint DEFAULT '0' NOT NULL,
  position smallint DEFAULT '0' NOT NULL,
  Linuxoffset smallint DEFAULT '0' NOT NULL,
  entryTime timestamp(14),
  Comment varchar(255),
  KEY ID (ID),
  PRIMARY KEY (name,ID)
);

#
# Table structure for table 'structure'
#
DROP TABLE IF EXISTS structure;
CREATE TABLE structure (
  name char(80) DEFAULT '' NOT NULL,
  lastSchemaID int(11) DEFAULT '1' NOT NULL,
  ID smallint DEFAULT '0' NOT NULL auto_increment,
  entryTime timestamp(14),
  Comment varchar(255),
  KEY ID (ID),
  PRIMARY KEY (name,ID)
);

#############################################################
#
#  Named reference table:  'Nodes' 
#  Hierarchy of named objects: 'NodeRelation'  
#
#############################################################

#
# Table structre for table 'Nodes'
#

DROP TABLE IF EXISTS Nodes;
CREATE TABLE Nodes (
  name char(80) DEFAULT '' NOT NULL,
  versionKey char(128) DEFAULT 'default' NOT NULL,
  nodeType enum('DB','directory','table','Config') DEFAULT 'directory' NOT NULL,
  structName char(80) DEFAULT NULL,
  elementID varchar(255) DEFAULT 'None',
  baseLine enum('Y','N') DEFAULT 'N' NOT NULL,
  isBinary enum('Y','N') DEFAULT 'N' NOT NULL,
  isIndexed enum('Y','N') DEFAULT 'Y' NOT NULL,
  ID int(11) DEFAULT '0' NOT NULL auto_increment,
  entryTime timestamp(14),
  Comment varchar(255),
  KEY ID (ID),
  PRIMARY KEY (name,versionKey)
);

#
# Table structre for table 'NodeRelation'
#
DROP TABLE IF EXISTS NodeRelation;
CREATE TABLE NodeRelation (
  ID int(11) DEFAULT '0' NOT NULL auto_increment,
  ParentID int(11) DEFAULT '0' NOT NULL,
  NodeID int(11) DEFAULT '0' NOT NULL,
  ConfigID int(11) Default '0' not null,
  entryTime timestamp(14),
  KEY ID (ID),
  Primary KEY (ParentID, NodeID, ConfigID)
);

#
# Table structure for table 'dbCollection'
#
DROP TABLE IF EXISTS dbCollection;
CREATE TABLE dbCollection (
  dataID int(11) DEFAULT '0' NOT NULL auto_increment,
  entryTime timestamp(14),
  name varchar(64) NOT NULL,
  KEY dataID (dataID),
  KEY name (name)
);



############################################################
#
#  index & data tables:  'dataIndex' & 'bytes' (for pure binary)
#                        general data tables are created at
#                        time c-struct is loaded into db.
#
############################################################

#
# Table structure for table 'dataIndex'
#
DROP TABLE IF EXISTS dataIndex;
CREATE TABLE dataIndex (
  count int(11) DEFAULT '0' NOT NULL auto_increment,
  nodeID smallint DEFAULT '0' NOT NULL,
  entryTime timestamp(14),
  schemaID int(11) DEFAULT '0' NOT NULL,
  beginTime datetime DEFAULT '1970-01-01 00:00:00' NOT NULL,
  version char(128) DEFAULT 'default' NOT NULL,
  flavor  char(8) default 'ofl' NOT NULL,
  elementID smallint DEFAULT '0' NOT NULL,
  numRows smallint DEFAULT '1' NOT NULL,
  deactive int unsigned DEFAULT '0' NOT NULL,
  dataID int(11) NOT NULL,
  KEY count (count),  
  KEY dataID (dataID),
  KEY flavor (flavor),
  PRIMARY KEY (nodeID,beginTime,flavor,elementID,deactive,version)
);

#
# Table structre for table 'bytes'
#
DROP TABLE IF EXISTS bytes;
CREATE TABLE bytes (
  dataID  int(11) DEFAULT '0' NOT NULL auto_increment,
  entryTime timestamp(14),
  bytes longblob,
  Primary Key (dataID)
);


############################################################
#
# Online's Catalog of Configurations:  'CatalogNode' &
#                                      'CatalogNodeRelation'  
#
############################################################

#
# Table structure for table 'CatalogNodes'
#
DROP TABLE IF EXISTS CatalogNodes;
CREATE TABLE CatalogNodes (
  Name varchar(80) DEFAULT '' NOT NULL,
  Author varchar(80) DEFAULT '' NOT NULL,
  ID int(11) DEFAULT '0' NOT NULL auto_increment,
  entryTime timestamp(14),
  Comment varchar(255),
  ConfigID int(11) DEFAULT '0',
  beginTime datetime DEFAULT '1970-01-01 00:00:00' NOT NULL,
  isFolder enum('Y','N') DEFAULT 'N' NOT NULL,
  KEY ID (ID),
  PRIMARY KEY (Name,ID,beginTime)
);

#
# Table structure for table 'CatalogNodeRelation'
#
DROP TABLE IF EXISTS CatalogNodeRelation;
CREATE TABLE CatalogNodeRelation (
  ID int(11) DEFAULT '0' NOT NULL auto_increment,
  ParentID int(11) DEFAULT '0' NOT NULL,
  ChildID int(11) DEFAULT '0' NOT NULL,
  entryTime timestamp(14),
  KEY ID (ID),
  KEY ParentID (ParentID),
  KEY ChildID (ChildID)
);

###############################################################
#
#  Log Tables for monitoring updates to structure 
#   - not data entry updates - 
#
###############################################################

#
# Table structure for table 'ConfigLog'
#
DROP TABLE IF EXISTS ConfigLog;
CREATE TABLE ConfigLog (
  ID int DEFAULT '0' NOT NULL auto_increment,
  ParentID int(11) DEFAULT '0' NOT NULL,
  NodeID int(11) DEFAULT '0' NOT NULL,
  ConfigID int(11) Default '0' not null,
  Action enum('add','delete') DEFAULT 'add' NOT NULL,
  Comment varchar(255),
  entryTime timestamp(14),
  Key ID (ID)
);

#
# Table structure for table 'StructureLog'
#
DROP TABLE IF EXISTS StructureLog;
CREATE TABLE StructureLog (
  ID int DEFAULT '0' NOT NULL auto_increment,
  structID smallint DEFAULT '0' NOT NULL,
  thisSchemaID smallint DEFAULT '0' NOT NULL,
  Action enum('new','evolve') DEFAULT 'new' NOT NULL,
  Comment varchar(255),
  entryTime timestamp(14),
  Key ID (ID)
);

#
# Table structure for table 'indexLog'
#
DROP TABLE IF EXISTS indexLog;
CREATE TABLE indexLog (
  ID int DEFAULT '0' NOT NULL auto_increment,
  count int Default '0' NOT NULL,
  changeType enum('deactive','delete','modtime') Default 'deactive' Not NULL,
  comment varchar(255),
  entryTime timestamp(14),
  Key ID (ID)
);








