TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49953; // +/- 4.41402e-05 cm/us East: Slope = 0.16542 +/- 0.00729317 DV = 5.49953 +/- 4.41402e-05
  row.laserDriftVelocityWest	 =   5.50201; // +/- 3.11341e-05 cm/us West: Slope = -0.232851 +/- 0.00584018 DV = 5.50201 +/- 3.11341e-05
//row.scaleY                  	 = 1.55369e-06;// +/-1.96442e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50118 +/- 2.5442e-05
};
