TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56023
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51255; // +/- 4.69765e-05 cm/us East: Slope = -1.44709 +/- 0.010228 DV = 5.51255 +/- 4.69765e-05
  row.laserDriftVelocityWest	 =   5.50933; // +/- 3.42331e-05 cm/us West: Slope = -0.878575 +/- 0.00670708 DV = 5.50933 +/- 3.42331e-05
//row.scaleY                  	 = 1.01391e-05;// +/-2.58716e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51045 +/- 2.76664e-05
};
