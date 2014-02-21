TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49007
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5024; // +/- 2.85994e-05 cm/us East: Slope = -0.129375 +/- 0.0052111 DV = 5.5024 +/- 2.85994e-05
  row.laserDriftVelocityWest	 =   5.50163; // +/- 2.13989e-05 cm/us West: Slope = -0.00934788 +/- 0.00397996 DV = 5.50163 +/- 2.13989e-05
//row.scaleY                  	 = -16689.7;// +/-4.92472e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5019 +/- 1.71337e-05
};
