TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34133
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51054; // +/- 2.42594e-05 cm/us East: Slope = 0.199487 +/- 0.00433928 DV = 5.51054 +/- 2.42594e-05
  row.laserDriftVelocityWest	 =   5.51139; // +/- 2.50287e-05 cm/us West: Slope = 0.129249 +/- 0.00470751 DV = 5.51139 +/- 2.50287e-05
//row.scaleY                  	 = 2.64514e-06;// +/-2.12744e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51095 +/- 1.74196e-05
};
