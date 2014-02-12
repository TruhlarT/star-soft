TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32057
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50312; // +/- 2.15385e-05 cm/us East: Slope = -0.382472 +/- 0.00399451 DV = 5.50312 +/- 2.15385e-05
  row.laserDriftVelocityWest	 =   5.50183; // +/- 2.63817e-05 cm/us West: Slope = -0.220485 +/- 0.00461938 DV = 5.50183 +/- 2.63817e-05
//row.scaleY                  	 = -2.00343e-07;// +/-1.09178e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50261 +/- 1.66843e-05
};
