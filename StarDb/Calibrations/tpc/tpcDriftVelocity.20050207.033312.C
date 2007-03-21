TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6037072
  row.laserDriftVelocityEast	 =   5.53359; // +/- 0.000134818 cm/us All: East = 5.53396 +/- 0.000363687
  row.laserDriftVelocityWest	 =   5.53359; // +/- 0.000134818 cm/us All: West = 5.53354 +/- 0.00014516
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.28786 +/- 0.0246259
  return (TDataSet *)tableSet;// West = 2.29247 +/- 0.0261119 East = 2.25072 +/- 0.0740548
};
