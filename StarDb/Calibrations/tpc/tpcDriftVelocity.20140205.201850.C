TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5099; // +/- 3.53798e-05 cm/us East: Slope = 0.239967 +/- 0.00659828 DV = 5.5099 +/- 3.53798e-05
  row.laserDriftVelocityWest	 =   5.50765; // +/- 3.85488e-05 cm/us West: Slope = 0.360002 +/- 0.00619426 DV = 5.50765 +/- 3.85488e-05
//row.scaleY                  	 = -3.37724e-08;// +/-1.44025e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50887 +/- 2.60657e-05
};
