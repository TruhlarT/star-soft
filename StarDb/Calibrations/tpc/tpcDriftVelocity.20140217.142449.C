TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48025
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5001; // +/- 4.96804e-05 cm/us East: Slope = 0.598481 +/- 0.00691734 DV = 5.5001 +/- 4.96804e-05
  row.laserDriftVelocityWest	 =   5.49873; // +/- 3.05902e-05 cm/us West: Slope = 0.366772 +/- 0.00557994 DV = 5.49873 +/- 3.05902e-05
//row.scaleY                  	 = -4.7377e-07;// +/-1.22538e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49911 +/- 2.60483e-05
};
