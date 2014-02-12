TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5103; // +/- 3.21905e-05 cm/us East: Slope = 0.150083 +/- 0.00637922 DV = 5.5103 +/- 3.21905e-05
  row.laserDriftVelocityWest	 =   5.50931; // +/- 3.63443e-05 cm/us West: Slope = 0.380369 +/- 0.00709778 DV = 5.50931 +/- 3.63443e-05
//row.scaleY                  	 = -2.62673e-07;// +/-1.22926e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50987 +/- 2.40975e-05
};
