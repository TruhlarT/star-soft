TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 58013
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5104; // +/- 2.83219e-05 cm/us East: Slope = 0.599797 +/- 0.00502328 DV = 5.5104 +/- 2.83219e-05
  row.laserDriftVelocityWest	 =   5.51559; // +/- 3.31543e-05 cm/us West: Slope = -0.375434 +/- 0.00667749 DV = 5.51559 +/- 3.31543e-05
//row.scaleY                  	 = 4.53652e-06;// +/-1.7562e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51259 +/- 2.15344e-05
};
