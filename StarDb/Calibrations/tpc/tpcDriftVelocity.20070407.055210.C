TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 97022
  row.laserDriftVelocityEast	 =   5.57627; // +/- 1.50154e-05 cm/us All: East = -1.77834 +/- 0.00403966
  row.laserDriftVelocityWest	 =   5.57627; // +/- 1.50154e-05 cm/us All: West = -1.49485 +/- 0.00363823
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57627 +/- 1.50154e-05
  return (TDataSet *)tableSet;// West = 5.57558 +/- 2.01695e-05 East = 5.57714 +/- 2.24894e-05
};
