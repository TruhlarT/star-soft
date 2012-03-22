#include "TpceGeo1.h"  
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
 namespace TPCEGEO1 // $NMSPC  
 {     
       //     
       // ---------------------------------------------------------------------------------------------------     
          //  -----------------------------------------------------     
          /// @defgroup tpcg_doc     
          /// \class Tpcg_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t rmin;     
          ///Float_t rmax;     
          ///Float_t length;     
          ///Float_t wheelir;     
          ///Float_t wheelor;     
          ///Float_t wheelthk;     
          ///Float_t sengasor;     
          ///Float_t tpeathk;     
          ///Float_t membthk;     
          ///Float_t tiaddr;     
          ///Float_t tinxdr;     
          ///Float_t tikadr;     
          ///Float_t tialdr;     
          ///Float_t tocsdr;     
          ///Float_t tokadr;     
          ///Float_t tonxdr;     
          ///Float_t toaddr;     
          ///Float_t toigdr;     
          ///Float_t toaldr;     
          ///Float_t tohadr;     
          ///Float_t mwcread;     
          ///Float_t gascorr;     
          ///Int_t _index;     
          //     
          Tpcg_t tpcg;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup tecw_doc     
          /// \class Tecw_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t sec;     
          ///Float_t gaprad;     
          ///Float_t gapheit;     
          ///Float_t gapwidi;     
          ///Float_t gapwido;     
          ///Float_t gapshft;     
          ///Float_t inwidth;     
          ///Float_t ouwidth;     
          ///Float_t height;     
          ///Float_t ppdepth;     
          ///Float_t asdepth;     
          ///Float_t ggdepth;     
          ///Float_t mwcdepth;     
          ///Float_t boundary;     
          ///Float_t rcenter;     
          ///Float_t mwcinn;     
          ///Float_t mwcout;     
          ///Float_t mwchei;     
          ///Float_t mwccent;     
          ///Float_t mwcnwir;     
          ///Float_t n;     
          ///Float_t nex;     
          ///Array_t<Float_t> z;     
          ///Array_t<Float_t> dz;     
          ///Array_t<Float_t> xex;     
          ///Array_t<Float_t> zex;     
          ///Array_t<Float_t> dxex;     
          ///Array_t<Float_t> dzex;     
          ///Array_t<Float_t> nhplane;     
          ///Float_t cardw;     
          ///Float_t cardth;     
          ///Float_t coolw;     
          ///Float_t coolth;     
          ///Float_t cardoff;     
          ///Float_t cooloff;     
          ///Float_t slotw;     
          ///Float_t slotrad;     
          ///Float_t pipethk;     
          ///Float_t pipeht;     
          ///Float_t manithk;     
          ///Float_t maniwid;     
          ///Float_t tan15;     
          ///Float_t clearance;     
          ///Float_t whlipthk;     
          ///Float_t whlipwid;     
          ///Float_t whblklen;     
          ///Float_t whblkpos;     
          ///Float_t whblkin;     
          ///Int_t _index;     
          //     
          Tecw_t tecw;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup trov_doc     
          /// \class Trov_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t sec;     
          ///Array_t<Float_t> nhp;     
          ///Array_t<Float_t> hx;     
          ///Float_t offcardinout;     
          ///Int_t _index;     
          //     
          Trov_t trov;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup tprs_doc     
          /// \class Tprs_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t sec;     
          ///Float_t nrow;     
          ///Float_t pitch;     
          ///Float_t width;     
          ///Float_t super;     
          ///Array_t<Float_t> rpads;     
          ///Array_t<Float_t> npads;     
          ///Int_t _index;     
          //     
          Tprs_t tprs;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup trdo_doc     
          /// \class Trdo_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t rdovthk;     
          ///Float_t rdothk;     
          ///Float_t rdolen;     
          ///Float_t nrdobrd;     
          ///Array_t<Float_t> rdoht;     
          ///Int_t _index;     
          //     
          Trdo_t trdo;     
          //     
          ///@addtogroup TpceGeo1_vars     
          ///@{        
                Float_t tocsir,tocsor,tokair,tokaor,tonxir,tonxor,toadir,toador,toigir,toigor,toalir,toalor,tohair,tohaor,tofsir,tofsor,tofcir,tofcor,tiadir,tiador,tinxir,tinxor,tikair,tikaor,tialir,tialor,tifcir,tifcor,tpgvir,tpgvleng,tofcleng,tpcwz,tpgvz,tpeaz,tprdoz,dx_dz,dxb,del,a,b,radoff,zvalue;        
                //        
                /// Float_t tocsir,tocsor,tokair,tokaor,tonxir,tonxor,toadir,toador,toigir,toigor,toalir,toalor,tohair,tohaor,tofsir,tofsor,tofcir,tofcor,tiadir,tiador,tinxir,tinxor,tikair,tikaor,tialir,tialor,tifcir,tifcor,tpgvir,tpgvleng,tofcleng,tpcwz,tpgvz,tpeaz,tprdoz,dx_dz,dxb,del,a,b,radoff,zvalue        
          ///@}     
          ///@addtogroup TpceGeo1_vars     
          ///@{        
                Float_t pipeoff;        
                //        
                /// Float_t pipeoff        
          ///@}     
          ///@addtogroup TpceGeo1_vars     
          ///@{        
                Float_t ztemp,xtemp,hpla,xbottom;        
                //        
                /// Float_t ztemp,xtemp,hpla,xbottom        
          ///@}     
          ///@addtogroup TpceGeo1_vars     
          ///@{        
                Float_t mntcylid,mntcylod,mntcylht,xlip;        
                //        
                /// Float_t mntcylid,mntcylod,mntcylht,xlip        
          ///@}     
          ///@addtogroup TpceGeo1_vars     
          ///@{        
                Float_t t,p,patm,rho,density;        
                //        
                /// Float_t t,p,patm,rho,density        
          ///@}     
          ///@addtogroup TpceGeo1_vars     
          ///@{        
                Int_t i_row,i_sec,i,jj,kk,i_nhp,j_nho;        
                //        
                /// Int_t i_row,i_sec,i,jj,kk,i_nhp,j_nho        
          ///@}     
       TpceGeo1::TpceGeo1()     
         : AgModule("TpceGeo1","  is the TPC system in GSTAR ")     
       {        
       }     
          // ---------------------------------------------------------------------------------------------------     
          void TPCE::Block( AgCreate create )     
          {         
                ///@addtogroup TPCE_doc        
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
                      { AgAttribute attr = AgAttribute("TPCE");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tpcg.rmin;              
                            shape.par("rmax")=tpcg.rmax;              
                            shape.par("dz")=tpcg.length/2;              
                            /// Shape Tube rmin=tpcg.rmin rmax=tpcg.rmax dz=tpcg.length/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TPCE;              
                            _stacker -> Build(this);              
                      }           
                      tpgvz  = (tpcg.membthk + tpgvleng)/2;           
                      _create = AgCreate("TPGV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TPGV              
                            Create("TPGV");               
                      }           
                      { AgPlacement place = AgPlacement("TPGV","TPCE");              
                            /// Add daughter volume TPGV to mother TPCE              
                            place.TranslateZ(+tpgvz);              
                            /// Translate z = +tpgvz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 75              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = -15              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=75,_thetay=90,_phiy=-15,_thetaz=0,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("TPGV"), place );              
                      } // end placement of TPGV           
                      { AgPlacement place = AgPlacement("TPGV","TPCE");              
                            /// Add daughter volume TPGV to mother TPCE              
                            place.TranslateZ(-tpgvz);              
                            /// Translate z = -tpgvz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 105              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 195              
                            /// G3 Reference: thetaz = 180              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=105,_thetay=90,_phiy=195,_thetaz=180,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("TPGV"), place );              
                      } // end placement of TPGV           
                      _create = AgCreate("TIFC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TIFC              
                            Create("TIFC");               
                      }           
                      { AgPlacement place = AgPlacement("TIFC","TPCE");              
                            /// Add daughter volume TIFC to mother TPCE              
                            _stacker -> Position( AgBlock::Find("TIFC"), place );              
                      } // end placement of TIFC           
                      _create = AgCreate("TOFC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOFC              
                            Create("TOFC");               
                      }           
                      { AgPlacement place = AgPlacement("TOFC","TPCE");              
                            /// Add daughter volume TOFC to mother TPCE              
                            _stacker -> Position( AgBlock::Find("TOFC"), place );              
                      } // end placement of TOFC           
                      _create = AgCreate("TPCM");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TPCM              
                            Create("TPCM");               
                      }           
                      { AgPlacement place = AgPlacement("TPCM","TPCE");              
                            /// Add daughter volume TPCM to mother TPCE              
                            _stacker -> Position( AgBlock::Find("TPCM"), place );              
                      } // end placement of TPCM           
                      tpeaz  = (tofcleng - tpcg.tpeathk)/2;           
                      _create = AgCreate("TPEA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TPEA              
                            Create("TPEA");               
                      }           
                      { AgPlacement place = AgPlacement("TPEA","TPCE");              
                            /// Add daughter volume TPEA to mother TPCE              
                            place.TranslateZ(+tpeaz);              
                            /// Translate z = +tpeaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 75              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = -15              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=75,_thetay=90,_phiy=-15,_thetaz=0,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("TPEA"), place );              
                      } // end placement of TPEA           
                      { AgPlacement place = AgPlacement("TPEA","TPCE");              
                            /// Add daughter volume TPEA to mother TPCE              
                            place.TranslateZ(-tpeaz);              
                            /// Translate z = -tpeaz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 105              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 195              
                            /// G3 Reference: thetaz = 180              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=105,_thetay=90,_phiy=195,_thetaz=180,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("TPEA"), place );              
                      } // end placement of TPEA           
                      tpcwz  = (tpcg.length-2*trdo.rdovthk-tpcg.wheelthk)/2;           
                      _create = AgCreate("TPCW");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TPCW              
                            Create("TPCW");               
                      }           
                      { AgPlacement place = AgPlacement("TPCW","TPCE");              
                            /// Add daughter volume TPCW to mother TPCE              
                            place.TranslateZ(+tpcwz);              
                            /// Translate z = +tpcwz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 75              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = -15              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=75,_thetay=90,_phiy=-15,_thetaz=0,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("TPCW"), place );              
                      } // end placement of TPCW           
                      { AgPlacement place = AgPlacement("TPCW","TPCE");              
                            /// Add daughter volume TPCW to mother TPCE              
                            place.TranslateZ(-tpcwz);              
                            /// Translate z = -tpcwz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 105              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 195              
                            /// G3 Reference: thetaz = 180              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=105,_thetay=90,_phiy=195,_thetaz=180,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("TPCW"), place );              
                      } // end placement of TPCW           
                      tprdoz  = (tpcg.length-trdo.rdovthk)/2;           
                      _create = AgCreate("TRDV");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TRDV              
                            Create("TRDV");               
                      }           
                      { AgPlacement place = AgPlacement("TRDV","TPCE");              
                            /// Add daughter volume TRDV to mother TPCE              
                            place.TranslateZ(+tprdoz);              
                            /// Translate z = +tprdoz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 75              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = -15              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=75,_thetay=90,_phiy=-15,_thetaz=0,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("TRDV"), place );              
                      } // end placement of TRDV           
                      { AgPlacement place = AgPlacement("TRDV","TPCE");              
                            /// Add daughter volume TRDV to mother TPCE              
                            place.TranslateZ(-tprdoz);              
                            /// Translate z = -tprdoz              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 105              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 195              
                            /// G3 Reference: thetaz = 180              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=105,_thetay=90,_phiy=195,_thetaz=180,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("TRDV"), place );              
                      } // end placement of TRDV           
                      END_OF_TPCE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPCE     
          // ---------------------------------------------------------------------------------------------------     
          void TPGV::Block( AgCreate create )     
          {         
                ///@addtogroup TPGV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      if ( tpcg.gascorr==1 )           
                      {              
                            density=0.9*0.001782+0.1*0.000667;              
                      }           
                      else           
                      {              
                            t    = 298.06;              
                            p    = 1016.59;              
                            patm = 0.001*p*750.062/760.;              
                            rho  =(0.9*0.001782+0.1*0.000717);              
                            density=rho*(273.15/t)*patm;              
                      }           
                      /// Component Ar	a=40	z=18	w=9           
                      /// Component C	a=12	z=6	w=1           
                      /// Component H	a=1	z=1	w=4           
                      /// Mixture p10 dens=density           
                      {  AgMaterial &mix = AgMaterial::Get("P10");              
                            mix.Component("Ar",40,18,9);              
                            mix.Component("C",12,6,1);              
                            mix.Component("H",1,1,4);              
                            mix.par("dens")=density;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tpgvir;              
                            shape.par("rmax")=tpcg.sengasor;              
                            shape.par("dz")=tpgvleng/2;              
                            /// Shape Tube rmin=tpgvir rmax=tpcg.sengasor dz=tpgvleng/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TPGV;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TPSS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TPSS              
                            Create("TPSS");               
                      }           
                      END_OF_TPGV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPGV     
          // ---------------------------------------------------------------------------------------------------     
          void TPSS::Block( AgCreate create )     
          {         
                ///@addtogroup TPSS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TPSS");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=12;              
                            shape.par("iaxis")=2;              
                            /// Shape Division ndiv=12 iaxis=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TPSS;              
                            _stacker -> Build(this);              
                      }           
                      /// Loop on i_sec from 1 to 2 step=1           
                      for ( i_sec=1; (1>0)? (i_sec<=2):(i_sec>=2); i_sec+=1 )           
                      {              
                            /// USE tprs sec=i_sec ;              
                            tprs.Use("sec",(Float_t)i_sec );              
                            /// Loop on i_row from 1 to nint(tprs.nrow) step=1              
                            for ( i_row=1; (1>0)? (i_row<=nint(tprs.nrow)):(i_row>=nint(tprs.nrow)); i_row+=1 )              
                            {                 
                                  if ( nint(tprs.super)==3||i_row==1 )                 
                                  {                    
                                        _create = AgCreate("TPAD");                    
                                        {                       
                                              AgShape myshape; // undefined shape                       
                                              ///Create TPAD                       
                                              Create("TPAD");                        
                                        }                    
                                        { AgPlacement place = AgPlacement("TPAD","TPSS");                       
                                              /// Add daughter volume TPAD to mother TPSS                       
                                              place.TranslateX(tprs.rpads(i_row)-tprs.width);                       
                                              /// Translate x = tprs.rpads(i_row)-tprs.width                       
                                              place.par("dx")=tprs.width/2;                       
                                              place.par("dy")=tprs.npads(i_row)*tprs.pitch/2;                       
                                              _stacker -> Position( AgBlock::Find("TPAD"), place );                       
                                        } // end placement of TPAD                    
                                  }                 
                                  if ( nint(tprs.super)>0 )                 
                                  {                    
                                        _create = AgCreate("TPAD");                    
                                        {                       
                                              AgShape myshape; // undefined shape                       
                                              ///Create TPAD                       
                                              Create("TPAD");                        
                                        }                    
                                        { AgPlacement place = AgPlacement("TPAD","TPSS");                       
                                              /// Add daughter volume TPAD to mother TPSS                       
                                              place.TranslateX(tprs.rpads(i_row));                       
                                              /// Translate x = tprs.rpads(i_row)                       
                                              place.par("dx")=tprs.width/2;                       
                                              place.par("dy")=tprs.npads(i_row)*tprs.pitch/2;                       
                                              _stacker -> Position( AgBlock::Find("TPAD"), place );                       
                                        } // end placement of TPAD                    
                                  }                 
                                  if ( nint(tprs.super)==3||i_row==nint(tprs.nrow) )                 
                                  {                    
                                        _create = AgCreate("TPAD");                    
                                        {                       
                                              AgShape myshape; // undefined shape                       
                                              ///Create TPAD                       
                                              Create("TPAD");                        
                                        }                    
                                        { AgPlacement place = AgPlacement("TPAD","TPSS");                       
                                              /// Add daughter volume TPAD to mother TPSS                       
                                              place.TranslateX(tprs.rpads(i_row)+tprs.width);                       
                                              /// Translate x = tprs.rpads(i_row)+tprs.width                       
                                              place.par("dx")=tprs.width/2;                       
                                              place.par("dy")=tprs.npads(i_row)*tprs.pitch/2;                       
                                              _stacker -> Position( AgBlock::Find("TPAD"), place );                       
                                        } // end placement of TPAD                    
                                  }                 
                            }              
                      }           
                      END_OF_TPSS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPSS     
          // ---------------------------------------------------------------------------------------------------     
          void TPAD::Block( AgCreate create )     
          {         
                ///@addtogroup TPAD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      if ( tprs.width<1.5 )           
                      { AgAttribute attr = AgAttribute("TPAD");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.par("serial")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      if ( tprs.width>1.5 )           
                      { AgAttribute attr = AgAttribute("TPAD");              
                            attr.par("seen")=0;              
                            attr.par("colo")=2;              
                            attr.par("serial")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material p10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("P10");              
                            _material = mat;              
                      }           
                      /// Material sensitive_gas isvol=1 stemax=2.5*tprs_width            
                      { AgMaterial &mat = AgMaterial::Get("Sensitive_gas");              
                            mat.par("isvol")=1;              
                            mat.par("stemax")=2.5*tprs.width;              
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
                            if (_same_shape) goto END_OF_TPAD;              
                            _stacker -> Build(this);              
                      }           
                      // _medium.par("STRA") = 1.;           
                      END_OF_TPAD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPAD     
          // ---------------------------------------------------------------------------------------------------     
          void TIFC::Block( AgCreate create )     
          {         
                ///@addtogroup TIFC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TIFC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tiadir;              
                            shape.par("rmax")=tifcor;              
                            shape.par("dz")=tofcleng/2;              
                            /// Shape Tube rmin=tiadir rmax=tifcor dz=tofcleng/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TIFC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TINX");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TINX              
                            Create("TINX");               
                      }           
                      { AgPlacement place = AgPlacement("TINX","TIFC");              
                            /// Add daughter volume TINX to mother TIFC              
                            _stacker -> Position( AgBlock::Find("TINX"), place );              
                      } // end placement of TINX           
                      END_OF_TIFC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TIFC     
          // ---------------------------------------------------------------------------------------------------     
          void TINX::Block( AgCreate create )     
          {         
                ///@addtogroup TINX_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component C	a=12	z=6	w=5           
                      /// Component H	a=1	z=1	w=8           
                      /// Component O	a=16	z=8	w=2           
                      /// Mixture Nomex dens=0.048           
                      {  AgMaterial &mix = AgMaterial::Get("Nomex");              
                            mix.Component("C",12,6,5);              
                            mix.Component("H",1,1,8);              
                            mix.Component("O",16,8,2);              
                            mix.par("dens")=0.048;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("TINX");              
                            attr.par("seen")=1;              
                            attr.par("colo")=5;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tinxir;              
                            /// Shape Tube rmin=tinxir               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TINX;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TIKA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TIKA              
                            Create("TIKA");               
                      }           
                      { AgPlacement place = AgPlacement("TIKA","TINX");              
                            /// Add daughter volume TIKA to mother TINX              
                            _stacker -> Position( AgBlock::Find("TIKA"), place );              
                      } // end placement of TIKA           
                      END_OF_TINX:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TINX     
          // ---------------------------------------------------------------------------------------------------     
          void TIKA::Block( AgCreate create )     
          {         
                ///@addtogroup TIKA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TIKA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tikair;              
                            /// Shape Tube rmin=tikair               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TIKA;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TIAL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TIAL              
                            Create("TIAL");               
                      }           
                      { AgPlacement place = AgPlacement("TIAL","TIKA");              
                            /// Add daughter volume TIAL to mother TIKA              
                            _stacker -> Position( AgBlock::Find("TIAL"), place );              
                      } // end placement of TIAL           
                      END_OF_TIKA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TIKA     
          // ---------------------------------------------------------------------------------------------------     
          void TIAL::Block( AgCreate create )     
          {         
                ///@addtogroup TIAL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TIAL");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tialir;              
                            /// Shape Tube rmin=tialir               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TIAL;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TIAL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TIAL     
          // ---------------------------------------------------------------------------------------------------     
          void TOFC::Block( AgCreate create )     
          {         
                ///@addtogroup TOFC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Nitrogen_gas            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Nitrogen_gas");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TOFC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tofcir;              
                            shape.par("rmax")=tofcor;              
                            shape.par("dz")=tofcleng/2;              
                            /// Shape Tube rmin=tofcir rmax=tofcor dz=tofcleng/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOFC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TOFS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOFS              
                            Create("TOFS");               
                      }           
                      { AgPlacement place = AgPlacement("TOFS","TOFC");              
                            /// Add daughter volume TOFS to mother TOFC              
                            _stacker -> Position( AgBlock::Find("TOFS"), place );              
                      } // end placement of TOFS           
                      _create = AgCreate("TOST");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOST              
                            Create("TOST");               
                      }           
                      { AgPlacement place = AgPlacement("TOST","TOFC");              
                            /// Add daughter volume TOST to mother TOFC              
                            _stacker -> Position( AgBlock::Find("TOST"), place );              
                      } // end placement of TOST           
                      END_OF_TOFC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TOFC     
          // ---------------------------------------------------------------------------------------------------     
          void TOFS::Block( AgCreate create )     
          {         
                ///@addtogroup TOFS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material COPPER            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Copper");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TOFS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmax")=tofsor;              
                            /// Shape Tube rmax=tofsor               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOFS;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TOKA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOKA              
                            Create("TOKA");               
                      }           
                      { AgPlacement place = AgPlacement("TOKA","TOFS");              
                            /// Add daughter volume TOKA to mother TOFS              
                            _stacker -> Position( AgBlock::Find("TOKA"), place );              
                      } // end placement of TOKA           
                      END_OF_TOFS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TOFS     
          // ---------------------------------------------------------------------------------------------------     
          void TOKA::Block( AgCreate create )     
          {         
                ///@addtogroup TOKA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TOKA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tokair;              
                            /// Shape Tube rmin=tokair               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOKA;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TONX");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TONX              
                            Create("TONX");               
                      }           
                      { AgPlacement place = AgPlacement("TONX","TOKA");              
                            /// Add daughter volume TONX to mother TOKA              
                            _stacker -> Position( AgBlock::Find("TONX"), place );              
                      } // end placement of TONX           
                      END_OF_TOKA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TOKA     
          // ---------------------------------------------------------------------------------------------------     
          void TONX::Block( AgCreate create )     
          {         
                ///@addtogroup TONX_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Nomex            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Nomex");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TONX");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tonxir;              
                            /// Shape Tube rmin=tonxir               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TONX;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TOAD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOAD              
                            Create("TOAD");               
                      }           
                      { AgPlacement place = AgPlacement("TOAD","TONX");              
                            /// Add daughter volume TOAD to mother TONX              
                            _stacker -> Position( AgBlock::Find("TOAD"), place );              
                      } // end placement of TOAD           
                      END_OF_TONX:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TONX     
          // ---------------------------------------------------------------------------------------------------     
          void TOAD::Block( AgCreate create )     
          {         
                ///@addtogroup TOAD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TOAD");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=toadir;              
                            /// Shape Tube rmin=toadir               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOAD;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TOAD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TOAD     
          // ---------------------------------------------------------------------------------------------------     
          void TOST::Block( AgCreate create )     
          {         
                ///@addtogroup TOST_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TOST");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=toalir;              
                            /// Shape Tube rmin=toalir               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOST;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TOHA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOHA              
                            Create("TOHA");               
                      }           
                      { AgPlacement place = AgPlacement("TOHA","TOST");              
                            /// Add daughter volume TOHA to mother TOST              
                            _stacker -> Position( AgBlock::Find("TOHA"), place );              
                      } // end placement of TOHA           
                      END_OF_TOST:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TOST     
          // ---------------------------------------------------------------------------------------------------     
          void TOHA::Block( AgCreate create )     
          {         
                ///@addtogroup TOHA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component Al	a=27	z=13	w=0.0105           
                      /// Component N	a=14	z=7	w=0.7395           
                      /// Component Adhesive	a=9	z=4.5	w=0.2500           
                      /// Mixture Al_honeycomb dens=0.282           
                      {  AgMaterial &mix = AgMaterial::Get("Al_honeycomb");              
                            mix.Component("Al",27,13,0.0105);              
                            mix.Component("N",14,7,0.7395);              
                            mix.Component("Adhesive",9,4.5,0.2500);              
                            mix.par("dens")=0.282;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
                      }           
                      { AgAttribute attr = AgAttribute("TOHA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tohair;              
                            /// Shape Tube rmin=tohair               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOHA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TOHA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TOHA     
          // ---------------------------------------------------------------------------------------------------     
          void TPCM::Block( AgCreate create )     
          {         
                ///@addtogroup TPCM_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Mylar            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Mylar");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TPCM");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tpgvir;              
                            shape.par("rmax")=tpcg.sengasor;              
                            shape.par("dz")=tpcg.membthk/2;              
                            /// Shape Tube rmin=tpgvir rmax=tpcg.sengasor dz=tpcg.membthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TPCM;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TPCM:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPCM     
          // ---------------------------------------------------------------------------------------------------     
          void TPEA::Block( AgCreate create )     
          {         
                ///@addtogroup TPEA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material p10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("P10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TPEA");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tpgvir;              
                            shape.par("rmax")=tpcg.sengasor;              
                            shape.par("dz")=tpcg.tpeathk/2;              
                            /// Shape Tube rmin=tpgvir rmax=tpcg.sengasor dz=tpcg.tpeathk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TPEA;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TESS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TESS              
                            Create("TESS");               
                      }           
                      END_OF_TPEA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPEA     
          // ---------------------------------------------------------------------------------------------------     
          void TESS::Block( AgCreate create )     
          {         
                ///@addtogroup TESS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TESS");              
                            attr.par("seen")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=12;              
                            shape.par("iaxis")=2;              
                            /// Shape Division ndiv=12 iaxis=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TESS;              
                            _stacker -> Build(this);              
                      }           
                      /// Loop on i_sec from 1 to 2 step=1           
                      for ( i_sec=1; (1>0)? (i_sec<=2):(i_sec>=2); i_sec+=1 )           
                      {              
                            /// USE tecw sec=i_sec ;              
                            tecw.Use("sec",(Float_t)i_sec );              
                            /// USE trov sec=i_sec ;              
                            trov.Use("sec",(Float_t)i_sec );              
                            _create = AgCreate("TSEC");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TSEC                 
                                  Create("TSEC");                  
                            }              
                            { AgPlacement place = AgPlacement("TSEC","TESS");                 
                                  /// Add daughter volume TSEC to mother TESS                 
                                  place.TranslateX(tecw.rcenter);                 
                                  /// Translate x = tecw.rcenter                 
                                  place.TranslateZ((tpcg.tpeathk-tecw.asdepth-tecw.ppdepth-tecw.ggdepth)/2);                 
                                  /// Translate z = (tpcg.tpeathk-tecw.asdepth-tecw.ppdepth-tecw.ggdepth)/2                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YZX" ); // ORT=YZX                 
                                  /// Axis substitution: XYZ --> YZX                 
                                  _stacker -> Position( AgBlock::Find("TSEC"), place );                 
                            } // end placement of TSEC              
                      }           
                      END_OF_TESS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TESS     
          // ---------------------------------------------------------------------------------------------------     
          void TSEC::Block( AgCreate create )     
          {         
                ///@addtogroup TSEC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Trd1");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx1")=tecw.inwidth/2;              
                            shape.par("dx2")=tecw.ouwidth/2;              
                            shape.par("dy")=(tecw.ppdepth+tecw.asdepth+tecw.ggdepth)/2;              
                            shape.par("dz")=tecw.height/2;              
                            /// Shape Trd1 dx1=tecw.inwidth/2 dx2=tecw.ouwidth/2 dy=(tecw.ppdepth+tecw.asdepth+tecw.ggdepth)/2 dz=tecw.height/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TSEC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TMWC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TMWC              
                            Create("TMWC");               
                      }           
                      { AgPlacement place = AgPlacement("TMWC","TSEC");              
                            /// Add daughter volume TMWC to mother TSEC              
                            place.TranslateY(-(tecw.ppdepth+tecw.asdepth)/2);              
                            /// Translate y = -(tecw.ppdepth+tecw.asdepth)/2              
                            _stacker -> Position( AgBlock::Find("TMWC"), place );              
                      } // end placement of TMWC           
                      _create = AgCreate("TIAG");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TIAG              
                            Create("TIAG");               
                      }           
                      dx_dz = (tecw.ouwidth - tecw.inwidth)/(2*tecw.height );           
                      dxb = tecw.boundary * sqrt( 1. + dx_dz*dx_dz );           
                      /// Loop on i from 1 to nint(tecw.n) step=1           
                      for ( i=1; (1>0)? (i<=nint(tecw.n)):(i>=nint(tecw.n)); i+=1 )           
                      {              
                            { AgPlacement place = AgPlacement("TIAG","TSEC");                 
                                  /// Add daughter volume TIAG to mother TSEC                 
                                  place.TranslateY(+tecw.ppdepth/2+tecw.ggdepth/2);                 
                                  /// Translate y = +tecw.ppdepth/2+tecw.ggdepth/2                 
                                  place.TranslateZ(-tecw.height/2+tecw.z(i));                 
                                  /// Translate z = -tecw.height/2+tecw.z(i)                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.par("dy")=tecw.asdepth/2;                 
                                  place.par("dz")=tecw.dz(i)/2;                 
                                  place.par("dx1")=tecw.inwidth/2-dxb+(tecw.z(i)-tecw.dz(i)/2)*dx_dz;                 
                                  place.par("dx2")=tecw.inwidth/2-dxb+(tecw.z(i)+tecw.dz(i)/2)*dx_dz;                 
                                  _stacker -> Position( AgBlock::Find("TIAG"), place );                 
                            } // end placement of TIAG              
                      }           
                      _create = AgCreate("TCEX");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TCEX              
                            Create("TCEX");               
                      }           
                      _create = AgCreate("TAEC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TAEC              
                            Create("TAEC");               
                      }           
                      _create = AgCreate("THOL");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create THOL              
                            Create("THOL");               
                      }           
                      _create = AgCreate("THRA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create THRA              
                            Create("THRA");               
                      }           
                      _create = AgCreate("THLA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create THLA              
                            Create("THLA");               
                      }           
                      /// Loop on i_nhp from 1 to 16 step=1           
                      for ( i_nhp=1; (1>0)? (i_nhp<=16):(i_nhp>=16); i_nhp+=1 )           
                      {              
                            hpla = -tecw.height/2+tecw.z(1)-tecw.dz(1)/2+trov.offcardinout ;//first pl;              
                            zvalue = hpla+4.0*(i_nhp-1);              
                            if ( trov.nhp(i_nhp)>0 )              
                            {                 
                                  /// Loop on j_nho from 1 to trov.nhp(i_nhp) step=1                 
                                  for ( j_nho=1; (1>0)? (j_nho<=trov.nhp(i_nhp)):(j_nho>=trov.nhp(i_nhp)); j_nho+=1 )                 
                                  {                    
                                        { AgPlacement place = AgPlacement("TCEX","TSEC");                       
                                              /// Add daughter volume TCEX to mother TSEC                       
                                              place.TranslateX(trov.hx(j_nho,i_nhp));                       
                                              /// Translate x = trov.hx(j_nho,i_nhp)                       
                                              place.TranslateY(+tecw.ppdepth/2+tecw.ggdepth/2);                       
                                              /// Translate y = +tecw.ppdepth/2+tecw.ggdepth/2                       
                                              place.TranslateZ(zvalue+tecw.cardoff);                       
                                              /// Translate z = zvalue+tecw.cardoff                       
                                              _stacker -> Position( AgBlock::Find("TCEX"), place );                       
                                        } // end placement of TCEX                    
                                        { AgPlacement place = AgPlacement("TAEC","TSEC");                       
                                              /// Add daughter volume TAEC to mother TSEC                       
                                              place.TranslateX(trov.hx(j_nho,i_nhp));                       
                                              /// Translate x = trov.hx(j_nho,i_nhp)                       
                                              place.TranslateY(+tecw.ppdepth/2+tecw.ggdepth/2);                       
                                              /// Translate y = +tecw.ppdepth/2+tecw.ggdepth/2                       
                                              place.TranslateZ(zvalue+tecw.cooloff);                       
                                              /// Translate z = zvalue+tecw.cooloff                       
                                              _stacker -> Position( AgBlock::Find("TAEC"), place );                       
                                        } // end placement of TAEC                    
                                        { AgPlacement place = AgPlacement("THOL","TSEC");                       
                                              /// Add daughter volume THOL to mother TSEC                       
                                              place.TranslateX(trov.hx(j_nho,i_nhp));                       
                                              /// Translate x = trov.hx(j_nho,i_nhp)                       
                                              place.TranslateY(+tecw.ggdepth/2-tecw.asdepth/2);                       
                                              /// Translate y = +tecw.ggdepth/2-tecw.asdepth/2                       
                                              place.TranslateZ(zvalue+tecw.cardoff);                       
                                              /// Translate z = zvalue+tecw.cardoff                       
                                              _stacker -> Position( AgBlock::Find("THOL"), place );                       
                                        } // end placement of THOL                    
                                        { AgPlacement place = AgPlacement("THRA","TSEC");                       
                                              /// Add daughter volume THRA to mother TSEC                       
                                              place.TranslateX(trov.hx(j_nho,i_nhp)+tecw.slotw/2);                       
                                              /// Translate x = trov.hx(j_nho,i_nhp)+tecw.slotw/2                       
                                              place.TranslateY(+tecw.ggdepth/2-tecw.asdepth/2);                       
                                              /// Translate y = +tecw.ggdepth/2-tecw.asdepth/2                       
                                              place.TranslateZ(zvalue+tecw.cardoff);                       
                                              /// Translate z = zvalue+tecw.cardoff                       
                                              /// G3 Reference: thetax = 90                       
                                              /// G3 Reference: phix = 0                       
                                              /// G3 Reference: thetay = 90                       
                                              /// G3 Reference: phiy = 90                       
                                              /// G3 Reference: thetaz = 0                       
                                              /// G3 Reference: phiz = 0                       
                                              place.Ortho( "ZXY" ); // ORT=ZXY                       
                                              /// Axis substitution: XYZ --> ZXY                       
                                              _stacker -> Position( AgBlock::Find("THRA"), place );                       
                                        } // end placement of THRA                    
                                        { AgPlacement place = AgPlacement("THLA","TSEC");                       
                                              /// Add daughter volume THLA to mother TSEC                       
                                              place.TranslateX(trov.hx(j_nho,i_nhp)-tecw.slotw/2);                       
                                              /// Translate x = trov.hx(j_nho,i_nhp)-tecw.slotw/2                       
                                              place.TranslateY(+tecw.ggdepth/2-tecw.asdepth/2);                       
                                              /// Translate y = +tecw.ggdepth/2-tecw.asdepth/2                       
                                              place.TranslateZ(zvalue+tecw.cardoff);                       
                                              /// Translate z = zvalue+tecw.cardoff                       
                                              /// G3 Reference: thetax = 90                       
                                              /// G3 Reference: phix = 0                       
                                              /// G3 Reference: thetay = 90                       
                                              /// G3 Reference: phiy = 90                       
                                              /// G3 Reference: thetaz = 0                       
                                              /// G3 Reference: phiz = 0                       
                                              place.Ortho( "ZXY" ); // ORT=ZXY                       
                                              /// Axis substitution: XYZ --> ZXY                       
                                              _stacker -> Position( AgBlock::Find("THLA"), place );                       
                                        } // end placement of THLA                    
                                  }                 
                            }              
                      }           
                      _create = AgCreate("TOAE");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOAE              
                            Create("TOAE");               
                      }           
                      /// Loop on i from 1 to nint(tecw.nex) step=1           
                      for ( i=1; (1>0)? (i<=nint(tecw.nex)):(i>=nint(tecw.nex)); i+=1 )           
                      {              
                            { AgPlacement place = AgPlacement("TOAE","TSEC");                 
                                  /// Add daughter volume TOAE to mother TSEC                 
                                  place.TranslateX(tecw.xex(i));                 
                                  /// Translate x = tecw.xex(i)                 
                                  place.TranslateY(+tecw.ppdepth/2+tecw.ggdepth/2);                 
                                  /// Translate y = +tecw.ppdepth/2+tecw.ggdepth/2                 
                                  place.TranslateZ(tecw.zex(i)-tecw.height/2);                 
                                  /// Translate z = tecw.zex(i)-tecw.height/2                 
                                  place.par("dx")=tecw.dxex(i)/2;                 
                                  place.par("dy")=tecw.asdepth/2;                 
                                  place.par("dz")=tecw.dzex(i)/2;                 
                                  _stacker -> Position( AgBlock::Find("TOAE"), place );                 
                            } // end placement of TOAE              
                      }           
                      END_OF_TSEC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TSEC     
          // ---------------------------------------------------------------------------------------------------     
          void TMWC::Block( AgCreate create )     
          {         
                ///@addtogroup TMWC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material p10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("P10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TMWC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=3;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trd1");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx1")=tecw.inwidth/2;              
                            shape.par("dx2")=tecw.ouwidth/2;              
                            shape.par("dy")=tecw.ggdepth/2;              
                            shape.par("dz")=tecw.height/2;              
                            /// Shape Trd1 dx1=tecw.inwidth/2 dx2=tecw.ouwidth/2 dy=tecw.ggdepth/2 dz=tecw.height/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TMWC;              
                            _stacker -> Build(this);              
                      }           
                      if ( not (  tpcg.mwcread>0 )) { return;   }           
                      _create = AgCreate("TMEA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TMEA              
                            Create("TMEA");               
                      }           
                      { AgPlacement place = AgPlacement("TMEA","TMWC");              
                            /// Add daughter volume TMEA to mother TMWC              
                            place.TranslateY(+(tecw.ggdepth-tecw.mwcdepth)/2);              
                            /// Translate y = +(tecw.ggdepth-tecw.mwcdepth)/2              
                            place.TranslateZ(tecw.mwccent);              
                            /// Translate z = tecw.mwccent              
                            _stacker -> Position( AgBlock::Find("TMEA"), place );              
                      } // end placement of TMEA           
                      END_OF_TMWC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TMWC     
          // ---------------------------------------------------------------------------------------------------     
          void TMEA::Block( AgCreate create )     
          {         
                ///@addtogroup TMEA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material p10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("P10");              
                            _material = mat;              
                      }           
                      /// Material sensitive_gas isvol=1 stemax=5            
                      { AgMaterial &mat = AgMaterial::Get("Sensitive_gas");              
                            mat.par("isvol")=1;              
                            mat.par("stemax")=5;              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TMEA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trd1");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx1")=tecw.mwcinn/2;              
                            shape.par("dx2")=tecw.mwcout/2;              
                            shape.par("dy")=tecw.mwcdepth/2;              
                            shape.par("dz")=tecw.mwchei/2;              
                            /// Shape Trd1 dx1=tecw.mwcinn/2 dx2=tecw.mwcout/2 dy=tecw.mwcdepth/2 dz=tecw.mwchei/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TMEA;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TMSE");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TMSE              
                            Create("TMSE");               
                      }           
                      // _medium.par("STRA") = 1.;           
                      END_OF_TMEA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TMEA     
          // ---------------------------------------------------------------------------------------------------     
          void TMSE::Block( AgCreate create )     
          {         
                ///@addtogroup TMSE_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=tecw.mwcnwir;              
                            shape.par("iaxis")=3;              
                            /// Shape Division ndiv=tecw.mwcnwir iaxis=3               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TMSE;              
                            _stacker -> Build(this);              
                      }           
                      if ( tpcg.mwcread==1 )           
                      {              
                      }           
                      else           
                      {              
                      }           
                      END_OF_TMSE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TMSE     
          // ---------------------------------------------------------------------------------------------------     
          void THOL::Block( AgCreate create )     
          {         
                ///@addtogroup THOL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tecw.slotw/2;              
                            shape.par("dy")=tecw.ppdepth/2;              
                            shape.par("dz")=tecw.slotrad;              
                            /// Shape Bbox dx=tecw.slotw/2 dy=tecw.ppdepth/2 dz=tecw.slotrad               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_THOL;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_THOL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block THOL     
          // ---------------------------------------------------------------------------------------------------     
          void THRA::Block( AgCreate create )     
          {         
                ///@addtogroup THRA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0.0;              
                            shape.par("rmax")=tecw.slotrad;              
                            shape.par("phi1")=0.0;              
                            shape.par("phi2")=180.0;              
                            shape.par("dz")=tecw.ppdepth/2;              
                            /// Shape Tubs rmin=0.0 rmax=tecw.slotrad phi1=0.0 phi2=180.0 dz=tecw.ppdepth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_THRA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_THRA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block THRA     
          // ---------------------------------------------------------------------------------------------------     
          void THLA::Block( AgCreate create )     
          {         
                ///@addtogroup THLA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=0.0;              
                            shape.par("rmax")=tecw.slotrad;              
                            shape.par("phi1")=180.0;              
                            shape.par("phi2")=360.0;              
                            shape.par("dz")=tecw.ppdepth/2;              
                            /// Shape Tubs rmin=0.0 rmax=tecw.slotrad phi1=180.0 phi2=360.0 dz=tecw.ppdepth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_THLA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_THLA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block THLA     
          // ---------------------------------------------------------------------------------------------------     
          void TIAG::Block( AgCreate create )     
          {         
                ///@addtogroup TIAG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Trd1");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx1")=0;              
                            shape.par("dx2")=0;              
                            shape.par("dy")=0;              
                            shape.par("dz")=0;              
                            /// Shape Trd1 dx1=0 dx2=0 dy=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TIAG;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TIAG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TIAG     
          // ---------------------------------------------------------------------------------------------------     
          void TOAE::Block( AgCreate create )     
          {         
                ///@addtogroup TOAE_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
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
                            if (_same_shape) goto END_OF_TOAE;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TOAE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TOAE     
          // ---------------------------------------------------------------------------------------------------     
          void TCEX::Block( AgCreate create )     
          {         
                ///@addtogroup TCEX_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
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
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tecw.cardw/2;              
                            shape.par("dy")=tecw.asdepth/2;              
                            shape.par("dz")=tecw.cardth/2;              
                            /// Shape Bbox dx=tecw.cardw/2 dy=tecw.asdepth/2 dz=tecw.cardth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TCEX;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TCEX:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TCEX     
          // ---------------------------------------------------------------------------------------------------     
          void TAEC::Block( AgCreate create )     
          {         
                ///@addtogroup TAEC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tecw.coolw/2;              
                            shape.par("dy")=tecw.asdepth/2;              
                            shape.par("dz")=tecw.coolth/2;              
                            /// Shape Bbox dx=tecw.coolw/2 dy=tecw.asdepth/2 dz=tecw.coolth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TAEC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TAEC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TAEC     
          // ---------------------------------------------------------------------------------------------------     
          void TPCW::Block( AgCreate create )     
          {         
                ///@addtogroup TPCW_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TPEA");              
                            attr.par("seen")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tpcg.wheelir;              
                            shape.par("rmax")=tpcg.wheelor;              
                            shape.par("dz")=tpcg.wheelthk/2;              
                            /// Shape Tube rmin=tpcg.wheelir rmax=tpcg.wheelor dz=tpcg.wheelthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TPCW;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TWSS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TWSS              
                            Create("TWSS");               
                      }           
                      END_OF_TPCW:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPCW     
          // ---------------------------------------------------------------------------------------------------     
          void TWSS::Block( AgCreate create )     
          {         
                ///@addtogroup TWSS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TWSS");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=12;              
                            shape.par("iaxis")=2;              
                            /// Shape Division ndiv=12 iaxis=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWSS;              
                            _stacker -> Build(this);              
                      }           
                      /// Loop on i_sec from 1 to 2 step=1           
                      for ( i_sec=1; (1>0)? (i_sec<=2):(i_sec>=2); i_sec+=1 )           
                      {              
                            /// USE tecw sec=i_sec ;              
                            tecw.Use("sec",(Float_t)i_sec );              
                            /// USE trov sec=i_sec ;              
                            trov.Use("sec",(Float_t)i_sec );              
                            _create = AgCreate("TWGI");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TWGI                 
                                  Create("TWGI");                  
                            }              
                            { AgPlacement place = AgPlacement("TWGI","TWSS");                 
                                  /// Add daughter volume TWGI to mother TWSS                 
                                  place.TranslateX(tecw.gaprad);                 
                                  /// Translate x = tecw.gaprad                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YZX" ); // ORT=YZX                 
                                  /// Axis substitution: XYZ --> YZX                 
                                  _stacker -> Position( AgBlock::Find("TWGI"), place );                 
                            } // end placement of TWGI              
                      }           
                      END_OF_TWSS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWSS     
          // ---------------------------------------------------------------------------------------------------     
          void TWGI::Block( AgCreate create )     
          {         
                ///@addtogroup TWGI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TWGI");              
                            attr.par("seen")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trd1");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx1")=tecw.gapwidi/2;              
                            shape.par("dx2")=tecw.gapwido/2;              
                            shape.par("dy")=tpcg.wheelthk/2;              
                            shape.par("dz")=tecw.gapheit/2;              
                            /// Shape Trd1 dx1=tecw.gapwidi/2 dx2=tecw.gapwido/2 dy=tpcg.wheelthk/2 dz=tecw.gapheit/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWGI;              
                            _stacker -> Build(this);              
                      }           
                      dx_dz=(tecw.gapwido/2-tecw.gapwidi/2)/tecw.gapheit;           
                      xlip=tecw.whlipwid*sqrt(1+dx_dz*dx_dz);           
                      xbottom =tecw.gapwidi/2+xlip-dx_dz*(tecw.whlipwid-tecw.gapshft);           
                      _create = AgCreate("TWGC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TWGC              
                            Create("TWGC");               
                      }           
                      { AgPlacement place = AgPlacement("TWGC","TWGI");              
                            /// Add daughter volume TWGC to mother TWGI              
                            place.TranslateY(tecw.whlipthk/2);              
                            /// Translate y = tecw.whlipthk/2              
                            place.TranslateZ(tecw.gapshft);              
                            /// Translate z = tecw.gapshft              
                            place.par("dy")=(tpcg.wheelthk-tecw.whlipthk)/2;              
                            place.par("dz")=tecw.gapheit/2+tecw.whlipwid-tecw.gapshft;              
                            place.par("dx1")=xbottom;              
                            place.par("dx2")=tecw.gapwido/2+xlip+dx_dz*tecw.whlipwid;              
                            _stacker -> Position( AgBlock::Find("TWGC"), place );              
                      } // end placement of TWGC           
                      _create = AgCreate("TWGB");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TWGB              
                            Create("TWGB");               
                      }           
                      { AgPlacement place = AgPlacement("TWGB","TWGI");              
                            /// Add daughter volume TWGB to mother TWGI              
                            place.TranslateX(0);              
                            /// Translate x = 0              
                            place.TranslateY(tecw.whlipthk/2);              
                            /// Translate y = tecw.whlipthk/2              
                            place.TranslateZ((tecw.gapheit/2+tecw.whlipwid/2));              
                            /// Translate z = (tecw.gapheit/2+tecw.whlipwid/2)              
                            place.AlphaY(90);              
                            /// Rotate: AlphaY = 90              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("TWGB"), place );              
                      } // end placement of TWGB           
                      if ( tecw.whblkin==1 )           
                      {              
                            { AgPlacement place = AgPlacement("TWGB","TWGI");                 
                                  /// Add daughter volume TWGB to mother TWGI                 
                                  place.TranslateX(0);                 
                                  /// Translate x = 0                 
                                  place.TranslateY(tecw.whlipthk/2);                 
                                  /// Translate y = tecw.whlipthk/2                 
                                  place.TranslateZ(-(tecw.gapheit/2+tecw.whlipwid/2));                 
                                  /// Translate z = -(tecw.gapheit/2+tecw.whlipwid/2)                 
                                  place.AlphaY(90);                 
                                  /// Rotate: AlphaY = 90                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("TWGB"), place );                 
                            } // end placement of TWGB              
                      }           
                      { AgPlacement place = AgPlacement("TWGB","TWGI");              
                            /// Add daughter volume TWGB to mother TWGI              
                            place.TranslateX(tecw.gapwidi/2+xlip/2+dx_dz*(tecw.whblkpos+tecw.gapheit/2));              
                            /// Translate x = tecw.gapwidi/2+xlip/2+dx_dz*(tecw.whblkpos+tecw.gapheit/2)              
                            place.TranslateY(tecw.whlipthk/2);              
                            /// Translate y = tecw.whlipthk/2              
                            place.TranslateZ(tecw.whblkpos);              
                            /// Translate z = tecw.whblkpos              
                            place.AlphaY(15);              
                            /// Rotate: AlphaY = 15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("TWGB"), place );              
                      } // end placement of TWGB           
                      { AgPlacement place = AgPlacement("TWGB","TWGI");              
                            /// Add daughter volume TWGB to mother TWGI              
                            place.TranslateX(tecw.gapwidi/2+xlip/2+dx_dz*(-tecw.whblkpos+tecw.gapheit/2));              
                            /// Translate x = tecw.gapwidi/2+xlip/2+dx_dz*(-tecw.whblkpos+tecw.gapheit/2)              
                            place.TranslateY(tecw.whlipthk/2);              
                            /// Translate y = tecw.whlipthk/2              
                            place.TranslateZ(-tecw.whblkpos);              
                            /// Translate z = -tecw.whblkpos              
                            place.AlphaY(15);              
                            /// Rotate: AlphaY = 15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("TWGB"), place );              
                      } // end placement of TWGB           
                      { AgPlacement place = AgPlacement("TWGB","TWGI");              
                            /// Add daughter volume TWGB to mother TWGI              
                            place.TranslateX(-tecw.gapwidi/2-xlip/2-dx_dz*(tecw.whblkpos+tecw.gapheit/2));              
                            /// Translate x = -tecw.gapwidi/2-xlip/2-dx_dz*(tecw.whblkpos+tecw.gapheit/2)              
                            place.TranslateY(tecw.whlipthk/2);              
                            /// Translate y = tecw.whlipthk/2              
                            place.TranslateZ(tecw.whblkpos);              
                            /// Translate z = tecw.whblkpos              
                            place.AlphaY(-15);              
                            /// Rotate: AlphaY = -15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("TWGB"), place );              
                      } // end placement of TWGB           
                      { AgPlacement place = AgPlacement("TWGB","TWGI");              
                            /// Add daughter volume TWGB to mother TWGI              
                            place.TranslateX(-tecw.gapwidi/2-xlip/2-dx_dz*(-tecw.whblkpos+tecw.gapheit/2));              
                            /// Translate x = -tecw.gapwidi/2-xlip/2-dx_dz*(-tecw.whblkpos+tecw.gapheit/2)              
                            place.TranslateY(tecw.whlipthk/2);              
                            /// Translate y = tecw.whlipthk/2              
                            place.TranslateZ(-tecw.whblkpos);              
                            /// Translate z = -tecw.whblkpos              
                            place.AlphaY(-15);              
                            /// Rotate: AlphaY = -15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("TWGB"), place );              
                      } // end placement of TWGB           
                      radoff = tecw.rcenter-tecw.gaprad-tecw.height/2+tecw.gapheit/2;           
                      /// Loop on i_nhp from 1 to 16 step=1           
                      for ( i_nhp=1; (1>0)? (i_nhp<=16):(i_nhp>=16); i_nhp+=1 )           
                      {              
                            if ( trov.nhp(i_nhp)>0 )              
                            {                 
                                  hpla = -tecw.gapheit/2+radoff+tecw.z(1)-tecw.dz(1)/2+trov.offcardinout ;//first pl;                 
                                  zvalue = hpla+4.0*(i_nhp-1);                 
                                  pipeoff=tecw.pipeht/2+tecw.coolth+tecw.cardth/2;                 
                                  xtemp=tecw.gapwidi/2;                 
                                  ztemp=zvalue+tecw.cardoff-pipeoff;                 
                                  _create = AgCreate("TPIP");                 
                                  {                    
                                        AgShape myshape; // undefined shape                    
                                        ///Create TPIP                    
                                        Create("TPIP");                     
                                  }                 
                                  { AgPlacement place = AgPlacement("TPIP","TWGI");                    
                                        /// Add daughter volume TPIP to mother TWGI                    
                                        place.TranslateY(-tpcg.wheelthk/2+tecw.pipethk/2);                    
                                        /// Translate y = -tpcg.wheelthk/2+tecw.pipethk/2                    
                                        place.TranslateZ(ztemp);                    
                                        /// Translate z = ztemp                    
                                        place.par("dy")=tecw.pipethk/2;                    
                                        place.par("dz")=tecw.pipeht/2;                    
                                        place.par("dx1")=xtemp+dx_dz*(ztemp+tecw.gapheit/2-tecw.pipeht/2);                    
                                        place.par("dx2")=xtemp+dx_dz*(ztemp+tecw.gapheit/2+tecw.pipeht/2);                    
                                        _stacker -> Position( AgBlock::Find("TPIP"), place );                    
                                  } // end placement of TPIP                 
                            }              
                      }           
                      _create = AgCreate("TMAN");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TMAN              
                            Create("TMAN");               
                      }           
                      { AgPlacement place = AgPlacement("TMAN","TWGI");              
                            /// Add daughter volume TMAN to mother TWGI              
                            place.TranslateX(tecw.gapwidi/2.+dx_dz*(tecw.gapheit/2)-(1+dx_dz*dx_dz)*tecw.maniwid/2);              
                            /// Translate x = tecw.gapwidi/2.+dx_dz*(tecw.gapheit/2)-(1+dx_dz*dx_dz)*tecw.maniwid/2              
                            place.TranslateY(-tpcg.wheelthk/2+tecw.pipethk+tecw.manithk/2);              
                            /// Translate y = -tpcg.wheelthk/2+tecw.pipethk+tecw.manithk/2              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            place.par("dx")=tecw.maniwid/2;              
                            place.par("dy")=tecw.manithk/2;              
                            place.par("dz")=(1.+dx_dz*dx_dz)*(tecw.gapheit/2-tecw.maniwid);              
                            place.AlphaY(15);              
                            /// Rotate: AlphaY = 15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("TMAN"), place );              
                      } // end placement of TMAN           
                      { AgPlacement place = AgPlacement("TMAN","TWGI");              
                            /// Add daughter volume TMAN to mother TWGI              
                            place.TranslateX(-tecw.gapwidi/2.-dx_dz*(tecw.gapheit/2)+(1+dx_dz*dx_dz)*tecw.maniwid/2);              
                            /// Translate x = -tecw.gapwidi/2.-dx_dz*(tecw.gapheit/2)+(1+dx_dz*dx_dz)*tecw.maniwid/2              
                            place.TranslateY(-tpcg.wheelthk/2+tecw.pipethk+tecw.manithk/2);              
                            /// Translate y = -tpcg.wheelthk/2+tecw.pipethk+tecw.manithk/2              
                            place.TranslateZ(0.0);              
                            /// Translate z = 0.0              
                            place.par("dx")=tecw.maniwid/2;              
                            place.par("dy")=tecw.manithk/2;              
                            place.par("dz")=(1.+dx_dz*dx_dz)*(tecw.gapheit/2-tecw.maniwid);              
                            place.AlphaY(-15);              
                            /// Rotate: AlphaY = -15              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            _stacker -> Position( AgBlock::Find("TMAN"), place );              
                      } // end placement of TMAN           
                      _create = AgCreate("TCRX");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TCRX              
                            Create("TCRX");               
                      }           
                      _create = AgCreate("TALC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TALC              
                            Create("TALC");               
                      }           
                      /// Loop on i_nhp from 1 to 16 step=1           
                      for ( i_nhp=1; (1>0)? (i_nhp<=16):(i_nhp>=16); i_nhp+=1 )           
                      {              
                            if ( trov.nhp(i_nhp)>0 )              
                            {                 
                                  hpla = -tecw.gapheit/2+radoff+tecw.z(1)-tecw.dz(1)/2+trov.offcardinout ;//first pl;                 
                                  zvalue = hpla+4.0*(i_nhp-1);                 
                                  /// Loop on j_nho from 1 to trov.nhp(i_nhp) step=1                 
                                  for ( j_nho=1; (1>0)? (j_nho<=trov.nhp(i_nhp)):(j_nho>=trov.nhp(i_nhp)); j_nho+=1 )                 
                                  {                    
                                        { AgPlacement place = AgPlacement("TCRX","TWGI");                       
                                              /// Add daughter volume TCRX to mother TWGI                       
                                              place.TranslateX(trov.hx(j_nho,i_nhp));                       
                                              /// Translate x = trov.hx(j_nho,i_nhp)                       
                                              place.TranslateZ(zvalue+tecw.cardoff);                       
                                              /// Translate z = zvalue+tecw.cardoff                       
                                              _stacker -> Position( AgBlock::Find("TCRX"), place );                       
                                        } // end placement of TCRX                    
                                        { AgPlacement place = AgPlacement("TALC","TWGI");                       
                                              /// Add daughter volume TALC to mother TWGI                       
                                              place.TranslateX(trov.hx(j_nho,i_nhp));                       
                                              /// Translate x = trov.hx(j_nho,i_nhp)                       
                                              place.TranslateZ(zvalue+tecw.cooloff);                       
                                              /// Translate z = zvalue+tecw.cooloff                       
                                              _stacker -> Position( AgBlock::Find("TALC"), place );                       
                                        } // end placement of TALC                    
                                  }                 
                            }              
                      }           
                      END_OF_TWGI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWGI     
          // ---------------------------------------------------------------------------------------------------     
          void TWGC::Block( AgCreate create )     
          {         
                ///@addtogroup TWGC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TWGC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=7;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trd1");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx1")=0;              
                            shape.par("dx2")=0;              
                            shape.par("dy")=0;              
                            shape.par("dz")=0;              
                            /// Shape Trd1 dx1=0 dx2=0 dy=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWGC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TWGC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWGC     
          // ---------------------------------------------------------------------------------------------------     
          void TWGB::Block( AgCreate create )     
          {         
                ///@addtogroup TWGB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TWGB");              
                            attr.par("seen")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tecw.whlipwid/2;              
                            shape.par("dy")=(tpcg.wheelthk-tecw.whlipthk)/2;              
                            shape.par("dz")=tecw.whblklen/2;              
                            /// Shape Bbox dx=tecw.whlipwid/2 dy=(tpcg.wheelthk-tecw.whlipthk)/2 dz=tecw.whblklen/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWGB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TWGB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWGB     
          // ---------------------------------------------------------------------------------------------------     
          void TMAN::Block( AgCreate create )     
          {         
                ///@addtogroup TMAN_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TWGB");              
                            attr.par("seen")=1;              
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
                            if (_same_shape) goto END_OF_TMAN;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TMAN:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TMAN     
          // ---------------------------------------------------------------------------------------------------     
          void TPIP::Block( AgCreate create )     
          {         
                ///@addtogroup TPIP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TPIP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Trd1");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx1")=0;              
                            shape.par("dx2")=0;              
                            shape.par("dy")=0;              
                            shape.par("dz")=0;              
                            /// Shape Trd1 dx1=0 dx2=0 dy=0 dz=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TPIP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TPIP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPIP     
          // ---------------------------------------------------------------------------------------------------     
          void TCRX::Block( AgCreate create )     
          {         
                ///@addtogroup TCRX_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TCRX");              
                            attr.par("seen")=1;              
                            attr.par("colo")=4;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tecw.cardw/2;              
                            shape.par("dy")=tpcg.wheelthk/2;              
                            shape.par("dz")=tecw.cardth/2;              
                            /// Shape Bbox dx=tecw.cardw/2 dy=tpcg.wheelthk/2 dz=tecw.cardth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TCRX;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TCRX:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TCRX     
          // ---------------------------------------------------------------------------------------------------     
          void TALC::Block( AgCreate create )     
          {         
                ///@addtogroup TALC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Aluminium            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TALC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=6;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tecw.coolw/2;              
                            shape.par("dy")=tpcg.wheelthk/2;              
                            shape.par("dz")=tecw.coolth/2;              
                            /// Shape Bbox dx=tecw.coolw/2 dy=tpcg.wheelthk/2 dz=tecw.coolth/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TALC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TALC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TALC     
          // ---------------------------------------------------------------------------------------------------     
          void TRDV::Block( AgCreate create )     
          {         
                ///@addtogroup TRDV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Air            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Air");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TRDV");              
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tpcg.wheelir;              
                            shape.par("rmax")=tpcg.wheelor;              
                            shape.par("dz")=trdo.rdovthk/2;              
                            /// Shape Tube rmin=tpcg.wheelir rmax=tpcg.wheelor dz=trdo.rdovthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TRDV;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TRDS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TRDS              
                            Create("TRDS");               
                      }           
                      END_OF_TRDV:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TRDV     
          // ---------------------------------------------------------------------------------------------------     
          void TRDS::Block( AgCreate create )     
          {         
                ///@addtogroup TRDS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TRDS");              
                            attr.par("seen")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Division");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("ndiv")=12;              
                            shape.par("iaxis")=2;              
                            /// Shape Division ndiv=12 iaxis=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TRDS;              
                            _stacker -> Build(this);              
                      }           
                      /// USE trdo _index=1;           
                      trdo.Use();           
                      /// Loop on kk from 1 to trdo.nrdobrd step=1           
                      for ( kk=1; (1>0)? (kk<=trdo.nrdobrd):(kk>=trdo.nrdobrd); kk+=1 )           
                      {              
                            _create = AgCreate("TRDC");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TRDC                 
                                  Create("TRDC");                  
                            }              
                            { AgPlacement place = AgPlacement("TRDC","TRDS");                 
                                  /// Add daughter volume TRDC to mother TRDS                 
                                  place.TranslateX(trdo.rdoht(kk));                 
                                  /// Translate x = trdo.rdoht(kk)                 
                                  place.par("dx")=(trdo.rdoht(kk)*tecw.tan15)-tecw.clearance;                 
                                  place.par("dy")=trdo.rdolen/2;                 
                                  place.par("dz")=trdo.rdothk/2;                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YZX" ); // ORT=YZX                 
                                  /// Axis substitution: XYZ --> YZX                 
                                  _stacker -> Position( AgBlock::Find("TRDC"), place );                 
                            } // end placement of TRDC              
                      }           
                      END_OF_TRDS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TRDS     
          // ---------------------------------------------------------------------------------------------------     
          void TRDC::Block( AgCreate create )     
          {         
                ///@addtogroup TRDC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Component Si	a=28.08	z=14	w=0.6*1*28./60.           
                      /// Component O	a=16	z=8	w=0.6*2*16./60.           
                      /// Component C	a=12	z=6	w=0.4*8*12./174.           
                      /// Component H	a=1	z=1	w=0.4*14*1./174.           
                      /// Component O	a=16	z=8	w=0.4*4*16./174.           
                      /// Mixture G10 dens=1.7           
                      {  AgMaterial &mix = AgMaterial::Get("G10");              
                            mix.Component("Si",28.08,14,0.6*1*28./60.);              
                            mix.Component("O",16,8,0.6*2*16./60.);              
                            mix.Component("C",12,6,0.4*8*12./174.);              
                            mix.Component("H",1,1,0.4*14*1./174.);              
                            mix.Component("O",16,8,0.4*4*16./174.);              
                            mix.par("dens")=1.7;              
                            mix.lock();              
                            _material = mix;              
                            _material.lock();              
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
                            if (_same_shape) goto END_OF_TRDC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TRDC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TRDC     
    // ----------------------------------------------------------------------- geoctr
       void TpceGeo1::ConstructGeometry( const Char_t *dummy )     
       {        
             ///@addtogroup TpceGeo1_revision        
             ///@{           
                   /// Author: David Underwood and Maxim Potekhin           
             ///@}        
             ///@addtogroup TpceGeo1_revision        
             ///@{           
                   /// Created:   March 7, 2005            
             ///@}        
             AddBlock("TPCE");        
             AddBlock("TOFC");        
             AddBlock("TOFS");        
             AddBlock("TOST");        
             AddBlock("TOKA");        
             AddBlock("TONX");        
             AddBlock("TOAD");        
             AddBlock("TOHA");        
             AddBlock("TPGV");        
             AddBlock("TPSS");        
             AddBlock("TIFC");        
             AddBlock("TIAL");        
             AddBlock("TIKA");        
             AddBlock("TINX");        
             AddBlock("TPCW");        
             AddBlock("TWSS");        
             AddBlock("TWGI");        
             AddBlock("TPCM");        
             AddBlock("TPEA");        
             AddBlock("TESS");        
             AddBlock("TSEC");        
             AddBlock("TMWC");        
             AddBlock("TMEA");        
             AddBlock("TMSE");        
             AddBlock("TIAG");        
             AddBlock("TOAE");        
             AddBlock("TPAD");        
             AddBlock("THOL");        
             AddBlock("THRA");        
             AddBlock("THLA");        
             AddBlock("TALC");        
             AddBlock("TAEC");        
             AddBlock("TCEX");        
             AddBlock("TCRX");        
             AddBlock("TWGC");        
             AddBlock("TWGB");        
             AddBlock("TPIP");        
             AddBlock("TMAN");        
             AddBlock("TRDV");        
             AddBlock("TRDS");        
             AddBlock("TRDC");        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tpcg_doc        
             ///@{           
                   ++tpcg._index;           
                   tpcg . version = 2; //  current version            
                   /// tpcg . version = 2; //  current version            
                   tpcg . rmin = 46.107; //  TPC inner radius             
                   /// tpcg . rmin = 46.107; //  TPC inner radius             
                   tpcg . rmax = 207.750; //  TPC outer radius            
                   /// tpcg . rmax = 207.750; //  TPC outer radius            
                   tpcg . length = 519.37; //  TPC full length            
                   /// tpcg . length = 519.37; //  TPC full length            
                   tpcg . wheelir = 49.60; //  support wheel inner radius            
                   /// tpcg . wheelir = 49.60; //  support wheel inner radius            
                   tpcg . wheelor = 206.75; //  support wheel outer radius            
                   /// tpcg . wheelor = 206.75; //  support wheel outer radius            
                   tpcg . wheelthk = 11.43; //  support wheel length            
                   /// tpcg . wheelthk = 11.43; //  support wheel length            
                   tpcg . sengasor = 200; //  TPC sensitive gas outer radius            
                   /// tpcg . sengasor = 200; //  TPC sensitive gas outer radius            
                   tpcg . tpeathk = 9.7; //  endcap MWC + sector thickness            
                   /// tpcg . tpeathk = 9.7; //  endcap MWC + sector thickness            
                   tpcg . membthk = .00762; //  Central membrane thickness            
                   /// tpcg . membthk = .00762; //  Central membrane thickness            
                   tpcg . tocsdr = .013; //  outer copper thickness            
                   /// tpcg . tocsdr = .013; //  outer copper thickness            
                   tpcg . tokadr = .015; //  outer kapton thickness            
                   /// tpcg . tokadr = .015; //  outer kapton thickness            
                   tpcg . tonxdr = 1.00; //  outer nomex thickness            
                   /// tpcg . tonxdr = 1.00; //  outer nomex thickness            
                   tpcg . toaddr = 0.02; //  outer adhesive thickness            
                   /// tpcg . toaddr = 0.02; //  outer adhesive thickness            
                   tpcg . toigdr = 5.70; //  outer isolating gas thickness            
                   /// tpcg . toigdr = 5.70; //  outer isolating gas thickness            
                   tpcg . toaldr = 0.40; //  outer aluminum thickness            
                   /// tpcg . toaldr = 0.40; //  outer aluminum thickness            
                   tpcg . tohadr = 0.60; //  outer HoneyUcomb Al thickness              
                   /// tpcg . tohadr = 0.60; //  outer HoneyUcomb Al thickness              
                   tpcg . tiaddr = 0.080; //  inner adhesive layer thickness            
                   /// tpcg . tiaddr = 0.080; //  inner adhesive layer thickness            
                   tpcg . tinxdr = 1.270; //  inner nomex structure thickness            
                   /// tpcg . tinxdr = 1.270; //  inner nomex structure thickness            
                   tpcg . tikadr = 0.015; //  inner Kapton layer thickness            
                   /// tpcg . tikadr = 0.015; //  inner Kapton layer thickness            
                   tpcg . tialdr = 0.004; //  inner aluminum layer thickness            
                   /// tpcg . tialdr = 0.004; //  inner aluminum layer thickness            
                   tpcg . mwcread = 2; //  MWC readout flag            
                   /// tpcg . mwcread = 2; //  MWC readout flag            
                   tpcg . gascorr = 1; //  gas density correction version            
                   /// tpcg . gascorr = 1; //  gas density correction version            
                   //           
                   tpcg.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup trdo_doc        
             ///@{           
                   ++trdo._index;           
                   trdo . rdovthk = 30.; //  length of RDO vloume            
                   /// trdo . rdovthk = 30.; //  length of RDO vloume            
                   trdo . rdothk = .25; //  thickness of rdo card            
                   /// trdo . rdothk = .25; //  thickness of rdo card            
                   trdo . rdolen = 27; //  card length along beam direction            
                   /// trdo . rdolen = 27; //  card length along beam direction            
                   trdo . nrdobrd = 9; //  number of RDO boards            
                   /// trdo . nrdobrd = 9; //  number of RDO boards            
                   trdo . rdoht.at(0) = 60.0; //  radial pos of rdo boards            
                   ///trdo . rdoht.at(0) = 60.0; //  radial pos of rdo boards            
                   trdo . rdoht.at(1) = 74.0; //  radial pos of rdo boards            
                   ///trdo . rdoht.at(1) = 74.0; //  radial pos of rdo boards            
                   trdo . rdoht.at(2) = 84.0; //  radial pos of rdo boards            
                   ///trdo . rdoht.at(2) = 84.0; //  radial pos of rdo boards            
                   trdo . rdoht.at(3) = 101.0; //  radial pos of rdo boards            
                   ///trdo . rdoht.at(3) = 101.0; //  radial pos of rdo boards            
                   trdo . rdoht.at(4) = 106.0; //  radial pos of rdo boards            
                   ///trdo . rdoht.at(4) = 106.0; //  radial pos of rdo boards            
                   trdo . rdoht.at(5) = 126.0; //  radial pos of rdo boards            
                   ///trdo . rdoht.at(5) = 126.0; //  radial pos of rdo boards            
                   trdo . rdoht.at(6) = 146.0; //  radial pos of rdo boards            
                   ///trdo . rdoht.at(6) = 146.0; //  radial pos of rdo boards            
                   trdo . rdoht.at(7) = 166.0; //  radial pos of rdo boards            
                   ///trdo . rdoht.at(7) = 166.0; //  radial pos of rdo boards            
                   trdo . rdoht.at(8) = 186.0; //  radial pos of rdo boards            
                   ///trdo . rdoht.at(8) = 186.0; //  radial pos of rdo boards            
                   //           
                   trdo.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tprs_doc        
             ///@{           
                   ++tprs._index;           
                   tprs . sec = 1; //  sector number: 1 for inner, 2 for outer            
                   /// tprs . sec = 1; //  sector number: 1 for inner, 2 for outer            
                   tprs . nrow = 13; //  number of padrows in the sector            
                   /// tprs . nrow = 13; //  number of padrows in the sector            
                   tprs . pitch = 0.335; //  tpc padrow pitch width            
                   /// tprs . pitch = 0.335; //  tpc padrow pitch width            
                   tprs . width = 1.15; //  tpc padrow thickness            
                   /// tprs . width = 1.15; //  tpc padrow thickness            
                   tprs . super = 3; //  number of padraws in a superpadrow            
                   /// tprs . super = 3; //  number of padraws in a superpadrow            
                   tprs . npads.at(0) = 88; //  number of pads in row            
                   ///tprs . npads.at(0) = 88; //  number of pads in row            
                   tprs . npads.at(1) = 96; //  number of pads in row            
                   ///tprs . npads.at(1) = 96; //  number of pads in row            
                   tprs . npads.at(2) = 104; //  number of pads in row            
                   ///tprs . npads.at(2) = 104; //  number of pads in row            
                   tprs . npads.at(3) = 112; //  number of pads in row            
                   ///tprs . npads.at(3) = 112; //  number of pads in row            
                   tprs . npads.at(4) = 118; //  number of pads in row            
                   ///tprs . npads.at(4) = 118; //  number of pads in row            
                   tprs . npads.at(5) = 126; //  number of pads in row            
                   ///tprs . npads.at(5) = 126; //  number of pads in row            
                   tprs . npads.at(6) = 134; //  number of pads in row            
                   ///tprs . npads.at(6) = 134; //  number of pads in row            
                   tprs . npads.at(7) = 142; //  number of pads in row            
                   ///tprs . npads.at(7) = 142; //  number of pads in row            
                   tprs . npads.at(8) = 150; //  number of pads in row            
                   ///tprs . npads.at(8) = 150; //  number of pads in row            
                   tprs . npads.at(9) = 158; //  number of pads in row            
                   ///tprs . npads.at(9) = 158; //  number of pads in row            
                   tprs . npads.at(10) = 166; //  number of pads in row            
                   ///tprs . npads.at(10) = 166; //  number of pads in row            
                   tprs . npads.at(11) = 174; //  number of pads in row            
                   ///tprs . npads.at(11) = 174; //  number of pads in row            
                   tprs . npads.at(12) = 182 ; //  number of pads in row            
                   ///tprs . npads.at(12) = 182 ; //  number of pads in row            
                   tprs . rpads.at(0) = 60.0; //  tpc padrow radii            
                   ///tprs . rpads.at(0) = 60.0; //  tpc padrow radii            
                   tprs . rpads.at(1) = 64.8; //  tpc padrow radii            
                   ///tprs . rpads.at(1) = 64.8; //  tpc padrow radii            
                   tprs . rpads.at(2) = 69.6; //  tpc padrow radii            
                   ///tprs . rpads.at(2) = 69.6; //  tpc padrow radii            
                   tprs . rpads.at(3) = 74.4; //  tpc padrow radii            
                   ///tprs . rpads.at(3) = 74.4; //  tpc padrow radii            
                   tprs . rpads.at(4) = 79.2; //  tpc padrow radii            
                   ///tprs . rpads.at(4) = 79.2; //  tpc padrow radii            
                   tprs . rpads.at(5) = 84.0; //  tpc padrow radii            
                   ///tprs . rpads.at(5) = 84.0; //  tpc padrow radii            
                   tprs . rpads.at(6) = 88.8; //  tpc padrow radii            
                   ///tprs . rpads.at(6) = 88.8; //  tpc padrow radii            
                   tprs . rpads.at(7) = 93.6; //  tpc padrow radii            
                   ///tprs . rpads.at(7) = 93.6; //  tpc padrow radii            
                   tprs . rpads.at(8) = 98.8; //  tpc padrow radii            
                   ///tprs . rpads.at(8) = 98.8; //  tpc padrow radii            
                   tprs . rpads.at(9) = 104.0; //  tpc padrow radii            
                   ///tprs . rpads.at(9) = 104.0; //  tpc padrow radii            
                   tprs . rpads.at(10) = 109.2; //  tpc padrow radii            
                   ///tprs . rpads.at(10) = 109.2; //  tpc padrow radii            
                   tprs . rpads.at(11) = 114.4; //  tpc padrow radii            
                   ///tprs . rpads.at(11) = 114.4; //  tpc padrow radii            
                   tprs . rpads.at(12) = 119.6 ; //  tpc padrow radii            
                   ///tprs . rpads.at(12) = 119.6 ; //  tpc padrow radii            
                   //           
                   tprs.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tprs_doc        
             ///@{           
                   ++tprs._index;           
                   tprs . sec = 2; //  sector number: 1 for inner, 2 for outer            
                   /// tprs . sec = 2; //  sector number: 1 for inner, 2 for outer            
                   tprs . nrow = 32; //  number of padrows in outer sector            
                   /// tprs . nrow = 32; //  number of padrows in outer sector            
                   tprs . pitch = 0.67; //  outer tpc padrow pitch width            
                   /// tprs . pitch = 0.67; //  outer tpc padrow pitch width            
                   tprs . width = 1.95; //  outer tpc padrow thickness            
                   /// tprs . width = 1.95; //  outer tpc padrow thickness            
                   tprs . super = 1; //  number of padrows in a superpadrow            
                   /// tprs . super = 1; //  number of padrows in a superpadrow            
                   tprs . npads.at(0) = 98; //  number of pads in row            
                   ///tprs . npads.at(0) = 98; //  number of pads in row            
                   tprs . npads.at(1) = 100; //  number of pads in row            
                   ///tprs . npads.at(1) = 100; //  number of pads in row            
                   tprs . npads.at(2) = 102; //  number of pads in row            
                   ///tprs . npads.at(2) = 102; //  number of pads in row            
                   tprs . npads.at(3) = 104; //  number of pads in row            
                   ///tprs . npads.at(3) = 104; //  number of pads in row            
                   tprs . npads.at(4) = 106; //  number of pads in row            
                   ///tprs . npads.at(4) = 106; //  number of pads in row            
                   tprs . npads.at(5) = 106; //  number of pads in row            
                   ///tprs . npads.at(5) = 106; //  number of pads in row            
                   tprs . npads.at(6) = 108; //  number of pads in row            
                   ///tprs . npads.at(6) = 108; //  number of pads in row            
                   tprs . npads.at(7) = 110; //  number of pads in row            
                   ///tprs . npads.at(7) = 110; //  number of pads in row            
                   tprs . npads.at(8) = 112; //  number of pads in row            
                   ///tprs . npads.at(8) = 112; //  number of pads in row            
                   tprs . npads.at(9) = 112; //  number of pads in row            
                   ///tprs . npads.at(9) = 112; //  number of pads in row            
                   tprs . npads.at(10) = 114; //  number of pads in row            
                   ///tprs . npads.at(10) = 114; //  number of pads in row            
                   tprs . npads.at(11) = 116; //  number of pads in row            
                   ///tprs . npads.at(11) = 116; //  number of pads in row            
                   tprs . npads.at(12) = 118; //  number of pads in row            
                   ///tprs . npads.at(12) = 118; //  number of pads in row            
                   tprs . npads.at(13) = 120; //  number of pads in row            
                   ///tprs . npads.at(13) = 120; //  number of pads in row            
                   tprs . npads.at(14) = 122; //  number of pads in row            
                   ///tprs . npads.at(14) = 122; //  number of pads in row            
                   tprs . npads.at(15) = 122; //  number of pads in row            
                   ///tprs . npads.at(15) = 122; //  number of pads in row            
                   tprs . npads.at(16) = 124; //  number of pads in row            
                   ///tprs . npads.at(16) = 124; //  number of pads in row            
                   tprs . npads.at(17) = 126; //  number of pads in row            
                   ///tprs . npads.at(17) = 126; //  number of pads in row            
                   tprs . npads.at(18) = 128; //  number of pads in row            
                   ///tprs . npads.at(18) = 128; //  number of pads in row            
                   tprs . npads.at(19) = 128; //  number of pads in row            
                   ///tprs . npads.at(19) = 128; //  number of pads in row            
                   tprs . npads.at(20) = 130; //  number of pads in row            
                   ///tprs . npads.at(20) = 130; //  number of pads in row            
                   tprs . npads.at(21) = 132; //  number of pads in row            
                   ///tprs . npads.at(21) = 132; //  number of pads in row            
                   tprs . npads.at(22) = 134; //  number of pads in row            
                   ///tprs . npads.at(22) = 134; //  number of pads in row            
                   tprs . npads.at(23) = 136; //  number of pads in row            
                   ///tprs . npads.at(23) = 136; //  number of pads in row            
                   tprs . npads.at(24) = 138; //  number of pads in row            
                   ///tprs . npads.at(24) = 138; //  number of pads in row            
                   tprs . npads.at(25) = 138; //  number of pads in row            
                   ///tprs . npads.at(25) = 138; //  number of pads in row            
                   tprs . npads.at(26) = 140; //  number of pads in row            
                   ///tprs . npads.at(26) = 140; //  number of pads in row            
                   tprs . npads.at(27) = 142; //  number of pads in row            
                   ///tprs . npads.at(27) = 142; //  number of pads in row            
                   tprs . npads.at(28) = 144; //  number of pads in row            
                   ///tprs . npads.at(28) = 144; //  number of pads in row            
                   tprs . npads.at(29) = 144; //  number of pads in row            
                   ///tprs . npads.at(29) = 144; //  number of pads in row            
                   tprs . npads.at(30) = 144; //  number of pads in row            
                   ///tprs . npads.at(30) = 144; //  number of pads in row            
                   tprs . npads.at(31) = 144 ; //  number of pads in row            
                   ///tprs . npads.at(31) = 144 ; //  number of pads in row            
                   tprs . rpads.at(0) = 127.195; //  tpc padrow radii            
                   ///tprs . rpads.at(0) = 127.195; //  tpc padrow radii            
                   tprs . rpads.at(1) = 129.195; //  tpc padrow radii            
                   ///tprs . rpads.at(1) = 129.195; //  tpc padrow radii            
                   tprs . rpads.at(2) = 131.195; //  tpc padrow radii            
                   ///tprs . rpads.at(2) = 131.195; //  tpc padrow radii            
                   tprs . rpads.at(3) = 133.195; //  tpc padrow radii            
                   ///tprs . rpads.at(3) = 133.195; //  tpc padrow radii            
                   tprs . rpads.at(4) = 135.195; //  tpc padrow radii            
                   ///tprs . rpads.at(4) = 135.195; //  tpc padrow radii            
                   tprs . rpads.at(5) = 137.195; //  tpc padrow radii            
                   ///tprs . rpads.at(5) = 137.195; //  tpc padrow radii            
                   tprs . rpads.at(6) = 139.195; //  tpc padrow radii            
                   ///tprs . rpads.at(6) = 139.195; //  tpc padrow radii            
                   tprs . rpads.at(7) = 141.195; //  tpc padrow radii            
                   ///tprs . rpads.at(7) = 141.195; //  tpc padrow radii            
                   tprs . rpads.at(8) = 143.195; //  tpc padrow radii            
                   ///tprs . rpads.at(8) = 143.195; //  tpc padrow radii            
                   tprs . rpads.at(9) = 145.195; //  tpc padrow radii            
                   ///tprs . rpads.at(9) = 145.195; //  tpc padrow radii            
                   tprs . rpads.at(10) = 147.195; //  tpc padrow radii            
                   ///tprs . rpads.at(10) = 147.195; //  tpc padrow radii            
                   tprs . rpads.at(11) = 149.195; //  tpc padrow radii            
                   ///tprs . rpads.at(11) = 149.195; //  tpc padrow radii            
                   tprs . rpads.at(12) = 151.195; //  tpc padrow radii            
                   ///tprs . rpads.at(12) = 151.195; //  tpc padrow radii            
                   tprs . rpads.at(13) = 153.195; //  tpc padrow radii            
                   ///tprs . rpads.at(13) = 153.195; //  tpc padrow radii            
                   tprs . rpads.at(14) = 155.195; //  tpc padrow radii            
                   ///tprs . rpads.at(14) = 155.195; //  tpc padrow radii            
                   tprs . rpads.at(15) = 157.195; //  tpc padrow radii            
                   ///tprs . rpads.at(15) = 157.195; //  tpc padrow radii            
                   tprs . rpads.at(16) = 159.195; //  tpc padrow radii            
                   ///tprs . rpads.at(16) = 159.195; //  tpc padrow radii            
                   tprs . rpads.at(17) = 161.195; //  tpc padrow radii            
                   ///tprs . rpads.at(17) = 161.195; //  tpc padrow radii            
                   tprs . rpads.at(18) = 163.195; //  tpc padrow radii            
                   ///tprs . rpads.at(18) = 163.195; //  tpc padrow radii            
                   tprs . rpads.at(19) = 165.195; //  tpc padrow radii            
                   ///tprs . rpads.at(19) = 165.195; //  tpc padrow radii            
                   tprs . rpads.at(20) = 167.195; //  tpc padrow radii            
                   ///tprs . rpads.at(20) = 167.195; //  tpc padrow radii            
                   tprs . rpads.at(21) = 169.195; //  tpc padrow radii            
                   ///tprs . rpads.at(21) = 169.195; //  tpc padrow radii            
                   tprs . rpads.at(22) = 171.195; //  tpc padrow radii            
                   ///tprs . rpads.at(22) = 171.195; //  tpc padrow radii            
                   tprs . rpads.at(23) = 173.195; //  tpc padrow radii            
                   ///tprs . rpads.at(23) = 173.195; //  tpc padrow radii            
                   tprs . rpads.at(24) = 175.195; //  tpc padrow radii            
                   ///tprs . rpads.at(24) = 175.195; //  tpc padrow radii            
                   tprs . rpads.at(25) = 177.195; //  tpc padrow radii            
                   ///tprs . rpads.at(25) = 177.195; //  tpc padrow radii            
                   tprs . rpads.at(26) = 179.195; //  tpc padrow radii            
                   ///tprs . rpads.at(26) = 179.195; //  tpc padrow radii            
                   tprs . rpads.at(27) = 181.195; //  tpc padrow radii            
                   ///tprs . rpads.at(27) = 181.195; //  tpc padrow radii            
                   tprs . rpads.at(28) = 183.195; //  tpc padrow radii            
                   ///tprs . rpads.at(28) = 183.195; //  tpc padrow radii            
                   tprs . rpads.at(29) = 185.195; //  tpc padrow radii            
                   ///tprs . rpads.at(29) = 185.195; //  tpc padrow radii            
                   tprs . rpads.at(30) = 187.195; //  tpc padrow radii            
                   ///tprs . rpads.at(30) = 187.195; //  tpc padrow radii            
                   tprs . rpads.at(31) = 189.195 ; //  tpc padrow radii            
                   ///tprs . rpads.at(31) = 189.195 ; //  tpc padrow radii            
                   //           
                   tprs.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tecw_doc        
             ///@{           
                   ++tecw._index;           
                   tecw . sec = 1; //  sector number: 1 for inner, 2 for outer            
                   /// tecw . sec = 1; //  sector number: 1 for inner, 2 for outer            
                   tecw . gapwidi = 2.* 10.91; //  air in support wheel - inner width            
                   /// tecw . gapwidi = 2.* 10.91; //  air in support wheel - inner width            
                   tecw . gapwido = 2.* 27.56; //  air in support wheel - outer width            
                   /// tecw . gapwido = 2.* 27.56; //  air in support wheel - outer width            
                   tecw . gapheit = 62.15; //  air in support wheel - height (dr)            
                   /// tecw . gapheit = 62.15; //  air in support wheel - height (dr)            
                   tecw . gaprad = 87.0; //  air in support wheel - center radius            
                   /// tecw . gaprad = 87.0; //  air in support wheel - center radius            
                   tecw . gapshft = 1.4; //  offset air gap to make lip            
                   /// tecw . gapshft = 1.4; //  offset air gap to make lip            
                   tecw . inwidth = 2.* 13.75; //  sector width at inner radius             
                   /// tecw . inwidth = 2.* 13.75; //  sector width at inner radius             
                   tecw . ouwidth = 2.* 32.38; //  sector width at outer radius            
                   /// tecw . ouwidth = 2.* 32.38; //  sector width at outer radius            
                   tecw . height = 69.52; //  sector radial height            
                   /// tecw . height = 69.52; //  sector radial height            
                   tecw . ppdepth = 1.35+0.32; //  padplane thickness (both Al and PCB)            
                   /// tecw . ppdepth = 1.35+0.32; //  padplane thickness (both Al and PCB)            
                   tecw . asdepth = 6.99; //  depth of openings in aluminum structure            
                   /// tecw . asdepth = 6.99; //  depth of openings in aluminum structure            
                   tecw . ggdepth = 1.0; //  MWC gap from gated grid to pad plane            
                   /// tecw . ggdepth = 1.0; //  MWC gap from gated grid to pad plane            
                   tecw . mwcdepth = 1.0; //  sensitive MWC gas gap full thickness            
                   /// tecw . mwcdepth = 1.0; //  sensitive MWC gas gap full thickness            
                   tecw . boundary = 3.74; //  al frame - boundary width            
                   /// tecw . boundary = 3.74; //  al frame - boundary width            
                   tecw . rcenter = 86.669; //  sector center radius (set by precision holes)            
                   /// tecw . rcenter = 86.669; //  sector center radius (set by precision holes)            
                   tecw . mwcinn = 2*12.804; //  MWC sensitive region inner size            
                   /// tecw . mwcinn = 2*12.804; //  MWC sensitive region inner size            
                   tecw . mwcout = 2*29.953; //  MWC sensitive region outer size            
                   /// tecw . mwcout = 2*29.953; //  MWC sensitive region outer size            
                   tecw . mwchei = 64; //  MWC sensitive region height (radial)            
                   /// tecw . mwchei = 64; //  MWC sensitive region height (radial)            
                   tecw . mwccent = -1.669; //  sensitive region center position            
                   /// tecw . mwccent = -1.669; //  sensitive region center position            
                   tecw . mwcnwir = 160; //  number of MWC sensitive wires            
                   /// tecw . mwcnwir = 160; //  number of MWC sensitive wires            
                   tecw . n = 5; //  number of air gaps in Al            
                   /// tecw . n = 5; //  number of air gaps in Al            
                   tecw . nex = 0; //  number of extra aluminum support pieces            
                   /// tecw . nex = 0; //  number of extra aluminum support pieces            
                   tecw . z.at(0) = 6.67; //  positions of air gaps            
                   ///tecw . z.at(0) = 6.67; //  positions of air gaps            
                   tecw . z.at(1) = 18.22; //  positions of air gaps            
                   ///tecw . z.at(1) = 18.22; //  positions of air gaps            
                   tecw . z.at(2) = 34.22; //  positions of air gaps            
                   ///tecw . z.at(2) = 34.22; //  positions of air gaps            
                   tecw . z.at(3) = 50.22; //  positions of air gaps            
                   ///tecw . z.at(3) = 50.22; //  positions of air gaps            
                   tecw . z.at(4) = 62.65 ; //  positions of air gaps            
                   ///tecw . z.at(4) = 62.65 ; //  positions of air gaps            
                   tecw . dz.at(0) = 6.13; //  size of air gaps            
                   ///tecw . dz.at(0) = 6.13; //  size of air gaps            
                   tecw . dz.at(1) = 15.05; //  size of air gaps            
                   ///tecw . dz.at(1) = 15.05; //  size of air gaps            
                   tecw . dz.at(2) = 15.05; //  size of air gaps            
                   ///tecw . dz.at(2) = 15.05; //  size of air gaps            
                   tecw . dz.at(3) = 15.05; //  size of air gaps            
                   ///tecw . dz.at(3) = 15.05; //  size of air gaps            
                   tecw . dz.at(4) = 7.09 ; //  size of air gaps            
                   ///tecw . dz.at(4) = 7.09 ; //  size of air gaps            
                   tecw . xex.at(0) = 0; //  x positions of extra aluminum            
                   ///tecw . xex.at(0) = 0; //  x positions of extra aluminum            
                   tecw . xex.at(1) = 0; //  x positions of extra aluminum            
                   ///tecw . xex.at(1) = 0; //  x positions of extra aluminum            
                   tecw . xex.at(2) = 0; //  x positions of extra aluminum            
                   ///tecw . xex.at(2) = 0; //  x positions of extra aluminum            
                   tecw . xex.at(3) = 0; //  x positions of extra aluminum            
                   ///tecw . xex.at(3) = 0; //  x positions of extra aluminum            
                   tecw . xex.at(4) = 0 ; //  x positions of extra aluminum            
                   ///tecw . xex.at(4) = 0 ; //  x positions of extra aluminum            
                   tecw . zex.at(0) = 0; //  z positions of extra aluminum            
                   ///tecw . zex.at(0) = 0; //  z positions of extra aluminum            
                   tecw . zex.at(1) = 0; //  z positions of extra aluminum            
                   ///tecw . zex.at(1) = 0; //  z positions of extra aluminum            
                   tecw . zex.at(2) = 0; //  z positions of extra aluminum            
                   ///tecw . zex.at(2) = 0; //  z positions of extra aluminum            
                   tecw . zex.at(3) = 0; //  z positions of extra aluminum            
                   ///tecw . zex.at(3) = 0; //  z positions of extra aluminum            
                   tecw . zex.at(4) = 0 ; //  z positions of extra aluminum            
                   ///tecw . zex.at(4) = 0 ; //  z positions of extra aluminum            
                   tecw . dxex.at(0) = 0; //  x-thickness of extra aluminum            
                   ///tecw . dxex.at(0) = 0; //  x-thickness of extra aluminum            
                   tecw . dxex.at(1) = 0; //  x-thickness of extra aluminum            
                   ///tecw . dxex.at(1) = 0; //  x-thickness of extra aluminum            
                   tecw . dxex.at(2) = 0; //  x-thickness of extra aluminum            
                   ///tecw . dxex.at(2) = 0; //  x-thickness of extra aluminum            
                   tecw . dxex.at(3) = 0; //  x-thickness of extra aluminum            
                   ///tecw . dxex.at(3) = 0; //  x-thickness of extra aluminum            
                   tecw . dxex.at(4) = 0 ; //  x-thickness of extra aluminum            
                   ///tecw . dxex.at(4) = 0 ; //  x-thickness of extra aluminum            
                   tecw . dzex.at(0) = 0; //  z-thickness of extra aluminum            
                   ///tecw . dzex.at(0) = 0; //  z-thickness of extra aluminum            
                   tecw . dzex.at(1) = 0; //  z-thickness of extra aluminum            
                   ///tecw . dzex.at(1) = 0; //  z-thickness of extra aluminum            
                   tecw . dzex.at(2) = 0; //  z-thickness of extra aluminum            
                   ///tecw . dzex.at(2) = 0; //  z-thickness of extra aluminum            
                   tecw . dzex.at(3) = 0; //  z-thickness of extra aluminum            
                   ///tecw . dzex.at(3) = 0; //  z-thickness of extra aluminum            
                   tecw . dzex.at(4) = 0 ; //  z-thickness of extra aluminum            
                   ///tecw . dzex.at(4) = 0 ; //  z-thickness of extra aluminum            
                   tecw . nhplane.at(0) = 1; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(0) = 1; //  number of PC planes per air gap            
                   tecw . nhplane.at(1) = 4; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(1) = 4; //  number of PC planes per air gap            
                   tecw . nhplane.at(2) = 4; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(2) = 4; //  number of PC planes per air gap            
                   tecw . nhplane.at(3) = 4; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(3) = 4; //  number of PC planes per air gap            
                   tecw . nhplane.at(4) = 2; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(4) = 2; //  number of PC planes per air gap            
                   tecw . whlipthk = 1.0; //  wheel bolt lip along beam            
                   /// tecw . whlipthk = 1.0; //  wheel bolt lip along beam            
                   tecw . whlipwid = 2.8; //  wheel lip in phi            
                   /// tecw . whlipwid = 2.8; //  wheel lip in phi            
                   tecw . whblklen = 5.5; //  blocks on wheel radial size            
                   /// tecw . whblklen = 5.5; //  blocks on wheel radial size            
                   tecw . whblkpos = 18.0; //  bolt blocks at +- 18 in whl            
                   /// tecw . whblkpos = 18.0; //  bolt blocks at +- 18 in whl            
                   tecw . whblkin = 0; //  no block bottom inner wheel            
                   /// tecw . whblkin = 0; //  no block bottom inner wheel            
                   tecw . cardw = 7.33; //  PC card width and thickness             
                   /// tecw . cardw = 7.33; //  PC card width and thickness             
                   tecw . cardth = 0.19; //  PC card width and thickness             
                   /// tecw . cardth = 0.19; //  PC card width and thickness             
                   tecw . coolw = 5.7; //  cooling AL width and thickness            
                   /// tecw . coolw = 5.7; //  cooling AL width and thickness            
                   tecw . coolth = 0.33; //  cooling AL width and thickness            
                   /// tecw . coolth = 0.33; //  cooling AL width and thickness            
                   tecw . cardoff = 1.77; //  card and cooling offsets from            
                   /// tecw . cardoff = 1.77; //  card and cooling offsets from            
                   tecw . cooloff = 1.50; //  card and cooling offsets from            
                   /// tecw . cooloff = 1.50; //  card and cooling offsets from            
                   tecw . slotw = 4.70; //  slot width and radius            
                   /// tecw . slotw = 4.70; //  slot width and radius            
                   tecw . slotrad = 0.95; //  slot width and radius            
                   /// tecw . slotrad = 0.95; //  slot width and radius            
                   tecw . pipethk = 1.26; //  water pipe along beam dir            
                   /// tecw . pipethk = 1.26; //  water pipe along beam dir            
                   tecw . pipeht = 1.9; //  water pipe radial            
                   /// tecw . pipeht = 1.9; //  water pipe radial            
                   tecw . manithk = 4.5; //  water manifold along beam            
                   /// tecw . manithk = 4.5; //  water manifold along beam            
                   tecw . maniwid = 2.2; //  water manifold in phi            
                   /// tecw . maniwid = 2.2; //  water manifold in phi            
                   tecw . tan15 = .26795; //  tangent of 15 deg            
                   /// tecw . tan15 = .26795; //  tangent of 15 deg            
                   tecw . clearance = 1.0; //  clearance for RDO boardsin phi            
                   /// tecw . clearance = 1.0; //  clearance for RDO boardsin phi            
                   //           
                   tecw.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tecw_doc        
             ///@{           
                   ++tecw._index;           
                   tecw . sec = 2; //  sector number: 1 for inner, 2 for outer            
                   /// tecw . sec = 2; //  sector number: 1 for inner, 2 for outer            
                   tecw . gapwidi = 2.* 28.92; //  air in support wheel - inner width            
                   /// tecw . gapwidi = 2.* 28.92; //  air in support wheel - inner width            
                   tecw . gapwido = 2.* 46.74; //  air in support wheel - outer width            
                   /// tecw . gapwido = 2.* 46.74; //  air in support wheel - outer width            
                   tecw . gapheit = 65.0; //  air in support wheel - height (dr)            
                   /// tecw . gapheit = 65.0; //  air in support wheel - height (dr)            
                   tecw . gaprad = 158.0; //  air in support wheel - radius            
                   /// tecw . gaprad = 158.0; //  air in support wheel - radius            
                   tecw . gapshft = 0.0; //  offset of air gap lip            
                   /// tecw . gapshft = 0.0; //  offset of air gap lip            
                   tecw . inwidth = 64.92; //  sector width at inner radius             
                   /// tecw . inwidth = 64.92; //  sector width at inner radius             
                   tecw . ouwidth = 103.25; //  sector width at outer radius             
                   /// tecw . ouwidth = 103.25; //  sector width at outer radius             
                   tecw . height = 71.51; //  sector radial height            
                   /// tecw . height = 71.51; //  sector radial height            
                   tecw . ppdepth = 0.95+0.32; //  padplane thickness (both Al and PCB)            
                   /// tecw . ppdepth = 0.95+0.32; //  padplane thickness (both Al and PCB)            
                   tecw . asdepth = 6.99; //  depth of openings in aluminum structure            
                   /// tecw . asdepth = 6.99; //  depth of openings in aluminum structure            
                   tecw . ggdepth = 1.4; //  MWC gap from gated grid to pad plane            
                   /// tecw . ggdepth = 1.4; //  MWC gap from gated grid to pad plane            
                   tecw . mwcdepth = 1.4; //  sensitive MWC gas gap full thickness            
                   /// tecw . mwcdepth = 1.4; //  sensitive MWC gas gap full thickness            
                   tecw . boundary = 3.74; //  al frame - boundary width            
                   /// tecw . boundary = 3.74; //  al frame - boundary width            
                   tecw . rcenter = 157.488; //  sector center radius (set by precision holes)            
                   /// tecw . rcenter = 157.488; //  sector center radius (set by precision holes)            
                   tecw . mwcinn = 2*32.202; //  MWC sensitive region inner size            
                   /// tecw . mwcinn = 2*32.202; //  MWC sensitive region inner size            
                   tecw . mwcout = 2*49.351; //  MWC sensitive region outer size            
                   /// tecw . mwcout = 2*49.351; //  MWC sensitive region outer size            
                   tecw . mwchei = 64; //  MWC sensitive region height (radial)            
                   /// tecw . mwchei = 64; //  MWC sensitive region height (radial)            
                   tecw . mwccent = -0.093; //  sensitive region center position            
                   /// tecw . mwccent = -0.093; //  sensitive region center position            
                   tecw . mwcnwir = 160; //  number of MWC sensitive wires            
                   /// tecw . mwcnwir = 160; //  number of MWC sensitive wires            
                   tecw . n = 8; //  number of air gaps in Al            
                   /// tecw . n = 8; //  number of air gaps in Al            
                   tecw . nex = 5; //  number of extra aluminum support pieces            
                   /// tecw . nex = 5; //  number of extra aluminum support pieces            
                   tecw . z.at(0) = 8.216; //  opening positions            
                   ///tecw . z.at(0) = 8.216; //  opening positions            
                   tecw . z.at(1) = 16.217; //  opening positions            
                   ///tecw . z.at(1) = 16.217; //  opening positions            
                   tecw . z.at(2) = 24.218; //  opening positions            
                   ///tecw . z.at(2) = 24.218; //  opening positions            
                   tecw . z.at(3) = 32.219; //  opening positions            
                   ///tecw . z.at(3) = 32.219; //  opening positions            
                   tecw . z.at(4) = 40.220; //  opening positions            
                   ///tecw . z.at(4) = 40.220; //  opening positions            
                   tecw . z.at(5) = 48.221; //  opening positions            
                   ///tecw . z.at(5) = 48.221; //  opening positions            
                   tecw . z.at(6) = 56.222; //  opening positions            
                   ///tecw . z.at(6) = 56.222; //  opening positions            
                   tecw . z.at(7) = 64.143    ; //  opening positions            
                   ///tecw . z.at(7) = 64.143    ; //  opening positions            
                   tecw . dz.at(0) = 7.05; //  opening size             
                   ///tecw . dz.at(0) = 7.05; //  opening size             
                   tecw . dz.at(1) = 7.05; //  opening size             
                   ///tecw . dz.at(1) = 7.05; //  opening size             
                   tecw . dz.at(2) = 7.05; //  opening size             
                   ///tecw . dz.at(2) = 7.05; //  opening size             
                   tecw . dz.at(3) = 7.05; //  opening size             
                   ///tecw . dz.at(3) = 7.05; //  opening size             
                   tecw . dz.at(4) = 7.05; //  opening size             
                   ///tecw . dz.at(4) = 7.05; //  opening size             
                   tecw . dz.at(5) = 7.05; //  opening size             
                   ///tecw . dz.at(5) = 7.05; //  opening size             
                   tecw . dz.at(6) = 7.05; //  opening size             
                   ///tecw . dz.at(6) = 7.05; //  opening size             
                   tecw . dz.at(7) = 6.89     ; //  opening size             
                   ///tecw . dz.at(7) = 6.89     ; //  opening size             
                   tecw . xex.at(0) = 0.; //  x positions            
                   ///tecw . xex.at(0) = 0.; //  x positions            
                   tecw . xex.at(1) = 0.; //  x positions            
                   ///tecw . xex.at(1) = 0.; //  x positions            
                   tecw . xex.at(2) = 0.; //  x positions            
                   ///tecw . xex.at(2) = 0.; //  x positions            
                   tecw . xex.at(3) = -21.907; //  x positions            
                   ///tecw . xex.at(3) = -21.907; //  x positions            
                   tecw . xex.at(4) = 21.907      ; //  x positions            
                   ///tecw . xex.at(4) = 21.907      ; //  x positions            
                   tecw . zex.at(0) = 6.69; //  z positions            
                   ///tecw . zex.at(0) = 6.69; //  z positions            
                   tecw . zex.at(1) = 32.22; //  z positions            
                   ///tecw . zex.at(1) = 32.22; //  z positions            
                   tecw . zex.at(2) = 40.22; //  z positions            
                   ///tecw . zex.at(2) = 40.22; //  z positions            
                   tecw . zex.at(3) = 56.22; //  z positions            
                   ///tecw . zex.at(3) = 56.22; //  z positions            
                   tecw . zex.at(4) = 56.22 ; //  z positions            
                   ///tecw . zex.at(4) = 56.22 ; //  z positions            
                   tecw . dxex.at(0) = 2.54; //  x-thickness            
                   ///tecw . dxex.at(0) = 2.54; //  x-thickness            
                   tecw . dxex.at(1) = 0.476; //  x-thickness            
                   ///tecw . dxex.at(1) = 0.476; //  x-thickness            
                   tecw . dxex.at(2) = 0.476; //  x-thickness            
                   ///tecw . dxex.at(2) = 0.476; //  x-thickness            
                   tecw . dxex.at(3) = 3.175; //  x-thickness            
                   ///tecw . dxex.at(3) = 3.175; //  x-thickness            
                   tecw . dxex.at(4) = 3.175 ; //  x-thickness            
                   ///tecw . dxex.at(4) = 3.175 ; //  x-thickness            
                   tecw . dzex.at(0) = 4.00; //  z-thickness            
                   ///tecw . dzex.at(0) = 4.00; //  z-thickness            
                   tecw . dzex.at(1) = 7.05; //  z-thickness            
                   ///tecw . dzex.at(1) = 7.05; //  z-thickness            
                   tecw . dzex.at(2) = 7.05; //  z-thickness            
                   ///tecw . dzex.at(2) = 7.05; //  z-thickness            
                   tecw . dzex.at(3) = 7.05; //  z-thickness            
                   ///tecw . dzex.at(3) = 7.05; //  z-thickness            
                   tecw . dzex.at(4) = 7.05  ; //  z-thickness            
                   ///tecw . dzex.at(4) = 7.05  ; //  z-thickness            
                   tecw . nhplane.at(0) = 2; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(0) = 2; //  number of PC planes per air gap            
                   tecw . nhplane.at(1) = 2; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(1) = 2; //  number of PC planes per air gap            
                   tecw . nhplane.at(2) = 2; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(2) = 2; //  number of PC planes per air gap            
                   tecw . nhplane.at(3) = 2; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(3) = 2; //  number of PC planes per air gap            
                   tecw . nhplane.at(4) = 2; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(4) = 2; //  number of PC planes per air gap            
                   tecw . nhplane.at(5) = 2; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(5) = 2; //  number of PC planes per air gap            
                   tecw . nhplane.at(6) = 2; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(6) = 2; //  number of PC planes per air gap            
                   tecw . nhplane.at(7) = 2; //  number of PC planes per air gap            
                   ///tecw . nhplane.at(7) = 2; //  number of PC planes per air gap            
                   tecw . whlipthk = 1.0; //  wheel bolt lip along beam            
                   /// tecw . whlipthk = 1.0; //  wheel bolt lip along beam            
                   tecw . whlipwid = 2.8; //  wheel lip in phi            
                   /// tecw . whlipwid = 2.8; //  wheel lip in phi            
                   tecw . whblklen = 5.5; //  blocks on wheel radial size            
                   /// tecw . whblklen = 5.5; //  blocks on wheel radial size            
                   tecw . whblkpos = 18.0; //  bolt blocks at +- 18 in whl            
                   /// tecw . whblkpos = 18.0; //  bolt blocks at +- 18 in whl            
                   tecw . whblkin = 1; //  is block bottom outer wheel            
                   /// tecw . whblkin = 1; //  is block bottom outer wheel            
                   tecw . cardw = 7.33; //  PC card width and thickness             
                   /// tecw . cardw = 7.33; //  PC card width and thickness             
                   tecw . cardth = 0.19; //  PC card width and thickness             
                   /// tecw . cardth = 0.19; //  PC card width and thickness             
                   tecw . coolw = 5.7; //  cooling AL width and thickness            
                   /// tecw . coolw = 5.7; //  cooling AL width and thickness            
                   tecw . coolth = 0.33; //  cooling AL width and thickness            
                   /// tecw . coolth = 0.33; //  cooling AL width and thickness            
                   tecw . cardoff = 1.77; //  card and cooling offsets from            
                   /// tecw . cardoff = 1.77; //  card and cooling offsets from            
                   tecw . cooloff = 1.50; //  card and cooling offsets from            
                   /// tecw . cooloff = 1.50; //  card and cooling offsets from            
                   tecw . slotw = 4.70; //  slot width and radius            
                   /// tecw . slotw = 4.70; //  slot width and radius            
                   tecw . slotrad = 0.95; //  slot width and radius            
                   /// tecw . slotrad = 0.95; //  slot width and radius            
                   tecw . pipethk = 1.26; //  water pipe along beam dir            
                   /// tecw . pipethk = 1.26; //  water pipe along beam dir            
                   tecw . pipeht = 1.9; //  water pipe radial            
                   /// tecw . pipeht = 1.9; //  water pipe radial            
                   tecw . manithk = 4.5; //  water manifold along beam            
                   /// tecw . manithk = 4.5; //  water manifold along beam            
                   tecw . maniwid = 2.2; //  water manifold in phi            
                   /// tecw . maniwid = 2.2; //  water manifold in phi            
                   tecw . tan15 = .26795; //  tangent of 15 deg            
                   /// tecw . tan15 = .26795; //  tangent of 15 deg            
                   tecw . clearance = 1.0; //  clearance for RDO boardsin phi            
                   /// tecw . clearance = 1.0; //  clearance for RDO boardsin phi            
                   //           
                   tecw.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup trov_doc        
             ///@{           
                   ++trov._index;           
                   trov . sec = 1; //   inner            
                   /// trov . sec = 1; //   inner            
                   trov . nhp.at(0) = 0; // no of holes/plane            
                   ///trov . nhp.at(0) = 0; // no of holes/plane            
                   trov . nhp.at(1) = 2; // no of holes/plane            
                   ///trov . nhp.at(1) = 2; // no of holes/plane            
                   trov . nhp.at(2) = 2; // no of holes/plane            
                   ///trov . nhp.at(2) = 2; // no of holes/plane            
                   trov . nhp.at(3) = 3; // no of holes/plane            
                   ///trov . nhp.at(3) = 3; // no of holes/plane            
                   trov . nhp.at(4) = 3; // no of holes/plane            
                   ///trov . nhp.at(4) = 3; // no of holes/plane            
                   trov . nhp.at(5) = 3; // no of holes/plane            
                   ///trov . nhp.at(5) = 3; // no of holes/plane            
                   trov . nhp.at(6) = 3; // no of holes/plane            
                   ///trov . nhp.at(6) = 3; // no of holes/plane            
                   trov . nhp.at(7) = 4; // no of holes/plane            
                   ///trov . nhp.at(7) = 4; // no of holes/plane            
                   trov . nhp.at(8) = 4; // no of holes/plane            
                   ///trov . nhp.at(8) = 4; // no of holes/plane            
                   trov . nhp.at(9) = 4; // no of holes/plane            
                   ///trov . nhp.at(9) = 4; // no of holes/plane            
                   trov . nhp.at(10) = 4; // no of holes/plane            
                   ///trov . nhp.at(10) = 4; // no of holes/plane            
                   trov . nhp.at(11) = 5; // no of holes/plane            
                   ///trov . nhp.at(11) = 5; // no of holes/plane            
                   trov . nhp.at(12) = 2; // no of holes/plane            
                   ///trov . nhp.at(12) = 2; // no of holes/plane            
                   trov . nhp.at(13) = 5; // no of holes/plane            
                   ///trov . nhp.at(13) = 5; // no of holes/plane            
                   trov . nhp.at(14) = 5; // no of holes/plane            
                   ///trov . nhp.at(14) = 5; // no of holes/plane            
                   trov . nhp.at(15) = 6; // no of holes/plane            
                   ///trov . nhp.at(15) = 6; // no of holes/plane            
                   trov . hx.at(0) = 9*0.0; //  x of holes            
                   ///trov . hx.at(0) = 9*0.0; //  x of holes            
                   trov . hx.at(1) = -5.17; //  x of holes            
                   ///trov . hx.at(1) = -5.17; //  x of holes            
                   trov . hx.at(2) =  5.17; //  x of holes            
                   ///trov . hx.at(2) =  5.17; //  x of holes            
                   trov . hx.at(3) =  7*0.0; //  x of holes            
                   ///trov . hx.at(3) =  7*0.0; //  x of holes            
                   trov . hx.at(4) = -6.21; //  x of holes            
                   ///trov . hx.at(4) = -6.21; //  x of holes            
                   trov . hx.at(5) =  6.21; //  x of holes            
                   ///trov . hx.at(5) =  6.21; //  x of holes            
                   trov . hx.at(6) =  7*0.0; //  x of holes            
                   ///trov . hx.at(6) =  7*0.0; //  x of holes            
                   trov . hx.at(7) = -7.79; //  x of holes            
                   ///trov . hx.at(7) = -7.79; //  x of holes            
                   trov . hx.at(8) =  0.0; //  x of holes            
                   ///trov . hx.at(8) =  0.0; //  x of holes            
                   trov . hx.at(9) =  7.79; //  x of holes            
                   ///trov . hx.at(9) =  7.79; //  x of holes            
                   trov . hx.at(10) =  6*0.0; //  x of holes            
                   ///trov . hx.at(10) =  6*0.0; //  x of holes            
                   trov . hx.at(11) = -8.34; //  x of holes            
                   ///trov . hx.at(11) = -8.34; //  x of holes            
                   trov . hx.at(12) =  0.0; //  x of holes            
                   ///trov . hx.at(12) =  0.0; //  x of holes            
                   trov . hx.at(13) =  8.34; //  x of holes            
                   ///trov . hx.at(13) =  8.34; //  x of holes            
                   trov . hx.at(14) =  6*0.0; //  x of holes            
                   ///trov . hx.at(14) =  6*0.0; //  x of holes            
                   trov . hx.at(15) = -9.38; //  x of holes            
                   ///trov . hx.at(15) = -9.38; //  x of holes            
                   trov . hx.at(16) =  0.0; //  x of holes            
                   ///trov . hx.at(16) =  0.0; //  x of holes            
                   trov . hx.at(17) =  9.38; //  x of holes            
                   ///trov . hx.at(17) =  9.38; //  x of holes            
                   trov . hx.at(18) =  6*0.0; //  x of holes            
                   ///trov . hx.at(18) =  6*0.0; //  x of holes            
                   trov . hx.at(19) = -10.50; //  x of holes            
                   ///trov . hx.at(19) = -10.50; //  x of holes            
                   trov . hx.at(20) =  0.0; //  x of holes            
                   ///trov . hx.at(20) =  0.0; //  x of holes            
                   trov . hx.at(21) =  10.50; //  x of holes            
                   ///trov . hx.at(21) =  10.50; //  x of holes            
                   trov . hx.at(22) =  6*0.0; //  x of holes            
                   ///trov . hx.at(22) =  6*0.0; //  x of holes            
                   trov . hx.at(23) = -11.97; //  x of holes            
                   ///trov . hx.at(23) = -11.97; //  x of holes            
                   trov . hx.at(24) =  -4.05; //  x of holes            
                   ///trov . hx.at(24) =  -4.05; //  x of holes            
                   trov . hx.at(25) =  4.05; //  x of holes            
                   ///trov . hx.at(25) =  4.05; //  x of holes            
                   trov . hx.at(26) =  11.97; //  x of holes            
                   ///trov . hx.at(26) =  11.97; //  x of holes            
                   trov . hx.at(27) =  5*0.0; //  x of holes            
                   ///trov . hx.at(27) =  5*0.0; //  x of holes            
                   trov . hx.at(28) = -12.70; //  x of holes            
                   ///trov . hx.at(28) = -12.70; //  x of holes            
                   trov . hx.at(29) =  -4.32; //  x of holes            
                   ///trov . hx.at(29) =  -4.32; //  x of holes            
                   trov . hx.at(30) =  4.32; //  x of holes            
                   ///trov . hx.at(30) =  4.32; //  x of holes            
                   trov . hx.at(31) =  12.70; //  x of holes            
                   ///trov . hx.at(31) =  12.70; //  x of holes            
                   trov . hx.at(32) =  5*0.0; //  x of holes            
                   ///trov . hx.at(32) =  5*0.0; //  x of holes            
                   trov . hx.at(33) = -13.70; //  x of holes            
                   ///trov . hx.at(33) = -13.70; //  x of holes            
                   trov . hx.at(34) =  -4.63; //  x of holes            
                   ///trov . hx.at(34) =  -4.63; //  x of holes            
                   trov . hx.at(35) =  4.63; //  x of holes            
                   ///trov . hx.at(35) =  4.63; //  x of holes            
                   trov . hx.at(36) =  13.70; //  x of holes            
                   ///trov . hx.at(36) =  13.70; //  x of holes            
                   trov . hx.at(37) =  5*0.0; //  x of holes            
                   ///trov . hx.at(37) =  5*0.0; //  x of holes            
                   trov . hx.at(38) = -14.67; //  x of holes            
                   ///trov . hx.at(38) = -14.67; //  x of holes            
                   trov . hx.at(39) =  -4.98; //  x of holes            
                   ///trov . hx.at(39) =  -4.98; //  x of holes            
                   trov . hx.at(40) =  4.98; //  x of holes            
                   ///trov . hx.at(40) =  4.98; //  x of holes            
                   trov . hx.at(41) =  14.67; //  x of holes            
                   ///trov . hx.at(41) =  14.67; //  x of holes            
                   trov . hx.at(42) =  5*0.0; //  x of holes            
                   ///trov . hx.at(42) =  5*0.0; //  x of holes            
                   trov . hx.at(43) = -15.86; //  x of holes            
                   ///trov . hx.at(43) = -15.86; //  x of holes            
                   trov . hx.at(44) =  -7.91; //  x of holes            
                   ///trov . hx.at(44) =  -7.91; //  x of holes            
                   trov . hx.at(45) =  0.0; //  x of holes            
                   ///trov . hx.at(45) =  0.0; //  x of holes            
                   trov . hx.at(46) =  7.91; //  x of holes            
                   ///trov . hx.at(46) =  7.91; //  x of holes            
                   trov . hx.at(47) =  15.86; //  x of holes            
                   ///trov . hx.at(47) =  15.86; //  x of holes            
                   trov . hx.at(48) =  4*0.0; //  x of holes            
                   ///trov . hx.at(48) =  4*0.0; //  x of holes            
                   trov . hx.at(49) = -16.95; //  x of holes            
                   ///trov . hx.at(49) = -16.95; //  x of holes            
                   trov . hx.at(50) =  16.95; //  x of holes            
                   ///trov . hx.at(50) =  16.95; //  x of holes            
                   trov . hx.at(51) =  7*0.0; //  x of holes            
                   ///trov . hx.at(51) =  7*0.0; //  x of holes            
                   trov . hx.at(52) = -18.37; //  x of holes            
                   ///trov . hx.at(52) = -18.37; //  x of holes            
                   trov . hx.at(53) =  -8.99; //  x of holes            
                   ///trov . hx.at(53) =  -8.99; //  x of holes            
                   trov . hx.at(54) =  0.0; //  x of holes            
                   ///trov . hx.at(54) =  0.0; //  x of holes            
                   trov . hx.at(55) =  8.99; //  x of holes            
                   ///trov . hx.at(55) =  8.99; //  x of holes            
                   trov . hx.at(56) =  18.37; //  x of holes            
                   ///trov . hx.at(56) =  18.37; //  x of holes            
                   trov . hx.at(57) =  4*0.0; //  x of holes            
                   ///trov . hx.at(57) =  4*0.0; //  x of holes            
                   trov . hx.at(58) = -19.11; //  x of holes            
                   ///trov . hx.at(58) = -19.11; //  x of holes            
                   trov . hx.at(59) =  -9.76; //  x of holes            
                   ///trov . hx.at(59) =  -9.76; //  x of holes            
                   trov . hx.at(60) =  0.0; //  x of holes            
                   ///trov . hx.at(60) =  0.0; //  x of holes            
                   trov . hx.at(61) =  9.76; //  x of holes            
                   ///trov . hx.at(61) =  9.76; //  x of holes            
                   trov . hx.at(62) =  19.11; //  x of holes            
                   ///trov . hx.at(62) =  19.11; //  x of holes            
                   trov . hx.at(63) =  4*0.0; //  x of holes            
                   ///trov . hx.at(63) =  4*0.0; //  x of holes            
                   trov . hx.at(64) = -20.15; //  x of holes            
                   ///trov . hx.at(64) = -20.15; //  x of holes            
                   trov . hx.at(65) =  -12.08; //  x of holes            
                   ///trov . hx.at(65) =  -12.08; //  x of holes            
                   trov . hx.at(66) =  -4.05; //  x of holes            
                   ///trov . hx.at(66) =  -4.05; //  x of holes            
                   trov . hx.at(67) =  4.05; //  x of holes            
                   ///trov . hx.at(67) =  4.05; //  x of holes            
                   trov . hx.at(68) =  12.08; //  x of holes            
                   ///trov . hx.at(68) =  12.08; //  x of holes            
                   trov . hx.at(69) =  20.15; //  x of holes            
                   ///trov . hx.at(69) =  20.15; //  x of holes            
                   trov . hx.at(70) =  3*0.0; //  x of holes            
                   ///trov . hx.at(70) =  3*0.0; //  x of holes            
                   trov . offcardinout = -0.9; //  cards, first row inner sector            
                   /// trov . offcardinout = -0.9; //  cards, first row inner sector            
                   //           
                   trov.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup trov_doc        
             ///@{           
                   ++trov._index;           
                   trov . sec = 2; //   outer            
                   /// trov . sec = 2; //   outer            
                   trov . nhp.at(0) = 6; //  number of holes / plane            
                   ///trov . nhp.at(0) = 6; //  number of holes / plane            
                   trov . nhp.at(1) = 7; //  number of holes / plane            
                   ///trov . nhp.at(1) = 7; //  number of holes / plane            
                   trov . nhp.at(2) = 7; //  number of holes / plane            
                   ///trov . nhp.at(2) = 7; //  number of holes / plane            
                   trov . nhp.at(3) = 7; //  number of holes / plane            
                   ///trov . nhp.at(3) = 7; //  number of holes / plane            
                   trov . nhp.at(4) = 7; //  number of holes / plane            
                   ///trov . nhp.at(4) = 7; //  number of holes / plane            
                   trov . nhp.at(5) = 7; //  number of holes / plane            
                   ///trov . nhp.at(5) = 7; //  number of holes / plane            
                   trov . nhp.at(6) = 8; //  number of holes / plane            
                   ///trov . nhp.at(6) = 8; //  number of holes / plane            
                   trov . nhp.at(7) = 8; //  number of holes / plane            
                   ///trov . nhp.at(7) = 8; //  number of holes / plane            
                   trov . nhp.at(8) = 8; //  number of holes / plane            
                   ///trov . nhp.at(8) = 8; //  number of holes / plane            
                   trov . nhp.at(9) = 8; //  number of holes / plane            
                   ///trov . nhp.at(9) = 8; //  number of holes / plane            
                   trov . nhp.at(10) = 8; //  number of holes / plane            
                   ///trov . nhp.at(10) = 8; //  number of holes / plane            
                   trov . nhp.at(11) = 9; //  number of holes / plane            
                   ///trov . nhp.at(11) = 9; //  number of holes / plane            
                   trov . nhp.at(12) = 9; //  number of holes / plane            
                   ///trov . nhp.at(12) = 9; //  number of holes / plane            
                   trov . nhp.at(13) = 9; //  number of holes / plane            
                   ///trov . nhp.at(13) = 9; //  number of holes / plane            
                   trov . nhp.at(14) = 9; //  number of holes / plane            
                   ///trov . nhp.at(14) = 9; //  number of holes / plane            
                   trov . nhp.at(15) = 9; //  number of holes / plane            
                   ///trov . nhp.at(15) = 9; //  number of holes / plane            
                   trov . hx.at(0) = -23.70; //  x of holes            
                   ///trov . hx.at(0) = -23.70; //  x of holes            
                   trov . hx.at(1) =  -15.77; //  x of holes            
                   ///trov . hx.at(1) =  -15.77; //  x of holes            
                   trov . hx.at(2) =  -7.72; //  x of holes            
                   ///trov . hx.at(2) =  -7.72; //  x of holes            
                   trov . hx.at(3) =  7.72; //  x of holes            
                   ///trov . hx.at(3) =  7.72; //  x of holes            
                   trov . hx.at(4) =  15.77; //  x of holes            
                   ///trov . hx.at(4) =  15.77; //  x of holes            
                   trov . hx.at(5) =  23.70; //  x of holes            
                   ///trov . hx.at(5) =  23.70; //  x of holes            
                   trov . hx.at(6) =  3*0.0; //  x of holes            
                   ///trov . hx.at(6) =  3*0.0; //  x of holes            
                   trov . hx.at(7) = -24.15; //  x of holes            
                   ///trov . hx.at(7) = -24.15; //  x of holes            
                   trov . hx.at(8) =  -16.25; //  x of holes            
                   ///trov . hx.at(8) =  -16.25; //  x of holes            
                   trov . hx.at(9) =  -8.10; //  x of holes            
                   ///trov . hx.at(9) =  -8.10; //  x of holes            
                   trov . hx.at(10) =  0.00; //  x of holes            
                   ///trov . hx.at(10) =  0.00; //  x of holes            
                   trov . hx.at(11) =   8.10; //  x of holes            
                   ///trov . hx.at(11) =   8.10; //  x of holes            
                   trov . hx.at(12) =  16.25; //  x of holes            
                   ///trov . hx.at(12) =  16.25; //  x of holes            
                   trov . hx.at(13) =  24.15; //  x of holes            
                   ///trov . hx.at(13) =  24.15; //  x of holes            
                   trov . hx.at(14) =  2*0.0; //  x of holes            
                   ///trov . hx.at(14) =  2*0.0; //  x of holes            
                   trov . hx.at(15) = -25.48; //  x of holes            
                   ///trov . hx.at(15) = -25.48; //  x of holes            
                   trov . hx.at(16) =  -17.47 ; //  x of holes            
                   ///trov . hx.at(16) =  -17.47 ; //  x of holes            
                   trov . hx.at(17) = -8.71; //  x of holes            
                   ///trov . hx.at(17) = -8.71; //  x of holes            
                   trov . hx.at(18) =  0.00; //  x of holes            
                   ///trov . hx.at(18) =  0.00; //  x of holes            
                   trov . hx.at(19) =   8.71; //  x of holes            
                   ///trov . hx.at(19) =   8.71; //  x of holes            
                   trov . hx.at(20) =  17.47; //  x of holes            
                   ///trov . hx.at(20) =  17.47; //  x of holes            
                   trov . hx.at(21) =  25.48; //  x of holes            
                   ///trov . hx.at(21) =  25.48; //  x of holes            
                   trov . hx.at(22) =  2*0.0; //  x of holes            
                   ///trov . hx.at(22) =  2*0.0; //  x of holes            
                   trov . hx.at(23) = -25.48; //  x of holes            
                   ///trov . hx.at(23) = -25.48; //  x of holes            
                   trov . hx.at(24) =  -17.47; //  x of holes            
                   ///trov . hx.at(24) =  -17.47; //  x of holes            
                   trov . hx.at(25) =  -8.71; //  x of holes            
                   ///trov . hx.at(25) =  -8.71; //  x of holes            
                   trov . hx.at(26) =  0.00; //  x of holes            
                   ///trov . hx.at(26) =  0.00; //  x of holes            
                   trov . hx.at(27) =   8.71; //  x of holes            
                   ///trov . hx.at(27) =   8.71; //  x of holes            
                   trov . hx.at(28) =  17.47; //  x of holes            
                   ///trov . hx.at(28) =  17.47; //  x of holes            
                   trov . hx.at(29) =  25.48; //  x of holes            
                   ///trov . hx.at(29) =  25.48; //  x of holes            
                   trov . hx.at(30) =  2*0.0; //  x of holes            
                   ///trov . hx.at(30) =  2*0.0; //  x of holes            
                   trov . hx.at(31) = -28.19; //  x of holes            
                   ///trov . hx.at(31) = -28.19; //  x of holes            
                   trov . hx.at(32) =  -19.43; //  x of holes            
                   ///trov . hx.at(32) =  -19.43; //  x of holes            
                   trov . hx.at(33) = -10.81; //  x of holes            
                   ///trov . hx.at(33) = -10.81; //  x of holes            
                   trov . hx.at(34) =  0.00 ; //  x of holes            
                   ///trov . hx.at(34) =  0.00 ; //  x of holes            
                   trov . hx.at(35) = 10.81; //  x of holes            
                   ///trov . hx.at(35) = 10.81; //  x of holes            
                   trov . hx.at(36) =  19.43; //  x of holes            
                   ///trov . hx.at(36) =  19.43; //  x of holes            
                   trov . hx.at(37) =  28.19; //  x of holes            
                   ///trov . hx.at(37) =  28.19; //  x of holes            
                   trov . hx.at(38) =  2*0.0; //  x of holes            
                   ///trov . hx.at(38) =  2*0.0; //  x of holes            
                   trov . hx.at(39) = -28.19; //  x of holes            
                   ///trov . hx.at(39) = -28.19; //  x of holes            
                   trov . hx.at(40) =  -19.43; //  x of holes            
                   ///trov . hx.at(40) =  -19.43; //  x of holes            
                   trov . hx.at(41) = -10.81; //  x of holes            
                   ///trov . hx.at(41) = -10.81; //  x of holes            
                   trov . hx.at(42) =  0.00; //  x of holes            
                   ///trov . hx.at(42) =  0.00; //  x of holes            
                   trov . hx.at(43) =  10.81; //  x of holes            
                   ///trov . hx.at(43) =  10.81; //  x of holes            
                   trov . hx.at(44) =  19.43; //  x of holes            
                   ///trov . hx.at(44) =  19.43; //  x of holes            
                   trov . hx.at(45) =  28.19; //  x of holes            
                   ///trov . hx.at(45) =  28.19; //  x of holes            
                   trov . hx.at(46) =  2*0.0; //  x of holes            
                   ///trov . hx.at(46) =  2*0.0; //  x of holes            
                   trov . hx.at(47) = -30.24; //  x of holes            
                   ///trov . hx.at(47) = -30.24; //  x of holes            
                   trov . hx.at(48) =  -21.51; //  x of holes            
                   ///trov . hx.at(48) =  -21.51; //  x of holes            
                   trov . hx.at(49) = -13.54; //  x of holes            
                   ///trov . hx.at(49) = -13.54; //  x of holes            
                   trov . hx.at(50) = -5.37; //  x of holes            
                   ///trov . hx.at(50) = -5.37; //  x of holes            
                   trov . hx.at(51) =   5.37; //  x of holes            
                   ///trov . hx.at(51) =   5.37; //  x of holes            
                   trov . hx.at(52) =  13.54; //  x of holes            
                   ///trov . hx.at(52) =  13.54; //  x of holes            
                   trov . hx.at(53) =  21.51; //  x of holes            
                   ///trov . hx.at(53) =  21.51; //  x of holes            
                   trov . hx.at(54) =  30.24; //  x of holes            
                   ///trov . hx.at(54) =  30.24; //  x of holes            
                   trov . hx.at(55) =    0.0; //  x of holes            
                   ///trov . hx.at(55) =    0.0; //  x of holes            
                   trov . hx.at(56) = -30.24; //  x of holes            
                   ///trov . hx.at(56) = -30.24; //  x of holes            
                   trov . hx.at(57) =  -21.51; //  x of holes            
                   ///trov . hx.at(57) =  -21.51; //  x of holes            
                   trov . hx.at(58) = -13.54; //  x of holes            
                   ///trov . hx.at(58) = -13.54; //  x of holes            
                   trov . hx.at(59) = -5.37; //  x of holes            
                   ///trov . hx.at(59) = -5.37; //  x of holes            
                   trov . hx.at(60) =   5.37; //  x of holes            
                   ///trov . hx.at(60) =   5.37; //  x of holes            
                   trov . hx.at(61) =  13.54; //  x of holes            
                   ///trov . hx.at(61) =  13.54; //  x of holes            
                   trov . hx.at(62) =  21.51; //  x of holes            
                   ///trov . hx.at(62) =  21.51; //  x of holes            
                   trov . hx.at(63) =  30.24; //  x of holes            
                   ///trov . hx.at(63) =  30.24; //  x of holes            
                   trov . hx.at(64) =  1*0.0; //  x of holes            
                   ///trov . hx.at(64) =  1*0.0; //  x of holes            
                   trov . hx.at(65) = -32.23; //  x of holes            
                   ///trov . hx.at(65) = -32.23; //  x of holes            
                   trov . hx.at(66) =  -24.17; //  x of holes            
                   ///trov . hx.at(66) =  -24.17; //  x of holes            
                   trov . hx.at(67) = -16.09; //  x of holes            
                   ///trov . hx.at(67) = -16.09; //  x of holes            
                   trov . hx.at(68) = -5.42; //  x of holes            
                   ///trov . hx.at(68) = -5.42; //  x of holes            
                   trov . hx.at(69) =   5.42; //  x of holes            
                   ///trov . hx.at(69) =   5.42; //  x of holes            
                   trov . hx.at(70) =  16.09; //  x of holes            
                   ///trov . hx.at(70) =  16.09; //  x of holes            
                   trov . hx.at(71) =  24.17; //  x of holes            
                   ///trov . hx.at(71) =  24.17; //  x of holes            
                   trov . hx.at(72) =  32.23; //  x of holes            
                   ///trov . hx.at(72) =  32.23; //  x of holes            
                   trov . hx.at(73) =    0.0; //  x of holes            
                   ///trov . hx.at(73) =    0.0; //  x of holes            
                   trov . hx.at(74) = -32.23; //  x of holes            
                   ///trov . hx.at(74) = -32.23; //  x of holes            
                   trov . hx.at(75) =  -24.17; //  x of holes            
                   ///trov . hx.at(75) =  -24.17; //  x of holes            
                   trov . hx.at(76) = -16.09; //  x of holes            
                   ///trov . hx.at(76) = -16.09; //  x of holes            
                   trov . hx.at(77) = -5.42; //  x of holes            
                   ///trov . hx.at(77) = -5.42; //  x of holes            
                   trov . hx.at(78) =   5.42; //  x of holes            
                   ///trov . hx.at(78) =   5.42; //  x of holes            
                   trov . hx.at(79) =  16.09; //  x of holes            
                   ///trov . hx.at(79) =  16.09; //  x of holes            
                   trov . hx.at(80) =  24.17; //  x of holes            
                   ///trov . hx.at(80) =  24.17; //  x of holes            
                   trov . hx.at(81) =  32.23; //  x of holes            
                   ///trov . hx.at(81) =  32.23; //  x of holes            
                   trov . hx.at(82) =  1*0.0; //  x of holes            
                   ///trov . hx.at(82) =  1*0.0; //  x of holes            
                   trov . hx.at(83) = -34.30; //  x of holes            
                   ///trov . hx.at(83) = -34.30; //  x of holes            
                   trov . hx.at(84) =  -25.86; //  x of holes            
                   ///trov . hx.at(84) =  -25.86; //  x of holes            
                   trov . hx.at(85) = -16.14; //  x of holes            
                   ///trov . hx.at(85) = -16.14; //  x of holes            
                   trov . hx.at(86) = -8.10; //  x of holes            
                   ///trov . hx.at(86) = -8.10; //  x of holes            
                   trov . hx.at(87) =   8.10; //  x of holes            
                   ///trov . hx.at(87) =   8.10; //  x of holes            
                   trov . hx.at(88) =  16.14; //  x of holes            
                   ///trov . hx.at(88) =  16.14; //  x of holes            
                   trov . hx.at(89) =  25.86; //  x of holes            
                   ///trov . hx.at(89) =  25.86; //  x of holes            
                   trov . hx.at(90) =  34.30; //  x of holes            
                   ///trov . hx.at(90) =  34.30; //  x of holes            
                   trov . hx.at(91) =    0.0; //  x of holes            
                   ///trov . hx.at(91) =    0.0; //  x of holes            
                   trov . hx.at(92) = -34.30; //  x of holes            
                   ///trov . hx.at(92) = -34.30; //  x of holes            
                   trov . hx.at(93) =  -25.86; //  x of holes            
                   ///trov . hx.at(93) =  -25.86; //  x of holes            
                   trov . hx.at(94) = -16.14; //  x of holes            
                   ///trov . hx.at(94) = -16.14; //  x of holes            
                   trov . hx.at(95) = -8.10; //  x of holes            
                   ///trov . hx.at(95) = -8.10; //  x of holes            
                   trov . hx.at(96) =   0.00; //  x of holes            
                   ///trov . hx.at(96) =   0.00; //  x of holes            
                   trov . hx.at(97) =   8.10; //  x of holes            
                   ///trov . hx.at(97) =   8.10; //  x of holes            
                   trov . hx.at(98) =  16.14; //  x of holes            
                   ///trov . hx.at(98) =  16.14; //  x of holes            
                   trov . hx.at(99) =  25.86; //  x of holes            
                   ///trov . hx.at(99) =  25.86; //  x of holes            
                   trov . hx.at(100) =   34.30; //  x of holes            
                   ///trov . hx.at(100) =   34.30; //  x of holes            
                   trov . hx.at(101) = 1*0.0; //  x of holes            
                   ///trov . hx.at(101) = 1*0.0; //  x of holes            
                   trov . hx.at(102) = -36.16; //  x of holes            
                   ///trov . hx.at(102) = -36.16; //  x of holes            
                   trov . hx.at(103) =  -28.12; //  x of holes            
                   ///trov . hx.at(103) =  -28.12; //  x of holes            
                   trov . hx.at(104) = -16.14; //  x of holes            
                   ///trov . hx.at(104) = -16.14; //  x of holes            
                   trov . hx.at(105) = -8.10; //  x of holes            
                   ///trov . hx.at(105) = -8.10; //  x of holes            
                   trov . hx.at(106) =   0.00; //  x of holes            
                   ///trov . hx.at(106) =   0.00; //  x of holes            
                   trov . hx.at(107) =   8.10; //  x of holes            
                   ///trov . hx.at(107) =   8.10; //  x of holes            
                   trov . hx.at(108) =  16.14; //  x of holes            
                   ///trov . hx.at(108) =  16.14; //  x of holes            
                   trov . hx.at(109) =  28.12; //  x of holes            
                   ///trov . hx.at(109) =  28.12; //  x of holes            
                   trov . hx.at(110) =   36.16; //  x of holes            
                   ///trov . hx.at(110) =   36.16; //  x of holes            
                   trov . hx.at(111) = -36.16; //  x of holes            
                   ///trov . hx.at(111) = -36.16; //  x of holes            
                   trov . hx.at(112) =  -28.12; //  x of holes            
                   ///trov . hx.at(112) =  -28.12; //  x of holes            
                   trov . hx.at(113) = -16.14; //  x of holes            
                   ///trov . hx.at(113) = -16.14; //  x of holes            
                   trov . hx.at(114) = -8.10; //  x of holes            
                   ///trov . hx.at(114) = -8.10; //  x of holes            
                   trov . hx.at(115) =   0.00; //  x of holes            
                   ///trov . hx.at(115) =   0.00; //  x of holes            
                   trov . hx.at(116) =   8.10; //  x of holes            
                   ///trov . hx.at(116) =   8.10; //  x of holes            
                   trov . hx.at(117) =  16.14; //  x of holes            
                   ///trov . hx.at(117) =  16.14; //  x of holes            
                   trov . hx.at(118) =  28.12; //  x of holes            
                   ///trov . hx.at(118) =  28.12; //  x of holes            
                   trov . hx.at(119) =   36.16; //  x of holes            
                   ///trov . hx.at(119) =   36.16; //  x of holes            
                   trov . hx.at(120) = 18*0.0; //  x of holes            
                   ///trov . hx.at(120) = 18*0.0; //  x of holes            
                   trov . hx.at(121) = -38.37; //  x of holes            
                   ///trov . hx.at(121) = -38.37; //  x of holes            
                   trov . hx.at(122) =  -29.47; //  x of holes            
                   ///trov . hx.at(122) =  -29.47; //  x of holes            
                   trov . hx.at(123) = -20.76; //  x of holes            
                   ///trov . hx.at(123) = -20.76; //  x of holes            
                   trov . hx.at(124) = -10.61; //  x of holes            
                   ///trov . hx.at(124) = -10.61; //  x of holes            
                   trov . hx.at(125) =  0.00; //  x of holes            
                   ///trov . hx.at(125) =  0.00; //  x of holes            
                   trov . hx.at(126) =  10.61; //  x of holes            
                   ///trov . hx.at(126) =  10.61; //  x of holes            
                   trov . hx.at(127) =  20.76; //  x of holes            
                   ///trov . hx.at(127) =  20.76; //  x of holes            
                   trov . hx.at(128) =  29.47; //  x of holes            
                   ///trov . hx.at(128) =  29.47; //  x of holes            
                   trov . hx.at(129) =   38.37; //  x of holes            
                   ///trov . hx.at(129) =   38.37; //  x of holes            
                   trov . hx.at(130) = -38.37; //  x of holes            
                   ///trov . hx.at(130) = -38.37; //  x of holes            
                   trov . hx.at(131) =  -29.47; //  x of holes            
                   ///trov . hx.at(131) =  -29.47; //  x of holes            
                   trov . hx.at(132) = -20.76; //  x of holes            
                   ///trov . hx.at(132) = -20.76; //  x of holes            
                   trov . hx.at(133) = -10.61; //  x of holes            
                   ///trov . hx.at(133) = -10.61; //  x of holes            
                   trov . hx.at(134) =  0.00; //  x of holes            
                   ///trov . hx.at(134) =  0.00; //  x of holes            
                   trov . hx.at(135) =  10.61; //  x of holes            
                   ///trov . hx.at(135) =  10.61; //  x of holes            
                   trov . hx.at(136) =  20.76; //  x of holes            
                   ///trov . hx.at(136) =  20.76; //  x of holes            
                   trov . hx.at(137) =  29.47; //  x of holes            
                   ///trov . hx.at(137) =  29.47; //  x of holes            
                   trov . hx.at(138) =   38.37; //  x of holes            
                   ///trov . hx.at(138) =   38.37; //  x of holes            
                   trov . offcardinout = 0.0; //   card no special case             
                   /// trov . offcardinout = 0.0; //   card no special case             
                   //           
                   trov.fill();           
             ///@}        
             //        
             /// USE tpcg _index=1;        
             tpcg.Use();        
             tofcleng = tpcg.length-2*tpcg.wheelthk-2*trdo.rdovthk  ;// gas plus endcaps;        
             tpgvleng = (tofcleng-tpcg.membthk-2*tpcg.tpeathk)/2 ;// active gas;        
             tocsir = tpcg.sengasor;   tocsor = tocsir + tpcg.tocsdr;        
             tokair = tocsor;          tokaor = tokair + tpcg.tokadr;        
             tonxir = tokaor;          tonxor = tonxir + tpcg.tonxdr;        
             toadir = tonxor;          toador = toadir + tpcg.toaddr;        
             toigir = toador;          toigor = toigir + tpcg.toigdr;        
             toalir = toigor;          toalor = toalir + tpcg.toaldr;        
             tohair = toalor;          tohaor = tohair + tpcg.tohadr;        
             tifcir = tpcg.rmin      ;// inner field cage inner radius;        
             tiadir = tifcir;          tiador = tiadir + tpcg.tiaddr;        
             tinxir = tiador;          tinxor = tinxir + tpcg.tinxdr;        
             tikair = tinxor;          tikaor = tikair + tpcg.tikadr;        
             tialir = tikaor;          tialor = tialir + tpcg.tialdr;        
             tofcir = tocsir;          tofcor = tohaor;        
             tofsir = tocsir;          tofsor = toador;        
             tifcir = tiadir;          tifcor = tialor;        
             tpgvir = tifcor         ;// tpc gas inner radius;        
             del = tpcg.rmax-tofcor;        
             // Print<level=%i> fmt=%s fortran format statements not supported        
             if ( del<0 )        
             {           
                   // Print<level=%i> fmt=%s fortran format statements not supported           
             }        
             // Print<level=%i> fmt=%s fortran format statements not supported        
             AGSSTEP( tpcelaser );// CALL AGSSTEP        
             _create = AgCreate("TPCE");        
             {           
                   AgShape myshape; // undefined shape           
                   ///Create TPCE           
                   Create("TPCE");            
             }        
             { AgPlacement place = AgPlacement("TPCE","CAVE");           
                   /// Add daughter volume TPCE to mother CAVE           
                   _stacker -> Position( AgBlock::Find("TPCE"), place );           
             } // end placement of TPCE        
       }; // TpceGeo1     
 }; // namespace TpceGeo1  
 