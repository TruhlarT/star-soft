TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37036
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50705; // +/- 3.73249e-05 cm/us East: Slope = 0.70255 +/- 0.00606115 DV = 5.50705 +/- 3.73249e-05
  row.laserDriftVelocityWest	 =   5.50952; // +/- 3.06765e-05 cm/us West: Slope = 0.347786 +/- 0.00596648 DV = 5.50952 +/- 3.06765e-05
//row.scaleY                  	 = -1.60327e-07;// +/-1.46362e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50853 +/- 2.36993e-05
};
