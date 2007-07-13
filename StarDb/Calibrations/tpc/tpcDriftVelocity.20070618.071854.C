TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169017
  row.laserDriftVelocityEast	 =   5.57061; // +/- 1.97444e-05 cm/us All: East = 0.814416 +/- 0.00411169
  row.laserDriftVelocityWest	 =   5.57061; // +/- 1.97444e-05 cm/us All: West = 0.394043 +/- 0.00683125
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57061 +/- 1.97444e-05
  return (TDataSet *)tableSet;// West = 5.57234 +/- 3.81583e-05 East = 5.56998 +/- 2.30733e-05
};
