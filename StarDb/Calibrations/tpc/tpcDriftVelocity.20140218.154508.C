TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49033
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50268; // +/- 4.12433e-05 cm/us East: Slope = -0.18976 +/- 0.00838421 DV = 5.50268 +/- 4.12433e-05
  row.laserDriftVelocityWest	 =   5.50228; // +/- 2.41861e-05 cm/us West: Slope = -0.134743 +/- 0.00450499 DV = 5.50228 +/- 2.41861e-05
//row.scaleY                  	 = 6.25492e-06;// +/-5.23035e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50239 +/- 2.08633e-05
};
