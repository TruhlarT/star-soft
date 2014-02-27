TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48088
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50226; // +/- 3.47947e-05 cm/us East: Slope = 0.22046 +/- 0.00661415 DV = 5.50226 +/- 3.47947e-05
  row.laserDriftVelocityWest	 =   5.50223; // +/- 2.88221e-05 cm/us West: Slope = 0.208502 +/- 0.00540877 DV = 5.50223 +/- 2.88221e-05
//row.scaleY                  	 = -9.93509e-07;// +/-4.69235e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50224 +/- 2.21961e-05
};
