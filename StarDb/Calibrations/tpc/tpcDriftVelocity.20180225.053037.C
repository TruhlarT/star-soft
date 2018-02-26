TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.53472; // +/- 1.64749e-05 cm/us All: East = 1.18468 +/- 0.00470615
  row.laserDriftVelocityWest	 =   5.53472; // +/- 1.64749e-05 cm/us All: West = 1.40325 +/- 0.00428486
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.53472 +/- 1.64749e-05
  return (TDataSet *)tableSet;// West = 5.53413 +/- 2.24699e-05 East = 5.5354 +/- 2.42271e-05
};
