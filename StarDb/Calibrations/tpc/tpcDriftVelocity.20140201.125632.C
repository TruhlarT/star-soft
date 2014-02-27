TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50057; // +/- 0.000144418 cm/us East: Slope = -0.00889718 +/- 0.052965 DV = 5.50057 +/- 0.000144418
  row.laserDriftVelocityWest	 =   5.4977; // +/- 3.05341e-05 cm/us West: Slope = 0.65663 +/- 0.00570876 DV = 5.4977 +/- 3.05341e-05
//row.scaleY                  	 = 1.32053e-07;// +/-1.74634e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49783 +/- 2.98737e-05
};
