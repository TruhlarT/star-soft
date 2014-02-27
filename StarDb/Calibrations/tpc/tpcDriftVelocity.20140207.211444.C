TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38065
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50994; // +/- 2.83141e-05 cm/us East: Slope = 0.210865 +/- 0.0053007 DV = 5.50994 +/- 2.83141e-05
  row.laserDriftVelocityWest	 =   5.50767; // +/- 4.70655e-05 cm/us West: Slope = 0.596649 +/- 0.00868607 DV = 5.50767 +/- 4.70655e-05
//row.scaleY                  	 = -4.98999e-07;// +/-1.92471e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50934 +/- 2.42621e-05
};
