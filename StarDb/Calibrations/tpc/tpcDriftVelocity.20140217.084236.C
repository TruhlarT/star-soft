TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48004
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49864; // +/- 3.25417e-05 cm/us East: Slope = 0.2307 +/- 0.00611989 DV = 5.49864 +/- 3.25417e-05
  row.laserDriftVelocityWest	 =   5.49855; // +/- 2.84303e-05 cm/us West: Slope = 0.21413 +/- 0.00552082 DV = 5.49855 +/- 2.84303e-05
//row.scaleY                  	 = -4.63558e-07;// +/-1.13661e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49859 +/- 2.14102e-05
};
