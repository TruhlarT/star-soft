TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33030
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50555; // +/- 3.8587e-05 cm/us East: Slope = -1.36869 +/- 138.151 DV = 5.50555 +/- 3.8587e-05
  row.laserDriftVelocityWest	 =   5.50531; // +/- 2.56267e-05 cm/us West: Slope = -11.0418 +/- 20.4088 DV = 5.50531 +/- 2.56267e-05
//row.scaleY                  	 = 1.53366e-07;// +/-1.27966e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50539 +/- 2.13477e-05
};
