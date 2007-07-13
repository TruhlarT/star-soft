TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126044
  row.laserDriftVelocityEast	 =   5.57654; // +/- 1.88062e-05 cm/us All: East = -0.311274 +/- 0.00385807
  row.laserDriftVelocityWest	 =   5.57654; // +/- 1.88062e-05 cm/us All: West = -0.485141 +/- 0.00682489
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57654 +/- 1.88062e-05
  return (TDataSet *)tableSet;// West = 5.57724 +/- 3.79287e-05 East = 5.57631 +/- 2.16556e-05
};
