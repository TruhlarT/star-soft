TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 159029
  row.laserDriftVelocityEast	 =   5.57066; // +/- -1 cm/us East: Slope = 0.687616 +/- 0.022922 DV = 5.57085 +/- 0.000112066
  row.laserDriftVelocityWest	 =   5.57387; // +/- 2.21865e-05 cm/us West: Slope = 0.116712 +/- 0.00404403 DV = 5.57387 +/- 2.21865e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
