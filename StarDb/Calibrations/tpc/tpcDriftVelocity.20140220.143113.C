TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51026
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50472; // +/- 2.01815e-05 cm/us East: Slope = 0.415525 +/- 0.00360454 DV = 5.50472 +/- 2.01815e-05
  row.laserDriftVelocityWest	 =   5.50693; // +/- 1.78261e-05 cm/us West: Slope = 0.0169462 +/- 0.00323262 DV = 5.50693 +/- 1.78261e-05
//row.scaleY                  	 = 2.05361e-05;// +/-3.61731e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50596 +/- 1.33605e-05
};
