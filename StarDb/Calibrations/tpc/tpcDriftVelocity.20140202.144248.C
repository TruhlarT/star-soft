TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33030
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50559; // +/- 3.92926e-05 cm/us East: Slope = 0.196929 +/- 0.0077814 DV = 5.50559 +/- 3.92926e-05
  row.laserDriftVelocityWest	 =   5.50535; // +/- 2.81756e-05 cm/us West: Slope = 0.0904348 +/- 0.00457818 DV = 5.50535 +/- 2.81756e-05
//row.scaleY                  	 = 1.4997e-07;// +/-1.28013e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50543 +/- 2.28972e-05
};
