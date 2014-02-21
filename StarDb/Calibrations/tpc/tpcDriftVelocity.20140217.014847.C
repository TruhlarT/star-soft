TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47098
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49811; // +/- 4.86323e-05 cm/us East: Slope = 1.54244 +/- 0.00939528 DV = 5.49811 +/- 4.86323e-05
  row.laserDriftVelocityWest	 =   5.49768; // +/- 0.000102365 cm/us West: Slope = 1.61509 +/- 0.0443455 DV = 5.49768 +/- 0.000102365
//row.scaleY                  	 = 4.07703e-06;// +/-3.2851e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49803 +/- 4.3927e-05
};
