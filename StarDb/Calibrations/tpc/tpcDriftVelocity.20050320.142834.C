TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6079050
  row.laserDriftVelocityEast	 =   5.52904; // +/- 0.000690326 cm/us All: East = 5.52899 +/- 0.00102989
  row.laserDriftVelocityWest	 =   5.52904; // +/- 0.000690326 cm/us All: West = 5.52908 +/- 0.000930233
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.340142 +/- 0.108545
  return (TDataSet *)tableSet;// West = 0.374806 +/- 0.135882 East = 0.279017 +/- 0.180438
};
