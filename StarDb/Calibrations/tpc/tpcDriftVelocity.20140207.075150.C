TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50658; // +/- 6.39933e-05 cm/us East: Slope = 0.195586 +/- 0.0122003 DV = 5.50658 +/- 6.39933e-05
  row.laserDriftVelocityWest	 =   5.50463; // +/- 4.96135e-05 cm/us West: Slope = 0.591387 +/- 0.00978465 DV = 5.50463 +/- 4.96135e-05
//row.scaleY                  	 = 3.30882e-06;// +/-2.80833e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50536 +/- 3.92097e-05
};
