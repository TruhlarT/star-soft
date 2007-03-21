TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6056064
  row.laserDriftVelocityEast	 =   5.53429; // +/- 3.79348e-05 cm/us All: East = 5.53579 +/- 7.09375e-05
  row.laserDriftVelocityWest	 =   5.53429; // +/- 3.79348e-05 cm/us All: West = 5.53369 +/- 4.48931e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.06765 +/- 0.00682343
  return (TDataSet *)tableSet;// West = 1.17948 +/- 0.00813023 East = 0.801189 +/- 0.0125495
};
