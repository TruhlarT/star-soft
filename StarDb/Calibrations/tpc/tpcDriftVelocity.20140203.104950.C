TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50931; // +/- 1.65841e-05 cm/us East: Slope = 0.1889 +/- 0.00299021 DV = 5.50931 +/- 1.65841e-05
  row.laserDriftVelocityWest	 =   5.50875; // +/- 2.07309e-05 cm/us West: Slope = 0.281702 +/- 0.00374269 DV = 5.50875 +/- 2.07309e-05
//row.scaleY                  	 = -1.76801e-07;// +/-8.60149e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50909 +/- 1.29502e-05
};
