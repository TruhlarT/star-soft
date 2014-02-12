TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50868; // +/- 4.99919e-05 cm/us East: Slope = 0.494572 +/- 0.0099737 DV = 5.50868 +/- 4.99919e-05
  row.laserDriftVelocityWest	 =   5.50217; // +/- 5.52136e-05 cm/us West: Slope = 0.893075 +/- 0.0118436 DV = 5.50217 +/- 5.52136e-05
//row.scaleY                  	 = -3.05167e-07;// +/-1.51285e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50575 +/- 3.70585e-05
};
