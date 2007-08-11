TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 134018
  row.laserDriftVelocityEast	 =   5.56951; // +/- -1 cm/us East: Slope = 0.48019 +/- 0.00793772 DV = 5.5719 +/- 4.39273e-05
  row.laserDriftVelocityWest	 =   5.57208; // +/- 3.04895e-05 cm/us West: Slope = 0.439481 +/- 0.00545938 DV = 5.57208 +/- 3.04895e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
