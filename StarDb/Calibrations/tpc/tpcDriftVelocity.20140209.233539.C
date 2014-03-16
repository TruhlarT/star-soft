TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40047
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50676; // +/- 1.18354e-05 cm/us East: Slope = 0.196598 +/- 0.00211864 DV = 5.50676 +/- 1.18354e-05
  row.laserDriftVelocityWest	 =   5.50512; // +/- 1.33588e-05 cm/us West: Slope = 0.483849 +/- 0.00239098 DV = 5.50512 +/- 1.33588e-05
//row.scaleY                  	 = -2.78452e-07;// +/-4.39783e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50604 +/- 8.85875e-06
};
