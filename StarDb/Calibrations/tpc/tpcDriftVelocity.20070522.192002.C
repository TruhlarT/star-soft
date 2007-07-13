TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 142033
  row.laserDriftVelocityEast	 =   5.5741; // +/- 1.334e-05 cm/us All: East = 0.0940196 +/- 0.0027251
  row.laserDriftVelocityWest	 =   5.5741; // +/- 1.334e-05 cm/us All: West = 0.0199011 +/- 0.00484071
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5741 +/- 1.334e-05
  return (TDataSet *)tableSet;// West = 5.57442 +/- 2.70916e-05 East = 5.57399 +/- 1.53269e-05
};
