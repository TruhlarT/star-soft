TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47107
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49822; // +/- 4.39636e-05 cm/us All: East = 0.341378 +/- 0.0116777
  row.laserDriftVelocityWest	 =   5.49822; // +/- 4.39636e-05 cm/us All: West = 0.410383 +/- 0.0206828
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.49822 +/- 4.39636e-05
  return (TDataSet *)tableSet;// West = 5.4976 +/- 8.19069e-05 East = 5.49847 +/- 5.21055e-05
};
