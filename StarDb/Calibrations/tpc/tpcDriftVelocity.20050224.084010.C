TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6055010
  row.laserDriftVelocityEast	 =   5.53268; // +/- 4.36457e-05 cm/us All: East = 5.53431 +/- 8.68418e-05
  row.laserDriftVelocityWest	 =   5.53268; // +/- 4.36457e-05 cm/us All: West = 5.53213 +/- 5.04852e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.18067 +/- 0.00789278
  return (TDataSet *)tableSet;// West = 1.28319 +/- 0.0090955 East = 0.868085 +/- 0.0158818
};
