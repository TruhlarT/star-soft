TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35003
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51021; // +/- 3.7411e-05 cm/us East: Slope = -6.92913 +/- 56.4884 DV = 5.51021 +/- 3.7411e-05
  row.laserDriftVelocityWest	 =   5.50799; // +/- 2.78577e-05 cm/us West: Slope = -1.77865 +/- 103.022 DV = 5.50799 +/- 2.78577e-05
//row.scaleY                  	 = -1.74249e-07;// +/-1.21477e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50878 +/- 2.23435e-05
};
