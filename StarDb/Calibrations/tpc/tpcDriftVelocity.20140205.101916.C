TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51186; // +/- 3.05712e-05 cm/us East: Slope = -0.072343 +/- 0.00549865 DV = 5.51186 +/- 3.05712e-05
  row.laserDriftVelocityWest	 =   5.51207; // +/- 2.95375e-05 cm/us West: Slope = -0.234374 +/- 0.00550734 DV = 5.51207 +/- 2.95375e-05
//row.scaleY                  	 = -1.78516e-07;// +/-1.26787e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51197 +/- 2.12422e-05
};
