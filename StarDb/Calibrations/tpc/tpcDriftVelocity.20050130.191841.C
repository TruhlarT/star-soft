TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6030063
  row.laserDriftVelocityEast	 =   5.55509; // +/- 9.84368e-05 cm/us All: East = 5.55365 +/- 0.00146381
  row.laserDriftVelocityWest	 =   5.55509; // +/- 9.84368e-05 cm/us All: West = 5.55509 +/- 9.86601e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -1.6764 +/- 0.0176892
  return (TDataSet *)tableSet;// West = -1.67721 +/- 0.0177216 East = -1.45659 +/- 0.292601
};
