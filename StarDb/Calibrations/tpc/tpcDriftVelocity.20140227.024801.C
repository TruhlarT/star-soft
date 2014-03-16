TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 57057
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51233; // +/- 2.43097e-05 cm/us East: Slope = 0.282349 +/- 0.00436701 DV = 5.51233 +/- 2.43097e-05
  row.laserDriftVelocityWest	 =   5.5156; // +/- 3.30621e-05 cm/us West: Slope = -0.367391 +/- 0.0064082 DV = 5.5156 +/- 3.30621e-05
//row.scaleY                  	 = 4.2872e-06;// +/-1.72329e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51348 +/- 1.95854e-05
};
