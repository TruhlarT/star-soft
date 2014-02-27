TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51017; // +/- 2.29432e-05 cm/us East: Slope = 0.155675 +/- 0.00416776 DV = 5.51017 +/- 2.29432e-05
  row.laserDriftVelocityWest	 =   5.50969; // +/- 3.54518e-05 cm/us West: Slope = 0.332182 +/- 0.0067831 DV = 5.50969 +/- 3.54518e-05
//row.scaleY                  	 = 4.51027e-06;// +/-2.05715e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51003 +/- 1.92615e-05
};
