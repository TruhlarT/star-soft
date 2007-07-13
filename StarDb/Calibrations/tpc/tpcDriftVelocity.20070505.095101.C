TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125034
  row.laserDriftVelocityEast	 =   5.57864; // +/- 2.20381e-05 cm/us All: East = -0.775254 +/- 0.0055014
  row.laserDriftVelocityWest	 =   5.57864; // +/- 2.20381e-05 cm/us All: West = -0.699102 +/- 0.00570133
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57864 +/- 2.20381e-05
  return (TDataSet *)tableSet;// West = 5.57846 +/- 3.13757e-05 East = 5.57881 +/- 3.09617e-05
};
