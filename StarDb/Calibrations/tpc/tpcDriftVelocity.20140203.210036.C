TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34105
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51002; // +/- 3.27759e-05 cm/us East: Slope = 0.190464 +/- 0.00668225 DV = 5.51002 +/- 3.27759e-05
  row.laserDriftVelocityWest	 =   5.50807; // +/- 3.22734e-05 cm/us West: Slope = 0.560598 +/- 0.00608674 DV = 5.50807 +/- 3.22734e-05
//row.scaleY                  	 = -2.43892e-07;// +/-1.20556e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50903 +/- 2.29963e-05
};
