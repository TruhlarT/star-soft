TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37001
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50975; // +/- 3.73074e-05 cm/us East: Slope = 0.245056 +/- 0.00666691 DV = 5.50975 +/- 3.73074e-05
  row.laserDriftVelocityWest	 =   5.50809; // +/- 3.17886e-05 cm/us West: Slope = 0.517772 +/- 0.00610647 DV = 5.50809 +/- 3.17886e-05
//row.scaleY                  	 = -1.41374e-07;// +/-1.20274e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50879 +/- 2.41962e-05
};
