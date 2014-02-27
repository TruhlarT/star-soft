TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38014
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5078; // +/- 5.00045e-05 cm/us East: Slope = 0.15668 +/- 0.00927493 DV = 5.5078 +/- 5.00045e-05
  row.laserDriftVelocityWest	 =   5.5078; // +/- 5.00045e-05 cm/us West: Slope = 0.15668 +/- 0.00927493 DV = 5.5078 +/- 5.00045e-05
//row.scaleY                  	 = 1.02371e-05;// +/-1.02709e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5078 +/- 5.00045e-05
};
