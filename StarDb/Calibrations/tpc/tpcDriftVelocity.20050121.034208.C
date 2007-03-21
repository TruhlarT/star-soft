TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6020063
  row.laserDriftVelocityEast	 =   5.55251; // +/- 5.89835e-05 cm/us All: East = 5.55257 +/- 0.00011861
  row.laserDriftVelocityWest	 =   5.55251; // +/- 5.89835e-05 cm/us All: West = 5.55249 +/- 6.79859e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.42103 +/- 0.0105974
  return (TDataSet *)tableSet;// West = 1.42505 +/- 0.0123066 East = 1.40952 +/- 0.0208442
};
