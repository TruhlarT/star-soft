TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111100
  row.laserDriftVelocityEast	 =   5.57556; // +/- 1.76906e-05 cm/us All: East = -0.172307 +/- 0.00468567
  row.laserDriftVelocityWest	 =   5.57556; // +/- 1.76906e-05 cm/us All: West = -0.190206 +/- 0.00430317
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57556 +/- 1.76906e-05
  return (TDataSet *)tableSet;// West = 5.57558 +/- 2.43393e-05 East = 5.57554 +/- 2.57575e-05
};
