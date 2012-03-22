#include "VpddGeo1.h"  
 // ---------------------------------------------------------------------------------------------------  
 //  
 #include "StarVMC/StarAgmlLib/StarAgmlStacker.h"  
 //  
 #include "StarVMC/StarAgmlLib/AgMaterial.h"  
 #include "StarVMC/StarAgmlLib/AgMedium.h"  
 #include "StarVMC/StarAgmlLib/AgShape.h"  
 #include "StarVMC/StarAgmlLib/AgBlock.h"  
 #include "StarVMC/StarAgmlLib/AgMath.h"  
 #include "StarVMC/StarAgmlLib/AgSTAR.h"  
 //  
 #include "StarVMC/StarAgmlLib/Mortran.h"  
 #include "StarVMC/StarAgmlLib/AgMath.h"  
 #include <iostream>  
 #include <vector>  
 #include <map>  
 const Int_t _printlevel = 0;  
 #define LOG_PRINT if(_printlevel>0) std::cout << GetName() << " -Print- "  
 #define LOG_INFO  if(_printlevel>1) std::cout << GetName() << " -Info-  "  
 #define LOG_DEBUG if(_printlevel>2) std::cout << GetName() << " -Debug- "  
 #define LOG_WARN  if(_printlevel>3) std::cout << GetName() << " -Warn-  "  
 #define printf(fmt,...) LOG_PRINT << Form(fmt,##__VA_ARGS__) << std::endl;  
 #include "StarVMC/Geometry/Helpers.h"  
 //  
 namespace VPDDGEO1 // $NMSPC  
 {     
       //     
       // ---------------------------------------------------------------------------------------------------     
          //  -----------------------------------------------------     
          /// @defgroup vpdv_doc     
          /// \class Vpdv_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Int_t vpdconfig;     
          ///Int_t _index;     
          //     
          Vpdv_t vpdv;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup vpdg_doc     
          /// \class Vpdg_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t zposeast;     
          ///Float_t zposwest;     
          ///Float_t rmin;     
          ///Float_t rmax;     
          ///Float_t bpwidth;     
          ///Float_t bplength;     
          ///Float_t bpthick;     
          ///Float_t bxheight;     
          ///Float_t bxlength;     
          ///Float_t bxwidth;     
          ///Float_t bxthick;     
          ///Float_t bxzposc;     
          ///Float_t fpwidth;     
          ///Float_t fpheight;     
          ///Float_t fpthick;     
          ///Float_t fpawidth;     
          ///Float_t fpahght;     
          ///Float_t fpchght;     
          ///Float_t fphhght;     
          ///Float_t fphwidth;     
          ///Float_t fphthick;     
          ///Float_t stthick;     
          ///Float_t stheight;     
          ///Float_t stangle;     
          ///Float_t stdiagsz;     
          ///Float_t scwidth;     
          ///Float_t scheight;     
          ///Float_t sclength;     
          ///Float_t scthick;     
          ///Float_t clheight;     
          ///Float_t clwidth;     
          ///Float_t cllength;     
          ///Float_t clthick;     
          ///Float_t detlen;     
          ///Float_t detrad;     
          ///Float_t detfront;     
          ///Float_t convthk;     
          ///Float_t radithk;     
          ///Float_t eleleng;     
          ///Float_t drlayer;     
          ///Float_t numpmt;     
          ///Float_t pmtwall;     
          ///Float_t pmtrad;     
          ///Float_t pmtlen;     
          ///Float_t ibchoice;     
          ///Float_t ibposyc;     
          ///Float_t ibposzc;     
          ///Float_t ibleng;     
          ///Float_t ibthickh;     
          ///Float_t ibthickv;     
          ///Float_t ibheight;     
          ///Float_t ibwidth;     
          ///Float_t ibwlen;     
          ///Float_t ibwhghtf;     
          ///Float_t ibwhghtb;     
          ///Int_t _index;     
          //     
          Vpdg_t vpdg;     
          //     
          ///@addtogroup VpddGeo1_vars     
          ///@{        
                Float_t ybase,ytop,convlength,detangle,strutheight,ydispl;        
                //        
                /// Float_t ybase,ytop,convlength,detangle,strutheight,ydispl        
          ///@}     
          ///@addtogroup VpddGeo1_vars     
          ///@{        
                Float_t electhck,elecwid,eleclen,xloc,yloc,zloc,zpos;        
                //        
                /// Float_t electhck,elecwid,eleclen,xloc,yloc,zloc,zpos        
          ///@}     
          ///@addtogroup VpddGeo1_vars     
          ///@{        
                Int_t isec;        
                //        
                /// Int_t isec        
          ///@}     
       VpddGeo1::VpddGeo1()     
         : AgModule("VpddGeo1","  is the Pseudo Vertex Position Detector of STAR ")     
       {        
       }     
          // ---------------------------------------------------------------------------------------------------     
          void VPDD::Block( AgCreate create )     
          {         
                ///@addtogroup VPDD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      /// Medium Standard           
                      {  AgMedium med = AgMedium::CopyMedium("Standard");              
                            _medium = med;              
                      }           
                      { AgAttribute attr = AgAttribute("VPDD");              
                            attr.par("seen")=0;              
                            attr.par("serial")=zpos;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=vpdg.rmin;              
                            shape.par("rmax")=vpdg.rmax;              
                            shape.par("dz")=vpdg.bplength/2;              
                            /// Shape Tube rmin=vpdg.rmin rmax=vpdg.rmax dz=vpdg.bplength/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPDD;              
                            _stacker -> Build(this);              
                      }           
                      ybase= vpdg.ibposyc - (vpdg.ibheight + vpdg.bpthick)/2;           
                      ytop = ybase + vpdg.bpthick/2+ vpdg.fpheight + vpdg.fpchght;           
                      _create = AgCreate("VPBP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPBP              
                            Create("VPBP");               
                      }           
                      { AgPlacement place = AgPlacement("VPBP","VPDD");              
                            /// Add daughter volume VPBP to mother VPDD              
                            place.TranslateY(ybase);              
                            /// Translate y = ybase              
                            _stacker -> Position( AgBlock::Find("VPBP"), place );              
                      } // end placement of VPBP           
                      _create = AgCreate("VPBO");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPBO              
                            Create("VPBO");               
                      }           
                      xloc=(vpdg.bpwidth-vpdg.fpwidth)/2;           
                      yloc=ybase+(vpdg.bpthick+vpdg.fphhght)/2;           
                      zloc=(vpdg.bplength-2*vpdg.fpthick-vpdg.fphhght)/2;           
                      { AgPlacement place = AgPlacement("VPBO","VPDD");              
                            /// Add daughter volume VPBO to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 180              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("VPBO"), place );              
                      } // end placement of VPBO           
                      { AgPlacement place = AgPlacement("VPBO","VPDD");              
                            /// Add daughter volume VPBO to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            _stacker -> Position( AgBlock::Find("VPBO"), place );              
                      } // end placement of VPBO           
                      { AgPlacement place = AgPlacement("VPBO","VPDD");              
                            /// Add daughter volume VPBO to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 180              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("VPBO"), place );              
                      } // end placement of VPBO           
                      { AgPlacement place = AgPlacement("VPBO","VPDD");              
                            /// Add daughter volume VPBO to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            _stacker -> Position( AgBlock::Find("VPBO"), place );              
                      } // end placement of VPBO           
                      _create = AgCreate("VPFA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPFA              
                            Create("VPFA");               
                      }           
                      yloc=ytop-vpdg.fpahght/2;           
                      zloc=(vpdg.bplength - vpdg.fpthick)/2;           
                      { AgPlacement place = AgPlacement("VPFA","VPDD");              
                            /// Add daughter volume VPFA to mother VPDD              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            _stacker -> Position( AgBlock::Find("VPFA"), place );              
                      } // end placement of VPFA           
                      { AgPlacement place = AgPlacement("VPFA","VPDD");              
                            /// Add daughter volume VPFA to mother VPDD              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            _stacker -> Position( AgBlock::Find("VPFA"), place );              
                      } // end placement of VPFA           
                      _create = AgCreate("VPFB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPFB              
                            Create("VPFB");               
                      }           
                      xloc=(vpdg.fpawidth+(vpdg.bpwidth-vpdg.fpawidth-2*vpdg.fpwidth)/2)/2;           
                      yloc=(ytop - (vpdg.fpchght+vpdg.fpahght)/4);           
                      zloc=(vpdg.bplength - vpdg.fpthick)/2;           
                      { AgPlacement place = AgPlacement("VPFB","VPDD");              
                            /// Add daughter volume VPFB to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "Y-XZ" ); // ORT=Y-XZ              
                            /// Axis substitution: XYZ --> Y-XZ              
                            _stacker -> Position( AgBlock::Find("VPFB"), place );              
                      } // end placement of VPFB           
                      { AgPlacement place = AgPlacement("VPFB","VPDD");              
                            /// Add daughter volume VPFB to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "Y-XZ" ); // ORT=Y-XZ              
                            /// Axis substitution: XYZ --> Y-XZ              
                            _stacker -> Position( AgBlock::Find("VPFB"), place );              
                      } // end placement of VPFB           
                      { AgPlacement place = AgPlacement("VPFB","VPDD");              
                            /// Add daughter volume VPFB to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "YXZ" ); // ORT=YXZ              
                            /// Axis substitution: XYZ --> YXZ              
                            _stacker -> Position( AgBlock::Find("VPFB"), place );              
                      } // end placement of VPFB           
                      { AgPlacement place = AgPlacement("VPFB","VPDD");              
                            /// Add daughter volume VPFB to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "YXZ" ); // ORT=YXZ              
                            /// Axis substitution: XYZ --> YXZ              
                            _stacker -> Position( AgBlock::Find("VPFB"), place );              
                      } // end placement of VPFB           
                      _create = AgCreate("VPFC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPFC              
                            Create("VPFC");               
                      }           
                      xloc=(vpdg.bpwidth-vpdg.fpwidth)/2;           
                      yloc=(ytop-(vpdg.fpchght+vpdg.fpwidth/2)/2);           
                      zloc=(vpdg.bplength - vpdg.fpthick)/2;           
                      { AgPlacement place = AgPlacement("VPFC","VPDD");              
                            /// Add daughter volume VPFC to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "Y-XZ" ); // ORT=Y-XZ              
                            /// Axis substitution: XYZ --> Y-XZ              
                            _stacker -> Position( AgBlock::Find("VPFC"), place );              
                      } // end placement of VPFC           
                      { AgPlacement place = AgPlacement("VPFC","VPDD");              
                            /// Add daughter volume VPFC to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "Y-XZ" ); // ORT=Y-XZ              
                            /// Axis substitution: XYZ --> Y-XZ              
                            _stacker -> Position( AgBlock::Find("VPFC"), place );              
                      } // end placement of VPFC           
                      { AgPlacement place = AgPlacement("VPFC","VPDD");              
                            /// Add daughter volume VPFC to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "YXZ" ); // ORT=YXZ              
                            /// Axis substitution: XYZ --> YXZ              
                            _stacker -> Position( AgBlock::Find("VPFC"), place );              
                      } // end placement of VPFC           
                      { AgPlacement place = AgPlacement("VPFC","VPDD");              
                            /// Add daughter volume VPFC to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "YXZ" ); // ORT=YXZ              
                            /// Axis substitution: XYZ --> YXZ              
                            _stacker -> Position( AgBlock::Find("VPFC"), place );              
                      } // end placement of VPFC           
                      _create = AgCreate("VPFP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPFP              
                            Create("VPFP");               
                      }           
                      xloc=(vpdg.bpwidth-vpdg.fpwidth)/2;           
                      yloc=(ybase+vpdg.bpthick/2+ vpdg.fpheight/2);           
                      zloc=(vpdg.bplength-vpdg.fpthick)/2;           
                      { AgPlacement place = AgPlacement("VPFP","VPDD");              
                            /// Add daughter volume VPFP to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            _stacker -> Position( AgBlock::Find("VPFP"), place );              
                      } // end placement of VPFP           
                      { AgPlacement place = AgPlacement("VPFP","VPDD");              
                            /// Add daughter volume VPFP to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            _stacker -> Position( AgBlock::Find("VPFP"), place );              
                      } // end placement of VPFP           
                      { AgPlacement place = AgPlacement("VPFP","VPDD");              
                            /// Add daughter volume VPFP to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            _stacker -> Position( AgBlock::Find("VPFP"), place );              
                      } // end placement of VPFP           
                      { AgPlacement place = AgPlacement("VPFP","VPDD");              
                            /// Add daughter volume VPFP to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            _stacker -> Position( AgBlock::Find("VPFP"), place );              
                      } // end placement of VPFP           
                      strutheight = vpdg.stdiagsz/cos(vpdg.stangle*degrad)                    + vpdg.bplength*tan(vpdg.stangle*degrad);           
                      _create = AgCreate("VPST");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPST              
                            Create("VPST");               
                      }           
                      xloc=(vpdg.bpwidth+vpdg.stthick)/2;           
                      yloc=ytop-vpdg.fpwidth-strutheight/2;           
                      { AgPlacement place = AgPlacement("VPST","VPDD");              
                            /// Add daughter volume VPST to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            _stacker -> Position( AgBlock::Find("VPST"), place );              
                      } // end placement of VPST           
                      { AgPlacement place = AgPlacement("VPST","VPDD");              
                            /// Add daughter volume VPST to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            _stacker -> Position( AgBlock::Find("VPST"), place );              
                      } // end placement of VPST           
                      _create = AgCreate("VPSC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPSC              
                            Create("VPSC");               
                      }           
                      xloc=(vpdg.bpwidth-vpdg.scwidth)/2;           
                      yloc=ytop-vpdg.fpwidth-strutheight+vpdg.scheight/2;           
                      zloc=(vpdg.bplength+vpdg.sclength)/2;           
                      { AgPlacement place = AgPlacement("VPSC","VPDD");              
                            /// Add daughter volume VPSC to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            place.AlphaX(180.);              
                            /// Rotate: AlphaX = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VPSC"), place );              
                      } // end placement of VPSC           
                      { AgPlacement place = AgPlacement("VPSC","VPDD");              
                            /// Add daughter volume VPSC to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(zloc);              
                            /// Translate z = zloc              
                            place.AlphaX(180.);              
                            /// Rotate: AlphaX = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VPSC"), place );              
                      } // end placement of VPSC           
                      yloc=ytop-vpdg.fpwidth-vpdg.scheight/2;           
                      { AgPlacement place = AgPlacement("VPSC","VPDD");              
                            /// Add daughter volume VPSC to mother VPDD              
                            place.TranslateX(xloc);              
                            /// Translate x = xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            _stacker -> Position( AgBlock::Find("VPSC"), place );              
                      } // end placement of VPSC           
                      { AgPlacement place = AgPlacement("VPSC","VPDD");              
                            /// Add daughter volume VPSC to mother VPDD              
                            place.TranslateX(-xloc);              
                            /// Translate x = -xloc              
                            place.TranslateY(yloc);              
                            /// Translate y = yloc              
                            place.TranslateZ(-zloc);              
                            /// Translate z = -zloc              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VPSC"), place );              
                      } // end placement of VPSC           
                      _create = AgCreate("VPBX");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPBX              
                            Create("VPBX");               
                      }           
                      { AgPlacement place = AgPlacement("VPBX","VPDD");              
                            /// Add daughter volume VPBX to mother VPDD              
                            place.TranslateX(-(vpdg.bpwidth-vpdg.bxwidth)/2);              
                            /// Translate x = -(vpdg.bpwidth-vpdg.bxwidth)/2              
                            place.TranslateY((ybase-vpdg.bpthick/2-vpdg.bxheight/2));              
                            /// Translate y = (ybase-vpdg.bpthick/2-vpdg.bxheight/2)              
                            _stacker -> Position( AgBlock::Find("VPBX"), place );              
                      } // end placement of VPBX           
                      _create = AgCreate("VRNG");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VRNG              
                            Create("VRNG");               
                      }           
                      { AgPlacement place = AgPlacement("VRNG","VPDD");              
                            /// Add daughter volume VRNG to mother VPDD              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("VRNG"), place );              
                      } // end placement of VRNG           
                      if ( vpdg.ibchoice!=0 )           
                      {              
                            _create = AgCreate("IBEM");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create IBEM                 
                                  Create("IBEM");                  
                            }              
                            { AgPlacement place = AgPlacement("IBEM","VPDD");                 
                                  /// Add daughter volume IBEM to mother VPDD                 
                                  place.TranslateY(vpdg.ibposyc);                 
                                  /// Translate y = vpdg.ibposyc                 
                                  place.TranslateZ(-zpos+vpdg.ibposzc);                 
                                  /// Translate z = -zpos+vpdg.ibposzc                 
                                  _stacker -> Position( AgBlock::Find("IBEM"), place );                 
                            } // end placement of IBEM              
                      }           
                      END_OF_VPDD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPDD     
          // ---------------------------------------------------------------------------------------------------     
          void VPBP::Block( AgCreate create )     
          {         
                ///@addtogroup VPBP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPBP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=5;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.bpwidth/2;              
                            shape.par("dy")=vpdg.bpthick/2;              
                            /// Shape Bbox dx=vpdg.bpwidth/2 dy=vpdg.bpthick/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPBP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPBP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPBP     
          // ---------------------------------------------------------------------------------------------------     
          void VPBO::Block( AgCreate create )     
          {         
                ///@addtogroup VPBO_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("VPBO");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.fphwidth/2;              
                            shape.par("dy")=vpdg.fphhght/2;              
                            shape.par("dz")=vpdg.fphhght/2;              
                            /// Shape Bbox dx=vpdg.fphwidth/2 dy=vpdg.fphhght/2 dz=vpdg.fphhght/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPBO;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("VPBA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPBA              
                            Create("VPBA");               
                      }           
                      { AgPlacement place = AgPlacement("VPBA","VPBO");              
                            /// Add daughter volume VPBA to mother VPBO              
                            place.TranslateZ(-(vpdg.fphhght-vpdg.fphthick)/2);              
                            /// Translate z = -(vpdg.fphhght-vpdg.fphthick)/2              
                            _stacker -> Position( AgBlock::Find("VPBA"), place );              
                      } // end placement of VPBA           
                      _create = AgCreate("VPBB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPBB              
                            Create("VPBB");               
                      }           
                      { AgPlacement place = AgPlacement("VPBB","VPBO");              
                            /// Add daughter volume VPBB to mother VPBO              
                            place.TranslateY(-(vpdg.fphhght-vpdg.fphthick)/2);              
                            /// Translate y = -(vpdg.fphhght-vpdg.fphthick)/2              
                            place.TranslateZ(vpdg.fphthick/2);              
                            /// Translate z = vpdg.fphthick/2              
                            _stacker -> Position( AgBlock::Find("VPBB"), place );              
                      } // end placement of VPBB           
                      END_OF_VPBO:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPBO     
          // ---------------------------------------------------------------------------------------------------     
          void VPBA::Block( AgCreate create )     
          {         
                ///@addtogroup VPBA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPBA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=5;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.fphwidth/2;              
                            shape.par("dy")=vpdg.fphhght/2;              
                            shape.par("dz")=vpdg.fphthick/2;              
                            /// Shape Bbox dx=vpdg.fphwidth/2 dy=vpdg.fphhght/2 dz=vpdg.fphthick/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPBA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPBA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPBA     
          // ---------------------------------------------------------------------------------------------------     
          void VPBB::Block( AgCreate create )     
          {         
                ///@addtogroup VPBB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPBB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=5;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.fphwidth/2;              
                            shape.par("dy")=vpdg.fphthick/2;              
                            shape.par("dz")=(vpdg.fphhght-vpdg.fphthick)/2;              
                            /// Shape Bbox dx=vpdg.fphwidth/2 dy=vpdg.fphthick/2 dz=(vpdg.fphhght-vpdg.fphthick)/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPBB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPBB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPBB     
          // ---------------------------------------------------------------------------------------------------     
          void VPFP::Block( AgCreate create )     
          {         
                ///@addtogroup VPFP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPFP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.fpwidth/2;              
                            shape.par("dy")=vpdg.fpheight/2;              
                            shape.par("dz")=vpdg.fpthick/2;              
                            /// Shape Bbox dx=vpdg.fpwidth/2 dy=vpdg.fpheight/2 dz=vpdg.fpthick/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPFP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPFP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPFP     
          // ---------------------------------------------------------------------------------------------------     
          void VPFA::Block( AgCreate create )     
          {         
                ///@addtogroup VPFA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPFA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.fpawidth/2;              
                            shape.par("dy")=vpdg.fpahght/2;              
                            shape.par("dz")=vpdg.fpthick/2;              
                            /// Shape Bbox dx=vpdg.fpawidth/2 dy=vpdg.fpahght/2 dz=vpdg.fpthick/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPFA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPFA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPFA     
          // ---------------------------------------------------------------------------------------------------     
          void VPFB::Block( AgCreate create )     
          {         
                ///@addtogroup VPFB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPFB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trap");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=vpdg.fpthick/2;              
                            shape.par("thet")=0.;              
                            shape.par("phi")=0.;              
                            shape.par("h1")=(vpdg.bpwidth-vpdg.fpawidth-2*vpdg.fpwidth)/4;              
                            shape.par("bl1")=vpdg.fpchght/2;              
                            shape.par("tl1")=vpdg.fpahght/2;              
                            shape.par("alp1")=atan(vpdg.fpahght/(vpdg.bpwidth-vpdg.fpawidth-2*vpdg.fpwidth)/2)*raddeg;              
                            shape.par("h2")=(vpdg.bpwidth-vpdg.fpawidth-2*vpdg.fpwidth)/4;              
                            shape.par("bl2")=vpdg.fpchght/2;              
                            shape.par("tl2")=vpdg.fpahght/2;              
                            shape.par("alp2")=atan(vpdg.fpahght/(vpdg.bpwidth-vpdg.fpawidth-2*vpdg.fpwidth)/2)*raddeg;              
                            /// Shape Trap dz=vpdg.fpthick/2 thet=0. phi=0. h1=(vpdg.bpwidth-vpdg.fpawidth-2*vpdg.fpwidth)/4 bl1=vpdg.fpchght/2 tl1=vpdg.fpahght/2 alp1=atan(vpdg.fpahght/(vpdg.bpwidth-vpdg.fpawidth-2*vpdg.fpwidth)/2)*raddeg h2=(vpdg.bpwidth-vpdg.fpawidth-2*vpdg.fpwidth)/4 bl2=vpdg.fpchght/2 tl2=vpdg.fpahght/2 alp2=atan(vpdg.fpahght/(vpdg.bpwidth-vpdg.fpawidth-2*vpdg.fpwidth)/2)*raddeg               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPFB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPFB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPFB     
          // ---------------------------------------------------------------------------------------------------     
          void VPFC::Block( AgCreate create )     
          {         
                ///@addtogroup VPFC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPFC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trap");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=vpdg.fpthick/2;              
                            shape.par("thet")=0.;              
                            shape.par("phi")=0.;              
                            shape.par("h1")=vpdg.fpwidth/2;              
                            shape.par("bl1")=(vpdg.fpchght-vpdg.fpwidth)/2;              
                            shape.par("tl1")=vpdg.fpchght/2;              
                            shape.par("alp1")=atan(.5)*raddeg;              
                            shape.par("h2")=vpdg.fpwidth/2;              
                            shape.par("bl2")=(vpdg.fpchght-vpdg.fpwidth)/2;              
                            shape.par("tl2")=vpdg.fpchght/2;              
                            shape.par("alp2")=atan(.5)*raddeg;              
                            /// Shape Trap dz=vpdg.fpthick/2 thet=0. phi=0. h1=vpdg.fpwidth/2 bl1=(vpdg.fpchght-vpdg.fpwidth)/2 tl1=vpdg.fpchght/2 alp1=atan(.5)*raddeg h2=vpdg.fpwidth/2 bl2=(vpdg.fpchght-vpdg.fpwidth)/2 tl2=vpdg.fpchght/2 alp2=atan(.5)*raddeg               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPFC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPFC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPFC     
          // ---------------------------------------------------------------------------------------------------     
          void VPST::Block( AgCreate create )     
          {         
                ///@addtogroup VPST_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("VPST");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.stthick/2;              
                            shape.par("dy")=strutheight/2;              
                            shape.par("dz")=(vpdg.bplength+2*vpdg.sclength)/2;              
                            /// Shape Bbox dx=vpdg.stthick/2 dy=strutheight/2 dz=(vpdg.bplength+2*vpdg.sclength)/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPST;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("VPSV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPSV              
                            Create("VPSV");               
                      }           
                      { AgPlacement place = AgPlacement("VPSV","VPST");              
                            /// Add daughter volume VPSV to mother VPST              
                            _stacker -> Position( AgBlock::Find("VPSV"), place );              
                      } // end placement of VPSV           
                      _create = AgCreate("VPSW");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPSW              
                            Create("VPSW");               
                      }           
                      ydispl=(vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad))+vpdg.scheight/2)/2;           
                      { AgPlacement place = AgPlacement("VPSW","VPST");              
                            /// Add daughter volume VPSW to mother VPST              
                            place.TranslateY(strutheight/2-ydispl);              
                            /// Translate y = strutheight/2-ydispl              
                            place.TranslateZ(-(vpdg.bplength+vpdg.sclength)/2);              
                            /// Translate z = -(vpdg.bplength+vpdg.sclength)/2              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "yzx" ); // ORT=yzx              
                            /// Axis substitution: XYZ --> yzx              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VPSW"), place );              
                      } // end placement of VPSW           
                      { AgPlacement place = AgPlacement("VPSW","VPST");              
                            /// Add daughter volume VPSW to mother VPST              
                            place.TranslateY(-(strutheight/2-ydispl));              
                            /// Translate y = -(strutheight/2-ydispl)              
                            place.TranslateZ((vpdg.bplength+vpdg.sclength)/2);              
                            /// Translate z = (vpdg.bplength+vpdg.sclength)/2              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "yzx" ); // ORT=yzx              
                            /// Axis substitution: XYZ --> yzx              
                            place.AlphaY(180.);              
                            /// Rotate: AlphaY = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VPSW"), place );              
                      } // end placement of VPSW           
                      END_OF_VPST:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPST     
          // ---------------------------------------------------------------------------------------------------     
          void VPSV::Block( AgCreate create )     
          {         
                ///@addtogroup VPSV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPSV");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trap");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=vpdg.bplength/2;              
                            shape.par("thet")=vpdg.stangle;              
                            shape.par("phi")=270.;              
                            shape.par("h1")=vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad));              
                            shape.par("bl1")=vpdg.stthick/2;              
                            shape.par("tl1")=vpdg.stthick/2;              
                            shape.par("alp1")=0.;              
                            shape.par("h2")=vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad));              
                            shape.par("bl2")=vpdg.stthick/2;              
                            shape.par("tl2")=vpdg.stthick/2;              
                            shape.par("alp2")=0.;              
                            /// Shape Trap dz=vpdg.bplength/2 thet=vpdg.stangle phi=270. h1=vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad)) bl1=vpdg.stthick/2 tl1=vpdg.stthick/2 alp1=0. h2=vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad)) bl2=vpdg.stthick/2 tl2=vpdg.stthick/2 alp2=0.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPSV;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPSV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPSV     
          // ---------------------------------------------------------------------------------------------------     
          void VPSW::Block( AgCreate create )     
          {         
                ///@addtogroup VPSW_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPSW");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trap");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=vpdg.stthick/2;              
                            shape.par("thet")=0.;              
                            shape.par("phi")=0.;              
                            shape.par("h1")=vpdg.sclength/2;              
                            shape.par("bl1")=vpdg.scheight/2;              
                            shape.par("tl1")=vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad));              
                            shape.par("alp1")=atan((vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad))-vpdg.scheight/2)/vpdg.sclength)*raddeg;              
                            shape.par("h2")=vpdg.sclength/2;              
                            shape.par("bl2")=vpdg.scheight/2;              
                            shape.par("tl2")=vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad));              
                            shape.par("alp2")=atan((vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad))-vpdg.scheight/2)/vpdg.sclength)*raddeg;              
                            /// Shape Trap dz=vpdg.stthick/2 thet=0. phi=0. h1=vpdg.sclength/2 bl1=vpdg.scheight/2 tl1=vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad)) alp1=atan((vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad))-vpdg.scheight/2)/vpdg.sclength)*raddeg h2=vpdg.sclength/2 bl2=vpdg.scheight/2 tl2=vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad)) alp2=atan((vpdg.stdiagsz/(2*cos(vpdg.stangle*degrad))-vpdg.scheight/2)/vpdg.sclength)*raddeg               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPSW;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPSW:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPSW     
          // ---------------------------------------------------------------------------------------------------     
          void VPSC::Block( AgCreate create )     
          {         
                ///@addtogroup VPSC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.scwidth/2;              
                            shape.par("dy")=vpdg.scheight/2;              
                            shape.par("dz")=vpdg.sclength/2;              
                            /// Shape Bbox dx=vpdg.scwidth/2 dy=vpdg.scheight/2 dz=vpdg.sclength/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPSC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("VPSA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPSA              
                            Create("VPSA");               
                      }           
                      { AgPlacement place = AgPlacement("VPSA","VPSC");              
                            /// Add daughter volume VPSA to mother VPSC              
                            place.TranslateX(-vpdg.scthick/2);              
                            /// Translate x = -vpdg.scthick/2              
                            place.TranslateZ((vpdg.sclength-vpdg.scthick)/2);              
                            /// Translate z = (vpdg.sclength-vpdg.scthick)/2              
                            _stacker -> Position( AgBlock::Find("VPSA"), place );              
                      } // end placement of VPSA           
                      _create = AgCreate("VPSB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPSB              
                            Create("VPSB");               
                      }           
                      { AgPlacement place = AgPlacement("VPSB","VPSC");              
                            /// Add daughter volume VPSB to mother VPSC              
                            place.TranslateX((vpdg.scwidth-vpdg.scthick)/2);              
                            /// Translate x = (vpdg.scwidth-vpdg.scthick)/2              
                            _stacker -> Position( AgBlock::Find("VPSB"), place );              
                      } // end placement of VPSB           
                      END_OF_VPSC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPSC     
          // ---------------------------------------------------------------------------------------------------     
          void VPSA::Block( AgCreate create )     
          {         
                ///@addtogroup VPSA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPSA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=(vpdg.scwidth-vpdg.scthick)/2;              
                            shape.par("dy")=vpdg.scheight/2;              
                            shape.par("dz")=vpdg.scthick/2;              
                            /// Shape Bbox dx=(vpdg.scwidth-vpdg.scthick)/2 dy=vpdg.scheight/2 dz=vpdg.scthick/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPSA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPSA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPSA     
          // ---------------------------------------------------------------------------------------------------     
          void VPSB::Block( AgCreate create )     
          {         
                ///@addtogroup VPSB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPSB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.scthick/2;              
                            shape.par("dy")=vpdg.scheight/2;              
                            shape.par("dz")=vpdg.sclength/2;              
                            /// Shape Bbox dx=vpdg.scthick/2 dy=vpdg.scheight/2 dz=vpdg.sclength/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPSB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPSB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPSB     
          // ---------------------------------------------------------------------------------------------------     
          void VPBX::Block( AgCreate create )     
          {         
                ///@addtogroup VPBX_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPBX");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.bxwidth/2;              
                            shape.par("dy")=vpdg.bxheight/2;              
                            shape.par("dz")=vpdg.bxlength/2;              
                            /// Shape Bbox dx=vpdg.bxwidth/2 dy=vpdg.bxheight/2 dz=vpdg.bxlength/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPBX;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("VPBI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPBI              
                            Create("VPBI");               
                      }           
                      { AgPlacement place = AgPlacement("VPBI","VPBX");              
                            /// Add daughter volume VPBI to mother VPBX              
                            _stacker -> Position( AgBlock::Find("VPBI"), place );              
                      } // end placement of VPBI           
                      END_OF_VPBX:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPBX     
          // ---------------------------------------------------------------------------------------------------     
          void VPBI::Block( AgCreate create )     
          {         
                ///@addtogroup VPBI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPBI");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=(vpdg.bxwidth-vpdg.bxthick)/2;              
                            shape.par("dy")=(vpdg.bxheight-vpdg.bxthick)/2;              
                            shape.par("dz")=(vpdg.bxlength-vpdg.bxthick)/2;              
                            /// Shape Bbox dx=(vpdg.bxwidth-vpdg.bxthick)/2 dy=(vpdg.bxheight-vpdg.bxthick)/2 dz=(vpdg.bxlength-vpdg.bxthick)/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPBI;              
                            _stacker -> Build(this);              
                      }           
                      elecwid=20.3;           
                      electhck=0.17;           
                      eleclen=5.1;           
                      _create = AgCreate("VFEE");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VFEE              
                            Create("VFEE");               
                      }           
                      { AgPlacement place = AgPlacement("VFEE","VPBI");              
                            /// Add daughter volume VFEE to mother VPBI              
                            place.TranslateX(-(vpdg.bxwidth-vpdg.bxthick-elecwid)/2+2.54);              
                            /// Translate x = -(vpdg.bxwidth-vpdg.bxthick-elecwid)/2+2.54              
                            place.TranslateY((vpdg.bxheight-vpdg.bxthick)/2-1.77);              
                            /// Translate y = (vpdg.bxheight-vpdg.bxthick)/2-1.77              
                            place.TranslateZ(-(vpdg.bxlength-vpdg.bxthick-eleclen)/2);              
                            /// Translate z = -(vpdg.bxlength-vpdg.bxthick-eleclen)/2              
                            _stacker -> Position( AgBlock::Find("VFEE"), place );              
                      } // end placement of VFEE           
                      END_OF_VPBI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPBI     
          // ---------------------------------------------------------------------------------------------------     
          void VFEE::Block( AgCreate create )     
          {         
                ///@addtogroup VFEE_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("VFEE");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Component Si	a=28.08	z=14	w=0.6*1*28./60.           
                      /// Component O	a=16	z=8	w=0.6*2*16./60. + 0.4*4*16./174.           
                      /// Component C	a=12	z=6	w=0.4*8*12./174.           
                      /// Component H	a=1	z=1	w=0.4*14*1./174.           
                      /// Mixture G10 dens=1.7           
                      {  AgMaterial &mix = AgMaterial::Get("G10");              
                            mix.Component("Si",28.08,14,0.6*1*28./60.);              
                            mix.Component("O",16,8,0.6*2*16./60. + 0.4*4*16./174.);              
                            mix.Component("C",12,6,0.4*8*12./174.);              
                            mix.Component("H",1,1,0.4*14*1./174.);              
                            mix.par("dens")=1.7;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=elecwid/2;              
                            shape.par("dy")=electhck/2;              
                            shape.par("dz")=eleclen/2;              
                            /// Shape Bbox dx=elecwid/2 dy=electhck/2 dz=eleclen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VFEE;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("VLEM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VLEM              
                            Create("VLEM");               
                      }           
                      electhck= 0.17;           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(-7.0);              
                            /// Translate x = -7.0              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(2);              
                            /// Translate z = 2              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(-3.5);              
                            /// Translate x = -3.5              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(2);              
                            /// Translate z = 2              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(2);              
                            /// Translate z = 2              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(3.5);              
                            /// Translate x = 3.5              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(2);              
                            /// Translate z = 2              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(-7.0);              
                            /// Translate x = -7.0              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(-2);              
                            /// Translate z = -2              
                            place.AlphaX(180);              
                            /// Rotate: AlphaX = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(-3.5);              
                            /// Translate x = -3.5              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(-2);              
                            /// Translate z = -2              
                            place.AlphaX(180);              
                            /// Rotate: AlphaX = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(-2);              
                            /// Translate z = -2              
                            place.AlphaX(180);              
                            /// Rotate: AlphaX = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(3.5);              
                            /// Translate x = 3.5              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(-2);              
                            /// Translate z = -2              
                            place.AlphaX(180);              
                            /// Rotate: AlphaX = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(-6.0);              
                            /// Translate x = -6.0              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(-2);              
                            /// Translate z = -2              
                            place.AlphaX(180);              
                            /// Rotate: AlphaX = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(-2.5);              
                            /// Translate x = -2.5              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(-2);              
                            /// Translate z = -2              
                            place.AlphaX(180);              
                            /// Rotate: AlphaX = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(1.);              
                            /// Translate x = 1.              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(-2);              
                            /// Translate z = -2              
                            place.AlphaX(180);              
                            /// Rotate: AlphaX = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(4.5);              
                            /// Translate x = 4.5              
                            place.TranslateY(electhck+(0.7/2));              
                            /// Translate y = electhck+(0.7/2)              
                            place.TranslateZ(-2);              
                            /// Translate z = -2              
                            place.AlphaX(180);              
                            /// Rotate: AlphaX = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      END_OF_VFEE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VFEE     
          // ---------------------------------------------------------------------------------------------------     
          void VLEM::Block( AgCreate create )     
          {         
                ///@addtogroup VLEM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("VLEM");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=(0.68/2+(0.9-0.72)/2);              
                            shape.par("dy")=(0.68/2);              
                            shape.par("dz")=(2.0/2+(0.8+1.0)/2);              
                            /// Shape Bbox dx=(0.68/2+(0.9-0.72)/2) dy=(0.68/2) dz=(2.0/2+(0.8+1.0)/2)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VLEM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("VPIP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPIP              
                            Create("VPIP");               
                      }           
                      { AgPlacement place = AgPlacement("VPIP","VLEM");              
                            /// Add daughter volume VPIP to mother VLEM              
                            place.TranslateX((0.9-0.72)/2);              
                            /// Translate x = (0.9-0.72)/2              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ((0.8+1.0)/2);              
                            /// Translate z = (0.8+1.0)/2              
                            place.par("dz")=2.0/2;              
                            place.par("rmin")=0.62/2;              
                            place.par("rmax")=0.68/2;              
                            _stacker -> Position( AgBlock::Find("VPIP"), place );              
                      } // end placement of VPIP           
                      END_OF_VLEM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VLEM     
          // ---------------------------------------------------------------------------------------------------     
          void VPIP::Block( AgCreate create )     
          {         
                ///@addtogroup VPIP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("VPIP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=0;              
                            shape.par("dz")=0;              
                            /// Shape Tube rmin=0 rmax=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPIP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPIP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPIP     
          // ---------------------------------------------------------------------------------------------------     
          void VRNG::Block( AgCreate create )     
          {         
                ///@addtogroup VRNG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=vpdg.rmin;              
                            shape.par("rmax")=vpdg.rmin+2*vpdg.detrad+vpdg.clheight;              
                            shape.par("dz")=vpdg.cllength/2;              
                            /// Shape Tube rmin=vpdg.rmin rmax=vpdg.rmin+2*vpdg.detrad+vpdg.clheight dz=vpdg.cllength/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VRNG;              
                            _stacker -> Build(this);              
                      }           
                      /// Loop on isec from 1 to vpdg.numpmt step=1           
                      for ( isec=1; (1>0)? (isec<=vpdg.numpmt):(isec>=vpdg.numpmt); isec+=1 )           
                      {              
                            detangle=-30+isec*(360/vpdg.numpmt);              
                            _create = AgCreate("VSEC");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create VSEC                 
                                  Create("VSEC");                  
                            }              
                            { AgPlacement place = AgPlacement("VSEC","VRNG");                 
                                  /// Add daughter volume VSEC to mother VRNG                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaZ(detangle);                 
                                  /// Rotate: AlphaZ = detangle                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("VSEC"), place );                 
                            } // end placement of VSEC              
                      }           
                      END_OF_VRNG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VRNG     
          // ---------------------------------------------------------------------------------------------------     
          void VSEC::Block( AgCreate create )     
          {         
                ///@addtogroup VSEC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("VSEC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=5;              
                            attr.par("serial")=isec;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-360/(2*vpdg.numpmt);              
                            shape.par("phi2")=+360/(2*vpdg.numpmt);              
                            /// Shape Tubs phi1=-360/(2*vpdg.numpmt) phi2=+360/(2*vpdg.numpmt)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VSEC;              
                            _stacker -> Build(this);              
                      }           
                      ydispl=vpdg.detrad - sqrt(vpdg.detrad*vpdg.detrad -             (vpdg.clwidth/2-vpdg.clthick)*(vpdg.clwidth/2-vpdg.clthick) );           
                      _create = AgCreate("VDET");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VDET              
                            Create("VDET");               
                      }           
                      { AgPlacement place = AgPlacement("VDET","VSEC");              
                            /// Add daughter volume VDET to mother VSEC              
                            place.TranslateX(vpdg.rmin+vpdg.detrad);              
                            /// Translate x = vpdg.rmin+vpdg.detrad              
                            _stacker -> Position( AgBlock::Find("VDET"), place );              
                      } // end placement of VDET           
                      if ( isec==3 )           
                      {              
                            _create = AgCreate("VPCL");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create VPCL                 
                                  Create("VPCL");                  
                            }              
                            { AgPlacement place = AgPlacement("VPCL","VSEC");                 
                                  /// Add daughter volume VPCL to mother VSEC                 
                                  place.TranslateX(vpdg.rmin+vpdg.detrad);                 
                                  /// Translate x = vpdg.rmin+vpdg.detrad                 
                                  place.TranslateY((vpdg.detrad+vpdg.clheight/2-ydispl));                 
                                  /// Translate y = (vpdg.detrad+vpdg.clheight/2-ydispl)                 
                                  _stacker -> Position( AgBlock::Find("VPCL"), place );                 
                            } // end placement of VPCL              
                      }           
                      else           
                      {              
                            _create = AgCreate("VPCL");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create VPCL                 
                                  Create("VPCL");                  
                            }              
                            { AgPlacement place = AgPlacement("VPCL","VSEC");                 
                                  /// Add daughter volume VPCL to mother VSEC                 
                                  place.TranslateX(vpdg.rmin+vpdg.detrad);                 
                                  /// Translate x = vpdg.rmin+vpdg.detrad                 
                                  place.TranslateY(-(vpdg.detrad+vpdg.clheight/2-ydispl));                 
                                  /// Translate y = -(vpdg.detrad+vpdg.clheight/2-ydispl)                 
                                  _stacker -> Position( AgBlock::Find("VPCL"), place );                 
                            } // end placement of VPCL              
                      }           
                      _create = AgCreate("VXST");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VXST              
                            Create("VXST");               
                      }           
                      { AgPlacement place = AgPlacement("VXST","VSEC");              
                            /// Add daughter volume VXST to mother VSEC              
                            place.TranslateX(vpdg.rmin+vpdg.detrad+0.4);              
                            /// Translate x = vpdg.rmin+vpdg.detrad+0.4              
                            place.TranslateY(+1.5);              
                            /// Translate y = +1.5              
                            place.TranslateZ(vpdg.detlen/2+1.0);              
                            /// Translate z = vpdg.detlen/2+1.0              
                            _stacker -> Position( AgBlock::Find("VXST"), place );              
                      } // end placement of VXST           
                      { AgPlacement place = AgPlacement("VXST","VSEC");              
                            /// Add daughter volume VXST to mother VSEC              
                            place.TranslateX(vpdg.rmin+vpdg.detrad-0.4);              
                            /// Translate x = vpdg.rmin+vpdg.detrad-0.4              
                            place.TranslateY(-1.5);              
                            /// Translate y = -1.5              
                            place.TranslateZ(vpdg.detlen/2+1.0);              
                            /// Translate z = vpdg.detlen/2+1.0              
                            _stacker -> Position( AgBlock::Find("VXST"), place );              
                      } // end placement of VXST           
                      END_OF_VSEC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VSEC     
          // ---------------------------------------------------------------------------------------------------     
          void VDET::Block( AgCreate create )     
          {         
                ///@addtogroup VDET_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material IRON            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Iron");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VDET");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=vpdg.detrad;              
                            shape.par("dz")=vpdg.detlen/2;              
                            /// Shape Tube rmin=0 rmax=vpdg.detrad dz=vpdg.detlen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VDET;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("VDTI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VDTI              
                            Create("VDTI");               
                      }           
                      { AgPlacement place = AgPlacement("VDTI","VDET");              
                            /// Add daughter volume VDTI to mother VDET              
                            place.TranslateZ(+vpdg.detfront);              
                            /// Translate z = +vpdg.detfront              
                            _stacker -> Position( AgBlock::Find("VDTI"), place );              
                      } // end placement of VDTI           
                      END_OF_VDET:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VDET     
          // ---------------------------------------------------------------------------------------------------     
          void VDTI::Block( AgCreate create )     
          {         
                ///@addtogroup VDTI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VDTI");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=vpdg.pmtrad;              
                            shape.par("dz")=vpdg.detlen/2-vpdg.detfront;              
                            /// Shape Tube rmin=0 rmax=vpdg.pmtrad dz=vpdg.detlen/2-vpdg.detfront               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VDTI;              
                            _stacker -> Build(this);              
                      }           
                      convlength=vpdg.convthk+vpdg.radithk;           
                      _create = AgCreate("VCNV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VCNV              
                            Create("VCNV");               
                      }           
                      { AgPlacement place = AgPlacement("VCNV","VDTI");              
                            /// Add daughter volume VCNV to mother VDTI              
                            place.TranslateZ(-(vpdg.detlen-convlength)/2);              
                            /// Translate z = -(vpdg.detlen-convlength)/2              
                            _stacker -> Position( AgBlock::Find("VCNV"), place );              
                      } // end placement of VCNV           
                      _create = AgCreate("VPMT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPMT              
                            Create("VPMT");               
                      }           
                      { AgPlacement place = AgPlacement("VPMT","VDTI");              
                            /// Add daughter volume VPMT to mother VDTI              
                            place.TranslateZ(-(vpdg.detlen/2-convlength-vpdg.pmtlen/2));              
                            /// Translate z = -(vpdg.detlen/2-convlength-vpdg.pmtlen/2)              
                            _stacker -> Position( AgBlock::Find("VPMT"), place );              
                      } // end placement of VPMT           
                      END_OF_VDTI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VDTI     
          // ---------------------------------------------------------------------------------------------------     
          void VCNV::Block( AgCreate create )     
          {         
                ///@addtogroup VCNV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Lead            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Lead");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VCNV");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=vpdg.convthk/2+vpdg.radithk/2;              
                            /// Shape Tube dz=vpdg.convthk/2+vpdg.radithk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VCNV;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("VRAD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VRAD              
                            Create("VRAD");               
                      }           
                      { AgPlacement place = AgPlacement("VRAD","VCNV");              
                            /// Add daughter volume VRAD to mother VCNV              
                            place.TranslateZ(vpdg.convthk/2);              
                            /// Translate z = vpdg.convthk/2              
                            _stacker -> Position( AgBlock::Find("VRAD"), place );              
                      } // end placement of VRAD           
                      END_OF_VCNV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VCNV     
          // ---------------------------------------------------------------------------------------------------     
          void VRAD::Block( AgCreate create )     
          {         
                ///@addtogroup VRAD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
                            _material = mat;              
                      }           
                      /// Medium sensitive           
                      ///  isvol = 1            
                      {  AgMedium &med = AgMedium::Get("Sensitive");              
                               med.Inherit(this);              
                            med.par("isvol")=1 ;              
                            _medium = med;              
                      }           
                      { AgAttribute attr = AgAttribute("VRAD");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=vpdg.radithk/2;              
                            /// Shape Tube dz=vpdg.radithk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VRAD;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VRAD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VRAD     
          // ---------------------------------------------------------------------------------------------------     
          void VPMT::Block( AgCreate create )     
          {         
                ///@addtogroup VPMT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Vacuum            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Vacuum");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPMT");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmax")=vpdg.pmtrad-vpdg.pmtwall;              
                            shape.par("dz")=vpdg.pmtlen/2-vpdg.pmtwall;              
                            /// Shape Tube rmax=vpdg.pmtrad-vpdg.pmtwall dz=vpdg.pmtlen/2-vpdg.pmtwall               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPMT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPMT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPMT     
          // ---------------------------------------------------------------------------------------------------     
          void VXST::Block( AgCreate create )     
          {         
                ///@addtogroup VXST_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("VXST");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=0.3;              
                            shape.par("dz")=1.0;              
                            /// Shape Tube rmin=0 rmax=0.3 dz=1.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VXST;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VXST:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VXST     
          // ---------------------------------------------------------------------------------------------------     
          void VPCL::Block( AgCreate create )     
          {         
                ///@addtogroup VPCL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("VPCL");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.clwidth/2;              
                            shape.par("dy")=vpdg.clheight/2;              
                            shape.par("dz")=vpdg.cllength/2;              
                            /// Shape Bbox dx=vpdg.clwidth/2 dy=vpdg.clheight/2 dz=vpdg.cllength/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPCL;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("VPCF");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPCF              
                            Create("VPCF");               
                      }           
                      { AgPlacement place = AgPlacement("VPCF","VPCL");              
                            /// Add daughter volume VPCF to mother VPCL              
                            place.TranslateZ(+(vpdg.cllength-vpdg.clthick)/2);              
                            /// Translate z = +(vpdg.cllength-vpdg.clthick)/2              
                            _stacker -> Position( AgBlock::Find("VPCF"), place );              
                      } // end placement of VPCF           
                      { AgPlacement place = AgPlacement("VPCF","VPCL");              
                            /// Add daughter volume VPCF to mother VPCL              
                            place.TranslateZ(-(vpdg.cllength-vpdg.clthick)/2);              
                            /// Translate z = -(vpdg.cllength-vpdg.clthick)/2              
                            _stacker -> Position( AgBlock::Find("VPCF"), place );              
                      } // end placement of VPCF           
                      _create = AgCreate("VPCH");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPCH              
                            Create("VPCH");               
                      }           
                      { AgPlacement place = AgPlacement("VPCH","VPCL");              
                            /// Add daughter volume VPCH to mother VPCL              
                            _stacker -> Position( AgBlock::Find("VPCH"), place );              
                      } // end placement of VPCH           
                      _create = AgCreate("VPCV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VPCV              
                            Create("VPCV");               
                      }           
                      { AgPlacement place = AgPlacement("VPCV","VPCL");              
                            /// Add daughter volume VPCV to mother VPCL              
                            place.TranslateX((vpdg.clwidth-vpdg.clthick)/2);              
                            /// Translate x = (vpdg.clwidth-vpdg.clthick)/2              
                            place.TranslateY(-vpdg.clthick/2-(vpdg.clheight/2-vpdg.clthick/2)/2);              
                            /// Translate y = -vpdg.clthick/2-(vpdg.clheight/2-vpdg.clthick/2)/2              
                            _stacker -> Position( AgBlock::Find("VPCV"), place );              
                      } // end placement of VPCV           
                      { AgPlacement place = AgPlacement("VPCV","VPCL");              
                            /// Add daughter volume VPCV to mother VPCL              
                            place.TranslateX(-(vpdg.clwidth-vpdg.clthick)/2);              
                            /// Translate x = -(vpdg.clwidth-vpdg.clthick)/2              
                            place.TranslateY(-vpdg.clthick/2-(vpdg.clheight/2-vpdg.clthick/2)/2);              
                            /// Translate y = -vpdg.clthick/2-(vpdg.clheight/2-vpdg.clthick/2)/2              
                            _stacker -> Position( AgBlock::Find("VPCV"), place );              
                      } // end placement of VPCV           
                      END_OF_VPCL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPCL     
          // ---------------------------------------------------------------------------------------------------     
          void VPCF::Block( AgCreate create )     
          {         
                ///@addtogroup VPCF_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPCF");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.clwidth/2;              
                            shape.par("dy")=vpdg.clheight/2;              
                            shape.par("dz")=vpdg.clthick/2;              
                            /// Shape Bbox dx=vpdg.clwidth/2 dy=vpdg.clheight/2 dz=vpdg.clthick/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPCF;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPCF:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPCF     
          // ---------------------------------------------------------------------------------------------------     
          void VPCH::Block( AgCreate create )     
          {         
                ///@addtogroup VPCH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPCH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.clwidth/2;              
                            shape.par("dy")=vpdg.clthick/2;              
                            shape.par("dz")=(vpdg.cllength-2*vpdg.clthick)/2;              
                            /// Shape Bbox dx=vpdg.clwidth/2 dy=vpdg.clthick/2 dz=(vpdg.cllength-2*vpdg.clthick)/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPCH;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPCH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPCH     
          // ---------------------------------------------------------------------------------------------------     
          void VPCV::Block( AgCreate create )     
          {         
                ///@addtogroup VPCV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("VPCV");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.clthick/2;              
                            shape.par("dy")=(vpdg.clheight/2-vpdg.clthick/2)/2;              
                            shape.par("dz")=(vpdg.cllength-2*vpdg.clthick)/2;              
                            /// Shape Bbox dx=vpdg.clthick/2 dy=(vpdg.clheight/2-vpdg.clthick/2)/2 dz=(vpdg.cllength-2*vpdg.clthick)/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_VPCV;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_VPCV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block VPCV     
          // ---------------------------------------------------------------------------------------------------     
          void IBEM::Block( AgCreate create )     
          {         
                ///@addtogroup IBEM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBEM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.ibwidth/2;              
                            shape.par("dy")=vpdg.ibheight/2;              
                            shape.par("dz")=vpdg.ibleng/2;              
                            /// Shape Bbox dx=vpdg.ibwidth/2 dy=vpdg.ibheight/2 dz=vpdg.ibleng/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBEM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("IBEH");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("IBEH");              
                            create.par("dy")=vpdg.ibthickh/2;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: dy = vpdg.ibthickh/2              
                            myshape.par("dy")=vpdg.ibthickh/2;              
                            ///Create IBEH              
                            Create("IBEH");               
                      }           
                      { AgPlacement place = AgPlacement("IBEH","IBEM");              
                            /// Add daughter volume IBEH to mother IBEM              
                            place.TranslateY(+(vpdg.ibheight-vpdg.ibthickh)/2);              
                            /// Translate y = +(vpdg.ibheight-vpdg.ibthickh)/2              
                            _stacker -> Position( AgBlock::Find("IBEH"), place );              
                      } // end placement of IBEH           
                      _create = AgCreate("IBEH");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("IBEH");              
                            create.par("dz")=(vpdg.ibleng-vpdg.ibwlen)/2;              
                            create.par("dy")=vpdg.ibthickh/2;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: dz = (vpdg.ibleng-vpdg.ibwlen)/2              
                            myshape.par("dz")=(vpdg.ibleng-vpdg.ibwlen)/2;              
                            /// Set shape par: dy = vpdg.ibthickh/2              
                            myshape.par("dy")=vpdg.ibthickh/2;              
                            ///Create IBEH              
                            Create("IBEH");               
                      }           
                      { AgPlacement place = AgPlacement("IBEH","IBEM");              
                            /// Add daughter volume IBEH to mother IBEM              
                            place.TranslateY(-(vpdg.ibheight-vpdg.ibthickh)/2);              
                            /// Translate y = -(vpdg.ibheight-vpdg.ibthickh)/2              
                            place.TranslateZ(+vpdg.ibwlen/2);              
                            /// Translate z = +vpdg.ibwlen/2              
                            _stacker -> Position( AgBlock::Find("IBEH"), place );              
                      } // end placement of IBEH           
                      _create = AgCreate("IBEV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create IBEV              
                            Create("IBEV");               
                      }           
                      { AgPlacement place = AgPlacement("IBEV","IBEM");              
                            /// Add daughter volume IBEV to mother IBEM              
                            place.TranslateZ(+vpdg.ibwlen/2);              
                            /// Translate z = +vpdg.ibwlen/2              
                            _stacker -> Position( AgBlock::Find("IBEV"), place );              
                      } // end placement of IBEV           
                      _create = AgCreate("IBEW");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create IBEW              
                            Create("IBEW");               
                      }           
                      { AgPlacement place = AgPlacement("IBEW","IBEM");              
                            /// Add daughter volume IBEW to mother IBEM              
                            place.TranslateY((vpdg.ibheight/2-vpdg.ibthickh-(vpdg.ibwhghtf+vpdg.ibwhghtb)/4));              
                            /// Translate y = (vpdg.ibheight/2-vpdg.ibthickh-(vpdg.ibwhghtf+vpdg.ibwhghtb)/4)              
                            place.TranslateZ(-(vpdg.ibleng-vpdg.ibwlen)/2);              
                            /// Translate z = -(vpdg.ibleng-vpdg.ibwlen)/2              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "yzx" ); // ORT=yzx              
                            /// Axis substitution: XYZ --> yzx              
                            place.AlphaZ(180);              
                            /// Rotate: AlphaZ = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("IBEW"), place );              
                      } // end placement of IBEW           
                      END_OF_IBEM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBEM     
          // ---------------------------------------------------------------------------------------------------     
          void IBEH::Block( AgCreate create )     
          {         
                ///@addtogroup IBEH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBEH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            /// Shape Bbox               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBEH;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBEH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBEH     
          // ---------------------------------------------------------------------------------------------------     
          void IBEV::Block( AgCreate create )     
          {         
                ///@addtogroup IBEV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBEV");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpdg.ibthickv/2;              
                            shape.par("dy")=(vpdg.ibheight-2*vpdg.ibthickh)/2;              
                            shape.par("dz")=(vpdg.ibleng-vpdg.ibwlen)/2;              
                            /// Shape Bbox dx=vpdg.ibthickv/2 dy=(vpdg.ibheight-2*vpdg.ibthickh)/2 dz=(vpdg.ibleng-vpdg.ibwlen)/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBEV;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBEV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBEV     
          // ---------------------------------------------------------------------------------------------------     
          void IBEW::Block( AgCreate create )     
          {         
                ///@addtogroup IBEW_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBEW");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.par("fill")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trap");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=vpdg.ibthickv/2;              
                            shape.par("thet")=0.;              
                            shape.par("phi")=0.;              
                            shape.par("h1")=vpdg.ibwlen/2;              
                            shape.par("bl1")=vpdg.ibwhghtf/2;              
                            shape.par("tl1")=vpdg.ibwhghtb/2;              
                            shape.par("alp1")=atan((vpdg.ibwhghtb-vpdg.ibwhghtf)/vpdg.ibwlen/2)*raddeg;              
                            shape.par("h2")=vpdg.ibwlen/2;              
                            shape.par("bl2")=vpdg.ibwhghtf/2;              
                            shape.par("tl2")=vpdg.ibwhghtb/2;              
                            shape.par("alp2")=atan((vpdg.ibwhghtb-vpdg.ibwhghtf)/vpdg.ibwlen/2)*raddeg;              
                            /// Shape Trap dz=vpdg.ibthickv/2 thet=0. phi=0. h1=vpdg.ibwlen/2 bl1=vpdg.ibwhghtf/2 tl1=vpdg.ibwhghtb/2 alp1=atan((vpdg.ibwhghtb-vpdg.ibwhghtf)/vpdg.ibwlen/2)*raddeg h2=vpdg.ibwlen/2 bl2=vpdg.ibwhghtf/2 tl2=vpdg.ibwhghtb/2 alp2=atan((vpdg.ibwhghtb-vpdg.ibwhghtf)/vpdg.ibwlen/2)*raddeg               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBEW;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBEW:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBEW     
    // ----------------------------------------------------------------------- geoctr
       void VpddGeo1::ConstructGeometry( const Char_t *dummy )     
       {        
             ///@addtogroup VpddGeo1_revision        
             ///@{           
                   /// Author: Frank Geurts           
             ///@}        
             ///@addtogroup VpddGeo1_revision        
             ///@{           
                   /// Created:  21 June 2000            
             ///@}        
             AddBlock("VPDD");        
             AddBlock("VPBP");        
             AddBlock("VPBO");        
             AddBlock("VPBA");        
             AddBlock("VPBB");        
             AddBlock("VPBX");        
             AddBlock("VFEE");        
             AddBlock("VLEM");        
             AddBlock("VPIP");        
             AddBlock("VPFP");        
             AddBlock("VPFA");        
             AddBlock("VPFB");        
             AddBlock("VPFC");        
             AddBlock("VPBI");        
             AddBlock("VPST");        
             AddBlock("VPSC");        
             AddBlock("VPSA");        
             AddBlock("VPSB");        
             AddBlock("VPSV");        
             AddBlock("VPSW");        
             AddBlock("VRNG");        
             AddBlock("VSEC");        
             AddBlock("VDET");        
             AddBlock("VXST");        
             AddBlock("VCNV");        
             AddBlock("VPMT");        
             AddBlock("VRAD");        
             AddBlock("VPCL");        
             AddBlock("VPCF");        
             AddBlock("VPCV");        
             AddBlock("VPCH");        
             AddBlock("VDTI");        
             AddBlock("IBEM");        
             AddBlock("IBEH");        
             AddBlock("IBEV");        
             AddBlock("IBEW");        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdv_doc        
             ///@{           
                   ++vpdv._index;           
                   vpdv . version = 1; //  version            
                   /// vpdv . version = 1; //  version            
                   vpdv . vpdconfig = 1; //  vpd configuration            
                   /// vpdv . vpdconfig = 1; //  vpd configuration            
                   //           
                   vpdv.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdg_doc        
             ///@{           
                   ++vpdg._index;           
                   vpdg . version = 1; //  geometry version            
                   /// vpdg . version = 1; //  geometry version            
                   vpdg . zposeast = 550.0000; //  Z position East            
                   /// vpdg . zposeast = 550.0000; //  Z position East            
                   vpdg . zposwest = 550.0000; //  Z position West            
                   /// vpdg . zposwest = 550.0000; //  Z position West            
                   vpdg . rmin = 6.35; //  mothervolume rmin               (2.5inch)            
                   /// vpdg . rmin = 6.35; //  mothervolume rmin               (2.5inch)            
                   vpdg . rmax = 31.27375; //  mothervolume rmin               (12.3125inch)            
                   /// vpdg . rmax = 31.27375; //  mothervolume rmin               (12.3125inch)            
                   vpdg . bpwidth = 30.48; //  baseplate width                 (12inch)            
                   /// vpdg . bpwidth = 30.48; //  baseplate width                 (12inch)            
                   vpdg . bplength = 46.355; //  baseplate length                (18.5inch)            
                   /// vpdg . bplength = 46.355; //  baseplate length                (18.5inch)            
                   vpdg . bpthick = 0.635; //  baseplate thickness             (0.25inch)            
                   /// vpdg . bpthick = 0.635; //  baseplate thickness             (0.25inch)            
                   vpdg . bxheight = 5.08; //  FEE box height                  (2inch)            
                   /// vpdg . bxheight = 5.08; //  FEE box height                  (2inch)            
                   vpdg . bxlength = 15.24; //  FEE box length                  (6inch)            
                   /// vpdg . bxlength = 15.24; //  FEE box length                  (6inch)            
                   vpdg . bxwidth = 25.4; //  FEE box width                   (10inch)            
                   /// vpdg . bxwidth = 25.4; //  FEE box width                   (10inch)            
                   vpdg . bxthick = 0.635; //  FEE box plate thickness         (0.25inch)            
                   /// vpdg . bxthick = 0.635; //  FEE box plate thickness         (0.25inch)            
                   vpdg . bxzposc = 0.635; //  FEE central z pos (+/-??)       (0.25inch)            
                   /// vpdg . bxzposc = 0.635; //  FEE central z pos (+/-??)       (0.25inch)            
                   vpdg . fpwidth = 7.62; //  frontplate width                (3inch)            
                   /// vpdg . fpwidth = 7.62; //  frontplate width                (3inch)            
                   vpdg . fpheight = 25.45842; //  frontplate height               (10.023inch)            
                   /// vpdg . fpheight = 25.45842; //  frontplate height               (10.023inch)            
                   vpdg . fpthick = 2.54; //  frontplate thickness            (1inch)            
                   /// vpdg . fpthick = 2.54; //  frontplate thickness            (1inch)            
                   vpdg . fpawidth = 6.63956; //  frontpl.part A width            (2.614inch)            
                   /// vpdg . fpawidth = 6.63956; //  frontpl.part A width            (2.614inch)            
                   vpdg . fpahght = 8.35405; //  frontpl.part A height           (3.289inch)            
                   /// vpdg . fpahght = 8.35405; //  frontpl.part A height           (3.289inch)            
                   vpdg . fpchght = 12.573; //  frontpl.part C height           (4.95inch)            
                   /// vpdg . fpchght = 12.573; //  frontpl.part C height           (4.95inch)            
                   vpdg . fphhght = 3.81; //  frontpl. hook height            (1.5inch)            
                   /// vpdg . fphhght = 3.81; //  frontpl. hook height            (1.5inch)            
                   vpdg . fphwidth = 5.08; //  frontpl. hook width             (2inch)            
                   /// vpdg . fphwidth = 5.08; //  frontpl. hook width             (2inch)            
                   vpdg . fphthick = 0.635; //  frontpl. hook thickness         (0.25inch)            
                   /// vpdg . fphthick = 0.635; //  frontpl. hook thickness         (0.25inch)            
                   vpdg . stthick = 0.635; //  strut thickness                 (0.25inch)            
                   /// vpdg . stthick = 0.635; //  strut thickness                 (0.25inch)            
                   vpdg . stheight = 23.1775; //  strut height                    (9.125 inch)            
                   /// vpdg . stheight = 23.1775; //  strut height                    (9.125 inch)            
                   vpdg . stangle = 25.; //  strut angle (degr)            
                   /// vpdg . stangle = 25.; //  strut angle (degr)            
                   vpdg . stdiagsz = 5.08; //  diagnoal strut size             (2inch)            
                   /// vpdg . stdiagsz = 5.08; //  diagnoal strut size             (2inch)            
                   vpdg . scwidth = 7.62; //  strut clamp width               (3inch)            
                   /// vpdg . scwidth = 7.62; //  strut clamp width               (3inch)            
                   vpdg . scheight = 3.81; //  strut clamp height              (1.5inch)            
                   /// vpdg . scheight = 3.81; //  strut clamp height              (1.5inch)            
                   vpdg . sclength = 3.81; //  strut clamp length              (1.5inch)            
                   /// vpdg . sclength = 3.81; //  strut clamp length              (1.5inch)            
                   vpdg . scthick = 0.635; //  strut clamp thickness           (0.25inch)            
                   /// vpdg . scthick = 0.635; //  strut clamp thickness           (0.25inch)            
                   vpdg . clheight = 3.4925; //  clamp height                    (1.375inch)            
                   /// vpdg . clheight = 3.4925; //  clamp height                    (1.375inch)            
                   vpdg . clwidth = 3.81; //  clamp width                     (1.5inch)            
                   /// vpdg . clwidth = 3.81; //  clamp width                     (1.5inch)            
                   vpdg . cllength = 41.275; //  clamp length                    (16.25inch)            
                   /// vpdg . cllength = 41.275; //  clamp length                    (16.25inch)            
                   vpdg . clthick = 0.3175; //  clamp plate thickness           (0.125inch)            
                   /// vpdg . clthick = 0.3175; //  clamp plate thickness           (0.125inch)            
                   vpdg . detlen = 33.02; //  PMT assembly length             (13inch)            
                   /// vpdg . detlen = 33.02; //  PMT assembly length             (13inch)            
                   vpdg . detrad = 3.81; //  PMT assembly radius             (1.5inch)            
                   /// vpdg . detrad = 3.81; //  PMT assembly radius             (1.5inch)            
                   vpdg . detfront = 1.016; //  PMT ass. frontplate thickness   (0.4inch)            
                   /// vpdg . detfront = 1.016; //  PMT ass. frontplate thickness   (0.4inch)            
                   vpdg . convthk = 1.; //  Converter layer thickness            
                   /// vpdg . convthk = 1.; //  Converter layer thickness            
                   vpdg . radithk = 1.; //  Radiator layer thickness                  
                   /// vpdg . radithk = 1.; //  Radiator layer thickness                  
                   vpdg . eleleng = 15.0; //  electronics mount length            
                   /// vpdg . eleleng = 15.0; //  electronics mount length            
                   vpdg . drlayer = 6.; //  layer radial width            
                   /// vpdg . drlayer = 6.; //  layer radial width            
                   vpdg . numpmt = 3; //  number of PMT in layer            
                   /// vpdg . numpmt = 3; //  number of PMT in layer            
                   vpdg . pmtwall = 0.1; //  PMT wall thickness            
                   /// vpdg . pmtwall = 0.1; //  PMT wall thickness            
                   vpdg . pmtrad = 2.54; //  PMT and detector radius         (1inch)            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius         (1inch)            
                   vpdg . pmtlen = 8.0; //  PMT tube length             
                   /// vpdg . pmtlen = 8.0; //  PMT tube length             
                   vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   /// vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   vpdg . ibposyc = -16.51; //  IBeam central Ylocation         (6.5inch)            
                   /// vpdg . ibposyc = -16.51; //  IBeam central Ylocation         (6.5inch)            
                   vpdg . ibposzc = 530.477; //  IBeam central Zposition            
                   /// vpdg . ibposzc = 530.477; //  IBeam central Zposition            
                   vpdg . ibleng = 294.894; //  IBeam length                    (116.1inch)            
                   /// vpdg . ibleng = 294.894; //  IBeam length                    (116.1inch)            
                   vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness    (0.29inch)            
                   /// vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness    (0.29inch)            
                   vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness     (0.17inch)            
                   /// vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness     (0.17inch)            
                   vpdg . ibheight = 10.16; //  IBeam height                    (4inch)            
                   /// vpdg . ibheight = 10.16; //  IBeam height                    (4inch)            
                   vpdg . ibwidth = 7.62; //  IBeam width                     (3inch)            
                   /// vpdg . ibwidth = 7.62; //  IBeam width                     (3inch)            
                   vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   /// vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   //           
                   vpdg.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdg_doc        
             ///@{           
                   ++vpdg._index;           
                   vpdg . version = 2; //  geometry version            
                   /// vpdg . version = 2; //  geometry version            
                   vpdg . zposeast = 561.2638; //  Z position East            
                   /// vpdg . zposeast = 561.2638; //  Z position East            
                   vpdg . zposwest = 563.1688; //  Z position West            
                   /// vpdg . zposwest = 563.1688; //  Z position West            
                   vpdg . rmin = 6.35; //  mothervolume rmin               (2.5inch)            
                   /// vpdg . rmin = 6.35; //  mothervolume rmin               (2.5inch)            
                   vpdg . rmax = 31.27375; //  mothervolume rmin               (12.3125inch)            
                   /// vpdg . rmax = 31.27375; //  mothervolume rmin               (12.3125inch)            
                   vpdg . bpwidth = 30.48; //  baseplate width                 (12inch)            
                   /// vpdg . bpwidth = 30.48; //  baseplate width                 (12inch)            
                   vpdg . bplength = 46.355; //  baseplate length                (18.5inch)            
                   /// vpdg . bplength = 46.355; //  baseplate length                (18.5inch)            
                   vpdg . bpthick = 0.635; //  baseplate thickness             (0.25inch)            
                   /// vpdg . bpthick = 0.635; //  baseplate thickness             (0.25inch)            
                   vpdg . bxheight = 5.08; //  FEE box height                  (2inch)            
                   /// vpdg . bxheight = 5.08; //  FEE box height                  (2inch)            
                   vpdg . bxlength = 15.24; //  FEE box length                  (6inch)            
                   /// vpdg . bxlength = 15.24; //  FEE box length                  (6inch)            
                   vpdg . bxwidth = 25.4; //  FEE box width                   (10inch)            
                   /// vpdg . bxwidth = 25.4; //  FEE box width                   (10inch)            
                   vpdg . bxthick = 0.635; //  FEE box plate thickness         (0.25inch)            
                   /// vpdg . bxthick = 0.635; //  FEE box plate thickness         (0.25inch)            
                   vpdg . bxzposc = 0.635; //  FEE central z pos (+/-??)       (0.25inch)            
                   /// vpdg . bxzposc = 0.635; //  FEE central z pos (+/-??)       (0.25inch)            
                   vpdg . fpwidth = 7.62; //  frontplate width                (3inch)            
                   /// vpdg . fpwidth = 7.62; //  frontplate width                (3inch)            
                   vpdg . fpheight = 25.45842; //  frontplate height               (10.023inch)            
                   /// vpdg . fpheight = 25.45842; //  frontplate height               (10.023inch)            
                   vpdg . fpthick = 2.54; //  frontplate thickness            (1inch)            
                   /// vpdg . fpthick = 2.54; //  frontplate thickness            (1inch)            
                   vpdg . fpawidth = 6.63956; //  frontpl.part A width            (2.614inch)            
                   /// vpdg . fpawidth = 6.63956; //  frontpl.part A width            (2.614inch)            
                   vpdg . fpahght = 8.35405; //  frontpl.part A height           (3.289inch)            
                   /// vpdg . fpahght = 8.35405; //  frontpl.part A height           (3.289inch)            
                   vpdg . fpchght = 12.573; //  frontpl.part C height           (4.95inch)            
                   /// vpdg . fpchght = 12.573; //  frontpl.part C height           (4.95inch)            
                   vpdg . fphhght = 3.81; //  frontpl. hook height            (1.5inch)            
                   /// vpdg . fphhght = 3.81; //  frontpl. hook height            (1.5inch)            
                   vpdg . fphwidth = 5.08; //  frontpl. hook width             (2inch)            
                   /// vpdg . fphwidth = 5.08; //  frontpl. hook width             (2inch)            
                   vpdg . fphthick = 0.635; //  frontpl. hook thickness         (0.25inch)            
                   /// vpdg . fphthick = 0.635; //  frontpl. hook thickness         (0.25inch)            
                   vpdg . stthick = 0.635; //  strut thickness                 (0.25inch)            
                   /// vpdg . stthick = 0.635; //  strut thickness                 (0.25inch)            
                   vpdg . stheight = 23.1775; //  strut height                    (9.125 inch)            
                   /// vpdg . stheight = 23.1775; //  strut height                    (9.125 inch)            
                   vpdg . stangle = 25.; //  strut angle (degr)            
                   /// vpdg . stangle = 25.; //  strut angle (degr)            
                   vpdg . stdiagsz = 5.08; //  diagnoal strut size             (2inch)            
                   /// vpdg . stdiagsz = 5.08; //  diagnoal strut size             (2inch)            
                   vpdg . scwidth = 7.62; //  strut clamp width               (3inch)            
                   /// vpdg . scwidth = 7.62; //  strut clamp width               (3inch)            
                   vpdg . scheight = 3.81; //  strut clamp height              (1.5inch)            
                   /// vpdg . scheight = 3.81; //  strut clamp height              (1.5inch)            
                   vpdg . sclength = 3.81; //  strut clamp length              (1.5inch)            
                   /// vpdg . sclength = 3.81; //  strut clamp length              (1.5inch)            
                   vpdg . scthick = 0.635; //  strut clamp thickness           (0.25inch)            
                   /// vpdg . scthick = 0.635; //  strut clamp thickness           (0.25inch)            
                   vpdg . clheight = 3.4925; //  clamp height                    (1.375inch)            
                   /// vpdg . clheight = 3.4925; //  clamp height                    (1.375inch)            
                   vpdg . clwidth = 3.81; //  clamp width                     (1.5inch)            
                   /// vpdg . clwidth = 3.81; //  clamp width                     (1.5inch)            
                   vpdg . cllength = 41.275; //  clamp length                    (16.25inch)            
                   /// vpdg . cllength = 41.275; //  clamp length                    (16.25inch)            
                   vpdg . clthick = 0.3175; //  clamp plate thickness           (0.125inch)            
                   /// vpdg . clthick = 0.3175; //  clamp plate thickness           (0.125inch)            
                   vpdg . detlen = 33.02; //  PMT assembly length             (13inch)            
                   /// vpdg . detlen = 33.02; //  PMT assembly length             (13inch)            
                   vpdg . detrad = 3.81; //  PMT assembly radius             (1.5inch)            
                   /// vpdg . detrad = 3.81; //  PMT assembly radius             (1.5inch)            
                   vpdg . detfront = 1.016; //  PMT ass. frontplate thickness   (0.4inch)            
                   /// vpdg . detfront = 1.016; //  PMT ass. frontplate thickness   (0.4inch)            
                   vpdg . convthk = 1.; //  Converter layer thickness            
                   /// vpdg . convthk = 1.; //  Converter layer thickness            
                   vpdg . radithk = 1.; //  Radiator layer thickness                  
                   /// vpdg . radithk = 1.; //  Radiator layer thickness                  
                   vpdg . eleleng = 15.0; //  electronics mount length            
                   /// vpdg . eleleng = 15.0; //  electronics mount length            
                   vpdg . drlayer = 6.; //  layer radial width            
                   /// vpdg . drlayer = 6.; //  layer radial width            
                   vpdg . numpmt = 3; //  number of PMT in layer            
                   /// vpdg . numpmt = 3; //  number of PMT in layer            
                   vpdg . pmtwall = 0.1; //  PMT wall thickness            
                   /// vpdg . pmtwall = 0.1; //  PMT wall thickness            
                   vpdg . pmtrad = 2.54; //  PMT and detector radius         (1inch)            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius         (1inch)            
                   vpdg . pmtlen = 8.0; //  PMT tube length             
                   /// vpdg . pmtlen = 8.0; //  PMT tube length             
                   vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   /// vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   vpdg . ibposyc = -16.51; //  IBeam central Ylocation         (6.5inch)            
                   /// vpdg . ibposyc = -16.51; //  IBeam central Ylocation         (6.5inch)            
                   vpdg . ibposzc = 530.477; //  IBeam central Zposition            
                   /// vpdg . ibposzc = 530.477; //  IBeam central Zposition            
                   vpdg . ibleng = 294.894; //  IBeam length                    (116.1inch)            
                   /// vpdg . ibleng = 294.894; //  IBeam length                    (116.1inch)            
                   vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness    (0.29inch)            
                   /// vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness    (0.29inch)            
                   vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness     (0.17inch)            
                   /// vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness     (0.17inch)            
                   vpdg . ibheight = 10.16; //  IBeam height                    (4inch)            
                   /// vpdg . ibheight = 10.16; //  IBeam height                    (4inch)            
                   vpdg . ibwidth = 7.62; //  IBeam width                     (3inch)            
                   /// vpdg . ibwidth = 7.62; //  IBeam width                     (3inch)            
                   vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   /// vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   //           
                   vpdg.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdg_doc        
             ///@{           
                   ++vpdg._index;           
                   vpdg . version = 3; //  geometry version            
                   /// vpdg . version = 3; //  geometry version            
                   vpdg . zposeast = 564.4388; //  Z position East            
                   /// vpdg . zposeast = 564.4388; //  Z position East            
                   vpdg . zposwest = 563.4069; //  Z position West            
                   /// vpdg . zposwest = 563.4069; //  Z position West            
                   vpdg . rmin = 6.35; //  mothervolume rmin               (2.5inch)            
                   /// vpdg . rmin = 6.35; //  mothervolume rmin               (2.5inch)            
                   vpdg . rmax = 31.27375; //  mothervolume rmin               (12.3125inch)            
                   /// vpdg . rmax = 31.27375; //  mothervolume rmin               (12.3125inch)            
                   vpdg . bpwidth = 30.48; //  baseplate width                 (12inch)            
                   /// vpdg . bpwidth = 30.48; //  baseplate width                 (12inch)            
                   vpdg . bplength = 46.355; //  baseplate length                (18.5inch)            
                   /// vpdg . bplength = 46.355; //  baseplate length                (18.5inch)            
                   vpdg . bpthick = 0.635; //  baseplate thickness             (0.25inch)            
                   /// vpdg . bpthick = 0.635; //  baseplate thickness             (0.25inch)            
                   vpdg . bxheight = 5.08; //  FEE box height                  (2inch)            
                   /// vpdg . bxheight = 5.08; //  FEE box height                  (2inch)            
                   vpdg . bxlength = 15.24; //  FEE box length                  (6inch)            
                   /// vpdg . bxlength = 15.24; //  FEE box length                  (6inch)            
                   vpdg . bxwidth = 25.4; //  FEE box width                   (10inch)            
                   /// vpdg . bxwidth = 25.4; //  FEE box width                   (10inch)            
                   vpdg . bxthick = 0.635; //  FEE box plate thickness         (0.25inch)            
                   /// vpdg . bxthick = 0.635; //  FEE box plate thickness         (0.25inch)            
                   vpdg . bxzposc = 0.635; //  FEE central z pos (+/-??)       (0.25inch)            
                   /// vpdg . bxzposc = 0.635; //  FEE central z pos (+/-??)       (0.25inch)            
                   vpdg . fpwidth = 7.62; //  frontplate width                (3inch)            
                   /// vpdg . fpwidth = 7.62; //  frontplate width                (3inch)            
                   vpdg . fpheight = 25.45842; //  frontplate height               (10.023inch)            
                   /// vpdg . fpheight = 25.45842; //  frontplate height               (10.023inch)            
                   vpdg . fpthick = 2.54; //  frontplate thickness            (1inch)            
                   /// vpdg . fpthick = 2.54; //  frontplate thickness            (1inch)            
                   vpdg . fpawidth = 6.63956; //  frontpl.part A width            (2.614inch)            
                   /// vpdg . fpawidth = 6.63956; //  frontpl.part A width            (2.614inch)            
                   vpdg . fpahght = 8.35405; //  frontpl.part A height           (3.289inch)            
                   /// vpdg . fpahght = 8.35405; //  frontpl.part A height           (3.289inch)            
                   vpdg . fpchght = 12.573; //  frontpl.part C height           (4.95inch)            
                   /// vpdg . fpchght = 12.573; //  frontpl.part C height           (4.95inch)            
                   vpdg . fphhght = 3.81; //  frontpl. hook height            (1.5inch)            
                   /// vpdg . fphhght = 3.81; //  frontpl. hook height            (1.5inch)            
                   vpdg . fphwidth = 5.08; //  frontpl. hook width             (2inch)            
                   /// vpdg . fphwidth = 5.08; //  frontpl. hook width             (2inch)            
                   vpdg . fphthick = 0.635; //  frontpl. hook thickness         (0.25inch)            
                   /// vpdg . fphthick = 0.635; //  frontpl. hook thickness         (0.25inch)            
                   vpdg . stthick = 0.635; //  strut thickness                 (0.25inch)            
                   /// vpdg . stthick = 0.635; //  strut thickness                 (0.25inch)            
                   vpdg . stheight = 23.1775; //  strut height                    (9.125 inch)            
                   /// vpdg . stheight = 23.1775; //  strut height                    (9.125 inch)            
                   vpdg . stangle = 25.; //  strut angle (degr)            
                   /// vpdg . stangle = 25.; //  strut angle (degr)            
                   vpdg . stdiagsz = 5.08; //  diagnoal strut size             (2inch)            
                   /// vpdg . stdiagsz = 5.08; //  diagnoal strut size             (2inch)            
                   vpdg . scwidth = 7.62; //  strut clamp width               (3inch)            
                   /// vpdg . scwidth = 7.62; //  strut clamp width               (3inch)            
                   vpdg . scheight = 3.81; //  strut clamp height              (1.5inch)            
                   /// vpdg . scheight = 3.81; //  strut clamp height              (1.5inch)            
                   vpdg . sclength = 3.81; //  strut clamp length              (1.5inch)            
                   /// vpdg . sclength = 3.81; //  strut clamp length              (1.5inch)            
                   vpdg . scthick = 0.635; //  strut clamp thickness           (0.25inch)            
                   /// vpdg . scthick = 0.635; //  strut clamp thickness           (0.25inch)            
                   vpdg . clheight = 3.4925; //  clamp height                    (1.375inch)            
                   /// vpdg . clheight = 3.4925; //  clamp height                    (1.375inch)            
                   vpdg . clwidth = 3.81; //  clamp width                     (1.5inch)            
                   /// vpdg . clwidth = 3.81; //  clamp width                     (1.5inch)            
                   vpdg . cllength = 41.275; //  clamp length                    (16.25inch)            
                   /// vpdg . cllength = 41.275; //  clamp length                    (16.25inch)            
                   vpdg . clthick = 0.3175; //  clamp plate thickness           (0.125inch)            
                   /// vpdg . clthick = 0.3175; //  clamp plate thickness           (0.125inch)            
                   vpdg . detlen = 33.02; //  PMT assembly length             (13inch)            
                   /// vpdg . detlen = 33.02; //  PMT assembly length             (13inch)            
                   vpdg . detrad = 3.81; //  PMT assembly radius             (1.5inch)            
                   /// vpdg . detrad = 3.81; //  PMT assembly radius             (1.5inch)            
                   vpdg . detfront = 1.016; //  PMT ass. frontplate thickness   (0.4inch)            
                   /// vpdg . detfront = 1.016; //  PMT ass. frontplate thickness   (0.4inch)            
                   vpdg . convthk = 1.; //  Converter layer thickness            
                   /// vpdg . convthk = 1.; //  Converter layer thickness            
                   vpdg . radithk = 1.; //  Radiator layer thickness                  
                   /// vpdg . radithk = 1.; //  Radiator layer thickness                  
                   vpdg . eleleng = 15.0; //  electronics mount length            
                   /// vpdg . eleleng = 15.0; //  electronics mount length            
                   vpdg . drlayer = 6.; //  layer radial width            
                   /// vpdg . drlayer = 6.; //  layer radial width            
                   vpdg . numpmt = 3; //  number of PMT in layer            
                   /// vpdg . numpmt = 3; //  number of PMT in layer            
                   vpdg . pmtwall = 0.1; //  PMT wall thickness            
                   /// vpdg . pmtwall = 0.1; //  PMT wall thickness            
                   vpdg . pmtrad = 2.54; //  PMT and detector radius         (1inch)            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius         (1inch)            
                   vpdg . pmtlen = 8.0; //  PMT tube length             
                   /// vpdg . pmtlen = 8.0; //  PMT tube length             
                   vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   /// vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   vpdg . ibposyc = -16.51; //  IBeam central Ylocation         (6.5inch)            
                   /// vpdg . ibposyc = -16.51; //  IBeam central Ylocation         (6.5inch)            
                   vpdg . ibposzc = 530.477; //  IBeam central Zposition            
                   /// vpdg . ibposzc = 530.477; //  IBeam central Zposition            
                   vpdg . ibleng = 294.894; //  IBeam length                    (116.1inch)            
                   /// vpdg . ibleng = 294.894; //  IBeam length                    (116.1inch)            
                   vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness    (0.29inch)            
                   /// vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness    (0.29inch)            
                   vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness     (0.17inch)            
                   /// vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness     (0.17inch)            
                   vpdg . ibheight = 10.16; //  IBeam height                    (4inch)            
                   /// vpdg . ibheight = 10.16; //  IBeam height                    (4inch)            
                   vpdg . ibwidth = 7.62; //  IBeam width                     (3inch)            
                   /// vpdg . ibwidth = 7.62; //  IBeam width                     (3inch)            
                   vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   /// vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   //           
                   vpdg.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdg_doc        
             ///@{           
                   ++vpdg._index;           
                   vpdg . version = 4; //  geometry version            
                   /// vpdg . version = 4; //  geometry version            
                   vpdg . zposeast = 574.5688; //  Z position East            
                   /// vpdg . zposeast = 574.5688; //  Z position East            
                   vpdg . zposwest = 573.5669; //  Z position West            
                   /// vpdg . zposwest = 573.5669; //  Z position West            
                   vpdg . rmin = 6.35; //  mothervolume rmin               (2.5inch)            
                   /// vpdg . rmin = 6.35; //  mothervolume rmin               (2.5inch)            
                   vpdg . rmax = 31.27375; //  mothervolume rmin               (12.3125inch)            
                   /// vpdg . rmax = 31.27375; //  mothervolume rmin               (12.3125inch)            
                   vpdg . bpwidth = 30.48; //  baseplate width                 (12inch)            
                   /// vpdg . bpwidth = 30.48; //  baseplate width                 (12inch)            
                   vpdg . bplength = 46.355; //  baseplate length                (18.5inch)            
                   /// vpdg . bplength = 46.355; //  baseplate length                (18.5inch)            
                   vpdg . bpthick = 0.635; //  baseplate thickness             (0.25inch)            
                   /// vpdg . bpthick = 0.635; //  baseplate thickness             (0.25inch)            
                   vpdg . bxheight = 5.08; //  FEE box height                  (2inch)            
                   /// vpdg . bxheight = 5.08; //  FEE box height                  (2inch)            
                   vpdg . bxlength = 15.24; //  FEE box length                  (6inch)            
                   /// vpdg . bxlength = 15.24; //  FEE box length                  (6inch)            
                   vpdg . bxwidth = 25.4; //  FEE box width                   (10inch)            
                   /// vpdg . bxwidth = 25.4; //  FEE box width                   (10inch)            
                   vpdg . bxthick = 0.635; //  FEE box plate thickness         (0.25inch)            
                   /// vpdg . bxthick = 0.635; //  FEE box plate thickness         (0.25inch)            
                   vpdg . bxzposc = 0.635; //  FEE central z pos (+/-??)       (0.25inch)            
                   /// vpdg . bxzposc = 0.635; //  FEE central z pos (+/-??)       (0.25inch)            
                   vpdg . fpwidth = 7.62; //  frontplate width                (3inch)            
                   /// vpdg . fpwidth = 7.62; //  frontplate width                (3inch)            
                   vpdg . fpheight = 25.45842; //  frontplate height               (10.023inch)            
                   /// vpdg . fpheight = 25.45842; //  frontplate height               (10.023inch)            
                   vpdg . fpthick = 2.54; //  frontplate thickness            (1inch)            
                   /// vpdg . fpthick = 2.54; //  frontplate thickness            (1inch)            
                   vpdg . fpawidth = 6.63956; //  frontpl.part A width            (2.614inch)            
                   /// vpdg . fpawidth = 6.63956; //  frontpl.part A width            (2.614inch)            
                   vpdg . fpahght = 8.35405; //  frontpl.part A height           (3.289inch)            
                   /// vpdg . fpahght = 8.35405; //  frontpl.part A height           (3.289inch)            
                   vpdg . fpchght = 12.573; //  frontpl.part C height           (4.95inch)            
                   /// vpdg . fpchght = 12.573; //  frontpl.part C height           (4.95inch)            
                   vpdg . fphhght = 3.81; //  frontpl. hook height            (1.5inch)            
                   /// vpdg . fphhght = 3.81; //  frontpl. hook height            (1.5inch)            
                   vpdg . fphwidth = 5.08; //  frontpl. hook width             (2inch)            
                   /// vpdg . fphwidth = 5.08; //  frontpl. hook width             (2inch)            
                   vpdg . fphthick = 0.635; //  frontpl. hook thickness         (0.25inch)            
                   /// vpdg . fphthick = 0.635; //  frontpl. hook thickness         (0.25inch)            
                   vpdg . stthick = 0.635; //  strut thickness                 (0.25inch)            
                   /// vpdg . stthick = 0.635; //  strut thickness                 (0.25inch)            
                   vpdg . stheight = 23.1775; //  strut height                    (9.125 inch)            
                   /// vpdg . stheight = 23.1775; //  strut height                    (9.125 inch)            
                   vpdg . stangle = 25.; //  strut angle (degr)            
                   /// vpdg . stangle = 25.; //  strut angle (degr)            
                   vpdg . stdiagsz = 5.08; //  diagnoal strut size             (2inch)            
                   /// vpdg . stdiagsz = 5.08; //  diagnoal strut size             (2inch)            
                   vpdg . scwidth = 7.62; //  strut clamp width               (3inch)            
                   /// vpdg . scwidth = 7.62; //  strut clamp width               (3inch)            
                   vpdg . scheight = 3.81; //  strut clamp height              (1.5inch)            
                   /// vpdg . scheight = 3.81; //  strut clamp height              (1.5inch)            
                   vpdg . sclength = 3.81; //  strut clamp length              (1.5inch)            
                   /// vpdg . sclength = 3.81; //  strut clamp length              (1.5inch)            
                   vpdg . scthick = 0.635; //  strut clamp thickness           (0.25inch)            
                   /// vpdg . scthick = 0.635; //  strut clamp thickness           (0.25inch)            
                   vpdg . clheight = 3.4925; //  clamp height                    (1.375inch)            
                   /// vpdg . clheight = 3.4925; //  clamp height                    (1.375inch)            
                   vpdg . clwidth = 3.81; //  clamp width                     (1.5inch)            
                   /// vpdg . clwidth = 3.81; //  clamp width                     (1.5inch)            
                   vpdg . cllength = 41.275; //  clamp length                    (16.25inch)            
                   /// vpdg . cllength = 41.275; //  clamp length                    (16.25inch)            
                   vpdg . clthick = 0.3175; //  clamp plate thickness           (0.125inch)            
                   /// vpdg . clthick = 0.3175; //  clamp plate thickness           (0.125inch)            
                   vpdg . detlen = 33.02; //  PMT assembly length             (13inch)            
                   /// vpdg . detlen = 33.02; //  PMT assembly length             (13inch)            
                   vpdg . detrad = 3.81; //  PMT assembly radius             (1.5inch)            
                   /// vpdg . detrad = 3.81; //  PMT assembly radius             (1.5inch)            
                   vpdg . detfront = 1.016; //  PMT ass. frontplate thickness   (0.4inch)            
                   /// vpdg . detfront = 1.016; //  PMT ass. frontplate thickness   (0.4inch)            
                   vpdg . convthk = 1.; //  Converter layer thickness            
                   /// vpdg . convthk = 1.; //  Converter layer thickness            
                   vpdg . radithk = 1.; //  Radiator layer thickness                  
                   /// vpdg . radithk = 1.; //  Radiator layer thickness                  
                   vpdg . eleleng = 15.0; //  electronics mount length            
                   /// vpdg . eleleng = 15.0; //  electronics mount length            
                   vpdg . drlayer = 6.; //  layer radial width            
                   /// vpdg . drlayer = 6.; //  layer radial width            
                   vpdg . numpmt = 3; //  number of PMT in layer            
                   /// vpdg . numpmt = 3; //  number of PMT in layer            
                   vpdg . pmtwall = 0.1; //  PMT wall thickness            
                   /// vpdg . pmtwall = 0.1; //  PMT wall thickness            
                   vpdg . pmtrad = 2.54; //  PMT and detector radius         (1inch)            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius         (1inch)            
                   vpdg . pmtlen = 8.0; //  PMT tube length             
                   /// vpdg . pmtlen = 8.0; //  PMT tube length             
                   vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   /// vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   vpdg . ibposyc = -16.51; //  IBeam central Ylocation         (6.5inch)            
                   /// vpdg . ibposyc = -16.51; //  IBeam central Ylocation         (6.5inch)            
                   vpdg . ibposzc = 530.477; //  IBeam central Zposition            
                   /// vpdg . ibposzc = 530.477; //  IBeam central Zposition            
                   vpdg . ibleng = 294.894; //  IBeam length                    (116.1inch)            
                   /// vpdg . ibleng = 294.894; //  IBeam length                    (116.1inch)            
                   vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness    (0.29inch)            
                   /// vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness    (0.29inch)            
                   vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness     (0.17inch)            
                   /// vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness     (0.17inch)            
                   vpdg . ibheight = 10.16; //  IBeam height                    (4inch)            
                   /// vpdg . ibheight = 10.16; //  IBeam height                    (4inch)            
                   vpdg . ibwidth = 7.62; //  IBeam width                     (3inch)            
                   /// vpdg . ibwidth = 7.62; //  IBeam width                     (3inch)            
                   vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   /// vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   //           
                   vpdg.fill();           
             ///@}        
             //        
             /// USE vpdv _index=1;        
             vpdv.Use();        
             /// USE vpdg version=vpdv.vpdconfig;        
             vpdg.Use("version",(Float_t)vpdv.vpdconfig);        
             _create = AgCreate("VPDD");        
             {           
                   AgShape myshape; // undefined shape           
                   ///Create VPDD           
                   Create("VPDD");            
             }        
             zpos = vpdg.zposwest;        
             { AgPlacement place = AgPlacement("VPDD","CAVE");           
                   /// Add daughter volume VPDD to mother CAVE           
                   place.TranslateZ(+zpos);           
                   /// Translate z = +zpos           
                   place.par("only")=AgPlacement::kMany;           
                   /// Overlap: agplacement::kmany           
                   _stacker -> Position( AgBlock::Find("VPDD"), place );           
             } // end placement of VPDD        
             zpos = vpdg.zposeast;        
             { AgPlacement place = AgPlacement("VPDD","CAVE");           
                   /// Add daughter volume VPDD to mother CAVE           
                   place.TranslateZ(-zpos);           
                   /// Translate z = -zpos           
                   place.par("only")=AgPlacement::kMany;           
                   /// Overlap: agplacement::kmany           
                   /// G3 Reference: thetax = 90           
                   /// G3 Reference: phix = 0           
                   /// G3 Reference: thetay = 90           
                   /// G3 Reference: phiy = 90           
                   /// G3 Reference: thetaz = 180           
                   /// G3 Reference: phiz = 0           
                   Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;           
                   place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );           
                   _stacker -> Position( AgBlock::Find("VPDD"), place );           
             } // end placement of VPDD        
             if ( vpdg.ibchoice!=0 )        
             {           
                   { AgPlacement place = AgPlacement("IBEM","CAVE");              
                         /// Add daughter volume IBEM to mother CAVE              
                         place.TranslateY(vpdg.ibposyc);              
                         /// Translate y = vpdg.ibposyc              
                         place.TranslateZ(+vpdg.ibposzc);              
                         /// Translate z = +vpdg.ibposzc              
                         _stacker -> Position( AgBlock::Find("IBEM"), place );              
                   } // end placement of IBEM           
                   { AgPlacement place = AgPlacement("IBEM","CAVE");              
                         /// Add daughter volume IBEM to mother CAVE              
                         place.TranslateY(vpdg.ibposyc);              
                         /// Translate y = vpdg.ibposyc              
                         place.TranslateZ(-vpdg.ibposzc);              
                         /// Translate z = -vpdg.ibposzc              
                         /// G3 Reference: thetax = 90              
                         /// G3 Reference: phix = 0              
                         /// G3 Reference: thetay = 90              
                         /// G3 Reference: phiy = 90              
                         /// G3 Reference: thetaz = 180              
                         /// G3 Reference: phiz = 0              
                         Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;              
                         place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                         _stacker -> Position( AgBlock::Find("IBEM"), place );              
                   } // end placement of IBEM           
             }        
       }; // VpddGeo1     
 }; // namespace VpddGeo1  
 