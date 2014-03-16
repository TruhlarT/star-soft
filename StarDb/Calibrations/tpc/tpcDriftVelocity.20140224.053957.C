TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55003
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50974; // +/- 4.2868e-05 cm/us East: Slope = 0.291563 +/- 0.00894448 DV = 5.50974 +/- 4.2868e-05
  row.laserDriftVelocityWest	 =   5.51184; // +/- 3.03945e-05 cm/us West: Slope = -0.156933 +/- 0.00591449 DV = 5.51184 +/- 3.03945e-05
//row.scaleY                  	 = -1.17054e-06;// +/-1.94699e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51114 +/- 2.47946e-05
};
