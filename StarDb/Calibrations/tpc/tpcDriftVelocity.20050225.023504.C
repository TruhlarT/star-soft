TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6055087
  row.laserDriftVelocityEast	 =   5.53288; // +/- 0.000112765 cm/us All: East = 5.53377 +/- 0.000226833
  row.laserDriftVelocityWest	 =   5.53288; // +/- 0.000112765 cm/us All: West = 5.53259 +/- 0.000129962
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.10803 +/- 0.0203057
  return (TDataSet *)tableSet;// West = 1.20865 +/- 0.023416 East = 0.802949 +/- 0.0407741
};
