TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33019
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50484; // +/- 1.94449e-05 cm/us East: Slope = 0.185912 +/- 0.00346789 DV = 5.50484 +/- 1.94449e-05
  row.laserDriftVelocityWest	 =   5.5039; // +/- 2.58341e-05 cm/us West: Slope = 0.350682 +/- 0.0045961 DV = 5.5039 +/- 2.58341e-05
//row.scaleY                  	 = -1.69682e-07;// +/-1.01822e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5045 +/- 1.55359e-05
};
