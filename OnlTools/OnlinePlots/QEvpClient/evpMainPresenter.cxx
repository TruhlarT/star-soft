#include "EvpPresenter.h"
#include "PresenterGui.h"
#include "PresenterConnect.h"
#include "evpMainPresenter.h"
#include "qapplication.h"
#include "qtimer.h"

#include "EvpUtil.h"
#include "TSystem.h"

//---- Main program ------------------------------------------------------
int evpMainPresenter::main(int argc, char **argv )
{


  cout << "command line arguments are: " << endl;
  for ( int i=0; i<argc; i++) {
    cout << i << " :   " << argv[i] << endl;
  }
  cout << endl;

  if ( argc==2 ) {
    EvpUtil::mMapFilePath = argv[1];
    cout << " shared memory file set to " << EvpUtil::mMapFilePath << endl;
  }

//     TMapFile* mfile = TMapFile::Create(EvpUtil::mMapFilePath,"READ",EvpUtil::mSharedMemorySize);

    PresenterGui* gui = new PresenterGui();

#if 0
    TSeqCollection* col = gSystem->GetListOfFileHandlers();
    TIter next(col);
    TFileHandler* o=0;
    while ( o=(TFileHandler*) next() ) {
      cout << o->GetFd() << endl;
      if ( o->GetFd()==0 ) {
	o->Remove();
	break;
      }
    }
#endif


    EvpUtil::ReadCanvasDefinitions();
    

    EvpPresenter* presenter = new EvpPresenter();
    PresenterConnect* con = new PresenterConnect(gui,presenter);
    presenter->Connect();
    gui->resize(500,500);
    gui->show();
    gui->TurnLive();
    // Everything is ready. It is safe to fire the event loop now !
    QTimer::singleShot (0,gui,SLOT(GetNextEvent()));
    //presenter->run();

//    delete presenter;
//    delete con;
//    cout << "good bye " << endl;
    return 0;
}
