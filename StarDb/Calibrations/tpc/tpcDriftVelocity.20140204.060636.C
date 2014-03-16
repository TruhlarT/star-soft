TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 35003
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51033; // +/- 3.68437e-05 cm/us East: Slope = 0.163911 +/- 0.0073748 DV = 5.51033 +/- 3.68437e-05
  row.laserDriftVelocityWest	 =   5.50696; // +/- 3.12545e-05 cm/us West: Slope = 0.550051 +/- 0.00527649 DV = 5.50696 +/- 3.12545e-05
//row.scaleY                  	 = -1.84368e-07;// +/-1.21273e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50837 +/- 2.3834e-05
};
