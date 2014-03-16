TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 65061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51849; // +/- 4.96139e-05 cm/us East: Slope = -0.834882 +/- 0.0100013 DV = 5.51849 +/- 4.96139e-05
  row.laserDriftVelocityWest	 =   5.51958; // +/- 3.29727e-05 cm/us West: Slope = -1.12968 +/- 0.00644672 DV = 5.51958 +/- 3.29727e-05
//row.scaleY                  	 = -2.53223e-07;// +/-1.33745e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51924 +/- 2.74613e-05
};
