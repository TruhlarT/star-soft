TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 58021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51102; // +/- 2.57609e-05 cm/us East: Slope = 0.512702 +/- 0.00480898 DV = 5.51102 +/- 2.57609e-05
  row.laserDriftVelocityWest	 =   5.51533; // +/- 3.10571e-05 cm/us West: Slope = -0.330071 +/- 0.00616162 DV = 5.51533 +/- 3.10571e-05
//row.scaleY                  	 = 12.3022;// +/-1.61651e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51278 +/- 1.98277e-05
};
