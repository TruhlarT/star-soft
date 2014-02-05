TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34105
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50995; // +/- 3.2958e-05 cm/us East: Slope = -0.939203 +/- 114.401 DV = 5.50995 +/- 3.2958e-05
  row.laserDriftVelocityWest	 =   5.50802; // +/- 2.66851e-05 cm/us West: Slope = -0.939203 +/- 114.401 DV = 5.50802 +/- 2.66851e-05
//row.scaleY                  	 = -2.29979e-07;// +/-1.2059e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50879 +/- 2.07394e-05
};
