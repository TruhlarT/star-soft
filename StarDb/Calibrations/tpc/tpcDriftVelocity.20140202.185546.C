TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33062
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50626; // +/- 0.000493031 cm/us East: Slope = 5.50626 +/- 0.000493031 DV = 5.50626 +/- 0.000493031
  row.laserDriftVelocityWest	 =   5.50464; // +/- 0.000306034 cm/us West: Slope = 5.50626 +/- 0.000493031 DV = 5.50464 +/- 0.000306034
//row.scaleY                  	 = 2.30165e-07;// +/-6.57626e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50509 +/- 0.000260015
};
