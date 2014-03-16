TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52017
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50188; // +/- 3.73848e-05 cm/us East: Slope = 0.250307 +/- 0.00731543 DV = 5.50188 +/- 3.73848e-05
  row.laserDriftVelocityWest	 =   5.50394; // +/- 3.57959e-05 cm/us West: Slope = -0.158861 +/- 0.00708986 DV = 5.50394 +/- 3.57959e-05
//row.scaleY                  	 = 3.27066e-06;// +/-2.0141e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50295 +/- 2.5855e-05
};
