TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33062
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50606; // +/- 0.000478971 cm/us East: Slope = 5.50606 +/- 0.000478971 DV = 5.50606 +/- 0.000478971
  row.laserDriftVelocityWest	 =   5.50462; // +/- 0.000301963 cm/us West: Slope = 5.50606 +/- 0.000478971 DV = 5.50462 +/- 0.000301963
//row.scaleY                  	 = 2.29573e-07;// +/-6.52242e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50503 +/- 0.000255438
};
