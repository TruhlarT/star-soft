TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51026
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50451; // +/- 2.46493e-05 cm/us East: Slope = 0.230321 +/- 0.00440141 DV = 5.50451 +/- 2.46493e-05
  row.laserDriftVelocityWest	 =   5.50092; // +/- 1.93248e-05 cm/us West: Slope = 0.870603 +/- 0.00348703 DV = 5.50092 +/- 1.93248e-05
//row.scaleY                  	 = 2.15579e-06;// +/-3.48258e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50228 +/- 1.52082e-05
};
