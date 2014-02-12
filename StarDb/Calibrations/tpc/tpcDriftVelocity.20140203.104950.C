TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50926; // +/- 1.66952e-05 cm/us East: Slope = -15.305 +/- 29.974 DV = 5.50926 +/- 1.66952e-05
  row.laserDriftVelocityWest	 =   5.50797; // +/- 1.88857e-05 cm/us West: Slope = -15.305 +/- 29.974 DV = 5.50797 +/- 1.88857e-05
//row.scaleY                  	 = -1.60085e-07;// +/-8.40934e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50869 +/- 1.25084e-05
};
