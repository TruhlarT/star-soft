TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 64003
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5097; // +/- 2.69318e-05 cm/us East: Slope = 0.744307 +/- 0.00494394 DV = 5.5097 +/- 2.69318e-05
  row.laserDriftVelocityWest	 =   5.51498; // +/- 3.15085e-05 cm/us West: Slope = -0.250981 +/- 0.00630859 DV = 5.51498 +/- 3.15085e-05
//row.scaleY                  	 = -1.27981e-06;// +/-1.8131e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51193 +/- 2.04724e-05
};
