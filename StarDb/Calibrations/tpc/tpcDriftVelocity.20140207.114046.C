TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38014
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50751; // +/- 4.87962e-05 cm/us East: Slope = 0.267152 +/- 0.00895621 DV = 5.50751 +/- 4.87962e-05
  row.laserDriftVelocityWest	 =   5.50751; // +/- 4.87962e-05 cm/us West: Slope = 0.267152 +/- 0.00895621 DV = 5.50751 +/- 4.87962e-05
//row.scaleY                  	 = -2.37132e-08;// +/-3.70243e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50751 +/- 4.87962e-05
};
