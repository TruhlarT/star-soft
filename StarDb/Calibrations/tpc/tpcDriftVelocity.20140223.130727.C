TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54018
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.89859; // +/- 0.000125751 cm/us East: Slope = 5.89859 +/- 0.000125751 DV = 5.89859 +/- 0.000125751
  row.laserDriftVelocityWest	 =   5.89767; // +/- 8.76809e-05 cm/us West: Slope = 5.89859 +/- 0.000125751 DV = 5.89767 +/- 8.76809e-05
//row.scaleY                  	 = 1.10011e-06;// +/-8.77447e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.89797 +/- 7.19236e-05
};
