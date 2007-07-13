TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 168107
  row.laserDriftVelocityEast	 =   5.57102; // +/- 1.9748e-05 cm/us All: East = 0.753908 +/- 0.00428574
  row.laserDriftVelocityWest	 =   5.57102; // +/- 1.9748e-05 cm/us All: West = 0.341687 +/- 0.00635543
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57102 +/- 1.9748e-05
  return (TDataSet *)tableSet;// West = 5.57263 +/- 3.59305e-05 East = 5.57032 +/- 2.36385e-05
};
