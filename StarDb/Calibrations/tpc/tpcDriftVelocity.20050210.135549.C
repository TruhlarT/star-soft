TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6041052
  row.laserDriftVelocityEast	 =   5.52792; // +/- 0.000127475 cm/us All: East = 5.52813 +/- 0.000316959
  row.laserDriftVelocityWest	 =   5.52792; // +/- 0.000127475 cm/us All: West = 5.52788 +/- 0.000139232
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.5394 +/- 0.0221094
  return (TDataSet *)tableSet;// West = 2.53839 +/- 0.0240359 East = 2.54497 +/- 0.0563635
};
