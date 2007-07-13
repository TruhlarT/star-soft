TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 134038
  row.laserDriftVelocityEast	 =   5.57315; // +/- 1.95091e-05 cm/us All: East = 0.223158 +/- 0.00410057
  row.laserDriftVelocityWest	 =   5.57315; // +/- 1.95091e-05 cm/us All: West = 0.354717 +/- 0.00679698
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57315 +/- 1.95091e-05
  return (TDataSet *)tableSet;// West = 5.57257 +/- 3.85712e-05 East = 5.57335 +/- 2.26152e-05
};
