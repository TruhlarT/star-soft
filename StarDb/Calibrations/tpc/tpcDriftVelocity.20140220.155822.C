TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51088
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50308; // +/- 1.55874e-05 cm/us East: Slope = 0.451168 +/- 0.00289299 DV = 5.50308 +/- 1.55874e-05
  row.laserDriftVelocityWest	 =   5.50046; // +/- 1.1654e-05 cm/us West: Slope = 0.902863 +/- 0.00210212 DV = 5.50046 +/- 1.1654e-05
//row.scaleY                  	 = 5.29366e-07;// +/-1.26915e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5014 +/- 9.33367e-06
};
