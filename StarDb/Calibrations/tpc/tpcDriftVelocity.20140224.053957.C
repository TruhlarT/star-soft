TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55003
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.8996; // +/- 0.000377519 cm/us East: Slope = 5.8996 +/- 0.000377519 DV = 5.8996 +/- 0.000377519
  row.laserDriftVelocityWest	 =   5.89827; // +/- 0.00017917 cm/us West: Slope = 5.8996 +/- 0.000377519 DV = 5.89827 +/- 0.00017917
//row.scaleY                  	 = -7.61133e-07;// +/-7.1064e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.89852 +/- 0.000161866
};
