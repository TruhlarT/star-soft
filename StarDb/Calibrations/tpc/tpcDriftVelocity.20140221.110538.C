TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52017
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50198; // +/- 3.73689e-05 cm/us East: Slope = 0.469122 +/- 0.00770945 DV = 5.50198 +/- 3.73689e-05
  row.laserDriftVelocityWest	 =   5.49826; // +/- 3.41758e-05 cm/us West: Slope = 1.13765 +/- 0.00660698 DV = 5.49826 +/- 3.41758e-05
//row.scaleY                  	 = 3.41321e-06;// +/-5.14534e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49995 +/- 2.52194e-05
};
