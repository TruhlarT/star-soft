TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 175009
  row.laserDriftVelocityEast	 =   5.57226; // +/- 2.32708e-05 cm/us All: East = 0.520283 +/- 0.00585851
  row.laserDriftVelocityWest	 =   5.57226; // +/- 2.32708e-05 cm/us All: West = 0.297238 +/- 0.00594822
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57226 +/- 2.32708e-05
  return (TDataSet *)tableSet;// West = 5.5729 +/- 3.30514e-05 East = 5.57163 +/- 3.27701e-05
};
