TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6058083
  row.laserDriftVelocityEast	 =   5.53682; // +/- 0.000110747 cm/us All: East = 5.53979 +/- 0.000369168
  row.laserDriftVelocityWest	 =   5.53682; // +/- 0.000110747 cm/us All: West = 5.53652 +/- 0.000116094
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.41136 +/- 0.0196886
  return (TDataSet *)tableSet;// West = 1.46929 +/- 0.0207443 East = 0.885339 +/- 0.0625136
};
