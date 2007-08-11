TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139006
  row.laserDriftVelocityEast	 =   5.57205; // +/- 1.33385e-05 cm/us East: Slope = 0.442724 +/- 0.00239333 DV = 5.57205 +/- 1.33385e-05
  row.laserDriftVelocityWest	 =   5.57475; // +/- 2.11903e-05 cm/us West: Slope = -0.0407818 +/- 0.00380836 DV = 5.57475 +/- 2.11903e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
