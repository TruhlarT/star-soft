TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37074
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50784; // +/- 3.69742e-05 cm/us East: Slope = 0.176129 +/- 0.00682645 DV = 5.50784 +/- 3.69742e-05
  row.laserDriftVelocityWest	 =   5.50599; // +/- 5.4096e-05 cm/us West: Slope = 0.524754 +/- 0.0100433 DV = 5.50599 +/- 5.4096e-05
//row.scaleY                  	 = 5.07074e-06;// +/-9.70832e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50725 +/- 3.05253e-05
};
