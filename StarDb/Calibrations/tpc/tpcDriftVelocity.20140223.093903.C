TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54009
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.89803; // +/- 0.000131898 cm/us East: Slope = 5.89803 +/- 0.000131898 DV = 5.89803 +/- 0.000131898
  row.laserDriftVelocityWest	 =   5.89678; // +/- 6.32805e-05 cm/us West: Slope = 5.89803 +/- 0.000131898 DV = 5.89678 +/- 6.32805e-05
//row.scaleY                  	 = 4.39994e-07;// +/-9.85192e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.89702 +/- 5.7054e-05
};
