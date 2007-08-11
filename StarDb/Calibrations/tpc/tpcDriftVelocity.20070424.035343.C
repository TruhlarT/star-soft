TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 113118
  row.laserDriftVelocityEast	 =   5.57553; // +/- 1.37677e-05 cm/us East: Slope = -0.179987 +/- 0.00246847 DV = 5.57553 +/- 1.37677e-05
  row.laserDriftVelocityWest	 =   5.57733; // +/- 1.35835e-05 cm/us West: Slope = -0.503075 +/- 0.00243205 DV = 5.57733 +/- 1.35835e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
