TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125109
  row.laserDriftVelocityEast	 =   5.57875; // +/- 1.7605e-05 cm/us All: East = -0.747667 +/- 0.00389728
  row.laserDriftVelocityWest	 =   5.57875; // +/- 1.7605e-05 cm/us All: West = -0.775275 +/- 0.00529515
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57875 +/- 1.7605e-05
  return (TDataSet *)tableSet;// West = 5.57885 +/- 2.9348e-05 East = 5.57869 +/- 2.20035e-05
};
