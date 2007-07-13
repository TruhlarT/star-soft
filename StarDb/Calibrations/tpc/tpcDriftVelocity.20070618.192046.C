TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169091
  row.laserDriftVelocityEast	 =   5.5702; // +/- 1.84475e-05 cm/us All: East = 0.945698 +/- 0.0043973
  row.laserDriftVelocityWest	 =   5.5702; // +/- 1.84475e-05 cm/us All: West = 0.549574 +/- 0.00511121
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5702 +/- 1.84475e-05
  return (TDataSet *)tableSet;// West = 5.57145 +/- 2.8366e-05 East = 5.56927 +/- 2.42844e-05
};
