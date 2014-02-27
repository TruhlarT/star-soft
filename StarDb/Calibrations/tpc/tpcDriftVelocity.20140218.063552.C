TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49007
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50223; // +/- 3.24013e-05 cm/us East: Slope = 0.238123 +/- 0.00628855 DV = 5.50223 +/- 3.24013e-05
  row.laserDriftVelocityWest	 =   5.50218; // +/- 2.45107e-05 cm/us West: Slope = 0.219605 +/- 0.00472638 DV = 5.50218 +/- 2.45107e-05
//row.scaleY                  	 = -1.99013e-06;// +/-3.94145e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50219 +/- 1.95477e-05
};
