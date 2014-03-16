TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 57049
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51317; // +/- 3.46185e-05 cm/us East: Slope = 0.113853 +/- 0.00677646 DV = 5.51317 +/- 3.46185e-05
  row.laserDriftVelocityWest	 =   5.51478; // +/- 3.51876e-05 cm/us West: Slope = -0.191609 +/- 0.0066418 DV = 5.51478 +/- 3.51876e-05
//row.scaleY                  	 = 9.94532e-07;// +/-1.70149e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51396 +/- 2.46777e-05
};
