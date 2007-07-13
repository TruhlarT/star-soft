TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 116091
  row.laserDriftVelocityEast	 =   5.57697; // +/- 2.03176e-05 cm/us All: East = -0.436502 +/- 0.00638932
  row.laserDriftVelocityWest	 =   5.57697; // +/- 2.03176e-05 cm/us All: West = -0.437924 +/- 0.00443607
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57697 +/- 2.03176e-05
  return (TDataSet *)tableSet;// West = 5.57696 +/- 2.48615e-05 East = 5.57699 +/- 3.52546e-05
};
