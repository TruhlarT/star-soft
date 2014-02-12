TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34105
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50996; // +/- 3.26863e-05 cm/us East: Slope = -0.939202 +/- 114.401 DV = 5.50996 +/- 3.26863e-05
  row.laserDriftVelocityWest	 =   5.50799; // +/- 2.65636e-05 cm/us West: Slope = -0.939202 +/- 114.401 DV = 5.50799 +/- 2.65636e-05
//row.scaleY                  	 = -2.30563e-07;// +/-1.19431e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50877 +/- 2.06145e-05
};
