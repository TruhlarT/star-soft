TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47024
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.4931; // +/- 3.75018e-05 cm/us East: Slope = 2.41261 +/- 0.00692124 DV = 5.4931 +/- 3.75018e-05
  row.laserDriftVelocityWest	 =   5.49299; // +/- 2.42815e-05 cm/us West: Slope = 2.42166 +/- 0.00468147 DV = 5.49299 +/- 2.42815e-05
//row.scaleY                  	 = 1.06551e-06;// +/-3.31118e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.49302 +/- 2.03822e-05
};
