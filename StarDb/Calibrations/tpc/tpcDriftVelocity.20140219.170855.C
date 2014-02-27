TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50192
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50337; // +/- 2.3e-05 cm/us East: Slope = 0.279389 +/- 0.00513174 DV = 5.50337 +/- 2.3e-05
  row.laserDriftVelocityWest	 =   5.50177; // +/- 3.13229e-05 cm/us West: Slope = 0.55177 +/- 0.00582194 DV = 5.50177 +/- 3.13229e-05
//row.scaleY                  	 = 3.121e-05;// +/-5.14885e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50281 +/- 1.85389e-05
};
