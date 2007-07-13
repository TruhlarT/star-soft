TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 172138
  row.laserDriftVelocityEast	 =   5.57109; // +/- 2.05809e-05 cm/us All: East = 0.763826 +/- 0.00546581
  row.laserDriftVelocityWest	 =   5.57109; // +/- 2.05809e-05 cm/us All: West = 0.475944 +/- 0.00516057
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57109 +/- 2.05809e-05
  return (TDataSet *)tableSet;// West = 5.57188 +/- 2.87195e-05 East = 5.57025 +/- 2.95081e-05
};
