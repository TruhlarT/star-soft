TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31081
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49534; // +/- 2.31979e-05 cm/us East: Slope = 0.192877 +/- 0.00430434 DV = 5.49534 +/- 2.31979e-05
  row.laserDriftVelocityWest	 =   5.48958; // +/- 3.38025e-05 cm/us West: Slope = 1.22755 +/- 0.00664182 DV = 5.48958 +/- 3.38025e-05
//row.scaleY                  	 = -4.13486e-07;// +/-1.36006e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.4935 +/- 1.91269e-05
};
