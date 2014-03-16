TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50807; // +/- 4.01558e-05 cm/us All: East = 0.17134 +/- 0.0125914
  row.laserDriftVelocityWest	 =   5.50807; // +/- 4.01558e-05 cm/us All: West = 0.298553 +/- 0.0125412
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50807 +/- 4.01558e-05
  return (TDataSet *)tableSet;// West = 5.50803 +/- 5.85947e-05 East = 5.5081 +/- 5.51403e-05
};
