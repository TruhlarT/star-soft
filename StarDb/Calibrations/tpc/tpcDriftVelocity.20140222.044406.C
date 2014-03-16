TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52074
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50242; // +/- 3.97343e-05 cm/us East: Slope = 0.339411 +/- 0.00773079 DV = 5.50242 +/- 3.97343e-05
  row.laserDriftVelocityWest	 =   5.50498; // +/- 3.62966e-05 cm/us West: Slope = -0.181376 +/- 0.00697861 DV = 5.50498 +/- 3.62966e-05
//row.scaleY                  	 = 5.36314e-06;// +/-1.81784e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50382 +/- 2.67987e-05
};
