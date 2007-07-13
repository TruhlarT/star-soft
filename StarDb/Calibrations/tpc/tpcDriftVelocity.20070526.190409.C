TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 146061
  row.laserDriftVelocityEast	 =   5.5742; // +/- 1.62937e-05 cm/us All: East = -0.0626286 +/- 1.00646
  row.laserDriftVelocityWest	 =   5.5742; // +/- 1.62937e-05 cm/us All: West = 0.0581475 +/- 0.00294031
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5742 +/- 1.62937e-05
  return (TDataSet *)tableSet;// West = 5.5742 +/- 1.62938e-05 East = 5.57594 +/- 0.00920377
};
