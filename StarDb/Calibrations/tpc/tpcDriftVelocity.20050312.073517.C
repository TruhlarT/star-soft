TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6071009
  row.laserDriftVelocityEast	 =   5.5311; // +/- 4.52002e-05 cm/us All: East = 5.53156 +/- 6.95286e-05
  row.laserDriftVelocityWest	 =   5.5311; // +/- 4.52002e-05 cm/us All: West = 5.53076 +/- 5.94854e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.547668 +/- 0.00836685
  return (TDataSet *)tableSet;// West = 0.604135 +/- 0.0108563 East = 0.465064 +/- 0.0131305
};
