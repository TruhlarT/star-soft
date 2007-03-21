TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6016016
  row.laserDriftVelocityEast	 =   5.5368; // +/- 0.000139719 cm/us All: East = 5.53886 +/- 0.000778643
  row.laserDriftVelocityWest	 =   5.5368; // +/- 0.000139719 cm/us All: West = 5.53673 +/- 0.000142024
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.45838 +/- 0.0253209
  return (TDataSet *)tableSet;// West = 1.47264 +/- 0.0257768 East = 1.06576 +/- 0.135232
};
