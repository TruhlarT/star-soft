TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48096
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50255; // +/- 3.5729e-05 cm/us East: Slope = 0.240126 +/- 0.00723702 DV = 5.50255 +/- 3.5729e-05
  row.laserDriftVelocityWest	 =   5.50454; // +/- 2.52609e-05 cm/us West: Slope = -0.12634 +/- 0.00471105 DV = 5.50454 +/- 2.52609e-05
//row.scaleY                  	 = 1.91158e-06;// +/-4.26765e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50388 +/- 2.06263e-05
};
