TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 46034
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.48058; // +/- 3.53197e-05 cm/us East: Slope = 0.789848 +/- 0.00610667 DV = 5.48058 +/- 3.53197e-05
  row.laserDriftVelocityWest	 =   5.48306; // +/- 2.93715e-05 cm/us West: Slope = 0.243582 +/- 0.00571823 DV = 5.48306 +/- 2.93715e-05
//row.scaleY                  	 = -3.10799e-07;// +/-1.17664e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.48205 +/- 2.25832e-05
};
