TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 61007
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51228; // +/- 3.20492e-05 cm/us East: Slope = 0.278021 +/- 0.00579061 DV = 5.51228 +/- 3.20492e-05
  row.laserDriftVelocityWest	 =   5.51579; // +/- 3.22342e-05 cm/us West: Slope = -0.39549 +/- 0.00615643 DV = 5.51579 +/- 3.22342e-05
//row.scaleY                  	 = 2.79973e-07;// +/-1.97115e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51402 +/- 2.27273e-05
};
