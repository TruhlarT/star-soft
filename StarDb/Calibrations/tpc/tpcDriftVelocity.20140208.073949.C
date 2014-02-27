TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39109
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50574; // +/- 0.000175763 cm/us East: Slope = 0.507191 +/- 0.243513 DV = 5.50574 +/- 0.000175763
  row.laserDriftVelocityWest	 =   5.50714; // +/- 4.1483e-05 cm/us West: Slope = 0.0748993 +/- 0.00790153 DV = 5.50714 +/- 4.1483e-05
//row.scaleY                  	 = 3.04657e-06;// +/-6.19885e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50707 +/- 4.03737e-05
};
