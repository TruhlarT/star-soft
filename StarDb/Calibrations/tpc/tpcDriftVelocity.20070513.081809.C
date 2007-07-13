TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133023
  row.laserDriftVelocityEast	 =   5.5703; // +/- 2.77028e-05 cm/us All: East = 0.651362 +/- 0.00671818
  row.laserDriftVelocityWest	 =   5.5703; // +/- 2.77028e-05 cm/us All: West = 0.87799 +/- 0.00742214
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5703 +/- 2.77028e-05
  return (TDataSet *)tableSet;// West = 5.56964 +/- 4.09064e-05 East = 5.57086 +/- 3.76512e-05
};
