TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48016
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49901; // +/- 3.1752e-05 cm/us East: Slope = 0.25871 +/- 0.00593821 DV = 5.49901 +/- 3.1752e-05
  row.laserDriftVelocityWest	 =   5.49923; // +/- 2.81999e-05 cm/us West: Slope = 0.183616 +/- 0.0054326 DV = 5.49923 +/- 2.81999e-05
//row.scaleY                  	 = -3.72873e-07;// +/-1.19416e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49913 +/- 2.10848e-05
};
