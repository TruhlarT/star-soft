TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56028
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51251; // +/- 4.46207e-05 cm/us East: Slope = 0.247716 +/- 0.0096396 DV = 5.51251 +/- 4.46207e-05
  row.laserDriftVelocityWest	 =   5.51472; // +/- 3.24706e-05 cm/us West: Slope = -0.159442 +/- 0.00623988 DV = 5.51472 +/- 3.24706e-05
//row.scaleY                  	 = 7.01124e-06;// +/-1.97903e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51396 +/- 2.62548e-05
};
