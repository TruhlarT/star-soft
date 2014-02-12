TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39166
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5065; // +/- 9.0481e-05 cm/us East: Slope = 0.865441 +/- 0.0217247 DV = 5.5065 +/- 9.0481e-05
  row.laserDriftVelocityWest	 =   5.50334; // +/- 5.43905e-05 cm/us West: Slope = 0.67364 +/- 0.0118908 DV = 5.50334 +/- 5.43905e-05
//row.scaleY                  	 = 2.5387e-07;// +/-2.18984e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50418 +/- 4.66163e-05
};
