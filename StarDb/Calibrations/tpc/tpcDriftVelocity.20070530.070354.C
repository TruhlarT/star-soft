TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 150013
  row.laserDriftVelocityEast	 =   5.56978; // +/- -1 cm/us East: Slope = 0.315939 +/- 1.41421 DV = 4.45788 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57275; // +/- 1.60811e-05 cm/us West: Slope = 0.319698 +/- 0.00287991 DV = 5.57275 +/- 1.60811e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
