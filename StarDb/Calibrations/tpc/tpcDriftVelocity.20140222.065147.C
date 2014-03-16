TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53004
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50157; // +/- 3.07766e-05 cm/us East: Slope = 0.574784 +/- 0.00567473 DV = 5.50157 +/- 3.07766e-05
  row.laserDriftVelocityWest	 =   5.50524; // +/- 3.26699e-05 cm/us West: Slope = -0.154916 +/- 0.00644061 DV = 5.50524 +/- 3.26699e-05
//row.scaleY                  	 = 4.87794e-06;// +/-1.86495e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5033 +/- 2.24018e-05
};
