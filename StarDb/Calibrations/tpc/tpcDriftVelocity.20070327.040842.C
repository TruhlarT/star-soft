TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 85175
  row.laserDriftVelocityEast	 =   5.57038; // +/- 2.20384e-05 cm/us All: East = -0.527214 +/- 0.0045775
  row.laserDriftVelocityWest	 =   5.57038; // +/- 2.20384e-05 cm/us All: West = -0.674462 +/- 0.00768369
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57038 +/- 2.20384e-05
  return (TDataSet *)tableSet;// West = 5.57101 +/- 4.31894e-05 East = 5.57016 +/- 2.56257e-05
};
