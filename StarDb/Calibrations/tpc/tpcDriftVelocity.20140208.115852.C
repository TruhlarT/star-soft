TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39118
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50688; // +/- 9.48472e-05 cm/us East: Slope = 0.776903 +/- 0.0220996 DV = 5.50688 +/- 9.48472e-05
  row.laserDriftVelocityWest	 =   5.5058; // +/- 5.18084e-05 cm/us West: Slope = 0.547007 +/- 0.0105799 DV = 5.5058 +/- 5.18084e-05
//row.scaleY                  	 = 2.89894e-07;// +/-1.97982e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50605 +/- 4.54676e-05
};
