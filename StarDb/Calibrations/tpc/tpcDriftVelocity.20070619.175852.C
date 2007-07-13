TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170052
  row.laserDriftVelocityEast	 =   5.57001; // +/- 2.12791e-05 cm/us All: East = 1.04296 +/- 0.00540674
  row.laserDriftVelocityWest	 =   5.57001; // +/- 2.12791e-05 cm/us All: West = 0.587777 +/- 0.00538045
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57001 +/- 2.12791e-05
  return (TDataSet *)tableSet;// West = 5.57125 +/- 2.98639e-05 East = 5.56874 +/- 3.03277e-05
};
