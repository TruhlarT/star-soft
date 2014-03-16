TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32057
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50318; // +/- 2.15682e-05 cm/us East: Slope = -0.0412929 +/- 0.0039936 DV = 5.50318 +/- 2.15682e-05
  row.laserDriftVelocityWest	 =   5.48355; // +/- 2.82889e-05 cm/us West: Slope = 0.366791 +/- 0.00484815 DV = 5.48355 +/- 2.82889e-05
//row.scaleY                  	 = -2.00463e-07;// +/-1.08994e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49597 +/- 1.71517e-05
};
