TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 159068
  row.laserDriftVelocityEast	 =   5.57177; // +/- 2.09983e-05 cm/us East: Slope = 0.497643 +/- 0.00375357 DV = 5.57177 +/- 2.09983e-05
  row.laserDriftVelocityWest	 =   5.57425; // +/- 1.49344e-05 cm/us West: Slope = 0.051071 +/- 0.00267873 DV = 5.57425 +/- 1.49344e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
