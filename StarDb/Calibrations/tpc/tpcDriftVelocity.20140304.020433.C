TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 62075
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50773; // +/- 3.43882e-05 cm/us East: Slope = 1.09514 +/- 0.00654274 DV = 5.50773 +/- 3.43882e-05
  row.laserDriftVelocityWest	 =   5.5154; // +/- 3.45807e-05 cm/us West: Slope = -0.324681 +/- 0.00678057 DV = 5.5154 +/- 3.45807e-05
//row.scaleY                  	 = 7.60887e-07;// +/-1.8828e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51154 +/- 2.43839e-05
};
