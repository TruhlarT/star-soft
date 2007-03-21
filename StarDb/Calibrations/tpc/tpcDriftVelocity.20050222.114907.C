TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6053023
  row.laserDriftVelocityEast	 =   5.53526; // +/- 3.93459e-05 cm/us All: East = 5.53668 +/- 8.09885e-05
  row.laserDriftVelocityWest	 =   5.53526; // +/- 3.93459e-05 cm/us All: West = 5.53483 +/- 4.50151e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.919201 +/- 0.00715867
  return (TDataSet *)tableSet;// West = 1.00159 +/- 0.00821005 East = 0.657906 +/- 0.0146211
};
