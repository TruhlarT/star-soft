TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6081015
  row.laserDriftVelocityEast	 =   5.52662; // +/- 0.000106656 cm/us All: East = 5.52662 +/- 0.00010722
  row.laserDriftVelocityWest	 =   5.52662; // +/- 0.000106656 cm/us All: West = 5.52698 +/- 0.0010411
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.384501 +/- 0.0191417
  return (TDataSet *)tableSet;// West = 0.304277 +/- 0.192876 East = 0.385299 +/- 0.0192367
};
