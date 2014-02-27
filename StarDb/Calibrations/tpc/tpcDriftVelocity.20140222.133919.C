TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53022
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.89491; // +/- 5.46185e-05 cm/us East: Slope = 5.89491 +/- 5.46185e-05 DV = 5.89491 +/- 5.46185e-05
  row.laserDriftVelocityWest	 =   5.89296; // +/- 4.25288e-05 cm/us West: Slope = 5.89491 +/- 5.46185e-05 DV = 5.89296 +/- 4.25288e-05
//row.scaleY                  	 = 2.72066e-06;// +/-1.19421e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.8937 +/- 3.3556e-05
};
