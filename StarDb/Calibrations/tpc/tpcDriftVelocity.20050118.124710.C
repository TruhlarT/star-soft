TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6018013
  row.laserDriftVelocityEast	 =   5.54412; // +/- 4.60258e-05 cm/us All: East = 5.54516 +/- 9.03678e-05
  row.laserDriftVelocityWest	 =   5.54412; // +/- 4.60258e-05 cm/us All: West = 5.54375 +/- 5.34823e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.28997 +/- 0.00866382
  return (TDataSet *)tableSet;// West = 1.35833 +/- 0.0100434 East = 1.09117 +/- 0.0171281
};
