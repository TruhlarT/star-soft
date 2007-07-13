TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139066
  row.laserDriftVelocityEast	 =   5.57474; // +/- 1.79068e-05 cm/us All: East = -0.0103673 +/- 0.00386145
  row.laserDriftVelocityWest	 =   5.57474; // +/- 1.79068e-05 cm/us All: West = -0.102515 +/- 0.00571576
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57474 +/- 1.79068e-05
  return (TDataSet *)tableSet;// West = 5.5751 +/- 3.19063e-05 East = 5.57457 +/- 2.16354e-05
};
