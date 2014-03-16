TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 64011
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50959; // +/- 3.01804e-05 cm/us East: Slope = 0.782866 +/- 0.00570139 DV = 5.50959 +/- 3.01804e-05
  row.laserDriftVelocityWest	 =   5.51388; // +/- 3.30273e-05 cm/us West: Slope = -0.0399022 +/- 0.00597533 DV = 5.51388 +/- 3.30273e-05
//row.scaleY                  	 = -1.11493e-06;// +/-1.96605e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51154 +/- 2.22794e-05
};
