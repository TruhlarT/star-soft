TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 46034
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.48412; // +/- 3.54064e-05 cm/us East: Slope = 4.0331 +/- 0.00658726 DV = 5.48412 +/- 3.54064e-05
  row.laserDriftVelocityWest	 =   5.48395; // +/- 2.12929e-05 cm/us West: Slope = 4.07704 +/- 0.00398903 DV = 5.48395 +/- 2.12929e-05
//row.scaleY                  	 = 6.53569e-06;// +/-2.83004e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.48399 +/- 1.82473e-05
};
