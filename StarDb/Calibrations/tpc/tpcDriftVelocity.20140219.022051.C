TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49092
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50099; // +/- 3.06194e-05 cm/us East: Slope = 0.259944 +/- 0.00575104 DV = 5.50099 +/- 3.06194e-05
  row.laserDriftVelocityWest	 =   5.50099; // +/- 3.06194e-05 cm/us West: Slope = 0.259944 +/- 0.00575104 DV = 5.50099 +/- 3.06194e-05
//row.scaleY                  	 = -2.02427e-06;// +/-5.40439e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50099 +/- 3.06194e-05
};
