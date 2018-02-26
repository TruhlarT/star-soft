TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56008
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.53623; // +/- 2.528e-05 cm/us All: East = 0.684611 +/- 0.0264674
  row.laserDriftVelocityWest	 =   5.53623; // +/- 2.528e-05 cm/us All: West = 1.09926 +/- 0.00547905
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.53623 +/- 2.528e-05
  return (TDataSet *)tableSet;// West = 5.53594 +/- 2.73598e-05 East = 5.53791 +/- 6.61025e-05
};
