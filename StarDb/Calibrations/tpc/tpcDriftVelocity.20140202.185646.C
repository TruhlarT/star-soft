TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33063
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50684; // +/- 3.30273e-05 cm/us East: Slope = -23.1451 +/- 15.5763 DV = 5.50684 +/- 3.30273e-05
  row.laserDriftVelocityWest	 =   5.50493; // +/- 2.35426e-05 cm/us West: Slope = -23.1451 +/- 15.5763 DV = 5.50493 +/- 2.35426e-05
//row.scaleY                  	 = 5.56232e-08;// +/-1.25808e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50557 +/- 1.91707e-05
};
