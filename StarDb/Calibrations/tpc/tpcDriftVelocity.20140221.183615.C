TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5013; // +/- 3.76198e-05 cm/us East: Slope = 0.590635 +/- 0.00804128 DV = 5.5013 +/- 3.76198e-05
  row.laserDriftVelocityWest	 =   5.49639; // +/- 3.51901e-05 cm/us West: Slope = 1.4795 +/- 0.00661287 DV = 5.49639 +/- 3.51901e-05
//row.scaleY                  	 = -1.96601e-06;// +/-3.30626e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49868 +/- 2.56992e-05
};
