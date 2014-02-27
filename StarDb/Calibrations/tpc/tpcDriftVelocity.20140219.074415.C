TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50151; // +/- 6.41045e-05 cm/us East: Slope = 0.19907 +/- 0.008484 DV = 5.50151 +/- 6.41045e-05
  row.laserDriftVelocityWest	 =   5.50146; // +/- 2.87585e-05 cm/us West: Slope = 0.226753 +/- 0.00530516 DV = 5.50146 +/- 2.87585e-05
//row.scaleY                  	 = -3.90144e-07;// +/-4.17759e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50147 +/- 2.6239e-05
};
