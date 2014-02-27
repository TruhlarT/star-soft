TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 46109
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.48824; // +/- 6.01192e-05 cm/us East: Slope = 0.66404 +/- 0.012511 DV = 5.48824 +/- 6.01192e-05
  row.laserDriftVelocityWest	 =   5.48925; // +/- 2.92148e-05 cm/us West: Slope = 0.399485 +/- 0.00542316 DV = 5.48925 +/- 2.92148e-05
//row.scaleY                  	 = 1.55118e-06;// +/-4.53715e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.48905 +/- 2.62765e-05
};
