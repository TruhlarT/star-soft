TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56009
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51345; // +/- 4.86913e-05 cm/us East: Slope = -1.46001 +/- 0.00849062 DV = 5.51345 +/- 4.86913e-05
  row.laserDriftVelocityWest	 =   5.50898; // +/- 3.2164e-05 cm/us West: Slope = -0.806868 +/- 0.0058975 DV = 5.50898 +/- 3.2164e-05
//row.scaleY                  	 = -9.27986e-07;// +/-2.19495e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51034 +/- 2.68374e-05
};
