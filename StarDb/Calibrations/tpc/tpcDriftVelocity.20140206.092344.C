TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37011
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51124; // +/- 3.27346e-05 cm/us East: Slope = 0.0181244 +/- 0.00605248 DV = 5.51124 +/- 3.27346e-05
  row.laserDriftVelocityWest	 =   5.50858; // +/- 3.55589e-05 cm/us West: Slope = 0.144042 +/- 0.00609751 DV = 5.50858 +/- 3.55589e-05
//row.scaleY                  	 = -1.65778e-07;// +/-1.25336e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51002 +/- 2.40835e-05
};
