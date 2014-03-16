TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 61062
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5115; // +/- 2.20083e-05 cm/us East: Slope = 0.359954 +/- 0.00386682 DV = 5.5115 +/- 2.20083e-05
  row.laserDriftVelocityWest	 =   5.5157; // +/- 2.5781e-05 cm/us West: Slope = -0.382294 +/- 0.00489735 DV = 5.5157 +/- 2.5781e-05
//row.scaleY                  	 = 1.16034e-07;// +/-1.4927e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51327 +/- 1.67387e-05
};
