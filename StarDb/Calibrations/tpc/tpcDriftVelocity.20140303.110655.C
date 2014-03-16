TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 62022
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51076; // +/- 2.53799e-05 cm/us East: Slope = 0.572248 +/- 0.00465454 DV = 5.51076 +/- 2.53799e-05
  row.laserDriftVelocityWest	 =   5.51581; // +/- 3.19444e-05 cm/us West: Slope = -0.421602 +/- 0.00616979 DV = 5.51581 +/- 3.19444e-05
//row.scaleY                  	 = 2.08943e-06;// +/-1.69544e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51272 +/- 1.98716e-05
};
