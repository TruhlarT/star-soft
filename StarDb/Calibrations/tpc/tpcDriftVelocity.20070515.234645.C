TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135105
  row.laserDriftVelocityEast	 =   5.5761; // +/- 1.92212e-05 cm/us All: East = -0.353686 +/- 0.00445315
  row.laserDriftVelocityWest	 =   5.5761; // +/- 1.92212e-05 cm/us All: West = -0.173307 +/- 0.00560024
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5761 +/- 1.92212e-05
  return (TDataSet *)tableSet;// West = 5.57548 +/- 3.06427e-05 East = 5.5765 +/- 2.46805e-05
};
