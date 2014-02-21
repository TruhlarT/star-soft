TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 46030
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.48231; // +/- 3.75241e-05 cm/us East: Slope = 4.41326 +/- 0.00735367 DV = 5.48231 +/- 3.75241e-05
  row.laserDriftVelocityWest	 =   5.48312; // +/- 2.01567e-05 cm/us West: Slope = 4.23151 +/- 0.00382094 DV = 5.48312 +/- 2.01567e-05
//row.scaleY                  	 = 6.20052e-06;// +/-2.36438e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.48294 +/- 1.7757e-05
};
