TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 61052
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51355; // +/- 2.82384e-05 cm/us East: Slope = -0.00630156 +/- 0.00543645 DV = 5.51355 +/- 2.82384e-05
  row.laserDriftVelocityWest	 =   5.51589; // +/- 3.53537e-05 cm/us West: Slope = -0.407768 +/- 0.00702841 DV = 5.51589 +/- 3.53537e-05
//row.scaleY                  	 = 6.66309e-06;// +/-1.69597e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51446 +/- 2.2064e-05
};
