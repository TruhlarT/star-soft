TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6080008
  row.laserDriftVelocityEast	 =   5.52811; // +/- 5.91171e-05 cm/us All: East = 5.52836 +/- 9.52406e-05
  row.laserDriftVelocityWest	 =   5.52811; // +/- 5.91171e-05 cm/us All: West = 5.52796 +/- 7.54008e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.53291 +/- 0.010658
  return (TDataSet *)tableSet;// West = 0.560968 +/- 0.0135355 East = 0.48713 +/- 0.0172899
};
