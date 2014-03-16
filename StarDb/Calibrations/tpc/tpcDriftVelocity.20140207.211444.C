TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38065
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50995; // +/- 2.74679e-05 cm/us East: Slope = 0.21631 +/- 0.00509526 DV = 5.50995 +/- 2.74679e-05
  row.laserDriftVelocityWest	 =   5.51013; // +/- 4.86188e-05 cm/us West: Slope = 0.234836 +/- 0.00968328 DV = 5.51013 +/- 4.86188e-05
//row.scaleY                  	 = -1.78194e-09;// +/-1.60403e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50999 +/- 2.39151e-05
};
