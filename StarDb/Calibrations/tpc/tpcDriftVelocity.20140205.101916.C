TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51183; // +/- 3.04042e-05 cm/us East: Slope = 0.32364 +/- 0.00540898 DV = 5.51183 +/- 3.04042e-05
  row.laserDriftVelocityWest	 =   5.51382; // +/- 3.01923e-05 cm/us West: Slope = 0.303076 +/- 0.00732844 DV = 5.51382 +/- 3.01923e-05
//row.scaleY                  	 = -1.79469e-07;// +/-1.26847e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51283 +/- 2.14237e-05
};
