TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33084
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50866; // +/- 2.13641e-05 cm/us East: Slope = 0.198074 +/- 0.00387301 DV = 5.50866 +/- 2.13641e-05
  row.laserDriftVelocityWest	 =   5.50673; // +/- 2.65997e-05 cm/us West: Slope = 0.551209 +/- 0.00485092 DV = 5.50673 +/- 2.65997e-05
//row.scaleY                  	 = -2.01533e-07;// +/-1.12914e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5079 +/- 1.66568e-05
};
