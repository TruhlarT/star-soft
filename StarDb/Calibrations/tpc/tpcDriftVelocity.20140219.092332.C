TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5037; // +/- 4.05945e-05 cm/us East: Slope = 0.336386 +/- 0.00738272 DV = 5.5037 +/- 4.05945e-05
  row.laserDriftVelocityWest	 =   5.50298; // +/- 2.99378e-05 cm/us West: Slope = 0.348577 +/- 0.00559759 DV = 5.50298 +/- 2.99378e-05
//row.scaleY                  	 = 1.07353e-05;// +/-1.77037e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50323 +/- 2.40942e-05
};
