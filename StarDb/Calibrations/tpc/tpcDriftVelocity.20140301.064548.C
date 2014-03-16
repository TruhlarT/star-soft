TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60007
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5106; // +/- 3.30797e-05 cm/us East: Slope = 0.606608 +/- 0.00595416 DV = 5.5106 +/- 3.30797e-05
  row.laserDriftVelocityWest	 =   5.51576; // +/- 3.11869e-05 cm/us West: Slope = -0.378603 +/- 0.00598371 DV = 5.51576 +/- 3.11869e-05
//row.scaleY                  	 = 4.87303e-07;// +/-1.94757e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51333 +/- 2.26921e-05
};
