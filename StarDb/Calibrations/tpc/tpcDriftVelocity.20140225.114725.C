TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56017
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51044; // +/- 3.76763e-05 cm/us East: Slope = 0.312702 +/- 0.0067958 DV = 5.51044 +/- 3.76763e-05
  row.laserDriftVelocityWest	 =   5.51296; // +/- 3.32198e-05 cm/us West: Slope = -0.185853 +/- 0.00601214 DV = 5.51296 +/- 3.32198e-05
//row.scaleY                  	 = 2.266e-06;// +/-2.02649e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51186 +/- 2.49173e-05
};
