TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39177
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5066; // +/- 8.50757e-05 cm/us East: Slope = 0.841662 +/- 0.0179001 DV = 5.5066 +/- 8.50757e-05
  row.laserDriftVelocityWest	 =   5.49769; // +/- 5.21711e-05 cm/us West: Slope = 0.837418 +/- 0.0114015 DV = 5.49769 +/- 5.21711e-05
//row.scaleY                  	 = 1.57835e-07;// +/-2.00451e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50013 +/- 4.44746e-05
};
