TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51001
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50599; // +/- 3.72236e-05 cm/us East: Slope = -0.811968 +/- 0.00706431 DV = 5.50599 +/- 3.72236e-05
  row.laserDriftVelocityWest	 =   5.50226; // +/- 3.24423e-05 cm/us West: Slope = -0.115001 +/- 0.006076 DV = 5.50226 +/- 3.24423e-05
//row.scaleY                  	 = 1.99364e-05;// +/-6.41829e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50387 +/- 2.44571e-05
};
