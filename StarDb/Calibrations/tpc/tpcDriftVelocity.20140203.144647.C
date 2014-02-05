TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34022
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51093; // +/- 2.22878e-05 cm/us East: Slope = -11.7596 +/- 24.4353 DV = 5.51093 +/- 2.22878e-05
  row.laserDriftVelocityWest	 =   5.50884; // +/- 2.52434e-05 cm/us West: Slope = -11.7596 +/- 24.4353 DV = 5.50884 +/- 2.52434e-05
//row.scaleY                  	 = -1.32899e-07;// +/-1.12425e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51001 +/- 1.67076e-05
};
