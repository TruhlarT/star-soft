TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5046; // +/- 4.20438e-05 cm/us East: Slope = -0.546532 +/- 0.00824778 DV = 5.5046 +/- 4.20438e-05
  row.laserDriftVelocityWest	 =   5.50358; // +/- 2.43524e-05 cm/us West: Slope = -0.360444 +/- 0.00455392 DV = 5.50358 +/- 2.43524e-05
//row.scaleY                  	 = 6.2201e-06;// +/-4.71697e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50383 +/- 2.10728e-05
};
