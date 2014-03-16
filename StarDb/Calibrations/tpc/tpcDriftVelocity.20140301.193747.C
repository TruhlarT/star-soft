TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60046
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5113; // +/- 2.8735e-05 cm/us East: Slope = 0.490663 +/- 0.00545547 DV = 5.5113 +/- 2.8735e-05
  row.laserDriftVelocityWest	 =   5.51694; // +/- 3.32836e-05 cm/us West: Slope = -0.629527 +/- 0.00657534 DV = 5.51694 +/- 3.32836e-05
//row.scaleY                  	 = 8.75012e-07;// +/-1.7564e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51371 +/- 2.17505e-05
};
