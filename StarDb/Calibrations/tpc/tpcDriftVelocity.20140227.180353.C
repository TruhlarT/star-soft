TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 58033
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51175; // +/- 3.31869e-05 cm/us East: Slope = 0.412392 +/- 0.00628574 DV = 5.51175 +/- 3.31869e-05
  row.laserDriftVelocityWest	 =   5.51448; // +/- 3.30985e-05 cm/us West: Slope = -0.159561 +/- 0.00660099 DV = 5.51448 +/- 3.30985e-05
//row.scaleY                  	 = 2.52034e-07;// +/-1.74258e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51312 +/- 2.34354e-05
};
