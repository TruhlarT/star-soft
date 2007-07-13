TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 136057
  row.laserDriftVelocityEast	 =   5.5758; // +/- 1.92039e-05 cm/us All: East = -0.216794 +/- 0.00440341
  row.laserDriftVelocityWest	 =   5.5758; // +/- 1.92039e-05 cm/us All: West = -0.249506 +/- 0.00549856
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5758 +/- 1.92039e-05
  return (TDataSet *)tableSet;// West = 5.57592 +/- 3.07223e-05 East = 5.57573 +/- 2.46027e-05
};
