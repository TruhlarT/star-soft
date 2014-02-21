TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50194
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5037; // +/- 1.97478e-05 cm/us East: Slope = -0.376382 +/- 0.00356679 DV = 5.5037 +/- 1.97478e-05
  row.laserDriftVelocityWest	 =   5.50189; // +/- 1.57227e-05 cm/us West: Slope = -0.0571795 +/- 0.0028382 DV = 5.50189 +/- 1.57227e-05
//row.scaleY                  	 = 1.37613e-05;// +/-2.19372e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50259 +/- 1.23003e-05
};
