TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50779; // +/- 4.59809e-05 cm/us East: Slope = 0.273012 +/- 0.0101347 DV = 5.50779 +/- 4.59809e-05
  row.laserDriftVelocityWest	 =   5.5067; // +/- 3.50767e-05 cm/us West: Slope = 0.377514 +/- 0.00653665 DV = 5.5067 +/- 3.50767e-05
//row.scaleY                  	 = 2.55054e-07;// +/-3.35211e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5071 +/- 2.78883e-05
};
