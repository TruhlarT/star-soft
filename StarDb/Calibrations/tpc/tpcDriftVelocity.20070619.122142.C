TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170030
  row.laserDriftVelocityEast	 =   5.56979; // +/- 2.00808e-05 cm/us All: East = 1.06808 +/- 0.00492787
  row.laserDriftVelocityWest	 =   5.56979; // +/- 2.00808e-05 cm/us All: West = 0.581105 +/- 0.00540907
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56979 +/- 2.00808e-05
  return (TDataSet *)tableSet;// West = 5.57127 +/- 2.99403e-05 East = 5.56858 +/- 2.70728e-05
};
