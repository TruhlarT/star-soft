TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 63056
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.512; // +/- 2.84893e-05 cm/us East: Slope = 0.329589 +/- 0.00529751 DV = 5.512 +/- 2.84893e-05
  row.laserDriftVelocityWest	 =   5.5149; // +/- 3.26893e-05 cm/us West: Slope = -0.259771 +/- 0.00620304 DV = 5.5149 +/- 3.26893e-05
//row.scaleY                  	 = 2.047e-06;// +/-1.96597e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51325 +/- 2.14774e-05
};
