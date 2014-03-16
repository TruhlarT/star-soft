TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48082
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50279; // +/- 4.58072e-05 cm/us East: Slope = 0.278405 +/- 0.00865748 DV = 5.50279 +/- 4.58072e-05
  row.laserDriftVelocityWest	 =   5.50007; // +/- 4.38652e-05 cm/us West: Slope = 0.59358 +/- 0.00941585 DV = 5.50007 +/- 4.38652e-05
//row.scaleY                  	 = -7.34629e-07;// +/-1.56431e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50137 +/- 3.16817e-05
};
