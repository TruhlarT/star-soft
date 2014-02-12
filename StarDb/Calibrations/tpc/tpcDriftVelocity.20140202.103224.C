TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33019
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50478; // +/- 1.93994e-05 cm/us East: Slope = -0.674951 +/- 0.00344819 DV = 5.50478 +/- 1.93994e-05
  row.laserDriftVelocityWest	 =   5.50383; // +/- 2.11792e-05 cm/us West: Slope = -0.520342 +/- 0.00374265 DV = 5.50383 +/- 2.11792e-05
//row.scaleY                  	 = -1.6655e-07;// +/-1.01913e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50435 +/- 1.43054e-05
};
