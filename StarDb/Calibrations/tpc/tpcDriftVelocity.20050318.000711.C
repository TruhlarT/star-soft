TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6076096
  row.laserDriftVelocityEast	 =   5.53064; // +/- 7.59671e-05 cm/us All: East = 5.53036 +/- 0.000128684
  row.laserDriftVelocityWest	 =   5.53064; // +/- 7.59671e-05 cm/us All: West = 5.53079 +/- 9.41169e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.396891 +/- 0.013614
  return (TDataSet *)tableSet;// West = 0.351699 +/- 0.017052 East = 0.476338 +/- 0.0226089
};
