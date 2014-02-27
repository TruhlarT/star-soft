TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50892; // +/- 4.66343e-05 cm/us East: Slope = -0.778052 +/- 0.00906439 DV = 5.50892 +/- 4.66343e-05
  row.laserDriftVelocityWest	 =   5.50578; // +/- 3.15888e-05 cm/us West: Slope = -0.237185 +/- 0.00638007 DV = 5.50578 +/- 3.15888e-05
//row.scaleY                  	 = -9.88547e-07;// +/-2.87553e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50677 +/- 2.61535e-05
};
