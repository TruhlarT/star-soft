TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37074
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50778; // +/- 3.54397e-05 cm/us East: Slope = 0.631146 +/- 0.00664465 DV = 5.50778 +/- 3.54397e-05
  row.laserDriftVelocityWest	 =   5.51001; // +/- 5.49882e-05 cm/us West: Slope = 0.138477 +/- 0.0103161 DV = 5.51001 +/- 5.49882e-05
//row.scaleY                  	 = 1.78138e-07;// +/-1.94415e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50844 +/- 2.97889e-05
};
