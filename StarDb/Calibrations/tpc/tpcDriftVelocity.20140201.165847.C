TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32031
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50087; // +/- 6.85026e-05 cm/us East: Slope = 0.236996 +/- 0.0142412 DV = 5.50087 +/- 6.85026e-05
  row.laserDriftVelocityWest	 =   5.49822; // +/- 3.36791e-05 cm/us West: Slope = 0.715417 +/- 0.00629893 DV = 5.49822 +/- 3.36791e-05
//row.scaleY                  	 = -1.21615e-07;// +/-1.76856e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49874 +/- 3.02238e-05
};
