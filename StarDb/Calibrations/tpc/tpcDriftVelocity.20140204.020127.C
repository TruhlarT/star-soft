TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34133
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51106; // +/- 3.34568e-05 cm/us East: Slope = -6.83791 +/- 101.495 DV = 5.51106 +/- 3.34568e-05
  row.laserDriftVelocityWest	 =   5.50803; // +/- 2.72549e-05 cm/us West: Slope = -6.83791 +/- 101.495 DV = 5.50803 +/- 2.72549e-05
//row.scaleY                  	 = -1.92099e-07;// +/-1.2109e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50924 +/- 2.11309e-05
};
