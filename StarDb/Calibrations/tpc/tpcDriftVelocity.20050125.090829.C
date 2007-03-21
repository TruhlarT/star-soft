TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6025039
  row.laserDriftVelocityEast	 =   5.55641; // +/- 0.000330953 cm/us All: East = 5.55649 +/- 0.000471164
  row.laserDriftVelocityWest	 =   5.55641; // +/- 0.000330953 cm/us All: West = 5.55633 +/- 0.000464974
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.38214 +/- 0.0626835
  return (TDataSet *)tableSet;// West = 1.40543 +/- 0.0909594 East = 1.36107 +/- 0.0865041
};
