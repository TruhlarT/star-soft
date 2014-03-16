TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 69005
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51583; // +/- 3.38103e-05 cm/us East: Slope = -0.378418 +/- 0.00630885 DV = 5.51583 +/- 3.38103e-05
  row.laserDriftVelocityWest	 =   5.51914; // +/- 2.89644e-05 cm/us West: Slope = -0.980775 +/- 0.00559923 DV = 5.51914 +/- 2.89644e-05
//row.scaleY                  	 = -1.23807e-07;// +/-1.21787e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51774 +/- 2.19965e-05
};
