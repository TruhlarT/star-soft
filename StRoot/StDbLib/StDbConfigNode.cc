/***************************************************************************
 *
 * $Id: StDbConfigNode.cc,v 1.10 1999/12/28 21:31:41 porter Exp $
 *
 * Author: R. Jeff Porter
 ***************************************************************************
 *
 * Description:  Node (directory) to hold list of dbtables
 *
 ***************************************************************************
 *
 * $Log: StDbConfigNode.cc,v $
 * Revision 1.10  1999/12/28 21:31:41  porter
 * added 'using std::vector' and 'using std::list' for Solaris CC5 compilation.
 * Also fixed some warnings arising from the CC5 compiles
 *
 * Revision 1.9  1999/12/03 22:24:00  porter
 * expanded functionality used by online, fixed bug in
 * mysqlAccessor::getElementID(char*), & update StDbDataSet to
 * conform to changes in Xml reader & writer
 *
 * Revision 1.8  1999/09/30 02:06:03  porter
 * add StDbTime to better handle timestamps, modify SQL content (mysqlAccessor)
 * allow multiple rows (StDbTable), & Added the comment sections at top of
 * each header and src file
 *
 **************************************************************************/
#include <iostream.h>
#include <strings.h>

#include "StDbConfigNode.hh"
#include "StDbManager.hh"
#include "StDbFactories.hh"
#include "TableIter.hh"
#include "StDbTable.h"
#include "StDbServer.hh"

////////////////////////////////////////////////////////////////

StDbConfigNode::StDbConfigNode(StDbConfigNode* parent, const char* nodeName, const char* configName){

  zeroNodes();
  mdbType = parent->getDbType();
  mdbDomain = parent->getDbDomain();
  setName(nodeName);
  setConfigName(configName);
  setParentNode(parent);

  // If StarDb Type, then name holds map to real Db type
  // while the domain may still be StarDb
  // Else if StarDb domain, then name holds map to real domain type
  // Else both type & domain are that of parent

  if(mdbType==StarDb){
    mdbType=StDbManager::Instance()->getDbType(mnodeName);
  } else if(mdbDomain==Star){
    mdbDomain=StDbManager::Instance()->getDbDomain(mnodeName);
  }

}

////////////////////////////////////////////////////////////////

StDbConfigNode::StDbConfigNode(StDbType type, StDbDomain domain, const char* nodeName, const char* configName){

  zeroNodes();
  mdbType = type;
  mdbDomain = domain;
  setName(nodeName);
  setConfigName(configName);

  // If StarDb Type, then name holds map to real Db type
  // while the domain may still be StarDb
  // Else if StarDb domain, then name holds map to real domain type
  // Else both type & domain are that of parent
  /*
  if(mdbType==StarDb){
    mdbType=StDbManager::Instance()->getDbType(mnodeName);
  } else if(mdbDomain==Star){
    mdbDomain=StDbManager::Instance()->getDbDomain(mnodeName);
  }
  */
}
////////////////////////////////////////////////////////////////

StDbConfigNode::~StDbConfigNode(){

deleteTables();
deleteChildren();
if(mconfigName) delete [] mconfigName;
if(mnodeName) delete [] mnodeName;

};



////////////////////////////////////////////////////////////////

void 
StDbConfigNode::setName(const char* name){ 

if(mnodeName) delete [] mnodeName;
mnodeName = new char[strlen(name)+1];
strcpy(mnodeName,name);

}

////////////////////////////////////////////////////////////////

void 
StDbConfigNode::setConfigName(const char* name){ 

if(!name)return;
if(mconfigName) delete [] mconfigName;
mconfigName = new char[strlen(name)+1];
strcpy(mconfigName,name);

}

////////////////////////////////////////////////////////////////

