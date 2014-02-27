TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47024
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49188; // +/- 5.27483e-05 cm/us East: Slope = 0.507978 +/- 0.0117229 DV = 5.49188 +/- 5.27483e-05
  row.laserDriftVelocityWest	 =   5.49171; // +/- 2.96765e-05 cm/us West: Slope = 0.42507 +/- 0.00590524 DV = 5.49171 +/- 2.96765e-05
//row.scaleY                  	 = -5.91788e-07;// +/-1.93148e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49175 +/- 2.58641e-05
};
