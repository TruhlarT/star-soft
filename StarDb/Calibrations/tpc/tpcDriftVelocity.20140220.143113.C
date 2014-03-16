TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51026
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5037; // +/- 2.58276e-05 cm/us East: Slope = 0.343609 +/- 0.00467812 DV = 5.5037 +/- 2.58276e-05
  row.laserDriftVelocityWest	 =   5.50621; // +/- 2.3983e-05 cm/us West: Slope = -0.141717 +/- 0.00431325 DV = 5.50621 +/- 2.3983e-05
//row.scaleY                  	 = -1.21975e-07;// +/-1.12031e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50505 +/- 1.75745e-05
};
