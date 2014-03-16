TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 59060
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51308; // +/- 2.78222e-05 cm/us East: Slope = 0.130732 +/- 0.00506143 DV = 5.51308 +/- 2.78222e-05
  row.laserDriftVelocityWest	 =   5.51579; // +/- 3.37544e-05 cm/us West: Slope = -0.395884 +/- 0.00671761 DV = 5.51579 +/- 3.37544e-05
//row.scaleY                  	 = 4.87176e-06;// +/-1.67908e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51418 +/- 2.14691e-05
};
