TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37058
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50902; // +/- 5.00545e-05 cm/us East: Slope = 0.0872561 +/- 0.00999281 DV = 5.50902 +/- 5.00545e-05
  row.laserDriftVelocityWest	 =   5.50559; // +/- 3.14561e-05 cm/us West: Slope = -0.440382 +/- 0.0054642 DV = 5.50559 +/- 3.14561e-05
//row.scaleY                  	 = -2.53142e-06;// +/-4.85208e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50656 +/- 2.66335e-05
};
