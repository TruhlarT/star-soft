TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 63021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51204; // +/- 2.92709e-05 cm/us East: Slope = 0.339076 +/- 0.00528773 DV = 5.51204 +/- 2.92709e-05
  row.laserDriftVelocityWest	 =   5.51491; // +/- 3.02048e-05 cm/us West: Slope = -0.237432 +/- 0.00593617 DV = 5.51491 +/- 3.02048e-05
//row.scaleY                  	 = 1.46329e-06;// +/-2.00525e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51343 +/- 2.10201e-05
};
