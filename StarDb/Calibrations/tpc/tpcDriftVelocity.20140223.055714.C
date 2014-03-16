TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54001
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50631; // +/- 4.15013e-05 cm/us East: Slope = 0.415534 +/- 0.00764226 DV = 5.50631 +/- 4.15013e-05
  row.laserDriftVelocityWest	 =   5.50934; // +/- 3.17175e-05 cm/us West: Slope = -0.188185 +/- 0.00628103 DV = 5.50934 +/- 3.17175e-05
//row.scaleY                  	 = 6.37957e-07;// +/-2.0824e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50822 +/- 2.52006e-05
};
