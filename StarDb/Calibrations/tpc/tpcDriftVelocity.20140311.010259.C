TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 69045
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51681; // +/- 3.50891e-05 cm/us East: Slope = -0.563249 +/- 0.00632688 DV = 5.51681 +/- 3.50891e-05
  row.laserDriftVelocityWest	 =   5.52002; // +/- 3.00493e-05 cm/us West: Slope = -1.13897 +/- 0.00583694 DV = 5.52002 +/- 3.00493e-05
//row.scaleY                  	 = -1.20776e-07;// +/-1.28935e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51866 +/- 2.28238e-05
};
