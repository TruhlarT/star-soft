TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50926; // +/- 1.68329e-05 cm/us East: Slope = -15.1807 +/- 30.1605 DV = 5.50926 +/- 1.68329e-05
  row.laserDriftVelocityWest	 =   5.50798; // +/- 1.87041e-05 cm/us West: Slope = -15.1807 +/- 30.1605 DV = 5.50798 +/- 1.87041e-05
//row.scaleY                  	 = -1.57763e-07;// +/-8.48825e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50869 +/- 1.25121e-05
};
