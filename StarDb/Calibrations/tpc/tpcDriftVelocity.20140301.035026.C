TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 59087
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51054; // +/- 2.80423e-05 cm/us East: Slope = 0.608359 +/- 0.00520049 DV = 5.51054 +/- 2.80423e-05
  row.laserDriftVelocityWest	 =   5.5164; // +/- 3.32909e-05 cm/us West: Slope = -0.518046 +/- 0.00660577 DV = 5.5164 +/- 3.32909e-05
//row.scaleY                  	 = 5.58922e-07;// +/-1.73537e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51297 +/- 2.14474e-05
};
