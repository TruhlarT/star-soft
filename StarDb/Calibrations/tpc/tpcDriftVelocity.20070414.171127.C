TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 104034
  row.laserDriftVelocityEast	 =   5.58021; // +/- 1.46471e-05 cm/us All: East = -1.00016 +/- 0.0034814
  row.laserDriftVelocityWest	 =   5.58021; // +/- 1.46471e-05 cm/us All: West = -1.0468 +/- 0.00399842
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58021 +/- 1.46471e-05
  return (TDataSet *)tableSet;// West = 5.58037 +/- 2.22947e-05 East = 5.58008 +/- 1.94281e-05
};
