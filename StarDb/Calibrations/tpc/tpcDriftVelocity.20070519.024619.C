TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138096
  row.laserDriftVelocityEast	 =   5.57446; // +/- 3.12088e-05 cm/us All: East = 0.225133 +/- 0.0118474
  row.laserDriftVelocityWest	 =   5.57446; // +/- 3.12088e-05 cm/us All: West = -0.051269 +/- 0.00631841
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57446 +/- 3.12088e-05
  return (TDataSet *)tableSet;// West = 5.57481 +/- 3.53953e-05 East = 5.57326 +/- 6.61524e-05
};
