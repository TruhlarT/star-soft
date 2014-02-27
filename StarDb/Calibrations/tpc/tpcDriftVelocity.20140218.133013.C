TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49025
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5015; // +/- 3.03067e-05 cm/us East: Slope = 0.321576 +/- 0.00558878 DV = 5.5015 +/- 3.03067e-05
  row.laserDriftVelocityWest	 =   5.50175; // +/- 2.66256e-05 cm/us West: Slope = 0.247772 +/- 0.00510594 DV = 5.50175 +/- 2.66256e-05
//row.scaleY                  	 = -3.52603e-06;// +/-2.73762e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50164 +/- 2.00027e-05
};
