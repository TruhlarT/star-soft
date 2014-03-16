TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50177; // +/- 4.12632e-05 cm/us East: Slope = 0.239339 +/- 0.00793784 DV = 5.50177 +/- 4.12632e-05
  row.laserDriftVelocityWest	 =   5.50387; // +/- 3.47966e-05 cm/us West: Slope = -0.17785 +/- 0.00641593 DV = 5.50387 +/- 3.47966e-05
//row.scaleY                  	 = 1.93085e-06;// +/-1.85774e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.503 +/- 2.66008e-05
};
