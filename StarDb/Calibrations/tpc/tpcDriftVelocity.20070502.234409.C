TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 122080
  row.laserDriftVelocityEast	 =   5.57926; // +/- 2.30632e-05 cm/us All: East = -0.891984 +/- 0.00601828
  row.laserDriftVelocityWest	 =   5.57926; // +/- 2.30632e-05 cm/us All: West = -0.806835 +/- 0.00563125
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57926 +/- 2.30632e-05
  return (TDataSet *)tableSet;// West = 5.57903 +/- 3.16529e-05 East = 5.57951 +/- 3.36735e-05
};
