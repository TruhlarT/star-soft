TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50807; // +/- 5.40708e-05 cm/us East: Slope = 0.186673 +/- 0.0121507 DV = 5.50807 +/- 5.40708e-05
  row.laserDriftVelocityWest	 =   5.5058; // +/- 5.49695e-05 cm/us West: Slope = 0.694717 +/- 0.0116055 DV = 5.5058 +/- 5.49695e-05
//row.scaleY                  	 = -5.43021e-07;// +/-1.7891e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50695 +/- 3.85476e-05
};
