TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37011
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51137; // +/- 3.29157e-05 cm/us East: Slope = 0.241129 +/- 0.00586055 DV = 5.51137 +/- 3.29157e-05
  row.laserDriftVelocityWest	 =   5.50918; // +/- 3.55823e-05 cm/us West: Slope = 0.58661 +/- 0.00700227 DV = 5.50918 +/- 3.55823e-05
//row.scaleY                  	 = -1.82166e-07;// +/-1.27645e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51036 +/- 2.41627e-05
};
