TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35003
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51027; // +/- 2.21558e-05 cm/us East: Slope = 0.135724 +/- 0.00393838 DV = 5.51027 +/- 2.21558e-05
  row.laserDriftVelocityWest	 =   5.51067; // +/- 2.39697e-05 cm/us West: Slope = 0.116095 +/- 0.00439102 DV = 5.51067 +/- 2.39697e-05
//row.scaleY                  	 = 6.78285e-06;// +/-1.94817e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51045 +/- 1.627e-05
};
