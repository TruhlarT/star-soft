TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60051
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51123; // +/- 2.96627e-05 cm/us East: Slope = 0.476915 +/- 0.00542428 DV = 5.51123 +/- 2.96627e-05
  row.laserDriftVelocityWest	 =   5.51644; // +/- 3.16678e-05 cm/us West: Slope = -0.529946 +/- 0.00616827 DV = 5.51644 +/- 3.16678e-05
//row.scaleY                  	 = 2.08766e-06;// +/-1.85373e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51366 +/- 2.16489e-05
};
