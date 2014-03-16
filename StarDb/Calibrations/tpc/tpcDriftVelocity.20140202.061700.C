TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33010
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50371; // +/- 1.9388e-05 cm/us East: Slope = 0.151711 +/- 0.00350271 DV = 5.50371 +/- 1.9388e-05
  row.laserDriftVelocityWest	 =   5.48289; // +/- 2.66013e-05 cm/us West: Slope = 0.165088 +/- 0.00458436 DV = 5.48289 +/- 2.66013e-05
//row.scaleY                  	 = -1.7835e-07;// +/-1.01685e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49649 +/- 1.56681e-05
};
