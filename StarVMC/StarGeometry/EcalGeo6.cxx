#include "EcalGeo6.h"  
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
 namespace ECALGEO6 // $NMSPC  
 {  
    //  
    // ---------------------------------------------------------------------------------------------------  
       //  -----------------------------------------------------  
       /// @defgroup emcg_doc  
       /// \class Emcg_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t version;  
       ///Int_t onoff;  
       ///Int_t fillmode;  
       ///Int_t _index;  
       //  
       Emcg_t emcg;  
       //  
       //  -----------------------------------------------------  
       /// @defgroup emcs_doc  
       /// \class Emcs_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t version;  
       ///Float_t type;  
       ///Float_t zorg;  
       ///Float_t zend;  
       ///Float_t etamin;  
       ///Float_t etamax;  
       ///Float_t phimin;  
       ///Float_t phimax;  
       ///Float_t offset;  
       ///Float_t nsupsec;  
       ///Float_t nsector;  
       ///Float_t nsection;  
       ///Float_t nslices;  
       ///Float_t front;  
       ///Float_t alincell;  
       ///Float_t frplast;  
       ///Float_t bkplast;  
       ///Float_t pbplate;  
       ///Float_t lamplate;  
       ///Float_t bckplate;  
       ///Float_t hub;  
       ///Float_t rmshift;  
       ///Float_t smshift;  
       ///Float_t gapplt;  
       ///Float_t gapcel;  
       ///Float_t gapsmd;  
       ///Float_t smdcentr;  
       ///Array_t<Float_t> tierod;  
       ///Float_t bckfrnt;  
       ///Float_t gaphalf;  
       ///Float_t cover;  
       ///Float_t rtie;  
       ///Float_t slop;  
       ///Int_t _index;  
       //  
       Emcs_t emcs;  
       //  
       //  -----------------------------------------------------  
       /// @defgroup eetr_doc  
       /// \class Eetr_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t type;  
       ///Float_t etagr;  
       ///Float_t phigr;  
       ///Float_t neta;  
       ///Array_t<Float_t> etabin;  
       ///Int_t _index;  
       //  
       Eetr_t eetr;  
       //  
       //  -----------------------------------------------------  
       /// @defgroup esec_doc  
       /// \class Esec_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t isect;  
       ///Float_t fplmat;  
       ///Float_t cell;  
       ///Float_t scint;  
       ///Float_t nlayer;  
       ///Float_t deltaz;  
       ///Array_t<Float_t> jiggle;  
       ///Int_t _index;  
       //  
       Esec_t esec;  
       //  
       //  -----------------------------------------------------  
       /// @defgroup emxg_doc  
       /// \class Emxg_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t version;  
       ///Float_t sapex;  
       ///Float_t sbase;  
       ///Float_t rin;  
       ///Float_t rout;  
       ///Float_t f4;  
       ///Int_t _index;  
       //  
       Emxg_t emxg;  
       //  
       //  -----------------------------------------------------  
       /// @defgroup exse_doc  
       /// \class Exse_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t jsect;  
       ///Float_t zshift;  
       ///Array_t<Float_t> sectype;  
       ///Int_t _index;  
       //  
       Exse_t exse;  
       //  
       //  -----------------------------------------------------  
       /// @defgroup esmd_doc  
       /// \class Esmd_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t version;  
       ///Float_t front_layer;  
       ///Float_t back_layer;  
       ///Float_t spacer_layer;  
       ///Float_t base;  
       ///Float_t apex;  
       ///Int_t _index;  
       //  
       Esmd_t esmd;  
       //  
       //  -----------------------------------------------------  
       /// @defgroup ecut_doc  
       /// \class Ecut_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t version;  
       ///Float_t absorber;  
       ///Float_t sensitive;  
       ///Float_t blah;  
       ///Int_t _index;  
       //  
       Ecut_t ecut;  
       //  
       //  -----------------------------------------------------  
       /// @defgroup eabs_doc  
       /// \class Eabs_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t version;  
       ///Float_t cutgam;  
       ///Float_t cutele;  
       ///Float_t cutneu;  
       ///Float_t cuthad;  
       ///Float_t cutmuo;  
       ///Float_t dcute;  
       ///Float_t dcutm;  
       ///Float_t bcute;  
       ///Float_t bcutm;  
       ///Int_t _index;  
       //  
       Eabs_t eabs;  
       //  
       //  -----------------------------------------------------  
       /// @defgroup esen_doc  
       /// \class Esen_t  
       /// \brief User-defined structure  
       ///                          
       /// AgML structure members:  
       ///                          
       ///Float_t version;  
       ///Float_t cutgam;  
       ///Float_t cutele;  
       ///Float_t cutneu;  
       ///Float_t cuthad;  
       ///Float_t cutmuo;  
       ///Float_t dcute;  
       ///Float_t dcutm;  
       ///Float_t bcute;  
       ///Float_t bcutm;  
       ///Int_t _index;  
       //  
       Esen_t esen;  
       //  
       ///@addtogroup EcalGeo6_vars  
       ///@{     
             Int_t i_section,j_section,ie,is,isec,istrip,nstr,type,ii,jj,cut,fsect,lsect,ihalf,filled,i,j,k,i_sector;     
             //     
             /// Int_t i_section,j_section,ie,is,isec,istrip,nstr,type,ii,jj,cut,fsect,lsect,ihalf,filled,i,j,k,i_sector     
       ///@}  
       ///@addtogroup EcalGeo6_vars  
       ///@{     
             Float_t center,plate,cell,g10,halfi,tan_low,tan_upp,rbot,rtop,deta,sq2,sq3,dup,dd,d2,d3,rshift,dphi,radiator;     
             //     
             /// Float_t center,plate,cell,g10,halfi,tan_low,tan_upp,rbot,rtop,deta,sq2,sq3,dup,dd,d2,d3,rshift,dphi,radiator     
       ///@}  
       ///@addtogroup EcalGeo6_vars  
       ///@{     
             Float_t maxcnt,msecwd,mxgten,curr,secwid,section,curcl,etatop,etabot,zwidth,zslice,gap,megatile,xleft,xright,yleft,yright,current,rth,length,p,xc,yc,xx,yy,rdel,dxy,ddn,ddup;     
             //     
             /// Float_t maxcnt,msecwd,mxgten,curr,secwid,section,curcl,etatop,etabot,zwidth,zslice,gap,megatile,xleft,xright,yleft,yright,current,rth,length,p,xc,yc,xx,yy,rdel,dxy,ddn,ddup     
       ///@}  
       ///@addtogroup EcalGeo6_vars  
       ///@{     
             Float_t myphi;     
             //     
             /// Float_t myphi     
       ///@}  
       ///@addtogroup EcalGeo6_vars  
       ///@{     
             Int_t n;     
             //     
             /// Int_t n     
       ///@}  
    EcalGeo6::EcalGeo6()  
      : AgModule("EcalGeo6"," is the EM EndCap Calorimeter GEOmetry ")  
    {     
    }  
       Float_t tanf(Float_t etax) { return tan(2*atan(exp(-etax))); }  
       // ---------------------------------------------------------------------------------------------------  
       void ECAL::Block( AgCreate create )  
       {      
             ///@addtogroup ECAL_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Air");           
                         _material = mat;           
                   }        
                   /// Material ECAL_Air isvol=0         
                   { AgMaterial &mat = AgMaterial::Get("Ecal_air");           
                         mat.par("isvol")=0;           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ECAL");           
                         attr.par("seen")=0;           
                         attr.par("colo")=7;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cone");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=(emcs.zend-emcs.zorg)/2;           
                         shape.par("rmn1")=emcs.zorg*tan_low-d2;           
                         shape.par("rmx1")=emcs.zorg*tan_upp+dup;           
                         shape.par("rmn2")=emcs.zend*tan_low-d2;           
                         shape.par("rmx2")=emcs.zend*tan_upp+dup;           
                         /// Shape Cone dz=(emcs.zend-emcs.zorg)/2 rmn1=emcs.zorg*tan_low-d2 rmx1=emcs.zorg*tan_upp+dup rmn2=emcs.zend*tan_low-d2 rmx2=emcs.zend*tan_upp+dup            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ECAL;           
                         _stacker -> Build(this);           
                   }        
                   /// Loop on ihalf from 1 to 2 step=1        
                   for ( ihalf=1; (1>0)? (ihalf<=2):(ihalf>=2); ihalf+=1 )        
                   {           
                         filled = 1;           
                         halfi  = -105 + (ihalf-1)*180;           
                         if ( (ihalf==2&&emcg.fillmode<3) )           
                         {              
                               filled = 0;              
                         }           
                         _create = AgCreate("EAGA");           
                         {              
                               AgShape myshape; // undefined shape              
                               ///Create EAGA              
                               Create("EAGA");               
                         }           
                         { AgPlacement place = AgPlacement("EAGA","ECAL");              
                               /// Add daughter volume EAGA to mother ECAL              
                               place.AlphaZ(halfi);              
                               /// Rotate: AlphaZ = halfi              
                               /// G3 Reference: thetax = 90              
                               /// G3 Reference: phix = 0              
                               /// G3 Reference: thetay = 90              
                               /// G3 Reference: phiy = 90              
                               /// G3 Reference: thetaz = 0              
                               /// G3 Reference: phiz = 0              
                               _stacker -> Position( AgBlock::Find("EAGA"), place );              
                         } // end placement of EAGA           
                   }        
                   END_OF_ECAL:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ECAL  
       // ---------------------------------------------------------------------------------------------------  
       void EAGA::Block( AgCreate create )  
       {      
             ///@addtogroup EAGA_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ECAL_Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_air");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("EAGA");           
                         attr.par("seen")=0;           
                         attr.par("colo")=1;           
                         attr.par("serial")=filled;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=(emcs.zend-emcs.zorg)/2;           
                         shape.par("rmn1")=emcs.zorg*tan_low-d2;           
                         shape.par("rmx1")=emcs.zorg*tan_upp+dup;           
                         shape.par("rmn2")=emcs.zend*tan_low-d2;           
                         shape.par("rmx2")=emcs.zend*tan_upp+dup;           
                         shape.par("phi1")=emcs.phimin;           
                         shape.par("phi2")=emcs.phimax;           
                         /// Shape Cons dz=(emcs.zend-emcs.zorg)/2 rmn1=emcs.zorg*tan_low-d2 rmx1=emcs.zorg*tan_upp+dup rmn2=emcs.zend*tan_low-d2 rmx2=emcs.zend*tan_upp+dup phi1=emcs.phimin phi2=emcs.phimax            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EAGA;           
                         _stacker -> Build(this);           
                   }        
                   if ( filled==1 )        
                   {           
                         _create = AgCreate("EMSS");           
                         {              
                               AgShape myshape; // undefined shape              
                               ///Create EMSS              
                               Create("EMSS");               
                         }           
                         { AgPlacement place = AgPlacement("EMSS","EAGA");              
                               /// Add daughter volume EMSS to mother EAGA              
                               place.par("only")=AgPlacement::kMany;              
                               /// Overlap: agplacement::kmany              
                               _stacker -> Position( AgBlock::Find("EMSS"), place );              
                         } // end placement of EMSS           
                         curr  = emcs.zorg;           
                         curcl = emcs.zend;           
                         _create = AgCreate("ECGH");           
                         {              
                               AgShape myshape; // undefined shape              
                               ///Create ECGH              
                               Create("ECGH");               
                         }           
                         { AgPlacement place = AgPlacement("ECGH","EAGA");              
                               /// Add daughter volume ECGH to mother EAGA              
                               place.par("only")=AgPlacement::kOnly;              
                               /// Overlap: agplacement::konly              
                               place.AlphaZ(90);              
                               /// Rotate: AlphaZ = 90              
                               /// G3 Reference: thetax = 90              
                               /// G3 Reference: phix = 0              
                               /// G3 Reference: thetay = 90              
                               /// G3 Reference: phiy = 90              
                               /// G3 Reference: thetaz = 0              
                               /// G3 Reference: phiz = 0              
                               _stacker -> Position( AgBlock::Find("ECGH"), place );              
                         } // end placement of ECGH           
                   }        
                   END_OF_EAGA:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EAGA  
       // ---------------------------------------------------------------------------------------------------  
       void EMSS::Block( AgCreate create )  
       {      
             ///@addtogroup EMSS_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Component Cr	a=51.9960	z=24	w=0.19        
                   /// Component Ni	a=58.6934	z=28	w=0.09        
                   /// Component Fe	a=55.8450	z=26	w=0.72        
                   /// Mixture Ecal_Steel dens=8.03        
                   {  AgMaterial &mix = AgMaterial::Get("Ecal_steel");           
                         mix.Component("Cr",51.9960,24,0.19);           
                         mix.Component("Ni",58.6934,28,0.09);           
                         mix.Component("Fe",55.8450,26,0.72);           
                         mix.par("dens")=8.03;           
                         mix.lock();           
                         _material = mix;           
                         _material.lock();           
                   }        
                   { AgAttribute attr = AgAttribute("EMSS");           
                         attr.par("seen")=1;           
                         attr.par("colo")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=(emcs.zend-emcs.zorg)/2;           
                         shape.par("rmn1")=emcs.zorg*tan_low-d2;           
                         shape.par("rmx1")=emcs.zorg*tan_upp+dup;           
                         shape.par("rmn2")=emcs.zend*tan_low-d2;           
                         shape.par("rmx2")=emcs.zend*tan_upp+dup;           
                         shape.par("phi1")=emcs.phimin;           
                         shape.par("phi2")=emcs.phimax;           
                         /// Shape Cons dz=(emcs.zend-emcs.zorg)/2 rmn1=emcs.zorg*tan_low-d2 rmx1=emcs.zorg*tan_upp+dup rmn2=emcs.zend*tan_low-d2 rmx2=emcs.zend*tan_upp+dup phi1=emcs.phimin phi2=emcs.phimax            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EMSS;           
                         _stacker -> Build(this);           
                   }        
                   zslice = emcs.zorg;        
                   zwidth = emcs.front;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   _create = AgCreate("EFLP");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create EFLP           
                         Create("EFLP");            
                   }        
                   { AgPlacement place = AgPlacement("EFLP","EMSS");           
                         /// Add daughter volume EFLP to mother EMSS           
                         place.TranslateZ(zslice-center+zwidth/2);           
                         /// Translate z = zslice-center+zwidth/2           
                         _stacker -> Position( AgBlock::Find("EFLP"), place );           
                   } // end placement of EFLP        
                   zslice = zslice + zwidth;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   fsect = 1                                          ;// first section;        
                   lsect = 3                                          ;// last section;        
                   zwidth = emcs.smdcentr - emcs.gapsmd/2 - zslice    ;// width of current slice;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   _create = AgCreate("ECVO");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create ECVO           
                         Create("ECVO");            
                   }        
                   { AgPlacement place = AgPlacement("ECVO","EMSS");           
                         /// Add daughter volume ECVO to mother EMSS           
                         place.TranslateZ(zslice-center+zwidth/2);           
                         /// Translate z = zslice-center+zwidth/2           
                         _stacker -> Position( AgBlock::Find("ECVO"), place );           
                   } // end placement of ECVO        
                   zwidth  = emcs.gapsmd;        
                   zslice  = emcs.smdcentr - emcs.gapsmd/2;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   _create = AgCreate("ESHM");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create ESHM           
                         Create("ESHM");            
                   }        
                   { AgPlacement place = AgPlacement("ESHM","EMSS");           
                         /// Add daughter volume ESHM to mother EMSS           
                         place.TranslateZ(zslice-center+zwidth/2);           
                         /// Translate z = zslice-center+zwidth/2           
                         place.par("only")=AgPlacement::kMany;           
                         /// Overlap: agplacement::kmany           
                         _stacker -> Position( AgBlock::Find("ESHM"), place );           
                   } // end placement of ESHM        
                   zslice = zslice + zwidth;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   fsect = 4                                             ;// first section;        
                   lsect = 5                                             ;// last section;        
                   zwidth = 0;        
                   /// Loop on i_section from fsect to lsect step=1        
                   for ( i_section=fsect; (1>0)? (i_section<=lsect):(i_section>=lsect); i_section+=1 )        
                   {           
                         /// USE esec isect=i_section   ;           
                         esec.Use("isect",(Float_t)i_section   );           
                         zwidth  = zwidth + esec.cell*esec.nlayer;           
                   }        
                   zwidth = emcs.bckfrnt - zslice;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   _create = AgCreate("ECVO");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create ECVO           
                         Create("ECVO");            
                   }        
                   { AgPlacement place = AgPlacement("ECVO","EMSS");           
                         /// Add daughter volume ECVO to mother EMSS           
                         place.TranslateZ(zslice-center+zwidth/2);           
                         /// Translate z = zslice-center+zwidth/2           
                         _stacker -> Position( AgBlock::Find("ECVO"), place );           
                   } // end placement of ECVO        
                   zslice = emcs.bckfrnt;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   zwidth  = emcs.bckplate;        
                   _create = AgCreate("ESSP");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create ESSP           
                         Create("ESSP");            
                   }        
                   { AgPlacement place = AgPlacement("ESSP","EMSS");           
                         /// Add daughter volume ESSP to mother EMSS           
                         place.TranslateZ(zslice-center+zwidth/2);           
                         /// Translate z = zslice-center+zwidth/2           
                         _stacker -> Position( AgBlock::Find("ESSP"), place );           
                   } // end placement of ESSP        
                   zslice = zslice + zwidth;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   zwidth = emcs.zend-emcs.zorg;        
                   _create = AgCreate("ERCM");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create ERCM           
                         Create("ERCM");            
                   }        
                   /// Loop on i from 1 to 2 step=1        
                   for ( i=1; (1>0)? (i<=2):(i>=2); i+=1 )        
                   {           
                         /// Loop on j from 1 to 5 step=1           
                         for ( j=1; (1>0)? (j<=5):(j>=5); j+=1 )           
                         {              
                               xx = emcs.phimin + j*30;              
                               yy = xx*degrad;              
                               xc = cos(yy)*emcs.tierod(i);              
                               yc = sin(yy)*emcs.tierod(i);              
                               { AgPlacement place = AgPlacement("ERCM","EMSS");                 
                                     /// Add daughter volume ERCM to mother EMSS                 
                                     place.TranslateX(xc);                 
                                     /// Translate x = xc                 
                                     place.TranslateY(yc);                 
                                     /// Translate y = yc                 
                                     place.TranslateZ(0);                 
                                     /// Translate z = 0                 
                                     _stacker -> Position( AgBlock::Find("ERCM"), place );                 
                               } // end placement of ERCM              
                         }           
                   }        
                   rth = emcs.zorg*tan_upp+dup + 2.5/2;        
                   xc = (emcs.zend - emcs.zorg)*tan_upp;        
                   length = .5*(emcs.zend + emcs.zorg)*tan_upp + dup + 2.5/2;        
                   yc = emcs.zend-emcs.zorg;        
                   p = atan(xc/yc)/degrad;        
                   _create = AgCreate("EPSB");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create EPSB           
                         Create("EPSB");            
                   }        
                   /// Loop on i from 1 to 6 step=1        
                   for ( i=1; (1>0)? (i<=6):(i>=6); i+=1 )        
                   {           
                         xx = -75 + (i-1)*30;           
                         yy = xx*degrad;           
                         xc = cos(yy)*length;           
                         yc = sin(yy)*length;           
                         { AgPlacement place = AgPlacement("EPSB","EMSS");              
                               /// Add daughter volume EPSB to mother EMSS              
                               place.TranslateX(xc);              
                               /// Translate x = xc              
                               place.TranslateY(yc);              
                               /// Translate y = yc              
                               place.AlphaZ(xx);              
                               /// Rotate: AlphaZ = xx              
                               /// G3 Reference: thetax = 90              
                               /// G3 Reference: phix = 0              
                               /// G3 Reference: thetay = 90              
                               /// G3 Reference: phiy = 90              
                               /// G3 Reference: thetaz = 0              
                               /// G3 Reference: phiz = 0              
                               _stacker -> Position( AgBlock::Find("EPSB"), place );              
                         } // end placement of EPSB           
                   }        
                   END_OF_EMSS:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EMSS  
       // ---------------------------------------------------------------------------------------------------  
       void ECVO::Block( AgCreate create )  
       {      
             ///@addtogroup ECVO_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ECAL_Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_air");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ECVO");           
                         attr.par("seen")=1;           
                         attr.par("colo")=3;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=zwidth/2;           
                         shape.par("rmn1")=zslice*tan_low-dd;           
                         shape.par("rmx1")=zslice*tan_upp+dup;           
                         shape.par("rmn2")=(zslice+zwidth)*tan_low-dd;           
                         shape.par("rmx2")=(zslice+zwidth)*tan_upp+dup;           
                         /// Shape Cons dz=zwidth/2 rmn1=zslice*tan_low-dd rmx1=zslice*tan_upp+dup rmn2=(zslice+zwidth)*tan_low-dd rmx2=(zslice+zwidth)*tan_upp+dup            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ECVO;           
                         _stacker -> Build(this);           
                   }        
                   /// Loop on i_sector from 1 to 6 step=1        
                   for ( i_sector=1; (1>0)? (i_sector<=6):(i_sector>=6); i_sector+=1 )        
                   {           
                         if (  (1<i_sector && i_sector<6)||emcg.fillmode>1 )           
                         {              
                               filled = 1;              
                         }           
                         else           
                         {              
                               filled = 0;              
                         }           
                         d3 = 75 - (i_sector-1)*30;           
                         _create = AgCreate("EMOD");           
                         {              
                               AgShape myshape; // undefined shape              
                               ///Create EMOD              
                               Create("EMOD");               
                         }           
                         { AgPlacement place = AgPlacement("EMOD","ECVO");              
                               /// Add daughter volume EMOD to mother ECVO              
                               place.par("ncopy")=i_sector;              
                               /// Ncopy: i_sector              
                               place.AlphaZ(d3);              
                               /// Rotate: AlphaZ = d3              
                               /// G3 Reference: thetax = 90              
                               /// G3 Reference: phix = 0              
                               /// G3 Reference: thetay = 90              
                               /// G3 Reference: phiy = 90              
                               /// G3 Reference: thetaz = 0              
                               /// G3 Reference: phiz = 0              
                               _stacker -> Position( AgBlock::Find("EMOD"), place );              
                         } // end placement of EMOD           
                   }        
                   END_OF_ECVO:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ECVO  
       // ---------------------------------------------------------------------------------------------------  
       void ESHM::Block( AgCreate create )  
       {      
             ///@addtogroup ESHM_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ECAL_Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_air");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ESHM");           
                         attr.par("seen")=1;           
                         attr.par("colo")=4;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=zwidth/2;           
                         shape.par("rmn1")=(zslice*tan_low)-dd;           
                         shape.par("rmx1")=(zslice)*tan_upp+dup;           
                         shape.par("rmn2")=(zslice+zwidth)*tan_low-dd;           
                         shape.par("rmx2")=(zslice+zwidth)*tan_upp+dup;           
                         shape.par("phi1")=emcs.phimin;           
                         shape.par("phi2")=emcs.phimax;           
                         /// Shape Cons dz=zwidth/2 rmn1=(zslice*tan_low)-dd rmx1=(zslice)*tan_upp+dup rmn2=(zslice+zwidth)*tan_low-dd rmx2=(zslice+zwidth)*tan_upp+dup phi1=emcs.phimin phi2=emcs.phimax            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ESHM;           
                         _stacker -> Build(this);           
                   }        
                   /// USE emxg _index=1;        
                   emxg.Use();        
                   maxcnt = emcs.smdcentr;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   /// Loop on j_section from 1 to 3 step=1        
                   for ( j_section=1; (1>0)? (j_section<=3):(j_section>=3); j_section+=1 )        
                   {           
                         /// USE exse jsect=j_section ;           
                         exse.Use("jsect",(Float_t)j_section );           
                         current = exse.zshift;           
                         secwid  = emxg.sapex + 2.*emxg.f4;           
                         section = maxcnt + exse.zshift;           
                         // Print<level=%i> fmt=%s fortran format statements not supported           
                         rbot=section*tan_low;           
                         rtop=section*tan_upp;           
                         // Print<level=%i> fmt=%s fortran format statements not supported           
                         // Print<level=%i> fmt=%s fortran format statements not supported           
                         _create = AgCreate("ESPL");           
                         {              
                               AgShape myshape; // undefined shape              
                               ///Create ESPL              
                               Create("ESPL");               
                         }           
                         { AgPlacement place = AgPlacement("ESPL","ESHM");              
                               /// Add daughter volume ESPL to mother ESHM              
                               place.TranslateZ(current);              
                               /// Translate z = current              
                               place.par("only")=AgPlacement::kMany;              
                               /// Overlap: agplacement::kmany              
                               _stacker -> Position( AgBlock::Find("ESPL"), place );              
                         } // end placement of ESPL           
                   }        
                   _create = AgCreate("ERSM");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create ERSM           
                         Create("ERSM");            
                   }        
                   /// Loop on i from 1 to 2 step=1        
                   for ( i=1; (1>0)? (i<=2):(i>=2); i+=1 )        
                   {           
                         /// Loop on j from 1 to 5 step=1           
                         for ( j=1; (1>0)? (j<=5):(j>=5); j+=1 )           
                         {              
                               xx = emcs.phimin + j*30;              
                               yy = xx*degrad;              
                               xc = cos(yy)*emcs.tierod(i);              
                               yc = sin(yy)*emcs.tierod(i);              
                               { AgPlacement place = AgPlacement("ERSM","ESHM");                 
                                     /// Add daughter volume ERSM to mother ESHM                 
                                     place.TranslateX(xc);                 
                                     /// Translate x = xc                 
                                     place.TranslateY(yc);                 
                                     /// Translate y = yc                 
                                     place.TranslateZ(0);                 
                                     /// Translate z = 0                 
                                     _stacker -> Position( AgBlock::Find("ERSM"), place );                 
                               } // end placement of ERSM              
                         }           
                   }        
                   END_OF_ESHM:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ESHM  
       // ---------------------------------------------------------------------------------------------------  
       void ECGH::Block( AgCreate create )  
       {      
             ///@addtogroup ECGH_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ECAL_Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_air");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ECGH");           
                         attr.par("seen")=0;           
                         attr.par("colo")=7;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Trd1");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dx1")=emcs.zorg*tan_upp+dup;           
                         shape.par("dx2")=emcs.zend*tan_upp+dup;           
                         shape.par("dy")=(emcs.gaphalf+emcs.cover)/2;           
                         shape.par("dz")=(emcs.zend-emcs.zorg)/2;           
                         /// Shape Trd1 dx1=emcs.zorg*tan_upp+dup dx2=emcs.zend*tan_upp+dup dy=(emcs.gaphalf+emcs.cover)/2 dz=(emcs.zend-emcs.zorg)/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ECGH;           
                         _stacker -> Build(this);           
                   }        
                   rth = emcs.gaphalf + emcs.cover;        
                   xx=curr*tan_low-d2;        
                   xleft = sqrt(xx*xx - rth*rth);        
                   yy=curr*tan_upp+dup;        
                   xright = sqrt(yy*yy - rth*rth);        
                   secwid = yy - xx;        
                   xx=curcl*tan_low-d2;        
                   yleft = sqrt(xx*xx - rth*rth);        
                   yy=curcl*tan_upp+dup;        
                   yright = sqrt(yy*yy - rth*rth);        
                   zwidth = yy - xx;        
                   xx=(xleft+xright)/2;        
                   yy=(yleft + yright)/2;        
                   xc = yy - xx;        
                   length = (xx+yy)/2;        
                   yc = curcl - curr;        
                   p = atan(xc/yc)/degrad;        
                   rth = -(emcs.gaphalf + emcs.cover)/2;        
                   _create = AgCreate("ECHC");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create ECHC           
                         Create("ECHC");            
                   }        
                   { AgPlacement place = AgPlacement("ECHC","ECGH");           
                         /// Add daughter volume ECHC to mother ECGH           
                         place.TranslateX(+length);           
                         /// Translate x = +length           
                         place.TranslateY(rth);           
                         /// Translate y = rth           
                         _stacker -> Position( AgBlock::Find("ECHC"), place );           
                   } // end placement of ECHC        
                   { AgPlacement place = AgPlacement("ECHC","ECGH");           
                         /// Add daughter volume ECHC to mother ECGH           
                         place.TranslateX(-length);           
                         /// Translate x = -length           
                         place.TranslateY(rth);           
                         /// Translate y = rth           
                         place.AlphaZ(180);           
                         /// Rotate: AlphaZ = 180           
                         /// G3 Reference: thetax = 90           
                         /// G3 Reference: phix = 0           
                         /// G3 Reference: thetay = 90           
                         /// G3 Reference: phiy = 90           
                         /// G3 Reference: thetaz = 0           
                         /// G3 Reference: phiz = 0           
                         _stacker -> Position( AgBlock::Find("ECHC"), place );           
                   } // end placement of ECHC        
                   END_OF_ECGH:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ECGH  
       // ---------------------------------------------------------------------------------------------------  
       void ECHC::Block( AgCreate create )  
       {      
             ///@addtogroup ECHC_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ecal_steel         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_steel");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ECHC");           
                         attr.par("seen")=1;           
                         attr.par("colo")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Trap");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=(curcl-curr)/2;           
                         shape.par("thet")=p;           
                         shape.par("phi")=0;           
                         shape.par("h1")=emcs.cover/2;           
                         shape.par("bl1")=secwid/2;           
                         shape.par("tl1")=secwid/2;           
                         shape.par("alp1")=0;           
                         shape.par("h2")=emcs.cover/2;           
                         shape.par("bl2")=zwidth/2;           
                         shape.par("tl2")=zwidth/2;           
                         shape.par("alp2")=0;           
                         /// Shape Trap dz=(curcl-curr)/2 thet=p phi=0 h1=emcs.cover/2 bl1=secwid/2 tl1=secwid/2 alp1=0 h2=emcs.cover/2 bl2=zwidth/2 tl2=zwidth/2 alp2=0            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ECHC;           
                         _stacker -> Build(this);           
                   }        
                   END_OF_ECHC:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ECHC  
       // ---------------------------------------------------------------------------------------------------  
       void ESSP::Block( AgCreate create )  
       {      
             ///@addtogroup ESSP_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ecal_steel         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_steel");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ESSP");           
                         attr.par("seen")=1;           
                         attr.par("colo")=6;           
                         attr.par("fill")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=emcs.bckplate/2;           
                         shape.par("rmn1")=zslice*tan_low-dd;           
                         shape.par("rmx1")=zslice*tan_upp+dup;           
                         shape.par("rmn2")=(zslice+zwidth)*tan_low-dd;           
                         shape.par("rmx2")=(zslice+zwidth)*tan_upp+dup;           
                         shape.par("phi1")=emcs.phimin;           
                         shape.par("phi2")=emcs.phimax;           
                         /// Shape Cons dz=emcs.bckplate/2 rmn1=zslice*tan_low-dd rmx1=zslice*tan_upp+dup rmn2=(zslice+zwidth)*tan_low-dd rmx2=(zslice+zwidth)*tan_upp+dup phi1=emcs.phimin phi2=emcs.phimax            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ESSP;           
                         _stacker -> Build(this);           
                   }        
                   END_OF_ESSP:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ESSP  
       // ---------------------------------------------------------------------------------------------------  
       void EPSB::Block( AgCreate create )  
       {      
             ///@addtogroup EPSB_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material Ecal_Steel         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_steel");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("EPSB");           
                         attr.par("seen")=1;           
                         attr.par("colo")=6;           
                         attr.par("fill")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Trap");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=(emcs.zend-emcs.zorg)/2;           
                         shape.par("thet")=p;           
                         shape.par("phi")=0;           
                         shape.par("h1")=2.0/2;           
                         shape.par("bl1")=2.5/2;           
                         shape.par("tl1")=2.5/2;           
                         shape.par("alp1")=0;           
                         shape.par("h2")=2.0/2;           
                         shape.par("bl2")=2.5/2;           
                         shape.par("tl2")=2.5/2;           
                         shape.par("alp2")=0;           
                         /// Shape Trap dz=(emcs.zend-emcs.zorg)/2 thet=p phi=0 h1=2.0/2 bl1=2.5/2 tl1=2.5/2 alp1=0 h2=2.0/2 bl2=2.5/2 tl2=2.5/2 alp2=0            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EPSB;           
                         _stacker -> Build(this);           
                   }        
                   END_OF_EPSB:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EPSB  
       // ---------------------------------------------------------------------------------------------------  
       void ERCM::Block( AgCreate create )  
       {      
             ///@addtogroup ERCM_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material Ecal_Steel         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_steel");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ERSM");           
                         attr.par("seen")=1;           
                         attr.par("colo")=6;           
                         attr.par("fill")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Tube");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("rmin")=0;           
                         shape.par("rmax")=emcs.rtie;           
                         shape.par("dz")=zwidth/2;           
                         /// Shape Tube rmin=0 rmax=emcs.rtie dz=zwidth/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ERCM;           
                         _stacker -> Build(this);           
                   }        
                   END_OF_ERCM:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ERCM  
       // ---------------------------------------------------------------------------------------------------  
       void ERSM::Block( AgCreate create )  
       {      
             ///@addtogroup ERSM_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material Ecal_Steel         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_steel");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ERSM");           
                         attr.par("seen")=1;           
                         attr.par("colo")=6;           
                         attr.par("fill")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Tube");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("rmin")=0;           
                         shape.par("rmax")=emcs.rtie;           
                         shape.par("dz")=zwidth/2;           
                         /// Shape Tube rmin=0 rmax=emcs.rtie dz=zwidth/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ERSM;           
                         _stacker -> Build(this);           
                   }        
                   END_OF_ERSM:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ERSM  
       // ---------------------------------------------------------------------------------------------------  
       void EMOD::Block( AgCreate create )  
       {      
             ///@addtogroup EMOD_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   { AgAttribute attr = AgAttribute("EMOD");           
                         attr.par("seen")=1;           
                         attr.par("colo")=3;           
                         attr.par("serial")=filled;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   /// Material ECAL_Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_air");           
                         _material = mat;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=zwidth/2;           
                         shape.par("rmn1")=zslice*tan_low-dd;           
                         shape.par("rmx1")=zslice*tan_upp+dup;           
                         shape.par("rmn2")=(zslice+zwidth)*tan_low-dd;           
                         shape.par("rmx2")=(zslice+zwidth)*tan_upp+dup;           
                         shape.par("phi1")=emcs.phimin/emcs.nsupsec;           
                         shape.par("phi2")=emcs.phimax/emcs.nsupsec;           
                         /// Shape Cons dz=zwidth/2 rmn1=zslice*tan_low-dd rmx1=zslice*tan_upp+dup rmn2=(zslice+zwidth)*tan_low-dd rmx2=(zslice+zwidth)*tan_upp+dup phi1=emcs.phimin/emcs.nsupsec phi2=emcs.phimax/emcs.nsupsec            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EMOD;           
                         _stacker -> Build(this);           
                   }        
                   section = zslice;        
                   curr = zslice + zwidth/2;        
                   /// Loop on i_section from fsect to lsect step=1        
                   for ( i_section=fsect; (1>0)? (i_section<=lsect):(i_section>=lsect); i_section+=1 )        
                   {           
                         /// USE esec isect=i_section   ;           
                         esec.Use("isect",(Float_t)i_section   );           
                         secwid  = esec.cell*esec.nlayer;           
                         if ( i_section==3||i_section==5 )           
                         {              
                               secwid  = secwid - radiator;              
                         }           
                         else if ( i_section==4 )           
                         {              
                               secwid  = secwid - esec.cell + radiator;              
                         }           
                         // Print<level=%i> fmt=%s fortran format statements not supported           
                         _create = AgCreate("ESEC");           
                         {              
                               AgShape myshape; // undefined shape              
                               ///Create ESEC              
                               Create("ESEC");               
                         }           
                         { AgPlacement place = AgPlacement("ESEC","EMOD");              
                               /// Add daughter volume ESEC to mother EMOD              
                               place.TranslateZ(section-curr+secwid/2);              
                               /// Translate z = section-curr+secwid/2              
                               _stacker -> Position( AgBlock::Find("ESEC"), place );              
                         } // end placement of ESEC           
                         section = section + secwid;           
                   }        
                   END_OF_EMOD:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EMOD  
       // ---------------------------------------------------------------------------------------------------  
       void ESEC::Block( AgCreate create )  
       {      
             ///@addtogroup ESEC_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ECAL_Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_air");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ESEC");           
                         attr.par("seen")=1;           
                         attr.par("colo")=1;           
                         attr.par("serial")=filled;           
                         attr.par("lsty")=2;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=secwid/2;           
                         shape.par("rmn1")=(section)*tan_low-dd;           
                         shape.par("rmx1")=(section)*tan_upp+dup;           
                         shape.par("rmn2")=(section+secwid)*tan_low-dd;           
                         shape.par("rmx2")=(section+secwid)*tan_upp+dup;           
                         /// Shape Cons dz=secwid/2 rmn1=(section)*tan_low-dd rmx1=(section)*tan_upp+dup rmn2=(section+secwid)*tan_low-dd rmx2=(section+secwid)*tan_upp+dup            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ESEC;           
                         _stacker -> Build(this);           
                   }        
                   length = -secwid/2;        
                   current = section;        
                   megatile = esec.scint+emcs.alincell+emcs.frplast+emcs.bkplast;        
                   gap = esec.cell - radiator - megatile;        
                   // Print<level=%i> fmt=%s fortran format statements not supported        
                   /// Loop on is from 1 to esec.nlayer step=1        
                   for ( is=1; (1>0)? (is<=esec.nlayer):(is>=esec.nlayer); is+=1 )        
                   {           
                         cell  = esec.cell;           
                         plate = radiator;           
                         if ( is==nint(esec.nlayer) && (i_section==3||i_section==5) )           
                         {              
                               cell = megatile + gap;              
                               plate=0;              
                         }           
                         else if ( i_section==4&&is==1 )           
                         {              
                               cell = radiator;              
                         }           
                         // Print<level=%i> fmt=%s fortran format statements not supported           
                         if ( i_section==4&&is==1 )           
                         {              
                               cell = radiator + emcs.slop;              
                               // Print<level=%i> fmt=%s fortran format statements not supported              
                               _create = AgCreate("ERAD");              
                               {                 
                                     AgShape myshape; // undefined shape                 
                                     ///Create ERAD                 
                                     Create("ERAD");                  
                               }              
                               { AgPlacement place = AgPlacement("ERAD","ESEC");                 
                                     /// Add daughter volume ERAD to mother ESEC                 
                                     place.TranslateZ(length+(cell)/2+esec.deltaz);                 
                                     /// Translate z = length+(cell)/2+esec.deltaz                 
                                     _stacker -> Position( AgBlock::Find("ERAD"), place );                 
                               } // end placement of ERAD              
                               length  = length + cell;              
                               current = current + cell;              
                         }           
                         else           
                         {              
                               cell = megatile;              
                               if ( filled==1 )              
                               {                 
                                     _create = AgCreate("EMGT");                 
                                     {                    
                                           AgShape myshape; // undefined shape                    
                                           ///Create EMGT                    
                                           Create("EMGT");                     
                                     }                 
                                     { AgPlacement place = AgPlacement("EMGT","ESEC");                    
                                           /// Add daughter volume EMGT to mother ESEC                    
                                           place.TranslateZ(length+(gap+cell)/2+esec.deltaz);                    
                                           /// Translate z = length+(gap+cell)/2+esec.deltaz                    
                                           _stacker -> Position( AgBlock::Find("EMGT"), place );                    
                                     } // end placement of EMGT                 
                                     xx = current + (gap+cell)/2+esec.deltaz;                 
                                     // Print<level=%i> fmt=%s fortran format statements not supported                 
                                     // Print<level=%i> fmt=%s fortran format statements not supported                 
                               }              
                               length  = length  + cell + gap;              
                               current = current + cell + gap;              
                               if ( plate>0 )              
                               {                 
                                     cell = radiator;                 
                                     // Print<level=%i> fmt=%s fortran format statements not supported                 
                                     _create = AgCreate("ERAD");                 
                                     {                    
                                           AgShape myshape; // undefined shape                    
                                           ///Create ERAD                    
                                           Create("ERAD");                     
                                     }                 
                                     { AgPlacement place = AgPlacement("ERAD","ESEC");                    
                                           /// Add daughter volume ERAD to mother ESEC                    
                                           place.TranslateZ(length+cell/2+esec.deltaz);                    
                                           /// Translate z = length+cell/2+esec.deltaz                    
                                           _stacker -> Position( AgBlock::Find("ERAD"), place );                    
                                     } // end placement of ERAD                 
                                     length  = length  + cell;                 
                                     current = current + cell;                 
                               }              
                         }           
                   }        
                   END_OF_ESEC:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ESEC  
       // ---------------------------------------------------------------------------------------------------  
       void EMGT::Block( AgCreate create )  
       {      
             ///@addtogroup EMGT_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ECAL_Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_air");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("EMGT");           
                         attr.par("seen")=1;           
                         attr.par("colo")=1;           
                         attr.par("lsty")=2;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=megatile/2;           
                         shape.par("rmn1")=(current)*tan_low-dd;           
                         shape.par("rmx1")=(current)*tan_upp+dup;           
                         shape.par("rmn2")=(current+megatile)*tan_low-dd;           
                         shape.par("rmx2")=(current+megatile)*tan_upp+dup;           
                         /// Shape Cons dz=megatile/2 rmn1=(current)*tan_low-dd rmx1=(current)*tan_upp+dup rmn2=(current+megatile)*tan_low-dd rmx2=(current+megatile)*tan_upp+dup            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EMGT;           
                         _stacker -> Build(this);           
                   }        
                   // _medium.par("CUTGAM") = 0.00001;        
                   // _medium.par("CUTELE") = 0.00001;        
                   /// Loop on isec from 1 to nint(emcs.nslices) step=1        
                   for ( isec=1; (1>0)? (isec<=nint(emcs.nslices)):(isec>=nint(emcs.nslices)); isec+=1 )        
                   {           
                         myphi = (emcs.nslices/2-isec+0.5)*dphi + esec.jiggle(is);           
                         _create = AgCreate("EPER");           
                         {              
                               AgShape myshape; // undefined shape              
                               ///Create EPER              
                               Create("EPER");               
                         }           
                         { AgPlacement place = AgPlacement("EPER","EMGT");              
                               /// Add daughter volume EPER to mother EMGT              
                               place.AlphaZ(myphi);              
                               /// Rotate: AlphaZ = myphi              
                               /// G3 Reference: thetax = 90              
                               /// G3 Reference: phix = 0              
                               /// G3 Reference: thetay = 90              
                               /// G3 Reference: phiy = 90              
                               /// G3 Reference: thetaz = 0              
                               /// G3 Reference: phiz = 0              
                               _stacker -> Position( AgBlock::Find("EPER"), place );              
                         } // end placement of EPER           
                   }        
                   END_OF_EMGT:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EMGT  
       // ---------------------------------------------------------------------------------------------------  
       void EPER::Block( AgCreate create )  
       {      
             ///@addtogroup EPER_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material Polystyren         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");           
                         _material = mat;           
                   }        
                   /// Material ECAL_Polystyren isvol=0         
                   { AgMaterial &mat = AgMaterial::Get("Ecal_polystyren");           
                         mat.par("isvol")=0;           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("EPER");           
                         attr.par("seen")=1;           
                         attr.par("colo")=1;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=megatile/2;           
                         shape.par("rmn1")=(current)*tan_low-dd;           
                         shape.par("rmx1")=(current)*tan_upp+dup;           
                         shape.par("rmn2")=(current+megatile)*tan_low-dd;           
                         shape.par("rmx2")=(current+megatile)*tan_upp+dup;           
                         shape.par("phi1")=emcs.phimin/emcs.nsector;           
                         shape.par("phi2")=emcs.phimax/emcs.nsector;           
                         /// Shape Cons dz=megatile/2 rmn1=(current)*tan_low-dd rmx1=(current)*tan_upp+dup rmn2=(current+megatile)*tan_low-dd rmx2=(current+megatile)*tan_upp+dup phi1=emcs.phimin/emcs.nsector phi2=emcs.phimax/emcs.nsector            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EPER;           
                         _stacker -> Build(this);           
                   }        
                   curcl = current+megatile/2;        
                   /// Loop on ie from 1 to nint(eetr.neta) step=1        
                   for ( ie=1; (1>0)? (ie<=nint(eetr.neta)):(ie>=nint(eetr.neta)); ie+=1 )        
                   {           
                         etabot  = eetr.etabin(ie);           
                         etatop  = eetr.etabin(ie+1);           
                         rbot=(curcl)*tanf(etabot);           
                         rtop=min((curcl)*tanf(etatop), ((current)*tan_upp+dup));           
                         if ( not ( rbot<rtop )) { continue; }           
                         xx=tan(pi*emcs.phimax/180.0/emcs.nsector);           
                         yy=cos(pi*emcs.phimax/180.0/emcs.nsector);           
                         _create = AgCreate("ETAR");           
                         {              
                               AgShape myshape; // undefined shape              
                               ///Create ETAR              
                               Create("ETAR");               
                         }           
                         { AgPlacement place = AgPlacement("ETAR","EPER");              
                               /// Add daughter volume ETAR to mother EPER              
                               place.TranslateX((rbot+rtop)/2);              
                               /// Translate x = (rbot+rtop)/2              
                               /// G3 Reference: thetax = 90              
                               /// G3 Reference: phix = 0              
                               /// G3 Reference: thetay = 90              
                               /// G3 Reference: phiy = 90              
                               /// G3 Reference: thetaz = 0              
                               /// G3 Reference: phiz = 0              
                               place.Ortho( "yzx" ); // ORT=yzx              
                               /// Axis substitution: XYZ --> yzx              
                               _stacker -> Position( AgBlock::Find("ETAR"), place );              
                         } // end placement of ETAR           
                         // Print<level=%i> fmt=%s fortran format statements not supported           
                   }        
                   END_OF_EPER:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EPER  
       // ---------------------------------------------------------------------------------------------------  
       void ETAR::Block( AgCreate create )  
       {      
             ///@addtogroup ETAR_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ECAL_POLYSTYREN         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_polystyren");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ETAR");           
                         attr.par("seen")=1;           
                         attr.par("colo")=4;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Trd1");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dx1")=rbot*xx-emcs.gapcel/yy;           
                         shape.par("dx2")=rtop*xx-emcs.gapcel/yy;           
                         shape.par("dy")=megatile/2;           
                         shape.par("dz")=(rtop-rbot)/2;           
                         /// Shape Trd1 dx1=rbot*xx-emcs.gapcel/yy dx2=rtop*xx-emcs.gapcel/yy dy=megatile/2 dz=(rtop-rbot)/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ETAR;           
                         _stacker -> Build(this);           
                   }        
                   _create = AgCreate("EALP");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create EALP           
                         Create("EALP");            
                   }        
                   { AgPlacement place = AgPlacement("EALP","ETAR");           
                         /// Add daughter volume EALP to mother ETAR           
                         place.TranslateY((-megatile+emcs.alincell)/2);           
                         /// Translate y = (-megatile+emcs.alincell)/2           
                         _stacker -> Position( AgBlock::Find("EALP"), place );           
                   } // end placement of EALP        
                   g10 = esec.scint;        
                   _create = AgCreate("ESCI");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create ESCI           
                         Create("ESCI");            
                   }        
                   { AgPlacement place = AgPlacement("ESCI","ETAR");           
                         /// Add daughter volume ESCI to mother ETAR           
                         place.TranslateY((-megatile+g10)/2+emcs.alincell+emcs.frplast);           
                         /// Translate y = (-megatile+g10)/2+emcs.alincell+emcs.frplast           
                         _stacker -> Position( AgBlock::Find("ESCI"), place );           
                   } // end placement of ESCI        
                   END_OF_ETAR:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ETAR  
       // ---------------------------------------------------------------------------------------------------  
       void ESCI::Block( AgCreate create )  
       {      
             ///@addtogroup ESCI_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material Polystyren         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");           
                         _material = mat;           
                   }        
                   /// Material Ecal_scint isvol=1         
                   { AgMaterial &mat = AgMaterial::Get("Ecal_scint");           
                         mat.par("isvol")=1;           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ESCI");           
                         attr.par("seen")=1;           
                         attr.par("colo")=7;           
                         attr.par("fill")=0;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Trd1");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dy")=esec.scint/2;           
                         shape.par("dz")=(rtop-rbot)/2-emcs.gapcel;           
                         /// Shape Trd1 dy=esec.scint/2 dz=(rtop-rbot)/2-emcs.gapcel            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ESCI;           
                         _stacker -> Build(this);           
                   }        
                   // _medium.par("CUTGAM") = 0.00008;        
                   // _medium.par("CUTELE") = 0.001;        
                   // _medium.par("BCUTE") = 0.0001;        
                   // _medium.par("CUTNEU") = 0.001;        
                   // _medium.par("CUTHAD") = 0.001;        
                   // _medium.par("CUTMUO") = 0.001;        
                   // _medium.par("BIRK1") = 1.;        
                   // _medium.par("BIRK2") = 0.013;        
                   // _medium.par("BIRK3") = 9.6E-6;        
                   END_OF_ESCI:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ESCI  
       // ---------------------------------------------------------------------------------------------------  
       void ERAD::Block( AgCreate create )  
       {      
             ///@addtogroup ERAD_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ECAL_STEEL         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_steel");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ERAD");           
                         attr.par("seen")=1;           
                         attr.par("colo")=6;           
                         attr.par("fill")=1;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=radiator/2;           
                         shape.par("rmn1")=(current)*tan_low-dd;           
                         shape.par("rmx1")=(current)*tan_upp+dup;           
                         shape.par("rmn2")=(current+cell)*tan_low-dd;           
                         shape.par("rmx2")=(current+radiator)*tan_upp+dup;           
                         /// Shape Cons dz=radiator/2 rmn1=(current)*tan_low-dd rmx1=(current)*tan_upp+dup rmn2=(current+cell)*tan_low-dd rmx2=(current+radiator)*tan_upp+dup            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ERAD;           
                         _stacker -> Build(this);           
                   }        
                   _create = AgCreate("ELED");        
                   {           
                         AgShape myshape; // undefined shape           
                         ///Create ELED           
                         Create("ELED");            
                   }        
                   { AgPlacement place = AgPlacement("ELED","ERAD");           
                         /// Add daughter volume ELED to mother ERAD           
                         _stacker -> Position( AgBlock::Find("ELED"), place );           
                   } // end placement of ELED        
                   END_OF_ERAD:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ERAD  
       // ---------------------------------------------------------------------------------------------------  
       void ELED::Block( AgCreate create )  
       {      
             ///@addtogroup ELED_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Component Sn	a=118.710	z=50	w=0.014        
                   /// Component Ca	a=40.0780	z=20	w=0.00075        
                   /// Component Al	a=26.9815	z=13	w=0.0003        
                   /// Component Pb	a=207.190	z=82	w=0.98495        
                   /// Mixture ECAL_PbAlloy dens=11.35        
                   {  AgMaterial &mix = AgMaterial::Get("Ecal_pballoy");           
                         mix.Component("Sn",118.710,50,0.014);           
                         mix.Component("Ca",40.0780,20,0.00075);           
                         mix.Component("Al",26.9815,13,0.0003);           
                         mix.Component("Pb",207.190,82,0.98495);           
                         mix.par("dens")=11.35;           
                         mix.lock();           
                         _material = mix;           
                         _material.lock();           
                   }        
                   { AgAttribute attr = AgAttribute("ELED");           
                         attr.par("seen")=1;           
                         attr.par("colo")=4;           
                         attr.par("fill")=1;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Tubs");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("rmin")=(current)*tan_low;           
                         shape.par("rmax")=(current+emcs.pbplate)*tan_upp;           
                         shape.par("dz")=emcs.pbplate/2;           
                         /// Shape Tubs rmin=(current)*tan_low rmax=(current+emcs.pbplate)*tan_upp dz=emcs.pbplate/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ELED;           
                         _stacker -> Build(this);           
                   }        
                   // _medium.par("CUTGAM") = 0.00008;        
                   // _medium.par("CUTELE") = 0.001;        
                   // _medium.par("BCUTE") = 0.0001;        
                   // _medium.par("CUTNEU") = 0.001;        
                   // _medium.par("CUTHAD") = 0.001;        
                   // _medium.par("CUTMUO") = 0.001;        
                   END_OF_ELED:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ELED  
       // ---------------------------------------------------------------------------------------------------  
       void EFLP::Block( AgCreate create )  
       {      
             ///@addtogroup EFLP_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ALUMINIUM         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");           
                         _material = mat;           
                   }        
                   /// Material ECAL_ALUMINIUM isvol=0         
                   { AgMaterial &mat = AgMaterial::Get("Ecal_aluminium");           
                         mat.par("isvol")=0;           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("EFLP");           
                         attr.par("seen")=1;           
                         attr.par("colo")=3;           
                         attr.par("fill")=1;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Cons");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dz")=emcs.front/2;           
                         shape.par("rmn1")=68.813;           
                         shape.par("rmx1")=(zslice)*tan_upp+dup;           
                         shape.par("rmn2")=68.813;           
                         shape.par("rmx2")=(zslice+zwidth)*tan_upp+dup;           
                         shape.par("phi1")=emcs.phimin;           
                         shape.par("phi2")=emcs.phimax;           
                         /// Shape Cons dz=emcs.front/2 rmn1=68.813 rmx1=(zslice)*tan_upp+dup rmn2=68.813 rmx2=(zslice+zwidth)*tan_upp+dup phi1=emcs.phimin phi2=emcs.phimax            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EFLP;           
                         _stacker -> Build(this);           
                   }        
                   END_OF_EFLP:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EFLP  
       // ---------------------------------------------------------------------------------------------------  
       void EALP::Block( AgCreate create )  
       {      
             ///@addtogroup EALP_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material Aluminium         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Aluminium");           
                         _material = mat;           
                   }        
                   /// Material ECAL_AluPlate isvol=0         
                   { AgMaterial &mat = AgMaterial::Get("Ecal_aluplate");           
                         mat.par("isvol")=0;           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("EALP");           
                         attr.par("seen")=1;           
                         attr.par("colo")=1;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Trd1");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dy")=emcs.alincell/2;           
                         shape.par("dz")=(rtop-rbot)/2;           
                         /// Shape Trd1 dy=emcs.alincell/2 dz=(rtop-rbot)/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EALP;           
                         _stacker -> Build(this);           
                   }        
                   // _medium.par("CUTGAM") = 0.00001;        
                   // _medium.par("CUTELE") = 0.00001;        
                   // _medium.par("LOSS") = 1.;        
                   // _medium.par("STRA") = 1.;        
                   END_OF_EALP:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EALP  
       // ---------------------------------------------------------------------------------------------------  
       void ESPL::Block( AgCreate create )  
       {      
             ///@addtogroup ESPL_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material ECAL_Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_air");           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("ESPL");           
                         attr.par("seen")=1;           
                         attr.par("colo")=4;           
                         attr.par("lsty")=4;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Tubs");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("rmin")=section*tan_low-1.526;           
                         shape.par("rmax")=(section-secwid/2)*tan_upp+dup;           
                         shape.par("phi1")=emcs.phimin;           
                         shape.par("phi2")=emcs.phimax;           
                         shape.par("dz")=emcs.gapsmd/3/2;           
                         /// Shape Tubs rmin=section*tan_low-1.526 rmax=(section-secwid/2)*tan_upp+dup phi1=emcs.phimin phi2=emcs.phimax dz=emcs.gapsmd/3/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_ESPL;           
                         _stacker -> Build(this);           
                   }        
                   /// USE emxg version=1 ;        
                   emxg.Use("version",(Float_t)1 );        
                   msecwd = (emxg.sapex+emxg.f4)/2;        
                   /// Loop on isec from 1 to 6 step=1        
                   for ( isec=1; (1>0)? (isec<=6):(isec>=6); isec+=1 )        
                   {           
                         cut=1;           
                         d3 = 75 - (isec-1)*30;           
                         if ( exse.sectype(isec)==0||(emcg.fillmode==1&&(isec==6||isec==1)) )           
                         {              
                               cut = 0;              
                         }           
                         else if ( exse.sectype(isec)==1 )           
                         {              
                               _create = AgCreate("EXSG");              
                               {                 
                                     AgShape myshape; // undefined shape                 
                                     ///Create EXSG                 
                                     Create("EXSG");                  
                               }              
                               { AgPlacement place = AgPlacement("EXSG","ESPL");                 
                                     /// Add daughter volume EXSG to mother ESPL                 
                                     place.par("only")=AgPlacement::kMany;                 
                                     /// Overlap: agplacement::kmany                 
                                     place.par("ncopy")=isec;                 
                                     /// Ncopy: isec                 
                                     place.AlphaZ(d3);                 
                                     /// Rotate: AlphaZ = d3                 
                                     /// G3 Reference: thetax = 90                 
                                     /// G3 Reference: phix = 0                 
                                     /// G3 Reference: thetay = 90                 
                                     /// G3 Reference: phiy = 90                 
                                     /// G3 Reference: thetaz = 0                 
                                     /// G3 Reference: phiz = 0                 
                                     _stacker -> Position( AgBlock::Find("EXSG"), place );                 
                               } // end placement of EXSG              
                         }           
                         else if ( exse.sectype(isec)==2 )           
                         {              
                               _create = AgCreate("EXSG");              
                               {                 
                                     AgShape myshape; // undefined shape                 
                                     ///Create EXSG                 
                                     Create("EXSG");                  
                               }              
                               { AgPlacement place = AgPlacement("EXSG","ESPL");                 
                                     /// Add daughter volume EXSG to mother ESPL                 
                                     place.par("only")=AgPlacement::kMany;                 
                                     /// Overlap: agplacement::kmany                 
                                     place.par("ncopy")=isec;                 
                                     /// Ncopy: isec                 
                                     place.AlphaZ(d3);                 
                                     /// Rotate: AlphaZ = d3                 
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
                                     place.Ortho( "x-y-z" ); // ORT=x-y-z                 
                                     /// Axis substitution: XYZ --> x-y-z                 
                                     _stacker -> Position( AgBlock::Find("EXSG"), place );                 
                               } // end placement of EXSG              
                         }           
                         else if ( exse.sectype(isec)==3 )           
                         {              
                               cut=2;              
                               _create = AgCreate("EXSG");              
                               {                 
                                     AgShape myshape; // undefined shape                 
                                     ///Create EXSG                 
                                     Create("EXSG");                  
                               }              
                               { AgPlacement place = AgPlacement("EXSG","ESPL");                 
                                     /// Add daughter volume EXSG to mother ESPL                 
                                     place.par("only")=AgPlacement::kMany;                 
                                     /// Overlap: agplacement::kmany                 
                                     place.par("ncopy")=isec;                 
                                     /// Ncopy: isec                 
                                     place.AlphaZ(d3);                 
                                     /// Rotate: AlphaZ = d3                 
                                     /// G3 Reference: thetax = 90                 
                                     /// G3 Reference: phix = 0                 
                                     /// G3 Reference: thetay = 90                 
                                     /// G3 Reference: phiy = 90                 
                                     /// G3 Reference: thetaz = 0                 
                                     /// G3 Reference: phiz = 0                 
                                     _stacker -> Position( AgBlock::Find("EXSG"), place );                 
                               } // end placement of EXSG              
                         }           
                         else if ( exse.sectype(isec)==4 )           
                         {              
                               cut=2;              
                               _create = AgCreate("EXSG");              
                               {                 
                                     AgShape myshape; // undefined shape                 
                                     ///Create EXSG                 
                                     Create("EXSG");                  
                               }              
                               { AgPlacement place = AgPlacement("EXSG","ESPL");                 
                                     /// Add daughter volume EXSG to mother ESPL                 
                                     place.par("only")=AgPlacement::kMany;                 
                                     /// Overlap: agplacement::kmany                 
                                     place.par("ncopy")=isec;                 
                                     /// Ncopy: isec                 
                                     place.AlphaZ(d3);                 
                                     /// Rotate: AlphaZ = d3                 
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
                                     place.Ortho( "x-y-z" ); // ORT=x-y-z                 
                                     /// Axis substitution: XYZ --> x-y-z                 
                                     _stacker -> Position( AgBlock::Find("EXSG"), place );                 
                               } // end placement of EXSG              
                         }           
                   }        
                   /// Loop on isec from 1 to 6 step=1        
                   for ( isec=1; (1>0)? (isec<=6):(isec>=6); isec+=1 )        
                   {           
                         d3=75 - (isec-1)*30;           
                         if ( exse.sectype(isec)==0||(emcg.fillmode==1&&(isec==6||isec==1)) )           
                         {              
                               cut = 0;              
                               _create = AgCreate("EXSG");              
                               {                 
                                     AgShape myshape; // undefined shape                 
                                     ///Create EXSG                 
                                     Create("EXSG");                  
                               }              
                               { AgPlacement place = AgPlacement("EXSG","ESPL");                 
                                     /// Add daughter volume EXSG to mother ESPL                 
                                     place.par("only")=AgPlacement::kMany;                 
                                     /// Overlap: agplacement::kmany                 
                                     place.par("ncopy")=isec;                 
                                     /// Ncopy: isec                 
                                     place.AlphaZ(d3);                 
                                     /// Rotate: AlphaZ = d3                 
                                     /// G3 Reference: thetax = 90                 
                                     /// G3 Reference: phix = 0                 
                                     /// G3 Reference: thetay = 90                 
                                     /// G3 Reference: phiy = 90                 
                                     /// G3 Reference: thetaz = 0                 
                                     /// G3 Reference: phiz = 0                 
                                     _stacker -> Position( AgBlock::Find("EXSG"), place );                 
                               } // end placement of EXSG              
                         }           
                   }        
                   END_OF_ESPL:        
                   mCurrent = _save;        
             ///@}     
       } // End Block ESPL  
       // ---------------------------------------------------------------------------------------------------  
       void EXSG::Block( AgCreate create )  
       {      
             ///@addtogroup EXSG_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   { AgAttribute attr = AgAttribute("EXSG");           
                         attr.par("seen")=1;           
                         attr.par("colo")=7;           
                         attr.par("serial")=cut;           
                         attr.par("lsty")=3;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   /// Material ECAL_Air         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Ecal_air");           
                         _material = mat;           
                   }        
                   {  AgShape shape = AgShape("Tubs");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("rmin")=section*tan_low-1.526;           
                         shape.par("rmax")=(section-secwid/2)*tan_upp+dup;           
                         shape.par("phi1")=emcs.phimin/emcs.nsupsec-5;           
                         shape.par("phi2")=emcs.phimax/emcs.nsupsec+5;           
                         shape.par("dz")=emcs.gapsmd/3/2;           
                         /// Shape Tubs rmin=section*tan_low-1.526 rmax=(section-secwid/2)*tan_upp+dup phi1=emcs.phimin/emcs.nsupsec-5 phi2=emcs.phimax/emcs.nsupsec+5 dz=emcs.gapsmd/3/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EXSG;           
                         _stacker -> Build(this);           
                   }        
                   rbot = emxg.rin;        
                   rtop = emxg.rout;        
                   if ( cut==0 )        
                   {           
                         _create = AgCreate("EXPS");           
                         {              
                               AgShape myshape; // undefined shape              
                               ///Create EXPS              
                               Create("EXPS");               
                         }           
                         { AgPlacement place = AgPlacement("EXPS","EXSG");              
                               /// Add daughter volume EXPS to mother EXSG              
                               place.par("only")=AgPlacement::kMany;              
                               /// Overlap: agplacement::kmany              
                               _stacker -> Position( AgBlock::Find("EXPS"), place );              
                         } // end placement of EXPS           
                   }        
                   if ( cut>0 )        
                   {           
                         if ( cut==1 )           
                         {              
                               nstr = 288;              
                         }           
                         else           
                         {              
                               nstr = 285;              
                         }           
                         /// Loop on istrip from 1 to nstr step=1           
                         for ( istrip=1; (1>0)? (istrip<=nstr):(istrip>=nstr); istrip+=1 )           
                         {              
                               ecal_get_strip( section,cut,istrip,xc,yc,length );// CALL ecal_get_strip              
                               if ( mod(istrip,2)!=0 )              
                               {                 
                                     _create = AgCreate("EHMS");                 
                                     {                    
                                           AgShape myshape; // undefined shape                    
                                           ///Create EHMS                    
                                           Create("EHMS");                     
                                     }                 
                                     { AgPlacement place = AgPlacement("EHMS","EXSG");                    
                                           /// Add daughter volume EHMS to mother EXSG                    
                                           place.TranslateX(xc);                    
                                           /// Translate x = xc                    
                                           place.TranslateY(yc);                    
                                           /// Translate y = yc                    
                                           place.AlphaZ(-45);                    
                                           /// Rotate: AlphaZ = -45                    
                                           /// G3 Reference: thetax = 90                    
                                           /// G3 Reference: phix = 0                    
                                           /// G3 Reference: thetay = 90                    
                                           /// G3 Reference: phiy = 90                    
                                           /// G3 Reference: thetaz = 0                    
                                           /// G3 Reference: phiz = 0                    
                                           _stacker -> Position( AgBlock::Find("EHMS"), place );                    
                                     } // end placement of EHMS                 
                                     _create = AgCreate("EBLS");                 
                                     {                    
                                           AgShape myshape; // undefined shape                    
                                           ///Create EBLS                    
                                           Create("EBLS");                     
                                     }                 
                                     { AgPlacement place = AgPlacement("EBLS","EXSG");                    
                                           /// Add daughter volume EBLS to mother EXSG                    
                                           place.TranslateX(xc);                    
                                           /// Translate x = xc                    
                                           place.TranslateY(yc);                    
                                           /// Translate y = yc                    
                                           place.TranslateZ((+esmd.apex/2+esmd.back_layer/2));                    
                                           /// Translate z = (+esmd.apex/2+esmd.back_layer/2)                    
                                           place.AlphaZ(-45);                    
                                           /// Rotate: AlphaZ = -45                    
                                           /// G3 Reference: thetax = 90                    
                                           /// G3 Reference: phix = 0                    
                                           /// G3 Reference: thetay = 90                    
                                           /// G3 Reference: phiy = 90                    
                                           /// G3 Reference: thetaz = 0                    
                                           /// G3 Reference: phiz = 0                    
                                           _stacker -> Position( AgBlock::Find("EBLS"), place );                    
                                     } // end placement of EBLS                 
                               }              
                               else              
                               {                 
                                     _create = AgCreate("EHMS");                 
                                     {                    
                                           AgShape myshape; // undefined shape                    
                                           ///Create EHMS                    
                                           Create("EHMS");                     
                                     }                 
                                     { AgPlacement place = AgPlacement("EHMS","EXSG");                    
                                           /// Add daughter volume EHMS to mother EXSG                    
                                           place.TranslateX(xc);                    
                                           /// Translate x = xc                    
                                           place.TranslateY(yc);                    
                                           /// Translate y = yc                    
                                           place.AlphaZ(-45);                    
                                           /// Rotate: AlphaZ = -45                    
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
                                           place.Ortho( "x-y-z" ); // ORT=x-y-z                    
                                           /// Axis substitution: XYZ --> x-y-z                    
                                           _stacker -> Position( AgBlock::Find("EHMS"), place );                    
                                     } // end placement of EHMS                 
                                     _create = AgCreate("EFLS");                 
                                     {                    
                                           AgShape myshape; // undefined shape                    
                                           ///Create EFLS                    
                                           Create("EFLS");                     
                                     }                 
                                     { AgPlacement place = AgPlacement("EFLS","EXSG");                    
                                           /// Add daughter volume EFLS to mother EXSG                    
                                           place.TranslateX(xc);                    
                                           /// Translate x = xc                    
                                           place.TranslateY(yc);                    
                                           /// Translate y = yc                    
                                           place.TranslateZ((-esmd.apex/2-esmd.front_layer/2));                    
                                           /// Translate z = (-esmd.apex/2-esmd.front_layer/2)                    
                                           place.AlphaZ(-45);                    
                                           /// Rotate: AlphaZ = -45                    
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
                                           place.Ortho( "x-y-z" ); // ORT=x-y-z                    
                                           /// Axis substitution: XYZ --> x-y-z                    
                                           _stacker -> Position( AgBlock::Find("EFLS"), place );                    
                                     } // end placement of EFLS                 
                               }              
                         }           
                   }        
                   END_OF_EXSG:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EXSG  
       // ---------------------------------------------------------------------------------------------------  
       void EHMS::Block( AgCreate create )  
       {      
             ///@addtogroup EHMS_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Material Polystyren         
                   {  AgMaterial mat = AgMaterial::CopyMaterial("Polystyren");           
                         _material = mat;           
                   }        
                   /// Material ECAL_smdstrip isvol=1         
                   { AgMaterial &mat = AgMaterial::Get("Ecal_smdstrip");           
                         mat.par("isvol")=1;           
                         _material = mat;           
                   }        
                   { AgAttribute attr = AgAttribute("EHMS");           
                         attr.par("seen")=1;           
                         attr.par("colo")=2;           
                         attr.par("serial")=cut;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Trd1");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dx1")=0;           
                         shape.par("dx2")=emxg.sbase/2;           
                         shape.par("dy")=length/2;           
                         shape.par("dz")=emxg.sapex/2;           
                         /// Shape Trd1 dx1=0 dx2=emxg.sbase/2 dy=length/2 dz=emxg.sapex/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EHMS;           
                         _stacker -> Build(this);           
                   }        
                   // _medium.par("CUTGAM") = 0.00008;        
                   // _medium.par("CUTELE") = 0.001;        
                   // _medium.par("BCUTE") = 0.0001;        
                   // _medium.par("BIRK1") = 1.;        
                   // _medium.par("BIRK2") = 0.0130;        
                   // _medium.par("BIRK3") = 9.6E-6;        
                   END_OF_EHMS:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EHMS  
       // ---------------------------------------------------------------------------------------------------  
       void EFLS::Block( AgCreate create )  
       {      
             ///@addtogroup EFLS_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Component G10	a=18.017	z=9.013	w=1.19*1.700/(1.19*1.700+0.25*1.530+0.17*1.390)        
                   /// Component Fiberglass	a=19.103	z=9.549	w=0.25*1.530/(1.19*1.700+0.25*1.530+0.17*1.390)        
                   /// Component AlMylar	a=12.889	z=6.465	w=0.17*1.390/(1.19*1.700+0.25*1.530+0.17*1.390)        
                   /// Mixture EFLS dens=(1.19*1.7+0.25*1.53+0.17*1.39)/(1.19+0.25+0.17)        
                   {  AgMaterial &mix = AgMaterial::Get("Efls");           
                         mix.Component("G10",18.017,9.013,1.19*1.700/(1.19*1.700+0.25*1.530+0.17*1.390));           
                         mix.Component("Fiberglass",19.103,9.549,0.25*1.530/(1.19*1.700+0.25*1.530+0.17*1.390));           
                         mix.Component("AlMylar",12.889,6.465,0.17*1.390/(1.19*1.700+0.25*1.530+0.17*1.390));           
                         mix.par("dens")=(1.19*1.7+0.25*1.53+0.17*1.39)/(1.19+0.25+0.17);           
                         mix.lock();           
                         _material = mix;           
                         _material.lock();           
                   }        
                   { AgAttribute attr = AgAttribute("EFLS");           
                         attr.par("seen")=0;           
                         attr.par("colo")=22;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Trd1");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dx1")=esmd.base/2;           
                         shape.par("dx2")=esmd.base/2;           
                         shape.par("dy")=length/2;           
                         shape.par("dz")=esmd.front_layer/2;           
                         /// Shape Trd1 dx1=esmd.base/2 dx2=esmd.base/2 dy=length/2 dz=esmd.front_layer/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EFLS;           
                         _stacker -> Build(this);           
                   }        
                   END_OF_EFLS:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EFLS  
       // ---------------------------------------------------------------------------------------------------  
       void EBLS::Block( AgCreate create )  
       {      
             ///@addtogroup EBLS_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Component AlMylar	a=12.889	z=6.465	w=0.10*1.390/(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699)        
                   /// Component Fiberglass	a=19.103	z=9.549	w=0.25*1.530/(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699)        
                   /// Component Polystyren	a=11.154	z=5.615	w=1.50*1.032/(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699)        
                   /// Component Al	a=28.08	z=14.00	w=0.25*2.699/(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699)        
                   /// Mixture EBLS dens=(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699)/(0.10+0.25+1.50+0.25)        
                   {  AgMaterial &mix = AgMaterial::Get("Ebls");           
                         mix.Component("AlMylar",12.889,6.465,0.10*1.390/(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699));           
                         mix.Component("Fiberglass",19.103,9.549,0.25*1.530/(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699));           
                         mix.Component("Polystyren",11.154,5.615,1.50*1.032/(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699));           
                         mix.Component("Al",28.08,14.00,0.25*2.699/(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699));           
                         mix.par("dens")=(0.10*1.390+0.25*1.530+1.50*1.032+0.25*2.699)/(0.10+0.25+1.50+0.25);           
                         mix.lock();           
                         _material = mix;           
                         _material.lock();           
                   }        
                   { AgAttribute attr = AgAttribute("EFLS");           
                         attr.par("seen")=0;           
                         attr.par("colo")=22;           
                         attr.par("lsty")=1;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Trd1");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("dx1")=esmd.base/2;           
                         shape.par("dx2")=esmd.base/2;           
                         shape.par("dy")=length/2;           
                         shape.par("dz")=esmd.back_layer/2;           
                         /// Shape Trd1 dx1=esmd.base/2 dx2=esmd.base/2 dy=length/2 dz=esmd.back_layer/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EBLS;           
                         _stacker -> Build(this);           
                   }        
                   END_OF_EBLS:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EBLS  
       // ---------------------------------------------------------------------------------------------------  
       void EXPS::Block( AgCreate create )  
       {      
             ///@addtogroup EXPS_doc     
             ///@{        
                     AgBlock *_save = mCurrent;        
                     mCurrent = this;        
                     Bool_t _same_shape = true;        
                   /// Component H	a=1	z=1	w=3.0*1.0/62.453        
                   /// Component C	a=12	z=6	w=2.0*12.0/62.453        
                   /// Component Cl	a=35.453	z=17	w=1.0*35.453/62.453        
                   /// Mixture PVC_Spacer dens=1.390*(1.20/1.00)        
                   {  AgMaterial &mix = AgMaterial::Get("Pvc_spacer");           
                         mix.Component("H",1,1,3.0*1.0/62.453);           
                         mix.Component("C",12,6,2.0*12.0/62.453);           
                         mix.Component("Cl",35.453,17,1.0*35.453/62.453);           
                         mix.par("dens")=1.390*(1.20/1.00);           
                         mix.lock();           
                         _material = mix;           
                         _material.lock();           
                   }        
                   { AgAttribute attr = AgAttribute("EXPS");           
                         attr.par("seen")=1;           
                         attr.par("colo")=6;           
                         attr.par("lsty")=1;           
                         attr.par("lwid")=2;           
                         attr.Inherit( AgBlock::previous() );            
                         _attribute = attr;           
                   }        
                   {  AgShape shape = AgShape("Tubs");           
                         shape     .Inherit( AgBlock::previous() );           
                         create     .SetParameters(shape);           
                         shape.par("rmin")=(section)*tan_low-1.526;           
                         shape.par("rmax")=(section+msecwd)*tan_upp;           
                         shape.par("phi1")=emcs.phimin/emcs.nsupsec;           
                         shape.par("phi2")=emcs.phimax/emcs.nsupsec;           
                         shape.par("dz")=1.0/2;           
                         /// Shape Tubs rmin=(section)*tan_low-1.526 rmax=(section+msecwd)*tan_upp phi1=emcs.phimin/emcs.nsupsec phi2=emcs.phimax/emcs.nsupsec dz=1.0/2            
                         _same_shape &= _stacker->SearchVolume( shape, _attribute );           
                         _shape = shape;           
                         if (_same_shape) goto END_OF_EXPS;           
                         _stacker -> Build(this);           
                   }        
                   END_OF_EXPS:        
                   mCurrent = _save;        
             ///@}     
       } // End Block EXPS  
 void ecal_get_strip(Float_t &section,Int_t &cut,Int_t &istrip,Float_t &xcenter,Float_t &ycenter,Float_t &length) {    
    ///@addtogroup EcalGeo6_vars     
    ///@{        
          Int_t nstrips;        
          //        
          /// Int_t nstrips        
    ///@}     
    ///@addtogroup EcalGeo6_vars     
    ///@{        
          Float_t rdel,rth,ddn,ddup,megatile,p,xleft,yleft,xright,yright,dxy,xx,yy,sqrt2,sqrt3;        
          //        
          /// Float_t rdel,rth,ddn,ddup,megatile,p,xleft,yleft,xright,yright,dxy,xx,yy,sqrt2,sqrt3        
    ///@}     
    ///@addtogroup EcalGeo6_vars     
    ///@{        
          Float_t base=1.0;        
          //        
          /// Float_t base=1.0        
    ///@}     
    ///@addtogroup EcalGeo6_vars     
    ///@{        
          Float_t rbot=77.41,rtop=213.922;        
          //        
          /// Float_t rbot=77.41,rtop=213.922        
    ///@}     
    ///@addtogroup EcalGeo6_vars     
    ///@{        
          Float_t tan_theta_max=0.761952162;        
          //        
          /// Float_t tan_theta_max=0.761952162        
    ///@}     
    if ( cut == 1 )     
    {        
          rdel    = 3.938;        
          nstrips = 288;        
    }     
    else     
    {        
          rdel    = -.475;        
          nstrips = 285;        
    }     
    xcenter=0.;     
    ycenter=0.;     
    length=0.;     
    if ( cut==0 )     
    {        
          return;        
    }     
    sqrt2 = sqrt(2.0);     
    sqrt3 = sqrt(3.0);     
    rth = .53*rdel        ;// .53 --- tentatavily    jcw-- wtf?;     
    ddn = sqrt(3.0)*1.713 + rdel;     
    ddup = .5*1.846 + 1.713;     
    megatile = base + .01;     
    p = .5*(istrip-1)*megatile + 41.3655;     
    if ( p<=(.5*rbot*sqrt3+rth) )     
    {        
          dxy     = 1.9375*sqrt2;        
          xleft  = .5*sqrt2*p*(sqrt3 + 1.) - dxy;        
          yleft  = .5*sqrt2*p*(sqrt3 - 1.) - dxy;        
          yright = .5*sqrt2*(sqrt( rbot*rbot - p*p) - p);        
          xright = sqrt2*p + yright;        
    }     
    else if ( (.5*rbot*sqrt3+rth)<p && p <=(.5*rtop+1.5) )     
    {        
          dxy = 1.9375*sqrt2;        
          xleft = .5*sqrt2*p*(sqrt3 + 1.) - dxy;        
          yleft = .5*sqrt2*p*(sqrt3 - 1.) - dxy;        
          dxy = rdel*sqrt2/sqrt3;        
          yright = .5*sqrt2*p*(1.- 1./sqrt3);        
          xright = sqrt2*p - yright - dxy;        
          yright = -yright - dxy;        
    }     
    else if ( p>(.5*rtop+1.5) )     
    {        
          yleft = (sqrt(rtop*rtop - p*p) - p)/sqrt2;        
          xleft = sqrt2*p + yleft;        
          dxy = rdel*sqrt2/sqrt3;        
          yright = .5*sqrt2*p*(1.- 1./sqrt3);        
          xright = sqrt2*p - yright - dxy;        
          yright = -yright - dxy;        
          dxy = 0.;        
          if ( (.5*sqrt3*160.-ddn)<p && p <=(.5*sqrt3*160.+ddup) )        
          {           
                xcenter = .5*(sqrt3*160.+1.846);           
                ycenter = xcenter - .5*sqrt3*1.713;           
                if ( p>ycenter )           
                {              
                      dxy = .5*sqrt2*(2/sqrt3*rdel + .5*sqrt3*1.846 + sqrt(1.713*1.713 - (p-xcenter)*(p-xcenter)));              
                }           
                else           
                {              
                      dxy = sqrt2/sqrt3*(p - .5*sqrt3* 160. + ddn);              
                }           
          }        
          else if ( (.5*sqrt3*195.-ddn)<p && p <=(.5*sqrt3*195.+ddup) )        
          {           
                xcenter = .5*(sqrt3*195.+1.846);           
                ycenter = xcenter - .5*sqrt3*1.713;           
                if ( p>ycenter )           
                {              
                      dxy = .5*sqrt2*(2/sqrt3*rdel + .5*sqrt3*1.846 + sqrt(1.713*1.713 - (p-xcenter)*(p-xcenter)));              
                }           
                else           
                {              
                      dxy = sqrt2/sqrt3*(p - .5*sqrt3*195. + ddn);              
                }           
          }        
          xright = xright + dxy;        
          yright = yright + dxy;        
    }     
    dxy     =  section*tan_theta_max - rtop;     
    xcenter = .5*(xright+xleft) + dxy;     
    ycenter = .5*(yright+yleft);     
    xx = .5*sqrt2*(xleft+yleft);     
    yy = .5*sqrt2*(xright+yright);     
    length = xx-yy;     
    return;     
 } // subroutine ecal_get_strip  
 // ----------------------------------------------------------------------- geoctr
    void EcalGeo6::ConstructGeometry( const Char_t *dummy )  
    {     
          ///@addtogroup EcalGeo6_revision     
          ///@{        
                /// Created:    11/13/2009         
          ///@}     
          ///@addtogroup EcalGeo6_revision     
          ///@{        
                /// Author: Jason Webb, Hal Spinka, Ilya Selyuzhenkov, Alice Bridgeman, Keith Krueger, Michael Betancourt        
          ///@}     
          AddBlock("EAGA");     
          AddBlock("EALP");     
          AddBlock("ECAL");     
          AddBlock("ECHC");     
          AddBlock("ECVO");     
          AddBlock("ECGH");     
          AddBlock("EFLP");     
          AddBlock("EHMS");     
          AddBlock("ELED");     
          AddBlock("EMGT");     
          AddBlock("EMOD");     
          AddBlock("EPER");     
          AddBlock("EPSB");     
          AddBlock("ERAD");     
          AddBlock("ERCM");     
          AddBlock("ERSM");     
          AddBlock("ESHM");     
          AddBlock("ESEC");     
          AddBlock("ESCI");     
          AddBlock("ESPL");     
          AddBlock("ESSP");     
          AddBlock("EMSS");     
          AddBlock("ETAR");     
          AddBlock("EXSG");     
          AddBlock("EXPS");     
          AddBlock("EFLS");     
          AddBlock("EBLS");     
          n=12;     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup emcg_doc     
          ///@{        
                ++emcg._index;        
                emcg . version = 6.1; //  Geometry version          
                /// emcg . version = 6.1; //  Geometry version          
                emcg . onoff = 3; //  Configurations 0-no, 1-west 2-east 3-both         
                /// emcg . onoff = 3; //  Configurations 0-no, 1-west 2-east 3-both         
                emcg . fillmode = 3; //  sectors fill mode          
                /// emcg . fillmode = 3; //  sectors fill mode          
                //        
                emcg.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup emcs_doc     
          ///@{        
                ++emcs._index;        
                emcs . version = 1; //  Versioning         
                /// emcs . version = 1; //  Versioning         
                emcs . type = 1; //  =1 endcap, =2 fpd edcap prototype         
                /// emcs . type = 1; //  =1 endcap, =2 fpd edcap prototype         
                emcs . zorg = 268.763; //  calorimeter origin in z         
                /// emcs . zorg = 268.763; //  calorimeter origin in z         
                emcs . zend = 310.007; //  Calorimeter end in z         
                /// emcs . zend = 310.007; //  Calorimeter end in z         
                emcs . etamin = 1.086; //  upper feducial eta cut          
                /// emcs . etamin = 1.086; //  upper feducial eta cut          
                emcs . etamax = 2.000; //  lower fiducial eta cut          
                /// emcs . etamax = 2.000; //  lower fiducial eta cut          
                emcs . phimin = -90; //  Min phi          
                /// emcs . phimin = -90; //  Min phi          
                emcs . phimax = 90; //  Max phi         
                /// emcs . phimax = 90; //  Max phi         
                emcs . offset = 0.0; //  offset in x         
                /// emcs . offset = 0.0; //  offset in x         
                emcs . nsupsec = 6; //  Number of azimuthal supersectors                 
                /// emcs . nsupsec = 6; //  Number of azimuthal supersectors                 
                emcs . nsector = 30; //  Number of azimutal sectors (Phi granularity)         
                /// emcs . nsector = 30; //  Number of azimutal sectors (Phi granularity)         
                emcs . nslices = 5; //  number of phi slices in supersector         
                /// emcs . nslices = 5; //  number of phi slices in supersector         
                emcs . nsection = 4; //  Number of readout sections         
                /// emcs . nsection = 4; //  Number of readout sections         
                emcs . front = 0.953; //  thickness of the front AL plates         
                /// emcs . front = 0.953; //  thickness of the front AL plates         
                emcs . alincell = 0.02; //  Aluminim plate in cell         
                /// emcs . alincell = 0.02; //  Aluminim plate in cell         
                emcs . frplast = 0.015; //  Front plastic in megatile         
                /// emcs . frplast = 0.015; //  Front plastic in megatile         
                emcs . bkplast = 0.155; //  Fiber routing guides and back plastic         
                /// emcs . bkplast = 0.155; //  Fiber routing guides and back plastic         
                emcs . pbplate = 0.457; //  Lead radiator thickness         
                /// emcs . pbplate = 0.457; //  Lead radiator thickness         
                emcs . lamplate = 0.05; //  Laminated SS plate thickness         
                /// emcs . lamplate = 0.05; //  Laminated SS plate thickness         
                emcs . bckplate = 3.175; //  Back SS plate thickness         
                /// emcs . bckplate = 3.175; //  Back SS plate thickness         
                emcs . hub = 3.81; //  thickness of EndCap hub         
                /// emcs . hub = 3.81; //  thickness of EndCap hub         
                emcs . rmshift = 2.121; //  radial shift of module         
                /// emcs . rmshift = 2.121; //  radial shift of module         
                emcs . smshift = 0.12; //  radial shift of steel support walls         
                /// emcs . smshift = 0.12; //  radial shift of steel support walls         
                emcs . gapplt = 0.3/2; //  HALF of the inter-plate gap in phi         
                /// emcs . gapplt = 0.3/2; //  HALF of the inter-plate gap in phi         
                emcs . gapcel = 0.03/2; //  HALF of the radial inter-cell gap         
                /// emcs . gapcel = 0.03/2; //  HALF of the radial inter-cell gap         
                emcs . gapsmd = 3.400; //  space for SMD detector                << version 2 -- 3.600 >>         
                /// emcs . gapsmd = 3.400; //  space for SMD detector                << version 2 -- 3.600 >>         
                emcs . smdcentr = 279.542; //  SMD position         
                /// emcs . smdcentr = 279.542; //  SMD position         
                emcs . tierod.at(0) = 160.; //  Radial position of tie rods         
                ///emcs . tierod.at(0) = 160.; //  Radial position of tie rods         
                emcs . tierod.at(1) = 195; //  Radial position of tie rods         
                ///emcs . tierod.at(1) = 195; //  Radial position of tie rods         
                emcs . bckfrnt = 306.832; //  Backplate front Z         
                /// emcs . bckfrnt = 306.832; //  Backplate front Z         
                emcs . gaphalf = 0.4; //  1/2 Gap between halves of endcap wheel         
                /// emcs . gaphalf = 0.4; //  1/2 Gap between halves of endcap wheel         
                emcs . cover = 0.075; //  Cover of wheel half         
                /// emcs . cover = 0.075; //  Cover of wheel half         
                emcs . rtie = 1.0425; //  Radius of tie rod         
                /// emcs . rtie = 1.0425; //  Radius of tie rod         
                emcs . slop = 0.1400; //  Added to cell containing radiator 6 (formerly hardcoded in geom)         
                /// emcs . slop = 0.1400; //  Added to cell containing radiator 6 (formerly hardcoded in geom)         
                //        
                emcs.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup emcs_doc     
          ///@{        
                ++emcs._index;        
                emcs . version = 2; //  Versioning         
                /// emcs . version = 2; //  Versioning         
                emcs . type = 1; //  =1 endcap, =2 fpd edcap prototype         
                /// emcs . type = 1; //  =1 endcap, =2 fpd edcap prototype         
                emcs . zorg = 268.763; //  calorimeter origin in z         
                /// emcs . zorg = 268.763; //  calorimeter origin in z         
                emcs . zend = 310.007; //  Calorimeter end in z         
                /// emcs . zend = 310.007; //  Calorimeter end in z         
                emcs . etamin = 1.086; //  upper feducial eta cut          
                /// emcs . etamin = 1.086; //  upper feducial eta cut          
                emcs . etamax = 2.000; //  lower fiducial eta cut          
                /// emcs . etamax = 2.000; //  lower fiducial eta cut          
                emcs . phimin = -90; //  Min phi          
                /// emcs . phimin = -90; //  Min phi          
                emcs . phimax = 90; //  Max phi         
                /// emcs . phimax = 90; //  Max phi         
                emcs . offset = 0.0; //  offset in x         
                /// emcs . offset = 0.0; //  offset in x         
                emcs . nsupsec = 6; //  Number of azimuthal supersectors                 
                /// emcs . nsupsec = 6; //  Number of azimuthal supersectors                 
                emcs . nsector = 30; //  Number of azimutal sectors (Phi granularity)         
                /// emcs . nsector = 30; //  Number of azimutal sectors (Phi granularity)         
                emcs . nslices = 5; //  number of phi slices in supersector         
                /// emcs . nslices = 5; //  number of phi slices in supersector         
                emcs . nsection = 4; //  Number of readout sections         
                /// emcs . nsection = 4; //  Number of readout sections         
                emcs . front = 0.953; //  thickness of the front AL plates         
                /// emcs . front = 0.953; //  thickness of the front AL plates         
                emcs . alincell = 0.02; //  Aluminim plate in cell         
                /// emcs . alincell = 0.02; //  Aluminim plate in cell         
                emcs . frplast = 0.015; //  Front plastic in megatile         
                /// emcs . frplast = 0.015; //  Front plastic in megatile         
                emcs . bkplast = 0.155; //  Fiber routing guides and back plastic         
                /// emcs . bkplast = 0.155; //  Fiber routing guides and back plastic         
                emcs . pbplate = 0.457; //  Lead radiator thickness         
                /// emcs . pbplate = 0.457; //  Lead radiator thickness         
                emcs . lamplate = 0.05; //  Laminated SS plate thickness         
                /// emcs . lamplate = 0.05; //  Laminated SS plate thickness         
                emcs . bckplate = 3.175; //  Back SS plate thickness         
                /// emcs . bckplate = 3.175; //  Back SS plate thickness         
                emcs . hub = 3.81; //  thickness of EndCap hub         
                /// emcs . hub = 3.81; //  thickness of EndCap hub         
                emcs . rmshift = 2.121; //  radial shift of module         
                /// emcs . rmshift = 2.121; //  radial shift of module         
                emcs . smshift = 0.12; //  radial shift of steel support walls         
                /// emcs . smshift = 0.12; //  radial shift of steel support walls         
                emcs . gapplt = 0.3/2; //  HALF of the inter-plate gap in phi         
                /// emcs . gapplt = 0.3/2; //  HALF of the inter-plate gap in phi         
                emcs . gapcel = 0.03/2; //  HALF of the radial inter-cell gap         
                /// emcs . gapcel = 0.03/2; //  HALF of the radial inter-cell gap         
                emcs . gapsmd = 3.600; //  space for SMD detector              (* from master_geom_bmp.xls *)         
                /// emcs . gapsmd = 3.600; //  space for SMD detector              (* from master_geom_bmp.xls *)         
                emcs . smdcentr = 279.542; //  SMD position         
                /// emcs . smdcentr = 279.542; //  SMD position         
                emcs . tierod.at(0) = 160.; //  Radial position of tie rods         
                ///emcs . tierod.at(0) = 160.; //  Radial position of tie rods         
                emcs . tierod.at(1) = 195; //  Radial position of tie rods         
                ///emcs . tierod.at(1) = 195; //  Radial position of tie rods         
                emcs . bckfrnt = 306.832; //  Backplate front Z         
                /// emcs . bckfrnt = 306.832; //  Backplate front Z         
                emcs . gaphalf = 0.4; //  1/2 Gap between halves of endcap wheel         
                /// emcs . gaphalf = 0.4; //  1/2 Gap between halves of endcap wheel         
                emcs . cover = 0.075; //  Cover of wheel half         
                /// emcs . cover = 0.075; //  Cover of wheel half         
                emcs . rtie = 0.75; //  Radius of tie rod         
                /// emcs . rtie = 0.75; //  Radius of tie rod         
                emcs . slop = 0.0000; //  Added to cell containing radiator 6 (formerly hardcoded in geom)         
                /// emcs . slop = 0.0000; //  Added to cell containing radiator 6 (formerly hardcoded in geom)         
                //        
                emcs.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esmd_doc     
          ///@{        
                ++esmd._index;        
                esmd . version = 1; //  versioning information         
                /// esmd . version = 1; //  versioning information         
                esmd . front_layer = 0.161; //  thickness of front layer          
                /// esmd . front_layer = 0.161; //  thickness of front layer          
                esmd . back_layer = 0.210; //  thickness of back layer         
                /// esmd . back_layer = 0.210; //  thickness of back layer         
                esmd . base = 1.0; //  base of the SMD strip         
                /// esmd . base = 1.0; //  base of the SMD strip         
                esmd . apex = 0.7; //  apex of the SMD strip         
                /// esmd . apex = 0.7; //  apex of the SMD strip         
                esmd . spacer_layer = 1.2; //  spacer layer         
                /// esmd . spacer_layer = 1.2; //  spacer layer         
                //        
                esmd.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup eetr_doc     
          ///@{        
                ++eetr._index;        
                eetr . type = 1; //  =1 endcap, =2 fpd         
                /// eetr . type = 1; //  =1 endcap, =2 fpd         
                eetr . etagr = 1.0536; //  eta_top/eta_bot tower granularity         
                /// eetr . etagr = 1.0536; //  eta_top/eta_bot tower granularity         
                eetr . phigr = 0.0981747; //  Phi granularity (radians)         
                /// eetr . phigr = 0.0981747; //  Phi granularity (radians)         
                eetr . neta = 12; //  Eta granularity         
                /// eetr . neta = 12; //  Eta granularity         
                eetr . etabin.at(0) = 2.0; //  Eta rapidities         
                ///eetr . etabin.at(0) = 2.0; //  Eta rapidities         
                eetr . etabin.at(1) = 1.9008; //  Eta rapidities         
                ///eetr . etabin.at(1) = 1.9008; //  Eta rapidities         
                eetr . etabin.at(2) = 1.8065; //  Eta rapidities         
                ///eetr . etabin.at(2) = 1.8065; //  Eta rapidities         
                eetr . etabin.at(3) = 1.7168; //  Eta rapidities         
                ///eetr . etabin.at(3) = 1.7168; //  Eta rapidities         
                eetr . etabin.at(4) = 1.6317; //  Eta rapidities         
                ///eetr . etabin.at(4) = 1.6317; //  Eta rapidities         
                eetr . etabin.at(5) = 1.5507; //  Eta rapidities         
                ///eetr . etabin.at(5) = 1.5507; //  Eta rapidities         
                eetr . etabin.at(6) = 1.4738; //  Eta rapidities         
                ///eetr . etabin.at(6) = 1.4738; //  Eta rapidities         
                eetr . etabin.at(7) = 1.4007; //  Eta rapidities         
                ///eetr . etabin.at(7) = 1.4007; //  Eta rapidities         
                eetr . etabin.at(8) = 1.3312; //  Eta rapidities         
                ///eetr . etabin.at(8) = 1.3312; //  Eta rapidities         
                eetr . etabin.at(9) = 1.2651; //  Eta rapidities         
                ///eetr . etabin.at(9) = 1.2651; //  Eta rapidities         
                eetr . etabin.at(10) = 1.2023; //  Eta rapidities         
                ///eetr . etabin.at(10) = 1.2023; //  Eta rapidities         
                eetr . etabin.at(11) = 1.1427; //  Eta rapidities         
                ///eetr . etabin.at(11) = 1.1427; //  Eta rapidities         
                eetr . etabin.at(12) = 1.086; //  Eta rapidities         
                ///eetr . etabin.at(12) = 1.086; //  Eta rapidities         
                //        
                eetr.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esec_doc     
          ///@{        
                ++esec._index;        
                esec . isect = 1; //  Section number            
                /// esec . isect = 1; //  Section number            
                esec . nlayer = 1; //  Number of Sci layers along z         
                /// esec . nlayer = 1; //  Number of Sci layers along z         
                esec . cell = 1.505; //  Cell full width in z         
                /// esec . cell = 1.505; //  Cell full width in z         
                esec . scint = 0.475; //  Sci layer thickness (4.75mm Bicron)         
                /// esec . scint = 0.475; //  Sci layer thickness (4.75mm Bicron)         
                esec . deltaz = -0.014; //  Amount to shift section in z to align with as-built numbers         
                /// esec . deltaz = -0.014; //  Amount to shift section in z to align with as-built numbers         
                esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                //        
                esec.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esec_doc     
          ///@{        
                ++esec._index;        
                esec . isect = 2; //  Section number            
                /// esec . isect = 2; //  Section number            
                esec . nlayer = 1; //  Number of Sci layers along z         
                /// esec . nlayer = 1; //  Number of Sci layers along z         
                esec . cell = 1.505; //  Cell full width in z         
                /// esec . cell = 1.505; //  Cell full width in z         
                esec . scint = 0.475; //  Sci layer thickness (4.75mm Bicron)         
                /// esec . scint = 0.475; //  Sci layer thickness (4.75mm Bicron)         
                esec . deltaz = -0.0182; //  Amount to shift section in z to align with as-built numbers         
                /// esec . deltaz = -0.0182; //  Amount to shift section in z to align with as-built numbers         
                esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                //        
                esec.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esec_doc     
          ///@{        
                ++esec._index;        
                esec . isect = 3; //  Section number         
                /// esec . isect = 3; //  Section number         
                esec . nlayer = 4; //  Number of Sci layers along z         
                /// esec . nlayer = 4; //  Number of Sci layers along z         
                esec . cell = 1.405; //  Cell full width in z         
                /// esec . cell = 1.405; //  Cell full width in z         
                esec . scint = 0.4; //  Sci layer thickness         
                /// esec . scint = 0.4; //  Sci layer thickness         
                esec . deltaz = -0.0145; //  Amount to shift section in z to align with as-built numbers         
                /// esec . deltaz = -0.0145; //  Amount to shift section in z to align with as-built numbers         
                esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                //        
                esec.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esec_doc     
          ///@{        
                ++esec._index;        
                esec . isect = 4; //  Section         
                /// esec . isect = 4; //  Section         
                esec . nlayer = 18; //  Number of layers along z         
                /// esec . nlayer = 18; //  Number of layers along z         
                esec . cell = 1.405; //  Cell full width in z         
                /// esec . cell = 1.405; //  Cell full width in z         
                esec . scint = 0.4; //  Sci layer thickness         
                /// esec . scint = 0.4; //  Sci layer thickness         
                esec . deltaz = +0.0336; //  Amount to shift section in z to align with as-built numbers         
                /// esec . deltaz = +0.0336; //  Amount to shift section in z to align with as-built numbers         
                esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                //        
                esec.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esec_doc     
          ///@{        
                ++esec._index;        
                esec . isect = 5; //  Section         
                /// esec . isect = 5; //  Section         
                esec . nlayer = 1; //  Number of  layers along z         
                /// esec . nlayer = 1; //  Number of  layers along z         
                esec . cell = 1.505; //  Cell full width in z         
                /// esec . cell = 1.505; //  Cell full width in z         
                esec . scint = 0.5; //  Sci layer thickness (5.0mm Kurarary)         
                /// esec . scint = 0.5; //  Sci layer thickness (5.0mm Kurarary)         
                esec . deltaz = +0.036; //  Amount to shift section in z to align with as-built numbers         
                /// esec . deltaz = +0.036; //  Amount to shift section in z to align with as-built numbers         
                esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(0) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(1) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(2) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(3) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(4) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(5) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(6) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(7) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(8) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(9) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(10) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(11) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(12) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(13) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(14) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(15) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(16) = 0; //  Degrees to shift EPER in each layer         
                esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                ///esec . jiggle.at(17) = 0; //  Degrees to shift EPER in each layer         
                //        
                esec.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup emxg_doc     
          ///@{        
                ++emxg._index;        
                emxg . version = 1; //  Geometry version         
                /// emxg . version = 1; //  Geometry version         
                emxg . sapex = 0.7; //  Scintillator strip apex         
                /// emxg . sapex = 0.7; //  Scintillator strip apex         
                emxg . sbase = 1.0; //  Scintillator strip base         
                /// emxg . sbase = 1.0; //  Scintillator strip base         
                emxg . rin = 77.41; //  inner radius of SMD plane           
                /// emxg . rin = 77.41; //  inner radius of SMD plane           
                emxg . rout = 213.922; //  outer radius of SMD plane         
                /// emxg . rout = 213.922; //  outer radius of SMD plane         
                emxg . f4 = .15; //  F4 thickness         
                /// emxg . f4 = .15; //  F4 thickness         
                //        
                emxg.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup exse_doc     
          ///@{        
                ++exse._index;        
                exse . jsect = 1; //  Section number         
                /// exse . jsect = 1; //  Section number         
                exse . zshift = -1.215; //  Section width         
                /// exse . zshift = -1.215; //  Section width         
                exse . sectype.at(0) = 4; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(0) = 4; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(1) = 1; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(1) = 1; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(2) = 0; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(2) = 0; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(3) = 2; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(3) = 2; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(4) = 1; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(4) = 1; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(5) = 0; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(5) = 0; //  1-V,2-U,3-cutV,4-cutU             
                //        
                exse.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup exse_doc     
          ///@{        
                ++exse._index;        
                exse . jsect = 2; //  Section number            
                /// exse . jsect = 2; //  Section number            
                exse . zshift = 0.; //  Section width         
                /// exse . zshift = 0.; //  Section width         
                exse . sectype.at(0) = 0; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(0) = 0; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(1) = 2; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(1) = 2; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(2) = 1; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(2) = 1; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(3) = 0; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(3) = 0; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(4) = 2; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(4) = 2; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(5) = 3; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(5) = 3; //  1-V,2-U,3-cutV,4-cutU             
                //        
                exse.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup exse_doc     
          ///@{        
                ++exse._index;        
                exse . jsect = 3; //  Section number            
                /// exse . jsect = 3; //  Section number            
                exse . zshift = 1.215; //  Section width         
                /// exse . zshift = 1.215; //  Section width         
                exse . sectype.at(0) = 1; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(0) = 1; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(1) = 0; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(1) = 0; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(2) = 2; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(2) = 2; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(3) = 1; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(3) = 1; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(4) = 0; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(4) = 0; //  1-V,2-U,3-cutV,4-cutU             
                exse . sectype.at(5) = 2; //  1-V,2-U,3-cutV,4-cutU             
                ///exse . sectype.at(5) = 2; //  1-V,2-U,3-cutV,4-cutU             
                //        
                exse.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup ecut_doc     
          ///@{        
                ++ecut._index;        
                ecut . version = 1; //  selector         
                /// ecut . version = 1; //  selector         
                ecut . absorber = 0; //  absorber cuts         
                /// ecut . absorber = 0; //  absorber cuts         
                ecut . sensitive = 0; //  sensitive cuts         
                /// ecut . sensitive = 0; //  sensitive cuts         
                ecut . blah = 1; //  meh         
                /// ecut . blah = 1; //  meh         
                //        
                ecut.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup eabs_doc     
          ///@{        
                ++eabs._index;        
                eabs . version = 0; //  versioning         
                /// eabs . version = 0; //  versioning         
                eabs . cutgam = 80 *1.0e-6; //  gamma transport cut         
                /// eabs . cutgam = 80 *1.0e-6; //  gamma transport cut         
                eabs . cutele = 1 *0.001; //  electron transport cut         
                /// eabs . cutele = 1 *0.001; //  electron transport cut         
                eabs . cuthad = 1 *0.001; //  hadron transport cut         
                /// eabs . cuthad = 1 *0.001; //  hadron transport cut         
                eabs . cutneu = 1 *0.001; //  neutron transport cut         
                /// eabs . cutneu = 1 *0.001; //  neutron transport cut         
                eabs . cutmuo = 1 *0.001; //  muon transport cut         
                /// eabs . cutmuo = 1 *0.001; //  muon transport cut         
                eabs . dcute = 1 *0.001; //  electron delta ray cut         
                /// eabs . dcute = 1 *0.001; //  electron delta ray cut         
                eabs . dcutm = 1 *0.001; //  muon delta ray cut         
                /// eabs . dcutm = 1 *0.001; //  muon delta ray cut         
                eabs . bcute = 100 *1.0e-6; //  electron brem cut         
                /// eabs . bcute = 100 *1.0e-6; //  electron brem cut         
                eabs . bcutm = 1 *0.001; //  muon brem cut              
                /// eabs . bcutm = 1 *0.001; //  muon brem cut              
                //        
                eabs.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup eabs_doc     
          ///@{        
                ++eabs._index;        
                eabs . version = 1; //  versioning         
                /// eabs . version = 1; //  versioning         
                eabs . cutgam = 10 *1.0e-6; //  gamma transport cut         
                /// eabs . cutgam = 10 *1.0e-6; //  gamma transport cut         
                eabs . cutele = 10 *1.0e-6; //  electron transport cut         
                /// eabs . cutele = 10 *1.0e-6; //  electron transport cut         
                eabs . cuthad = 1 *0.001; //  hadron transport cut         
                /// eabs . cuthad = 1 *0.001; //  hadron transport cut         
                eabs . cutneu = 1 *0.001; //  neutron transport cut         
                /// eabs . cutneu = 1 *0.001; //  neutron transport cut         
                eabs . cutmuo = 1 *0.001; //  muon transport cut         
                /// eabs . cutmuo = 1 *0.001; //  muon transport cut         
                eabs . dcute = 10 *1.0e-6; //  electron delta ray cut         
                /// eabs . dcute = 10 *1.0e-6; //  electron delta ray cut         
                eabs . dcutm = 10 *1.0e-6; //  muon delta ray cut         
                /// eabs . dcutm = 10 *1.0e-6; //  muon delta ray cut         
                eabs . bcute = 10 *1.0e-6; //  electron brem cut         
                /// eabs . bcute = 10 *1.0e-6; //  electron brem cut         
                eabs . bcutm = 10 *1.0e-6; //  muon brem cut         
                /// eabs . bcutm = 10 *1.0e-6; //  muon brem cut         
                //        
                eabs.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup eabs_doc     
          ///@{        
                ++eabs._index;        
                eabs . version = 2; //  versioning         
                /// eabs . version = 2; //  versioning         
                eabs . cutgam = 30 *1.0e-6; //  gamma transport cut         
                /// eabs . cutgam = 30 *1.0e-6; //  gamma transport cut         
                eabs . cutele = 30 *1.0e-6; //  electron transport cut         
                /// eabs . cutele = 30 *1.0e-6; //  electron transport cut         
                eabs . cuthad = 1 *0.001; //  hadron transport cut         
                /// eabs . cuthad = 1 *0.001; //  hadron transport cut         
                eabs . cutneu = 1 *0.001; //  neutron transport cut         
                /// eabs . cutneu = 1 *0.001; //  neutron transport cut         
                eabs . cutmuo = 1 *0.001; //  muon transport cut         
                /// eabs . cutmuo = 1 *0.001; //  muon transport cut         
                eabs . dcute = 30 *1.0e-6; //  electron delta ray cut         
                /// eabs . dcute = 30 *1.0e-6; //  electron delta ray cut         
                eabs . dcutm = 30 *1.0e-6; //  muon delta ray cut         
                /// eabs . dcutm = 30 *1.0e-6; //  muon delta ray cut         
                eabs . bcute = 30 *1.0e-6; //  electron brem cut         
                /// eabs . bcute = 30 *1.0e-6; //  electron brem cut         
                eabs . bcutm = 30 *1.0e-6; //  muon brem cut         
                /// eabs . bcutm = 30 *1.0e-6; //  muon brem cut         
                //        
                eabs.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup eabs_doc     
          ///@{        
                ++eabs._index;        
                eabs . version = 3; //  versioning         
                /// eabs . version = 3; //  versioning         
                eabs . cutgam = 100 *1.0e-6; //  gamma transport cut         
                /// eabs . cutgam = 100 *1.0e-6; //  gamma transport cut         
                eabs . cutele = 100 *1.0e-6; //  electron transport cut         
                /// eabs . cutele = 100 *1.0e-6; //  electron transport cut         
                eabs . cuthad = 1 *0.001; //  hadron transport cut         
                /// eabs . cuthad = 1 *0.001; //  hadron transport cut         
                eabs . cutneu = 1 *0.001; //  neutron transport cut         
                /// eabs . cutneu = 1 *0.001; //  neutron transport cut         
                eabs . cutmuo = 1 *0.001; //  muon transport cut         
                /// eabs . cutmuo = 1 *0.001; //  muon transport cut         
                eabs . dcute = 100 *1.0e-6; //  electron delta ray cut         
                /// eabs . dcute = 100 *1.0e-6; //  electron delta ray cut         
                eabs . dcutm = 100 *1.0e-6; //  muon delta ray cut         
                /// eabs . dcutm = 100 *1.0e-6; //  muon delta ray cut         
                eabs . bcute = 100 *1.0e-6; //  electron brem cut         
                /// eabs . bcute = 100 *1.0e-6; //  electron brem cut         
                eabs . bcutm = 100 *1.0e-6; //  muon brem cut         
                /// eabs . bcutm = 100 *1.0e-6; //  muon brem cut         
                //        
                eabs.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup eabs_doc     
          ///@{        
                ++eabs._index;        
                eabs . version = 4; //  versioning         
                /// eabs . version = 4; //  versioning         
                eabs . cutgam = 1 *0.001; //  gamma transport cut         
                /// eabs . cutgam = 1 *0.001; //  gamma transport cut         
                eabs . cutele = 1 *0.001; //  electron transport cut         
                /// eabs . cutele = 1 *0.001; //  electron transport cut         
                eabs . cuthad = 1 *0.001; //  hadron transport cut         
                /// eabs . cuthad = 1 *0.001; //  hadron transport cut         
                eabs . cutneu = 1 *0.001; //  neutron transport cut         
                /// eabs . cutneu = 1 *0.001; //  neutron transport cut         
                eabs . cutmuo = 1 *0.001; //  muon transport cut         
                /// eabs . cutmuo = 1 *0.001; //  muon transport cut         
                eabs . dcute = 1 *0.001; //  electron delta ray cut         
                /// eabs . dcute = 1 *0.001; //  electron delta ray cut         
                eabs . dcutm = 1 *0.001; //  muon delta ray cut         
                /// eabs . dcutm = 1 *0.001; //  muon delta ray cut         
                eabs . bcute = 1 *0.001; //  electron brem cut         
                /// eabs . bcute = 1 *0.001; //  electron brem cut         
                eabs . bcutm = 1 *0.001; //  muon brem cut         
                /// eabs . bcutm = 1 *0.001; //  muon brem cut         
                //        
                eabs.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esen_doc     
          ///@{        
                ++esen._index;        
                esen . version = 0; //  versioning         
                /// esen . version = 0; //  versioning         
                esen . cutgam = 80 *1.0e-6; //  gamma transport cut         
                /// esen . cutgam = 80 *1.0e-6; //  gamma transport cut         
                esen . cutele = 1 *0.001; //  electron transport cut         
                /// esen . cutele = 1 *0.001; //  electron transport cut         
                esen . cuthad = 1 *0.001; //  hadron transport cut         
                /// esen . cuthad = 1 *0.001; //  hadron transport cut         
                esen . cutneu = 1 *0.001; //  neutron transport cut         
                /// esen . cutneu = 1 *0.001; //  neutron transport cut         
                esen . cutmuo = 1 *0.001; //  muon transport cut         
                /// esen . cutmuo = 1 *0.001; //  muon transport cut         
                esen . dcute = 1 *0.001; //  electron delta ray cut         
                /// esen . dcute = 1 *0.001; //  electron delta ray cut         
                esen . dcutm = 1 *0.001; //  muon delta ray cut         
                /// esen . dcutm = 1 *0.001; //  muon delta ray cut         
                esen . bcute = 100 *1.0e-6; //  electron brem cut         
                /// esen . bcute = 100 *1.0e-6; //  electron brem cut         
                esen . bcutm = 1 *0.001; //  muon brem cut              
                /// esen . bcutm = 1 *0.001; //  muon brem cut              
                //        
                esen.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esen_doc     
          ///@{        
                ++esen._index;        
                esen . version = 1; //  versioning         
                /// esen . version = 1; //  versioning         
                esen . cutgam = 10 *1.0e-6; //  gamma transport cut         
                /// esen . cutgam = 10 *1.0e-6; //  gamma transport cut         
                esen . cutele = 10 *1.0e-6; //  electron transport cut         
                /// esen . cutele = 10 *1.0e-6; //  electron transport cut         
                esen . cuthad = 1 *0.001; //  hadron transport cut         
                /// esen . cuthad = 1 *0.001; //  hadron transport cut         
                esen . cutneu = 1 *0.001; //  neutron transport cut         
                /// esen . cutneu = 1 *0.001; //  neutron transport cut         
                esen . cutmuo = 1 *0.001; //  muon transport cut         
                /// esen . cutmuo = 1 *0.001; //  muon transport cut         
                esen . dcute = 10 *1.0e-6; //  electron delta ray cut         
                /// esen . dcute = 10 *1.0e-6; //  electron delta ray cut         
                esen . dcutm = 10 *1.0e-6; //  muon delta ray cut         
                /// esen . dcutm = 10 *1.0e-6; //  muon delta ray cut         
                esen . bcute = 10 *1.0e-6; //  electron brem cut         
                /// esen . bcute = 10 *1.0e-6; //  electron brem cut         
                esen . bcutm = 10 *1.0e-6; //  muon brem cut         
                /// esen . bcutm = 10 *1.0e-6; //  muon brem cut         
                //        
                esen.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esen_doc     
          ///@{        
                ++esen._index;        
                esen . version = 2; //  versioning         
                /// esen . version = 2; //  versioning         
                esen . cutgam = 30 *1.0e-6; //  gamma transport cut         
                /// esen . cutgam = 30 *1.0e-6; //  gamma transport cut         
                esen . cutele = 30 *1.0e-6; //  electron transport cut         
                /// esen . cutele = 30 *1.0e-6; //  electron transport cut         
                esen . cuthad = 1 *0.001; //  hadron transport cut         
                /// esen . cuthad = 1 *0.001; //  hadron transport cut         
                esen . cutneu = 1 *0.001; //  neutron transport cut         
                /// esen . cutneu = 1 *0.001; //  neutron transport cut         
                esen . cutmuo = 1 *0.001; //  muon transport cut         
                /// esen . cutmuo = 1 *0.001; //  muon transport cut         
                esen . dcute = 30 *1.0e-6; //  electron delta ray cut         
                /// esen . dcute = 30 *1.0e-6; //  electron delta ray cut         
                esen . dcutm = 30 *1.0e-6; //  muon delta ray cut         
                /// esen . dcutm = 30 *1.0e-6; //  muon delta ray cut         
                esen . bcute = 30 *1.0e-6; //  electron brem cut         
                /// esen . bcute = 30 *1.0e-6; //  electron brem cut         
                esen . bcutm = 30 *1.0e-6; //  muon brem cut         
                /// esen . bcutm = 30 *1.0e-6; //  muon brem cut         
                //        
                esen.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esen_doc     
          ///@{        
                ++esen._index;        
                esen . version = 3; //  versioning         
                /// esen . version = 3; //  versioning         
                esen . cutgam = 100 *1.0e-6; //  gamma transport cut         
                /// esen . cutgam = 100 *1.0e-6; //  gamma transport cut         
                esen . cutele = 100 *1.0e-6; //  electron transport cut         
                /// esen . cutele = 100 *1.0e-6; //  electron transport cut         
                esen . cuthad = 1 *0.001; //  hadron transport cut         
                /// esen . cuthad = 1 *0.001; //  hadron transport cut         
                esen . cutneu = 1 *0.001; //  neutron transport cut         
                /// esen . cutneu = 1 *0.001; //  neutron transport cut         
                esen . cutmuo = 1 *0.001; //  muon transport cut         
                /// esen . cutmuo = 1 *0.001; //  muon transport cut         
                esen . dcute = 100 *1.0e-6; //  electron delta ray cut         
                /// esen . dcute = 100 *1.0e-6; //  electron delta ray cut         
                esen . dcutm = 100 *1.0e-6; //  muon delta ray cut         
                /// esen . dcutm = 100 *1.0e-6; //  muon delta ray cut         
                esen . bcute = 100 *1.0e-6; //  electron brem cut         
                /// esen . bcute = 100 *1.0e-6; //  electron brem cut         
                esen . bcutm = 100 *1.0e-6; //  muon brem cut         
                /// esen . bcutm = 100 *1.0e-6; //  muon brem cut         
                //        
                esen.fill();        
          ///@}     
          //     
          // ---------------------------------------------------------------------------------------------------     
          ///@addtogroup esen_doc     
          ///@{        
                ++esen._index;        
                esen . version = 4; //  versioning         
                /// esen . version = 4; //  versioning         
                esen . cutgam = 1 *0.001; //  gamma transport cut         
                /// esen . cutgam = 1 *0.001; //  gamma transport cut         
                esen . cutele = 1 *0.001; //  electron transport cut         
                /// esen . cutele = 1 *0.001; //  electron transport cut         
                esen . cuthad = 1 *0.001; //  hadron transport cut         
                /// esen . cuthad = 1 *0.001; //  hadron transport cut         
                esen . cutneu = 1 *0.001; //  neutron transport cut         
                /// esen . cutneu = 1 *0.001; //  neutron transport cut         
                esen . cutmuo = 1 *0.001; //  muon transport cut         
                /// esen . cutmuo = 1 *0.001; //  muon transport cut         
                esen . dcute = 1 *0.001; //  electron delta ray cut         
                /// esen . dcute = 1 *0.001; //  electron delta ray cut         
                esen . dcutm = 1 *0.001; //  muon delta ray cut         
                /// esen . dcutm = 1 *0.001; //  muon delta ray cut         
                esen . bcute = 1 *0.001; //  electron brem cut         
                /// esen . bcute = 1 *0.001; //  electron brem cut         
                esen . bcutm = 1 *0.001; //  muon brem cut         
                /// esen . bcutm = 1 *0.001; //  muon brem cut         
                //        
                esen.fill();        
          ///@}     
          //     
          /// USE emcg _index=1;     
          emcg.Use();     
          /// USE emcs version=2    ;     
          emcs.Use("version",(Float_t)2    );     
          /// USE eetr _index=1;     
          eetr.Use();     
          /// USE ecut version=1 ;     
          ecut.Use("version",(Float_t)1 );     
          /// USE eabs version=ecut.absorber ;     
          eabs.Use("version",(Float_t)ecut.absorber );     
          /// USE esen version=ecut.sensitive ;     
          esen.Use("version",(Float_t)ecut.sensitive );     
          sq3 = sqrt(3.)                                ;// 1/tan(30deg) = sq3;     
          sq2 = sqrt(2.);     
          center  = (emcs.zorg+emcs.zend)/2             ;// center of the calorimeter;     
          tan_upp = tanf(emcs.etamin)                   ;// think this is angle pointing to top of calo;     
          tan_low = tanf(emcs.etamax)                   ;// think this is angle pointing to bot of calo;     
          rth     = sqrt(1. + tan_low*tan_low)          ;// ??;     
          rshift  = emcs.hub * rth                      ;// ??;     
          dup     = emcs.rmshift*tan_upp                ;//;     
          dd      = emcs.rmshift*rth                    ;//;     
          d2      = rshift + dd                         ;//;     
          radiator  = emcs.pbplate + 2*emcs.lamplate    ;// thickness of radiator assembly;     
          dphi = (emcs.phimax-emcs.phimin)/emcs.nsector ;// single endcap sector;     
          // Print<level=%i> fmt=%s fortran format statements not supported     
          // Print<level=%i> fmt=%s fortran format statements not supported     
          // Print<level=%i> fmt=%s fortran format statements not supported     
          if ( emcg.onoff>0 )     
          {        
                _create = AgCreate("ECAL");        
                {           
                      AgShape myshape; // undefined shape           
                      ///Create ECAL           
                      Create("ECAL");            
                }        
                if ( emcg.onoff==1||emcg.onoff==3 )        
                {           
                      { AgPlacement place = AgPlacement("ECAL","CAVE");              
                            /// Add daughter volume ECAL to mother CAVE              
                            place.TranslateZ(+center);              
                            /// Translate z = +center              
                            _stacker -> Position( AgBlock::Find("ECAL"), place );              
                      } // end placement of ECAL           
                }        
                if ( section>emcs.zend )        
                {           
                      // Print<level=%i> fmt=%s fortran format statements not supported           
                }        
                if ( emcg.onoff==2||emcg.onoff==3 )        
                {           
                      { AgPlacement place = AgPlacement("ECAL","CAVE");              
                            /// Add daughter volume ECAL to mother CAVE              
                            place.TranslateZ(-center);              
                            /// Translate z = -center              
                            /// G3 Reference: thetax = 90              
                            /// G3 Reference: phix = 0              
                            /// G3 Reference: thetay = 90              
                            /// G3 Reference: phiy = 90              
                            /// G3 Reference: thetaz = 180              
                            /// G3 Reference: phiz = 0              
                            Double_t _thetax=90,_phix=0,_thetay=90,_phiy=90,_thetaz=180,_phiz=0;              
                            place.Reference( _thetax, _phix, _thetay, _phiy, _thetaz, _phiz );              
                            _stacker -> Position( AgBlock::Find("ECAL"), place );              
                      } // end placement of ECAL           
                }        
          }     
          // Print<level=%i> fmt=%s fortran format statements not supported     
    }; // EcalGeo6  
 }; // namespace EcalGeo6  
 