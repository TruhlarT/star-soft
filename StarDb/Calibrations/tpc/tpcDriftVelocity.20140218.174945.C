TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50365; // +/- 4.27102e-05 cm/us East: Slope = -0.377311 +/- 0.00846835 DV = 5.50365 +/- 4.27102e-05
  row.laserDriftVelocityWest	 =   5.50205; // +/- 2.68662e-05 cm/us West: Slope = -0.0906241 +/- 0.00506239 DV = 5.50205 +/- 2.68662e-05
//row.scaleY                  	 = 2.26337e-06;// +/-6.73957e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.5025 +/- 2.27412e-05
};
