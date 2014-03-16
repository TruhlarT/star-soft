TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51025; // +/- 3.32769e-05 cm/us East: Slope = 0.11129 +/- 0.00676201 DV = 5.51025 +/- 3.32769e-05
  row.laserDriftVelocityWest	 =   5.50774; // +/- 3.33084e-05 cm/us West: Slope = 0.585959 +/- 0.00643959 DV = 5.50774 +/- 3.33084e-05
//row.scaleY                  	 = -2.40844e-07;// +/-1.22696e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.509 +/- 2.35414e-05
};
