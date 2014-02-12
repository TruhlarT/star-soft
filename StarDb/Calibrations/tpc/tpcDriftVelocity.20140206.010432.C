TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50994; // +/- 3.32268e-05 cm/us East: Slope = 0.245304 +/- 0.00596235 DV = 5.50994 +/- 3.32268e-05
  row.laserDriftVelocityWest	 =   5.50818; // +/- 3.42788e-05 cm/us West: Slope = 0.279734 +/- 0.00553186 DV = 5.50818 +/- 3.42788e-05
//row.scaleY                  	 = -1.32695e-07;// +/-1.25068e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50909 +/- 2.38581e-05
};
