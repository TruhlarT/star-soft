TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49092
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5029; // +/- 2.69862e-05 cm/us East: Slope = 0.207169 +/- 0.00488207 DV = 5.5029 +/- 2.69862e-05
  row.laserDriftVelocityWest	 =   5.5029; // +/- 2.69862e-05 cm/us West: Slope = 0.207169 +/- 0.00488207 DV = 5.5029 +/- 2.69862e-05
//row.scaleY                  	 = 1.54516e-06;// +/-1.52534e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5029 +/- 2.69862e-05
};
