TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50806; // +/- 5.33835e-05 cm/us East: Slope = 0.679236 +/- 0.0117107 DV = 5.50806 +/- 5.33835e-05
  row.laserDriftVelocityWest	 =   5.50641; // +/- 5.73454e-05 cm/us West: Slope = 0.927201 +/- 0.0112315 DV = 5.50641 +/- 5.73454e-05
//row.scaleY                  	 = -4.23634e-07;// +/-1.40561e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50729 +/- 3.90735e-05
};
