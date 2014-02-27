TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50865; // +/- 2.14838e-05 cm/us East: Slope = 0.190386 +/- 0.00392072 DV = 5.50865 +/- 2.14838e-05
  row.laserDriftVelocityWest	 =   5.50793; // +/- 2.72115e-05 cm/us West: Slope = 0.298162 +/- 0.00484303 DV = 5.50793 +/- 2.72115e-05
//row.scaleY                  	 = -2.6653e-07;// +/-1.12533e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50837 +/- 1.68619e-05
};
