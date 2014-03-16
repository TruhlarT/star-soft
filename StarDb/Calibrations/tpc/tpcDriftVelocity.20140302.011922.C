TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60062
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5138; // +/- 4.11464e-05 cm/us East: Slope = -0.0239647 +/- 0.00757049 DV = 5.5138 +/- 4.11464e-05
  row.laserDriftVelocityWest	 =   5.51565; // +/- 3.25882e-05 cm/us West: Slope = -0.368051 +/- 0.00612567 DV = 5.51565 +/- 3.25882e-05
//row.scaleY                  	 = 1.54501e-06;// +/-2.23362e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51493 +/- 2.55464e-05
};
