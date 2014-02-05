TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31080
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49577; // +/- 5.43349e-05 cm/us East: Slope = 0.989793 +/- 0.0170411 DV = 5.49577 +/- 5.43349e-05
  row.laserDriftVelocityWest	 =   5.48966; // +/- 8.10726e-05 cm/us West: Slope = 2.0632 +/- 0.0360726 DV = 5.48966 +/- 8.10726e-05
//row.scaleY                  	 = -3.90027e-07;// +/-3.02852e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49387 +/- 4.51356e-05
};
