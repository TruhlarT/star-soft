TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50862; // +/- 2.15718e-05 cm/us East: Slope = -11.2403 +/- 13.3327 DV = 5.50862 +/- 2.15718e-05
  row.laserDriftVelocityWest	 =   5.50663; // +/- 2.28911e-05 cm/us West: Slope = -11.2403 +/- 13.3327 DV = 5.50663 +/- 2.28911e-05
//row.scaleY                  	 = -1.971e-07;// +/-1.12758e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50768 +/- 1.56993e-05
};
