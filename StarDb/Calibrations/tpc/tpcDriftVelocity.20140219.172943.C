TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50194
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5031; // +/- 1.53963e-05 cm/us East: Slope = 0.303819 +/- 0.00280629 DV = 5.5031 +/- 1.53963e-05
  row.laserDriftVelocityWest	 =   5.50359; // +/- 1.56024e-05 cm/us West: Slope = 0.206787 +/- 0.00280546 DV = 5.50359 +/- 1.56024e-05
//row.scaleY                  	 = 1.80938e-07;// +/-2.30745e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50334 +/- 1.0959e-05
};
