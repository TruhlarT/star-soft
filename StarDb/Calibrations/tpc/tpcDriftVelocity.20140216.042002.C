TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 46109
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49043; // +/- 4.49514e-05 cm/us East: Slope = 2.88626 +/- 0.00821246 DV = 5.49043 +/- 4.49514e-05
  row.laserDriftVelocityWest	 =   5.49015; // +/- 2.33813e-05 cm/us West: Slope = 2.93714 +/- 0.00449699 DV = 5.49015 +/- 2.33813e-05
//row.scaleY                  	 = 1.92949e-06;// +/-4.02488e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49021 +/- 2.0743e-05
};
