TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 63051
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51067; // +/- 3.40859e-05 cm/us East: Slope = 0.584955 +/- 0.00653876 DV = 5.51067 +/- 3.40859e-05
  row.laserDriftVelocityWest	 =   5.51494; // +/- 3.21073e-05 cm/us West: Slope = -0.226407 +/- 0.00598978 DV = 5.51494 +/- 3.21073e-05
//row.scaleY                  	 = 1.24763e-06;// +/-1.76636e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51293 +/- 2.33715e-05
};
