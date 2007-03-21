TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6046036
  row.laserDriftVelocityEast	 =   5.52685; // +/- 0.000132837 cm/us All: East = 5.52639 +/- 0.000312544
  row.laserDriftVelocityWest	 =   5.52685; // +/- 0.000132837 cm/us All: West = 5.52695 +/- 0.000146751
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.6158 +/- 0.0239824
  return (TDataSet *)tableSet;// West = 1.59812 +/- 0.0264793 East = 1.69648 +/- 0.0565748
};
