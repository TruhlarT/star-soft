TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 174038
  row.laserDriftVelocityEast	 =   5.57183; // +/- 2.38749e-05 cm/us All: East = 0.6188 +/- 0.00635503
  row.laserDriftVelocityWest	 =   5.57183; // +/- 2.38749e-05 cm/us All: West = 0.361144 +/- 0.00588635
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57183 +/- 2.38749e-05
  return (TDataSet *)tableSet;// West = 5.57252 +/- 3.26622e-05 East = 5.57105 +/- 3.49858e-05
};
