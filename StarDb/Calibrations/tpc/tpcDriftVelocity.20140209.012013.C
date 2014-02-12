TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39189
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50858; // +/- 0.000127119 cm/us East: Slope = 0.487617 +/- 0.0281183 DV = 5.50858 +/- 0.000127119
  row.laserDriftVelocityWest	 =   5.50743; // +/- 5.84292e-05 cm/us West: Slope = 0.822674 +/- 0.0125139 DV = 5.50743 +/- 5.84292e-05
//row.scaleY                  	 = 9.21984e-08;// +/-1.95368e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50763 +/- 5.30896e-05
};
