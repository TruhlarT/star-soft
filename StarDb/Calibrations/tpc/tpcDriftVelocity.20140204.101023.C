TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51; // +/- 2.3489e-05 cm/us East: Slope = 0.151364 +/- 0.00389308 DV = 5.51 +/- 2.3489e-05
  row.laserDriftVelocityWest	 =   5.50946; // +/- 2.51745e-05 cm/us West: Slope = 0.330353 +/- 0.00474033 DV = 5.50946 +/- 2.51745e-05
//row.scaleY                  	 = 8.71484e-06;// +/-2.07806e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50975 +/- 1.71742e-05
};
