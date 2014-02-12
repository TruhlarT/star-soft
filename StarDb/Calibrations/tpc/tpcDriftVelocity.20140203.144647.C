TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34022
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51094; // +/- 2.20398e-05 cm/us East: Slope = -11.7596 +/- 24.4353 DV = 5.51094 +/- 2.20398e-05
  row.laserDriftVelocityWest	 =   5.50884; // +/- 2.50172e-05 cm/us West: Slope = -11.7596 +/- 24.4353 DV = 5.50884 +/- 2.50172e-05
//row.scaleY                  	 = -1.32367e-07;// +/-1.11415e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51002 +/- 1.65375e-05
};
