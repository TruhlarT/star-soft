TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6082013
  row.laserDriftVelocityEast	 =   5.5255; // +/- 3.37432e-05 cm/us All: East = 5.52476 +/- 5.29204e-05
  row.laserDriftVelocityWest	 =   5.5255; // +/- 3.37432e-05 cm/us All: West = 5.52601 +/- 4.38024e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.66752 +/- 0.00640051
  return (TDataSet *)tableSet;// West = 0.5798 +/- 0.00825766 East = 0.799528 +/- 0.01013
};
