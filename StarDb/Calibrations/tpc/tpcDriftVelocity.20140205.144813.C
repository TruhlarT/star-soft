TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 36021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50779; // +/- 3.96644e-05 cm/us East: Slope = 0.235321 +/- 0.00724695 DV = 5.50779 +/- 3.96644e-05
  row.laserDriftVelocityWest	 =   5.50563; // +/- 3.22596e-05 cm/us West: Slope = 0.552921 +/- 0.00615564 DV = 5.50563 +/- 3.22596e-05
//row.scaleY                  	 = -1.63077e-07;// +/-1.48411e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50649 +/- 2.50271e-05
};
