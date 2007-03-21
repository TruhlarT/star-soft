TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6078081
  row.laserDriftVelocityEast	 =   5.52949; // +/- 8.291e-05 cm/us All: East = 5.52983 +/- 0.000124622
  row.laserDriftVelocityWest	 =   5.52949; // +/- 8.291e-05 cm/us All: West = 5.52922 +/- 0.000111052
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.511201 +/- 0.0147717
  return (TDataSet *)tableSet;// West = 0.582944 +/- 0.0198103 East = 0.421359 +/- 0.0221688
};
