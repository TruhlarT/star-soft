TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54026
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5091; // +/- 3.1443e-05 cm/us East: Slope = -0.789265 +/- 0.00739755 DV = 5.5091 +/- 3.1443e-05
  row.laserDriftVelocityWest	 =   5.50573; // +/- 3.03354e-05 cm/us West: Slope = -0.249371 +/- 0.00561185 DV = 5.50573 +/- 3.03354e-05
//row.scaleY                  	 = -1.89393e-06;// +/-2.77731e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50736 +/- 2.18314e-05
};
