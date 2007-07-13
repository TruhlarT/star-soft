TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169123
  row.laserDriftVelocityEast	 =   5.57017; // +/- 1.94976e-05 cm/us All: East = 0.876696 +/- 0.00436561
  row.laserDriftVelocityWest	 =   5.57017; // +/- 1.94976e-05 cm/us All: West = 0.612345 +/- 0.00571409
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57017 +/- 1.94976e-05
  return (TDataSet *)tableSet;// West = 5.57109 +/- 3.21986e-05 East = 5.56963 +/- 2.45003e-05
};
