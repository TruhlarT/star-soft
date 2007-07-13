TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 97076
  row.laserDriftVelocityEast	 =   5.57548; // +/- 1.85379e-05 cm/us All: East = -1.56877 +/- 0.00515591
  row.laserDriftVelocityWest	 =   5.57548; // +/- 1.85379e-05 cm/us All: West = -1.41852 +/- 0.00432318
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57548 +/- 1.85379e-05
  return (TDataSet *)tableSet;// West = 5.57514 +/- 2.41065e-05 East = 5.57597 +/- 2.89995e-05
};
