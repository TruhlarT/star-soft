TDataSet *CreateTable() { 
// -----------------------------------------------------------------
// bfc/.make/StarDb/.data/StarDb/Calibrations/tpc/tpcDriftVelocity Allocated rows: 1  Used rows: 1  Row size: 16 bytes
//  Table: tpcDriftVelocity_st[0]--> tpcDriftVelocity_st[0]
// ====================================================================
// ------  Test whether this table share library was loaded ------
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
tpcDriftVelocity_st row;
St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
//
memset(&row,0,tableSet->GetRowSize());
    row.laserDriftVelocityEast	 =       5.43; // cm/us : from laser beam analysis  ;
    row.laserDriftVelocityWest	 =       5.43; // cm/us : from laser beam analysis  ;
    row.cathodeDriftVelocityEast	 =       5.43; // cm/us : from cathode emission  ;
    row.cathodeDriftVelocityWest	 =       5.43; // cm/us : from cathode emission  ;
tableSet->AddAt(&row,0);
// ----------------- end of code ---------------
 return (TDataSet *)tableSet;
}
