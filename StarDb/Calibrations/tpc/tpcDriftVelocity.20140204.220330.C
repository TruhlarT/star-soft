TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35073
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51151; // +/- 2.95666e-05 cm/us East: Slope = -0.0367345 +/- 0.00537509 DV = 5.51151 +/- 2.95666e-05
  row.laserDriftVelocityWest	 =   5.50921; // +/- 3.91505e-05 cm/us West: Slope = 0.560056 +/- 0.0058067 DV = 5.50921 +/- 3.91505e-05
//row.scaleY                  	 = -1.87612e-07;// +/-1.29177e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51067 +/- 2.35942e-05
};
