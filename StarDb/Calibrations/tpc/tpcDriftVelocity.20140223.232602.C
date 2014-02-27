TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54043
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.75052; // +/- 5.33401e-05 cm/us East: Slope = -8.72993 +/- 5.44488 DV = 5.75052 +/- 5.33401e-05
  row.laserDriftVelocityWest	 =   5.74802; // +/- 3.9629e-05 cm/us West: Slope = -8.72993 +/- 5.44488 DV = 5.74802 +/- 3.9629e-05
//row.scaleY                  	 = 3.23341e-05;// +/-5.3359e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.74891 +/- 3.18105e-05
};
