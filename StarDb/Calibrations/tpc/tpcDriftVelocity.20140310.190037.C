TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 69031
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51893; // +/- 4.91378e-05 cm/us East: Slope = -0.981672 +/- 0.00904888 DV = 5.51893 +/- 4.91378e-05
  row.laserDriftVelocityWest	 =   5.51946; // +/- 2.91262e-05 cm/us West: Slope = -1.03739 +/- 0.00561779 DV = 5.51946 +/- 2.91262e-05
//row.scaleY                  	 = -8.67012e-08;// +/-1.24711e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51932 +/- 2.50553e-05
};
