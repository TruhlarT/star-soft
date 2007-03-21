TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6080022
  row.laserDriftVelocityEast	 =   5.52798; // +/- 0.000742601 cm/us All: East = 5.52778 +/- 0.000831236
  row.laserDriftVelocityWest	 =   5.52798; // +/- 0.000742601 cm/us All: West = 5.52877 +/- 0.00165271
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.541225 +/- 0.113602
  return (TDataSet *)tableSet;// West = 0.411967 +/- 0.288904 East = 0.564866 +/- 0.123554
};
