TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 174057
  row.laserDriftVelocityEast	 =   5.5693; // +/- 3.00699e-05 cm/us East: Slope = 0.937439 +/- 0.00546831 DV = 5.5693 +/- 3.00699e-05
  row.laserDriftVelocityWest	 =   5.57264; // +/- 3.11383e-05 cm/us West: Slope = 0.336766 +/- 0.00562123 DV = 5.57264 +/- 3.11383e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
