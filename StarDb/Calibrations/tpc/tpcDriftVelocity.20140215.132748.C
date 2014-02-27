TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 46030
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.48212; // +/- 4.18501e-05 cm/us East: Slope = 0.342555 +/- 0.00826609 DV = 5.48212 +/- 4.18501e-05
  row.laserDriftVelocityWest	 =   5.4808; // +/- 2.48737e-05 cm/us West: Slope = 0.457416 +/- 0.00464568 DV = 5.4808 +/- 2.48737e-05
//row.scaleY                  	 = -6.86161e-07;// +/-2.15802e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.48115 +/- 2.13821e-05
};
