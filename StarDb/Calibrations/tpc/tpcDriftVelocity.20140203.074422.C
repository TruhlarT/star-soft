TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5092; // +/- 1.88056e-05 cm/us East: Slope = 0.186612 +/- 0.0033685 DV = 5.5092 +/- 1.88056e-05
  row.laserDriftVelocityWest	 =   5.50842; // +/- 2.47034e-05 cm/us West: Slope = 0.316827 +/- 0.00435747 DV = 5.50842 +/- 2.47034e-05
//row.scaleY                  	 = -2.33975e-07;// +/-1.00444e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50891 +/- 1.49632e-05
};
