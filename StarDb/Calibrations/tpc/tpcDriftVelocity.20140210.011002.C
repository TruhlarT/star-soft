TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40049
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50535; // +/- 1.20329e-05 cm/us East: Slope = 0.305157 +/- 0.00218491 DV = 5.50535 +/- 1.20329e-05
  row.laserDriftVelocityWest	 =   5.50285; // +/- 1.80799e-05 cm/us West: Slope = 0.783848 +/- 0.0032344 DV = 5.50285 +/- 1.80799e-05
//row.scaleY                  	 = -4.07262e-07;// +/-5.17282e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50458 +/- 1.00172e-05
};
