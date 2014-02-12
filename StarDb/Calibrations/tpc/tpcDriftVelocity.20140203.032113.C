TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50861; // +/- 2.1368e-05 cm/us East: Slope = -11.3495 +/- 13.2086 DV = 5.50861 +/- 2.1368e-05
  row.laserDriftVelocityWest	 =   5.5066; // +/- 2.27909e-05 cm/us West: Slope = -11.3495 +/- 13.2086 DV = 5.5066 +/- 2.27909e-05
//row.scaleY                  	 = -1.95917e-07;// +/-1.11702e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50767 +/- 1.55882e-05
};