void
StDbConfigNode::buildTree(){

 StDbServer* server=0;
 TableIter* itr=0;
 StDbTableI* table=0;

 server = StDbManager::Instance()->findServer(mdbType, mdbDomain);
 if(server)server->QueryDb(this);
 itr = getTableIter();
 while(!itr->done()){
   table = itr->next();
   server->QueryDescriptor((StDbTable*)table);
 }
 if(itr)delete itr;
 if(mfirstChildNode)mfirstChildNode->buildTree();
 if(mnextNode)mnextNode->buildTree();

}

/////////////////////////////////////////////////////////////////

void
StDbConfigNode::printTree(){

 if(mfirstChildNode){
   //   cout << mnodeName << " Sends to Child" << mfirstChildNode->getName() << endl;
   mfirstChildNode->printTree();
 }
 if(mnextNode){
   //   cout << mnodeName << " Sends To Sib" << mnextNode->getName() << endl;
   mnextNode->printTree();
 }

}

////////////////////////////////////////////////////////////////////////

StDbTable*
StDbConfigNode::addDbTable(const char* tableName, const char* version, bool isBaseLine){
  // just like addTable but also loads the descriptor from the database

  StDbTable* table = addTable(tableName,version,isBaseLine);
  StDbServer* server = StDbManager::Instance()->findServer(mdbType, mdbDomain);
  if(server)server->QueryDescriptor(table);

  return table;
}

////////////////////////////////////////////////////////////////////////

StDbTable*
StDbConfigNode::addTable(const char* tableName, const char* version, bool isBaseLine){

  if(!mfactory)mfactory = StDbFactories::Instance()->getFactory(mdbType);

  if(!mfactory) cout << " No Factory " << endl;
  StDbTable* table = 0;
  table = mfactory->getDbTable(tableName,0);

  if(table){
    table->setVersion((char*)version);
    //    table->setElementID(elementID);
    table->setDbType(mdbType);
    table->setDbDomain(mdbDomain);
    table->setIsBaseLine(isBaseLine);
    mTables.push_back(table);
    if(!mhasData)mhasData=true;
  } else {
    cout << " Could not Find table " << tableName << endl;
  }

return table;
}

////////////////////////////////////////////////////////////////
StDbTable*
StDbConfigNode::findLocalTable(const char* name){

  TableList::iterator itr;
  StDbTable* table=0;
    for(itr = mTables.begin(); itr!=mTables.end(); ++itr){
      if((*itr)->checkTableName(name)){
	table=*itr;
        break;
      }
    }

return table;
}
////////////////////////////////////////////////////////////////

void
StDbConfigNode::removeTable(StDbTable* table){
 
  if(!table)return;


  TableList::iterator itr;
  StDbTable* myTable=0;

  do {
    for(itr = mTables.begin(); itr!=mTables.end(); ++itr){
        myTable=*itr;
        if(myTable && compareTables(myTable,table)){
                 mTables.erase(itr);
                 break;
        }
        myTable=0;
    }
  } while (mTables.begin() != mTables.end());


}


////////////////////////////////////////////////////////////////
/*
StDbTable*
StDbConfigNode::findTable(const char* tableName, const char* version, int elementID){

  TableList::iterator itr;
  StDbTable* table=0;
  char* mtableName=0;
  char* mversion=0;
  int meID;

  do {
    for(itr = mTables.begin(); itr!=mTables.end(); ++itr){
        table=*itr;
        if(table){
          mtableName=table->getTableName();
          mversion=table->getVersion();
          meID=table->getElementID();
          if(strcmp(tableName,mtableName)==0 &&
           strcmp(version,mversion)==0 && elementID==meID){
            break;
          } else { delete [] mtableName; delete [] mversion;}
        }
        table=0;
    }
  } while (mTables.begin() != mTables.end());

if(mtableName)delete [] mtableName;
if(mversion)delete [] mversion;

return table;
}
*/

