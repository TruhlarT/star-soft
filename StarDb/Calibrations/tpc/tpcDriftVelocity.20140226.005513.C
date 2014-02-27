TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56114
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51199; // +/- 3.27628e-05 cm/us East: Slope = -1.35934 +/- 0.00640959 DV = 5.51199 +/- 3.27628e-05
  row.laserDriftVelocityWest	 =   5.50954; // +/- 3.42809e-05 cm/us West: Slope = -0.936851 +/- 0.0068025 DV = 5.50954 +/- 3.42809e-05
//row.scaleY                  	 = 6.28505e-07;// +/-2.75242e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51082 +/- 2.36853e-05
};
