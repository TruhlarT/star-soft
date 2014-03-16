TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51142; // +/- 3.18073e-05 cm/us East: Slope = 0.205842 +/- 0.00572863 DV = 5.51142 +/- 3.18073e-05
  row.laserDriftVelocityWest	 =   5.50918; // +/- 3.55038e-05 cm/us West: Slope = 0.592409 +/- 0.00699291 DV = 5.50918 +/- 3.55038e-05
//row.scaleY                  	 = -1.65946e-07;// +/-1.28006e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51042 +/- 2.36906e-05
};
