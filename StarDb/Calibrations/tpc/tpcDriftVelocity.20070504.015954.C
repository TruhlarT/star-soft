TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 123075
  row.laserDriftVelocityEast	 =   5.57952; // +/- 1.9774e-05 cm/us All: East = -0.927837 +/- 0.00422418
  row.laserDriftVelocityWest	 =   5.57952; // +/- 1.9774e-05 cm/us All: West = -0.827205 +/- 0.00640458
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57952 +/- 1.9774e-05
  return (TDataSet *)tableSet;// West = 5.57914 +/- 3.54611e-05 East = 5.57969 +/- 2.38215e-05
};
