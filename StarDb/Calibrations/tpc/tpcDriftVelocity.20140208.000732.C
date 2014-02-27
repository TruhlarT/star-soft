TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38073
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51168; // +/- 8.56902e-05 cm/us East: Slope = 0.230639 +/- 0.0169451 DV = 5.51168 +/- 8.56902e-05
  row.laserDriftVelocityWest	 =   5.50998; // +/- 4.37983e-05 cm/us West: Slope = 0.493859 +/- 0.00778465 DV = 5.50998 +/- 4.37983e-05
//row.scaleY                  	 = 7.67853e-07;// +/-3.40068e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51033 +/- 3.89993e-05
};
