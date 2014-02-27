TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5083; // +/- 4.10636e-05 cm/us East: Slope = 0.272377 +/- 0.00766959 DV = 5.5083 +/- 4.10636e-05
  row.laserDriftVelocityWest	 =   5.51006; // +/- 4.63442e-05 cm/us West: Slope = -0.354918 +/- 0.00874748 DV = 5.51006 +/- 4.63442e-05
//row.scaleY                  	 = 4.24075e-07;// +/-4.82388e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50907 +/- 3.07345e-05
};
