TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50917; // +/- 1.88742e-05 cm/us East: Slope = -17.5963 +/- 16.2993 DV = 5.50917 +/- 1.88742e-05
  row.laserDriftVelocityWest	 =   5.50736; // +/- 2.09898e-05 cm/us West: Slope = -17.5963 +/- 16.2993 DV = 5.50736 +/- 2.09898e-05
//row.scaleY                  	 = -2.249e-07;// +/-1.00424e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50836 +/- 1.40346e-05
};
