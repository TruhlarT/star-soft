typedef struct{
  int event;
  int BChi;
  int BClo;
  int Token;
  int TrgWd;
  int prepost;
  int bunchId; 
  int bunchid7bit; 
  int spinBit; 
  int VTXDSM[8]; 
  int FPDDSM[8];
  int ZDC[16];
  int CTB[256]; 
  int BBC[80]; 
  int FPDENS[112]; 
  int FPDETB[64]; 
  int FPDWNS[112]; 
  int FPDWTB[64]; 
  int FPDADC[256];
  int FPDTDC[8]; 
  int FPDWEST[72]; 
  int NPrimTrk; 
  int NTPCTrk; 
  int NEastFTPCTrk;
  float xVertex;
  float yVertex;
  float zVertex;
} ntpcb;

extern ntpcb ntp2003_;
