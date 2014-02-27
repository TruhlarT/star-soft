TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48016
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.4993; // +/- 3.28768e-05 cm/us East: Slope = 0.373881 +/- 0.00601327 DV = 5.4993 +/- 3.28768e-05
  row.laserDriftVelocityWest	 =   5.49826; // +/- 2.78397e-05 cm/us West: Slope = 0.516684 +/- 0.00534713 DV = 5.49826 +/- 2.78397e-05
//row.scaleY                  	 = -20.7508;// +/-1.60364e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49869 +/- 2.12458e-05
};
