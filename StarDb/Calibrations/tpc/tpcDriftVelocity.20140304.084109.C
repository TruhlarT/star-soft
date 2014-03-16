TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 63012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50952; // +/- 2.91639e-05 cm/us East: Slope = 0.763564 +/- 0.0052278 DV = 5.50952 +/- 2.91639e-05
  row.laserDriftVelocityWest	 =   5.51488; // +/- 3.02425e-05 cm/us West: Slope = -0.2225 +/- 0.00566225 DV = 5.51488 +/- 3.02425e-05
//row.scaleY                  	 = 8.77525e-07;// +/-1.81485e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5121 +/- 2.0993e-05
};
