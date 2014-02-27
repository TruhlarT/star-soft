TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 31061
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50042; // +/- 4.6399e-05 cm/us East: Slope = 0.179624 +/- 0.0127114 DV = 5.50042 +/- 4.6399e-05
  row.laserDriftVelocityWest	 =   5.50067; // +/- 5.4593e-05 cm/us West: Slope = 0.0758766 +/- 0.0126999 DV = 5.50067 +/- 5.4593e-05
//row.scaleY                  	 = -1.04686e-06;// +/-2.49931e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50052 +/- 3.53549e-05
};
