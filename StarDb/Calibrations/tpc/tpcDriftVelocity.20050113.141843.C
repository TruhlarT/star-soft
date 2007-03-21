TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6013065
  row.laserDriftVelocityEast	 =   5.52361; // +/- 0.00010096 cm/us All: East = 5.52251 +/- 0.000225425
  row.laserDriftVelocityWest	 =   5.52361; // +/- 0.00010096 cm/us All: West = 5.52388 +/- 0.000112918
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -0.726538 +/- 0.0250776
  return (TDataSet *)tableSet;// West = -0.860151 +/- 0.0295643 East = -0.383796 +/- 0.0473506
};
