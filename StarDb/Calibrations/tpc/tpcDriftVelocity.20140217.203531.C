TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 48076
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50149; // +/- 2.88267e-05 cm/us East: Slope = 0.0378084 +/- 0.00516235 DV = 5.50149 +/- 2.88267e-05
  row.laserDriftVelocityWest	 =   5.50042; // +/- 2.61293e-05 cm/us West: Slope = 0.208271 +/- 0.00478244 DV = 5.50042 +/- 2.61293e-05
//row.scaleY                  	 = -2.59667e-05;// +/-2.42329e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5009 +/- 1.93597e-05
};
