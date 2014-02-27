TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47107
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49849; // +/- 5.18823e-05 cm/us East: Slope = 0.380654 +/- 0.0114185 DV = 5.49849 +/- 5.18823e-05
  row.laserDriftVelocityWest	 =   5.49558; // +/- 8.10779e-05 cm/us West: Slope = 0.839393 +/- 0.0206427 DV = 5.49558 +/- 8.10779e-05
//row.scaleY                  	 = -6.33734e-07;// +/-1.75147e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49764 +/- 4.37008e-05
};
