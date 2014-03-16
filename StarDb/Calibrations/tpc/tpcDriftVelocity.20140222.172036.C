TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53029
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50627; // +/- 4.09001e-05 cm/us East: Slope = 0.184458 +/- 0.00805365 DV = 5.50627 +/- 4.09001e-05
  row.laserDriftVelocityWest	 =   5.50833; // +/- 4.62008e-05 cm/us West: Slope = -0.177126 +/- 0.00917833 DV = 5.50833 +/- 4.62008e-05
//row.scaleY                  	 = 0.0137267;// +/-1.43276e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50718 +/- 3.06241e-05
};
