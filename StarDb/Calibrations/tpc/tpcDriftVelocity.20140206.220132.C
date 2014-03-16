TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37058
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50522; // +/- 2.56711e-05 cm/us All: East = 0.214734 +/- 0.00981656
  row.laserDriftVelocityWest	 =   5.50522; // +/- 2.56711e-05 cm/us All: West = -0.00775355 +/- 0.00564245
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50522 +/- 2.56711e-05
  return (TDataSet *)tableSet;// West = 5.50418 +/- 2.92279e-05 East = 5.50872 +/- 5.36952e-05
};
