#ifndef STDBSERVER_HH
#define STDBSERVER_HH

#include "StDbDefs.hh"    // enumeration of type & domain

class StDbTable;
class StDbConfigNode;

#include "tableQuery.hh" // includes the query

class StDbServer {

private:
  
  char* mserverName;
  char* mhostName;
  char* munixSocket;
  int   mportNumber;
  char* mdbName;

  StDbType mdbType;
  StDbDomain mdbDomain;
  char* mdomainName;
  char* mtypeName;
  bool  mconnectState;
  bool  misDefault;

  tableQuery* mdatabase; // low level query access of DataBase

protected:

  virtual void initServer();
  char* mstringDup(const char * str) const;


public:

  StDbServer(): mserverName(0), mhostName(0), munixSocket(0), mdbName(0), mconnectState(false), mdatabase(0), misDefault(false), mdomainName(0), mtypeName(0) {};
  StDbServer(StDbType type, StDbDomain domain);
  StDbServer(StDbType type, StDbDomain domain, const char* typeName, const char* domainName);
  //  StDbServer(const char* server, const char* hostname, int port);
  virtual ~StDbServer();

  StDbServer(StDbServer& server);
  //  virtual StDbServer* getServer(const char* dbName);

  virtual void setDbName(const char* dbName);
  virtual void setDataBase(StDbType type, StDbDomain domain, const char* typeName, const char* domainName);


  virtual void setHostName(const char* name);
  virtual void setUnixSocket(const char* name);
  virtual void setDomainName(const char* name);
  virtual void setTypeName(const char* name);
  virtual void setPortNumber(int port){ mportNumber = port;}
  virtual void setDbType(StDbType type) { mdbType = type;}
  virtual void setDbDomain(StDbDomain domain) { mdbDomain=domain;}
  virtual void setServerName(const char* name);
  virtual void setIsDefaultServer() {misDefault=true;};

  virtual char* getDbName() const;
  virtual StDbType getDbType() const { return mdbType; };
  virtual StDbDomain getDbDomain() const { return mdbDomain; };
 
  virtual char* getServerName() const ;
  virtual char* getHostName() const ;
  virtual char* getUnixSocket() const;
  virtual int   getPortNumber() const { return mportNumber;} ;
  virtual char* getTypeName() const ;
  virtual char* getDomainName() const ;

  virtual void  init() { initServer(); };
  virtual bool  isconnected() const { return mconnectState;};
  virtual bool  isDefault() const { return misDefault; };
  
//Here's the real work of the server -> providing Query access to the DataBase

  virtual void QueryDb(StDbTable* table);
  virtual void QueryDb(StDbConfigNode* node);
  virtual void QueryDescriptor(StDbTable* table);
  virtual void WriteDb(StDbTable* table);


};

#endif
















