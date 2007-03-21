TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6069096
  row.laserDriftVelocityEast	 =   5.53175; // +/- 0.000476191 cm/us All: East = 5.53251 +/- 0.000850385
  row.laserDriftVelocityWest	 =   5.53175; // +/- 0.000476191 cm/us All: West = 5.53141 +/- 0.000574754
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.65149 +/- 0.0837461
  return (TDataSet *)tableSet;// West = 0.674906 +/- 0.108155 East = 0.616432 +/- 0.132342
};
