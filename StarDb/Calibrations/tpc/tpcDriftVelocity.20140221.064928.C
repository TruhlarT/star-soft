TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52007
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49863; // +/- 3.64982e-05 cm/us East: Slope = 0.566292 +/- 0.00676424 DV = 5.49863 +/- 3.64982e-05
  row.laserDriftVelocityWest	 =   5.50224; // +/- 3.54447e-05 cm/us West: Slope = -0.117865 +/- 0.00678499 DV = 5.50224 +/- 3.54447e-05
//row.scaleY                  	 = 1.32126e-06;// +/-2.11993e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50049 +/- 2.54275e-05
};
