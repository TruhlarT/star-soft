#include <TROOT.h>
#include <TServerSocket.h>
#include <TSocket.h>
#include <TMessage.h>
#include <TMonitor.h>
#include "JTMonitor.h"
#include <TClass.h>

#include "DAQ_READER/daqReader.h"

#include "Jevp/StJevpPlot/EvpMessage.h"
#include "Jevp/StJevpPlot/JevpPlot.h"
#include "DisplayDefs.h"
#include "Jevp/StJevpPlot/RunStatus.h"
#include "EvpConstants.h"
#include "Jevp/StJevpPlot/BuilderStatus.h"

#define MAX_DISPLAY_DEFS 20

class JevpServer {
 public:
  int log_output;
  char *log_dest;
  int log_port;
  char *log_level;

  TServerSocket *ssocket;
  JTMonitor *mon;
  
  int throttleAlgos;

  char *pdfdir;        // pdf dir
  char *refplotdir;    // ref plot dir
  char *basedir;       // base for config files...
  char *diska;
  int myport;

  daqReader *rdr;

  char *displays_fn;      // Display Information...
  DisplayFile *displays;
  char *serverTags;

  int eventsThisRun;
  // int run;                // run number
  int nodb;               // send to db?
  int die;                // die when the run is over? or wait for the next run...
  char *daqfilename;      // NULL if running real data

  RunStatus runStatus;    // are we in a run or not?
  TList builders;         
  

  JevpServer() {
    myport = JEVP_PORT;
    ssocket = NULL;
    mon = NULL;
    refplotdir = (char *)DEFAULT_REF_PLOT_DIR;
    diska = (char *)"/";
 
    displays = NULL;
    displays_fn = NULL;
    
    basedir = (char *)DEFAULT_BASEDIR;
    refplotdir = (char *)DEFAULT_REF_PLOT_DIR;
    pdfdir = (char *)DEFAULT_PDFDIR;
    nodb = 0;
    die = 0;
    daqfilename = NULL;
    serverTags = NULL;
  };
  
  static void main(int argc, char *argv[]);
  void parseArgs(int argc, char *argv[]);
  int init(int port, int argc, char *argv[]);

  void performStopRun();                                 // Handle run status
  void performStartRun();
  void clearForNewRun();
  int calculateAndUpdateRunStatus(BuilderStatus *changedBuilder);
  void addServerTag(char *tag);
  void addServerTags(char *tags);


  void archive_display_file();                           // Archive utilities
  void addToPallete(JevpPlot *plot);

  JevpPlot *getJevpSummaryPlot();                        // Build The Summary plot...

  int handleEvent();
  void handleClient(int delay);

  void handleEvpMessage(TSocket *s, EvpMessage *msg);
  void handleEvpPlot(TSocket *s, JevpPlot *plot);
  void handleGetPlot(TSocket *s, char *argstring);
  void handleSwapRefs(char *args);

  double liney(double x);


  int getMaxRef(char *name);                             // Reference plots...
  void shiftRefPlotsUp(char *name, int idx);
  void shiftRefPlotsDown(char *name, int idx);
  void deleteReferencePlot(char *name, int idx);
  void saveReferencePlot(JevpPlot *plot);

  // Write the histograms out....
  int writeHistogramLeavesPdf(DisplayNode *node, PdfIndex *index, index_entry *prevIndexEntry, char *filename, int page);
  int writeNodePdf(DisplayNode *node, PdfIndex *index, index_entry *prevIndexEntry, char *filename, int page, int nosibs);
  void writeRunPdf(int display, int run);
  void writePdf(char *fn, int display, int combo_index);



  JevpPlot *getPlot(char *name);



  void dump();
  int updateDisplayDefs();
  void DrawCrossOfDeath(char *str);

  char *getParamFromString(char *dest, char *source, char *param=NULL);
  void getMonitorString(char *s, EvpMessage *m);




  int execScript(const char *name,  char *args[], int waitforreturn=1);
};
