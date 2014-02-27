TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53048
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5061; // +/- 5.53244e-05 cm/us East: Slope = -0.246702 +/- 0.0103753 DV = 5.5061 +/- 5.53244e-05
  row.laserDriftVelocityWest	 =   5.50287; // +/- 4.06655e-05 cm/us West: Slope = 0.292111 +/- 0.0072897 DV = 5.50287 +/- 4.06655e-05
//row.scaleY                  	 = -1.10608e-06;// +/-3.26568e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50401 +/- 3.27662e-05
};
