TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6039137
  row.laserDriftVelocityEast	 =   5.53247; // +/- 0.000169295 cm/us All: East = 5.53094 +/- 0.000381599
  row.laserDriftVelocityWest	 =   5.53247; // +/- 0.000169295 cm/us All: West = 5.53284 +/- 0.000188903
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.539749 +/- 0.030491
  return (TDataSet *)tableSet;// West = 0.472345 +/- 0.0339776 East = 0.818539 +/- 0.0691014
};
