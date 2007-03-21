TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6070008
  row.laserDriftVelocityEast	 =   5.53267; // +/- 4.55636e-05 cm/us All: East = 5.53258 +/- 6.86316e-05
  row.laserDriftVelocityWest	 =   5.53267; // +/- 4.55636e-05 cm/us All: West = 5.53274 +/- 6.09276e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.3816 +/- 0.00813975
  return (TDataSet *)tableSet;// West = 0.362093 +/- 0.0108419 East = 0.406799 +/- 0.0123224
};
