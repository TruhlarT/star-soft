TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34133
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5112; // +/- 3.34623e-05 cm/us East: Slope = 0.0582127 +/- 0.00626887 DV = 5.5112 +/- 3.34623e-05
  row.laserDriftVelocityWest	 =   5.50655; // +/- 3.12714e-05 cm/us West: Slope = 0.934755 +/- 0.00606229 DV = 5.50655 +/- 3.12714e-05
//row.scaleY                  	 = -2.03247e-07;// +/-1.22165e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50872 +/- 2.28475e-05
};
