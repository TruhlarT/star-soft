TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56125
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5126; // +/- 3.1754e-05 cm/us East: Slope = -1.42483 +/- 0.00587968 DV = 5.5126 +/- 3.1754e-05
  row.laserDriftVelocityWest	 =   5.50923; // +/- 3.03835e-05 cm/us West: Slope = -0.8707 +/- 0.0057532 DV = 5.50923 +/- 3.03835e-05
//row.scaleY                  	 = 4.6339e-06;// +/-1.91688e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51084 +/- 2.19529e-05
};
