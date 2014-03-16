TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39189
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50739; // +/- 4.9434e-05 cm/us All: East = 0.0575007 +/- 0.0281166
  row.laserDriftVelocityWest	 =   5.50739; // +/- 4.9434e-05 cm/us All: West = 0.501894 +/- 0.011186
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50739 +/- 4.9434e-05
  return (TDataSet *)tableSet;// West = 5.5071 +/- 5.39933e-05 East = 5.50885 +/- 0.000122914
};
