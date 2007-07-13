TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 137074
  row.laserDriftVelocityEast	 =   5.57446; // +/- 1.63989e-05 cm/us All: East = 0.0281988 +/- 0.0033844
  row.laserDriftVelocityWest	 =   5.57446; // +/- 1.63989e-05 cm/us All: West = -0.0348681 +/- 0.0062801
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57446 +/- 1.63989e-05
  return (TDataSet *)tableSet;// West = 5.57474 +/- 3.45837e-05 East = 5.57438 +/- 1.86261e-05
};
