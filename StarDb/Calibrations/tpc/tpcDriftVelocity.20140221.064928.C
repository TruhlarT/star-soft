TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52007
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50057; // +/- 5.50271e-05 cm/us East: Slope = 0.69478 +/- 0.0116756 DV = 5.50057 +/- 5.50271e-05
  row.laserDriftVelocityWest	 =   5.49906; // +/- 3.27703e-05 cm/us West: Slope = 0.987469 +/- 0.00622318 DV = 5.49906 +/- 3.27703e-05
//row.scaleY                  	 = 0.000222814;// +/-7.19263e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49946 +/- 2.81557e-05
};
