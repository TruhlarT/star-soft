TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 68018
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51779; // +/- 3.41079e-05 cm/us East: Slope = -0.721535 +/- 0.00658916 DV = 5.51779 +/- 3.41079e-05
  row.laserDriftVelocityWest	 =   5.51779; // +/- 3.41079e-05 cm/us West: Slope = -0.721535 +/- 0.00658916 DV = 5.51779 +/- 3.41079e-05
//row.scaleY                  	 = 6.5712e-07;// +/-2.12436e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51779 +/- 3.41079e-05
};
