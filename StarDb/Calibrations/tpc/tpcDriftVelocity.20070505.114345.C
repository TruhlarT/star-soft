TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125043
  row.laserDriftVelocityEast	 =   5.57873; // +/- 1.74876e-05 cm/us All: East = -0.746227 +/- 0.00361577
  row.laserDriftVelocityWest	 =   5.57873; // +/- 1.74876e-05 cm/us All: West = -0.757322 +/- 0.00626602
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57873 +/- 1.74876e-05
  return (TDataSet *)tableSet;// West = 5.57877 +/- 3.49769e-05 East = 5.57871 +/- 2.01925e-05
};
