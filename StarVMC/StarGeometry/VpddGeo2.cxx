#include "VpddGeo2.h"  
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
 namespace VPDDGEO2 // $NMSPC  
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
          ///Float_t vpdconfig;     
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
          ///Float_t ewshift;     
          ///Float_t udshift;     
          ///Float_t boltshift;     
          ///Int_t _index;     
          //     
          Vpdg_t vpdg;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup vpdh_doc     
          /// \class Vpdh_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t zposeast;     
          ///Float_t zposwest;     
          ///Float_t rmin;     
          ///Float_t rmax;     
          ///Float_t length;     
          ///Float_t detrad;     
          ///Float_t detlen;     
          ///Float_t pmtrad;     
          ///Float_t pmtlen;     
          ///Float_t detwall;     
          ///Float_t detfront;     
          ///Float_t leadthick;     
          ///Float_t scintthick;     
          ///Float_t ring1_ndet;     
          ///Float_t ring1_rad;     
          ///Float_t ring1_phi0;     
          ///Float_t ring1_dphi;     
          ///Float_t ring1_kproj;     
          ///Float_t ring2_ndet;     
          ///Float_t ring2_rad;     
          ///Float_t ring2_phi0;     
          ///Float_t ring2_dphi;     
          ///Float_t ring2_kproj;     
          ///Float_t ring3_ndet;     
          ///Float_t ring3_rad;     
          ///Float_t ring3_phi0;     
          ///Float_t ring3_dphi;     
          ///Float_t ring3_kproj;     
          ///Float_t ewshift;     
          ///Float_t udshift;     
          ///Float_t boltshift;     
          ///Int_t _index;     
          //     
          Vpdh_t vpdh;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup vpds_doc     
          /// \class Vpds_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t ibsazc;     
          ///Float_t ibsayc;     
          ///Float_t ibsaxc;     
          ///Float_t ibsbzc;     
          ///Float_t ibsbyc;     
          ///Float_t ibsbxc;     
          ///Float_t ibsczc;     
          ///Float_t ibscyc;     
          ///Float_t ibscxc;     
          ///Float_t ibsdzc1;     
          ///Float_t ibsdzc2;     
          ///Float_t ibsdyc1;     
          ///Float_t ibsdyc2;     
          ///Float_t ibsdxc;     
          ///Float_t ibsezc1;     
          ///Float_t ibsezc2;     
          ///Float_t ibseyc;     
          ///Float_t ibsexc;     
          ///Float_t ibsfzc;     
          ///Float_t ibsfyc;     
          ///Float_t ibsfxc;     
          ///Float_t ibsgzc1;     
          ///Float_t ibsgzc2;     
          ///Float_t ibsgzc3;     
          ///Float_t ibsgyc;     
          ///Float_t ibsgxc;     
          ///Float_t ibshzc1;     
          ///Float_t ibshzc2;     
          ///Float_t ibshyc;     
          ///Float_t ibshxc1;     
          ///Float_t ibshxc2;     
          ///Float_t bsalenx;     
          ///Float_t bsaleny;     
          ///Float_t bsalenz;     
          ///Float_t baalenz;     
          ///Float_t bsbleny;     
          ///Float_t bsclenx;     
          ///Float_t bscleny;     
          ///Float_t bsclenz;     
          ///Float_t baclenz;     
          ///Float_t bsdlenx;     
          ///Float_t bseleny;     
          ///Float_t bselenz;     
          ///Float_t bsfrmax;     
          ///Float_t bsflenz;     
          ///Float_t bsslenz;     
          ///Float_t bsgrmax;     
          ///Float_t bsglenz1;     
          ///Float_t bsglenz2;     
          ///Float_t bsglenz3;     
          ///Float_t bshlenz;     
          ///Float_t elecwid;     
          ///Float_t electhck;     
          ///Float_t eleclen;     
          ///Float_t vfeeposx;     
          ///Float_t vfeeposy;     
          ///Float_t vfeeposz;     
          ///Array_t<Float_t> vlemposx;     
          ///Float_t vlemposy;     
          ///Array_t<Float_t> vlemposz;     
          ///Float_t vlemlenx;     
          ///Float_t vlemleny;     
          ///Float_t vlemlenz;     
          ///Float_t vpipposx;     
          ///Float_t vpipposy;     
          ///Float_t vpipposz;     
          ///Float_t vpiprmin;     
          ///Float_t vpiprmax;     
          ///Float_t vpiplenz;     
          ///Int_t _index;     
          //     
          Vpds_t vpds;     
          //     
          ///@addtogroup VpddGeo2_vars     
          ///@{        
                Float_t ybase,ytop,convlength,detangle,strutheight,ydispl;        
                //        
                /// Float_t ybase,ytop,convlength,detangle,strutheight,ydispl        
          ///@}     
          ///@addtogroup VpddGeo2_vars     
          ///@{        
                Float_t xloc,yloc,zloc,zpos,tempos;        
                //        
                /// Float_t xloc,yloc,zloc,zpos,tempos        
          ///@}     
          ///@addtogroup VpddGeo2_vars     
          ///@{        
                Float_t zpose,zposw,ewshift,udshift,boltshift,locang,phiang,detzint;        
                //        
                /// Float_t zpose,zposw,ewshift,udshift,boltshift,locang,phiang,detzint        
          ///@}     
          ///@addtogroup VpddGeo2_vars     
          ///@{        
                Int_t isec;        
                //        
                /// Int_t isec        
          ///@}     
          ///@addtogroup VpddGeo2_vars     
          ///@{        
                Int_t kdetstyle,kibeamstyle;        
                //        
                /// Int_t kdetstyle,kibeamstyle        
          ///@}     
       VpddGeo2::VpddGeo2()     
         : AgModule("VpddGeo2","  is the StartDet and pipe support hardware ")     
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
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.par("serial")=zpos;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      if ( kdetstyle<2 )           
                      {              
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
                      }           
                      else           
                      {              
                            {  AgShape shape = AgShape("Tube");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("rmin")=vpdh.rmin;                 
                                  shape.par("rmax")=vpdh.rmax;                 
                                  shape.par("dz")=vpdh.length/2;                 
                                  /// Shape Tube rmin=vpdh.rmin rmax=vpdh.rmax dz=vpdh.length/2                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_VPDD;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      if ( kdetstyle<2 )           
                      {              
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
                            if ( vpdv.vpdconfig<4 )              
                            {                 
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
                            }              
                            else              
                            {                 
                                  _create = AgCreate("VPBX");                 
                                  {                    
                                        AgShape myshape; // undefined shape                    
                                        ///Create VPBX                    
                                        Create("VPBX");                     
                                  }                 
                                  { AgPlacement place = AgPlacement("VPBX","VPDD");                    
                                        /// Add daughter volume VPBX to mother VPDD                    
                                        place.TranslateX(-(vpdg.bpwidth+2.*vpdg.stthick+vpdg.bxheight)/2.);                    
                                        /// Translate x = -(vpdg.bpwidth+2.*vpdg.stthick+vpdg.bxheight)/2.                    
                                        place.TranslateY(-4);                    
                                        /// Translate y = -4                    
                                        /// G3 Reference: thetax = 150                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        Double_t _thetax=150,_phix=0,_thetay=90,_phiy=90,_thetaz=0,_phiz=0;                    
                                        place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                    
                                        place.AlphaZ(90);                    
                                        /// Rotate: AlphaZ = 90                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("VPBX"), place );                    
                                  } // end placement of VPBX                 
                            }              
                      }           
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
                      _create = AgCreate("VFEE");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create VFEE              
                            Create("VFEE");               
                      }           
                      { AgPlacement place = AgPlacement("VFEE","VPBI");              
                            /// Add daughter volume VFEE to mother VPBI              
                            place.TranslateX(vpds.vfeeposx);              
                            /// Translate x = vpds.vfeeposx              
                            place.TranslateY(vpds.vfeeposy);              
                            /// Translate y = vpds.vfeeposy              
                            place.TranslateZ(vpds.vfeeposz);              
                            /// Translate z = vpds.vfeeposz              
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
                            shape.par("dx")=vpds.elecwid/2;              
                            shape.par("dy")=vpds.electhck/2;              
                            shape.par("dz")=vpds.eleclen/2;              
                            /// Shape Bbox dx=vpds.elecwid/2 dy=vpds.electhck/2 dz=vpds.eleclen/2               
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
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(vpds.vlemposx(1));              
                            /// Translate x = vpds.vlemposx(1)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(1));              
                            /// Translate z = vpds.vlemposz(1)              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(vpds.vlemposx(2));              
                            /// Translate x = vpds.vlemposx(2)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(2));              
                            /// Translate z = vpds.vlemposz(2)              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(vpds.vlemposx(3));              
                            /// Translate x = vpds.vlemposx(3)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(3));              
                            /// Translate z = vpds.vlemposz(3)              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(vpds.vlemposx(4));              
                            /// Translate x = vpds.vlemposx(4)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(4));              
                            /// Translate z = vpds.vlemposz(4)              
                            _stacker -> Position( AgBlock::Find("VLEM"), place );              
                      } // end placement of VLEM           
                      { AgPlacement place = AgPlacement("VLEM","VFEE");              
                            /// Add daughter volume VLEM to mother VFEE              
                            place.TranslateX(vpds.vlemposx(6));              
                            /// Translate x = vpds.vlemposx(6)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(6));              
                            /// Translate z = vpds.vlemposz(6)              
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
                            place.TranslateX(vpds.vlemposx(7));              
                            /// Translate x = vpds.vlemposx(7)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(7));              
                            /// Translate z = vpds.vlemposz(7)              
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
                            place.TranslateX(vpds.vlemposx(8));              
                            /// Translate x = vpds.vlemposx(8)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(8));              
                            /// Translate z = vpds.vlemposz(8)              
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
                            place.TranslateX(vpds.vlemposx(9));              
                            /// Translate x = vpds.vlemposx(9)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(9));              
                            /// Translate z = vpds.vlemposz(9)              
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
                            place.TranslateX(vpds.vlemposx(11));              
                            /// Translate x = vpds.vlemposx(11)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(11));              
                            /// Translate z = vpds.vlemposz(11)              
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
                            place.TranslateX(vpds.vlemposx(12));              
                            /// Translate x = vpds.vlemposx(12)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(12));              
                            /// Translate z = vpds.vlemposz(12)              
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
                            place.TranslateX(vpds.vlemposx(13));              
                            /// Translate x = vpds.vlemposx(13)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(13));              
                            /// Translate z = vpds.vlemposz(13)              
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
                            place.TranslateX(vpds.vlemposx(14));              
                            /// Translate x = vpds.vlemposx(14)              
                            place.TranslateY(vpds.vlemposy);              
                            /// Translate y = vpds.vlemposy              
                            place.TranslateZ(vpds.vlemposz(14));              
                            /// Translate z = vpds.vlemposz(14)              
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
                            shape.par("dx")=vpds.vlemlenx/2.;              
                            shape.par("dy")=vpds.vlemleny/2.;              
                            shape.par("dz")=vpds.vlemlenz/2.;              
                            /// Shape Bbox dx=vpds.vlemlenx/2. dy=vpds.vlemleny/2. dz=vpds.vlemlenz/2.               
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
                            place.TranslateX(vpds.vpipposx);              
                            /// Translate x = vpds.vpipposx              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(vpds.vpipposz);              
                            /// Translate z = vpds.vpipposz              
                            place.par("dz")=vpds.vpiplenz/2;              
                            place.par("rmin")=vpds.vpiprmin;              
                            place.par("rmax")=vpds.vpiprmax;              
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
                      if ( kdetstyle<2 )           
                      {              
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
                      }           
                      else if ( kdetstyle==2 )           
                      {              
                            {  AgShape shape = AgShape("Tube");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("rmin")=vpdh.rmin;                 
                                  shape.par("rmax")=vpdh.rmax;                 
                                  shape.par("dz")=vpdh.length/2;                 
                                  /// Shape Tube rmin=vpdh.rmin rmax=vpdh.rmax dz=vpdh.length/2                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_VRNG;                 
                                  _stacker -> Build(this);                 
                            }              
                            _create = AgCreate("VDET");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create VDET                 
                                  Create("VDET");                  
                            }              
                            detzint = -(vpdh.detlen/2.0)+vpdh.detfront+(vpdh.leadthick+vpdh.scintthick);              
                            locang=0.;              
                            if ( vpdh.ring1_kproj>0 )              
                            {                 
                                  locang=degrad*0.;                 
                                  locang=atan((vpdh.ring1_rad)/(0.5*vpdh.zposwest+0.5*vpdh.zposeast+detzint));                 
                            }              
                            /// Loop on isec from 0 to vpdh.ring1_ndet-1 step=1              
                            for ( isec=0; (1>0)? (isec<=vpdh.ring1_ndet-1):(isec>=vpdh.ring1_ndet-1); isec+=1 )              
                            {                 
                                  phiang = degrad*(vpdh.ring1_phi0 + isec*vpdh.ring1_dphi);                 
                                  xloc   = (vpdh.ring1_rad+0.5*vpdh.detlen*sin(locang))*cos(phiang);                 
                                  yloc   = (vpdh.ring1_rad+0.5*vpdh.detlen*sin(locang))*sin(phiang);                 
                                  { AgPlacement place = AgPlacement("VDET","VRNG");                    
                                        /// Add daughter volume VDET to mother VRNG                    
                                        place.TranslateX(xloc);                    
                                        /// Translate x = xloc                    
                                        place.TranslateY(yloc);                    
                                        /// Translate y = yloc                    
                                        place.par("only")=AgPlacement::kMany;                    
                                        /// Overlap: agplacement::kmany                    
                                        /// G3 Reference: thetax = 90.+(cos(phiang)*locang)                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90.+(sin(phiang)*locang)                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        Double_t _thetax=90.+(cos(phiang)*locang),_phix=0,_thetay=90.+(sin(phiang)*locang),_phiy=90,_thetaz=0,_phiz=0;                    
                                        place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                    
                                        _stacker -> Position( AgBlock::Find("VDET"), place );                    
                                  } // end placement of VDET                 
                            }              
                            locang=0.;              
                            if ( vpdh.ring2_kproj>0 )              
                            {                 
                                  locang=degrad*4.;                 
                                  locang=atan((vpdh.ring2_rad)/(0.5*vpdh.zposwest+0.5*vpdh.zposeast+detzint));                 
                            }              
                            /// Loop on isec from 0 to vpdh.ring2_ndet-1 step=1              
                            for ( isec=0; (1>0)? (isec<=vpdh.ring2_ndet-1):(isec>=vpdh.ring2_ndet-1); isec+=1 )              
                            {                 
                                  phiang = degrad*(vpdh.ring2_phi0 + isec*vpdh.ring2_dphi);                 
                                  xloc   = (vpdh.ring2_rad+0.5*vpdh.detlen*sin(locang))*cos(phiang);                 
                                  yloc   = (vpdh.ring2_rad+0.5*vpdh.detlen*sin(locang))*sin(phiang);                 
                                  { AgPlacement place = AgPlacement("VDET","VRNG");                    
                                        /// Add daughter volume VDET to mother VRNG                    
                                        place.TranslateX(xloc);                    
                                        /// Translate x = xloc                    
                                        place.TranslateY(yloc);                    
                                        /// Translate y = yloc                    
                                        place.par("only")=AgPlacement::kMany;                    
                                        /// Overlap: agplacement::kmany                    
                                        /// G3 Reference: thetax = 90.+(cos(phiang)*locang)                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90.+(sin(phiang)*locang)                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        Double_t _thetax=90.+(cos(phiang)*locang),_phix=0,_thetay=90.+(sin(phiang)*locang),_phiy=90,_thetaz=0,_phiz=0;                    
                                        place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                    
                                        _stacker -> Position( AgBlock::Find("VDET"), place );                    
                                  } // end placement of VDET                 
                            }              
                            locang=0.;              
                            if ( vpdh.ring3_kproj>0 )              
                            {                 
                                  locang=degrad*8.;                 
                                  locang=atan((vpdh.ring3_rad)/(0.5*vpdh.zposwest+0.5*vpdh.zposeast+detzint));                 
                            }              
                            /// Loop on isec from 0 to vpdh.ring3_ndet-1 step=1              
                            for ( isec=0; (1>0)? (isec<=vpdh.ring3_ndet-1):(isec>=vpdh.ring3_ndet-1); isec+=1 )              
                            {                 
                                  phiang = degrad*(vpdh.ring3_phi0 + isec*vpdh.ring3_dphi);                 
                                  xloc   = (vpdh.ring3_rad+0.5*vpdh.detlen*sin(locang))*cos(phiang);                 
                                  yloc   = (vpdh.ring3_rad+0.5*vpdh.detlen*sin(locang))*sin(phiang);                 
                                  { AgPlacement place = AgPlacement("VDET","VRNG");                    
                                        /// Add daughter volume VDET to mother VRNG                    
                                        place.TranslateX(xloc);                    
                                        /// Translate x = xloc                    
                                        place.TranslateY(yloc);                    
                                        /// Translate y = yloc                    
                                        place.par("only")=AgPlacement::kMany;                    
                                        /// Overlap: agplacement::kmany                    
                                        /// G3 Reference: thetax = 90.+(cos(phiang)*locang)                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90.+(sin(phiang)*locang)                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        Double_t _thetax=90.+(cos(phiang)*locang),_phix=0,_thetay=90.+(sin(phiang)*locang),_phiy=90,_thetaz=0,_phiz=0;                    
                                        place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                    
                                        _stacker -> Position( AgBlock::Find("VDET"), place );                    
                                  } // end placement of VDET                 
                            }              
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
                      ydispl=vpdg.detrad - sqrt(vpdg.detrad*vpdg.detrad -             (vpdg.clwidth/2-vpdg.clthick)*(vpdg.clwidth/2-vpdg.clthick));           
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
                                  place.AlphaZ(180);                 
                                  /// Rotate: AlphaZ = 180                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
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
                      if ( kdetstyle<2 )           
                      {              
                            /// Material IRON               
                            {  AgMaterial mat = AgMaterial::CopyMaterial("Iron");                 
                                  _material = mat;                 
                            }              
                            { AgAttribute attr = AgAttribute("VDET");                 
                                  attr.par("seen")=1;                 
                                  attr.par("colo")=1;                 
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
                      }           
                      else if ( kdetstyle==2 )           
                      {              
                            /// Material Aluminium               
                            {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");                 
                                  _material = mat;                 
                            }              
                            { AgAttribute attr = AgAttribute("VDET");                 
                                  attr.par("seen")=1;                 
                                  attr.par("colo")=1;                 
                                  attr.par("serial")=0;                 
                                  attr.Inherit( AgBlock::previous() );                  
                                  _attribute = attr;                 
                            }              
                            {  AgShape shape = AgShape("Tube");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("rmin")=0;                 
                                  shape.par("rmax")=vpdh.detrad;                 
                                  shape.par("dz")=vpdh.detlen/2;                 
                                  /// Shape Tube rmin=0 rmax=vpdh.detrad dz=vpdh.detlen/2                  
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
                                  place.TranslateZ(0);                 
                                  /// Translate z = 0                 
                                  _stacker -> Position( AgBlock::Find("VDTI"), place );                 
                            } // end placement of VDTI              
                      }           
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
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      if ( kdetstyle<2 )           
                      {              
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
                      }           
                      else if ( kdetstyle==2 )           
                      {              
                            {  AgShape shape = AgShape("Tube");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("rmin")=0;                 
                                  shape.par("rmax")=vpdh.detrad-vpdh.detwall;                 
                                  shape.par("dz")=(vpdh.detlen/2.)-(2.0*vpdh.detfront);                 
                                  /// Shape Tube rmin=0 rmax=vpdh.detrad-vpdh.detwall dz=(vpdh.detlen/2.)-(2.0*vpdh.detfront)                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_VDTI;                 
                                  _stacker -> Build(this);                 
                            }              
                            _create = AgCreate("VCNV");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create VCNV                 
                                  Create("VCNV");                  
                            }              
                            { AgPlacement place = AgPlacement("VCNV","VDTI");                 
                                  /// Add daughter volume VCNV to mother VDTI                 
                                  place.TranslateX(0);                 
                                  /// Translate x = 0                 
                                  place.TranslateZ(-(vpdh.detlen/2.0)+vpdh.detfront+(vpdh.leadthick+vpdh.scintthick));                 
                                  /// Translate z = -(vpdh.detlen/2.0)+vpdh.detfront+(vpdh.leadthick+vpdh.scintthick)                 
                                  _stacker -> Position( AgBlock::Find("VCNV"), place );                 
                            } // end placement of VCNV              
                      }           
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
                      if ( kdetstyle<2 )           
                      {              
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
                      }           
                      else if ( kdetstyle==2 )           
                      {              
                            {  AgShape shape = AgShape("Tube");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("rmin")=0;                 
                                  shape.par("rmax")=vpdh.pmtrad;                 
                                  shape.par("dz")=(vpdh.leadthick+vpdh.scintthick)/2.;                 
                                  /// Shape Tube rmin=0 rmax=vpdh.pmtrad dz=(vpdh.leadthick+vpdh.scintthick)/2.                  
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
                                  place.TranslateZ(vpdh.leadthick/2.);                 
                                  /// Translate z = vpdh.leadthick/2.                 
                                  _stacker -> Position( AgBlock::Find("VRAD"), place );                 
                            } // end placement of VRAD              
                      }           
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
                      if ( kdetstyle<2 )           
                      {              
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
                      }           
                      else if ( kdetstyle==2 )           
                      {              
                            {  AgShape shape = AgShape("Tube");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("dz")=vpdh.scintthick/2.;                 
                                  /// Shape Tube dz=vpdh.scintthick/2.                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_VRAD;                 
                                  _stacker -> Build(this);                 
                            }              
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
                            attr.par("fill")=7;              
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
                            attr.par("fill")=7;              
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
                            attr.par("fill")=7;              
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
          // ---------------------------------------------------------------------------------------------------     
          void IBSA::Block( AgCreate create )     
          {         
                ///@addtogroup IBSA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBSA");              
                            attr.par("seen")=0;              
                            attr.par("colo")=5;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.bsalenx/2.;              
                            shape.par("dy")=vpds.bsaleny/2.;              
                            shape.par("dz")=vpds.bsalenz/2.;              
                            /// Shape Bbox dx=vpds.bsalenx/2. dy=vpds.bsaleny/2. dz=vpds.bsalenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBSA;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("IBAA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create IBAA              
                            Create("IBAA");               
                      }           
                      { AgPlacement place = AgPlacement("IBAA","IBSA");              
                            /// Add daughter volume IBAA to mother IBSA              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateZ(-(vpds.bsalenx-vpds.baalenz)/2.);              
                            /// Translate z = -(vpds.bsalenx-vpds.baalenz)/2.              
                            _stacker -> Position( AgBlock::Find("IBAA"), place );              
                      } // end placement of IBAA           
                      { AgPlacement place = AgPlacement("IBAA","IBSA");              
                            /// Add daughter volume IBAA to mother IBSA              
                            place.TranslateX(-(vpds.bsalenx-vpds.baalenz)/2.);              
                            /// Translate x = -(vpds.bsalenx-vpds.baalenz)/2.              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            place.AlphaY(90);              
                            /// Rotate: AlphaY = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("IBAA"), place );              
                      } // end placement of IBAA           
                      END_OF_IBSA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBSA     
          // ---------------------------------------------------------------------------------------------------     
          void IBAA::Block( AgCreate create )     
          {         
                ///@addtogroup IBAA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBAA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.par("fill")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.bsalenx/2.;              
                            shape.par("dy")=vpds.bsaleny/2.;              
                            shape.par("dz")=vpds.baalenz/2.;              
                            /// Shape Bbox dx=vpds.bsalenx/2. dy=vpds.bsaleny/2. dz=vpds.baalenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBAA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBAA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBAA     
          // ---------------------------------------------------------------------------------------------------     
          void IBSB::Block( AgCreate create )     
          {         
                ///@addtogroup IBSB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBSB");              
                            attr.par("seen")=0;              
                            attr.par("colo")=5;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.bsalenx/2.;              
                            shape.par("dy")=vpds.bsbleny/2.;              
                            shape.par("dz")=vpds.bsalenz/2.;              
                            /// Shape Bbox dx=vpds.bsalenx/2. dy=vpds.bsbleny/2. dz=vpds.bsalenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBSB;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("IBAB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create IBAB              
                            Create("IBAB");               
                      }           
                      { AgPlacement place = AgPlacement("IBAB","IBSB");              
                            /// Add daughter volume IBAB to mother IBSB              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateZ((vpds.bsalenx-vpds.baalenz)/2.);              
                            /// Translate z = (vpds.bsalenx-vpds.baalenz)/2.              
                            _stacker -> Position( AgBlock::Find("IBAB"), place );              
                      } // end placement of IBAB           
                      { AgPlacement place = AgPlacement("IBAB","IBSB");              
                            /// Add daughter volume IBAB to mother IBSB              
                            place.TranslateX(-(vpds.bsalenx-vpds.baalenz)/2.);              
                            /// Translate x = -(vpds.bsalenx-vpds.baalenz)/2.              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            place.AlphaY(90);              
                            /// Rotate: AlphaY = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("IBAB"), place );              
                      } // end placement of IBAB           
                      END_OF_IBSB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBSB     
          // ---------------------------------------------------------------------------------------------------     
          void IBAB::Block( AgCreate create )     
          {         
                ///@addtogroup IBAB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBAB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.par("fill")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.bsalenx/2.;              
                            shape.par("dy")=vpds.bsbleny/2.;              
                            shape.par("dz")=vpds.baalenz/2.;              
                            /// Shape Bbox dx=vpds.bsalenx/2. dy=vpds.bsbleny/2. dz=vpds.baalenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBAB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBAB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBAB     
          // ---------------------------------------------------------------------------------------------------     
          void IBSC::Block( AgCreate create )     
          {         
                ///@addtogroup IBSC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBSC");              
                            attr.par("seen")=0;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.bsclenx/2.;              
                            shape.par("dy")=vpds.bscleny/2.;              
                            shape.par("dz")=vpds.bsclenz/2.;              
                            /// Shape Bbox dx=vpds.bsclenx/2. dy=vpds.bscleny/2. dz=vpds.bsclenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBSC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("IBAC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create IBAC              
                            Create("IBAC");               
                      }           
                      { AgPlacement place = AgPlacement("IBAC","IBSC");              
                            /// Add daughter volume IBAC to mother IBSC              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(+(vpds.bsclenz-vpds.baclenz)/2.);              
                            /// Translate z = +(vpds.bsclenz-vpds.baclenz)/2.              
                            _stacker -> Position( AgBlock::Find("IBAC"), place );              
                      } // end placement of IBAC           
                      { AgPlacement place = AgPlacement("IBAC","IBSC");              
                            /// Add daughter volume IBAC to mother IBSC              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(-(vpds.bsclenz-vpds.baclenz)/2.);              
                            /// Translate z = -(vpds.bsclenz-vpds.baclenz)/2.              
                            _stacker -> Position( AgBlock::Find("IBAC"), place );              
                      } // end placement of IBAC           
                      _create = AgCreate("IBBC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create IBBC              
                            Create("IBBC");               
                      }           
                      { AgPlacement place = AgPlacement("IBBC","IBSC");              
                            /// Add daughter volume IBBC to mother IBSC              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY((vpds.bscleny-vpds.baclenz)/2.);              
                            /// Translate y = (vpds.bscleny-vpds.baclenz)/2.              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            _stacker -> Position( AgBlock::Find("IBBC"), place );              
                      } // end placement of IBBC           
                      _create = AgCreate("IBCC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create IBCC              
                            Create("IBCC");               
                      }           
                      { AgPlacement place = AgPlacement("IBCC","IBSC");              
                            /// Add daughter volume IBCC to mother IBSC              
                            place.TranslateX(+(vpds.bsclenx-vpds.baclenz)/2.);              
                            /// Translate x = +(vpds.bsclenx-vpds.baclenz)/2.              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            _stacker -> Position( AgBlock::Find("IBCC"), place );              
                      } // end placement of IBCC           
                      _create = AgCreate("IBCC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create IBCC              
                            Create("IBCC");               
                      }           
                      { AgPlacement place = AgPlacement("IBCC","IBSC");              
                            /// Add daughter volume IBCC to mother IBSC              
                            place.TranslateX(-(vpds.bsclenx-vpds.baclenz)/2.);              
                            /// Translate x = -(vpds.bsclenx-vpds.baclenz)/2.              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            _stacker -> Position( AgBlock::Find("IBCC"), place );              
                      } // end placement of IBCC           
                      END_OF_IBSC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBSC     
          // ---------------------------------------------------------------------------------------------------     
          void IBAC::Block( AgCreate create )     
          {         
                ///@addtogroup IBAC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBAC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.par("fill")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.bsclenx/2.-vpds.baclenz;              
                            shape.par("dy")=vpds.bscleny/2;              
                            shape.par("dz")=vpds.baclenz/2.;              
                            /// Shape Bbox dx=vpds.bsclenx/2.-vpds.baclenz dy=vpds.bscleny/2 dz=vpds.baclenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBAC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBAC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBAC     
          // ---------------------------------------------------------------------------------------------------     
          void IBBC::Block( AgCreate create )     
          {         
                ///@addtogroup IBBC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBBC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.par("fill")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.bsclenx/2.-vpds.baclenz;              
                            shape.par("dy")=vpds.baclenz/2.;              
                            shape.par("dz")=vpds.bsclenz/2.;              
                            /// Shape Bbox dx=vpds.bsclenx/2.-vpds.baclenz dy=vpds.baclenz/2. dz=vpds.bsclenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBBC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBBC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBBC     
          // ---------------------------------------------------------------------------------------------------     
          void IBCC::Block( AgCreate create )     
          {         
                ///@addtogroup IBCC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBCC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.par("fill")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.baclenz/2.;              
                            shape.par("dy")=vpds.bscleny/2.;              
                            shape.par("dz")=vpds.bsclenz/2.;              
                            /// Shape Bbox dx=vpds.baclenz/2. dy=vpds.bscleny/2. dz=vpds.bsclenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBCC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBCC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBCC     
          // ---------------------------------------------------------------------------------------------------     
          void IBSD::Block( AgCreate create )     
          {         
                ///@addtogroup IBSD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBSD");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.par("fill")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.bsdlenx/2.;              
                            shape.par("dy")=vpds.baclenz/2;              
                            shape.par("dz")=vpds.bsalenx/2.;              
                            /// Shape Bbox dx=vpds.bsdlenx/2. dy=vpds.baclenz/2 dz=vpds.bsalenx/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBSD;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBSD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBSD     
          // ---------------------------------------------------------------------------------------------------     
          void IBSE::Block( AgCreate create )     
          {         
                ///@addtogroup IBSE_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBSE");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.par("fill")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=vpds.baalenz/2.;              
                            shape.par("dy")=vpds.bseleny/2;              
                            shape.par("dz")=vpds.bselenz/2.;              
                            /// Shape Bbox dx=vpds.baalenz/2. dy=vpds.bseleny/2 dz=vpds.bselenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBSE;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBSE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBSE     
          // ---------------------------------------------------------------------------------------------------     
          void IBSF::Block( AgCreate create )     
          {         
                ///@addtogroup IBSF_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Iron            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Iron");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBSF");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=vpds.bsfrmax;              
                            shape.par("dz")=vpds.bsflenz/2.;              
                            /// Shape Tube rmin=0 rmax=vpds.bsfrmax dz=vpds.bsflenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBSF;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBSF:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBSF     
          // ---------------------------------------------------------------------------------------------------     
          void IBSS::Block( AgCreate create )     
          {         
                ///@addtogroup IBSS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Iron            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Iron");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBSS");              
                            attr.par("seen")=0;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=vpds.bsfrmax;              
                            shape.par("dz")=vpds.bsslenz/2.;              
                            /// Shape Tube rmin=0 rmax=vpds.bsfrmax dz=vpds.bsslenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBSS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBSS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBSS     
          // ---------------------------------------------------------------------------------------------------     
          void IBSG::Block( AgCreate create )     
          {         
                ///@addtogroup IBSG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Iron            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Iron");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBSG");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      if ( vpdv.vpdconfig<8 )           
                      {              
                            {  AgShape shape = AgShape("Tube");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("rmin")=0;                 
                                  shape.par("rmax")=vpds.bsgrmax;                 
                                  shape.par("dz")=vpds.bsglenz1/2.;                 
                                  /// Shape Tube rmin=0 rmax=vpds.bsgrmax dz=vpds.bsglenz1/2.                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_IBSG;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      else if ( vpdv.vpdconfig==8 )           
                      {              
                            {  AgShape shape = AgShape("Tube");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("rmin")=0;                 
                                  shape.par("rmax")=vpds.bsgrmax;                 
                                  shape.par("dz")=vpds.bsglenz2/2.;                 
                                  /// Shape Tube rmin=0 rmax=vpds.bsgrmax dz=vpds.bsglenz2/2.                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_IBSG;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      else           
                      {              
                            {  AgShape shape = AgShape("Tube");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("rmin")=0;                 
                                  shape.par("rmax")=vpds.bsgrmax;                 
                                  shape.par("dz")=vpds.bsglenz3/2.;                 
                                  /// Shape Tube rmin=0 rmax=vpds.bsgrmax dz=vpds.bsglenz3/2.                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_IBSG;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      END_OF_IBSG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBSG     
          // ---------------------------------------------------------------------------------------------------     
          void IBSH::Block( AgCreate create )     
          {         
                ///@addtogroup IBSH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Iron            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Iron");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("IBSH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=vpds.bsgrmax;              
                            shape.par("dz")=vpds.bshlenz/2.;              
                            /// Shape Tube rmin=0 rmax=vpds.bsgrmax dz=vpds.bshlenz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_IBSH;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_IBSH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block IBSH     
    // ----------------------------------------------------------------------- geoctr
       void VpddGeo2::ConstructGeometry( const Char_t *dummy )     
       {        
             ///@addtogroup VpddGeo2_revision        
             ///@{           
                   /// Author: W.J. Llope           
             ///@}        
             ///@addtogroup VpddGeo2_revision        
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
             AddBlock("IBSA");        
             AddBlock("IBSB");        
             AddBlock("IBSC");        
             AddBlock("IBSD");        
             AddBlock("IBSE");        
             AddBlock("IBSF");        
             AddBlock("IBSG");        
             AddBlock("IBSH");        
             AddBlock("IBAA");        
             AddBlock("IBAB");        
             AddBlock("IBAC");        
             AddBlock("IBSS");        
             AddBlock("IBBC");        
             AddBlock("IBCC");        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdv_doc        
             ///@{           
                   ++vpdv._index;           
                   vpdv . version = 2; //  default version (set in geometry.g)            
                   /// vpdv . version = 2; //  default version (set in geometry.g)            
                   vpdv . vpdconfig = 1; //  default config  (set in geometry.g)            
                   /// vpdv . vpdconfig = 1; //  default config  (set in geometry.g)            
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
                   vpdg . pmtrad = 2.54; //  PMT and detector radius            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius            
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
                   vpdg . ewshift = 0.0; //  east west z shift            
                   /// vpdg . ewshift = 0.0; //  east west z shift            
                   vpdg . udshift = 0.0; //  up down y shift            
                   /// vpdg . udshift = 0.0; //  up down y shift            
                   vpdg . boltshift = 0.0; //  Bolt additional y shift            
                   /// vpdg . boltshift = 0.0; //  Bolt additional y shift            
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
                   vpdg . bxzposc = 0.635; //  FEE central z pos       (0.25inch)            
                   /// vpdg . bxzposc = 0.635; //  FEE central z pos       (0.25inch)            
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
                   vpdg . pmtrad = 2.54; //  PMT and detector radius            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius            
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
                   vpdg . ewshift = 0.0; //  east west z shift            
                   /// vpdg . ewshift = 0.0; //  east west z shift            
                   vpdg . udshift = 0.0; //  up down y shift            
                   /// vpdg . udshift = 0.0; //  up down y shift            
                   vpdg . boltshift = 0.0; //  Bolt additional y shift            
                   /// vpdg . boltshift = 0.0; //  Bolt additional y shift            
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
                   vpdg . bxzposc = 0.635; //  FEE central z pos       (0.25inch)            
                   /// vpdg . bxzposc = 0.635; //  FEE central z pos       (0.25inch)            
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
                   vpdg . pmtrad = 2.54; //  PMT and detector radius            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius            
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
                   vpdg . ewshift = 0.0; //  east west z shift            
                   /// vpdg . ewshift = 0.0; //  east west z shift            
                   vpdg . udshift = 0.0; //  up down y shift            
                   /// vpdg . udshift = 0.0; //  up down y shift            
                   vpdg . boltshift = 0.0; //  Bolt additional y shift            
                   /// vpdg . boltshift = 0.0; //  Bolt additional y shift            
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
                   vpdg . bxzposc = 0.635; //  FEE central z pos       (0.25inch)            
                   /// vpdg . bxzposc = 0.635; //  FEE central z pos       (0.25inch)            
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
                   vpdg . pmtrad = 2.54; //  PMT and detector radius            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius            
                   vpdg . pmtlen = 8.0; //  PMT tube length            
                   /// vpdg . pmtlen = 8.0; //  PMT tube length            
                   vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   /// vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   vpdg . ibposyc = -16.51; //  IBeam central Ylocation           (6.5inch)            
                   /// vpdg . ibposyc = -16.51; //  IBeam central Ylocation           (6.5inch)            
                   vpdg . ibposzc = 530.477; //  IBeam central Zposition              
                   /// vpdg . ibposzc = 530.477; //  IBeam central Zposition              
                   vpdg . ibleng = 294.894; //  IBeam length                (116.1inch)             
                   /// vpdg . ibleng = 294.894; //  IBeam length                (116.1inch)             
                   vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness (0.29inch)            
                   /// vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness (0.29inch)            
                   vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness      (0.17inch)            
                   /// vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness      (0.17inch)            
                   vpdg . ibheight = 10.16; //  IBeam height                        (4inch)            
                   /// vpdg . ibheight = 10.16; //  IBeam height                        (4inch)            
                   vpdg . ibwidth = 7.62; //  IBeam width                                 (3inch)            
                   /// vpdg . ibwidth = 7.62; //  IBeam width                                 (3inch)            
                   vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   /// vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   vpdg . ewshift = 0.0; //  east west z shift            
                   /// vpdg . ewshift = 0.0; //  east west z shift            
                   vpdg . udshift = 0.0; //  up down y shift            
                   /// vpdg . udshift = 0.0; //  up down y shift            
                   vpdg . boltshift = 0.0; //  Bolt additional y shift            
                   /// vpdg . boltshift = 0.0; //  Bolt additional y shift            
                   //           
                   vpdg.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdg_doc        
             ///@{           
                   ++vpdg._index;           
                   vpdg . version = 5; //  geometry version    WJL ...used by Y2004Y            
                   /// vpdg . version = 5; //  geometry version    WJL ...used by Y2004Y            
                   vpdg . zposeast = 570.0; //  Z position East         WJL see next, plus add 3/4in to take care of E/W offset (was 574.5688)            
                   /// vpdg . zposeast = 570.0; //  Z position East         WJL see next, plus add 3/4in to take care of E/W offset (was 574.5688)            
                   vpdg . zposwest = 568.1; //  Z position West         WJL via CADD: 362.2+(194.3-11.6)+2.54*(18.25/2)=568.08  (was 573.5669)            
                   /// vpdg . zposwest = 568.1; //  Z position West         WJL via CADD: 362.2+(194.3-11.6)+2.54*(18.25/2)=568.08  (was 573.5669)            
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
                   vpdg . bxthick = 0.127; //  FEE box plate thickness         WJL should be 50mils;//;// MODIFIED (was 0.635)            
                   /// vpdg . bxthick = 0.127; //  FEE box plate thickness         WJL should be 50mils;//;// MODIFIED (was 0.635)            
                   vpdg . bxzposc = 0.635; //  FEE central z pos               (0.25inch)            
                   /// vpdg . bxzposc = 0.635; //  FEE central z pos               (0.25inch)            
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
                   vpdg . pmtrad = 2.54; //  PMT and detector radius            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius            
                   vpdg . pmtlen = 8.0; //  PMT tube length            
                   /// vpdg . pmtlen = 8.0; //  PMT tube length            
                   vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   /// vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   vpdg . ibposyc = -16.51; //  IBeam central Ypos      (6.5inch)            
                   /// vpdg . ibposyc = -16.51; //  IBeam central Ypos      (6.5inch)            
                   vpdg . ibposzc = 540.45; //  IBeam central Zpos      WJL should be 362.2+(12.125*2.54)+(IBLeng/2)=540.45 MODIFIED, NOTE EAST is 3/4in farther, add that offset in the code;//;//;//;//            
                   /// vpdg . ibposzc = 540.45; //  IBeam central Zpos      WJL should be 362.2+(12.125*2.54)+(IBLeng/2)=540.45 MODIFIED, NOTE EAST is 3/4in farther, add that offset in the code;//;//;//;//            
                   vpdg . ibleng = 294.894; //  IBeam length                (116.1inch)             
                   /// vpdg . ibleng = 294.894; //  IBeam length                (116.1inch)             
                   vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness (0.29inch)            
                   /// vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness (0.29inch)            
                   vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness      (0.17inch)            
                   /// vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness      (0.17inch)            
                   vpdg . ibheight = 10.16; //  IBeam height                        (4inch)            
                   /// vpdg . ibheight = 10.16; //  IBeam height                        (4inch)            
                   vpdg . ibwidth = 7.62; //  IBeam width                                 (3inch)            
                   /// vpdg . ibwidth = 7.62; //  IBeam width                                 (3inch)            
                   vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   /// vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   vpdg . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   /// vpdg . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   vpdg . udshift = 0.0; //  up down y shift            
                   /// vpdg . udshift = 0.0; //  up down y shift            
                   vpdg . boltshift = 0.0; //  Bolt additional y shift            
                   /// vpdg . boltshift = 0.0; //  Bolt additional y shift            
                   //           
                   vpdg.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdg_doc        
             ///@{           
                   ++vpdg._index;           
                   vpdg . version = 6; //  geometry version    WJL ...used by Y2005, Y2006A, Y2006B            
                   /// vpdg . version = 6; //  geometry version    WJL ...used by Y2005, Y2006A, Y2006B            
                   vpdg . zposeast = 583.806; //  Z position East         WJL from newer CADD: 220.720in+(18.25in/2)=229.845in              
                   /// vpdg . zposeast = 583.806; //  Z position East         WJL from newer CADD: 220.720in+(18.25in/2)=229.845in              
                   vpdg . zposwest = 583.488; //  Z position West         WJL from newer CADD: 220.595in+(18.25in/2)=229.720in            
                   /// vpdg . zposwest = 583.488; //  Z position West         WJL from newer CADD: 220.595in+(18.25in/2)=229.720in            
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
                   vpdg . bxthick = 0.127; //  FEE box plate thickness         WJL should be 50mils;//;// MODIFIED (was 0.635)            
                   /// vpdg . bxthick = 0.127; //  FEE box plate thickness         WJL should be 50mils;//;// MODIFIED (was 0.635)            
                   vpdg . bxzposc = 0.635; //  FEE central z pos               (0.25inch)            
                   /// vpdg . bxzposc = 0.635; //  FEE central z pos               (0.25inch)            
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
                   vpdg . pmtrad = 2.54; //  PMT and detector radius            
                   /// vpdg . pmtrad = 2.54; //  PMT and detector radius            
                   vpdg . pmtlen = 8.0; //  PMT tube length            
                   /// vpdg . pmtlen = 8.0; //  PMT tube length            
                   vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   /// vpdg . ibchoice = 1; //  active/de-activate (0) ibeam            
                   vpdg . ibposyc = -16.51; //  IBeam central Ypos      (6.5inch)            
                   /// vpdg . ibposyc = -16.51; //  IBeam central Ypos      (6.5inch)            
                   vpdg . ibposzc = 540.45; //  IBeam central Zpos      WJL should be 362.2+(12.125*2.54)+(IBLeng/2)=540.45 MODIFIED, NOTE EAST is 3/4in farther, add that offset in the code;//;//;//;//            
                   /// vpdg . ibposzc = 540.45; //  IBeam central Zpos      WJL should be 362.2+(12.125*2.54)+(IBLeng/2)=540.45 MODIFIED, NOTE EAST is 3/4in farther, add that offset in the code;//;//;//;//            
                   vpdg . ibleng = 294.894; //  IBeam length                (116.1inch)             
                   /// vpdg . ibleng = 294.894; //  IBeam length                (116.1inch)             
                   vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness (0.29inch)            
                   /// vpdg . ibthickh = 0.7366; //  IBeam horiz. plate thickness (0.29inch)            
                   vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness      (0.17inch)            
                   /// vpdg . ibthickv = 0.4318; //  IBeam vert. plate thickness      (0.17inch)            
                   vpdg . ibheight = 10.16; //  IBeam height                        (4inch)            
                   /// vpdg . ibheight = 10.16; //  IBeam height                        (4inch)            
                   vpdg . ibwidth = 7.62; //  IBeam width                                 (3inch)            
                   /// vpdg . ibwidth = 7.62; //  IBeam width                                 (3inch)            
                   vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   /// vpdg . ibwlen = 22.86; //  IBeam vert. front piece         (9inch)               
                   vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtf = 4.4489; //  IBeam vert. front piece height            
                   vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   /// vpdg . ibwhghtb = 8.3097; //  IBeam vert. front piece height            
                   vpdg . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   /// vpdg . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   vpdg . udshift = 0.0; //  up down y shift            
                   /// vpdg . udshift = 0.0; //  up down y shift            
                   vpdg . boltshift = 0.0; //  Bolt additional y shift            
                   /// vpdg . boltshift = 0.0; //  Bolt additional y shift            
                   //           
                   vpdg.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdh_doc        
             ///@{           
                   ++vpdh._index;           
                   vpdh . version = 7; //  geometry version       WJL ...used by Y2006A --- and future 2007 run            
                   /// vpdh . version = 7; //  geometry version       WJL ...used by Y2006A --- and future 2007 run            
                   vpdh . zposeast = 571.45; //  Z position East        (more or less arbitrary)            
                   /// vpdh . zposeast = 571.45; //  Z position East        (more or less arbitrary)            
                   vpdh . zposwest = 571.45; //  Z position West        (more or less arbitrary)            
                   /// vpdh . zposwest = 571.45; //  Z position West        (more or less arbitrary)            
                   vpdh . rmin = 6.6675; //  mothervolume rmin      (2 5/8in)            
                   /// vpdh . rmin = 6.6675; //  mothervolume rmin      (2 5/8in)            
                   vpdh . rmax = 16.51; //  mothervolume rmax      (6 1/2in)            
                   /// vpdh . rmax = 16.51; //  mothervolume rmax      (6 1/2in)            
                   vpdh . length = 32.; //  mothervolume length            
                   /// vpdh . length = 32.; //  mothervolume length            
                   vpdh . detrad = 2.54; //  det assy cylnder radius (2in diameter)            
                   /// vpdh . detrad = 2.54; //  det assy cylnder radius (2in diameter)            
                   vpdh . detlen = 20.32; //  det assy cylinder radius (8in)            
                   /// vpdh . detlen = 20.32; //  det assy cylinder radius (8in)            
                   vpdh . pmtrad = 1.905; //  pmt cylinder radius (1.5in diameter)            
                   /// vpdh . pmtrad = 1.905; //  pmt cylinder radius (1.5in diameter)            
                   vpdh . pmtlen = 1.905; //  pmt cylinder length (1.5in)            
                   /// vpdh . pmtlen = 1.905; //  pmt cylinder length (1.5in)            
                   vpdh . detwall = 0.127; //  det assy cylinder wall thickness (50mils)            
                   /// vpdh . detwall = 0.127; //  det assy cylinder wall thickness (50mils)            
                   vpdh . detfront = 0.3175; //  det assy front and back plate thicknesses (1/8in)            
                   /// vpdh . detfront = 0.3175; //  det assy front and back plate thicknesses (1/8in)            
                   vpdh . leadthick = 1.0; //  lead converter layer thickness (1cm)            
                   /// vpdh . leadthick = 1.0; //  lead converter layer thickness (1cm)            
                   vpdh . scintthick = 1.0; //    scintillator layer thickness (1cm)            
                   /// vpdh . scintthick = 1.0; //    scintillator layer thickness (1cm)            
                   vpdh . ring1_ndet = 10; //  upVPD number of tubes in ring 1            
                   /// vpdh . ring1_ndet = 10; //  upVPD number of tubes in ring 1            
                   vpdh . ring1_rad = 10.16; //  upVPD geo parameter (4in)            
                   /// vpdh . ring1_rad = 10.16; //  upVPD geo parameter (4in)            
                   vpdh . ring1_phi0 = -49.; //  upVPD geo parameter            
                   /// vpdh . ring1_phi0 = -49.; //  upVPD geo parameter            
                   vpdh . ring1_dphi = 31.; //  upVPD geo parameter            
                   /// vpdh . ring1_dphi = 31.; //  upVPD geo parameter            
                   vpdh . ring1_kproj = 0; //  upVPD geo parameter            
                   /// vpdh . ring1_kproj = 0; //  upVPD geo parameter            
                   vpdh . ring2_ndet = 9; //  upVPD number of tubes in ring 2            
                   /// vpdh . ring2_ndet = 9; //  upVPD number of tubes in ring 2            
                   vpdh . ring2_rad = 14.2875; //  upVPD geo parameter (5 5/8in)            
                   /// vpdh . ring2_rad = 14.2875; //  upVPD geo parameter (5 5/8in)            
                   vpdh . ring2_phi0 = -33.5; //  upVPD geo parameter            
                   /// vpdh . ring2_phi0 = -33.5; //  upVPD geo parameter            
                   vpdh . ring2_dphi = 31.; //  upVPD geo parameter            
                   /// vpdh . ring2_dphi = 31.; //  upVPD geo parameter            
                   vpdh . ring2_kproj = 0; //  upVPD geo parameter            
                   /// vpdh . ring2_kproj = 0; //  upVPD geo parameter            
                   vpdh . ring3_ndet = 0; //  upVPD number of tubes in ring 3            
                   /// vpdh . ring3_ndet = 0; //  upVPD number of tubes in ring 3            
                   vpdh . ring3_rad = 99.; //  upVPD geo parameter (5 5/8in)            
                   /// vpdh . ring3_rad = 99.; //  upVPD geo parameter (5 5/8in)            
                   vpdh . ring3_phi0 = 99.; //  upVPD geo parameter            
                   /// vpdh . ring3_phi0 = 99.; //  upVPD geo parameter            
                   vpdh . ring3_dphi = 99.; //  upVPD geo parameter            
                   /// vpdh . ring3_dphi = 99.; //  upVPD geo parameter            
                   vpdh . ring3_kproj = 0; //  upVPD geo parameter            
                   /// vpdh . ring3_kproj = 0; //  upVPD geo parameter            
                   vpdh . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   /// vpdh . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   vpdh . udshift = 0.0; //  up down y shift            
                   /// vpdh . udshift = 0.0; //  up down y shift            
                   vpdh . boltshift = 0.0; //  Bolt additional y shift            
                   /// vpdh . boltshift = 0.0; //  Bolt additional y shift            
                   //           
                   vpdh.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdh_doc        
             ///@{           
                   ++vpdh._index;           
                   vpdh . version = 8; //  geometry version       WJL ...used by Y2006B            
                   /// vpdh . version = 8; //  geometry version       WJL ...used by Y2006B            
                   vpdh . zposeast = 571.45; //  Z position East        (more or less arbitrary)            
                   /// vpdh . zposeast = 571.45; //  Z position East        (more or less arbitrary)            
                   vpdh . zposwest = 571.45; //  Z position West        (more or less arbitrary)            
                   /// vpdh . zposwest = 571.45; //  Z position West        (more or less arbitrary)            
                   vpdh . rmin = 6.6675; //  mothervolume rmin      (2 5/8in)            
                   /// vpdh . rmin = 6.6675; //  mothervolume rmin      (2 5/8in)            
                   vpdh . rmax = 16.51; //  mothervolume rmax      (6 1/2in)            
                   /// vpdh . rmax = 16.51; //  mothervolume rmax      (6 1/2in)            
                   vpdh . length = 32.; //  mothervolume length            
                   /// vpdh . length = 32.; //  mothervolume length            
                   vpdh . detrad = 2.54; //  det assy cylnder radius (2in diameter)            
                   /// vpdh . detrad = 2.54; //  det assy cylnder radius (2in diameter)            
                   vpdh . detlen = 20.32; //  det assy cylinder radius (8in)            
                   /// vpdh . detlen = 20.32; //  det assy cylinder radius (8in)            
                   vpdh . pmtrad = 1.905; //  pmt cylinder radius (1.5in diameter)            
                   /// vpdh . pmtrad = 1.905; //  pmt cylinder radius (1.5in diameter)            
                   vpdh . pmtlen = 1.905; //  pmt cylinder length (1.5in)            
                   /// vpdh . pmtlen = 1.905; //  pmt cylinder length (1.5in)            
                   vpdh . detwall = 0.127; //  det assy cylinder wall thickness (50mils)            
                   /// vpdh . detwall = 0.127; //  det assy cylinder wall thickness (50mils)            
                   vpdh . detfront = 0.3175; //  det assy front and back plate thicknesses (1/8in)            
                   /// vpdh . detfront = 0.3175; //  det assy front and back plate thicknesses (1/8in)            
                   vpdh . leadthick = 1.0; //  lead converter layer thickness (1cm)            
                   /// vpdh . leadthick = 1.0; //  lead converter layer thickness (1cm)            
                   vpdh . scintthick = 1.0; //    scintillator layer thickness (1cm)            
                   /// vpdh . scintthick = 1.0; //    scintillator layer thickness (1cm)            
                   vpdh . ring1_ndet = 11; //  upVPD number of tubes in ring 1            
                   /// vpdh . ring1_ndet = 11; //  upVPD number of tubes in ring 1            
                   vpdh . ring1_rad = 9.5; //  upVPD geo parameter      (3.74in)            
                   /// vpdh . ring1_rad = 9.5; //  upVPD geo parameter      (3.74in)            
                   vpdh . ring1_phi0 = -73.6364; //  upVPD geo parameter      (360/11)            
                   /// vpdh . ring1_phi0 = -73.6364; //  upVPD geo parameter      (360/11)            
                   vpdh . ring1_dphi = 32.7272; //  upVPD geo parameter (-90+(360/11/2))            
                   /// vpdh . ring1_dphi = 32.7272; //  upVPD geo parameter (-90+(360/11/2))            
                   vpdh . ring1_kproj = 0; //  upVPD geo parameter            
                   /// vpdh . ring1_kproj = 0; //  upVPD geo parameter            
                   vpdh . ring2_ndet = 11; //  upVPD number of tubes in ring 2            
                   /// vpdh . ring2_ndet = 11; //  upVPD number of tubes in ring 2            
                   vpdh . ring2_rad = 13.7; //  upVPD geo parameter      (5.394in)            
                   /// vpdh . ring2_rad = 13.7; //  upVPD geo parameter      (5.394in)            
                   vpdh . ring2_phi0 = -90; //  upVPD geo parameter             
                   /// vpdh . ring2_phi0 = -90; //  upVPD geo parameter             
                   vpdh . ring2_dphi = 32.7272; //  upVPD geo parameter      (360/11)            
                   /// vpdh . ring2_dphi = 32.7272; //  upVPD geo parameter      (360/11)            
                   vpdh . ring2_kproj = 0; //  upVPD geo parameter            
                   /// vpdh . ring2_kproj = 0; //  upVPD geo parameter            
                   vpdh . ring3_ndet = 0; //  upVPD number of tubes in ring 3            
                   /// vpdh . ring3_ndet = 0; //  upVPD number of tubes in ring 3            
                   vpdh . ring3_rad = 99.; //  upVPD geo parameter (5 5/8in)            
                   /// vpdh . ring3_rad = 99.; //  upVPD geo parameter (5 5/8in)            
                   vpdh . ring3_phi0 = 99.; //  upVPD geo parameter            
                   /// vpdh . ring3_phi0 = 99.; //  upVPD geo parameter            
                   vpdh . ring3_dphi = 99.; //  upVPD geo parameter            
                   /// vpdh . ring3_dphi = 99.; //  upVPD geo parameter            
                   vpdh . ring3_kproj = 0; //  upVPD geo parameter            
                   /// vpdh . ring3_kproj = 0; //  upVPD geo parameter            
                   vpdh . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   /// vpdh . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   vpdh . udshift = -5.715; //  up down y shift            
                   /// vpdh . udshift = -5.715; //  up down y shift            
                   vpdh . boltshift = 1.0; //  Bolt additional y shift            
                   /// vpdh . boltshift = 1.0; //  Bolt additional y shift            
                   //           
                   vpdh.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdh_doc        
             ///@{           
                   ++vpdh._index;           
                   vpdh . version = 9; //  geometry version       WJL ...used by Y2006C            
                   /// vpdh . version = 9; //  geometry version       WJL ...used by Y2006C            
                   vpdh . zposeast = 571.45; //  Z position East        (more or less arbitrary)            
                   /// vpdh . zposeast = 571.45; //  Z position East        (more or less arbitrary)            
                   vpdh . zposwest = 571.45; //  Z position West        (more or less arbitrary)            
                   /// vpdh . zposwest = 571.45; //  Z position West        (more or less arbitrary)            
                   vpdh . rmin = 6.6675; //  mothervolume rmin      (2 5/8in)            
                   /// vpdh . rmin = 6.6675; //  mothervolume rmin      (2 5/8in)            
                   vpdh . rmax = 19.685; //  mothervolume rmax  (7 3/4in)            
                   /// vpdh . rmax = 19.685; //  mothervolume rmax  (7 3/4in)            
                   vpdh . length = 32.; //  mothervolume length            
                   /// vpdh . length = 32.; //  mothervolume length            
                   vpdh . detrad = 2.54; //  det assy cylnder radius (2in diameter)            
                   /// vpdh . detrad = 2.54; //  det assy cylnder radius (2in diameter)            
                   vpdh . detlen = 20.32; //  det assy cylinder radius (8in)            
                   /// vpdh . detlen = 20.32; //  det assy cylinder radius (8in)            
                   vpdh . pmtrad = 1.905; //  pmt cylinder radius (1.5in diameter)            
                   /// vpdh . pmtrad = 1.905; //  pmt cylinder radius (1.5in diameter)            
                   vpdh . pmtlen = 1.905; //  pmt cylinder length (1.5in)            
                   /// vpdh . pmtlen = 1.905; //  pmt cylinder length (1.5in)            
                   vpdh . detwall = 0.127; //  det assy cylinder wall thickness (50mils)            
                   /// vpdh . detwall = 0.127; //  det assy cylinder wall thickness (50mils)            
                   vpdh . detfront = 0.3175; //  det assy front and back plate thicknesses (1/8in)            
                   /// vpdh . detfront = 0.3175; //  det assy front and back plate thicknesses (1/8in)            
                   vpdh . leadthick = 1.0; //  lead converter layer thickness (1cm)            
                   /// vpdh . leadthick = 1.0; //  lead converter layer thickness (1cm)            
                   vpdh . scintthick = 1.0; //    scintillator layer thickness (1cm)            
                   /// vpdh . scintthick = 1.0; //    scintillator layer thickness (1cm)            
                   vpdh . ring1_ndet = 11; //  upVPD number of tubes in ring 1            
                   /// vpdh . ring1_ndet = 11; //  upVPD number of tubes in ring 1            
                   vpdh . ring1_rad = 9.5; //  upVPD geo parameter      (3.74in)            
                   /// vpdh . ring1_rad = 9.5; //  upVPD geo parameter      (3.74in)            
                   vpdh . ring1_phi0 = -73.6364; //  upVPD geo parameter      (360/11)            
                   /// vpdh . ring1_phi0 = -73.6364; //  upVPD geo parameter      (360/11)            
                   vpdh . ring1_dphi = 32.7272; //  upVPD geo parameter (-90+(360/11/2))            
                   /// vpdh . ring1_dphi = 32.7272; //  upVPD geo parameter (-90+(360/11/2))            
                   vpdh . ring1_kproj = 0; //  upVPD geo parameter            
                   /// vpdh . ring1_kproj = 0; //  upVPD geo parameter            
                   vpdh . ring2_ndet = 11; //  upVPD number of tubes in ring 2            
                   /// vpdh . ring2_ndet = 11; //  upVPD number of tubes in ring 2            
                   vpdh . ring2_rad = 13.7; //  upVPD geo parameter      (5.394in)            
                   /// vpdh . ring2_rad = 13.7; //  upVPD geo parameter      (5.394in)            
                   vpdh . ring2_phi0 = -90; //  upVPD geo parameter             
                   /// vpdh . ring2_phi0 = -90; //  upVPD geo parameter             
                   vpdh . ring2_dphi = 32.7272; //  upVPD geo parameter      (360/11)            
                   /// vpdh . ring2_dphi = 32.7272; //  upVPD geo parameter      (360/11)            
                   vpdh . ring2_kproj = 0; //  upVPD geo parameter            
                   /// vpdh . ring2_kproj = 0; //  upVPD geo parameter            
                   vpdh . ring3_ndet = 11; //  upVPD number of tubes in ring 3            
                   /// vpdh . ring3_ndet = 11; //  upVPD number of tubes in ring 3            
                   vpdh . ring3_rad = 16.8; //  upVPD geo parameter            
                   /// vpdh . ring3_rad = 16.8; //  upVPD geo parameter            
                   vpdh . ring3_phi0 = -73.6364; //  upVPD geo parameter            
                   /// vpdh . ring3_phi0 = -73.6364; //  upVPD geo parameter            
                   vpdh . ring3_dphi = 32.7272; //  upVPD geo parameter            
                   /// vpdh . ring3_dphi = 32.7272; //  upVPD geo parameter            
                   vpdh . ring3_kproj = 0; //  upVPD geo parameter            
                   /// vpdh . ring3_kproj = 0; //  upVPD geo parameter            
                   vpdh . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   /// vpdh . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   vpdh . udshift = -8.255; //  up down y shift            
                   /// vpdh . udshift = -8.255; //  up down y shift            
                   vpdh . boltshift = 1.5; //  Bolt additional y shift            
                   /// vpdh . boltshift = 1.5; //  Bolt additional y shift            
                   //           
                   vpdh.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpdh_doc        
             ///@{           
                   ++vpdh._index;           
                   vpdh . version = 10; //  geometry version       WJL ...used by Y2006D            
                   /// vpdh . version = 10; //  geometry version       WJL ...used by Y2006D            
                   vpdh . zposeast = 571.45; //  Z position East        (more or less arbitrary)            
                   /// vpdh . zposeast = 571.45; //  Z position East        (more or less arbitrary)            
                   vpdh . zposwest = 571.45; //  Z position West        (more or less arbitrary)            
                   /// vpdh . zposwest = 571.45; //  Z position West        (more or less arbitrary)            
                   vpdh . rmin = 6.6675; //  mothervolume rmin      (2 5/8in)            
                   /// vpdh . rmin = 6.6675; //  mothervolume rmin      (2 5/8in)            
                   vpdh . rmax = 19.685; //  mothervolume rmax  (7 3/4in)            
                   /// vpdh . rmax = 19.685; //  mothervolume rmax  (7 3/4in)            
                   vpdh . length = 32.; //  mothervolume length            
                   /// vpdh . length = 32.; //  mothervolume length            
                   vpdh . detrad = 2.54; //  det assy cylnder radius (2in diameter)            
                   /// vpdh . detrad = 2.54; //  det assy cylnder radius (2in diameter)            
                   vpdh . detlen = 20.32; //  det assy cylinder radius (8in)            
                   /// vpdh . detlen = 20.32; //  det assy cylinder radius (8in)            
                   vpdh . pmtrad = 1.905; //  pmt cylinder radius (1.5in diameter)            
                   /// vpdh . pmtrad = 1.905; //  pmt cylinder radius (1.5in diameter)            
                   vpdh . pmtlen = 1.905; //  pmt cylinder length (1.5in)            
                   /// vpdh . pmtlen = 1.905; //  pmt cylinder length (1.5in)            
                   vpdh . detwall = 0.127; //  det assy cylinder wall thickness (50mils)            
                   /// vpdh . detwall = 0.127; //  det assy cylinder wall thickness (50mils)            
                   vpdh . detfront = 0.3175; //  det assy front and back plate thicknesses (1/8in)            
                   /// vpdh . detfront = 0.3175; //  det assy front and back plate thicknesses (1/8in)            
                   vpdh . leadthick = 1.0; //  lead converter layer thickness (1cm)            
                   /// vpdh . leadthick = 1.0; //  lead converter layer thickness (1cm)            
                   vpdh . scintthick = 1.0; //    scintillator layer thickness (1cm)            
                   /// vpdh . scintthick = 1.0; //    scintillator layer thickness (1cm)            
                   vpdh . ring1_ndet = 11; //  upVPD number of tubes in ring 1            
                   /// vpdh . ring1_ndet = 11; //  upVPD number of tubes in ring 1            
                   vpdh . ring1_rad = 9.5; //  upVPD geo parameter      (3.74in)            
                   /// vpdh . ring1_rad = 9.5; //  upVPD geo parameter      (3.74in)            
                   vpdh . ring1_phi0 = -73.6364; //  upVPD geo parameter      (360/11)            
                   /// vpdh . ring1_phi0 = -73.6364; //  upVPD geo parameter      (360/11)            
                   vpdh . ring1_dphi = 32.7272; //  upVPD geo parameter (-90+(360/11/2))            
                   /// vpdh . ring1_dphi = 32.7272; //  upVPD geo parameter (-90+(360/11/2))            
                   vpdh . ring1_kproj = 1; //  upVPD geo parameter            
                   /// vpdh . ring1_kproj = 1; //  upVPD geo parameter            
                   vpdh . ring2_ndet = 11; //  upVPD number of tubes in ring 2            
                   /// vpdh . ring2_ndet = 11; //  upVPD number of tubes in ring 2            
                   vpdh . ring2_rad = 13.7; //  upVPD geo parameter      (5.394in)            
                   /// vpdh . ring2_rad = 13.7; //  upVPD geo parameter      (5.394in)            
                   vpdh . ring2_phi0 = -90; //  upVPD geo parameter             
                   /// vpdh . ring2_phi0 = -90; //  upVPD geo parameter             
                   vpdh . ring2_dphi = 32.7272; //  upVPD geo parameter      (360/11)            
                   /// vpdh . ring2_dphi = 32.7272; //  upVPD geo parameter      (360/11)            
                   vpdh . ring2_kproj = 1; //  upVPD geo parameter            
                   /// vpdh . ring2_kproj = 1; //  upVPD geo parameter            
                   vpdh . ring3_ndet = 11; //  upVPD number of tubes in ring 3            
                   /// vpdh . ring3_ndet = 11; //  upVPD number of tubes in ring 3            
                   vpdh . ring3_rad = 16.8; //  upVPD geo parameter            
                   /// vpdh . ring3_rad = 16.8; //  upVPD geo parameter            
                   vpdh . ring3_phi0 = -73.6364; //  upVPD geo parameter            
                   /// vpdh . ring3_phi0 = -73.6364; //  upVPD geo parameter            
                   vpdh . ring3_dphi = 32.7272; //  upVPD geo parameter            
                   /// vpdh . ring3_dphi = 32.7272; //  upVPD geo parameter            
                   vpdh . ring3_kproj = 1; //  upVPD geo parameter            
                   /// vpdh . ring3_kproj = 1; //  upVPD geo parameter            
                   vpdh . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   /// vpdh . ewshift = 1.905; //  east west z shift (0.75*2.54)            
                   vpdh . udshift = -8.255; //  up down y shift            
                   /// vpdh . udshift = -8.255; //  up down y shift            
                   vpdh . boltshift = 1.5; //  Bolt additional y shift            
                   /// vpdh . boltshift = 1.5; //  Bolt additional y shift            
                   //           
                   vpdh.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup vpds_doc        
             ///@{           
                   ++vpds._index;           
                   vpds . version = 1; //  first version in Year 2007            
                   /// vpds . version = 1; //  first version in Year 2007            
                   vpds . ibsazc = 692.91; //  IBSA position Z center            
                   /// vpds . ibsazc = 692.91; //  IBSA position Z center            
                   vpds . ibsayc = -60.10; //  IBSA position Y center            
                   /// vpds . ibsayc = -60.10; //  IBSA position Y center            
                   vpds . ibsaxc = 24.11; //  IBSA position X center            
                   /// vpds . ibsaxc = 24.11; //  IBSA position X center            
                   vpds . ibsbzc = 631.20; //  IBSB position Z center            
                   /// vpds . ibsbzc = 631.20; //  IBSB position Z center            
                   vpds . ibsbyc = -69.50; //  IBSB position Y center = (Yc + UDshift)            
                   /// vpds . ibsbyc = -69.50; //  IBSB position Y center = (Yc + UDshift)            
                   vpds . ibsbxc = 24.11; //  IBSB position X center            
                   /// vpds . ibsbxc = 24.11; //  IBSB position X center            
                   vpds . ibsczc = 581.10; //  IBSC position Z center            
                   /// vpds . ibsczc = 581.10; //  IBSC position Z center            
                   vpds . ibscyc = -23.60; //  IBSC position Y center = (Yc + UDshift)            
                   /// vpds . ibscyc = -23.60; //  IBSC position Y center = (Yc + UDshift)            
                   vpds . ibscxc = 0.00; //  IBSC position X center            
                   /// vpds . ibscxc = 0.00; //  IBSC position X center            
                   vpds . ibsdzc1 = 397.70; //  IBSD position Z center 1            
                   /// vpds . ibsdzc1 = 397.70; //  IBSD position Z center 1            
                   vpds . ibsdzc2 = 442.80; //  IBSD position Z center 2            
                   /// vpds . ibsdzc2 = 442.80; //  IBSD position Z center 2            
                   vpds . ibsdyc1 = -11.01; //  IBSD position Y center 1 = (Yc+UDshift)            
                   /// vpds . ibsdyc1 = -11.01; //  IBSD position Y center 1 = (Yc+UDshift)            
                   vpds . ibsdyc2 = -7.20; //  IBSD position Y center 2             
                   /// vpds . ibsdyc2 = -7.20; //  IBSD position Y center 2             
                   vpds . ibsdxc = 0.00; //  IBSD position X center            
                   /// vpds . ibsdxc = 0.00; //  IBSD position X center            
                   vpds . ibsezc1 = 397.70; //  IBSE position Z center 1            
                   /// vpds . ibsezc1 = 397.70; //  IBSE position Z center 1            
                   vpds . ibsezc2 = 442.80; //  IBSE position Z center 2            
                   /// vpds . ibsezc2 = 442.80; //  IBSE position Z center 2            
                   vpds . ibseyc = -13.44; //  IBSE position Y center             
                   /// vpds . ibseyc = -13.44; //  IBSE position Y center             
                   vpds . ibsexc = 6.99; //  IBSE position X center            
                   /// vpds . ibsexc = 6.99; //  IBSE position X center            
                   vpds . ibsfzc = 411.70; //  IBSF position Z center            
                   /// vpds . ibsfzc = 411.70; //  IBSF position Z center            
                   vpds . ibsfyc = -16.51; //  IBSF position Y center = (Yc + UDshift)            
                   /// vpds . ibsfyc = -16.51; //  IBSF position Y center = (Yc + UDshift)            
                   vpds . ibsfxc = 0.00; //  IBSF position X center            
                   /// vpds . ibsfxc = 0.00; //  IBSF position X center            
                   vpds . ibsgzc1 = 397.70; //  IBSE position Z center 1            
                   /// vpds . ibsgzc1 = 397.70; //  IBSE position Z center 1            
                   vpds . ibsgzc2 = 442.80; //  IBSE position Z center 2            
                   /// vpds . ibsgzc2 = 442.80; //  IBSE position Z center 2            
                   vpds . ibsgzc3 = 2.54; //  IBSG position Z center offset            
                   /// vpds . ibsgzc3 = 2.54; //  IBSG position Z center offset            
                   vpds . ibsgyc = -17.57; //  IBSG position Y center = (Yc+UDshift+BoltShift)            
                   /// vpds . ibsgyc = -17.57; //  IBSG position Y center = (Yc+UDshift+BoltShift)            
                   vpds . ibsgxc = 0.00; //  IBSG position X center            
                   /// vpds . ibsgxc = 0.00; //  IBSG position X center            
                   vpds . ibshzc1 = 397.70; //  IBSH position Z center 1            
                   /// vpds . ibshzc1 = 397.70; //  IBSH position Z center 1            
                   vpds . ibshzc2 = 442.80; //  IBSH position Z center 2            
                   /// vpds . ibshzc2 = 442.80; //  IBSH position Z center 2            
                   vpds . ibshyc = 0.00; //  IBSH position Y center            
                   /// vpds . ibshyc = 0.00; //  IBSH position Y center            
                   vpds . ibshxc1 = 6.35; //  IBSH position X center 1            
                   /// vpds . ibshxc1 = 6.35; //  IBSH position X center 1            
                   vpds . ibshxc2 = 7.62; //  IBSH position X center 2            
                   /// vpds . ibshxc2 = 7.62; //  IBSH position X center 2            
                   vpds . bsalenx = 7.62; //  IBSA X length            
                   /// vpds . bsalenx = 7.62; //  IBSA X length            
                   vpds . bsaleny = 84.00; //  IBSA Y length            
                   /// vpds . bsaleny = 84.00; //  IBSA Y length            
                   vpds . bsalenz = 7.62; //  IBSA Z length            
                   /// vpds . bsalenz = 7.62; //  IBSA Z length            
                   vpds . baalenz = 0.95; //  IBAA Z length            
                   /// vpds . baalenz = 0.95; //  IBAA Z length            
                   vpds . bsbleny = 142.4; //  IBSB Y length            
                   /// vpds . bsbleny = 142.4; //  IBSB Y length            
                   vpds . bsclenx = 40.64; //  IBSC X length            
                   /// vpds . bsclenx = 40.64; //  IBSC X length            
                   vpds . bscleny = 4.01; //  IBSC Y length            
                   /// vpds . bscleny = 4.01; //  IBSC Y length            
                   vpds . bsclenz = 10.16; //  IBSC Z length            
                   /// vpds . bsclenz = 10.16; //  IBSC Z length            
                   vpds . baclenz = 0.64; //  IBAC Z length            
                   /// vpds . baclenz = 0.64; //  IBAC Z length            
                   vpds . bsdlenx = 20.32; //  IBSD X length            
                   /// vpds . bsdlenx = 20.32; //  IBSD X length            
                   vpds . bseleny = 8.26; //  IBSE Y length            
                   /// vpds . bseleny = 8.26; //  IBSE Y length            
                   vpds . bselenz = 6.35; //  IBSE Z length            
                   /// vpds . bselenz = 6.35; //  IBSE Z length            
                   vpds . bsfrmax = 0.95; //  IBSF Rmax            
                   /// vpds . bsfrmax = 0.95; //  IBSF Rmax            
                   vpds . bsflenz = 182.88; //  IBSF Z length            
                   /// vpds . bsflenz = 182.88; //  IBSF Z length            
                   vpds . bsslenz = 7.62; //  IBSS Z length            
                   /// vpds . bsslenz = 7.62; //  IBSS Z length            
                   vpds . bsgrmax = 0.64; //  IBSG Rmax            
                   /// vpds . bsgrmax = 0.64; //  IBSG Rmax            
                   vpds . bsglenz1 = 10.16; //  IBSG Z length 1 for vpdConfig<8            
                   /// vpds . bsglenz1 = 10.16; //  IBSG Z length 1 for vpdConfig<8            
                   vpds . bsglenz2 = 12.70; //  IBSG Z length 2 for vpdConfig=8            
                   /// vpds . bsglenz2 = 12.70; //  IBSG Z length 2 for vpdConfig=8            
                   vpds . bsglenz3 = 15.24; //  IBSG Z length 3 for vpdConfig else            
                   /// vpds . bsglenz3 = 15.24; //  IBSG Z length 3 for vpdConfig else            
                   vpds . bshlenz = 5.08; //  IBSH Z length            
                   /// vpds . bshlenz = 5.08; //  IBSH Z length            
                   vpds . elecwid = 20.3; //  Electronic box width            
                   /// vpds . elecwid = 20.3; //  Electronic box width            
                   vpds . electhck = 0.17; //  Electronic box thickness            
                   /// vpds . electhck = 0.17; //  Electronic box thickness            
                   vpds . eleclen = 5.10; //  Electronic box length            
                   /// vpds . eleclen = 5.10; //  Electronic box length            
                   vpds . vfeeposx = 0.31; //  VFEE position X center            
                   /// vpds . vfeeposx = 0.31; //  VFEE position X center            
                   vpds . vfeeposy = 0.45; //  VFEE position Y center            
                   /// vpds . vfeeposy = 0.45; //  VFEE position Y center            
                   vpds . vfeeposz = -4.75; //  VFEE position Z center            
                   /// vpds . vfeeposz = -4.75; //  VFEE position Z center            
                   vpds . vlemposx.at(0) = -7.0; //  VLEM position X center            
                   ///vpds . vlemposx.at(0) = -7.0; //  VLEM position X center            
                   vpds . vlemposx.at(1) = -3.5; //  VLEM position X center            
                   ///vpds . vlemposx.at(1) = -3.5; //  VLEM position X center            
                   vpds . vlemposx.at(2) = 0.0; //  VLEM position X center            
                   ///vpds . vlemposx.at(2) = 0.0; //  VLEM position X center            
                   vpds . vlemposx.at(3) = 3.5; //  VLEM position X center            
                   ///vpds . vlemposx.at(3) = 3.5; //  VLEM position X center            
                   vpds . vlemposx.at(4) = 7.0; //  VLEM position X center            
                   ///vpds . vlemposx.at(4) = 7.0; //  VLEM position X center            
                   vpds . vlemposx.at(5) = -7.0; //  VLEM position X center            
                   ///vpds . vlemposx.at(5) = -7.0; //  VLEM position X center            
                   vpds . vlemposx.at(6) = -3.5; //  VLEM position X center            
                   ///vpds . vlemposx.at(6) = -3.5; //  VLEM position X center            
                   vpds . vlemposx.at(7) = 0.0; //  VLEM position X center            
                   ///vpds . vlemposx.at(7) = 0.0; //  VLEM position X center            
                   vpds . vlemposx.at(8) = 3.5; //  VLEM position X center            
                   ///vpds . vlemposx.at(8) = 3.5; //  VLEM position X center            
                   vpds . vlemposx.at(9) = 7.0; //  VLEM position X center            
                   ///vpds . vlemposx.at(9) = 7.0; //  VLEM position X center            
                   vpds . vlemposx.at(10) = -6.0; //  VLEM position X center            
                   ///vpds . vlemposx.at(10) = -6.0; //  VLEM position X center            
                   vpds . vlemposx.at(11) = -2.5; //  VLEM position X center            
                   ///vpds . vlemposx.at(11) = -2.5; //  VLEM position X center            
                   vpds . vlemposx.at(12) = 1.0; //  VLEM position X center            
                   ///vpds . vlemposx.at(12) = 1.0; //  VLEM position X center            
                   vpds . vlemposx.at(13) = 4.5; //  VLEM position X center            
                   ///vpds . vlemposx.at(13) = 4.5; //  VLEM position X center            
                   vpds . vlemposx.at(14) = 8.0 ; //  VLEM position X center            
                   ///vpds . vlemposx.at(14) = 8.0 ; //  VLEM position X center            
                   vpds . vlemposy = 0.52; //  VLEM position Y center            
                   /// vpds . vlemposy = 0.52; //  VLEM position Y center            
                   vpds . vlemposz.at(0) = 2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(0) = 2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(1) = 2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(1) = 2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(2) = 2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(2) = 2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(3) = 2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(3) = 2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(4) = 2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(4) = 2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(5) = -2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(5) = -2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(6) = -2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(6) = -2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(7) = -2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(7) = -2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(8) = -2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(8) = -2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(9) = -2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(9) = -2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(10) = -2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(10) = -2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(11) = -2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(11) = -2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(12) = -2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(12) = -2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(13) = -2.0; //  VLEM position Z center            
                   ///vpds . vlemposz.at(13) = -2.0; //  VLEM position Z center            
                   vpds . vlemposz.at(14) = -2.0 ; //  VLEM position Z center            
                   ///vpds . vlemposz.at(14) = -2.0 ; //  VLEM position Z center            
                   vpds . vlemlenx = 0.86; //  VLEM X length            
                   /// vpds . vlemlenx = 0.86; //  VLEM X length            
                   vpds . vlemleny = 0.68; //  VLEM Y length            
                   /// vpds . vlemleny = 0.68; //  VLEM Y length            
                   vpds . vlemlenz = 3.8; //  VLEM Z length            
                   /// vpds . vlemlenz = 3.8; //  VLEM Z length            
                   vpds . vpipposx = 0.09; //  VPIP position X center            
                   /// vpds . vpipposx = 0.09; //  VPIP position X center            
                   vpds . vpipposy = 0.0; //  VPIP position Y center            
                   /// vpds . vpipposy = 0.0; //  VPIP position Y center            
                   vpds . vpipposz = 0.9; //  VPIP position Z center            
                   /// vpds . vpipposz = 0.9; //  VPIP position Z center            
                   vpds . vpiprmin = 0.31; //  VPIP Rmin            
                   /// vpds . vpiprmin = 0.31; //  VPIP Rmin            
                   vpds . vpiprmax = 0.34; //  VPIP Rmax            
                   /// vpds . vpiprmax = 0.34; //  VPIP Rmax            
                   vpds . vpiplenz = 2.0; //  VPIP Z length            
                   /// vpds . vpiplenz = 2.0; //  VPIP Z length            
                   //           
                   vpds.fill();           
             ///@}        
             //        
             /// USE vpdv _index=1;        
             vpdv.Use();        
             /// USE vpds _index=1;        
             vpds.Use();        
             if ( vpdv.vpdconfig<=4 )        
             {           
                   kdetstyle = 0;           
                   /// USE vpdg version=vpdv.vpdconfig;           
                   vpdg.Use("version",(Float_t)vpdv.vpdconfig);           
                   zpose     = vpdg.zposeast;           
                   zposw     = vpdg.zposwest;           
                   ewshift   = vpdg.ewshift;           
                   udshift   = vpdg.udshift;           
                   boltshift = vpdg.boltshift;           
             }        
             else if ( vpdv.vpdconfig==5||vpdv.vpdconfig==6 )        
             {           
                   kdetstyle = 1;           
                   /// USE vpdg version=vpdv.vpdconfig;           
                   vpdg.Use("version",(Float_t)vpdv.vpdconfig);           
                   zpose     = vpdg.zposeast;           
                   zposw     = vpdg.zposwest;           
                   ewshift   = vpdg.ewshift;           
                   udshift   = vpdg.udshift;           
                   boltshift = vpdg.boltshift;           
             }        
             else if ( vpdv.vpdconfig>=7 )        
             {           
                   kdetstyle = 2;           
                   /// USE vpdg version=6;           
                   vpdg.Use("version",(Float_t)6);           
                   /// USE vpdh version=vpdv.vpdconfig;           
                   vpdh.Use("version",(Float_t)vpdv.vpdconfig);           
                   zpose     = vpdh.zposeast;           
                   zposw     = vpdh.zposwest;           
                   ewshift   = vpdh.ewshift;           
                   udshift   = vpdh.udshift;           
                   boltshift = vpdh.boltshift;           
             }        
             _create = AgCreate("VPDD");        
             {           
                   AgShape myshape; // undefined shape           
                   ///Create VPDD           
                   Create("VPDD");            
             }        
             zpos = zposw;        
             { AgPlacement place = AgPlacement("VPDD","CAVE");           
                   /// Add daughter volume VPDD to mother CAVE           
                   place.TranslateZ(+zpos);           
                   /// Translate z = +zpos           
                   place.par("only")=AgPlacement::kMany;           
                   /// Overlap: agplacement::kmany           
                   _stacker -> Position( AgBlock::Find("VPDD"), place );           
             } // end placement of VPDD        
             zpos = zpose;        
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
             kibeamstyle=0;        
             if ( vpdg.ibchoice!=0 )        
             {           
                   kibeamstyle=1;           
                   if ( vpdv.vpdconfig>4 )           
                   {              
                         kibeamstyle=2;              
                         if ( vpdv.vpdconfig>=8 )              
                         {                 
                               kibeamstyle=3;                 
                         }              
                   }           
             }        
             if ( kibeamstyle>0 )        
             {           
                   _create = AgCreate("IBEM");           
                   {              
                         AgShape myshape; // undefined shape              
                         ///Create IBEM              
                         Create("IBEM");               
                   }           
                   { AgPlacement place = AgPlacement("IBEM","CAVE");              
                         /// Add daughter volume IBEM to mother CAVE              
                         place.TranslateY(vpdg.ibposyc+udshift);              
                         /// Translate y = vpdg.ibposyc+udshift              
                         place.TranslateZ(+(vpdg.ibposzc));              
                         /// Translate z = +(vpdg.ibposzc)              
                         _stacker -> Position( AgBlock::Find("IBEM"), place );              
                   } // end placement of IBEM           
                   { AgPlacement place = AgPlacement("IBEM","CAVE");              
                         /// Add daughter volume IBEM to mother CAVE              
                         place.TranslateY(vpdg.ibposyc+udshift);              
                         /// Translate y = vpdg.ibposyc+udshift              
                         place.TranslateZ(-(vpdg.ibposzc+ewshift));              
                         /// Translate z = -(vpdg.ibposzc+ewshift)              
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
                   if ( kibeamstyle>1 )           
                   {              
                         _create = AgCreate("IBSA");              
                         {                 
                               AgShape myshape; // undefined shape                 
                               ///Create IBSA                 
                               Create("IBSA");                  
                         }              
                         { AgPlacement place = AgPlacement("IBSA","CAVE");                 
                               /// Add daughter volume IBSA to mother CAVE                 
                               place.TranslateX(vpds.ibsaxc);                 
                               /// Translate x = vpds.ibsaxc                 
                               place.TranslateY(vpds.ibsayc);                 
                               /// Translate y = vpds.ibsayc                 
                               place.TranslateZ(vpds.ibsazc);                 
                               /// Translate z = vpds.ibsazc                 
                               _stacker -> Position( AgBlock::Find("IBSA"), place );                 
                         } // end placement of IBSA              
                         { AgPlacement place = AgPlacement("IBSA","CAVE");                 
                               /// Add daughter volume IBSA to mother CAVE                 
                               place.TranslateX(-vpds.ibsaxc);                 
                               /// Translate x = -vpds.ibsaxc                 
                               place.TranslateY(vpds.ibsayc);                 
                               /// Translate y = vpds.ibsayc                 
                               place.TranslateZ(vpds.ibsazc);                 
                               /// Translate z = vpds.ibsazc                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               place.Ortho( "-X-YZ" ); // ORT=-X-YZ                 
                               /// Axis substitution: XYZ --> -X-YZ                 
                               _stacker -> Position( AgBlock::Find("IBSA"), place );                 
                         } // end placement of IBSA              
                         { AgPlacement place = AgPlacement("IBSA","CAVE");                 
                               /// Add daughter volume IBSA to mother CAVE                 
                               place.TranslateX(vpds.ibsaxc);                 
                               /// Translate x = vpds.ibsaxc                 
                               place.TranslateY(vpds.ibsayc);                 
                               /// Translate y = vpds.ibsayc                 
                               place.TranslateZ(-(vpds.ibsazc+ewshift));                 
                               /// Translate z = -(vpds.ibsazc+ewshift)                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               place.Ortho( "-X-YZ" ); // ORT=-X-YZ                 
                               /// Axis substitution: XYZ --> -X-YZ                 
                               _stacker -> Position( AgBlock::Find("IBSA"), place );                 
                         } // end placement of IBSA              
                         { AgPlacement place = AgPlacement("IBSA","CAVE");                 
                               /// Add daughter volume IBSA to mother CAVE                 
                               place.TranslateX(-vpds.ibsaxc);                 
                               /// Translate x = -vpds.ibsaxc                 
                               place.TranslateY(vpds.ibsayc);                 
                               /// Translate y = vpds.ibsayc                 
                               place.TranslateZ(-(vpds.ibsazc+ewshift));                 
                               /// Translate z = -(vpds.ibsazc+ewshift)                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               place.Ortho( "-X-Y-Z" ); // ORT=-X-Y-Z                 
                               /// Axis substitution: XYZ --> -X-Y-Z                 
                               _stacker -> Position( AgBlock::Find("IBSA"), place );                 
                         } // end placement of IBSA              
                         _create = AgCreate("IBSB");              
                         {                 
                               AgShape myshape; // undefined shape                 
                               ///Create IBSB                 
                               Create("IBSB");                  
                         }              
                         { AgPlacement place = AgPlacement("IBSB","CAVE");                 
                               /// Add daughter volume IBSB to mother CAVE                 
                               place.TranslateX(vpds.ibsbxc);                 
                               /// Translate x = vpds.ibsbxc                 
                               place.TranslateY(vpds.ibsbyc+udshift);                 
                               /// Translate y = vpds.ibsbyc+udshift                 
                               place.TranslateZ(vpds.ibsbzc);                 
                               /// Translate z = vpds.ibsbzc                 
                               place.AlphaX(-45);                 
                               /// Rotate: AlphaX = -45                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSB"), place );                 
                         } // end placement of IBSB              
                         { AgPlacement place = AgPlacement("IBSB","CAVE");                 
                               /// Add daughter volume IBSB to mother CAVE                 
                               place.TranslateX(-vpds.ibsbxc);                 
                               /// Translate x = -vpds.ibsbxc                 
                               place.TranslateY(vpds.ibsbyc+udshift);                 
                               /// Translate y = vpds.ibsbyc+udshift                 
                               place.TranslateZ(vpds.ibsbzc);                 
                               /// Translate z = vpds.ibsbzc                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               place.AlphaX(-45);                 
                               /// Rotate: AlphaX = -45                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSB"), place );                 
                         } // end placement of IBSB              
                         { AgPlacement place = AgPlacement("IBSB","CAVE");                 
                               /// Add daughter volume IBSB to mother CAVE                 
                               place.TranslateX(vpds.ibsbxc);                 
                               /// Translate x = vpds.ibsbxc                 
                               place.TranslateY(vpds.ibsbyc+udshift);                 
                               /// Translate y = vpds.ibsbyc+udshift                 
                               place.TranslateZ(-(vpds.ibsbzc+ewshift));                 
                               /// Translate z = -(vpds.ibsbzc+ewshift)                 
                               place.AlphaY(-90);                 
                               /// Rotate: AlphaY = -90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               place.AlphaX(45);                 
                               /// Rotate: AlphaX = 45                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSB"), place );                 
                         } // end placement of IBSB              
                         { AgPlacement place = AgPlacement("IBSB","CAVE");                 
                               /// Add daughter volume IBSB to mother CAVE                 
                               place.TranslateX(-vpds.ibsbxc);                 
                               /// Translate x = -vpds.ibsbxc                 
                               place.TranslateY(vpds.ibsbyc+udshift);                 
                               /// Translate y = vpds.ibsbyc+udshift                 
                               place.TranslateZ(-(vpds.ibsbzc+ewshift));                 
                               /// Translate z = -(vpds.ibsbzc+ewshift)                 
                               place.AlphaY(180);                 
                               /// Rotate: AlphaY = 180                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               place.AlphaX(45);                 
                               /// Rotate: AlphaX = 45                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSB"), place );                 
                         } // end placement of IBSB              
                         _create = AgCreate("IBSC");              
                         {                 
                               AgShape myshape; // undefined shape                 
                               ///Create IBSC                 
                               Create("IBSC");                  
                         }              
                         { AgPlacement place = AgPlacement("IBSC","CAVE");                 
                               /// Add daughter volume IBSC to mother CAVE                 
                               place.TranslateY(vpds.ibscyc+udshift);                 
                               /// Translate y = vpds.ibscyc+udshift                 
                               place.TranslateZ(vpds.ibsczc);                 
                               /// Translate z = vpds.ibsczc                 
                               _stacker -> Position( AgBlock::Find("IBSC"), place );                 
                         } // end placement of IBSC              
                         { AgPlacement place = AgPlacement("IBSC","CAVE");                 
                               /// Add daughter volume IBSC to mother CAVE                 
                               place.TranslateY(vpds.ibscyc+udshift);                 
                               /// Translate y = vpds.ibscyc+udshift                 
                               place.TranslateZ(-(vpds.ibsczc+ewshift));                 
                               /// Translate z = -(vpds.ibsczc+ewshift)                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 180                 
                               /// G3 Reference: phiz = 0                 
                               Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;                 
                               place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                 
                               _stacker -> Position( AgBlock::Find("IBSC"), place );                 
                         } // end placement of IBSC              
                         _create = AgCreate("IBSD");              
                         {                 
                               AgShape myshape; // undefined shape                 
                               ///Create IBSD                 
                               Create("IBSD");                  
                         }              
                         { AgPlacement place = AgPlacement("IBSD","CAVE");                 
                               /// Add daughter volume IBSD to mother CAVE                 
                               place.TranslateX(0);                 
                               /// Translate x = 0                 
                               place.TranslateY(vpds.ibsdyc1+udshift);                 
                               /// Translate y = vpds.ibsdyc1+udshift                 
                               place.TranslateZ(vpds.ibsdzc1);                 
                               /// Translate z = vpds.ibsdzc1                 
                               _stacker -> Position( AgBlock::Find("IBSD"), place );                 
                         } // end placement of IBSD              
                         { AgPlacement place = AgPlacement("IBSD","CAVE");                 
                               /// Add daughter volume IBSD to mother CAVE                 
                               place.TranslateX(0);                 
                               /// Translate x = 0                 
                               place.TranslateY(vpds.ibsdyc1+udshift);                 
                               /// Translate y = vpds.ibsdyc1+udshift                 
                               place.TranslateZ(vpds.ibsdzc2);                 
                               /// Translate z = vpds.ibsdzc2                 
                               _stacker -> Position( AgBlock::Find("IBSD"), place );                 
                         } // end placement of IBSD              
                         { AgPlacement place = AgPlacement("IBSD","CAVE");                 
                               /// Add daughter volume IBSD to mother CAVE                 
                               place.TranslateX(0);                 
                               /// Translate x = 0                 
                               place.TranslateY(vpds.ibsdyc1+udshift);                 
                               /// Translate y = vpds.ibsdyc1+udshift                 
                               place.TranslateZ(-(vpds.ibsdzc1+ewshift));                 
                               /// Translate z = -(vpds.ibsdzc1+ewshift)                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 180                 
                               /// G3 Reference: phiz = 0                 
                               Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;                 
                               place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                 
                               _stacker -> Position( AgBlock::Find("IBSD"), place );                 
                         } // end placement of IBSD              
                         { AgPlacement place = AgPlacement("IBSD","CAVE");                 
                               /// Add daughter volume IBSD to mother CAVE                 
                               place.TranslateX(0);                 
                               /// Translate x = 0                 
                               place.TranslateY(vpds.ibsdyc1+udshift);                 
                               /// Translate y = vpds.ibsdyc1+udshift                 
                               place.TranslateZ(-(vpds.ibsdzc2+ewshift));                 
                               /// Translate z = -(vpds.ibsdzc2+ewshift)                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 180                 
                               /// G3 Reference: phiz = 0                 
                               Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;                 
                               place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                 
                               _stacker -> Position( AgBlock::Find("IBSD"), place );                 
                         } // end placement of IBSD              
                         { AgPlacement place = AgPlacement("IBSD","CAVE");                 
                               /// Add daughter volume IBSD to mother CAVE                 
                               place.TranslateX(0);                 
                               /// Translate x = 0                 
                               place.TranslateY(vpds.ibsdyc2);                 
                               /// Translate y = vpds.ibsdyc2                 
                               place.TranslateZ(vpds.ibsdzc1);                 
                               /// Translate z = vpds.ibsdzc1                 
                               _stacker -> Position( AgBlock::Find("IBSD"), place );                 
                         } // end placement of IBSD              
                         { AgPlacement place = AgPlacement("IBSD","CAVE");                 
                               /// Add daughter volume IBSD to mother CAVE                 
                               place.TranslateX(0);                 
                               /// Translate x = 0                 
                               place.TranslateY(vpds.ibsdyc2);                 
                               /// Translate y = vpds.ibsdyc2                 
                               place.TranslateZ(vpds.ibsdzc2);                 
                               /// Translate z = vpds.ibsdzc2                 
                               _stacker -> Position( AgBlock::Find("IBSD"), place );                 
                         } // end placement of IBSD              
                         { AgPlacement place = AgPlacement("IBSD","CAVE");                 
                               /// Add daughter volume IBSD to mother CAVE                 
                               place.TranslateX(0);                 
                               /// Translate x = 0                 
                               place.TranslateY(vpds.ibsdyc2);                 
                               /// Translate y = vpds.ibsdyc2                 
                               place.TranslateZ(-(vpds.ibsdzc1+ewshift));                 
                               /// Translate z = -(vpds.ibsdzc1+ewshift)                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 180                 
                               /// G3 Reference: phiz = 0                 
                               Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;                 
                               place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                 
                               _stacker -> Position( AgBlock::Find("IBSD"), place );                 
                         } // end placement of IBSD              
                         { AgPlacement place = AgPlacement("IBSD","CAVE");                 
                               /// Add daughter volume IBSD to mother CAVE                 
                               place.TranslateX(0);                 
                               /// Translate x = 0                 
                               place.TranslateY(vpds.ibsdyc2);                 
                               /// Translate y = vpds.ibsdyc2                 
                               place.TranslateZ(-(vpds.ibsdzc2+ewshift));                 
                               /// Translate z = -(vpds.ibsdzc2+ewshift)                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 180                 
                               /// G3 Reference: phiz = 0                 
                               Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;                 
                               place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                 
                               _stacker -> Position( AgBlock::Find("IBSD"), place );                 
                         } // end placement of IBSD              
                         tempos = (vpdg.ibposyc+vpdg.ibthickh+(vpdg.ibheight/2.));              
                         _create = AgCreate("IBSE");              
                         {                 
                               AgShape myshape; // undefined shape                 
                               ///Create IBSE                 
                               Create("IBSE");                  
                         }              
                         { AgPlacement place = AgPlacement("IBSE","CAVE");                 
                               /// Add daughter volume IBSE to mother CAVE                 
                               place.TranslateX(+vpds.ibsexc);                 
                               /// Translate x = +vpds.ibsexc                 
                               place.TranslateY(vpds.ibseyc);                 
                               /// Translate y = vpds.ibseyc                 
                               place.TranslateZ(vpds.ibsezc1);                 
                               /// Translate z = vpds.ibsezc1                 
                               _stacker -> Position( AgBlock::Find("IBSE"), place );                 
                         } // end placement of IBSE              
                         { AgPlacement place = AgPlacement("IBSE","CAVE");                 
                               /// Add daughter volume IBSE to mother CAVE                 
                               place.TranslateX(-vpds.ibsexc);                 
                               /// Translate x = -vpds.ibsexc                 
                               place.TranslateY(vpds.ibseyc);                 
                               /// Translate y = vpds.ibseyc                 
                               place.TranslateZ(vpds.ibsezc1);                 
                               /// Translate z = vpds.ibsezc1                 
                               _stacker -> Position( AgBlock::Find("IBSE"), place );                 
                         } // end placement of IBSE              
                         { AgPlacement place = AgPlacement("IBSE","CAVE");                 
                               /// Add daughter volume IBSE to mother CAVE                 
                               place.TranslateX(+vpds.ibsexc);                 
                               /// Translate x = +vpds.ibsexc                 
                               place.TranslateY(vpds.ibseyc);                 
                               /// Translate y = vpds.ibseyc                 
                               place.TranslateZ(vpds.ibsezc2);                 
                               /// Translate z = vpds.ibsezc2                 
                               _stacker -> Position( AgBlock::Find("IBSE"), place );                 
                         } // end placement of IBSE              
                         { AgPlacement place = AgPlacement("IBSE","CAVE");                 
                               /// Add daughter volume IBSE to mother CAVE                 
                               place.TranslateX(-vpds.ibsexc);                 
                               /// Translate x = -vpds.ibsexc                 
                               place.TranslateY(vpds.ibseyc);                 
                               /// Translate y = vpds.ibseyc                 
                               place.TranslateZ(vpds.ibsezc2);                 
                               /// Translate z = vpds.ibsezc2                 
                               _stacker -> Position( AgBlock::Find("IBSE"), place );                 
                         } // end placement of IBSE              
                         { AgPlacement place = AgPlacement("IBSE","CAVE");                 
                               /// Add daughter volume IBSE to mother CAVE                 
                               place.TranslateX(+vpds.ibsexc);                 
                               /// Translate x = +vpds.ibsexc                 
                               place.TranslateY(vpds.ibseyc);                 
                               /// Translate y = vpds.ibseyc                 
                               place.TranslateZ(-(vpds.ibsezc1+ewshift));                 
                               /// Translate z = -(vpds.ibsezc1+ewshift)                 
                               _stacker -> Position( AgBlock::Find("IBSE"), place );                 
                         } // end placement of IBSE              
                         { AgPlacement place = AgPlacement("IBSE","CAVE");                 
                               /// Add daughter volume IBSE to mother CAVE                 
                               place.TranslateX(-vpds.ibsexc);                 
                               /// Translate x = -vpds.ibsexc                 
                               place.TranslateY(vpds.ibseyc);                 
                               /// Translate y = vpds.ibseyc                 
                               place.TranslateZ(-(vpds.ibsezc1+ewshift));                 
                               /// Translate z = -(vpds.ibsezc1+ewshift)                 
                               _stacker -> Position( AgBlock::Find("IBSE"), place );                 
                         } // end placement of IBSE              
                         { AgPlacement place = AgPlacement("IBSE","CAVE");                 
                               /// Add daughter volume IBSE to mother CAVE                 
                               place.TranslateX(+vpds.ibsexc);                 
                               /// Translate x = +vpds.ibsexc                 
                               place.TranslateY(vpds.ibseyc);                 
                               /// Translate y = vpds.ibseyc                 
                               place.TranslateZ(-(vpds.ibsezc2+ewshift));                 
                               /// Translate z = -(vpds.ibsezc2+ewshift)                 
                               _stacker -> Position( AgBlock::Find("IBSE"), place );                 
                         } // end placement of IBSE              
                         { AgPlacement place = AgPlacement("IBSE","CAVE");                 
                               /// Add daughter volume IBSE to mother CAVE                 
                               place.TranslateX(-vpds.ibsexc);                 
                               /// Translate x = -vpds.ibsexc                 
                               place.TranslateY(vpds.ibseyc);                 
                               /// Translate y = vpds.ibseyc                 
                               place.TranslateZ(-(vpds.ibsezc2+ewshift));                 
                               /// Translate z = -(vpds.ibsezc2+ewshift)                 
                               _stacker -> Position( AgBlock::Find("IBSE"), place );                 
                         } // end placement of IBSE              
                         _create = AgCreate("IBSF");              
                         {                 
                               AgShape myshape; // undefined shape                 
                               ///Create IBSF                 
                               Create("IBSF");                  
                         }              
                         { AgPlacement place = AgPlacement("IBSF","CAVE");                 
                               /// Add daughter volume IBSF to mother CAVE                 
                               place.TranslateY(vpdg.ibposyc+udshift);                 
                               /// Translate y = vpdg.ibposyc+udshift                 
                               place.TranslateZ(vpds.ibsfzc);                 
                               /// Translate z = vpds.ibsfzc                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSF"), place );                 
                         } // end placement of IBSF              
                         { AgPlacement place = AgPlacement("IBSF","CAVE");                 
                               /// Add daughter volume IBSF to mother CAVE                 
                               place.TranslateY(vpdg.ibposyc+udshift);                 
                               /// Translate y = vpdg.ibposyc+udshift                 
                               place.TranslateZ(-(vpds.ibsfzc+ewshift));                 
                               /// Translate z = -(vpds.ibsfzc+ewshift)                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSF"), place );                 
                         } // end placement of IBSF              
                         _create = AgCreate("IBSS");              
                         {                 
                               AgShape myshape; // undefined shape                 
                               ///Create IBSS                 
                               Create("IBSS");                  
                         }              
                         { AgPlacement place = AgPlacement("IBSS","IBEM");                 
                               /// Add daughter volume IBSS to mother IBEM                 
                               place.TranslateY(0);                 
                               /// Translate y = 0                 
                               place.TranslateZ(+(vpds.ibsfzc)-(vpdg.ibposzc));                 
                               /// Translate z = +(vpds.ibsfzc)-(vpdg.ibposzc)                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSS"), place );                 
                         } // end placement of IBSS              
                         { AgPlacement place = AgPlacement("IBSS","IBEM");                 
                               /// Add daughter volume IBSS to mother IBEM                 
                               place.TranslateY(0);                 
                               /// Translate y = 0                 
                               place.TranslateZ(-(vpds.ibsfzc+ewshift)+(vpdg.ibposzc));                 
                               /// Translate z = -(vpds.ibsfzc+ewshift)+(vpdg.ibposzc)                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSS"), place );                 
                         } // end placement of IBSS              
                         _create = AgCreate("IBSG");              
                         {                 
                               AgShape myshape; // undefined shape                 
                               ///Create IBSG                 
                               Create("IBSG");                  
                         }              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(+vpds.ibsgxc);                 
                               /// Translate x = +vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(vpds.ibsgzc1-vpds.ibsgzc3);                 
                               /// Translate z = vpds.ibsgzc1-vpds.ibsgzc3                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(-vpds.ibsgxc);                 
                               /// Translate x = -vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(vpds.ibsgzc1-vpds.ibsgzc3);                 
                               /// Translate z = vpds.ibsgzc1-vpds.ibsgzc3                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(+vpds.ibsgxc);                 
                               /// Translate x = +vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(vpds.ibsgzc1+vpds.ibsgzc3);                 
                               /// Translate z = vpds.ibsgzc1+vpds.ibsgzc3                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(-vpds.ibsgxc);                 
                               /// Translate x = -vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(vpds.ibsgzc1+vpds.ibsgzc3);                 
                               /// Translate z = vpds.ibsgzc1+vpds.ibsgzc3                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(+vpds.ibsgxc);                 
                               /// Translate x = +vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(vpds.ibsgzc2-vpds.ibsgzc3);                 
                               /// Translate z = vpds.ibsgzc2-vpds.ibsgzc3                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(-vpds.ibsgxc);                 
                               /// Translate x = -vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(vpds.ibsgzc2-vpds.ibsgzc3);                 
                               /// Translate z = vpds.ibsgzc2-vpds.ibsgzc3                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(+vpds.ibsgxc);                 
                               /// Translate x = +vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(vpds.ibsgzc2+vpds.ibsgzc3);                 
                               /// Translate z = vpds.ibsgzc2+vpds.ibsgzc3                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(-vpds.ibsgxc);                 
                               /// Translate x = -vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(vpds.ibsgzc2+vpds.ibsgzc3);                 
                               /// Translate z = vpds.ibsgzc2+vpds.ibsgzc3                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(+vpds.ibsgxc);                 
                               /// Translate x = +vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(-(vpds.ibsgzc1-vpds.ibsgzc3+ewshift));                 
                               /// Translate z = -(vpds.ibsgzc1-vpds.ibsgzc3+ewshift)                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(-vpds.ibsgxc);                 
                               /// Translate x = -vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(-(vpds.ibsgzc1-vpds.ibsgzc3+ewshift));                 
                               /// Translate z = -(vpds.ibsgzc1-vpds.ibsgzc3+ewshift)                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(+vpds.ibsgxc);                 
                               /// Translate x = +vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(-(vpds.ibsgzc1+vpds.ibsgzc3+ewshift));                 
                               /// Translate z = -(vpds.ibsgzc1+vpds.ibsgzc3+ewshift)                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(-vpds.ibsgxc);                 
                               /// Translate x = -vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(-(vpds.ibsgzc1+vpds.ibsgzc3+ewshift));                 
                               /// Translate z = -(vpds.ibsgzc1+vpds.ibsgzc3+ewshift)                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(+vpds.ibsgxc);                 
                               /// Translate x = +vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(-(vpds.ibsgzc2-vpds.ibsgzc3+ewshift));                 
                               /// Translate z = -(vpds.ibsgzc2-vpds.ibsgzc3+ewshift)                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(-vpds.ibsgxc);                 
                               /// Translate x = -vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(-(vpds.ibsgzc2-vpds.ibsgzc3+ewshift));                 
                               /// Translate z = -(vpds.ibsgzc2-vpds.ibsgzc3+ewshift)                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(+vpds.ibsgxc);                 
                               /// Translate x = +vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(-(vpds.ibsgzc2+vpds.ibsgzc3+ewshift));                 
                               /// Translate z = -(vpds.ibsgzc2+vpds.ibsgzc3+ewshift)                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         { AgPlacement place = AgPlacement("IBSG","CAVE");                 
                               /// Add daughter volume IBSG to mother CAVE                 
                               place.TranslateX(-vpds.ibsgxc);                 
                               /// Translate x = -vpds.ibsgxc                 
                               place.TranslateY(udshift+boltshift+vpds.ibsgyc);                 
                               /// Translate y = udshift+boltshift+vpds.ibsgyc                 
                               place.TranslateZ(-(vpds.ibsgzc2+vpds.ibsgzc3+ewshift));                 
                               /// Translate z = -(vpds.ibsgzc2+vpds.ibsgzc3+ewshift)                 
                               place.AlphaX(90);                 
                               /// Rotate: AlphaX = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSG"), place );                 
                         } // end placement of IBSG              
                         _create = AgCreate("IBSH");              
                         {                 
                               AgShape myshape; // undefined shape                 
                               ///Create IBSH                 
                               Create("IBSH");                  
                         }              
                         { AgPlacement place = AgPlacement("IBSH","CAVE");                 
                               /// Add daughter volume IBSH to mother CAVE                 
                               place.TranslateX(+vpds.ibshxc1);                 
                               /// Translate x = +vpds.ibshxc1                 
                               place.TranslateZ(+vpds.ibshzc1);                 
                               /// Translate z = +vpds.ibshzc1                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSH"), place );                 
                         } // end placement of IBSH              
                         { AgPlacement place = AgPlacement("IBSH","CAVE");                 
                               /// Add daughter volume IBSH to mother CAVE                 
                               place.TranslateX(-vpds.ibshxc1);                 
                               /// Translate x = -vpds.ibshxc1                 
                               place.TranslateZ(+vpds.ibshzc1);                 
                               /// Translate z = +vpds.ibshzc1                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSH"), place );                 
                         } // end placement of IBSH              
                         { AgPlacement place = AgPlacement("IBSH","CAVE");                 
                               /// Add daughter volume IBSH to mother CAVE                 
                               place.TranslateX(+vpds.ibshxc1);                 
                               /// Translate x = +vpds.ibshxc1                 
                               place.TranslateZ(-(vpds.ibshzc1+ewshift));                 
                               /// Translate z = -(vpds.ibshzc1+ewshift)                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSH"), place );                 
                         } // end placement of IBSH              
                         { AgPlacement place = AgPlacement("IBSH","CAVE");                 
                               /// Add daughter volume IBSH to mother CAVE                 
                               place.TranslateX(-vpds.ibshxc1);                 
                               /// Translate x = -vpds.ibshxc1                 
                               place.TranslateZ(-(vpds.ibshzc1+ewshift));                 
                               /// Translate z = -(vpds.ibshzc1+ewshift)                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSH"), place );                 
                         } // end placement of IBSH              
                         { AgPlacement place = AgPlacement("IBSH","CAVE");                 
                               /// Add daughter volume IBSH to mother CAVE                 
                               place.TranslateX(+vpds.ibshxc2);                 
                               /// Translate x = +vpds.ibshxc2                 
                               place.TranslateZ(+vpds.ibshzc2);                 
                               /// Translate z = +vpds.ibshzc2                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSH"), place );                 
                         } // end placement of IBSH              
                         { AgPlacement place = AgPlacement("IBSH","CAVE");                 
                               /// Add daughter volume IBSH to mother CAVE                 
                               place.TranslateX(-vpds.ibshxc2);                 
                               /// Translate x = -vpds.ibshxc2                 
                               place.TranslateZ(+vpds.ibshzc2);                 
                               /// Translate z = +vpds.ibshzc2                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSH"), place );                 
                         } // end placement of IBSH              
                         { AgPlacement place = AgPlacement("IBSH","CAVE");                 
                               /// Add daughter volume IBSH to mother CAVE                 
                               place.TranslateX(+vpds.ibshxc2);                 
                               /// Translate x = +vpds.ibshxc2                 
                               place.TranslateZ(-(vpds.ibshzc2+ewshift));                 
                               /// Translate z = -(vpds.ibshzc2+ewshift)                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSH"), place );                 
                         } // end placement of IBSH              
                         { AgPlacement place = AgPlacement("IBSH","CAVE");                 
                               /// Add daughter volume IBSH to mother CAVE                 
                               place.TranslateX(-vpds.ibshxc2);                 
                               /// Translate x = -vpds.ibshxc2                 
                               place.TranslateZ(-(vpds.ibshzc2+ewshift));                 
                               /// Translate z = -(vpds.ibshzc2+ewshift)                 
                               place.AlphaY(90);                 
                               /// Rotate: AlphaY = 90                 
                               /// G3 Reference: thetax = 90                 
                               /// G3 Reference: phix = 0                 
                               /// G3 Reference: thetay = 90                 
                               /// G3 Reference: phiy = 90                 
                               /// G3 Reference: thetaz = 0                 
                               /// G3 Reference: phiz = 0                 
                               _stacker -> Position( AgBlock::Find("IBSH"), place );                 
                         } // end placement of IBSH              
                   }           
             }        
             else        
             {           
             }        
       }; // VpddGeo2     
 }; // namespace VpddGeo2  
 