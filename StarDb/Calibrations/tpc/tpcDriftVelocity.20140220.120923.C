TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51016
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50323; // +/- 7.0849e-05 cm/us East: Slope = 0.638354 +/- 0.0139453 DV = 5.50323 +/- 7.0849e-05
  row.laserDriftVelocityWest	 =   5.50581; // +/- 3.50562e-05 cm/us West: Slope = 0.226199 +/- 0.00699735 DV = 5.50581 +/- 3.50562e-05
//row.scaleY                  	 = 1.05355e-05;// +/-5.74722e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5053 +/- 3.14203e-05
};
