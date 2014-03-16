TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 67033
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51606; // +/- 4.21315e-05 cm/us East: Slope = -0.39562 +/- 0.00852566 DV = 5.51606 +/- 4.21315e-05
  row.laserDriftVelocityWest	 =   5.5162; // +/- 2.9697e-05 cm/us West: Slope = -0.445414 +/- 0.00586656 DV = 5.5162 +/- 2.9697e-05
//row.scaleY                  	 = -1.91237e-07;// +/-1.21309e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51615 +/- 2.42731e-05
};
