TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51088
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50218; // +/- 1.36315e-05 cm/us East: Slope = 0.261074 +/- 0.00268865 DV = 5.50218 +/- 1.36315e-05
  row.laserDriftVelocityWest	 =   5.50307; // +/- 1.20539e-05 cm/us West: Slope = -0.157147 +/- 0.00220258 DV = 5.50307 +/- 1.20539e-05
//row.scaleY                  	 = 6.23617e-07;// +/-6.07762e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50268 +/- 9.02987e-06
};
