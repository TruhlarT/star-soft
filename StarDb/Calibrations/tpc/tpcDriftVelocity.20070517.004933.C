TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 136079
  row.laserDriftVelocityEast	 =   5.57534; // +/- 1.85943e-05 cm/us All: East = -0.13901 +/- 0.00369839
  row.laserDriftVelocityWest	 =   5.57534; // +/- 1.85943e-05 cm/us All: West = -0.194814 +/- 0.00782689
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57534 +/- 1.85943e-05
  return (TDataSet *)tableSet;// West = 5.57562 +/- 4.40052e-05 East = 5.57528 +/- 2.05158e-05
};
