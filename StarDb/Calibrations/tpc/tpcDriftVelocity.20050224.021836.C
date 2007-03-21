TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6054065
  row.laserDriftVelocityEast	 =   5.532; // +/- 0.000124702 cm/us All: East = 5.53428 +/- 0.000302309
  row.laserDriftVelocityWest	 =   5.532; // +/- 0.000124702 cm/us All: West = 5.53153 +/- 0.000136891
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.33906 +/- 0.0220999
  return (TDataSet *)tableSet;// West = 1.41965 +/- 0.0236929 East = 0.799523 +/- 0.0613063
};
