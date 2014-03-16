TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47024
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49182; // +/- 2.75113e-05 cm/us All: East = 0.326719 +/- 0.0125658
  row.laserDriftVelocityWest	 =   5.49182; // +/- 2.75113e-05 cm/us All: West = 0.185861 +/- 0.00603306
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.49182 +/- 2.75113e-05
  return (TDataSet *)tableSet;// West = 5.49177 +/- 3.09266e-05 East = 5.492 +/- 6.02253e-05
};
