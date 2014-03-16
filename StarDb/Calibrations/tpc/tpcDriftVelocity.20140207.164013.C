TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38033
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5078; // +/- 2.85421e-05 cm/us All: East = 0.271751 +/- 0.00588173
  row.laserDriftVelocityWest	 =   5.5078; // +/- 2.85421e-05 cm/us All: West = -0.737412 +/- 0.0107629
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5078 +/- 2.85421e-05
  return (TDataSet *)tableSet;// West = 5.51099 +/- 5.71242e-05 East = 5.50674 +/- 3.29499e-05
};
