TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 59037
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51298; // +/- 4.22818e-05 cm/us East: Slope = 0.181687 +/- 0.00851353 DV = 5.51298 +/- 4.22818e-05
  row.laserDriftVelocityWest	 =   5.51526; // +/- 3.42777e-05 cm/us West: Slope = -0.277701 +/- 0.00628772 DV = 5.51526 +/- 3.42777e-05
//row.scaleY                  	 = 9.823e-07;// +/-1.67608e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51435 +/- 2.66269e-05
};
