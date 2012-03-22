#include "BtofGeo3.h"  
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
 namespace BTOFGEO3 // $NMSPC  
 {     
       //     
       // ---------------------------------------------------------------------------------------------------     
          //  -----------------------------------------------------     
          /// @defgroup btog_doc     
          /// \class Btog_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t rmin;     
          ///Float_t rmax;     
          ///Float_t dz;     
          ///Float_t choice;     
          ///Array_t<Float_t> posit1;     
          ///Float_t posit2;     
          ///Int_t _index;     
          //     
          Btog_t btog;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup tray_doc     
          /// \class Tray_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t height;     
          ///Float_t width;     
          ///Float_t length;     
          ///Float_t wallthk;     
          ///Float_t supfullh;     
          ///Float_t supfullw;     
          ///Float_t suplen;     
          ///Float_t supbaset;     
          ///Float_t supbasew;     
          ///Float_t suparmt;     
          ///Float_t cooloutr;     
          ///Float_t coolinnr;     
          ///Float_t stript;     
          ///Float_t footinse;     
          ///Float_t footthk;     
          ///Float_t foot1len;     
          ///Float_t foot2thk;     
          ///Float_t foot3len;     
          ///Int_t _index;     
          //     
          Tray_t tray;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup ctbb_doc     
          /// \class Ctbb_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t slab1len;     
          ///Float_t slab2len;     
          ///Float_t slab1x;     
          ///Float_t slab2x;     
          ///Float_t slabthck;     
          ///Float_t slabwid;     
          ///Float_t convlen;     
          ///Float_t convwidm;     
          ///Float_t convthck;     
          ///Float_t pmtlen;     
          ///Float_t pmtmaxr;     
          ///Float_t pmtminr;     
          ///Float_t baselen;     
          ///Float_t basemaxr;     
          ///Float_t baseminr;     
          ///Float_t electhck;     
          ///Float_t wrap;     
          ///Float_t shim;     
          ///Int_t _index;     
          //     
          Ctbb_t ctbb;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup toff_doc     
          /// \class Toff_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t boxwidth;     
          ///Float_t slatlen;     
          ///Float_t slat01z;     
          ///Float_t slat02z;     
          ///Float_t slat03z;     
          ///Float_t slat04z;     
          ///Float_t slat05z;     
          ///Float_t slat06z;     
          ///Float_t slat07z;     
          ///Float_t slat08z;     
          ///Float_t slat09z;     
          ///Float_t slat10z;     
          ///Float_t slatthck;     
          ///Float_t slatwid;     
          ///Float_t slatang;     
          ///Float_t pmtlen;     
          ///Float_t pmtmaxr;     
          ///Float_t pmtminr;     
          ///Float_t baselen;     
          ///Float_t basemaxr;     
          ///Float_t baseminr;     
          ///Float_t socklen;     
          ///Float_t cellwid;     
          ///Float_t cellhgt;     
          ///Float_t elechgt;     
          ///Float_t electhck;     
          ///Float_t elecwid;     
          ///Float_t eleclen;     
          ///Float_t elec01z;     
          ///Float_t elec02z;     
          ///Float_t elec03z;     
          ///Float_t elec04z;     
          ///Float_t elec05z;     
          ///Float_t elec06z;     
          ///Float_t elec07z;     
          ///Float_t elec08z;     
          ///Float_t elec09z;     
          ///Float_t elec10z;     
          ///Float_t railthck;     
          ///Float_t railwid;     
          ///Float_t coolinnr;     
          ///Float_t cooloutr;     
          ///Int_t _index;     
          //     
          Toff_t toff;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup modr_doc     
          /// \class Modr_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t height;     
          ///Float_t width;     
          ///Float_t length;     
          ///Float_t center;     
          ///Array_t<Float_t> mrpcx;     
          ///Array_t<Float_t> mrpcz;     
          ///Array_t<Float_t> mrpca;     
          ///Float_t hchgt;     
          ///Float_t hcwid;     
          ///Float_t hclen;     
          ///Float_t pcbhgt;     
          ///Float_t pcbwid;     
          ///Float_t pcblen;     
          ///Float_t myhgt;     
          ///Float_t mywid;     
          ///Float_t mylen;     
          ///Float_t grhgt;     
          ///Float_t grwid;     
          ///Float_t grlen;     
          ///Float_t oghgt;     
          ///Float_t ogwid;     
          ///Float_t oglen;     
          ///Float_t ighgt;     
          ///Float_t igwid;     
          ///Float_t iglen;     
          ///Float_t sprmin;     
          ///Float_t sprmax;     
          ///Float_t splen;     
          ///Float_t wgrmin;     
          ///Float_t wgrmax;     
          ///Float_t wglen;     
          ///Float_t feeh;     
          ///Float_t hbwid;     
          ///Float_t ngap;     
          ///Int_t _index;     
          //     
          Modr_t modr;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup mod4_doc     
          /// \class Mod4_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t height;     
          ///Float_t width;     
          ///Float_t length;     
          ///Float_t center;     
          ///Array_t<Float_t> mrpcx;     
          ///Array_t<Float_t> mrpcz;     
          ///Array_t<Float_t> mrpca;     
          ///Float_t hchgt;     
          ///Float_t hcwid;     
          ///Float_t hclen;     
          ///Float_t pcbhgt;     
          ///Float_t pcbwid;     
          ///Float_t pcblen;     
          ///Float_t myhgt;     
          ///Float_t mywid;     
          ///Float_t mylen;     
          ///Float_t grhgt;     
          ///Float_t grwid;     
          ///Float_t grlen;     
          ///Float_t oghgt;     
          ///Float_t ogwid;     
          ///Float_t oglen;     
          ///Float_t ighgt;     
          ///Float_t igwid;     
          ///Float_t iglen;     
          ///Float_t sprmin;     
          ///Float_t sprmax;     
          ///Float_t splen;     
          ///Float_t wgrmin;     
          ///Float_t wgrmax;     
          ///Float_t wglen;     
          ///Float_t feeh;     
          ///Float_t hbwid;     
          ///Float_t ngap;     
          ///Float_t trayedgez;     
          ///Int_t _index;     
          //     
          Mod4_t mod4;     
          //     
          ///@addtogroup BtofGeo3_vars     
          ///@{        
                Float_t support_arm_width,support_arm_xpos,support_arm_ypos,support_aile_width,support_aile_ypos,xpos,ypos,zpos,totlen,sublen,subcen,x0,z0,y,z,dthgt;        
                //        
                /// Float_t support_arm_width,support_arm_xpos,support_arm_ypos,support_aile_width,support_aile_ypos,xpos,ypos,zpos,totlen,sublen,subcen,x0,z0,y,z,dthgt        
          ///@}     
          ///@addtogroup BtofGeo3_vars     
          ///@{        
                Int_t i,is,choice,tof,iwid,igap,year;        
                //        
                /// Int_t i,is,choice,tof,iwid,igap,year        
          ///@}     
       BtofGeo3::BtofGeo3()     
         : AgModule("BtofGeo3"," is the Geometry of Barrel Trigger / Time Of Flight system  ")     
       {        
       }     
          // ---------------------------------------------------------------------------------------------------     
          void BTOF::Block( AgCreate create )     
          {         
                ///@addtogroup BTOF_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BTOF");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      /// Medium Standard           
                      {  AgMedium med = AgMedium::CopyMedium("Standard");              
                            _medium = med;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=btog.rmin;              
                            shape.par("rmax")=btog.rmax;              
                            shape.par("dz")=btog.dz;              
                            /// Shape Tube rmin=btog.rmin rmax=btog.rmax dz=btog.dz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BTOF;              
                            _stacker -> Build(this);              
                      }           
                      // Print<level=%i> fmt=%s fortran format statements not supported           
                      year=btog.choice-3;           
                      // Print<level=%i> fmt=%s fortran format statements not supported           
                      choice = 1                                     ;// ctb;           
                      if ( (btog.choice==2) )           
                      {              
                            choice=btog.choice       ;// full tofp;              
                      }           
                      if ( (btog.choice==6) )           
                      {              
                            choice=btog.choice       ;// full tofr;              
                      }           
                      _create = AgCreate("BTOH");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BTOH              
                            Create("BTOH");               
                      }           
                      { AgPlacement place = AgPlacement("BTOH","BTOF");              
                            /// Add daughter volume BTOH to mother BTOF              
                            place.TranslateZ(+btog.dz/2);              
                            /// Translate z = +btog.dz/2              
                            place.AlphaY(180);              
                            /// Rotate: AlphaY = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("BTOH"), place );              
                      } // end placement of BTOH           
                      choice=btog.choice;           
                      _create = AgCreate("BTOH");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BTOH              
                            Create("BTOH");               
                      }           
                      { AgPlacement place = AgPlacement("BTOH","BTOF");              
                            /// Add daughter volume BTOH to mother BTOF              
                            place.TranslateZ(-btog.dz/2);              
                            /// Translate z = -btog.dz/2              
                            _stacker -> Position( AgBlock::Find("BTOH"), place );              
                      } // end placement of BTOH           
                      END_OF_BTOF:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BTOF     
          // ---------------------------------------------------------------------------------------------------     
          void BTOH::Block( AgCreate create )     
          {         
                ///@addtogroup BTOH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BTOH");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.par("serial")=choice;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dz")=btog.dz/2;              
                            /// Shape Tube dz=btog.dz/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BTOH;              
                            _stacker -> Build(this);              
                      }           
                      /// Loop on is from 1 to 60 step=1           
                      for ( is=1; (1>0)? (is<=60):(is>=60); is+=1 )           
                      {              
                            tof=0                                          ;//// all ctb for choice=1;              
                            if ( (choice==2) )              
                            {                 
                                  tof=1      ;//// all tofp;                 
                            }              
                            if ( (choice==3&&46<=is&&is<=60) )              
                            {                 
                                  tof=1      ;//// big tofp patch, rest ctb;                 
                            }              
                            if ( (choice==4&&is==btog.posit1(1)) )              
                            {                 
                                  tof=1      ;//// run-2 (one tofp tray);                 
                            }              
                            if ( (choice==5&&is==btog.posit1(1)) )              
                            {                 
                                  tof=1      ;//// run-3 (one tofp tray;                 
                            }              
                            if ( (choice==5&&is==btog.posit2) )              
                            {                 
                                  tof=2      ;//      and one tofr tray);                 
                            }              
                            if ( (choice==6) )              
                            {                 
                                  tof=2      ;//// all tofr;                 
                            }              
                            if ( (choice==7&&is==btog.posit1(2)) )              
                            {                 
                                  tof=1      ;//// run-4 (one tofp tray moved 1 slot;                 
                            }              
                            if ( (choice==7&&is==btog.posit2) )              
                            {                 
                                  tof=3      ;//      and one tofrp tray);                 
                            }              
                            _create = AgCreate("BSEC");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create BSEC                 
                                  Create("BSEC");                  
                            }              
                            { AgPlacement place = AgPlacement("BSEC","BTOH");                 
                                  /// Add daughter volume BSEC to mother BTOH                 
                                  place.AlphaZ(102+6*is);                 
                                  /// Rotate: AlphaZ = 102+6*is                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BSEC"), place );                 
                            } // end placement of BSEC              
                      }           
                      END_OF_BTOH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BTOH     
          // ---------------------------------------------------------------------------------------------------     
          void BSEC::Block( AgCreate create )     
          {         
                ///@addtogroup BSEC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BSEC");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.par("serial")=tof;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-3.0;              
                            shape.par("phi2")=3.0;              
                            /// Shape Tubs phi1=-3.0 phi2=3.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BSEC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BTRA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BTRA              
                            Create("BTRA");               
                      }           
                      { AgPlacement place = AgPlacement("BTRA","BSEC");              
                            /// Add daughter volume BTRA to mother BSEC              
                            place.TranslateX(btog.rmin+(tray.supfullh+tray.height+tray.stript)/2);              
                            /// Translate x = btog.rmin+(tray.supfullh+tray.height+tray.stript)/2              
                            _stacker -> Position( AgBlock::Find("BTRA"), place );              
                      } // end placement of BTRA           
                      if ( tof==2 )           
                      {              
                            _create = AgCreate("BRFE");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create BRFE                 
                                  Create("BRFE");                  
                            }              
                            { AgPlacement place = AgPlacement("BRFE","BSEC");                 
                                  /// Add daughter volume BRFE to mother BSEC                 
                                  place.TranslateX(btog.rmin+tray.supfullh+tray.stript+tray.height+modr.feeh/2);                 
                                  /// Translate x = btog.rmin+tray.supfullh+tray.stript+tray.height+modr.feeh/2                 
                                  place.TranslateZ((btog.dz-tray.length)/2);                 
                                  /// Translate z = (btog.dz-tray.length)/2                 
                                  _stacker -> Position( AgBlock::Find("BRFE"), place );                 
                            } // end placement of BRFE              
                      }           
                      END_OF_BSEC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BSEC     
          // ---------------------------------------------------------------------------------------------------     
          void BTRA::Block( AgCreate create )     
          {         
                ///@addtogroup BTRA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BTRA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=(tray.supfullh+tray.height+tray.stript)/2;              
                            shape.par("dy")=tray.width/2;              
                            /// Shape Bbox dx=(tray.supfullh+tray.height+tray.stript)/2 dy=tray.width/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BTRA;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BXTR");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BXTR              
                            Create("BXTR");               
                      }           
                      { AgPlacement place = AgPlacement("BXTR","BTRA");              
                            /// Add daughter volume BXTR to mother BTRA              
                            place.TranslateX((tray.supfullh+tray.stript)/2);              
                            /// Translate x = (tray.supfullh+tray.stript)/2              
                            place.TranslateZ((btog.dz-tray.length)/2);              
                            /// Translate z = (btog.dz-tray.length)/2              
                            _stacker -> Position( AgBlock::Find("BXTR"), place );              
                      } // end placement of BXTR           
                      _create = AgCreate("BUND");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BUND              
                            Create("BUND");               
                      }           
                      { AgPlacement place = AgPlacement("BUND","BTRA");              
                            /// Add daughter volume BUND to mother BTRA              
                            place.TranslateX(-(tray.height+tray.stript)/2);              
                            /// Translate x = -(tray.height+tray.stript)/2              
                            place.TranslateZ((btog.dz-tray.suplen)/2);              
                            /// Translate z = (btog.dz-tray.suplen)/2              
                            _stacker -> Position( AgBlock::Find("BUND"), place );              
                      } // end placement of BUND           
                      END_OF_BTRA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BTRA     
          // ---------------------------------------------------------------------------------------------------     
          void BRFE::Block( AgCreate create )     
          {         
                ///@addtogroup BRFE_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRFE");              
                            attr.par("seen")=0;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=modr.feeh/2;              
                            shape.par("dy")=tray.width/2;              
                            shape.par("dz")=tray.length/2;              
                            /// Shape Bbox dx=modr.feeh/2 dy=tray.width/2 dz=tray.length/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRFE;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BRFE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRFE     
          // ---------------------------------------------------------------------------------------------------     
          void BXTR::Block( AgCreate create )     
          {         
                ///@addtogroup BXTR_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BXTR");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.height/2;              
                            shape.par("dz")=tray.length/2;              
                            /// Shape Bbox dx=tray.height/2 dz=tray.length/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BXTR;              
                            _stacker -> Build(this);              
                      }           
                      if ( tof==1 )           
                      {              
                            _create = AgCreate("BTTC");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create BTTC                 
                                  Create("BTTC");                  
                            }              
                            { AgPlacement place = AgPlacement("BTTC","BXTR");                 
                                  /// Add daughter volume BTTC to mother BXTR                 
                                  _stacker -> Position( AgBlock::Find("BTTC"), place );                 
                            } // end placement of BTTC              
                      }           
                      else if ( tof>=2 )           
                      {              
                            _create = AgCreate("BRTC");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create BRTC                 
                                  Create("BRTC");                  
                            }              
                            { AgPlacement place = AgPlacement("BRTC","BXTR");                 
                                  /// Add daughter volume BRTC to mother BXTR                 
                                  _stacker -> Position( AgBlock::Find("BRTC"), place );                 
                            } // end placement of BRTC              
                            _create = AgCreate("BUPC");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create BUPC                 
                                  Create("BUPC");                  
                            }              
                            { AgPlacement place = AgPlacement("BUPC","BXTR");                 
                                  /// Add daughter volume BUPC to mother BXTR                 
                                  place.TranslateX((tray.height-tray.wallthk)/2);                 
                                  /// Translate x = (tray.height-tray.wallthk)/2                 
                                  _stacker -> Position( AgBlock::Find("BUPC"), place );                 
                            } // end placement of BUPC              
                      }           
                      else           
                      {              
                            _create = AgCreate("BMTC");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create BMTC                 
                                  Create("BMTC");                  
                            }              
                            { AgPlacement place = AgPlacement("BMTC","BXTR");                 
                                  /// Add daughter volume BMTC to mother BXTR                 
                                  _stacker -> Position( AgBlock::Find("BMTC"), place );                 
                            } // end placement of BMTC              
                      }           
                      END_OF_BXTR:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BXTR     
          // ---------------------------------------------------------------------------------------------------     
          void BMTC::Block( AgCreate create )     
          {         
                ///@addtogroup BMTC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BMTC");              
                            attr.par("seen")=-1;              
                            attr.par("colo")=5;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.height/2-tray.wallthk;              
                            shape.par("dy")=tray.width/2-tray.wallthk;              
                            shape.par("dz")=tray.length/2-tray.wallthk;              
                            /// Shape Bbox dx=tray.height/2-tray.wallthk dy=tray.width/2-tray.wallthk dz=tray.length/2-tray.wallthk               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BMTC;              
                            _stacker -> Build(this);              
                      }           
                      zpos  =  (tray.length-ctbb.slab1len)/2-tray.wallthk-ctbb.wrap;           
                      xpos  =  -tray.height/2+ctbb.slab1x;           
                      _create = AgCreate("BXSA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BXSA              
                            Create("BXSA");               
                      }           
                      { AgPlacement place = AgPlacement("BXSA","BMTC");              
                            /// Add daughter volume BXSA to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            place.par("dx")=ctbb.slabthck/2;              
                            place.par("dy")=ctbb.slabwid/2;              
                            place.par("dz")=ctbb.slab1len/2;              
                            _stacker -> Position( AgBlock::Find("BXSA"), place );              
                      } // end placement of BXSA           
                      zpos = zpos - (ctbb.slab1len + ctbb.convlen)/2;           
                      _create = AgCreate("BCCV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCCV              
                            Create("BCCV");               
                      }           
                      { AgPlacement place = AgPlacement("BCCV","BMTC");              
                            /// Add daughter volume BCCV to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            place.par("dz")=ctbb.convlen/2;              
                            place.par("dx1")=ctbb.slabthck/2;              
                            place.par("dx2")=ctbb.slabthck/2;              
                            place.par("dy1")=ctbb.convwidm/2;              
                            place.par("dy2")=ctbb.slabwid/2;              
                            _stacker -> Position( AgBlock::Find("BCCV"), place );              
                      } // end placement of BCCV           
                      zpos = zpos - (ctbb.convlen + ctbb.pmtlen)/2;           
                      _create = AgCreate("BCPM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCPM              
                            Create("BCPM");               
                      }           
                      { AgPlacement place = AgPlacement("BCPM","BMTC");              
                            /// Add daughter volume BCPM to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            place.par("dz")=ctbb.pmtlen/2;              
                            place.par("rmin")=ctbb.pmtminr;              
                            place.par("rmax")=ctbb.pmtmaxr;              
                            _stacker -> Position( AgBlock::Find("BCPM"), place );              
                      } // end placement of BCPM           
                      zpos = zpos - (ctbb.pmtlen + ctbb.baselen)/2;           
                      _create = AgCreate("BCSK");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCSK              
                            Create("BCSK");               
                      }           
                      { AgPlacement place = AgPlacement("BCSK","BMTC");              
                            /// Add daughter volume BCSK to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            place.par("dz")=ctbb.baselen/2;              
                            place.par("rmin")=ctbb.baseminr;              
                            place.par("rmax")=ctbb.basemaxr;              
                            _stacker -> Position( AgBlock::Find("BCSK"), place );              
                      } // end placement of BCSK           
                      _create = AgCreate("BZEL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BZEL              
                            Create("BZEL");               
                      }           
                      { AgPlacement place = AgPlacement("BZEL","BMTC");              
                            /// Add daughter volume BZEL to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            place.par("dx")=ctbb.electhck/2;              
                            place.par("dy")=ctbb.baseminr-0.1;              
                            place.par("dz")=ctbb.baselen/2;              
                            _stacker -> Position( AgBlock::Find("BZEL"), place );              
                      } // end placement of BZEL           
                      zpos  =  (tray.length-ctbb.slab2len)/2-tray.wallthk-ctbb.wrap-ctbb.shim;           
                      xpos  =  -tray.height/2+ctbb.slab2x;           
                      _create = AgCreate("BXSA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BXSA              
                            Create("BXSA");               
                      }           
                      { AgPlacement place = AgPlacement("BXSA","BMTC");              
                            /// Add daughter volume BXSA to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(-zpos);              
                            /// Translate z = -zpos              
                            place.par("dx")=ctbb.slabthck/2;              
                            place.par("dy")=ctbb.slabwid/2;              
                            place.par("dz")=ctbb.slab2len/2;              
                            _stacker -> Position( AgBlock::Find("BXSA"), place );              
                      } // end placement of BXSA           
                      zpos = zpos - (ctbb.slab2len + ctbb.convlen)/2;           
                      { AgPlacement place = AgPlacement("BCCV","BMTC");              
                            /// Add daughter volume BCCV to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(-zpos);              
                            /// Translate z = -zpos              
                            place.par("dz")=ctbb.convlen/2;              
                            place.par("dx1")=ctbb.slabthck/2;              
                            place.par("dx2")=ctbb.slabthck/2;              
                            place.par("dy1")=ctbb.convwidm/2;              
                            place.par("dy2")=ctbb.slabwid/2;              
                            place.AlphaX(180);              
                            /// Rotate: AlphaX = 180              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("BCCV"), place );              
                      } // end placement of BCCV           
                      zpos = zpos - (ctbb.convlen + ctbb.pmtlen)/2;           
                      { AgPlacement place = AgPlacement("BCPM","BMTC");              
                            /// Add daughter volume BCPM to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(-zpos);              
                            /// Translate z = -zpos              
                            place.par("dz")=ctbb.pmtlen/2;              
                            place.par("rmin")=ctbb.pmtminr;              
                            place.par("rmax")=ctbb.pmtmaxr;              
                            _stacker -> Position( AgBlock::Find("BCPM"), place );              
                      } // end placement of BCPM           
                      zpos = zpos - (ctbb.pmtlen + ctbb.baselen)/2;           
                      { AgPlacement place = AgPlacement("BCSK","BMTC");              
                            /// Add daughter volume BCSK to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(-zpos);              
                            /// Translate z = -zpos              
                            place.par("dz")=ctbb.baselen/2;              
                            place.par("rmin")=ctbb.baseminr;              
                            place.par("rmax")=ctbb.basemaxr;              
                            _stacker -> Position( AgBlock::Find("BCSK"), place );              
                      } // end placement of BCSK           
                      { AgPlacement place = AgPlacement("BZEL","BMTC");              
                            /// Add daughter volume BZEL to mother BMTC              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateZ(-zpos);              
                            /// Translate z = -zpos              
                            place.par("dx")=ctbb.electhck/2;              
                            place.par("dy")=ctbb.baseminr-0.1;              
                            place.par("dz")=ctbb.baselen/2;              
                            _stacker -> Position( AgBlock::Find("BZEL"), place );              
                      } // end placement of BZEL           
                      END_OF_BMTC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BMTC     
          // ---------------------------------------------------------------------------------------------------     
          void BTTC::Block( AgCreate create )     
          {         
                ///@addtogroup BTTC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BTTC");              
                            attr.par("seen")=0;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Component C	a=12	z=6	w=1           
                      /// Component H2	a=1	z=1	w=2           
                      /// Mixture LastAFoam dens=0.048           
                      {  AgMaterial &mix = AgMaterial::Get("Lastafoam");              
                            mix.Component("C",12,6,1);              
                            mix.Component("H2",1,1,2);              
                            mix.par("dens")=0.048;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.height/2-tray.wallthk;              
                            shape.par("dy")=tray.width/2-tray.wallthk;              
                            shape.par("dz")=tray.length/2-tray.wallthk;              
                            /// Shape Bbox dx=tray.height/2-tray.wallthk dy=tray.width/2-tray.wallthk dz=tray.length/2-tray.wallthk               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BTTC;              
                            _stacker -> Build(this);              
                      }           
                      sublen             = ((toff.slat02z+15.5)-(toff.slat10z-15.5));           
                      subcen             = (toff.slat02z+15.5)-sublen/2.;           
                      iwid=4;           
                      _create = AgCreate("BMAA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BMAA              
                            Create("BMAA");               
                      }           
                      { AgPlacement place = AgPlacement("BMAA","BTTC");              
                            /// Add daughter volume BMAA to mother BTTC              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateZ(subcen);              
                            /// Translate z = subcen              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("BMAA"), place );              
                      } // end placement of BMAA           
                      iwid=5;           
                      _create = AgCreate("BMAA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BMAA              
                            Create("BMAA");               
                      }           
                      { AgPlacement place = AgPlacement("BMAA","BTTC");              
                            /// Add daughter volume BMAA to mother BTTC              
                            place.TranslateX(0.0);              
                            /// Translate x = 0.0              
                            place.TranslateZ(toff.slat01z);              
                            /// Translate z = toff.slat01z              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("BMAA"), place );              
                      } // end placement of BMAA           
                      _create = AgCreate("BCOO");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCOO              
                            Create("BCOO");               
                      }           
                      { AgPlacement place = AgPlacement("BCOO","BTTC");              
                            /// Add daughter volume BCOO to mother BTTC              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            _stacker -> Position( AgBlock::Find("BCOO"), place );              
                      } // end placement of BCOO           
                      _create = AgCreate("BFEE");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BFEE");              
                            create.par("dz")=toff.eleclen/2;              
                            create.par("dx")=toff.electhck/2;              
                            create.par("dy")=toff.elecwid/2;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: dz = toff.eleclen/2              
                            myshape.par("dz")=toff.eleclen/2;              
                            /// Set shape par: dx = toff.electhck/2              
                            myshape.par("dx")=toff.electhck/2;              
                            /// Set shape par: dy = toff.elecwid/2              
                            myshape.par("dy")=toff.elecwid/2;              
                            ///Create BFEE              
                            Create("BFEE");               
                      }           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec01z-toff.eleclen/2);              
                            /// Translate z = toff.elec01z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec02z-toff.eleclen/2);              
                            /// Translate z = toff.elec02z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec03z-toff.eleclen/2);              
                            /// Translate z = toff.elec03z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec04z-toff.eleclen/2);              
                            /// Translate z = toff.elec04z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec05z-toff.eleclen/2);              
                            /// Translate z = toff.elec05z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec06z-toff.eleclen/2);              
                            /// Translate z = toff.elec06z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec07z-toff.eleclen/2);              
                            /// Translate z = toff.elec07z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec08z-toff.eleclen/2);              
                            /// Translate z = toff.elec08z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec09z-toff.eleclen/2);              
                            /// Translate z = toff.elec09z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      { AgPlacement place = AgPlacement("BFEE","BTTC");              
                            /// Add daughter volume BFEE to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateZ(toff.elec10z-toff.eleclen/2);              
                            /// Translate z = toff.elec10z-toff.eleclen/2              
                            _stacker -> Position( AgBlock::Find("BFEE"), place );              
                      } // end placement of BFEE           
                      _create = AgCreate("BPLA");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BPLA");              
                            create.par("dz")=toff.eleclen/2;              
                            create.par("dx")=toff.electhck/2;              
                            create.par("dy")=toff.elecwid/2;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: dz = toff.eleclen/2              
                            myshape.par("dz")=toff.eleclen/2;              
                            /// Set shape par: dx = toff.electhck/2              
                            myshape.par("dx")=toff.electhck/2;              
                            /// Set shape par: dy = toff.elecwid/2              
                            myshape.par("dy")=toff.elecwid/2;              
                            ///Create BPLA              
                            Create("BPLA");               
                      }           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec01z+3.0);              
                            /// Translate z = toff.elec01z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec02z+3.0);              
                            /// Translate z = toff.elec02z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec03z+3.0);              
                            /// Translate z = toff.elec03z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec04z+3.0);              
                            /// Translate z = toff.elec04z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec05z+3.0);              
                            /// Translate z = toff.elec05z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec06z+3.0);              
                            /// Translate z = toff.elec06z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec07z+3.0);              
                            /// Translate z = toff.elec07z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec08z+3.0);              
                            /// Translate z = toff.elec08z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec09z+3.0);              
                            /// Translate z = toff.elec09z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      { AgPlacement place = AgPlacement("BPLA","BTTC");              
                            /// Add daughter volume BPLA to mother BTTC              
                            place.TranslateX(toff.elechgt);              
                            /// Translate x = toff.elechgt              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(toff.elec10z+3.0);              
                            /// Translate z = toff.elec10z+3.0              
                            _stacker -> Position( AgBlock::Find("BPLA"), place );              
                      } // end placement of BPLA           
                      END_OF_BTTC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BTTC     
          // ---------------------------------------------------------------------------------------------------     
          void BUPC::Block( AgCreate create )     
          {         
                ///@addtogroup BUPC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BUPC");              
                            attr.par("seen")=0;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.wallthk/2;              
                            shape.par("dy")=tray.width/2-tray.wallthk;              
                            shape.par("dz")=tray.length/2-tray.wallthk;              
                            /// Shape Bbox dx=tray.wallthk/2 dy=tray.width/2-tray.wallthk dz=tray.length/2-tray.wallthk               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BUPC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BUPC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BUPC     
          // ---------------------------------------------------------------------------------------------------     
          void BRTC::Block( AgCreate create )     
          {         
                ///@addtogroup BRTC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRTC");              
                            attr.par("seen")=0;              
                            attr.par("colo")=5;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material HoneyComb            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Honeycomb");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.height/2-tray.wallthk;              
                            shape.par("dy")=tray.width/2-tray.wallthk;              
                            shape.par("dz")=tray.length/2-tray.wallthk;              
                            /// Shape Bbox dx=tray.height/2-tray.wallthk dy=tray.width/2-tray.wallthk dz=tray.length/2-tray.wallthk               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRTC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BGMT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BGMT              
                            Create("BGMT");               
                      }           
                      { AgPlacement place = AgPlacement("BGMT","BRTC");              
                            /// Add daughter volume BGMT to mother BRTC              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("BGMT"), place );              
                      } // end placement of BGMT           
                      _create = AgCreate("BRMD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BRMD              
                            Create("BRMD");               
                      }           
                      if ( tof==2 )           
                      {              
                            z0 = tray.length/2 - 0.05;              
                            x0 = -3.66;              
                            /// Loop on i from 1 to 33 step=1              
                            for ( i=1; (1>0)? (i<=33):(i>=33); i+=1 )              
                            {                 
                                  { AgPlacement place = AgPlacement("BRMD","BRTC");                    
                                        /// Add daughter volume BRMD to mother BRTC                    
                                        place.TranslateX(x0+modr.mrpcx(i));                    
                                        /// Translate x = x0+modr.mrpcx(i)                    
                                        place.TranslateZ(z0-modr.mrpcz(i));                    
                                        /// Translate z = z0-modr.mrpcz(i)                    
                                        place.AlphaY(modr.mrpca(i));                    
                                        /// Rotate: AlphaY = modr.mrpca(i)                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("BRMD"), place );                    
                                  } // end placement of BRMD                 
                            }              
                      }           
                      else if ( tof==3 )           
                      {              
                            z0 = tray.length/2 - 0.05 - mod4.trayedgez;              
                            x0 = -3.66;              
                            /// Loop on i from 1 to 32 step=1              
                            for ( i=1; (1>0)? (i<=32):(i>=32); i+=1 )              
                            {                 
                                  if ( i<=20||(i>=25&&i<=28) )                 
                                  {                    
                                        { AgPlacement place = AgPlacement("BRMD","BRTC");                       
                                              /// Add daughter volume BRMD to mother BRTC                       
                                              place.TranslateX(x0+mod4.mrpcx(i));                       
                                              /// Translate x = x0+mod4.mrpcx(i)                       
                                              place.TranslateZ(z0-mod4.mrpcz(i));                       
                                              /// Translate z = z0-mod4.mrpcz(i)                       
                                              place.AlphaY(mod4.mrpca(i));                       
                                              /// Rotate: AlphaY = mod4.mrpca(i)                       
                                              /// G3 Reference: thetax = 90                       
                                              /// G3 Reference: phix = 0                       
                                              /// G3 Reference: thetay = 90                       
                                              /// G3 Reference: phiy = 90                       
                                              /// G3 Reference: thetaz = 0                       
                                              /// G3 Reference: phiz = 0                       
                                              _stacker -> Position( AgBlock::Find("BRMD"), place );                       
                                        } // end placement of BRMD                    
                                  }                 
                            }              
                      }           
                      else           
                      {              
                      }           
                      END_OF_BRTC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRTC     
          // ---------------------------------------------------------------------------------------------------     
          void BGMT::Block( AgCreate create )     
          {         
                ///@addtogroup BGMT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BGMT");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material RPCgas            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Rpcgas");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.height/2-tray.wallthk;              
                            shape.par("dy")=tray.width/2-tray.wallthk-modr.hbwid;              
                            shape.par("dz")=tray.length/2-tray.wallthk;              
                            /// Shape Bbox dx=tray.height/2-tray.wallthk dy=tray.width/2-tray.wallthk-modr.hbwid dz=tray.length/2-tray.wallthk               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BGMT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BGMT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BGMT     
          // ---------------------------------------------------------------------------------------------------     
          void BMAA::Block( AgCreate create )     
          {         
                ///@addtogroup BMAA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BMAA");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      if ( iwid==4 )           
                      {              
                            {  AgShape shape = AgShape("Bbox");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("dx")=tray.height/2-tray.wallthk;                 
                                  shape.par("dy")=0.8*toff.boxwidth/2;                 
                                  shape.par("dz")=sublen/2.;                 
                                  /// Shape Bbox dx=tray.height/2-tray.wallthk dy=0.8*toff.boxwidth/2 dz=sublen/2.                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_BMAA;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      else           
                      {              
                            {  AgShape shape = AgShape("Bbox");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("dx")=tray.height/2-tray.wallthk;                 
                                  shape.par("dy")=toff.boxwidth/2;                 
                                  shape.par("dz")=15.5;                 
                                  /// Shape Bbox dx=tray.height/2-tray.wallthk dy=toff.boxwidth/2 dz=15.5                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_BMAA;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      _create = AgCreate("BMTD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BMTD              
                            Create("BMTD");               
                      }           
                      END_OF_BMAA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BMAA     
          // ---------------------------------------------------------------------------------------------------     
          void BMTD::Block( AgCreate create )     
          {         
                ///@addtogroup BMTD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BMTD");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=iwid;              
                            shape.par("iaxis")=2;              
                            /// Shape Division ndiv=iwid iaxis=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BMTD;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BASS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BASS              
                            Create("BASS");               
                      }           
                      if ( iwid==5 )           
                      {              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-1.7);                 
                                  /// Translate x = -1.7                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(5.0);                 
                                  /// Rotate: AlphaY = 5.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                      }           
                      else           
                      {              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-0.4);                 
                                  /// Translate x = -0.4                 
                                  place.TranslateZ(toff.slat02z-subcen);                 
                                  /// Translate z = toff.slat02z-subcen                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(10.0);                 
                                  /// Rotate: AlphaY = 10.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-0.2);                 
                                  /// Translate x = -0.2                 
                                  place.TranslateZ(toff.slat03z-subcen);                 
                                  /// Translate z = toff.slat03z-subcen                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(11.0);                 
                                  /// Rotate: AlphaY = 11.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-0.2);                 
                                  /// Translate x = -0.2                 
                                  place.TranslateZ(toff.slat04z-subcen);                 
                                  /// Translate z = toff.slat04z-subcen                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(11.0);                 
                                  /// Rotate: AlphaY = 11.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-0.2);                 
                                  /// Translate x = -0.2                 
                                  place.TranslateZ(toff.slat05z-subcen);                 
                                  /// Translate z = toff.slat05z-subcen                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(11.0);                 
                                  /// Rotate: AlphaY = 11.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-0.2);                 
                                  /// Translate x = -0.2                 
                                  place.TranslateZ(toff.slat06z-subcen);                 
                                  /// Translate z = toff.slat06z-subcen                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(11.0);                 
                                  /// Rotate: AlphaY = 11.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-0.2);                 
                                  /// Translate x = -0.2                 
                                  place.TranslateZ(toff.slat07z-subcen);                 
                                  /// Translate z = toff.slat07z-subcen                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(11.0);                 
                                  /// Rotate: AlphaY = 11.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-0.2);                 
                                  /// Translate x = -0.2                 
                                  place.TranslateZ(toff.slat08z-subcen);                 
                                  /// Translate z = toff.slat08z-subcen                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(11.0);                 
                                  /// Rotate: AlphaY = 11.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-0.2);                 
                                  /// Translate x = -0.2                 
                                  place.TranslateZ(toff.slat09z-subcen);                 
                                  /// Translate z = toff.slat09z-subcen                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(11.0);                 
                                  /// Rotate: AlphaY = 11.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                            { AgPlacement place = AgPlacement("BASS","BMTD");                 
                                  /// Add daughter volume BASS to mother BMTD                 
                                  place.TranslateX(-0.2);                 
                                  /// Translate x = -0.2                 
                                  place.TranslateZ(toff.slat10z-subcen);                 
                                  /// Translate z = toff.slat10z-subcen                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaY(11.0);                 
                                  /// Rotate: AlphaY = 11.0                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("BASS"), place );                 
                            } // end placement of BASS              
                      }           
                      END_OF_BMTD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BMTD     
          // ---------------------------------------------------------------------------------------------------     
          void BASS::Block( AgCreate create )     
          {         
                ///@addtogroup BASS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BASS");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      totlen = toff.slatlen+toff.pmtlen+toff.baselen;           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=toff.pmtmaxr;              
                            shape.par("dy")=(tray.width/2-tray.wallthk)/5.;              
                            shape.par("dz")=totlen/2.;              
                            /// Shape Bbox dx=toff.pmtmaxr dy=(tray.width/2-tray.wallthk)/5. dz=totlen/2.               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BASS;              
                            _stacker -> Build(this);              
                      }           
                      zpos = -(totlen-toff.slatlen)/2;           
                      _create = AgCreate("BCSB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCSB              
                            Create("BCSB");               
                      }           
                      { AgPlacement place = AgPlacement("BCSB","BASS");              
                            /// Add daughter volume BCSB to mother BASS              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            _stacker -> Position( AgBlock::Find("BCSB"), place );              
                      } // end placement of BCSB           
                      zpos = zpos + (toff.slatlen+toff.pmtlen)/2;           
                      _create = AgCreate("BCPM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCPM              
                            Create("BCPM");               
                      }           
                      { AgPlacement place = AgPlacement("BCPM","BASS");              
                            /// Add daughter volume BCPM to mother BASS              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            place.par("dz")=toff.pmtlen/2;              
                            place.par("rmin")=toff.pmtminr;              
                            place.par("rmax")=toff.pmtmaxr;              
                            _stacker -> Position( AgBlock::Find("BCPM"), place );              
                      } // end placement of BCPM           
                      zpos = zpos + toff.pmtlen/2.;           
                      _create = AgCreate("BTSK");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BTSK              
                            Create("BTSK");               
                      }           
                      { AgPlacement place = AgPlacement("BTSK","BASS");              
                            /// Add daughter volume BTSK to mother BASS              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateZ(zpos+(toff.socklen/2));              
                            /// Translate z = zpos+(toff.socklen/2)              
                            place.par("dz")=toff.socklen/2;              
                            place.par("rmin")=toff.pmtminr;              
                            place.par("rmax")=toff.pmtmaxr;              
                            _stacker -> Position( AgBlock::Find("BTSK"), place );              
                      } // end placement of BTSK           
                      _create = AgCreate("BCEL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCEL              
                            Create("BCEL");               
                      }           
                      { AgPlacement place = AgPlacement("BCEL","BASS");              
                            /// Add daughter volume BCEL to mother BASS              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateZ(zpos+(toff.electhck/2));              
                            /// Translate z = zpos+(toff.electhck/2)              
                            place.par("dz")=toff.electhck/2;              
                            place.par("rmin")=0;              
                            place.par("rmax")=toff.pmtminr;              
                            _stacker -> Position( AgBlock::Find("BCEL"), place );              
                      } // end placement of BCEL           
                      zpos = zpos + toff.baselen/2;           
                      _create = AgCreate("BCEB");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BCEB");              
                            create.par("dz")=toff.baselen/2;              
                            create.par("dx")=toff.electhck/2;              
                            create.par("dy")=toff.cellwid/2;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: dz = toff.baselen/2              
                            myshape.par("dz")=toff.baselen/2;              
                            /// Set shape par: dx = toff.electhck/2              
                            myshape.par("dx")=toff.electhck/2;              
                            /// Set shape par: dy = toff.cellwid/2              
                            myshape.par("dy")=toff.cellwid/2;              
                            ///Create BCEB              
                            Create("BCEB");               
                      }           
                      { AgPlacement place = AgPlacement("BCEB","BASS");              
                            /// Add daughter volume BCEB to mother BASS              
                            place.TranslateX(toff.cellhgt/2);              
                            /// Translate x = toff.cellhgt/2              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            _stacker -> Position( AgBlock::Find("BCEB"), place );              
                      } // end placement of BCEB           
                      { AgPlacement place = AgPlacement("BCEB","BASS");              
                            /// Add daughter volume BCEB to mother BASS              
                            place.TranslateX(-toff.cellhgt/2);              
                            /// Translate x = -toff.cellhgt/2              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            _stacker -> Position( AgBlock::Find("BCEB"), place );              
                      } // end placement of BCEB           
                      zpos = zpos + toff.baselen/2 - 0.6;           
                      _create = AgCreate("BCON");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCON              
                            Create("BCON");               
                      }           
                      { AgPlacement place = AgPlacement("BCON","BASS");              
                            /// Add daughter volume BCON to mother BASS              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ(zpos);              
                            /// Translate z = zpos              
                            place.par("dx")=(toff.cellhgt-toff.electhck)/2;              
                            place.par("dy")=1.25;              
                            place.par("dz")=0.6;              
                            _stacker -> Position( AgBlock::Find("BCON"), place );              
                      } // end placement of BCON           
                      END_OF_BASS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BASS     
          // ---------------------------------------------------------------------------------------------------     
          void BXSA::Block( AgCreate create )     
          {         
                ///@addtogroup BXSA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BXSA");              
                            attr.par("seen")=0;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material polystyren            
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
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=0;              
                            shape.par("dy")=0;              
                            shape.par("dz")=0;              
                            /// Shape Bbox dx=0 dy=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BXSA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BXSA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BXSA     
          // ---------------------------------------------------------------------------------------------------     
          void BCSB::Block( AgCreate create )     
          {         
                ///@addtogroup BCSB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BCSB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material polystyren            
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
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=toff.slatthck/2;              
                            shape.par("dy")=toff.slatwid/2;              
                            shape.par("dz")=toff.slatlen/2;              
                            /// Shape Bbox dx=toff.slatthck/2 dy=toff.slatwid/2 dz=toff.slatlen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BCSB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BCSB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BCSB     
          // ---------------------------------------------------------------------------------------------------     
          void BCCV::Block( AgCreate create )     
          {         
                ///@addtogroup BCCV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BCCV");              
                            attr.par("seen")=0;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Trd2");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx1")=0;              
                            shape.par("dx2")=0;              
                            shape.par("dy1")=0;              
                            shape.par("dy2")=0;              
                            shape.par("dz")=0;              
                            /// Shape Trd2 dx1=0 dx2=0 dy1=0 dy2=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BCCV;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BCCV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BCCV     
          // ---------------------------------------------------------------------------------------------------     
          void BCSK::Block( AgCreate create )     
          {         
                ///@addtogroup BCSK_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BCSK");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
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
                            if (_same_shape) goto END_OF_BCSK;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BCSK:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BCSK     
          // ---------------------------------------------------------------------------------------------------     
          void BZEL::Block( AgCreate create )     
          {         
                ///@addtogroup BZEL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BZEL");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material silicon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Silicon");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=0;              
                            shape.par("dy")=0;              
                            shape.par("dz")=0;              
                            /// Shape Bbox dx=0 dy=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BZEL;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BZEL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BZEL     
          // ---------------------------------------------------------------------------------------------------     
          void BCPM::Block( AgCreate create )     
          {         
                ///@addtogroup BCPM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BCPM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
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
                            if (_same_shape) goto END_OF_BCPM;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BCPM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BCPM     
          // ---------------------------------------------------------------------------------------------------     
          void BTSK::Block( AgCreate create )     
          {         
                ///@addtogroup BTSK_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BTSK");              
                            attr.par("seen")=0;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
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
                            if (_same_shape) goto END_OF_BTSK;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BTSK:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BTSK     
          // ---------------------------------------------------------------------------------------------------     
          void BCEL::Block( AgCreate create )     
          {         
                ///@addtogroup BCEL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BCEL");              
                            attr.par("seen")=0;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
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
                            if (_same_shape) goto END_OF_BCEL;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BCEL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BCEL     
          // ---------------------------------------------------------------------------------------------------     
          void BCEB::Block( AgCreate create )     
          {         
                ///@addtogroup BCEB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BCEL");              
                            attr.par("seen")=0;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=0;              
                            shape.par("dy")=0;              
                            shape.par("dz")=0;              
                            /// Shape Bbox dx=0 dy=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BCEB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BCEB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BCEB     
          // ---------------------------------------------------------------------------------------------------     
          void BPLA::Block( AgCreate create )     
          {         
                ///@addtogroup BPLA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BPLA");              
                            attr.par("seen")=0;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=0;              
                            shape.par("dy")=0;              
                            shape.par("dz")=0;              
                            /// Shape Bbox dx=0 dy=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BPLA;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BCON");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCON              
                            Create("BCON");               
                      }           
                      { AgPlacement place = AgPlacement("BCON","BPLA");              
                            /// Add daughter volume BCON to mother BPLA              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ((-0.5*2.54)/2);              
                            /// Translate z = (-0.5*2.54)/2              
                            place.par("dx")=0.08*2.54/2;              
                            place.par("dy")=tray.width/2-tray.wallthk-0.5;              
                            place.par("dz")=0.5*2.54/2;              
                            _stacker -> Position( AgBlock::Find("BCON"), place );              
                      } // end placement of BCON           
                      { AgPlacement place = AgPlacement("BCON","BPLA");              
                            /// Add daughter volume BCON to mother BPLA              
                            place.TranslateX((-0.08*2.54-0.25*2.54)/2);              
                            /// Translate x = (-0.08*2.54-0.25*2.54)/2              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ((-0.08*2.54)/2);              
                            /// Translate z = (-0.08*2.54)/2              
                            place.par("dx")=0.25*2.54/2;              
                            place.par("dy")=tray.width/2-tray.wallthk-2.0;              
                            place.par("dz")=0.08*2.54/2;              
                            _stacker -> Position( AgBlock::Find("BCON"), place );              
                      } // end placement of BCON           
                      END_OF_BPLA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BPLA     
          // ---------------------------------------------------------------------------------------------------     
          void BCON::Block( AgCreate create )     
          {         
                ///@addtogroup BCON_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BCON");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material polystyren            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=0;              
                            shape.par("dy")=0;              
                            shape.par("dz")=0;              
                            /// Shape Bbox dx=0 dy=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BCON;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BCON:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BCON     
          // ---------------------------------------------------------------------------------------------------     
          void BFEE::Block( AgCreate create )     
          {         
                ///@addtogroup BFEE_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BFEE");              
                            attr.par("seen")=0;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=toff.electhck/2;              
                            shape.par("dy")=toff.elecwid/2;              
                            shape.par("dz")=toff.eleclen/2;              
                            /// Shape Bbox dx=toff.electhck/2 dy=toff.elecwid/2 dz=toff.eleclen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BFEE;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BLEM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BLEM              
                            Create("BLEM");               
                      }           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(-7.0);              
                            /// Translate y = -7.0              
                            place.TranslateZ(2);              
                            /// Translate z = 2              
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(-3.5);              
                            /// Translate y = -3.5              
                            place.TranslateZ(2);              
                            /// Translate z = 2              
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
                            place.TranslateZ(2);              
                            /// Translate z = 2              
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(3.5);              
                            /// Translate y = 3.5              
                            place.TranslateZ(2);              
                            /// Translate z = 2              
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(7);              
                            /// Translate y = 7              
                            place.TranslateZ(2);              
                            /// Translate z = 2              
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(-7.0);              
                            /// Translate y = -7.0              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(-3.5);              
                            /// Translate y = -3.5              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(0.);              
                            /// Translate y = 0.              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(3.5);              
                            /// Translate y = 3.5              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(7);              
                            /// Translate y = 7              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(-6.0);              
                            /// Translate y = -6.0              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(-2.5);              
                            /// Translate y = -2.5              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(1.);              
                            /// Translate y = 1.              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(4.5);              
                            /// Translate y = 4.5              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      { AgPlacement place = AgPlacement("BLEM","BFEE");              
                            /// Add daughter volume BLEM to mother BFEE              
                            place.TranslateX(toff.electhck+(0.7/2));              
                            /// Translate x = toff.electhck+(0.7/2)              
                            place.TranslateY(8.);              
                            /// Translate y = 8.              
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
                            _stacker -> Position( AgBlock::Find("BLEM"), place );              
                      } // end placement of BLEM           
                      END_OF_BFEE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BFEE     
          // ---------------------------------------------------------------------------------------------------     
          void BLEM::Block( AgCreate create )     
          {         
                ///@addtogroup BLEM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BLEM");              
                            attr.par("seen")=0;              
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
                            if (_same_shape) goto END_OF_BLEM;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BPIP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BPIP              
                            Create("BPIP");               
                      }           
                      { AgPlacement place = AgPlacement("BPIP","BLEM");              
                            /// Add daughter volume BPIP to mother BLEM              
                            place.TranslateX((0.9-0.72)/2);              
                            /// Translate x = (0.9-0.72)/2              
                            place.TranslateY(0);              
                            /// Translate y = 0              
                            place.TranslateZ((0.8+1.0)/2);              
                            /// Translate z = (0.8+1.0)/2              
                            place.par("dz")=2.0/2;              
                            place.par("rmin")=0.62/2;              
                            place.par("rmax")=0.68/2;              
                            _stacker -> Position( AgBlock::Find("BPIP"), place );              
                      } // end placement of BPIP           
                      END_OF_BLEM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BLEM     
          // ---------------------------------------------------------------------------------------------------     
          void BCOO::Block( AgCreate create )     
          {         
                ///@addtogroup BCOO_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BCOO");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=0;              
                            shape.par("dy")=0;              
                            shape.par("dz")=0;              
                            /// Shape Bbox dx=0 dy=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BCOO;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BRAI");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BRAI");              
                            create.par("dz")=tray.length/2-tray.wallthk;              
                            create.par("dx")=toff.railthck/2;              
                            create.par("dy")=toff.railwid/2;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: dz = tray.length/2-tray.wallthk              
                            myshape.par("dz")=tray.length/2-tray.wallthk;              
                            /// Set shape par: dx = toff.railthck/2              
                            myshape.par("dx")=toff.railthck/2;              
                            /// Set shape par: dy = toff.railwid/2              
                            myshape.par("dy")=toff.railwid/2;              
                            ///Create BRAI              
                            Create("BRAI");               
                      }           
                      { AgPlacement place = AgPlacement("BRAI","BCOO");              
                            /// Add daughter volume BRAI to mother BCOO              
                            place.TranslateX(toff.elechgt-toff.railthck);              
                            /// Translate x = toff.elechgt-toff.railthck              
                            place.TranslateY((tray.width/2-toff.railwid/2-tray.wallthk));              
                            /// Translate y = (tray.width/2-toff.railwid/2-tray.wallthk)              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("BRAI"), place );              
                      } // end placement of BRAI           
                      { AgPlacement place = AgPlacement("BRAI","BCOO");              
                            /// Add daughter volume BRAI to mother BCOO              
                            place.TranslateX(toff.elechgt-toff.railwid/2-toff.railthck/2);              
                            /// Translate x = toff.elechgt-toff.railwid/2-toff.railthck/2              
                            place.TranslateY((tray.width/2-toff.railthck/2-tray.wallthk));              
                            /// Translate y = (tray.width/2-toff.railthck/2-tray.wallthk)              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            place.AlphaZ(90);              
                            /// Rotate: AlphaZ = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("BRAI"), place );              
                      } // end placement of BRAI           
                      { AgPlacement place = AgPlacement("BRAI","BCOO");              
                            /// Add daughter volume BRAI to mother BCOO              
                            place.TranslateX(toff.elechgt-toff.railthck);              
                            /// Translate x = toff.elechgt-toff.railthck              
                            place.TranslateY(-(tray.width/2-toff.railwid/2-tray.wallthk));              
                            /// Translate y = -(tray.width/2-toff.railwid/2-tray.wallthk)              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("BRAI"), place );              
                      } // end placement of BRAI           
                      { AgPlacement place = AgPlacement("BRAI","BCOO");              
                            /// Add daughter volume BRAI to mother BCOO              
                            place.TranslateX(toff.elechgt-toff.railwid/2-toff.railthck/2);              
                            /// Translate x = toff.elechgt-toff.railwid/2-toff.railthck/2              
                            place.TranslateY(-(tray.width/2-toff.railthck/2-tray.wallthk));              
                            /// Translate y = -(tray.width/2-toff.railthck/2-tray.wallthk)              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            place.AlphaZ(90);              
                            /// Rotate: AlphaZ = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("BRAI"), place );              
                      } // end placement of BRAI           
                      _create = AgCreate("BPIP");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BPIP");              
                            create.par("rmax")=toff.cooloutr;              
                            create.par("rmin")=toff.coolinnr;              
                            create.par("dz")=tray.length/2-tray.wallthk;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: rmax = toff.cooloutr              
                            myshape.par("rmax")=toff.cooloutr;              
                            /// Set shape par: rmin = toff.coolinnr              
                            myshape.par("rmin")=toff.coolinnr;              
                            /// Set shape par: dz = tray.length/2-tray.wallthk              
                            myshape.par("dz")=tray.length/2-tray.wallthk;              
                            ///Create BPIP              
                            Create("BPIP");               
                      }           
                      { AgPlacement place = AgPlacement("BPIP","BCOO");              
                            /// Add daughter volume BPIP to mother BCOO              
                            place.TranslateX(toff.elechgt-3.*toff.railthck/2.-toff.cooloutr);              
                            /// Translate x = toff.elechgt-3.*toff.railthck/2.-toff.cooloutr              
                            place.TranslateY((tray.width/2-toff.railthck-tray.wallthk-toff.cooloutr));              
                            /// Translate y = (tray.width/2-toff.railthck-tray.wallthk-toff.cooloutr)              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("BPIP"), place );              
                      } // end placement of BPIP           
                      { AgPlacement place = AgPlacement("BPIP","BCOO");              
                            /// Add daughter volume BPIP to mother BCOO              
                            place.TranslateX(toff.elechgt-3.*toff.railthck/2.-toff.cooloutr);              
                            /// Translate x = toff.elechgt-3.*toff.railthck/2.-toff.cooloutr              
                            place.TranslateY(-(tray.width/2-toff.railthck-tray.wallthk-toff.cooloutr));              
                            /// Translate y = -(tray.width/2-toff.railthck-tray.wallthk-toff.cooloutr)              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("BPIP"), place );              
                      } // end placement of BPIP           
                      _create = AgCreate("BPIQ");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BPIQ");              
                            create.par("rmax")=toff.cooloutr;              
                            create.par("rmin")=toff.coolinnr;              
                            create.par("dz")=tray.width/2-tray.wallthk-2.*toff.cooloutr-toff.railthck;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: rmax = toff.cooloutr              
                            myshape.par("rmax")=toff.cooloutr;              
                            /// Set shape par: rmin = toff.coolinnr              
                            myshape.par("rmin")=toff.coolinnr;              
                            /// Set shape par: dz = tray.width/2-tray.wallthk-2.*toff.cooloutr-toff.railthck              
                            myshape.par("dz")=tray.width/2-tray.wallthk-2.*toff.cooloutr-toff.railthck;              
                            ///Create BPIQ              
                            Create("BPIQ");               
                      }           
                      { AgPlacement place = AgPlacement("BPIQ","BCOO");              
                            /// Add daughter volume BPIQ to mother BCOO              
                            place.TranslateX(toff.elechgt-3.*toff.railthck/2.-toff.cooloutr);              
                            /// Translate x = toff.elechgt-3.*toff.railthck/2.-toff.cooloutr              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(tray.length/2-tray.wallthk-toff.railthck-toff.cooloutr);              
                            /// Translate z = tray.length/2-tray.wallthk-toff.railthck-toff.cooloutr              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            place.AlphaX(90);              
                            /// Rotate: AlphaX = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("BPIQ"), place );              
                      } // end placement of BPIQ           
                      _create = AgCreate("BWAT");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BWAT");              
                            create.par("rmax")=toff.coolinnr;              
                            create.par("rmin")=0;              
                            create.par("dz")=tray.length/2-tray.wallthk;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: rmax = toff.coolinnr              
                            myshape.par("rmax")=toff.coolinnr;              
                            /// Set shape par: rmin = 0              
                            myshape.par("rmin")=0;              
                            /// Set shape par: dz = tray.length/2-tray.wallthk              
                            myshape.par("dz")=tray.length/2-tray.wallthk;              
                            ///Create BWAT              
                            Create("BWAT");               
                      }           
                      { AgPlacement place = AgPlacement("BWAT","BCOO");              
                            /// Add daughter volume BWAT to mother BCOO              
                            place.TranslateX(toff.elechgt-3.*toff.railthck/2.-toff.cooloutr);              
                            /// Translate x = toff.elechgt-3.*toff.railthck/2.-toff.cooloutr              
                            place.TranslateY((tray.width/2-toff.railthck-tray.wallthk-toff.cooloutr));              
                            /// Translate y = (tray.width/2-toff.railthck-tray.wallthk-toff.cooloutr)              
                            _stacker -> Position( AgBlock::Find("BWAT"), place );              
                      } // end placement of BWAT           
                      { AgPlacement place = AgPlacement("BWAT","BCOO");              
                            /// Add daughter volume BWAT to mother BCOO              
                            place.TranslateX(toff.elechgt-3.*toff.railthck/2.-toff.cooloutr);              
                            /// Translate x = toff.elechgt-3.*toff.railthck/2.-toff.cooloutr              
                            place.TranslateY(-(tray.width/2-toff.railthck-tray.wallthk-toff.cooloutr));              
                            /// Translate y = -(tray.width/2-toff.railthck-tray.wallthk-toff.cooloutr)              
                            _stacker -> Position( AgBlock::Find("BWAT"), place );              
                      } // end placement of BWAT           
                      _create = AgCreate("BWAT");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BWAT");              
                            create.par("rmax")=toff.coolinnr;              
                            create.par("rmin")=0;              
                            create.par("dz")=tray.width/2-tray.wallthk-2.*toff.cooloutr-toff.railthck;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: rmax = toff.coolinnr              
                            myshape.par("rmax")=toff.coolinnr;              
                            /// Set shape par: rmin = 0              
                            myshape.par("rmin")=0;              
                            /// Set shape par: dz = tray.width/2-tray.wallthk-2.*toff.cooloutr-toff.railthck              
                            myshape.par("dz")=tray.width/2-tray.wallthk-2.*toff.cooloutr-toff.railthck;              
                            ///Create BWAT              
                            Create("BWAT");               
                      }           
                      { AgPlacement place = AgPlacement("BWAT","BCOO");              
                            /// Add daughter volume BWAT to mother BCOO              
                            place.TranslateX(toff.elechgt-3.*toff.railthck/2.-toff.cooloutr);              
                            /// Translate x = toff.elechgt-3.*toff.railthck/2.-toff.cooloutr              
                            place.TranslateY(0.0);              
                            /// Translate y = 0.0              
                            place.TranslateZ(tray.length/2-tray.wallthk-toff.railthck-toff.cooloutr);              
                            /// Translate z = tray.length/2-tray.wallthk-toff.railthck-toff.cooloutr              
                            place.AlphaX(90);              
                            /// Rotate: AlphaX = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("BWAT"), place );              
                      } // end placement of BWAT           
                      END_OF_BCOO:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BCOO     
          // ---------------------------------------------------------------------------------------------------     
          void BRAI::Block( AgCreate create )     
          {         
                ///@addtogroup BRAI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRAI");              
                            attr.par("seen")=0;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=0.0;              
                            shape.par("dy")=0.0;              
                            shape.par("dz")=0.0;              
                            /// Shape Bbox dx=0.0 dy=0.0 dz=0.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRAI;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BRAI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRAI     
          // ---------------------------------------------------------------------------------------------------     
          void BPIP::Block( AgCreate create )     
          {         
                ///@addtogroup BPIP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BPIP");              
                            attr.par("seen")=0;              
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
                            if (_same_shape) goto END_OF_BPIP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BPIP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BPIP     
          // ---------------------------------------------------------------------------------------------------     
          void BPIQ::Block( AgCreate create )     
          {         
                ///@addtogroup BPIQ_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BPIQ");              
                            attr.par("seen")=0;              
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
                            if (_same_shape) goto END_OF_BPIQ;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BPIQ:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BPIQ     
          // ---------------------------------------------------------------------------------------------------     
          void BUND::Block( AgCreate create )     
          {         
                ///@addtogroup BUND_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BUND");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.par("serial")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.supfullh/2;              
                            shape.par("dy")=tray.width/2;              
                            shape.par("dz")=tray.suplen/2;              
                            /// Shape Bbox dx=tray.supfullh/2 dy=tray.width/2 dz=tray.suplen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BUND;              
                            _stacker -> Build(this);              
                      }           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      xpos = (tray.supfullh - tray.footthk)/2;           
                      ypos = (tray.width - tray.foot1len)/2 - tray.footinse;           
                      _create = AgCreate("BTFT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BTFT              
                            Create("BTFT");               
                      }           
                      { AgPlacement place = AgPlacement("BTFT","BUND");              
                            /// Add daughter volume BTFT to mother BUND              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateY(-ypos);              
                            /// Translate y = -ypos              
                            place.par("dx")=tray.footthk/2;              
                            place.par("dy")=tray.foot1len/2;              
                            _stacker -> Position( AgBlock::Find("BTFT"), place );              
                      } // end placement of BTFT           
                      { AgPlacement place = AgPlacement("BTFT","BUND");              
                            /// Add daughter volume BTFT to mother BUND              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateY(+ypos);              
                            /// Translate y = +ypos              
                            place.par("dx")=tray.footthk/2;              
                            place.par("dy")=tray.foot1len/2;              
                            _stacker -> Position( AgBlock::Find("BTFT"), place );              
                      } // end placement of BTFT           
                      xpos = (tray.supfullh - tray.foot2thk)/2;           
                      ypos = ypos - (tray.foot1len + tray.footthk)/2;           
                      { AgPlacement place = AgPlacement("BTFT","BUND");              
                            /// Add daughter volume BTFT to mother BUND              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateY(-ypos);              
                            /// Translate y = -ypos              
                            place.par("dx")=tray.foot2thk/2;              
                            place.par("dy")=tray.footthk/2;              
                            _stacker -> Position( AgBlock::Find("BTFT"), place );              
                      } // end placement of BTFT           
                      { AgPlacement place = AgPlacement("BTFT","BUND");              
                            /// Add daughter volume BTFT to mother BUND              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateY(+ypos);              
                            /// Translate y = +ypos              
                            place.par("dx")=tray.foot2thk/2;              
                            place.par("dy")=tray.footthk/2;              
                            _stacker -> Position( AgBlock::Find("BTFT"), place );              
                      } // end placement of BTFT           
                      xpos = (tray.supfullh + tray.footthk)/2 - tray.foot2thk;           
                      ypos = ypos - (tray.footthk + tray.foot3len)/2;           
                      { AgPlacement place = AgPlacement("BTFT","BUND");              
                            /// Add daughter volume BTFT to mother BUND              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateY(-ypos);              
                            /// Translate y = -ypos              
                            place.par("dx")=tray.footthk/2;              
                            place.par("dy")=tray.foot3len/2;              
                            _stacker -> Position( AgBlock::Find("BTFT"), place );              
                      } // end placement of BTFT           
                      { AgPlacement place = AgPlacement("BTFT","BUND");              
                            /// Add daughter volume BTFT to mother BUND              
                            place.TranslateX(xpos);              
                            /// Translate x = xpos              
                            place.TranslateY(+ypos);              
                            /// Translate y = +ypos              
                            place.par("dx")=tray.footthk/2;              
                            place.par("dy")=tray.foot3len/2;              
                            _stacker -> Position( AgBlock::Find("BTFT"), place );              
                      } // end placement of BTFT           
                      support_aile_width = ( tray.supfullh-tray.suparmt )/tan(60*degrad);           
                      support_arm_width  = ( tray.supfullw-tray.supbasew)/2-support_aile_width;           
                      support_aile_ypos  = ( tray.supbasew+support_aile_width)/2;           
                      support_arm_xpos   = ( tray.supfullh-tray.suparmt )/2;           
                      support_arm_ypos   = ( tray.supfullw-support_arm_width)/2;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      _create = AgCreate("BASE");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BASE              
                            Create("BASE");               
                      }           
                      { AgPlacement place = AgPlacement("BASE","BUND");              
                            /// Add daughter volume BASE to mother BUND              
                            place.TranslateX((-tray.supfullh+tray.supbaset)/2);              
                            /// Translate x = (-tray.supfullh+tray.supbaset)/2              
                            _stacker -> Position( AgBlock::Find("BASE"), place );              
                      } // end placement of BASE           
                      _create = AgCreate("BARM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BARM              
                            Create("BARM");               
                      }           
                      { AgPlacement place = AgPlacement("BARM","BUND");              
                            /// Add daughter volume BARM to mother BUND              
                            place.TranslateX(support_arm_xpos);              
                            /// Translate x = support_arm_xpos              
                            place.TranslateY(-support_arm_ypos);              
                            /// Translate y = -support_arm_ypos              
                            _stacker -> Position( AgBlock::Find("BARM"), place );              
                      } // end placement of BARM           
                      { AgPlacement place = AgPlacement("BARM","BUND");              
                            /// Add daughter volume BARM to mother BUND              
                            place.TranslateX(support_arm_xpos);              
                            /// Translate x = support_arm_xpos              
                            place.TranslateY(+support_arm_ypos);              
                            /// Translate y = +support_arm_ypos              
                            _stacker -> Position( AgBlock::Find("BARM"), place );              
                      } // end placement of BARM           
                      _create = AgCreate("BANG");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BANG              
                            Create("BANG");               
                      }           
                      { AgPlacement place = AgPlacement("BANG","BUND");              
                            /// Add daughter volume BANG to mother BUND              
                            place.TranslateY(-support_aile_ypos);              
                            /// Translate y = -support_aile_ypos              
                            _stacker -> Position( AgBlock::Find("BANG"), place );              
                      } // end placement of BANG           
                      { AgPlacement place = AgPlacement("BANG","BUND");              
                            /// Add daughter volume BANG to mother BUND              
                            place.TranslateY(+support_aile_ypos);              
                            /// Translate y = +support_aile_ypos              
                            /// G3 Reference: thetax = 270              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=270,_phix=0,_thetay=90,_phiy=90,_thetaz=0,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("BANG"), place );              
                      } // end placement of BANG           
                      _create = AgCreate("BCOV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BCOV              
                            Create("BCOV");               
                      }           
                      { AgPlacement place = AgPlacement("BCOV","BUND");              
                            /// Add daughter volume BCOV to mother BUND              
                            place.TranslateX(-tray.supfullh/2+tray.cooloutr);              
                            /// Translate x = -tray.supfullh/2+tray.cooloutr              
                            _stacker -> Position( AgBlock::Find("BCOV"), place );              
                      } // end placement of BCOV           
                      END_OF_BUND:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BUND     
          // ---------------------------------------------------------------------------------------------------     
          void BTFT::Block( AgCreate create )     
          {         
                ///@addtogroup BTFT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BTFT");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=0.0;              
                            shape.par("dy")=0.0;              
                            shape.par("dz")=0.0;              
                            /// Shape Bbox dx=0.0 dy=0.0 dz=0.0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BTFT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BTFT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BTFT     
          // ---------------------------------------------------------------------------------------------------     
          void BARM::Block( AgCreate create )     
          {         
                ///@addtogroup BARM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BARM");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.suparmt/2;              
                            shape.par("dy")=support_arm_width/2;              
                            /// Shape Bbox dx=tray.suparmt/2 dy=support_arm_width/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BARM;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BARM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BARM     
          // ---------------------------------------------------------------------------------------------------     
          void BANG::Block( AgCreate create )     
          {         
                ///@addtogroup BANG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BANG");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Para");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.suparmt/2;              
                            shape.par("dy")=support_aile_width/2;              
                            shape.par("alph")=-60;              
                            shape.par("thet")=0;              
                            shape.par("phi")=0;              
                            /// Shape Para dx=tray.suparmt/2 dy=support_aile_width/2 alph=-60 thet=0 phi=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BANG;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BANG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BANG     
          // ---------------------------------------------------------------------------------------------------     
          void BASE::Block( AgCreate create )     
          {         
                ///@addtogroup BASE_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BASE");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tray.supbaset/2;              
                            shape.par("dy")=tray.supbasew/2;              
                            /// Shape Bbox dx=tray.supbaset/2 dy=tray.supbasew/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BASE;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BASE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BASE     
          // ---------------------------------------------------------------------------------------------------     
          void BCOV::Block( AgCreate create )     
          {         
                ///@addtogroup BCOV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BCOV");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=tray.cooloutr;              
                            /// Shape Tube rmin=0 rmax=tray.cooloutr               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BCOV;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BWAT");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BWAT");              
                            create.par("rmin")=0;              
                            create.par("rmax")=tray.coolinnr;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: rmin = 0              
                            myshape.par("rmin")=0;              
                            /// Set shape par: rmax = tray.coolinnr              
                            myshape.par("rmax")=tray.coolinnr;              
                            ///Create BWAT              
                            Create("BWAT");               
                      }           
                      { AgPlacement place = AgPlacement("BWAT","BCOV");              
                            /// Add daughter volume BWAT to mother BCOV              
                            _stacker -> Position( AgBlock::Find("BWAT"), place );              
                      } // end placement of BWAT           
                      END_OF_BCOV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BCOV     
          // ---------------------------------------------------------------------------------------------------     
          void BWAT::Block( AgCreate create )     
          {         
                ///@addtogroup BWAT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BWAT");              
                            attr.par("seen")=0;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
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
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0;              
                            shape.par("rmax")=0;              
                            /// Shape Tube rmin=0 rmax=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BWAT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BWAT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BWAT     
          // ---------------------------------------------------------------------------------------------------     
          void BRMD::Block( AgCreate create )     
          {         
                ///@addtogroup BRMD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRMD");              
                            attr.par("seen")=0;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material RPCgas            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Rpcgas");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=modr.height/2;              
                            shape.par("dy")=modr.width/2;              
                            shape.par("dz")=modr.length/2;              
                            /// Shape Bbox dx=modr.height/2 dy=modr.width/2 dz=modr.length/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRMD;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BRHC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BRHC              
                            Create("BRHC");               
                      }           
                      _create = AgCreate("BRCB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BRCB              
                            Create("BRCB");               
                      }           
                      _create = AgCreate("BRMY");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BRMY              
                            Create("BRMY");               
                      }           
                      _create = AgCreate("BRGR");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BRGR              
                            Create("BRGR");               
                      }           
                      _create = AgCreate("BROG");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BROG              
                            Create("BROG");               
                      }           
                      dthgt = (modr.ighgt+modr.sprmax*2)*(modr.ngap-1)+modr.sprmax*2;           
                      _create = AgCreate("BRDT");           
                      { // Paramters passed in via the Create operatir              
                            AgCreate create("BRDT");              
                            create.par("dz")=modr.iglen/2.;              
                            create.par("dx")=dthgt/2.;              
                            create.par("dy")=modr.igwid/2.;              
                            _create = create;              
                      }           
                      {              
                            AgShape myshape; // undefined shape              
                            /// Set shape par: dz = modr.iglen/2.              
                            myshape.par("dz")=modr.iglen/2.;              
                            /// Set shape par: dx = dthgt/2.              
                            myshape.par("dx")=dthgt/2.;              
                            /// Set shape par: dy = modr.igwid/2.              
                            myshape.par("dy")=modr.igwid/2.;              
                            ///Create BRDT              
                            Create("BRDT");               
                      }           
                      _create = AgCreate("BRWG");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BRWG              
                            Create("BRWG");               
                      }           
                      xpos = modr.height/2.;           
                      y = 0.;           
                      z = modr.center;           
                      { AgPlacement place = AgPlacement("BRHC","BRMD");              
                            /// Add daughter volume BRHC to mother BRMD              
                            place.TranslateX(xpos-modr.hchgt/2);              
                            /// Translate x = xpos-modr.hchgt/2              
                            place.TranslateZ(modr.center);              
                            /// Translate z = modr.center              
                            _stacker -> Position( AgBlock::Find("BRHC"), place );              
                      } // end placement of BRHC           
                      xpos = xpos - modr.hchgt;           
                      { AgPlacement place = AgPlacement("BRCB","BRMD");              
                            /// Add daughter volume BRCB to mother BRMD              
                            place.TranslateX(xpos-modr.pcbhgt/2);              
                            /// Translate x = xpos-modr.pcbhgt/2              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("BRCB"), place );              
                      } // end placement of BRCB           
                      xpos = xpos - modr.pcbhgt;           
                      { AgPlacement place = AgPlacement("BRMY","BRMD");              
                            /// Add daughter volume BRMY to mother BRMD              
                            place.TranslateX(xpos-modr.myhgt/2);              
                            /// Translate x = xpos-modr.myhgt/2              
                            place.TranslateZ(modr.center);              
                            /// Translate z = modr.center              
                            _stacker -> Position( AgBlock::Find("BRMY"), place );              
                      } // end placement of BRMY           
                      xpos = xpos - modr.myhgt;           
                      { AgPlacement place = AgPlacement("BRGR","BRMD");              
                            /// Add daughter volume BRGR to mother BRMD              
                            place.TranslateX(xpos-modr.grhgt/2);              
                            /// Translate x = xpos-modr.grhgt/2              
                            _stacker -> Position( AgBlock::Find("BRGR"), place );              
                      } // end placement of BRGR           
                      xpos = xpos - modr.grhgt;           
                      { AgPlacement place = AgPlacement("BROG","BRMD");              
                            /// Add daughter volume BROG to mother BRMD              
                            place.TranslateX(xpos-modr.oghgt/2);              
                            /// Translate x = xpos-modr.oghgt/2              
                            _stacker -> Position( AgBlock::Find("BROG"), place );              
                      } // end placement of BROG           
                      xpos = xpos - modr.oghgt;           
                      { AgPlacement place = AgPlacement("BRDT","BRMD");              
                            /// Add daughter volume BRDT to mother BRMD              
                            place.TranslateX(xpos-dthgt/2);              
                            /// Translate x = xpos-dthgt/2              
                            _stacker -> Position( AgBlock::Find("BRDT"), place );              
                      } // end placement of BRDT           
                      xpos = xpos - dthgt;           
                      { AgPlacement place = AgPlacement("BROG","BRMD");              
                            /// Add daughter volume BROG to mother BRMD              
                            place.TranslateX(xpos-modr.oghgt/2);              
                            /// Translate x = xpos-modr.oghgt/2              
                            _stacker -> Position( AgBlock::Find("BROG"), place );              
                      } // end placement of BROG           
                      xpos = xpos - modr.oghgt;           
                      { AgPlacement place = AgPlacement("BRGR","BRMD");              
                            /// Add daughter volume BRGR to mother BRMD              
                            place.TranslateX(xpos-modr.grhgt/2);              
                            /// Translate x = xpos-modr.grhgt/2              
                            _stacker -> Position( AgBlock::Find("BRGR"), place );              
                      } // end placement of BRGR           
                      xpos = xpos - modr.grhgt;           
                      { AgPlacement place = AgPlacement("BRMY","BRMD");              
                            /// Add daughter volume BRMY to mother BRMD              
                            place.TranslateX(xpos-modr.myhgt/2);              
                            /// Translate x = xpos-modr.myhgt/2              
                            _stacker -> Position( AgBlock::Find("BRMY"), place );              
                      } // end placement of BRMY           
                      xpos = xpos - modr.myhgt;           
                      { AgPlacement place = AgPlacement("BRCB","BRMD");              
                            /// Add daughter volume BRCB to mother BRMD              
                            place.TranslateX(xpos-modr.pcbhgt/2);              
                            /// Translate x = xpos-modr.pcbhgt/2              
                            place.TranslateZ(0.);              
                            /// Translate z = 0.              
                            _stacker -> Position( AgBlock::Find("BRCB"), place );              
                      } // end placement of BRCB           
                      xpos = xpos - modr.pcbhgt;           
                      { AgPlacement place = AgPlacement("BRHC","BRMD");              
                            /// Add daughter volume BRHC to mother BRMD              
                            place.TranslateX(xpos-modr.hchgt/2);              
                            /// Translate x = xpos-modr.hchgt/2              
                            place.TranslateZ(modr.center);              
                            /// Translate z = modr.center              
                            _stacker -> Position( AgBlock::Find("BRHC"), place );              
                      } // end placement of BRHC           
                      xpos = xpos - modr.hchgt;           
                      END_OF_BRMD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRMD     
          // ---------------------------------------------------------------------------------------------------     
          void BRHC::Block( AgCreate create )     
          {         
                ///@addtogroup BRHC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRHC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material HoneyComb            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Honeycomb");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=modr.hchgt/2;              
                            shape.par("dy")=modr.hcwid/2;              
                            shape.par("dz")=modr.hclen/2;              
                            /// Shape Bbox dx=modr.hchgt/2 dy=modr.hcwid/2 dz=modr.hclen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRHC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BRHC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRHC     
          // ---------------------------------------------------------------------------------------------------     
          void BRCB::Block( AgCreate create )     
          {         
                ///@addtogroup BRCB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRCB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=modr.pcbhgt/2;              
                            shape.par("dy")=modr.pcbwid/2;              
                            shape.par("dz")=modr.pcblen/2;              
                            /// Shape Bbox dx=modr.pcbhgt/2 dy=modr.pcbwid/2 dz=modr.pcblen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRCB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BRCB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRCB     
          // ---------------------------------------------------------------------------------------------------     
          void BRMY::Block( AgCreate create )     
          {         
                ///@addtogroup BRMY_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRMY");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material MYLAR            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=modr.myhgt/2;              
                            shape.par("dy")=modr.mywid/2;              
                            shape.par("dz")=modr.mylen/2;              
                            /// Shape Bbox dx=modr.myhgt/2 dy=modr.mywid/2 dz=modr.mylen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRMY;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BRMY:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRMY     
          // ---------------------------------------------------------------------------------------------------     
          void BRGR::Block( AgCreate create )     
          {         
                ///@addtogroup BRGR_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRGR");              
                            attr.par("seen")=0;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Carbon            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Carbon");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=modr.grhgt/2;              
                            shape.par("dy")=modr.grwid/2;              
                            shape.par("dz")=modr.grlen/2;              
                            /// Shape Bbox dx=modr.grhgt/2 dy=modr.grwid/2 dz=modr.grlen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRGR;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BRGR:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRGR     
          // ---------------------------------------------------------------------------------------------------     
          void BROG::Block( AgCreate create )     
          {         
                ///@addtogroup BROG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BROG");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Component Si	a=28	z=14	w=1.           
                      /// Component O	a=16	z=8	w=2.           
                      /// Mixture Glass dens=2.2           
                      {  AgMaterial &mix = AgMaterial::Get("Glass");              
                            mix.Component("Si",28,14,1.);              
                            mix.Component("O",16,8,2.);              
                            mix.par("dens")=2.2;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=modr.oghgt/2;              
                            shape.par("dy")=modr.ogwid/2;              
                            shape.par("dz")=modr.oglen/2;              
                            /// Shape Bbox dx=modr.oghgt/2 dy=modr.ogwid/2 dz=modr.oglen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BROG;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BROG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BROG     
          // ---------------------------------------------------------------------------------------------------     
          void BRDT::Block( AgCreate create )     
          {         
                ///@addtogroup BRDT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRDT");              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            /// Shape Bbox               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRDT;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("BRIG");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BRIG              
                            Create("BRIG");               
                      }           
                      _create = AgCreate("BRSG");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create BRSG              
                            Create("BRSG");               
                      }           
                      xpos = dthgt/2.;           
                      y    = 0.;           
                      z    = 0.;           
                      /// Loop on igap from 1 to modr.ngap-1 step=1           
                      for ( igap=1; (1>0)? (igap<=modr.ngap-1):(igap>=modr.ngap-1); igap+=1 )           
                      {              
                            { AgPlacement place = AgPlacement("BRSG","BRDT");                 
                                  /// Add daughter volume BRSG to mother BRDT                 
                                  place.TranslateX(xpos-modr.sprmax);                 
                                  /// Translate x = xpos-modr.sprmax                 
                                  _stacker -> Position( AgBlock::Find("BRSG"), place );                 
                            } // end placement of BRSG              
                            xpos = xpos - modr.sprmax*2.;              
                            { AgPlacement place = AgPlacement("BRIG","BRDT");                 
                                  /// Add daughter volume BRIG to mother BRDT                 
                                  place.TranslateX(xpos-modr.ighgt/2);                 
                                  /// Translate x = xpos-modr.ighgt/2                 
                                  _stacker -> Position( AgBlock::Find("BRIG"), place );                 
                            } // end placement of BRIG              
                            xpos = xpos - modr.ighgt;              
                      }           
                      { AgPlacement place = AgPlacement("BRSG","BRDT");              
                            /// Add daughter volume BRSG to mother BRDT              
                            place.TranslateX(xpos-modr.sprmax);              
                            /// Translate x = xpos-modr.sprmax              
                            _stacker -> Position( AgBlock::Find("BRSG"), place );              
                      } // end placement of BRSG           
                      xpos = xpos - modr.sprmax*2.;           
                      END_OF_BRDT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRDT     
          // ---------------------------------------------------------------------------------------------------     
          void BRIG::Block( AgCreate create )     
          {         
                ///@addtogroup BRIG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRIG");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Glass            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Glass");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=modr.ighgt/2;              
                            shape.par("dy")=modr.igwid/2;              
                            shape.par("dz")=modr.iglen/2;              
                            /// Shape Bbox dx=modr.ighgt/2 dy=modr.igwid/2 dz=modr.iglen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRIG;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BRIG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRIG     
          // ---------------------------------------------------------------------------------------------------     
          void BRSG::Block( AgCreate create )     
          {         
                ///@addtogroup BRSG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRSG");              
                            attr.par("seen")=0;              
                            attr.par("colo")=5;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material RPCgas            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Rpcgas");              
                            _material = mat;              
                      }           
                      /// Medium sensitive           
                      ///  isvol = 1            
                      {  AgMedium &med = AgMedium::Get("Sensitive");              
                               med.Inherit(this);              
                            med.par("isvol")=1 ;              
                            _medium = med;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=modr.ighgt/2;              
                            shape.par("dy")=modr.igwid/2;              
                            shape.par("dz")=modr.iglen/2;              
                            /// Shape Bbox dx=modr.ighgt/2 dy=modr.igwid/2 dz=modr.iglen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRSG;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BRSG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRSG     
          // ---------------------------------------------------------------------------------------------------     
          void BRWG::Block( AgCreate create )     
          {         
                ///@addtogroup BRWG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("BRWG");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Component O	a=16	z=8	w=2           
                      /// Component C	a=12	z=6	w=5           
                      /// Component H	a=1	z=1	w=8           
                      /// Mixture Lucite dens=1.18           
                      {  AgMaterial &mix = AgMaterial::Get("Lucite");              
                            mix.Component("O",16,8,2);              
                            mix.Component("C",12,6,5);              
                            mix.Component("H",1,1,8);              
                            mix.par("dens")=1.18;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=modr.wgrmin;              
                            shape.par("rmax")=modr.wgrmax;              
                            shape.par("dz")=modr.wglen/2;              
                            /// Shape Tube rmin=modr.wgrmin rmax=modr.wgrmax dz=modr.wglen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_BRWG;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_BRWG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block BRWG     
    // ----------------------------------------------------------------------- geoctr
       void BtofGeo3::ConstructGeometry( const Char_t *dummy )     
       {        
             ///@addtogroup BtofGeo3_revision        
             ///@{           
                   /// Author: W.J. Llope           
             ///@}        
             ///@addtogroup BtofGeo3_revision        
             ///@{           
                   /// Created:     29 December 1999            
             ///@}        
             AddBlock("BTOF");        
             AddBlock("BTOH");        
             AddBlock("BSEC");        
             AddBlock("BTRA");        
             AddBlock("BUND");        
             AddBlock("BTFT");        
             AddBlock("BASE");        
             AddBlock("BARM");        
             AddBlock("BANG");        
             AddBlock("BWAT");        
             AddBlock("BCOV");        
             AddBlock("BXTR");        
             AddBlock("BMTC");        
             AddBlock("BTTC");        
             AddBlock("BMAA");        
             AddBlock("BMTD");        
             AddBlock("BASS");        
             AddBlock("BXSA");        
             AddBlock("BCSB");        
             AddBlock("BCCV");        
             AddBlock("BFEE");        
             AddBlock("BLEM");        
             AddBlock("BCPM");        
             AddBlock("BCSK");        
             AddBlock("BTSK");        
             AddBlock("BZEL");        
             AddBlock("BCEL");        
             AddBlock("BCEB");        
             AddBlock("BCON");        
             AddBlock("BPLA");        
             AddBlock("BCOO");        
             AddBlock("BRAI");        
             AddBlock("BPIP");        
             AddBlock("BPIQ");        
             AddBlock("BRTC");        
             AddBlock("BRMD");        
             AddBlock("BRHC");        
             AddBlock("BRCB");        
             AddBlock("BRMY");        
             AddBlock("BRGR");        
             AddBlock("BROG");        
             AddBlock("BRDT");        
             AddBlock("BRSG");        
             AddBlock("BRIG");        
             AddBlock("BRWG");        
             AddBlock("BRFE");        
             AddBlock("BUPC");        
             AddBlock("BGMT");        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup btog_doc        
             ///@{           
                   ++btog._index;           
                   btog . version = 5; //  geometry version            
                   /// btog . version = 5; //  geometry version            
                   btog . rmin = 207.80; //  minimum CTB/TOF system radius (as built)            
                   /// btog . rmin = 207.80; //  minimum CTB/TOF system radius (as built)            
                   btog . rmax = 219.5; //  maximum CTB/TOF system radius            
                   /// btog . rmax = 219.5; //  maximum CTB/TOF system radius            
                   btog . dz = 246.0; //  CTB/TOF tube half length            
                   /// btog . dz = 246.0; //  CTB/TOF tube half length            
                   btog . choice = 7; //  1=CTB, 2=Full-TOFp, 3=25% TOFp, 4=1 tray-TOFp,                                ;// 5=1 tray-TOFr, 6=Full-TOFr, 7=TOFp+TOFrp Run-IV           
                   /// btog . choice = 7; //  1=CTB, 2=Full-TOFp, 3=25% TOFp, 4=1 tray-TOFp,                                ;// 5=1 tray-TOFr, 6=Full-TOFr, 7=TOFp+TOFrp Run-IV           
                   btog . posit1.at(0) = 32; //  TOFp tray position: (0) choice 4 or 5 -> run-2,3 posn,                                ;//                     (1) choice 7 -> run-4 posn           
                   ///btog . posit1.at(0) = 32; //  TOFp tray position: (0) choice 4 or 5 -> run-2,3 posn,                                ;//                     (1) choice 7 -> run-4 posn           
                   btog . posit1.at(1) = 33; //  TOFp tray position: (0) choice 4 or 5 -> run-2,3 posn,                                ;//                     (1) choice 7 -> run-4 posn           
                   ///btog . posit1.at(1) = 33; //  TOFp tray position: (0) choice 4 or 5 -> run-2,3 posn,                                ;//                     (1) choice 7 -> run-4 posn           
                   btog . posit2 = 23; //  TOFr tray position for choice 5             
                   /// btog . posit2 = 23; //  TOFr tray position for choice 5             
                   //           
                   btog.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tray_doc        
             ///@{           
                   ++tray._index;           
                   tray . height = 8.89; //  tray height(8.89)            
                   /// tray . height = 8.89; //  tray height(8.89)            
                   tray . width = 21.59; //  full tray width            
                   /// tray . width = 21.59; //  full tray width            
                   tray . length = 241.62; //  full tray length(241.62)            
                   /// tray . length = 241.62; //  full tray length(241.62)            
                   tray . wallthk = 0.13; //  tray wall thickness            
                   /// tray . wallthk = 0.13; //  tray wall thickness            
                   tray . supfullh = 2.03; //  support height (radial)            
                   /// tray . supfullh = 2.03; //  support height (radial)            
                   tray . supfullw = 15.24; //  support full width with arms            
                   /// tray . supfullw = 15.24; //  support full width with arms            
                   tray . suplen = 215.9; //  support length            
                   /// tray . suplen = 215.9; //  support length            
                   tray . supbasew = 9.22; //  support base width            
                   /// tray . supbasew = 9.22; //  support base width            
                   tray . supbaset = 0.32; //  support base thickness              
                   /// tray . supbaset = 0.32; //  support base thickness              
                   tray . suparmt = 0.64; //  support arm  thickness            
                   /// tray . suparmt = 0.64; //  support arm  thickness            
                   tray . cooloutr = 0.80; //  Cooling channel outer radius            
                   /// tray . cooloutr = 0.80; //  Cooling channel outer radius            
                   tray . coolinnr = 0.48; //  Cooling channel inner radius            
                   /// tray . coolinnr = 0.48; //  Cooling channel inner radius            
                   tray . stript = 0.08; //  Thickness of polyethylene strip on bottom            
                   /// tray . stript = 0.08; //  Thickness of polyethylene strip on bottom            
                   tray . footinse = 1.06; //  foot inset from tray edge            
                   /// tray . footinse = 1.06; //  foot inset from tray edge            
                   tray . footthk = 0.23; //  thickness of foot material            
                   /// tray . footthk = 0.23; //  thickness of foot material            
                   tray . foot1len = 1.68; //  length (in section) of first part of foot            
                   /// tray . foot1len = 1.68; //  length (in section) of first part of foot            
                   tray . foot2thk = 1.16; //  thickness of second foot section            
                   /// tray . foot2thk = 1.16; //  thickness of second foot section            
                   tray . foot3len = 2.16; //  length of third part of foot            
                   /// tray . foot3len = 2.16; //  length of third part of foot            
                   //           
                   tray.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup ctbb_doc        
             ///@{           
                   ++ctbb._index;           
                   ctbb . slab1len = 112.5; //  first slab (B) length            
                   /// ctbb . slab1len = 112.5; //  first slab (B) length            
                   ctbb . slab2len = 130.0; //  second slab (A)length             
                   /// ctbb . slab2len = 130.0; //  second slab (A)length             
                   ctbb . slab1x = 5.84; //  first slab (B) x position            
                   /// ctbb . slab1x = 5.84; //  first slab (B) x position            
                   ctbb . slab2x = 2.67; //  second slab (A) x position            
                   /// ctbb . slab2x = 2.67; //  second slab (A) x position            
                   ctbb . slabthck = 1.0; //  scintillator slab thicknesses            
                   /// ctbb . slabthck = 1.0; //  scintillator slab thicknesses            
                   ctbb . slabwid = 21.0; //  scintillator slab width            
                   /// ctbb . slabwid = 21.0; //  scintillator slab width            
                   ctbb . convlen = 8.5; //  optical converter length            
                   /// ctbb . convlen = 8.5; //  optical converter length            
                   ctbb . convwidm = 4.0; //  optical convertor min width            
                   /// ctbb . convwidm = 4.0; //  optical convertor min width            
                   ctbb . convthck = 0.92; //  optical convertor thickness            
                   /// ctbb . convthck = 0.92; //  optical convertor thickness            
                   ctbb . pmtlen = 5.0; //  PMT length            
                   /// ctbb . pmtlen = 5.0; //  PMT length            
                   ctbb . pmtmaxr = 2.0; //  PMT max radius            
                   /// ctbb . pmtmaxr = 2.0; //  PMT max radius            
                   ctbb . pmtminr = 1.84; //  PMT min radius            
                   /// ctbb . pmtminr = 1.84; //  PMT min radius            
                   ctbb . baselen = 4.0; //  Base length            
                   /// ctbb . baselen = 4.0; //  Base length            
                   ctbb . basemaxr = 2.13; //  Base max radius            
                   /// ctbb . basemaxr = 2.13; //  Base max radius            
                   ctbb . baseminr = 1.0; //  Base min radius            
                   /// ctbb . baseminr = 1.0; //  Base min radius            
                   ctbb . electhck = 0.25; //  readout electronics thickness            
                   /// ctbb . electhck = 0.25; //  readout electronics thickness            
                   ctbb . wrap = 0.13; //  thickness of Tyvek + black plastic            
                   /// ctbb . wrap = 0.13; //  thickness of Tyvek + black plastic            
                   ctbb . shim = 0.26; //  thickness of shim to position slat 2            
                   /// ctbb . shim = 0.26; //  thickness of shim to position slat 2            
                   //           
                   ctbb.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup toff_doc        
             ///@{           
                   ++toff._index;           
                   toff . boxwidth = 21.0875; //  width of the 5w box (BMTD)            
                   /// toff . boxwidth = 21.0875; //  width of the 5w box (BMTD)            
                   toff . slatlen = 20.0; //  slat length            
                   /// toff . slatlen = 20.0; //  slat length            
                   toff . slat01z = 104.938; //  5_wide_slat Z position for row 1 from AutoCAD            
                   /// toff . slat01z = 104.938; //  5_wide_slat Z position for row 1 from AutoCAD            
                   toff . slat02z = 84.060; //  4_wide_slat Z position for row 2 from AutoCAD            
                   /// toff . slat02z = 84.060; //  4_wide_slat Z position for row 2 from AutoCAD            
                   toff . slat03z = 62.860; //  4_wide_slat Z position for row 3 from AutoCAD            
                   /// toff . slat03z = 62.860; //  4_wide_slat Z position for row 3 from AutoCAD            
                   toff . slat04z = 41.254; //  4_wide_slat Z position for row 4 from AutoCAD            
                   /// toff . slat04z = 41.254; //  4_wide_slat Z position for row 4 from AutoCAD            
                   toff . slat05z = 18.966; //  4_wide_slat Z position for row 5 from AutoCAD            
                   /// toff . slat05z = 18.966; //  4_wide_slat Z position for row 5 from AutoCAD            
                   toff . slat06z = -3.954; //  4_wide_slat Z position for row 6 from AutoCAD            
                   /// toff . slat06z = -3.954; //  4_wide_slat Z position for row 6 from AutoCAD            
                   toff . slat07z = -27.528; //  4_wide_slat Z position for row 7 from AutoCAD            
                   /// toff . slat07z = -27.528; //  4_wide_slat Z position for row 7 from AutoCAD            
                   toff . slat08z = -51.254; //  4_wide_slat Z position for row 8 from AutoCAD            
                   /// toff . slat08z = -51.254; //  4_wide_slat Z position for row 8 from AutoCAD            
                   toff . slat09z = -75.634; //  4_wide_slat Z position for row 9 from AutoCAD            
                   /// toff . slat09z = -75.634; //  4_wide_slat Z position for row 9 from AutoCAD            
                   toff . slat10z = -100.683; //  4_wide_slat Z position for row 10 from AutoCAD            
                   /// toff . slat10z = -100.683; //  4_wide_slat Z position for row 10 from AutoCAD            
                   toff . slatthck = 2.0; //  scintillator slab thicknesses            
                   /// toff . slatthck = 2.0; //  scintillator slab thicknesses            
                   toff . slatwid = 3.81; //  scintillator slab width (4.0)            
                   /// toff . slatwid = 3.81; //  scintillator slab width (4.0)            
                   toff . slatang = 11.5; //  slat assy. angle w.r.t. tray            
                   /// toff . slatang = 11.5; //  slat assy. angle w.r.t. tray            
                   toff . pmtlen = 5.0; //  PMT length            
                   /// toff . pmtlen = 5.0; //  PMT length            
                   toff . pmtmaxr = 1.91; //  PMT max radius            
                   /// toff . pmtmaxr = 1.91; //  PMT max radius            
                   toff . pmtminr = 1.8; //  PMT min radius            
                   /// toff . pmtminr = 1.8; //  PMT min radius            
                   toff . socklen = 1.0; //  thickness of socket            
                   /// toff . socklen = 1.0; //  thickness of socket            
                   toff . baselen = 5.0; //  Base length            
                   /// toff . baselen = 5.0; //  Base length            
                   toff . basemaxr = 1.91; //  Base max radius            
                   /// toff . basemaxr = 1.91; //  Base max radius            
                   toff . baseminr = 1.8; //  Base min radius              
                   /// toff . baseminr = 1.8; //  Base min radius              
                   toff . cellwid = 3.1; //  Cell width             
                   /// toff . cellwid = 3.1; //  Cell width             
                   toff . cellhgt = 1.6; //  Cell height            
                   /// toff . cellhgt = 1.6; //  Cell height            
                   toff . elechgt = 3.0; //  FEE Board height in tray... (rails/loop too).            
                   /// toff . elechgt = 3.0; //  FEE Board height in tray... (rails/loop too).            
                   toff . electhck = 0.17; //  FEE Board thickness (67 mils)            
                   /// toff . electhck = 0.17; //  FEE Board thickness (67 mils)            
                   toff . elecwid = 20.3; //  FEE Board width (was 21)            
                   /// toff . elecwid = 20.3; //  FEE Board width (was 21)            
                   toff . eleclen = 5.715; //  FEE Board length (was 16)            
                   /// toff . eleclen = 5.715; //  FEE Board length (was 16)            
                   toff . elec01z = 105.610; //  FEE Z position for row 1 from AutoCAD            
                   /// toff . elec01z = 105.610; //  FEE Z position for row 1 from AutoCAD            
                   toff . elec02z = 84.573; //  FEE Z position for row 2 from AutoCAD            
                   /// toff . elec02z = 84.573; //  FEE Z position for row 2 from AutoCAD            
                   toff . elec03z = 63.224; //  FEE Z position for row 3 from AutoCAD            
                   /// toff . elec03z = 63.224; //  FEE Z position for row 3 from AutoCAD            
                   toff . elec04z = 41.667; //  FEE Z position for row 4 from AutoCAD            
                   /// toff . elec04z = 41.667; //  FEE Z position for row 4 from AutoCAD            
                   toff . elec05z = 19.379; //  FEE Z position for row 5 from AutoCAD            
                   /// toff . elec05z = 19.379; //  FEE Z position for row 5 from AutoCAD            
                   toff . elec06z = -3.542; //  FEE Z position for row 6 from AutoCAD            
                   /// toff . elec06z = -3.542; //  FEE Z position for row 6 from AutoCAD            
                   toff . elec07z = -27.165; //  FEE Z position for row 7 from AutoCAD            
                   /// toff . elec07z = -27.165; //  FEE Z position for row 7 from AutoCAD            
                   toff . elec08z = -50.841; //  FEE Z position for row 8 from AutoCAD            
                   /// toff . elec08z = -50.841; //  FEE Z position for row 8 from AutoCAD            
                   toff . elec09z = -75.170; //  FEE Z position for row 9 from AutoCAD            
                   /// toff . elec09z = -75.170; //  FEE Z position for row 9 from AutoCAD            
                   toff . elec10z = -100.270; //  FEE Z position for row 10 from AutoCAD            
                   /// toff . elec10z = -100.270; //  FEE Z position for row 10 from AutoCAD            
                   toff . railthck = 0.2; //  Cooling loop rail thickness            
                   /// toff . railthck = 0.2; //  Cooling loop rail thickness            
                   toff . railwid = 1.5; //  Cooling loop rail width            
                   /// toff . railwid = 1.5; //  Cooling loop rail width            
                   toff . cooloutr = 0.635; //  Cooling loop pipe outer radius, 0.5in/2            
                   /// toff . cooloutr = 0.635; //  Cooling loop pipe outer radius, 0.5in/2            
                   toff . coolinnr = 0.561; //  Cooling loop pipe inner radius, (0.5in-0.058in)/2            
                   /// toff . coolinnr = 0.561; //  Cooling loop pipe inner radius, (0.5in-0.058in)/2            
                   //           
                   toff.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup modr_doc        
             ///@{           
                   ++modr._index;           
                   modr . height = 1.95; //  Module height (r)            
                   /// modr . height = 1.95; //  Module height (r)            
                   modr . width = 21.2; //  Module width (phi)            
                   /// modr . width = 21.2; //  Module width (phi)            
                   modr . length = 9.4; //  Module length (z)            
                   /// modr . length = 9.4; //  Module length (z)            
                   modr . center = 0.35; //  Module detector center in (phi)            
                   /// modr . center = 0.35; //  Module detector center in (phi)            
                   modr . mrpcx.at(0) = 4.76; //  mrpc Xpositions            
                   ///modr . mrpcx.at(0) = 4.76; //  mrpc Xpositions            
                   modr . mrpcx.at(1) = 1.21; //  mrpc Xpositions            
                   ///modr . mrpcx.at(1) = 1.21; //  mrpc Xpositions            
                   modr . mrpcx.at(2) = 4.99; //  mrpc Xpositions            
                   ///modr . mrpcx.at(2) = 4.99; //  mrpc Xpositions            
                   modr . mrpcx.at(3) = 1.46; //  mrpc Xpositions            
                   ///modr . mrpcx.at(3) = 1.46; //  mrpc Xpositions            
                   modr . mrpcx.at(4) = 5.19; //  mrpc Xpositions            
                   ///modr . mrpcx.at(4) = 5.19; //  mrpc Xpositions            
                   modr . mrpcx.at(5) = 1.71; //  mrpc Xpositions            
                   ///modr . mrpcx.at(5) = 1.71; //  mrpc Xpositions            
                   modr . mrpcx.at(6) = 4.98; //  mrpc Xpositions            
                   ///modr . mrpcx.at(6) = 4.98; //  mrpc Xpositions            
                   modr . mrpcx.at(7) = 1.54; //  mrpc Xpositions            
                   ///modr . mrpcx.at(7) = 1.54; //  mrpc Xpositions            
                   modr . mrpcx.at(8) = 2.69; //  mrpc Xpositions            
                   ///modr . mrpcx.at(8) = 2.69; //  mrpc Xpositions            
                   modr . mrpcx.at(9) = 3.39; //  mrpc Xpositions            
                   ///modr . mrpcx.at(9) = 3.39; //  mrpc Xpositions            
                   modr . mrpcx.at(10) = 3.25; //  mrpc Xpositions            
                   ///modr . mrpcx.at(10) = 3.25; //  mrpc Xpositions            
                   modr . mrpcx.at(11) = 3.49; //  mrpc Xpositions            
                   ///modr . mrpcx.at(11) = 3.49; //  mrpc Xpositions            
                   modr . mrpcx.at(12) = 3.33; //  mrpc Xpositions            
                   ///modr . mrpcx.at(12) = 3.33; //  mrpc Xpositions            
                   modr . mrpcx.at(13) = 3.54; //  mrpc Xpositions            
                   ///modr . mrpcx.at(13) = 3.54; //  mrpc Xpositions            
                   modr . mrpcx.at(14) = 3.54; //  mrpc Xpositions            
                   ///modr . mrpcx.at(14) = 3.54; //  mrpc Xpositions            
                   modr . mrpcx.at(15) = 3.57; //  mrpc Xpositions            
                   ///modr . mrpcx.at(15) = 3.57; //  mrpc Xpositions            
                   modr . mrpcx.at(16) = 3.48; //  mrpc Xpositions            
                   ///modr . mrpcx.at(16) = 3.48; //  mrpc Xpositions            
                   modr . mrpcx.at(17) = 3.51; //  mrpc Xpositions            
                   ///modr . mrpcx.at(17) = 3.51; //  mrpc Xpositions            
                   modr . mrpcx.at(18) = 3.19; //  mrpc Xpositions            
                   ///modr . mrpcx.at(18) = 3.19; //  mrpc Xpositions            
                   modr . mrpcx.at(19) = 3.19; //  mrpc Xpositions            
                   ///modr . mrpcx.at(19) = 3.19; //  mrpc Xpositions            
                   modr . mrpcx.at(20) = 3.19; //  mrpc Xpositions            
                   ///modr . mrpcx.at(20) = 3.19; //  mrpc Xpositions            
                   modr . mrpcx.at(21) = 3.19; //  mrpc Xpositions            
                   ///modr . mrpcx.at(21) = 3.19; //  mrpc Xpositions            
                   modr . mrpcx.at(22) = 3.19; //  mrpc Xpositions            
                   ///modr . mrpcx.at(22) = 3.19; //  mrpc Xpositions            
                   modr . mrpcx.at(23) = 3.43; //  mrpc Xpositions            
                   ///modr . mrpcx.at(23) = 3.43; //  mrpc Xpositions            
                   modr . mrpcx.at(24) = 3.43; //  mrpc Xpositions            
                   ///modr . mrpcx.at(24) = 3.43; //  mrpc Xpositions            
                   modr . mrpcx.at(25) = 3.43; //  mrpc Xpositions            
                   ///modr . mrpcx.at(25) = 3.43; //  mrpc Xpositions            
                   modr . mrpcx.at(26) = 3.43; //  mrpc Xpositions            
                   ///modr . mrpcx.at(26) = 3.43; //  mrpc Xpositions            
                   modr . mrpcx.at(27) = 3.43; //  mrpc Xpositions            
                   ///modr . mrpcx.at(27) = 3.43; //  mrpc Xpositions            
                   modr . mrpcx.at(28) = 3.43; //  mrpc Xpositions            
                   ///modr . mrpcx.at(28) = 3.43; //  mrpc Xpositions            
                   modr . mrpcx.at(29) = 3.43; //  mrpc Xpositions            
                   ///modr . mrpcx.at(29) = 3.43; //  mrpc Xpositions            
                   modr . mrpcx.at(30) = 3.43; //  mrpc Xpositions            
                   ///modr . mrpcx.at(30) = 3.43; //  mrpc Xpositions            
                   modr . mrpcx.at(31) = 3.43; //  mrpc Xpositions            
                   ///modr . mrpcx.at(31) = 3.43; //  mrpc Xpositions            
                   modr . mrpcx.at(32) = 3.43 ; //  mrpc Xpositions            
                   ///modr . mrpcx.at(32) = 3.43 ; //  mrpc Xpositions            
                   modr . mrpcz.at(0) = 4.50; //  mrpc Zpositions            
                   ///modr . mrpcz.at(0) = 4.50; //  mrpc Zpositions            
                   modr . mrpcz.at(1) = 10.48; //  mrpc Zpositions            
                   ///modr . mrpcz.at(1) = 10.48; //  mrpc Zpositions            
                   modr . mrpcz.at(2) = 16.83; //  mrpc Zpositions            
                   ///modr . mrpcz.at(2) = 16.83; //  mrpc Zpositions            
                   modr . mrpcz.at(3) = 22.64; //  mrpc Zpositions            
                   ///modr . mrpcz.at(3) = 22.64; //  mrpc Zpositions            
                   modr . mrpcz.at(4) = 29.25; //  mrpc Zpositions            
                   ///modr . mrpcz.at(4) = 29.25; //  mrpc Zpositions            
                   modr . mrpcz.at(5) = 34.89; //  mrpc Zpositions            
                   ///modr . mrpcz.at(5) = 34.89; //  mrpc Zpositions            
                   modr . mrpcz.at(6) = 41.68; //  mrpc Zpositions            
                   ///modr . mrpcz.at(6) = 41.68; //  mrpc Zpositions            
                   modr . mrpcz.at(7) = 47.19; //  mrpc Zpositions            
                   ///modr . mrpcz.at(7) = 47.19; //  mrpc Zpositions            
                   modr . mrpcz.at(8) = 53.76; //  mrpc Zpositions            
                   ///modr . mrpcz.at(8) = 53.76; //  mrpc Zpositions            
                   modr . mrpcz.at(9) = 60.18; //  mrpc Zpositions            
                   ///modr . mrpcz.at(9) = 60.18; //  mrpc Zpositions            
                   modr . mrpcz.at(10) = 66.53; //  mrpc Zpositions            
                   ///modr . mrpcz.at(10) = 66.53; //  mrpc Zpositions            
                   modr . mrpcz.at(11) = 72.95; //  mrpc Zpositions            
                   ///modr . mrpcz.at(11) = 72.95; //  mrpc Zpositions            
                   modr . mrpcz.at(12) = 79.42; //  mrpc Zpositions            
                   ///modr . mrpcz.at(12) = 79.42; //  mrpc Zpositions            
                   modr . mrpcz.at(13) = 85.97; //  mrpc Zpositions            
                   ///modr . mrpcz.at(13) = 85.97; //  mrpc Zpositions            
                   modr . mrpcz.at(14) = 92.59; //  mrpc Zpositions            
                   ///modr . mrpcz.at(14) = 92.59; //  mrpc Zpositions            
                   modr . mrpcz.at(15) = 99.28; //  mrpc Zpositions            
                   ///modr . mrpcz.at(15) = 99.28; //  mrpc Zpositions            
                   modr . mrpcz.at(16) = 106.00; //  mrpc Zpositions            
                   ///modr . mrpcz.at(16) = 106.00; //  mrpc Zpositions            
                   modr . mrpcz.at(17) = 112.84; //  mrpc Zpositions            
                   ///modr . mrpcz.at(17) = 112.84; //  mrpc Zpositions            
                   modr . mrpcz.at(18) = 119.60; //  mrpc Zpositions            
                   ///modr . mrpcz.at(18) = 119.60; //  mrpc Zpositions            
                   modr . mrpcz.at(19) = 126.66; //  mrpc Zpositions            
                   ///modr . mrpcz.at(19) = 126.66; //  mrpc Zpositions            
                   modr . mrpcz.at(20) = 133.80; //  mrpc Zpositions            
                   ///modr . mrpcz.at(20) = 133.80; //  mrpc Zpositions            
                   modr . mrpcz.at(21) = 141.06; //  mrpc Zpositions            
                   ///modr . mrpcz.at(21) = 141.06; //  mrpc Zpositions            
                   modr . mrpcz.at(22) = 148.43; //  mrpc Zpositions            
                   ///modr . mrpcz.at(22) = 148.43; //  mrpc Zpositions            
                   modr . mrpcz.at(23) = 156.09; //  mrpc Zpositions            
                   ///modr . mrpcz.at(23) = 156.09; //  mrpc Zpositions            
                   modr . mrpcz.at(24) = 163.71; //  mrpc Zpositions            
                   ///modr . mrpcz.at(24) = 163.71; //  mrpc Zpositions            
                   modr . mrpcz.at(25) = 171.46; //  mrpc Zpositions            
                   ///modr . mrpcz.at(25) = 171.46; //  mrpc Zpositions            
                   modr . mrpcz.at(26) = 179.35; //  mrpc Zpositions            
                   ///modr . mrpcz.at(26) = 179.35; //  mrpc Zpositions            
                   modr . mrpcz.at(27) = 187.38; //  mrpc Zpositions            
                   ///modr . mrpcz.at(27) = 187.38; //  mrpc Zpositions            
                   modr . mrpcz.at(28) = 195.56; //  mrpc Zpositions            
                   ///modr . mrpcz.at(28) = 195.56; //  mrpc Zpositions            
                   modr . mrpcz.at(29) = 203.84; //  mrpc Zpositions            
                   ///modr . mrpcz.at(29) = 203.84; //  mrpc Zpositions            
                   modr . mrpcz.at(30) = 212.33; //  mrpc Zpositions            
                   ///modr . mrpcz.at(30) = 212.33; //  mrpc Zpositions            
                   modr . mrpcz.at(31) = 220.94; //  mrpc Zpositions            
                   ///modr . mrpcz.at(31) = 220.94; //  mrpc Zpositions            
                   modr . mrpcz.at(32) = 229.7 ; //  mrpc Zpositions            
                   ///modr . mrpcz.at(32) = 229.7 ; //  mrpc Zpositions            
                   modr . mrpca.at(0) = 1.20; //  mrpc angles            
                   ///modr . mrpca.at(0) = 1.20; //  mrpc angles            
                   modr . mrpca.at(1) = 2.84; //  mrpc angles            
                   ///modr . mrpca.at(1) = 2.84; //  mrpc angles            
                   modr . mrpca.at(2) = 4.48; //  mrpc angles            
                   ///modr . mrpca.at(2) = 4.48; //  mrpc angles            
                   modr . mrpca.at(3) = 6.12; //  mrpc angles            
                   ///modr . mrpca.at(3) = 6.12; //  mrpc angles            
                   modr . mrpca.at(4) = 7.74; //  mrpc angles            
                   ///modr . mrpca.at(4) = 7.74; //  mrpc angles            
                   modr . mrpca.at(5) = 9.36; //  mrpc angles            
                   ///modr . mrpca.at(5) = 9.36; //  mrpc angles            
                   modr . mrpca.at(6) = 10.97; //  mrpc angles            
                   ///modr . mrpca.at(6) = 10.97; //  mrpc angles            
                   modr . mrpca.at(7) = 7.60; //  mrpc angles            
                   ///modr . mrpca.at(7) = 7.60; //  mrpc angles            
                   modr . mrpca.at(8) = 14.30; //  mrpc angles            
                   ///modr . mrpca.at(8) = 14.30; //  mrpc angles            
                   modr . mrpca.at(9) = 22.30; //  mrpc angles            
                   ///modr . mrpca.at(9) = 22.30; //  mrpc angles            
                   modr . mrpca.at(10) = 22.30; //  mrpc angles            
                   ///modr . mrpca.at(10) = 22.30; //  mrpc angles            
                   modr . mrpca.at(11) = 22.30; //  mrpc angles            
                   ///modr . mrpca.at(11) = 22.30; //  mrpc angles            
                   modr . mrpca.at(12) = 22.30; //  mrpc angles            
                   ///modr . mrpca.at(12) = 22.30; //  mrpc angles            
                   modr . mrpca.at(13) = 22.30; //  mrpc angles            
                   ///modr . mrpca.at(13) = 22.30; //  mrpc angles            
                   modr . mrpca.at(14) = 22.30; //  mrpc angles            
                   ///modr . mrpca.at(14) = 22.30; //  mrpc angles            
                   modr . mrpca.at(15) = 22.30; //  mrpc angles            
                   ///modr . mrpca.at(15) = 22.30; //  mrpc angles            
                   modr . mrpca.at(16) = 22.30; //  mrpc angles            
                   ///modr . mrpca.at(16) = 22.30; //  mrpc angles            
                   modr . mrpca.at(17) = 22.30; //  mrpc angles            
                   ///modr . mrpca.at(17) = 22.30; //  mrpc angles            
                   modr . mrpca.at(18) = 33.00; //  mrpc angles            
                   ///modr . mrpca.at(18) = 33.00; //  mrpc angles            
                   modr . mrpca.at(19) = 33.00; //  mrpc angles            
                   ///modr . mrpca.at(19) = 33.00; //  mrpc angles            
                   modr . mrpca.at(20) = 33.00; //  mrpc angles            
                   ///modr . mrpca.at(20) = 33.00; //  mrpc angles            
                   modr . mrpca.at(21) = 33.00; //  mrpc angles            
                   ///modr . mrpca.at(21) = 33.00; //  mrpc angles            
                   modr . mrpca.at(22) = 33.00; //  mrpc angles            
                   ///modr . mrpca.at(22) = 33.00; //  mrpc angles            
                   modr . mrpca.at(23) = 37.58; //  mrpc angles            
                   ///modr . mrpca.at(23) = 37.58; //  mrpc angles            
                   modr . mrpca.at(24) = 37.58; //  mrpc angles            
                   ///modr . mrpca.at(24) = 37.58; //  mrpc angles            
                   modr . mrpca.at(25) = 37.58; //  mrpc angles            
                   ///modr . mrpca.at(25) = 37.58; //  mrpc angles            
                   modr . mrpca.at(26) = 37.58; //  mrpc angles            
                   ///modr . mrpca.at(26) = 37.58; //  mrpc angles            
                   modr . mrpca.at(27) = 37.58; //  mrpc angles            
                   ///modr . mrpca.at(27) = 37.58; //  mrpc angles            
                   modr . mrpca.at(28) = 37.58; //  mrpc angles            
                   ///modr . mrpca.at(28) = 37.58; //  mrpc angles            
                   modr . mrpca.at(29) = 37.58; //  mrpc angles            
                   ///modr . mrpca.at(29) = 37.58; //  mrpc angles            
                   modr . mrpca.at(30) = 37.58; //  mrpc angles            
                   ///modr . mrpca.at(30) = 37.58; //  mrpc angles            
                   modr . mrpca.at(31) = 37.58; //  mrpc angles            
                   ///modr . mrpca.at(31) = 37.58; //  mrpc angles            
                   modr . mrpca.at(32) = 37.58 ; //  mrpc angles            
                   ///modr . mrpca.at(32) = 37.58 ; //  mrpc angles            
                   modr . hchgt = 0.466; //  HC->Height (r)            
                   /// modr . hchgt = 0.466; //  HC->Height (r)            
                   modr . hcwid = 20.8; //   HC->Width (phi)            
                   /// modr . hcwid = 20.8; //   HC->Width (phi)            
                   modr . hclen = 8.4; //    HC->Length (z)            
                   /// modr . hclen = 8.4; //    HC->Length (z)            
                   modr . pcbhgt = 0.15; //  PCB->Height (r)            
                   /// modr . pcbhgt = 0.15; //  PCB->Height (r)            
                   modr . pcbwid = 21.0; //   PCB->Width  (phi)            
                   /// modr . pcbwid = 21.0; //   PCB->Width  (phi)            
                   modr . pcblen = 9.4; //    PCB->Length (z) *PCBLen =  9.4(real)            
                   /// modr . pcblen = 9.4; //    PCB->Length (z) *PCBLen =  9.4(real)            
                   modr . myhgt = 0.035; //  MYlar->Height            
                   /// modr . myhgt = 0.035; //  MYlar->Height            
                   modr . mywid = 21.2; //   MYlar->Width            
                   /// modr . mywid = 21.2; //   MYlar->Width            
                   modr . mylen = 8.4; //    MYlar->Length            
                   /// modr . mylen = 8.4; //    MYlar->Length            
                   modr . grhgt = 0.013; //  GRaphite->Height            
                   /// modr . grhgt = 0.013; //  GRaphite->Height            
                   modr . grwid = 20.2; //   GRaphite->Width            
                   /// modr . grwid = 20.2; //   GRaphite->Width            
                   modr . grlen = 7.4; //    GRaphite->Length            
                   /// modr . grlen = 7.4; //    GRaphite->Length            
                   modr . oghgt = 0.11; //  Outer Glass->Height            
                   /// modr . oghgt = 0.11; //  Outer Glass->Height            
                   modr . ogwid = 20.6; //   Outer Glass->Width            
                   /// modr . ogwid = 20.6; //   Outer Glass->Width            
                   modr . oglen = 7.8; //    Outer Glass->Length            
                   /// modr . oglen = 7.8; //    Outer Glass->Length            
                   modr . ighgt = 0.054; //  Inner Glass->Height            
                   /// modr . ighgt = 0.054; //  Inner Glass->Height            
                   modr . igwid = 20.0; //   Inner Glass->Width            
                   /// modr . igwid = 20.0; //   Inner Glass->Width            
                   modr . iglen = 6.1; //    Inner Glass->Length            
                   /// modr . iglen = 6.1; //    Inner Glass->Length            
                   modr . sprmin = 0.; //  SeParator Tube->RMin            
                   /// modr . sprmin = 0.; //  SeParator Tube->RMin            
                   modr . sprmax = 0.011; //   SeParator Tube->RMax            
                   /// modr . sprmax = 0.011; //   SeParator Tube->RMax            
                   modr . splen = 7.8; //    SeParator Tube->Length            
                   /// modr . splen = 7.8; //    SeParator Tube->Length            
                   modr . wgrmin = 0.; //  Wedge Tube: RMin            
                   /// modr . wgrmin = 0.; //  Wedge Tube: RMin            
                   modr . wgrmax = 0.15; //   Wedge Tube->RMax            
                   /// modr . wgrmax = 0.15; //   Wedge Tube->RMax            
                   modr . wglen = 10.0; //    Wedge Tube->Length            
                   /// modr . wglen = 10.0; //    Wedge Tube->Length            
                   modr . feeh = 0.15; //  tofr fee pcb thickness            
                   /// modr . feeh = 0.15; //  tofr fee pcb thickness            
                   modr . hbwid = 0.635; //  the slim honeycomb support box width            
                   /// modr . hbwid = 0.635; //  the slim honeycomb support box width            
                   modr . ngap = 6; //  Number of gaps in MRPC            
                   /// modr . ngap = 6; //  Number of gaps in MRPC            
                   //           
                   modr.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup mod4_doc        
             ///@{           
                   ++mod4._index;           
                   mod4 . height = 1.95; //  Module height (r)            
                   /// mod4 . height = 1.95; //  Module height (r)            
                   mod4 . width = 21.2; //  Module width (phi)            
                   /// mod4 . width = 21.2; //  Module width (phi)            
                   mod4 . length = 9.4; //  Module length (z)            
                   /// mod4 . length = 9.4; //  Module length (z)            
                   mod4 . center = 0.35; //  Module detector center (phi)            
                   /// mod4 . center = 0.35; //  Module detector center (phi)            
                   mod4 . mrpcz.at(0) = 5.83; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(0) = 5.83; //  mrpc Zposns            
                   mod4 . mrpcz.at(1) = 11.97; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(1) = 11.97; //  mrpc Zposns            
                   mod4 . mrpcz.at(2) = 18.17; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(2) = 18.17; //  mrpc Zposns            
                   mod4 . mrpcz.at(3) = 24.03; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(3) = 24.03; //  mrpc Zposns            
                   mod4 . mrpcz.at(4) = 30.55; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(4) = 30.55; //  mrpc Zposns            
                   mod4 . mrpcz.at(5) = 36.22; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(5) = 36.22; //  mrpc Zposns            
                   mod4 . mrpcz.at(6) = 42.54; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(6) = 42.54; //  mrpc Zposns            
                   mod4 . mrpcz.at(7) = 48.87; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(7) = 48.87; //  mrpc Zposns            
                   mod4 . mrpcz.at(8) = 55.19; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(8) = 55.19; //  mrpc Zposns            
                   mod4 . mrpcz.at(9) = 61.53; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(9) = 61.53; //  mrpc Zposns            
                   mod4 . mrpcz.at(10) = 67.86; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(10) = 67.86; //  mrpc Zposns            
                   mod4 . mrpcz.at(11) = 74.24; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(11) = 74.24; //  mrpc Zposns            
                   mod4 . mrpcz.at(12) = 80.68; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(12) = 80.68; //  mrpc Zposns            
                   mod4 . mrpcz.at(13) = 87.08; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(13) = 87.08; //  mrpc Zposns            
                   mod4 . mrpcz.at(14) = 93.64; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(14) = 93.64; //  mrpc Zposns            
                   mod4 . mrpcz.at(15) = 100.36; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(15) = 100.36; //  mrpc Zposns            
                   mod4 . mrpcz.at(16) = 107.19; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(16) = 107.19; //  mrpc Zposns            
                   mod4 . mrpcz.at(17) = 114.05; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(17) = 114.05; //  mrpc Zposns            
                   mod4 . mrpcz.at(18) = 121.02; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(18) = 121.02; //  mrpc Zposns            
                   mod4 . mrpcz.at(19) = 128.08; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(19) = 128.08; //  mrpc Zposns            
                   mod4 . mrpcz.at(20) = 135.24; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(20) = 135.24; //  mrpc Zposns            
                   mod4 . mrpcz.at(21) = 142.51; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(21) = 142.51; //  mrpc Zposns            
                   mod4 . mrpcz.at(22) = 149.88; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(22) = 149.88; //  mrpc Zposns            
                   mod4 . mrpcz.at(23) = 157.35; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(23) = 157.35; //  mrpc Zposns            
                   mod4 . mrpcz.at(24) = 164.93; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(24) = 164.93; //  mrpc Zposns            
                   mod4 . mrpcz.at(25) = 172.63; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(25) = 172.63; //  mrpc Zposns            
                   mod4 . mrpcz.at(26) = 180.43; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(26) = 180.43; //  mrpc Zposns            
                   mod4 . mrpcz.at(27) = 188.35; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(27) = 188.35; //  mrpc Zposns            
                   mod4 . mrpcz.at(28) = 196.38; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(28) = 196.38; //  mrpc Zposns            
                   mod4 . mrpcz.at(29) = 204.52; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(29) = 204.52; //  mrpc Zposns            
                   mod4 . mrpcz.at(30) = 212.79; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(30) = 212.79; //  mrpc Zposns            
                   mod4 . mrpcz.at(31) = 221.17 ; //  mrpc Zposns            
                   ///mod4 . mrpcz.at(31) = 221.17 ; //  mrpc Zposns            
                   mod4 . mrpcx.at(0) = 1.5; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(0) = 1.5; //  mrpc Xposns            
                   mod4 . mrpcx.at(1) = 2.83; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(1) = 2.83; //  mrpc Xposns            
                   mod4 . mrpcx.at(2) = 4.16; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(2) = 4.16; //  mrpc Xposns            
                   mod4 . mrpcx.at(3) = 1.55; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(3) = 1.55; //  mrpc Xposns            
                   mod4 . mrpcx.at(4) = 4.73; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(4) = 4.73; //  mrpc Xposns            
                   mod4 . mrpcx.at(5) = 1.88; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(5) = 1.88; //  mrpc Xposns            
                   mod4 . mrpcx.at(6) = 2.56; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(6) = 2.56; //  mrpc Xposns            
                   mod4 . mrpcx.at(7) = 3.06; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(7) = 3.06; //  mrpc Xposns            
                   mod4 . mrpcx.at(8) = 3.3; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(8) = 3.3; //  mrpc Xposns            
                   mod4 . mrpcx.at(9) = 3.41; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(9) = 3.41; //  mrpc Xposns            
                   mod4 . mrpcx.at(10) = 3.32; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(10) = 3.32; //  mrpc Xposns            
                   mod4 . mrpcx.at(11) = 3.2; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(11) = 3.2; //  mrpc Xposns            
                   mod4 . mrpcx.at(12) = 3.07; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(12) = 3.07; //  mrpc Xposns            
                   mod4 . mrpcx.at(13) = 2.73; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(13) = 2.73; //  mrpc Xposns            
                   mod4 . mrpcx.at(14) = 2.58; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(14) = 2.58; //  mrpc Xposns            
                   mod4 . mrpcx.at(15) = 2.64; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(15) = 2.64; //  mrpc Xposns            
                   mod4 . mrpcx.at(16) = 2.74; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(16) = 2.74; //  mrpc Xposns            
                   mod4 . mrpcx.at(17) = 2.74; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(17) = 2.74; //  mrpc Xposns            
                   mod4 . mrpcx.at(18) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(18) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(19) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(19) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(20) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(20) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(21) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(21) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(22) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(22) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(23) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(23) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(24) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(24) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(25) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(25) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(26) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(26) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(27) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(27) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(28) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(28) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(29) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(29) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(30) = 2.76; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(30) = 2.76; //  mrpc Xposns            
                   mod4 . mrpcx.at(31) = 2.76 ; //  mrpc Xposns            
                   ///mod4 . mrpcx.at(31) = 2.76 ; //  mrpc Xposns            
                   mod4 . mrpca.at(0) = 6.; //  mrpc angles            
                   ///mod4 . mrpca.at(0) = 6.; //  mrpc angles            
                   mod4 . mrpca.at(1) = 6.; //  mrpc angles            
                   ///mod4 . mrpca.at(1) = 6.; //  mrpc angles            
                   mod4 . mrpca.at(2) = 6.; //  mrpc angles            
                   ///mod4 . mrpca.at(2) = 6.; //  mrpc angles            
                   mod4 . mrpca.at(3) = 6.; //  mrpc angles            
                   ///mod4 . mrpca.at(3) = 6.; //  mrpc angles            
                   mod4 . mrpca.at(4) = 0.; //  mrpc angles            
                   ///mod4 . mrpca.at(4) = 0.; //  mrpc angles            
                   mod4 . mrpca.at(5) = 12.; //  mrpc angles            
                   ///mod4 . mrpca.at(5) = 12.; //  mrpc angles            
                   mod4 . mrpca.at(6) = 12.; //  mrpc angles            
                   ///mod4 . mrpca.at(6) = 12.; //  mrpc angles            
                   mod4 . mrpca.at(7) = 16.; //  mrpc angles            
                   ///mod4 . mrpca.at(7) = 16.; //  mrpc angles            
                   mod4 . mrpca.at(8) = 16.; //  mrpc angles            
                   ///mod4 . mrpca.at(8) = 16.; //  mrpc angles            
                   mod4 . mrpca.at(9) = 19.; //  mrpc angles            
                   ///mod4 . mrpca.at(9) = 19.; //  mrpc angles            
                   mod4 . mrpca.at(10) = 19.; //  mrpc angles            
                   ///mod4 . mrpca.at(10) = 19.; //  mrpc angles            
                   mod4 . mrpca.at(11) = 19.; //  mrpc angles            
                   ///mod4 . mrpca.at(11) = 19.; //  mrpc angles            
                   mod4 . mrpca.at(12) = 19.; //  mrpc angles            
                   ///mod4 . mrpca.at(12) = 19.; //  mrpc angles            
                   mod4 . mrpca.at(13) = 24.; //  mrpc angles            
                   ///mod4 . mrpca.at(13) = 24.; //  mrpc angles            
                   mod4 . mrpca.at(14) = 24.; //  mrpc angles            
                   ///mod4 . mrpca.at(14) = 24.; //  mrpc angles            
                   mod4 . mrpca.at(15) = 25.; //  mrpc angles            
                   ///mod4 . mrpca.at(15) = 25.; //  mrpc angles            
                   mod4 . mrpca.at(16) = 27.; //  mrpc angles            
                   ///mod4 . mrpca.at(16) = 27.; //  mrpc angles            
                   mod4 . mrpca.at(17) = 29.; //  mrpc angles            
                   ///mod4 . mrpca.at(17) = 29.; //  mrpc angles            
                   mod4 . mrpca.at(18) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(18) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(19) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(19) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(20) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(20) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(21) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(21) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(22) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(22) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(23) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(23) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(24) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(24) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(25) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(25) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(26) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(26) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(27) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(27) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(28) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(28) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(29) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(29) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(30) = 30.; //  mrpc angles            
                   ///mod4 . mrpca.at(30) = 30.; //  mrpc angles            
                   mod4 . mrpca.at(31) = 30. ; //  mrpc angles            
                   ///mod4 . mrpca.at(31) = 30. ; //  mrpc angles            
                   mod4 . hchgt = 0.466; //  HC->Height (r)            
                   /// mod4 . hchgt = 0.466; //  HC->Height (r)            
                   mod4 . hcwid = 20.8; //   HC->Width (phi)            
                   /// mod4 . hcwid = 20.8; //   HC->Width (phi)            
                   mod4 . hclen = 8.4; //    HC->Length (z)            
                   /// mod4 . hclen = 8.4; //    HC->Length (z)            
                   mod4 . pcbhgt = 0.15; //  PCB->Height (r)            
                   /// mod4 . pcbhgt = 0.15; //  PCB->Height (r)            
                   mod4 . pcbwid = 21.0; //   PCB->Width  (phi)            
                   /// mod4 . pcbwid = 21.0; //   PCB->Width  (phi)            
                   mod4 . pcblen = 9.4; //    PCB->Length (z) *PCBLen =  9.4(real)            
                   /// mod4 . pcblen = 9.4; //    PCB->Length (z) *PCBLen =  9.4(real)            
                   mod4 . myhgt = 0.035; //  MYlar->Height            
                   /// mod4 . myhgt = 0.035; //  MYlar->Height            
                   mod4 . mywid = 21.2; //   MYlar->Width            
                   /// mod4 . mywid = 21.2; //   MYlar->Width            
                   mod4 . mylen = 8.4; //    MYlar->Length            
                   /// mod4 . mylen = 8.4; //    MYlar->Length            
                   mod4 . grhgt = 0.013; //  GRaphite->Height            
                   /// mod4 . grhgt = 0.013; //  GRaphite->Height            
                   mod4 . grwid = 20.2; //   GRaphite->Width            
                   /// mod4 . grwid = 20.2; //   GRaphite->Width            
                   mod4 . grlen = 7.4; //    GRaphite->Length            
                   /// mod4 . grlen = 7.4; //    GRaphite->Length            
                   mod4 . oghgt = 0.11; //  Outer Glass->Height            
                   /// mod4 . oghgt = 0.11; //  Outer Glass->Height            
                   mod4 . ogwid = 20.6; //   Outer Glass->Width            
                   /// mod4 . ogwid = 20.6; //   Outer Glass->Width            
                   mod4 . oglen = 7.8; //    Outer Glass->Length            
                   /// mod4 . oglen = 7.8; //    Outer Glass->Length            
                   mod4 . ighgt = 0.054; //  Inner Glass->Height            
                   /// mod4 . ighgt = 0.054; //  Inner Glass->Height            
                   mod4 . igwid = 20.0; //   Inner Glass->Width            
                   /// mod4 . igwid = 20.0; //   Inner Glass->Width            
                   mod4 . iglen = 6.1; //    Inner Glass->Length            
                   /// mod4 . iglen = 6.1; //    Inner Glass->Length            
                   mod4 . sprmin = 0.; //  SeParator Tube->RMin            
                   /// mod4 . sprmin = 0.; //  SeParator Tube->RMin            
                   mod4 . sprmax = 0.011; //   SeParator Tube->RMax            
                   /// mod4 . sprmax = 0.011; //   SeParator Tube->RMax            
                   mod4 . splen = 7.8; //    SeParator Tube->Length            
                   /// mod4 . splen = 7.8; //    SeParator Tube->Length            
                   mod4 . wgrmin = 0.; //  Wedge Tube: RMin            
                   /// mod4 . wgrmin = 0.; //  Wedge Tube: RMin            
                   mod4 . wgrmax = 0.15; //   Wedge Tube->RMax            
                   /// mod4 . wgrmax = 0.15; //   Wedge Tube->RMax            
                   mod4 . wglen = 10.0; //    Wedge Tube->Length            
                   /// mod4 . wglen = 10.0; //    Wedge Tube->Length            
                   mod4 . feeh = 0.15; //  tofr fee pcb thickness            
                   /// mod4 . feeh = 0.15; //  tofr fee pcb thickness            
                   mod4 . hbwid = 0.635; //  the slim honeycomb support box width            
                   /// mod4 . hbwid = 0.635; //  the slim honeycomb support box width            
                   mod4 . ngap = 6; //  Number of gaps in MRPC            
                   /// mod4 . ngap = 6; //  Number of gaps in MRPC            
                   mod4 . trayedgez = (3.0*2.54)+1.0; //  tray posn along rail wrt TPC centerplane (Z)            
                   /// mod4 . trayedgez = (3.0*2.54)+1.0; //  tray posn along rail wrt TPC centerplane (Z)            
                   //           
                   mod4.fill();           
             ///@}        
             //        
             /// USE btog _index=1;        
             btog.Use();        
             /// USE tray _index=1;        
             tray.Use();        
             /// USE ctbb _index=1;        
             ctbb.Use();        
             /// USE toff _index=1;        
             toff.Use();        
             /// USE modr _index=1;        
             modr.Use();        
             /// USE mod4 _index=1;        
             mod4.Use();        
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
             /// Component H	a=1	z=1	w=0.90*2*1./102.+0.+0.05*10*1./58.        
             /// Component C	a=12	z=6	w=0.90*2*12./102.+0.+0.05*4*12./58.        
             /// Component F	a=19	z=9	w=0.90*4*19./102.+0.05*6*19./146.+0.        
             /// Component S	a=32	z=16	w=0.+0.05*1*32./146.+0.        
             /// Mixture RPCgas dens=4.55e-3        
             {  AgMaterial &mix = AgMaterial::Get("Rpcgas");           
                   mix.Component("H",1,1,0.90*2*1./102.+0.+0.05*10*1./58.);           
                   mix.Component("C",12,6,0.90*2*12./102.+0.+0.05*4*12./58.);           
                   mix.Component("F",19,9,0.90*4*19./102.+0.05*6*19./146.+0.);           
                   mix.Component("S",32,16,0.+0.05*1*32./146.+0.);           
                   mix.par("dens")=4.55e-3;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
             /// Component Al	a=27	z=13	w=0.0105        
             /// Component N	a=14	z=7	w=0.7395        
             /// Component Adhesive	a=9	z=4.5	w=0.2500        
             /// Mixture HoneyComb dens=0.282        
             {  AgMaterial &mix = AgMaterial::Get("Honeycomb");           
                   mix.Component("Al",27,13,0.0105);           
                   mix.Component("N",14,7,0.7395);           
                   mix.Component("Adhesive",9,4.5,0.2500);           
                   mix.par("dens")=0.282;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
             _create = AgCreate("BTOF");        
             {           
                   AgShape myshape; // undefined shape           
                   ///Create BTOF           
                   Create("BTOF");            
             }        
             { AgPlacement place = AgPlacement("BTOF","CAVE");           
                   /// Add daughter volume BTOF to mother CAVE           
                   _stacker -> Position( AgBlock::Find("BTOF"), place );           
             } // end placement of BTOF        
       }; // BtofGeo3     
 }; // namespace BtofGeo3  
 