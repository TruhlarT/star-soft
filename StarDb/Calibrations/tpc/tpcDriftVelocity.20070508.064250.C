TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 128009
  row.laserDriftVelocityEast	 =   5.57377; // +/- -1 cm/us East: Slope = 0.130115 +/- 0.0235878 DV = 5.57382 +/- 0.000125355
  row.laserDriftVelocityWest	 =   5.57618; // +/- 3.80315e-05 cm/us West: Slope = -0.303405 +/- 0.00677904 DV = 5.57618 +/- 3.80315e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
