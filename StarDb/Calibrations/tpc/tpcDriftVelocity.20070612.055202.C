TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 163008
  row.laserDriftVelocityEast	 =   5.56968; // +/- -1 cm/us East: Slope = 0.624494 +/- 0.00846207 DV = 5.57099 +/- 4.69073e-05
  row.laserDriftVelocityWest	 =   5.57298; // +/- 2.36426e-05 cm/us West: Slope = 0.278139 +/- 0.00425021 DV = 5.57298 +/- 2.36426e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
