TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 97076
  row.laserDriftVelocityEast	 =   5.57399; // +/- 2.88709e-05 cm/us East: Slope = -1.21137 +/- 0.00514907 DV = 5.57399 +/- 2.88709e-05
  row.laserDriftVelocityWest	 =   5.57514; // +/- 2.40089e-05 cm/us West: Slope = -1.41505 +/- 0.0043884 DV = 5.57514 +/- 2.40089e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
