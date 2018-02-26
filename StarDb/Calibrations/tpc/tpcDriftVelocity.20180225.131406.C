TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56023
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.53915; // +/- 1.37233e-05 cm/us All: East = 0.193412 +/- 0.00481444
  row.laserDriftVelocityWest	 =   5.53915; // +/- 1.37233e-05 cm/us All: West = 0.656215 +/- 0.00319775
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.53915 +/- 1.37233e-05
  return (TDataSet *)tableSet;// West = 5.53835 +/- 1.67321e-05 East = 5.54079 +/- 2.39873e-05
};
