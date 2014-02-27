TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48076
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50007; // +/- 3.89337e-05 cm/us East: Slope = 0.568381 +/- 0.00699222 DV = 5.50007 +/- 3.89337e-05
  row.laserDriftVelocityWest	 =   5.50089; // +/- 3.42512e-05 cm/us West: Slope = 0.252267 +/- 0.00629122 DV = 5.50089 +/- 3.42512e-05
//row.scaleY                  	 = 8.82128e-06;// +/-2.07983e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50053 +/- 2.57162e-05
};
