TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32057
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50313; // +/- 2.17523e-05 cm/us East: Slope = -0.383751 +/- 0.00403367 DV = 5.50313 +/- 2.17523e-05
  row.laserDriftVelocityWest	 =   5.50183; // +/- 2.65837e-05 cm/us West: Slope = -0.153607 +/- 0.0049849 DV = 5.50183 +/- 2.65837e-05
//row.scaleY                  	 = -1.99877e-07;// +/-1.10267e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50261 +/- 1.68347e-05
};
