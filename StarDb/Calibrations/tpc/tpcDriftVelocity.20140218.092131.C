TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50248; // +/- 4.62341e-05 cm/us East: Slope = 0.183567 +/- 0.00867136 DV = 5.50248 +/- 4.62341e-05
  row.laserDriftVelocityWest	 =   5.50195; // +/- 2.6058e-05 cm/us West: Slope = 0.170219 +/- 0.00491471 DV = 5.50195 +/- 2.6058e-05
//row.scaleY                  	 = -2.06698e-06;// +/-3.67331e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50208 +/- 2.27007e-05
};
