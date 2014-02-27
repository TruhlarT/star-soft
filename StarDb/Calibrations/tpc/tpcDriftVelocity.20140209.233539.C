TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40047
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50689; // +/- 1.29171e-05 cm/us East: Slope = 0.12238 +/- 0.00235181 DV = 5.50689 +/- 1.29171e-05
  row.laserDriftVelocityWest	 =   5.50485; // +/- 1.23557e-05 cm/us West: Slope = 0.486437 +/- 0.00220297 DV = 5.50485 +/- 1.23557e-05
//row.scaleY                  	 = 4.69465e-06;// +/-1.83161e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50582 +/- 8.92867e-06
};
