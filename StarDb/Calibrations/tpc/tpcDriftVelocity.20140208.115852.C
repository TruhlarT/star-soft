TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39118
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50674; // +/- 0.000102627 cm/us East: Slope = 0.208087 +/- 0.022635 DV = 5.50674 +/- 0.000102627
  row.laserDriftVelocityWest	 =   5.50093; // +/- 4.97538e-05 cm/us West: Slope = 0.147722 +/- 0.0103284 DV = 5.50093 +/- 4.97538e-05
//row.scaleY                  	 = 4.6904e-06;// +/-4.62684e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50204 +/- 4.477e-05
};
