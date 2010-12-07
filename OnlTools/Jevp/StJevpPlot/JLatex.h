#ifndef _JLATEX_H_
#define _JLATEX_H_

#include <TROOT.h>
#include <TObject.h>
#include <TLatex.h>

class JLatex : public TLatex {
  int ndcY;
  int ndcX;
 
  Double_t jx;
  Double_t jy;

 public:
  void SetNDC_x(int ndc);
  void SetNDC_y(int ndc);

  void SetX(Double_t x);
  void SetY(Double_t y);
  
  JLatex();
  JLatex(Double_t x, Double_t y, const char *text);
  JLatex(JLatex &l); 
    
  void SetText(const char *text) {
    TLatex::SetText(jx,jy,text);
  }
      

  void SetText(Double_t x, Double_t y, const char *text) {
    jx = x; jy = y; TLatex::SetText(x,y,text);
  };

  void Draw(Option_t * option = "");

  ClassDef(JLatex, 1);
};

#endif
