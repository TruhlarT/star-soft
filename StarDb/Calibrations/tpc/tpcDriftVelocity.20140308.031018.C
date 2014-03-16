TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 66088
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51724; // +/- 2.88123e-05 cm/us East: Slope = -0.608298 +/- 0.00521709 DV = 5.51724 +/- 2.88123e-05
  row.laserDriftVelocityWest	 =   5.5199; // +/- 2.98791e-05 cm/us West: Slope = -1.10624 +/- 0.00575738 DV = 5.5199 +/- 2.98791e-05
//row.scaleY                  	 = -3.6114e-08;// +/-1.23297e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51852 +/- 2.07402e-05
};
