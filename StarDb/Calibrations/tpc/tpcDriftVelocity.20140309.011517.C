TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 67043
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5161; // +/- 3.77849e-05 cm/us East: Slope = -0.440307 +/- 0.00742825 DV = 5.5161 +/- 3.77849e-05
  row.laserDriftVelocityWest	 =   5.51698; // +/- 2.88624e-05 cm/us West: Slope = -0.584178 +/- 0.00551336 DV = 5.51698 +/- 2.88624e-05
//row.scaleY                  	 = -3.03528e-07;// +/-1.20615e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51666 +/- 2.29364e-05
};
