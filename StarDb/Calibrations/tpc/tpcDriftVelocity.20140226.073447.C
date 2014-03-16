TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 57003
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51018; // +/- 2.67285e-05 cm/us East: Slope = 0.660393 +/- 0.00489259 DV = 5.51018 +/- 2.67285e-05
  row.laserDriftVelocityWest	 =   5.51533; // +/- 3.45912e-05 cm/us West: Slope = -0.32775 +/- 0.006959 DV = 5.51533 +/- 3.45912e-05
//row.scaleY                  	 = 1.89832e-06;// +/-1.93077e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51211 +/- 2.11502e-05
};
