#include "SvttGeo4.h"  
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
 namespace SVTTGEO4 // $NMSPC  
 {     
       //     
       // ---------------------------------------------------------------------------------------------------     
          //  -----------------------------------------------------     
          /// @defgroup svtg_doc     
          /// \class Svtg_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Int_t nlayer;     
          ///Float_t rsizemin;     
          ///Float_t rsizemax;     
          ///Float_t zsizemax;     
          ///Float_t angoff;     
          ///Float_t supportver;     
          ///Float_t conever;     
          ///Float_t ifmany;     
          ///Float_t nmin;     
          ///Int_t _index;     
          //     
          Svtg_t svtg;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup swca_doc     
          /// \class Swca_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t length;     
          ///Float_t waferwid;     
          ///Float_t waferlen;     
          ///Float_t waferthk;     
          ///Float_t rohathk;     
          ///Float_t wafcarwd;     
          ///Float_t wafcarth;     
          ///Float_t wafergap;     
          ///Float_t drift;     
          ///Float_t strutlen;     
          ///Int_t _index;     
          //     
          Swca_t swca;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup ssup_doc     
          /// \class Ssup_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t cabthk;     
          ///Float_t hosrmn;     
          ///Float_t hosrmx;     
          ///Float_t nhoses;     
          ///Float_t wrpmythk;     
          ///Float_t wrpalthk;     
          ///Float_t grphthk;     
          ///Float_t cone1zmn;     
          ///Float_t rodlen;     
          ///Float_t roddist;     
          ///Float_t rodid;     
          ///Float_t rodod;     
          ///Float_t con1idmn;     
          ///Float_t con3idmn;     
          ///Float_t con4idmn;     
          ///Float_t con4idmx;     
          ///Float_t cone3zmx;     
          ///Float_t cone4zmx;     
          ///Float_t brathk;     
          ///Float_t erjthk;     
          ///Float_t erjwid;     
          ///Float_t erjlen;     
          ///Float_t erjzdis;     
          ///Float_t erj1x;     
          ///Float_t erj2x;     
          ///Float_t erj2y;     
          ///Float_t erjrad;     
          ///Float_t erjdia;     
          ///Int_t _index;     
          //     
          Ssup_t ssup;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup ssub_doc     
          /// \class Ssub_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t kmountid;     
          ///Float_t kmountod;     
          ///Float_t kmntthk;     
          ///Float_t kmcutod;     
          ///Float_t kmcutid;     
          ///Float_t kmcutoa;     
          ///Float_t kmcutoff;     
          ///Float_t sringid;     
          ///Float_t sringod;     
          ///Float_t sringthk;     
          ///Float_t srcutphi;     
          ///Float_t srcutwid;     
          ///Float_t srcutout;     
          ///Float_t srcutin;     
          ///Float_t srollid;     
          ///Float_t srollod;     
          ///Float_t srolllen;     
          ///Float_t swirelen;     
          ///Float_t mblkhgh;     
          ///Float_t mblkowid;     
          ///Float_t mblkolen;     
          ///Float_t mblkiwid;     
          ///Float_t mblkilen;     
          ///Float_t mblkorad;     
          ///Float_t mblkirad;     
          ///Float_t mroddia;     
          ///Int_t _index;     
          //     
          Ssub_t ssub;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup swam_doc     
          /// \class Swam_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t zmin;     
          ///Float_t len;     
          ///Float_t rmin;     
          ///Float_t rmax;     
          ///Float_t tbrdthk;     
          ///Float_t wallthk;     
          ///Int_t _index;     
          //     
          Swam_t swam;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup serg_doc     
          /// \class Serg_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t irngtrmx;     
          ///Float_t irngprmn;     
          ///Float_t orngrmin;     
          ///Float_t orngrmax;     
          ///Float_t endrngth;     
          ///Float_t endrngzm;     
          ///Int_t _index;     
          //     
          Serg_t serg;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup selc_doc     
          /// \class Selc_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t bethk;     
          ///Float_t watthk;     
          ///Float_t beothk;     
          ///Float_t dyethk;     
          ///Float_t dyewid;     
          ///Float_t dyespc;     
          ///Float_t elcawid;     
          ///Float_t agpdthk;     
          ///Float_t glassthk;     
          ///Float_t cabthk;     
          ///Float_t cabwid;     
          ///Int_t _index;     
          //     
          Selc_t selc;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup svtl_doc     
          /// \class Svtl_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Int_t layer;     
          ///Float_t nladder;     
          ///Float_t nwafer;     
          ///Float_t radius;     
          ///Float_t bareedge;     
          ///Float_t pcblen;     
          ///Float_t pcbwidth;     
          ///Float_t pcbthk;     
          ///Float_t pcbgap;     
          ///Int_t _index;     
          //     
          Svtl_t svtl;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup ssld_doc     
          /// \class Ssld_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t sinrinn;     
          ///Float_t sinrout;     
          ///Float_t sinlen;     
          ///Float_t sseprinn;     
          ///Float_t sseprout;     
          ///Float_t sseplen;     
          ///Float_t soutrinn;     
          ///Float_t soutrout;     
          ///Float_t soutlen;     
          ///Float_t almeshid;     
          ///Float_t almeshod;     
          ///Float_t almshthk;     
          ///Float_t almshpos;     
          ///Int_t _index;     
          //     
          Ssld_t ssld;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup scbp_doc     
          /// \class Scbp_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Int_t layer;     
          ///Float_t len;     
          ///Float_t rmin1;     
          ///Float_t rmax1;     
          ///Float_t rmin2;     
          ///Float_t rmax2;     
          ///Float_t vol;     
          ///Int_t _index;     
          //     
          Scbp_t scbp;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup sfep_doc     
          /// \class Sfep_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Int_t layer;     
          ///Float_t len;     
          ///Float_t rmin1;     
          ///Float_t rmax1;     
          ///Float_t rmin2;     
          ///Float_t rmax2;     
          ///Float_t vol;     
          ///Float_t volplast;     
          ///Int_t _index;     
          //     
          Sfep_t sfep;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup swcx_doc     
          /// \class Swcx_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Int_t layer;     
          ///Float_t length;     
          ///Float_t dr;     
          ///Float_t offset;     
          ///Float_t rad;     
          ///Float_t wall;     
          ///Float_t roffset;     
          ///Int_t _index;     
          //     
          Swcx_t swcx;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup soup_doc     
          /// \class Soup_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t length;     
          ///Float_t rout;     
          ///Float_t dr;     
          ///Float_t phi1;     
          ///Float_t phi2;     
          ///Float_t diamout;     
          ///Float_t diamin;     
          ///Int_t _index;     
          //     
          Soup_t soup;     
          //     
          ///@addtogroup SvttGeo4_vars     
          ///@{        
                Int_t ilayer,s,side,ilad,iwaf,i,j;        
                //        
                /// Int_t ilayer,s,side,ilad,iwaf,i,j        
          ///@}     
          ///@addtogroup SvttGeo4_vars     
          ///@{        
                Float_t ladthk,cone_thk1,cone_thk2,roffset,rsizemax,deg,rad,c0;        
                //        
                /// Float_t ladthk,cone_thk1,cone_thk2,roffset,rsizemax,deg,rad,c0        
          ///@}     
          ///@addtogroup SvttGeo4_vars     
          ///@{        
                Float_t cone_len,cone_sin,cone_cos,rmin,rmax,zmin,zmax,angle;        
                //        
                /// Float_t cone_len,cone_sin,cone_cos,rmin,rmax,zmin,zmax,angle        
          ///@}     
          ///@addtogroup SvttGeo4_vars     
          ///@{        
                Float_t xpos,ypos,zpos,clearance,rin,rou,elethk,tablen,radmax;        
                //        
                /// Float_t xpos,ypos,zpos,clearance,rin,rou,elethk,tablen,radmax        
          ///@}     
          ///@addtogroup SvttGeo4_vars     
          ///@{        
                Float_t endrng_z,brack_z,screw_z,ir_rmin,ang,wafpcklen,dthk,radtilt;        
                //        
                /// Float_t endrng_z,brack_z,screw_z,ir_rmin,ang,wafpcklen,dthk,radtilt        
          ///@}     
          ///@addtogroup SvttGeo4_vars     
          ///@{        
                Float_t xbuf,phi,xbuf1,xbuf2;        
                //        
                /// Float_t xbuf,phi,xbuf1,xbuf2        
          ///@}     
          ///@addtogroup SvttGeo4_vars     
          ///@{        
                Float_t ypcb,a,cuthk,sq,tube_angle;        
                //        
                /// Float_t ypcb,a,cuthk,sq,tube_angle        
          ///@}     
          ///@addtogroup SvttGeo4_vars     
          ///@{        
                Float_t rad_offset;        
                //        
                /// Float_t rad_offset        
                Array_t<Float_t> radii(6);        
                /// radii(6) : array of Float_t        
                Array_t<Float_t> rad_cones_in(5);        
                /// rad_cones_in(5) : array of Float_t        
                Array_t<Float_t> rad_cones_out(5);        
                /// rad_cones_out(5) : array of Float_t        
                Array_t<Float_t> shield_phi(4);        
                /// shield_phi(4) : array of Float_t        
          ///@}     
          ///@addtogroup SvttGeo4_vars     
          ///@{        
                Int_t i_phi;        
                //        
                /// Int_t i_phi        
          ///@}     
       SvttGeo4::SvttGeo4()     
         : AgModule("SvttGeo4","  is the SVT geometry for STAR: corrected ELECTRONICS ")     
       {        
       }     
          // ---------------------------------------------------------------------------------------------------     
          void SVTT::Block( AgCreate create )     
          {         
                ///@addtogroup SVTT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      rsizemax=ssup.con4idmx;           
                      rsizemax=rsizemax+ssup.grphthk+ssup.cabthk+2.0*ssup.hosrmx;           
                      rsizemax=rsizemax+ssup.wrpmythk+ssup.wrpalthk;           
                      clearance=svtg.rsizemax-rsizemax;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SVTT");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=svtg.rsizemin;              
                            shape.par("rmax")=svtg.rsizemax;              
                            shape.par("dz")=svtg.zsizemax;              
                            /// Shape Tube rmin=svtg.rsizemin rmax=svtg.rsizemax dz=svtg.zsizemax               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SVTT;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SIRP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SIRP              
                            Create("SIRP");               
                      }           
                      { AgPlacement place = AgPlacement("SIRP","SVTT");              
                            /// Add daughter volume SIRP to mother SVTT              
                            place.TranslateZ(serg.endrngzm+serg.endrngth/2);              
                            /// Translate z = serg.endrngzm+serg.endrngth/2              
                            place.AlphaZ(22.5);              
                            /// Rotate: AlphaZ = 22.5              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SIRP"), place );              
                      } // end placement of SIRP           
                      { AgPlacement place = AgPlacement("SIRP","SVTT");              
                            /// Add daughter volume SIRP to mother SVTT              
                            place.TranslateZ(-serg.endrngzm-serg.endrngth/2);              
                            /// Translate z = -serg.endrngzm-serg.endrngth/2              
                            place.AlphaZ(22.5);              
                            /// Rotate: AlphaZ = 22.5              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SIRP"), place );              
                      } // end placement of SIRP           
                      _create = AgCreate("SIRT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SIRT              
                            Create("SIRT");               
                      }           
                      { AgPlacement place = AgPlacement("SIRT","SVTT");              
                            /// Add daughter volume SIRT to mother SVTT              
                            place.TranslateZ(serg.endrngzm+serg.endrngth/2);              
                            /// Translate z = serg.endrngzm+serg.endrngth/2              
                            place.AlphaZ(22.5);              
                            /// Rotate: AlphaZ = 22.5              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SIRT"), place );              
                      } // end placement of SIRT           
                      { AgPlacement place = AgPlacement("SIRT","SVTT");              
                            /// Add daughter volume SIRT to mother SVTT              
                            place.TranslateZ(-serg.endrngzm-serg.endrngth/2);              
                            /// Translate z = -serg.endrngzm-serg.endrngth/2              
                            place.AlphaZ(22.5);              
                            /// Rotate: AlphaZ = 22.5              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SIRT"), place );              
                      } // end placement of SIRT           
                      _create = AgCreate("SOER");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SOER              
                            Create("SOER");               
                      }           
                      { AgPlacement place = AgPlacement("SOER","SVTT");              
                            /// Add daughter volume SOER to mother SVTT              
                            place.TranslateZ(serg.endrngzm+serg.endrngth/2);              
                            /// Translate z = serg.endrngzm+serg.endrngth/2              
                            _stacker -> Position( AgBlock::Find("SOER"), place );              
                      } // end placement of SOER           
                      { AgPlacement place = AgPlacement("SOER","SVTT");              
                            /// Add daughter volume SOER to mother SVTT              
                            place.TranslateZ(-serg.endrngzm-serg.endrngth/2);              
                            /// Translate z = -serg.endrngzm-serg.endrngth/2              
                            _stacker -> Position( AgBlock::Find("SOER"), place );              
                      } // end placement of SOER           
                      _create = AgCreate("SBRG");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBRG              
                            Create("SBRG");               
                      }           
                      { AgPlacement place = AgPlacement("SBRG","SVTT");              
                            /// Add daughter volume SBRG to mother SVTT              
                            place.TranslateZ(swca.length/2+ssup.erjzdis+ssup.erjthk/2);              
                            /// Translate z = swca.length/2+ssup.erjzdis+ssup.erjthk/2              
                            _stacker -> Position( AgBlock::Find("SBRG"), place );              
                      } // end placement of SBRG           
                      { AgPlacement place = AgPlacement("SBRG","SVTT");              
                            /// Add daughter volume SBRG to mother SVTT              
                            place.TranslateZ(-swca.length/2-ssup.erjzdis-ssup.erjthk/2);              
                            /// Translate z = -swca.length/2-ssup.erjzdis-ssup.erjthk/2              
                            _stacker -> Position( AgBlock::Find("SBRG"), place );              
                      } // end placement of SBRG           
                      endrng_z=serg.endrngzm+serg.endrngth;           
                      brack_z=swca.length/2+ssup.erjzdis;           
                      screw_z=endrng_z+0.5*(brack_z-endrng_z);           
                      _create = AgCreate("SOES");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SOES              
                            Create("SOES");               
                      }           
                      { AgPlacement place = AgPlacement("SOES","SVTT");              
                            /// Add daughter volume SOES to mother SVTT              
                            place.TranslateZ(screw_z);              
                            /// Translate z = screw_z              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SOES"), place );              
                      } // end placement of SOES           
                      { AgPlacement place = AgPlacement("SOES","SVTT");              
                            /// Add daughter volume SOES to mother SVTT              
                            place.TranslateZ(-screw_z);              
                            /// Translate z = -screw_z              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SOES"), place );              
                      } // end placement of SOES           
                      _create = AgCreate("SIES");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SIES              
                            Create("SIES");               
                      }           
                      { AgPlacement place = AgPlacement("SIES","SVTT");              
                            /// Add daughter volume SIES to mother SVTT              
                            place.TranslateZ(screw_z);              
                            /// Translate z = screw_z              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SIES"), place );              
                      } // end placement of SIES           
                      { AgPlacement place = AgPlacement("SIES","SVTT");              
                            /// Add daughter volume SIES to mother SVTT              
                            place.TranslateZ(-screw_z);              
                            /// Translate z = -screw_z              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SIES"), place );              
                      } // end placement of SIES           
                      if ( swam.len>0 )           
                      {              
                            _create = AgCreate("SWMM");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SWMM                 
                                  Create("SWMM");                  
                            }              
                            { AgPlacement place = AgPlacement("SWMM","SVTT");                 
                                  /// Add daughter volume SWMM to mother SVTT                 
                                  place.TranslateZ(swam.zmin+swam.len/2);                 
                                  /// Translate z = swam.zmin+swam.len/2                 
                                  _stacker -> Position( AgBlock::Find("SWMM"), place );                 
                            } // end placement of SWMM              
                            { AgPlacement place = AgPlacement("SWMM","SVTT");                 
                                  /// Add daughter volume SWMM to mother SVTT                 
                                  place.TranslateZ(-swam.zmin-swam.len/2);                 
                                  /// Translate z = -swam.zmin-swam.len/2                 
                                  _stacker -> Position( AgBlock::Find("SWMM"), place );                 
                            } // end placement of SWMM              
                      }           
                      if ( swam.len>0 )           
                      {              
                            _create = AgCreate("SBWC");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SBWC                 
                                  Create("SBWC");                  
                            }              
                            { AgPlacement place = AgPlacement("SBWC","SVTT");                 
                                  /// Add daughter volume SBWC to mother SVTT                 
                                  place.TranslateZ((swam.zmin+swam.len+(ssup.cone1zmn-(swam.zmin+swam.len))/2));                 
                                  /// Translate z = (swam.zmin+swam.len+(ssup.cone1zmn-(swam.zmin+swam.len))/2)                 
                                  _stacker -> Position( AgBlock::Find("SBWC"), place );                 
                            } // end placement of SBWC              
                            { AgPlacement place = AgPlacement("SBWC","SVTT");                 
                                  /// Add daughter volume SBWC to mother SVTT                 
                                  place.TranslateZ(-(swam.zmin+swam.len+(ssup.cone1zmn-(swam.zmin+swam.len))/2));                 
                                  /// Translate z = -(swam.zmin+swam.len+(ssup.cone1zmn-(swam.zmin+swam.len))/2)                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 180                 
                                  /// G3 Reference: phiz = 0                 
                                  Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;                 
                                  place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );                 
                                  _stacker -> Position( AgBlock::Find("SBWC"), place );                 
                            } // end placement of SBWC              
                      }           
                      _create = AgCreate("SCON");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCON              
                            Create("SCON");               
                      }           
                      { AgPlacement place = AgPlacement("SCON","SVTT");              
                            /// Add daughter volume SCON to mother SVTT              
                            _stacker -> Position( AgBlock::Find("SCON"), place );              
                      } // end placement of SCON           
                      { AgPlacement place = AgPlacement("SCON","SVTT");              
                            /// Add daughter volume SCON to mother SVTT              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 180              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("SCON"), place );              
                      } // end placement of SCON           
                      _create = AgCreate("SBSP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBSP              
                            Create("SBSP");               
                      }           
                      { AgPlacement place = AgPlacement("SBSP","SVTT");              
                            /// Add daughter volume SBSP to mother SVTT              
                            place.TranslateZ((ssup.rodlen/2-ssub.kmntthk/2));              
                            /// Translate z = (ssup.rodlen/2-ssub.kmntthk/2)              
                            _stacker -> Position( AgBlock::Find("SBSP"), place );              
                      } // end placement of SBSP           
                      { AgPlacement place = AgPlacement("SBSP","SVTT");              
                            /// Add daughter volume SBSP to mother SVTT              
                            place.TranslateZ(-(ssup.rodlen/2-ssub.kmntthk/2));              
                            /// Translate z = -(ssup.rodlen/2-ssub.kmntthk/2)              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 180              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("SBSP"), place );              
                      } // end placement of SBSP           
                      _create = AgCreate("SROD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SROD              
                            Create("SROD");               
                      }           
                      { AgPlacement place = AgPlacement("SROD","SVTT");              
                            /// Add daughter volume SROD to mother SVTT              
                            place.TranslateY(ssup.roddist+ssup.rodod/2);              
                            /// Translate y = ssup.roddist+ssup.rodod/2              
                            _stacker -> Position( AgBlock::Find("SROD"), place );              
                      } // end placement of SROD           
                      { AgPlacement place = AgPlacement("SROD","SVTT");              
                            /// Add daughter volume SROD to mother SVTT              
                            place.TranslateY(-ssup.roddist-ssup.rodod/2);              
                            /// Translate y = -ssup.roddist-ssup.rodod/2              
                            _stacker -> Position( AgBlock::Find("SROD"), place );              
                      } // end placement of SROD           
                      radmax=svtg.rsizemax;           
                      /// Loop on ilayer from svtg.nmin to min(6,svtg.nlayer) step=1           
                      for ( ilayer=svtg.nmin; (1>0)? (ilayer<=min(6,svtg.nlayer)):(ilayer>=min(6,svtg.nlayer)); ilayer+=1 )           
                      {              
                            if ( ilayer<6 )              
                            {                 
                                  /// USE svtl layer=ilayer+1 ;                 
                                  svtl.Use("layer",(Int_t)ilayer+1 );                 
                                  radmax=svtl.radius;                 
                            }              
                            else              
                            {                 
                                  radmax=svtg.rsizemax;                 
                            }              
                            /// USE svtl layer=ilayer ;              
                            svtl.Use("layer",(Int_t)ilayer );              
                            _create = AgCreate("SLYD");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SLYD                 
                                  Create("SLYD");                  
                            }              
                            if ( ilayer==2||ilayer==4||ilayer==6 )              
                            {                 
                                  { AgPlacement place = AgPlacement("SLYD","SVTT");                    
                                        /// Add daughter volume SLYD to mother SVTT                    
                                        place.par("only")=AgPlacement::kMany;                    
                                        /// Overlap: agplacement::kmany                    
                                        _stacker -> Position( AgBlock::Find("SLYD"), place );                    
                                  } // end placement of SLYD                 
                            }              
                            else              
                            {                 
                                  { AgPlacement place = AgPlacement("SLYD","SVTT");                    
                                        /// Add daughter volume SLYD to mother SVTT                    
                                        _stacker -> Position( AgBlock::Find("SLYD"), place );                    
                                  } // end placement of SLYD                 
                            }              
                      }           
                      if ( svtg.nlayer<0 )           
                      {              
                            /// USE svtl layer=-svtg.nlayer ;              
                            svtl.Use("layer",(Int_t)-svtg.nlayer );              
                            _create = AgCreate("SLYD");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SLYD                 
                                  Create("SLYD");                  
                            }              
                            { AgPlacement place = AgPlacement("SLYD","SVTT");                 
                                  /// Add daughter volume SLYD to mother SVTT                 
                                  _stacker -> Position( AgBlock::Find("SLYD"), place );                 
                            } // end placement of SLYD              
                      }           
                      _create = AgCreate("SISH");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SISH              
                            Create("SISH");               
                      }           
                      { AgPlacement place = AgPlacement("SISH","SVTT");              
                            /// Add daughter volume SISH to mother SVTT              
                            _stacker -> Position( AgBlock::Find("SISH"), place );              
                      } // end placement of SISH           
                      _create = AgCreate("SOSH");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SOSH              
                            Create("SOSH");               
                      }           
                      { AgPlacement place = AgPlacement("SOSH","SVTT");              
                            /// Add daughter volume SOSH to mother SVTT              
                            _stacker -> Position( AgBlock::Find("SOSH"), place );              
                      } // end placement of SOSH           
                      if ( svtg.nlayer>6 )           
                      {              
                            _create = AgCreate("SSSH");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SSSH                 
                                  Create("SSSH");                  
                            }              
                            { AgPlacement place = AgPlacement("SSSH","SVTT");                 
                                  /// Add daughter volume SSSH to mother SVTT                 
                                  _stacker -> Position( AgBlock::Find("SSSH"), place );                 
                            } // end placement of SSSH              
                      }           
                      _create = AgCreate("SALM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SALM              
                            Create("SALM");               
                      }           
                      { AgPlacement place = AgPlacement("SALM","SVTT");              
                            /// Add daughter volume SALM to mother SVTT              
                            place.TranslateZ(ssld.almshpos-ssld.almshthk/2);              
                            /// Translate z = ssld.almshpos-ssld.almshthk/2              
                            _stacker -> Position( AgBlock::Find("SALM"), place );              
                      } // end placement of SALM           
                      { AgPlacement place = AgPlacement("SALM","SVTT");              
                            /// Add daughter volume SALM to mother SVTT              
                            place.TranslateZ(-(ssld.almshpos-ssld.almshthk/2));              
                            /// Translate z = -(ssld.almshpos-ssld.almshthk/2)              
                            _stacker -> Position( AgBlock::Find("SALM"), place );              
                      } // end placement of SALM           
                      _create = AgCreate("SCBM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCBM              
                            Create("SCBM");               
                      }           
                      { AgPlacement place = AgPlacement("SCBM","SVTT");              
                            /// Add daughter volume SCBM to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(swam.zmin-scbp.len);              
                            /// Translate z = swam.zmin-scbp.len              
                            _stacker -> Position( AgBlock::Find("SCBM"), place );              
                      } // end placement of SCBM           
                      { AgPlacement place = AgPlacement("SCBM","SVTT");              
                            /// Add daughter volume SCBM to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(-(swam.zmin-scbp.len));              
                            /// Translate z = -(swam.zmin-scbp.len)              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 180.0              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180.0,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("SCBM"), place );              
                      } // end placement of SCBM           
                      /// USE svtl layer=6 ;           
                      svtl.Use("layer",(Int_t)6 );           
                      _create = AgCreate("SXRL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SXRL              
                            Create("SXRL");               
                      }           
                      { AgPlacement place = AgPlacement("SXRL","SVTT");              
                            /// Add daughter volume SXRL to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(swca.length/2.0-swcx.length/2.0-swcx.offset);              
                            /// Translate z = swca.length/2.0-swcx.length/2.0-swcx.offset              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SXRL"), place );              
                      } // end placement of SXRL           
                      { AgPlacement place = AgPlacement("SXRL","SVTT");              
                            /// Add daughter volume SXRL to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(-swca.length/2.0+swcx.length/2.0+swcx.offset);              
                            /// Translate z = -swca.length/2.0+swcx.length/2.0+swcx.offset              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SXRL"), place );              
                      } // end placement of SXRL           
                      /// USE svtl layer=4 ;           
                      svtl.Use("layer",(Int_t)4 );           
                      _create = AgCreate("SXRL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SXRL              
                            Create("SXRL");               
                      }           
                      { AgPlacement place = AgPlacement("SXRL","SVTT");              
                            /// Add daughter volume SXRL to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(swca.length/2.0-swcx.length/2.0-swcx.offset);              
                            /// Translate z = swca.length/2.0-swcx.length/2.0-swcx.offset              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SXRL"), place );              
                      } // end placement of SXRL           
                      { AgPlacement place = AgPlacement("SXRL","SVTT");              
                            /// Add daughter volume SXRL to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(-swca.length/2.0+swcx.length/2.0+swcx.offset);              
                            /// Translate z = -swca.length/2.0+swcx.length/2.0+swcx.offset              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SXRL"), place );              
                      } // end placement of SXRL           
                      /// USE svtl layer=2 ;           
                      svtl.Use("layer",(Int_t)2 );           
                      _create = AgCreate("SXRL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SXRL              
                            Create("SXRL");               
                      }           
                      { AgPlacement place = AgPlacement("SXRL","SVTT");              
                            /// Add daughter volume SXRL to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(swca.length/2.0-swcx.length/2.0-swcx.offset);              
                            /// Translate z = swca.length/2.0-swcx.length/2.0-swcx.offset              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SXRL"), place );              
                      } // end placement of SXRL           
                      { AgPlacement place = AgPlacement("SXRL","SVTT");              
                            /// Add daughter volume SXRL to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(-swca.length/2.0+swcx.length/2.0+swcx.offset);              
                            /// Translate z = -swca.length/2.0+swcx.length/2.0+swcx.offset              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SXRL"), place );              
                      } // end placement of SXRL           
                      _create = AgCreate("SOUM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SOUM              
                            Create("SOUM");               
                      }           
                      { AgPlacement place = AgPlacement("SOUM","SVTT");              
                            /// Add daughter volume SOUM to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            _stacker -> Position( AgBlock::Find("SOUM"), place );              
                      } // end placement of SOUM           
                      { AgPlacement place = AgPlacement("SOUM","SVTT");              
                            /// Add daughter volume SOUM to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            place.AlphaY(180.0);              
                            /// Rotate: AlphaY = 180.0              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SOUM"), place );              
                      } // end placement of SOUM           
                      { AgPlacement place = AgPlacement("SOUM","SVTT");              
                            /// Add daughter volume SOUM to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            place.AlphaY(180.0);              
                            /// Rotate: AlphaY = 180.0              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.AlphaZ(180);              
                            /// Rotate: AlphaZ = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SOUM"), place );              
                      } // end placement of SOUM           
                      { AgPlacement place = AgPlacement("SOUM","SVTT");              
                            /// Add daughter volume SOUM to mother SVTT              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            place.AlphaZ(180);              
                            /// Rotate: AlphaZ = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SOUM"), place );              
                      } // end placement of SOUM           
                      END_OF_SVTT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SVTT     
          // ---------------------------------------------------------------------------------------------------     
          void SXRL::Block( AgCreate create )     
          {         
                ///@addtogroup SXRL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SXRL");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=swcx.roffset+svtl.radius;              
                            shape.par("rmax")=swcx.roffset+svtl.radius+swcx.dr;              
                            shape.par("dz")=swcx.length/2.0;              
                            /// Shape Tube rmin=swcx.roffset+svtl.radius rmax=swcx.roffset+svtl.radius+swcx.dr dz=swcx.length/2.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SXRL;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SWRP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWRP              
                            Create("SWRP");               
                      }           
                      _create = AgCreate("SYRU");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SYRU              
                            Create("SYRU");               
                      }           
                      /// Loop on i_phi from 1 to 4*svtl.nladder step=1           
                      for ( i_phi=1; (1>0)? (i_phi<=4*svtl.nladder):(i_phi>=4*svtl.nladder); i_phi+=1 )           
                      {              
                            tube_angle=(pi/(2.0*svtl.nladder))*(i_phi-0.5);              
                            { AgPlacement place = AgPlacement("SWRP","SXRL");                 
                                  /// Add daughter volume SWRP to mother SXRL                 
                                  place.TranslateX(cos(tube_angle)*(svtl.radius+swcx.roffset+swcx.dr/2.0));                 
                                  /// Translate x = cos(tube_angle)*(svtl.radius+swcx.roffset+swcx.dr/2.0)                 
                                  place.TranslateY(sin(tube_angle)*(svtl.radius+swcx.roffset+swcx.dr/2.0));                 
                                  /// Translate y = sin(tube_angle)*(svtl.radius+swcx.roffset+swcx.dr/2.0)                 
                                  place.TranslateZ(0.0);                 
                                  /// Translate z = 0.0                 
                                  _stacker -> Position( AgBlock::Find("SWRP"), place );                 
                            } // end placement of SWRP              
                            { AgPlacement place = AgPlacement("SYRU","SXRL");                 
                                  /// Add daughter volume SYRU to mother SXRL                 
                                  place.TranslateX(cos(tube_angle)*(svtl.radius+swcx.roffset+swcx.dr/2.0));                 
                                  /// Translate x = cos(tube_angle)*(svtl.radius+swcx.roffset+swcx.dr/2.0)                 
                                  place.TranslateY(sin(tube_angle)*(svtl.radius+swcx.roffset+swcx.dr/2.0));                 
                                  /// Translate y = sin(tube_angle)*(svtl.radius+swcx.roffset+swcx.dr/2.0)                 
                                  place.TranslateZ(0.0);                 
                                  /// Translate z = 0.0                 
                                  _stacker -> Position( AgBlock::Find("SYRU"), place );                 
                            } // end placement of SYRU              
                      }           
                      END_OF_SXRL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SXRL     
          // ---------------------------------------------------------------------------------------------------     
          void SWRP::Block( AgCreate create )     
          {         
                ///@addtogroup SWRP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Water            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Water");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SWRP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0.0;              
                            shape.par("rmax")=swcx.rad;              
                            shape.par("dz")=swcx.length/2.0;              
                            /// Shape Tube rmin=0.0 rmax=swcx.rad dz=swcx.length/2.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWRP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SWRP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWRP     
          // ---------------------------------------------------------------------------------------------------     
          void SYRU::Block( AgCreate create )     
          {         
                ///@addtogroup SYRU_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component C	a=12	z=6	w=1           
                      /// Component H2	a=1	z=1	w=2           
                      /// Mixture CH2 dens=0.935           
                      {  AgMaterial &mix = AgMaterial::Get("Ch2");              
                            mix.Component("C",12,6,1);              
                            mix.Component("H2",1,1,2);              
                            mix.par("dens")=0.935;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("SYRU");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=swcx.rad;              
                            shape.par("rmax")=swcx.rad+swcx.wall;              
                            shape.par("dz")=swcx.length/2.0;              
                            /// Shape Tube rmin=swcx.rad rmax=swcx.rad+swcx.wall dz=swcx.length/2.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SYRU;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SYRU:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SYRU     
          // ---------------------------------------------------------------------------------------------------     
          void SOUM::Block( AgCreate create )     
          {         
                ///@addtogroup SOUM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SOUM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=soup.rout-soup.dr;              
                            shape.par("rmax")=soup.rout;              
                            shape.par("phi1")=soup.phi1;              
                            shape.par("phi2")=soup.phi2;              
                            shape.par("dz")=soup.length/2.0;              
                            /// Shape Tubs rmin=soup.rout-soup.dr rmax=soup.rout phi1=soup.phi1 phi2=soup.phi2 dz=soup.length/2.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SOUM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SOUR");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SOUR              
                            Create("SOUR");               
                      }           
                      /// Loop on i_phi from 1 to 4 step=1           
                      for ( i_phi=1; (1>0)? (i_phi<=4):(i_phi>=4); i_phi+=1 )           
                      {              
                            { AgPlacement place = AgPlacement("SOUR","SOUM");                 
                                  /// Add daughter volume SOUR to mother SOUM                 
                                  place.TranslateX(cos(shield_phi(i_phi)*pi/180.0)*(soup.rout-soup.dr/2.0));                 
                                  /// Translate x = cos(shield_phi(i_phi)*pi/180.0)*(soup.rout-soup.dr/2.0)                 
                                  place.TranslateY(sin(shield_phi(i_phi)*pi/180.0)*(soup.rout-soup.dr/2.0));                 
                                  /// Translate y = sin(shield_phi(i_phi)*pi/180.0)*(soup.rout-soup.dr/2.0)                 
                                  place.TranslateZ(0.0);                 
                                  /// Translate z = 0.0                 
                                  _stacker -> Position( AgBlock::Find("SOUR"), place );                 
                            } // end placement of SOUR              
                      }           
                      END_OF_SOUM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SOUM     
          // ---------------------------------------------------------------------------------------------------     
          void SOUR::Block( AgCreate create )     
          {         
                ///@addtogroup SOUR_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SOUM");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=soup.diamin/2.0;              
                            shape.par("rmax")=soup.diamout/2.0;              
                            shape.par("dz")=soup.length/2.0;              
                            /// Shape Tube rmin=soup.diamin/2.0 rmax=soup.diamout/2.0 dz=soup.length/2.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SOUR;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SOUR:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SOUR     
          // ---------------------------------------------------------------------------------------------------     
          void SLYD::Block( AgCreate create )     
          {         
                ///@addtogroup SLYD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      ladthk = swca.waferthk/2+swca.rohathk+swca.wafcarth;           
                      elethk=2.0*selc.bethk+selc.watthk+selc.beothk+selc.agpdthk;           
                      elethk=elethk+selc.glassthk+selc.dyethk;           
                      deg=180.0/svtl.nladder;           
                      rad=pi/svtl.nladder;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SLYD");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      rmin=svtl.radius-ladthk;           
                      rmax  = svtl.radius*svtl.radius;           
                      rmax += swca.waferwid * swca.waferwid / 4.0;           
                      rmax  = sqrt(rmax) + elethk;           
                      rmax=min(rmax,radmax-ladthk);           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=rmin;              
                            shape.par("rmax")=rmax;              
                            shape.par("dz")=swca.length/2;              
                            /// Shape Tube rmin=rmin rmax=rmax dz=swca.length/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SLYD;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SLSD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SLSD              
                            Create("SLSD");               
                      }           
                      END_OF_SLYD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SLYD     
          // ---------------------------------------------------------------------------------------------------     
          void SLSD::Block( AgCreate create )     
          {         
                ///@addtogroup SLSD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SLSD");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      if ( svtg.nlayer<0 )           
                      {              
                            {  AgShape shape = AgShape("Division");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("ndiv")=1;                 
                                  shape.par("iaxis")=2;                 
                                  shape.par("c0")=-90;                 
                                  /// Shape Division ndiv=1 iaxis=2 c0=-90                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_SLSD;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      else           
                      {              
                            if ( svtg.version==1 )              
                            {                 
                                  c0=-deg*mod(ilayer,2)+svtg.angoff*int((ilayer-1)/2);                 
                            }              
                            else              
                            {                 
                                  c0=90-deg*mod(ilayer,2);                 
                            }              
                            {  AgShape shape = AgShape("Division");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("ndiv")=svtl.nladder;                 
                                  shape.par("iaxis")=2;                 
                                  shape.par("c0")=c0;                 
                                  /// Shape Division ndiv=svtl.nladder iaxis=2 c0=c0                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_SLSD;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      _create = AgCreate("SLDI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SLDI              
                            Create("SLDI");               
                      }           
                      { AgPlacement place = AgPlacement("SLDI","SLSD");              
                            /// Add daughter volume SLDI to mother SLSD              
                            place.TranslateX(svtl.radius);              
                            /// Translate x = svtl.radius              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "YZX" ); // ORT=YZX              
                            /// Axis substitution: XYZ --> YZX              
                            _stacker -> Position( AgBlock::Find("SLDI"), place );              
                      } // end placement of SLDI           
                      _create = AgCreate("SELE");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SELE              
                            Create("SELE");               
                      }           
                      deg=180.0/svtl.nladder;           
                      rad=(twopi/2)/svtl.nladder;           
                      xpos=sin(rad)*selc.elcawid/2-cos(rad)*elethk/2;           
                      ypos=cos(rad)*selc.elcawid/2+sin(rad)*elethk/2;           
                      /// Loop on s from -1 to 1 step=2           
                      for ( s=-1; (2>0)? (s<=1):(s>=1); s+=2 )           
                      {              
                            side=s;              
                            { AgPlacement place = AgPlacement("SELE","SLSD");                 
                                  /// Add daughter volume SELE to mother SLSD                 
                                  place.TranslateX(svtl.radius-ladthk-xpos);                 
                                  /// Translate x = svtl.radius-ladthk-xpos                 
                                  place.TranslateY(s*(swca.waferwid/2+ypos));                 
                                  /// Translate y = s*(swca.waferwid/2+ypos)                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YZX" ); // ORT=YZX                 
                                  /// Axis substitution: XYZ --> YZX                 
                                  place.AlphaX(90*(1-s));                 
                                  /// Rotate: AlphaX = 90*(1-s)                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.AlphaZ(s*deg);                 
                                  /// Rotate: AlphaZ = s*deg                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SELE"), place );                 
                            } // end placement of SELE              
                      }           
                      END_OF_SLSD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SLSD     
          // ---------------------------------------------------------------------------------------------------     
          void SLDI::Block( AgCreate create )     
          {         
                ///@addtogroup SLDI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      tablen=swca.length/2-7*(swca.waferwid/2+swca.wafergap);           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SLDI");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.par("serial")=svtl.nwafer;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=swca.waferwid/2;              
                            shape.par("dy")=swca.length/2;              
                            shape.par("dz")=ladthk;              
                            /// Shape Bbox dx=swca.waferwid/2 dy=swca.length/2 dz=ladthk               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SLDI;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("STLI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create STLI              
                            Create("STLI");               
                      }           
                      { AgPlacement place = AgPlacement("STLI","SLDI");              
                            /// Add daughter volume STLI to mother SLDI              
                            _stacker -> Position( AgBlock::Find("STLI"), place );              
                      } // end placement of STLI           
                      _create = AgCreate("SBER");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBER              
                            Create("SBER");               
                      }           
                      { AgPlacement place = AgPlacement("SBER","SLDI");              
                            /// Add daughter volume SBER to mother SLDI              
                            place.TranslateX(+swca.waferwid/2-swca.wafcarwd/2);              
                            /// Translate x = +swca.waferwid/2-swca.wafcarwd/2              
                            place.TranslateZ(-ladthk+swca.wafcarth/2);              
                            /// Translate z = -ladthk+swca.wafcarth/2              
                            _stacker -> Position( AgBlock::Find("SBER"), place );              
                      } // end placement of SBER           
                      { AgPlacement place = AgPlacement("SBER","SLDI");              
                            /// Add daughter volume SBER to mother SLDI              
                            place.TranslateX(-swca.waferwid/2+swca.wafcarwd/2);              
                            /// Translate x = -swca.waferwid/2+swca.wafcarwd/2              
                            place.TranslateZ(-ladthk+swca.wafcarth/2);              
                            /// Translate z = -ladthk+swca.wafcarth/2              
                            _stacker -> Position( AgBlock::Find("SBER"), place );              
                      } // end placement of SBER           
                      _create = AgCreate("STAB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create STAB              
                            Create("STAB");               
                      }           
                      { AgPlacement place = AgPlacement("STAB","SLDI");              
                            /// Add daughter volume STAB to mother SLDI              
                            place.TranslateY(swca.length/2-tablen/2);              
                            /// Translate y = swca.length/2-tablen/2              
                            place.TranslateZ(-ladthk+swca.wafcarth/2);              
                            /// Translate z = -ladthk+swca.wafcarth/2              
                            _stacker -> Position( AgBlock::Find("STAB"), place );              
                      } // end placement of STAB           
                      { AgPlacement place = AgPlacement("STAB","SLDI");              
                            /// Add daughter volume STAB to mother SLDI              
                            place.TranslateY(-swca.length/2+tablen/2);              
                            /// Translate y = -swca.length/2+tablen/2              
                            place.TranslateZ(-ladthk+swca.wafcarth/2);              
                            /// Translate z = -ladthk+swca.wafcarth/2              
                            _stacker -> Position( AgBlock::Find("STAB"), place );              
                      } // end placement of STAB           
                      _create = AgCreate("STRU");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create STRU              
                            Create("STRU");               
                      }           
                      { AgPlacement place = AgPlacement("STRU","SLDI");              
                            /// Add daughter volume STRU to mother SLDI              
                            place.TranslateY((svtl.nwafer*(swca.waferlen/2+swca.wafergap)+swca.wafergap+swca.strutlen/2));              
                            /// Translate y = (svtl.nwafer*(swca.waferlen/2+swca.wafergap)+swca.wafergap+swca.strutlen/2)              
                            place.TranslateZ(-ladthk+swca.wafcarth/2);              
                            /// Translate z = -ladthk+swca.wafcarth/2              
                            _stacker -> Position( AgBlock::Find("STRU"), place );              
                      } // end placement of STRU           
                      { AgPlacement place = AgPlacement("STRU","SLDI");              
                            /// Add daughter volume STRU to mother SLDI              
                            place.TranslateY(-(svtl.nwafer*(swca.waferlen/2+swca.wafergap)+swca.wafergap+swca.strutlen/2));              
                            /// Translate y = -(svtl.nwafer*(swca.waferlen/2+swca.wafergap)+swca.wafergap+swca.strutlen/2)              
                            place.TranslateZ(-ladthk+swca.wafcarth/2);              
                            /// Translate z = -ladthk+swca.wafcarth/2              
                            _stacker -> Position( AgBlock::Find("STRU"), place );              
                      } // end placement of STRU           
                      _create = AgCreate("SRHC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SRHC              
                            Create("SRHC");               
                      }           
                      { AgPlacement place = AgPlacement("SRHC","SLDI");              
                            /// Add daughter volume SRHC to mother SLDI              
                            place.TranslateX(+swca.waferwid/2-swca.wafcarwd/2);              
                            /// Translate x = +swca.waferwid/2-swca.wafcarwd/2              
                            place.TranslateZ(-ladthk+2.0*swca.wafcarth/2+swca.rohathk/2);              
                            /// Translate z = -ladthk+2.0*swca.wafcarth/2+swca.rohathk/2              
                            _stacker -> Position( AgBlock::Find("SRHC"), place );              
                      } // end placement of SRHC           
                      { AgPlacement place = AgPlacement("SRHC","SLDI");              
                            /// Add daughter volume SRHC to mother SLDI              
                            place.TranslateX(-swca.waferwid/2+swca.wafcarwd/2);              
                            /// Translate x = -swca.waferwid/2+swca.wafcarwd/2              
                            place.TranslateZ(-ladthk+2.0*swca.wafcarth/2+swca.rohathk/2);              
                            /// Translate z = -ladthk+2.0*swca.wafcarth/2+swca.rohathk/2              
                            _stacker -> Position( AgBlock::Find("SRHC"), place );              
                      } // end placement of SRHC           
                      _create = AgCreate("SPCB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SPCB              
                            Create("SPCB");               
                      }           
                      ypcb = svtl.nwafer*(swca.waferlen+swca.wafergap)/2.0 + svtl.pcbgap + svtl.pcblen/2.0;           
                      { AgPlacement place = AgPlacement("SPCB","SLDI");              
                            /// Add daughter volume SPCB to mother SLDI              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(ypcb);              
                            /// Translate y = ypcb              
                            place.TranslateZ(svtl.pcbthk/2.0);              
                            /// Translate z = svtl.pcbthk/2.0              
                            _stacker -> Position( AgBlock::Find("SPCB"), place );              
                      } // end placement of SPCB           
                      { AgPlacement place = AgPlacement("SPCB","SLDI");              
                            /// Add daughter volume SPCB to mother SLDI              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(-ypcb);              
                            /// Translate y = -ypcb              
                            place.TranslateZ(svtl.pcbthk/2.0);              
                            /// Translate z = svtl.pcbthk/2.0              
                            place.AlphaZ(180.0);              
                            /// Rotate: AlphaZ = 180.0              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SPCB"), place );              
                      } // end placement of SPCB           
                      END_OF_SLDI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SLDI     
          // ---------------------------------------------------------------------------------------------------     
          void SRHC::Block( AgCreate create )     
          {         
                ///@addtogroup SRHC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component C	a=12	z=6	w=1           
                      /// Component H2	a=1	z=1	w=2           
                      /// Mixture ROHA dens=0.0304           
                      {  AgMaterial &mix = AgMaterial::Get("Roha");              
                            mix.Component("C",12,6,1);              
                            mix.Component("H2",1,1,2);              
                            mix.par("dens")=0.0304;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("SRHC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=swca.wafcarwd/2;              
                            shape.par("dy")=svtl.nwafer*(swca.waferlen/2+swca.wafergap);              
                            shape.par("dz")=swca.rohathk/2;              
                            /// Shape Bbox dx=swca.wafcarwd/2 dy=svtl.nwafer*(swca.waferlen/2+swca.wafergap) dz=swca.rohathk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SRHC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SRHC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SRHC     
          // ---------------------------------------------------------------------------------------------------     
          void STLI::Block( AgCreate create )     
          {         
                ///@addtogroup STLI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("STLI");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dy")=svtl.nwafer*(swca.waferlen/2+swca.wafergap);              
                            shape.par("dz")=swca.waferthk/2;              
                            /// Shape Bbox dy=svtl.nwafer*(swca.waferlen/2+swca.wafergap) dz=swca.waferthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_STLI;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("STSI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create STSI              
                            Create("STSI");               
                      }           
                      END_OF_STLI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block STLI     
          // ---------------------------------------------------------------------------------------------------     
          void STSI::Block( AgCreate create )     
          {         
                ///@addtogroup STSI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=svtl.nwafer;              
                            shape.par("iaxis")=2;              
                            /// Shape Division ndiv=svtl.nwafer iaxis=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_STSI;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SVTD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SVTD              
                            Create("SVTD");               
                      }           
                      { AgPlacement place = AgPlacement("SVTD","STSI");              
                            /// Add daughter volume SVTD to mother STSI              
                            _stacker -> Position( AgBlock::Find("SVTD"), place );              
                      } // end placement of SVTD           
                      END_OF_STSI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block STSI     
          // ---------------------------------------------------------------------------------------------------     
          void SVTD::Block( AgCreate create )     
          {         
                ///@addtogroup SVTD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Silicon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Silicon");              
                            _material = mat;              
                      }           
                      /// Material Sensitive isvol=1            
                      { AgMaterial &mat = AgMaterial::Get("Sensitive");              
                            mat.par("isvol")=1;              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SVTD");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dy")=swca.waferlen/2;              
                            /// Shape Bbox dy=swca.waferlen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SVTD;              
                            _stacker -> Build(this);              
                      }           
                      /*{              
                            GSTPAR( %imed,"stra",1. );// CALL GSTPAR              
                      }*/           
                      END_OF_SVTD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SVTD     
          // ---------------------------------------------------------------------------------------------------     
          void SBER::Block( AgCreate create )     
          {         
                ///@addtogroup SBER_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBER");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=swca.wafcarwd/2;              
                            shape.par("dy")=swca.length/2;              
                            shape.par("dz")=swca.wafcarth/2;              
                            /// Shape Bbox dx=swca.wafcarwd/2 dy=swca.length/2 dz=swca.wafcarth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBER;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBER:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBER     
          // ---------------------------------------------------------------------------------------------------     
          void STAB::Block( AgCreate create )     
          {         
                ///@addtogroup STAB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("STAB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=swca.waferwid/2-swca.wafcarwd;              
                            shape.par("dy")=tablen/2;              
                            shape.par("dz")=swca.wafcarth/2;              
                            /// Shape Bbox dx=swca.waferwid/2-swca.wafcarwd dy=tablen/2 dz=swca.wafcarth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_STAB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_STAB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block STAB     
          // ---------------------------------------------------------------------------------------------------     
          void STRU::Block( AgCreate create )     
          {         
                ///@addtogroup STRU_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("STRU");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=swca.waferwid/2-swca.wafcarwd;              
                            shape.par("dy")=swca.strutlen/2;              
                            shape.par("dz")=swca.wafcarth/2;              
                            /// Shape Bbox dx=swca.waferwid/2-swca.wafcarwd dy=swca.strutlen/2 dz=swca.wafcarth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_STRU;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_STRU:           
                      mCurrent = _save;           
                ///@}        
          } // End Block STRU     
          // ---------------------------------------------------------------------------------------------------     
          void SPCB::Block( AgCreate create )     
          {         
                ///@addtogroup SPCB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SPCB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=5;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=svtl.pcbwidth/2.0;              
                            shape.par("dy")=svtl.pcblen/2.0;              
                            shape.par("dz")=svtl.pcbthk/2.0;              
                            /// Shape Bbox dx=svtl.pcbwidth/2.0 dy=svtl.pcblen/2.0 dz=svtl.pcbthk/2.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SPCB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SPCB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SPCB     
          // ---------------------------------------------------------------------------------------------------     
          void SCBM::Block( AgCreate create )     
          {         
                ///@addtogroup SCBM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCBM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=radii(1);              
                            shape.par("rmax")=swam.rmax;              
                            shape.par("dz")=scbp.len;              
                            /// Shape Tube rmin=radii(1) rmax=swam.rmax dz=scbp.len               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCBM;              
                            _stacker -> Build(this);              
                      }           
                      /// Loop on ilayer from 1 to 4 step=1           
                      for ( ilayer=1; (1>0)? (ilayer<=4):(ilayer>=4); ilayer+=1 )           
                      {              
                            /// USE scbp layer=ilayer ;              
                            scbp.Use("layer",(Int_t)ilayer );              
                            _create = AgCreate("SCBL");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SCBL                 
                                  Create("SCBL");                  
                            }              
                            { AgPlacement place = AgPlacement("SCBL","SCBM");                 
                                  /// Add daughter volume SCBL to mother SCBM                 
                                  place.TranslateX(0.0);                 
                                  /// Translate x = 0.0                 
                                  place.TranslateY(0.0);                 
                                  /// Translate y = 0.0                 
                                  place.TranslateZ(0.0);                 
                                  /// Translate z = 0.0                 
                                  _stacker -> Position( AgBlock::Find("SCBL"), place );                 
                            } // end placement of SCBL              
                      }           
                      /// Loop on ilayer from 1 to 3 step=1           
                      for ( ilayer=1; (1>0)? (ilayer<=3):(ilayer>=3); ilayer+=1 )           
                      {              
                            /// USE sfep layer=ilayer ;              
                            sfep.Use("layer",(Int_t)ilayer );              
                            _create = AgCreate("SFED");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SFED                 
                                  Create("SFED");                  
                            }              
                            { AgPlacement place = AgPlacement("SFED","SCBM");                 
                                  /// Add daughter volume SFED to mother SCBM                 
                                  place.TranslateX(0.0);                 
                                  /// Translate x = 0.0                 
                                  place.TranslateY(0.0);                 
                                  /// Translate y = 0.0                 
                                  place.TranslateZ(0.0);                 
                                  /// Translate z = 0.0                 
                                  _stacker -> Position( AgBlock::Find("SFED"), place );                 
                            } // end placement of SFED              
                            _create = AgCreate("SPLS");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SPLS                 
                                  Create("SPLS");                  
                            }              
                            { AgPlacement place = AgPlacement("SPLS","SCBM");                 
                                  /// Add daughter volume SPLS to mother SCBM                 
                                  place.TranslateX(0.0);                 
                                  /// Translate x = 0.0                 
                                  place.TranslateY(0.0);                 
                                  /// Translate y = 0.0                 
                                  place.TranslateZ(0.0);                 
                                  /// Translate z = 0.0                 
                                  _stacker -> Position( AgBlock::Find("SPLS"), place );                 
                            } // end placement of SPLS              
                      }           
                      END_OF_SCBM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCBM     
          // ---------------------------------------------------------------------------------------------------     
          void SCBL::Block( AgCreate create )     
          {         
                ///@addtogroup SCBL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Copper            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Copper");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCBL");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      sq  = (scbp.len*scbp.len);           
                      sq /= (scbp.rmin2-scbp.rmin1);           
                      sq /= (scbp.rmin2-scbp.rmin1);           
                      a   = pi;           
                      a  *= (scbp.rmin1*scbp.rmin1 + scbp.rmin2*scbp.rmin2);           
                      a  *= sqrt(1+sq);           
                      cuthk=(scbp.vol/a)*sqrt(1.0+1.0/sq);           
                      {  AgShape shape = AgShape("Cone");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=scbp.len;              
                            shape.par("rmn1")=scbp.rmin1;              
                            shape.par("rmx1")=scbp.rmin1+cuthk;              
                            shape.par("rmn2")=scbp.rmin2;              
                            shape.par("rmx2")=scbp.rmin2+cuthk;              
                            /// Shape Cone dz=scbp.len rmn1=scbp.rmin1 rmx1=scbp.rmin1+cuthk rmn2=scbp.rmin2 rmx2=scbp.rmin2+cuthk               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCBL;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SCBL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCBL     
          // ---------------------------------------------------------------------------------------------------     
          void SFED::Block( AgCreate create )     
          {         
                ///@addtogroup SFED_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Water            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Water");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFED");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      sq  = sfep.len * sfep.len;           
                      sq /= (sfep.rmin2 - sfep.rmin1);           
                      sq /= (sfep.rmin2 - sfep.rmin1);           
                      a   = pi;           
                      a  *= (sfep.rmin1*sfep.rmin1 + sfep.rmin2+sfep.rmin2);           
                      a  *= sqrt(1+sq);           
                      cuthk=(sfep.vol/a)*sqrt(1.0+1.0/sq);           
                      {  AgShape shape = AgShape("Cone");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=sfep.len;              
                            shape.par("rmn1")=sfep.rmin1;              
                            shape.par("rmx1")=sfep.rmin1+cuthk;              
                            shape.par("rmn2")=sfep.rmin2;              
                            shape.par("rmx2")=sfep.rmin2+cuthk;              
                            /// Shape Cone dz=sfep.len rmn1=sfep.rmin1 rmx1=sfep.rmin1+cuthk rmn2=sfep.rmin2 rmx2=sfep.rmin2+cuthk               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFED;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFED:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFED     
          // ---------------------------------------------------------------------------------------------------     
          void SPLS::Block( AgCreate create )     
          {         
                ///@addtogroup SPLS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component C	a=12	z=6	w=1           
                      /// Component H2	a=1	z=1	w=2           
                      /// Mixture CH2 dens=0.935           
                      {  AgMaterial &mix = AgMaterial::Get("Ch2");              
                            mix.Component("C",12,6,1);              
                            mix.Component("H2",1,1,2);              
                            mix.par("dens")=0.935;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("SPLS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      sq  = sfep.len * sfep.len;           
                      sq /= (sfep.rmin2 - sfep.rmin1);           
                      sq /= (sfep.rmin2 - sfep.rmin1);           
                      a   = pi;           
                      a  *= (sfep.rmin1*sfep.rmin1 + sfep.rmin2+sfep.rmin2);           
                      a  *= sqrt(1+sq);           
                      cuthk=(sfep.vol/a)*sqrt(1.0+1.0/sq);           
                      {  AgShape shape = AgShape("Cone");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=sfep.len;              
                            shape.par("rmn1")=sfep.rmin1+0.2;              
                            shape.par("rmx1")=sfep.rmin1+0.2+cuthk;              
                            shape.par("rmn2")=sfep.rmin2+0.2;              
                            shape.par("rmx2")=sfep.rmin2+0.2+cuthk;              
                            /// Shape Cone dz=sfep.len rmn1=sfep.rmin1+0.2 rmx1=sfep.rmin1+0.2+cuthk rmn2=sfep.rmin2+0.2 rmx2=sfep.rmin2+0.2+cuthk               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SPLS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SPLS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SPLS     
          // ---------------------------------------------------------------------------------------------------     
          void SELE::Block( AgCreate create )     
          {         
                ///@addtogroup SELE_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SELE");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.par("serial")=ilayer;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=selc.elcawid/2;              
                            shape.par("dy")=swca.length/2;              
                            shape.par("dz")=elethk/2;              
                            /// Shape Bbox dx=selc.elcawid/2 dy=swca.length/2 dz=elethk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SELE;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SWCH");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWCH              
                            Create("SWCH");               
                      }           
                      { AgPlacement place = AgPlacement("SWCH","SELE");              
                            /// Add daughter volume SWCH to mother SELE              
                            place.TranslateZ(-elethk/2+selc.bethk/2);              
                            /// Translate z = -elethk/2+selc.bethk/2              
                            _stacker -> Position( AgBlock::Find("SWCH"), place );              
                      } // end placement of SWCH           
                      { AgPlacement place = AgPlacement("SWCH","SELE");              
                            /// Add daughter volume SWCH to mother SELE              
                            place.TranslateZ(-elethk/2+selc.bethk+selc.watthk+selc.bethk/2);              
                            /// Translate z = -elethk/2+selc.bethk+selc.watthk+selc.bethk/2              
                            _stacker -> Position( AgBlock::Find("SWCH"), place );              
                      } // end placement of SWCH           
                      _create = AgCreate("SWCS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWCS              
                            Create("SWCS");               
                      }           
                      { AgPlacement place = AgPlacement("SWCS","SELE");              
                            /// Add daughter volume SWCS to mother SELE              
                            place.TranslateX(-selc.elcawid/2+selc.bethk/2);              
                            /// Translate x = -selc.elcawid/2+selc.bethk/2              
                            place.TranslateZ(-elethk/2+selc.bethk+selc.watthk/2);              
                            /// Translate z = -elethk/2+selc.bethk+selc.watthk/2              
                            _stacker -> Position( AgBlock::Find("SWCS"), place );              
                      } // end placement of SWCS           
                      { AgPlacement place = AgPlacement("SWCS","SELE");              
                            /// Add daughter volume SWCS to mother SELE              
                            place.TranslateX(+selc.elcawid/2-selc.bethk/2);              
                            /// Translate x = +selc.elcawid/2-selc.bethk/2              
                            place.TranslateZ(-elethk/2+selc.bethk+selc.watthk/2);              
                            /// Translate z = -elethk/2+selc.bethk+selc.watthk/2              
                            _stacker -> Position( AgBlock::Find("SWCS"), place );              
                      } // end placement of SWCS           
                      _create = AgCreate("SWCW");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWCW              
                            Create("SWCW");               
                      }           
                      { AgPlacement place = AgPlacement("SWCW","SELE");              
                            /// Add daughter volume SWCW to mother SELE              
                            place.TranslateZ(-elethk/2+selc.bethk+selc.watthk/2);              
                            /// Translate z = -elethk/2+selc.bethk+selc.watthk/2              
                            _stacker -> Position( AgBlock::Find("SWCW"), place );              
                      } // end placement of SWCW           
                      _create = AgCreate("SBOI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBOI              
                            Create("SBOI");               
                      }           
                      { AgPlacement place = AgPlacement("SBOI","SELE");              
                            /// Add daughter volume SBOI to mother SELE              
                            place.TranslateZ((elethk/2-selc.dyethk-selc.agpdthk-selc.glassthk-selc.beothk/2));              
                            /// Translate z = (elethk/2-selc.dyethk-selc.agpdthk-selc.glassthk-selc.beothk/2)              
                            _stacker -> Position( AgBlock::Find("SBOI"), place );              
                      } // end placement of SBOI           
                      _create = AgCreate("SGLA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SGLA              
                            Create("SGLA");               
                      }           
                      { AgPlacement place = AgPlacement("SGLA","SELE");              
                            /// Add daughter volume SGLA to mother SELE              
                            place.TranslateZ(elethk/2-selc.dyethk-selc.agpdthk-selc.glassthk/2);              
                            /// Translate z = elethk/2-selc.dyethk-selc.agpdthk-selc.glassthk/2              
                            _stacker -> Position( AgBlock::Find("SGLA"), place );              
                      } // end placement of SGLA           
                      _create = AgCreate("SAGP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SAGP              
                            Create("SAGP");               
                      }           
                      { AgPlacement place = AgPlacement("SAGP","SELE");              
                            /// Add daughter volume SAGP to mother SELE              
                            place.TranslateZ(elethk/2-selc.dyethk-selc.agpdthk/2);              
                            /// Translate z = elethk/2-selc.dyethk-selc.agpdthk/2              
                            _stacker -> Position( AgBlock::Find("SAGP"), place );              
                      } // end placement of SAGP           
                      _create = AgCreate("SDYE");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SDYE              
                            Create("SDYE");               
                      }           
                      { AgPlacement place = AgPlacement("SDYE","SELE");              
                            /// Add daughter volume SDYE to mother SELE              
                            place.TranslateX(selc.elcawid/2-selc.dyespc-selc.dyewid/2);              
                            /// Translate x = selc.elcawid/2-selc.dyespc-selc.dyewid/2              
                            place.TranslateZ(elethk/2-selc.dyethk/2);              
                            /// Translate z = elethk/2-selc.dyethk/2              
                            _stacker -> Position( AgBlock::Find("SDYE"), place );              
                      } // end placement of SDYE           
                      { AgPlacement place = AgPlacement("SDYE","SELE");              
                            /// Add daughter volume SDYE to mother SELE              
                            place.TranslateX(selc.elcawid/2-2.0*selc.dyespc-3.0*selc.dyewid/2);              
                            /// Translate x = selc.elcawid/2-2.0*selc.dyespc-3.0*selc.dyewid/2              
                            place.TranslateZ(elethk/2-selc.dyethk/2);              
                            /// Translate z = elethk/2-selc.dyethk/2              
                            _stacker -> Position( AgBlock::Find("SDYE"), place );              
                      } // end placement of SDYE           
                      _create = AgCreate("SECA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SECA              
                            Create("SECA");               
                      }           
                      { AgPlacement place = AgPlacement("SECA","SELE");              
                            /// Add daughter volume SECA to mother SELE              
                            place.TranslateX(-selc.elcawid/2+selc.cabwid/2);              
                            /// Translate x = -selc.elcawid/2+selc.cabwid/2              
                            place.TranslateZ(elethk/2-selc.dyethk+selc.cabthk/2);              
                            /// Translate z = elethk/2-selc.dyethk+selc.cabthk/2              
                            _stacker -> Position( AgBlock::Find("SECA"), place );              
                      } // end placement of SECA           
                      END_OF_SELE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SELE     
          // ---------------------------------------------------------------------------------------------------     
          void SDYE::Block( AgCreate create )     
          {         
                ///@addtogroup SDYE_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Silicon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Silicon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SDYE");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=selc.dyewid/2;              
                            shape.par("dy")=svtl.nwafer*(swca.waferlen/2+swca.wafergap);              
                            shape.par("dz")=selc.dyethk/2;              
                            /// Shape Bbox dx=selc.dyewid/2 dy=svtl.nwafer*(swca.waferlen/2+swca.wafergap) dz=selc.dyethk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SDYE;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SDYE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SDYE     
          // ---------------------------------------------------------------------------------------------------     
          void SECA::Block( AgCreate create )     
          {         
                ///@addtogroup SECA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Copper            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Copper");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SECA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=selc.cabwid/2;              
                            shape.par("dy")=swca.length/2;              
                            shape.par("dz")=selc.cabthk/2;              
                            /// Shape Bbox dx=selc.cabwid/2 dy=swca.length/2 dz=selc.cabthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SECA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SECA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SECA     
          // ---------------------------------------------------------------------------------------------------     
          void SBOI::Block( AgCreate create )     
          {         
                ///@addtogroup SBOI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component Be	a=9	z=4	w=1           
                      /// Component O	a=16	z=8	w=1           
                      /// Mixture BeO dens=2.85           
                      {  AgMaterial &mix = AgMaterial::Get("Beo");              
                            mix.Component("Be",9,4,1);              
                            mix.Component("O",16,8,1);              
                            mix.par("dens")=2.85;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("SBOI");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=selc.elcawid/2;              
                            shape.par("dy")=svtl.nwafer*(swca.waferlen/2+swca.wafergap);              
                            shape.par("dz")=selc.beothk/2;              
                            /// Shape Bbox dx=selc.elcawid/2 dy=svtl.nwafer*(swca.waferlen/2+swca.wafergap) dz=selc.beothk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBOI;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBOI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBOI     
          // ---------------------------------------------------------------------------------------------------     
          void SAGP::Block( AgCreate create )     
          {         
                ///@addtogroup SAGP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component Ag	a=108	z=47	w=1           
                      /// Component Pd	a=106	z=46	w=1           
                      /// Mixture AgPd dens=11.25           
                      {  AgMaterial &mix = AgMaterial::Get("Agpd");              
                            mix.Component("Ag",108,47,1);              
                            mix.Component("Pd",106,46,1);              
                            mix.par("dens")=11.25;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("SAGP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=selc.elcawid/2;              
                            shape.par("dy")=svtl.nwafer*(swca.waferlen/2+swca.wafergap);              
                            shape.par("dz")=selc.agpdthk/2;              
                            /// Shape Bbox dx=selc.elcawid/2 dy=svtl.nwafer*(swca.waferlen/2+swca.wafergap) dz=selc.agpdthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SAGP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SAGP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SAGP     
          // ---------------------------------------------------------------------------------------------------     
          void SGLA::Block( AgCreate create )     
          {         
                ///@addtogroup SGLA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component Si	a=28	z=14	w=1           
                      /// Component O	a=16	z=8	w=2           
                      /// Mixture glass dens=2.2           
                      {  AgMaterial &mix = AgMaterial::Get("Glass");              
                            mix.Component("Si",28,14,1);              
                            mix.Component("O",16,8,2);              
                            mix.par("dens")=2.2;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("SGLA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=selc.elcawid/2;              
                            shape.par("dy")=svtl.nwafer*(swca.waferlen/2+swca.wafergap);              
                            shape.par("dz")=selc.glassthk/2;              
                            /// Shape Bbox dx=selc.elcawid/2 dy=svtl.nwafer*(swca.waferlen/2+swca.wafergap) dz=selc.glassthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SGLA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SGLA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SGLA     
          // ---------------------------------------------------------------------------------------------------     
          void SWCH::Block( AgCreate create )     
          {         
                ///@addtogroup SWCH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SWCH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=selc.elcawid/2;              
                            shape.par("dy")=swca.length/2;              
                            shape.par("dz")=selc.bethk/2;              
                            /// Shape Bbox dx=selc.elcawid/2 dy=swca.length/2 dz=selc.bethk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWCH;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SWCH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWCH     
          // ---------------------------------------------------------------------------------------------------     
          void SWCS::Block( AgCreate create )     
          {         
                ///@addtogroup SWCS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SWCS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=selc.bethk/2;              
                            shape.par("dy")=swca.length/2;              
                            shape.par("dz")=selc.watthk/2;              
                            /// Shape Bbox dx=selc.bethk/2 dy=swca.length/2 dz=selc.watthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWCS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SWCS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWCS     
          // ---------------------------------------------------------------------------------------------------     
          void SWCW::Block( AgCreate create )     
          {         
                ///@addtogroup SWCW_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Water            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Water");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SWCW");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=(selc.elcawid-2.0*selc.bethk)/2;              
                            shape.par("dy")=swca.length/2;              
                            shape.par("dz")=(selc.watthk/2);              
                            /// Shape Bbox dx=(selc.elcawid-2.0*selc.bethk)/2 dy=swca.length/2 dz=(selc.watthk/2)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWCW;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SWCW:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWCW     
          // ---------------------------------------------------------------------------------------------------     
          void SIRT::Block( AgCreate create )     
          {         
                ///@addtogroup SIRT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SIRT");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      ir_rmin  = cos(pi/8.0);           
                      ir_rmin += sqrt( tan(pi/8.0)*tan(pi/8.0) - sin(pi/8.0)*sin(pi/8.0) );           
                      ir_rmin *= serg.irngprmn;           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ir_rmin;              
                            shape.par("rmax")=serg.irngtrmx;              
                            shape.par("dz")=serg.endrngth/2;              
                            /// Shape Tube rmin=ir_rmin rmax=serg.irngtrmx dz=serg.endrngth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SIRT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SIRT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SIRT     
          // ---------------------------------------------------------------------------------------------------     
          void SIRP::Block( AgCreate create )     
          {         
                ///@addtogroup SIRP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SIRP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      rou  = cos(pi/8.0);           
                      rou += sqrt( tan(pi/8.0)*tan(pi/8.0) - sin(pi/8.0)*sin(pi/8.0) );           
                      rou  = serg.irngtrmx / rou;           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("npdiv")=8;              
                            shape.par("nz")=2;              
                            shape.Z(0)=-serg.endrngth/2;              
                            shape.Z(1)=+serg.endrngth/2;              
                            shape.Rmin(0)=serg.irngprmn;              
                            shape.Rmin(1)=serg.irngprmn;              
                            shape.Rmax(0)=rou;              
                            shape.Rmax(1)=rou;              
                            /// Shape Pgon phi1=0 dphi=360 npdiv=8 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SIRP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SIRP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SIRP     
          // ---------------------------------------------------------------------------------------------------     
          void SOER::Block( AgCreate create )     
          {         
                ///@addtogroup SOER_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SOER");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=serg.orngrmin;              
                            shape.par("rmax")=serg.orngrmax;              
                            shape.par("dz")=serg.endrngth/2;              
                            /// Shape Tube rmin=serg.orngrmin rmax=serg.orngrmax dz=serg.endrngth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SOER;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SOER:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SOER     
          // ---------------------------------------------------------------------------------------------------     
          void SIES::Block( AgCreate create )     
          {         
                ///@addtogroup SIES_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SIES");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ir_rmin;              
                            shape.par("rmax")=serg.irngtrmx;              
                            shape.par("dz")=0.5*(brack_z-endrng_z);              
                            /// Shape Tube rmin=ir_rmin rmax=serg.irngtrmx dz=0.5*(brack_z-endrng_z)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SIES;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SISM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SISM              
                            Create("SISM");               
                      }           
                      END_OF_SIES:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SIES     
          // ---------------------------------------------------------------------------------------------------     
          void SISM::Block( AgCreate create )     
          {         
                ///@addtogroup SISM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SISM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=4;              
                            shape.par("iaxis")=2;              
                            shape.par("c0")=45;              
                            /// Shape Division ndiv=4 iaxis=2 c0=45               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SISM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SCRW");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCRW              
                            Create("SCRW");               
                      }           
                      { AgPlacement place = AgPlacement("SCRW","SISM");              
                            /// Add daughter volume SCRW to mother SISM              
                            place.TranslateX(ssup.erjrad-ssup.erjlen/2+ssup.erj1x);              
                            /// Translate x = ssup.erjrad-ssup.erjlen/2+ssup.erj1x              
                            _stacker -> Position( AgBlock::Find("SCRW"), place );              
                      } // end placement of SCRW           
                      END_OF_SISM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SISM     
          // ---------------------------------------------------------------------------------------------------     
          void SOES::Block( AgCreate create )     
          {         
                ///@addtogroup SOES_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SOES");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=serg.orngrmin;              
                            shape.par("rmax")=serg.orngrmax;              
                            shape.par("dz")=0.5*(brack_z-endrng_z);              
                            /// Shape Tube rmin=serg.orngrmin rmax=serg.orngrmax dz=0.5*(brack_z-endrng_z)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SOES;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SOSM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SOSM              
                            Create("SOSM");               
                      }           
                      END_OF_SOES:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SOES     
          // ---------------------------------------------------------------------------------------------------     
          void SOSM::Block( AgCreate create )     
          {         
                ///@addtogroup SOSM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SOSM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=4;              
                            shape.par("iaxis")=2;              
                            shape.par("c0")=45;              
                            /// Shape Division ndiv=4 iaxis=2 c0=45               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SOSM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SCRW");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCRW              
                            Create("SCRW");               
                      }           
                      { AgPlacement place = AgPlacement("SCRW","SOSM");              
                            /// Add daughter volume SCRW to mother SOSM              
                            place.TranslateX(ssup.erjrad+ssup.erjlen/2-ssup.erj1x);              
                            /// Translate x = ssup.erjrad+ssup.erjlen/2-ssup.erj1x              
                            _stacker -> Position( AgBlock::Find("SCRW"), place );              
                      } // end placement of SCRW           
                      { AgPlacement place = AgPlacement("SCRW","SOSM");              
                            /// Add daughter volume SCRW to mother SOSM              
                            place.TranslateX(ssup.erjrad+ssup.erjlen/2-ssup.erj2x);              
                            /// Translate x = ssup.erjrad+ssup.erjlen/2-ssup.erj2x              
                            _stacker -> Position( AgBlock::Find("SCRW"), place );              
                      } // end placement of SCRW           
                      { AgPlacement place = AgPlacement("SCRW","SOSM");              
                            /// Add daughter volume SCRW to mother SOSM              
                            place.TranslateX(ssup.erjrad+ssup.erjlen/2-ssup.erj2x);              
                            /// Translate x = ssup.erjrad+ssup.erjlen/2-ssup.erj2x              
                            place.TranslateY(ssup.erj2y);              
                            /// Translate y = ssup.erj2y              
                            _stacker -> Position( AgBlock::Find("SCRW"), place );              
                      } // end placement of SCRW           
                      { AgPlacement place = AgPlacement("SCRW","SOSM");              
                            /// Add daughter volume SCRW to mother SOSM              
                            place.TranslateX(ssup.erjrad+ssup.erjlen/2-ssup.erj2x);              
                            /// Translate x = ssup.erjrad+ssup.erjlen/2-ssup.erj2x              
                            place.TranslateY(-ssup.erj2y);              
                            /// Translate y = -ssup.erj2y              
                            _stacker -> Position( AgBlock::Find("SCRW"), place );              
                      } // end placement of SCRW           
                      END_OF_SOSM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SOSM     
          // ---------------------------------------------------------------------------------------------------     
          void SBRG::Block( AgCreate create )     
          {         
                ///@addtogroup SBRG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      rin=serg.irngprmn;           
                      rou=serg.orngrmax;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBRG");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=rin;              
                            shape.par("rmax")=rou;              
                            shape.par("dz")=ssup.erjthk/2;              
                            /// Shape Tube rmin=rin rmax=rou dz=ssup.erjthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBRG;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SBRM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBRM              
                            Create("SBRM");               
                      }           
                      END_OF_SBRG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBRG     
          // ---------------------------------------------------------------------------------------------------     
          void SBRM::Block( AgCreate create )     
          {         
                ///@addtogroup SBRM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SBRM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=4;              
                            shape.par("iaxis")=2;              
                            shape.par("c0")=45;              
                            /// Shape Division ndiv=4 iaxis=2 c0=45               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBRM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SBRI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBRI              
                            Create("SBRI");               
                      }           
                      { AgPlacement place = AgPlacement("SBRI","SBRM");              
                            /// Add daughter volume SBRI to mother SBRM              
                            place.TranslateX(ssup.erjrad);              
                            /// Translate x = ssup.erjrad              
                            _stacker -> Position( AgBlock::Find("SBRI"), place );              
                      } // end placement of SBRI           
                      END_OF_SBRM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBRM     
          // ---------------------------------------------------------------------------------------------------     
          void SBRI::Block( AgCreate create )     
          {         
                ///@addtogroup SBRI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SBRI");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=ssup.erjlen/2;              
                            shape.par("dy")=ssup.erjwid/2;              
                            shape.par("dz")=ssup.erjthk/2;              
                            /// Shape Bbox dx=ssup.erjlen/2 dy=ssup.erjwid/2 dz=ssup.erjthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBRI;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBRI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBRI     
          // ---------------------------------------------------------------------------------------------------     
          void SROD::Block( AgCreate create )     
          {         
                ///@addtogroup SROD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SROD");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssup.rodid/2;              
                            shape.par("rmax")=ssup.rodod/2;              
                            shape.par("dz")=ssup.rodlen/2;              
                            /// Shape Tube rmin=ssup.rodid/2 rmax=ssup.rodod/2 dz=ssup.rodlen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SROD;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SROD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SROD     
          // ---------------------------------------------------------------------------------------------------     
          void SCON::Block( AgCreate create )     
          {         
                ///@addtogroup SCON_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      cone_thk1=ssup.grphthk;           
                      cone_thk2=cone_thk1+ssup.cabthk+2*ssup.hosrmx;           
                      cone_thk2=cone_thk2+ssup.wrpmythk+ssup.wrpalthk;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCON");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("nz")=7;              
                            shape.Z(0)=ssup.cone1zmn;              
                            shape.Z(1)=ssup.rodlen/2;              
                            shape.Z(2)=ssup.rodlen/2;              
                            shape.Z(3)=ssup.rodlen/2+ssup.grphthk;              
                            shape.Z(4)=ssup.rodlen/2+ssup.grphthk;              
                            shape.Z(5)=ssup.cone3zmx;              
                            shape.Z(6)=ssup.cone4zmx;              
                            shape.Rmin(0)=ssup.con1idmn;              
                            shape.Rmin(1)=ssup.con1idmn;              
                            shape.Rmin(2)=ssup.con1idmn;              
                            shape.Rmin(3)=ssup.con1idmn;              
                            shape.Rmin(4)=ssup.con3idmn;              
                            shape.Rmin(5)=ssup.con4idmn;              
                            shape.Rmin(6)=ssup.con4idmx;              
                            shape.Rmax(0)=ssup.con1idmn+cone_thk1;              
                            shape.Rmax(1)=ssup.con1idmn+cone_thk1;              
                            shape.Rmax(2)=ssup.con3idmn+cone_thk1;              
                            shape.Rmax(3)=ssup.con3idmn+cone_thk1;              
                            shape.Rmax(4)=ssup.con3idmn+cone_thk2;              
                            shape.Rmax(5)=ssup.con4idmn+cone_thk2;              
                            shape.Rmax(6)=ssup.con4idmx+cone_thk2;              
                            /// Shape Pcon phi1=0 dphi=360 nz=7               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCON;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SGRA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SGRA              
                            Create("SGRA");               
                      }           
                      { AgPlacement place = AgPlacement("SGRA","SCON");              
                            /// Add daughter volume SGRA to mother SCON              
                            _stacker -> Position( AgBlock::Find("SGRA"), place );              
                      } // end placement of SGRA           
                      _create = AgCreate("STAP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create STAP              
                            Create("STAP");               
                      }           
                      { AgPlacement place = AgPlacement("STAP","SCON");              
                            /// Add daughter volume STAP to mother SCON              
                            _stacker -> Position( AgBlock::Find("STAP"), place );              
                      } // end placement of STAP           
                      _create = AgCreate("STAC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create STAC              
                            Create("STAC");               
                      }           
                      { AgPlacement place = AgPlacement("STAC","SCON");              
                            /// Add daughter volume STAC to mother SCON              
                            _stacker -> Position( AgBlock::Find("STAC"), place );              
                      } // end placement of STAC           
                      _create = AgCreate("SHLA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SHLA              
                            Create("SHLA");               
                      }           
                      { AgPlacement place = AgPlacement("SHLA","SCON");              
                            /// Add daughter volume SHLA to mother SCON              
                            place.TranslateZ(ssup.rodlen/2+ssup.grphthk+0.5*(ssup.cone3zmx-ssup.rodlen/2-ssup.grphthk));              
                            /// Translate z = ssup.rodlen/2+ssup.grphthk+0.5*(ssup.cone3zmx-ssup.rodlen/2-ssup.grphthk)              
                            _stacker -> Position( AgBlock::Find("SHLA"), place );              
                      } // end placement of SHLA           
                      _create = AgCreate("SHLB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SHLB              
                            Create("SHLB");               
                      }           
                      { AgPlacement place = AgPlacement("SHLB","SCON");              
                            /// Add daughter volume SHLB to mother SCON              
                            place.TranslateZ(ssup.cone3zmx+0.5*(ssup.cone4zmx-ssup.cone3zmx));              
                            /// Translate z = ssup.cone3zmx+0.5*(ssup.cone4zmx-ssup.cone3zmx)              
                            _stacker -> Position( AgBlock::Find("SHLB"), place );              
                      } // end placement of SHLB           
                      _create = AgCreate("SCMY");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCMY              
                            Create("SCMY");               
                      }           
                      { AgPlacement place = AgPlacement("SCMY","SCON");              
                            /// Add daughter volume SCMY to mother SCON              
                            _stacker -> Position( AgBlock::Find("SCMY"), place );              
                      } // end placement of SCMY           
                      _create = AgCreate("SCAL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCAL              
                            Create("SCAL");               
                      }           
                      { AgPlacement place = AgPlacement("SCAL","SCON");              
                            /// Add daughter volume SCAL to mother SCON              
                            _stacker -> Position( AgBlock::Find("SCAL"), place );              
                      } // end placement of SCAL           
                      END_OF_SCON:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCON     
          // ---------------------------------------------------------------------------------------------------     
          void SGRA::Block( AgCreate create )     
          {         
                ///@addtogroup SGRA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SGRA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("nz")=5;              
                            shape.Z(0)=ssup.rodlen/2;              
                            shape.Z(1)=ssup.rodlen/2+ssup.grphthk;              
                            shape.Z(2)=ssup.rodlen/2+ssup.grphthk;              
                            shape.Z(3)=ssup.cone3zmx;              
                            shape.Z(4)=ssup.cone4zmx;              
                            shape.Rmin(0)=ssup.con1idmn;              
                            shape.Rmin(1)=ssup.con1idmn;              
                            shape.Rmin(2)=ssup.con3idmn;              
                            shape.Rmin(3)=ssup.con4idmn;              
                            shape.Rmin(4)=ssup.con4idmx;              
                            shape.Rmax(0)=ssup.con3idmn+ssup.grphthk;              
                            shape.Rmax(1)=ssup.con3idmn+ssup.grphthk;              
                            shape.Rmax(2)=ssup.con3idmn+ssup.grphthk;              
                            shape.Rmax(3)=ssup.con4idmn+ssup.grphthk;              
                            shape.Rmax(4)=ssup.con4idmx+ssup.grphthk;              
                            /// Shape Pcon phi1=0 dphi=360 nz=5               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SGRA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SGRA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SGRA     
          // ---------------------------------------------------------------------------------------------------     
          void STAP::Block( AgCreate create )     
          {         
                ///@addtogroup STAP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      roffset=ssup.grphthk;           
                      /// Component C	a=12	z=6	w=1           
                      /// Component H2	a=1	z=1	w=2           
                      /// Mixture CH2 dens=0.935           
                      {  AgMaterial &mix = AgMaterial::Get("Ch2");              
                            mix.Component("C",12,6,1);              
                            mix.Component("H2",1,1,2);              
                            mix.par("dens")=0.935;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("STAP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("nz")=3;              
                            shape.Z(0)=ssup.rodlen/2+ssup.grphthk;              
                            shape.Z(1)=ssup.cone3zmx;              
                            shape.Z(2)=ssup.cone4zmx;              
                            shape.Rmin(0)=ssup.con3idmn+roffset;              
                            shape.Rmin(1)=ssup.con4idmn+roffset;              
                            shape.Rmin(2)=ssup.con4idmx+roffset;              
                            shape.Rmax(0)=ssup.con3idmn+roffset+ssup.cabthk/2;              
                            shape.Rmax(1)=ssup.con4idmn+roffset+ssup.cabthk/2;              
                            shape.Rmax(2)=ssup.con4idmx+roffset+ssup.cabthk/2;              
                            /// Shape Pcon phi1=0 dphi=360 nz=3               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_STAP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_STAP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block STAP     
          // ---------------------------------------------------------------------------------------------------     
          void STAC::Block( AgCreate create )     
          {         
                ///@addtogroup STAC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      roffset=ssup.grphthk+ssup.cabthk/2;           
                      /// Material Copper            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Copper");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("STAC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("nz")=3;              
                            shape.Z(0)=ssup.rodlen/2+ssup.grphthk;              
                            shape.Z(1)=ssup.cone3zmx;              
                            shape.Z(2)=ssup.cone4zmx;              
                            shape.Rmin(0)=ssup.con3idmn+roffset;              
                            shape.Rmin(1)=ssup.con4idmn+roffset;              
                            shape.Rmin(2)=ssup.con4idmx+roffset;              
                            shape.Rmax(0)=ssup.con3idmn+roffset+ssup.cabthk/2;              
                            shape.Rmax(1)=ssup.con4idmn+roffset+ssup.cabthk/2;              
                            shape.Rmax(2)=ssup.con4idmx+roffset+ssup.cabthk/2;              
                            /// Shape Pcon phi1=0 dphi=360 nz=3               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_STAC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_STAC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block STAC     
          // ---------------------------------------------------------------------------------------------------     
          void SHLA::Block( AgCreate create )     
          {         
                ///@addtogroup SHLA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      roffset=ssup.grphthk+ssup.cabthk;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SHLA");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Cone");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=.5*(ssup.cone3zmx-ssup.rodlen/2-ssup.grphthk);              
                            shape.par("rmn1")=ssup.con3idmn+roffset;              
                            shape.par("rmx1")=ssup.con3idmn+roffset+2.0*ssup.hosrmx;              
                            shape.par("rmn2")=ssup.con4idmn+roffset;              
                            shape.par("rmx2")=ssup.con4idmn+roffset+2.0*ssup.hosrmx;              
                            /// Shape Cone dz=.5*(ssup.cone3zmx-ssup.rodlen/2-ssup.grphthk) rmn1=ssup.con3idmn+roffset rmx1=ssup.con3idmn+roffset+2.0*ssup.hosrmx rmn2=ssup.con4idmn+roffset rmx2=ssup.con4idmn+roffset+2.0*ssup.hosrmx               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SHLA;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SHMA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SHMA              
                            Create("SHMA");               
                      }           
                      END_OF_SHLA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SHLA     
          // ---------------------------------------------------------------------------------------------------     
          void SHMA::Block( AgCreate create )     
          {         
                ///@addtogroup SHMA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      roffset=ssup.grphthk+ssup.cabthk;           
                      rmin=ssup.con3idmn+roffset;           
                      rmax=ssup.con4idmn+roffset;           
                      zmin=ssup.rodlen/2+ssup.grphthk;           
                      zmax=ssup.cone3zmx;           
                      cone_len  = (zmax-zmin)*(zmax-zmin);           
                      cone_len += (rmax-rmin)*(rmax-rmin);           
                      cone_len  = sqrt(cone_len);           
                      cone_sin=(rmax-rmin)/cone_len;           
                      cone_cos=(zmax-zmin)/cone_len;           
                      angle=asin(cone_sin)*180/pi;           
                      xpos=rmin+0.5*(rmax-rmin)+ssup.hosrmx*cone_cos;           
                      zpos=-ssup.hosrmx*cone_sin;           
                      { AgAttribute attr = AgAttribute("SHMA");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=ssup.nhoses;              
                            shape.par("iaxis")=2;              
                            shape.par("c0")=0.0;              
                            /// Shape Division ndiv=ssup.nhoses iaxis=2 c0=0.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SHMA;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SWHO");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWHO              
                            Create("SWHO");               
                      }           
                      { AgPlacement place = AgPlacement("SWHO","SHMA");              
                            /// Add daughter volume SWHO to mother SHMA              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            place.AlphaY(angle);              
                            /// Rotate: AlphaY = angle              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SWHO"), place );              
                      } // end placement of SWHO           
                      END_OF_SHMA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SHMA     
          // ---------------------------------------------------------------------------------------------------     
          void SHLB::Block( AgCreate create )     
          {         
                ///@addtogroup SHLB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      roffset=ssup.grphthk+ssup.cabthk;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SHLB");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Cone");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=.5*(ssup.cone4zmx-ssup.cone3zmx);              
                            shape.par("rmn1")=ssup.con4idmn+roffset;              
                            shape.par("rmx1")=ssup.con4idmn+roffset+2.0*ssup.hosrmx;              
                            shape.par("rmn2")=ssup.con4idmx+roffset;              
                            shape.par("rmx2")=ssup.con4idmx+roffset+2.0*ssup.hosrmx;              
                            /// Shape Cone dz=.5*(ssup.cone4zmx-ssup.cone3zmx) rmn1=ssup.con4idmn+roffset rmx1=ssup.con4idmn+roffset+2.0*ssup.hosrmx rmn2=ssup.con4idmx+roffset rmx2=ssup.con4idmx+roffset+2.0*ssup.hosrmx               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SHLB;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SHMB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SHMB              
                            Create("SHMB");               
                      }           
                      END_OF_SHLB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SHLB     
          // ---------------------------------------------------------------------------------------------------     
          void SHMB::Block( AgCreate create )     
          {         
                ///@addtogroup SHMB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      roffset=ssup.grphthk+ssup.cabthk;           
                      rmin=ssup.con4idmn+roffset;           
                      rmax=ssup.con4idmx+roffset;           
                      zmin=ssup.cone3zmx;           
                      zmax=ssup.cone4zmx;           
                      cone_len  = (zmax-zmin)*(zmax-zmin);           
                      cone_len += (rmax-rmin)*(rmax-rmin);           
                      cone_len  = sqrt(cone_len);           
                      cone_sin=(rmax-rmin)/cone_len;           
                      cone_cos=(zmax-zmin)/cone_len;           
                      angle=asin(cone_sin)*180/pi;           
                      xpos=rmin+0.5*(rmax-rmin)+ssup.hosrmx*cone_cos;           
                      zpos=-ssup.hosrmx*cone_sin;           
                      { AgAttribute attr = AgAttribute("SHMB");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=ssup.nhoses;              
                            shape.par("iaxis")=2;              
                            shape.par("c0")=0.0;              
                            /// Shape Division ndiv=ssup.nhoses iaxis=2 c0=0.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SHMB;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SWHO");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWHO              
                            Create("SWHO");               
                      }           
                      { AgPlacement place = AgPlacement("SWHO","SHMB");              
                            /// Add daughter volume SWHO to mother SHMB              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            place.AlphaY(angle);              
                            /// Rotate: AlphaY = angle              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SWHO"), place );              
                      } // end placement of SWHO           
                      END_OF_SHMB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SHMB     
          // ---------------------------------------------------------------------------------------------------     
          void SWHO::Block( AgCreate create )     
          {         
                ///@addtogroup SWHO_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SWHO");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Component C	a=12	z=6	w=1           
                      /// Component H2	a=1	z=1	w=2           
                      /// Mixture CH2 dens=0.935           
                      {  AgMaterial &mix = AgMaterial::Get("Ch2");              
                            mix.Component("C",12,6,1);              
                            mix.Component("H2",1,1,2);              
                            mix.par("dens")=0.935;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("SWHO");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=ssup.hosrmx;              
                            shape.par("dz")=0.5*cone_len;              
                            /// Shape Tube rmin=0 rmax=ssup.hosrmx dz=0.5*cone_len               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWHO;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SHWA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SHWA              
                            Create("SHWA");               
                      }           
                      { AgPlacement place = AgPlacement("SHWA","SWHO");              
                            /// Add daughter volume SHWA to mother SWHO              
                            _stacker -> Position( AgBlock::Find("SHWA"), place );              
                      } // end placement of SHWA           
                      END_OF_SWHO:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWHO     
          // ---------------------------------------------------------------------------------------------------     
          void SHWA::Block( AgCreate create )     
          {         
                ///@addtogroup SHWA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SHWA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Water            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Water");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmax")=ssup.hosrmn;              
                            /// Shape Tube rmax=ssup.hosrmn               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SHWA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SHWA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SHWA     
          // ---------------------------------------------------------------------------------------------------     
          void SCMY::Block( AgCreate create )     
          {         
                ///@addtogroup SCMY_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      roffset=ssup.grphthk+ssup.cabthk+2.0*ssup.hosrmx;           
                      /// Component C5	a=12	z=6	w=5           
                      /// Component H4	a=1	z=1	w=4           
                      /// Component O2	a=16	z=8	w=2           
                      /// Mixture Mylar dens=1.39           
                      {  AgMaterial &mix = AgMaterial::Get("Mylar");              
                            mix.Component("C5",12,6,5);              
                            mix.Component("H4",1,1,4);              
                            mix.Component("O2",16,8,2);              
                            mix.par("dens")=1.39;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("SCMY");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("nz")=3;              
                            shape.Z(0)=ssup.rodlen/2+ssup.grphthk;              
                            shape.Z(1)=ssup.cone3zmx;              
                            shape.Z(2)=ssup.cone4zmx;              
                            shape.Rmin(0)=ssup.con3idmn+roffset;              
                            shape.Rmin(1)=ssup.con4idmn+roffset;              
                            shape.Rmin(2)=ssup.con4idmx+roffset;              
                            shape.Rmax(0)=ssup.con3idmn+roffset+ssup.wrpmythk;              
                            shape.Rmax(1)=ssup.con4idmn+roffset+ssup.wrpmythk;              
                            shape.Rmax(2)=ssup.con4idmx+roffset+ssup.wrpmythk;              
                            /// Shape Pcon phi1=0 dphi=360 nz=3               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCMY;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SCMY:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCMY     
          // ---------------------------------------------------------------------------------------------------     
          void SCAL::Block( AgCreate create )     
          {         
                ///@addtogroup SCAL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      roffset=ssup.grphthk+ssup.cabthk+2.0*ssup.hosrmx+ssup.wrpmythk;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCAL");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("nz")=3;              
                            shape.Z(0)=ssup.rodlen/2+ssup.grphthk;              
                            shape.Z(1)=ssup.cone3zmx;              
                            shape.Z(2)=ssup.cone4zmx;              
                            shape.Rmin(0)=ssup.con3idmn+roffset;              
                            shape.Rmin(1)=ssup.con4idmn+roffset;              
                            shape.Rmin(2)=ssup.con4idmx+roffset;              
                            shape.Rmax(0)=ssup.con3idmn+roffset+ssup.wrpalthk;              
                            shape.Rmax(1)=ssup.con4idmn+roffset+ssup.wrpalthk;              
                            shape.Rmax(2)=ssup.con4idmx+roffset+ssup.wrpalthk;              
                            /// Shape Pcon phi1=0 dphi=360 nz=3               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCAL;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SCAL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCAL     
          // ---------------------------------------------------------------------------------------------------     
          void SWMM::Block( AgCreate create )     
          {         
                ///@addtogroup SWMM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      rin=swam.rmin-swam.tbrdthk;           
                      rou=swam.rmax+swam.tbrdthk;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SWMM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("npdiv")=18;              
                            shape.par("nz")=2;              
                            shape.Z(0)=-swam.len/2;              
                            shape.Z(1)=+swam.len/2;              
                            shape.Rmin(0)=rin;              
                            shape.Rmin(1)=rin;              
                            shape.Rmax(0)=rou;              
                            shape.Rmax(1)=rou;              
                            /// Shape Pgon phi1=0 dphi=360 npdiv=18 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWMM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SWMB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWMB              
                            Create("SWMB");               
                      }           
                      { AgPlacement place = AgPlacement("SWMB","SWMM");              
                            /// Add daughter volume SWMB to mother SWMM              
                            _stacker -> Position( AgBlock::Find("SWMB"), place );              
                      } // end placement of SWMB           
                      _create = AgCreate("SWMT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWMT              
                            Create("SWMT");               
                      }           
                      { AgPlacement place = AgPlacement("SWMT","SWMM");              
                            /// Add daughter volume SWMT to mother SWMM              
                            _stacker -> Position( AgBlock::Find("SWMT"), place );              
                      } // end placement of SWMT           
                      _create = AgCreate("SWMS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWMS              
                            Create("SWMS");               
                      }           
                      { AgPlacement place = AgPlacement("SWMS","SWMM");              
                            /// Add daughter volume SWMS to mother SWMM              
                            place.TranslateZ(-swam.len/2+swam.wallthk/2);              
                            /// Translate z = -swam.len/2+swam.wallthk/2              
                            _stacker -> Position( AgBlock::Find("SWMS"), place );              
                      } // end placement of SWMS           
                      { AgPlacement place = AgPlacement("SWMS","SWMM");              
                            /// Add daughter volume SWMS to mother SWMM              
                            place.TranslateZ(swam.len/2-swam.wallthk/2);              
                            /// Translate z = swam.len/2-swam.wallthk/2              
                            _stacker -> Position( AgBlock::Find("SWMS"), place );              
                      } // end placement of SWMS           
                      _create = AgCreate("SWMW");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWMW              
                            Create("SWMW");               
                      }           
                      { AgPlacement place = AgPlacement("SWMW","SWMM");              
                            /// Add daughter volume SWMW to mother SWMM              
                            _stacker -> Position( AgBlock::Find("SWMW"), place );              
                      } // end placement of SWMW           
                      _create = AgCreate("SOTB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SOTB              
                            Create("SOTB");               
                      }           
                      { AgPlacement place = AgPlacement("SOTB","SWMM");              
                            /// Add daughter volume SOTB to mother SWMM              
                            _stacker -> Position( AgBlock::Find("SOTB"), place );              
                      } // end placement of SOTB           
                      _create = AgCreate("SITB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SITB              
                            Create("SITB");               
                      }           
                      { AgPlacement place = AgPlacement("SITB","SWMM");              
                            /// Add daughter volume SITB to mother SWMM              
                            _stacker -> Position( AgBlock::Find("SITB"), place );              
                      } // end placement of SITB           
                      END_OF_SWMM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWMM     
          // ---------------------------------------------------------------------------------------------------     
          void SWMB::Block( AgCreate create )     
          {         
                ///@addtogroup SWMB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SWMB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("npdiv")=18;              
                            shape.par("nz")=2;              
                            shape.Z(0)=-swam.len/2+swam.wallthk;              
                            shape.Z(1)=swam.len/2-swam.wallthk;              
                            shape.Rmin(0)=swam.rmin;              
                            shape.Rmin(1)=swam.rmin;              
                            shape.Rmax(0)=swam.rmin+swam.wallthk;              
                            shape.Rmax(1)=swam.rmin+swam.wallthk;              
                            /// Shape Pgon phi1=0 dphi=360 npdiv=18 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWMB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SWMB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWMB     
          // ---------------------------------------------------------------------------------------------------     
          void SWMT::Block( AgCreate create )     
          {         
                ///@addtogroup SWMT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SWMT");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("npdiv")=18;              
                            shape.par("nz")=2;              
                            shape.Z(0)=-swam.len/2+swam.wallthk;              
                            shape.Z(1)=swam.len/2-swam.wallthk;              
                            shape.Rmin(0)=swam.rmax-swam.wallthk;              
                            shape.Rmin(1)=swam.rmax-swam.wallthk;              
                            shape.Rmax(0)=swam.rmax;              
                            shape.Rmax(1)=swam.rmax;              
                            /// Shape Pgon phi1=0 dphi=360 npdiv=18 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWMT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SWMT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWMT     
          // ---------------------------------------------------------------------------------------------------     
          void SWMS::Block( AgCreate create )     
          {         
                ///@addtogroup SWMS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SWMS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("npdiv")=18;              
                            shape.par("nz")=2;              
                            shape.Z(0)=-swam.wallthk/2;              
                            shape.Z(1)=swam.wallthk/2;              
                            shape.Rmin(0)=swam.rmin;              
                            shape.Rmin(1)=swam.rmin;              
                            shape.Rmax(0)=swam.rmax;              
                            shape.Rmax(1)=swam.rmax;              
                            /// Shape Pgon phi1=0 dphi=360 npdiv=18 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWMS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SWMS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWMS     
          // ---------------------------------------------------------------------------------------------------     
          void SWMW::Block( AgCreate create )     
          {         
                ///@addtogroup SWMW_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SWMW");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Water            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Water");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("npdiv")=18;              
                            shape.par("nz")=2;              
                            shape.Z(0)=-swam.len/2+swam.wallthk;              
                            shape.Z(1)=swam.len/2-swam.wallthk;              
                            shape.Rmin(0)=swam.rmin+swam.wallthk;              
                            shape.Rmin(1)=swam.rmin+swam.wallthk;              
                            shape.Rmax(0)=swam.rmax-swam.wallthk;              
                            shape.Rmax(1)=swam.rmax-swam.wallthk;              
                            /// Shape Pgon phi1=0 dphi=360 npdiv=18 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWMW;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SWMW:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWMW     
          // ---------------------------------------------------------------------------------------------------     
          void SOTB::Block( AgCreate create )     
          {         
                ///@addtogroup SOTB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SOTB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("npdiv")=18;              
                            shape.par("nz")=2;              
                            shape.Z(0)=-swam.len/2;              
                            shape.Z(1)=+swam.len/2;              
                            shape.Rmin(0)=swam.rmax;              
                            shape.Rmin(1)=swam.rmax;              
                            shape.Rmax(0)=swam.rmax+swam.tbrdthk;              
                            shape.Rmax(1)=swam.rmax+swam.tbrdthk;              
                            /// Shape Pgon phi1=0 dphi=360 npdiv=18 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SOTB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SOTB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SOTB     
          // ---------------------------------------------------------------------------------------------------     
          void SITB::Block( AgCreate create )     
          {         
                ///@addtogroup SITB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component C	a=12	z=6	w=1           
                      /// Component H2	a=1	z=1	w=2           
                      /// Mixture CH2 dens=0.935           
                      {  AgMaterial &mix = AgMaterial::Get("Ch2");              
                            mix.Component("C",12,6,1);              
                            mix.Component("H2",1,1,2);              
                            mix.par("dens")=0.935;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("SITB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("npdiv")=18;              
                            shape.par("nz")=2;              
                            shape.Z(0)=-swam.len/2;              
                            shape.Z(1)=+swam.len/2;              
                            shape.Rmin(0)=swam.rmin-swam.tbrdthk;              
                            shape.Rmin(1)=swam.rmin-swam.tbrdthk;              
                            shape.Rmax(0)=swam.rmin;              
                            shape.Rmax(1)=swam.rmin;              
                            /// Shape Pgon phi1=0 dphi=360 npdiv=18 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SITB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SITB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SITB     
          // ---------------------------------------------------------------------------------------------------     
          void SBWC::Block( AgCreate create )     
          {         
                ///@addtogroup SBWC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      rin=swam.rmin;           
                      rou=ssup.con1idmn;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBWC");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=rin;              
                            shape.par("rmax")=rou;              
                            shape.par("dz")=(ssup.cone1zmn-(swam.zmin+swam.len))/2;              
                            /// Shape Tube rmin=rin rmax=rou dz=(ssup.cone1zmn-(swam.zmin+swam.len))/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBWC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SWCM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SWCM              
                            Create("SWCM");               
                      }           
                      END_OF_SBWC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBWC     
          // ---------------------------------------------------------------------------------------------------     
          void SWCM::Block( AgCreate create )     
          {         
                ///@addtogroup SWCM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SWCM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=3;              
                            shape.par("iaxis")=2;              
                            shape.par("c0")=0;              
                            /// Shape Division ndiv=3 iaxis=2 c0=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SWCM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SXAI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SXAI              
                            Create("SXAI");               
                      }           
                      { AgPlacement place = AgPlacement("SXAI","SWCM");              
                            /// Add daughter volume SXAI to mother SWCM              
                            place.TranslateZ((-(ssup.cone1zmn-(swam.zmin+swam.len))/2+ssup.brathk/2));              
                            /// Translate z = (-(ssup.cone1zmn-(swam.zmin+swam.len))/2+ssup.brathk/2)              
                            _stacker -> Position( AgBlock::Find("SXAI"), place );              
                      } // end placement of SXAI           
                      _create = AgCreate("SXBI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SXBI              
                            Create("SXBI");               
                      }           
                      { AgPlacement place = AgPlacement("SXBI","SWCM");              
                            /// Add daughter volume SXBI to mother SWCM              
                            place.TranslateZ((ssup.brathk/2));              
                            /// Translate z = (ssup.brathk/2)              
                            _stacker -> Position( AgBlock::Find("SXBI"), place );              
                      } // end placement of SXBI           
                      END_OF_SWCM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SWCM     
          // ---------------------------------------------------------------------------------------------------     
          void SXAI::Block( AgCreate create )     
          {         
                ///@addtogroup SXAI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SXAI");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=swam.rmin;              
                            shape.par("rmax")=ssup.con1idmn;              
                            shape.par("phi1")=-5;              
                            shape.par("phi2")=5;              
                            shape.par("dz")=ssup.brathk/2;              
                            /// Shape Tubs rmin=swam.rmin rmax=ssup.con1idmn phi1=-5 phi2=5 dz=ssup.brathk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SXAI;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SXAI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SXAI     
          // ---------------------------------------------------------------------------------------------------     
          void SXBI::Block( AgCreate create )     
          {         
                ///@addtogroup SXBI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("SXBI");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssup.con1idmn-ssup.brathk;              
                            shape.par("rmax")=ssup.con1idmn;              
                            shape.par("phi1")=-5;              
                            shape.par("phi2")=5;              
                            shape.par("dz")=((ssup.cone1zmn-(swam.zmin+swam.len)-ssup.brathk)/2);              
                            /// Shape Tubs rmin=ssup.con1idmn-ssup.brathk rmax=ssup.con1idmn phi1=-5 phi2=5 dz=((ssup.cone1zmn-(swam.zmin+swam.len)-ssup.brathk)/2)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SXBI;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SXBI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SXBI     
          // ---------------------------------------------------------------------------------------------------     
          void SCRW::Block( AgCreate create )     
          {         
                ///@addtogroup SCRW_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Berillium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Berillium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCRW");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=ssup.erjdia/2;              
                            shape.par("dz")=0.5*(brack_z-endrng_z);              
                            /// Shape Tube rmin=0 rmax=ssup.erjdia/2 dz=0.5*(brack_z-endrng_z)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCRW;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SCRW:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCRW     
          // ---------------------------------------------------------------------------------------------------     
          void SBSP::Block( AgCreate create )     
          {         
                ///@addtogroup SBSP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBSP");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=svtg.rsizemin;              
                            shape.par("rmax")=ssub.kmountod/2;              
                            shape.par("dz")=ssub.kmntthk/2+ssub.mblkhgh;              
                            /// Shape Tube rmin=svtg.rsizemin rmax=ssub.kmountod/2 dz=ssub.kmntthk/2+ssub.mblkhgh               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBSP;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SAKM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SAKM              
                            Create("SAKM");               
                      }           
                      { AgPlacement place = AgPlacement("SAKM","SBSP");              
                            /// Add daughter volume SAKM to mother SBSP              
                            _stacker -> Position( AgBlock::Find("SAKM"), place );              
                      } // end placement of SAKM           
                      _create = AgCreate("SBMM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBMM              
                            Create("SBMM");               
                      }           
                      _create = AgCreate("SBMM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBMM              
                            Create("SBMM");               
                      }           
                      _create = AgCreate("SBRL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBRL              
                            Create("SBRL");               
                      }           
                      _create = AgCreate("SBRX");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBRX              
                            Create("SBRX");               
                      }           
                      /// Loop on i from -1 to 1 step=2           
                      for ( i=-1; (2>0)? (i<=1):(i>=1); i+=2 )           
                      {              
                            /// Loop on j from 0 to 1 step=1              
                            for ( j=0; (1>0)? (j<=1):(j>=1); j+=1 )              
                            {                 
                                  phi=i*ssub.srcutphi+180*j;                 
                                  xbuf1=(ssub.kmountod/4.0+(svtg.rsizemin+ssub.srollod)/2.0);                 
                                  { AgPlacement place = AgPlacement("SBMM","SBSP");                    
                                        /// Add daughter volume SBMM to mother SBSP                    
                                        place.TranslateX(xbuf1*sin(degrad*phi));                    
                                        /// Translate x = xbuf1*sin(degrad*phi)                    
                                        place.TranslateY(-xbuf1*cos(degrad*phi));                    
                                        /// Translate y = -xbuf1*cos(degrad*phi)                    
                                        place.TranslateZ(-ssub.kmntthk/2-ssub.mblkhgh/2);                    
                                        /// Translate z = -ssub.kmntthk/2-ssub.mblkhgh/2                    
                                        place.AlphaZ(phi);                    
                                        /// Rotate: AlphaZ = phi                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SBMM"), place );                    
                                  } // end placement of SBMM                 
                                  xbuf2=svtg.rsizemin+ssub.srollod/2;                 
                                  { AgPlacement place = AgPlacement("SBRL","SBSP");                    
                                        /// Add daughter volume SBRL to mother SBSP                    
                                        place.TranslateX(xbuf2*sin(degrad*phi));                    
                                        /// Translate x = xbuf2*sin(degrad*phi)                    
                                        place.TranslateY(-xbuf2*cos(degrad*phi));                    
                                        /// Translate y = -xbuf2*cos(degrad*phi)                    
                                        place.TranslateZ(ssub.sringthk/2+ssub.srollid/2);                    
                                        /// Translate z = ssub.sringthk/2+ssub.srollid/2                    
                                        place.AlphaZ(phi-90);                    
                                        /// Rotate: AlphaZ = phi-90                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        place.Ortho( "ZXY" ); // ORT=ZXY                    
                                        /// Axis substitution: XYZ --> ZXY                    
                                        _stacker -> Position( AgBlock::Find("SBRL"), place );                    
                                  } // end placement of SBRL                 
                                  { AgPlacement place = AgPlacement("SBRX","SBSP");                    
                                        /// Add daughter volume SBRX to mother SBSP                    
                                        place.TranslateX(xbuf2*sin(degrad*phi));                    
                                        /// Translate x = xbuf2*sin(degrad*phi)                    
                                        place.TranslateY(-xbuf2*cos(degrad*phi));                    
                                        /// Translate y = -xbuf2*cos(degrad*phi)                    
                                        place.TranslateZ(ssub.sringthk/2+ssub.srollid/2);                    
                                        /// Translate z = ssub.sringthk/2+ssub.srollid/2                    
                                        place.AlphaZ(phi-90);                    
                                        /// Rotate: AlphaZ = phi-90                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        place.Ortho( "ZXY" ); // ORT=ZXY                    
                                        /// Axis substitution: XYZ --> ZXY                    
                                        _stacker -> Position( AgBlock::Find("SBRX"), place );                    
                                  } // end placement of SBRX                 
                            }              
                      }           
                      _create = AgCreate("SBSR");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBSR              
                            Create("SBSR");               
                      }           
                      { AgPlacement place = AgPlacement("SBSR","SBSP");              
                            /// Add daughter volume SBSR to mother SBSP              
                            _stacker -> Position( AgBlock::Find("SBSR"), place );              
                      } // end placement of SBSR           
                      END_OF_SBSP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBSP     
          // ---------------------------------------------------------------------------------------------------     
          void SAKM::Block( AgCreate create )     
          {         
                ///@addtogroup SAKM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SAKM");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssub.kmountid/2;              
                            shape.par("rmax")=ssub.kmountod/2;              
                            shape.par("dz")=ssub.kmntthk/2;              
                            /// Shape Tube rmin=ssub.kmountid/2 rmax=ssub.kmountod/2 dz=ssub.kmntthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SAKM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SCKM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCKM              
                            Create("SCKM");               
                      }           
                      { AgPlacement place = AgPlacement("SCKM","SAKM");              
                            /// Add daughter volume SCKM to mother SAKM              
                            place.TranslateY(ssub.kmcutoff);              
                            /// Translate y = ssub.kmcutoff              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("SCKM"), place );              
                      } // end placement of SCKM           
                      { AgPlacement place = AgPlacement("SCKM","SAKM");              
                            /// Add daughter volume SCKM to mother SAKM              
                            place.TranslateY(-ssub.kmcutoff);              
                            /// Translate y = -ssub.kmcutoff              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            place.AlphaZ(180);              
                            /// Rotate: AlphaZ = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCKM"), place );              
                      } // end placement of SCKM           
                      END_OF_SAKM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SAKM     
          // ---------------------------------------------------------------------------------------------------     
          void SCKM::Block( AgCreate create )     
          {         
                ///@addtogroup SCKM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCKM");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssub.kmcutid/2;              
                            shape.par("rmax")=ssub.kmcutod/2;              
                            shape.par("phi1")=270-ssub.kmcutoa;              
                            shape.par("phi2")=270+ssub.kmcutoa;              
                            shape.par("dz")=ssub.kmntthk/2;              
                            /// Shape Tubs rmin=ssub.kmcutid/2 rmax=ssub.kmcutod/2 phi1=270-ssub.kmcutoa phi2=270+ssub.kmcutoa dz=ssub.kmntthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCKM;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SCKM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCKM     
          // ---------------------------------------------------------------------------------------------------     
          void SBSR::Block( AgCreate create )     
          {         
                ///@addtogroup SBSR_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBSR");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssub.sringid/2;              
                            shape.par("rmax")=ssub.sringod/2;              
                            shape.par("dz")=ssub.sringthk/2;              
                            /// Shape Tube rmin=ssub.sringid/2 rmax=ssub.sringod/2 dz=ssub.sringthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBSR;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SBCR");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBCR              
                            Create("SBCR");               
                      }           
                      xbuf=ssub.srcutin+(ssub.srcutout-ssub.srcutin)/2;           
                      /// Loop on i from -1 to 1 step=2           
                      for ( i=-1; (2>0)? (i<=1):(i>=1); i+=2 )           
                      {              
                            /// Loop on j from 0 to 1 step=1              
                            for ( j=0; (1>0)? (j<=1):(j>=1); j+=1 )              
                            {                 
                                  phi=i*ssub.srcutphi+180*j;                 
                                  { AgPlacement place = AgPlacement("SBCR","SBSR");                    
                                        /// Add daughter volume SBCR to mother SBSR                    
                                        place.TranslateX(xbuf*sin(degrad*phi));                    
                                        /// Translate x = xbuf*sin(degrad*phi)                    
                                        place.TranslateY(-xbuf*cos(degrad*phi));                    
                                        /// Translate y = -xbuf*cos(degrad*phi)                    
                                        place.par("only")=AgPlacement::kMany;                    
                                        /// Overlap: agplacement::kmany                    
                                        place.AlphaZ(phi);                    
                                        /// Rotate: AlphaZ = phi                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SBCR"), place );                    
                                  } // end placement of SBCR                 
                            }              
                      }           
                      END_OF_SBSR:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBSR     
          // ---------------------------------------------------------------------------------------------------     
          void SBCR::Block( AgCreate create )     
          {         
                ///@addtogroup SBCR_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBCR");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=ssub.srcutwid/2;              
                            shape.par("dy")=(ssub.srcutout-ssub.srcutin)/2;              
                            shape.par("dz")=ssub.sringthk/2;              
                            /// Shape Bbox dx=ssub.srcutwid/2 dy=(ssub.srcutout-ssub.srcutin)/2 dz=ssub.sringthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBCR;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBCR:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBCR     
          // ---------------------------------------------------------------------------------------------------     
          void SBRL::Block( AgCreate create )     
          {         
                ///@addtogroup SBRL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material PYREX a=20.719 z=10.307 dens=2.23 absl=50.7 radl=12.6            
                      { AgMaterial &mat = AgMaterial::Get("Pyrex");              
                            mat.par("a")=20.719;              
                            mat.par("z")=10.307;              
                            mat.par("dens")=2.23;              
                            mat.par("absl")=50.7;              
                            mat.par("radl")=12.6;              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBRL");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssub.srollid/2;              
                            shape.par("rmax")=ssub.srollod/2;              
                            /// Shape Tube rmin=ssub.srollid/2 rmax=ssub.srollod/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBRL;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBRL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBRL     
          // ---------------------------------------------------------------------------------------------------     
          void SBRX::Block( AgCreate create )     
          {         
                ///@addtogroup SBRX_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Iron            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Iron");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBRX");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0.0;              
                            shape.par("rmax")=ssub.srollid/2;              
                            shape.par("dz")=ssub.swirelen/2;              
                            /// Shape Tube rmin=0.0 rmax=ssub.srollid/2 dz=ssub.swirelen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBRX;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBRX:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBRX     
          // ---------------------------------------------------------------------------------------------------     
          void SBMM::Block( AgCreate create )     
          {         
                ///@addtogroup SBMM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBMM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=ssub.mblkiwid/2;              
                            shape.par("dy")=(ssub.kmountod/2-svtg.rsizemin-ssub.srollod)/2;              
                            shape.par("dz")=ssub.mblkhgh/2;              
                            /// Shape Bbox dx=ssub.mblkiwid/2 dy=(ssub.kmountod/2-svtg.rsizemin-ssub.srollod)/2 dz=ssub.mblkhgh/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBMM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SMRD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SMRD              
                            Create("SMRD");               
                      }           
                      xbuf=-(ssub.mblkorad+ssub.mblkirad)/2+svtg.rsizemin+ssub.srollod;           
                      { AgPlacement place = AgPlacement("SMRD","SBMM");              
                            /// Add daughter volume SMRD to mother SBMM              
                            place.TranslateY(xbuf+(ssub.kmountod/2-svtg.rsizemin-ssub.srollod)/2);              
                            /// Translate y = xbuf+(ssub.kmountod/2-svtg.rsizemin-ssub.srollod)/2              
                            place.AlphaX(90);              
                            /// Rotate: AlphaX = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SMRD"), place );              
                      } // end placement of SMRD           
                      _create = AgCreate("SBMO");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBMO              
                            Create("SBMO");               
                      }           
                      xbuf=-ssub.mblkorad+svtg.rsizemin+ssub.srollod;           
                      { AgPlacement place = AgPlacement("SBMO","SBMM");              
                            /// Add daughter volume SBMO to mother SBMM              
                            place.TranslateY(xbuf+(ssub.kmountod/2-svtg.rsizemin-ssub.srollod)/2);              
                            /// Translate y = xbuf+(ssub.kmountod/2-svtg.rsizemin-ssub.srollod)/2              
                            _stacker -> Position( AgBlock::Find("SBMO"), place );              
                      } // end placement of SBMO           
                      _create = AgCreate("SBMI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBMI              
                            Create("SBMI");               
                      }           
                      xbuf=-ssub.mblkirad+svtg.rsizemin+ssub.srollod;           
                      { AgPlacement place = AgPlacement("SBMI","SBMM");              
                            /// Add daughter volume SBMI to mother SBMM              
                            place.TranslateY(xbuf+(ssub.kmountod/2-svtg.rsizemin-ssub.srollod)/2);              
                            /// Translate y = xbuf+(ssub.kmountod/2-svtg.rsizemin-ssub.srollod)/2              
                            _stacker -> Position( AgBlock::Find("SBMI"), place );              
                      } // end placement of SBMI           
                      END_OF_SBMM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBMM     
          // ---------------------------------------------------------------------------------------------------     
          void SMRD::Block( AgCreate create )     
          {         
                ///@addtogroup SMRD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SMRD");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0.0;              
                            shape.par("rmax")=ssub.mroddia/2;              
                            shape.par("dz")=(ssub.mblkorad-ssub.mblkirad+ssub.mblkolen)/2;              
                            /// Shape Tube rmin=0.0 rmax=ssub.mroddia/2 dz=(ssub.mblkorad-ssub.mblkirad+ssub.mblkolen)/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SMRD;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SMRD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SMRD     
          // ---------------------------------------------------------------------------------------------------     
          void SBMO::Block( AgCreate create )     
          {         
                ///@addtogroup SBMO_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBMO");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=ssub.mblkowid/2;              
                            shape.par("dy")=ssub.mblkolen/2;              
                            shape.par("dz")=ssub.mblkhgh/2;              
                            /// Shape Bbox dx=ssub.mblkowid/2 dy=ssub.mblkolen/2 dz=ssub.mblkhgh/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBMO;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBMO:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBMO     
          // ---------------------------------------------------------------------------------------------------     
          void SBMI::Block( AgCreate create )     
          {         
                ///@addtogroup SBMI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBMO");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=ssub.mblkiwid/2;              
                            shape.par("dy")=ssub.mblkilen/2;              
                            shape.par("dz")=ssub.mblkhgh/2;              
                            /// Shape Bbox dx=ssub.mblkiwid/2 dy=ssub.mblkilen/2 dz=ssub.mblkhgh/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBMI;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBMI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBMI     
          // ---------------------------------------------------------------------------------------------------     
          void SALM::Block( AgCreate create )     
          {         
                ///@addtogroup SALM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SALM");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssld.almeshid/2;              
                            shape.par("rmax")=ssld.almeshod/2;              
                            shape.par("dz")=ssld.almshthk/2;              
                            /// Shape Tube rmin=ssld.almeshid/2 rmax=ssld.almeshod/2 dz=ssld.almshthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SALM;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SALM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SALM     
          // ---------------------------------------------------------------------------------------------------     
          void SISH::Block( AgCreate create )     
          {         
                ///@addtogroup SISH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material ALKAP            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Alkap");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SISH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssld.sinrinn;              
                            shape.par("rmax")=ssld.sinrout;              
                            shape.par("dz")=ssld.sinlen;              
                            /// Shape Tube rmin=ssld.sinrinn rmax=ssld.sinrout dz=ssld.sinlen               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SISH;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SISH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SISH     
          // ---------------------------------------------------------------------------------------------------     
          void SSSH::Block( AgCreate create )     
          {         
                ///@addtogroup SSSH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material SSDALMY            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Ssdalmy");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SSSH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssld.sseprinn;              
                            shape.par("rmax")=ssld.sseprout;              
                            shape.par("dz")=ssld.sseplen;              
                            /// Shape Tube rmin=ssld.sseprinn rmax=ssld.sseprout dz=ssld.sseplen               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSSH;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SSSH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSSH     
          // ---------------------------------------------------------------------------------------------------     
          void SOSH::Block( AgCreate create )     
          {         
                ///@addtogroup SOSH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material SSDALMY            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Ssdalmy");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SOSH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=ssld.soutrinn;              
                            shape.par("rmax")=ssld.soutrout;              
                            shape.par("dz")=ssld.soutlen;              
                            /// Shape Tube rmin=ssld.soutrinn rmax=ssld.soutrout dz=ssld.soutlen               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SOSH;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SOSH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SOSH     
    // ----------------------------------------------------------------------- geoctr
       void SvttGeo4::ConstructGeometry()     
       {        
             ///@addtogroup SvttGeo4_revision        
             ///@{           
                   /// Author: Maxim Potekhin           
             ///@}        
             ///@addtogroup SvttGeo4_revision        
             ///@{           
                   /// Created:  24 Mar 2004            
             ///@}        
             AddBlock("SVTT");        
             AddBlock("SLYD");        
             AddBlock("SLSD");        
             AddBlock("SLDI");        
             AddBlock("STLI");        
             AddBlock("STSI");        
             AddBlock("SVTD");        
             AddBlock("SBER");        
             AddBlock("STAB");        
             AddBlock("STRU");        
             AddBlock("SPCB");        
             AddBlock("SRHC");        
             AddBlock("SBWC");        
             AddBlock("SWCM");        
             AddBlock("SXAI");        
             AddBlock("SXBI");        
             AddBlock("SELE");        
             AddBlock("SWCH");        
             AddBlock("SWCW");        
             AddBlock("SWCS");        
             AddBlock("SBOI");        
             AddBlock("SAGP");        
             AddBlock("SDYE");        
             AddBlock("SECA");        
             AddBlock("SIRP");        
             AddBlock("SIRT");        
             AddBlock("SOER");        
             AddBlock("SCON");        
             AddBlock("SROD");        
             AddBlock("SGRA");        
             AddBlock("STAP");        
             AddBlock("STAC");        
             AddBlock("SHLA");        
             AddBlock("SHLB");        
             AddBlock("SHMA");        
             AddBlock("SHMB");        
             AddBlock("SWHO");        
             AddBlock("SHWA");        
             AddBlock("SCMY");        
             AddBlock("SCAL");        
             AddBlock("SWMM");        
             AddBlock("SWMB");        
             AddBlock("SWRP");        
             AddBlock("SXRL");        
             AddBlock("SYRU");        
             AddBlock("SWMT");        
             AddBlock("SWMS");        
             AddBlock("SWMW");        
             AddBlock("SOTB");        
             AddBlock("SITB");        
             AddBlock("SBRG");        
             AddBlock("SBRM");        
             AddBlock("SBRI");        
             AddBlock("SOES");        
             AddBlock("SIES");        
             AddBlock("SOSM");        
             AddBlock("SISM");        
             AddBlock("SCRW");        
             AddBlock("SGLA");        
             AddBlock("SBSP");        
             AddBlock("SAKM");        
             AddBlock("SCKM");        
             AddBlock("SBSR");        
             AddBlock("SBCR");        
             AddBlock("SBRX");        
             AddBlock("SBRL");        
             AddBlock("SBMM");        
             AddBlock("SBMO");        
             AddBlock("SBMI");        
             AddBlock("SMRD");        
             AddBlock("SALM");        
             AddBlock("SISH");        
             AddBlock("SSSH");        
             AddBlock("SOSH");        
             AddBlock("SCBM");        
             AddBlock("SCBL");        
             AddBlock("SFED");        
             AddBlock("SPLS");        
             AddBlock("SOUM");        
             AddBlock("SOUR");        
             radii(1)= 6.37;        
             radii(2)= 7.38;        
             radii(3)=10.38;        
             radii(4)=11.27;        
             radii(5)=14.19;        
             radii(6)=15.13;        
             rad_offset=0.015;        
             shield_phi(1)=9.0;        
             shield_phi(2)=27.0;        
             shield_phi(3)=45.0;        
             shield_phi(4)=63.0;        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup svtg_doc        
             ///@{           
                   ++svtg._index;           
                   svtg . version = 2; //  geometry version            
                   /// svtg . version = 2; //  geometry version            
                   svtg . nlayer = 7; //  number of svt layers (was 7)            
                   /// svtg . nlayer = 7; //  number of svt layers (was 7)            
                   svtg . rsizemin = 4.100; //  STV innermost radius            
                   /// svtg . rsizemin = 4.100; //  STV innermost radius            
                   svtg . rsizemax = 46.107; //  STV outermost radius            
                   /// svtg . rsizemax = 46.107; //  STV outermost radius            
                   svtg . zsizemax = 270; //  SVT+FTPC length            
                   /// svtg . zsizemax = 270; //  SVT+FTPC length            
                   svtg . angoff = 0; //  angular offset x1 for slayer 2 x2 for slayer 3            
                   /// svtg . angoff = 0; //  angular offset x1 for slayer 2 x2 for slayer 3            
                   svtg . supportver = 1; //  versioning of the shield            
                   /// svtg . supportver = 1; //  versioning of the shield            
                   svtg . conever = 1; //  versioning of the support cone            
                   /// svtg . conever = 1; //  versioning of the support cone            
                   svtg . ifmany = 0; //  whether we use the geant MANY option            
                   /// svtg . ifmany = 0; //  whether we use the geant MANY option            
                   svtg . nmin = 1; //  the index of the innermost layer            
                   /// svtg . nmin = 1; //  the index of the innermost layer            
                   //           
                   svtg.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup swca_doc        
             ///@{           
                   ++swca._index;           
                   swca . version = 1; //  geometry version            
                   /// swca . version = 1; //  geometry version            
                   swca . length = 56.04; //  ladder length            
                   /// swca . length = 56.04; //  ladder length            
                   swca . waferwid = 6.305; //  wafer width            
                   /// swca . waferwid = 6.305; //  wafer width            
                   swca . waferlen = 6.305; //  wafer length            
                   /// swca . waferlen = 6.305; //  wafer length            
                   swca . waferthk = 0.0300; //  wafer thickness            
                   /// swca . waferthk = 0.0300; //  wafer thickness            
                   swca . rohathk = 0.0381; //  Roha cell plus glue thickness             
                   /// swca . rohathk = 0.0381; //  Roha cell plus glue thickness             
                   swca . wafcarwd = 1.5; //  wafer carrier rails width            
                   /// swca . wafcarwd = 1.5; //  wafer carrier rails width            
                   swca . wafcarth = 0.0300; //  wafer carrier thickness             
                   /// swca . wafcarth = 0.0300; //  wafer carrier thickness             
                   swca . wafergap = 0.05; //  width of the inter-wafer gap (was 0 in prev versions)            
                   /// swca . wafergap = 0.05; //  width of the inter-wafer gap (was 0 in prev versions)            
                   swca . drift = 1; //  drift direction            
                   /// swca . drift = 1; //  drift direction            
                   swca . strutlen = 1.0; //  len (z) of strut between waf car. rails (approx)            
                   /// swca . strutlen = 1.0; //  len (z) of strut between waf car. rails (approx)            
                   //           
                   swca.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup ssup_doc        
             ///@{           
                   ++ssup._index;           
                   ssup . version = 1; //  geometry version            
                   /// ssup . version = 1; //  geometry version            
                   ssup . cabthk = 0.05; //  thickness of layer of cables on support cone            
                   /// ssup . cabthk = 0.05; //  thickness of layer of cables on support cone            
                   ssup . hosrmn = 0.75; //  inner radius of water hoses on support cone            
                   /// ssup . hosrmn = 0.75; //  inner radius of water hoses on support cone            
                   ssup . hosrmx = 0.95; //  outer radius of water hoses on support cone            
                   /// ssup . hosrmx = 0.95; //  outer radius of water hoses on support cone            
                   ssup . nhoses = 10; //  number of water hoses            
                   /// ssup . nhoses = 10; //  number of water hoses            
                   ssup . wrpmythk = 0.10; //  thickness of mylar wrap around cone (guess)            
                   /// ssup . wrpmythk = 0.10; //  thickness of mylar wrap around cone (guess)            
                   ssup . wrpalthk = 0.01; //  thickness of Al on mylar wrap (guess)            
                   /// ssup . wrpalthk = 0.01; //  thickness of Al on mylar wrap (guess)            
                   ssup . grphthk = 0.16; //  support cone thickness            
                   /// ssup . grphthk = 0.16; //  support cone thickness            
                   ssup . cone1zmn = 52.23; //  Cone z min (parts 1,2,3,4 in increasing z)            
                   /// ssup . cone1zmn = 52.23; //  Cone z min (parts 1,2,3,4 in increasing z)            
                   ssup . rodlen = 110.8; //  Length of support rods            
                   /// ssup . rodlen = 110.8; //  Length of support rods            
                   ssup . roddist = 17.5; //  Distance of support rod od from beam axis             
                   /// ssup . roddist = 17.5; //  Distance of support rod od from beam axis             
                   ssup . rodid = 2.5; //  ID of Carbon support rods (approx)            
                   /// ssup . rodid = 2.5; //  ID of Carbon support rods (approx)            
                   ssup . rodod = 3.05; //  OD of Carbon support rods (approx)            
                   /// ssup . rodod = 3.05; //  OD of Carbon support rods (approx)            
                   ssup . con1idmn = 15.67; //  Minimum id of cone 1             
                   /// ssup . con1idmn = 15.67; //  Minimum id of cone 1             
                   ssup . con3idmn = 21.67; //  Minimum id of cone 3 (TBD)            
                   /// ssup . con3idmn = 21.67; //  Minimum id of cone 3 (TBD)            
                   ssup . con4idmn = 37.4; //  Minimum id of cone 4 (TBD)            
                   /// ssup . con4idmn = 37.4; //  Minimum id of cone 4 (TBD)            
                   ssup . con4idmx = 37.4; //  Maximum id of cone 4 (TBD)            
                   /// ssup . con4idmx = 37.4; //  Maximum id of cone 4 (TBD)            
                   ssup . cone3zmx = 150.0; //  Maximum z of cone 3 (TBD)            
                   /// ssup . cone3zmx = 150.0; //  Maximum z of cone 3 (TBD)            
                   ssup . cone4zmx = 229.36; //  Maximum z of cone 4 (TBD)            
                   /// ssup . cone4zmx = 229.36; //  Maximum z of cone 4 (TBD)            
                   ssup . brathk = .2; //  thickness of Al brackets             
                   /// ssup . brathk = .2; //  thickness of Al brackets             
                   ssup . erjthk = .1; //  (z) thickness of end ring joining brackets            
                   /// ssup . erjthk = .1; //  (z) thickness of end ring joining brackets            
                   ssup . erjwid = 2.07; //  (azimuthal) width of end ring joining brackets            
                   /// ssup . erjwid = 2.07; //  (azimuthal) width of end ring joining brackets            
                   ssup . erjlen = 5.19; //  (radial) length of end ring joining brackets            
                   /// ssup . erjlen = 5.19; //  (radial) length of end ring joining brackets            
                   ssup . erjzdis = 2.0; //  dist from ladder ends to ERJ (guess)            
                   /// ssup . erjzdis = 2.0; //  dist from ladder ends to ERJ (guess)            
                   ssup . erj1x = 0.31; //  ERJ screw 1 x position (radial)            
                   /// ssup . erj1x = 0.31; //  ERJ screw 1 x position (radial)            
                   ssup . erj2x = 1.15; //  ERJ screw 2 x position            
                   /// ssup . erj2x = 1.15; //  ERJ screw 2 x position            
                   ssup . erj2y = 0.72; //  ERJ screw 2 y position            
                   /// ssup . erj2y = 0.72; //  ERJ screw 2 y position            
                   ssup . erjrad = 10.80; //  distance of ERJ center from beam axis            
                   /// ssup . erjrad = 10.80; //  distance of ERJ center from beam axis            
                   ssup . erjdia = 0.17; //  ERJ screw diameter            
                   /// ssup . erjdia = 0.17; //  ERJ screw diameter            
                   //           
                   ssup.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup ssup_doc        
             ///@{           
                   ++ssup._index;           
                   ssup . version = 2; //  geometry version            
                   /// ssup . version = 2; //  geometry version            
                   ssup . cabthk = 0.21; //  thickness of layer of cables on support cone            
                   /// ssup . cabthk = 0.21; //  thickness of layer of cables on support cone            
                   ssup . hosrmn = 0.75; //  inner radius of water hoses on support cone            
                   /// ssup . hosrmn = 0.75; //  inner radius of water hoses on support cone            
                   ssup . hosrmx = 0.95; //  outer radius of water hoses on support cone            
                   /// ssup . hosrmx = 0.95; //  outer radius of water hoses on support cone            
                   ssup . nhoses = 10; //  number of water hoses            
                   /// ssup . nhoses = 10; //  number of water hoses            
                   ssup . wrpmythk = 0.10; //  thickness of mylar wrap around cone (guess)            
                   /// ssup . wrpmythk = 0.10; //  thickness of mylar wrap around cone (guess)            
                   ssup . wrpalthk = 0.01; //  thickness of Al on mylar wrap (guess)            
                   /// ssup . wrpalthk = 0.01; //  thickness of Al on mylar wrap (guess)            
                   ssup . grphthk = 0.16; //  support cone thickness            
                   /// ssup . grphthk = 0.16; //  support cone thickness            
                   ssup . cone1zmn = 52.23; //  Cone z min (parts 1,2,3,4 in increasing z)            
                   /// ssup . cone1zmn = 52.23; //  Cone z min (parts 1,2,3,4 in increasing z)            
                   ssup . rodlen = 110.8; //  Length of support rods            
                   /// ssup . rodlen = 110.8; //  Length of support rods            
                   ssup . roddist = 17.5; //  Distance of support rod od from beam axis             
                   /// ssup . roddist = 17.5; //  Distance of support rod od from beam axis             
                   ssup . rodid = 2.5; //  ID of Carbon support rods (approx)            
                   /// ssup . rodid = 2.5; //  ID of Carbon support rods (approx)            
                   ssup . rodod = 3.05; //  OD of Carbon support rods (approx)            
                   /// ssup . rodod = 3.05; //  OD of Carbon support rods (approx)            
                   ssup . con1idmn = 15.67; //  Minimum id of cone 1             
                   /// ssup . con1idmn = 15.67; //  Minimum id of cone 1             
                   ssup . con3idmn = 21.67; //  Minimum id of cone 3 (TBD)            
                   /// ssup . con3idmn = 21.67; //  Minimum id of cone 3 (TBD)            
                   ssup . con4idmn = 37.4; //  Minimum id of cone 4 (TBD)            
                   /// ssup . con4idmn = 37.4; //  Minimum id of cone 4 (TBD)            
                   ssup . con4idmx = 37.4; //  Maximum id of cone 4 (TBD)            
                   /// ssup . con4idmx = 37.4; //  Maximum id of cone 4 (TBD)            
                   ssup . cone3zmx = 150.0; //  Maximum z of cone 3 (TBD)            
                   /// ssup . cone3zmx = 150.0; //  Maximum z of cone 3 (TBD)            
                   ssup . cone4zmx = 229.36; //  Maximum z of cone 4 (TBD)            
                   /// ssup . cone4zmx = 229.36; //  Maximum z of cone 4 (TBD)            
                   ssup . brathk = .2; //  thickness of Al brackets             
                   /// ssup . brathk = .2; //  thickness of Al brackets             
                   ssup . erjthk = .1; //  (z) thickness of end ring joining brackets            
                   /// ssup . erjthk = .1; //  (z) thickness of end ring joining brackets            
                   ssup . erjwid = 2.07; //  (azimuthal) width of end ring joining brackets            
                   /// ssup . erjwid = 2.07; //  (azimuthal) width of end ring joining brackets            
                   ssup . erjlen = 5.19; //  (radial) length of end ring joining brackets            
                   /// ssup . erjlen = 5.19; //  (radial) length of end ring joining brackets            
                   ssup . erjzdis = 2.0; //  dist from ladder ends to ERJ (guess)            
                   /// ssup . erjzdis = 2.0; //  dist from ladder ends to ERJ (guess)            
                   ssup . erj1x = 0.31; //  ERJ screw 1 x position (radial)            
                   /// ssup . erj1x = 0.31; //  ERJ screw 1 x position (radial)            
                   ssup . erj2x = 1.15; //  ERJ screw 2 x position            
                   /// ssup . erj2x = 1.15; //  ERJ screw 2 x position            
                   ssup . erj2y = 0.72; //  ERJ screw 2 y position            
                   /// ssup . erj2y = 0.72; //  ERJ screw 2 y position            
                   ssup . erjrad = 10.80; //  distance of ERJ center from beam axis            
                   /// ssup . erjrad = 10.80; //  distance of ERJ center from beam axis            
                   ssup . erjdia = 0.17; //  ERJ screw diameter            
                   /// ssup . erjdia = 0.17; //  ERJ screw diameter            
                   //           
                   ssup.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup ssub_doc        
             ///@{           
                   ++ssub._index;           
                   ssub . version = 1; //  geometry version            
                   /// ssub . version = 1; //  geometry version            
                   ssub . kmountid = 31.34; //  id of beampipe support kinematic mount            
                   /// ssub . kmountid = 31.34; //  id of beampipe support kinematic mount            
                   ssub . kmountod = 38.96; //  od of beampipe support kinematic mount            
                   /// ssub . kmountod = 38.96; //  od of beampipe support kinematic mount            
                   ssub . kmntthk = 0.64; //  thickness of support kinematic mount            
                   /// ssub . kmntthk = 0.64; //  thickness of support kinematic mount            
                   ssub . kmcutod = 18.31; //  od of cutout in kinematic mount            
                   /// ssub . kmcutod = 18.31; //  od of cutout in kinematic mount            
                   ssub . kmcutid = 14; //  id of cutout in kinematic mount            
                   /// ssub . kmcutid = 14; //  id of cutout in kinematic mount            
                   ssub . kmcutoa = 38; //  opening angle of cutout            
                   /// ssub . kmcutoa = 38; //  opening angle of cutout            
                   ssub . kmcutoff = 26.58; //  offset of cutout center from axis            
                   /// ssub . kmcutoff = 26.58; //  offset of cutout center from axis            
                   ssub . sringid = 8.47; //  id of beampipe support ring             
                   /// ssub . sringid = 8.47; //  id of beampipe support ring             
                   ssub . sringod = 12.78; //  od of beampipe support ring            
                   /// ssub . sringod = 12.78; //  od of beampipe support ring            
                   ssub . sringthk = 0.64; //  thichkness of beampipe support ring            
                   /// ssub . sringthk = 0.64; //  thichkness of beampipe support ring            
                   ssub . srcutphi = 38; //  support ring cutout angle to z-axis            
                   /// ssub . srcutphi = 38; //  support ring cutout angle to z-axis            
                   ssub . srcutwid = 3.63; //  support ring cutout width            
                   /// ssub . srcutwid = 3.63; //  support ring cutout width            
                   ssub . srcutout = 5.08; //  support ring cutout depth            
                   /// ssub . srcutout = 5.08; //  support ring cutout depth            
                   ssub . srcutin = 3.5; //  support ring cutout start            
                   /// ssub . srcutin = 3.5; //  support ring cutout start            
                   ssub . srollid = 0.2; //  support roller Id            
                   /// ssub . srollid = 0.2; //  support roller Id            
                   ssub . srollod = 0.62; //  support roller Od            
                   /// ssub . srollod = 0.62; //  support roller Od            
                   ssub . srolllen = 2.54; //  support roller length            
                   /// ssub . srolllen = 2.54; //  support roller length            
                   ssub . swirelen = 5.08; //  support roller axis length            
                   /// ssub . swirelen = 5.08; //  support roller axis length            
                   ssub . mblkhgh = 0.97; //  mounting block height            
                   /// ssub . mblkhgh = 0.97; //  mounting block height            
                   ssub . mblkowid = 2.54; //  outer mounting block width            
                   /// ssub . mblkowid = 2.54; //  outer mounting block width            
                   ssub . mblkolen = 1.27; //  outer mounting block length            
                   /// ssub . mblkolen = 1.27; //  outer mounting block length            
                   ssub . mblkiwid = 3.175; //  inner mounting block width            
                   /// ssub . mblkiwid = 3.175; //  inner mounting block width            
                   ssub . mblkilen = 1.27; //  inner mounting block length            
                   /// ssub . mblkilen = 1.27; //  inner mounting block length            
                   ssub . mblkorad = 17.4; //  outer mounting block at radius            
                   /// ssub . mblkorad = 17.4; //  outer mounting block at radius            
                   ssub . mblkirad = 5.42; //  inner mounting block at radius            
                   /// ssub . mblkirad = 5.42; //  inner mounting block at radius            
                   ssub . mroddia = 0.32; //  mounting support rod diameter            
                   /// ssub . mroddia = 0.32; //  mounting support rod diameter            
                   //           
                   ssub.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup serg_doc        
             ///@{           
                   ++serg._index;           
                   serg . version = 1; //  geometry version            
                   /// serg . version = 1; //  geometry version            
                   serg . irngtrmx = 9.703; //  Inner end ring tube maximum radius             
                   /// serg . irngtrmx = 9.703; //  Inner end ring tube maximum radius             
                   serg . irngprmn = 7.671; //  Inner end ring polygon minimum radius            
                   /// serg . irngprmn = 7.671; //  Inner end ring polygon minimum radius            
                   serg . orngrmin = 11.900; //  Outer end ring minimum radius            
                   /// serg . orngrmin = 11.900; //  Outer end ring minimum radius            
                   serg . orngrmax = 13.805; //  Outer end ring maximum radius            
                   /// serg . orngrmax = 13.805; //  Outer end ring maximum radius            
                   serg . endrngth = 0.2; //  End ring thickness            
                   /// serg . endrngth = 0.2; //  End ring thickness            
                   serg . endrngzm = 23.01; //  minimum z for end rings            
                   /// serg . endrngzm = 23.01; //  minimum z for end rings            
                   //           
                   serg.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup swam_doc        
             ///@{           
                   ++swam._index;           
                   swam . version = 1; //  geometry version            
                   /// swam . version = 1; //  geometry version            
                   swam . zmin = 33.9; //  minimum z for positioning water manifold            
                   /// swam . zmin = 33.9; //  minimum z for positioning water manifold            
                   swam . len = 16.0; //  water manifold full length             
                   /// swam . len = 16.0; //  water manifold full length             
                   swam . rmin = 15.24; //  water manifold rmin (not including trans. brds)            
                   /// swam . rmin = 15.24; //  water manifold rmin (not including trans. brds)            
                   swam . rmax = 16.83; //  water manifold rmax (not including trans. brds)            
                   /// swam . rmax = 16.83; //  water manifold rmax (not including trans. brds)            
                   swam . tbrdthk = 0.1; //  transition board thickness            
                   /// swam . tbrdthk = 0.1; //  transition board thickness            
                   swam . wallthk = 0.1; //  water manifold wall thickness            
                   /// swam . wallthk = 0.1; //  water manifold wall thickness            
                   //           
                   swam.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup selc_doc        
             ///@{           
                   ++selc._index;           
                   selc . version = 1; //  geometry version            
                   /// selc . version = 1; //  geometry version            
                   selc . bethk = 0.0500; //  thickness of Berillium water channel walls            
                   /// selc . bethk = 0.0500; //  thickness of Berillium water channel walls            
                   selc . watthk = 0.0750; //  thickness of water channel            
                   /// selc . watthk = 0.0750; //  thickness of water channel            
                   selc . beothk = 0.0500; //  thickness of Berrillia (BeO) substra            
                   /// selc . beothk = 0.0500; //  thickness of Berrillia (BeO) substra            
                   selc . dyethk = 0.0340; //  to give .11% of a radiation length of Si             
                   /// selc . dyethk = 0.0340; //  to give .11% of a radiation length of Si             
                   selc . dyewid = 0.3; //  width of ic chips (2 covers 0.3 of area)            
                   /// selc . dyewid = 0.3; //  width of ic chips (2 covers 0.3 of area)            
                   selc . dyespc = 0.1; //  space ic chips            
                   /// selc . dyespc = 0.1; //  space ic chips            
                   selc . elcawid = 2.0; //  electronics carrier width            
                   /// selc . elcawid = 2.0; //  electronics carrier width            
                   selc . agpdthk = 0.0030; //  thickness of Ag-Pd conductor            
                   /// selc . agpdthk = 0.0030; //  thickness of Ag-Pd conductor            
                   selc . glassthk = 0.0150; //  thickness of glass insulator            
                   /// selc . glassthk = 0.0150; //  thickness of glass insulator            
                   selc . cabthk = 0.0033; //  Cu for cables of .23% rad len (weighted average)            
                   /// selc . cabthk = 0.0033; //  Cu for cables of .23% rad len (weighted average)            
                   selc . cabwid = 0.6; //  cable width             
                   /// selc . cabwid = 0.6; //  cable width             
                   //           
                   selc.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup svtl_doc        
             ///@{           
                   ++svtl._index;           
                   svtl . layer = 1; //  layer number            
                   /// svtl . layer = 1; //  layer number            
                   svtl . radius = radii(1)+rad_offset; //  layer radius (center of wafer position)            
                   /// svtl . radius = radii(1)+rad_offset; //  layer radius (center of wafer position)            
                   svtl . nladder = 4; //  number of ladder            
                   /// svtl . nladder = 4; //  number of ladder            
                   svtl . nwafer = 4; //  number of wafers            
                   /// svtl . nwafer = 4; //  number of wafers            
                   svtl . bareedge = 1.0; //  the strip of bare Be which makes the PCB shorter            
                   /// svtl . bareedge = 1.0; //  the strip of bare Be which makes the PCB shorter            
                   svtl . pcblen = 14.9; //  PCB Length            
                   /// svtl . pcblen = 14.9; //  PCB Length            
                   svtl . pcbwidth = 6.3; //  PCB Width            
                   /// svtl . pcbwidth = 6.3; //  PCB Width            
                   svtl . pcbthk = 0.1; //  PCB Thickness -- should be 0.09, but we add extra for copper            
                   /// svtl . pcbthk = 0.1; //  PCB Thickness -- should be 0.09, but we add extra for copper            
                   svtl . pcbgap = 0.2; //  Gap between the PCB and the Si Wafer            
                   /// svtl . pcbgap = 0.2; //  Gap between the PCB and the Si Wafer            
                   //           
                   svtl.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup svtl_doc        
             ///@{           
                   ++svtl._index;           
                   svtl . layer = 2; //  layer number            
                   /// svtl . layer = 2; //  layer number            
                   svtl . radius = radii(2)+rad_offset; //  layer radius            
                   /// svtl . radius = radii(2)+rad_offset; //  layer radius            
                   svtl . pcblen = 14.9; //  PCB Length            
                   /// svtl . pcblen = 14.9; //  PCB Length            
                   //           
                   svtl.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup svtl_doc        
             ///@{           
                   ++svtl._index;           
                   svtl . layer = 3; //  layer number            
                   /// svtl . layer = 3; //  layer number            
                   svtl . radius = radii(3)+rad_offset; //  layer radius            
                   /// svtl . radius = radii(3)+rad_offset; //  layer radius            
                   svtl . nladder = 6; //  number of ladder            
                   /// svtl . nladder = 6; //  number of ladder            
                   svtl . nwafer = 6; //  number of wafers            
                   /// svtl . nwafer = 6; //  number of wafers            
                   svtl . pcblen = 7.5; //  PCB Length            
                   /// svtl . pcblen = 7.5; //  PCB Length            
                   //           
                   svtl.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup svtl_doc        
             ///@{           
                   ++svtl._index;           
                   svtl . layer = 4; //  layer number            
                   /// svtl . layer = 4; //  layer number            
                   svtl . radius = radii(4)+rad_offset; //  layer radius            
                   /// svtl . radius = radii(4)+rad_offset; //  layer radius            
                   svtl . pcblen = 7.5; //  PCB Length            
                   /// svtl . pcblen = 7.5; //  PCB Length            
                   //           
                   svtl.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup svtl_doc        
             ///@{           
                   ++svtl._index;           
                   svtl . layer = 5; //  layer number            
                   /// svtl . layer = 5; //  layer number            
                   svtl . radius = radii(5)+rad_offset; //  layer radius            
                   /// svtl . radius = radii(5)+rad_offset; //  layer radius            
                   svtl . nladder = 8; //  number of ladder            
                   /// svtl . nladder = 8; //  number of ladder            
                   svtl . nwafer = 7; //  number of wafers            
                   /// svtl . nwafer = 7; //  number of wafers            
                   svtl . pcblen = 4.4; //  PCB Length            
                   /// svtl . pcblen = 4.4; //  PCB Length            
                   //           
                   svtl.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup svtl_doc        
             ///@{           
                   ++svtl._index;           
                   svtl . layer = 6; //  layer number            
                   /// svtl . layer = 6; //  layer number            
                   svtl . radius = radii(6)+rad_offset; //  layer radius            
                   /// svtl . radius = radii(6)+rad_offset; //  layer radius            
                   svtl . pcblen = 4.4; //  PCB Length            
                   /// svtl . pcblen = 4.4; //  PCB Length            
                   //           
                   svtl.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup ssld_doc        
             ///@{           
                   ++ssld._index;           
                   ssld . version = 1; //  geometry version            
                   /// ssld . version = 1; //  geometry version            
                   ssld . sinrinn = 5; //  inner shield cylinder, inner radius            
                   /// ssld . sinrinn = 5; //  inner shield cylinder, inner radius            
                   ssld . sinrout = 5.008; //  inner shield cylinder, outer radius            
                   /// ssld . sinrout = 5.008; //  inner shield cylinder, outer radius            
                   ssld . sinlen = 53.5; //  inner shield cylinder, half length            
                   /// ssld . sinlen = 53.5; //  inner shield cylinder, half length            
                   ssld . sseprinn = 22; //  separation shield cylinder, inner radius            
                   /// ssld . sseprinn = 22; //  separation shield cylinder, inner radius            
                   ssld . sseprout = 22.018; //  separation shield cylinder, outer radius            
                   /// ssld . sseprout = 22.018; //  separation shield cylinder, outer radius            
                   ssld . sseplen = 55.4; //  separation shield cylinder, half length            
                   /// ssld . sseplen = 55.4; //  separation shield cylinder, half length            
                   ssld . soutrinn = 29.5; //  outer shield cylinder, inner radius            
                   /// ssld . soutrinn = 29.5; //  outer shield cylinder, inner radius            
                   ssld . soutrout = 29.52; //  outer shield cylinder, outer radius            
                   /// ssld . soutrout = 29.52; //  outer shield cylinder, outer radius            
                   ssld . soutlen = 65.4; //  outer shield cylinder, half length            
                   /// ssld . soutlen = 65.4; //  outer shield cylinder, half length            
                   ssld . almeshid = 9.7; //  Aluminum shield mesh inner diameter            
                   /// ssld . almeshid = 9.7; //  Aluminum shield mesh inner diameter            
                   ssld . almeshod = 44; //  Aluminum shield mesh outer diameter            
                   /// ssld . almeshod = 44; //  Aluminum shield mesh outer diameter            
                   ssld . almshthk = 0.03; //  Aluminum shield mesh effective thickness            
                   /// ssld . almshthk = 0.03; //  Aluminum shield mesh effective thickness            
                   ssld . almshpos = 53.5; //  Aluminum shield mesh z position            
                   /// ssld . almshpos = 53.5; //  Aluminum shield mesh z position            
                   //           
                   ssld.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup ssld_doc        
             ///@{           
                   ++ssld._index;           
                   ssld . version = 2; //  geometry version            
                   /// ssld . version = 2; //  geometry version            
                   ssld . sinrinn = 5.7; //  inner shield cylinder, inner radius            
                   /// ssld . sinrinn = 5.7; //  inner shield cylinder, inner radius            
                   ssld . sinrout = 5.708; //  inner shield cylinder, outer radius            
                   /// ssld . sinrout = 5.708; //  inner shield cylinder, outer radius            
                   //           
                   ssld.fill();           
             ///@}        
             //        
             /// Loop on i from 1 to 4 step=1        
             for ( i=1; (1>0)? (i<=4):(i>=4); i+=1 )        
             {           
                   rad_cones_in(i) = 8.5+2.60*(i-1);           
                   rad_cones_out(i)=15.0+0.85*(i-1);           
             }        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup scbp_doc        
             ///@{           
                   ++scbp._index;           
                   scbp . layer = 1; //  Layer            
                   /// scbp . layer = 1; //  Layer            
                   scbp . len = 1.85; //  Length            
                   /// scbp . len = 1.85; //  Length            
                   scbp . rmin1 = rad_cones_in(1); //  Min radius closer to wafers            
                   /// scbp . rmin1 = rad_cones_in(1); //  Min radius closer to wafers            
                   scbp . rmin2 = rad_cones_out(1); //  Min radius further from wafers            
                   /// scbp . rmin2 = rad_cones_out(1); //  Min radius further from wafers            
                   scbp . vol = 7.24+3.21; //  Volume of copper, LV+HV cables            
                   /// scbp . vol = 7.24+3.21; //  Volume of copper, LV+HV cables            
                   //           
                   scbp.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup scbp_doc        
             ///@{           
                   ++scbp._index;           
                   scbp . layer = 2; //  Layer            
                   /// scbp . layer = 2; //  Layer            
                   scbp . rmin1 = rad_cones_in(2); //  Min radius closer to wafers            
                   /// scbp . rmin1 = rad_cones_in(2); //  Min radius closer to wafers            
                   scbp . rmin2 = rad_cones_out(2); //  Min radius further from wafers            
                   /// scbp . rmin2 = rad_cones_out(2); //  Min radius further from wafers            
                   scbp . vol = 15.54+5.7; //  Volume of copper, LV+HV cables            
                   /// scbp . vol = 15.54+5.7; //  Volume of copper, LV+HV cables            
                   //           
                   scbp.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup scbp_doc        
             ///@{           
                   ++scbp._index;           
                   scbp . layer = 3; //  Layer            
                   /// scbp . layer = 3; //  Layer            
                   scbp . rmin1 = rad_cones_in(3); //  Min radius closer to wafers            
                   /// scbp . rmin1 = rad_cones_in(3); //  Min radius closer to wafers            
                   scbp . rmin2 = rad_cones_out(3); //  Min radius further from wafers            
                   /// scbp . rmin2 = rad_cones_out(3); //  Min radius further from wafers            
                   scbp . vol = 4.05+2.02+3.67+1.69; //  Volume of copper, LV+HV cables -- 3+4 layers coalesce            
                   /// scbp . vol = 4.05+2.02+3.67+1.69; //  Volume of copper, LV+HV cables -- 3+4 layers coalesce            
                   //           
                   scbp.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup scbp_doc        
             ///@{           
                   ++scbp._index;           
                   scbp . layer = 4; //  Layer (former 5th)            
                   /// scbp . layer = 4; //  Layer (former 5th)            
                   scbp . rmin1 = rad_cones_in(4); //  Min radius closer to wafers            
                   /// scbp . rmin1 = rad_cones_in(4); //  Min radius closer to wafers            
                   scbp . rmin2 = rad_cones_out(4); //  Min radius further from wafers            
                   /// scbp . rmin2 = rad_cones_out(4); //  Min radius further from wafers            
                   scbp . vol = 6.95+2.43; //  Volume of copper, LV+HV cables            
                   /// scbp . vol = 6.95+2.43; //  Volume of copper, LV+HV cables            
                   //           
                   scbp.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfep_doc        
             ///@{           
                   ++sfep._index;           
                   sfep . layer = 1; //  Layer            
                   /// sfep . layer = 1; //  Layer            
                   sfep . len = 1.85; //  Length            
                   /// sfep . len = 1.85; //  Length            
                   sfep . rmin1 = 0.5*(rad_cones_in(1) +rad_cones_in(2)); //  Min radius closer to wafers            
                   /// sfep . rmin1 = 0.5*(rad_cones_in(1) +rad_cones_in(2)); //  Min radius closer to wafers            
                   sfep . rmin2 = 0.5*(rad_cones_out(1)+rad_cones_out(2)); //  Min radius further from wafers            
                   /// sfep . rmin2 = 0.5*(rad_cones_out(1)+rad_cones_out(2)); //  Min radius further from wafers            
                   sfep . vol = 16.0; //  Volume of water            
                   /// sfep . vol = 16.0; //  Volume of water            
                   sfep . volplast = 38.4; //  Volume of plastic            
                   /// sfep . volplast = 38.4; //  Volume of plastic            
                   //           
                   sfep.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfep_doc        
             ///@{           
                   ++sfep._index;           
                   sfep . layer = 2; //  Layer            
                   /// sfep . layer = 2; //  Layer            
                   sfep . rmin1 = 0.5*(rad_cones_in(2) +rad_cones_in(3)); //  Min radius closer to wafers            
                   /// sfep . rmin1 = 0.5*(rad_cones_in(2) +rad_cones_in(3)); //  Min radius closer to wafers            
                   sfep . rmin2 = 0.5*(rad_cones_out(2)+rad_cones_out(3)); //  Min radius further from wafers            
                   /// sfep . rmin2 = 0.5*(rad_cones_out(2)+rad_cones_out(3)); //  Min radius further from wafers            
                   sfep . vol = 24.0; //  Volume of water            
                   /// sfep . vol = 24.0; //  Volume of water            
                   sfep . volplast = 57.6; //  Volume of plastic            
                   /// sfep . volplast = 57.6; //  Volume of plastic            
                   //           
                   sfep.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfep_doc        
             ///@{           
                   ++sfep._index;           
                   sfep . layer = 3; //  Layer            
                   /// sfep . layer = 3; //  Layer            
                   sfep . rmin1 = 0.5*(rad_cones_in(3) +rad_cones_in(4)); //  Min radius closer to wafers            
                   /// sfep . rmin1 = 0.5*(rad_cones_in(3) +rad_cones_in(4)); //  Min radius closer to wafers            
                   sfep . rmin2 = 0.5*(rad_cones_out(3)+rad_cones_out(4)); //  Min radius further from wafers            
                   /// sfep . rmin2 = 0.5*(rad_cones_out(3)+rad_cones_out(4)); //  Min radius further from wafers            
                   sfep . vol = 32; //  Volume of water            
                   /// sfep . vol = 32; //  Volume of water            
                   sfep . volplast = 76.8; //  Volume of plastic            
                   /// sfep . volplast = 76.8; //  Volume of plastic            
                   //           
                   sfep.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup swcx_doc        
             ///@{           
                   ++swcx._index;           
                   swcx . layer = 1; //  version            
                   /// swcx . layer = 1; //  version            
                   swcx . length = 2.8; //  of the ring in the Z direction            
                   /// swcx . length = 2.8; //  of the ring in the Z direction            
                   swcx . dr = 0.72; //  thickness of the mother layer            
                   /// swcx . dr = 0.72; //  thickness of the mother layer            
                   swcx . rad = 0.2; //  inner plastic tube radius            
                   /// swcx . rad = 0.2; //  inner plastic tube radius            
                   swcx . offset = -2.0; //  from the edge of the ladder support, inward            
                   /// swcx . offset = -2.0; //  from the edge of the ladder support, inward            
                   swcx . roffset = 1.0; //  Radial offset            
                   /// swcx . roffset = 1.0; //  Radial offset            
                   swcx . wall = 0.16; //  thickness of the plastic pipe wall            
                   /// swcx . wall = 0.16; //  thickness of the plastic pipe wall            
                   //           
                   swcx.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup soup_doc        
             ///@{           
                   ++soup._index;           
                   soup . version = 1; //  Version            
                   /// soup . version = 1; //  Version            
                   soup . length = 82.5; //  Length            
                   /// soup . length = 82.5; //  Length            
                   soup . rout = 19.41; //  Outer radius of the shield            
                   /// soup . rout = 19.41; //  Outer radius of the shield            
                   soup . dr = 0.711; //  Diameter of the tubes constituting the cage (also dR of the mother)            
                   /// soup . dr = 0.711; //  Diameter of the tubes constituting the cage (also dR of the mother)            
                   soup . phi1 = 0.0; //  Starting angle of the mother            
                   /// soup . phi1 = 0.0; //  Starting angle of the mother            
                   soup . phi2 = 70.0; //  Finishing angle of the mother            
                   /// soup . phi2 = 70.0; //  Finishing angle of the mother            
                   soup . diamout = 0.711; //  Outer diam of the carbon tube            
                   /// soup . diamout = 0.711; //  Outer diam of the carbon tube            
                   soup . diamin = 0.620; //  Inner diam of the carbon tube            
                   /// soup . diamin = 0.620; //  Inner diam of the carbon tube            
                   //           
                   soup.fill();           
             ///@}        
             //        
             /// USE svtg _index=1;        
             svtg.Use();        
             /// USE swca _index=1;        
             swca.Use();        
             /// USE selc _index=1;        
             selc.Use();        
             /// USE ssup version=svtg.conever ;        
             ssup.Use("version",(Float_t)svtg.conever );        
             /// USE ssub _index=1;        
             ssub.Use();        
             /// USE serg _index=1;        
             serg.Use();        
             /// USE swam _index=1;        
             swam.Use();        
             /// USE selc _index=1;        
             selc.Use();        
             /// USE ssld version=svtg.supportver ;        
             ssld.Use("version",(Float_t)svtg.supportver );        
             /// USE scbp _index=1;        
             scbp.Use();        
             /// USE swcx _index=1;        
             swcx.Use();        
             /// USE soup _index=1;        
             soup.Use();        
             if ( svtg.supportver==2 )        
             {           
                   svtg.rsizemin = 1.4;           
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
             /// Component C5	a=12	z=6	w=10000*5        
             /// Component H4	a=1	z=1	w=10000*4        
             /// Component O2	a=16	z=8	w=10000*2        
             /// Component Al	a=27	z=13	w=10000*0.2302        
             /// Mixture ALKAP dens=1.432        
             {  AgMaterial &mix = AgMaterial::Get("Alkap");           
                   mix.Component("C5",12,6,10000*5);           
                   mix.Component("H4",1,1,10000*4);           
                   mix.Component("O2",16,8,10000*2);           
                   mix.Component("Al",27,13,10000*0.2302);           
                   mix.par("dens")=1.432;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
             /// Component C5	a=12	z=6	w=10000*5        
             /// Component H4	a=1	z=1	w=10000*4        
             /// Component O2	a=16	z=8	w=10000*2        
             /// Component Al	a=27	z=13	w=986        
             /// Mixture SSDALMY dens=1.40845        
             {  AgMaterial &mix = AgMaterial::Get("Ssdalmy");           
                   mix.Component("C5",12,6,10000*5);           
                   mix.Component("H4",1,1,10000*4);           
                   mix.Component("O2",16,8,10000*2);           
                   mix.Component("Al",27,13,986);           
                   mix.par("dens")=1.40845;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
             if ( swam.len>0 )        
             {           
                   /// Component H2	a=1	z=1	w=2           
                   /// Component O	a=16	z=8	w=1           
                   /// Mixture Water dens=1.0           
                   {  AgMaterial &mix = AgMaterial::Get("Water");              
                         mix.Component("H2",1,1,2);              
                         mix.Component("O",16,8,1);              
                         mix.par("dens")=1.0;              
                         mix.lock();              
                         _material = mix;              
                         _material.lock();              
                   }           
             }        
             else        
             {           
                   /// Mixture Water dens=0.0009           
                   {  AgMaterial &mix = AgMaterial::Get("Water");              
                         mix.par("dens")=0.0009;              
                         mix.lock();              
                         _material = mix;              
                         _material.lock();              
                   }           
             }        
             if ( svtg.ifmany>0 )        
             {           
                   _create = AgCreate("SVTT");           
                   {              
                         AgShape myshape; // undefined shape              
                         ///Create SVTT              
                         Create("SVTT");               
                   }           
                   { AgPlacement place = AgPlacement("SVTT","CAVE");              
                         /// Add daughter volume SVTT to mother CAVE              
                         place.par("only")=AgPlacement::kMany;              
                         /// Overlap: agplacement::kmany              
                         _stacker -> Position( AgBlock::Find("SVTT"), place );              
                   } // end placement of SVTT           
             }        
             else        
             {           
                   _create = AgCreate("SVTT");           
                   {              
                         AgShape myshape; // undefined shape              
                         ///Create SVTT              
                         Create("SVTT");               
                   }           
                   { AgPlacement place = AgPlacement("SVTT","CAVE");              
                         /// Add daughter volume SVTT to mother CAVE              
                         _stacker -> Position( AgBlock::Find("SVTT"), place );              
                   } // end placement of SVTT           
             }        
       }; // SvttGeo4     
 }; // namespace SvttGeo4  
 