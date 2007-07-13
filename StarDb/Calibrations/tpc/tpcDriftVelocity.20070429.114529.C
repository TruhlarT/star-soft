TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119020
  row.laserDriftVelocityEast	 =   5.57808; // +/- 1.72949e-05 cm/us All: East = -0.644124 +/- 0.00368177
  row.laserDriftVelocityWest	 =   5.57808; // +/- 1.72949e-05 cm/us All: West = -0.62807 +/- 0.00573247
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57808 +/- 1.72949e-05
  return (TDataSet *)tableSet;// West = 5.57803 +/- 3.21812e-05 East = 5.57811 +/- 2.05083e-05
};
