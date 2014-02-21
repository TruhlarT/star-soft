TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50126; // +/- 5.63697e-05 cm/us East: Slope = -0.0979988 +/- 0.00992827 DV = 5.50126 +/- 5.63697e-05
  row.laserDriftVelocityWest	 =   5.50358; // +/- 2.30269e-05 cm/us West: Slope = -0.364297 +/- 0.00417723 DV = 5.50358 +/- 2.30269e-05
//row.scaleY                  	 = 2.50693e-05;// +/-3.13364e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50325 +/- 2.13169e-05
};
