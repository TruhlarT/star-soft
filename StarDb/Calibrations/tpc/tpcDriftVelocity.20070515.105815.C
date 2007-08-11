TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135033
  row.laserDriftVelocityEast	 =   5.57271; // +/- 2.26597e-05 cm/us East: Slope = 0.329972 +/- 0.00408073 DV = 5.57271 +/- 2.26597e-05
  row.laserDriftVelocityWest	 =   5.57484; // +/- 3.14059e-05 cm/us West: Slope = -0.0534364 +/- 0.00560166 DV = 5.57484 +/- 3.14059e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
