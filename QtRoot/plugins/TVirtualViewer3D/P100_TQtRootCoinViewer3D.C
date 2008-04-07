void P100_TQtRootCoinViewer3D()
{
   gPluginMgr->AddHandler("TVirtualViewer3D", "oiv", "TQtRootCoinViewer3D",
      "RQIVTGL", "TQtRootCoinViewer3D(TVirtualPad*)");
}
