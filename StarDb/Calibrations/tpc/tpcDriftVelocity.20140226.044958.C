TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56125
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51232; // +/- 3.07421e-05 cm/us East: Slope = 0.268199 +/- 0.00563908 DV = 5.51232 +/- 3.07421e-05
  row.laserDriftVelocityWest	 =   5.51457; // +/- 3.12149e-05 cm/us West: Slope = -0.200682 +/- 0.00592984 DV = 5.51457 +/- 3.12149e-05
//row.scaleY                  	 = 5.54638e-06;// +/-1.70385e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51343 +/- 2.19032e-05
};
