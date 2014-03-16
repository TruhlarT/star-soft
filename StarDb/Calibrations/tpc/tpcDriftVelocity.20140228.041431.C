TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 58055
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51143; // +/- 2.84782e-05 cm/us East: Slope = 0.418456 +/- 0.00500853 DV = 5.51143 +/- 2.84782e-05
  row.laserDriftVelocityWest	 =   5.51589; // +/- 3.50676e-05 cm/us West: Slope = -0.40717 +/- 0.00690976 DV = 5.51589 +/- 3.50676e-05
//row.scaleY                  	 = 7.62175e-06;// +/-1.7983e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51321 +/- 2.21067e-05
};
