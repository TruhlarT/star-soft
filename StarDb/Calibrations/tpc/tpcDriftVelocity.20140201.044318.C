TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31129
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49916; // +/- 2.45695e-05 cm/us East: Slope = 0.340302 +/- 0.00452489 DV = 5.49916 +/- 2.45695e-05
  row.laserDriftVelocityWest	 =   5.49409; // +/- 3.32858e-05 cm/us West: Slope = 1.27086 +/- 0.00656984 DV = 5.49409 +/- 3.32858e-05
//row.scaleY                  	 = -1.80975e-07;// +/-1.47889e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49737 +/- 1.97676e-05
};
