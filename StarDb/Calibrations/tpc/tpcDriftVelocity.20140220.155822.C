TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51088
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50444; // +/- 1.22901e-05 cm/us East: Slope = 0.466183 +/- 0.00219696 DV = 5.50444 +/- 1.22901e-05
  row.laserDriftVelocityWest	 =   5.50652; // +/- 9.50468e-06 cm/us West: Slope = 0.0876491 +/- 0.00170985 DV = 5.50652 +/- 9.50468e-06
//row.scaleY                  	 = 1.52173e-05;// +/-3.13763e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50574 +/- 7.5186e-06
};
