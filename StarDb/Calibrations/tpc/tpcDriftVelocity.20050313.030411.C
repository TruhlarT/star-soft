TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6071090
  row.laserDriftVelocityEast	 =   5.53233; // +/- 0.000587309 cm/us All: East = 5.53241 +/- 0.000732336
  row.laserDriftVelocityWest	 =   5.53233; // +/- 0.000587309 cm/us All: West = 5.53219 +/- 0.000983161
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.10363 +/- 0.0967269
  return (TDataSet *)tableSet;// West = 0.101475 +/- 0.151128 East = 0.105125 +/- 0.12589
};
