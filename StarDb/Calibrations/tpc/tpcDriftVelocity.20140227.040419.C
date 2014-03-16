TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 57061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51367; // +/- 2.82017e-05 cm/us East: Slope = 0.118093 +/- 0.0050257 DV = 5.51367 +/- 2.82017e-05
  row.laserDriftVelocityWest	 =   5.51565; // +/- 3.45422e-05 cm/us West: Slope = -0.370209 +/- 0.00705152 DV = 5.51565 +/- 3.45422e-05
//row.scaleY                  	 = 7.52481e-06;// +/-1.70736e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51446 +/- 2.18455e-05
};
