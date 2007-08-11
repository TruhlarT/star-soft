TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 85175
  row.laserDriftVelocityEast	 =   5.56816; // +/- 2.54505e-05 cm/us East: Slope = -0.170222 +/- 0.00458188 DV = 5.56816 +/- 2.54505e-05
  row.laserDriftVelocityWest	 =   5.56949; // +/- -1 cm/us West: Slope = -0.678865 +/- 0.00782205 DV = 5.57102 +/- 4.33132e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
