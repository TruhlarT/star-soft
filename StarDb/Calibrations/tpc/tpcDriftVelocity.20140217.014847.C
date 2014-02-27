TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47098
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49709; // +/- 5.09873e-05 cm/us East: Slope = 0.469839 +/- 0.011312 DV = 5.49709 +/- 5.09873e-05
  row.laserDriftVelocityWest	 =   5.49579; // +/- 0.000110685 cm/us West: Slope = 0.798628 +/- 0.0452365 DV = 5.49579 +/- 0.000110685
//row.scaleY                  	 = -1.05467e-07;// +/-2.73912e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49686 +/- 4.631e-05
};
