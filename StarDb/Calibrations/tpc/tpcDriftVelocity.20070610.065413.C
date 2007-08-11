TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161018
  row.laserDriftVelocityEast	 =   5.56965; // +/- -1 cm/us East: Slope = 0.755607 +/- 0.0105512 DV = 5.57033 +/- 5.80852e-05
  row.laserDriftVelocityWest	 =   5.5729; // +/- 1.59966e-05 cm/us West: Slope = 0.29046 +/- 0.00287347 DV = 5.5729 +/- 1.59966e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
