TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56009
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51258; // +/- 3.70994e-05 cm/us East: Slope = 0.35586 +/- 0.00760305 DV = 5.51258 +/- 3.70994e-05
  row.laserDriftVelocityWest	 =   5.51557; // +/- 3.24464e-05 cm/us West: Slope = -0.165699 +/- 0.00565861 DV = 5.51557 +/- 3.24464e-05
//row.scaleY                  	 = 5.64133e-06;// +/-1.73282e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51427 +/- 2.44235e-05
};
