TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49025
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5013; // +/- 2.74026e-05 cm/us East: Slope = 0.256578 +/- 0.00498028 DV = 5.5013 +/- 2.74026e-05
  row.laserDriftVelocityWest	 =   5.5009; // +/- 2.74705e-05 cm/us West: Slope = 0.299331 +/- 0.00526477 DV = 5.5009 +/- 2.74705e-05
//row.scaleY                  	 = -1.44638e-06;// +/-1.69771e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5011 +/- 1.94005e-05
};
