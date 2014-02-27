TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51141; // +/- 3.18049e-05 cm/us East: Slope = 0.199096 +/- 0.00572782 DV = 5.51141 +/- 3.18049e-05
  row.laserDriftVelocityWest	 =   5.50927; // +/- 3.53723e-05 cm/us West: Slope = 0.57108 +/- 0.00684212 DV = 5.50927 +/- 3.53723e-05
//row.scaleY                  	 = -1.63405e-07;// +/-1.29491e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51045 +/- 2.36504e-05
};
