TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 67008
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.519; // +/- 3.20661e-05 cm/us East: Slope = -0.969266 +/- 0.00600139 DV = 5.519 +/- 3.20661e-05
  row.laserDriftVelocityWest	 =   5.52004; // +/- 2.91173e-05 cm/us West: Slope = -1.16428 +/- 0.00567422 DV = 5.52004 +/- 2.91173e-05
//row.scaleY                  	 = -2.30407e-06;// +/-8.31403e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51957 +/- 2.15563e-05
};
