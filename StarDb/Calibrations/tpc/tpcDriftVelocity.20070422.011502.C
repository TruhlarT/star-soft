TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111101
  row.laserDriftVelocityEast	 =   5.57553; // +/- 1.96224e-05 cm/us All: East = -0.176069 +/- 0.00496155
  row.laserDriftVelocityWest	 =   5.57553; // +/- 1.96224e-05 cm/us All: West = -0.185172 +/- 0.00494775
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57553 +/- 1.96224e-05
  return (TDataSet *)tableSet;// West = 5.57556 +/- 2.77222e-05 East = 5.5755 +/- 2.77785e-05
};
