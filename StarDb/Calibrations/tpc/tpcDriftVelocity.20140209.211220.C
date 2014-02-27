TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50376; // +/- 3.65533e-05 cm/us East: Slope = 0.556423 +/- 0.00692311 DV = 5.50376 +/- 3.65533e-05
  row.laserDriftVelocityWest	 =   5.50376; // +/- 3.65533e-05 cm/us West: Slope = 0.556423 +/- 0.00692311 DV = 5.50376 +/- 3.65533e-05
//row.scaleY                  	 = -1.2124e-06;// +/-1.29677e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50376 +/- 3.65533e-05
};
