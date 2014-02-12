TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 34006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50916; // +/- 1.86841e-05 cm/us East: Slope = -17.7067 +/- 16.2756 DV = 5.50916 +/- 1.86841e-05
  row.laserDriftVelocityWest	 =   5.50734; // +/- 2.08431e-05 cm/us West: Slope = -17.7067 +/- 16.2756 DV = 5.50734 +/- 2.08431e-05
//row.scaleY                  	 = -2.25653e-07;// +/-9.94687e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50835 +/- 1.39125e-05
};
