TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 46034
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.48344; // +/- 3.90143e-05 cm/us East: Slope = 0.327562 +/- 0.00773909 DV = 5.48344 +/- 3.90143e-05
  row.laserDriftVelocityWest	 =   5.4827; // +/- 2.36982e-05 cm/us West: Slope = 0.441042 +/- 0.00439609 DV = 5.4827 +/- 2.36982e-05
//row.scaleY                  	 = 7.54145e-06;// +/-3.06857e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.4829 +/- 2.02544e-05
};
