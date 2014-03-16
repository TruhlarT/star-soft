TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53022
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50537; // +/- 3.60194e-05 cm/us East: Slope = 0.162584 +/- 0.00740835 DV = 5.50537 +/- 3.60194e-05
  row.laserDriftVelocityWest	 =   5.50717; // +/- 3.31023e-05 cm/us West: Slope = -0.163343 +/- 0.00642497 DV = 5.50717 +/- 3.31023e-05
//row.scaleY                  	 = 4.60587e-06;// +/-1.68211e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50635 +/- 2.4373e-05
};
