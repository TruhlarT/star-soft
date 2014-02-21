TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50377; // +/- 3.60842e-05 cm/us East: Slope = -0.390451 +/- 0.00658801 DV = 5.50377 +/- 3.60842e-05
  row.laserDriftVelocityWest	 =   5.5026; // +/- 2.39445e-05 cm/us West: Slope = -0.185926 +/- 0.00439116 DV = 5.5026 +/- 2.39445e-05
//row.scaleY                  	 = 9.84667e-06;// +/-4.24691e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50296 +/- 1.99515e-05
};
