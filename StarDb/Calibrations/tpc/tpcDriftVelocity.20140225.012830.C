TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55134
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5103; // +/- 3.38778e-05 cm/us East: Slope = -1.01954 +/- 0.00627687 DV = 5.5103 +/- 3.38778e-05
  row.laserDriftVelocityWest	 =   5.50757; // +/- 3.91718e-05 cm/us West: Slope = -0.565489 +/- 0.00773635 DV = 5.50757 +/- 3.91718e-05
//row.scaleY                  	 = -1.74379e-06;// +/-2.01101e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50913 +/- 2.56241e-05
};
