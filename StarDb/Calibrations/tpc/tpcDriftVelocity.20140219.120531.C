TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49983; // +/- 5.95388e-05 cm/us East: Slope = 0.312608 +/- 0.00937384 DV = 5.49983 +/- 5.95388e-05
  row.laserDriftVelocityWest	 =   5.50133; // +/- 3.05751e-05 cm/us West: Slope = 0.188199 +/- 0.0056172 DV = 5.50133 +/- 3.05751e-05
//row.scaleY                  	 = -9.79949e-07;// +/-2.78341e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50102 +/- 2.71984e-05
};
