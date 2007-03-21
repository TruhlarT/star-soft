TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6074022
  row.laserDriftVelocityEast	 =   5.53014; // +/- 6.09593e-05 cm/us All: East = 5.53086 +/- 9.4471e-05
  row.laserDriftVelocityWest	 =   5.53014; // +/- 6.09593e-05 cm/us All: West = 5.52962 +/- 7.97945e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.351894 +/- 0.0111757
  return (TDataSet *)tableSet;// West = 0.447843 +/- 0.0146635 East = 0.21892 +/- 0.0172623
};
