TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 33063
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50683; // +/- 3.26863e-05 cm/us East: Slope = -22.5084 +/- 15.0808 DV = 5.50683 +/- 3.26863e-05
  row.laserDriftVelocityWest	 =   5.50492; // +/- 2.3401e-05 cm/us West: Slope = -22.5084 +/- 15.0808 DV = 5.50492 +/- 2.3401e-05
//row.scaleY                  	 = 5.52997e-08;// +/-1.24574e-09
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet; // 1e3*Delta: All = 5.50557 +/- 1.90274e-05
};
