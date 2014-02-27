TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39189
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50823; // +/- 0.000112013 cm/us East: Slope = 0.292736 +/- 0.0244226 DV = 5.50823 +/- 0.000112013
  row.laserDriftVelocityWest	 =   5.50635; // +/- 5.32123e-05 cm/us West: Slope = 0.667055 +/- 0.0106712 DV = 5.50635 +/- 5.32123e-05
//row.scaleY                  	 = -1.77864e-06;// +/-2.07076e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50669 +/- 4.80644e-05
};
