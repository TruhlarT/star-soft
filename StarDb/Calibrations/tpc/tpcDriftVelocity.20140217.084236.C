TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48004
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49876; // +/- 3.29737e-05 cm/us East: Slope = 0.356522 +/- 0.0060788 DV = 5.49876 +/- 3.29737e-05
  row.laserDriftVelocityWest	 =   5.49769; // +/- 2.78057e-05 cm/us West: Slope = 0.512762 +/- 0.00546241 DV = 5.49769 +/- 2.78057e-05
//row.scaleY                  	 = -3.39641e-07;// +/-1.58172e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49813 +/- 2.12567e-05
};
