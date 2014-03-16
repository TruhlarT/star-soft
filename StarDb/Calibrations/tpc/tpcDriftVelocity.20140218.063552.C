TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49007
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50211; // +/- 3.14346e-05 cm/us East: Slope = 0.244374 +/- 0.0059356 DV = 5.50211 +/- 3.14346e-05
  row.laserDriftVelocityWest	 =   5.50103; // +/- 2.58794e-05 cm/us West: Slope = 0.40292 +/- 0.00489213 DV = 5.50103 +/- 2.58794e-05
//row.scaleY                  	 = -1.21467e-06;// +/-1.85972e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50147 +/- 1.99796e-05
};
