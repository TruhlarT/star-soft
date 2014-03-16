TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54018
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50922; // +/- 3.71019e-05 cm/us East: Slope = 0.085204 +/- 0.00703392 DV = 5.50922 +/- 3.71019e-05
  row.laserDriftVelocityWest	 =   5.51054; // +/- 3.14785e-05 cm/us West: Slope = -0.17604 +/- 0.00592091 DV = 5.51054 +/- 3.14785e-05
//row.scaleY                  	 = 3.88041e-05;// +/-1.71594e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50999 +/- 2.40033e-05
};
