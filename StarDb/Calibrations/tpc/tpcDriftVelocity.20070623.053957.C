TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 174010
  row.laserDriftVelocityEast	 =   5.57163; // +/- 2.20259e-05 cm/us All: East = 0.638845 +/- 0.00580452
  row.laserDriftVelocityWest	 =   5.57163; // +/- 2.20259e-05 cm/us All: West = 0.416366 +/- 0.00544634
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57163 +/- 2.20259e-05
  return (TDataSet *)tableSet;// West = 5.57222 +/- 2.99186e-05 East = 5.57094 +/- 3.25457e-05
};
