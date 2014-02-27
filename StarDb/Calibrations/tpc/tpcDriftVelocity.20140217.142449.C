TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48025
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5; // +/- 4.82138e-05 cm/us East: Slope = 0.365276 +/- 0.0090428 DV = 5.5 +/- 4.82138e-05
  row.laserDriftVelocityWest	 =   5.50075; // +/- 3.03759e-05 cm/us West: Slope = 0.0873484 +/- 0.00553489 DV = 5.50075 +/- 3.03759e-05
//row.scaleY                  	 = -1.27822e-05;// +/-1.53739e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50053 +/- 2.57005e-05
};
