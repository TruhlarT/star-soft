TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47075
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49694; // +/- 4.28808e-05 cm/us East: Slope = 0.305084 +/- 0.00903463 DV = 5.49694 +/- 4.28808e-05
  row.laserDriftVelocityWest	 =   5.49694; // +/- 4.28808e-05 cm/us West: Slope = 0.305083 +/- 0.00903463 DV = 5.49694 +/- 4.28808e-05
//row.scaleY                  	 = 8.86398e-05;// +/-7.86871e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49694 +/- 4.28808e-05
};
