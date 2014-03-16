TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 46030
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.48199; // +/- 4.14522e-05 cm/us East: Slope = 0.350811 +/- 0.00802351 DV = 5.48199 +/- 4.14522e-05
  row.laserDriftVelocityWest	 =   5.48288; // +/- 2.53533e-05 cm/us West: Slope = 0.0531716 +/- 0.00481364 DV = 5.48288 +/- 2.53533e-05
//row.scaleY                  	 = -1.784e-07;// +/-1.26339e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.48264 +/- 2.16286e-05
};
