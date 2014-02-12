TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35003
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51021; // +/- 3.71147e-05 cm/us East: Slope = -6.5708 +/- 55.4326 DV = 5.51021 +/- 3.71147e-05
  row.laserDriftVelocityWest	 =   5.50801; // +/- 2.74969e-05 cm/us West: Slope = -1.77862 +/- 103.019 DV = 5.50801 +/- 2.74969e-05
//row.scaleY                  	 = -1.73712e-07;// +/-1.20266e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50879 +/- 2.2094e-05
};
