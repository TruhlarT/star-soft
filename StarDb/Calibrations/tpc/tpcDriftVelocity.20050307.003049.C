TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6065057
  row.laserDriftVelocityEast	 =   5.53381; // +/- 0.000358059 cm/us All: East = 5.53971 +/- 0.00145627
  row.laserDriftVelocityWest	 =   5.53381; // +/- 0.000358059 cm/us All: West = 5.53343 +/- 0.000369399
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.71494 +/- 0.0638859
  return (TDataSet *)tableSet;// West = 1.79316 +/- 0.0661972 East = 0.653067 +/- 0.243893
};
