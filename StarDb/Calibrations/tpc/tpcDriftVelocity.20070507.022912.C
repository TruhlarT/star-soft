TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126095
  row.laserDriftVelocityEast	 =   5.57638; // +/- 1.97643e-05 cm/us All: East = -0.407733 +/- 0.00456723
  row.laserDriftVelocityWest	 =   5.57638; // +/- 1.97643e-05 cm/us All: West = -0.23699 +/- 0.00545806
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57638 +/- 1.97643e-05
  return (TDataSet *)tableSet;// West = 5.57585 +/- 3.05632e-05 East = 5.57676 +/- 2.59113e-05
};
