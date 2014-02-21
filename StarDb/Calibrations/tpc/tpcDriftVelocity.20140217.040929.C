TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47107
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49877; // +/- 4.69314e-05 cm/us East: Slope = 1.39479 +/- 0.00946674 DV = 5.49877 +/- 4.69314e-05
  row.laserDriftVelocityWest	 =   5.49789; // +/- 0.000100205 cm/us West: Slope = 1.54561 +/- 0.040443 DV = 5.49789 +/- 0.000100205
//row.scaleY                  	 = 7.23237e-06;// +/-2.58718e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49861 +/- 4.25009e-05
};
