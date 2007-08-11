TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119114
  row.laserDriftVelocityEast	 =   5.57637; // +/- 1.45485e-05 cm/us East: Slope = -0.329514 +/- 0.00260752 DV = 5.57637 +/- 1.45485e-05
  row.laserDriftVelocityWest	 =   5.5782; // +/- 2.22219e-05 cm/us West: Slope = -0.656022 +/- 0.00398251 DV = 5.5782 +/- 2.22219e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
