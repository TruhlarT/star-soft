TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125064
  row.laserDriftVelocityEast	 =   5.57832; // +/- 1.70059e-05 cm/us All: East = -0.6613 +/- 0.00349554
  row.laserDriftVelocityWest	 =   5.57832; // +/- 1.70059e-05 cm/us All: West = -0.751242 +/- 0.00645319
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57832 +/- 1.70059e-05
  return (TDataSet *)tableSet;// West = 5.57872 +/- 3.54279e-05 East = 5.57819 +/- 1.93852e-05
};
