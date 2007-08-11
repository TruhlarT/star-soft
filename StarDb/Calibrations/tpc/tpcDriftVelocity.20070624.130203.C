TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 175023
  row.laserDriftVelocityEast	 =   5.56928; // +/- 2.138e-05 cm/us East: Slope = 0.940776 +/- 0.00385176 DV = 5.56928 +/- 2.138e-05
  row.laserDriftVelocityWest	 =   5.57291; // +/- 2.29622e-05 cm/us West: Slope = 0.291075 +/- 0.00413232 DV = 5.57291 +/- 2.29622e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
