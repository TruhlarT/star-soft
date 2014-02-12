TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50778; // +/- 4.02923e-05 cm/us East: Slope = 0.734569 +/- 0.00730007 DV = 5.50778 +/- 4.02923e-05
  row.laserDriftVelocityWest	 =   5.51027; // +/- 3.19887e-05 cm/us West: Slope = 0.604737 +/- 0.00778967 DV = 5.51027 +/- 3.19887e-05
//row.scaleY                  	 = -1.34292e-07;// +/-1.45308e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50931 +/- 2.50532e-05
};
