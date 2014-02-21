TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50192
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5035; // +/- 2.94507e-05 cm/us East: Slope = -0.358739 +/- 0.00535107 DV = 5.5035 +/- 2.94507e-05
  row.laserDriftVelocityWest	 =   5.50129; // +/- 2.47592e-05 cm/us West: Slope = 0.0451137 +/- 0.00462684 DV = 5.50129 +/- 2.47592e-05
//row.scaleY                  	 = 1.10179e-05;// +/-2.30412e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50221 +/- 1.89517e-05
};
