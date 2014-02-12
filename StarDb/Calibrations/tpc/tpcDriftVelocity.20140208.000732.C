TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38073
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51202; // +/- 8.59199e-05 cm/us East: Slope = -0.214604 +/- 0.0170201 DV = 5.51202 +/- 8.59199e-05
  row.laserDriftVelocityWest	 =   5.50925; // +/- 4.75839e-05 cm/us West: Slope = 0.420343 +/- 0.00981458 DV = 5.50925 +/- 4.75839e-05
//row.scaleY                  	 = 8.41076e-08;// +/-1.77724e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5099 +/- 4.16265e-05
};
