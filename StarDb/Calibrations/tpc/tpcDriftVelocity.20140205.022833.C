TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51112; // +/- 3.27306e-05 cm/us East: Slope = 0.186467 +/- 0.00592322 DV = 5.51112 +/- 3.27306e-05
  row.laserDriftVelocityWest	 =   5.51379; // +/- 3.04608e-05 cm/us West: Slope = -0.326423 +/- 0.00559745 DV = 5.51379 +/- 3.04608e-05
//row.scaleY                  	 = -1.90056e-07;// +/-1.19619e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51255 +/- 2.22983e-05
};
