TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53064
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50669; // +/- 3.58551e-05 cm/us East: Slope = 0.244407 +/- 0.00667995 DV = 5.50669 +/- 3.58551e-05
  row.laserDriftVelocityWest	 =   5.50889; // +/- 3.48437e-05 cm/us West: Slope = -0.165858 +/- 0.0064261 DV = 5.50889 +/- 3.48437e-05
//row.scaleY                  	 = 7.01907e-06;// +/-1.66033e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50783 +/- 2.49881e-05
};
