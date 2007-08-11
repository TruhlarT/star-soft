TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 172054
  row.laserDriftVelocityEast	 =   5.56772; // +/- -1 cm/us East: Slope = 1.24748 +/- 0.00779084 DV = 5.56755 +/- 4.31958e-05
  row.laserDriftVelocityWest	 =   5.57126; // +/- 2.22644e-05 cm/us West: Slope = 0.584207 +/- 0.00398889 DV = 5.57126 +/- 2.22644e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
