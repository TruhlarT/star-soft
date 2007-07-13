TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 117021
  row.laserDriftVelocityEast	 =   5.57717; // +/- 2.00779e-05 cm/us All: East = -0.491795 +/- 0.00477987
  row.laserDriftVelocityWest	 =   5.57717; // +/- 2.00779e-05 cm/us All: West = -0.461438 +/- 0.00542858
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57717 +/- 2.00779e-05
  return (TDataSet *)tableSet;// West = 5.5771 +/- 3.00726e-05 East = 5.57723 +/- 2.69692e-05
};
