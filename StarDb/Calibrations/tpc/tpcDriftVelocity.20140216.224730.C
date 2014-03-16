TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47075
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49682; // +/- 4.41646e-05 cm/us East: Slope = 0.244639 +/- 0.00907579 DV = 5.49682 +/- 4.41646e-05
  row.laserDriftVelocityWest	 =   5.49682; // +/- 4.41646e-05 cm/us West: Slope = 0.244639 +/- 0.00907579 DV = 5.49682 +/- 4.41646e-05
//row.scaleY                  	 = -1.33683e-06;// +/-2.10881e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49682 +/- 4.41646e-05
};
