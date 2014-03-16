TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60020
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51155; // +/- 3.78034e-05 cm/us East: Slope = 0.475329 +/- 0.00689285 DV = 5.51155 +/- 3.78034e-05
  row.laserDriftVelocityWest	 =   5.51621; // +/- 3.07188e-05 cm/us West: Slope = -0.468884 +/- 0.00594143 DV = 5.51621 +/- 3.07188e-05
//row.scaleY                  	 = 2.23193e-06;// +/-1.84717e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51435 +/- 2.38402e-05
};
