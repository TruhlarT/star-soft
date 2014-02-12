TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39109
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50656; // +/- 0.000170741 cm/us East: Slope = 0.859491 +/- 0.100126 DV = 5.50656 +/- 0.000170741
  row.laserDriftVelocityWest	 =   5.50632; // +/- 5.52017e-05 cm/us West: Slope = 0.531285 +/- 0.0112166 DV = 5.50632 +/- 5.52017e-05
//row.scaleY                  	 = 2.70417e-07;// +/-2.1109e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50634 +/- 5.25248e-05
};
