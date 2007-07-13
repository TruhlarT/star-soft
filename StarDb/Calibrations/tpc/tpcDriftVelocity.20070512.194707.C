TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 132025
  row.laserDriftVelocityEast	 =   5.56777; // +/- 2.37744e-05 cm/us All: East = 1.19225 +/- 0.00508623
  row.laserDriftVelocityWest	 =   5.56777; // +/- 2.37744e-05 cm/us All: West = 1.26004 +/- 0.00738473
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56777 +/- 2.37744e-05
  return (TDataSet *)tableSet;// West = 5.56753 +/- 4.20408e-05 East = 5.56789 +/- 2.88264e-05
};
