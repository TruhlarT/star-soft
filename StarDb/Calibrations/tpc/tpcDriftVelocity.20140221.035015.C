TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51157
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50348; // +/- 4.06017e-05 cm/us East: Slope = 0.649033 +/- 0.00749962 DV = 5.50348 +/- 4.06017e-05
  row.laserDriftVelocityWest	 =   5.50564; // +/- 2.75772e-05 cm/us West: Slope = 0.245864 +/- 0.00513151 DV = 5.50564 +/- 2.75772e-05
//row.scaleY                  	 = -5.17186e-06;// +/-5.38996e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50496 +/- 2.28127e-05
};
