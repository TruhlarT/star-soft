TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 174106
  row.laserDriftVelocityEast	 =   5.57194; // +/- 3.06298e-05 cm/us All: East = 0.630843 +/- 0.00748186
  row.laserDriftVelocityWest	 =   5.57194; // +/- 3.06298e-05 cm/us All: West = 0.269031 +/- 0.00805315
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57194 +/- 3.06298e-05
  return (TDataSet *)tableSet;// West = 5.57302 +/- 4.51801e-05 East = 5.57103 +/- 4.16671e-05
};
