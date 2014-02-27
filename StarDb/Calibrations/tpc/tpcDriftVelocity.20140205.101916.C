TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51245; // +/- 2.47803e-05 cm/us East: Slope = 0.0766794 +/- 0.00450022 DV = 5.51245 +/- 2.47803e-05
  row.laserDriftVelocityWest	 =   5.50862; // +/- 2.72911e-05 cm/us West: Slope = 0.769415 +/- 0.00504229 DV = 5.50862 +/- 2.72911e-05
//row.scaleY                  	 = 6.10061e-06;// +/-1.96997e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51072 +/- 1.83459e-05
};
