TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51137; // +/- 3.13487e-05 cm/us East: Slope = -0.00857776 +/- 0.00564914 DV = 5.51137 +/- 3.13487e-05
  row.laserDriftVelocityWest	 =   5.50918; // +/- 3.50805e-05 cm/us West: Slope = 0.0991847 +/- 0.0061796 DV = 5.50918 +/- 3.50805e-05
//row.scaleY                  	 = -1.66266e-07;// +/-1.28197e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5104 +/- 2.33753e-05
};
