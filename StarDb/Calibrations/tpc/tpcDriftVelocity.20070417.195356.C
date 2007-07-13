TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107058
  row.laserDriftVelocityEast	 =   5.57645; // +/- 1.60228e-05 cm/us All: East = -0.298428 +/- 0.00330728
  row.laserDriftVelocityWest	 =   5.57645; // +/- 1.60228e-05 cm/us All: West = -0.467866 +/- 0.00532163
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57645 +/- 1.60228e-05
  return (TDataSet *)tableSet;// West = 5.57711 +/- 2.97298e-05 East = 5.57618 +/- 1.90219e-05
};
