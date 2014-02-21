TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49092
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50307; // +/- 2.54111e-05 cm/us East: Slope = -0.268788 +/- 0.00467805 DV = 5.50307 +/- 2.54111e-05
  row.laserDriftVelocityWest	 =   5.50307; // +/- 2.54111e-05 cm/us West: Slope = -0.268788 +/- 0.00467805 DV = 5.50307 +/- 2.54111e-05
//row.scaleY                  	 = 6.61611e-06;// +/-6.07745e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50307 +/- 2.54111e-05
};
