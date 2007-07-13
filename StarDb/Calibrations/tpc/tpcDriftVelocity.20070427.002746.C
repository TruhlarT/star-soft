TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 116093
  row.laserDriftVelocityEast	 =   5.57694; // +/- 2.00821e-05 cm/us All: East = -0.424772 +/- 0.00465128
  row.laserDriftVelocityWest	 =   5.57694; // +/- 2.00821e-05 cm/us All: West = -0.43966 +/- 0.00571521
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57694 +/- 2.00821e-05
  return (TDataSet *)tableSet;// West = 5.57701 +/- 3.16756e-05 East = 5.5769 +/- 2.5968e-05
};
