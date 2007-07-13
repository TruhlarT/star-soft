TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 97093
  row.laserDriftVelocityEast	 =   5.57586; // +/- 1.78462e-05 cm/us All: East = -1.6761 +/- 0.00435924
  row.laserDriftVelocityWest	 =   5.57586; // +/- 1.78462e-05 cm/us All: West = -1.39127 +/- 0.00470576
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57586 +/- 1.78462e-05
  return (TDataSet *)tableSet;// West = 5.57499 +/- 2.64943e-05 East = 5.57659 +/- 2.41456e-05
};
