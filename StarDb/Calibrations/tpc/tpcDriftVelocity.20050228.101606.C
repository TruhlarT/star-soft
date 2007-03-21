TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6059017
  row.laserDriftVelocityEast	 =   5.53681; // +/- 3.35777e-05 cm/us All: East = 5.54062 +/- 8.78478e-05
  row.laserDriftVelocityWest	 =   5.53681; // +/- 3.35777e-05 cm/us All: West = 5.53616 +/- 3.63367e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.37966 +/- 0.00608484
  return (TDataSet *)tableSet;// West = 1.50151 +/- 0.0066017 East = 0.691642 +/- 0.0156872
};
