TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 69011
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51614; // +/- 3.08717e-05 cm/us East: Slope = -0.437989 +/- 0.00563961 DV = 5.51614 +/- 3.08717e-05
  row.laserDriftVelocityWest	 =   5.51933; // +/- 2.88252e-05 cm/us West: Slope = -0.998025 +/- 0.0055024 DV = 5.51933 +/- 2.88252e-05
//row.scaleY                  	 = -1.79319e-07;// +/-1.22564e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51785 +/- 2.10689e-05
};
