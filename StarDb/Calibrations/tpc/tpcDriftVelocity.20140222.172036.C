TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53029
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50623; // +/- 4.42074e-05 cm/us East: Slope = -0.347572 +/- 0.00876477 DV = 5.50623 +/- 4.42074e-05
  row.laserDriftVelocityWest	 =   5.5023; // +/- 4.80908e-05 cm/us West: Slope = 0.406616 +/- 0.00952325 DV = 5.5023 +/- 4.80908e-05
//row.scaleY                  	 = -1.22454e-06;// +/-2.92121e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50443 +/- 3.25458e-05
};
