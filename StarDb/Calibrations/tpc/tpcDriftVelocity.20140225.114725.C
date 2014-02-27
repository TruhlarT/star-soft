TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56017
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5108; // +/- 4.71061e-05 cm/us East: Slope = -1.08254 +/- 0.00875547 DV = 5.5108 +/- 4.71061e-05
  row.laserDriftVelocityWest	 =   5.50909; // +/- 3.37282e-05 cm/us West: Slope = -0.822161 +/- 0.00625843 DV = 5.50909 +/- 3.37282e-05
//row.scaleY                  	 = -4.22093e-07;// +/-3.24665e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50967 +/- 2.74234e-05
};
