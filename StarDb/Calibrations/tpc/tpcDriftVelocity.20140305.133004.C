TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 64013
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51226; // +/- 4.60551e-05 cm/us East: Slope = 0.267899 +/- 0.0104986 DV = 5.51226 +/- 4.60551e-05
  row.laserDriftVelocityWest	 =   5.5137; // +/- 4.42449e-05 cm/us West: Slope = -0.0768768 +/- 0.00891877 DV = 5.5137 +/- 4.42449e-05
//row.scaleY                  	 = -1.06397e-06;// +/-3.48713e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51301 +/- 3.19066e-05
};
