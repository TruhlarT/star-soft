TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50997; // +/- 3.54066e-05 cm/us East: Slope = 0.233402 +/- 0.00657207 DV = 5.50997 +/- 3.54066e-05
  row.laserDriftVelocityWest	 =   5.50691; // +/- 3.98068e-05 cm/us West: Slope = 0.500797 +/- 0.00651768 DV = 5.50691 +/- 3.98068e-05
//row.scaleY                  	 = -3.33985e-08;// +/-1.43901e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50862 +/- 2.64557e-05
};
