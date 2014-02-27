TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51016
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50219; // +/- 7.88132e-05 cm/us East: Slope = 0.358723 +/- 0.0148575 DV = 5.50219 +/- 7.88132e-05
  row.laserDriftVelocityWest	 =   5.49912; // +/- 3.58478e-05 cm/us West: Slope = 0.940323 +/- 0.00696726 DV = 5.49912 +/- 3.58478e-05
//row.scaleY                  	 = -5.70713e-06;// +/-1.21037e-08
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49965 +/- 3.26309e-05
};
