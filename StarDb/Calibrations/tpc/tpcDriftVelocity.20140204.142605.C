TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5103; // +/- 3.19076e-05 cm/us East: Slope = 0.151336 +/- 0.00631647 DV = 5.5103 +/- 3.19076e-05
  row.laserDriftVelocityWest	 =   5.5077; // +/- 3.65308e-05 cm/us West: Slope = 0.674615 +/- 0.00705403 DV = 5.5077 +/- 3.65308e-05
//row.scaleY                  	 = -2.62543e-07;// +/-1.23024e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50917 +/- 2.40314e-05
};
