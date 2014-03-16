TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54009
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50662; // +/- 3.5918e-05 cm/us East: Slope = 0.512369 +/- 0.0067711 DV = 5.50662 +/- 3.5918e-05
  row.laserDriftVelocityWest	 =   5.50996; // +/- 3.18138e-05 cm/us West: Slope = -0.190807 +/- 0.00607447 DV = 5.50996 +/- 3.18138e-05
//row.scaleY                  	 = 1.3745e-06;// +/-1.91456e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50849 +/- 2.38152e-05
};
