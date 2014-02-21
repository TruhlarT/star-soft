TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49718; // +/- 3.70379e-05 cm/us East: Slope = 1.67356 +/- 0.00724914 DV = 5.49718 +/- 3.70379e-05
  row.laserDriftVelocityWest	 =   5.49718; // +/- 3.70379e-05 cm/us West: Slope = 1.67356 +/- 0.00724914 DV = 5.49718 +/- 3.70379e-05
//row.scaleY                  	 = 5.17404e-06;// +/-3.9076e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49718 +/- 3.70379e-05
};