////////////////////////////////////////////////////////////////
bool
StDbConfigNode::compareTables(StDbTable* tab1, StDbTable* tab2){

bool retVal=false;
// compare name & version
    char* name1=tab1->getTableName();
    char* version1 = tab1->getVersion();
    char* name2=tab2->getTableName();
    char* version2 = tab2->getVersion();

    if(!(strcmp(name1,name2)==0) || !(strcmp(version1,version2)==0)){
      delete [] name1; delete [] name2; delete [] version1; delete [] version2;
      return retVal;
    }

    // compare number of rows
    int nRows1 = tab1->GetNRows();
    int nRows2 = tab2->GetNRows();
    if(nRows1 != nRows2) return retVal;

    // compare each row identifier
    int* elements1 = tab1->getElementID();
    int* elements2 = tab2->getElementID();
    bool check=true;
    for(int i=0;i<nRows1;i++){
      if(elements1[i] != elements2[i]){
        check = false;
        break;
      }
    }
    if(check)retVal=true;

return retVal;
}




////////////////////////////////////////////////////////////////

TableIter*
StDbConfigNode::getTableIter(){

  TableIter* itr = new TableIter();
  itr->init(this);

return itr;
}

////////////////////////////////////////////////////////////////

void
StDbConfigNode::deleteTree(){

if(hasChildren())getFirstChildNode()->deleteTree();
if(mnextNode)mnextNode->deleteTree();
if(mnextNode)delete mnextNode;
if(mfirstChildNode)delete mfirstChildNode;

}


////////////////////////////////////////////////////////////////

void
StDbConfigNode::deleteChildren(){
if(hasChildren())getFirstChildNode()->deleteTree();
}

////////////////////////////////////////////////////////////////

StDbConfigNode*
StDbConfigNode::findConfigNode(StDbType type, StDbDomain domain){

  //
  // Searches for the "highest" node of type & domain
  // e.g. if request Calibrations , tpc & node is of that
  // type & domain it checks parent 1st and if it is also
  // that type & domain returns this call to the parent node
  // .. else continue down the tree ...

StDbConfigNode* node = 0;

  if(type == mdbType && domain == mdbDomain){
    if(mparentNode && mparentNode->isNode(type,domain))return mparentNode->findConfigNode(type,domain);
    return this;
    }
   if(hasChildren())node=mfirstChildNode->findConfigNode(type,domain);
   if(node)return node;
   if(mnextNode)node = mnextNode->findConfigNode(type,domain);

return node;
}

////////////////////////////////////////////////////////////////

void
StDbConfigNode::resetConfig(const char* configName){

if(mfirstChildNode)mfirstChildNode->deleteTree();
if(mhasData)deleteTables();
setConfigName(configName);
buildTree();

}

////////////////////////////////////////////////////////////////

void StDbConfigNode::setParentNode(StDbConfigNode* parent){

mparentNode = parent;
 if(parent->hasChildren()){
   StDbConfigNode* sib = parent->getFirstChildNode();
   sib->appendNode(this);
  } else {
  parent->setFirstChildNode(this);
  }

}

////////////////////////////////////////////////////////////////

void StDbConfigNode::appendNode(StDbConfigNode* node){

  if(mnextNode){
     mnextNode->appendNode(node);
  } else {
     mnextNode = node;
  }

}
  
////////////////////////////////////////////////////////////////

void 
StDbConfigNode::setFirstChildNode(StDbConfigNode* node){
  mfirstChildNode = node;
  
} 

////////////////////////////////////////////////////////////////

char * 
StDbConfigNode::getName() const { 
if(!mnodeName)return mnodeName;

char* retString = new char[strlen(mnodeName)+1];
strcpy(retString,mnodeName);
return retString;
}

////////////////////////////////////////////////////////////////

char * 
StDbConfigNode::getConfigName() const { 

if(!mconfigName)return mconfigName;

char* retString = new char[strlen(mconfigName)+1];
strcpy(retString,mconfigName);
return retString;
}

////////////////////////////////////////////////////////////////

void
StDbConfigNode::deleteTables(){

  TableList::iterator itr;
  StDbTable* table;

  do {
    for(itr = mTables.begin(); itr!=mTables.end(); ++itr){
        table=*itr;
        mTables.erase(itr);
        delete table;
        break;
    }
  } while (mTables.begin() != mTables.end());

}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////











