TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56038
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51259; // +/- 4.05293e-05 cm/us East: Slope = -1.42681 +/- 0.00849981 DV = 5.51259 +/- 4.05293e-05
  row.laserDriftVelocityWest	 =   5.50935; // +/- 3.29831e-05 cm/us West: Slope = -0.875071 +/- 0.00592827 DV = 5.50935 +/- 3.29831e-05
//row.scaleY                  	 = -1.08865e-06;// +/-1.96635e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51064 +/- 2.55823e-05
};
