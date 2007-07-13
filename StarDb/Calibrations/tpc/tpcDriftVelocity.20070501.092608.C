TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121020
  row.laserDriftVelocityEast	 =   5.57948; // +/- 2.47268e-05 cm/us All: East = -1.11547 +/- 0.00723696
  row.laserDriftVelocityWest	 =   5.57948; // +/- 2.47268e-05 cm/us All: West = -0.757385 +/- 0.0056983
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57948 +/- 2.47268e-05
  return (TDataSet *)tableSet;// West = 5.57873 +/- 3.14206e-05 East = 5.5807 +/- 4.00758e-05
};
