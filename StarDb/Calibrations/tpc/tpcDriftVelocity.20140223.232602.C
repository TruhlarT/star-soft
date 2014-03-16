TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54043
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50806; // +/- 3.46035e-05 cm/us East: Slope = 0.452266 +/- 0.00657275 DV = 5.50806 +/- 3.46035e-05
  row.laserDriftVelocityWest	 =   5.51142; // +/- 3.08477e-05 cm/us West: Slope = -0.192869 +/- 0.00580955 DV = 5.51142 +/- 3.08477e-05
//row.scaleY                  	 = 3.29445e-06;// +/-1.95097e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50993 +/- 2.30264e-05
};
