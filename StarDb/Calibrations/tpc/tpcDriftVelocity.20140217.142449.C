TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48025
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50041; // +/- 3.51526e-05 cm/us East: Slope = 0.138456 +/- 0.00635021 DV = 5.50041 +/- 3.51526e-05
  row.laserDriftVelocityWest	 =   5.49926; // +/- 2.36987e-05 cm/us West: Slope = 0.338788 +/- 0.00434064 DV = 5.49926 +/- 2.36987e-05
//row.scaleY                  	 = 881.353;// +/-2.29177e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49962 +/- 1.96502e-05
};
