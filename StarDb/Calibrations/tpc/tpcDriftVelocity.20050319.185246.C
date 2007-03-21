TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6078069
  row.laserDriftVelocityEast	 =   5.52945; // +/- 0.000332572 cm/us All: East = 5.52744 +/- 0.000665448
  row.laserDriftVelocityWest	 =   5.52945; // +/- 0.000332572 cm/us All: West = 5.53011 +/- 0.000383963
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -2.78005 +/- 0.0550116
  return (TDataSet *)tableSet;// West = -2.90717 +/- 0.0673538 East = -2.52532 +/- 0.0953432
};
