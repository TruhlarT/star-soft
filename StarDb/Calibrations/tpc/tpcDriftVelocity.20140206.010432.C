TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50991; // +/- 3.33223e-05 cm/us East: Slope = 0.192147 +/- 0.00592949 DV = 5.50991 +/- 3.33223e-05
  row.laserDriftVelocityWest	 =   5.50782; // +/- 3.43858e-05 cm/us West: Slope = 0.311024 +/- 0.00559252 DV = 5.50782 +/- 3.43858e-05
//row.scaleY                  	 = -1.30911e-07;// +/-1.24991e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50889 +/- 2.39295e-05
};
