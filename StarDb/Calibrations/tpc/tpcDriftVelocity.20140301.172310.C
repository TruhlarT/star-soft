TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60037
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51298; // +/- 4.04594e-05 cm/us East: Slope = 0.183131 +/- 0.00766542 DV = 5.51298 +/- 4.04594e-05
  row.laserDriftVelocityWest	 =   5.51616; // +/- 3.20015e-05 cm/us West: Slope = -0.470566 +/- 0.00616766 DV = 5.51616 +/- 3.20015e-05
//row.scaleY                  	 = 3.84808e-07;// +/-1.75296e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51494 +/- 2.50994e-05
};
