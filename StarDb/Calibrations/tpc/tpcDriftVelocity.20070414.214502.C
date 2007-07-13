TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 104057
  row.laserDriftVelocityEast	 =   5.58212; // +/- 1.72367e-05 cm/us All: East = -1.45746 +/- 0.00418467
  row.laserDriftVelocityWest	 =   5.58212; // +/- 1.72367e-05 cm/us All: West = -1.2416 +/- 0.00454115
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58212 +/- 1.72367e-05
  return (TDataSet *)tableSet;// West = 5.58147 +/- 2.53869e-05 East = 5.58268 +/- 2.34776e-05
};
