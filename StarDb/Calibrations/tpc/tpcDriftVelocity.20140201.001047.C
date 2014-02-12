TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31081
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49533; // +/- 2.27487e-05 cm/us East: Slope = 1.03984 +/- 0.00445526 DV = 5.49533 +/- 2.27487e-05
  row.laserDriftVelocityWest	 =   5.48959; // +/- 3.60056e-05 cm/us West: Slope = 2.01248 +/- 0.00895796 DV = 5.48959 +/- 3.60056e-05
//row.scaleY                  	 = 4.59212e-07;// +/-3.44205e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49369 +/- 1.92318e-05
};
