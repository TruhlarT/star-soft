void P110_TQtGedEditor()
{
   gPluginMgr->AddHandler("TVirtualPadEditor", "Ged", "TQtGedEditor",
      "QtGed", "TQtGedEditor(TCanvas*)");
}
