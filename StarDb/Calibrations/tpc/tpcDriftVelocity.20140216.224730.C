TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47075
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49752; // +/- 4.0705e-05 cm/us East: Slope = 1.59809 +/- 0.00745208 DV = 5.49752 +/- 4.0705e-05
  row.laserDriftVelocityWest	 =   5.49752; // +/- 4.0705e-05 cm/us West: Slope = 1.59809 +/- 0.00745208 DV = 5.49752 +/- 4.0705e-05
//row.scaleY                  	 = 6.67746e-06;// +/-3.61969e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49752 +/- 4.0705e-05
};
