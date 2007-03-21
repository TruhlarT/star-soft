TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6040047
  row.laserDriftVelocityEast	 =   5.53017; // +/- 0.000211629 cm/us All: East = 5.52922 +/- 0.000415695
  row.laserDriftVelocityWest	 =   5.53017; // +/- 0.000211629 cm/us All: West = 5.5305 +/- 0.000245878
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.63526 +/- 0.0589406
  return (TDataSet *)tableSet;// West = 1.54923 +/- 0.0725524 East = 1.80224 +/- 0.101078
};
