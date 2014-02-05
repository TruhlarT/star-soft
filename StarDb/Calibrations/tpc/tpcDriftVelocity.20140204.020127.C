TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34133
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51105; // +/- 3.39158e-05 cm/us East: Slope = -6.83791 +/- 101.495 DV = 5.51105 +/- 3.39158e-05
  row.laserDriftVelocityWest	 =   5.50801; // +/- 2.75896e-05 cm/us West: Slope = -6.83791 +/- 101.495 DV = 5.50801 +/- 2.75896e-05
//row.scaleY                  	 = -1.91458e-07;// +/-1.22248e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50922 +/- 2.14025e-05
};
