TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40049
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50529; // +/- 1.34448e-05 cm/us East: Slope = 1.08473 +/- 0.00243558 DV = 5.50529 +/- 1.34448e-05
  row.laserDriftVelocityWest	 =   5.504; // +/- 2.05467e-05 cm/us West: Slope = 1.35011 +/- 0.00369753 DV = 5.504 +/- 2.05467e-05
//row.scaleY                  	 = -4.08529e-07;// +/-5.82156e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5049 +/- 1.12503e-05
};
