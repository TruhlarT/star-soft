TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33062
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50717; // +/- 0.000854061 cm/us East: Slope = -0.169781 +/- 1.05324 DV = 5.50717 +/- 0.000854061
  row.laserDriftVelocityWest	 =   5.50582; // +/- 0.000159433 cm/us West: Slope = 0.265247 +/- 0.229924 DV = 5.50582 +/- 0.000159433
//row.scaleY                  	 = 5.68072e-06;// +/-1.35595e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50586 +/- 0.000156726
};
