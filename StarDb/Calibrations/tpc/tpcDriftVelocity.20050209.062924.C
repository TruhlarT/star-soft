TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6040002
  row.laserDriftVelocityEast	 =   5.53152; // +/- 4.17614e-05 cm/us All: East = 5.53088 +/- 0.000103092
  row.laserDriftVelocityWest	 =   5.53152; // +/- 4.17614e-05 cm/us All: West = 5.53165 +/- 4.5677e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.24543 +/- 0.0091986
  return (TDataSet *)tableSet;// West = 1.21859 +/- 0.0102309 East = 1.35866 +/- 0.0210136
};
