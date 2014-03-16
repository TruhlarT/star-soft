TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35073
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51144; // +/- 2.91388e-05 cm/us East: Slope = 0.238519 +/- 0.00524355 DV = 5.51144 +/- 2.91388e-05
  row.laserDriftVelocityWest	 =   5.50762; // +/- 3.99228e-05 cm/us West: Slope = 1.09213 +/- 0.00578329 DV = 5.50762 +/- 3.99228e-05
//row.scaleY                  	 = -1.90483e-07;// +/-1.29304e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51011 +/- 2.35364e-05
};
