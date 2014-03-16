TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48031
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49892; // +/- 3.09016e-05 cm/us East: Slope = 0.566778 +/- 0.00578208 DV = 5.49892 +/- 3.09016e-05
  row.laserDriftVelocityWest	 =   5.49909; // +/- 3.24548e-05 cm/us West: Slope = 0.444939 +/- 0.00606581 DV = 5.49909 +/- 3.24548e-05
//row.scaleY                  	 = -4.06049e-07;// +/-1.1768e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.499 +/- 2.23797e-05
};
