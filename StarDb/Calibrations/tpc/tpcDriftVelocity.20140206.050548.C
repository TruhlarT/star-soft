TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37001
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50982; // +/- 3.82303e-05 cm/us East: Slope = 0.305791 +/- 0.0066028 DV = 5.50982 +/- 3.82303e-05
  row.laserDriftVelocityWest	 =   5.50814; // +/- 3.20114e-05 cm/us West: Slope = 0.572767 +/- 0.00608208 DV = 5.50814 +/- 3.20114e-05
//row.scaleY                  	 = -1.42516e-07;// +/-1.2044e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50883 +/- 2.45435e-05
};
