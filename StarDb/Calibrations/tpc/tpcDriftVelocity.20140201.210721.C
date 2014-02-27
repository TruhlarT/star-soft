TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32049
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50061; // +/- 0.0001638 cm/us East: Slope = 0.382251 +/- 0.0161609 DV = 5.50061 +/- 0.0001638
  row.laserDriftVelocityWest	 =   5.50039; // +/- 2.2998e-05 cm/us West: Slope = 0.548742 +/- 0.00413353 DV = 5.50039 +/- 2.2998e-05
//row.scaleY                  	 = 7.67355e-06;// +/-2.20359e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50039 +/- 2.27746e-05
};
