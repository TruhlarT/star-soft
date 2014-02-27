TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33063
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50759; // +/- 3.53941e-05 cm/us East: Slope = 0.0498497 +/- 0.00654909 DV = 5.50759 +/- 3.53941e-05
  row.laserDriftVelocityWest	 =   5.50655; // +/- 2.32693e-05 cm/us West: Slope = 0.253924 +/- 0.00416682 DV = 5.50655 +/- 2.32693e-05
//row.scaleY                  	 = 7.06129e-06;// +/-2.34581e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50686 +/- 1.94437e-05
};
