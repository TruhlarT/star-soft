TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6075039
  row.laserDriftVelocityEast	 =   5.52925; // +/- 9.37104e-05 cm/us All: East = 5.52949 +/- 0.000134683
  row.laserDriftVelocityWest	 =   5.52925; // +/- 9.37104e-05 cm/us All: West = 5.52904 +/- 0.00013047
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.534348 +/- 0.0173116
  return (TDataSet *)tableSet;// West = 0.561149 +/- 0.0254604 East = 0.511304 +/- 0.0236089
};
