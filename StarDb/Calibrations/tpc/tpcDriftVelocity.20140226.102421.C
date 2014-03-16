TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 57010
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51168; // +/- 2.63602e-05 cm/us East: Slope = 0.418441 +/- 0.004795 DV = 5.51168 +/- 2.63602e-05
  row.laserDriftVelocityWest	 =   5.51516; // +/- 3.59255e-05 cm/us West: Slope = -0.303413 +/- 0.00717685 DV = 5.51516 +/- 3.59255e-05
//row.scaleY                  	 = 7.56202e-06;// +/-1.75321e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5129 +/- 2.12528e-05
};
