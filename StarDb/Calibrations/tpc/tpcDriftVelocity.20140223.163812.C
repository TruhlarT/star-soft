TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54026
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50729; // +/- 2.17222e-05 cm/us East: Slope = 0.553242 +/- 0.0039652 DV = 5.50729 +/- 2.17222e-05
  row.laserDriftVelocityWest	 =   5.51096; // +/- 3.41175e-05 cm/us West: Slope = -0.165307 +/- 0.00655636 DV = 5.51096 +/- 3.41175e-05
//row.scaleY                  	 = 2.71414e-06;// +/-1.63731e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50835 +/- 1.83235e-05
};
