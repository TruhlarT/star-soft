TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34022
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51096; // +/- 2.18758e-05 cm/us East: Slope = 0.185674 +/- 0.00397283 DV = 5.51096 +/- 2.18758e-05
  row.laserDriftVelocityWest	 =   5.51036; // +/- 2.86662e-05 cm/us West: Slope = 0.282021 +/- 0.00519244 DV = 5.51036 +/- 2.86662e-05
//row.scaleY                  	 = -1.56098e-07;// +/-1.15092e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51074 +/- 1.73905e-05
};
