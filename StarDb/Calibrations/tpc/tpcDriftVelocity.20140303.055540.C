TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 62004
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51149; // +/- 3.20322e-05 cm/us East: Slope = 0.451795 +/- 0.00589975 DV = 5.51149 +/- 3.20322e-05
  row.laserDriftVelocityWest	 =   5.51582; // +/- 3.13904e-05 cm/us West: Slope = -0.39597 +/- 0.00638703 DV = 5.51582 +/- 3.13904e-05
//row.scaleY                  	 = 3.70442e-06;// +/-1.87653e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5137 +/- 2.24198e-05
};
