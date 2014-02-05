TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31129
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49916; // +/- 2.48312e-05 cm/us East: Slope = 0.339048 +/- 0.00460572 DV = 5.49916 +/- 2.48312e-05
  row.laserDriftVelocityWest	 =   5.49408; // +/- 3.36521e-05 cm/us West: Slope = 1.2707 +/- 0.00665059 DV = 5.49408 +/- 3.36521e-05
//row.scaleY                  	 = -1.81962e-07;// +/-1.49509e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49737 +/- 1.99806e-05
};
