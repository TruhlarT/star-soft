#include "SisdGeo1.h"  
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
 namespace SISDGEO1 // $NMSPC  
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
          ///Float_t config;     
          ///Int_t placement;     
          ///Int_t _index;     
          //     
          Ssdp_t ssdp;     
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
          ///Float_t version;     
          ///Float_t rmin;     
          ///Float_t rmax;     
          ///Float_t len;     
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
          ///@addtogroup SisdGeo1_vars     
          ///@{        
                Int_t ilad,iwaf,jwaf,nc;        
                //        
                /// Int_t ilad,iwaf,jwaf,nc        
          ///@}     
          ///@addtogroup SisdGeo1_vars     
          ///@{        
                Float_t wafpcklen,dthk,radtilt,ang;        
                //        
                /// Float_t wafpcklen,dthk,radtilt,ang        
          ///@}     
          ///@addtogroup SisdGeo1_vars     
          ///@{        
                Float_t essai,hight,lng,leng,yoffset;        
                //        
                /// Float_t essai,hight,lng,leng,yoffset        
          ///@}     
          ///@addtogroup SisdGeo1_vars     
          ///@{        
                Float_t zs1,zs2,zs3,zs4,zs5,ys1,ys2,ys3,ys4;        
                //        
                /// Float_t zs1,zs2,zs3,zs4,zs5,ys1,ys2,ys3,ys4        
          ///@}     
       SisdGeo1::SisdGeo1()     
         : AgModule("SisdGeo1","  is the Silicon Strip Detector ")     
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
                      dthk=sfpa.smthk+sfpa.gpthk;           
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
                      zs1=49.8+0.95+2.5/2.+0.2;           
                      zs2=49.8+0.95+0.5/2.+0.2;           
                      zs3=49.8+0.95+0.5+0.2+2.5/2;           
                      zs4=49.8+0.95+0.5+0.2+2.5+5.05/2.;           
                      zs5=57.5;           
                      ys1=19.1;           
                      ys2=18.1;           
                      ys3=15.945;           
                      ys4=17.0;           
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
                            place.TranslateZ(-zs1);              
                            /// Translate z = -zs1              
                            _stacker -> Position( AgBlock::Find("SSST"), place );              
                      } // end placement of SSST           
                      { AgPlacement place = AgPlacement("SSST","SFMO");              
                            /// Add daughter volume SSST to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(zs1);              
                            /// Translate z = zs1              
                            _stacker -> Position( AgBlock::Find("SSST"), place );              
                      } // end placement of SSST           
                      { AgPlacement place = AgPlacement("SSST","SFMO");              
                            /// Add daughter volume SSST to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-zs1);              
                            /// Translate z = -zs1              
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
                            place.TranslateZ(zs1);              
                            /// Translate z = zs1              
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
                            place.TranslateZ(-zs2);              
                            /// Translate z = -zs2              
                            _stacker -> Position( AgBlock::Find("SSSS"), place );              
                      } // end placement of SSSS           
                      { AgPlacement place = AgPlacement("SSSS","SFMO");              
                            /// Add daughter volume SSSS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(zs2);              
                            /// Translate z = zs2              
                            _stacker -> Position( AgBlock::Find("SSSS"), place );              
                      } // end placement of SSSS           
                      { AgPlacement place = AgPlacement("SSSS","SFMO");              
                            /// Add daughter volume SSSS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-zs2);              
                            /// Translate z = -zs2              
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
                            place.TranslateZ(zs2);              
                            /// Translate z = zs2              
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
                            place.TranslateZ(-zs1);              
                            /// Translate z = -zs1              
                            _stacker -> Position( AgBlock::Find("SSRT"), place );              
                      } // end placement of SSRT           
                      { AgPlacement place = AgPlacement("SSRT","SFMO");              
                            /// Add daughter volume SSRT to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(zs1);              
                            /// Translate z = zs1              
                            _stacker -> Position( AgBlock::Find("SSRT"), place );              
                      } // end placement of SSRT           
                      { AgPlacement place = AgPlacement("SSRT","SFMO");              
                            /// Add daughter volume SSRT to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-zs1);              
                            /// Translate z = -zs1              
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
                            place.TranslateZ(zs1);              
                            /// Translate z = zs1              
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
                            place.TranslateZ(-zs2);              
                            /// Translate z = -zs2              
                            _stacker -> Position( AgBlock::Find("SSRS"), place );              
                      } // end placement of SSRS           
                      { AgPlacement place = AgPlacement("SSRS","SFMO");              
                            /// Add daughter volume SSRS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(zs2);              
                            /// Translate z = zs2              
                            _stacker -> Position( AgBlock::Find("SSRS"), place );              
                      } // end placement of SSRS           
                      { AgPlacement place = AgPlacement("SSRS","SFMO");              
                            /// Add daughter volume SSRS to mother SFMO              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-zs2);              
                            /// Translate z = -zs2              
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
                            place.TranslateZ(zs2);              
                            /// Translate z = zs2              
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
                      { AgPlacement place = AgPlacement("SSLB","SFMO");              
                            /// Add daughter volume SSLB to mother SFMO              
                            place.TranslateX(ys1);              
                            /// Translate x = ys1              
                            place.TranslateY(ys1);              
                            /// Translate y = ys1              
                            place.TranslateZ(-zs3);              
                            /// Translate z = -zs3              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(-ys1);              
                            /// Translate x = -ys1              
                            place.TranslateY(-ys1);              
                            /// Translate y = -ys1              
                            place.TranslateZ(-zs3);              
                            /// Translate z = -zs3              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(ys1);              
                            /// Translate x = ys1              
                            place.TranslateY(-ys1);              
                            /// Translate y = -ys1              
                            place.TranslateZ(-zs3);              
                            /// Translate z = -zs3              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            place.TranslateX(-ys1);              
                            /// Translate x = -ys1              
                            place.TranslateY(ys1);              
                            /// Translate y = ys1              
                            place.TranslateZ(-zs3);              
                            /// Translate z = -zs3              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            place.TranslateX(ys1);              
                            /// Translate x = ys1              
                            place.TranslateY(ys1);              
                            /// Translate y = ys1              
                            place.TranslateZ(zs3);              
                            /// Translate z = zs3              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(-ys1);              
                            /// Translate x = -ys1              
                            place.TranslateY(-ys1);              
                            /// Translate y = -ys1              
                            place.TranslateZ(zs3);              
                            /// Translate z = zs3              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(ys1);              
                            /// Translate x = ys1              
                            place.TranslateY(-ys1);              
                            /// Translate y = -ys1              
                            place.TranslateZ(zs3);              
                            /// Translate z = zs3              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            place.TranslateX(-ys1);              
                            /// Translate x = -ys1              
                            place.TranslateY(ys1);              
                            /// Translate y = ys1              
                            place.TranslateZ(zs3);              
                            /// Translate z = zs3              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("SSLB"), place );              
                      } // end placement of SSLB           
                      _create = AgCreate("SSLT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SSLT              
                            Create("SSLT");               
                      }           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(ys2);              
                            /// Translate x = ys2              
                            place.TranslateY(ys2);              
                            /// Translate y = ys2              
                            place.TranslateZ(-zs4);              
                            /// Translate z = -zs4              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(-ys2);              
                            /// Translate x = -ys2              
                            place.TranslateY(-ys2);              
                            /// Translate y = -ys2              
                            place.TranslateZ(-zs4);              
                            /// Translate z = -zs4              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(ys2);              
                            /// Translate x = ys2              
                            place.TranslateY(-ys2);              
                            /// Translate y = -ys2              
                            place.TranslateZ(-zs4);              
                            /// Translate z = -zs4              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(-ys2);              
                            /// Translate x = -ys2              
                            place.TranslateY(ys2);              
                            /// Translate y = ys2              
                            place.TranslateZ(-zs4);              
                            /// Translate z = -zs4              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(ys2);              
                            /// Translate x = ys2              
                            place.TranslateY(ys2);              
                            /// Translate y = ys2              
                            place.TranslateZ(zs4);              
                            /// Translate z = zs4              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(-ys2);              
                            /// Translate x = -ys2              
                            place.TranslateY(-ys2);              
                            /// Translate y = -ys2              
                            place.TranslateZ(zs4);              
                            /// Translate z = zs4              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(ys2);              
                            /// Translate x = ys2              
                            place.TranslateY(-ys2);              
                            /// Translate y = -ys2              
                            place.TranslateZ(zs4);              
                            /// Translate z = zs4              
                            _stacker -> Position( AgBlock::Find("SSLT"), place );              
                      } // end placement of SSLT           
                      { AgPlacement place = AgPlacement("SSLT","SFMO");              
                            /// Add daughter volume SSLT to mother SFMO              
                            place.TranslateX(-ys2);              
                            /// Translate x = -ys2              
                            place.TranslateY(ys2);              
                            /// Translate y = ys2              
                            place.TranslateZ(zs4);              
                            /// Translate z = zs4              
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
                            place.TranslateX(ys3);              
                            /// Translate x = ys3              
                            place.TranslateY(ys3);              
                            /// Translate y = ys3              
                            place.TranslateZ(zs5);              
                            /// Translate z = zs5              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            place.TranslateX(-ys3);              
                            /// Translate x = -ys3              
                            place.TranslateY(-ys3);              
                            /// Translate y = -ys3              
                            place.TranslateZ(zs5);              
                            /// Translate z = zs5              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            place.TranslateX(ys3);              
                            /// Translate x = ys3              
                            place.TranslateY(-ys3);              
                            /// Translate y = -ys3              
                            place.TranslateZ(zs5);              
                            /// Translate z = zs5              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(-ys3);              
                            /// Translate x = -ys3              
                            place.TranslateY(ys3);              
                            /// Translate y = ys3              
                            place.TranslateZ(zs5);              
                            /// Translate z = zs5              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(ys3);              
                            /// Translate x = ys3              
                            place.TranslateY(ys3);              
                            /// Translate y = ys3              
                            place.TranslateZ(-zs5);              
                            /// Translate z = -zs5              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            place.TranslateX(-ys3);              
                            /// Translate x = -ys3              
                            place.TranslateY(-ys3);              
                            /// Translate y = -ys3              
                            place.TranslateZ(-zs5);              
                            /// Translate z = -zs5              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            place.TranslateX(ys3);              
                            /// Translate x = ys3              
                            place.TranslateY(-ys3);              
                            /// Translate y = -ys3              
                            place.TranslateZ(-zs5);              
                            /// Translate z = -zs5              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(-ys3);              
                            /// Translate x = -ys3              
                            place.TranslateY(ys3);              
                            /// Translate y = ys3              
                            place.TranslateZ(-zs5);              
                            /// Translate z = -zs5              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(ys4);              
                            /// Translate x = ys4              
                            place.TranslateY(ys4);              
                            /// Translate y = ys4              
                            place.TranslateZ(zs5);              
                            /// Translate z = zs5              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            place.TranslateX(-ys4);              
                            /// Translate x = -ys4              
                            place.TranslateY(-ys4);              
                            /// Translate y = -ys4              
                            place.TranslateZ(zs5);              
                            /// Translate z = zs5              
                            place.AlphaZ(135.);              
                            /// Rotate: AlphaZ = 135.              
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
                            place.TranslateX(ys4);              
                            /// Translate x = ys4              
                            place.TranslateY(-ys4);              
                            /// Translate y = -ys4              
                            place.TranslateZ(zs5);              
                            /// Translate z = zs5              
                            place.AlphaZ(-135.);              
                            /// Rotate: AlphaZ = -135.              
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
                            place.TranslateX(-ys4);              
                            /// Translate x = -ys4              
                            place.TranslateY(ys4);              
                            /// Translate y = ys4              
                            place.TranslateZ(zs5);              
                            /// Translate z = zs5              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(ys4);              
                            /// Translate x = ys4              
                            place.TranslateY(ys4);              
                            /// Translate y = ys4              
                            place.TranslateZ(-zs5);              
                            /// Translate z = -zs5              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            place.TranslateX(-ys4);              
                            /// Translate x = -ys4              
                            place.TranslateY(-ys4);              
                            /// Translate y = -ys4              
                            place.TranslateZ(-zs5);              
                            /// Translate z = -zs5              
                            place.AlphaZ(135.);              
                            /// Rotate: AlphaZ = 135.              
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
                            place.TranslateX(ys4);              
                            /// Translate x = ys4              
                            place.TranslateY(-ys4);              
                            /// Translate y = -ys4              
                            place.TranslateZ(-zs5);              
                            /// Translate z = -zs5              
                            place.AlphaZ(-135.);              
                            /// Rotate: AlphaZ = -135.              
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
                            place.TranslateX(-ys4);              
                            /// Translate x = -ys4              
                            place.TranslateY(ys4);              
                            /// Translate y = ys4              
                            place.TranslateZ(-zs5);              
                            /// Translate z = -zs5              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            attr.par("seen")=0;              
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
                            shape.par("dy")=1.;              
                            shape.par("dz")=2.25;              
                            /// Shape Bbox dx=sfpa.dmwid/2 dy=1. dz=2.25               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SFSW;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("SFSD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFSD              
                            Create("SFSD");               
                      }           
                      { AgPlacement place = AgPlacement("SFSD","SFSW");              
                            /// Add daughter volume SFSD to mother SFSW              
                            _stacker -> Position( AgBlock::Find("SFSD"), place );              
                      } // end placement of SFSD           
                      _create = AgCreate("SFRA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFRA              
                            Create("SFRA");               
                      }           
                      { AgPlacement place = AgPlacement("SFRA","SFSW");              
                            /// Add daughter volume SFRA to mother SFSW              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.099);              
                            /// Translate y = 0.099              
                            place.TranslateZ(1.1);              
                            /// Translate z = 1.1              
                            _stacker -> Position( AgBlock::Find("SFRA"), place );              
                      } // end placement of SFRA           
                      { AgPlacement place = AgPlacement("SFRA","SFSW");              
                            /// Add daughter volume SFRA to mother SFSW              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.099);              
                            /// Translate y = 0.099              
                            place.TranslateZ(-1.1);              
                            /// Translate z = -1.1              
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
                            place.TranslateX(3.8);              
                            /// Translate x = 3.8              
                            place.TranslateY(0.0265);              
                            /// Translate y = 0.0265              
                            place.TranslateZ(1.1);              
                            /// Translate z = 1.1              
                            _stacker -> Position( AgBlock::Find("SFRS"), place );              
                      } // end placement of SFRS           
                      { AgPlacement place = AgPlacement("SFRS","SFSW");              
                            /// Add daughter volume SFRS to mother SFSW              
                            place.TranslateX(3.8);              
                            /// Translate x = 3.8              
                            place.TranslateY(0.0265);              
                            /// Translate y = 0.0265              
                            place.TranslateZ(-1.1);              
                            /// Translate z = -1.1              
                            _stacker -> Position( AgBlock::Find("SFRS"), place );              
                      } // end placement of SFRS           
                      { AgPlacement place = AgPlacement("SFRS","SFSW");              
                            /// Add daughter volume SFRS to mother SFSW              
                            place.TranslateX(-3.8);              
                            /// Translate x = -3.8              
                            place.TranslateY(0.0265);              
                            /// Translate y = 0.0265              
                            place.TranslateZ(1.1);              
                            /// Translate z = 1.1              
                            _stacker -> Position( AgBlock::Find("SFRS"), place );              
                      } // end placement of SFRS           
                      { AgPlacement place = AgPlacement("SFRS","SFSW");              
                            /// Add daughter volume SFRS to mother SFSW              
                            place.TranslateX(-3.8);              
                            /// Translate x = -3.8              
                            place.TranslateY(0.0265);              
                            /// Translate y = 0.0265              
                            place.TranslateZ(-1.1);              
                            /// Translate z = -1.1              
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
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.099+0.0190+0.0007);              
                            /// Translate y = 0.099+0.0190+0.0007              
                            place.TranslateZ(1.1);              
                            /// Translate z = 1.1              
                            _stacker -> Position( AgBlock::Find("SFFX"), place );              
                      } // end placement of SFFX           
                      { AgPlacement place = AgPlacement("SFFX","SFSW");              
                            /// Add daughter volume SFFX to mother SFSW              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(0.099+0.0190+0.0007);              
                            /// Translate y = 0.099+0.0190+0.0007              
                            place.TranslateZ(-1.1);              
                            /// Translate z = -1.1              
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
                            place.TranslateX(3.2);              
                            /// Translate x = 3.2              
                            place.TranslateY(0.099+0.019+0.35-0.0250);              
                            /// Translate y = 0.099+0.019+0.35-0.0250              
                            place.TranslateZ(0.1+0.6);              
                            /// Translate z = 0.1+0.6              
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
                            place.TranslateX(-3.2);              
                            /// Translate x = -3.2              
                            place.TranslateY(0.099+0.019+0.35-0.0250);              
                            /// Translate y = 0.099+0.019+0.35-0.0250              
                            place.TranslateZ(0.7);              
                            /// Translate z = 0.7              
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
                            place.TranslateX(3.2);              
                            /// Translate x = 3.2              
                            place.TranslateY(0.099+0.019+0.35-0.0250);              
                            /// Translate y = 0.099+0.019+0.35-0.0250              
                            place.TranslateZ(-0.7);              
                            /// Translate z = -0.7              
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
                            place.TranslateX(-3.2);              
                            /// Translate x = -3.2              
                            place.TranslateY(0.099+0.019+0.35-0.0250);              
                            /// Translate y = 0.099+0.019+0.35-0.0250              
                            place.TranslateZ(-0.7);              
                            /// Translate z = -0.7              
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
                            place.TranslateX(-0.325-0.3);              
                            /// Translate x = -0.325-0.3              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(1.1+1.0-0.02-0.4);              
                            /// Translate z = 1.1+1.0-0.02-0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-0.325-0.3-0.65-0.6);              
                            /// Translate x = -0.325-0.3-0.65-0.6              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(1.1+1.0-0.02-0.4);              
                            /// Translate z = 1.1+1.0-0.02-0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-0.325-0.3-0.65-0.6-0.65-0.6);              
                            /// Translate x = -0.325-0.3-0.65-0.6-0.65-0.6              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(1.1+1.0-0.02-0.4);              
                            /// Translate z = 1.1+1.0-0.02-0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+0.325+0.3);              
                            /// Translate x = +0.325+0.3              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(1.1+1.0-0.02-0.4);              
                            /// Translate z = 1.1+1.0-0.02-0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+0.325+0.3+0.65+0.6);              
                            /// Translate x = +0.325+0.3+0.65+0.6              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(1.1+1.0-0.02-0.4);              
                            /// Translate z = 1.1+1.0-0.02-0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+0.325+0.3+0.65+0.6+0.65+0.6);              
                            /// Translate x = +0.325+0.3+0.65+0.6+0.65+0.6              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(1.1+1.0-0.02-0.4);              
                            /// Translate z = 1.1+1.0-0.02-0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-0.325-0.3);              
                            /// Translate x = -0.325-0.3              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(-1.1-1.0+0.02+0.4);              
                            /// Translate z = -1.1-1.0+0.02+0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-0.325-0.3-0.65-0.6);              
                            /// Translate x = -0.325-0.3-0.65-0.6              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(-1.1-1.0+0.02+0.4);              
                            /// Translate z = -1.1-1.0+0.02+0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(-0.325-0.3-0.65-0.6-0.65-0.6);              
                            /// Translate x = -0.325-0.3-0.65-0.6-0.65-0.6              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(-1.1-1.0+0.02+0.4);              
                            /// Translate z = -1.1-1.0+0.02+0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+0.325+0.3);              
                            /// Translate x = +0.325+0.3              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(-1.1-1.0+0.02+0.4);              
                            /// Translate z = -1.1-1.0+0.02+0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+0.325+0.3+0.65+0.6);              
                            /// Translate x = +0.325+0.3+0.65+0.6              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(-1.1-1.0+0.02+0.4);              
                            /// Translate z = -1.1-1.0+0.02+0.4              
                            _stacker -> Position( AgBlock::Find("SFAA"), place );              
                      } // end placement of SFAA           
                      { AgPlacement place = AgPlacement("SFAA","SFSW");              
                            /// Add daughter volume SFAA to mother SFSW              
                            place.TranslateX(+0.325+0.3+0.65+0.6+0.65+0.6);              
                            /// Translate x = +0.325+0.3+0.65+0.6+0.65+0.6              
                            place.TranslateY(0.099+0.0190+0.0007*2+0.0150);              
                            /// Translate y = 0.099+0.0190+0.0007*2+0.0150              
                            place.TranslateZ(-1.1-1.0+0.02+0.4);              
                            /// Translate z = -1.1-1.0+0.02+0.4              
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
                            shape.par("dx")=3.76;              
                            shape.par("dy")=0.019;              
                            shape.par("dz")=1.;              
                            /// Shape Bbox dx=3.76 dy=0.019 dz=1.               
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
                            shape.par("dx")=0.04;              
                            shape.par("dy")=0.0915;              
                            shape.par("dz")=1.;              
                            /// Shape Bbox dx=0.04 dy=0.0915 dz=1.               
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
                            shape.par("dx")=3.84;              
                            shape.par("dy")=0.0007;              
                            shape.par("dz")=1.;              
                            /// Shape Bbox dx=3.84 dy=0.0007 dz=1.               
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
                            shape.par("dx")=0.3;              
                            shape.par("dy")=0.015;              
                            shape.par("dz")=0.4;              
                            /// Shape Bbox dx=0.3 dy=0.015 dz=0.4               
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
                            shape.par("rmin")=0.15/2;              
                            shape.par("rmax")=0.2/2;              
                            shape.par("dz")=0.35;              
                            /// Shape Tube rmin=0.15/2 rmax=0.2/2 dz=0.35               
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
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(-0.35+0.0125);              
                            /// Translate z = -0.35+0.0125              
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
                            shape.par("rmin")=0.075+0.025;              
                            shape.par("rmax")=0.3;              
                            shape.par("dz")=0.0125;              
                            /// Shape Tube rmin=0.075+0.025 rmax=0.3 dz=0.0125               
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
                            shape.par("dx")=3.75;              
                            shape.par("dy")=0.015;              
                            shape.par("dz")=2.1;              
                            /// Shape Bbox dx=3.75 dy=0.015 dz=2.1               
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
                      yoffset=-1.7;           
                      _create = AgCreate("SFLT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create SFLT              
                            Create("SFLT");               
                      }           
                      hight = 2.6*tan(54*pi/180)-sfpb.hhight/tan(pi/5)-0.02;           
                      { AgPlacement place = AgPlacement("SFLT","SFSM");              
                            /// Add daughter volume SFLT to mother SFSM              
                            place.TranslateX(-(sfpb.hhight-sfpb.khight));              
                            /// Translate x = -(sfpb.hhight-sfpb.khight)              
                            place.TranslateY(hight+yoffset);              
                            /// Translate y = hight+yoffset              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
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
                            place.TranslateX(0.-(2.6-(0.2+0.01/tan(pi/5))));              
                            /// Translate x = 0.-(2.6-(0.2+0.01/tan(pi/5)))              
                            place.TranslateY(0.+yoffset);              
                            /// Translate y = 0.+yoffset              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SFLU"), place );              
                      } // end placement of SFLU           
                      essai=180;           
                      essai=essai+27+27;           
                      { AgPlacement place = AgPlacement("SFLU","SFSM");              
                            /// Add daughter volume SFLU to mother SFSM              
                            place.TranslateX(-cos(63*pi/180)*2*(sfpb.hbase-sfpb.kbase)-(2.6-(0.2+0.01/tan(pi/5))));              
                            /// Translate x = -cos(63*pi/180)*2*(sfpb.hbase-sfpb.kbase)-(2.6-(0.2+0.01/tan(pi/5)))              
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
                            place.TranslateX(0.+(2.6-(0.2+0.01/tan(pi/5))));              
                            /// Translate x = 0.+(2.6-(0.2+0.01/tan(pi/5)))              
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
                            place.TranslateX(cos(63*pi/180)*2*(sfpb.hbase-sfpb.kbase)+(2.6-(0.2+0.01/tan(pi/5))));              
                            /// Translate x = cos(63*pi/180)*2*(sfpb.hbase-sfpb.kbase)+(2.6-(0.2+0.01/tan(pi/5)))              
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
                            place.TranslateX(3.5/2+0.4);              
                            /// Translate x = 3.5/2+0.4              
                            place.TranslateY(-0.02-0.04-0.02+yoffset);              
                            /// Translate y = -0.02-0.04-0.02+yoffset              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
                            _stacker -> Position( AgBlock::Find("SFFK"), place );              
                      } // end placement of SFFK           
                      { AgPlacement place = AgPlacement("SFFK","SFSM");              
                            /// Add daughter volume SFFK to mother SFSM              
                            place.TranslateX(-3.5/2-0.4);              
                            /// Translate x = -3.5/2-0.4              
                            place.TranslateY(-0.02-0.04-0.02+yoffset);              
                            /// Translate y = -0.02-0.04-0.02+yoffset              
                            place.TranslateZ(0);              
                            /// Translate z = 0              
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
                            place.TranslateX(-2.55-sfpb.fsize*cos(15*pi/180));              
                            /// Translate x = -2.55-sfpb.fsize*cos(15*pi/180)              
                            place.TranslateY(-0.02-0.04-0.02-sfpb.fsize*cos(75*pi/180)+yoffset);              
                            /// Translate y = -0.02-0.04-0.02-sfpb.fsize*cos(75*pi/180)+yoffset              
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
                            place.TranslateX(2.55+sfpb.fsize*cos(15*pi/180));              
                            /// Translate x = 2.55+sfpb.fsize*cos(15*pi/180)              
                            place.TranslateY(-0.02-0.04-0.02-sfpb.fsize*cos(75*pi/180)+yoffset);              
                            /// Translate y = -0.02-0.04-0.02-sfpb.fsize*cos(75*pi/180)+yoffset              
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
                            place.TranslateY(-0.02-0.04-0.04+yoffset-0.0025/2.);              
                            /// Translate y = -0.02-0.04-0.04+yoffset-0.0025/2.              
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
                            place.TranslateX(-2.55-sfpb.fsize*cos(15*pi/180)+0.005);              
                            /// Translate x = -2.55-sfpb.fsize*cos(15*pi/180)+0.005              
                            place.TranslateY(-0.02-0.04-0.02-sfpb.fsize*cos(75*pi/180)+yoffset-0.021);              
                            /// Translate y = -0.02-0.04-0.02-sfpb.fsize*cos(75*pi/180)+yoffset-0.021              
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
                            place.TranslateX(+2.55+sfpb.fsize*cos(15*pi/180)-0.005);              
                            /// Translate x = +2.55+sfpb.fsize*cos(15*pi/180)-0.005              
                            place.TranslateY(-0.02-0.04-0.02-sfpb.fsize*cos(75*pi/180)+yoffset-0.021);              
                            /// Translate y = -0.02-0.04-0.02-sfpb.fsize*cos(75*pi/180)+yoffset-0.021              
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
                            place.TranslateY(-0.04-(0.5+0.08)/2.+yoffset);              
                            /// Translate y = -0.04-(0.5+0.08)/2.+yoffset              
                            place.TranslateZ(69.75/2+1.275/2.);              
                            /// Translate z = 69.75/2+1.275/2.              
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
                            place.TranslateY(-0.04-(0.5+0.08)/2.+yoffset);              
                            /// Translate y = -0.04-(0.5+0.08)/2.+yoffset              
                            place.TranslateZ(-(69.75/2+1.275/2.));              
                            /// Translate z = -(69.75/2+1.275/2.)              
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
                            place.TranslateY(-0.04-(0.5+0.08)/2.+yoffset);              
                            /// Translate y = -0.04-(0.5+0.08)/2.+yoffset              
                            place.TranslateZ(-(69.75/2+1.275)-(12.4)/2.);              
                            /// Translate z = -(69.75/2+1.275)-(12.4)/2.              
                            _stacker -> Position( AgBlock::Find("SFAM"), place );              
                      } // end placement of SFAM           
                      { AgPlacement place = AgPlacement("SFAM","SFSM");              
                            /// Add daughter volume SFAM to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(-0.04-(0.5+0.08)/2.+yoffset);              
                            /// Translate y = -0.04-(0.5+0.08)/2.+yoffset              
                            place.TranslateZ(+(69.75/2+1.275)+(12.4)/2.);              
                            /// Translate z = +(69.75/2+1.275)+(12.4)/2.              
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
                            place.TranslateX(-1.7);              
                            /// Translate x = -1.7              
                            place.TranslateY(0.2);              
                            /// Translate y = 0.2              
                            place.TranslateZ(-(69.75/2-0.6)-15.8/2.);              
                            /// Translate z = -(69.75/2-0.6)-15.8/2.              
                            place.AlphaZ(+54.);              
                            /// Rotate: AlphaZ = +54.              
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
                            place.TranslateX(+1.7);              
                            /// Translate x = +1.7              
                            place.TranslateY(0.2);              
                            /// Translate y = 0.2              
                            place.TranslateZ(+(69.75/2-0.6)+15.8/2.);              
                            /// Translate z = +(69.75/2-0.6)+15.8/2.              
                            place.AlphaZ(-54.);              
                            /// Rotate: AlphaZ = -54.              
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
                            place.TranslateX(+1.7);              
                            /// Translate x = +1.7              
                            place.TranslateY(0.2);              
                            /// Translate y = 0.2              
                            place.TranslateZ(-(69.75/2-0.6)-15.8/2.);              
                            /// Translate z = -(69.75/2-0.6)-15.8/2.              
                            place.AlphaZ(-54.);              
                            /// Rotate: AlphaZ = -54.              
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
                            place.TranslateX(-1.7);              
                            /// Translate x = -1.7              
                            place.TranslateY(0.2);              
                            /// Translate y = 0.2              
                            place.TranslateZ(+(69.75/2-0.6)+15.8/2.);              
                            /// Translate z = +(69.75/2-0.6)+15.8/2.              
                            place.AlphaY(180);              
                            /// Rotate: AlphaY = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.AlphaZ(+54.);              
                            /// Rotate: AlphaZ = +54.              
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
                            place.TranslateX(-0.16);              
                            /// Translate x = -0.16              
                            place.TranslateY(2.07);              
                            /// Translate y = 2.07              
                            place.TranslateZ(-(69.75/2-0.6)-8.1/2-0.2);              
                            /// Translate z = -(69.75/2-0.6)-8.1/2-0.2              
                            place.AlphaZ(+54.);              
                            /// Rotate: AlphaZ = +54.              
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
                            place.TranslateX(+0.16);              
                            /// Translate x = +0.16              
                            place.TranslateY(2.07);              
                            /// Translate y = 2.07              
                            place.TranslateZ(+(69.75/2-0.6)+8.1/2+0.2);              
                            /// Translate z = +(69.75/2-0.6)+8.1/2+0.2              
                            place.AlphaZ(-54.);              
                            /// Rotate: AlphaZ = -54.              
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
                            place.TranslateX(+0.505);              
                            /// Translate x = +0.505              
                            place.TranslateY(1.585);              
                            /// Translate y = 1.585              
                            place.TranslateZ(-(69.75/2-0.6)-8.1/2-0.2);              
                            /// Translate z = -(69.75/2-0.6)-8.1/2-0.2              
                            place.AlphaZ(-54.);              
                            /// Rotate: AlphaZ = -54.              
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
                            place.TranslateX(-0.505);              
                            /// Translate x = -0.505              
                            place.TranslateY(1.585);              
                            /// Translate y = 1.585              
                            place.TranslateZ(+(69.75/2-0.6)+8.1/2+0.2);              
                            /// Translate z = +(69.75/2-0.6)+8.1/2+0.2              
                            place.AlphaZ(+54.);              
                            /// Rotate: AlphaZ = +54.              
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
                            place.TranslateY(+1.79);              
                            /// Translate y = +1.79              
                            place.TranslateZ(-49.8);              
                            /// Translate z = -49.8              
                            _stacker -> Position( AgBlock::Find("SFPR"), place );              
                      } // end placement of SFPR           
                      { AgPlacement place = AgPlacement("SFPR","SFSM");              
                            /// Add daughter volume SFPR to mother SFSM              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(+1.79);              
                            /// Translate y = +1.79              
                            place.TranslateZ(+49.8-3.7);              
                            /// Translate z = +49.8-3.7              
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
                            place.TranslateY(+1.79-3.48+0.08);              
                            /// Translate y = +1.79-3.48+0.08              
                            place.TranslateZ(-49.8-0.95/2.);              
                            /// Translate z = -49.8-0.95/2.              
                            _stacker -> Position( AgBlock::Find("SFPB"), place );              
                      } // end placement of SFPB           
                      { AgPlacement place = AgPlacement("SFPB","SFSM");              
                            /// Add daughter volume SFPB to mother SFSM              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(+1.79-3.48+0.08);              
                            /// Translate y = +1.79-3.48+0.08              
                            place.TranslateZ(+49.8+0.95/2.);              
                            /// Translate z = +49.8+0.95/2.              
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
                            place.TranslateY(+1.79-3.48+0.08-0.8/2.-0.5/2.);              
                            /// Translate y = +1.79-3.48+0.08-0.8/2.-0.5/2.              
                            place.TranslateZ(-49.8-0.95-0.2+1.9+2.5/2.);              
                            /// Translate z = -49.8-0.95-0.2+1.9+2.5/2.              
                            _stacker -> Position( AgBlock::Find("SSBS"), place );              
                      } // end placement of SSBS           
                      { AgPlacement place = AgPlacement("SSBS","SFSM");              
                            /// Add daughter volume SSBS to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(+1.79-3.48+0.08-0.8/2.-0.5/2.);              
                            /// Translate y = +1.79-3.48+0.08-0.8/2.-0.5/2.              
                            place.TranslateZ(+49.8+0.95+0.2-1.9-2.5/2.);              
                            /// Translate z = +49.8+0.95+0.2-1.9-2.5/2.              
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
                            place.TranslateY(+1.79-3.48+0.08-0.8/2.-0.5/2.);              
                            /// Translate y = +1.79-3.48+0.08-0.8/2.-0.5/2.              
                            place.TranslateZ(-49.8-0.95-0.2+1.9/2.);              
                            /// Translate z = -49.8-0.95-0.2+1.9/2.              
                            _stacker -> Position( AgBlock::Find("SSBB"), place );              
                      } // end placement of SSBB           
                      { AgPlacement place = AgPlacement("SSBB","SFSM");              
                            /// Add daughter volume SSBB to mother SFSM              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(+1.79-3.48+0.08-0.8/2.-0.5/2.);              
                            /// Translate y = +1.79-3.48+0.08-0.8/2.-0.5/2.              
                            place.TranslateZ(+49.8+0.95+0.2-1.9/2.);              
                            /// Translate z = +49.8+0.95+0.2-1.9/2.              
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
                                        place.TranslateX(+1.1+0.02*jwaf);                    
                                        /// Translate x = +1.1+0.02*jwaf                    
                                        place.TranslateY(1.35+0.02*jwaf);                    
                                        /// Translate y = 1.35+0.02*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+iwaf*wafpcklen);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2+iwaf*wafpcklen                    
                                        place.AlphaZ(-54);                    
                                        /// Rotate: AlphaZ = -54                    
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
                                        place.TranslateX(-1.1-0.02*jwaf);                    
                                        /// Translate x = -1.1-0.02*jwaf                    
                                        place.TranslateY(1.35+0.02*jwaf);                    
                                        /// Translate y = 1.35+0.02*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-iwaf*wafpcklen);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2-iwaf*wafpcklen                    
                                        place.AlphaZ(+54);                    
                                        /// Rotate: AlphaZ = +54                    
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
                                        place.TranslateX(+1.1+0.02*jwaf);                    
                                        /// Translate x = +1.1+0.02*jwaf                    
                                        place.TranslateY(1.35+0.02*jwaf);                    
                                        /// Translate y = 1.35+0.02*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+7.5+8.5*0.93-iwaf*0.93);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+7.5+8.5*0.93-iwaf*0.93                    
                                        place.AlphaZ(-54);                    
                                        /// Rotate: AlphaZ = -54                    
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
                                        place.TranslateX(-1.1-0.02*jwaf);                    
                                        /// Translate x = -1.1-0.02*jwaf                    
                                        place.TranslateY(1.35+0.02*jwaf);                    
                                        /// Translate y = 1.35+0.02*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-7.5-8.5*0.93+iwaf*0.93);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-7.5-8.5*0.93+iwaf*0.93                    
                                        place.AlphaZ(+54);                    
                                        /// Rotate: AlphaZ = +54                    
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
                                        place.TranslateX(+2.3+0.02*jwaf);                    
                                        /// Translate x = +2.3+0.02*jwaf                    
                                        place.TranslateY(-0.3+0.02*jwaf);                    
                                        /// Translate y = -0.3+0.02*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen                    
                                        place.AlphaZ(-54);                    
                                        /// Rotate: AlphaZ = -54                    
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
                                        place.TranslateX(-2.3-0.02*jwaf);                    
                                        /// Translate x = -2.3-0.02*jwaf                    
                                        place.TranslateY(-0.3+0.02*jwaf);                    
                                        /// Translate y = -0.3+0.02*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen                    
                                        place.AlphaZ(+54);                    
                                        /// Rotate: AlphaZ = +54                    
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
                                        place.TranslateX(+2.3+0.02*jwaf);                    
                                        /// Translate x = +2.3+0.02*jwaf                    
                                        place.TranslateY(-0.3+0.02*jwaf);                    
                                        /// Translate y = -0.3+0.02*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+8.5*0.93-iwaf*0.93);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+8.5*0.93-iwaf*0.93                    
                                        place.AlphaZ(-54);                    
                                        /// Rotate: AlphaZ = -54                    
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
                                        place.TranslateX(-2.3-0.02*jwaf);                    
                                        /// Translate x = -2.3-0.02*jwaf                    
                                        place.TranslateY(-0.3+0.02*jwaf);                    
                                        /// Translate y = -0.3+0.02*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-8.5*0.93+iwaf*0.93);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-8.5*0.93+iwaf*0.93                    
                                        place.AlphaZ(+54);                    
                                        /// Rotate: AlphaZ = +54                    
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
                                        place.TranslateX(+1.1+0.02*jwaf);                    
                                        /// Translate x = +1.1+0.02*jwaf                    
                                        place.TranslateY(1.35+0.02*jwaf);                    
                                        /// Translate y = 1.35+0.02*jwaf                    
                                        place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen);                    
                                        /// Translate z = -(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen                    
                                        place.AlphaZ(-54);                    
                                        /// Rotate: AlphaZ = -54                    
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
                                        place.TranslateX(-1.1-0.02*jwaf);                    
                                        /// Translate x = -1.1-0.02*jwaf                    
                                        place.TranslateY(1.35+0.02*jwaf);                    
                                        /// Translate y = 1.35+0.02*jwaf                    
                                        place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen);                    
                                        /// Translate z = +(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen                    
                                        place.AlphaZ(+54);                    
                                        /// Rotate: AlphaZ = +54                    
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
                                  place.TranslateX(+1.1+0.02*iwaf);                 
                                  /// Translate x = +1.1+0.02*iwaf                 
                                  place.TranslateY(1.35+0.02*iwaf);                 
                                  /// Translate y = 1.35+0.02*iwaf                 
                                  place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+7.5/2.);                 
                                  /// Translate z = -(sfpa.wplen+wafpcklen)/2+16*wafpcklen+wafpcklen/2.+7.5/2.                 
                                  place.AlphaZ(-54);                 
                                  /// Rotate: AlphaZ = -54                 
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
                                  place.TranslateX(-1.1-0.02*iwaf);                 
                                  /// Translate x = -1.1-0.02*iwaf                 
                                  place.TranslateY(1.35+0.02*iwaf);                 
                                  /// Translate y = 1.35+0.02*iwaf                 
                                  place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-7.5/2.);                 
                                  /// Translate z = +(sfpa.wplen+wafpcklen)/2-16*wafpcklen-wafpcklen/2.-7.5/2.                 
                                  place.AlphaZ(+54);                 
                                  /// Rotate: AlphaZ = +54                 
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
                                  place.TranslateX(-3.32);                 
                                  /// Translate x = -3.32                 
                                  place.TranslateY(-1.6);                 
                                  /// Translate y = -1.6                 
                                  place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+(iwaf)*wafpcklen+wafpcklen/2.-1.5/2.-0.1/2.);                 
                                  /// Translate z = -(sfpa.wplen+wafpcklen)/2+(iwaf)*wafpcklen+wafpcklen/2.-1.5/2.-0.1/2.                 
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
                                  place.TranslateX(+3.32);                 
                                  /// Translate x = +3.32                 
                                  place.TranslateY(-1.6);                 
                                  /// Translate y = -1.6                 
                                  place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-(iwaf)*wafpcklen-wafpcklen/2.+1.5/2.+0.1/2.);                 
                                  /// Translate z = +(sfpa.wplen+wafpcklen)/2-(iwaf)*wafpcklen-wafpcklen/2.+1.5/2.+0.1/2.                 
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
                                  place.TranslateX(-2.71);                 
                                  /// Translate x = -2.71                 
                                  place.TranslateY(-0.75);                 
                                  /// Translate y = -0.75                 
                                  place.TranslateZ(-(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen+wafpcklen/2.-1.5/2.-0.1/2.);                 
                                  /// Translate z = -(sfpa.wplen+wafpcklen)/2+(iwaf+8)*wafpcklen+wafpcklen/2.-1.5/2.-0.1/2.                 
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
                                  place.TranslateX(+2.71);                 
                                  /// Translate x = +2.71                 
                                  place.TranslateY(-0.75);                 
                                  /// Translate y = -0.75                 
                                  place.TranslateZ(+(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen-wafpcklen/2.+1.5/2.+0.1/2.);                 
                                  /// Translate z = +(sfpa.wplen+wafpcklen)/2-(iwaf+8)*wafpcklen-wafpcklen/2.+1.5/2.+0.1/2.                 
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
                            shape.par("dz")=49.8;              
                            shape.par("thet")=0;              
                            shape.par("phi")=0;              
                            shape.par("h1")=0.02;              
                            shape.par("bl1")=0.2;              
                            shape.par("tl1")=0.2-0.02/tan(pi/5);              
                            shape.par("alp1")=(pi/2-atan(2*tan(pi/5)))*360/(2*pi);              
                            shape.par("h2")=0.02;              
                            shape.par("bl2")=0.2;              
                            shape.par("tl2")=0.2-0.02/tan(pi/5);              
                            shape.par("alp2")=(pi/2-atan(2*tan(pi/5)))*360/(2*pi);              
                            /// Shape Trap dz=49.8 thet=0 phi=0 h1=0.02 bl1=0.2 tl1=0.2-0.02/tan(pi/5) alp1=(pi/2-atan(2*tan(pi/5)))*360/(2*pi) h2=0.02 bl2=0.2 tl2=0.2-0.02/tan(pi/5) alp2=(pi/2-atan(2*tan(pi/5)))*360/(2*pi)               
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
                            shape.par("dz")=49.8;              
                            shape.par("thet")=0;              
                            shape.par("phi")=0;              
                            shape.par("h1")=0.02;              
                            shape.par("bl1")=0.2;              
                            shape.par("tl1")=0.2-0.02/tan(27*2*pi/360);              
                            shape.par("alp1")=(pi/2-atan(2*tan(27*2*pi/360)))*360/(2*pi);              
                            shape.par("h2")=0.02;              
                            shape.par("bl2")=0.2;              
                            shape.par("tl2")=0.2-0.02/tan(27*2*pi/360);              
                            shape.par("alp2")=(pi/2-atan(2*tan(27*2*pi/360)))*360/(2*pi);              
                            /// Shape Trap dz=49.8 thet=0 phi=0 h1=0.02 bl1=0.2 tl1=0.2-0.02/tan(27*2*pi/360) alp1=(pi/2-atan(2*tan(27*2*pi/360)))*360/(2*pi) h2=0.02 bl2=0.2 tl2=0.2-0.02/tan(27*2*pi/360) alp2=(pi/2-atan(2*tan(27*2*pi/360)))*360/(2*pi)               
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
                            shape.par("dx")=0.4;              
                            shape.par("dy")=0.02;              
                            shape.par("dz")=69.75/2;              
                            /// Shape Bbox dx=0.4 dy=0.02 dz=69.75/2               
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
                            shape.par("dx")=0.6/cos(15*pi/180);              
                            shape.par("dy")=0.02;              
                            shape.par("dz")=69.75/2;              
                            /// Shape Bbox dx=0.6/cos(15*pi/180) dy=0.02 dz=69.75/2               
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
                            shape.par("dx")=5.1/2.;              
                            shape.par("dy")=0.0025/2.;              
                            shape.par("dz")=69.75/2;              
                            /// Shape Bbox dx=5.1/2. dy=0.0025/2. dz=69.75/2               
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
                            shape.par("dx")=0.6/cos(15*pi/180);              
                            shape.par("dy")=0.0025/2.;              
                            shape.par("dz")=69.75/2;              
                            /// Shape Bbox dx=0.6/cos(15*pi/180) dy=0.0025/2. dz=69.75/2               
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
                            shape.par("dx")=1.5/2.;              
                            shape.par("dy")=0.0130/2.;              
                            shape.par("dz")=4.3/2.;              
                            /// Shape Bbox dx=1.5/2. dy=0.0130/2. dz=4.3/2.               
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
                            shape.par("dx")=1.5/2.;              
                            shape.par("dy")=0.0130/2.;              
                            shape.par("dz")=7.5/2.;              
                            /// Shape Bbox dx=1.5/2. dy=0.0130/2. dz=7.5/2.               
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
                            shape.par("dx")=1.5/2.;              
                            shape.par("dy")=0.0130/2.;              
                            shape.par("dz")=0.93/2.;              
                            /// Shape Bbox dx=1.5/2. dy=0.0130/2. dz=0.93/2.               
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
                            shape.par("dx")=3.89/2.;              
                            shape.par("dy")=0.0130/2.;              
                            shape.par("dz")=1.5/2.;              
                            /// Shape Bbox dx=3.89/2. dy=0.0130/2. dz=1.5/2.               
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
                            shape.par("dx")=1.875/2.;              
                            shape.par("dy")=0.0130/2.;              
                            shape.par("dz")=1.5/2.;              
                            /// Shape Bbox dx=1.875/2. dy=0.0130/2. dz=1.5/2.               
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
                            shape.par("dx")=7.2/2.;              
                            shape.par("dy")=0.3/2.;              
                            shape.par("dz")=12.4/2;              
                            /// Shape Bbox dx=7.2/2. dy=0.3/2. dz=12.4/2               
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
                            place.TranslateZ(12.4/2-10.25/2);              
                            /// Translate z = 12.4/2-10.25/2              
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
                            place.TranslateX(7.2/2.-2.1/2.);              
                            /// Translate x = 7.2/2.-2.1/2.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-12.4/2+2.15/2);              
                            /// Translate z = -12.4/2+2.15/2              
                            _stacker -> Position( AgBlock::Find("SFAS"), place );              
                      } // end placement of SFAS           
                      { AgPlacement place = AgPlacement("SFAS","SFAM");              
                            /// Add daughter volume SFAS to mother SFAM              
                            place.TranslateX(-7.2/2.+2.1/2.);              
                            /// Translate x = -7.2/2.+2.1/2.              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(-12.4/2+2.15/2);              
                            /// Translate z = -12.4/2+2.15/2              
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
                            shape.par("dx")=7.2/2.;              
                            shape.par("dy")=0.3/2.;              
                            shape.par("dz")=10.25/2;              
                            /// Shape Bbox dx=7.2/2. dy=0.3/2. dz=10.25/2               
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
                            shape.par("dx")=2.1/2.;              
                            shape.par("dy")=0.3/2.;              
                            shape.par("dz")=2.15/2;              
                            /// Shape Bbox dx=2.1/2. dy=0.3/2. dz=2.15/2               
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
                            shape.par("dx")=(7.6+0.08)/2.;              
                            shape.par("dy")=(0.5+0.08)/2.;              
                            shape.par("dz")=1.275/2.;              
                            /// Shape Bbox dx=(7.6+0.08)/2. dy=(0.5+0.08)/2. dz=1.275/2.               
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
                            place.TranslateZ((-1.275+0.5)/2.);              
                            /// Translate z = (-1.275+0.5)/2.              
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
                            place.TranslateX(7.6/2.+0.04/2);              
                            /// Translate x = 7.6/2.+0.04/2              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SAPS"), place );              
                      } // end placement of SAPS           
                      { AgPlacement place = AgPlacement("SAPS","SAPP");              
                            /// Add daughter volume SAPS to mother SAPP              
                            place.TranslateX(-(7.6/2.+0.04/2));              
                            /// Translate x = -(7.6/2.+0.04/2)              
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
                            place.TranslateY((0.5+0.04)/2.);              
                            /// Translate y = (0.5+0.04)/2.              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("SAPT"), place );              
                      } // end placement of SAPT           
                      { AgPlacement place = AgPlacement("SAPT","SAPP");              
                            /// Add daughter volume SAPT to mother SAPP              
                            place.TranslateX(0.);              
                            /// Translate x = 0.              
                            place.TranslateY(-(0.5+0.04)/2.);              
                            /// Translate y = -(0.5+0.04)/2.              
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
                            shape.par("dx")=7.6/2.;              
                            shape.par("dy")=0.5/2.;              
                            shape.par("dz")=0.5/2.;              
                            /// Shape Bbox dx=7.6/2. dy=0.5/2. dz=0.5/2.               
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
                            shape.par("dx")=0.04/2.;              
                            shape.par("dy")=(0.5+0.08)/2.;              
                            shape.par("dz")=1.275/2.;              
                            /// Shape Bbox dx=0.04/2. dy=(0.5+0.08)/2. dz=1.275/2.               
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
                            shape.par("dx")=7.6/2.;              
                            shape.par("dy")=0.04/2.;              
                            shape.par("dz")=1.275/2.;              
                            /// Shape Bbox dx=7.6/2. dy=0.04/2. dz=1.275/2.               
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
                            shape.par("dx")=4.4/2.;              
                            shape.par("dy")=0.37/2.;              
                            shape.par("dz")=15.8/2;              
                            /// Shape Bbox dx=4.4/2. dy=0.37/2. dz=15.8/2               
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
                            shape.par("dx")=4.0/2.;              
                            shape.par("dy")=0.37/2.;              
                            shape.par("dz")=15.8/2;              
                            /// Shape Bbox dx=4.0/2. dy=0.37/2. dz=15.8/2               
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
                            place.TranslateZ(-15.8/2+7.5/2);              
                            /// Translate z = -15.8/2+7.5/2              
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
                            shape.par("dx")=3.0/2.;              
                            shape.par("dy")=0.37/2.;              
                            shape.par("dz")=15.8/2;              
                            /// Shape Bbox dx=3.0/2. dy=0.37/2. dz=15.8/2               
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
                            shape.par("dx")=1.0/2.;              
                            shape.par("dy")=0.37/2.;              
                            shape.par("dz")=7.5/2;              
                            /// Shape Bbox dx=1.0/2. dy=0.37/2. dz=7.5/2               
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
                            shape.par("dx")=0.44/2.;              
                            shape.par("dy")=0.065/2.;              
                            shape.par("dz")=8.1/2;              
                            /// Shape Bbox dx=0.44/2. dy=0.065/2. dz=8.1/2               
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
                            shape.par("dx")=1.65/2.;              
                            shape.par("dy")=0.065/2.;              
                            shape.par("dz")=8.1/2;              
                            /// Shape Bbox dx=1.65/2. dy=0.065/2. dz=8.1/2               
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
                            shape.par("dx")=4.3/2.;              
                            shape.par("dy")=0.8/2.;              
                            shape.par("dz")=0.95/2.;              
                            /// Shape Bbox dx=4.3/2. dy=0.8/2. dz=0.95/2.               
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
                            shape.par("dx")=2.5/2.;              
                            shape.par("dy")=0.5/2.;              
                            shape.par("dz")=2.5/2.;              
                            /// Shape Bbox dx=2.5/2. dy=0.5/2. dz=2.5/2.               
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
                            shape.par("dx")=4.3/2.;              
                            shape.par("dy")=0.5/2.;              
                            shape.par("dz")=1.9/2.;              
                            /// Shape Bbox dx=4.3/2. dy=0.5/2. dz=1.9/2.               
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
                            shape.par("rmin")=31.285;              
                            shape.par("rmax")=31.8;              
                            shape.par("phi1")=45.;              
                            shape.par("phi2")=135.;              
                            shape.par("dz")=2.5/2.;              
                            /// Shape Tubs rmin=31.285 rmax=31.8 phi1=45. phi2=135. dz=2.5/2.               
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
                            shape.par("rmin")=23.3;              
                            shape.par("rmax")=31.285;              
                            shape.par("phi1")=45.;              
                            shape.par("phi2")=135.;              
                            shape.par("dz")=0.5/2.;              
                            /// Shape Tubs rmin=23.3 rmax=31.285 phi1=45. phi2=135. dz=0.5/2.               
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
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
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
                            shape.par("rmin")=31.285;              
                            shape.par("rmax")=31.8;              
                            shape.par("phi1")=-45.;              
                            shape.par("phi2")=+45.;              
                            shape.par("dz")=2.5/2.;              
                            /// Shape Tubs rmin=31.285 rmax=31.8 phi1=-45. phi2=+45. dz=2.5/2.               
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
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
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
                            shape.par("rmin")=28.0;              
                            shape.par("rmax")=31.285;              
                            shape.par("phi1")=-45.;              
                            shape.par("phi2")=+45.;              
                            shape.par("dz")=0.5/2.;              
                            /// Shape Tubs rmin=28.0 rmax=31.285 phi1=-45. phi2=+45. dz=0.5/2.               
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
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("SSLB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=7.8/2.;              
                            shape.par("dy")=7.3/2.;              
                            shape.par("dz")=2.5/2.;              
                            /// Shape Bbox dx=7.8/2. dy=7.3/2. dz=2.5/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SSLB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SSLB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SSLB     
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
                            shape.par("rmax")=0.8;              
                            shape.par("dz")=5.05/2.;              
                            /// Shape Tube rmin=0. rmax=0.8 dz=5.05/2.               
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
                            shape.par("dx")=6.3/2.;              
                            shape.par("dy")=0.4/2.;              
                            shape.par("dz")=3.6/2;              
                            /// Shape Bbox dx=6.3/2. dy=0.4/2. dz=3.6/2               
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
                            shape.par("dx")=6.4/2.;              
                            shape.par("dy")=2.6/2.;              
                            shape.par("dz")=3.6/2;              
                            /// Shape Bbox dx=6.4/2. dy=2.6/2. dz=3.6/2               
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
                            place.TranslateY(-2.6/2.+0.5/2.);              
                            /// Translate y = -2.6/2.+0.5/2.              
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
                            place.TranslateX(1.0);              
                            /// Translate x = 1.0              
                            place.TranslateY(0.22);              
                            /// Translate y = 0.22              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            place.AlphaZ(45.);              
                            /// Rotate: AlphaZ = 45.              
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
                            place.TranslateX(-1.0);              
                            /// Translate x = -1.0              
                            place.TranslateY(0.22);              
                            /// Translate y = 0.22              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            place.AlphaZ(-45.);              
                            /// Rotate: AlphaZ = -45.              
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
                            shape.par("dx")=6.4/2.;              
                            shape.par("dy")=0.5/2.;              
                            shape.par("dz")=3.6/2;              
                            /// Shape Bbox dx=6.4/2. dy=0.5/2. dz=3.6/2               
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
                            shape.par("dx")=2.3/2.;              
                            shape.par("dy")=0.6/2.;              
                            shape.par("dz")=3.6/2;              
                            /// Shape Bbox dx=2.3/2. dy=0.6/2. dz=3.6/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_SCVS;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_SCVS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block SCVS     
    // ----------------------------------------------------------------------- geoctr
       void SisdGeo1::ConstructGeometry( const Char_t *dummy )     
       {        
             ///@addtogroup SisdGeo1_revision        
             ///@{           
                   /// Author: Lilian Martin           
             ///@}        
             ///@addtogroup SisdGeo1_revision        
             ///@{           
                   /// Created:  23 Apr 04            
             ///@}        
             AddBlock("SFMO");        
             AddBlock("SFLM");        
             AddBlock("SFDM");        
             AddBlock("SFSW");        
             AddBlock("SFSD");        
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
             AddBlock("SSLT");        
             AddBlock("SCMP");        
             AddBlock("SCVM");        
             AddBlock("SCVB");        
             AddBlock("SCVS");        
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
                   sfpa . rmax = 29.5; //  mother rmax            
                   /// sfpa . rmax = 29.5; //  mother rmax            
                   sfpa . len = 120.; //  mother Len along the z direction            
                   /// sfpa . len = 120.; //  mother Len along the z direction            
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
                   sfpa . wplen = 68.8; //  length of wafer pack            
                   /// sfpa . wplen = 68.8; //  length of wafer pack            
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
             /// USE ssdp _index=1;        
             ssdp.Use();        
             /// USE sfpa version=ssdp.config ;        
             sfpa.Use("version",(Float_t)ssdp.config );        
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
                         _stacker -> Position( AgBlock::Find("SFMO"), place );              
                   } // end placement of SFMO           
             }        
       }; // SisdGeo1     
 }; // namespace SisdGeo1  
 