TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 120070
  row.laserDriftVelocityEast	 =   5.57733; // +/- 1.57398e-05 cm/us East: Slope = -0.498829 +/- 0.00282647 DV = 5.57733 +/- 1.57398e-05
  row.laserDriftVelocityWest	 =   5.57906; // +/- 1.90451e-05 cm/us West: Slope = -0.814258 +/- 0.00340104 DV = 5.57906 +/- 1.90451e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
