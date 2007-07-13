TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 136013
  row.laserDriftVelocityEast	 =   5.57579; // +/- 2.07906e-05 cm/us All: East = -0.291255 +/- 0.00496843
  row.laserDriftVelocityWest	 =   5.57579; // +/- 2.07906e-05 cm/us All: West = -0.106743 +/- 0.00584542
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57579 +/- 2.07906e-05
  return (TDataSet *)tableSet;// West = 5.57515 +/- 3.1894e-05 East = 5.57625 +/- 2.74161e-05
};
