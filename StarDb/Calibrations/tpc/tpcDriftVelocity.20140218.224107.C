TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5031; // +/- 4.33305e-05 cm/us East: Slope = 0.443149 +/- 0.00822721 DV = 5.5031 +/- 4.33305e-05
  row.laserDriftVelocityWest	 =   5.50295; // +/- 3.13409e-05 cm/us West: Slope = 0.264178 +/- 0.00567072 DV = 5.50295 +/- 3.13409e-05
//row.scaleY                  	 = -1.85701e-05;// +/-1.75078e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.503 +/- 2.53945e-05
};
