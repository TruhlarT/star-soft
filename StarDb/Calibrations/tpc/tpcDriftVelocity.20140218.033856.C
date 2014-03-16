TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48096
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50029; // +/- 3.13099e-05 cm/us East: Slope = 0.685185 +/- 0.00572468 DV = 5.50029 +/- 3.13099e-05
  row.laserDriftVelocityWest	 =   5.49894; // +/- 3.12001e-05 cm/us West: Slope = 0.836937 +/- 0.00602728 DV = 5.49894 +/- 3.12001e-05
//row.scaleY                  	 = -1.20789e-06;// +/-1.78124e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49961 +/- 2.21005e-05
};
