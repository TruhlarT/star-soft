TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 70022
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51629; // +/- 1.36418e-05 cm/us East: Slope = -0.760461 +/- 0.00318855 DV = 5.51629 +/- 1.36418e-05
  row.laserDriftVelocityWest	 =   5.51986; // +/- 1.25407e-05 cm/us West: Slope = -1.13989 +/- 0.00225571 DV = 5.51986 +/- 1.25407e-05
//row.scaleY                  	 = -3.40341e-07;// +/-5.1719e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51822 +/- 9.23237e-06
};
