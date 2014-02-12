TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33030
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50553; // +/- 3.86438e-05 cm/us East: Slope = -1.36869 +/- 138.151 DV = 5.50553 +/- 3.86438e-05
  row.laserDriftVelocityWest	 =   5.50529; // +/- 2.54729e-05 cm/us West: Slope = -11.2237 +/- 19.8395 DV = 5.50529 +/- 2.54729e-05
//row.scaleY                  	 = 1.53885e-07;// +/-1.26704e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50536 +/- 2.1268e-05
};
