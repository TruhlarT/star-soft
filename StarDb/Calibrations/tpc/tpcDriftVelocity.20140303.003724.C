TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 61056
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51104; // +/- 2.68695e-05 cm/us East: Slope = 0.439428 +/- 0.00488885 DV = 5.51104 +/- 2.68695e-05
  row.laserDriftVelocityWest	 =   5.51579; // +/- 3.28184e-05 cm/us West: Slope = -0.421739 +/- 0.00659396 DV = 5.51579 +/- 3.28184e-05
//row.scaleY                  	 = 5.66034e-06;// +/-1.7615e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51295 +/- 2.07903e-05
};
