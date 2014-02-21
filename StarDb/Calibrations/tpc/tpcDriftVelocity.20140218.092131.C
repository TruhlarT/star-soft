TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50202; // +/- 3.90024e-05 cm/us East: Slope = -0.085604 +/- 0.00757424 DV = 5.50202 +/- 3.90024e-05
  row.laserDriftVelocityWest	 =   5.50161; // +/- 2.21785e-05 cm/us West: Slope = -0.00351807 +/- 0.00408278 DV = 5.50161 +/- 2.21785e-05
//row.scaleY                  	 = 2.1957e-06;// +/-6.55829e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50171 +/- 1.92794e-05
};
