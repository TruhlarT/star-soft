TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54031
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50941; // +/- 6.93041e-05 cm/us East: Slope = -0.81045 +/- 0.0145572 DV = 5.50941 +/- 6.93041e-05
  row.laserDriftVelocityWest	 =   5.50607; // +/- 3.93559e-05 cm/us West: Slope = -0.285063 +/- 0.00768744 DV = 5.50607 +/- 3.93559e-05
//row.scaleY                  	 = -2.07483e-06;// +/-4.42233e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50689 +/- 3.42228e-05
};
