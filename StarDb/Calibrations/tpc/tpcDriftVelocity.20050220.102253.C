TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6051019
  row.laserDriftVelocityEast	 =   5.53449; // +/- 5.83235e-05 cm/us All: East = 5.53884 +/- 0.000141022
  row.laserDriftVelocityWest	 =   5.53449; // +/- 5.83235e-05 cm/us All: West = 5.53359 +/- 6.40588e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.989261 +/- 0.0104656
  return (TDataSet *)tableSet;// West = 1.13449 +/- 0.0113568 East = 0.17134 +/- 0.0269516
};
