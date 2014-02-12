TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39197
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50949; // +/- 5.04495e-05 cm/us East: Slope = 0.278101 +/- 0.0113364 DV = 5.50949 +/- 5.04495e-05
  row.laserDriftVelocityWest	 =   5.50789; // +/- 5.86781e-05 cm/us West: Slope = 1.03805 +/- 0.00698527 DV = 5.50789 +/- 5.86781e-05
//row.scaleY                  	 = -3.59011e-07;// +/-1.32163e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50881 +/- 3.82545e-05
};
