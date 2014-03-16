TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34022
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.511; // +/- 2.2077e-05 cm/us East: Slope = 0.188134 +/- 0.00404049 DV = 5.511 +/- 2.2077e-05
  row.laserDriftVelocityWest	 =   5.50888; // +/- 2.86626e-05 cm/us West: Slope = 0.558863 +/- 0.00516631 DV = 5.50888 +/- 2.86626e-05
//row.scaleY                  	 = -1.41521e-07;// +/-1.12723e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51021 +/- 1.74903e-05
};
