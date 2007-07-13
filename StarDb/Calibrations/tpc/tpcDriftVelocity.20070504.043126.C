TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 124003
  row.laserDriftVelocityEast	 =   5.57834; // +/- 1.73807e-05 cm/us All: East = -0.642931 +/- 0.00357551
  row.laserDriftVelocityWest	 =   5.57834; // +/- 1.73807e-05 cm/us All: West = -0.81029 +/- 0.00628368
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57834 +/- 1.73807e-05
  return (TDataSet *)tableSet;// West = 5.57902 +/- 3.58484e-05 East = 5.57813 +/- 1.98727e-05
};
