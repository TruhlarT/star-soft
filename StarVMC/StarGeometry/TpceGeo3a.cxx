#include "TpceGeo3a.h"  
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
 namespace TPCEGEO3A // $NMSPC  
 {     
       //     
       // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                TString voluname;        
                //        
                /// TString voluname        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t tsas_zoffset=0.0,tsgt_zoffset=0.0;        
                //        
                /// Float_t tsas_zoffset=0.0,tsgt_zoffset=0.0        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Int_t kinner,kouter;        
                //        
                /// Int_t kinner,kouter        
          ///@}     
          /* Export block
///@addtogroup TpceGeo3a_vars
*/     
          /* Export block
///@{
*/        
                /* Export block
Float_t inch,cm;
*/        
                /* Export block
//
*/        
                /* Export block
/// Float_t inch,cm
*/        
          /* Export block
///@}
*/     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Int_t kblack,kred,kgreen,kblue,kyellow,kviolet,klightblue;        
                //        
                /// Int_t kblack,kred,kgreen,kblue,kyellow,kviolet,klightblue        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Int_t kbbox,kpara,ktrd1,ishape;        
                //        
                /// Int_t kbbox,kpara,ktrd1,ishape        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                int mycount=0;        
                //        
                /// int mycount=0        
          ///@}     
          /* Export block
///@addtogroup TpceGeo3a_vars
*/     
          /* Export block
///@{
*/        
                /* Export block
Float_t sind,cosd,tand;
*/        
                /* Export block
//
*/        
                /* Export block
/// Float_t sind,cosd,tand
*/        
          /* Export block
///@}
*/     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t cos15,sin15,tan15;        
                //        
                /// Float_t cos15,sin15,tan15        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Int_t i,j,isecang,ncount=0,jtrib,kase;        
                //        
                /// Int_t i,j,isecang,ncount=0,jtrib,kase        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t x,x0,x1,x2,dx,dx1,dx2,xc;        
                //        
                /// Float_t x,x0,x1,x2,dx,dx1,dx2,xc        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t y,y0,y1,y2,dy,dy1,dy2;        
                //        
                /// Float_t y,y0,y1,y2,dy,dy1,dy2        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t z,z0,z1,z2,dz,dz1,dz2;        
                //        
                /// Float_t z,z0,z1,z2,dz,dz1,dz2        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t zbeg,zded,zpmt,zend;        
                //        
                /// Float_t zbeg,zded,zpmt,zend        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t r,r0,r1,r2,dr;        
                //        
                /// Float_t r,r0,r1,r2,dr        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t alpha,beta;        
                //        
                /// Float_t alpha,beta        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t xw,dxw,yw,dyw,zw,dzw,dydx;        
                //        
                /// Float_t xw,dxw,yw,dyw,zw,dzw,dydx        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t drsectorshift=0;        
                //        
                /// Float_t drsectorshift=0        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t mydx,mydy,mydz,myalph,mythet,myphi;        
                //        
                /// Float_t mydx,mydy,mydz,myalph,mythet,myphi        
                Array_t<Float_t> mypar(20);        
                /// mypar(20) : array of Float_t        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t tocsir,tocsor,tokair,tokaor,tonxir,tonxor,toadir,toador,toigir,toigor;        
                //        
                /// Float_t tocsir,tocsor,tokair,tokaor,tonxir,tonxor,toadir,toador,toigir,toigor        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t toalir,toalor,tohair,tohaor,toalir2,toalor2,tofcir,tofcor,tofsir,tofsor;        
                //        
                /// Float_t toalir,toalor,tohair,tohaor,toalir2,toalor2,tofcir,tofcor,tofsir,tofsor        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t tifcir,tialir,tialor,tikair,tikaor,tinxir,tinxor,tiadir,tiador,tifcor;        
                //        
                /// Float_t tifcir,tialir,tialor,tikair,tikaor,tinxir,tinxor,tiadir,tiador,tifcor        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t tpgvleng,tofcleng,tpgvz;        
                //        
                /// Float_t tpgvleng,tofcleng,tpgvz        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Int_t i_sec,i_row;        
                //        
                /// Int_t i_sec,i_row        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t tpgvir;        
                //        
                /// Float_t tpgvir        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t del;        
                //        
                /// Float_t del        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t zwheel1,ztofcend,ztifcend,ztifcflangebegin;        
                //        
                /// Float_t zwheel1,ztofcend,ztifcend,ztifcflangebegin        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> qwe(10);        
                /// qwe(10) : array of Float_t        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> xholes(1);        
                /// xholes : array of Float_t : low=0 upper=15        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> width1iof(2);        
                /// width1iof(2) : array of Float_t        
                Array_t<Float_t> width2iof(2);        
                /// width2iof(2) : array of Float_t        
                Array_t<Float_t> heightiof(2);        
                /// heightiof(2) : array of Float_t        
                Array_t<Float_t> depthiof(2);        
                /// depthiof(2) : array of Float_t        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Int_t inout;        
                //        
                /// Int_t inout        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> zzzsa(2);        
                /// zzzsa(2) : array of Float_t        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> rmnsa(1);        
                /// rmnsa : array of Float_t : low=0 upper=1        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> rmxsa(1);        
                /// rmxsa : array of Float_t : low=0 upper=1        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> zzzwa(2);        
                /// zzzwa(2) : array of Float_t        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> rmnwa(1);        
                /// rmnwa : array of Float_t : low=0 upper=1        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> rmxwa(1);        
                /// rmxwa : array of Float_t : low=0 upper=1        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> zzzrdo(2);        
                /// zzzrdo(2) : array of Float_t        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> rmnrdo(2);        
                /// rmnrdo(2) : array of Float_t        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> rmxrdo(2);        
                /// rmxrdo(2) : array of Float_t        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t mycos,myrmin,myrmax,myg1,myg2;        
                //        
                /// Float_t mycos,myrmin,myrmax,myg1,myg2        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Array_t<Float_t> drdocooling(1);        
                /// drdocooling : array of Float_t : low=0 upper=7        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Float_t rcoolingtube=123456789;        
                //        
                /// Float_t rcoolingtube=123456789        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                TString mysha;        
                //        
                /// TString mysha        
          ///@}     
          ///@addtogroup TpceGeo3a_vars     
          ///@{        
                Int_t icoo,icab,jcoo,irib,itals,jtals;        
                //        
                /// Int_t icoo,icab,jcoo,irib,itals,jtals        
          ///@}     
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
          ///Float_t rminifc;     
          ///Float_t lengtht;     
          ///Float_t length;     
          ///Float_t lengthw;     
          ///Float_t lengthv;     
          ///Float_t dzenvelop;     
          ///Float_t wheelir;     
          ///Float_t wheelr0;     
          ///Float_t wheelr1;     
          ///Float_t wheelr2;     
          ///Float_t wheeltotalribwidth;     
          ///Float_t wheelribwidth;     
          ///Float_t wheelribheight;     
          ///Float_t wheelboxdx;     
          ///Float_t wheelboxdy;     
          ///Float_t wheelor1;     
          ///Float_t wheelor;     
          ///Float_t wheelthk1;     
          ///Float_t wheelthk;     
          ///Float_t sengasor;     
          ///Float_t membthk;     
          ///Float_t tocsdr;     
          ///Float_t tokadr;     
          ///Float_t tonxdr;     
          ///Float_t toaddr;     
          ///Float_t toigdr;     
          ///Float_t toaldr;     
          ///Float_t tohadr;     
          ///Float_t tiaddr;     
          ///Float_t tinxdr;     
          ///Float_t tikadr;     
          ///Float_t tialdr;     
          ///Float_t tifcrf;     
          ///Float_t tifcdrt;     
          ///Float_t dzyf1;     
          ///Float_t dzyf2;     
          ///Float_t dzyf3;     
          ///Float_t padplanethickness;     
          ///Float_t dgateground;     
          ///Float_t wiremountwidth;     
          ///Float_t wiremountheight;     
          ///Float_t dxrdo;     
          ///Float_t dyrdo;     
          ///Float_t dzrdo;     
          ///Float_t zrdo;     
          ///Float_t heigtube;     
          ///Float_t widtube;     
          ///Float_t rdocoolingdx;     
          ///Float_t rdocoolingdy;     
          ///Float_t rdocoolingdz;     
          ///Float_t zgatinggrid;     
          ///Float_t zgroundgrid;     
          ///Float_t deadzone;     
          ///Array_t<Float_t> danode;     
          ///Int_t _index;     
          //     
          Tpcg_t tpcg;     
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
          ///Float_t danode;     
          ///Array_t<Float_t> rpads;     
          ///Array_t<Float_t> npads;     
          ///Int_t _index;     
          //     
          Tprs_t tprs;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup tecw_doc     
          /// \class Tecw_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t sec;     
          ///Float_t gapwidi;     
          ///Float_t gapwido;     
          ///Float_t gapheit;     
          ///Float_t gaprad;     
          ///Float_t inwidth;     
          ///Float_t ouwidth;     
          ///Float_t widthlip;     
          ///Float_t noribs;     
          ///Float_t zsteprib;     
          ///Float_t widthrib;     
          ///Float_t height;     
          ///Float_t thick;     
          ///Float_t thickal;     
          ///Float_t rmin;     
          ///Float_t rcenter;     
          ///Float_t holedx;     
          ///Float_t holedy;     
          ///Int_t _index;     
          //     
          Tecw_t tecw;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup tpcr_doc     
          /// \class Tpcr_t     
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
          Tpcr_t tpcr;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup tfee_doc     
          /// \class Tfee_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t vers;     
          ///Float_t carddx;     
          ///Float_t carddy;     
          ///Float_t carddz;     
          ///Float_t platedx;     
          ///Float_t platedy;     
          ///Float_t platedz;     
          ///Float_t assemblythickness;     
          ///Float_t ribdx;     
          ///Float_t ribdy;     
          ///Float_t ribdz;     
          ///Array_t<Float_t> ass;     
          ///Int_t _index;     
          //     
          Tfee_t tfee;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup ribs_doc     
          /// \class Ribs_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Float_t version;     
          ///Float_t inout;     
          ///Float_t num;     
          ///Array_t<Float_t> x;     
          ///Array_t<Float_t> dx;     
          ///Array_t<Float_t> y;     
          ///Array_t<Float_t> dy;     
          ///Int_t _index;     
          //     
          Ribs_t ribs;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup holz_doc     
          /// \class Holz_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Int_t inout;     
          ///Int_t numberofrows;     
          ///Array_t<Int_t> numberperrow;     
          ///Array_t<Float_t> yholes;     
          ///Int_t _index;     
          //     
          Holz_t holz;     
          //     
          //  -----------------------------------------------------     
          /// @defgroup cool_doc     
          /// \class Cool_t     
          /// \brief User-defined structure     
          ///                             
          /// AgML structure members:     
          ///                             
          ///Int_t inout;     
          ///Array_t<Float_t> tubelength;     
          ///Int_t _index;     
          //     
          Cool_t cool;     
          //     
       TpceGeo3a::TpceGeo3a()     
         : AgModule("TpceGeo3a","  is the updated TPC ")     
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
                            attr.par("colo")=kred;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tpcg.rmin;              
                            shape.par("rmax")=tpcg.rmax;              
                            shape.par("dz")=tpcg.dzenvelop;              
                            /// Shape Tube rmin=tpcg.rmin rmax=tpcg.rmax dz=tpcg.dzenvelop               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TPCE;              
                            _stacker -> Build(this);              
                      }           
                      // Print<level=%i> fmt=%s fortran format statements not supported           
                      tpgvz  = (tpcg.membthk + tpgvleng)/2;           
                      zwheel1  = tpcg.lengthw/2 - tpcg.wheelthk;;           
                      ztofcend = tpcg.lengthw/2 - tpcg.wheelthk1;;           
                      ztifcend = tpcg.lengthw/2 + 0.97;;           
                      ztifcflangebegin = ztifcend - 1*inch;;           
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
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
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
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
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
                      /// Loop on isecang from 0 to 360-30 step=30           
                      for ( isecang=0; (30>0)? (isecang<=360-30):(isecang>=360-30); isecang+=30 )           
                      {              
                            _create = AgCreate("TSWH");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TSWH                 
                                  Create("TSWH");                  
                            }              
                            { AgPlacement place = AgPlacement("TSWH","TPCE");                 
                                  /// Add daughter volume TSWH to mother TPCE                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaZ(isecang);                 
                                  /// Rotate: AlphaZ = isecang                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("TSWH"), place );                 
                            } // end placement of TSWH              
                            _create = AgCreate("TSWH");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TSWH                 
                                  Create("TSWH");                  
                            }              
                            { AgPlacement place = AgPlacement("TSWH","TPCE");                 
                                  /// Add daughter volume TSWH to mother TPCE                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "XY-Z" ); // ORT=XY-Z                 
                                  /// Axis substitution: XYZ --> XY-Z                 
                                  place.AlphaZ(isecang);                 
                                  /// Rotate: AlphaZ = isecang                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("TSWH"), place );                 
                            } // end placement of TSWH              
                      }           
                      END_OF_TPCE:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPCE     
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
                            attr.par("colo")=kblue;              
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
          void TIFC::Block( AgCreate create )     
          {         
                ///@addtogroup TIFC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TIFC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kblue;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("nz")=6;              
                            shape.Z(0)=-ztifcend;              
                            shape.Z(1)=-ztifcflangebegin;              
                            shape.Z(2)=-ztifcflangebegin;              
                            shape.Z(3)=ztifcflangebegin;              
                            shape.Z(4)=ztifcflangebegin;              
                            shape.Z(5)=ztifcend;              
                            shape.Rmin(0)=tifcir;              
                            shape.Rmin(1)=tifcir;              
                            shape.Rmin(2)=tifcir;              
                            shape.Rmin(3)=tifcir;              
                            shape.Rmin(4)=tifcir;              
                            shape.Rmin(5)=tifcir;              
                            shape.Rmax(0)=tpcg.tifcrf;              
                            shape.Rmax(1)=tpcg.tifcrf;              
                            shape.Rmax(2)=tifcor;              
                            shape.Rmax(3)=tifcor;              
                            shape.Rmax(4)=tpcg.tifcrf;              
                            shape.Rmax(5)=tpcg.tifcrf;              
                            /// Shape Pcon phi1=0 dphi=360 nz=6               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TIFC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TIKA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TIKA              
                            Create("TIKA");               
                      }           
                      { AgPlacement place = AgPlacement("TIKA","TIFC");              
                            /// Add daughter volume TIKA to mother TIFC              
                            _stacker -> Position( AgBlock::Find("TIKA"), place );              
                      } // end placement of TIKA           
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
                      _create = AgCreate("TIAD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TIAD              
                            Create("TIAD");               
                      }           
                      { AgPlacement place = AgPlacement("TIAD","TIFC");              
                            /// Add daughter volume TIAD to mother TIFC              
                            _stacker -> Position( AgBlock::Find("TIAD"), place );              
                      } // end placement of TIAD           
                      END_OF_TIFC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TIFC     
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
                            attr.par("colo")=kviolet;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tikair;              
                            shape.par("rmax")=tikaor;              
                            shape.par("dz")=tpcg.dzyf1;              
                            /// Shape Tube rmin=tikair rmax=tikaor dz=tpcg.dzyf1               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TIKA;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TIKA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TIKA     
          // ---------------------------------------------------------------------------------------------------     
          void TINX::Block( AgCreate create )     
          {         
                ///@addtogroup TINX_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material Nomex            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Nomex");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TINX");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kyellow;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tinxir;              
                            shape.par("rmax")=tinxor;              
                            shape.par("dz")=tpcg.dzyf1;              
                            /// Shape Tube rmin=tinxir rmax=tinxor dz=tpcg.dzyf1               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TINX;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TINX:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TINX     
          // ---------------------------------------------------------------------------------------------------     
          void TIAD::Block( AgCreate create )     
          {         
                ///@addtogroup TIAD_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material ADHESIVE            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Adhesive");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TIKA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kviolet;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tiadir;              
                            shape.par("rmax")=tiador;              
                            shape.par("dz")=tpcg.dzyf1;              
                            /// Shape Tube rmin=tiadir rmax=tiador dz=tpcg.dzyf1               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TIAD;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TIAD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TIAD     
          // ---------------------------------------------------------------------------------------------------     
          void TOFC::Block( AgCreate create )     
          {         
                ///@addtogroup TOFC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TOFC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kgreen;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("nz")=6;              
                            shape.Z(0)=-ztofcend;              
                            shape.Z(1)=-zwheel1;              
                            shape.Z(2)=-zwheel1;              
                            shape.Z(3)=zwheel1;              
                            shape.Z(4)=zwheel1;              
                            shape.Z(5)=ztofcend;              
                            shape.Rmin(0)=tpcg.wheelor1;              
                            shape.Rmin(1)=tpcg.wheelor1;              
                            shape.Rmin(2)=tofcir;              
                            shape.Rmin(3)=tofcir;              
                            shape.Rmin(4)=tpcg.wheelor1;              
                            shape.Rmin(5)=tpcg.wheelor1;              
                            shape.Rmax(0)=tpcg.wheelor;              
                            shape.Rmax(1)=tpcg.wheelor;              
                            shape.Rmax(2)=tofcor;              
                            shape.Rmax(3)=tofcor;              
                            shape.Rmax(4)=tpcg.wheelor;              
                            shape.Rmax(5)=tpcg.wheelor;              
                            /// Shape Pcon phi1=0 dphi=360 nz=6               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOFC;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TOAD");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOAD              
                            Create("TOAD");               
                      }           
                      { AgPlacement place = AgPlacement("TOAD","TOFC");              
                            /// Add daughter volume TOAD to mother TOFC              
                            _stacker -> Position( AgBlock::Find("TOAD"), place );              
                      } // end placement of TOAD           
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
                      _create = AgCreate("TOKA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOKA              
                            Create("TOKA");               
                      }           
                      { AgPlacement place = AgPlacement("TOKA","TOFC");              
                            /// Add daughter volume TOKA to mother TOFC              
                            _stacker -> Position( AgBlock::Find("TOKA"), place );              
                      } // end placement of TOKA           
                      _create = AgCreate("TONX");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TONX              
                            Create("TONX");               
                      }           
                      { AgPlacement place = AgPlacement("TONX","TOFC");              
                            /// Add daughter volume TONX to mother TOFC              
                            _stacker -> Position( AgBlock::Find("TONX"), place );              
                      } // end placement of TONX           
                      _create = AgCreate("TOIG");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOIG              
                            Create("TOIG");               
                      }           
                      { AgPlacement place = AgPlacement("TOIG","TOFC");              
                            /// Add daughter volume TOIG to mother TOFC              
                            _stacker -> Position( AgBlock::Find("TOIG"), place );              
                      } // end placement of TOIG           
                      _create = AgCreate("TOHA");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TOHA              
                            Create("TOHA");               
                      }           
                      { AgPlacement place = AgPlacement("TOHA","TOFC");              
                            /// Add daughter volume TOHA to mother TOFC              
                            _stacker -> Position( AgBlock::Find("TOHA"), place );              
                      } // end placement of TOHA           
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
                      /// Medium TOFS_copper           
                      ///  ifield = 1           
                      ///  fieldm = 20           
                      ///  tmaxfd = 20           
                      ///  epsil = 0.01           
                      ///  stemax = 10           
                      ///  deemax = 0.25           
                      ///  stmin = 0.0281386           
                      ///  isvol = 0           
                      {  AgMedium &med = AgMedium::Get("Tofs_copper");              
                               med.Inherit(this);              
                            med.par("ifield")=1;              
                            med.par("fieldm")=20;              
                            med.par("tmaxfd")=20;              
                            med.par("epsil")=0.01;              
                            med.par("stemax")=10;              
                            med.par("deemax")=0.25;              
                            med.par("stmin")=0.0281386;              
                            med.par("isvol")=0;              
                            _medium = med;              
                      }           
                      { AgAttribute attr = AgAttribute("TOFS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kblue;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tocsir;              
                            shape.par("rmax")=tocsor;              
                            shape.par("dz")=tpcg.dzyf2;              
                            /// Shape Tube rmin=tocsir rmax=tocsor dz=tpcg.dzyf2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOFS;              
                            _stacker -> Build(this);              
                      }           
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
                            attr.par("colo")=kgreen;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tokair;              
                            shape.par("rmax")=tokaor;              
                            shape.par("dz")=tpcg.dzyf2;              
                            /// Shape Tube rmin=tokair rmax=tokaor dz=tpcg.dzyf2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOKA;              
                            _stacker -> Build(this);              
                      }           
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
                            attr.par("colo")=kred;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=0;              
                            shape.par("dphi")=360;              
                            shape.par("nz")=6;              
                            shape.Z(0)=-tpcg.dzyf2;              
                            shape.Z(1)=-tpcg.dzyf3;              
                            shape.Z(2)=-tpcg.dzyf3;              
                            shape.Z(3)=tpcg.dzyf3;              
                            shape.Z(4)=tpcg.dzyf3;              
                            shape.Z(5)=tpcg.dzyf2;              
                            shape.Rmin(0)=tonxor-0.2;              
                            shape.Rmin(1)=tonxor-0.2;              
                            shape.Rmin(2)=tonxir;              
                            shape.Rmin(3)=tonxir;              
                            shape.Rmin(4)=tonxor-0.2;              
                            shape.Rmin(5)=tonxor-0.2;              
                            shape.Rmax(0)=tonxor;              
                            shape.Rmax(1)=tonxor;              
                            shape.Rmax(2)=tonxor;              
                            shape.Rmax(3)=tonxor;              
                            shape.Rmax(4)=tonxor;              
                            shape.Rmax(5)=tonxor;              
                            /// Shape Pcon phi1=0 dphi=360 nz=6               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TONX;              
                            _stacker -> Build(this);              
                      }           
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
                            attr.par("colo")=klightblue;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=toadir;              
                            shape.par("rmax")=toador;              
                            shape.par("dz")=tpcg.dzyf2;              
                            /// Shape Tube rmin=toadir rmax=toador dz=tpcg.dzyf2               
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
          void TOIG::Block( AgCreate create )     
          {         
                ///@addtogroup TOIG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material NITROGEN_GAS            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Nitrogen_gas");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TOAD");              
                            attr.par("seen")=1;              
                            attr.par("colo")=klightblue;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=toigir;              
                            shape.par("rmax")=toigor;              
                            shape.par("dz")=tpcg.dzyf2;              
                            /// Shape Tube rmin=toigir rmax=toigor dz=tpcg.dzyf2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TOIG;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TOIG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TOIG     
          // ---------------------------------------------------------------------------------------------------     
          void TOHA::Block( AgCreate create )     
          {         
                ///@addtogroup TOHA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material AL_HONEYCOMB            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Al_honeycomb");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("TOHA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kviolet;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tube");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("rmin")=tohair;              
                            shape.par("rmax")=tohaor;              
                            shape.par("dz")=tpcg.dzyf3;              
                            /// Shape Tube rmin=tohair rmax=tohaor dz=tpcg.dzyf3               
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
          void TSWH::Block( AgCreate create )     
          {         
                ///@addtogroup TSWH_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Medium STANDARD           
                      {  AgMedium med = AgMedium::CopyMedium("Standard");              
                            _medium = med;              
                      }           
                      { AgAttribute attr = AgAttribute("TSWH");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kviolet;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("nz")=8;              
                            shape.Z(0)=tpcg.membthk/2;              
                            shape.Z(1)=zwheel1;              
                            shape.Z(2)=zwheel1;              
                            shape.Z(3)=ztofcend;              
                            shape.Z(4)=ztofcend;              
                            shape.Z(5)=ztifcflangebegin;              
                            shape.Z(6)=ztifcflangebegin;              
                            shape.Z(7)=tpcg.dzenvelop;              
                            shape.Rmin(0)=tifcor;              
                            shape.Rmin(1)=tifcor;              
                            shape.Rmin(2)=tifcor;              
                            shape.Rmin(3)=tifcor;              
                            shape.Rmin(4)=tifcor;              
                            shape.Rmin(5)=tpcg.tifcrf+tpcg.tifcdrt;              
                            shape.Rmin(6)=tpcg.tifcrf+tpcg.tifcdrt;              
                            shape.Rmin(7)=tpcg.tifcrf+tpcg.tifcdrt;              
                            shape.Rmax(0)=tofcir;              
                            shape.Rmax(1)=tofcir;              
                            shape.Rmax(2)=tpcg.wheelor1;              
                            shape.Rmax(3)=tpcg.wheelor1;              
                            shape.Rmax(4)=tpcg.wheelor;              
                            shape.Rmax(5)=tpcg.wheelor;              
                            shape.Rmax(6)=tpcg.wheelor;              
                            shape.Rmax(7)=tpcg.wheelor;              
                            /// Shape Pcon phi1=-15 dphi=30 nz=8               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TSWH;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("TSAW");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TSAW              
                            Create("TSAW");               
                      }           
                      { AgPlacement place = AgPlacement("TSAW","TSWH");              
                            /// Add daughter volume TSAW to mother TSWH              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("TSAW"), place );              
                      } // end placement of TSAW           
                      END_OF_TSWH:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TSWH     
          // ---------------------------------------------------------------------------------------------------     
          void TSAW::Block( AgCreate create )     
          {         
                ///@addtogroup TSAW_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Medium STANDARD           
                      {  AgMedium med = AgMedium::CopyMedium("Standard");              
                            _medium = med;              
                      }           
                      { AgAttribute attr = AgAttribute("TSAW");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kyellow;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("nz")=2;              
                            shape.Z(0)=204;              
                            shape.Z(1)=tpcg.dzenvelop-tpcg.membthk/2;              
                            shape.Rmin(0)=48;              
                            shape.Rmin(1)=48;              
                            shape.Rmax(0)=208;              
                            shape.Rmax(1)=208;              
                            /// Shape Pcon phi1=-15 dphi=30 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TSAW;              
                            _stacker -> Build(this);              
                      }           
                      dx2 = 1.470;           
                      dx  = 0;           
                      /// USE tecw sec=1;           
                      tecw.Use("sec",(Float_t)1);           
                      /// Loop on inout from kinner to kouter step=1           
                      for ( inout=kinner; (1>0)? (inout<=kouter):(inout>=kouter); inout+=1 )           
                      {              
                            mycount = 0;;              
                            /// USE cool inout=inout ;              
                            cool.Use("inout",(Int_t)inout );              
                            /// USE ribs inout=inout ;              
                            ribs.Use("inout",(Float_t)inout );              
                            /// USE holz inout=inout ;              
                            holz.Use("inout",(Int_t)inout );              
                            /// USE tecw sec=(inout+1) ;              
                            tecw.Use("sec",(Float_t)(inout+1) );              
                            z2 = zwheel1;              
                            z1 = z2 - tecw.thick;              
                            z  = (z1 + tpcg.membthk/2)/2;              
                            dz = (z1 - tpcg.membthk/2)/2;              
                            x1 = -tecw.height/2;              
                            x2 =  tecw.height/2;              
                            y1 =  tecw.inwidth/2;              
                            y2 =  tecw.ouwidth/2;              
                            x0 =  (y1*x2-y2*x1)/(x2-x1);              
                            dydx  =  (y2 - y1)/(x2 - x1);              
                            alpha = 180./pi*atan(dydx);              
                            r1 = y1/dydx;              
                            r2 = y2/dydx;              
                            drsectorshift = tecw.rmin - r1;              
                            if ( inout==kinner )              
                            {                 
                                  xholes(0) = r2 - 1.988*inch;                 
                                  /// Loop on i from 1 to holz.numberofrows-1 step=1                 
                                  for ( i=1; (1>0)? (i<=holz.numberofrows-1):(i>=holz.numberofrows-1); i+=1 )                 
                                  {                    
                                        xholes(i) = xholes(i-1) - 1.575*inch;                    
                                  }                 
                            }              
                            else              
                            {                 
                                  /// Loop on i from 0 to holz.numberofrows - 1 step=1                 
                                  for ( i=0; (1>0)? (i<=holz.numberofrows - 1):(i>=holz.numberofrows - 1); i+=1 )                 
                                  {                    
                                        xholes(i) = r2 - (1.988 + 1.575*i)*inch;                    
                                  }                 
                            }              
                            _create = AgCreate("TSAS");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TSAS                 
                                  Create("TSAS");                  
                            }              
                            { AgPlacement place = AgPlacement("TSAS","TSAW");                 
                                  /// Add daughter volume TSAS to mother TSAW                 
                                  place.TranslateZ(tsas_zoffset);                 
                                  /// Translate z = tsas_zoffset                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  _stacker -> Position( AgBlock::Find("TSAS"), place );                 
                            } // end placement of TSAS              
                            _create = AgCreate("TWAS");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TWAS                 
                                  Create("TWAS");                  
                            }              
                            { AgPlacement place = AgPlacement("TWAS","TSAW");                 
                                  /// Add daughter volume TWAS to mother TSAW                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  _stacker -> Position( AgBlock::Find("TWAS"), place );                 
                            } // end placement of TWAS              
                            if ( inout==0 )              
                            {                 
                                  _create = AgCreate("TBRW");                 
                                  {                    
                                        AgShape myshape; // undefined shape                    
                                        ///Create TBRW                    
                                        Create("TBRW");                     
                                  }                 
                                  { AgPlacement place = AgPlacement("TBRW","TSAW");                    
                                        /// Add daughter volume TBRW to mother TSAW                    
                                        place.TranslateX(tpcg.wheelr1);                    
                                        /// Translate x = tpcg.wheelr1                    
                                        place.TranslateZ(zwheel1+tpcg.wheelthk/2);                    
                                        /// Translate z = zwheel1+tpcg.wheelthk/2                    
                                        _stacker -> Position( AgBlock::Find("TBRW"), place );                    
                                  } // end placement of TBRW                 
                            }              
                            x1 = tpcg.wheelr0*cos15;              
                            x2 = tpcg.wheelr2;              
                            dz = tpcg.wheelribheight/2;              
                            z  = zwheel1 + dz;              
                            dx = (x2 - x1)/2;              
                            dy = tpcg.wheeltotalribwidth/4;              
                            x  = (x1 + x2)/2;              
                            y  = (x *tan15 - dy)*(2*inout-1);              
                            mydx=dy; mydy=dx; mydz=dz; myalph=-(1-2*inout)*15;              
                            _create = AgCreate("TWRB");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TWRB                 
                                  Create("TWRB");                  
                            }              
                            { AgPlacement place = AgPlacement("TWRB","TSAW");                 
                                  /// Add daughter volume TWRB to mother TSAW                 
                                  place.TranslateX(x);                 
                                  /// Translate x = x                 
                                  place.TranslateY(y);                 
                                  /// Translate y = y                 
                                  place.TranslateZ(z);                 
                                  /// Translate z = z                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YX-Z" ); // ORT=YX-Z                 
                                  /// Axis substitution: XYZ --> YX-Z                 
                                  _stacker -> Position( AgBlock::Find("TWRB"), place );                 
                            } // end placement of TWRB              
                            dz = tpcg.wheelthk/2;              
                            z  = zwheel1 + dz;              
                            dy = tpcg.wheelribwidth/4;              
                            x  = (x1 + x2)/2;              
                            y  = (x *tan15 - dy)*(2*inout-1);              
                            mydx=dy; mydy=dx; mydz=dz; myalph=-(1-2*inout)*15;              
                            _create = AgCreate("TWRB");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TWRB                 
                                  Create("TWRB");                  
                            }              
                            { AgPlacement place = AgPlacement("TWRB","TSAW");                 
                                  /// Add daughter volume TWRB to mother TSAW                 
                                  place.TranslateX(x);                 
                                  /// Translate x = x                 
                                  place.TranslateY(y);                 
                                  /// Translate y = y                 
                                  place.TranslateZ(z);                 
                                  /// Translate z = z                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YX-Z" ); // ORT=YX-Z                 
                                  /// Axis substitution: XYZ --> YX-Z                 
                                  _stacker -> Position( AgBlock::Find("TWRB"), place );                 
                            } // end placement of TWRB              
                      }           
                      /// Loop on alpha from -15 to 15 step=30           
                      for ( alpha=-15; (30>0)? (alpha<=15):(alpha>=15); alpha+=30 )           
                      {              
                            /// Loop on j from 0 to 3 step=1              
                            for ( j=0; (1>0)? (j<=3):(j>=3); j+=1 )              
                            {                 
                                  if ( (j==0) )                 
                                  {                    
                                        r = tpcg.wheelr2 - 1.5/8.5*(tpcg.wheelr2 - tpcg.wheelr1);                    
                                  }                 
                                  if ( (j==1) )                 
                                  {                    
                                        r = tpcg.wheelr2 - 6.5/8.5*(tpcg.wheelr2 - tpcg.wheelr1);                    
                                  }                 
                                  if ( (j==2) )                 
                                  {                    
                                        r = tpcg.wheelr1 - 2.0/8.5*(tpcg.wheelr1 - tpcg.wheelr0);                    
                                  }                 
                                  if ( (j==3) )                 
                                  {                    
                                        r = tpcg.wheelr1 - 7.0/8.5*(tpcg.wheelr1 - tpcg.wheelr0);                    
                                  }                 
                                  x = r;                 
                                  y = r *tand(alpha);                 
                                  { AgPlacement place = AgPlacement("TBRW","TSAW");                    
                                        /// Add daughter volume TBRW to mother TSAW                    
                                        place.TranslateX(x);                    
                                        /// Translate x = x                    
                                        place.TranslateY(y);                    
                                        /// Translate y = y                    
                                        place.TranslateZ(zwheel1+tpcg.wheelthk/2);                    
                                        /// Translate z = zwheel1+tpcg.wheelthk/2                    
                                        place.AlphaZ(alpha);                    
                                        /// Rotate: AlphaZ = alpha                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        _stacker -> Position( AgBlock::Find("TBRW"), place );                    
                                  } // end placement of TBRW                 
                                  mycount+=1;;                 
                            }              
                            qwe(1) = -qwe(1);              
                            qwe(2) = -qwe(2);              
                      }           
                      _create = AgCreate("TWBT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TWBT              
                            Create("TWBT");               
                      }           
                      { AgPlacement place = AgPlacement("TWBT","TSAW");              
                            /// Add daughter volume TWBT to mother TSAW              
                            _stacker -> Position( AgBlock::Find("TWBT"), place );              
                      } // end placement of TWBT           
                      _create = AgCreate("TWRI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TWRI              
                            Create("TWRI");               
                      }           
                      { AgPlacement place = AgPlacement("TWRI","TSAW");              
                            /// Add daughter volume TWRI to mother TSAW              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("TWRI"), place );              
                      } // end placement of TWRI           
                      _create = AgCreate("TWTR");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TWTR              
                            Create("TWTR");               
                      }           
                      { AgPlacement place = AgPlacement("TWTR","TSAW");              
                            /// Add daughter volume TWTR to mother TSAW              
                            _stacker -> Position( AgBlock::Find("TWTR"), place );              
                      } // end placement of TWTR           
                      _create = AgCreate("TWMR");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TWMR              
                            Create("TWMR");               
                      }           
                      { AgPlacement place = AgPlacement("TWMR","TSAW");              
                            /// Add daughter volume TWMR to mother TSAW              
                            _stacker -> Position( AgBlock::Find("TWMR"), place );              
                      } // end placement of TWMR           
                      _create = AgCreate("TRDO");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TRDO              
                            Create("TRDO");               
                      }           
                      { AgPlacement place = AgPlacement("TRDO","TSAW");              
                            /// Add daughter volume TRDO to mother TSAW              
                            place.par("only")=AgPlacement::kMany;              
                            /// Overlap: agplacement::kmany              
                            _stacker -> Position( AgBlock::Find("TRDO"), place );              
                      } // end placement of TRDO           
                      rcoolingtube = tpcg.wheelr2 - tpcg.heigtube - 2*tpcg.dxrdo;           
                      /// Loop on icoo from 0 to 7 step=1           
                      for ( icoo=0; (1>0)? (icoo<=7):(icoo>=7); icoo+=1 )           
                      {              
                            dz = tpcg.heigtube*cm/2;              
                            dy = tpcg.widtube *cm/2;              
                            z  = rcoolingtube;              
                            dx1 = (z-dz)*tan15 - 2*tpcg.rdocoolingdy;              
                            dx2 = (z+dz)*tan15 - 2*tpcg.rdocoolingdy;              
                            ishape = ktrd1;;              
                            mypar.at(0) = dx1;              
                            mypar.at(1) = dx2;              
                            mypar.at(2) = dy;              
                            mypar.at(3) = dz;              
                            _create = AgCreate("TCOO");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TCOO                 
                                  Create("TCOO");                  
                            }              
                            { AgPlacement place = AgPlacement("TCOO","TSAW");                 
                                  /// Add daughter volume TCOO to mother TSAW                 
                                  place.TranslateX(z);                 
                                  /// Translate x = z                 
                                  place.TranslateZ((tpcg.zrdo-2*dy));                 
                                  /// Translate z = (tpcg.zrdo-2*dy)                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YZX" ); // ORT=YZX                 
                                  /// Axis substitution: XYZ --> YZX                 
                                  _stacker -> Position( AgBlock::Find("TCOO"), place );                 
                            } // end placement of TCOO              
                            rcoolingtube -= drdocooling(icoo);              
                      }           
                      dz = 4.5;           
                      dy = 4.5/2;           
                      z  = tpcg.zrdo + tpcg.dzrdo + dz;           
                      x1 = tpcg.wheelr0;           
                      x2 = tpcg.wheelr2;           
                      dx = (x2 - x1)/2;           
                      x  = (x1 + x2)/2;           
                      /// Loop on icab from 0 to 1 step=1           
                      for ( icab=0; (1>0)? (icab<=1):(icab>=1); icab+=1 )           
                      {              
                            y  = - (x *tan15 - dy) * (1 - 2*icab);              
                            mypar.at(0) = dy;              
                            mypar.at(1) = dx;              
                            mypar.at(2) = dz;              
                            mypar.at(3) = -15*(1-2*icab);              
                            mypar.at(4) = 0;              
                            mypar.at(5) = 0;              
                            _create = AgCreate("TCAB");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TCAB                 
                                  Create("TCAB");                  
                            }              
                            { AgPlacement place = AgPlacement("TCAB","TSAW");                 
                                  /// Add daughter volume TCAB to mother TSAW                 
                                  place.TranslateX(x);                 
                                  /// Translate x = x                 
                                  place.TranslateY(y);                 
                                  /// Translate y = y                 
                                  place.TranslateZ(z);                 
                                  /// Translate z = z                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YX-Z" ); // ORT=YX-Z                 
                                  /// Axis substitution: XYZ --> YX-Z                 
                                  _stacker -> Position( AgBlock::Find("TCAB"), place );                 
                            } // end placement of TCAB              
                      }           
                      END_OF_TSAW:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TSAW     
          // ---------------------------------------------------------------------------------------------------     
          void TSAS::Block( AgCreate create )     
          {         
                ///@addtogroup TSAS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("npdiv")=1;              
                            shape.par("nz")=2;              
                            shape.Z(0)=zzzsa(1);              
                            shape.Z(1)=zzzsa(2);              
                            shape.Rmin(0)=rmnsa(inout);              
                            shape.Rmin(1)=rmnsa(inout);              
                            shape.Rmax(0)=rmxsa(inout);              
                            shape.Rmax(1)=rmxsa(inout);              
                            /// Shape Pgon phi1=-15 dphi=30 npdiv=1 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TSAS;              
                            _stacker -> Build(this);              
                      }           
                      { AgAttribute attr = AgAttribute("TSAS");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      _create = AgCreate("TALS");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TALS              
                            Create("TALS");               
                      }           
                      { AgPlacement place = AgPlacement("TALS","TSAS");              
                            /// Add daughter volume TALS to mother TSAS              
                            _stacker -> Position( AgBlock::Find("TALS"), place );              
                      } // end placement of TALS           
                      _create = AgCreate("TSGT");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TSGT              
                            Create("TSGT");               
                      }           
                      { AgPlacement place = AgPlacement("TSGT","TSAS");              
                            /// Add daughter volume TSGT to mother TSAS              
                            place.TranslateZ(tsgt_zoffset);              
                            /// Translate z = tsgt_zoffset              
                            _stacker -> Position( AgBlock::Find("TSGT"), place );              
                      } // end placement of TSGT           
                      dy = (r2 - r1)/2;           
                      y  = (r2 + r1)/2;           
                      dx = tecw.widthrib/2;           
                      dz = (tecw.thick - tpcg.padplanethickness - tecw.thickal)/2;           
                      z  = z2 - dz;           
                      dxw = tpcg.wiremountwidth/cos15/2;           
                      dzw = tpcg.wiremountheight/2;           
                      xw = 0;           
                      /// Loop on irib from 0 to 1 step=1           
                      for ( irib=0; (1>0)? (irib<=1):(irib>=1); irib+=1 )           
                      {              
                            ishape = kpara;;              
                            mypar.at(0) = dx;              
                            mypar.at(1) = dy;              
                            mypar.at(2) = dz;              
                            mypar.at(3) = -(1-2*irib)*alpha;              
                            _create = AgCreate("TRIB");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TRIB                 
                                  Create("TRIB");                  
                            }              
                            x  = ((y1 + y2)/2 - dx)*(1-2*irib);              
                            { AgPlacement place = AgPlacement("TRIB","TSAS");                 
                                  /// Add daughter volume TRIB to mother TSAS                 
                                  place.TranslateX(y);                 
                                  /// Translate x = y                 
                                  place.TranslateY(-x);                 
                                  /// Translate y = -x                 
                                  place.TranslateZ(z);                 
                                  /// Translate z = z                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YX-Z" ); // ORT=YX-Z                 
                                  /// Axis substitution: XYZ --> YX-Z                 
                                  _stacker -> Position( AgBlock::Find("TRIB"), place );                 
                            } // end placement of TRIB              
                            xw = ((y1 + y2)/2 -  dxw)*(1-2*irib);              
                            mypar.at(0) = dxw;              
                            mypar.at(1) = dy;              
                            mypar.at(2) = dzw;              
                            mypar.at(3) = -(1-2*irib)*alpha;              
                            mypar.at(4) = 0;              
                            mypar.at(5) = 0;              
                            _create = AgCreate("TWIR");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TWIR                 
                                  Create("TWIR");                  
                            }              
                            zw = z1 - dzw/2;              
                            { AgPlacement place = AgPlacement("TWIR","TSAS");                 
                                  /// Add daughter volume TWIR to mother TSAS                 
                                  place.TranslateX(y);                 
                                  /// Translate x = y                 
                                  place.TranslateY(-xw);                 
                                  /// Translate y = -xw                 
                                  place.TranslateZ(zw);                 
                                  /// Translate z = zw                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YX-Z" ); // ORT=YX-Z                 
                                  /// Axis substitution: XYZ --> YX-Z                 
                                  _stacker -> Position( AgBlock::Find("TWIR"), place );                 
                            } // end placement of TWIR              
                      }           
                      /// Loop on irib from 0 to tecw.noribs-1 step=1           
                      for ( irib=0; (1>0)? (irib<=tecw.noribs-1):(irib>=tecw.noribs-1); irib+=1 )           
                      {              
                            r   = r2 - ribs.x  (irib+1) * inch;              
                            y   =      ribs.y  (irib+1) * inch;              
                            dr  =      ribs.dx (irib+1) * inch;              
                            dy  =      ribs.dy (irib+1) * inch;              
                            if ( dy<1.e-7 )              
                            {                 
                                  dx2 =  r      *dydx - tecw.widthrib - 2*dxw; ;// tecw.widthlip;                 
                                  dx1 = (r - dr)*dydx - tecw.widthrib - 2*dxw; ;// tecw.widthlip;                 
                                  xc = r - tecw.zsteprib/2;                 
                                  ishape = ktrd1;;                 
                                  mypar.at(0) = dx1;                 
                                  mypar.at(1) = dx2;                 
                                  mypar.at(2) = dz;                 
                                  mypar.at(3) = dr/2;                 
                                  _create = AgCreate("TRIB");                 
                                  {                    
                                        AgShape myshape; // undefined shape                    
                                        ///Create TRIB                    
                                        Create("TRIB");                     
                                  }                 
                                  { AgPlacement place = AgPlacement("TRIB","TSAS");                    
                                        /// Add daughter volume TRIB to mother TSAS                    
                                        place.TranslateX(r-dr/2);                    
                                        /// Translate x = r-dr/2                    
                                        place.TranslateY(0);                    
                                        /// Translate y = 0                    
                                        place.TranslateZ(z2-dz);                    
                                        /// Translate z = z2-dz                    
                                        /// G3 Reference: thetax = 90                    
                                        /// G3 Reference: phix = 0                    
                                        /// G3 Reference: thetay = 90                    
                                        /// G3 Reference: phiy = 90                    
                                        /// G3 Reference: thetaz = 0                    
                                        /// G3 Reference: phiz = 0                    
                                        place.Ortho( "YZX" ); // ORT=YZX                    
                                        /// Axis substitution: XYZ --> YZX                    
                                        _stacker -> Position( AgBlock::Find("TRIB"), place );                    
                                  } // end placement of TRIB                 
                            }              
                            else              
                            {                 
                                  ishape = kbbox;;                 
                                  mypar.at(0) = dr/2;                 
                                  mypar.at(1) = dy/2;                 
                                  mypar.at(2) = dz;                 
                                  _create = AgCreate("TRIB");                 
                                  {                    
                                        AgShape myshape; // undefined shape                    
                                        ///Create TRIB                    
                                        Create("TRIB");                     
                                  }                 
                                  { AgPlacement place = AgPlacement("TRIB","TSAS");                    
                                        /// Add daughter volume TRIB to mother TSAS                    
                                        place.TranslateX(r);                    
                                        /// Translate x = r                    
                                        place.TranslateY(y);                    
                                        /// Translate y = y                    
                                        place.TranslateZ(z2-dz);                    
                                        /// Translate z = z2-dz                    
                                        _stacker -> Position( AgBlock::Find("TRIB"), place );                    
                                  } // end placement of TRIB                 
                            }              
                      }           
                      END_OF_TSAS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TSAS     
          // ---------------------------------------------------------------------------------------------------     
          void TWAS::Block( AgCreate create )     
          {         
                ///@addtogroup TWAS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TWAS");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("npdiv")=1;              
                            shape.par("nz")=2;              
                            shape.Z(0)=zzzwa(1);              
                            shape.Z(1)=zzzwa(2);              
                            shape.Rmin(0)=rmnwa(inout);              
                            shape.Rmin(1)=rmnwa(inout);              
                            shape.Rmax(0)=rmxwa(inout);              
                            shape.Rmax(1)=rmxwa(inout);              
                            /// Shape Pgon phi1=-15 dphi=30 npdiv=1 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWAS;              
                            _stacker -> Build(this);              
                      }           
                      dx =   tpcg.widtube*cm/2;           
                      dz =   depthiof(inout+1)/2;           
                      dy =   heightiof(inout+1)/2;           
                      y1 = - dy;           
                      y2 =   dy;           
                      x1 =  width1iof(inout+1)/2 - dx;           
                      x2 =  width2iof(inout+1)/2 - dx;           
                      x0 =  (y1*x2-y2*x1)/(y2-y1);           
                      dydx  =  (x2 - x1)/(y2 - y1);           
                      beta = 180./pi*atan(dydx);           
                      if ( (inout==kouter) )           
                      {              
                            dy -= 0.7;              
                      }           
                      y  = xholes(0) - dy;           
                      x = (x1 + x2)/2;           
                      /// Loop on icoo from 0 to 1 step=1           
                      for ( icoo=0; (1>0)? (icoo<=1):(icoo>=1); icoo+=1 )           
                      {              
                            mypar.at(0) = dx;              
                            mypar.at(1) = dy;              
                            mypar.at(2) = dz;              
                            mypar.at(3) = -(1-2*icoo)*beta;              
                            mypar.at(4) = 0;              
                            mypar.at(5) = 0;              
                            ishape = kpara;;              
                            _create = AgCreate("TCOO");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TCOO                 
                                  Create("TCOO");                  
                            }              
                            { AgPlacement place = AgPlacement("TCOO","TWAS");                 
                                  /// Add daughter volume TCOO to mother TWAS                 
                                  place.TranslateX(y);                 
                                  /// Translate x = y                 
                                  place.TranslateY(x*(2*icoo-1));                 
                                  /// Translate y = x*(2*icoo-1)                 
                                  place.TranslateZ(zwheel1+dz);                 
                                  /// Translate z = zwheel1+dz                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YX-Z" ); // ORT=YX-Z                 
                                  /// Axis substitution: XYZ --> YX-Z                 
                                  _stacker -> Position( AgBlock::Find("TCOO"), place );                 
                            } // end placement of TCOO              
                      }           
                      /// Loop on icoo from 0 to holz.numberofrows - 1 step=1           
                      for ( icoo=0; (1>0)? (icoo<=holz.numberofrows - 1):(icoo>=holz.numberofrows - 1); icoo+=1 )           
                      {              
                            x = xholes(icoo);         ;//// cm;              
                            dx = tpcg.heigtube*cm/2;              
                            dz = tpcg.widtube*cm/2;              
                            dy = cool.tubelength( icoo+1 )*inch / 2;              
                            if ( inout==kinner )              
                            {                 
                                  dy2 = dy + 2*dydx*dx;                 
                                  dy1 = dy;;                 
                            }              
                            else              
                            {                 
                                  dy2 = dy;                 
                                  dy1 = dy - 2*dydx*dx;                 
                            }              
                            ishape = ktrd1;;              
                            mypar.at(0) = dy1;              
                            mypar.at(1) = dy2;              
                            mypar.at(2) = dz;              
                            mypar.at(3) = dx;              
                            mypar(11) = x-dx-tfee.assemblythickness/2+drsectorshift;              
                            mypar(13) = zwheel1+dz;              
                            _create = AgCreate("TCOO");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TCOO                 
                                  Create("TCOO");                  
                            }              
                            { AgPlacement place = AgPlacement("TCOO","TWAS");                 
                                  /// Add daughter volume TCOO to mother TWAS                 
                                  place.TranslateX(mypar(11));                 
                                  /// Translate x = mypar(11)                 
                                  place.TranslateZ(mypar(13));                 
                                  /// Translate z = mypar(13)                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YZX" ); // ORT=YZX                 
                                  /// Axis substitution: XYZ --> YZX                 
                                  _stacker -> Position( AgBlock::Find("TCOO"), place );                 
                            } // end placement of TCOO              
                            /// Loop on jcoo from 0 to holz.numberperrow(icoo+1) - 1 step=1              
                            for ( jcoo=0; (1>0)? (jcoo<=holz.numberperrow(icoo+1) - 1):(jcoo>=holz.numberperrow(icoo+1) - 1); jcoo+=1 )              
                            {                 
                                  y = holz.yholes( 9*icoo + jcoo + 1 )*inch;                 
                                  _create = AgCreate("FEEA");                 
                                  {                    
                                        AgShape myshape; // undefined shape                    
                                        ///Create FEEA                    
                                        Create("FEEA");                     
                                  }                 
                                  { AgPlacement place = AgPlacement("FEEA","TWAS");                    
                                        /// Add daughter volume FEEA to mother TWAS                    
                                        place.TranslateX(x+tfee.assemblythickness/2+drsectorshift);                    
                                        /// Translate x = x+tfee.assemblythickness/2+drsectorshift                    
                                        place.TranslateY(y);                    
                                        /// Translate y = y                    
                                        place.TranslateZ(zwheel1+2*dz+tfee.ribdz);                    
                                        /// Translate z = zwheel1+2*dz+tfee.ribdz                    
                                        place.par("only")=AgPlacement::kMany;                    
                                        /// Overlap: agplacement::kmany                    
                                        _stacker -> Position( AgBlock::Find("FEEA"), place );                    
                                  } // end placement of FEEA                 
                            }              
                      }           
                      END_OF_TWAS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWAS     
          // ---------------------------------------------------------------------------------------------------     
          void FEEA::Block( AgCreate create )     
          {         
                ///@addtogroup FEEA_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("FEEA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kgreen;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tfee.ass(1);              
                            shape.par("dy")=tfee.ass(2);              
                            shape.par("dz")=tfee.ass(3);              
                            /// Shape Bbox dx=tfee.ass(1) dy=tfee.ass(2) dz=tfee.ass(3)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_FEEA;              
                            _stacker -> Build(this);              
                      }           
                      { AgAttribute attr = AgAttribute("FEEA");              
                            attr.par("seen")=1;              
                            attr.par("colo")=42;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      _create = AgCreate("FEEP");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create FEEP              
                            Create("FEEP");               
                      }           
                      { AgPlacement place = AgPlacement("FEEP","FEEA");              
                            /// Add daughter volume FEEP to mother FEEA              
                            _stacker -> Position( AgBlock::Find("FEEP"), place );              
                      } // end placement of FEEP           
                      _create = AgCreate("FEER");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create FEER              
                            Create("FEER");               
                      }           
                      { AgPlacement place = AgPlacement("FEER","FEEA");              
                            /// Add daughter volume FEER to mother FEEA              
                            place.TranslateX(-tfee.ribdx-tfee.carddx);              
                            /// Translate x = -tfee.ribdx-tfee.carddx              
                            _stacker -> Position( AgBlock::Find("FEER"), place );              
                      } // end placement of FEER           
                      _create = AgCreate("FEEI");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create FEEI              
                            Create("FEEI");               
                      }           
                      { AgPlacement place = AgPlacement("FEEI","FEEA");              
                            /// Add daughter volume FEEI to mother FEEA              
                            place.TranslateX(2*tfee.carddx);              
                            /// Translate x = 2*tfee.carddx              
                            place.TranslateZ(0.5);              
                            /// Translate z = 0.5              
                            _stacker -> Position( AgBlock::Find("FEEI"), place );              
                      } // end placement of FEEI           
                      END_OF_FEEA:           
                      mCurrent = _save;           
                ///@}        
          } // End Block FEEA     
          // ---------------------------------------------------------------------------------------------------     
          void FEEP::Block( AgCreate create )     
          {         
                ///@addtogroup FEEP_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("FEEP");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kred;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tfee.platedx;              
                            shape.par("dy")=tfee.platedy;              
                            shape.par("dz")=tfee.platedz;              
                            /// Shape Bbox dx=tfee.platedx dy=tfee.platedy dz=tfee.platedz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_FEEP;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_FEEP:           
                      mCurrent = _save;           
                ///@}        
          } // End Block FEEP     
          // ---------------------------------------------------------------------------------------------------     
          void FEER::Block( AgCreate create )     
          {         
                ///@addtogroup FEER_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("FEER");              
                            attr.par("seen")=1;              
                            attr.par("colo")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tfee.ribdx;              
                            shape.par("dy")=tfee.ribdy;              
                            shape.par("dz")=tfee.ribdz;              
                            /// Shape Bbox dx=tfee.ribdx dy=tfee.ribdy dz=tfee.ribdz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_FEER;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_FEER:           
                      mCurrent = _save;           
                ///@}        
          } // End Block FEER     
          // ---------------------------------------------------------------------------------------------------     
          void FEEI::Block( AgCreate create )     
          {         
                ///@addtogroup FEEI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("FEEI");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kviolet;              
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
                            shape.par("dx")=tfee.carddx;              
                            shape.par("dy")=tfee.carddy;              
                            shape.par("dz")=tfee.carddz;              
                            /// Shape Bbox dx=tfee.carddx dy=tfee.carddy dz=tfee.carddz               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_FEEI;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_FEEI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block FEEI     
          // ---------------------------------------------------------------------------------------------------     
          void TALS::Block( AgCreate create )     
          {         
                ///@addtogroup TALS_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TALS");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kyellow;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-alpha;              
                            shape.par("dphi")=2*alpha;              
                            shape.par("npdiv")=1;              
                            shape.par("nz")=2;              
                            shape.Z(0)=z1+tpcg.padplanethickness;              
                            shape.Z(1)=z1+tpcg.padplanethickness+tecw.thickal;              
                            shape.Rmin(0)=r1;              
                            shape.Rmin(1)=r1;              
                            shape.Rmax(0)=r2;              
                            shape.Rmax(1)=r2;              
                            /// Shape Pgon phi1=-alpha dphi=2*alpha npdiv=1 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TALS;              
                            _stacker -> Build(this);              
                      }           
                      mypar(1)  = tecw.holedx;           
                      mypar(2)  = tecw.holedy;           
                      mypar(3)  = tecw.thickal/2;           
                      mypar(13) = zwheel1 - tecw.thick + tpcg.padplanethickness + tecw.thickal/2;           
                      /// Loop on itals from 0 to holz.numberofrows - 1 step=1           
                      for ( itals=0; (1>0)? (itals<=holz.numberofrows - 1):(itals>=holz.numberofrows - 1); itals+=1 )           
                      {              
                            mypar(11) = xholes(itals); ;//// cm;              
                            /// Loop on jtals from 0 to holz.numberperrow( itals+1 ) - 1 step=1              
                            for ( jtals=0; (1>0)? (jtals<=holz.numberperrow( itals+1 ) - 1):(jtals>=holz.numberperrow( itals+1 ) - 1); jtals+=1 )              
                            {                 
                                  mypar(12) = holz.yholes( 9*itals+jtals+1) *inch;                 
                                  _create = AgCreate("THOL");                 
                                  {                    
                                        AgShape myshape; // undefined shape                    
                                        ///Create THOL                    
                                        Create("THOL");                     
                                  }                 
                                  { AgPlacement place = AgPlacement("THOL","TALS");                    
                                        /// Add daughter volume THOL to mother TALS                    
                                        place.TranslateX(mypar(11));                    
                                        /// Translate x = mypar(11)                    
                                        place.TranslateY(mypar(12));                    
                                        /// Translate y = mypar(12)                    
                                        place.TranslateZ(mypar(13));                    
                                        /// Translate z = mypar(13)                    
                                        _stacker -> Position( AgBlock::Find("THOL"), place );                    
                                  } // end placement of THOL                 
                            }              
                      }           
                      END_OF_TALS:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TALS     
          // ---------------------------------------------------------------------------------------------------     
          void TSGT::Block( AgCreate create )     
          {         
                ///@addtogroup TSGT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TSGT");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kblue;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-alpha;              
                            shape.par("dphi")=2*alpha;              
                            shape.par("npdiv")=1;              
                            shape.par("nz")=2;              
                            shape.Z(0)=z1;              
                            shape.Z(1)=z1+tpcg.padplanethickness;              
                            shape.Rmin(0)=r1;              
                            shape.Rmin(1)=r1;              
                            shape.Rmax(0)=r2;              
                            shape.Rmax(1)=r2;              
                            /// Shape Pgon phi1=-alpha dphi=2*alpha npdiv=1 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TSGT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TSGT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TSGT     
          // ---------------------------------------------------------------------------------------------------     
          void TWBT::Block( AgCreate create )     
          {         
                ///@addtogroup TWBT_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TWBT");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kgreen;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("nz")=4;              
                            shape.Z(0)=zwheel1;              
                            shape.Z(1)=zwheel1+3.500*inch;              
                            shape.Z(2)=zwheel1+3.500*inch;              
                            shape.Z(3)=tpcg.lengthw/2;              
                            shape.Rmin(0)=tpcg.wheelir;              
                            shape.Rmin(1)=tpcg.wheelir;              
                            shape.Rmin(2)=tpcg.wheelir+3.6;              
                            shape.Rmin(3)=tpcg.wheelir+3.6;              
                            shape.Rmax(0)=tpcg.wheelr0;              
                            shape.Rmax(1)=tpcg.wheelr0;              
                            shape.Rmax(2)=tpcg.wheelr0;              
                            shape.Rmax(3)=tpcg.wheelr0;              
                            /// Shape Pcon phi1=-15 dphi=30 nz=4               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWBT;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TWBT:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWBT     
          // ---------------------------------------------------------------------------------------------------     
          void TWRI::Block( AgCreate create )     
          {         
                ///@addtogroup TWRI_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("nz")=4;              
                            shape.Z(0)=zwheel1;              
                            shape.Z(1)=ztofcend;              
                            shape.Z(2)=ztofcend;              
                            shape.Z(3)=tpcg.lengthw/2;              
                            shape.Rmin(0)=tpcg.wheelr2*cos15;              
                            shape.Rmin(1)=tpcg.wheelr2*cos15;              
                            shape.Rmin(2)=tpcg.wheelr2*cos15;              
                            shape.Rmin(3)=tpcg.wheelr2*cos15;              
                            shape.Rmax(0)=tpcg.wheelor1;              
                            shape.Rmax(1)=tpcg.wheelor1;              
                            shape.Rmax(2)=tpcg.wheelor;              
                            shape.Rmax(3)=tpcg.wheelor;              
                            /// Shape Pcon phi1=-15 dphi=30 nz=4               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWRI;              
                            _stacker -> Build(this);              
                      }           
                      /// Medium TWRI_something           
                      ///  deemax = 0.248853           
                      ///  stmin = 1.15055           
                      {  AgMedium &med = AgMedium::Get("Twri_something");              
                               med.Inherit(this);              
                            med.par("deemax")=0.248853;              
                            med.par("stmin")=1.15055;              
                            _medium = med;              
                      }           
                      { AgAttribute attr = AgAttribute("TWRI");              
                            attr.par("seen")=0;              
                            attr.par("colo")=kgreen;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      _create = AgCreate("TWRC");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TWRC              
                            Create("TWRC");               
                      }           
                      { AgPlacement place = AgPlacement("TWRC","TWRI");              
                            /// Add daughter volume TWRC to mother TWRI              
                            _stacker -> Position( AgBlock::Find("TWRC"), place );              
                      } // end placement of TWRC           
                      mycos = cos15; myrmin=tpcg.wheelr2; myrmax = tpcg.wheelor1;           
                      myg1 = myrmin*cos15;           
                      ncount = 0;           
                      while ( myg2 < myrmin  )           
                      {              
                            ncount += 1;              
                            myg2 = myrmin;              
                            if ( (myg2>myrmax*mycos) )              
                            {                 
                                  myg2 = myrmax*mycos;                 
                            }              
                            alpha = acos(mycos)*raddeg;;              
                            _create = AgCreate("TWRG");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TWRG                 
                                  Create("TWRG");                  
                            }              
                            { AgPlacement place = AgPlacement("TWRG","TWRI");                 
                                  /// Add daughter volume TWRG to mother TWRI                 
                                  _stacker -> Position( AgBlock::Find("TWRG"), place );                 
                            } // end placement of TWRG              
                            mycos = myg2/myrmin; myg1=myg2;              
                            if ( (ncount>10) )              
                            {                 
                                  break;                 
                            }              
                      }           
                      END_OF_TWRI:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWRI     
          // ---------------------------------------------------------------------------------------------------     
          void TWRG::Block( AgCreate create )     
          {         
                ///@addtogroup TWRG_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TWRG");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kgreen;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-alpha;              
                            shape.par("dphi")=alpha*2;              
                            shape.par("npdiv")=1;              
                            shape.par("nz")=2;              
                            shape.Z(0)=zwheel1;              
                            shape.Z(1)=tpcg.lengthw/2;              
                            shape.Rmin(0)=myg1;              
                            shape.Rmin(1)=myg1;              
                            shape.Rmax(0)=myg2;              
                            shape.Rmax(1)=myg2;              
                            /// Shape Pgon phi1=-alpha dphi=alpha*2 npdiv=1 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWRG;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TWRG:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWRG     
          // ---------------------------------------------------------------------------------------------------     
          void TWRC::Block( AgCreate create )     
          {         
                ///@addtogroup TWRC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TWRC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kgreen;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Pcon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("nz")=4;              
                            shape.Z(0)=zwheel1;              
                            shape.Z(1)=ztofcend;              
                            shape.Z(2)=ztofcend;              
                            shape.Z(3)=tpcg.lengthw/2;              
                            shape.Rmin(0)=tpcg.wheelr2/cos15;              
                            shape.Rmin(1)=tpcg.wheelr2/cos15;              
                            shape.Rmin(2)=tpcg.wheelr2/cos15;              
                            shape.Rmin(3)=tpcg.wheelr2/cos15;              
                            shape.Rmax(0)=tpcg.wheelor1;              
                            shape.Rmax(1)=tpcg.wheelor1;              
                            shape.Rmax(2)=tpcg.wheelor;              
                            shape.Rmax(3)=tpcg.wheelor;              
                            /// Shape Pcon phi1=-15 dphi=30 nz=4               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWRC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TWRC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWRC     
          // ---------------------------------------------------------------------------------------------------     
          void TWTR::Block( AgCreate create )     
          {         
                ///@addtogroup TWTR_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TWTR");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kblue;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      myg1=tpcg.wheelr2 - (tpcg.wheeltotalribwidth-tpcg.wheelribwidth)/2;           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("npdiv")=1;              
                            shape.par("nz")=2;              
                            shape.Z(0)=zwheel1;              
                            shape.Z(1)=zwheel1+tpcg.wheelribheight;              
                            shape.Rmin(0)=myg1;              
                            shape.Rmin(1)=myg1;              
                            shape.Rmax(0)=tpcg.wheelr2;              
                            shape.Rmax(1)=tpcg.wheelr2;              
                            /// Shape Pgon phi1=-15 dphi=30 npdiv=1 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWTR;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TWTR:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWTR     
          // ---------------------------------------------------------------------------------------------------     
          void TWMR::Block( AgCreate create )     
          {         
                ///@addtogroup TWMR_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TWMR");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kyellow;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      myg1=tpcg.wheelr2 - (tpcg.wheeltotalribwidth-tpcg.wheelribwidth)/2;           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("npdiv")=1;              
                            shape.par("nz")=4;              
                            shape.Z(0)=zwheel1;              
                            shape.Z(1)=zwheel1+tpcg.wheelribheight;              
                            shape.Z(2)=zwheel1+tpcg.wheelribheight;              
                            shape.Z(3)=tpcg.lengthw/2;              
                            shape.Rmin(0)= tpcg.wheelr1-tpcg.wheeltotalribwidth/2;              
                            shape.Rmin(1)=tpcg.wheelr1-tpcg.wheeltotalribwidth/2;              
                            shape.Rmin(2)=tpcg.wheelr1-tpcg.wheelribwidth/2;              
                            shape.Rmin(3)=tpcg.wheelr1-tpcg.wheelribwidth/2;              
                            shape.Rmax(0)= tpcg.wheelr1+tpcg.wheeltotalribwidth/2;              
                            shape.Rmax(1)=tpcg.wheelr1+tpcg.wheeltotalribwidth/2;              
                            shape.Rmax(2)=tpcg.wheelr1+tpcg.wheelribwidth/2;              
                            shape.Rmax(3)=tpcg.wheelr1+tpcg.wheelribwidth/2;              
                            /// Shape Pgon phi1=-15 dphi=30 npdiv=1 nz=4               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWMR;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TWMR:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWMR     
          // ---------------------------------------------------------------------------------------------------     
          void TRDO::Block( AgCreate create )     
          {         
                ///@addtogroup TRDO_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TRDO");              
                            attr.par("seen")=0;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      { AgAttribute attr = AgAttribute("TRDO");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kyellow;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Pgon");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("dphi")=30;              
                            shape.par("npdiv")=1;              
                            shape.par("nz")=2;              
                            shape.Z(0)=zzzrdo(1);              
                            shape.Z(1)=zzzrdo(2);              
                            shape.Rmin(0)=rmnrdo(1);              
                            shape.Rmin(1)=rmnrdo(2);              
                            shape.Rmax(0)=rmxrdo(1);              
                            shape.Rmax(1)=rmxrdo(2);              
                            /// Shape Pgon phi1=-15 dphi=30 npdiv=1 nz=2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TRDO;              
                            _stacker -> Build(this);              
                      }           
                      ishape = kpara;;           
                      mypar.at(0) = tpcg.rdocoolingdy;           
                      mypar.at(1) = tpcg.rdocoolingdx;           
                      mypar.at(2) = tpcg.rdocoolingdz;           
                      mypar.at(3) = 15;           
                      x = tpcg.wheelr2 - tpcg.rdocoolingdx;           
                      y = x*tan15 - tpcg.rdocoolingdy;           
                      z = tpcg.zrdo - 2*dy;           
                      _create = AgCreate("TCOO");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TCOO              
                            Create("TCOO");               
                      }           
                      { AgPlacement place = AgPlacement("TCOO","TRDO");              
                            /// Add daughter volume TCOO to mother TRDO              
                            place.TranslateX(x);              
                            /// Translate x = x              
                            place.TranslateY(y);              
                            /// Translate y = y              
                            place.TranslateZ(z);              
                            /// Translate z = z              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "YX-Z" ); // ORT=YX-Z              
                            /// Axis substitution: XYZ --> YX-Z              
                            _stacker -> Position( AgBlock::Find("TCOO"), place );              
                      } // end placement of TCOO           
                      ishape = kpara;;           
                      mypar.at(0) = tpcg.rdocoolingdy;           
                      mypar.at(1) = tpcg.rdocoolingdx;           
                      mypar.at(2) = tpcg.rdocoolingdz;           
                      mypar.at(3) = -15;           
                      x = tpcg.wheelr2 - tpcg.rdocoolingdx;           
                      y = x*tan15 - tpcg.rdocoolingdy;           
                      z = tpcg.zrdo - 2*dy;           
                      _create = AgCreate("TCOO");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create TCOO              
                            Create("TCOO");               
                      }           
                      { AgPlacement place = AgPlacement("TCOO","TRDO");              
                            /// Add daughter volume TCOO to mother TRDO              
                            place.TranslateX(x);              
                            /// Translate x = x              
                            place.TranslateY(-y);              
                            /// Translate y = -y              
                            place.TranslateZ(z);              
                            /// Translate z = z              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 0              
                            /// G3 Reference: phiz = 0              
                            place.Ortho( "YX-Z" ); // ORT=YX-Z              
                            /// Axis substitution: XYZ --> YX-Z              
                            _stacker -> Position( AgBlock::Find("TCOO"), place );              
                      } // end placement of TCOO           
                      rcoolingtube = tpcg.wheelr2 - tpcg.heigtube - 2*tpcg.dxrdo;           
                      /// Loop on icoo from 0 to 7 step=1           
                      for ( icoo=0; (1>0)? (icoo<=7):(icoo>=7); icoo+=1 )           
                      {              
                            dz = tpcg.heigtube*cm/2;              
                            dy = tpcg.widtube*cm/2;              
                            z  = rcoolingtube;              
                            dx1 = (z-dz)*tan15 - 2*tpcg.rdocoolingdy;              
                            dx2 = (z+dz)*tan15 - 2*tpcg.rdocoolingdy;              
                            ishape = ktrd1;;              
                            mypar.at(0) = dx1;              
                            mypar.at(1) = dx2;              
                            mypar.at(2) = dy;              
                            mypar.at(3) = dz;              
                            mypar(11) = z; mypar(13) = tpcg.zrdo - 2*dy;              
                            _create = AgCreate("TCOO");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TCOO                 
                                  Create("TCOO");                  
                            }              
                            { AgPlacement place = AgPlacement("TCOO","TRDO");                 
                                  /// Add daughter volume TCOO to mother TRDO                 
                                  place.TranslateX(mypar(11));                 
                                  /// Translate x = mypar(11)                 
                                  place.TranslateY(0);                 
                                  /// Translate y = 0                 
                                  place.TranslateZ(mypar(13));                 
                                  /// Translate z = mypar(13)                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  place.Ortho( "YZX" ); // ORT=YZX                 
                                  /// Axis substitution: XYZ --> YZX                 
                                  _stacker -> Position( AgBlock::Find("TCOO"), place );                 
                            } // end placement of TCOO              
                            if ( (icoo != 0 && icoo != 6) )              
                            {                 
                                  mypar(11) = z + dz + tpcg.dxrdo;;                 
                                  mypar(13) =          tpcg.zrdo-tpcg.dzrdo;                 
                                  _create = AgCreate("TRDC");                 
                                  {                    
                                        AgShape myshape; // undefined shape                    
                                        ///Create TRDC                    
                                        Create("TRDC");                     
                                  }                 
                                  { AgPlacement place = AgPlacement("TRDC","TRDO");                    
                                        /// Add daughter volume TRDC to mother TRDO                    
                                        place.TranslateX(mypar(11));                    
                                        /// Translate x = mypar(11)                    
                                        place.TranslateY(0);                    
                                        /// Translate y = 0                    
                                        place.TranslateZ(mypar(13));                    
                                        /// Translate z = mypar(13)                    
                                        _stacker -> Position( AgBlock::Find("TRDC"), place );                    
                                  } // end placement of TRDC                 
                            }              
                            rcoolingtube -= drdocooling(icoo);              
                      }           
                      END_OF_TRDO:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TRDO     
          // ---------------------------------------------------------------------------------------------------     
          void TBRW::Block( AgCreate create )     
          {         
                ///@addtogroup TBRW_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TBRW");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kviolet;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=tpcg.wheelboxdy/2;              
                            shape.par("dy")=tpcg.wheelboxdx/2;              
                            shape.par("dz")=tpcg.wheelthk/2;              
                            /// Shape Bbox dx=tpcg.wheelboxdy/2 dy=tpcg.wheelboxdx/2 dz=tpcg.wheelthk/2               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TBRW;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TBRW:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TBRW     
          // ---------------------------------------------------------------------------------------------------     
          void TWRB::Block( AgCreate create )     
          {         
                ///@addtogroup TWRB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TWRB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kyellow;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Para");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=mydx;              
                            shape.par("dy")=mydy;              
                            shape.par("dz")=mydz;              
                            shape.par("alph")=myalph;              
                            shape.par("thet")=0;              
                            shape.par("phi")=0;              
                            /// Shape Para dx=mydx dy=mydy dz=mydz alph=myalph thet=0 phi=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWRB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TWRB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWRB     
          // ---------------------------------------------------------------------------------------------------     
          void TCOO::Block( AgCreate create )     
          {         
                ///@addtogroup TCOO_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TCOO");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kred;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Water_Pipe            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Water_pipe");              
                            _material = mat;              
                      }           
                      if ( ishape==kpara )           
                      {              
                            {  AgShape shape = AgShape("Para");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("dx")=mypar(1);                 
                                  shape.par("dy")=mypar(2);                 
                                  shape.par("dz")=mypar(3);                 
                                  shape.par("alph")=mypar(4);                 
                                  shape.par("thet")=0;                 
                                  shape.par("phi")=0;                 
                                  /// Shape Para dx=mypar(1) dy=mypar(2) dz=mypar(3) alph=mypar(4) thet=0 phi=0                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_TCOO;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      if ( ishape==ktrd1 )           
                      {              
                            {  AgShape shape = AgShape("Trd1");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("dx1")=mypar(1);                 
                                  shape.par("dx2")=mypar(2);                 
                                  shape.par("dy")=mypar(3);                 
                                  shape.par("dz")=mypar(4);                 
                                  /// Shape Trd1 dx1=mypar(1) dx2=mypar(2) dy=mypar(3) dz=mypar(4)                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_TCOO;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      END_OF_TCOO:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TCOO     
          // ---------------------------------------------------------------------------------------------------     
          void TCAB::Block( AgCreate create )     
          {         
                ///@addtogroup TCAB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TCAB");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kgreen;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material Cables            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Cables");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Para");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=mypar(1);              
                            shape.par("dy")=mypar(2);              
                            shape.par("dz")=mypar(3);              
                            shape.par("alph")=mypar(4);              
                            shape.par("thet")=0;              
                            shape.par("phi")=0;              
                            /// Shape Para dx=mypar(1) dy=mypar(2) dz=mypar(3) alph=mypar(4) thet=0 phi=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TCAB;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TCAB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TCAB     
          // ---------------------------------------------------------------------------------------------------     
          void TRDC::Block( AgCreate create )     
          {         
                ///@addtogroup TRDC_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TRDC");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kblue;              
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
                            shape.par("dx")=tpcg.dxrdo;              
                            shape.par("dy")=tpcg.dyrdo;              
                            shape.par("dz")=tpcg.dzrdo;              
                            /// Shape Bbox dx=tpcg.dxrdo dy=tpcg.dyrdo dz=tpcg.dzrdo               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TRDC;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TRDC:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TRDC     
          // ---------------------------------------------------------------------------------------------------     
          void TRIB::Block( AgCreate create )     
          {         
                ///@addtogroup TRIB_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TRib");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kred;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material ALUMINIUM            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");              
                            _material = mat;              
                      }           
                      if ( ishape==kpara )           
                      {              
                            {  AgShape shape = AgShape("Para");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("dx")=mypar(1);                 
                                  shape.par("dy")=mypar(2);                 
                                  shape.par("dz")=mypar(3);                 
                                  shape.par("alph")=mypar(4);                 
                                  shape.par("thet")=0;                 
                                  shape.par("phi")=0;                 
                                  /// Shape Para dx=mypar(1) dy=mypar(2) dz=mypar(3) alph=mypar(4) thet=0 phi=0                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_TRIB;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      else if ( ishape==ktrd1 )           
                      {              
                            {  AgShape shape = AgShape("Trd1");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("dx1")=mypar(1);                 
                                  shape.par("dx2")=mypar(2);                 
                                  shape.par("dy")=mypar(3);                 
                                  shape.par("dz")=mypar(4);                 
                                  /// Shape Trd1 dx1=mypar(1) dx2=mypar(2) dy=mypar(3) dz=mypar(4)                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_TRIB;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      else if ( ishape==kbbox )           
                      {              
                            {  AgShape shape = AgShape("Bbox");                 
                                  shape     .Inherit( AgBlock::previous() );                 
                                  create     .SetParameters(shape);                 
                                  shape.par("dx")=mypar(1);                 
                                  shape.par("dy")=mypar(2);                 
                                  shape.par("dz")=mypar(3);                 
                                  /// Shape Bbox dx=mypar(1) dy=mypar(2) dz=mypar(3)                  
                                  _same_shape &= _stacker->SearchVolume( shape, _attribute );                 
                                  _shape = shape;                 
                                  if (_same_shape) goto END_OF_TRIB;                 
                                  _stacker -> Build(this);                 
                            }              
                      }           
                      END_OF_TRIB:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TRIB     
          // ---------------------------------------------------------------------------------------------------     
          void TWIR::Block( AgCreate create )     
          {         
                ///@addtogroup TWIR_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TWIR");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kyellow;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      {  AgShape shape = AgShape("Para");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=mypar(1);              
                            shape.par("dy")=mypar(2);              
                            shape.par("dz")=mypar(3);              
                            shape.par("alph")=mypar(4);              
                            shape.par("thet")=0;              
                            shape.par("phi")=0;              
                            /// Shape Para dx=mypar(1) dy=mypar(2) dz=mypar(3) alph=mypar(4) thet=0 phi=0               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TWIR;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_TWIR:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TWIR     
          // ---------------------------------------------------------------------------------------------------     
          void THOL::Block( AgCreate create )     
          {         
                ///@addtogroup THOL_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("THOL");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kgreen;              
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
                            shape.par("dx")=mypar(1);              
                            shape.par("dy")=mypar(2);              
                            shape.par("dz")=mypar(3);              
                            /// Shape Bbox dx=mypar(1) dy=mypar(2) dz=mypar(3)               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_THOL;              
                            _stacker -> Build(this);              
                      }           
                      _create = AgCreate("FEES");           
                      {              
                            AgShape myshape; // undefined shape              
                            ///Create FEES              
                            Create("FEES");               
                      }           
                      { AgPlacement place = AgPlacement("FEES","THOL");              
                            /// Add daughter volume FEES to mother THOL              
                            _stacker -> Position( AgBlock::Find("FEES"), place );              
                      } // end placement of FEES           
                      END_OF_THOL:           
                      mCurrent = _save;           
                ///@}        
          } // End Block THOL     
          // ---------------------------------------------------------------------------------------------------     
          void FEES::Block( AgCreate create )     
          {         
                ///@addtogroup FEES_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      /// Material G10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("G10");              
                            _material = mat;              
                      }           
                      { AgAttribute attr = AgAttribute("FEES");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kblue;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Bbox");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("dx")=6.2/20;              
                            shape.par("dy")=57./20;              
                            shape.par("dz")=5.8/20;              
                            /// Shape Bbox dx=6.2/20 dy=57./20 dz=5.8/20               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_FEES;              
                            _stacker -> Build(this);              
                      }           
                      END_OF_FEES:           
                      mCurrent = _save;           
                ///@}        
          } // End Block FEES     
          // ---------------------------------------------------------------------------------------------------     
          void TPGV::Block( AgCreate create )     
          {         
                ///@addtogroup TPGV_doc        
                ///@{           
                        AgBlock *_save = mCurrent;           
                        mCurrent = this;           
                        Bool_t _same_shape = true;           
                      { AgAttribute attr = AgAttribute("TPGV");              
                            attr.par("seen")=1;              
                            attr.par("colo")=kred;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      /// Material P10            
                      {  AgMaterial mat = AgMaterial::CopyMaterial("P10");              
                            _material = mat;              
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
                      /// Loop on isecang from 15 to 360-15 step=30           
                      for ( isecang=15; (30>0)? (isecang<=360-15):(isecang>=360-15); isecang+=30 )           
                      {              
                            _create = AgCreate("TPSS");              
                            {                 
                                  AgShape myshape; // undefined shape                 
                                  ///Create TPSS                 
                                  Create("TPSS");                  
                            }              
                            { AgPlacement place = AgPlacement("TPSS","TPGV");                 
                                  /// Add daughter volume TPSS to mother TPGV                 
                                  place.par("only")=AgPlacement::kMany;                 
                                  /// Overlap: agplacement::kmany                 
                                  place.AlphaZ(isecang);                 
                                  /// Rotate: AlphaZ = isecang                 
                                  /// G3 Reference: thetax = 90                 
                                  /// G3 Reference: phix = 0                 
                                  /// G3 Reference: thetay = 90                 
                                  /// G3 Reference: phiy = 90                 
                                  /// G3 Reference: thetaz = 0                 
                                  /// G3 Reference: phiz = 0                 
                                  _stacker -> Position( AgBlock::Find("TPSS"), place );                 
                            } // end placement of TPSS              
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
                            attr.par("seen")=1;              
                            attr.par("colo")=kblue;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      {  AgShape shape = AgShape("Tubs");              
                            shape     .Inherit( AgBlock::previous() );              
                            create     .SetParameters(shape);              
                            shape.par("phi1")=-15;              
                            shape.par("phi2")=15;              
                            /// Shape Tubs phi1=-15 phi2=15               
                            _same_shape &= _stacker->SearchVolume( shape, _attribute );              
                            _shape = shape;              
                            if (_same_shape) goto END_OF_TPSS;              
                            _stacker -> Build(this);              
                      }           
                      /// Loop on kase from 1 to 2 step=1           
                      for ( kase=1; (1>0)? (kase<=2):(kase>=2); kase+=1 )           
                      {              
                            /// Loop on i_sec from 1 to 2 step=1              
                            for ( i_sec=1; (1>0)? (i_sec<=2):(i_sec>=2); i_sec+=1 )              
                            {                 
                                  /// USE tprs sec=i_sec;                 
                                  tprs.Use("sec",(Float_t)i_sec);                 
                                  /// USE tecw sec=i_sec;                 
                                  tecw.Use("sec",(Float_t)i_sec);                 
                                  zwheel1  = tpcg.lengthw/2 - tpcg.wheelthk;                 
                                  zbeg     = tpcg.membthk/2;                 
                                  zend     = tpcg.zgroundgrid + tprs.danode*2;                 
                                  zded     = tpcg.zgatinggrid - tpcg.deadzone;                 
                                  zpmt     = tpcg.zgatinggrid;                 
                                  dx       = tprs.width/2;                 
                                  if ( kase==1 )                 
                                  {                    
                                        dz = (zded - zbeg)/2;;                    
                                        z  = (zded + zbeg)/2 - tpgvz;                    
                                  }                 
                                  if ( kase==2 )                 
                                  {                    
                                        dz = (zend - zpmt)/2;;                    
                                        z  = (zend + zpmt)/2 - tpgvz;                    
                                  }                 
                                  /// Loop on i_row from 1 to nint(tprs.nrow) step=1                 
                                  for ( i_row=1; (1>0)? (i_row<=nint(tprs.nrow)):(i_row>=nint(tprs.nrow)); i_row+=1 )                 
                                  {                    
                                        if ( (nint(tprs.super)==3||i_row==1) )                    
                                        {                       
                                              dy=tprs.npads(i_row)*tprs.pitch/2;                       
                                              x=tprs.rpads(i_row)-tprs.width;                       
                                              _create = AgCreate("TPAD");                       
                                              {                          
                                                    AgShape myshape; // undefined shape                          
                                                    ///Create TPAD                          
                                                    Create("TPAD");                           
                                              }                       
                                              { AgPlacement place = AgPlacement("TPAD","TPSS");                          
                                                    /// Add daughter volume TPAD to mother TPSS                          
                                                    place.TranslateX(x);                          
                                                    /// Translate x = x                          
                                                    place.TranslateZ(z);                          
                                                    /// Translate z = z                          
                                                    place.par("dx")=dx;                          
                                                    place.par("dy")=dy;                          
                                                    place.par("dz")=dz;                          
                                                    _stacker -> Position( AgBlock::Find("TPAD"), place );                          
                                              } // end placement of TPAD                       
                                        }                    
                                        dy=tprs.npads(i_row)*tprs.pitch/2;                    
                                        x=tprs.rpads(i_row);                    
                                        _create = AgCreate("TPAD");                    
                                        {                       
                                              AgShape myshape; // undefined shape                       
                                              ///Create TPAD                       
                                              Create("TPAD");                        
                                        }                    
                                        { AgPlacement place = AgPlacement("TPAD","TPSS");                       
                                              /// Add daughter volume TPAD to mother TPSS                       
                                              place.TranslateX(x);                       
                                              /// Translate x = x                       
                                              place.TranslateZ(z);                       
                                              /// Translate z = z                       
                                              place.par("dx")=dx;                       
                                              place.par("dy")=dy;                       
                                              place.par("dz")=dz;                       
                                              _stacker -> Position( AgBlock::Find("TPAD"), place );                       
                                        } // end placement of TPAD                    
                                        if ( (nint(tprs.super)==3||i_row==nint(tprs.nrow)) )                    
                                        {                       
                                              x=tprs.rpads(i_row)+tprs.width;                       
                                              dy=tprs.npads(i_row)*tprs.pitch/2;                       
                                              _create = AgCreate("TPAD");                       
                                              {                          
                                                    AgShape myshape; // undefined shape                          
                                                    ///Create TPAD                          
                                                    Create("TPAD");                           
                                              }                       
                                              { AgPlacement place = AgPlacement("TPAD","TPSS");                          
                                                    /// Add daughter volume TPAD to mother TPSS                          
                                                    place.TranslateX(x);                          
                                                    /// Translate x = x                          
                                                    place.TranslateZ(z);                          
                                                    /// Translate z = z                          
                                                    place.par("dx")=dx;                          
                                                    place.par("dy")=dy;                          
                                                    place.par("dz")=dz;                          
                                                    _stacker -> Position( AgBlock::Find("TPAD"), place );                          
                                              } // end placement of TPAD                       
                                        }                    
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
                            attr.par("seen")=1;              
                            attr.par("colo")=2;              
                            attr.par("serial")=1;              
                            attr.Inherit( AgBlock::previous() );               
                            _attribute = attr;              
                      }           
                      if ( tprs.width>1.5 )           
                      { AgAttribute attr = AgAttribute("TPAD");              
                            attr.par("seen")=1;              
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
                      /// Medium TPAD_p10           
                      ///  stemax = 2.5*tprs_width           
                      ///  deemax = 0.00175367           
                      ///  stmin = 0.0249056           
                      ///  isvol = 1           
                      {  AgMedium &med = AgMedium::Get("Tpad_p10");              
                               med.Inherit(this);              
                            med.par("stemax")=2.5*tprs.width;              
                            med.par("deemax")=0.00175367;              
                            med.par("stmin")=0.0249056;              
                            med.par("isvol")=1;              
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
                            if (_same_shape) goto END_OF_TPAD;              
                            _stacker -> Build(this);              
                      }           
                      // _medium.par("CUTGAM") = 1e-4;           
                      // _medium.par("CUTELE") = 1e-4;           
                      // _medium.par("DCUTE") = 1e-4;           
                      // _medium.par("DCUTM") = 1e-4;           
                      // _medium.par("STRA") = 1.;           
                      END_OF_TPAD:           
                      mCurrent = _save;           
                ///@}        
          } // End Block TPAD     
    // ----------------------------------------------------------------------- geoctr
       void TpceGeo3a::ConstructGeometry( const Char_t *dummy )     
       {        
             ///@addtogroup TpceGeo3a_revision        
             ///@{           
                   /// Author: David Underwood corrected by Maxim Potekhin,          implmented in TGeo by Yuri, translated back          to AgSTAR by Victor, and code cleanup by          Jason           
             ///@}        
             ///@addtogroup TpceGeo3a_revision        
             ///@{           
                   /// Created:   Dec 7, 2005            
             ///@}        
             AddBlock("TPCE");        
             AddBlock("TPCM");        
             AddBlock("TIFC");        
             AddBlock("TIKA");        
             AddBlock("TINX");        
             AddBlock("TIAD");        
             AddBlock("TOFC");        
             AddBlock("TOFS");        
             AddBlock("TOKA");        
             AddBlock("TONX");        
             AddBlock("TOAD");        
             AddBlock("TOIG");        
             AddBlock("TOHA");        
             AddBlock("TSWH");        
             AddBlock("TSAW");        
             AddBlock("TSAS");        
             AddBlock("TWAS");        
             AddBlock("FEEA");        
             AddBlock("FEEP");        
             AddBlock("FEER");        
             AddBlock("FEEI");        
             AddBlock("TALS");        
             AddBlock("TSGT");        
             AddBlock("TWBT");        
             AddBlock("TWRI");        
             AddBlock("TWRG");        
             AddBlock("TWRC");        
             AddBlock("TWTR");        
             AddBlock("TWMR");        
             AddBlock("TRDO");        
             AddBlock("TBRW");        
             AddBlock("TWRB");        
             AddBlock("TCOO");        
             AddBlock("TCAB");        
             AddBlock("TRDC");        
             AddBlock("TRIB");        
             AddBlock("TWIR");        
             AddBlock("THOL");        
             AddBlock("FEES");        
             AddBlock("TPGV");        
             AddBlock("TPSS");        
             AddBlock("TPAD");        
             kinner=0;        
             kouter=1;        
             /* Export block
inch=2.54;
*/        
             /* Export block
cm=1.;
*/        
             kblack=1;        
             kred=2;        
             kgreen=3;        
             kblue=4;        
             kyellow=5;        
             kviolet=6;        
             klightblue=7;        
             kbbox=0;        
             kpara=1;        
             ktrd1=2;        
             cos15=.965925826289068312;        
             sin15=.258819045102520739;        
             tan15=.267949192431122696;        
                xholes.SetRange(0,15);        
                rmnsa.SetRange(0,1);        
                rmxsa.SetRange(0,1);        
             zzzsa.at(0) = 207.4;        
             zzzsa.at(1) = 219.1;        
             rmnsa.at(0) = 51;        
             rmnsa.at(1) = 121.07;        
             rmxsa.at(0) = 121.07;        
             rmxsa.at(1) = 194;        
                rmnwa.SetRange(0,1);        
                rmxwa.SetRange(0,1);        
             zzzwa.at(0) = 211.4;        
             zzzwa.at(1) = 229.2;        
             rmnwa.at(0) = 54;        
             rmnwa.at(1) = 121;        
             rmxwa.at(0) = 121;        
             rmxwa.at(1) = 189;        
             zzzrdo.at(0) = 232.;        
             zzzrdo.at(1) = 252.;        
             rmnrdo.at(0) = 88.;        
             rmnrdo.at(1) = 88.;        
             rmxrdo.at(0) = 198.;        
             rmxrdo.at(1) = 198.;        
                drdocooling.SetRange(0,7);        
             drdocooling.at(0) = 16.0;        
             drdocooling.at(1) = 16.0;        
             drdocooling.at(2) = 16.0;        
             drdocooling.at(3) = 16.7;        
             drdocooling.at(4) = 15.0;        
             drdocooling.at(5) = 3.5;        
             drdocooling.at(6) = 14.5;        
             drdocooling.at(7) = 0.0;        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tpcg_doc        
             ///@{           
                   ++tpcg._index;           
                   tpcg . version = 3; // // version    => current version            
                   /// tpcg . version = 3; // // version    => current version            
                   tpcg . rmin = 46.107; // // Rmin          => TPC envelope inner radius            
                   /// tpcg . rmin = 46.107; // // Rmin          => TPC envelope inner radius            
                   tpcg . rmax = 206.75/cos15; // // Rmax          => TPC envelope outer radius            
                   /// tpcg . rmax = 206.75/cos15; // // Rmax          => TPC envelope outer radius            
                   tpcg . rminifc = 46.6; // // RminIFC    => inner radius TPC IFC  : A.Lebedev measurement 10/16/08            
                   /// tpcg . rminifc = 46.6; // // RminIFC    => inner radius TPC IFC  : A.Lebedev measurement 10/16/08            
                   tpcg . lengtht = 2*271.0; // // LengthT    => TPC full length up to front of EEMC            
                   /// tpcg . lengtht = 2*271.0; // // LengthT    => TPC full length up to front of EEMC            
                   tpcg . length = 2*259.685; // // Length        => TPC full length including RDOs            
                   /// tpcg . length = 2*259.685; // // Length        => TPC full length including RDOs            
                   tpcg . lengthw = 2*229.71; // // LengthW    => TPC length including Wheel            
                   /// tpcg . lengthw = 2*229.71; // // LengthW    => TPC length including Wheel            
                   tpcg . lengthv = 2*210.00; // // LengthV    => TPC gas volume length            
                   /// tpcg . lengthv = 2*210.00; // // LengthV    => TPC gas volume length            
                   tpcg . dzenvelop = 268.; // // TPCE envelop dz            
                   /// tpcg . dzenvelop = 268.; // // TPCE envelop dz            
                   tpcg . wheelir = 38.620*inch/2; // // 49.60 WheelIR    => support wheel inner radius            
                   /// tpcg . wheelir = 38.620*inch/2; // // 49.60 WheelIR    => support wheel inner radius            
                   tpcg . wheelr0 = 21.500*inch; // // WheelR0 => Distance from IP of end of inner cylindrical part            
                   /// tpcg . wheelr0 = 21.500*inch; // // WheelR0 => Distance from IP of end of inner cylindrical part            
                   tpcg . wheelr1 = 47.867*inch; // // WheelR1 => Distance from IP of middle Rib            
                   /// tpcg . wheelr1 = 47.867*inch; // // WheelR1 => Distance from IP of middle Rib            
                   tpcg . wheelr2 = 76.093*inch; // // WheelR2 => Distance from IP of upper Rib            
                   /// tpcg . wheelr2 = 76.093*inch; // // WheelR2 => Distance from IP of upper Rib            
                   tpcg . wheeltotalribwidth = 7.6; // // WheelTotalRibWidth => total rib width (A.Lebedev measurement)            
                   /// tpcg . wheeltotalribwidth = 7.6; // // WheelTotalRibWidth => total rib width (A.Lebedev measurement)            
                   tpcg . wheelribwidth = 1.9; // // WheelRibWidth         => rib plate width (A.Lebedev measurement)            
                   /// tpcg . wheelribwidth = 1.9; // // WheelRibWidth         => rib plate width (A.Lebedev measurement)            
                   tpcg . wheelribheight = 1.3; // // WheelRibHeight        => rib plate height (A.Lebedev measurement)            
                   /// tpcg . wheelribheight = 1.3; // // WheelRibHeight        => rib plate height (A.Lebedev measurement)            
                   tpcg . wheelboxdx = 4.7; // // WheelBoxDx (A.Lebedev measurement)            
                   /// tpcg . wheelboxdx = 4.7; // // WheelBoxDx (A.Lebedev measurement)            
                   tpcg . wheelboxdy = 7.6; // // WheelBoxDy (A.Lebedev measurement)            
                   /// tpcg . wheelboxdy = 7.6; // // WheelBoxDy (A.Lebedev measurement)            
                   tpcg . wheelor1 = 201.0; // // WheelOR1   => @ TOFC            
                   /// tpcg . wheelor1 = 201.0; // // WheelOR1   => @ TOFC            
                   tpcg . wheelor = 206.75; // // WheelOR    => support wheel outer radius            
                   /// tpcg . wheelor = 206.75; // // WheelOR    => support wheel outer radius            
                   tpcg . wheelthk1 = 5.72; // // WheelTHK1            
                   /// tpcg . wheelthk1 = 5.72; // // WheelTHK1            
                   tpcg . wheelthk = 11.43; // // WheelTHK   => support wheel length            
                   /// tpcg . wheelthk = 11.43; // // WheelTHK   => support wheel length            
                   tpcg . sengasor = 200; // // SenGasOR   => TPC sensitive gas outer radius            
                   /// tpcg . sengasor = 200; // // SenGasOR   => TPC sensitive gas outer radius            
                   tpcg . membthk = 0.00762; // // MembTHK    => Central membrane thickness            
                   /// tpcg . membthk = 0.00762; // // MembTHK    => Central membrane thickness            
                   tpcg . tocsdr = 0.013; // // tocsDR        => outer copper thickness:  NIM A499 (2003) 659-678 Table 2            
                   /// tpcg . tocsdr = 0.013; // // tocsDR        => outer copper thickness:  NIM A499 (2003) 659-678 Table 2            
                   tpcg . tokadr = 0.015; // // tokaDR        => outer kapton thickness            
                   /// tpcg . tokadr = 0.015; // // tokaDR        => outer kapton thickness            
                   tpcg . tonxdr = 0.953; // // tonxDR        => outer nomex thickness            
                   /// tpcg . tonxdr = 0.953; // // tonxDR        => outer nomex thickness            
                   tpcg . toaddr = 0.05; // // toadDR        => outer adhesive thickness            
                   /// tpcg . toaddr = 0.05; // // toadDR        => outer adhesive thickness            
                   tpcg . toigdr = 5.70; // // toigDR        => outer isolating gas thickness            
                   /// tpcg . toigdr = 5.70; // // toigDR        => outer isolating gas thickness            
                   tpcg . toaldr = 0.40; // // toalDR        => outer aluminum thickness (for both layers)            
                   /// tpcg . toaldr = 0.40; // // toalDR        => outer aluminum thickness (for both layers)            
                   tpcg . tohadr = 0.60; // // tohaDR        => outer Honeycomb Al thickness            
                   /// tpcg . tohadr = 0.60; // // tohaDR        => outer Honeycomb Al thickness            
                   tpcg . tiaddr = 0.080; // // tiadDR        => inner adhesive layer thickness:  NIM A499 (2003) 659-678 Table 2            
                   /// tpcg . tiaddr = 0.080; // // tiadDR        => inner adhesive layer thickness:  NIM A499 (2003) 659-678 Table 2            
                   tpcg . tinxdr = 1.270; // // tinxDR        => inner nomex structureure thickness            
                   /// tpcg . tinxdr = 1.270; // // tinxDR        => inner nomex structureure thickness            
                   tpcg . tikadr = 0.015; // // tikaDR        => inner Kapton layer thickness            
                   /// tpcg . tikadr = 0.015; // // tikaDR        => inner Kapton layer thickness            
                   tpcg . tialdr = 0.004; // // tialDR        => inner aluminum layer thickness            
                   /// tpcg . tialdr = 0.004; // // tialDR        => inner aluminum layer thickness            
                   tpcg . tifcrf = 51.7; // // tifcRF        => outer radius of IFC flange            
                   /// tpcg . tifcrf = 51.7; // // tifcRF        => outer radius of IFC flange            
                   tpcg . tifcdrt = 0.1; // // tifcDRT    => tolerance between flange and wheel            
                   /// tpcg . tifcdrt = 0.1; // // tifcDRT    => tolerance between flange and wheel            
                   tpcg . dzyf1 = 221.162; // // dz of YF1            
                   /// tpcg . dzyf1 = 221.162; // // dz of YF1            
                   tpcg . dzyf2 = 211.9; // // dz of YF2            
                   /// tpcg . dzyf2 = 211.9; // // dz of YF2            
                   tpcg . dzyf3 = 208.02; // // dz of YF3            
                   /// tpcg . dzyf3 = 208.02; // // dz of YF3            
                   tpcg . padplanethickness = 0.182; // // 1.82 mm  Drawing 24A0314 & 24A0304            
                   /// tpcg . padplanethickness = 0.182; // // 1.82 mm  Drawing 24A0314 & 24A0304            
                   tpcg . dgateground = 0.6; // //            
                   /// tpcg . dgateground = 0.6; // //            
                   tpcg . wiremountwidth = 5*((0.130+0.1376)/2)*inch; // //            
                   /// tpcg . wiremountwidth = 5*((0.130+0.1376)/2)*inch; // //            
                   tpcg . wiremountheight = 1.340*inch; // // Drawing 24A0434            
                   /// tpcg . wiremountheight = 1.340*inch; // // Drawing 24A0434            
                   tpcg . dxrdo = 1.75/2; // // A.Lebedev 1 RDO = 5 lb            
                   /// tpcg . dxrdo = 1.75/2; // // A.Lebedev 1 RDO = 5 lb            
                   tpcg . dyrdo = 45./2; // //            
                   /// tpcg . dyrdo = 45./2; // //            
                   tpcg . dzrdo = 17.0/2; // //            
                   /// tpcg . dzrdo = 17.0/2; // //            
                   tpcg . zrdo = tpcg.lengthw/2 + 20.0; // //            
                   /// tpcg . zrdo = tpcg.lengthw/2 + 20.0; // //            
                   tpcg . heigtube = 0.703*inch; // // x Cooling TUBE Drawing 24A0801B            
                   /// tpcg . heigtube = 0.703*inch; // // x Cooling TUBE Drawing 24A0801B            
                   tpcg . widtube = 0.500*inch; // // z Mixture TPCE_Water_Pipe => rho = 2.32155 g/cm**3            
                   /// tpcg . widtube = 0.500*inch; // // z Mixture TPCE_Water_Pipe => rho = 2.32155 g/cm**3            
                   tpcg . rdocoolingdx = (38.0 + 9.0 + 58.0)/2; // //            
                   /// tpcg . rdocoolingdx = (38.0 + 9.0 + 58.0)/2; // //            
                   tpcg . rdocoolingdy = 1.25; // //            
                   /// tpcg . rdocoolingdy = 1.25; // //            
                   tpcg . rdocoolingdz = 2.50; // //            
                   /// tpcg . rdocoolingdz = 2.50; // //            
                   tpcg . danode.at(0) = 0.2 ; // // Inner/Outer anode width            
                   ///tpcg . danode.at(0) = 0.2 ; // // Inner/Outer anode width            
                   tpcg . danode.at(1) = 0.4 ; // // Inner/Outer anode width            
                   ///tpcg . danode.at(1) = 0.4 ; // // Inner/Outer anode width            
                   tpcg . zgatinggrid = tpcg.lengthv/2 -(tpcg.dgateground+2*tpcg.danode(2)); // //             
                   /// tpcg . zgatinggrid = tpcg.lengthv/2 -(tpcg.dgateground+2*tpcg.danode(2)); // //             
                   tpcg . zgroundgrid = tpcg.zgatinggrid+tpcg.dgateground; // //            
                   /// tpcg . zgroundgrid = tpcg.zgatinggrid+tpcg.dgateground; // //            
                   tpcg . deadzone = 12.; // // Dead zone before GatingGrid. No hits there            
                   /// tpcg . deadzone = 12.; // // Dead zone before GatingGrid. No hits there            
                   //           
                   tpcg.fill();           
             ///@}        
             //        
             /// USE tpcg _index=1;        
             tpcg.Use();        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tprs_doc        
             ///@{           
                   ++tprs._index;           
                   tprs . sec = 1; // // sector number: 1 for inner, 2 for outer            
                   /// tprs . sec = 1; // // sector number: 1 for inner, 2 for outer            
                   tprs . nrow = 13; // // number of padrows in the sector            
                   /// tprs . nrow = 13; // // number of padrows in the sector            
                   tprs . pitch = 0.335; // // tpc padrow pitch width            
                   /// tprs . pitch = 0.335; // // tpc padrow pitch width            
                   tprs . width = 1.15; // // tpc padrow thickness            
                   /// tprs . width = 1.15; // // tpc padrow thickness            
                   tprs . super = 3; // // number of padraws in a superpadrow            
                   /// tprs . super = 3; // // number of padraws in a superpadrow            
                   tprs . danode = 0.2; // // distance to anode wire from pad plane            
                   /// tprs . danode = 0.2; // // distance to anode wire from pad plane            
                   tprs . npads.at(0) = 88; // // number of pads in row            
                   ///tprs . npads.at(0) = 88; // // number of pads in row            
                   tprs . npads.at(1) = 96; // // number of pads in row            
                   ///tprs . npads.at(1) = 96; // // number of pads in row            
                   tprs . npads.at(2) = 104; // // number of pads in row            
                   ///tprs . npads.at(2) = 104; // // number of pads in row            
                   tprs . npads.at(3) = 112; // // number of pads in row            
                   ///tprs . npads.at(3) = 112; // // number of pads in row            
                   tprs . npads.at(4) = 118; // // number of pads in row            
                   ///tprs . npads.at(4) = 118; // // number of pads in row            
                   tprs . npads.at(5) = 126; // // number of pads in row            
                   ///tprs . npads.at(5) = 126; // // number of pads in row            
                   tprs . npads.at(6) = 134; // // number of pads in row            
                   ///tprs . npads.at(6) = 134; // // number of pads in row            
                   tprs . npads.at(7) = 142; // // number of pads in row            
                   ///tprs . npads.at(7) = 142; // // number of pads in row            
                   tprs . npads.at(8) = 150; // // number of pads in row            
                   ///tprs . npads.at(8) = 150; // // number of pads in row            
                   tprs . npads.at(9) = 158 ; // // number of pads in row            
                   ///tprs . npads.at(9) = 158 ; // // number of pads in row            
                   tprs . npads.at(10) = 166; // // number of pads in row            
                   ///tprs . npads.at(10) = 166; // // number of pads in row            
                   tprs . npads.at(11) = 174; // // number of pads in row            
                   ///tprs . npads.at(11) = 174; // // number of pads in row            
                   tprs . npads.at(12) = 182 ; // // number of pads in row            
                   ///tprs . npads.at(12) = 182 ; // // number of pads in row            
                   tprs . rpads.at(0) = 60.0; // // tpc padrow radii            
                   ///tprs . rpads.at(0) = 60.0; // // tpc padrow radii            
                   tprs . rpads.at(1) = 64.8; // // tpc padrow radii            
                   ///tprs . rpads.at(1) = 64.8; // // tpc padrow radii            
                   tprs . rpads.at(2) = 69.6; // // tpc padrow radii            
                   ///tprs . rpads.at(2) = 69.6; // // tpc padrow radii            
                   tprs . rpads.at(3) = 74.4; // // tpc padrow radii            
                   ///tprs . rpads.at(3) = 74.4; // // tpc padrow radii            
                   tprs . rpads.at(4) = 79.2; // // tpc padrow radii            
                   ///tprs . rpads.at(4) = 79.2; // // tpc padrow radii            
                   tprs . rpads.at(5) = 84.0; // // tpc padrow radii            
                   ///tprs . rpads.at(5) = 84.0; // // tpc padrow radii            
                   tprs . rpads.at(6) = 88.8; // // tpc padrow radii            
                   ///tprs . rpads.at(6) = 88.8; // // tpc padrow radii            
                   tprs . rpads.at(7) = 93.6; // // tpc padrow radii            
                   ///tprs . rpads.at(7) = 93.6; // // tpc padrow radii            
                   tprs . rpads.at(8) = 98.8; // // tpc padrow radii            
                   ///tprs . rpads.at(8) = 98.8; // // tpc padrow radii            
                   tprs . rpads.at(9) = 104.0; // // tpc padrow radii            
                   ///tprs . rpads.at(9) = 104.0; // // tpc padrow radii            
                   tprs . rpads.at(10) = 109.2; // // tpc padrow radii            
                   ///tprs . rpads.at(10) = 109.2; // // tpc padrow radii            
                   tprs . rpads.at(11) = 114.4; // // tpc padrow radii            
                   ///tprs . rpads.at(11) = 114.4; // // tpc padrow radii            
                   tprs . rpads.at(12) = 119.6 ; // // tpc padrow radii            
                   ///tprs . rpads.at(12) = 119.6 ; // // tpc padrow radii            
                   //           
                   tprs.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tprs_doc        
             ///@{           
                   ++tprs._index;           
                   tprs . sec = 2; // // sector number: 1 for inner, 2 for outer            
                   /// tprs . sec = 2; // // sector number: 1 for inner, 2 for outer            
                   tprs . nrow = 32; // // number of padrows in outer sector            
                   /// tprs . nrow = 32; // // number of padrows in outer sector            
                   tprs . pitch = 0.67; // // outer tpc padrow pitch width            
                   /// tprs . pitch = 0.67; // // outer tpc padrow pitch width            
                   tprs . width = 1.95; // // outer tpc padrow thickness            
                   /// tprs . width = 1.95; // // outer tpc padrow thickness            
                   tprs . super = 1; // // number of padrows in a superpadrow            
                   /// tprs . super = 1; // // number of padrows in a superpadrow            
                   tprs . danode = 0.4; // // distance to anode wire from pad plane            
                   /// tprs . danode = 0.4; // // distance to anode wire from pad plane            
                   tprs . npads.at(0) = 98; // // number of pads in row            
                   ///tprs . npads.at(0) = 98; // // number of pads in row            
                   tprs . npads.at(1) = 100; // // number of pads in row            
                   ///tprs . npads.at(1) = 100; // // number of pads in row            
                   tprs . npads.at(2) = 102; // // number of pads in row            
                   ///tprs . npads.at(2) = 102; // // number of pads in row            
                   tprs . npads.at(3) = 104; // // number of pads in row            
                   ///tprs . npads.at(3) = 104; // // number of pads in row            
                   tprs . npads.at(4) = 106; // // number of pads in row            
                   ///tprs . npads.at(4) = 106; // // number of pads in row            
                   tprs . npads.at(5) = 106; // // number of pads in row            
                   ///tprs . npads.at(5) = 106; // // number of pads in row            
                   tprs . npads.at(6) = 108; // // number of pads in row            
                   ///tprs . npads.at(6) = 108; // // number of pads in row            
                   tprs . npads.at(7) = 110; // // number of pads in row            
                   ///tprs . npads.at(7) = 110; // // number of pads in row            
                   tprs . npads.at(8) = 112; // // number of pads in row            
                   ///tprs . npads.at(8) = 112; // // number of pads in row            
                   tprs . npads.at(9) = 112 ; // // number of pads in row            
                   ///tprs . npads.at(9) = 112 ; // // number of pads in row            
                   tprs . npads.at(10) = 114; // // number of pads in row            
                   ///tprs . npads.at(10) = 114; // // number of pads in row            
                   tprs . npads.at(11) = 116; // // number of pads in row            
                   ///tprs . npads.at(11) = 116; // // number of pads in row            
                   tprs . npads.at(12) = 118; // // number of pads in row            
                   ///tprs . npads.at(12) = 118; // // number of pads in row            
                   tprs . npads.at(13) = 120; // // number of pads in row            
                   ///tprs . npads.at(13) = 120; // // number of pads in row            
                   tprs . npads.at(14) = 122; // // number of pads in row            
                   ///tprs . npads.at(14) = 122; // // number of pads in row            
                   tprs . npads.at(15) = 122; // // number of pads in row            
                   ///tprs . npads.at(15) = 122; // // number of pads in row            
                   tprs . npads.at(16) = 124; // // number of pads in row            
                   ///tprs . npads.at(16) = 124; // // number of pads in row            
                   tprs . npads.at(17) = 126; // // number of pads in row            
                   ///tprs . npads.at(17) = 126; // // number of pads in row            
                   tprs . npads.at(18) = 128 ; // // number of pads in row            
                   ///tprs . npads.at(18) = 128 ; // // number of pads in row            
                   tprs . npads.at(19) = 128; // // number of pads in row            
                   ///tprs . npads.at(19) = 128; // // number of pads in row            
                   tprs . npads.at(20) = 130; // // number of pads in row            
                   ///tprs . npads.at(20) = 130; // // number of pads in row            
                   tprs . npads.at(21) = 132; // // number of pads in row            
                   ///tprs . npads.at(21) = 132; // // number of pads in row            
                   tprs . npads.at(22) = 134; // // number of pads in row            
                   ///tprs . npads.at(22) = 134; // // number of pads in row            
                   tprs . npads.at(23) = 136; // // number of pads in row            
                   ///tprs . npads.at(23) = 136; // // number of pads in row            
                   tprs . npads.at(24) = 138; // // number of pads in row            
                   ///tprs . npads.at(24) = 138; // // number of pads in row            
                   tprs . npads.at(25) = 138; // // number of pads in row            
                   ///tprs . npads.at(25) = 138; // // number of pads in row            
                   tprs . npads.at(26) = 140; // // number of pads in row            
                   ///tprs . npads.at(26) = 140; // // number of pads in row            
                   tprs . npads.at(27) = 142 ; // // number of pads in row            
                   ///tprs . npads.at(27) = 142 ; // // number of pads in row            
                   tprs . npads.at(28) = 144; // // number of pads in row            
                   ///tprs . npads.at(28) = 144; // // number of pads in row            
                   tprs . npads.at(29) = 144; // // number of pads in row            
                   ///tprs . npads.at(29) = 144; // // number of pads in row            
                   tprs . npads.at(30) = 144; // // number of pads in row            
                   ///tprs . npads.at(30) = 144; // // number of pads in row            
                   tprs . npads.at(31) = 144 ; // // number of pads in row            
                   ///tprs . npads.at(31) = 144 ; // // number of pads in row            
                   tprs . rpads.at(0) = 127.195; // // tpc padrow radii            
                   ///tprs . rpads.at(0) = 127.195; // // tpc padrow radii            
                   tprs . rpads.at(1) = 129.195; // // tpc padrow radii            
                   ///tprs . rpads.at(1) = 129.195; // // tpc padrow radii            
                   tprs . rpads.at(2) = 131.195; // // tpc padrow radii            
                   ///tprs . rpads.at(2) = 131.195; // // tpc padrow radii            
                   tprs . rpads.at(3) = 133.195; // // tpc padrow radii            
                   ///tprs . rpads.at(3) = 133.195; // // tpc padrow radii            
                   tprs . rpads.at(4) = 135.195; // // tpc padrow radii            
                   ///tprs . rpads.at(4) = 135.195; // // tpc padrow radii            
                   tprs . rpads.at(5) = 137.195; // // tpc padrow radii            
                   ///tprs . rpads.at(5) = 137.195; // // tpc padrow radii            
                   tprs . rpads.at(6) = 139.195; // // tpc padrow radii            
                   ///tprs . rpads.at(6) = 139.195; // // tpc padrow radii            
                   tprs . rpads.at(7) = 141.195; // // tpc padrow radii            
                   ///tprs . rpads.at(7) = 141.195; // // tpc padrow radii            
                   tprs . rpads.at(8) = 143.195; // // tpc padrow radii            
                   ///tprs . rpads.at(8) = 143.195; // // tpc padrow radii            
                   tprs . rpads.at(9) = 145.195; // // tpc padrow radii            
                   ///tprs . rpads.at(9) = 145.195; // // tpc padrow radii            
                   tprs . rpads.at(10) = 147.195; // // tpc padrow radii            
                   ///tprs . rpads.at(10) = 147.195; // // tpc padrow radii            
                   tprs . rpads.at(11) = 149.195; // // tpc padrow radii            
                   ///tprs . rpads.at(11) = 149.195; // // tpc padrow radii            
                   tprs . rpads.at(12) = 151.195; // // tpc padrow radii            
                   ///tprs . rpads.at(12) = 151.195; // // tpc padrow radii            
                   tprs . rpads.at(13) = 153.195; // // tpc padrow radii            
                   ///tprs . rpads.at(13) = 153.195; // // tpc padrow radii            
                   tprs . rpads.at(14) = 155.195; // // tpc padrow radii            
                   ///tprs . rpads.at(14) = 155.195; // // tpc padrow radii            
                   tprs . rpads.at(15) = 157.195; // // tpc padrow radii            
                   ///tprs . rpads.at(15) = 157.195; // // tpc padrow radii            
                   tprs . rpads.at(16) = 159.195; // // tpc padrow radii            
                   ///tprs . rpads.at(16) = 159.195; // // tpc padrow radii            
                   tprs . rpads.at(17) = 161.195; // // tpc padrow radii            
                   ///tprs . rpads.at(17) = 161.195; // // tpc padrow radii            
                   tprs . rpads.at(18) = 163.195; // // tpc padrow radii            
                   ///tprs . rpads.at(18) = 163.195; // // tpc padrow radii            
                   tprs . rpads.at(19) = 165.195; // // tpc padrow radii            
                   ///tprs . rpads.at(19) = 165.195; // // tpc padrow radii            
                   tprs . rpads.at(20) = 167.195; // // tpc padrow radii            
                   ///tprs . rpads.at(20) = 167.195; // // tpc padrow radii            
                   tprs . rpads.at(21) = 169.195; // // tpc padrow radii            
                   ///tprs . rpads.at(21) = 169.195; // // tpc padrow radii            
                   tprs . rpads.at(22) = 171.195; // // tpc padrow radii            
                   ///tprs . rpads.at(22) = 171.195; // // tpc padrow radii            
                   tprs . rpads.at(23) = 173.195; // // tpc padrow radii            
                   ///tprs . rpads.at(23) = 173.195; // // tpc padrow radii            
                   tprs . rpads.at(24) = 175.195; // // tpc padrow radii            
                   ///tprs . rpads.at(24) = 175.195; // // tpc padrow radii            
                   tprs . rpads.at(25) = 177.195; // // tpc padrow radii            
                   ///tprs . rpads.at(25) = 177.195; // // tpc padrow radii            
                   tprs . rpads.at(26) = 179.195; // // tpc padrow radii            
                   ///tprs . rpads.at(26) = 179.195; // // tpc padrow radii            
                   tprs . rpads.at(27) = 181.195; // // tpc padrow radii            
                   ///tprs . rpads.at(27) = 181.195; // // tpc padrow radii            
                   tprs . rpads.at(28) = 183.195; // // tpc padrow radii            
                   ///tprs . rpads.at(28) = 183.195; // // tpc padrow radii            
                   tprs . rpads.at(29) = 185.195; // // tpc padrow radii            
                   ///tprs . rpads.at(29) = 185.195; // // tpc padrow radii            
                   tprs . rpads.at(30) = 187.195; // // tpc padrow radii            
                   ///tprs . rpads.at(30) = 187.195; // // tpc padrow radii            
                   tprs . rpads.at(31) = 189.195 ; // // tpc padrow radii            
                   ///tprs . rpads.at(31) = 189.195 ; // // tpc padrow radii            
                   //           
                   tprs.fill();           
             ///@}        
             //        
             /// USE tprs _index=1;        
             tprs.Use();        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tecw_doc        
             ///@{           
                   ++tecw._index;           
                   tecw . sec = 1; // // sec   => sector number: 1 for inner, 2 for outer            
                   /// tecw . sec = 1; // // sec   => sector number: 1 for inner, 2 for outer            
                   tecw . gapwidi = 2.* 10.91; // // GapWidI  => air in support wheel - inner width            
                   /// tecw . gapwidi = 2.* 10.91; // // GapWidI  => air in support wheel - inner width            
                   tecw . gapwido = 2.* 27.56; // // GapWidO  => air in support wheel - outer width            
                   /// tecw . gapwido = 2.* 27.56; // // GapWidO  => air in support wheel - outer width            
                   tecw . gapheit = 62.15; // // GapHeit  => air in support wheel - Height (dr)            
                   /// tecw . gapheit = 62.15; // // GapHeit  => air in support wheel - Height (dr)            
                   tecw . gaprad = 87.0; // // GapRad   => air in support wheel - center radius            
                   /// tecw . gaprad = 87.0; // // GapRad   => air in support wheel - center radius            
                   tecw . inwidth = 10.829*inch; // //2.* 13.75,   ;//// inwidth  => sector width at inner radius            
                   /// tecw . inwidth = 10.829*inch; // //2.* 13.75,   ;//// inwidth  => sector width at inner radius            
                   tecw . ouwidth = 25.498*inch; // //2.* 32.38,   ;//// ouwidth  => sector width at outer radius            
                   /// tecw . ouwidth = 25.498*inch; // //2.* 32.38,   ;//// ouwidth  => sector width at outer radius            
                   tecw . noribs = 11; // // noribs            
                   /// tecw . noribs = 11; // // noribs            
                   tecw . zsteprib = 3.150*inch; // // zStepRib            
                   /// tecw . zsteprib = 3.150*inch; // // zStepRib            
                   tecw . widthrib = 1.47*cos(15./180*acos(-1.))*inch; // // widthRib => side rib width            
                   /// tecw . widthrib = 1.47*cos(15./180*acos(-1.))*inch; // // widthRib => side rib width            
                   tecw . height = 27.373*inch; // // Drawing 24A3685B 27.77*INCH from drawing 24A0325,     ;//// => 69.527 => (Wire Plane)  69.52,  Height   => sector radial Height           
                   /// tecw . height = 27.373*inch; // // Drawing 24A3685B 27.77*INCH from drawing 24A0325,     ;//// => 69.527 => (Wire Plane)  69.52,  Height   => sector radial Height           
                   tecw . thick = 3.300*inch; // // 24A3685B  3.219*INCH        ;//// Thick    => sector thickness            
                   /// tecw . thick = 3.300*inch; // // 24A3685B  3.219*INCH        ;//// Thick    => sector thickness            
                   tecw . thickal = 0.375*inch; // //             
                   /// tecw . thickal = 0.375*inch; // //             
                   tecw . rmin = 51.905; // // rMin     => Minimum distance to beam line (wire plane)            
                   /// tecw . rmin = 51.905; // // rMin     => Minimum distance to beam line (wire plane)            
                   tecw . rcenter = 86.669; // // Rcenter  => sector center radius (set by precision holes)            
                   /// tecw . rcenter = 86.669; // // Rcenter  => sector center radius (set by precision holes)            
                   tecw . holedx = 0.750/2*inch; // // = 0.9525 cm            
                   /// tecw . holedx = 0.750/2*inch; // // = 0.9525 cm            
                   tecw . holedy = 2.625/2*inch; // // = 3.33375 cm            
                   /// tecw . holedy = 2.625/2*inch; // // = 3.33375 cm            
                   //           
                   tecw.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tecw_doc        
             ///@{           
                   ++tecw._index;           
                   tecw . sec = 2; // // sec    => sector number: 1 for inner, 2 for outer            
                   /// tecw . sec = 2; // // sec    => sector number: 1 for inner, 2 for outer            
                   tecw . gapwidi = 2.* 28.92; // // GapWidI  => air in support wheel - inner width            
                   /// tecw . gapwidi = 2.* 28.92; // // GapWidI  => air in support wheel - inner width            
                   tecw . gapwido = 2.* 46.74; // // GapWidO  => air in support wheel - outer width            
                   /// tecw . gapwido = 2.* 46.74; // // GapWidO  => air in support wheel - outer width            
                   tecw . gapheit = 65.0; // // GapHeit  => air in support wheel - Height (dr)            
                   /// tecw . gapheit = 65.0; // // GapHeit  => air in support wheel - Height (dr)            
                   tecw . gaprad = 158.0; // // aGapRad   => ir in support wheel - radius            
                   /// tecw . gaprad = 158.0; // // aGapRad   => ir in support wheel - radius            
                   tecw . inwidth = 25.561*inch; // //64.92,       ;//// inwidth  => sector width at inner radius            
                   /// tecw . inwidth = 25.561*inch; // //64.92,       ;//// inwidth  => sector width at inner radius            
                   tecw . ouwidth = 40.649*inch; // //103.25,      ;//// ouwidth  => sector width at outer radius            
                   /// tecw . ouwidth = 40.649*inch; // //103.25,      ;//// ouwidth  => sector width at outer radius            
                   tecw . widthlip = ((25.561-24.583)+(40.649-39.671))/4*inch; // // = 1.242060 widthLip =>  width of lip            
                   /// tecw . widthlip = ((25.561-24.583)+(40.649-39.671))/4*inch; // // = 1.242060 widthLip =>  width of lip            
                   tecw . noribs = 14; // // noribs            
                   /// tecw . noribs = 14; // // noribs            
                   tecw . zsteprib = 3.150*inch; // // zStepRib            
                   /// tecw . zsteprib = 3.150*inch; // // zStepRib            
                   tecw . widthrib = 1.47*cos(15./180*acos(-1.))*inch; // // widthRib = > side rib width            
                   /// tecw . widthrib = 1.47*cos(15./180*acos(-1.))*inch; // // widthRib = > side rib width            
                   tecw . height = 28.155*inch; // // 71.514 (Wire Plane) => 71.51,       ;//// Height   => sector radial Height            
                   /// tecw . height = 28.155*inch; // // 71.514 (Wire Plane) => 71.51,       ;//// Height   => sector radial Height            
                   tecw . thick = 3.140*inch; // // 24A3925G thick    => sector thickness            
                   /// tecw . thick = 3.140*inch; // // 24A3925G thick    => sector thickness            
                   tecw . thickal = 0.375*inch; // //             
                   /// tecw . thickal = 0.375*inch; // //             
                   tecw . rmin = 121.732; // // rMin     => Minimum distance to beam line (wire plane)            
                   /// tecw . rmin = 121.732; // // rMin     => Minimum distance to beam line (wire plane)            
                   tecw . rcenter = 157.488; // // Rcenter  => sector center radius (set by precision holes)            
                   /// tecw . rcenter = 157.488; // // Rcenter  => sector center radius (set by precision holes)            
                   tecw . holedx = 0.750/2*inch; // //            
                   /// tecw . holedx = 0.750/2*inch; // //            
                   tecw . holedy = 2.500/2*inch; // //            
                   /// tecw . holedy = 2.500/2*inch; // //            
                   //           
                   tecw.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tpcr_doc        
             ///@{           
                   ++tpcr._index;           
                   tpcr . rdovthk = 30.; // // length of RDO volume            
                   /// tpcr . rdovthk = 30.; // // length of RDO volume            
                   tpcr . rdothk = .25; // // thickness of rdo card            
                   /// tpcr . rdothk = .25; // // thickness of rdo card            
                   tpcr . rdolen = 27; // // card length along beam direction            
                   /// tpcr . rdolen = 27; // // card length along beam direction            
                   tpcr . nrdobrd = 9; // // number of RDO boards            
                   /// tpcr . nrdobrd = 9; // // number of RDO boards            
                   tpcr . rdoht.at(0) = 60.0; // // radial pos of rdo boards            
                   ///tpcr . rdoht.at(0) = 60.0; // // radial pos of rdo boards            
                   tpcr . rdoht.at(1) = 74.0; // // radial pos of rdo boards            
                   ///tpcr . rdoht.at(1) = 74.0; // // radial pos of rdo boards            
                   tpcr . rdoht.at(2) = 84.0; // // radial pos of rdo boards            
                   ///tpcr . rdoht.at(2) = 84.0; // // radial pos of rdo boards            
                   tpcr . rdoht.at(3) = 101.0; // // radial pos of rdo boards            
                   ///tpcr . rdoht.at(3) = 101.0; // // radial pos of rdo boards            
                   tpcr . rdoht.at(4) = 106.0; // // radial pos of rdo boards            
                   ///tpcr . rdoht.at(4) = 106.0; // // radial pos of rdo boards            
                   tpcr . rdoht.at(5) = 126.0; // // radial pos of rdo boards            
                   ///tpcr . rdoht.at(5) = 126.0; // // radial pos of rdo boards            
                   tpcr . rdoht.at(6) = 146.0; // // radial pos of rdo boards            
                   ///tpcr . rdoht.at(6) = 146.0; // // radial pos of rdo boards            
                   tpcr . rdoht.at(7) = 166.0; // // radial pos of rdo boards            
                   ///tpcr . rdoht.at(7) = 166.0; // // radial pos of rdo boards            
                   tpcr . rdoht.at(8) = 186.0; // // radial pos of rdo boards            
                   ///tpcr . rdoht.at(8) = 186.0; // // radial pos of rdo boards            
                   //           
                   tpcr.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup tfee_doc        
             ///@{           
                   ++tfee._index;           
                   tfee . vers = 1; // // version of FrontEndElectronics            
                   /// tfee . vers = 1; // // version of FrontEndElectronics            
                   tfee . carddx = 1.47*0.110*inch/2; // // 1.47 scale factor account for 9 lb of cables            
                   /// tfee . carddx = 1.47*0.110*inch/2; // // 1.47 scale factor account for 9 lb of cables            
                   tfee . carddy = 2.900*inch/2; // //...            
                   /// tfee . carddy = 2.900*inch/2; // //...            
                   tfee . carddz = 7.000*inch/2; // //...            
                   /// tfee . carddz = 7.000*inch/2; // //...            
                   tfee . platedx = 0.110*inch/2; // //...            
                   /// tfee . platedx = 0.110*inch/2; // //...            
                   tfee . platedy = 1.480*inch; // //...            
                   /// tfee . platedy = 1.480*inch; // //...            
                   tfee . platedz = 4.650*inch/2; // //...            
                   /// tfee . platedz = 4.650*inch/2; // //...            
                   tfee . assemblythickness = tfee.carddx + tfee.platedx; // //...            
                   /// tfee . assemblythickness = tfee.carddx + tfee.platedx; // //...            
                   tfee . ribdx = 0.820*inch/2 - 2*   tfee.carddx; // //...            
                   /// tfee . ribdx = 0.820*inch/2 - 2*   tfee.carddx; // //...            
                   tfee . ribdy = 2.900*inch/2 - 2*   tfee.carddx; // //...            
                   /// tfee . ribdy = 2.900*inch/2 - 2*   tfee.carddx; // //...            
                   tfee . ribdz = tfee.carddx; // //...            
                   /// tfee . ribdz = tfee.carddx; // //...            
                   tfee . ass.at(0) = 1.6; // // Fee assembly brik size            
                   ///tfee . ass.at(0) = 1.6; // // Fee assembly brik size            
                   tfee . ass.at(1) = 4; // // Fee assembly brik size            
                   ///tfee . ass.at(1) = 4; // // Fee assembly brik size            
                   tfee . ass.at(2) = 10; // // Fee assembly brik size            
                   ///tfee . ass.at(2) = 10; // // Fee assembly brik size            
                   //           
                   tfee.fill();           
             ///@}        
             //        
             /// USE tecw sec=kinner+1 ;        
             tecw.Use("sec",(Float_t)kinner+1 );        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup ribs_doc        
             ///@{           
                   ++ribs._index;           
                   ribs . version = kinner; // // version number            
                   /// ribs . version = kinner; // // version number            
                   ribs . inout = kinner; // // selctor            
                   /// ribs . inout = kinner; // // selctor            
                   ribs . num = 11; // // number of elements             
                   /// ribs . num = 11; // // number of elements             
                   ribs . x.at(0) = 0.000; // // x            
                   ///ribs . x.at(0) = 0.000; // // x            
                   ribs . x.at(1) = 4.261; // // x            
                   ///ribs . x.at(1) = 4.261; // // x            
                   ribs . x.at(2) = 10.561; // // x            
                   ///ribs . x.at(2) = 10.561; // // x            
                   ribs . x.at(3) = 16.861; // // x            
                   ///ribs . x.at(3) = 16.861; // // x            
                   ribs . x.at(4) = 23.161; // // x            
                   ///ribs . x.at(4) = 23.161; // // x            
                   ribs . x.at(5) = 25.950; // // x            
                   ///ribs . x.at(5) = 25.950; // // x            
                   ribs . x.at(6) = 3.726; // // x            
                   ///ribs . x.at(6) = 3.726; // // x            
                   ribs . x.at(7) = 3.726; // // x            
                   ///ribs . x.at(7) = 3.726; // // x            
                   ribs . x.at(8) = 10.026; // // x            
                   ///ribs . x.at(8) = 10.026; // // x            
                   ribs . x.at(9) = 10.026; // // x            
                   ///ribs . x.at(9) = 10.026; // // x            
                   ribs . x.at(10) = 25.480 ; // // x            
                   ///ribs . x.at(10) = 25.480 ; // // x            
                   ribs . y.at(0) = 0.000; // // y              
                   ///ribs . y.at(0) = 0.000; // // y              
                   ribs . y.at(1) = 0.000; // // y              
                   ///ribs . y.at(1) = 0.000; // // y              
                   ribs . y.at(2) = 0.000; // // y              
                   ///ribs . y.at(2) = 0.000; // // y              
                   ribs . y.at(3) = 0.000; // // y              
                   ///ribs . y.at(3) = 0.000; // // y              
                   ribs . y.at(4) = 0.000; // // y              
                   ///ribs . y.at(4) = 0.000; // // y              
                   ribs . y.at(5) = 0.000; // // y              
                   ///ribs . y.at(5) = 0.000; // // y              
                   ribs . y.at(6) = -5.645; // // y              
                   ///ribs . y.at(6) = -5.645; // // y              
                   ribs . y.at(7) = 5.645; // // y              
                   ///ribs . y.at(7) = 5.645; // // y              
                   ribs . y.at(8) = -3.895; // // y              
                   ///ribs . y.at(8) = -3.895; // // y              
                   ribs . y.at(9) = 3.895; // // y              
                   ///ribs . y.at(9) = 3.895; // // y              
                   ribs . y.at(10) = 0.000        ; // // y              
                   ///ribs . y.at(10) = 0.000        ; // // y              
                   ribs . dx.at(0) = 1.470; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(0) = 1.470; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(1) = 0.375; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(1) = 0.375; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(2) = 0.375 ; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(2) = 0.375 ; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(3) = 0.375 ; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(3) = 0.375 ; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(4) = 0.375 ; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(4) = 0.375 ; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(5) = tecw.height/inch-25.950; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(5) = tecw.height/inch-25.950; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(6) = 1.070; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(6) = 1.070; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(7) = 1.070; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(7) = 1.070; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(8) = 1.070; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(8) = 1.070; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(9) = 1.070; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(9) = 1.070; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dx.at(10) = 0.940 ; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ///ribs . dx.at(10) = 0.940 ; // // dx  ... last=2*(25.950-(1.050+2.515+21.915))             
                   ribs . dy.at(0) = 0.; // // dy             
                   ///ribs . dy.at(0) = 0.; // // dy             
                   ribs . dy.at(1) = 0.; // // dy             
                   ///ribs . dy.at(1) = 0.; // // dy             
                   ribs . dy.at(2) = 0.; // // dy             
                   ///ribs . dy.at(2) = 0.; // // dy             
                   ribs . dy.at(3) = 0.; // // dy             
                   ///ribs . dy.at(3) = 0.; // // dy             
                   ribs . dy.at(4) = 0.; // // dy             
                   ///ribs . dy.at(4) = 0.; // // dy             
                   ribs . dy.at(5) = 0.; // // dy             
                   ///ribs . dy.at(5) = 0.; // // dy             
                   ribs . dy.at(6) = 0.750; // // dy             
                   ///ribs . dy.at(6) = 0.750; // // dy             
                   ribs . dy.at(7) = 0.750; // // dy             
                   ///ribs . dy.at(7) = 0.750; // // dy             
                   ribs . dy.at(8) = 0.750; // // dy             
                   ///ribs . dy.at(8) = 0.750; // // dy             
                   ribs . dy.at(9) = 0.750; // // dy             
                   ///ribs . dy.at(9) = 0.750; // // dy             
                   ribs . dy.at(10) = 2.0; // // dy             
                   ///ribs . dy.at(10) = 2.0; // // dy             
                   //           
                   ribs.fill();           
             ///@}        
             //        
             /// USE tecw sec=kouter+1 ;        
             tecw.Use("sec",(Float_t)kouter+1 );        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup ribs_doc        
             ///@{           
                   ++ribs._index;           
                   ribs . version = kouter; // // version number            
                   /// ribs . version = kouter; // // version number            
                   ribs . inout = kouter; // // selctor            
                   /// ribs . inout = kouter; // // selctor            
                   ribs . num = 14; // // number of elements             
                   /// ribs . num = 14; // // number of elements             
                   ribs . x.at(0) = 0.280; // // x            
                   ///ribs . x.at(0) = 0.280; // // x            
                   ribs . x.at(1) = 4.261; // // x            
                   ///ribs . x.at(1) = 4.261; // // x            
                   ribs . x.at(2) = 7.410; // // x            
                   ///ribs . x.at(2) = 7.410; // // x            
                   ribs . x.at(3) = 10.560; // // x            
                   ///ribs . x.at(3) = 10.560; // // x            
                   ribs . x.at(4) = 13.710; // // x            
                   ///ribs . x.at(4) = 13.710; // // x            
                   ribs . x.at(5) = 16.859; // // x            
                   ///ribs . x.at(5) = 16.859; // // x            
                   ribs . x.at(6) = 20.009; // // x            
                   ///ribs . x.at(6) = 20.009; // // x            
                   ribs . x.at(7) = 23.158; // // x            
                   ///ribs . x.at(7) = 23.158; // // x            
                   ribs . x.at(8) = 26.309; // // x            
                   ///ribs . x.at(8) = 26.309; // // x            
                   ribs . x.at(9) = 6.023; // // x            
                   ///ribs . x.at(9) = 6.023; // // x            
                   ribs . x.at(10) = 6.023; // // x            
                   ///ribs . x.at(10) = 6.023; // // x            
                   ribs . x.at(11) = 12.3225; // // x            
                   ///ribs . x.at(11) = 12.3225; // // x            
                   ribs . x.at(12) = 15.472; // // x            
                   ///ribs . x.at(12) = 15.472; // // x            
                   ribs . x.at(13) = 26.309-1.575/2; // // x            
                   ///ribs . x.at(13) = 26.309-1.575/2; // // x            
                   ribs . y.at(0) = 0; // // y            
                   ///ribs . y.at(0) = 0; // // y            
                   ribs . y.at(1) = 0; // // y            
                   ///ribs . y.at(1) = 0; // // y            
                   ribs . y.at(2) = 0; // // y            
                   ///ribs . y.at(2) = 0; // // y            
                   ribs . y.at(3) = 0; // // y            
                   ///ribs . y.at(3) = 0; // // y            
                   ribs . y.at(4) = 0; // // y            
                   ///ribs . y.at(4) = 0; // // y            
                   ribs . y.at(5) = 0; // // y            
                   ///ribs . y.at(5) = 0; // // y            
                   ribs . y.at(6) = 0; // // y            
                   ///ribs . y.at(6) = 0; // // y            
                   ribs . y.at(7) = 0; // // y            
                   ///ribs . y.at(7) = 0; // // y            
                   ribs . y.at(8) = 0; // // y            
                   ///ribs . y.at(8) = 0; // // y            
                   ribs . y.at(9) = 17.250/2; // // y            
                   ///ribs . y.at(9) = 17.250/2; // // y            
                   ribs . y.at(10) = -17.250/2; // // y            
                   ///ribs . y.at(10) = -17.250/2; // // y            
                   ribs . y.at(11) = 0; // // y            
                   ///ribs . y.at(11) = 0; // // y            
                   ribs . y.at(12) = 0; // // y            
                   ///ribs . y.at(12) = 0; // // y            
                   ribs . y.at(13) = 0; // // y            
                   ///ribs . y.at(13) = 0; // // y            
                   ribs . dx.at(0) = 1.268; // // dx            
                   ///ribs . dx.at(0) = 1.268; // // dx            
                   ribs . dx.at(1) = 0.375; // // dx            
                   ///ribs . dx.at(1) = 0.375; // // dx            
                   ribs . dx.at(2) = 0.375; // // dx            
                   ///ribs . dx.at(2) = 0.375; // // dx            
                   ribs . dx.at(3) = 0.375; // // dx            
                   ///ribs . dx.at(3) = 0.375; // // dx            
                   ribs . dx.at(4) = 0.375; // // dx            
                   ///ribs . dx.at(4) = 0.375; // // dx            
                   ribs . dx.at(5) = 0.375; // // dx            
                   ///ribs . dx.at(5) = 0.375; // // dx            
                   ribs . dx.at(6) = 0.375; // // dx            
                   ///ribs . dx.at(6) = 0.375; // // dx            
                   ribs . dx.at(7) = 0.375; // // dx            
                   ///ribs . dx.at(7) = 0.375; // // dx            
                   ribs . dx.at(8) = 1.566; // // dx            
                   ///ribs . dx.at(8) = 1.566; // // dx            
                   ribs . dx.at(9) = 2.774; // // dx            
                   ///ribs . dx.at(9) = 2.774; // // dx            
                   ribs . dx.at(10) = 2.774; // // dx            
                   ///ribs . dx.at(10) = 2.774; // // dx            
                   ribs . dx.at(11) = 2.775; // // dx            
                   ///ribs . dx.at(11) = 2.775; // // dx            
                   ribs . dx.at(12) = 2.774; // // dx            
                   ///ribs . dx.at(12) = 2.774; // // dx            
                   ribs . dx.at(13) = 1.575 ; // // dx            
                   ///ribs . dx.at(13) = 1.575 ; // // dx            
                   ribs . dy.at(0) = 0; // // dy            
                   ///ribs . dy.at(0) = 0; // // dy            
                   ribs . dy.at(1) = 0; // // dy            
                   ///ribs . dy.at(1) = 0; // // dy            
                   ribs . dy.at(2) = 0; // // dy            
                   ///ribs . dy.at(2) = 0; // // dy            
                   ribs . dy.at(3) = 0; // // dy            
                   ///ribs . dy.at(3) = 0; // // dy            
                   ribs . dy.at(4) = 0; // // dy            
                   ///ribs . dy.at(4) = 0; // // dy            
                   ribs . dy.at(5) = 0; // // dy            
                   ///ribs . dy.at(5) = 0; // // dy            
                   ribs . dy.at(6) = 0; // // dy            
                   ///ribs . dy.at(6) = 0; // // dy            
                   ribs . dy.at(7) = 0; // // dy            
                   ///ribs . dy.at(7) = 0; // // dy            
                   ribs . dy.at(8) = 0; // // dy            
                   ///ribs . dy.at(8) = 0; // // dy            
                   ribs . dy.at(9) = 1.250; // // dy            
                   ///ribs . dy.at(9) = 1.250; // // dy            
                   ribs . dy.at(10) = 1.250; // // dy            
                   ///ribs . dy.at(10) = 1.250; // // dy            
                   ribs . dy.at(11) = 0.375; // // dy            
                   ///ribs . dy.at(11) = 0.375; // // dy            
                   ribs . dy.at(12) = 0.375; // // dy            
                   ///ribs . dy.at(12) = 0.375; // // dy            
                   ribs . dy.at(13) = 1.5680; // // dy            
                   ///ribs . dy.at(13) = 1.5680; // // dy            
                   //           
                   ribs.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup holz_doc        
             ///@{           
                   ++holz._index;           
                   holz . inout = kinner; // // selector            
                   /// holz . inout = kinner; // // selector            
                   holz . numberofrows = 15; // // Number of rows            
                   /// holz . numberofrows = 15; // // Number of rows            
                   holz . numberperrow.at(0) = 6; // // n/row            
                   ///holz . numberperrow.at(0) = 6; // // n/row            
                   holz . numberperrow.at(1) = 5; // // n/row            
                   ///holz . numberperrow.at(1) = 5; // // n/row            
                   holz . numberperrow.at(2) = 5; // // n/row            
                   ///holz . numberperrow.at(2) = 5; // // n/row            
                   holz . numberperrow.at(3) = 2; // // n/row            
                   ///holz . numberperrow.at(3) = 2; // // n/row            
                   holz . numberperrow.at(4) = 5; // // n/row            
                   ///holz . numberperrow.at(4) = 5; // // n/row            
                   holz . numberperrow.at(5) = 4; // // n/row            
                   ///holz . numberperrow.at(5) = 4; // // n/row            
                   holz . numberperrow.at(6) = 4; // // n/row            
                   ///holz . numberperrow.at(6) = 4; // // n/row            
                   holz . numberperrow.at(7) = 4; // // n/row            
                   ///holz . numberperrow.at(7) = 4; // // n/row            
                   holz . numberperrow.at(8) = 4; // // n/row            
                   ///holz . numberperrow.at(8) = 4; // // n/row            
                   holz . numberperrow.at(9) = 3; // // n/row            
                   ///holz . numberperrow.at(9) = 3; // // n/row            
                   holz . numberperrow.at(10) = 3; // // n/row            
                   ///holz . numberperrow.at(10) = 3; // // n/row            
                   holz . numberperrow.at(11) = 3; // // n/row            
                   ///holz . numberperrow.at(11) = 3; // // n/row            
                   holz . numberperrow.at(12) = 3; // // n/row            
                   ///holz . numberperrow.at(12) = 3; // // n/row            
                   holz . numberperrow.at(13) = 2; // // n/row            
                   ///holz . numberperrow.at(13) = 2; // // n/row            
                   holz . numberperrow.at(14) = 2; // // n/row            
                   ///holz . numberperrow.at(14) = 2; // // n/row            
                   holz . numberperrow.at(15) = 0 ; // // n/row            
                   ///holz . numberperrow.at(15) = 0 ; // // n/row            
                   holz . yholes.at(0) = 3.180*(-2.5+0); // // y holes            
                   ///holz . yholes.at(0) = 3.180*(-2.5+0); // // y holes            
                   holz . yholes.at(1) = 3.180*(-2.5+1); // // y holes            
                   ///holz . yholes.at(1) = 3.180*(-2.5+1); // // y holes            
                   holz . yholes.at(2) = 3.180*(-2.5+2); // // y holes            
                   ///holz . yholes.at(2) = 3.180*(-2.5+2); // // y holes            
                   holz . yholes.at(3) = 3.180*(-2.5+3); // // y holes            
                   ///holz . yholes.at(3) = 3.180*(-2.5+3); // // y holes            
                   holz . yholes.at(4) = 3.180*(-2.5+4); // // y holes            
                   ///holz . yholes.at(4) = 3.180*(-2.5+4); // // y holes            
                   holz . yholes.at(5) = 3.180*(-2.5+5); // // y holes            
                   ///holz . yholes.at(5) = 3.180*(-2.5+5); // // y holes            
                   holz . yholes.at(6) = 3.180*(-2.5+6); // // y holes            
                   ///holz . yholes.at(6) = 3.180*(-2.5+6); // // y holes            
                   holz . yholes.at(7) = 3.180*(-2.5+7); // // y holes            
                   ///holz . yholes.at(7) = 3.180*(-2.5+7); // // y holes            
                   holz . yholes.at(8) = 3.180*(-2.5+8); // // y holes            
                   ///holz . yholes.at(8) = 3.180*(-2.5+8); // // y holes            
                   holz . yholes.at(9) = 3.764*(-2.0+0); // // y holes            
                   ///holz . yholes.at(9) = 3.764*(-2.0+0); // // y holes            
                   holz . yholes.at(10) = 3.764*(-2.0+1); // // y holes            
                   ///holz . yholes.at(10) = 3.764*(-2.0+1); // // y holes            
                   holz . yholes.at(11) = 3.764*(-2.0+2); // // y holes            
                   ///holz . yholes.at(11) = 3.764*(-2.0+2); // // y holes            
                   holz . yholes.at(12) = 3.764*(-2.0+3); // // y holes            
                   ///holz . yholes.at(12) = 3.764*(-2.0+3); // // y holes            
                   holz . yholes.at(13) = 3.764*(-2.0+4); // // y holes            
                   ///holz . yholes.at(13) = 3.764*(-2.0+4); // // y holes            
                   holz . yholes.at(14) = 3.764*(-2.0+5); // // y holes            
                   ///holz . yholes.at(14) = 3.764*(-2.0+5); // // y holes            
                   holz . yholes.at(15) = 3.764*(-2.0+6); // // y holes            
                   ///holz . yholes.at(15) = 3.764*(-2.0+6); // // y holes            
                   holz . yholes.at(16) = 3.764*(-2.0+7); // // y holes            
                   ///holz . yholes.at(16) = 3.764*(-2.0+7); // // y holes            
                   holz . yholes.at(17) = 3.764*(-2.0+8); // // y holes            
                   ///holz . yholes.at(17) = 3.764*(-2.0+8); // // y holes            
                   holz . yholes.at(18) = 3.553*(-2.0+0); // // y holes            
                   ///holz . yholes.at(18) = 3.553*(-2.0+0); // // y holes            
                   holz . yholes.at(19) = 3.553*(-2.0+1); // // y holes            
                   ///holz . yholes.at(19) = 3.553*(-2.0+1); // // y holes            
                   holz . yholes.at(20) = 3.553*(-2.0+2); // // y holes            
                   ///holz . yholes.at(20) = 3.553*(-2.0+2); // // y holes            
                   holz . yholes.at(21) = 3.553*(-2.0+3); // // y holes            
                   ///holz . yholes.at(21) = 3.553*(-2.0+3); // // y holes            
                   holz . yholes.at(22) = 3.553*(-2.0+4); // // y holes            
                   ///holz . yholes.at(22) = 3.553*(-2.0+4); // // y holes            
                   holz . yholes.at(23) = 3.553*(-2.0+5); // // y holes            
                   ///holz . yholes.at(23) = 3.553*(-2.0+5); // // y holes            
                   holz . yholes.at(24) = 3.553*(-2.0+6); // // y holes            
                   ///holz . yholes.at(24) = 3.553*(-2.0+6); // // y holes            
                   holz . yholes.at(25) = 3.553*(-2.0+7); // // y holes            
                   ///holz . yholes.at(25) = 3.553*(-2.0+7); // // y holes            
                   holz . yholes.at(26) = 3.553*(-2.0+8); // // y holes            
                   ///holz . yholes.at(26) = 3.553*(-2.0+8); // // y holes            
                   holz . yholes.at(27) = 13.368*(-0.5+0); // // y holes            
                   ///holz . yholes.at(27) = 13.368*(-0.5+0); // // y holes            
                   holz . yholes.at(28) = 13.368*(-0.5+1); // // y holes            
                   ///holz . yholes.at(28) = 13.368*(-0.5+1); // // y holes            
                   holz . yholes.at(29) = 13.368*(-0.5+2); // // y holes            
                   ///holz . yholes.at(29) = 13.368*(-0.5+2); // // y holes            
                   holz . yholes.at(30) = 13.368*(-0.5+3); // // y holes            
                   ///holz . yholes.at(30) = 13.368*(-0.5+3); // // y holes            
                   holz . yholes.at(31) = 13.368*(-0.5+4); // // y holes            
                   ///holz . yholes.at(31) = 13.368*(-0.5+4); // // y holes            
                   holz . yholes.at(32) = 13.368*(-0.5+5); // // y holes            
                   ///holz . yholes.at(32) = 13.368*(-0.5+5); // // y holes            
                   holz . yholes.at(33) = 13.368*(-0.5+6); // // y holes            
                   ///holz . yholes.at(33) = 13.368*(-0.5+6); // // y holes            
                   holz . yholes.at(34) = 13.368*(-0.5+7); // // y holes            
                   ///holz . yholes.at(34) = 13.368*(-0.5+7); // // y holes            
                   holz . yholes.at(35) = 13.368*(-0.5+8); // // y holes            
                   ///holz . yholes.at(35) = 13.368*(-0.5+8); // // y holes            
                   holz . yholes.at(36) = 3.131*(-2.0+0); // // y holes            
                   ///holz . yholes.at(36) = 3.131*(-2.0+0); // // y holes            
                   holz . yholes.at(37) = 3.131*(-2.0+1); // // y holes            
                   ///holz . yholes.at(37) = 3.131*(-2.0+1); // // y holes            
                   holz . yholes.at(38) = 3.131*(-2.0+2); // // y holes            
                   ///holz . yholes.at(38) = 3.131*(-2.0+2); // // y holes            
                   holz . yholes.at(39) = 3.131*(-2.0+3); // // y holes            
                   ///holz . yholes.at(39) = 3.131*(-2.0+3); // // y holes            
                   holz . yholes.at(40) = 3.131*(-2.0+4); // // y holes            
                   ///holz . yholes.at(40) = 3.131*(-2.0+4); // // y holes            
                   holz . yholes.at(41) = 3.131*(-2.0+5); // // y holes            
                   ///holz . yholes.at(41) = 3.131*(-2.0+5); // // y holes            
                   holz . yholes.at(42) = 3.131*(-2.0+6); // // y holes            
                   ///holz . yholes.at(42) = 3.131*(-2.0+6); // // y holes            
                   holz . yholes.at(43) = 3.131*(-2.0+7); // // y holes            
                   ///holz . yholes.at(43) = 3.131*(-2.0+7); // // y holes            
                   holz . yholes.at(44) = 3.131*(-2.0+8); // // y holes            
                   ///holz . yholes.at(44) = 3.131*(-2.0+8); // // y holes            
                   holz . yholes.at(45) = -3.892 - 1.948 ; // // y holes            
                   ///holz . yholes.at(45) = -3.892 - 1.948 ; // // y holes            
                   holz . yholes.at(46) = -1.948        ; // // y holes            
                   ///holz . yholes.at(46) = -1.948        ; // // y holes            
                   holz . yholes.at(47) = +1.948        ; // // y holes            
                   ///holz . yholes.at(47) = +1.948        ; // // y holes            
                   holz . yholes.at(48) = 3.892 + 1.948 ; // // y holes            
                   ///holz . yholes.at(48) = 3.892 + 1.948 ; // // y holes            
                   holz . yholes.at(49) = 0.000         ; // // y holes            
                   ///holz . yholes.at(49) = 0.000         ; // // y holes            
                   holz . yholes.at(50) = 0.000         ; // // y holes            
                   ///holz . yholes.at(50) = 0.000         ; // // y holes            
                   holz . yholes.at(51) = 0.000         ; // // y holes            
                   ///holz . yholes.at(51) = 0.000         ; // // y holes            
                   holz . yholes.at(52) = 0.000         ; // // y holes            
                   ///holz . yholes.at(52) = 0.000         ; // // y holes            
                   holz . yholes.at(53) = 0.000         ; // // y holes            
                   ///holz . yholes.at(53) = 0.000         ; // // y holes            
                   holz . yholes.at(54) = -3.611 - 1.807 ; // // y holes            
                   ///holz . yholes.at(54) = -3.611 - 1.807 ; // // y holes            
                   holz . yholes.at(55) = -1.807        ; // // y holes            
                   ///holz . yholes.at(55) = -1.807        ; // // y holes            
                   holz . yholes.at(56) = +1.807        ; // // y holes            
                   ///holz . yholes.at(56) = +1.807        ; // // y holes            
                   holz . yholes.at(57) = 3.611 + 1.807 ; // // y holes            
                   ///holz . yholes.at(57) = 3.611 + 1.807 ; // // y holes            
                   holz . yholes.at(58) = 0.000         ; // // y holes            
                   ///holz . yholes.at(58) = 0.000         ; // // y holes            
                   holz . yholes.at(59) = 0.000         ; // // y holes            
                   ///holz . yholes.at(59) = 0.000         ; // // y holes            
                   holz . yholes.at(60) = 0.000         ; // // y holes            
                   ///holz . yholes.at(60) = 0.000         ; // // y holes            
                   holz . yholes.at(61) = 0.000         ; // // y holes            
                   ///holz . yholes.at(61) = 0.000         ; // // y holes            
                   holz . yholes.at(62) = 0.000         ; // // y holes            
                   ///holz . yholes.at(62) = 0.000         ; // // y holes            
                   holz . yholes.at(63) = -3.281 - 1.7145; // // y holes            
                   ///holz . yholes.at(63) = -3.281 - 1.7145; // // y holes            
                   holz . yholes.at(64) = -1.7145       ; // // y holes            
                   ///holz . yholes.at(64) = -1.7145       ; // // y holes            
                   holz . yholes.at(65) = +1.7145       ; // // y holes            
                   ///holz . yholes.at(65) = +1.7145       ; // // y holes            
                   holz . yholes.at(66) = 3.281 + 1.7145; // // y holes            
                   ///holz . yholes.at(66) = 3.281 + 1.7145; // // y holes            
                   holz . yholes.at(67) = 0.000         ; // // y holes            
                   ///holz . yholes.at(67) = 0.000         ; // // y holes            
                   holz . yholes.at(68) = 0.000         ; // // y holes            
                   ///holz . yholes.at(68) = 0.000         ; // // y holes            
                   holz . yholes.at(69) = 0.000         ; // // y holes            
                   ///holz . yholes.at(69) = 0.000         ; // // y holes            
                   holz . yholes.at(70) = 0.000         ; // // y holes            
                   ///holz . yholes.at(70) = 0.000         ; // // y holes            
                   holz . yholes.at(71) = 0.000         ; // // y holes            
                   ///holz . yholes.at(71) = 0.000         ; // // y holes            
                   holz . yholes.at(72) = 3.150*(-1.5+0); // // y holes            
                   ///holz . yholes.at(72) = 3.150*(-1.5+0); // // y holes            
                   holz . yholes.at(73) = 3.150*(-1.5+1); // // y holes            
                   ///holz . yholes.at(73) = 3.150*(-1.5+1); // // y holes            
                   holz . yholes.at(74) = 3.150*(-1.5+2); // // y holes            
                   ///holz . yholes.at(74) = 3.150*(-1.5+2); // // y holes            
                   holz . yholes.at(75) = 3.150*(-1.5+3); // // y holes            
                   ///holz . yholes.at(75) = 3.150*(-1.5+3); // // y holes            
                   holz . yholes.at(76) = 3.150*(-1.5+4); // // y holes            
                   ///holz . yholes.at(76) = 3.150*(-1.5+4); // // y holes            
                   holz . yholes.at(77) = 3.150*(-1.5+5); // // y holes            
                   ///holz . yholes.at(77) = 3.150*(-1.5+5); // // y holes            
                   holz . yholes.at(78) = 3.150*(-1.5+6); // // y holes            
                   ///holz . yholes.at(78) = 3.150*(-1.5+6); // // y holes            
                   holz . yholes.at(79) = 3.150*(-1.5+7); // // y holes            
                   ///holz . yholes.at(79) = 3.150*(-1.5+7); // // y holes            
                   holz . yholes.at(80) = 3.150*(-1.5+8); // // y holes            
                   ///holz . yholes.at(80) = 3.150*(-1.5+8); // // y holes            
                   holz . yholes.at(81) = 4.152*(-1.0+0); // // y holes            
                   ///holz . yholes.at(81) = 4.152*(-1.0+0); // // y holes            
                   holz . yholes.at(82) = 4.152*(-1.0+1); // // y holes            
                   ///holz . yholes.at(82) = 4.152*(-1.0+1); // // y holes            
                   holz . yholes.at(83) = 4.152*(-1.0+2); // // y holes            
                   ///holz . yholes.at(83) = 4.152*(-1.0+2); // // y holes            
                   holz . yholes.at(84) = 4.152*(-1.0+3); // // y holes            
                   ///holz . yholes.at(84) = 4.152*(-1.0+3); // // y holes            
                   holz . yholes.at(85) = 4.152*(-1.0+4); // // y holes            
                   ///holz . yholes.at(85) = 4.152*(-1.0+4); // // y holes            
                   holz . yholes.at(86) = 4.152*(-1.0+5); // // y holes            
                   ///holz . yholes.at(86) = 4.152*(-1.0+5); // // y holes            
                   holz . yholes.at(87) = 4.152*(-1.0+6); // // y holes            
                   ///holz . yholes.at(87) = 4.152*(-1.0+6); // // y holes            
                   holz . yholes.at(88) = 4.152*(-1.0+7); // // y holes            
                   ///holz . yholes.at(88) = 4.152*(-1.0+7); // // y holes            
                   holz . yholes.at(89) = 4.152*(-1.0+8); // // y holes            
                   ///holz . yholes.at(89) = 4.152*(-1.0+8); // // y holes            
                   holz . yholes.at(90) = 3.730*(-1.0+0); // // y holes            
                   ///holz . yholes.at(90) = 3.730*(-1.0+0); // // y holes            
                   holz . yholes.at(91) = 3.730*(-1.0+1); // // y holes            
                   ///holz . yholes.at(91) = 3.730*(-1.0+1); // // y holes            
                   holz . yholes.at(92) = 3.730*(-1.0+2); // // y holes            
                   ///holz . yholes.at(92) = 3.730*(-1.0+2); // // y holes            
                   holz . yholes.at(93) = 3.730*(-1.0+3); // // y holes            
                   ///holz . yholes.at(93) = 3.730*(-1.0+3); // // y holes            
                   holz . yholes.at(94) = 3.730*(-1.0+4); // // y holes            
                   ///holz . yholes.at(94) = 3.730*(-1.0+4); // // y holes            
                   holz . yholes.at(95) = 3.730*(-1.0+5); // // y holes            
                   ///holz . yholes.at(95) = 3.730*(-1.0+5); // // y holes            
                   holz . yholes.at(96) = 3.730*(-1.0+6); // // y holes            
                   ///holz . yholes.at(96) = 3.730*(-1.0+6); // // y holes            
                   holz . yholes.at(97) = 3.730*(-1.0+7); // // y holes            
                   ///holz . yholes.at(97) = 3.730*(-1.0+7); // // y holes            
                   holz . yholes.at(98) = 3.730*(-1.0+8); // // y holes            
                   ///holz . yholes.at(98) = 3.730*(-1.0+8); // // y holes            
                   holz . yholes.at(99) = 3.308*(-1.0+0); // // y holes            
                   ///holz . yholes.at(99) = 3.308*(-1.0+0); // // y holes            
                   holz . yholes.at(100) = 3.308*(-1.0+1); // // y holes            
                   ///holz . yholes.at(100) = 3.308*(-1.0+1); // // y holes            
                   holz . yholes.at(101) = 3.308*(-1.0+2); // // y holes            
                   ///holz . yholes.at(101) = 3.308*(-1.0+2); // // y holes            
                   holz . yholes.at(102) = 3.308*(-1.0+3); // // y holes            
                   ///holz . yholes.at(102) = 3.308*(-1.0+3); // // y holes            
                   holz . yholes.at(103) = 3.308*(-1.0+4); // // y holes            
                   ///holz . yholes.at(103) = 3.308*(-1.0+4); // // y holes            
                   holz . yholes.at(104) = 3.308*(-1.0+5); // // y holes            
                   ///holz . yholes.at(104) = 3.308*(-1.0+5); // // y holes            
                   holz . yholes.at(105) = 3.308*(-1.0+6); // // y holes            
                   ///holz . yholes.at(105) = 3.308*(-1.0+6); // // y holes            
                   holz . yholes.at(106) = 3.308*(-1.0+7); // // y holes            
                   ///holz . yholes.at(106) = 3.308*(-1.0+7); // // y holes            
                   holz . yholes.at(107) = 3.308*(-1.0+8); // // y holes            
                   ///holz . yholes.at(107) = 3.308*(-1.0+8); // // y holes            
                   holz . yholes.at(108) = 3.075*(-1.0+0); // // y holes            
                   ///holz . yholes.at(108) = 3.075*(-1.0+0); // // y holes            
                   holz . yholes.at(109) = 3.075*(-1.0+1); // // y holes            
                   ///holz . yholes.at(109) = 3.075*(-1.0+1); // // y holes            
                   holz . yholes.at(110) = 3.075*(-1.0+2); // // y holes            
                   ///holz . yholes.at(110) = 3.075*(-1.0+2); // // y holes            
                   holz . yholes.at(111) = 3.075*(-1.0+3); // // y holes            
                   ///holz . yholes.at(111) = 3.075*(-1.0+3); // // y holes            
                   holz . yholes.at(112) = 3.075*(-1.0+4); // // y holes            
                   ///holz . yholes.at(112) = 3.075*(-1.0+4); // // y holes            
                   holz . yholes.at(113) = 3.075*(-1.0+5); // // y holes            
                   ///holz . yholes.at(113) = 3.075*(-1.0+5); // // y holes            
                   holz . yholes.at(114) = 3.075*(-1.0+6); // // y holes            
                   ///holz . yholes.at(114) = 3.075*(-1.0+6); // // y holes            
                   holz . yholes.at(115) = 3.075*(-1.0+7); // // y holes            
                   ///holz . yholes.at(115) = 3.075*(-1.0+7); // // y holes            
                   holz . yholes.at(116) = 3.075*(-1.0+8); // // y holes            
                   ///holz . yholes.at(116) = 3.075*(-1.0+8); // // y holes            
                   holz . yholes.at(117) = 4.927*(-0.5+0); // // y holes            
                   ///holz . yholes.at(117) = 4.927*(-0.5+0); // // y holes            
                   holz . yholes.at(118) = 4.927*(-0.5+1); // // y holes            
                   ///holz . yholes.at(118) = 4.927*(-0.5+1); // // y holes            
                   holz . yholes.at(119) = 4.927*(-0.5+2); // // y holes            
                   ///holz . yholes.at(119) = 4.927*(-0.5+2); // // y holes            
                   holz . yholes.at(120) = 4.927*(-0.5+3); // // y holes            
                   ///holz . yholes.at(120) = 4.927*(-0.5+3); // // y holes            
                   holz . yholes.at(121) = 4.927*(-0.5+4); // // y holes            
                   ///holz . yholes.at(121) = 4.927*(-0.5+4); // // y holes            
                   holz . yholes.at(122) = 4.927*(-0.5+5); // // y holes            
                   ///holz . yholes.at(122) = 4.927*(-0.5+5); // // y holes            
                   holz . yholes.at(123) = 4.927*(-0.5+6); // // y holes            
                   ///holz . yholes.at(123) = 4.927*(-0.5+6); // // y holes            
                   holz . yholes.at(124) = 4.927*(-0.5+7); // // y holes            
                   ///holz . yholes.at(124) = 4.927*(-0.5+7); // // y holes            
                   holz . yholes.at(125) = 4.927*(-0.5+8); // // y holes            
                   ///holz . yholes.at(125) = 4.927*(-0.5+8); // // y holes            
                   holz . yholes.at(126) = 4.083*(-0.5+0); // // y holes            
                   ///holz . yholes.at(126) = 4.083*(-0.5+0); // // y holes            
                   holz . yholes.at(127) = 4.083*(-0.5+1); // // y holes            
                   ///holz . yholes.at(127) = 4.083*(-0.5+1); // // y holes            
                   holz . yholes.at(128) = 4.083*(-0.5+2); // // y holes            
                   ///holz . yholes.at(128) = 4.083*(-0.5+2); // // y holes            
                   holz . yholes.at(129) = 4.083*(-0.5+3); // // y holes            
                   ///holz . yholes.at(129) = 4.083*(-0.5+3); // // y holes            
                   holz . yholes.at(130) = 4.083*(-0.5+4); // // y holes            
                   ///holz . yholes.at(130) = 4.083*(-0.5+4); // // y holes            
                   holz . yholes.at(131) = 4.083*(-0.5+5); // // y holes            
                   ///holz . yholes.at(131) = 4.083*(-0.5+5); // // y holes            
                   holz . yholes.at(132) = 4.083*(-0.5+6); // // y holes            
                   ///holz . yholes.at(132) = 4.083*(-0.5+6); // // y holes            
                   holz . yholes.at(133) = 4.083*(-0.5+7); // // y holes            
                   ///holz . yholes.at(133) = 4.083*(-0.5+7); // // y holes            
                   holz . yholes.at(134) = 4.083*(-0.5+8); // // y holes            
                   ///holz . yholes.at(134) = 4.083*(-0.5+8); // // y holes            
                   holz . yholes.at(135) = 0.000         ; // // y holes            
                   ///holz . yholes.at(135) = 0.000         ; // // y holes            
                   holz . yholes.at(136) = 0.000         ; // // y holes            
                   ///holz . yholes.at(136) = 0.000         ; // // y holes            
                   holz . yholes.at(137) = 0.000         ; // // y holes            
                   ///holz . yholes.at(137) = 0.000         ; // // y holes            
                   holz . yholes.at(138) = 0.000         ; // // y holes            
                   ///holz . yholes.at(138) = 0.000         ; // // y holes            
                   holz . yholes.at(139) = 0.000         ; // // y holes            
                   ///holz . yholes.at(139) = 0.000         ; // // y holes            
                   holz . yholes.at(140) = 0.000         ; // // y holes            
                   ///holz . yholes.at(140) = 0.000         ; // // y holes            
                   holz . yholes.at(141) = 0.000         ; // // y holes            
                   ///holz . yholes.at(141) = 0.000         ; // // y holes            
                   holz . yholes.at(142) = 0.000         ; // // y holes            
                   ///holz . yholes.at(142) = 0.000         ; // // y holes            
                   holz . yholes.at(143) = 0.000                 ; // // y holes            
                   ///holz . yholes.at(143) = 0.000                 ; // // y holes            
                   //           
                   holz.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup holz_doc        
             ///@{           
                   ++holz._index;           
                   holz . inout = kouter; // // selector            
                   /// holz . inout = kouter; // // selector            
                   holz . numberofrows = 16; // // Number of rows            
                   /// holz . numberofrows = 16; // // Number of rows            
                   holz . numberperrow.at(0) = 9; // // n/row            
                   ///holz . numberperrow.at(0) = 9; // // n/row            
                   holz . numberperrow.at(1) = 9; // // n/row            
                   ///holz . numberperrow.at(1) = 9; // // n/row            
                   holz . numberperrow.at(2) = 9; // // n/row            
                   ///holz . numberperrow.at(2) = 9; // // n/row            
                   holz . numberperrow.at(3) = 9; // // n/row            
                   ///holz . numberperrow.at(3) = 9; // // n/row            
                   holz . numberperrow.at(4) = 9; // // n/row            
                   ///holz . numberperrow.at(4) = 9; // // n/row            
                   holz . numberperrow.at(5) = 8; // // n/row            
                   ///holz . numberperrow.at(5) = 8; // // n/row            
                   holz . numberperrow.at(6) = 8; // // n/row            
                   ///holz . numberperrow.at(6) = 8; // // n/row            
                   holz . numberperrow.at(7) = 8; // // n/row            
                   ///holz . numberperrow.at(7) = 8; // // n/row            
                   holz . numberperrow.at(8) = 8; // // n/row            
                   ///holz . numberperrow.at(8) = 8; // // n/row            
                   holz . numberperrow.at(9) = 8; // // n/row            
                   ///holz . numberperrow.at(9) = 8; // // n/row            
                   holz . numberperrow.at(10) = 7; // // n/row            
                   ///holz . numberperrow.at(10) = 7; // // n/row            
                   holz . numberperrow.at(11) = 7; // // n/row            
                   ///holz . numberperrow.at(11) = 7; // // n/row            
                   holz . numberperrow.at(12) = 7; // // n/row            
                   ///holz . numberperrow.at(12) = 7; // // n/row            
                   holz . numberperrow.at(13) = 7; // // n/row            
                   ///holz . numberperrow.at(13) = 7; // // n/row            
                   holz . numberperrow.at(14) = 7; // // n/row            
                   ///holz . numberperrow.at(14) = 7; // // n/row            
                   holz . numberperrow.at(15) = 6 ; // // n/row            
                   ///holz . numberperrow.at(15) = 6 ; // // n/row            
                   holz . yholes.at(0) = -15.025; // // y holes            
                   ///holz . yholes.at(0) = -15.025; // // y holes            
                   holz . yholes.at(1) = -11.606; // // y holes            
                   ///holz . yholes.at(1) = -11.606; // // y holes            
                   holz . yholes.at(2) = -8.177; // // y holes            
                   ///holz . yholes.at(2) = -8.177; // // y holes            
                   holz . yholes.at(3) = -4.220; // // y holes            
                   ///holz . yholes.at(3) = -4.220; // // y holes            
                   holz . yholes.at(4) = 0; // // y holes            
                   ///holz . yholes.at(4) = 0; // // y holes            
                   holz . yholes.at(5) = 4.220; // // y holes            
                   ///holz . yholes.at(5) = 4.220; // // y holes            
                   holz . yholes.at(6) = 8.177; // // y holes            
                   ///holz . yholes.at(6) = 8.177; // // y holes            
                   holz . yholes.at(7) = 11.606; // // y holes            
                   ///holz . yholes.at(7) = 11.606; // // y holes            
                   holz . yholes.at(8) = 15.025; // // y holes            
                   ///holz . yholes.at(8) = 15.025; // // y holes            
                   holz . yholes.at(9) = -15.025; // // y holes            
                   ///holz . yholes.at(9) = -15.025; // // y holes            
                   holz . yholes.at(10) = -11.606; // // y holes            
                   ///holz . yholes.at(10) = -11.606; // // y holes            
                   holz . yholes.at(11) = -8.177; // // y holes            
                   ///holz . yholes.at(11) = -8.177; // // y holes            
                   holz . yholes.at(12) = -4.220; // // y holes            
                   ///holz . yholes.at(12) = -4.220; // // y holes            
                   holz . yholes.at(13) = 0; // // y holes            
                   ///holz . yholes.at(13) = 0; // // y holes            
                   holz . yholes.at(14) = 4.220; // // y holes            
                   ///holz . yholes.at(14) = 4.220; // // y holes            
                   holz . yholes.at(15) = 8.177; // // y holes            
                   ///holz . yholes.at(15) = 8.177; // // y holes            
                   holz . yholes.at(16) = 11.606; // // y holes            
                   ///holz . yholes.at(16) = 11.606; // // y holes            
                   holz . yholes.at(17) = 15.025; // // y holes            
                   ///holz . yholes.at(17) = 15.025; // // y holes            
                   holz . yholes.at(18) = -14.243; // // y holes            
                   ///holz . yholes.at(18) = -14.243; // // y holes            
                   holz . yholes.at(19) = -11.078; // // y holes            
                   ///holz . yholes.at(19) = -11.078; // // y holes            
                   holz . yholes.at(20) = -6.330; // // y holes            
                   ///holz . yholes.at(20) = -6.330; // // y holes            
                   holz . yholes.at(21) = -3.165; // // y holes            
                   ///holz . yholes.at(21) = -3.165; // // y holes            
                   holz . yholes.at(22) = 0; // // y holes            
                   ///holz . yholes.at(22) = 0; // // y holes            
                   holz . yholes.at(23) = 3.165; // // y holes            
                   ///holz . yholes.at(23) = 3.165; // // y holes            
                   holz . yholes.at(24) = 6.330; // // y holes            
                   ///holz . yholes.at(24) = 6.330; // // y holes            
                   holz . yholes.at(25) = 11.078; // // y holes            
                   ///holz . yholes.at(25) = 11.078; // // y holes            
                   holz . yholes.at(26) = 14.243; // // y holes            
                   ///holz . yholes.at(26) = 14.243; // // y holes            
                   holz . yholes.at(27) = -14.243; // // y holes            
                   ///holz . yholes.at(27) = -14.243; // // y holes            
                   holz . yholes.at(28) = -11.078; // // y holes            
                   ///holz . yholes.at(28) = -11.078; // // y holes            
                   holz . yholes.at(29) = -6.330; // // y holes            
                   ///holz . yholes.at(29) = -6.330; // // y holes            
                   holz . yholes.at(30) = -3.165; // // y holes            
                   ///holz . yholes.at(30) = -3.165; // // y holes            
                   holz . yholes.at(31) = 0; // // y holes            
                   ///holz . yholes.at(31) = 0; // // y holes            
                   holz . yholes.at(32) = 3.165; // // y holes            
                   ///holz . yholes.at(32) = 3.165; // // y holes            
                   holz . yholes.at(33) = 6.330; // // y holes            
                   ///holz . yholes.at(33) = 6.330; // // y holes            
                   holz . yholes.at(34) = 11.078; // // y holes            
                   ///holz . yholes.at(34) = 11.078; // // y holes            
                   holz . yholes.at(35) = 14.243; // // y holes            
                   ///holz . yholes.at(35) = 14.243; // // y holes            
                   holz . yholes.at(36) = -13.452; // // y holes            
                   ///holz . yholes.at(36) = -13.452; // // y holes            
                   holz . yholes.at(37) = -10.023; // // y holes            
                   ///holz . yholes.at(37) = -10.023; // // y holes            
                   holz . yholes.at(38) = -6.330; // // y holes            
                   ///holz . yholes.at(38) = -6.330; // // y holes            
                   holz . yholes.at(39) = -3.165; // // y holes            
                   ///holz . yholes.at(39) = -3.165; // // y holes            
                   holz . yholes.at(40) = 0; // // y holes            
                   ///holz . yholes.at(40) = 0; // // y holes            
                   holz . yholes.at(41) = 3.165; // // y holes            
                   ///holz . yholes.at(41) = 3.165; // // y holes            
                   holz . yholes.at(42) = 6.330; // // y holes            
                   ///holz . yholes.at(42) = 6.330; // // y holes            
                   holz . yholes.at(43) = 10.023; // // y holes            
                   ///holz . yholes.at(43) = 10.023; // // y holes            
                   holz . yholes.at(44) = 13.452; // // y holes            
                   ///holz . yholes.at(44) = 13.452; // // y holes            
                   holz . yholes.at(45) = -13.452; // // y holes            
                   ///holz . yholes.at(45) = -13.452; // // y holes            
                   holz . yholes.at(46) = -10.023; // // y holes            
                   ///holz . yholes.at(46) = -10.023; // // y holes            
                   holz . yholes.at(47) = -6.330; // // y holes            
                   ///holz . yholes.at(47) = -6.330; // // y holes            
                   holz . yholes.at(48) = -3.165; // // y holes            
                   ///holz . yholes.at(48) = -3.165; // // y holes            
                   holz . yholes.at(49) = 3.165; // // y holes            
                   ///holz . yholes.at(49) = 3.165; // // y holes            
                   holz . yholes.at(50) = 6.330; // // y holes            
                   ///holz . yholes.at(50) = 6.330; // // y holes            
                   holz . yholes.at(51) = 10.023; // // y holes            
                   ///holz . yholes.at(51) = 10.023; // // y holes            
                   holz . yholes.at(52) = 13.452; // // y holes            
                   ///holz . yholes.at(52) = 13.452; // // y holes            
                   holz . yholes.at(53) = 0; // // y holes            
                   ///holz . yholes.at(53) = 0; // // y holes            
                   holz . yholes.at(54) = -12.660; // // y holes            
                   ///holz . yholes.at(54) = -12.660; // // y holes            
                   holz . yholes.at(55) = -9.495; // // y holes            
                   ///holz . yholes.at(55) = -9.495; // // y holes            
                   holz . yholes.at(56) = -6.330; // // y holes            
                   ///holz . yholes.at(56) = -6.330; // // y holes            
                   holz . yholes.at(57) = -2.110; // // y holes            
                   ///holz . yholes.at(57) = -2.110; // // y holes            
                   holz . yholes.at(58) = 2.110; // // y holes            
                   ///holz . yholes.at(58) = 2.110; // // y holes            
                   holz . yholes.at(59) = 6.330; // // y holes            
                   ///holz . yholes.at(59) = 6.330; // // y holes            
                   holz . yholes.at(60) = 9.495; // // y holes            
                   ///holz . yholes.at(60) = 9.495; // // y holes            
                   holz . yholes.at(61) = 12.660; // // y holes            
                   ///holz . yholes.at(61) = 12.660; // // y holes            
                   holz . yholes.at(62) = 0; // // y holes            
                   ///holz . yholes.at(62) = 0; // // y holes            
                   holz . yholes.at(63) = -12.660; // // y holes            
                   ///holz . yholes.at(63) = -12.660; // // y holes            
                   holz . yholes.at(64) = -9.495; // // y holes            
                   ///holz . yholes.at(64) = -9.495; // // y holes            
                   holz . yholes.at(65) = -6.330; // // y holes            
                   ///holz . yholes.at(65) = -6.330; // // y holes            
                   holz . yholes.at(66) = -2.110; // // y holes            
                   ///holz . yholes.at(66) = -2.110; // // y holes            
                   holz . yholes.at(67) = 2.110; // // y holes            
                   ///holz . yholes.at(67) = 2.110; // // y holes            
                   holz . yholes.at(68) = 6.330; // // y holes            
                   ///holz . yholes.at(68) = 6.330; // // y holes            
                   holz . yholes.at(69) = 9.495; // // y holes            
                   ///holz . yholes.at(69) = 9.495; // // y holes            
                   holz . yholes.at(70) = 12.660; // // y holes            
                   ///holz . yholes.at(70) = 12.660; // // y holes            
                   holz . yholes.at(71) = 0; // // y holes            
                   ///holz . yholes.at(71) = 0; // // y holes            
                   holz . yholes.at(72) = -11.870; // // y holes            
                   ///holz . yholes.at(72) = -11.870; // // y holes            
                   holz . yholes.at(73) = -8.440; // // y holes            
                   ///holz . yholes.at(73) = -8.440; // // y holes            
                   holz . yholes.at(74) = -5.275; // // y holes            
                   ///holz . yholes.at(74) = -5.275; // // y holes            
                   holz . yholes.at(75) = -2.110; // // y holes            
                   ///holz . yholes.at(75) = -2.110; // // y holes            
                   holz . yholes.at(76) = 2.110; // // y holes            
                   ///holz . yholes.at(76) = 2.110; // // y holes            
                   holz . yholes.at(77) = 5.275; // // y holes            
                   ///holz . yholes.at(77) = 5.275; // // y holes            
                   holz . yholes.at(78) = 8.440; // // y holes            
                   ///holz . yholes.at(78) = 8.440; // // y holes            
                   holz . yholes.at(79) = 11.870; // // y holes            
                   ///holz . yholes.at(79) = 11.870; // // y holes            
                   holz . yholes.at(80) = 0; // // y holes            
                   ///holz . yholes.at(80) = 0; // // y holes            
                   holz . yholes.at(81) = -11.870; // // y holes            
                   ///holz . yholes.at(81) = -11.870; // // y holes            
                   holz . yholes.at(82) = -8.440; // // y holes            
                   ///holz . yholes.at(82) = -8.440; // // y holes            
                   holz . yholes.at(83) = -5.275; // // y holes            
                   ///holz . yholes.at(83) = -5.275; // // y holes            
                   holz . yholes.at(84) = -2.110; // // y holes            
                   ///holz . yholes.at(84) = -2.110; // // y holes            
                   holz . yholes.at(85) = 2.110; // // y holes            
                   ///holz . yholes.at(85) = 2.110; // // y holes            
                   holz . yholes.at(86) = 5.275; // // y holes            
                   ///holz . yholes.at(86) = 5.275; // // y holes            
                   holz . yholes.at(87) = 8.440; // // y holes            
                   ///holz . yholes.at(87) = 8.440; // // y holes            
                   holz . yholes.at(88) = 11.870; // // y holes            
                   ///holz . yholes.at(88) = 11.870; // // y holes            
                   holz . yholes.at(89) = 0; // // y holes            
                   ///holz . yholes.at(89) = 0; // // y holes            
                   holz . yholes.at(90) = -11.078; // // y holes            
                   ///holz . yholes.at(90) = -11.078; // // y holes            
                   holz . yholes.at(91) = -7.649; // // y holes            
                   ///holz . yholes.at(91) = -7.649; // // y holes            
                   holz . yholes.at(92) = -4.220; // // y holes            
                   ///holz . yholes.at(92) = -4.220; // // y holes            
                   holz . yholes.at(93) = 0; // // y holes            
                   ///holz . yholes.at(93) = 0; // // y holes            
                   holz . yholes.at(94) = 4.220; // // y holes            
                   ///holz . yholes.at(94) = 4.220; // // y holes            
                   holz . yholes.at(95) = 7.649; // // y holes            
                   ///holz . yholes.at(95) = 7.649; // // y holes            
                   holz . yholes.at(96) = 11.078; // // y holes            
                   ///holz . yholes.at(96) = 11.078; // // y holes            
                   holz . yholes.at(97) = 0; // // y holes            
                   ///holz . yholes.at(97) = 0; // // y holes            
                   holz . yholes.at(98) = 0; // // y holes            
                   ///holz . yholes.at(98) = 0; // // y holes            
                   holz . yholes.at(99) = -11.078; // // y holes            
                   ///holz . yholes.at(99) = -11.078; // // y holes            
                   holz . yholes.at(100) = -7.649; // // y holes            
                   ///holz . yholes.at(100) = -7.649; // // y holes            
                   holz . yholes.at(101) = -4.220; // // y holes            
                   ///holz . yholes.at(101) = -4.220; // // y holes            
                   holz . yholes.at(102) = 0; // // y holes            
                   ///holz . yholes.at(102) = 0; // // y holes            
                   holz . yholes.at(103) = 4.220; // // y holes            
                   ///holz . yholes.at(103) = 4.220; // // y holes            
                   holz . yholes.at(104) = 7.649; // // y holes            
                   ///holz . yholes.at(104) = 7.649; // // y holes            
                   holz . yholes.at(105) = 11.078; // // y holes            
                   ///holz . yholes.at(105) = 11.078; // // y holes            
                   holz . yholes.at(106) = 0; // // y holes            
                   ///holz . yholes.at(106) = 0; // // y holes            
                   holz . yholes.at(107) = 0; // // y holes            
                   ///holz . yholes.at(107) = 0; // // y holes            
                   holz . yholes.at(108) = -10.022; // // y holes            
                   ///holz . yholes.at(108) = -10.022; // // y holes            
                   holz . yholes.at(109) = -6.858; // // y holes            
                   ///holz . yholes.at(109) = -6.858; // // y holes            
                   holz . yholes.at(110) = -3.429; // // y holes            
                   ///holz . yholes.at(110) = -3.429; // // y holes            
                   holz . yholes.at(111) = 0; // // y holes            
                   ///holz . yholes.at(111) = 0; // // y holes            
                   holz . yholes.at(112) = 3.429; // // y holes            
                   ///holz . yholes.at(112) = 3.429; // // y holes            
                   holz . yholes.at(113) = 6.858; // // y holes            
                   ///holz . yholes.at(113) = 6.858; // // y holes            
                   holz . yholes.at(114) = 10.022; // // y holes            
                   ///holz . yholes.at(114) = 10.022; // // y holes            
                   holz . yholes.at(115) = 0; // // y holes            
                   ///holz . yholes.at(115) = 0; // // y holes            
                   holz . yholes.at(116) = 0; // // y holes            
                   ///holz . yholes.at(116) = 0; // // y holes            
                   holz . yholes.at(117) = -10.022; // // y holes            
                   ///holz . yholes.at(117) = -10.022; // // y holes            
                   holz . yholes.at(118) = -6.858; // // y holes            
                   ///holz . yholes.at(118) = -6.858; // // y holes            
                   holz . yholes.at(119) = -3.429; // // y holes            
                   ///holz . yholes.at(119) = -3.429; // // y holes            
                   holz . yholes.at(120) = 0; // // y holes            
                   ///holz . yholes.at(120) = 0; // // y holes            
                   holz . yholes.at(121) = 3.429; // // y holes            
                   ///holz . yholes.at(121) = 3.429; // // y holes            
                   holz . yholes.at(122) = 6.858; // // y holes            
                   ///holz . yholes.at(122) = 6.858; // // y holes            
                   holz . yholes.at(123) = 10.022; // // y holes            
                   ///holz . yholes.at(123) = 10.022; // // y holes            
                   holz . yholes.at(124) = 0; // // y holes            
                   ///holz . yholes.at(124) = 0; // // y holes            
                   holz . yholes.at(125) = 0; // // y holes            
                   ///holz . yholes.at(125) = 0; // // y holes            
                   holz . yholes.at(126) = -9.495; // // y holes            
                   ///holz . yholes.at(126) = -9.495; // // y holes            
                   holz . yholes.at(127) = -6.330; // // y holes            
                   ///holz . yholes.at(127) = -6.330; // // y holes            
                   holz . yholes.at(128) = -3.165; // // y holes            
                   ///holz . yholes.at(128) = -3.165; // // y holes            
                   holz . yholes.at(129) = 0; // // y holes            
                   ///holz . yholes.at(129) = 0; // // y holes            
                   holz . yholes.at(130) = 3.165; // // y holes            
                   ///holz . yholes.at(130) = 3.165; // // y holes            
                   holz . yholes.at(131) = 6.330; // // y holes            
                   ///holz . yholes.at(131) = 6.330; // // y holes            
                   holz . yholes.at(132) = 9.495; // // y holes            
                   ///holz . yholes.at(132) = 9.495; // // y holes            
                   holz . yholes.at(133) = 0; // // y holes            
                   ///holz . yholes.at(133) = 0; // // y holes            
                   holz . yholes.at(134) = 0; // // y holes            
                   ///holz . yholes.at(134) = 0; // // y holes            
                   holz . yholes.at(135) = -9.495; // // y holes            
                   ///holz . yholes.at(135) = -9.495; // // y holes            
                   holz . yholes.at(136) = -6.330; // // y holes            
                   ///holz . yholes.at(136) = -6.330; // // y holes            
                   holz . yholes.at(137) = -3.165; // // y holes            
                   ///holz . yholes.at(137) = -3.165; // // y holes            
                   holz . yholes.at(138) = 3.165; // // y holes            
                   ///holz . yholes.at(138) = 3.165; // // y holes            
                   holz . yholes.at(139) = 6.330; // // y holes            
                   ///holz . yholes.at(139) = 6.330; // // y holes            
                   holz . yholes.at(140) = 9.495; // // y holes            
                   ///holz . yholes.at(140) = 9.495; // // y holes            
                   holz . yholes.at(141) = 0; // // y holes            
                   ///holz . yholes.at(141) = 0; // // y holes            
                   holz . yholes.at(142) = 0; // // y holes            
                   ///holz . yholes.at(142) = 0; // // y holes            
                   holz . yholes.at(143) = 0 ; // // y holes            
                   ///holz . yholes.at(143) = 0 ; // // y holes            
                   //           
                   holz.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup cool_doc        
             ///@{           
                   ++cool._index;           
                   cool . inout = kinner; // // Inner vs outer            
                   /// cool . inout = kinner; // // Inner vs outer            
                   cool . tubelength.at(0) = 19.300; // // Tube lengths            
                   ///cool . tubelength.at(0) = 19.300; // // Tube lengths            
                   cool . tubelength.at(1) = 18.454; // // Tube lengths            
                   ///cool . tubelength.at(1) = 18.454; // // Tube lengths            
                   cool . tubelength.at(2) = 17.610; // // Tube lengths            
                   ///cool . tubelength.at(2) = 17.610; // // Tube lengths            
                   cool . tubelength.at(3) = 16.766; // // Tube lengths            
                   ///cool . tubelength.at(3) = 16.766; // // Tube lengths            
                   cool . tubelength.at(4) = 15.922; // // Tube lengths            
                   ///cool . tubelength.at(4) = 15.922; // // Tube lengths            
                   cool . tubelength.at(5) = 15.078; // // Tube lengths            
                   ///cool . tubelength.at(5) = 15.078; // // Tube lengths            
                   cool . tubelength.at(6) = 14.235; // // Tube lengths            
                   ///cool . tubelength.at(6) = 14.235; // // Tube lengths            
                   cool . tubelength.at(7) = 13.390; // // Tube lengths            
                   ///cool . tubelength.at(7) = 13.390; // // Tube lengths            
                   cool . tubelength.at(8) = 12.546; // // Tube lengths            
                   ///cool . tubelength.at(8) = 12.546; // // Tube lengths            
                   cool . tubelength.at(9) = 11.704; // // Tube lengths            
                   ///cool . tubelength.at(9) = 11.704; // // Tube lengths            
                   cool . tubelength.at(10) = 10.860; // // Tube lengths            
                   ///cool . tubelength.at(10) = 10.860; // // Tube lengths            
                   cool . tubelength.at(11) = 10.016; // // Tube lengths            
                   ///cool . tubelength.at(11) = 10.016; // // Tube lengths            
                   cool . tubelength.at(12) = 9.172; // // Tube lengths            
                   ///cool . tubelength.at(12) = 9.172; // // Tube lengths            
                   cool . tubelength.at(13) = 8.327; // // Tube lengths            
                   ///cool . tubelength.at(13) = 8.327; // // Tube lengths            
                   cool . tubelength.at(14) = 7.483; // // Tube lengths            
                   ///cool . tubelength.at(14) = 7.483; // // Tube lengths            
                   cool . tubelength.at(15) = 0.000 ; // // Tube lengths            
                   ///cool . tubelength.at(15) = 0.000 ; // // Tube lengths            
                   //           
                   cool.fill();           
             ///@}        
             //        
             // ---------------------------------------------------------------------------------------------------        
             ///@addtogroup cool_doc        
             ///@{           
                   ++cool._index;           
                   cool . inout = kouter; // // Inner vs outer            
                   /// cool . inout = kouter; // // Inner vs outer            
                   cool . tubelength.at(0) = 33.620; // // Tube lengths            
                   ///cool . tubelength.at(0) = 33.620; // // Tube lengths            
                   cool . tubelength.at(1) = 33.605; // // Tube lengths            
                   ///cool . tubelength.at(1) = 33.605; // // Tube lengths            
                   cool . tubelength.at(2) = 32.761; // // Tube lengths            
                   ///cool . tubelength.at(2) = 32.761; // // Tube lengths            
                   cool . tubelength.at(3) = 31.917; // // Tube lengths            
                   ///cool . tubelength.at(3) = 31.917; // // Tube lengths            
                   cool . tubelength.at(4) = 31.073; // // Tube lengths            
                   ///cool . tubelength.at(4) = 31.073; // // Tube lengths            
                   cool . tubelength.at(5) = 30.229; // // Tube lengths            
                   ///cool . tubelength.at(5) = 30.229; // // Tube lengths            
                   cool . tubelength.at(6) = 29.385; // // Tube lengths            
                   ///cool . tubelength.at(6) = 29.385; // // Tube lengths            
                   cool . tubelength.at(7) = 28.541; // // Tube lengths            
                   ///cool . tubelength.at(7) = 28.541; // // Tube lengths            
                   cool . tubelength.at(8) = 27.697; // // Tube lengths            
                   ///cool . tubelength.at(8) = 27.697; // // Tube lengths            
                   cool . tubelength.at(9) = 26.853; // // Tube lengths            
                   ///cool . tubelength.at(9) = 26.853; // // Tube lengths            
                   cool . tubelength.at(10) = 26.009; // // Tube lengths            
                   ///cool . tubelength.at(10) = 26.009; // // Tube lengths            
                   cool . tubelength.at(11) = 25.165; // // Tube lengths            
                   ///cool . tubelength.at(11) = 25.165; // // Tube lengths            
                   cool . tubelength.at(12) = 24.321; // // Tube lengths            
                   ///cool . tubelength.at(12) = 24.321; // // Tube lengths            
                   cool . tubelength.at(13) = 23.478; // // Tube lengths            
                   ///cool . tubelength.at(13) = 23.478; // // Tube lengths            
                   cool . tubelength.at(14) = 22.634; // // Tube lengths            
                   ///cool . tubelength.at(14) = 22.634; // // Tube lengths            
                   cool . tubelength.at(15) = 21.790 ; // // Tube lengths            
                   ///cool . tubelength.at(15) = 21.790 ; // // Tube lengths            
                   //           
                   cool.fill();           
             ///@}        
             //        
             /// USE tfee _index=1;        
             tfee.Use();        
             /// USE tecw _index=1;        
             tecw.Use();        
             /// USE tpcr _index=1;        
             tpcr.Use();        
             /// USE tpcg _index=1;        
             tpcg.Use();        
             tofcleng = tpcg.length-2*tpcg.wheelthk-2*tpcr.rdovthk  ;// gas plus endcaps;        
             tpgvleng = (tofcleng-tpcg.membthk)/2          ;// active gas;        
             tpgvleng = (tpcg.lengthv-tpcg.membthk)/2      ;// active gas;        
             tocsir = tpcg.sengasor;        
             tocsor = tocsir + tpcg.tocsdr;        
             tokair = tocsor; tokaor = tokair + tpcg.tokadr;        
             tonxir = tokaor; tonxor = tonxir + tpcg.tonxdr;        
             toadir = tonxor; toador = toadir + tpcg.toaddr;        
             toigir = toador; toigor = toigir + tpcg.toigdr;        
             toalir = toigor; toalor = toalir + tpcg.toaldr/2.;        
             tohair = toalor; tohaor = tohair + tpcg.tohadr;        
             toalir2= tohaor; toalor2= toalir2+ tpcg.toaldr/2.;        
             tofcir = tocsir; tofcor = toalor2;        
             tofsir = tocsir; tofsor = toador;        
             tifcir = tpcg.rminifc;        
             tialir = tifcir; tialor = tialir + tpcg.tialdr/2.;        
             tikair = tialor; tikaor = tikair + tpcg.tikadr;        
             tinxir = tikaor; tinxor = tinxir + tpcg.tinxdr;        
             tiadir = tinxor; tiador = tiadir + tpcg.tiaddr;        
             tifcor = tiador + tpcg.tialdr/2.;        
             tpgvir = tifcor;         ;//// tpc gas inner radius;        
             del = tpcg.rmax-tofcor;        
             // Print<level=%i> fmt=%s fortran format statements not supported        
             width1iof.at(0) = 7.661*inch;        
             width1iof.at(1) = 22.287*inch;        
             width2iof.at(0) = 20.552*inch;        
             width2iof.at(1) = 35.422*inch;        
             heightiof.at(0) = 24.222*inch;        
             heightiof.at(1) = 24.840*inch;        
             depthiof.at(0) = 1.800*inch;        
             depthiof.at(1) = 1.800*inch;        
             /// Component C	a=12	z=6	w=5        
             /// Component H	a=1	z=1	w=8        
             /// Component O	a=16	z=8	w=2        
             /// Mixture Nomex dens=0.064        
             {  AgMaterial &mix = AgMaterial::Get("Nomex");           
                   mix.Component("C",12,6,5);           
                   mix.Component("H",1,1,8);           
                   mix.Component("O",16,8,2);           
                   mix.par("dens")=0.064;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
             /// Component C	a=12	z=6	w=0.625        
             /// Component H	a=1	z=1	w=0.4166667e-01        
             /// Component O	a=16	z=8	w=0.3333333        
             /// Mixture Adhesive dens=1.2        
             {  AgMaterial &mix = AgMaterial::Get("Adhesive");           
                   mix.Component("C",12,6,0.625);           
                   mix.Component("H",1,1,0.4166667e-01);           
                   mix.Component("O",16,8,0.3333333);           
                   mix.par("dens")=1.2;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
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
             /// Component H	a=1	z=1	w=1.06546299984001044e-02        
             /// Component O	a=16	z=8	w=8.52370399872008355e-02        
             /// Component AL	a=27	z=14	w=9.04108330014399053e-01        
             /// Mixture Water_Pipe dens=2.32155        
             {  AgMaterial &mix = AgMaterial::Get("Water_pipe");           
                   mix.Component("H",1,1,1.06546299984001044e-02);           
                   mix.Component("O",16,8,8.52370399872008355e-02);           
                   mix.Component("AL",27,14,9.04108330014399053e-01);           
                   mix.par("dens")=2.32155;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
             /// Component CU	a=63.54	z=29	w=0.586        
             /// Component C	a=12.01	z=6	w=0.259        
             /// Component O	a=15.999	z=8	w=0.138        
             /// Component H	a=1.00794	z=1	w=0.017        
             /// Mixture Cables dens=2.68        
             {  AgMaterial &mix = AgMaterial::Get("Cables");           
                   mix.Component("CU",63.54,29,0.586);           
                   mix.Component("C",12.01,6,0.259);           
                   mix.Component("O",15.999,8,0.138);           
                   mix.Component("H",1.00794,1,0.017);           
                   mix.par("dens")=2.68;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
             /// Component Ar	a=40	z=18	w=9        
             /// Component C	a=12	z=6	w=1        
             /// Component H	a=1	z=1	w=4        
             /// Mixture P10 dens=0.154053e-02        
             {  AgMaterial &mix = AgMaterial::Get("P10");           
                   mix.Component("Ar",40,18,9);           
                   mix.Component("C",12,6,1);           
                   mix.Component("H",1,1,4);           
                   mix.par("dens")=0.154053e-02;           
                   mix.lock();           
                   _material = mix;           
                   _material.lock();           
             }        
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
       }; // TpceGeo3a     
 }; // namespace TpceGeo3a  
 