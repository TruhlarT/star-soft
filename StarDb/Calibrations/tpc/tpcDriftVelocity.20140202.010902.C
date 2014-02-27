TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32057
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50315; // +/- 2.15258e-05 cm/us East: Slope = 0.183504 +/- 0.00396329 DV = 5.50315 +/- 2.15258e-05
  row.laserDriftVelocityWest	 =   5.48459; // +/- 2.82334e-05 cm/us West: Slope = 0.236868 +/- 0.00571129 DV = 5.48459 +/- 2.82334e-05
//row.scaleY                  	 = -2.04125e-07;// +/-1.08342e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49633 +/- 1.7118e-05
};
