/***************************************************************************
 *
 * $Id: StDbDefs.hh,v 1.9 2000/03/28 17:03:18 porter Exp $
 *
 * Author: R. Jeff Porter
 ***************************************************************************
 *
 * Description:  enum definitions for DataBase Type & Domain.
 *               This allows compile-time checks for standard DB accesses.
 *               The StDbManager _does_ support access by names (strings) for
 *               greater flexibility - though poorer compile-time safegaurds
 *
 ***************************************************************************
 *
 * $Log: StDbDefs.hh,v $
 * Revision 1.9  2000/03/28 17:03:18  porter
 * Several upgrades:
 * 1. configuration by timestamp for Conditions
 * 2. query by whereClause made more systematic
 * 3. conflict between db-stored comments & number lists resolved
 * 4. ensure endtime is correct for certain query falures
 * 5. dbstl.h->handles ObjectSpace & RogueWave difference (Online vs Offline)
 *
 * Revision 1.8  2000/01/27 05:54:33  porter
 * Updated for compiling on CC5 + HPUX-aCC + KCC (when flags are reset)
 * Fixed reConnect()+transaction model mismatch
 * added some in-code comments
 *
 * Revision 1.7  2000/01/10 20:37:53  porter
 * expanded functionality based on planned additions or feedback from Online work.
 * update includes:
 * 	1. basis for real transaction model with roll-back
 * 	2. limited SQL access via the manager for run-log & tagDb
 * 	3. balance obtained between enumerated & string access to databases
 * 	4. 3-levels of diagnostic output: Quiet, Normal, Verbose
 * 	5. restructured Node model for better XML support
 *
 * Revision 1.6  1999/12/29 13:49:35  porter
 * fix for Solaris-CC4.2 within StRoot make (cons)...
 * replaced #include <config.h> with #include <ospace/config.h>
 *
 * Revision 1.5  1999/12/28 21:31:41  porter
 * added 'using std::vector' and 'using std::list' for Solaris CC5 compilation.
 * Also fixed some warnings arising from the CC5 compiles
 *
 * Revision 1.4  1999/09/30 02:06:04  porter
 * add StDbTime to better handle timestamps, modify SQL content (mysqlAccessor)
 * allow multiple rows (StDbTable), & Added the comment sections at top of
 * each header and src file
 *
 **************************************************************************/
#ifndef STDBDEFS_HH
#define STDBDEFS_HH

// enumerated standard set of database types

enum StDbType { dbStDb=0, dbServer, dbRunLog, dbConfigurations, dbConditions, dbCalibrations, dbGeometry, dbRunCatalog, dbRunParams, dbTestScheme, dbUser};

// enumerated standard set of database domains

enum StDbDomain {dbDomainUnknown=0, dbStar, dbTpc, dbEmc, dbFtpc, dbSvt, dbCtb, dbTrg, dbDaq, dbScaler, dbGlobal, dbL3 };

#include "dbstl.h"

#endif










