TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52020
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50292; // +/- 2.54184e-05 cm/us East: Slope = 0.305639 +/- 0.00476594 DV = 5.50292 +/- 2.54184e-05
  row.laserDriftVelocityWest	 =   5.50546; // +/- 3.55968e-05 cm/us West: Slope = -0.195509 +/- 0.00687036 DV = 5.50546 +/- 3.55968e-05
//row.scaleY                  	 = 5.43668e-06;// +/-1.75428e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50378 +/- 2.0686e-05
};
