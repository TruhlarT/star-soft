TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 52065
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5013; // +/- 5.25803e-05 cm/us East: Slope = 0.58909 +/- 0.0103467 DV = 5.5013 +/- 5.25803e-05
  row.laserDriftVelocityWest	 =   5.49901; // +/- 4.46799e-05 cm/us West: Slope = 0.982299 +/- 0.00902341 DV = 5.49901 +/- 4.46799e-05
//row.scaleY                  	 = 0.00012785;// +/-5.85942e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49997 +/- 3.40476e-05
};
