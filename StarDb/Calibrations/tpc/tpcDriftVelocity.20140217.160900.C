TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48031
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50099; // +/- 3.2372e-05 cm/us East: Slope = 0.129852 +/- 0.00599571 DV = 5.50099 +/- 3.2372e-05
  row.laserDriftVelocityWest	 =   5.49975; // +/- 2.35714e-05 cm/us West: Slope = 0.326294 +/- 0.00444621 DV = 5.49975 +/- 2.35714e-05
//row.scaleY                  	 = 5.35749e-06;// +/-2.18315e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50018 +/- 1.90551e-05
};
