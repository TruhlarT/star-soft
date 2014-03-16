TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 57023
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51092; // +/- 2.50147e-05 cm/us East: Slope = 0.544651 +/- 0.00446064 DV = 5.51092 +/- 2.50147e-05
  row.laserDriftVelocityWest	 =   5.51543; // +/- 3.23449e-05 cm/us West: Slope = -0.341492 +/- 0.00640537 DV = 5.51543 +/- 3.23449e-05
//row.scaleY                  	 = 5.61452e-06;// +/-1.59072e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51261 +/- 1.97876e-05
};
