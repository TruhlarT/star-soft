#include "SisdGeo6.h"  
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
 namespace SISDGEO6 // $NMSPC  
 {     
       //     
       // ---------------------------------------------------------------------------------------------------     
          //  -----------------------------------------------------     
          /// @defgroup ssdp_doc     
          /// \class Ssdp_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Int_t config;     
          ///Int_t placement;     
          ///Int_t _index;     
          //     
          Ssdp_t ssdp;     
          //     
          ///@addtogroup SisdGeo6_vars     
          ///@{        
                Int_t configa,configb;        
                //        
                /// Int_t configa,configb        
          ///@}     
          //  -----------------------------------------------------     
          /// @defgroup sfjp_doc     
          /// \class Sfjp_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Int_t version;     
          ///Float_t alphaz;     
          ///Float_t alphazh;     
          ///Float_t ssst_rmin;     
          ///Float_t ssst_rmax;     
          ///Float_t ssst_width;     
          ///Float_t ssst_pz;     
          ///Float_t ssss_rmin;     
          ///Float_t ssss_width;     
          ///Float_t ssrs_rmin;     
          ///Float_t sslb_dx;     
          ///Float_t sslb_px;     
          ///Float_t sslb_dy;     
          ///Float_t sslb_dz;     
          ///Float_t ssbq_dx;     
          ///Float_t ssbq_dy;     
          ///Float_t ssbq_dz;     
          ///Float_t sscr_tha;     
          ///Float_t sscr_thd;     
          ///Float_t sscr_wd;     
          ///Float_t sscr_hl;     
          ///Float_t sscr_vl;     
          ///Float_t sslt_px;     
          ///Float_t sslt_rmax;     
          ///Float_t sslt_dz;     
          ///Float_t scmp_dx;     
          ///Float_t scmp_dy;     
          ///Float_t scmp_dz;     
          ///Float_t scmp_px;     
          ///Float_t scvm_dz;     
          ///Float_t scvm_dx;     
          ///Float_t scvm_px;     
          ///Float_t scvm_dy;     
          ///Float_t scvm_pz;     
          ///Float_t scvb_dy;     
          ///Float_t scvs_dx;     
          ///Float_t scvs_dy;     
          ///Float_t scvs_px;     
          ///Float_t scvs_py;     
          ///Float_t sfco_dx;     
          ///Float_t sfco_dy;     
          ///Float_t sfco_dz;     
          ///Float_t sfco_px;     
          ///Float_t sfco_py;     
          ///Float_t sfcm_dx;     
          ///Float_t sfcs_dz;     
          ///Float_t sfkf_dy;     
          ///Float_t sfkf_dz;     
          ///Float_t sfkf_dx;     
          ///Float_t sfkf_px;     
          ///Float_t sfkf_py;     
          ///Float_t sfks_dx;     
          ///Float_t sfks_px;     
          ///Float_t sfks_py;     
          ///Float_t sfpr_py;     
          ///Float_t sfpb_py;     
          ///Float_t sfpb_py2;     
          ///Float_t sfcb_dx;     
          ///Float_t ssbs_dy;     
          ///Float_t ssbs_dx;     
          ///Float_t ssbb_dx;     
          ///Float_t ssbb_dz;     
          ///Float_t flex_di;     
          ///Float_t sfpb_dx;     
          ///Float_t sfpb_dy;     
          ///Float_t sfpbdz;     
          ///Float_t sapp_dxe;     
          ///Float_t sapp_dxz;     
          ///Float_t sapp_dy;     
          ///Float_t sapp_dz;     
          ///Float_t sapp_py1;     
          ///Float_t sapp_py2;     
          ///Float_t sapp_py3;     
          ///Float_t sfam_dxe;     
          ///Float_t sfam_dxz;     
          ///Float_t sfam_dy;     
          ///Float_t sfam_dz;     
          ///Float_t sfam_dzs;     
          ///Float_t sfla_dx;     
          ///Float_t sfla_dy;     
          ///Float_t sfla_dz;     
          ///Float_t sflb_dz;     
          ///Float_t sflc_dz;     
          ///Float_t sfeb_dx;     
          ///Float_t sfeb_dz;     
          ///Float_t sfes_dx;     
          ///Float_t sffk_dxe;     
          ///Float_t sffk_dy;     
          ///Float_t sffx_dye;     
          ///Float_t sffk_dz;     
          ///Float_t sffl_dx;     
          ///Float_t sffk_dxz;     
          ///Float_t sffk_px;     
          ///Float_t sffk_py1;     
          ///Float_t sffk_py2;     
          ///Float_t sfkl_px;     
          ///Float_t sfkk_dy;     
          ///Float_t sflu_dz;     
          ///Float_t sflu_h1;     
          ///Float_t sflu_bl1;     
          ///Float_t sfra_dx;     
          ///Float_t sfra_dy;     
          ///Float_t sfra_py;     
          ///Float_t sfra_dz;     
          ///Float_t sfra_pz;     
          ///Float_t sfsw_dy;     
          ///Float_t sfsw_dz;     
          ///Float_t sfrs_dx;     
          ///Float_t sfrs_dy;     
          ///Float_t sfrs_px;     
          ///Float_t sfrs_py;     
          ///Float_t sfsm_ll;     
          ///Float_t sffx_dx;     
          ///Float_t sffx_dyz;     
          ///Float_t sfpi_rmin;     
          ///Float_t sfpi_rmax;     
          ///Float_t sfpi_px;     
          ///Float_t sfpi_py1;     
          ///Float_t sfpi_py2;     
          ///Float_t sfpi_pz;     
          ///Float_t sfpj_dx1;     
          ///Float_t sfpj_dx2;     
          ///Float_t sfpj_dy;     
          ///Float_t sfpj_dz;     
          ///Float_t sfaa_dx;     
          ///Float_t sfaa_dy;     
          ///Float_t sfaa_dz;     
          ///Float_t sfaa_px1;     
          ///Float_t sfaa_px2;     
          ///Float_t sfaa_px3;     
          ///Float_t sfaa_pz1;     
          ///Float_t sfaa_pz2;     
          ///Float_t sfaa_pz3;     
          ///Float_t sfsl_dx;     
          ///Float_t sfsl_dy;     
          ///Float_t sfsl_dz;     
          ///Float_t sfsd_dx;     
          ///Float_t sfsd_dy;     
          ///Float_t sfsd_dz;     
          ///Float_t sfla_px;     
          ///Float_t sfla_py;     
          ///Float_t sflc_px;     
          ///Float_t sflc_py;     
          ///Float_t sfes_px;     
          ///Float_t sfes_py;     
          ///Float_t sfes_pz;     
          ///Float_t sfeb_px;     
          ///Float_t sfeb_py;     
          ///Int_t _index;     
          //     
          Sfjp_t sfjp;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup sfpb_doc     
          /// \class Sfpb_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t hhight;     
          ///Float_t khight;     
          ///Float_t hbase;     
          ///Float_t kbase;     
          ///Float_t fsize;     
          ///Float_t zcoor;     
          ///Int_t _index;     
          //     
          Sfpb_t sfpb;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup sfpa_doc     
          /// \class Sfpa_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Int_t version;     
          ///Float_t rmin;     
          ///Float_t rmax;     
          ///Float_t len;     
          ///Float_t soutrinn;     
          ///Float_t soutrout;     
          ///Float_t soutlen;     
          ///Float_t rad;     
          ///Float_t nssd;     
          ///Float_t dmwid;     
          ///Float_t dmthk;     
          ///Float_t dmlen;     
          ///Float_t smwid;     
          ///Float_t smthk;     
          ///Float_t smlen;     
          ///Float_t sslen;     
          ///Float_t wplen;     
          ///Float_t sdlen;     
          ///Float_t tilt;     
          ///Float_t cprad;     
          ///Float_t cpral;     
          ///Float_t cfrad;     
          ///Float_t gpthk;     
          ///Array_t<Int_t> laddermap;     
          ///Array_t<Float_t> ladderangle;     
          ///Array_t<Float_t> laddertilt;     
          ///Array_t<Float_t> ladderradius;     
          ///Int_t _index;     
          //     
          Sfpa_t sfpa;     
          //     
          ///@addtogroup SisdGeo6_vars     
          ///@{        
                Int_t ilad,iwaf,jwaf,nc;        
                //        
                /// Int_t ilad,iwaf,jwaf,nc        
          ///@}     
          ///@addtogroup SisdGeo6_vars     
          ///@{        
                Float_t wafpcklen,dthk,radtilt,ang;        
                //        
                /// Float_t wafpcklen,dthk,radtilt,ang        
          ///@}     
          ///@addtogroup SisdGeo6_vars     
          ///@{        
                Float_t essai,hight,lng,leng,yoffset;        
                //        
                /// Float_t essai,hight,lng,leng,yoffset        
          ///@}     
       SisdGeo6::SisdGeo6()     
         : AgModule("SisdGeo6","  is the Silicon Strip Detector with TUP modifications ")     
       {        
       }     
          // ---------------------------------------------------------------------------------------------------     
          void SFMO::Block( AgCreate create )     
          {         
                ///@addtogroup SFMO_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFMO");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=sfpa.rmin;              
                            shape.par("rmax")=sfpa.rmax;              
                            shape.par("dz")=sfpa.len/2;              
                            /// Shape Tube rmin=sfpa.rmin rmax=sfpa.rmax dz=sfpa.len/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFMO;              
                            _stacker -> Build(this);              
                      }           
                      dthk = sfpa.smthk + sfpa.gpthk;           
                      if ( configb>=7 )           
                      {              
                            _create = AgCreate("SOSK");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SOSK                 
                                  Create("SOSK");                  
                            }              
                            { AgPlacement place = AgPlacement("SOSK","SFMO");                 
                                  /// Add daughter volume SOSK to mother SFMO                 
                                  _stacker -> Position( AgBlock::Find("SOSK"), place );                 
                            } // end placement of SOSK              
                      }           
                      _create = AgCreate("SFLM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFLM              
                            Create("SFLM");               
                      }           
                      /// Loop on ilad from 1 to 20 step=1           
                      for ( ilad=1; (1>0)? (ilad<=20):(ilad>=20); ilad+=1 )           
                      {              
                            if ( sfpa.laddermap(ilad)>0 )              
                            {                 
                                  ang     = (sfpa.ladderangle(ilad)*pi)/180.0;                 
                                  radtilt = (sfpa.laddertilt(ilad) *pi)/180.0;                 
                                  if ( ilad==1 )                 
                                  {                    
                                        nc=1;                    
                                  }                 
                                  else                 
                                  {                    
                                        nc=20-ilad+2;                    
                                  }                 
                                  { AgPlacement place = AgPlacement("SFLM","SFMO");                    
                                        /// Add daughter volume SFLM to mother SFMO                    
                                        place.TranslateX((sfpa.ladderradius(ilad)*cos(ang)+(dthk*cos(ang+radtilt))/2.0));                    
                                        /// Translate x = (sfpa.ladderradius(ilad)*cos(ang)+(dthk*cos(ang+radtilt))/2.0)                    
                                        place.TranslateY((sfpa.ladderradius(ilad)*sin(ang)+(dthk*sin(ang+radtilt))/2.0));                    
                                        /// Translate y = (sfpa.ladderradius(ilad)*sin(ang)+(dthk*sin(ang+radtilt))/2.0)                    
                                        place.TranslateZ(0);                    
                                        /// Translate z = 0                    
                                        place.par("only")=AgPlacement::kMany;                    
                                        /// Overlap: agplacement::kmany                    
                                        place.par("ncopy")=nc;                    
                                        /// Ncopy: nc                    
                                        place.AlphaZ(sfpa.ladderangle(ilad)-90.0+sfpa.laddertilt(ilad));                    
                                        /// Rotate: AlphaZ = sfpa.ladderangle(ilad)-90.0+sfpa.laddertilt(ilad)                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLM"), place );                    
                                  } // end placement of SFLM                 
                            }              
                      }           
                      _create = AgCreate("SSST");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SSST              
                            Create("SSST");               
                      }           
                      { AgPlacement place = AgPlacement("SSST","SFMO");              
                            /// Add daughter volume SSST to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssst_width/2.-sfjp.ssst_pz);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssst_width/2.-sfjp.ssst_pz              
                            _stacker -> Position( AgBlock::Find("SSST"), place );              
                      } // end placement of SSST           
                      { AgPlacement place = AgPlacement("SSST","SFMO");              
                            /// Add daughter volume SSST to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssst_width/2.+sfjp.ssst_pz);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssst_width/2.+sfjp.ssst_pz              
                            _stacker -> Position( AgBlock::Find("SSST"), place );              
                      } // end placement of SSST           
                      { AgPlacement place = AgPlacement("SSST","SFMO");              
                            /// Add daughter volume SSST to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssst_width/2.-sfjp.ssst_pz);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssst_width/2.-sfjp.ssst_pz              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SSST"), place );              
                      } // end placement of SSST           
                      { AgPlacement place = AgPlacement("SSST","SFMO");              
                            /// Add daughter volume SSST to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssst_width/2.+sfjp.ssst_pz);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssst_width/2.+sfjp.ssst_pz              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SSST"), place );              
                      } // end placement of SSST           
                      _create = AgCreate("SSSS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SSSS              
                            Create("SSSS");               
                      }           
                      { AgPlacement place = AgPlacement("SSSS","SFMO");              
                            /// Add daughter volume SSSS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width/2.-sfjp.ssst_pz);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width/2.-sfjp.ssst_pz              
                            _stacker -> Position( AgBlock::Find("SSSS"), place );              
                      } // end placement of SSSS           
                      { AgPlacement place = AgPlacement("SSSS","SFMO");              
                            /// Add daughter volume SSSS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width/2.+sfjp.ssst_pz);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width/2.+sfjp.ssst_pz              
                            _stacker -> Position( AgBlock::Find("SSSS"), place );              
                      } // end placement of SSSS           
                      { AgPlacement place = AgPlacement("SSSS","SFMO");              
                            /// Add daughter volume SSSS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width/2.-sfjp.ssst_pz);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width/2.-sfjp.ssst_pz              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SSSS"), place );              
                      } // end placement of SSSS           
                      { AgPlacement place = AgPlacement("SSSS","SFMO");              
                            /// Add daughter volume SSSS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width/2.+sfjp.ssst_pz);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width/2.+sfjp.ssst_pz              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SSSS"), place );              
                      } // end placement of SSSS           
                      _create = AgCreate("SSRT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SSRT              
                            Create("SSRT");               
                      }           
                      { AgPlacement place = AgPlacement("SSRT","SFMO");              
                            /// Add daughter volume SSRT to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssst_width/2.-sfjp.ssst_pz);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssst_width/2.-sfjp.ssst_pz              
                            _stacker -> Position( AgBlock::Find("SSRT"), place );              
                      } // end placement of SSRT           
                      { AgPlacement place = AgPlacement("SSRT","SFMO");              
                            /// Add daughter volume SSRT to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssst_width/2.+sfjp.ssst_pz);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssst_width/2.+sfjp.ssst_pz              
                            _stacker -> Position( AgBlock::Find("SSRT"), place );              
                      } // end placement of SSRT           
                      { AgPlacement place = AgPlacement("SSRT","SFMO");              
                            /// Add daughter volume SSRT to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssst_width/2.-sfjp.ssst_pz);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssst_width/2.-sfjp.ssst_pz              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SSRT"), place );              
                      } // end placement of SSRT           
                      { AgPlacement place = AgPlacement("SSRT","SFMO");              
                            /// Add daughter volume SSRT to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssst_width/2.+sfjp.ssst_pz);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssst_width/2.+sfjp.ssst_pz              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SSRT"), place );              
                      } // end placement of SSRT           
                      _create = AgCreate("SSRS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SSRS              
                            Create("SSRS");               
                      }           
                      { AgPlacement place = AgPlacement("SSRS","SFMO");              
                            /// Add daughter volume SSRS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width/2.-sfjp.ssst_pz);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width/2.-sfjp.ssst_pz              
                            _stacker -> Position( AgBlock::Find("SSRS"), place );              
                      } // end placement of SSRS           
                      { AgPlacement place = AgPlacement("SSRS","SFMO");              
                            /// Add daughter volume SSRS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width/2.+sfjp.ssst_pz);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width/2.+sfjp.ssst_pz              
                            _stacker -> Position( AgBlock::Find("SSRS"), place );              
                      } // end placement of SSRS           
                      { AgPlacement place = AgPlacement("SSRS","SFMO");              
                            /// Add daughter volume SSRS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width/2.-sfjp.ssst_pz);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width/2.-sfjp.ssst_pz              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SSRS"), place );              
                      } // end placement of SSRS           
                      { AgPlacement place = AgPlacement("SSRS","SFMO");              
                            /// Add daughter volume SSRS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width/2.+sfjp.ssst_pz);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width/2.+sfjp.ssst_pz              
                            place.AlphaZ(180.);              
                            /// Rotate: AlphaZ = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SSRS"), place );              
                      } // end placement of SSRS           
                      _create = AgCreate("SSLB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SSLB              
                            Create("SSLB");               
                      }           
                      if ( sfjp.version==1 )           
                      {              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(sfjp.sslb_px);                 
                                  /// Translate x = sfjp.sslb_px                 
                                  place.TranslateY(sfjp.sslb_px);                 
                                  /// Translate y = sfjp.sslb_px                 
                                  place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.);                 
                                  /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.                 
                                  place.AlphaZ(sfjp.alphazh);                 
                                  /// Rotate: AlphaZ = sfjp.alphazh                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(-sfjp.sslb_px);                 
                                  /// Translate x = -sfjp.sslb_px                 
                                  place.TranslateY(-sfjp.sslb_px);                 
                                  /// Translate y = -sfjp.sslb_px                 
                                  place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.);                 
                                  /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.                 
                                  place.AlphaZ(sfjp.alphazh);                 
                                  /// Rotate: AlphaZ = sfjp.alphazh                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(sfjp.sslb_px);                 
                                  /// Translate x = sfjp.sslb_px                 
                                  place.TranslateY(-sfjp.sslb_px);                 
                                  /// Translate y = -sfjp.sslb_px                 
                                  place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.);                 
                                  /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.                 
                                  place.AlphaZ(-sfjp.alphazh);                 
                                  /// Rotate: AlphaZ = -sfjp.alphazh                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(-sfjp.sslb_px);                 
                                  /// Translate x = -sfjp.sslb_px                 
                                  place.TranslateY(sfjp.sslb_px);                 
                                  /// Translate y = sfjp.sslb_px                 
                                  place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.);                 
                                  /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.                 
                                  place.AlphaZ(-sfjp.alphazh);                 
                                  /// Rotate: AlphaZ = -sfjp.alphazh                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(sfjp.sslb_px);                 
                                  /// Translate x = sfjp.sslb_px                 
                                  place.TranslateY(sfjp.sslb_px);                 
                                  /// Translate y = sfjp.sslb_px                 
                                  place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.);                 
                                  /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.                 
                                  place.AlphaZ(sfjp.alphazh);                 
                                  /// Rotate: AlphaZ = sfjp.alphazh                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(-sfjp.sslb_px);                 
                                  /// Translate x = -sfjp.sslb_px                 
                                  place.TranslateY(-sfjp.sslb_px);                 
                                  /// Translate y = -sfjp.sslb_px                 
                                  place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.);                 
                                  /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.                 
                                  place.AlphaZ(sfjp.alphazh);                 
                                  /// Rotate: AlphaZ = sfjp.alphazh                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(sfjp.sslb_px);                 
                                  /// Translate x = sfjp.sslb_px                 
                                  place.TranslateY(-sfjp.sslb_px);                 
                                  /// Translate y = -sfjp.sslb_px                 
                                  place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.);                 
                                  /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.                 
                                  place.AlphaZ(-sfjp.alphazh);                 
                                  /// Rotate: AlphaZ = -sfjp.alphazh                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(-sfjp.sslb_px);                 
                                  /// Translate x = -sfjp.sslb_px                 
                                  place.TranslateY(sfjp.sslb_px);                 
                                  /// Translate y = sfjp.sslb_px                 
                                  place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.);                 
                                  /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.                 
                                  place.AlphaZ(-sfjp.alphazh);                 
                                  /// Rotate: AlphaZ = -sfjp.alphazh                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                      }           
                      else           
                      {              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(sfjp.sslt_px);                 
                                  /// Translate x = sfjp.sslt_px                 
                                  place.TranslateY(sfjp.sslt_px);                 
                                  /// Translate y = sfjp.sslt_px                 
                                  place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.);                 
                                  /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.                 
                                  place.AlphaZ(0);                 
                                  /// Rotate: AlphaZ = 0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(-sfjp.sslt_px);                 
                                  /// Translate x = -sfjp.sslt_px                 
                                  place.TranslateY(-sfjp.sslt_px);                 
                                  /// Translate y = -sfjp.sslt_px                 
                                  place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.);                 
                                  /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.                 
                                  place.AlphaZ(0);                 
                                  /// Rotate: AlphaZ = 0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(sfjp.sslt_px);                 
                                  /// Translate x = sfjp.sslt_px                 
                                  place.TranslateY(-sfjp.sslt_px);                 
                                  /// Translate y = -sfjp.sslt_px                 
                                  place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.);                 
                                  /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.                 
                                  place.AlphaZ(0);                 
                                  /// Rotate: AlphaZ = 0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(-sfjp.sslt_px);                 
                                  /// Translate x = -sfjp.sslt_px                 
                                  place.TranslateY(sfjp.sslt_px);                 
                                  /// Translate y = sfjp.sslt_px                 
                                  place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.);                 
                                  /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz/2.                 
                                  place.AlphaZ(0);                 
                                  /// Rotate: AlphaZ = 0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(sfjp.sslt_px);                 
                                  /// Translate x = sfjp.sslt_px                 
                                  place.TranslateY(sfjp.sslt_px);                 
                                  /// Translate y = sfjp.sslt_px                 
                                  place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.);                 
                                  /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.                 
                                  place.AlphaY(180);                 
                                  /// Rotate: AlphaY = 180                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(-sfjp.sslt_px);                 
                                  /// Translate x = -sfjp.sslt_px                 
                                  place.TranslateY(-sfjp.sslt_px);                 
                                  /// Translate y = -sfjp.sslt_px                 
                                  place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.);                 
                                  /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.                 
                                  place.AlphaY(180);                 
                                  /// Rotate: AlphaY = 180                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(sfjp.sslt_px);                 
                                  /// Translate x = sfjp.sslt_px                 
                                  place.TranslateY(-sfjp.sslt_px);                 
                                  /// Translate y = -sfjp.sslt_px                 
                                  place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.);                 
                                  /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.                 
                                  place.AlphaY(180);                 
                                  /// Rotate: AlphaY = 180                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                            { AgPlacement place = AgPlacement("SSLB","SFMO");                 
                                  /// Add daughter volume SSLB to mother SFMO                 
                                  place.TranslateX(-sfjp.sslt_px);                 
                                  /// Translate x = -sfjp.sslt_px                 
                                  place.TranslateY(sfjp.sslt_px);                 
                                  /// Translate y = sfjp.sslt_px                 
                                  place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.);                 
                                  /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz/2.                 
                                  place.AlphaY(180);                 
                                  /// Rotate: AlphaY = 180                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SSLB"), place );                 
                            } // end placement of SSLB              
                      }           
                      _create = AgCreate("SSLT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SSLT              
                            Create("SSLT");               
                      }           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(sfjp.sslt_px);              
                            /// Translate x = sfjp.sslt_px              
                            place.TranslateY(sfjp.sslt_px);              
                            /// Translate y = sfjp.sslt_px              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz-sfjp.sslt_dz/2.);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz-sfjp.sslt_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(-sfjp.sslt_px);              
                            /// Translate x = -sfjp.sslt_px              
                            place.TranslateY(-sfjp.sslt_px);              
                            /// Translate y = -sfjp.sslt_px              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz-sfjp.sslt_dz/2.);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz-sfjp.sslt_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(sfjp.sslt_px);              
                            /// Translate x = sfjp.sslt_px              
                            place.TranslateY(-sfjp.sslt_px);              
                            /// Translate y = -sfjp.sslt_px              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz-sfjp.sslt_dz/2.);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz-sfjp.sslt_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(-sfjp.sslt_px);              
                            /// Translate x = -sfjp.sslt_px              
                            place.TranslateY(sfjp.sslt_px);              
                            /// Translate y = sfjp.sslt_px              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz-sfjp.sslt_dz/2.);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-sfjp.ssss_width-sfjp.ssst_pz-sfjp.sslb_dz-sfjp.sslt_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(sfjp.sslt_px);              
                            /// Translate x = sfjp.sslt_px              
                            place.TranslateY(sfjp.sslt_px);              
                            /// Translate y = sfjp.sslt_px              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz+sfjp.sslt_dz/2.);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz+sfjp.sslt_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(-sfjp.sslt_px);              
                            /// Translate x = -sfjp.sslt_px              
                            place.TranslateY(-sfjp.sslt_px);              
                            /// Translate y = -sfjp.sslt_px              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz+sfjp.sslt_dz/2.);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz+sfjp.sslt_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(sfjp.sslt_px);              
                            /// Translate x = sfjp.sslt_px              
                            place.TranslateY(-sfjp.sslt_px);              
                            /// Translate y = -sfjp.sslt_px              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz+sfjp.sslt_dz/2.);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz+sfjp.sslt_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(-sfjp.sslt_px);              
                            /// Translate x = -sfjp.sslt_px              
                            place.TranslateY(sfjp.sslt_px);              
                            /// Translate y = sfjp.sslt_px              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz+sfjp.sslt_dz/2.);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+sfjp.ssss_width+sfjp.ssst_pz+sfjp.sslb_dz+sfjp.sslt_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      _create = AgCreate("SCMP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCMP              
                            Create("SCMP");               
                      }           
                      { AgPlacement place = AgPlacement("SCMP","SFMO");              
                            /// Add daughter volume SCMP to mother SFMO              
                            place.TranslateX(sfjp.scmp_px);              
                            /// Translate x = sfjp.scmp_px              
                            place.TranslateY(sfjp.scmp_px);              
                            /// Translate y = sfjp.scmp_px              
                            place.TranslateZ(sfjp.scvm_pz);              
                            /// Translate z = sfjp.scvm_pz              
                            place.AlphaZ(-sfjp.alphazh);              
                            /// Rotate: AlphaZ = -sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCMP"), place );              
                      } // end placement of SCMP           
                      { AgPlacement place = AgPlacement("SCMP","SFMO");              
                            /// Add daughter volume SCMP to mother SFMO              
                            place.TranslateX(-sfjp.scmp_px);              
                            /// Translate x = -sfjp.scmp_px              
                            place.TranslateY(-sfjp.scmp_px);              
                            /// Translate y = -sfjp.scmp_px              
                            place.TranslateZ(sfjp.scvm_pz);              
                            /// Translate z = sfjp.scvm_pz              
                            place.AlphaZ(-sfjp.alphazh);              
                            /// Rotate: AlphaZ = -sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCMP"), place );              
                      } // end placement of SCMP           
                      { AgPlacement place = AgPlacement("SCMP","SFMO");              
                            /// Add daughter volume SCMP to mother SFMO              
                            place.TranslateX(sfjp.scmp_px);              
                            /// Translate x = sfjp.scmp_px              
                            place.TranslateY(-sfjp.scmp_px);              
                            /// Translate y = -sfjp.scmp_px              
                            place.TranslateZ(sfjp.scvm_pz);              
                            /// Translate z = sfjp.scvm_pz              
                            place.AlphaZ(sfjp.alphazh);              
                            /// Rotate: AlphaZ = sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCMP"), place );              
                      } // end placement of SCMP           
                      { AgPlacement place = AgPlacement("SCMP","SFMO");              
                            /// Add daughter volume SCMP to mother SFMO              
                            place.TranslateX(-sfjp.scmp_px);              
                            /// Translate x = -sfjp.scmp_px              
                            place.TranslateY(sfjp.scmp_px);              
                            /// Translate y = sfjp.scmp_px              
                            place.TranslateZ(sfjp.scvm_pz);              
                            /// Translate z = sfjp.scvm_pz              
                            place.AlphaZ(sfjp.alphazh);              
                            /// Rotate: AlphaZ = sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCMP"), place );              
                      } // end placement of SCMP           
                      { AgPlacement place = AgPlacement("SCMP","SFMO");              
                            /// Add daughter volume SCMP to mother SFMO              
                            place.TranslateX(sfjp.scmp_px);              
                            /// Translate x = sfjp.scmp_px              
                            place.TranslateY(sfjp.scmp_px);              
                            /// Translate y = sfjp.scmp_px              
                            place.TranslateZ(-sfjp.scvm_pz);              
                            /// Translate z = -sfjp.scvm_pz              
                            place.AlphaZ(-sfjp.alphazh);              
                            /// Rotate: AlphaZ = -sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCMP"), place );              
                      } // end placement of SCMP           
                      { AgPlacement place = AgPlacement("SCMP","SFMO");              
                            /// Add daughter volume SCMP to mother SFMO              
                            place.TranslateX(-sfjp.scmp_px);              
                            /// Translate x = -sfjp.scmp_px              
                            place.TranslateY(-sfjp.scmp_px);              
                            /// Translate y = -sfjp.scmp_px              
                            place.TranslateZ(-sfjp.scvm_pz);              
                            /// Translate z = -sfjp.scvm_pz              
                            place.AlphaZ(-sfjp.alphazh);              
                            /// Rotate: AlphaZ = -sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCMP"), place );              
                      } // end placement of SCMP           
                      { AgPlacement place = AgPlacement("SCMP","SFMO");              
                            /// Add daughter volume SCMP to mother SFMO              
                            place.TranslateX(sfjp.scmp_px);              
                            /// Translate x = sfjp.scmp_px              
                            place.TranslateY(-sfjp.scmp_px);              
                            /// Translate y = -sfjp.scmp_px              
                            place.TranslateZ(-sfjp.scvm_pz);              
                            /// Translate z = -sfjp.scvm_pz              
                            place.AlphaZ(sfjp.alphazh);              
                            /// Rotate: AlphaZ = sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCMP"), place );              
                      } // end placement of SCMP           
                      { AgPlacement place = AgPlacement("SCMP","SFMO");              
                            /// Add daughter volume SCMP to mother SFMO              
                            place.TranslateX(-sfjp.scmp_px);              
                            /// Translate x = -sfjp.scmp_px              
                            place.TranslateY(sfjp.scmp_px);              
                            /// Translate y = sfjp.scmp_px              
                            place.TranslateZ(-sfjp.scvm_pz);              
                            /// Translate z = -sfjp.scvm_pz              
                            place.AlphaZ(sfjp.alphazh);              
                            /// Rotate: AlphaZ = sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCMP"), place );              
                      } // end placement of SCMP           
                      _create = AgCreate("SCVM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCVM              
                            Create("SCVM");               
                      }           
                      { AgPlacement place = AgPlacement("SCVM","SFMO");              
                            /// Add daughter volume SCVM to mother SFMO              
                            place.TranslateX(sfjp.scvm_px);              
                            /// Translate x = sfjp.scvm_px              
                            place.TranslateY(sfjp.scvm_px);              
                            /// Translate y = sfjp.scvm_px              
                            place.TranslateZ(sfjp.scvm_pz);              
                            /// Translate z = sfjp.scvm_pz              
                            place.AlphaZ(-sfjp.alphazh);              
                            /// Rotate: AlphaZ = -sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVM"), place );              
                      } // end placement of SCVM           
                      { AgPlacement place = AgPlacement("SCVM","SFMO");              
                            /// Add daughter volume SCVM to mother SFMO              
                            place.TranslateX(-sfjp.scvm_px);              
                            /// Translate x = -sfjp.scvm_px              
                            place.TranslateY(-sfjp.scvm_px);              
                            /// Translate y = -sfjp.scvm_px              
                            place.TranslateZ(sfjp.scvm_pz);              
                            /// Translate z = sfjp.scvm_pz              
                            place.AlphaZ((180.-sfjp.alphazh));              
                            /// Rotate: AlphaZ = (180.-sfjp.alphazh)              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVM"), place );              
                      } // end placement of SCVM           
                      { AgPlacement place = AgPlacement("SCVM","SFMO");              
                            /// Add daughter volume SCVM to mother SFMO              
                            place.TranslateX(sfjp.scvm_px);              
                            /// Translate x = sfjp.scvm_px              
                            place.TranslateY(-sfjp.scvm_px);              
                            /// Translate y = -sfjp.scvm_px              
                            place.TranslateZ(sfjp.scvm_pz);              
                            /// Translate z = sfjp.scvm_pz              
                            place.AlphaZ(-(180.-sfjp.alphazh));              
                            /// Rotate: AlphaZ = -(180.-sfjp.alphazh)              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVM"), place );              
                      } // end placement of SCVM           
                      { AgPlacement place = AgPlacement("SCVM","SFMO");              
                            /// Add daughter volume SCVM to mother SFMO              
                            place.TranslateX(-sfjp.scvm_px);              
                            /// Translate x = -sfjp.scvm_px              
                            place.TranslateY(sfjp.scvm_px);              
                            /// Translate y = sfjp.scvm_px              
                            place.TranslateZ(sfjp.scvm_pz);              
                            /// Translate z = sfjp.scvm_pz              
                            place.AlphaZ(sfjp.alphazh);              
                            /// Rotate: AlphaZ = sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVM"), place );              
                      } // end placement of SCVM           
                      { AgPlacement place = AgPlacement("SCVM","SFMO");              
                            /// Add daughter volume SCVM to mother SFMO              
                            place.TranslateX(sfjp.scvm_px);              
                            /// Translate x = sfjp.scvm_px              
                            place.TranslateY(sfjp.scvm_px);              
                            /// Translate y = sfjp.scvm_px              
                            place.TranslateZ(-sfjp.scvm_pz);              
                            /// Translate z = -sfjp.scvm_pz              
                            place.AlphaZ(-sfjp.alphazh);              
                            /// Rotate: AlphaZ = -sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVM"), place );              
                      } // end placement of SCVM           
                      { AgPlacement place = AgPlacement("SCVM","SFMO");              
                            /// Add daughter volume SCVM to mother SFMO              
                            place.TranslateX(-sfjp.scvm_px);              
                            /// Translate x = -sfjp.scvm_px              
                            place.TranslateY(-sfjp.scvm_px);              
                            /// Translate y = -sfjp.scvm_px              
                            place.TranslateZ(-sfjp.scvm_pz);              
                            /// Translate z = -sfjp.scvm_pz              
                            place.AlphaZ((180.-sfjp.alphazh));              
                            /// Rotate: AlphaZ = (180.-sfjp.alphazh)              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVM"), place );              
                      } // end placement of SCVM           
                      { AgPlacement place = AgPlacement("SCVM","SFMO");              
                            /// Add daughter volume SCVM to mother SFMO              
                            place.TranslateX(sfjp.scvm_px);              
                            /// Translate x = sfjp.scvm_px              
                            place.TranslateY(-sfjp.scvm_px);              
                            /// Translate y = -sfjp.scvm_px              
                            place.TranslateZ(-sfjp.scvm_pz);              
                            /// Translate z = -sfjp.scvm_pz              
                            place.AlphaZ(-(180.-sfjp.alphazh));              
                            /// Rotate: AlphaZ = -(180.-sfjp.alphazh)              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVM"), place );              
                      } // end placement of SCVM           
                      { AgPlacement place = AgPlacement("SCVM","SFMO");              
                            /// Add daughter volume SCVM to mother SFMO              
                            place.TranslateX(-sfjp.scvm_px);              
                            /// Translate x = -sfjp.scvm_px              
                            place.TranslateY(sfjp.scvm_px);              
                            /// Translate y = sfjp.scvm_px              
                            place.TranslateZ(-sfjp.scvm_pz);              
                            /// Translate z = -sfjp.scvm_pz              
                            place.AlphaZ(sfjp.alphazh);              
                            /// Rotate: AlphaZ = sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVM"), place );              
                      } // end placement of SCVM           
                      END_OF_SFMO:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFMO     
          // ---------------------------------------------------------------------------------------------------     
          void SFLM::Block( AgCreate create )     
          {         
                ///@addtogroup SFLM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFLM");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfpa.dmwid/2;              
                            shape.par("dy")=(sfpa.dmthk+sfpa.gpthk+sfpa.smthk)/2;              
                            shape.par("dz")=sfpa.smlen/2;              
                            /// Shape Bbox dx=sfpa.dmwid/2 dy=(sfpa.dmthk+sfpa.gpthk+sfpa.smthk)/2 dz=sfpa.smlen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFLM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SFDM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFDM              
                            Create("SFDM");               
                      }           
                      { AgPlacement place = AgPlacement("SFDM","SFLM");              
                            /// Add daughter volume SFDM to mother SFLM              
                            place.TranslateY(-(sfpa.smthk+sfpa.gpthk)/2);              
                            /// Translate y = -(sfpa.smthk+sfpa.gpthk)/2              
                            _stacker -> Position( AgBlock::Find("SFDM"), place );              
                      } // end placement of SFDM           
                      _create = AgCreate("SFSM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFSM              
                            Create("SFSM");               
                      }           
                      { AgPlacement place = AgPlacement("SFSM","SFLM");              
                            /// Add daughter volume SFSM to mother SFLM              
                            place.TranslateY((sfpa.dmthk+sfpa.gpthk)/2);              
                            /// Translate y = (sfpa.dmthk+sfpa.gpthk)/2              
                            _stacker -> Position( AgBlock::Find("SFSM"), place );              
                      } // end placement of SFSM           
                      END_OF_SFLM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFLM     
          // ---------------------------------------------------------------------------------------------------     
          void SFDM::Block( AgCreate create )     
          {         
                ///@addtogroup SFDM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFDM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfpa.dmwid/2;              
                            shape.par("dy")=sfpa.dmthk/2;              
                            shape.par("dz")=sfpa.wplen/2;              
                            /// Shape Bbox dx=sfpa.dmwid/2 dy=sfpa.dmthk/2 dz=sfpa.wplen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFDM;              
                            _stacker -> Build(this);              
                      }           
                      wafpcklen=sfpa.wplen/(sfpa.nssd*1.);           
                      /// Loop on iwaf from 1 to sfpa.nssd step=1           
                      for ( iwaf=1; (1>0)? (iwaf<=sfpa.nssd):(iwaf>=sfpa.nssd); iwaf+=1 )           
                      {              
                            _create = AgCreate("SFSW");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create SFSW                 
                                  Create("SFSW");                  
                            }              
                            { AgPlacement place = AgPlacement("SFSW","SFDM");                 
                                  /// Add daughter volume SFSW to mother SFDM                 
                                  place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+iwaf*wafpcklen);                 
                                  /// Translate z = -(sfpa.wplen+wafpcklen)/2+iwaf*wafpcklen                 
                                  _stacker -> Position( AgBlock::Find("SFSW"), place );                 
                            } // end placement of SFSW              
                      }           
                      END_OF_SFDM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFDM     
          // ---------------------------------------------------------------------------------------------------     
          void SFSW::Block( AgCreate create )     
          {         
                ///@addtogroup SFSW_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFSW");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfpa.dmwid/2;              
                            shape.par("dy")=sfjp.sfsw_dy;              
                            shape.par("dz")=sfjp.sfsw_dz;              
                            /// Shape Bbox dx=sfpa.dmwid/2 dy=sfjp.sfsw_dy dz=sfjp.sfsw_dz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFSW;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SFSL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFSL              
                            Create("SFSL");               
                      }           
                      { AgPlacement place = AgPlacement("SFSL","SFSW");              
                            /// Add daughter volume SFSL to mother SFSW              
                            _stacker -> Position( AgBlock::Find("SFSL"), place );              
                      } // end placement of SFSL           
                      _create = AgCreate("SFRA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFRA              
                            Create("SFRA");               
                      }           
                      { AgPlacement place = AgPlacement("SFRA","SFSW");              
                            /// Add daughter volume SFRA to mother SFSW              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(sfjp.sfra_py);              
                            /// Translate y = sfjp.sfra_py              
                            place.TranslateZ(sfjp.sfra_pz);              
                            /// Translate z = sfjp.sfra_pz              
                            _stacker -> Position( AgBlock::Find("SFRA"), place );              
                      } // end placement of SFRA           
                      { AgPlacement place = AgPlacement("SFRA","SFSW");              
                            /// Add daughter volume SFRA to mother SFSW              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(sfjp.sfra_py);              
                            /// Translate y = sfjp.sfra_py              
                            place.TranslateZ(-sfjp.sfra_pz);              
                            /// Translate z = -sfjp.sfra_pz              
                            _stacker -> Position( AgBlock::Find("SFRA"), place );              
                      } // end placement of SFRA           
                      _create = AgCreate("SFRS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFRS              
                            Create("SFRS");               
                      }           
                      { AgPlacement place = AgPlacement("SFRS","SFSW");              
                            /// Add daughter volume SFRS to mother SFSW              
                            place.TranslateX(sfjp.sfrs_px);              
                            /// Translate x = sfjp.sfrs_px              
                            place.TranslateY(sfjp.sfrs_py);              
                            /// Translate y = sfjp.sfrs_py              
                            place.TranslateZ(sfjp.sfra_pz);              
                            /// Translate z = sfjp.sfra_pz              
                            _stacker -> Position( AgBlock::Find("SFRS"), place );              
                      } // end placement of SFRS           
                      { AgPlacement place = AgPlacement("SFRS","SFSW");              
                            /// Add daughter volume SFRS to mother SFSW              
                            place.TranslateX(sfjp.sfrs_px);              
                            /// Translate x = sfjp.sfrs_px              
                            place.TranslateY(sfjp.sfrs_py);              
                            /// Translate y = sfjp.sfrs_py              
                            place.TranslateZ(-sfjp.sfra_pz);              
                            /// Translate z = -sfjp.sfra_pz              
                            _stacker -> Position( AgBlock::Find("SFRS"), place );              
                      } // end placement of SFRS           
                      { AgPlacement place = AgPlacement("SFRS","SFSW");              
                            /// Add daughter volume SFRS to mother SFSW              
                            place.TranslateX(-sfjp.sfrs_px);              
                            /// Translate x = -sfjp.sfrs_px              
                            place.TranslateY(sfjp.sfrs_py);              
                            /// Translate y = sfjp.sfrs_py              
                            place.TranslateZ(sfjp.sfra_pz);              
                            /// Translate z = sfjp.sfra_pz              
                            _stacker -> Position( AgBlock::Find("SFRS"), place );              
                      } // end placement of SFRS           
                      { AgPlacement place = AgPlacement("SFRS","SFSW");              
                            /// Add daughter volume SFRS to mother SFSW              
                            place.TranslateX(-sfjp.sfrs_px);              
                            /// Translate x = -sfjp.sfrs_px              
                            place.TranslateY(sfjp.sfrs_py);              
                            /// Translate y = sfjp.sfrs_py              
                            place.TranslateZ(-sfjp.sfra_pz);              
                            /// Translate z = -sfjp.sfra_pz              
                            _stacker -> Position( AgBlock::Find("SFRS"), place );              
                      } // end placement of SFRS           
                      _create = AgCreate("SFFX");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFFX              
                            Create("SFFX");               
                      }           
                      { AgPlacement place = AgPlacement("SFFX","SFSW");              
                            /// Add daughter volume SFFX to mother SFSW              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz              
                            place.TranslateZ(sfjp.sfra_pz);              
                            /// Translate z = sfjp.sfra_pz              
                            _stacker -> Position( AgBlock::Find("SFFX"), place );              
                      } // end placement of SFFX           
                      { AgPlacement place = AgPlacement("SFFX","SFSW");              
                            /// Add daughter volume SFFX to mother SFSW              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz              
                            place.TranslateZ(-sfjp.sfra_pz);              
                            /// Translate z = -sfjp.sfra_pz              
                            _stacker -> Position( AgBlock::Find("SFFX"), place );              
                      } // end placement of SFFX           
                      _create = AgCreate("SFPI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFPI              
                            Create("SFPI");               
                      }           
                      { AgPlacement place = AgPlacement("SFPI","SFSW");              
                            /// Add daughter volume SFPI to mother SFSW              
                            place.TranslateX(sfjp.sfpi_px);              
                            /// Translate x = sfjp.sfpi_px              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sfpi_py1-sfjp.sfpi_py2);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sfpi_py1-sfjp.sfpi_py2              
                            place.TranslateZ(sfjp.sfpi_pz);              
                            /// Translate z = sfjp.sfpi_pz              
                            place.AlphaX(90);              
                            /// Rotate: AlphaX = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFPI"), place );              
                      } // end placement of SFPI           
                      { AgPlacement place = AgPlacement("SFPI","SFSW");              
                            /// Add daughter volume SFPI to mother SFSW              
                            place.TranslateX(-sfjp.sfpi_px);              
                            /// Translate x = -sfjp.sfpi_px              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sfpi_py1-sfjp.sfpi_py2);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sfpi_py1-sfjp.sfpi_py2              
                            place.TranslateZ(sfjp.sfpi_pz);              
                            /// Translate z = sfjp.sfpi_pz              
                            place.AlphaX(90);              
                            /// Rotate: AlphaX = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFPI"), place );              
                      } // end placement of SFPI           
                      { AgPlacement place = AgPlacement("SFPI","SFSW");              
                            /// Add daughter volume SFPI to mother SFSW              
                            place.TranslateX(sfjp.sfpi_px);              
                            /// Translate x = sfjp.sfpi_px              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sfpi_py1-sfjp.sfpi_py2);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sfpi_py1-sfjp.sfpi_py2              
                            place.TranslateZ(-sfjp.sfpi_pz);              
                            /// Translate z = -sfjp.sfpi_pz              
                            place.AlphaX(90);              
                            /// Rotate: AlphaX = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFPI"), place );              
                      } // end placement of SFPI           
                      { AgPlacement place = AgPlacement("SFPI","SFSW");              
                            /// Add daughter volume SFPI to mother SFSW              
                            place.TranslateX(-sfjp.sfpi_px);              
                            /// Translate x = -sfjp.sfpi_px              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sfpi_py1-sfjp.sfpi_py2);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sfpi_py1-sfjp.sfpi_py2              
                            place.TranslateZ(-sfjp.sfpi_pz);              
                            /// Translate z = -sfjp.sfpi_pz              
                            place.AlphaX(90);              
                            /// Rotate: AlphaX = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFPI"), place );              
                      } // end placement of SFPI           
                      _create = AgCreate("SFAA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFAA              
                            Create("SFAA");               
                      }           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-sfjp.sfaa_px1-sfjp.sfaa_dx);              
                            /// Translate x = -sfjp.sfaa_px1-sfjp.sfaa_dx              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz);              
                            /// Translate z = sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-sfjp.sfaa_px1-sfjp.sfaa_dx-sfjp.sfaa_px2-sfjp.sfaa_px3);              
                            /// Translate x = -sfjp.sfaa_px1-sfjp.sfaa_dx-sfjp.sfaa_px2-sfjp.sfaa_px3              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz);              
                            /// Translate z = sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-sfjp.sfaa_px1-sfjp.sfaa_dx-sfjp.sfaa_px2-sfjp.sfaa_px3-sfjp.sfaa_px2-sfjp.sfaa_px3);              
                            /// Translate x = -sfjp.sfaa_px1-sfjp.sfaa_dx-sfjp.sfaa_px2-sfjp.sfaa_px3-sfjp.sfaa_px2-sfjp.sfaa_px3              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz);              
                            /// Translate z = sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+sfjp.sfaa_px1+sfjp.sfaa_dx);              
                            /// Translate x = +sfjp.sfaa_px1+sfjp.sfaa_dx              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz);              
                            /// Translate z = sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+sfjp.sfaa_px1+sfjp.sfaa_dx+sfjp.sfaa_px2+sfjp.sfaa_px3);              
                            /// Translate x = +sfjp.sfaa_px1+sfjp.sfaa_dx+sfjp.sfaa_px2+sfjp.sfaa_px3              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz);              
                            /// Translate z = sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+sfjp.sfaa_px1+sfjp.sfaa_dx+sfjp.sfaa_px2+sfjp.sfaa_px3+sfjp.sfaa_px2+sfjp.sfaa_px3);              
                            /// Translate x = +sfjp.sfaa_px1+sfjp.sfaa_dx+sfjp.sfaa_px2+sfjp.sfaa_px3+sfjp.sfaa_px2+sfjp.sfaa_px3              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz);              
                            /// Translate z = sfjp.sfaa_pz1+sfjp.sfaa_pz2-sfjp.sfaa_pz3-sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-sfjp.sfaa_px1-sfjp.sfaa_dx);              
                            /// Translate x = -sfjp.sfaa_px1-sfjp.sfaa_dx              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(-sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz);              
                            /// Translate z = -sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-sfjp.sfaa_px1-sfjp.sfaa_dx-sfjp.sfaa_px2-sfjp.sfaa_px3);              
                            /// Translate x = -sfjp.sfaa_px1-sfjp.sfaa_dx-sfjp.sfaa_px2-sfjp.sfaa_px3              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(-sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz);              
                            /// Translate z = -sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-sfjp.sfaa_px1-sfjp.sfaa_dx-sfjp.sfaa_px2-sfjp.sfaa_px3-sfjp.sfaa_px2-sfjp.sfaa_px3);              
                            /// Translate x = -sfjp.sfaa_px1-sfjp.sfaa_dx-sfjp.sfaa_px2-sfjp.sfaa_px3-sfjp.sfaa_px2-sfjp.sfaa_px3              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(-sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz);              
                            /// Translate z = -sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+sfjp.sfaa_px1+sfjp.sfaa_dx);              
                            /// Translate x = +sfjp.sfaa_px1+sfjp.sfaa_dx              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(-sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz);              
                            /// Translate z = -sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+sfjp.sfaa_px1+sfjp.sfaa_dx+sfjp.sfaa_px2+sfjp.sfaa_px3);              
                            /// Translate x = +sfjp.sfaa_px1+sfjp.sfaa_dx+sfjp.sfaa_px2+sfjp.sfaa_px3              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(-sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz);              
                            /// Translate z = -sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+sfjp.sfaa_px1+sfjp.sfaa_dx+sfjp.sfaa_px2+sfjp.sfaa_px3+sfjp.sfaa_px2+sfjp.sfaa_px3);              
                            /// Translate x = +sfjp.sfaa_px1+sfjp.sfaa_dx+sfjp.sfaa_px2+sfjp.sfaa_px3+sfjp.sfaa_px2+sfjp.sfaa_px3              
                            place.TranslateY(sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy);              
                            /// Translate y = sfjp.sfra_py+sfjp.sfra_dy+sfjp.sffx_dyz*2+sfjp.sfaa_dy              
                            place.TranslateZ(-sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz);              
                            /// Translate z = -sfjp.sfaa_pz1-sfjp.sfaa_pz2+sfjp.sfaa_pz3+sfjp.sfaa_dz              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      END_OF_SFSW:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFSW     
          // ---------------------------------------------------------------------------------------------------     
          void SFRA::Block( AgCreate create )     
          {         
                ///@addtogroup SFRA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFRA");              
                            attr.par("seen")=2;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfra_dx;              
                            shape.par("dy")=sfjp.sfra_dy;              
                            shape.par("dz")=sfjp.sfra_dz;              
                            /// Shape Bbox dx=sfjp.sfra_dx dy=sfjp.sfra_dy dz=sfjp.sfra_dz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFRA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFRA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFRA     
          // ---------------------------------------------------------------------------------------------------     
          void SFRS::Block( AgCreate create )     
          {         
                ///@addtogroup SFRS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFRS");              
                            attr.par("seen")=2;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfrs_dx;              
                            shape.par("dy")=sfjp.sfrs_dy;              
                            shape.par("dz")=sfjp.sfra_dz;              
                            /// Shape Bbox dx=sfjp.sfrs_dx dy=sfjp.sfrs_dy dz=sfjp.sfra_dz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFRS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFRS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFRS     
          // ---------------------------------------------------------------------------------------------------     
          void SFFX::Block( AgCreate create )     
          {         
                ///@addtogroup SFFX_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Copper            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Copper");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFFX");              
                            attr.par("seen")=1;              
                            attr.par("colo")=42;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sffx_dx;              
                            shape.par("dy")=sfjp.sffx_dyz;              
                            shape.par("dz")=sfjp.sfra_dz;              
                            /// Shape Bbox dx=sfjp.sffx_dx dy=sfjp.sffx_dyz dz=sfjp.sfra_dz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFFX;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFFX:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFFX     
          // ---------------------------------------------------------------------------------------------------     
          void SFAA::Block( AgCreate create )     
          {         
                ///@addtogroup SFAA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Silicon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Silicon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFAA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=41;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfaa_dx;              
                            shape.par("dy")=sfjp.sfaa_dy;              
                            shape.par("dz")=sfjp.sfaa_dz;              
                            /// Shape Bbox dx=sfjp.sfaa_dx dy=sfjp.sfaa_dy dz=sfjp.sfaa_dz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFAA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFAA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFAA     
          // ---------------------------------------------------------------------------------------------------     
          void SFPI::Block( AgCreate create )     
          {         
                ///@addtogroup SFPI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFPI");              
                            attr.par("seen")=2;              
                            attr.par("colo")=33;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=sfjp.sfpi_rmin/2.;              
                            shape.par("rmax")=sfjp.sfpi_rmax/2.;              
                            shape.par("dz")=sfjp.sfpi_pz/2.0;              
                            /// Shape Tube rmin=sfjp.sfpi_rmin/2. rmax=sfjp.sfpi_rmax/2. dz=sfjp.sfpi_pz/2.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFPI;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SFPJ");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFPJ              
                            Create("SFPJ");               
                      }           
                      { AgPlacement place = AgPlacement("SFPJ","SFPI");              
                            /// Add daughter volume SFPJ to mother SFPI              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-sfjp.sfpi_pz/2.0+sfjp.sfpj_dz);              
                            /// Translate z = -sfjp.sfpi_pz/2.0+sfjp.sfpj_dz              
                            _stacker -> Position( AgBlock::Find("SFPJ"), place );              
                      } // end placement of SFPJ           
                      END_OF_SFPI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFPI     
          // ---------------------------------------------------------------------------------------------------     
          void SFPJ::Block( AgCreate create )     
          {         
                ///@addtogroup SFPJ_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFPJ");              
                            attr.par("seen")=2;              
                            attr.par("colo")=33;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=sfjp.sfpj_dx1+sfjp.sfpj_dx2;              
                            shape.par("rmax")=sfjp.sfpj_dy;              
                            shape.par("dz")=sfjp.sfpj_dz;              
                            /// Shape Tube rmin=sfjp.sfpj_dx1+sfjp.sfpj_dx2 rmax=sfjp.sfpj_dy dz=sfjp.sfpj_dz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFPJ;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFPJ:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFPJ     
          // ---------------------------------------------------------------------------------------------------     
          void SFSL::Block( AgCreate create )     
          {         
                ///@addtogroup SFSL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Silicon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Silicon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFSL");              
                            attr.par("seen")=2;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfsl_dx;              
                            shape.par("dy")=sfjp.sfsl_dy;              
                            shape.par("dz")=sfjp.sfsl_dz;              
                            /// Shape Bbox dx=sfjp.sfsl_dx dy=sfjp.sfsl_dy dz=sfjp.sfsl_dz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFSL;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SFSD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFSD              
                            Create("SFSD");               
                      }           
                      { AgPlacement place = AgPlacement("SFSD","SFSL");              
                            /// Add daughter volume SFSD to mother SFSL              
                            _stacker -> Position( AgBlock::Find("SFSD"), place );              
                      } // end placement of SFSD           
                      END_OF_SFSL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFSL     
          // ---------------------------------------------------------------------------------------------------     
          void SFSD::Block( AgCreate create )     
          {         
                ///@addtogroup SFSD_doc        
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
                      { AgAttribute attr = AgAttribute("SFSD");              
                            attr.par("seen")=2;              
                            attr.par("colo")=41;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfsd_dx;              
                            shape.par("dy")=sfjp.sfsd_dy;              
                            shape.par("dz")=sfjp.sfsd_dz;              
                            /// Shape Bbox dx=sfjp.sfsd_dx dy=sfjp.sfsd_dy dz=sfjp.sfsd_dz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFSD;              
                            _stacker -> Build(this);              
                      }           
                      /*{              
                            GSTPAR( %imed,"stra",1. );// CALL GSTPAR              
                      }*/           
                      END_OF_SFSD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFSD     
          // ---------------------------------------------------------------------------------------------------     
          void SFSM::Block( AgCreate create )     
          {         
                ///@addtogroup SFSM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFSM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfpa.dmwid/2;              
                            shape.par("dy")=sfpa.smthk/2;              
                            shape.par("dz")=sfpa.smlen/2.;              
                            /// Shape Bbox dx=sfpa.dmwid/2 dy=sfpa.smthk/2 dz=sfpa.smlen/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFSM;              
                            _stacker -> Build(this);              
                      }           
                      yoffset = -1.7;           
                      _create = AgCreate("SFLT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFLT              
                            Create("SFLT");               
                      }           
                      hight = sfjp.sfsm_ll*tan(54*pi/180)-sfpb.hhight/tan(pi/5)-0.02;           
                      { AgPlacement place = AgPlacement("SFLT","SFSM");              
                            /// Add daughter volume SFLT to mother SFSM              
                            place.TranslateX(-(sfpb.hhight-sfpb.khight));              
                            /// Translate x = -(sfpb.hhight-sfpb.khight)              
                            place.TranslateY(hight+yoffset);              
                            /// Translate y = hight+yoffset              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            place.AlphaZ(-90-36);              
                            /// Rotate: AlphaZ = -90-36              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFLT"), place );              
                      } // end placement of SFLT           
                      { AgPlacement place = AgPlacement("SFLT","SFSM");              
                            /// Add daughter volume SFLT to mother SFSM              
                            place.TranslateX((sfpb.hhight-sfpb.khight));              
                            /// Translate x = (sfpb.hhight-sfpb.khight)              
                            place.TranslateY(hight+yoffset);              
                            /// Translate y = hight+yoffset              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            place.AlphaY(180.);              
                            /// Rotate: AlphaY = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.AlphaZ(90.+36.);              
                            /// Rotate: AlphaZ = 90.+36.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFLT"), place );              
                      } // end placement of SFLT           
                      _create = AgCreate("SFLU");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFLU              
                            Create("SFLU");               
                      }           
                      { AgPlacement place = AgPlacement("SFLU","SFSM");              
                            /// Add daughter volume SFLU to mother SFSM              
                            place.TranslateX(0.-(sfjp.sfsm_ll-(sfjp.sflu_bl1+sfjp.sflu_h1/2*1/tan(pi/5))));              
                            /// Translate x = 0.-(sfjp.sfsm_ll-(sfjp.sflu_bl1+sfjp.sflu_h1/2*1/tan(pi/5)))              
                            place.TranslateY(0.+yoffset);              
                            /// Translate y = 0.+yoffset              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SFLU"), place );              
                      } // end placement of SFLU           
                      essai = 180;           
                      essai = essai + 27 + 27;           
                      { AgPlacement place = AgPlacement("SFLU","SFSM");              
                            /// Add daughter volume SFLU to mother SFSM              
                            place.TranslateX(-cos(63*pi/180)*2*(sfpb.hbase-sfpb.kbase)-(sfjp.sfsm_ll-(0.2+0.01/tan(pi/5))));              
                            /// Translate x = -cos(63*pi/180)*2*(sfpb.hbase-sfpb.kbase)-(sfjp.sfsm_ll-(0.2+0.01/tan(pi/5)))              
                            place.TranslateY(cos(27*pi/180)*2*(sfpb.hbase-sfpb.kbase)+yoffset);              
                            /// Translate y = cos(27*pi/180)*2*(sfpb.hbase-sfpb.kbase)+yoffset              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            place.AlphaY(180);              
                            /// Rotate: AlphaY = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.AlphaZ(essai);              
                            /// Rotate: AlphaZ = essai              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFLU"), place );              
                      } // end placement of SFLU           
                      { AgPlacement place = AgPlacement("SFLU","SFSM");              
                            /// Add daughter volume SFLU to mother SFSM              
                            place.TranslateX(0.+(sfjp.sfsm_ll-(0.2+0.01/tan(pi/5))));              
                            /// Translate x = 0.+(sfjp.sfsm_ll-(0.2+0.01/tan(pi/5)))              
                            place.TranslateY(0.+yoffset);              
                            /// Translate y = 0.+yoffset              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            place.AlphaY(180.);              
                            /// Rotate: AlphaY = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFLU"), place );              
                      } // end placement of SFLU           
                      { AgPlacement place = AgPlacement("SFLU","SFSM");              
                            /// Add daughter volume SFLU to mother SFSM              
                            place.TranslateX(cos(63*pi/180)*2*(sfpb.hbase-sfpb.kbase)+(sfjp.sfsm_ll-(0.2+0.01/tan(pi/5))));              
                            /// Translate x = cos(63*pi/180)*2*(sfpb.hbase-sfpb.kbase)+(sfjp.sfsm_ll-(0.2+0.01/tan(pi/5)))              
                            place.TranslateY(cos(27*pi/180)*2*(sfpb.hbase-sfpb.kbase)+yoffset);              
                            /// Translate y = cos(27*pi/180)*2*(sfpb.hbase-sfpb.kbase)+yoffset              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            place.AlphaZ(-essai);              
                            /// Rotate: AlphaZ = -essai              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFLU"), place );              
                      } // end placement of SFLU           
                      _create = AgCreate("SFFK");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFFK              
                            Create("SFFK");               
                      }           
                      { AgPlacement place = AgPlacement("SFFK","SFSM");              
                            /// Add daughter volume SFFK to mother SFSM              
                            place.TranslateX(sfjp.sffk_px/2+sfjp.sffk_dxe);              
                            /// Translate x = sfjp.sffk_px/2+sfjp.sffk_dxe              
                            place.TranslateY(-sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy+yoffset);              
                            /// Translate y = -sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy+yoffset              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            _stacker -> Position( AgBlock::Find("SFFK"), place );              
                      } // end placement of SFFK           
                      { AgPlacement place = AgPlacement("SFFK","SFSM");              
                            /// Add daughter volume SFFK to mother SFSM              
                            place.TranslateX(-sfjp.sffk_px/2-sfjp.sffk_dxe);              
                            /// Translate x = -sfjp.sffk_px/2-sfjp.sffk_dxe              
                            place.TranslateY(-sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy+yoffset);              
                            /// Translate y = -sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy+yoffset              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            _stacker -> Position( AgBlock::Find("SFFK"), place );              
                      } // end placement of SFFK           
                      _create = AgCreate("SFFL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFFL              
                            Create("SFFL");               
                      }           
                      { AgPlacement place = AgPlacement("SFFL","SFSM");              
                            /// Add daughter volume SFFL to mother SFSM              
                            place.TranslateX(-sfjp.sfkl_px-sfpb.fsize*cos(15*pi/180));              
                            /// Translate x = -sfjp.sfkl_px-sfpb.fsize*cos(15*pi/180)              
                            place.TranslateY(-sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy-sfpb.fsize*cos(75*pi/180)+yoffset);              
                            /// Translate y = -sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy-sfpb.fsize*cos(75*pi/180)+yoffset              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            place.AlphaZ(15);              
                            /// Rotate: AlphaZ = 15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFFL"), place );              
                      } // end placement of SFFL           
                      { AgPlacement place = AgPlacement("SFFL","SFSM");              
                            /// Add daughter volume SFFL to mother SFSM              
                            place.TranslateX(sfjp.sfkl_px+sfpb.fsize*cos(15*pi/180));              
                            /// Translate x = sfjp.sfkl_px+sfpb.fsize*cos(15*pi/180)              
                            place.TranslateY(-sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy-sfpb.fsize*cos(75*pi/180)+yoffset);              
                            /// Translate y = -sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy-sfpb.fsize*cos(75*pi/180)+yoffset              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            place.AlphaZ(-15);              
                            /// Rotate: AlphaZ = -15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFFL"), place );              
                      } // end placement of SFFL           
                      _create = AgCreate("SFKK");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFKK              
                            Create("SFKK");               
                      }           
                      { AgPlacement place = AgPlacement("SFKK","SFSM");              
                            /// Add daughter volume SFKK to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(-sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_py2+yoffset-sfjp.sfkk_dy/2.);              
                            /// Translate y = -sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_py2+yoffset-sfjp.sfkk_dy/2.              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SFKK"), place );              
                      } // end placement of SFKK           
                      _create = AgCreate("SFKL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFKL              
                            Create("SFKL");               
                      }           
                      { AgPlacement place = AgPlacement("SFKL","SFSM");              
                            /// Add daughter volume SFKL to mother SFSM              
                            place.TranslateX(-sfjp.sfkl_px-sfpb.fsize*cos(15*pi/180)+0.005);              
                            /// Translate x = -sfjp.sfkl_px-sfpb.fsize*cos(15*pi/180)+0.005              
                            place.TranslateY(-sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy-sfpb.fsize*cos(75*pi/180)+yoffset-0.021);              
                            /// Translate y = -sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy-sfpb.fsize*cos(75*pi/180)+yoffset-0.021              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            place.AlphaZ(15);              
                            /// Rotate: AlphaZ = 15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFKL"), place );              
                      } // end placement of SFKL           
                      { AgPlacement place = AgPlacement("SFKL","SFSM");              
                            /// Add daughter volume SFKL to mother SFSM              
                            place.TranslateX(+sfjp.sfkl_px+sfpb.fsize*cos(15*pi/180)-0.005);              
                            /// Translate x = +sfjp.sfkl_px+sfpb.fsize*cos(15*pi/180)-0.005              
                            place.TranslateY(-sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy-sfpb.fsize*cos(75*pi/180)+yoffset-0.021);              
                            /// Translate y = -sfjp.sffk_py1-sfjp.sffk_py2-sfjp.sffk_dy-sfpb.fsize*cos(75*pi/180)+yoffset-0.021              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            place.AlphaZ(-15);              
                            /// Rotate: AlphaZ = -15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFKL"), place );              
                      } // end placement of SFKL           
                      _create = AgCreate("SAPP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SAPP              
                            Create("SAPP");               
                      }           
                      { AgPlacement place = AgPlacement("SAPP","SFSM");              
                            /// Add daughter volume SAPP to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(-sfjp.sapp_py1-(sfjp.sapp_py2+sfjp.sapp_py3)/2.+yoffset);              
                            /// Translate y = -sfjp.sapp_py1-(sfjp.sapp_py2+sfjp.sapp_py3)/2.+yoffset              
                            place.TranslateZ(sfjp.sffk_dz/2+sfjp.sapp_dz/2.);              
                            /// Translate z = sfjp.sffk_dz/2+sfjp.sapp_dz/2.              
                            place.AlphaY(180.);              
                            /// Rotate: AlphaY = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SAPP"), place );              
                      } // end placement of SAPP           
                      { AgPlacement place = AgPlacement("SAPP","SFSM");              
                            /// Add daughter volume SAPP to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(-sfjp.sapp_py1-(sfjp.sapp_py2+sfjp.sapp_py3)/2.+yoffset);              
                            /// Translate y = -sfjp.sapp_py1-(sfjp.sapp_py2+sfjp.sapp_py3)/2.+yoffset              
                            place.TranslateZ(-(sfjp.sffk_dz/2+sfjp.sapp_dz/2.));              
                            /// Translate z = -(sfjp.sffk_dz/2+sfjp.sapp_dz/2.)              
                            _stacker -> Position( AgBlock::Find("SAPP"), place );              
                      } // end placement of SAPP           
                      _create = AgCreate("SFAM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFAM              
                            Create("SFAM");               
                      }           
                      { AgPlacement place = AgPlacement("SFAM","SFSM");              
                            /// Add daughter volume SFAM to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(-sfjp.sapp_py1-(sfjp.sapp_py2+sfjp.sapp_py3)/2.+yoffset);              
                            /// Translate y = -sfjp.sapp_py1-(sfjp.sapp_py2+sfjp.sapp_py3)/2.+yoffset              
                            place.TranslateZ(-(sfjp.sffk_dz/2+sfjp.sapp_dz)-sfjp.sfam_dz/2.);              
                            /// Translate z = -(sfjp.sffk_dz/2+sfjp.sapp_dz)-sfjp.sfam_dz/2.              
                            _stacker -> Position( AgBlock::Find("SFAM"), place );              
                      } // end placement of SFAM           
                      { AgPlacement place = AgPlacement("SFAM","SFSM");              
                            /// Add daughter volume SFAM to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(-sfjp.sapp_py1-(sfjp.sapp_py2+sfjp.sapp_py3)/2.+yoffset);              
                            /// Translate y = -sfjp.sapp_py1-(sfjp.sapp_py2+sfjp.sapp_py3)/2.+yoffset              
                            place.TranslateZ(+(sfjp.sffk_dz/2+sfjp.sapp_dz)+sfjp.sfam_dz/2.);              
                            /// Translate z = +(sfjp.sffk_dz/2+sfjp.sapp_dz)+sfjp.sfam_dz/2.              
                            place.AlphaY(180.);              
                            /// Rotate: AlphaY = 180.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFAM"), place );              
                      } // end placement of SFAM           
                      _create = AgCreate("SFCO");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFCO              
                            Create("SFCO");               
                      }           
                      { AgPlacement place = AgPlacement("SFCO","SFSM");              
                            /// Add daughter volume SFCO to mother SFSM              
                            place.TranslateX(-sfjp.sfco_px);              
                            /// Translate x = -sfjp.sfco_px              
                            place.TranslateY(sfjp.sfco_py);              
                            /// Translate y = sfjp.sfco_py              
                            place.TranslateZ(-(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))-sfjp.sfco_dz/2.);              
                            /// Translate z = -(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))-sfjp.sfco_dz/2.              
                            place.AlphaZ(+sfjp.alphaz);              
                            /// Rotate: AlphaZ = +sfjp.alphaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFCO"), place );              
                      } // end placement of SFCO           
                      { AgPlacement place = AgPlacement("SFCO","SFSM");              
                            /// Add daughter volume SFCO to mother SFSM              
                            place.TranslateX(+sfjp.sfco_px);              
                            /// Translate x = +sfjp.sfco_px              
                            place.TranslateY(sfjp.sfco_py);              
                            /// Translate y = sfjp.sfco_py              
                            place.TranslateZ(+(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))+sfjp.sfco_dz/2.);              
                            /// Translate z = +(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))+sfjp.sfco_dz/2.              
                            place.AlphaZ(-sfjp.alphaz);              
                            /// Rotate: AlphaZ = -sfjp.alphaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFCO"), place );              
                      } // end placement of SFCO           
                      _create = AgCreate("SFCM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFCM              
                            Create("SFCM");               
                      }           
                      { AgPlacement place = AgPlacement("SFCM","SFSM");              
                            /// Add daughter volume SFCM to mother SFSM              
                            place.TranslateX(+sfjp.sfco_px);              
                            /// Translate x = +sfjp.sfco_px              
                            place.TranslateY(sfjp.sfco_py);              
                            /// Translate y = sfjp.sfco_py              
                            place.TranslateZ(-(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))-sfjp.sfco_dz/2.);              
                            /// Translate z = -(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))-sfjp.sfco_dz/2.              
                            place.AlphaZ(-sfjp.alphaz);              
                            /// Rotate: AlphaZ = -sfjp.alphaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFCM"), place );              
                      } // end placement of SFCM           
                      { AgPlacement place = AgPlacement("SFCM","SFSM");              
                            /// Add daughter volume SFCM to mother SFSM              
                            place.TranslateX(-sfjp.sfco_px);              
                            /// Translate x = -sfjp.sfco_px              
                            place.TranslateY(sfjp.sfco_py);              
                            /// Translate y = sfjp.sfco_py              
                            place.TranslateZ(+(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))+sfjp.sfco_dz/2.);              
                            /// Translate z = +(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))+sfjp.sfco_dz/2.              
                            place.AlphaY(180);              
                            /// Rotate: AlphaY = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.AlphaZ(+sfjp.alphaz);              
                            /// Rotate: AlphaZ = +sfjp.alphaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFCM"), place );              
                      } // end placement of SFCM           
                      _create = AgCreate("SFKF");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFKF              
                            Create("SFKF");               
                      }           
                      { AgPlacement place = AgPlacement("SFKF","SFSM");              
                            /// Add daughter volume SFKF to mother SFSM              
                            place.TranslateX(-sfjp.sfkf_px);              
                            /// Translate x = -sfjp.sfkf_px              
                            place.TranslateY(sfjp.sfkf_py);              
                            /// Translate y = sfjp.sfkf_py              
                            place.TranslateZ(-(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))-sfjp.sfkf_dz/2-0.2);              
                            /// Translate z = -(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))-sfjp.sfkf_dz/2-0.2              
                            place.AlphaZ(+sfjp.alphaz);              
                            /// Rotate: AlphaZ = +sfjp.alphaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFKF"), place );              
                      } // end placement of SFKF           
                      { AgPlacement place = AgPlacement("SFKF","SFSM");              
                            /// Add daughter volume SFKF to mother SFSM              
                            place.TranslateX(+sfjp.sfkf_px);              
                            /// Translate x = +sfjp.sfkf_px              
                            place.TranslateY(sfjp.sfkf_py);              
                            /// Translate y = sfjp.sfkf_py              
                            place.TranslateZ(+(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))+sfjp.sfkf_dz/2+0.2);              
                            /// Translate z = +(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))+sfjp.sfkf_dz/2+0.2              
                            place.AlphaZ(-sfjp.alphaz);              
                            /// Rotate: AlphaZ = -sfjp.alphaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFKF"), place );              
                      } // end placement of SFKF           
                      _create = AgCreate("SFKS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFKS              
                            Create("SFKS");               
                      }           
                      { AgPlacement place = AgPlacement("SFKS","SFSM");              
                            /// Add daughter volume SFKS to mother SFSM              
                            place.TranslateX(+sfjp.sfks_px);              
                            /// Translate x = +sfjp.sfks_px              
                            place.TranslateY(sfjp.sfks_py);              
                            /// Translate y = sfjp.sfks_py              
                            place.TranslateZ(-(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))-sfjp.sfkf_dz/2-0.2);              
                            /// Translate z = -(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))-sfjp.sfkf_dz/2-0.2              
                            place.AlphaZ(-sfjp.alphaz);              
                            /// Rotate: AlphaZ = -sfjp.alphaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFKS"), place );              
                      } // end placement of SFKS           
                      { AgPlacement place = AgPlacement("SFKS","SFSM");              
                            /// Add daughter volume SFKS to mother SFSM              
                            place.TranslateX(-sfjp.sfks_px);              
                            /// Translate x = -sfjp.sfks_px              
                            place.TranslateY(sfjp.sfks_py);              
                            /// Translate y = sfjp.sfks_py              
                            place.TranslateZ(+(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))+sfjp.sfkf_dz/2+0.2);              
                            /// Translate z = +(sfjp.sffk_dz/2-(sfjp.sfkf_dz-sfjp.sfcs_dz))+sfjp.sfkf_dz/2+0.2              
                            place.AlphaZ(+sfjp.alphaz);              
                            /// Rotate: AlphaZ = +sfjp.alphaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SFKS"), place );              
                      } // end placement of SFKS           
                      _create = AgCreate("SFPR");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFPR              
                            Create("SFPR");               
                      }           
                      { AgPlacement place = AgPlacement("SFPR","SFSM");              
                            /// Add daughter volume SFPR to mother SFSM              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(+sfjp.sfpr_py);              
                            /// Translate y = +sfjp.sfpr_py              
                            place.TranslateZ(-sfjp.sflu_dz);              
                            /// Translate z = -sfjp.sflu_dz              
                            _stacker -> Position( AgBlock::Find("SFPR"), place );              
                      } // end placement of SFPR           
                      { AgPlacement place = AgPlacement("SFPR","SFSM");              
                            /// Add daughter volume SFPR to mother SFSM              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(+sfjp.sfpr_py);              
                            /// Translate y = +sfjp.sfpr_py              
                            place.TranslateZ(+sfjp.sflu_dz-3.7);              
                            /// Translate z = +sfjp.sflu_dz-3.7              
                            _stacker -> Position( AgBlock::Find("SFPR"), place );              
                      } // end placement of SFPR           
                      _create = AgCreate("SFPB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFPB              
                            Create("SFPB");               
                      }           
                      { AgPlacement place = AgPlacement("SFPB","SFSM");              
                            /// Add daughter volume SFPB to mother SFSM              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(+sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2);              
                            /// Translate y = +sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz/2.);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz/2.              
                            _stacker -> Position( AgBlock::Find("SFPB"), place );              
                      } // end placement of SFPB           
                      { AgPlacement place = AgPlacement("SFPB","SFSM");              
                            /// Add daughter volume SFPB to mother SFSM              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(+sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2);              
                            /// Translate y = +sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz/2.);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz/2.              
                            _stacker -> Position( AgBlock::Find("SFPB"), place );              
                      } // end placement of SFPB           
                      _create = AgCreate("SSBS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SSBS              
                            Create("SSBS");               
                      }           
                      { AgPlacement place = AgPlacement("SSBS","SFSM");              
                            /// Add daughter volume SSBS to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(+sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2-0.8/2.-sfjp.ssbs_dy/2.);              
                            /// Translate y = +sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2-0.8/2.-sfjp.ssbs_dy/2.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-0.2+sfjp.ssbb_dz+sfjp.ssbs_dx/2.);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-0.2+sfjp.ssbb_dz+sfjp.ssbs_dx/2.              
                            _stacker -> Position( AgBlock::Find("SSBS"), place );              
                      } // end placement of SSBS           
                      { AgPlacement place = AgPlacement("SSBS","SFSM");              
                            /// Add daughter volume SSBS to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(+sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2-0.8/2.-sfjp.ssbs_dy/2.);              
                            /// Translate y = +sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2-0.8/2.-sfjp.ssbs_dy/2.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+0.2-sfjp.ssbb_dz-sfjp.ssbs_dx/2.);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+0.2-sfjp.ssbb_dz-sfjp.ssbs_dx/2.              
                            _stacker -> Position( AgBlock::Find("SSBS"), place );              
                      } // end placement of SSBS           
                      _create = AgCreate("SSBB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SSBB              
                            Create("SSBB");               
                      }           
                      { AgPlacement place = AgPlacement("SSBB","SFSM");              
                            /// Add daughter volume SSBB to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(+sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2-0.8/2.-sfjp.ssbs_dy/2.);              
                            /// Translate y = +sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2-0.8/2.-sfjp.ssbs_dy/2.              
                            place.TranslateZ(-sfjp.sflu_dz-sfjp.sfpbdz-0.2+sfjp.ssbb_dz/2.);              
                            /// Translate z = -sfjp.sflu_dz-sfjp.sfpbdz-0.2+sfjp.ssbb_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSBB"), place );              
                      } // end placement of SSBB           
                      { AgPlacement place = AgPlacement("SSBB","SFSM");              
                            /// Add daughter volume SSBB to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(+sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2-0.8/2.-sfjp.ssbs_dy/2.);              
                            /// Translate y = +sfjp.sfpr_py-sfjp.sfpb_py+sfjp.sfpb_py2-0.8/2.-sfjp.ssbs_dy/2.              
                            place.TranslateZ(+sfjp.sflu_dz+sfjp.sfpbdz+0.2-sfjp.ssbb_dz/2.);              
                            /// Translate z = +sfjp.sflu_dz+sfjp.sfpbdz+0.2-sfjp.ssbb_dz/2.              
                            _stacker -> Position( AgBlock::Find("SSBB"), place );              
                      } // end placement of SSBB           
                      _create = AgCreate("SFLA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFLA              
                            Create("SFLA");               
                      }           
                      _create = AgCreate("SFLB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFLB              
                            Create("SFLB");               
                      }           
                      _create = AgCreate("SFLC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFLC              
                            Create("SFLC");               
                      }           
                      _create = AgCreate("SFEB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFEB              
                            Create("SFEB");               
                      }           
                      _create = AgCreate("SFES");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFES              
                            Create("SFES");               
                      }           
                      wafpcklen=sfpa.wplen/(sfpa.nssd*1.);           
                      /// Loop on iwaf from 1 to 8 step=1           
                      for ( iwaf=1; (1>0)? (iwaf<=8):(iwaf>=8); iwaf+=1 )           
                      {              
                            /// Loop on jwaf from 1 to iwaf step=1              
                            for ( jwaf=1; (1>0)? (jwaf<=iwaf):(jwaf>=iwaf); jwaf+=1 )              
                            {                 
                                  { AgPlacement place = AgPlacement("SFLA","SFSM");                    
                                        /// Add daughter volume SFLA to mother SFSM                    
                                        place.TranslateX(+sfjp.sfla_px+sfjp.flex_di*jwaf);                    
                                        /// Translate x = +sfjp.sfla_px+sfjp.flex_di*jwaf                    
                                        place.TranslateY(sfjp.sfla_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = sfjp.sfla_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+iwaf*wafpcklen);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2+iwaf*wafpcklen                    
                                        place.AlphaZ(-sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = -sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLA"), place );                    
                                  } // end placement of SFLA                 
                                  { AgPlacement place = AgPlacement("SFLA","SFSM");                    
                                        /// Add daughter volume SFLA to mother SFSM                    
                                        place.TranslateX(-sfjp.sfla_px-sfjp.flex_di*jwaf);                    
                                        /// Translate x = -sfjp.sfla_px-sfjp.flex_di*jwaf                    
                                        place.TranslateY(sfjp.sfla_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = sfjp.sfla_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-iwaf*wafpcklen);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2-iwaf*wafpcklen                    
                                        place.AlphaZ(+sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = +sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLA"), place );                    
                                  } // end placement of SFLA                 
                                  { AgPlacement place = AgPlacement("SFLC","SFSM");                    
                                        /// Add daughter volume SFLC to mother SFSM                    
                                        place.TranslateX(+sfjp.sfla_px+sfjp.flex_di*jwaf);                    
                                        /// Translate x = +sfjp.sfla_px+sfjp.flex_di*jwaf                    
                                        place.TranslateY(sfjp.sfla_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = sfjp.sfla_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2.+16*wafpcklen+wafpcklen/2.+sfjp.sflb_dz+8.5*sfjp.sflc_dz-iwaf*sfjp.sflc_dz);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2.+16*wafpcklen+wafpcklen/2.+sfjp.sflb_dz+8.5*sfjp.sflc_dz-iwaf*sfjp.sflc_dz                    
                                        place.AlphaZ(-sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = -sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLC"), place );                    
                                  } // end placement of SFLC                 
                                  { AgPlacement place = AgPlacement("SFLC","SFSM");                    
                                        /// Add daughter volume SFLC to mother SFSM                    
                                        place.TranslateX(-sfjp.sfla_px-sfjp.flex_di*jwaf);                    
                                        /// Translate x = -sfjp.sfla_px-sfjp.flex_di*jwaf                    
                                        place.TranslateY(sfjp.sfla_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = sfjp.sfla_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2.-16*wafpcklen-wafpcklen/2.-sfjp.sflb_dz-8.5*sfjp.sflc_dz+iwaf*sfjp.sflc_dz);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2.-16*wafpcklen-wafpcklen/2.-sfjp.sflb_dz-8.5*sfjp.sflc_dz+iwaf*sfjp.sflc_dz                    
                                        place.AlphaZ(+sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = +sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLC"), place );                    
                                  } // end placement of SFLC                 
                                  { AgPlacement place = AgPlacement("SFLA","SFSM");                    
                                        /// Add daughter volume SFLA to mother SFSM                    
                                        place.TranslateX(+sfjp.sflc_px+sfjp.flex_di*jwaf);                    
                                        /// Translate x = +sfjp.sflc_px+sfjp.flex_di*jwaf                    
                                        place.TranslateY(-sfjp.sflc_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = -sfjp.sflc_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen                    
                                        place.AlphaZ(-sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = -sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLA"), place );                    
                                  } // end placement of SFLA                 
                                  { AgPlacement place = AgPlacement("SFLA","SFSM");                    
                                        /// Add daughter volume SFLA to mother SFSM                    
                                        place.TranslateX(-sfjp.sflc_px-sfjp.flex_di*jwaf);                    
                                        /// Translate x = -sfjp.sflc_px-sfjp.flex_di*jwaf                    
                                        place.TranslateY(-sfjp.sflc_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = -sfjp.sflc_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen                    
                                        place.AlphaZ(+sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = +sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLA"), place );                    
                                  } // end placement of SFLA                 
                                  { AgPlacement place = AgPlacement("SFLC","SFSM");                    
                                        /// Add daughter volume SFLC to mother SFSM                    
                                        place.TranslateX(+sfjp.sflc_px+sfjp.flex_di*jwaf);                    
                                        /// Translate x = +sfjp.sflc_px+sfjp.flex_di*jwaf                    
                                        place.TranslateY(-sfjp.sflc_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = -sfjp.sflc_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+8.5*sfjp.sflc_dz-iwaf*sfjp.sflc_dz);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+8.5*sfjp.sflc_dz-iwaf*sfjp.sflc_dz                    
                                        place.AlphaZ(-sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = -sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLC"), place );                    
                                  } // end placement of SFLC                 
                                  { AgPlacement place = AgPlacement("SFLC","SFSM");                    
                                        /// Add daughter volume SFLC to mother SFSM                    
                                        place.TranslateX(-sfjp.sflc_px-sfjp.flex_di*jwaf);                    
                                        /// Translate x = -sfjp.sflc_px-sfjp.flex_di*jwaf                    
                                        place.TranslateY(-sfjp.sflc_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = -sfjp.sflc_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-8.5*sfjp.sflc_dz+iwaf*sfjp.sflc_dz);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-8.5*sfjp.sflc_dz+iwaf*sfjp.sflc_dz                    
                                        place.AlphaZ(+sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = +sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLC"), place );                    
                                  } // end placement of SFLC                 
                            }              
                            /// Loop on jwaf from 1 to 8 step=1              
                            for ( jwaf=1; (1>0)? (jwaf<=8):(jwaf>=8); jwaf+=1 )              
                            {                 
                                  { AgPlacement place = AgPlacement("SFLA","SFSM");                    
                                        /// Add daughter volume SFLA to mother SFSM                    
                                        place.TranslateX(+sfjp.sfla_px+sfjp.flex_di*jwaf);                    
                                        /// Translate x = +sfjp.sfla_px+sfjp.flex_di*jwaf                    
                                        place.TranslateY(sfjp.sfla_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = sfjp.sfla_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen                    
                                        place.AlphaZ(-sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = -sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLA"), place );                    
                                  } // end placement of SFLA                 
                                  { AgPlacement place = AgPlacement("SFLA","SFSM");                    
                                        /// Add daughter volume SFLA to mother SFSM                    
                                        place.TranslateX(-sfjp.sfla_px-sfjp.flex_di*jwaf);                    
                                        /// Translate x = -sfjp.sfla_px-sfjp.flex_di*jwaf                    
                                        place.TranslateY(sfjp.sfla_py+sfjp.flex_di*jwaf);                    
                                        /// Translate y = sfjp.sfla_py+sfjp.flex_di*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen                    
                                        place.AlphaZ(+sfjp.alphaz);                    
                                        /// Rotate: AlphaZ = +sfjp.alphaz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("SFLA"), place );                    
                                  } // end placement of SFLA                 
                            }              
                            { AgPlacement place = AgPlacement("SFLB","SFSM");                 
                                  /// Add daughter volume SFLB to mother SFSM                 
                                  place.TranslateX(+sfjp.sfla_px+sfjp.flex_di*iwaf);                 
                                  /// Translate x = +sfjp.sfla_px+sfjp.flex_di*iwaf                 
                                  place.TranslateY(sfjp.sfla_py+sfjp.flex_di*iwaf);                 
                                  /// Translate y = sfjp.sfla_py+sfjp.flex_di*iwaf                 
                                  place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+sfjp.sflb_dz/2.);                 
                                  /// Translate z = -(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+sfjp.sflb_dz/2.                 
                                  place.AlphaZ(-sfjp.alphaz);                 
                                  /// Rotate: AlphaZ = -sfjp.alphaz                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SFLB"), place );                 
                            } // end placement of SFLB              
                            { AgPlacement place = AgPlacement("SFLB","SFSM");                 
                                  /// Add daughter volume SFLB to mother SFSM                 
                                  place.TranslateX(-sfjp.sfla_px-sfjp.flex_di*iwaf);                 
                                  /// Translate x = -sfjp.sfla_px-sfjp.flex_di*iwaf                 
                                  place.TranslateY(sfjp.sfla_py+sfjp.flex_di*iwaf);                 
                                  /// Translate y = sfjp.sfla_py+sfjp.flex_di*iwaf                 
                                  place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-sfjp.sflb_dz/2.);                 
                                  /// Translate z = +(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-sfjp.sflb_dz/2.                 
                                  place.AlphaZ(+sfjp.alphaz);                 
                                  /// Rotate: AlphaZ = +sfjp.alphaz                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SFLB"), place );                 
                            } // end placement of SFLB              
                            { AgPlacement place = AgPlacement("SFES","SFSM");                 
                                  /// Add daughter volume SFES to mother SFSM                 
                                  place.TranslateX(-sfjp.sfes_px);                 
                                  /// Translate x = -sfjp.sfes_px                 
                                  place.TranslateY(-sfjp.sfes_py);                 
                                  /// Translate y = -sfjp.sfes_py                 
                                  place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+(iwaf)*wafpcklen+wafpcklen/2.-sfjp.sfeb_dz/2.-sfjp.sfes_pz/2.);                 
                                  /// Translate z = -(sfpa.wplen+wafpcklen)/2+(iwaf)*wafpcklen+wafpcklen/2.-sfjp.sfeb_dz/2.-sfjp.sfes_pz/2.                 
                                  place.AlphaZ(57.66);                 
                                  /// Rotate: AlphaZ = 57.66                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SFES"), place );                 
                            } // end placement of SFES              
                            { AgPlacement place = AgPlacement("SFES","SFSM");                 
                                  /// Add daughter volume SFES to mother SFSM                 
                                  place.TranslateX(+sfjp.sfes_px);                 
                                  /// Translate x = +sfjp.sfes_px                 
                                  place.TranslateY(-sfjp.sfes_py);                 
                                  /// Translate y = -sfjp.sfes_py                 
                                  place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-(iwaf)*wafpcklen-wafpcklen/2.+sfjp.sfeb_dz/2.+sfjp.sfes_pz/2.);                 
                                  /// Translate z = +(sfpa.wplen+wafpcklen)/2-(iwaf)*wafpcklen-wafpcklen/2.+sfjp.sfeb_dz/2.+sfjp.sfes_pz/2.                 
                                  place.AlphaZ(-57.66);                 
                                  /// Rotate: AlphaZ = -57.66                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SFES"), place );                 
                            } // end placement of SFES              
                            { AgPlacement place = AgPlacement("SFEB","SFSM");                 
                                  /// Add daughter volume SFEB to mother SFSM                 
                                  place.TranslateX(-sfjp.sfeb_px);                 
                                  /// Translate x = -sfjp.sfeb_px                 
                                  place.TranslateY(-sfjp.sfeb_py);                 
                                  /// Translate y = -sfjp.sfeb_py                 
                                  place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen+wafpcklen/2.-sfjp.sfeb_dz/2.-sfjp.sfes_pz/2.);                 
                                  /// Translate z = -(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen+wafpcklen/2.-sfjp.sfeb_dz/2.-sfjp.sfes_pz/2.                 
                                  place.AlphaZ(55.35);                 
                                  /// Rotate: AlphaZ = 55.35                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SFEB"), place );                 
                            } // end placement of SFEB              
                            { AgPlacement place = AgPlacement("SFEB","SFSM");                 
                                  /// Add daughter volume SFEB to mother SFSM                 
                                  place.TranslateX(+sfjp.sfeb_px);                 
                                  /// Translate x = +sfjp.sfeb_px                 
                                  place.TranslateY(-sfjp.sfeb_py);                 
                                  /// Translate y = -sfjp.sfeb_py                 
                                  place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen-wafpcklen/2.+sfjp.sfeb_dz/2.+sfjp.sfes_pz/2.);                 
                                  /// Translate z = +(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen-wafpcklen/2.+sfjp.sfeb_dz/2.+sfjp.sfes_pz/2.                 
                                  place.AlphaZ(-55.35);                 
                                  /// Rotate: AlphaZ = -55.35                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("SFEB"), place );                 
                            } // end placement of SFEB              
                      }           
                      END_OF_SFSM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFSM     
          // ---------------------------------------------------------------------------------------------------     
          void SFLT::Block( AgCreate create )     
          {         
                ///@addtogroup SFLT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFLT");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trap");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=sfjp.sflu_dz;              
                            shape.par("thet")=0;              
                            shape.par("phi")=0;              
                            shape.par("h1")=sfjp.sflu_h1;              
                            shape.par("bl1")=sfjp.sflu_bl1;              
                            shape.par("tl1")=sfjp.sflu_bl1-sfjp.sflu_h1/tan(pi/5);              
                            shape.par("alp1")=(pi/2-atan(2*tan(pi/5)))*360/(2*pi);              
                            shape.par("h2")=sfjp.sflu_h1;              
                            shape.par("bl2")=sfjp.sflu_bl1;              
                            shape.par("tl2")=sfjp.sflu_bl1-sfjp.sflu_h1/tan(pi/5);              
                            shape.par("alp2")=(pi/2-atan(2*tan(pi/5)))*360/(2*pi);              
                            /// Shape Trap dz=sfjp.sflu_dz thet=0 phi=0 h1=sfjp.sflu_h1 bl1=sfjp.sflu_bl1 tl1=sfjp.sflu_bl1-sfjp.sflu_h1/tan(pi/5) alp1=(pi/2-atan(2*tan(pi/5)))*360/(2*pi) h2=sfjp.sflu_h1 bl2=sfjp.sflu_bl1 tl2=sfjp.sflu_bl1-sfjp.sflu_h1/tan(pi/5) alp2=(pi/2-atan(2*tan(pi/5)))*360/(2*pi)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFLT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFLT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFLT     
          // ---------------------------------------------------------------------------------------------------     
          void SFLU::Block( AgCreate create )     
          {         
                ///@addtogroup SFLU_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFLU");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trap");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=sfjp.sflu_dz;              
                            shape.par("thet")=0;              
                            shape.par("phi")=0;              
                            shape.par("h1")=sfjp.sflu_h1;              
                            shape.par("bl1")=sfjp.sflu_bl1;              
                            shape.par("tl1")=sfjp.sflu_bl1-sfjp.sflu_h1/tan(27*2*pi/360);              
                            shape.par("alp1")=(pi/2-atan(2*tan(27*2*pi/360)))*360/(2*pi);              
                            shape.par("h2")=sfjp.sflu_h1;              
                            shape.par("bl2")=sfjp.sflu_bl1;              
                            shape.par("tl2")=sfjp.sflu_bl1-sfjp.sflu_h1/tan(27*2*pi/360);              
                            shape.par("alp2")=(pi/2-atan(2*tan(27*2*pi/360)))*360/(2*pi);              
                            /// Shape Trap dz=sfjp.sflu_dz thet=0 phi=0 h1=sfjp.sflu_h1 bl1=sfjp.sflu_bl1 tl1=sfjp.sflu_bl1-sfjp.sflu_h1/tan(27*2*pi/360) alp1=(pi/2-atan(2*tan(27*2*pi/360)))*360/(2*pi) h2=sfjp.sflu_h1 bl2=sfjp.sflu_bl1 tl2=sfjp.sflu_bl1-sfjp.sflu_h1/tan(27*2*pi/360) alp2=(pi/2-atan(2*tan(27*2*pi/360)))*360/(2*pi)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFLU;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFLU:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFLU     
          // ---------------------------------------------------------------------------------------------------     
          void SFFK::Block( AgCreate create )     
          {         
                ///@addtogroup SFFK_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFFK");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sffk_dxe;              
                            shape.par("dy")=sfjp.sffk_dy;              
                            shape.par("dz")=sfjp.sffk_dz/2;              
                            /// Shape Bbox dx=sfjp.sffk_dxe dy=sfjp.sffk_dy dz=sfjp.sffk_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFFK;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFFK:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFFK     
          // ---------------------------------------------------------------------------------------------------     
          void SFFL::Block( AgCreate create )     
          {         
                ///@addtogroup SFFL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFFL");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sffl_dx/cos(15*pi/180);              
                            shape.par("dy")=sfjp.sffk_dy;              
                            shape.par("dz")=sfjp.sffk_dz/2;              
                            /// Shape Bbox dx=sfjp.sffl_dx/cos(15*pi/180) dy=sfjp.sffk_dy dz=sfjp.sffk_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFFL;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFFL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFFL     
          // ---------------------------------------------------------------------------------------------------     
          void SFKK::Block( AgCreate create )     
          {         
                ///@addtogroup SFKK_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFKK");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sffk_dxz/2.;              
                            shape.par("dy")=sfjp.sfkk_dy/2.;              
                            shape.par("dz")=sfjp.sffk_dz/2;              
                            /// Shape Bbox dx=sfjp.sffk_dxz/2. dy=sfjp.sfkk_dy/2. dz=sfjp.sffk_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFKK;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFKK:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFKK     
          // ---------------------------------------------------------------------------------------------------     
          void SFKL::Block( AgCreate create )     
          {         
                ///@addtogroup SFKL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFKL");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sffl_dx/cos(15*pi/180);              
                            shape.par("dy")=sfjp.sfkk_dy/2.;              
                            shape.par("dz")=sfjp.sffk_dz/2;              
                            /// Shape Bbox dx=sfjp.sffl_dx/cos(15*pi/180) dy=sfjp.sfkk_dy/2. dz=sfjp.sffk_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFKL;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFKL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFKL     
          // ---------------------------------------------------------------------------------------------------     
          void SFLA::Block( AgCreate create )     
          {         
                ///@addtogroup SFLA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFLA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfla_dx/2.;              
                            shape.par("dy")=sfjp.sfla_dy/2.;              
                            shape.par("dz")=sfjp.sfla_dz/2.;              
                            /// Shape Bbox dx=sfjp.sfla_dx/2. dy=sfjp.sfla_dy/2. dz=sfjp.sfla_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFLA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFLA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFLA     
          // ---------------------------------------------------------------------------------------------------     
          void SFLB::Block( AgCreate create )     
          {         
                ///@addtogroup SFLB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFLB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfla_dx/2.;              
                            shape.par("dy")=sfjp.sfla_dy/2.;              
                            shape.par("dz")=sfjp.sflb_dz/2.;              
                            /// Shape Bbox dx=sfjp.sfla_dx/2. dy=sfjp.sfla_dy/2. dz=sfjp.sflb_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFLB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFLB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFLB     
          // ---------------------------------------------------------------------------------------------------     
          void SFLC::Block( AgCreate create )     
          {         
                ///@addtogroup SFLC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFLC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfla_dx/2.;              
                            shape.par("dy")=sfjp.sfla_dy/2.;              
                            shape.par("dz")=sfjp.sflc_dz/2.;              
                            /// Shape Bbox dx=sfjp.sfla_dx/2. dy=sfjp.sfla_dy/2. dz=sfjp.sflc_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFLC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFLC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFLC     
          // ---------------------------------------------------------------------------------------------------     
          void SFEB::Block( AgCreate create )     
          {         
                ///@addtogroup SFEB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFEB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfeb_dx/2.;              
                            shape.par("dy")=sfjp.sfla_dy/2.;              
                            shape.par("dz")=sfjp.sfeb_dz/2.;              
                            /// Shape Bbox dx=sfjp.sfeb_dx/2. dy=sfjp.sfla_dy/2. dz=sfjp.sfeb_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFEB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFEB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFEB     
          // ---------------------------------------------------------------------------------------------------     
          void SFES::Block( AgCreate create )     
          {         
                ///@addtogroup SFES_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFES");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfes_dx/2.;              
                            shape.par("dy")=sfjp.sfla_dy/2.;              
                            shape.par("dz")=sfjp.sfeb_dz/2.;              
                            /// Shape Bbox dx=sfjp.sfes_dx/2. dy=sfjp.sfla_dy/2. dz=sfjp.sfeb_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFES;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFES:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFES     
          // ---------------------------------------------------------------------------------------------------     
          void SFAM::Block( AgCreate create )     
          {         
                ///@addtogroup SFAM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFAM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfam_dxe/2.;              
                            shape.par("dy")=sfjp.sfam_dy/2.;              
                            shape.par("dz")=sfjp.sfam_dz/2;              
                            /// Shape Bbox dx=sfjp.sfam_dxe/2. dy=sfjp.sfam_dy/2. dz=sfjp.sfam_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFAM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SFAB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFAB              
                            Create("SFAB");               
                      }           
                      { AgPlacement place = AgPlacement("SFAB","SFAM");              
                            /// Add daughter volume SFAB to mother SFAM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(sfjp.sfam_dzs/2);              
                            /// Translate z = sfjp.sfam_dzs/2              
                            _stacker -> Position( AgBlock::Find("SFAB"), place );              
                      } // end placement of SFAB           
                      _create = AgCreate("SFAS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFAS              
                            Create("SFAS");               
                      }           
                      { AgPlacement place = AgPlacement("SFAS","SFAM");              
                            /// Add daughter volume SFAS to mother SFAM              
                            place.TranslateX((sfjp.sfam_dxe-sfjp.sfam_dxz)/2.);              
                            /// Translate x = (sfjp.sfam_dxe-sfjp.sfam_dxz)/2.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ((-sfjp.sfam_dz+sfjp.sfam_dzs)/2);              
                            /// Translate z = (-sfjp.sfam_dz+sfjp.sfam_dzs)/2              
                            _stacker -> Position( AgBlock::Find("SFAS"), place );              
                      } // end placement of SFAS           
                      { AgPlacement place = AgPlacement("SFAS","SFAM");              
                            /// Add daughter volume SFAS to mother SFAM              
                            place.TranslateX((-sfjp.sfam_dxe+sfjp.sfam_dxz)/2.);              
                            /// Translate x = (-sfjp.sfam_dxe+sfjp.sfam_dxz)/2.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ((-sfjp.sfam_dz+sfjp.sfam_dzs)/2);              
                            /// Translate z = (-sfjp.sfam_dz+sfjp.sfam_dzs)/2              
                            _stacker -> Position( AgBlock::Find("SFAS"), place );              
                      } // end placement of SFAS           
                      END_OF_SFAM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFAM     
          // ---------------------------------------------------------------------------------------------------     
          void SFAB::Block( AgCreate create )     
          {         
                ///@addtogroup SFAB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFAB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=30;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfam_dxe/2.;              
                            shape.par("dy")=sfjp.sfam_dy/2.;              
                            shape.par("dz")=(sfjp.sfam_dz-sfjp.sfam_dzs)/2;              
                            /// Shape Bbox dx=sfjp.sfam_dxe/2. dy=sfjp.sfam_dy/2. dz=(sfjp.sfam_dz-sfjp.sfam_dzs)/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFAB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFAB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFAB     
          // ---------------------------------------------------------------------------------------------------     
          void SFAS::Block( AgCreate create )     
          {         
                ///@addtogroup SFAS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFAS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=30;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=(sfjp.sfam_dxz)/2.;              
                            shape.par("dy")=(sfjp.sfam_dy)/2.;              
                            shape.par("dz")=(sfjp.sfam_dzs)/2;              
                            /// Shape Bbox dx=(sfjp.sfam_dxz)/2. dy=(sfjp.sfam_dy)/2. dz=(sfjp.sfam_dzs)/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFAS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFAS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFAS     
          // ---------------------------------------------------------------------------------------------------     
          void SAPP::Block( AgCreate create )     
          {         
                ///@addtogroup SAPP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SAPP");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=(sfjp.sapp_dxe+2*sfjp.sapp_dxz)/2.;              
                            shape.par("dy")=(sfjp.sapp_dy+2*sfjp.sapp_dxz)/2.;              
                            shape.par("dz")=sfjp.sapp_dz/2.;              
                            /// Shape Bbox dx=(sfjp.sapp_dxe+2*sfjp.sapp_dxz)/2. dy=(sfjp.sapp_dy+2*sfjp.sapp_dxz)/2. dz=sfjp.sapp_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SAPP;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SAPC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SAPC              
                            Create("SAPC");               
                      }           
                      { AgPlacement place = AgPlacement("SAPC","SAPP");              
                            /// Add daughter volume SAPC to mother SAPP              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ((-sfjp.sapp_dz+sfjp.sapp_dy)/2.);              
                            /// Translate z = (-sfjp.sapp_dz+sfjp.sapp_dy)/2.              
                            _stacker -> Position( AgBlock::Find("SAPC"), place );              
                      } // end placement of SAPC           
                      _create = AgCreate("SAPS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SAPS              
                            Create("SAPS");               
                      }           
                      { AgPlacement place = AgPlacement("SAPS","SAPP");              
                            /// Add daughter volume SAPS to mother SAPP              
                            place.TranslateX(sfjp.sapp_dxe/2.+sfjp.sapp_dxz/2);              
                            /// Translate x = sfjp.sapp_dxe/2.+sfjp.sapp_dxz/2              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SAPS"), place );              
                      } // end placement of SAPS           
                      { AgPlacement place = AgPlacement("SAPS","SAPP");              
                            /// Add daughter volume SAPS to mother SAPP              
                            place.TranslateX(-(sfjp.sapp_dxe/2.+sfjp.sapp_dxz/2));              
                            /// Translate x = -(sfjp.sapp_dxe/2.+sfjp.sapp_dxz/2)              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SAPS"), place );              
                      } // end placement of SAPS           
                      _create = AgCreate("SAPT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SAPT              
                            Create("SAPT");               
                      }           
                      { AgPlacement place = AgPlacement("SAPT","SAPP");              
                            /// Add daughter volume SAPT to mother SAPP              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY((sfjp.sapp_dy+sfjp.sapp_dxz)/2.);              
                            /// Translate y = (sfjp.sapp_dy+sfjp.sapp_dxz)/2.              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SAPT"), place );              
                      } // end placement of SAPT           
                      { AgPlacement place = AgPlacement("SAPT","SAPP");              
                            /// Add daughter volume SAPT to mother SAPP              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(-(sfjp.sapp_dy+sfjp.sapp_dxz)/2.);              
                            /// Translate y = -(sfjp.sapp_dy+sfjp.sapp_dxz)/2.              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SAPT"), place );              
                      } // end placement of SAPT           
                      END_OF_SAPP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SAPP     
          // ---------------------------------------------------------------------------------------------------     
          void SAPC::Block( AgCreate create )     
          {         
                ///@addtogroup SAPC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SAPC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sapp_dxe/2.;              
                            shape.par("dy")=sfjp.sapp_dy/2.;              
                            shape.par("dz")=sfjp.sapp_dy/2.;              
                            /// Shape Bbox dx=sfjp.sapp_dxe/2. dy=sfjp.sapp_dy/2. dz=sfjp.sapp_dy/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SAPC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SAPC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SAPC     
          // ---------------------------------------------------------------------------------------------------     
          void SAPS::Block( AgCreate create )     
          {         
                ///@addtogroup SAPS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SAPS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sapp_dxz/2.;              
                            shape.par("dy")=(sfjp.sapp_dy+2*sfjp.sapp_dxz)/2.;              
                            shape.par("dz")=sfjp.sapp_dz/2.;              
                            /// Shape Bbox dx=sfjp.sapp_dxz/2. dy=(sfjp.sapp_dy+2*sfjp.sapp_dxz)/2. dz=sfjp.sapp_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SAPS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SAPS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SAPS     
          // ---------------------------------------------------------------------------------------------------     
          void SAPT::Block( AgCreate create )     
          {         
                ///@addtogroup SAPT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SAPT");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sapp_dxe/2.;              
                            shape.par("dy")=sfjp.sapp_dxz/2.;              
                            shape.par("dz")=sfjp.sapp_dz/2.;              
                            /// Shape Bbox dx=sfjp.sapp_dxe/2. dy=sfjp.sapp_dxz/2. dz=sfjp.sapp_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SAPT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SAPT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SAPT     
          // ---------------------------------------------------------------------------------------------------     
          void SFCO::Block( AgCreate create )     
          {         
                ///@addtogroup SFCO_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFCO");              
                            attr.par("seen")=1;              
                            attr.par("colo")=30;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfco_dx/2.;              
                            shape.par("dy")=sfjp.sfco_dy/2.;              
                            shape.par("dz")=sfjp.sfco_dz/2;              
                            /// Shape Bbox dx=sfjp.sfco_dx/2. dy=sfjp.sfco_dy/2. dz=sfjp.sfco_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFCO;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFCO:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFCO     
          // ---------------------------------------------------------------------------------------------------     
          void SFCM::Block( AgCreate create )     
          {         
                ///@addtogroup SFCM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFCM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfcm_dx/2.;              
                            shape.par("dy")=sfjp.sfco_dy/2.;              
                            shape.par("dz")=sfjp.sfco_dz/2;              
                            /// Shape Bbox dx=sfjp.sfcm_dx/2. dy=sfjp.sfco_dy/2. dz=sfjp.sfco_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFCM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SFCB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFCB              
                            Create("SFCB");               
                      }           
                      { AgPlacement place = AgPlacement("SFCB","SFCM");              
                            /// Add daughter volume SFCB to mother SFCM              
                            place.TranslateX(+0.5);              
                            /// Translate x = +0.5              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            _stacker -> Position( AgBlock::Find("SFCB"), place );              
                      } // end placement of SFCB           
                      _create = AgCreate("SFCS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFCS              
                            Create("SFCS");               
                      }           
                      { AgPlacement place = AgPlacement("SFCS","SFCM");              
                            /// Add daughter volume SFCS to mother SFCM              
                            place.TranslateX(-1.5);              
                            /// Translate x = -1.5              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(-sfjp.sfco_dz/2+sfjp.sfcs_dz/2);              
                            /// Translate z = -sfjp.sfco_dz/2+sfjp.sfcs_dz/2              
                            _stacker -> Position( AgBlock::Find("SFCS"), place );              
                      } // end placement of SFCS           
                      END_OF_SFCM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFCM     
          // ---------------------------------------------------------------------------------------------------     
          void SFCB::Block( AgCreate create )     
          {         
                ///@addtogroup SFCB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFCB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=30;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfcb_dx/2.;              
                            shape.par("dy")=sfjp.sfco_dy/2.;              
                            shape.par("dz")=sfjp.sfco_dz/2;              
                            /// Shape Bbox dx=sfjp.sfcb_dx/2. dy=sfjp.sfco_dy/2. dz=sfjp.sfco_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFCB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFCB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFCB     
          // ---------------------------------------------------------------------------------------------------     
          void SFCS::Block( AgCreate create )     
          {         
                ///@addtogroup SFCS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFCS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=30;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=(sfjp.sfcm_dx-sfjp.sfcb_dx)/2.;              
                            shape.par("dy")=sfjp.sfco_dy/2.;              
                            shape.par("dz")=sfjp.sfcs_dz/2;              
                            /// Shape Bbox dx=(sfjp.sfcm_dx-sfjp.sfcb_dx)/2. dy=sfjp.sfco_dy/2. dz=sfjp.sfcs_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFCS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFCS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFCS     
          // ---------------------------------------------------------------------------------------------------     
          void SFKF::Block( AgCreate create )     
          {         
                ///@addtogroup SFKF_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFKF");              
                            attr.par("seen")=1;              
                            attr.par("colo")=30;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfkf_dx/2.;              
                            shape.par("dy")=sfjp.sfkf_dy/2.;              
                            shape.par("dz")=sfjp.sfkf_dz/2;              
                            /// Shape Bbox dx=sfjp.sfkf_dx/2. dy=sfjp.sfkf_dy/2. dz=sfjp.sfkf_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFKF;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFKF:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFKF     
          // ---------------------------------------------------------------------------------------------------     
          void SFKS::Block( AgCreate create )     
          {         
                ///@addtogroup SFKS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFKS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=30;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfks_dx/2.;              
                            shape.par("dy")=sfjp.sfkf_dy/2.;              
                            shape.par("dz")=sfjp.sfkf_dz/2;              
                            /// Shape Bbox dx=sfjp.sfks_dx/2. dy=sfjp.sfkf_dy/2. dz=sfjp.sfkf_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFKS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFKS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFKS     
          // ---------------------------------------------------------------------------------------------------     
          void SFPR::Block( AgCreate create )     
          {         
                ///@addtogroup SFPR_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G5            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G5");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFPR");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-126;              
                            shape.par("dphi")=72;              
                            shape.par("npdiv")=1;              
                            shape.par("nz")=2;              
                            shape.Z(0)=0;              
                            shape.Z(1)=3.7;              
                            shape.Rmin(0)=0;              
                            shape.Rmin(1)=0;              
                            shape.Rmax(0)=3.48;              
                            shape.Rmax(1)=3.48;              
                            /// Shape Pgon phi1=-126 dphi=72 npdiv=1 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFPR;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFPR:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFPR     
          // ---------------------------------------------------------------------------------------------------     
          void SFPB::Block( AgCreate create )     
          {         
                ///@addtogroup SFPB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SFPB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sfpb_dx/2.;              
                            shape.par("dy")=sfjp.sfpb_dy/2.;              
                            shape.par("dz")=sfjp.sfpbdz/2.;              
                            /// Shape Bbox dx=sfjp.sfpb_dx/2. dy=sfjp.sfpb_dy/2. dz=sfjp.sfpbdz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFPB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SFPB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SFPB     
          // ---------------------------------------------------------------------------------------------------     
          void SSBS::Block( AgCreate create )     
          {         
                ///@addtogroup SSBS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SSBS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.ssbs_dx/2.;              
                            shape.par("dy")=sfjp.ssbs_dy/2.;              
                            shape.par("dz")=sfjp.ssbs_dx/2.;              
                            /// Shape Bbox dx=sfjp.ssbs_dx/2. dy=sfjp.ssbs_dy/2. dz=sfjp.ssbs_dx/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSBS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SSBS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSBS     
          // ---------------------------------------------------------------------------------------------------     
          void SSBB::Block( AgCreate create )     
          {         
                ///@addtogroup SSBB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SSBB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.ssbb_dx/2.;              
                            shape.par("dy")=sfjp.ssbs_dy/2.;              
                            shape.par("dz")=sfjp.ssbb_dz/2.;              
                            /// Shape Bbox dx=sfjp.ssbb_dx/2. dy=sfjp.ssbs_dy/2. dz=sfjp.ssbb_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSBB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SSBB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSBB     
          // ---------------------------------------------------------------------------------------------------     
          void SSST::Block( AgCreate create )     
          {         
                ///@addtogroup SSST_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SSST");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=sfjp.ssst_rmin;              
                            shape.par("rmax")=sfjp.ssst_rmax;              
                            shape.par("phi1")=sfjp.alphazh;              
                            shape.par("phi2")=(180.-sfjp.alphazh);              
                            shape.par("dz")=sfjp.ssst_width/2.;              
                            /// Shape Tubs rmin=sfjp.ssst_rmin rmax=sfjp.ssst_rmax phi1=sfjp.alphazh phi2=(180.-sfjp.alphazh) dz=sfjp.ssst_width/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSST;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SSST:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSST     
          // ---------------------------------------------------------------------------------------------------     
          void SSSS::Block( AgCreate create )     
          {         
                ///@addtogroup SSSS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SSSS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=sfjp.ssss_rmin;              
                            shape.par("rmax")=sfjp.ssst_rmin;              
                            shape.par("phi1")=sfjp.alphazh;              
                            shape.par("phi2")=(180.-sfjp.alphazh);              
                            shape.par("dz")=sfjp.ssss_width/2.;              
                            /// Shape Tubs rmin=sfjp.ssss_rmin rmax=sfjp.ssst_rmin phi1=sfjp.alphazh phi2=(180.-sfjp.alphazh) dz=sfjp.ssss_width/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSSS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SSSS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSSS     
          // ---------------------------------------------------------------------------------------------------     
          void SSRT::Block( AgCreate create )     
          {         
                ///@addtogroup SSRT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      if ( configb<=5 )           
                      {              
                            /// Material Aluminium               
                            {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");                 
                                  _material = mat;                 
                            }              
                      }           
                      else           
                      {              
                            /// Material Carbon               
                            {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");                 
                                  _material = mat;                 
                            }              
                      }           
                      { AgAttribute attr = AgAttribute("SSRT");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=sfjp.ssst_rmin;              
                            shape.par("rmax")=sfjp.ssst_rmax;              
                            shape.par("phi1")=-sfjp.alphazh;              
                            shape.par("phi2")=+sfjp.alphazh;              
                            shape.par("dz")=sfjp.ssst_width/2.;              
                            /// Shape Tubs rmin=sfjp.ssst_rmin rmax=sfjp.ssst_rmax phi1=-sfjp.alphazh phi2=+sfjp.alphazh dz=sfjp.ssst_width/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSRT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SSRT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSRT     
          // ---------------------------------------------------------------------------------------------------     
          void SSRS::Block( AgCreate create )     
          {         
                ///@addtogroup SSRS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      if ( configb<=5 )           
                      {              
                            /// Material Aluminium               
                            {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");                 
                                  _material = mat;                 
                            }              
                      }           
                      else           
                      {              
                            /// Material Carbon               
                            {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");                 
                                  _material = mat;                 
                            }              
                      }           
                      { AgAttribute attr = AgAttribute("SSRS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=sfjp.ssrs_rmin;              
                            shape.par("rmax")=sfjp.ssst_rmin;              
                            shape.par("phi1")=-sfjp.alphazh;              
                            shape.par("phi2")=+sfjp.alphazh;              
                            shape.par("dz")=sfjp.ssss_width/2.;              
                            /// Shape Tubs rmin=sfjp.ssrs_rmin rmax=sfjp.ssst_rmin phi1=-sfjp.alphazh phi2=+sfjp.alphazh dz=sfjp.ssss_width/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSRS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SSRS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSRS     
          // ---------------------------------------------------------------------------------------------------     
          void SSLB::Block( AgCreate create )     
          {         
                ///@addtogroup SSLB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SSLB");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sslb_dx/2.;              
                            shape.par("dy")=sfjp.sslb_dy/2.;              
                            shape.par("dz")=sfjp.sslb_dz/2.;              
                            /// Shape Bbox dx=sfjp.sslb_dx/2. dy=sfjp.sslb_dy/2. dz=sfjp.sslb_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSLB;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SBCH");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBCH              
                            Create("SBCH");               
                      }           
                      { AgPlacement place = AgPlacement("SBCH","SSLB");              
                            /// Add daughter volume SBCH to mother SSLB              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(sfjp.sslb_dz/2.-sfjp.sscr_thd/2.);              
                            /// Translate z = sfjp.sslb_dz/2.-sfjp.sscr_thd/2.              
                            _stacker -> Position( AgBlock::Find("SBCH"), place );              
                      } // end placement of SBCH           
                      _create = AgCreate("SBCV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBCV              
                            Create("SBCV");               
                      }           
                      { AgPlacement place = AgPlacement("SBCV","SSLB");              
                            /// Add daughter volume SBCV to mother SSLB              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY((sfjp.sscr_wd+sfjp.sscr_vl)/2);              
                            /// Translate y = (sfjp.sscr_wd+sfjp.sscr_vl)/2              
                            place.TranslateZ(sfjp.sslb_dz/2.-sfjp.sscr_thd/2.);              
                            /// Translate z = sfjp.sslb_dz/2.-sfjp.sscr_thd/2.              
                            _stacker -> Position( AgBlock::Find("SBCV"), place );              
                      } // end placement of SBCV           
                      { AgPlacement place = AgPlacement("SBCV","SSLB");              
                            /// Add daughter volume SBCV to mother SSLB              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(-(sfjp.sscr_wd+sfjp.sscr_vl)/2);              
                            /// Translate y = -(sfjp.sscr_wd+sfjp.sscr_vl)/2              
                            place.TranslateZ(sfjp.sslb_dz/2.-sfjp.sscr_thd/2.);              
                            /// Translate z = sfjp.sslb_dz/2.-sfjp.sscr_thd/2.              
                            _stacker -> Position( AgBlock::Find("SBCV"), place );              
                      } // end placement of SBCV           
                      _create = AgCreate("SBFH");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBFH              
                            Create("SBFH");               
                      }           
                      { AgPlacement place = AgPlacement("SBFH","SSLB");              
                            /// Add daughter volume SBFH to mother SSLB              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(sfjp.sslb_dz/2.-sfjp.sscr_thd-sfjp.sscr_tha/2.);              
                            /// Translate z = sfjp.sslb_dz/2.-sfjp.sscr_thd-sfjp.sscr_tha/2.              
                            _stacker -> Position( AgBlock::Find("SBFH"), place );              
                      } // end placement of SBFH           
                      _create = AgCreate("SBFV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SBFV              
                            Create("SBFV");               
                      }           
                      { AgPlacement place = AgPlacement("SBFV","SSLB");              
                            /// Add daughter volume SBFV to mother SSLB              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY((sfjp.sscr_wd+sfjp.sscr_vl)/2);              
                            /// Translate y = (sfjp.sscr_wd+sfjp.sscr_vl)/2              
                            place.TranslateZ(sfjp.sslb_dz/2.-sfjp.sscr_thd-sfjp.sscr_tha/2.);              
                            /// Translate z = sfjp.sslb_dz/2.-sfjp.sscr_thd-sfjp.sscr_tha/2.              
                            _stacker -> Position( AgBlock::Find("SBFV"), place );              
                      } // end placement of SBFV           
                      { AgPlacement place = AgPlacement("SBFV","SSLB");              
                            /// Add daughter volume SBFV to mother SSLB              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(-(sfjp.sscr_wd+sfjp.sscr_vl)/2);              
                            /// Translate y = -(sfjp.sscr_wd+sfjp.sscr_vl)/2              
                            place.TranslateZ(sfjp.sslb_dz/2.-sfjp.sscr_thd-sfjp.sscr_tha/2.);              
                            /// Translate z = sfjp.sslb_dz/2.-sfjp.sscr_thd-sfjp.sscr_tha/2.              
                            _stacker -> Position( AgBlock::Find("SBFV"), place );              
                      } // end placement of SBFV           
                      END_OF_SSLB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSLB     
          // ---------------------------------------------------------------------------------------------------     
          void SBCH::Block( AgCreate create )     
          {         
                ///@addtogroup SBCH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Delrin            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Delrin");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBCH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sscr_hl/2.;              
                            shape.par("dy")=sfjp.sscr_wd/2.;              
                            shape.par("dz")=sfjp.sscr_thd/2.;              
                            /// Shape Bbox dx=sfjp.sscr_hl/2. dy=sfjp.sscr_wd/2. dz=sfjp.sscr_thd/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBCH;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBCH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBCH     
          // ---------------------------------------------------------------------------------------------------     
          void SBFH::Block( AgCreate create )     
          {         
                ///@addtogroup SBFH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBFH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sscr_hl/2.;              
                            shape.par("dy")=sfjp.sscr_wd/2.;              
                            shape.par("dz")=sfjp.sscr_tha/2.;              
                            /// Shape Bbox dx=sfjp.sscr_hl/2. dy=sfjp.sscr_wd/2. dz=sfjp.sscr_tha/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBFH;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBFH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBFH     
          // ---------------------------------------------------------------------------------------------------     
          void SBCV::Block( AgCreate create )     
          {         
                ///@addtogroup SBCV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Delrin            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Delrin");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBCV");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sscr_wd/2.;              
                            shape.par("dy")=sfjp.sscr_vl/2.;              
                            shape.par("dz")=sfjp.sscr_thd/2.;              
                            /// Shape Bbox dx=sfjp.sscr_wd/2. dy=sfjp.sscr_vl/2. dz=sfjp.sscr_thd/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBCV;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBCV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBCV     
          // ---------------------------------------------------------------------------------------------------     
          void SBFV::Block( AgCreate create )     
          {         
                ///@addtogroup SBFV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SBFV");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.sscr_wd/2.;              
                            shape.par("dy")=sfjp.sscr_vl/2.;              
                            shape.par("dz")=sfjp.sscr_tha/2.;              
                            /// Shape Bbox dx=sfjp.sscr_wd/2. dy=sfjp.sscr_vl/2. dz=sfjp.sscr_tha/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SBFV;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SBFV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SBFV     
          // ---------------------------------------------------------------------------------------------------     
          void SSLT::Block( AgCreate create )     
          {         
                ///@addtogroup SSLT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SSLT");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0.;              
                            shape.par("rmax")=sfjp.sslt_rmax;              
                            shape.par("dz")=sfjp.sslt_dz/2.;              
                            /// Shape Tube rmin=0. rmax=sfjp.sslt_rmax dz=sfjp.sslt_dz/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSLT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SSLT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSLT     
          // ---------------------------------------------------------------------------------------------------     
          void SCMP::Block( AgCreate create )     
          {         
                ///@addtogroup SCMP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCMP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.scmp_dx/2.;              
                            shape.par("dy")=sfjp.scmp_dy/2.;              
                            shape.par("dz")=sfjp.scmp_dz/2;              
                            /// Shape Bbox dx=sfjp.scmp_dx/2. dy=sfjp.scmp_dy/2. dz=sfjp.scmp_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCMP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SCMP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCMP     
          // ---------------------------------------------------------------------------------------------------     
          void SCVM::Block( AgCreate create )     
          {         
                ///@addtogroup SCVM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCVM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.scvm_dx/2.;              
                            shape.par("dy")=sfjp.scvm_dy/2.;              
                            shape.par("dz")=sfjp.scvm_dz/2;              
                            /// Shape Bbox dx=sfjp.scvm_dx/2. dy=sfjp.scvm_dy/2. dz=sfjp.scvm_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCVM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SCVB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCVB              
                            Create("SCVB");               
                      }           
                      { AgPlacement place = AgPlacement("SCVB","SCVM");              
                            /// Add daughter volume SCVB to mother SCVM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(-sfjp.scvm_dy/2.+sfjp.scvb_dy/2.);              
                            /// Translate y = -sfjp.scvm_dy/2.+sfjp.scvb_dy/2.              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SCVB"), place );              
                      } // end placement of SCVB           
                      _create = AgCreate("SCVS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SCVS              
                            Create("SCVS");               
                      }           
                      { AgPlacement place = AgPlacement("SCVS","SCVM");              
                            /// Add daughter volume SCVS to mother SCVM              
                            place.TranslateX(sfjp.scvs_px);              
                            /// Translate x = sfjp.scvs_px              
                            place.TranslateY(sfjp.scvs_py);              
                            /// Translate y = sfjp.scvs_py              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            place.AlphaZ(sfjp.alphazh);              
                            /// Rotate: AlphaZ = sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVS"), place );              
                      } // end placement of SCVS           
                      { AgPlacement place = AgPlacement("SCVS","SCVM");              
                            /// Add daughter volume SCVS to mother SCVM              
                            place.TranslateX(-sfjp.scvs_px);              
                            /// Translate x = -sfjp.scvs_px              
                            place.TranslateY(sfjp.scvs_py);              
                            /// Translate y = sfjp.scvs_py              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            place.AlphaZ(-sfjp.alphazh);              
                            /// Rotate: AlphaZ = -sfjp.alphazh              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SCVS"), place );              
                      } // end placement of SCVS           
                      END_OF_SCVM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCVM     
          // ---------------------------------------------------------------------------------------------------     
          void SCVB::Block( AgCreate create )     
          {         
                ///@addtogroup SCVB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCVB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.scvm_dx/2.;              
                            shape.par("dy")=sfjp.scvb_dy/2.;              
                            shape.par("dz")=sfjp.scvm_dz/2;              
                            /// Shape Bbox dx=sfjp.scvm_dx/2. dy=sfjp.scvb_dy/2. dz=sfjp.scvm_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCVB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SCVB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCVB     
          // ---------------------------------------------------------------------------------------------------     
          void SCVS::Block( AgCreate create )     
          {         
                ///@addtogroup SCVS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SCVS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=sfjp.scvs_dx/2.;              
                            shape.par("dy")=sfjp.scvs_dy/2.;              
                            shape.par("dz")=sfjp.scvm_dz/2;              
                            /// Shape Bbox dx=sfjp.scvs_dx/2. dy=sfjp.scvs_dy/2. dz=sfjp.scvm_dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCVS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SCVS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCVS     
          // ---------------------------------------------------------------------------------------------------     
          void SOSK::Block( AgCreate create )     
          {         
                ///@addtogroup SOSK_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
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
                      /// Material SSDALMY            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Ssdalmy");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SOSK");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=sfpa.soutrinn;              
                            shape.par("rmax")=sfpa.soutrout;              
                            shape.par("dz")=sfpa.soutlen;              
                            /// Shape Tube rmin=sfpa.soutrinn rmax=sfpa.soutrout dz=sfpa.soutlen               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SOSK;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SOSK:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SOSK     
    // ----------------------------------------------------------------------- geoctr
       void SisdGeo6::ConstructGeometry( const Char_t *dummy )     
       {        
             ///@addtogroup SisdGeo6_revision        
             ///@{           
                   /// Author: Bouchet and Potekhin           
             ///@}        
             ///@addtogroup SisdGeo6_revision        
             ///@{           
                   /// Created:  1 Feb 07            
             ///@}        
             AddBlock("SFMO");        
             AddBlock("SFLM");        
             AddBlock("SFDM");        
             AddBlock("SFSW");        
             AddBlock("SFSD");        
             AddBlock("SFSL");        
             AddBlock("SFSM");        
             AddBlock("SFLT");        
             AddBlock("SFLU");        
             AddBlock("SFFK");        
             AddBlock("SFFL");        
             AddBlock("SFKK");        
             AddBlock("SFKL");        
             AddBlock("SFRA");        
             AddBlock("SFRS");        
             AddBlock("SFFX");        
             AddBlock("SFPI");        
             AddBlock("SFPJ");        
             AddBlock("SFAA");        
             AddBlock("SFAM");        
             AddBlock("SFAB");        
             AddBlock("SFAS");        
             AddBlock("SAPP");        
             AddBlock("SAPC");        
             AddBlock("SAPS");        
             AddBlock("SAPT");        
             AddBlock("SFLA");        
             AddBlock("SFLB");        
             AddBlock("SFLC");        
             AddBlock("SFES");        
             AddBlock("SFEB");        
             AddBlock("SFCO");        
             AddBlock("SFCM");        
             AddBlock("SFCB");        
             AddBlock("SFCS");        
             AddBlock("SFKF");        
             AddBlock("SFKS");        
             AddBlock("SSBS");        
             AddBlock("SSBB");        
             AddBlock("SFPR");        
             AddBlock("SFPB");        
             AddBlock("SSST");        
             AddBlock("SSSS");        
             AddBlock("SSRS");        
             AddBlock("SSRT");        
             AddBlock("SSLB");        
             AddBlock("SBCH");        
             AddBlock("SBCV");        
             AddBlock("SBFH");        
             AddBlock("SBFV");        
             AddBlock("SSLT");        
             AddBlock("SCMP");        
             AddBlock("SCVM");        
             AddBlock("SCVB");        
             AddBlock("SCVS");        
             AddBlock("SOSK");        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup ssdp_doc        
             ///@{           
                   ++ssdp._index;           
                   ssdp . version = 1; //  Version            
                   /// ssdp . version = 1; //  Version            
                   ssdp . config = 1; //  There are a few configuraions possible            
                   /// ssdp . config = 1; //  There are a few configuraions possible            
                   ssdp . placement = 0; //  0=cave, 1=svtt            
                   /// ssdp . placement = 0; //  0=cave, 1=svtt            
                   //           
                   ssdp.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfjp_doc        
             ///@{           
                   ++sfjp._index;           
                   sfjp . version = 1; //  new version information             
                   /// sfjp . version = 1; //  new version information             
                   sfjp . alphaz = 54; //  Alpha of the SFLA and other parts            
                   /// sfjp . alphaz = 54; //  Alpha of the SFLA and other parts            
                   sfjp . alphazh = 45; //  Alpha of other parts            
                   /// sfjp . alphazh = 45; //  Alpha of other parts            
                   sfjp . ssst_rmin = 31.285; //  Minimum Radius of the Small aluminium sector (outside structure)            
                   /// sfjp . ssst_rmin = 31.285; //  Minimum Radius of the Small aluminium sector (outside structure)            
                   sfjp . ssst_rmax = 31.8; //  Maximum Radios of the Small aluminium sector (outside structure)            
                   /// sfjp . ssst_rmax = 31.8; //  Maximum Radios of the Small aluminium sector (outside structure)            
                   sfjp . ssst_width = 2.5; //  Width of the small aluminium sector (outside structure)            
                   /// sfjp . ssst_width = 2.5; //  Width of the small aluminium sector (outside structure)            
                   sfjp . ssst_pz = 0.2; //  Additional Z-Position of the aluminium sectors            
                   /// sfjp . ssst_pz = 0.2; //  Additional Z-Position of the aluminium sectors            
                   sfjp . ssss_rmin = 23.3; //  Width of the small inner aluminium sector (outside structure)            
                   /// sfjp . ssss_rmin = 23.3; //  Width of the small inner aluminium sector (outside structure)            
                   sfjp . ssss_width = 0.5; //  Width of the small inner aluminium sector (outside structure)            
                   /// sfjp . ssss_width = 0.5; //  Width of the small inner aluminium sector (outside structure)            
                   sfjp . ssrs_rmin = 28.0; //  Width of the side of the small rib (outside structure)            
                   /// sfjp . ssrs_rmin = 28.0; //  Width of the side of the small rib (outside structure)            
                   sfjp . sslb_dx = 8.5; //  Mother volume of the linking box (sector to the cone)            
                   /// sfjp . sslb_dx = 8.5; //  Mother volume of the linking box (sector to the cone)            
                   sfjp . sslb_px = 19.1; //  X-Position = Y-Position of the mother volume of the linking box            
                   /// sfjp . sslb_px = 19.1; //  X-Position = Y-Position of the mother volume of the linking box            
                   sfjp . sslb_dy = 7.3; //  Mother volume of the linking box (sector to the cone)            
                   /// sfjp . sslb_dy = 7.3; //  Mother volume of the linking box (sector to the cone)            
                   sfjp . sslb_dz = 2.5; //  Mother volume of the linking box (sector to the cone)            
                   /// sfjp . sslb_dz = 2.5; //  Mother volume of the linking box (sector to the cone)            
                   sfjp . ssbq_dx = 7.8; //  Linking box (sector to the cone)            
                   /// sfjp . ssbq_dx = 7.8; //  Linking box (sector to the cone)            
                   sfjp . ssbq_dy = 7.3; //  Linking box (sector to the cone)            
                   /// sfjp . ssbq_dy = 7.3; //  Linking box (sector to the cone)            
                   sfjp . ssbq_dz = 2.5; //  Linking box (sector to the cone)            
                   /// sfjp . ssbq_dz = 2.5; //  Linking box (sector to the cone)            
                   sfjp . sscr_tha = 1.5; //  Linking cross total thickness (aluminum part)            
                   /// sfjp . sscr_tha = 1.5; //  Linking cross total thickness (aluminum part)            
                   sfjp . sscr_thd = 1.0; //  Linking cross total thickness (DELRIN part)            
                   /// sfjp . sscr_thd = 1.0; //  Linking cross total thickness (DELRIN part)            
                   sfjp . sscr_wd = 1.2; //  Linking cross total width            
                   /// sfjp . sscr_wd = 1.2; //  Linking cross total width            
                   sfjp . sscr_hl = 8.5; //  Linking cross horizontal arm full length            
                   /// sfjp . sscr_hl = 8.5; //  Linking cross horizontal arm full length            
                   sfjp . sscr_vl = 1.6; //  Linking cross vertical arm full length            
                   /// sfjp . sscr_vl = 1.6; //  Linking cross vertical arm full length            
                   sfjp . sslt_px = 18.1; //  X-Position = Y-Position of the linking tube            
                   /// sfjp . sslt_px = 18.1; //  X-Position = Y-Position of the linking tube            
                   sfjp . sslt_rmax = 0.8; //  Radius of the linking tube (sector to the cone)            
                   /// sfjp . sslt_rmax = 0.8; //  Radius of the linking tube (sector to the cone)            
                   sfjp . sslt_dz = 5.05; //  Width of the linking tube (sector of the cone)            
                   /// sfjp . sslt_dz = 5.05; //  Width of the linking tube (sector of the cone)            
                   sfjp . scmp_dx = 6.3; //  Width of the mounting plate inserted in the cones            
                   /// sfjp . scmp_dx = 6.3; //  Width of the mounting plate inserted in the cones            
                   sfjp . scmp_dy = 0.4; //  Width of the mounting plate inserted in the cones            
                   /// sfjp . scmp_dy = 0.4; //  Width of the mounting plate inserted in the cones            
                   sfjp . scmp_dz = 3.6; //  Width of the mounting plate inserted in the cones            
                   /// sfjp . scmp_dz = 3.6; //  Width of the mounting plate inserted in the cones            
                   sfjp . scmp_px = 15.945; //  X-Position = Y-Position of the mounting plate            
                   /// sfjp . scmp_px = 15.945; //  X-Position = Y-Position of the mounting plate            
                   sfjp . scvm_dz = 3.6; //  Mother volume of the V-shape piece length            
                   /// sfjp . scvm_dz = 3.6; //  Mother volume of the V-shape piece length            
                   sfjp . scvm_dx = 6.4; //  Mother volume of the V-shape piece dx            
                   /// sfjp . scvm_dx = 6.4; //  Mother volume of the V-shape piece dx            
                   sfjp . scvm_px = 17.00; //  X-Position = Y-Position of the V-Shape piece            
                   /// sfjp . scvm_px = 17.00; //  X-Position = Y-Position of the V-Shape piece            
                   sfjp . scvm_dy = 2.6; //  Mother volume of the V-Shape piece dy            
                   /// sfjp . scvm_dy = 2.6; //  Mother volume of the V-Shape piece dy            
                   sfjp . scvm_pz = 57.5; //  Z-Position of the mother volume            
                   /// sfjp . scvm_pz = 57.5; //  Z-Position of the mother volume            
                   sfjp . scvb_dy = 0.5; //  Height of the base of the V-Shape piece            
                   /// sfjp . scvb_dy = 0.5; //  Height of the base of the V-Shape piece            
                   sfjp . scvs_dx = 2.3; //  Dx of the V-plates of the V-shape piece 45 degrees            
                   /// sfjp . scvs_dx = 2.3; //  Dx of the V-plates of the V-shape piece 45 degrees            
                   sfjp . scvs_dy = 0.6; //  Medium Height of the V-plates of the V-shape piece 45 degrees            
                   /// sfjp . scvs_dy = 0.6; //  Medium Height of the V-plates of the V-shape piece 45 degrees            
                   sfjp . scvs_px = 1.0; //  x-Position of the V-plates of the V-shape piece 45 degrees            
                   /// sfjp . scvs_px = 1.0; //  x-Position of the V-plates of the V-shape piece 45 degrees            
                   sfjp . scvs_py = 0.22; //  x-Position of the V-plates of the V-shape piece 45 degrees            
                   /// sfjp . scvs_py = 0.22; //  x-Position of the V-plates of the V-shape piece 45 degrees            
                   sfjp . sfco_dx = 4.4; //  Dx of the connection board (end of the ladder)            
                   /// sfjp . sfco_dx = 4.4; //  Dx of the connection board (end of the ladder)            
                   sfjp . sfco_dy = 0.37; //  Width of the connection board (end of the ladder)            
                   /// sfjp . sfco_dy = 0.37; //  Width of the connection board (end of the ladder)            
                   sfjp . sfco_dz = 15.8; //  Length of the connection board (end of the ladder)            
                   /// sfjp . sfco_dz = 15.8; //  Length of the connection board (end of the ladder)            
                   sfjp . sfco_px = 1.7; //  X-Position of the connection board (end of the ladder)            
                   /// sfjp . sfco_px = 1.7; //  X-Position of the connection board (end of the ladder)            
                   sfjp . sfco_py = 0.2; //  Y-Position of the connection board (end of the ladder)            
                   /// sfjp . sfco_py = 0.2; //  Y-Position of the connection board (end of the ladder)            
                   sfjp . sfcm_dx = 4.0; //  Dx of the second connection board (smaller than the above one;//;//)            
                   /// sfjp . sfcm_dx = 4.0; //  Dx of the second connection board (smaller than the above one;//;//)            
                   sfjp . sfcs_dz = 7.5; //  Dx of the small part of the second connection board            
                   /// sfjp . sfcs_dz = 7.5; //  Dx of the small part of the second connection board            
                   sfjp . sfkf_dy = 0.065; //  Width of the kapton flex circuit between the connection boards            
                   /// sfjp . sfkf_dy = 0.065; //  Width of the kapton flex circuit between the connection boards            
                   sfjp . sfkf_dz = 8.1; //  Length of the kapton flex circuit between the connection boards            
                   /// sfjp . sfkf_dz = 8.1; //  Length of the kapton flex circuit between the connection boards            
                   sfjp . sfkf_dx = 0.44; //  Dx of the first part of the kapton flex circuit            
                   /// sfjp . sfkf_dx = 0.44; //  Dx of the first part of the kapton flex circuit            
                   sfjp . sfkf_px = 0.16; //  x-Position of the first part of the kapton flex circuit            
                   /// sfjp . sfkf_px = 0.16; //  x-Position of the first part of the kapton flex circuit            
                   sfjp . sfkf_py = 2.07; //  y-Position of the first part of the kapton flex circuit            
                   /// sfjp . sfkf_py = 2.07; //  y-Position of the first part of the kapton flex circuit            
                   sfjp . sfks_dx = 1.65; //  Dx of the second part of the kapton flex circuit            
                   /// sfjp . sfks_dx = 1.65; //  Dx of the second part of the kapton flex circuit            
                   sfjp . sfks_px = 0.505; //  x-Position of the second part ot the kapton flex            
                   /// sfjp . sfks_px = 0.505; //  x-Position of the second part ot the kapton flex            
                   sfjp . sfks_py = 1.585; //  y-Position of the second part ot the kapton flex            
                   /// sfjp . sfks_py = 1.585; //  y-Position of the second part ot the kapton flex            
                   sfjp . sfpr_py = 1.79; //  Y-Position of the mechanical parts            
                   /// sfjp . sfpr_py = 1.79; //  Y-Position of the mechanical parts            
                   sfjp . sfpb_py = 3.48; //  Y-Position of the mechanical parts 2            
                   /// sfjp . sfpb_py = 3.48; //  Y-Position of the mechanical parts 2            
                   sfjp . sfpb_py2 = 0.08; //  Y-Position of the mechanical parts 2            
                   /// sfjp . sfpb_py2 = 0.08; //  Y-Position of the mechanical parts 2            
                   sfjp . sfcb_dx = 3.0; //  Dx of the big part of the second connection board            
                   /// sfjp . sfcb_dx = 3.0; //  Dx of the big part of the second connection board            
                   sfjp . ssbs_dy = 0.5; //  Width of the aluminium plates linking the ladder to the sector            
                   /// sfjp . ssbs_dy = 0.5; //  Width of the aluminium plates linking the ladder to the sector            
                   sfjp . ssbs_dx = 2.5; //  Dx = Dz = small part of the aluminium plate linking the ladder            
                   /// sfjp . ssbs_dx = 2.5; //  Dx = Dz = small part of the aluminium plate linking the ladder            
                   sfjp . ssbb_dx = 4.3; //  Dx of the Big part of the aluminium plate linking the ladder             
                   /// sfjp . ssbb_dx = 4.3; //  Dx of the Big part of the aluminium plate linking the ladder             
                   sfjp . ssbb_dz = 1.9; //  Dz of the Big part of the aluminium plate linking the ladder             
                   /// sfjp . ssbb_dz = 1.9; //  Dz of the Big part of the aluminium plate linking the ladder             
                   sfjp . flex_di = 0.02; //  Distanze between overlaying flexes            
                   /// sfjp . flex_di = 0.02; //  Distanze between overlaying flexes            
                   sfjp . sfpb_dx = 4.3; //  Dx of the outside mechanical part (G10 rectangle - box base)            
                   /// sfjp . sfpb_dx = 4.3; //  Dx of the outside mechanical part (G10 rectangle - box base)            
                   sfjp . sfpb_dy = 0.8; //  Width of the outside mechanical part (G10 rectangle - box base)            
                   /// sfjp . sfpb_dy = 0.8; //  Width of the outside mechanical part (G10 rectangle - box base)            
                   sfjp . sfpbdz = 0.95; //  Length of the outside mechanical part (G10 rectangle - box base)            
                   /// sfjp . sfpbdz = 0.95; //  Length of the outside mechanical part (G10 rectangle - box base)            
                   sfjp . sapp_dxe = 7.6; //  Dx of the epoxy core of the adc board appendice mother volume            
                   /// sfjp . sapp_dxe = 7.6; //  Dx of the epoxy core of the adc board appendice mother volume            
                   sfjp . sapp_dxz = 0.04; //  Dx of the carbon side shell of the adc board appendice            
                   /// sfjp . sapp_dxz = 0.04; //  Dx of the carbon side shell of the adc board appendice            
                   sfjp . sapp_dy = 0.5; //  Width of the epoxy core of the adc board appendice mother volume            
                   /// sfjp . sapp_dy = 0.5; //  Width of the epoxy core of the adc board appendice mother volume            
                   sfjp . sapp_dz = 1.275; //  Length of the adc board appendice mother volume            
                   /// sfjp . sapp_dz = 1.275; //  Length of the adc board appendice mother volume            
                   sfjp . sapp_py1 = 0.04; //  1. y-Position of the mother colume of the adc board            
                   /// sfjp . sapp_py1 = 0.04; //  1. y-Position of the mother colume of the adc board            
                   sfjp . sapp_py2 = 0.5; //  2. y-Position of the mother colume of the adc board            
                   /// sfjp . sapp_py2 = 0.5; //  2. y-Position of the mother colume of the adc board            
                   sfjp . sapp_py3 = 0.08; //  3. y-Position of the mother colume of the adc board            
                   /// sfjp . sapp_py3 = 0.08; //  3. y-Position of the mother colume of the adc board            
                   sfjp . sfam_dxe = 7.2; //  Dx of the mother volume of the adc board            
                   /// sfjp . sfam_dxe = 7.2; //  Dx of the mother volume of the adc board            
                   sfjp . sfam_dxz = 2.1; //  Dx of the small volume of the adc board            
                   /// sfjp . sfam_dxz = 2.1; //  Dx of the small volume of the adc board            
                   sfjp . sfam_dy = 0.3; //  Width of the mother volume of the adc board            
                   /// sfjp . sfam_dy = 0.3; //  Width of the mother volume of the adc board            
                   sfjp . sfam_dz = 12.4; //  Length of the mother volume of the adc board            
                   /// sfjp . sfam_dz = 12.4; //  Length of the mother volume of the adc board            
                   sfjp . sfam_dzs = 2.15; //  Length of the small volume of the adc board            
                   /// sfjp . sfam_dzs = 2.15; //  Length of the small volume of the adc board            
                   sfjp . sfla_dx = 1.5; //  Dx of the long part of the bus cable linking the modules            
                   /// sfjp . sfla_dx = 1.5; //  Dx of the long part of the bus cable linking the modules            
                   sfjp . sfla_dy = 0.0130; //  Width of the long part of the bus cable linking the modules            
                   /// sfjp . sfla_dy = 0.0130; //  Width of the long part of the bus cable linking the modules            
                   sfjp . sfla_dz = 4.3; //  Length of the long part of the bus cable linking the modules            
                   /// sfjp . sfla_dz = 4.3; //  Length of the long part of the bus cable linking the modules            
                   sfjp . sflb_dz = 7.5; //  Length of the long bus cable            
                   /// sfjp . sflb_dz = 7.5; //  Length of the long bus cable            
                   sfjp . sflc_dz = 0.93; //  Length of the long bus cable on the cb up to the connector            
                   /// sfjp . sflc_dz = 0.93; //  Length of the long bus cable on the cb up to the connector            
                   sfjp . sfeb_dx = 3.89; //  Dx of the big bus elbow            
                   /// sfjp . sfeb_dx = 3.89; //  Dx of the big bus elbow            
                   sfjp . sfeb_dz = 1.5; //  Length of the bus elbow            
                   /// sfjp . sfeb_dz = 1.5; //  Length of the bus elbow            
                   sfjp . sfes_dx = 1.875; //  Dx of the big bus elbow            
                   /// sfjp . sfes_dx = 1.875; //  Dx of the big bus elbow            
                   sfjp . sffk_dxe = 0.4; //  Dx of the horizontal part of the ladder skeleton carbon base            
                   /// sfjp . sffk_dxe = 0.4; //  Dx of the horizontal part of the ladder skeleton carbon base            
                   sfjp . sffk_dy = 0.02; //  Width of the horizontal part of the ladder skeleton carbon base            
                   /// sfjp . sffk_dy = 0.02; //  Width of the horizontal part of the ladder skeleton carbon base            
                   sfjp . sffk_dz = 69.75; //  Lengthof of the horizontal part of the ladder skeleton carbon base            
                   /// sfjp . sffk_dz = 69.75; //  Lengthof of the horizontal part of the ladder skeleton carbon base            
                   sfjp . sffl_dx = 0.6; //  Dx of the tilted part of the ladder            
                   /// sfjp . sffl_dx = 0.6; //  Dx of the tilted part of the ladder            
                   sfjp . sffk_dxz = 5.1; //  Dx of the horizontal part of the kapton film            
                   /// sfjp . sffk_dxz = 5.1; //  Dx of the horizontal part of the kapton film            
                   sfjp . sffk_px = 3.5; //     x-Position of the carbon base under the ladder            
                   /// sfjp . sffk_px = 3.5; //     x-Position of the carbon base under the ladder            
                   sfjp . sffk_py1 = 0.02; //  1. y-Position of the carbon base under the ladder            
                   /// sfjp . sffk_py1 = 0.02; //  1. y-Position of the carbon base under the ladder            
                   sfjp . sffk_py2 = 0.04; //  2. y-Position of the carbon base under the ladder            
                   /// sfjp . sffk_py2 = 0.04; //  2. y-Position of the carbon base under the ladder            
                   sfjp . sfkl_px = 2.55; //     x-Position of the tilted kapton film under the ladder            
                   /// sfjp . sfkl_px = 2.55; //     x-Position of the tilted kapton film under the ladder            
                   sfjp . sfkk_dy = 0.0025; //  Width of the kapton film            
                   /// sfjp . sfkk_dy = 0.0025; //  Width of the kapton film            
                   sfjp . sflu_dz = 49.8; //  Length of the triangular ladder skeleton            
                   /// sfjp . sflu_dz = 49.8; //  Length of the triangular ladder skeleton            
                   sfjp . sflu_h1 = 0.02; //  Height of the triangular ladder skeleton            
                   /// sfjp . sflu_h1 = 0.02; //  Height of the triangular ladder skeleton            
                   sfjp . sflu_bl1 = 0.2; //  Base length  of the triangular ladder skeleton            
                   /// sfjp . sflu_bl1 = 0.2; //  Base length  of the triangular ladder skeleton            
                   sfjp . sfra_dx = 3.76; //          Dx of the hybrid stiffner            
                   /// sfjp . sfra_dx = 3.76; //          Dx of the hybrid stiffner            
                   sfjp . sfra_dy = 0.019; //       Width of the hybrid stiffner            
                   /// sfjp . sfra_dy = 0.019; //       Width of the hybrid stiffner            
                   sfjp . sfra_py = 0.099; //  Y-Position of the hybrid stiffner            
                   /// sfjp . sfra_py = 0.099; //  Y-Position of the hybrid stiffner            
                   sfjp . sfra_dz = 1.0; //      Length of the hybrid stiffner            
                   /// sfjp . sfra_dz = 1.0; //      Length of the hybrid stiffner            
                   sfjp . sfra_pz = 1.1; //  Z-Position of the hybrid stiffner            
                   /// sfjp . sfra_pz = 1.1; //  Z-Position of the hybrid stiffner            
                   sfjp . sfsw_dy = 1.0; //  Width of a single wafer container            
                   /// sfjp . sfsw_dy = 1.0; //  Width of a single wafer container            
                   sfjp . sfsw_dz = 2.25; //  Lengthof of a single wafer container            
                   /// sfjp . sfsw_dz = 2.25; //  Lengthof of a single wafer container            
                   sfjp . sfrs_dx = 0.04; //  Dx of the two supports of the hybrid stiffner            
                   /// sfjp . sfrs_dx = 0.04; //  Dx of the two supports of the hybrid stiffner            
                   sfjp . sfrs_dy = 0.0915; //  Dy of the two supports of the hybrid stiffner            
                   /// sfjp . sfrs_dy = 0.0915; //  Dy of the two supports of the hybrid stiffner            
                   sfjp . sfrs_px = 3.8; //  x-Position of the two supports of the hybrid stiffner            
                   /// sfjp . sfrs_px = 3.8; //  x-Position of the two supports of the hybrid stiffner            
                   sfjp . sfrs_py = 0.0265; //  y-Position of the two supports of the hybrid stiffner            
                   /// sfjp . sfrs_py = 0.0265; //  y-Position of the two supports of the hybrid stiffner            
                   sfjp . sfsm_ll = 2.6; //  Length of the triangular base            
                   /// sfjp . sfsm_ll = 2.6; //  Length of the triangular base            
                   sfjp . sffx_dx = 3.84; //  Dx of the flex            
                   /// sfjp . sffx_dx = 3.84; //  Dx of the flex            
                   sfjp . sffx_dyz = 0.0007; //  Width of the flex            
                   /// sfjp . sffx_dyz = 0.0007; //  Width of the flex            
                   sfjp . sfpi_rmin = 0.15; //  Rmin of the pions            
                   /// sfjp . sfpi_rmin = 0.15; //  Rmin of the pions            
                   sfjp . sfpi_rmax = 0.2; //  Rmax of the pions            
                   /// sfjp . sfpi_rmax = 0.2; //  Rmax of the pions            
                   sfjp . sfpi_px = 3.2; //  X-Position of the four pions             
                   /// sfjp . sfpi_px = 3.2; //  X-Position of the four pions             
                   sfjp . sfpi_py1 = 0.35; //  1. Y-Position of the four pions             
                   /// sfjp . sfpi_py1 = 0.35; //  1. Y-Position of the four pions             
                   sfjp . sfpi_py2 = 0.025; //  2. Y-Position of the four pions             
                   /// sfjp . sfpi_py2 = 0.025; //  2. Y-Position of the four pions             
                   sfjp . sfpi_pz = 0.7; //  Z-Position of the four pions             
                   /// sfjp . sfpi_pz = 0.7; //  Z-Position of the four pions             
                   sfjp . sfpj_dx1 = 0.075; //  1. Dx of the base of the pions            
                   /// sfjp . sfpj_dx1 = 0.075; //  1. Dx of the base of the pions            
                   sfjp . sfpj_dx2 = 0.025; //  2. Dx of the base of the pions            
                   /// sfjp . sfpj_dx2 = 0.025; //  2. Dx of the base of the pions            
                   sfjp . sfpj_dy = 0.3; //  Dy of the base of the pions            
                   /// sfjp . sfpj_dy = 0.3; //  Dy of the base of the pions            
                   sfjp . sfpj_dz = 0.0125; //  Dz of the base of the pions            
                   /// sfjp . sfpj_dz = 0.0125; //  Dz of the base of the pions            
                   sfjp . sfaa_dx = 0.3; //  Dx of the A128C chip            
                   /// sfjp . sfaa_dx = 0.3; //  Dx of the A128C chip            
                   sfjp . sfaa_dy = 0.015; //  Dy of the A128C chip            
                   /// sfjp . sfaa_dy = 0.015; //  Dy of the A128C chip            
                   sfjp . sfaa_dz = 0.4; //  Dz of the A128C chip                   
                   /// sfjp . sfaa_dz = 0.4; //  Dz of the A128C chip                   
                   sfjp . sfaa_px1 = 0.325; //  1. x-=Position of the A128C chips            
                   /// sfjp . sfaa_px1 = 0.325; //  1. x-=Position of the A128C chips            
                   sfjp . sfaa_px2 = 0.65; //  2. x-=Position of the A128C chips            
                   /// sfjp . sfaa_px2 = 0.65; //  2. x-=Position of the A128C chips            
                   sfjp . sfaa_px3 = 0.6; //  3. x-=Position of the A128C chips            
                   /// sfjp . sfaa_px3 = 0.6; //  3. x-=Position of the A128C chips            
                   sfjp . sfaa_pz1 = 1.1; //  1. z-=Position of the A128C chips            
                   /// sfjp . sfaa_pz1 = 1.1; //  1. z-=Position of the A128C chips            
                   sfjp . sfaa_pz2 = 1.0; //  2. z-=Position of the A128C chips            
                   /// sfjp . sfaa_pz2 = 1.0; //  2. z-=Position of the A128C chips            
                   sfjp . sfaa_pz3 = 0.02; //  3. z-=Position of the A128C chips            
                   /// sfjp . sfaa_pz3 = 0.02; //  3. z-=Position of the A128C chips            
                   sfjp . sfsl_dx = 3.75; //  Dx of the strip detector            
                   /// sfjp . sfsl_dx = 3.75; //  Dx of the strip detector            
                   sfjp . sfsl_dy = 0.015; //  Dy of the strip detector            
                   /// sfjp . sfsl_dy = 0.015; //  Dy of the strip detector            
                   sfjp . sfsl_dz = 2.1; //  Dz of the strip detector            
                   /// sfjp . sfsl_dz = 2.1; //  Dz of the strip detector            
                   sfjp . sfsd_dx = 3.65; //  Dx of the sensitive area            
                   /// sfjp . sfsd_dx = 3.65; //  Dx of the sensitive area            
                   sfjp . sfsd_dy = 0.015; //  Dy of the sensitive area            
                   /// sfjp . sfsd_dy = 0.015; //  Dy of the sensitive area            
                   sfjp . sfsd_dz = 2.0; //  Dz of the sensitive area            
                   /// sfjp . sfsd_dz = 2.0; //  Dz of the sensitive area            
                   sfjp . sfla_px = 1.1; //  x-Position of the top flex along the z-axis                
                   /// sfjp . sfla_px = 1.1; //  x-Position of the top flex along the z-axis                
                   sfjp . sfla_py = 1.35; //  y-Position of the top flex along the z-axis            
                   /// sfjp . sfla_py = 1.35; //  y-Position of the top flex along the z-axis            
                   sfjp . sflc_px = 2.3; //  x-Position of the bottom flex along the z-axis            
                   /// sfjp . sflc_px = 2.3; //  x-Position of the bottom flex along the z-axis            
                   sfjp . sflc_py = 0.3; //  y-Position of the bottom flex along the z-axis            
                   /// sfjp . sflc_py = 0.3; //  y-Position of the bottom flex along the z-axis            
                   sfjp . sfes_px = 3.32; //  x-Position of the small elbow bus            
                   /// sfjp . sfes_px = 3.32; //  x-Position of the small elbow bus            
                   sfjp . sfes_py = 1.6; //  y-Position of the small elbow bus            
                   /// sfjp . sfes_py = 1.6; //  y-Position of the small elbow bus            
                   sfjp . sfes_pz = 0.1; //  z-Position of the small elbow bus            
                   /// sfjp . sfes_pz = 0.1; //  z-Position of the small elbow bus            
                   sfjp . sfeb_px = 2.71; //  x-Position of the big elbow bus            
                   /// sfjp . sfeb_px = 2.71; //  x-Position of the big elbow bus            
                   sfjp . sfeb_py = 0.75; //  y-Position of the big elbow bus            
                   /// sfjp . sfeb_py = 0.75; //  y-Position of the big elbow bus            
                   //           
                   sfjp.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfjp_doc        
             ///@{           
                   ++sfjp._index;           
                   sfjp . version = 2; //  Version             
                   /// sfjp . version = 2; //  Version             
                   sfjp . ssrs_rmin = 23.3; //  Width of the side of the small rib (outside structure)            
                   /// sfjp . ssrs_rmin = 23.3; //  Width of the side of the small rib (outside structure)            
                   //           
                   sfjp.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfpb_doc        
             ///@{           
                   ++sfpb._index;           
                   sfpb . hhight = (0.02/tan(54*pi/180)+0.02/(2*tan(pi/5))+0.2)*sin(pi/5); //  haut 1            
                   /// sfpb . hhight = (0.02/tan(54*pi/180)+0.02/(2*tan(pi/5))+0.2)*sin(pi/5); //  haut 1            
                   sfpb . khight = 0.02/sin(54*pi/180); //  haut 2            
                   /// sfpb . khight = 0.02/sin(54*pi/180); //  haut 2            
                   sfpb . hbase = (0.02/tan(63*pi/180)+0.01/tan(27*pi/180)+0.2)*sin(27*pi/180); //  bas 1            
                   /// sfpb . hbase = (0.02/tan(63*pi/180)+0.01/tan(27*pi/180)+0.2)*sin(27*pi/180); //  bas 1            
                   sfpb . kbase = 0.02/sin(63*pi/180); //  bas 2            
                   /// sfpb . kbase = 0.02/sin(63*pi/180); //  bas 2            
                   sfpb . fsize = 0.6/cos(15*pi/180)+0.02*tan(15*pi/180); //  lenght of the side kapton film            
                   /// sfpb . fsize = 0.6/cos(15*pi/180)+0.02*tan(15*pi/180); //  lenght of the side kapton film            
                   sfpb . zcoor = 5.18462095393834410; //  z coord            
                   /// sfpb . zcoor = 5.18462095393834410; //  z coord            
                   //           
                   sfpb.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfpa_doc        
             ///@{           
                   ++sfpa._index;           
                   sfpa . version = 1; //  geometry version            
                   /// sfpa . version = 1; //  geometry version            
                   sfpa . rmin = 21.8; //  mother rmin            
                   /// sfpa . rmin = 21.8; //  mother rmin            
                   sfpa . rmax = 32.; //  mother rmax            
                   /// sfpa . rmax = 32.; //  mother rmax            
                   sfpa . soutrinn = 29.5; //  outer shield cylinder, inner radius            
                   /// sfpa . soutrinn = 29.5; //  outer shield cylinder, inner radius            
                   sfpa . soutrout = 29.52; //  outer shield cylinder, outer radius            
                   /// sfpa . soutrout = 29.52; //  outer shield cylinder, outer radius            
                   sfpa . soutlen = 65.4; //  outer shield cylinder, half length            
                   /// sfpa . soutlen = 65.4; //  outer shield cylinder, half length            
                   sfpa . len = 107.; //  mother Len along the z direction            
                   /// sfpa . len = 107.; //  mother Len along the z direction            
                   sfpa . rad = 23.; //  distance from beam axis to detector center            
                   /// sfpa . rad = 23.; //  distance from beam axis to detector center            
                   sfpa . nssd = 16; //  number of silicon strip detectors             
                   /// sfpa . nssd = 16; //  number of silicon strip detectors             
                   sfpa . dmwid = 7.8; //  detector mother width             
                   /// sfpa . dmwid = 7.8; //  detector mother width             
                   sfpa . dmthk = 2.0; //  detector mother thickness            
                   /// sfpa . dmthk = 2.0; //  detector mother thickness            
                   sfpa . dmlen = 90.; //  detector mother length (detectors + adc board)             
                   /// sfpa . dmlen = 90.; //  detector mother length (detectors + adc board)             
                   sfpa . smwid = 7.5; //  structure mother width            
                   /// sfpa . smwid = 7.5; //  structure mother width            
                   sfpa . smthk = 5.0; //  structure mother thickness            
                   /// sfpa . smthk = 5.0; //  structure mother thickness            
                   sfpa . smlen = 101.9; //  structure mother length             
                   /// sfpa . smlen = 101.9; //  structure mother length             
                   sfpa . sslen = 95./20.; //  length of a subvolume of the structure            
                   /// sfpa . sslen = 95./20.; //  length of a subvolume of the structure            
                   sfpa . wplen = 69.6; //  length of wafer pack            
                   /// sfpa . wplen = 69.6; //  length of wafer pack            
                   sfpa . sdlen = 4.2; //  length of one strip detector (along beam axis)            
                   /// sfpa . sdlen = 4.2; //  length of one strip detector (along beam axis)            
                   sfpa . tilt = 5.0; //  tiling angle (degrees)            
                   /// sfpa . tilt = 5.0; //  tiling angle (degrees)            
                   sfpa . cprad = 0.1; //  cooling pipe outer radius            
                   /// sfpa . cprad = 0.1; //  cooling pipe outer radius            
                   sfpa . cpral = 0.09; //  cooling pipe inner radius            
                   /// sfpa . cpral = 0.09; //  cooling pipe inner radius            
                   sfpa . cfrad = 0.1; //  carbon fiber tube radius (support structure)            
                   /// sfpa . cfrad = 0.1; //  carbon fiber tube radius (support structure)            
                   sfpa . gpthk = -1.0; //  gap between structure mother and detector            
                   /// sfpa . gpthk = -1.0; //  gap between structure mother and detector            
                   sfpa . laddermap.at(0) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(0) = 0; //  presence of ladders            
                   sfpa . laddermap.at(1) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(1) = 0; //  presence of ladders            
                   sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   sfpa . laddermap.at(3) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(3) = 0; //  presence of ladders            
                   sfpa . laddermap.at(4) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(4) = 0; //  presence of ladders            
                   sfpa . laddermap.at(5) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(5) = 0; //  presence of ladders            
                   sfpa . laddermap.at(6) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(6) = 0; //  presence of ladders            
                   sfpa . laddermap.at(7) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(7) = 0; //  presence of ladders            
                   sfpa . laddermap.at(8) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(8) = 0; //  presence of ladders            
                   sfpa . laddermap.at(9) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(9) = 0; //  presence of ladders            
                   sfpa . laddermap.at(10) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(10) = 0; //  presence of ladders            
                   sfpa . laddermap.at(11) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(11) = 0; //  presence of ladders            
                   sfpa . laddermap.at(12) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(12) = 0; //  presence of ladders            
                   sfpa . laddermap.at(13) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(13) = 0; //  presence of ladders            
                   sfpa . laddermap.at(14) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(14) = 0; //  presence of ladders            
                   sfpa . laddermap.at(15) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(15) = 0; //  presence of ladders            
                   sfpa . laddermap.at(16) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(16) = 0; //  presence of ladders            
                   sfpa . laddermap.at(17) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(17) = 0; //  presence of ladders            
                   sfpa . laddermap.at(18) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(18) = 0; //  presence of ladders            
                   sfpa . laddermap.at(19) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(19) = 0; //  presence of ladders            
                   sfpa . ladderangle.at(0) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(0) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(1) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(1) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(2) = 45.0; //  individual angles            
                   ///sfpa . ladderangle.at(2) = 45.0; //  individual angles            
                   sfpa . ladderangle.at(3) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(3) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(4) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(4) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(5) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(5) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(6) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(6) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(7) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(7) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(8) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(8) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(9) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(9) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(10) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(10) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(11) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(11) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(12) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(12) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(13) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(13) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(14) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(14) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(15) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(15) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(16) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(16) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(17) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(17) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(18) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(18) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(19) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(19) = -1.0; //  individual angles            
                   sfpa . laddertilt.at(0) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(0) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(1) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(1) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(2) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(2) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(3) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(3) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(4) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(4) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(5) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(5) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(6) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(6) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(7) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(7) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(8) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(8) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(9) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(9) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(10) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(10) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(11) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(11) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(12) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(12) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(13) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(13) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(14) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(14) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(15) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(15) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(16) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(16) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(17) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(17) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(18) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(18) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(19) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(19) = -1.0; //  individual tilts            
                   sfpa . ladderradius.at(0) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(0) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(1) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(1) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(2) = 23.000; //  individual radii            
                   ///sfpa . ladderradius.at(2) = 23.000; //  individual radii            
                   sfpa . ladderradius.at(3) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(3) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(4) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(4) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(5) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(5) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(6) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(6) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(7) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(7) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(8) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(8) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(9) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(9) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(10) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(10) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(11) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(11) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(12) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(12) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(13) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(13) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(14) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(14) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(15) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(15) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(16) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(16) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(17) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(17) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(18) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(18) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(19) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(19) = -1.0; //  individual radii            
                   //           
                   sfpa.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfpa_doc        
             ///@{           
                   ++sfpa._index;           
                   sfpa . version = 2; //  geometry version            
                   /// sfpa . version = 2; //  geometry version            
                   sfpa . laddermap.at(0) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(0) = 1; //  presence of ladders            
                   sfpa . laddermap.at(1) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(1) = 1; //  presence of ladders            
                   sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   sfpa . laddermap.at(3) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(3) = 0; //  presence of ladders            
                   sfpa . laddermap.at(4) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(4) = 0; //  presence of ladders            
                   sfpa . laddermap.at(5) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(5) = 0; //  presence of ladders            
                   sfpa . laddermap.at(6) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(6) = 0; //  presence of ladders            
                   sfpa . laddermap.at(7) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(7) = 0; //  presence of ladders            
                   sfpa . laddermap.at(8) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(8) = 1; //  presence of ladders            
                   sfpa . laddermap.at(9) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(9) = 1; //  presence of ladders            
                   sfpa . laddermap.at(10) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(10) = 1; //  presence of ladders            
                   sfpa . laddermap.at(11) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(11) = 1; //  presence of ladders            
                   sfpa . laddermap.at(12) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(12) = 1; //  presence of ladders            
                   sfpa . laddermap.at(13) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(13) = 0; //  presence of ladders            
                   sfpa . laddermap.at(14) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(14) = 0; //  presence of ladders            
                   sfpa . laddermap.at(15) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(15) = 0; //  presence of ladders            
                   sfpa . laddermap.at(16) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(16) = 0; //  presence of ladders            
                   sfpa . laddermap.at(17) = 0; //  presence of ladders            
                   ///sfpa . laddermap.at(17) = 0; //  presence of ladders            
                   sfpa . laddermap.at(18) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(18) = 1; //  presence of ladders            
                   sfpa . laddermap.at(19) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(19) = 1; //  presence of ladders            
                   sfpa . ladderangle.at(0) = 90.0; //  individual angles            
                   ///sfpa . ladderangle.at(0) = 90.0; //  individual angles            
                   sfpa . ladderangle.at(1) = 108.3; //  individual angles            
                   ///sfpa . ladderangle.at(1) = 108.3; //  individual angles            
                   sfpa . ladderangle.at(2) = 130.0; //  individual angles            
                   ///sfpa . ladderangle.at(2) = 130.0; //  individual angles            
                   sfpa . ladderangle.at(3) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(3) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(4) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(4) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(5) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(5) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(6) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(6) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(7) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(7) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(8) = 230.0; //  individual angles            
                   ///sfpa . ladderangle.at(8) = 230.0; //  individual angles            
                   sfpa . ladderangle.at(9) = 251.7; //  individual angles            
                   ///sfpa . ladderangle.at(9) = 251.7; //  individual angles            
                   sfpa . ladderangle.at(10) = 270.0; //  individual angles            
                   ///sfpa . ladderangle.at(10) = 270.0; //  individual angles            
                   sfpa . ladderangle.at(11) = 288.3; //  individual angles            
                   ///sfpa . ladderangle.at(11) = 288.3; //  individual angles            
                   sfpa . ladderangle.at(12) = 310.0; //  individual angles            
                   ///sfpa . ladderangle.at(12) = 310.0; //  individual angles            
                   sfpa . ladderangle.at(13) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(13) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(14) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(14) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(15) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(15) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(16) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(16) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(17) = -1.0; //  individual angles            
                   ///sfpa . ladderangle.at(17) = -1.0; //  individual angles            
                   sfpa . ladderangle.at(18) = 50.0; //  individual angles            
                   ///sfpa . ladderangle.at(18) = 50.0; //  individual angles            
                   sfpa . ladderangle.at(19) = 71.7; //  individual angles            
                   ///sfpa . ladderangle.at(19) = 71.7; //  individual angles            
                   sfpa . laddertilt.at(0) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(0) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(1) = -6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(1) = -6.0; //  individual tilts            
                   sfpa . laddertilt.at(2) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(2) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(3) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(3) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(4) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(4) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(5) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(5) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(6) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(6) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(7) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(7) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(8) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(8) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(9) = 6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(9) = 6.0; //  individual tilts            
                   sfpa . laddertilt.at(10) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(10) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(11) = -6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(11) = -6.0; //  individual tilts            
                   sfpa . laddertilt.at(12) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(12) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(13) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(13) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(14) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(14) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(15) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(15) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(16) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(16) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(17) = -1.0; //  individual tilts            
                   ///sfpa . laddertilt.at(17) = -1.0; //  individual tilts            
                   sfpa . laddertilt.at(18) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(18) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(19) = 6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(19) = 6.0; //  individual tilts            
                   sfpa . ladderradius.at(0) = 23.174; //  individual radii            
                   ///sfpa . ladderradius.at(0) = 23.174; //  individual radii            
                   sfpa . ladderradius.at(1) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(1) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(2) = 24.600; //  individual radii            
                   ///sfpa . ladderradius.at(2) = 24.600; //  individual radii            
                   sfpa . ladderradius.at(3) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(3) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(4) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(4) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(5) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(5) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(6) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(6) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(7) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(7) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(8) = 24.600; //  individual radii            
                   ///sfpa . ladderradius.at(8) = 24.600; //  individual radii            
                   sfpa . ladderradius.at(9) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(9) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(10) = 23.174; //  individual radii            
                   ///sfpa . ladderradius.at(10) = 23.174; //  individual radii            
                   sfpa . ladderradius.at(11) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(11) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(12) = 24.600; //  individual radii            
                   ///sfpa . ladderradius.at(12) = 24.600; //  individual radii            
                   sfpa . ladderradius.at(13) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(13) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(14) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(14) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(15) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(15) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(16) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(16) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(17) = -1.0; //  individual radii            
                   ///sfpa . ladderradius.at(17) = -1.0; //  individual radii            
                   sfpa . ladderradius.at(18) = 24.600; //  individual radii            
                   ///sfpa . ladderradius.at(18) = 24.600; //  individual radii            
                   sfpa . ladderradius.at(19) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(19) = 22.800; //  individual radii            
                   //           
                   sfpa.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfpa_doc        
             ///@{           
                   ++sfpa._index;           
                   sfpa . version = 3; //  geometry version            
                   /// sfpa . version = 3; //  geometry version            
                   sfpa . laddermap.at(0) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(0) = 1; //  presence of ladders            
                   sfpa . laddermap.at(1) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(1) = 1; //  presence of ladders            
                   sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   sfpa . laddermap.at(3) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(3) = 1; //  presence of ladders            
                   sfpa . laddermap.at(4) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(4) = 1; //  presence of ladders            
                   sfpa . laddermap.at(5) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(5) = 1; //  presence of ladders            
                   sfpa . laddermap.at(6) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(6) = 1; //  presence of ladders            
                   sfpa . laddermap.at(7) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(7) = 1; //  presence of ladders            
                   sfpa . laddermap.at(8) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(8) = 1; //  presence of ladders            
                   sfpa . laddermap.at(9) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(9) = 1; //  presence of ladders            
                   sfpa . laddermap.at(10) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(10) = 1; //  presence of ladders            
                   sfpa . laddermap.at(11) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(11) = 1; //  presence of ladders            
                   sfpa . laddermap.at(12) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(12) = 1; //  presence of ladders            
                   sfpa . laddermap.at(13) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(13) = 1; //  presence of ladders            
                   sfpa . laddermap.at(14) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(14) = 1; //  presence of ladders            
                   sfpa . laddermap.at(15) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(15) = 1; //  presence of ladders            
                   sfpa . laddermap.at(16) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(16) = 1; //  presence of ladders            
                   sfpa . laddermap.at(17) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(17) = 1; //  presence of ladders            
                   sfpa . laddermap.at(18) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(18) = 1; //  presence of ladders            
                   sfpa . laddermap.at(19) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(19) = 1; //  presence of ladders            
                   sfpa . ladderangle.at(0) = 90.0; //  individual angles            
                   ///sfpa . ladderangle.at(0) = 90.0; //  individual angles            
                   sfpa . ladderangle.at(1) = 108.3; //  individual angles            
                   ///sfpa . ladderangle.at(1) = 108.3; //  individual angles            
                   sfpa . ladderangle.at(2) = 126.6; //  individual angles            
                   ///sfpa . ladderangle.at(2) = 126.6; //  individual angles            
                   sfpa . ladderangle.at(3) = 144.4; //  individual angles            
                   ///sfpa . ladderangle.at(3) = 144.4; //  individual angles            
                   sfpa . ladderangle.at(4) = 162.2; //  individual angles            
                   ///sfpa . ladderangle.at(4) = 162.2; //  individual angles            
                   sfpa . ladderangle.at(5) = 180.0; //  individual angles            
                   ///sfpa . ladderangle.at(5) = 180.0; //  individual angles            
                   sfpa . ladderangle.at(6) = 197.8; //  individual angles            
                   ///sfpa . ladderangle.at(6) = 197.8; //  individual angles            
                   sfpa . ladderangle.at(7) = 215.6; //  individual angles            
                   ///sfpa . ladderangle.at(7) = 215.6; //  individual angles            
                   sfpa . ladderangle.at(8) = 233.4; //  individual angles            
                   ///sfpa . ladderangle.at(8) = 233.4; //  individual angles            
                   sfpa . ladderangle.at(9) = 251.7; //  individual angles            
                   ///sfpa . ladderangle.at(9) = 251.7; //  individual angles            
                   sfpa . ladderangle.at(10) = 270.0; //  individual angles            
                   ///sfpa . ladderangle.at(10) = 270.0; //  individual angles            
                   sfpa . ladderangle.at(11) = 288.3; //  individual angles            
                   ///sfpa . ladderangle.at(11) = 288.3; //  individual angles            
                   sfpa . ladderangle.at(12) = 306.6; //  individual angles            
                   ///sfpa . ladderangle.at(12) = 306.6; //  individual angles            
                   sfpa . ladderangle.at(13) = 324.4; //  individual angles            
                   ///sfpa . ladderangle.at(13) = 324.4; //  individual angles            
                   sfpa . ladderangle.at(14) = 342.2; //  individual angles            
                   ///sfpa . ladderangle.at(14) = 342.2; //  individual angles            
                   sfpa . ladderangle.at(15) = 0.0; //  individual angles            
                   ///sfpa . ladderangle.at(15) = 0.0; //  individual angles            
                   sfpa . ladderangle.at(16) = 17.8; //  individual angles            
                   ///sfpa . ladderangle.at(16) = 17.8; //  individual angles            
                   sfpa . ladderangle.at(17) = 35.6; //  individual angles            
                   ///sfpa . ladderangle.at(17) = 35.6; //  individual angles            
                   sfpa . ladderangle.at(18) = 53.4; //  individual angles            
                   ///sfpa . ladderangle.at(18) = 53.4; //  individual angles            
                   sfpa . ladderangle.at(19) = 71.7; //  individual angles            
                   ///sfpa . ladderangle.at(19) = 71.7; //  individual angles            
                   sfpa . laddertilt.at(0) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(0) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(1) = -6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(1) = -6.0; //  individual tilts            
                   sfpa . laddertilt.at(2) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(2) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(3) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(3) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(4) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(4) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(5) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(5) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(6) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(6) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(7) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(7) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(8) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(8) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(9) = 6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(9) = 6.0; //  individual tilts            
                   sfpa . laddertilt.at(10) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(10) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(11) = -6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(11) = -6.0; //  individual tilts            
                   sfpa . laddertilt.at(12) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(12) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(13) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(13) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(14) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(14) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(15) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(15) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(16) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(16) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(17) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(17) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(18) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(18) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(19) = 6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(19) = 6.0; //  individual tilts            
                   sfpa . ladderradius.at(0) = 23.177; //  individual radii            
                   ///sfpa . ladderradius.at(0) = 23.177; //  individual radii            
                   sfpa . ladderradius.at(1) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(1) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(2) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(2) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(3) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(3) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(4) = 23.800; //  individual radii            
                   ///sfpa . ladderradius.at(4) = 23.800; //  individual radii            
                   sfpa . ladderradius.at(5) = 22.500; //  individual radii            
                   ///sfpa . ladderradius.at(5) = 22.500; //  individual radii            
                   sfpa . ladderradius.at(6) = 23.800; //  individual radii            
                   ///sfpa . ladderradius.at(6) = 23.800; //  individual radii            
                   sfpa . ladderradius.at(7) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(7) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(8) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(8) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(9) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(9) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(10) = 23.177; //  individual radii            
                   ///sfpa . ladderradius.at(10) = 23.177; //  individual radii            
                   sfpa . ladderradius.at(11) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(11) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(12) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(12) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(13) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(13) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(14) = 23.800; //  individual radii            
                   ///sfpa . ladderradius.at(14) = 23.800; //  individual radii            
                   sfpa . ladderradius.at(15) = 22.500; //  individual radii            
                   ///sfpa . ladderradius.at(15) = 22.500; //  individual radii            
                   sfpa . ladderradius.at(16) = 23.800; //  individual radii            
                   ///sfpa . ladderradius.at(16) = 23.800; //  individual radii            
                   sfpa . ladderradius.at(17) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(17) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(18) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(18) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(19) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(19) = 22.800; //  individual radii            
                   //           
                   sfpa.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfpa_doc        
             ///@{           
                   ++sfpa._index;           
                   sfpa . version = 4; //  geometry version            
                   /// sfpa . version = 4; //  geometry version            
                   sfpa . laddermap.at(0) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(0) = 1; //  presence of ladders            
                   sfpa . laddermap.at(1) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(1) = 1; //  presence of ladders            
                   sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   sfpa . laddermap.at(3) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(3) = 1; //  presence of ladders            
                   sfpa . laddermap.at(4) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(4) = 1; //  presence of ladders            
                   sfpa . laddermap.at(5) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(5) = 1; //  presence of ladders            
                   sfpa . laddermap.at(6) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(6) = 1; //  presence of ladders            
                   sfpa . laddermap.at(7) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(7) = 1; //  presence of ladders            
                   sfpa . laddermap.at(8) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(8) = 1; //  presence of ladders            
                   sfpa . laddermap.at(9) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(9) = 1; //  presence of ladders            
                   sfpa . laddermap.at(10) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(10) = 1; //  presence of ladders            
                   sfpa . laddermap.at(11) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(11) = 1; //  presence of ladders            
                   sfpa . laddermap.at(12) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(12) = 1; //  presence of ladders            
                   sfpa . laddermap.at(13) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(13) = 1; //  presence of ladders            
                   sfpa . laddermap.at(14) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(14) = 1; //  presence of ladders            
                   sfpa . laddermap.at(15) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(15) = 1; //  presence of ladders            
                   sfpa . laddermap.at(16) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(16) = 1; //  presence of ladders            
                   sfpa . laddermap.at(17) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(17) = 1; //  presence of ladders            
                   sfpa . laddermap.at(18) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(18) = 1; //  presence of ladders            
                   sfpa . laddermap.at(19) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(19) = 1; //  presence of ladders            
                   sfpa . ladderangle.at(0) = 90.0; //  individual angles            
                   ///sfpa . ladderangle.at(0) = 90.0; //  individual angles            
                   sfpa . ladderangle.at(1) = 108.3; //  individual angles            
                   ///sfpa . ladderangle.at(1) = 108.3; //  individual angles            
                   sfpa . ladderangle.at(2) = 126.6; //  individual angles            
                   ///sfpa . ladderangle.at(2) = 126.6; //  individual angles            
                   sfpa . ladderangle.at(3) = 144.4; //  individual angles            
                   ///sfpa . ladderangle.at(3) = 144.4; //  individual angles            
                   sfpa . ladderangle.at(4) = 162.2; //  individual angles            
                   ///sfpa . ladderangle.at(4) = 162.2; //  individual angles            
                   sfpa . ladderangle.at(5) = 180.0; //  individual angles            
                   ///sfpa . ladderangle.at(5) = 180.0; //  individual angles            
                   sfpa . ladderangle.at(6) = 197.8; //  individual angles            
                   ///sfpa . ladderangle.at(6) = 197.8; //  individual angles            
                   sfpa . ladderangle.at(7) = 215.6; //  individual angles            
                   ///sfpa . ladderangle.at(7) = 215.6; //  individual angles            
                   sfpa . ladderangle.at(8) = 233.4; //  individual angles            
                   ///sfpa . ladderangle.at(8) = 233.4; //  individual angles            
                   sfpa . ladderangle.at(9) = 251.7; //  individual angles            
                   ///sfpa . ladderangle.at(9) = 251.7; //  individual angles            
                   sfpa . ladderangle.at(10) = 270.0; //  individual angles            
                   ///sfpa . ladderangle.at(10) = 270.0; //  individual angles            
                   sfpa . ladderangle.at(11) = 288.3; //  individual angles            
                   ///sfpa . ladderangle.at(11) = 288.3; //  individual angles            
                   sfpa . ladderangle.at(12) = 306.6; //  individual angles            
                   ///sfpa . ladderangle.at(12) = 306.6; //  individual angles            
                   sfpa . ladderangle.at(13) = 324.4; //  individual angles            
                   ///sfpa . ladderangle.at(13) = 324.4; //  individual angles            
                   sfpa . ladderangle.at(14) = 342.2; //  individual angles            
                   ///sfpa . ladderangle.at(14) = 342.2; //  individual angles            
                   sfpa . ladderangle.at(15) = 0.0; //  individual angles            
                   ///sfpa . ladderangle.at(15) = 0.0; //  individual angles            
                   sfpa . ladderangle.at(16) = 17.8; //  individual angles            
                   ///sfpa . ladderangle.at(16) = 17.8; //  individual angles            
                   sfpa . ladderangle.at(17) = 35.6; //  individual angles            
                   ///sfpa . ladderangle.at(17) = 35.6; //  individual angles            
                   sfpa . ladderangle.at(18) = 53.4; //  individual angles            
                   ///sfpa . ladderangle.at(18) = 53.4; //  individual angles            
                   sfpa . ladderangle.at(19) = 71.7; //  individual angles            
                   ///sfpa . ladderangle.at(19) = 71.7; //  individual angles            
                   sfpa . laddertilt.at(0) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(0) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(1) = -6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(1) = -6.0; //  individual tilts            
                   sfpa . laddertilt.at(2) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(2) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(3) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(3) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(4) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(4) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(5) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(5) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(6) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(6) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(7) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(7) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(8) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(8) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(9) = 6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(9) = 6.0; //  individual tilts            
                   sfpa . laddertilt.at(10) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(10) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(11) = -6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(11) = -6.0; //  individual tilts            
                   sfpa . laddertilt.at(12) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(12) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(13) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(13) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(14) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(14) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(15) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(15) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(16) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(16) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(17) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(17) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(18) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(18) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(19) = 6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(19) = 6.0; //  individual tilts            
                   sfpa . ladderradius.at(0) = 23.177; //  individual radii            
                   ///sfpa . ladderradius.at(0) = 23.177; //  individual radii            
                   sfpa . ladderradius.at(1) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(1) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(2) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(2) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(3) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(3) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(4) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(4) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(5) = 22.500; //  individual radii            
                   ///sfpa . ladderradius.at(5) = 22.500; //  individual radii            
                   sfpa . ladderradius.at(6) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(6) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(7) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(7) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(8) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(8) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(9) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(9) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(10) = 23.177; //  individual radii            
                   ///sfpa . ladderradius.at(10) = 23.177; //  individual radii            
                   sfpa . ladderradius.at(11) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(11) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(12) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(12) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(13) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(13) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(14) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(14) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(15) = 22.500; //  individual radii            
                   ///sfpa . ladderradius.at(15) = 22.500; //  individual radii            
                   sfpa . ladderradius.at(16) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(16) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(17) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(17) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(18) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(18) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(19) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(19) = 22.800; //  individual radii            
                   //           
                   sfpa.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup sfpa_doc        
             ///@{           
                   ++sfpa._index;           
                   sfpa . version = 5; //  geometry version            
                   /// sfpa . version = 5; //  geometry version            
                   sfpa . laddermap.at(0) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(0) = 1; //  presence of ladders            
                   sfpa . laddermap.at(1) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(1) = 1; //  presence of ladders            
                   sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(2) = 1; //  presence of ladders            
                   sfpa . laddermap.at(3) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(3) = 1; //  presence of ladders            
                   sfpa . laddermap.at(4) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(4) = 1; //  presence of ladders            
                   sfpa . laddermap.at(5) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(5) = 1; //  presence of ladders            
                   sfpa . laddermap.at(6) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(6) = 1; //  presence of ladders            
                   sfpa . laddermap.at(7) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(7) = 1; //  presence of ladders            
                   sfpa . laddermap.at(8) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(8) = 1; //  presence of ladders            
                   sfpa . laddermap.at(9) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(9) = 1; //  presence of ladders            
                   sfpa . laddermap.at(10) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(10) = 1; //  presence of ladders            
                   sfpa . laddermap.at(11) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(11) = 1; //  presence of ladders            
                   sfpa . laddermap.at(12) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(12) = 1; //  presence of ladders            
                   sfpa . laddermap.at(13) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(13) = 1; //  presence of ladders            
                   sfpa . laddermap.at(14) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(14) = 1; //  presence of ladders            
                   sfpa . laddermap.at(15) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(15) = 1; //  presence of ladders            
                   sfpa . laddermap.at(16) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(16) = 1; //  presence of ladders            
                   sfpa . laddermap.at(17) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(17) = 1; //  presence of ladders            
                   sfpa . laddermap.at(18) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(18) = 1; //  presence of ladders            
                   sfpa . laddermap.at(19) = 1; //  presence of ladders            
                   ///sfpa . laddermap.at(19) = 1; //  presence of ladders            
                   sfpa . ladderangle.at(0) = 90.0; //  individual angles            
                   ///sfpa . ladderangle.at(0) = 90.0; //  individual angles            
                   sfpa . ladderangle.at(1) = 108.3; //  individual angles            
                   ///sfpa . ladderangle.at(1) = 108.3; //  individual angles            
                   sfpa . ladderangle.at(2) = 126.6; //  individual angles            
                   ///sfpa . ladderangle.at(2) = 126.6; //  individual angles            
                   sfpa . ladderangle.at(3) = 144.4; //  individual angles            
                   ///sfpa . ladderangle.at(3) = 144.4; //  individual angles            
                   sfpa . ladderangle.at(4) = 162.2; //  individual angles            
                   ///sfpa . ladderangle.at(4) = 162.2; //  individual angles            
                   sfpa . ladderangle.at(5) = 180.0; //  individual angles            
                   ///sfpa . ladderangle.at(5) = 180.0; //  individual angles            
                   sfpa . ladderangle.at(6) = 197.8; //  individual angles            
                   ///sfpa . ladderangle.at(6) = 197.8; //  individual angles            
                   sfpa . ladderangle.at(7) = 215.6; //  individual angles            
                   ///sfpa . ladderangle.at(7) = 215.6; //  individual angles            
                   sfpa . ladderangle.at(8) = 233.4; //  individual angles            
                   ///sfpa . ladderangle.at(8) = 233.4; //  individual angles            
                   sfpa . ladderangle.at(9) = 251.7; //  individual angles            
                   ///sfpa . ladderangle.at(9) = 251.7; //  individual angles            
                   sfpa . ladderangle.at(10) = 270.0; //  individual angles            
                   ///sfpa . ladderangle.at(10) = 270.0; //  individual angles            
                   sfpa . ladderangle.at(11) = 288.3; //  individual angles            
                   ///sfpa . ladderangle.at(11) = 288.3; //  individual angles            
                   sfpa . ladderangle.at(12) = 306.6; //  individual angles            
                   ///sfpa . ladderangle.at(12) = 306.6; //  individual angles            
                   sfpa . ladderangle.at(13) = 324.4; //  individual angles            
                   ///sfpa . ladderangle.at(13) = 324.4; //  individual angles            
                   sfpa . ladderangle.at(14) = 342.2; //  individual angles            
                   ///sfpa . ladderangle.at(14) = 342.2; //  individual angles            
                   sfpa . ladderangle.at(15) = 0.0; //  individual angles            
                   ///sfpa . ladderangle.at(15) = 0.0; //  individual angles            
                   sfpa . ladderangle.at(16) = 17.8; //  individual angles            
                   ///sfpa . ladderangle.at(16) = 17.8; //  individual angles            
                   sfpa . ladderangle.at(17) = 35.6; //  individual angles            
                   ///sfpa . ladderangle.at(17) = 35.6; //  individual angles            
                   sfpa . ladderangle.at(18) = 53.4; //  individual angles            
                   ///sfpa . ladderangle.at(18) = 53.4; //  individual angles            
                   sfpa . ladderangle.at(19) = 71.7; //  individual angles            
                   ///sfpa . ladderangle.at(19) = 71.7; //  individual angles            
                   sfpa . laddertilt.at(0) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(0) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(1) = -6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(1) = -6.0; //  individual tilts            
                   sfpa . laddertilt.at(2) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(2) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(3) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(3) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(4) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(4) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(5) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(5) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(6) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(6) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(7) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(7) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(8) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(8) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(9) = 6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(9) = 6.0; //  individual tilts            
                   sfpa . laddertilt.at(10) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(10) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(11) = -6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(11) = -6.0; //  individual tilts            
                   sfpa . laddertilt.at(12) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(12) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(13) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(13) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(14) = -7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(14) = -7.0; //  individual tilts            
                   sfpa . laddertilt.at(15) = 0.0; //  individual tilts            
                   ///sfpa . laddertilt.at(15) = 0.0; //  individual tilts            
                   sfpa . laddertilt.at(16) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(16) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(17) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(17) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(18) = 7.0; //  individual tilts            
                   ///sfpa . laddertilt.at(18) = 7.0; //  individual tilts            
                   sfpa . laddertilt.at(19) = 6.0; //  individual tilts            
                   ///sfpa . laddertilt.at(19) = 6.0; //  individual tilts            
                   sfpa . ladderradius.at(0) = 23.177; //  individual radii            
                   ///sfpa . ladderradius.at(0) = 23.177; //  individual radii            
                   sfpa . ladderradius.at(1) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(1) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(2) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(2) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(3) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(3) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(4) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(4) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(5) = 22.300; //  individual radii            
                   ///sfpa . ladderradius.at(5) = 22.300; //  individual radii            
                   sfpa . ladderradius.at(6) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(6) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(7) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(7) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(8) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(8) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(9) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(9) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(10) = 23.177; //  individual radii            
                   ///sfpa . ladderradius.at(10) = 23.177; //  individual radii            
                   sfpa . ladderradius.at(11) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(11) = 22.800; //  individual radii            
                   sfpa . ladderradius.at(12) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(12) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(13) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(13) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(14) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(14) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(15) = 22.500; //  individual radii            
                   ///sfpa . ladderradius.at(15) = 22.500; //  individual radii            
                   sfpa . ladderradius.at(16) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(16) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(17) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(17) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(18) = 22.600; //  individual radii            
                   ///sfpa . ladderradius.at(18) = 22.600; //  individual radii            
                   sfpa . ladderradius.at(19) = 22.800; //  individual radii            
                   ///sfpa . ladderradius.at(19) = 22.800; //  individual radii            
                   //           
                   sfpa.fill();           
             ///@}        
             //        
             /// USE ssdp _index=1;        
             ssdp.Use();        
             configa = mod(ssdp.config   ,10);        
             configb = mod(ssdp.config/10,10);        
             /// USE sfpa version=configa ;        
             sfpa.Use("version",(Int_t)configa );        
             /// USE sfjp version=2 ;        
             sfjp.Use("version",(Int_t)2 );        
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
             /// Component Si	a=28.08	z=14	w=0.6*1*28./60.        
             /// Component O	a=16	z=8	w=0.6*2*16./60. + 0.4*4*16./174.        
             /// Component C	a=12	z=6	w=0.4*8*12./174.        
             /// Component H	a=1	z=1	w=0.4*14*1./174.        
             /// Mixture G5 dens=0.85        
             {  AgMaterial &mix = AgMaterial::Get("G5");           
                   mix.Component("Si",28.08,14,0.6*1*28./60.);           
                   mix.Component("O",16,8,0.6*2*16./60. + 0.4*4*16./174.);           
                   mix.Component("C",12,6,0.4*8*12./174.);           
                   mix.Component("H",1,1,0.4*14*1./174.);           
                   mix.par("dens")=0.85;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
             /// Component O	a=16	z=8	w=2*16./100.        
             /// Component C	a=12	z=6	w=5*12./100.        
             /// Component H	a=1	z=1	w=8*1.0/100.        
             /// Mixture DELRIN dens=1.2        
             {  AgMaterial &mix = AgMaterial::Get("Delrin");           
                   mix.Component("O",16,8,2*16./100.);           
                   mix.Component("C",12,6,5*12./100.);           
                   mix.Component("H",1,1,8*1.0/100.);           
                   mix.par("dens")=1.2;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
             if ( ssdp.placement==1 )        
             {           
                   _create = AgCreate("SFMO");           
                   {              
                         AgShape myshape; // undefined shape              
                         ///Create SFMO              
                         Create("SFMO");               
                   }           
                   { AgPlacement place = AgPlacement("SFMO","SVTT");              
                         /// Add daughter volume SFMO to mother SVTT              
                         _stacker -> Position( AgBlock::Find("SFMO"), place );              
                   } // end placement of SFMO           
             }        
             else        
             {           
                   _create = AgCreate("SFMO");           
                   {              
                         AgShape myshape; // undefined shape              
                         ///Create SFMO              
                         Create("SFMO");               
                   }           
                   { AgPlacement place = AgPlacement("SFMO","CAVE");              
                         /// Add daughter volume SFMO to mother CAVE              
                         place.par("only")=AgPlacement::kOnly;              
                         /// Overlap: agplacement::konly              
                         _stacker -> Position( AgBlock::Find("SFMO"), place );              
                   } // end placement of SFMO           
             }        
       }; // SisdGeo6     
 }; // namespace SisdGeo6  
 