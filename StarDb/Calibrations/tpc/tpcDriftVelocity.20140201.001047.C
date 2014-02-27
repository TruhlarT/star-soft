TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31081
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49534; // +/- 2.31432e-05 cm/us East: Slope = 0.199239 +/- 0.00423248 DV = 5.49534 +/- 2.31432e-05
  row.laserDriftVelocityWest	 =   5.495; // +/- 3.401e-05 cm/us West: Slope = 0.250669 +/- 0.0066661 DV = 5.495 +/- 3.401e-05
//row.scaleY                  	 = -4.15465e-07;// +/-1.35922e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49523 +/- 1.91334e-05
};
