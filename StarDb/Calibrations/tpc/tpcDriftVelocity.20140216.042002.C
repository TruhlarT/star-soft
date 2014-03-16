TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 46109
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.48635; // +/- 4.9255e-05 cm/us East: Slope = 0.614076 +/- 0.00923793 DV = 5.48635 +/- 4.9255e-05
  row.laserDriftVelocityWest	 =   5.48804; // +/- 3.13111e-05 cm/us West: Slope = 0.202675 +/- 0.00595015 DV = 5.48804 +/- 3.13111e-05
//row.scaleY                  	 = -2.6183e-07;// +/-1.28403e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.48756 +/- 2.6424e-05
};
