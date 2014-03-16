TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37036
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50688; // +/- 3.85064e-05 cm/us East: Slope = 0.0450251 +/- 0.00589872 DV = 5.50688 +/- 3.85064e-05
  row.laserDriftVelocityWest	 =   5.50913; // +/- 3.12226e-05 cm/us West: Slope = -0.126499 +/- 0.00508621 DV = 5.50913 +/- 3.12226e-05
//row.scaleY                  	 = -1.59119e-07;// +/-1.46173e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50824 +/- 2.4252e-05
};
