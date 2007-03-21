TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6059060
  row.laserDriftVelocityEast	 =   5.53771; // +/- 6.80286e-05 cm/us All: East = 5.54171 +/- 0.000158967
  row.laserDriftVelocityWest	 =   5.53771; // +/- 6.80286e-05 cm/us All: West = 5.53681 +/- 7.5269e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.31483 +/- 0.0130227
  return (TDataSet *)tableSet;// West = 1.47831 +/- 0.0145033 East = 0.634504 +/- 0.0295858
};
