TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31080
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49783; // +/- 6.63682e-05 cm/us East: Slope = -0.131855 +/- 0.0205668 DV = 5.49783 +/- 6.63682e-05
  row.laserDriftVelocityWest	 =   5.49732; // +/- 5.03494e-05 cm/us West: Slope = -0.169834 +/- 0.0137336 DV = 5.49732 +/- 5.03494e-05
//row.scaleY                  	 = 4.75263e-06;// +/-5.48315e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.4975 +/- 4.01126e-05
};
