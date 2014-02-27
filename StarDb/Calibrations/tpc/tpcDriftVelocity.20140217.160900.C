TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48031
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50061; // +/- 3.8811e-05 cm/us East: Slope = 0.322824 +/- 0.00758138 DV = 5.50061 +/- 3.8811e-05
  row.laserDriftVelocityWest	 =   5.50082; // +/- 3.11251e-05 cm/us West: Slope = 0.203015 +/- 0.00581172 DV = 5.50082 +/- 3.11251e-05
//row.scaleY                  	 = -4.59353e-07;// +/-1.64457e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50074 +/- 2.42813e-05
};
