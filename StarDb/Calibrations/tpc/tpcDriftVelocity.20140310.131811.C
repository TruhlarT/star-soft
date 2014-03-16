TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 69017
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51672; // +/- 4.6451e-05 cm/us East: Slope = -0.508792 +/- 0.00871464 DV = 5.51672 +/- 4.6451e-05
  row.laserDriftVelocityWest	 =   5.51974; // +/- 3.00037e-05 cm/us West: Slope = -1.09363 +/- 0.00578994 DV = 5.51974 +/- 3.00037e-05
//row.scaleY                  	 = -7.22489e-08;// +/-1.29701e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51885 +/- 2.52033e-05
};
