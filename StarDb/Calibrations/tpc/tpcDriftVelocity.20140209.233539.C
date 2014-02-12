TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40047
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50679; // +/- 1.21987e-05 cm/us East: Slope = 0.823896 +/- 0.00219327 DV = 5.50679 +/- 1.21987e-05
  row.laserDriftVelocityWest	 =   5.50548; // +/- 1.35759e-05 cm/us West: Slope = 1.0473 +/- 0.00244613 DV = 5.50548 +/- 1.35759e-05
//row.scaleY                  	 = -2.78285e-07;// +/-4.40202e-10
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50621 +/- 9.07375e-06
};
