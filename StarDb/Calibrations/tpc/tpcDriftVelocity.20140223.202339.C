TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50896; // +/- 4.45162e-05 cm/us East: Slope = 0.239911 +/- 0.00838139 DV = 5.50896 +/- 4.45162e-05
  row.laserDriftVelocityWest	 =   5.51089; // +/- 3.0204e-05 cm/us West: Slope = -0.196054 +/- 0.00606495 DV = 5.51089 +/- 3.0204e-05
//row.scaleY                  	 = 4.32876e-06;// +/-2.26746e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51028 +/- 2.4994e-05
};
