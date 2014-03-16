TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 58049
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5133; // +/- 2.79944e-05 cm/us East: Slope = 0.0880254 +/- 0.00511136 DV = 5.5133 +/- 2.79944e-05
  row.laserDriftVelocityWest	 =   5.51537; // +/- 3.5287e-05 cm/us West: Slope = -0.315925 +/- 0.0070783 DV = 5.51537 +/- 3.5287e-05
//row.scaleY                  	 = 1.81507e-06;// +/-1.62849e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5141 +/- 2.19311e-05
};
