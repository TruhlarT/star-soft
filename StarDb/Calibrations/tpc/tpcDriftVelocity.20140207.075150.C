TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50636; // +/- 6.02499e-05 cm/us East: Slope = 0.92295 +/- 0.0115614 DV = 5.50636 +/- 6.02499e-05
  row.laserDriftVelocityWest	 =   5.51; // +/- 5.80699e-05 cm/us West: Slope = 0.344199 +/- 0.0108432 DV = 5.51 +/- 5.80699e-05
//row.scaleY                  	 = 2.63122e-07;// +/-2.23501e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50825 +/- 4.18111e-05
};
