TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37036
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50668; // +/- 3.9092e-05 cm/us East: Slope = 0.110388 +/- 0.00596354 DV = 5.50668 +/- 3.9092e-05
  row.laserDriftVelocityWest	 =   5.50494; // +/- 3.12176e-05 cm/us West: Slope = 0.692075 +/- 0.00502964 DV = 5.50494 +/- 3.12176e-05
//row.scaleY                  	 = -1.58865e-07;// +/-1.46032e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50562 +/- 2.43939e-05
};
