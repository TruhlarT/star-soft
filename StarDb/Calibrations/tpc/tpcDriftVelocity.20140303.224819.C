TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 62067
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5118; // +/- 3.87098e-05 cm/us East: Slope = 0.352842 +/- 0.00763221 DV = 5.5118 +/- 3.87098e-05
  row.laserDriftVelocityWest	 =   5.51465; // +/- 3.43447e-05 cm/us West: Slope = -0.177057 +/- 0.00659392 DV = 5.51465 +/- 3.43447e-05
//row.scaleY                  	 = 2.68652e-06;// +/-1.68359e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51339 +/- 2.56906e-05
};
