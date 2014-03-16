TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54050
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50944; // +/- 3.28388e-05 cm/us East: Slope = 0.225966 +/- 0.00631705 DV = 5.50944 +/- 3.28388e-05
  row.laserDriftVelocityWest	 =   5.51171; // +/- 3.04643e-05 cm/us West: Slope = -0.203648 +/- 0.00564107 DV = 5.51171 +/- 3.04643e-05
//row.scaleY                  	 = 1.2349e-06;// +/-1.67444e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.51066 +/- 2.23338e-05
};
