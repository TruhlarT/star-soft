TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51115; // +/- 3.30124e-05 cm/us East: Slope = 0.0211904 +/- 0.00602115 DV = 5.51115 +/- 3.30124e-05
  row.laserDriftVelocityWest	 =   5.51193; // +/- 2.97059e-05 cm/us West: Slope = 0.260658 +/- 0.00673646 DV = 5.51193 +/- 2.97059e-05
//row.scaleY                  	 = -1.87528e-07;// +/-1.19539e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51158 +/- 2.2082e-05
};
