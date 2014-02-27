TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51001
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50483; // +/- 3.63565e-05 cm/us East: Slope = 0.363209 +/- 0.00704498 DV = 5.50483 +/- 3.63565e-05
  row.laserDriftVelocityWest	 =   5.50577; // +/- 3.14815e-05 cm/us West: Slope = 0.21863 +/- 0.0059147 DV = 5.50577 +/- 3.14815e-05
//row.scaleY                  	 = -1.69421e-06;// +/-4.13819e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50537 +/- 2.37991e-05
};
