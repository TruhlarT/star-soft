TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55134
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51002; // +/- 2.8805e-05 cm/us East: Slope = 0.278818 +/- 0.0050075 DV = 5.51002 +/- 2.8805e-05
  row.laserDriftVelocityWest	 =   5.51246; // +/- 3.49566e-05 cm/us West: Slope = -0.205964 +/- 0.00695111 DV = 5.51246 +/- 3.49566e-05
//row.scaleY                  	 = -1.34559e-06;// +/-1.78423e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.511 +/- 2.22301e-05
};
