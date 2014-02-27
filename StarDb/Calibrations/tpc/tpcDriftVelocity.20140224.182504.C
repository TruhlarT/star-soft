TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51137; // +/- 4.16997e-05 cm/us East: Slope = -1.26014 +/- 0.00754842 DV = 5.51137 +/- 4.16997e-05
  row.laserDriftVelocityWest	 =   5.50742; // +/- 3.60787e-05 cm/us West: Slope = -0.533559 +/- 0.00682866 DV = 5.50742 +/- 3.60787e-05
//row.scaleY                  	 = -1.1092e-06;// +/-2.27293e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50911 +/- 2.7284e-05
};
