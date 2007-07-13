TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105092
  row.laserDriftVelocityEast	 =   5.58214; // +/- 1.23149e-05 cm/us All: East = -1.31632 +/- 0.00306851
  row.laserDriftVelocityWest	 =   5.58214; // +/- 1.23149e-05 cm/us All: West = -1.41001 +/- 0.00317878
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58214 +/- 1.23149e-05
  return (TDataSet *)tableSet;// West = 5.5824 +/- 1.77471e-05 East = 5.58189 +/- 1.71025e-05
};
