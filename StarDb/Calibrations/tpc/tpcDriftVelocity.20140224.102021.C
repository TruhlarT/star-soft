TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55009
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50909; // +/- 3.91084e-05 cm/us East: Slope = 0.455996 +/- 0.00758343 DV = 5.50909 +/- 3.91084e-05
  row.laserDriftVelocityWest	 =   5.51215; // +/- 3.47743e-05 cm/us West: Slope = -0.115934 +/- 0.00645852 DV = 5.51215 +/- 3.47743e-05
//row.scaleY                  	 = 7.53352e-06;// +/-2.07183e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51079 +/- 2.59869e-05
};
