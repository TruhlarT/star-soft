TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 62011
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51166; // +/- 3.2388e-05 cm/us East: Slope = 0.415039 +/- 0.00579608 DV = 5.51166 +/- 3.2388e-05
  row.laserDriftVelocityWest	 =   5.51568; // +/- 3.02347e-05 cm/us West: Slope = -0.377626 +/- 0.00600306 DV = 5.51568 +/- 3.02347e-05
//row.scaleY                  	 = 2.38513e-06;// +/-1.95789e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51381 +/- 2.21012e-05
};
