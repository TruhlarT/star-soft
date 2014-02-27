TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53004
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.8935; // +/- 4.83915e-05 cm/us East: Slope = 5.8935 +/- 4.83915e-05 DV = 5.8935 +/- 4.83915e-05
  row.laserDriftVelocityWest	 =   5.89221; // +/- 3.41803e-05 cm/us West: Slope = 5.8935 +/- 4.83915e-05 DV = 5.89221 +/- 3.41803e-05
//row.scaleY                  	 = -8.82842e-07;// +/-8.31766e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.89264 +/- 2.79183e-05
};
