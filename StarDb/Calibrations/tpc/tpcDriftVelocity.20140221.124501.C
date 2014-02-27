TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52020
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50341; // +/- 2.79172e-05 cm/us East: Slope = 0.232465 +/- 0.00518621 DV = 5.50341 +/- 2.79172e-05
  row.laserDriftVelocityWest	 =   5.49819; // +/- 3.59109e-05 cm/us West: Slope = 1.12367 +/- 0.0067784 DV = 5.49819 +/- 3.59109e-05
//row.scaleY                  	 = -1.11278e-06;// +/-1.85897e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50144 +/- 2.20405e-05
};
