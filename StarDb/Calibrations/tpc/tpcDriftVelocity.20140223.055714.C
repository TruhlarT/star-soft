TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54001
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.71732; // +/- 5.2126e-05 cm/us East: Slope = -3.40579 +/- 67.7819 DV = 5.71732 +/- 5.2126e-05
  row.laserDriftVelocityWest	 =   5.71487; // +/- 3.93326e-05 cm/us West: Slope = -3.40579 +/- 67.7819 DV = 5.71487 +/- 3.93326e-05
//row.scaleY                  	 = 1.21455e-05;// +/-4.58672e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.71576 +/- 3.13971e-05
};
