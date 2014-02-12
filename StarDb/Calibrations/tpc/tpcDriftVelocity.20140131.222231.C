TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50041; // +/- 4.66585e-05 cm/us East: Slope = 0.084364 +/- 0.0130618 DV = 5.50041 +/- 4.66585e-05
  row.laserDriftVelocityWest	 =   5.48531; // +/- 6.51267e-05 cm/us West: Slope = 2.83707 +/- 0.0171098 DV = 5.48531 +/- 6.51267e-05
//row.scaleY                  	 = -1.04419e-06;// +/-2.50701e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49529 +/- 3.79291e-05
};
