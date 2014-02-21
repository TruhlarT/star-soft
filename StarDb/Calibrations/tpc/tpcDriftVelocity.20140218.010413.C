TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48088
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50233; // +/- 3.21274e-05 cm/us East: Slope = -0.123498 +/- 0.00616998 DV = 5.50233 +/- 3.21274e-05
  row.laserDriftVelocityWest	 =   5.50125; // +/- 2.7094e-05 cm/us West: Slope = 0.0592573 +/- 0.00511006 DV = 5.50125 +/- 2.7094e-05
//row.scaleY                  	 = 1.01893e-05;// +/-5.42202e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5017 +/- 2.0712e-05
};
