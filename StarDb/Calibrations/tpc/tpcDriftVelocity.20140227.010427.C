TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 57053
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51009; // +/- 2.8795e-05 cm/us East: Slope = 0.702647 +/- 0.00538704 DV = 5.51009 +/- 2.8795e-05
  row.laserDriftVelocityWest	 =   5.51567; // +/- 3.53177e-05 cm/us West: Slope = -0.370984 +/- 0.00729278 DV = 5.51567 +/- 3.53177e-05
//row.scaleY                  	 = 9.50473e-07;// +/-1.64587e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51232 +/- 2.23175e-05
};
