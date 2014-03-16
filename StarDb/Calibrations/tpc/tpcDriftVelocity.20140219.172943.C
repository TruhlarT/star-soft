TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50194
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50298; // +/- 1.36226e-05 cm/us East: Slope = 0.216562 +/- 0.00248437 DV = 5.50298 +/- 1.36226e-05
  row.laserDriftVelocityWest	 =   5.50065; // +/- 1.98204e-05 cm/us West: Slope = 0.605911 +/- 0.00345629 DV = 5.50065 +/- 1.98204e-05
//row.scaleY                  	 = -1.61041e-07;// +/-8.51867e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50223 +/- 1.12266e-05
};
