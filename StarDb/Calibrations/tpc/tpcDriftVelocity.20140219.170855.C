TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50192
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50353; // +/- 2.1707e-05 cm/us East: Slope = 0.13633 +/- 0.00391588 DV = 5.50353 +/- 2.1707e-05
  row.laserDriftVelocityWest	 =   5.49967; // +/- 3.23579e-05 cm/us West: Slope = 0.89398 +/- 0.005987 DV = 5.49967 +/- 3.23579e-05
//row.scaleY                  	 = 6.12201e-07;// +/-1.27397e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50233 +/- 1.80265e-05
};
