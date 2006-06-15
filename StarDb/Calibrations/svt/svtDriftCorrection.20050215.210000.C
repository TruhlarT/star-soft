// #include <string.h>
// #include "Riostream.h"
// #include "TTable.h"
// #include "tables/St_svtCorrection_Table.h"
TDataSet *CreateTable() { 
// -----------------------------------------------------------------
// db/.const/StarDb/Calibrations/svt/.svtDriftCorrection/svtDriftCorrection Allocated rows: 432  Used rows: 432  Row size: 248 bytes
//  Table: svtCorrection_st[0]--> svtCorrection_st[431]
// ====================================================================
// ------  Test whether this table share library was loaded ------
  if (!gROOT->GetClass("St_svtCorrection")) return 0;
  svtCorrection_st row;
  St_svtCorrection *tableSet = new St_svtCorrection("svtDriftCorrection",432);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =          1; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00617; // ;
    row.param[1]	 =   -0.00933;
    row.param[2]	 =   -0.00202;
    row.param[3]	 =   -0.00388;
    row.param[4]	 =   -0.00077;
    row.param[5]	 =   -0.00436;
    row.param[6]	 =   -0.00556;
    row.param[7]	 =   -0.00464;
    row.param[8]	 =   -0.00314;
    row.param[9]	 =   -0.00297;
    row.param[10]	 =   -0.00233;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008832893; // ;
    row.dparam[1]	 = 0.001738275;
    row.dparam[2]	 = 0.001625238;
    row.dparam[3]	 = 0.001569235;
    row.dparam[4]	 = 0.001408048;
    row.dparam[5]	 = 0.001296919;
    row.dparam[6]	 =    0.00104;
    row.dparam[7]	 =    0.00099;
    row.dparam[8]	 =    0.00076;
    row.dparam[9]	 =    0.00069;
    row.dparam[10]	 =    0.00047;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP2101",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =          2; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01583; // ;
    row.param[1]	 =    0.02269;
    row.param[2]	 =    0.04173;
    row.param[3]	 =    0.03834;
    row.param[4]	 =    0.03983;
    row.param[5]	 =     0.0319;
    row.param[6]	 =    0.02864;
    row.param[7]	 =    0.02184;
    row.param[8]	 =    0.01651;
    row.param[9]	 =    0.01181;
    row.param[10]	 =    0.00537;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001298075; // ;
    row.dparam[1]	 = 0.002624881;
    row.dparam[2]	 = 0.002415802;
    row.dparam[3]	 = 0.002365164;
    row.dparam[4]	 = 0.00209122;
    row.dparam[5]	 =    0.00193;
    row.dparam[6]	 =    0.00161;
    row.dparam[7]	 =    0.00148;
    row.dparam[8]	 =    0.00112;
    row.dparam[9]	 =    0.00103;
    row.dparam[10]	 =    0.00065;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP2101",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =          3; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =    -0.0241; // ;
    row.param[1]	 =    0.01188;
    row.param[2]	 =      0.007;
    row.param[3]	 =    0.00179;
    row.param[4]	 =    0.00288;
    row.param[5]	 =     0.0034;
    row.param[6]	 =      7e-05;
    row.param[7]	 =    0.00072;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005239275; // ;
    row.dparam[1]	 = 0.0009087354;
    row.dparam[2]	 =    0.00088;
    row.dparam[3]	 =    0.00074;
    row.dparam[4]	 =    0.00077;
    row.dparam[5]	 =     0.0006;
    row.dparam[6]	 =     0.0006;
    row.dparam[7]	 =    0.00043;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP2201",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =          4; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03685; // ;
    row.param[1]	 =    0.05647;
    row.param[2]	 =    0.03519;
    row.param[3]	 =    0.02596;
    row.param[4]	 =    0.04969;
    row.param[5]	 =    0.02655;
    row.param[6]	 =     0.0381;
    row.param[7]	 =    0.02017;
    row.param[8]	 =    0.01946;
    row.param[9]	 =    0.00623;
    row.param[10]	 =    0.01491;
    row.param[11]	 =   -0.00068;
    row.dparam[0]	 = 0.001793042; // ;
    row.dparam[1]	 = 0.003726137;
    row.dparam[2]	 = 0.003264966;
    row.dparam[3]	 = 0.003387093;
    row.dparam[4]	 = 0.002895566;
    row.dparam[5]	 = 0.002891505;
    row.dparam[6]	 = 0.002437478;
    row.dparam[7]	 = 0.002395099;
    row.dparam[8]	 = 0.001839402;
    row.dparam[9]	 = 0.001959719;
    row.dparam[10]	 = 0.001154903;
    row.dparam[11]	 =    0.00068;
 memcpy(&row.Comment,"duuP2201",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =          5; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00828; // ;
    row.param[1]	 =    0.01638;
    row.param[2]	 =    0.00655;
    row.param[3]	 =    0.01108;
    row.param[4]	 =    0.00129;
    row.param[5]	 =    0.00661;
    row.param[6]	 =    0.00028;
    row.param[7]	 =    0.00525;
    row.param[8]	 =    -0.0013;
    row.param[9]	 =    0.00238;
    row.param[10]	 =    0.00123;
    row.param[11]	 =    0.00021;
    row.dparam[0]	 = 0.001183765; // ;
    row.dparam[1]	 = 0.002495155;
    row.dparam[2]	 = 0.002234748;
    row.dparam[3]	 = 0.002287007;
    row.dparam[4]	 = 0.001957422;
    row.dparam[5]	 = 0.001957882;
    row.dparam[6]	 = 0.00157623;
    row.dparam[7]	 = 0.001553673;
    row.dparam[8]	 = 0.001143241;
    row.dparam[9]	 = 0.001091467;
    row.dparam[10]	 = 0.0007044147;
    row.dparam[11]	 =    0.00039;
 memcpy(&row.Comment,"duuP2301",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =          6; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.07592; // ;
    row.param[1]	 =    0.04106;
    row.param[2]	 =    0.03355;
    row.param[3]	 =    0.02971;
    row.param[4]	 =    0.02929;
    row.param[5]	 =    0.01998;
    row.param[6]	 =    0.02624;
    row.param[7]	 =    0.00965;
    row.param[8]	 =    0.01561;
    row.param[9]	 =    0.00146;
    row.param[10]	 =    0.00632;
    row.param[11]	 =   -0.00288;
    row.dparam[0]	 = 0.001800722; // ;
    row.dparam[1]	 = 0.003718145;
    row.dparam[2]	 = 0.00336061;
    row.dparam[3]	 = 0.003311722;
    row.dparam[4]	 = 0.002824907;
    row.dparam[5]	 = 0.002696108;
    row.dparam[6]	 = 0.002118891;
    row.dparam[7]	 = 0.001912302;
    row.dparam[8]	 = 0.00138398;
    row.dparam[9]	 = 0.001252078;
    row.dparam[10]	 = 0.000766942;
    row.dparam[11]	 =    0.00049;
 memcpy(&row.Comment,"duuP2301",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =          7; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00788; // ;
    row.param[1]	 =   -0.01388;
    row.param[2]	 =    0.00407;
    row.param[3]	 =   -0.00428;
    row.param[4]	 =    0.00096;
    row.param[5]	 =    -0.0021;
    row.param[6]	 =   -0.00209;
    row.param[7]	 =   -0.00184;
    row.param[8]	 =   -0.00186;
    row.param[9]	 =   -0.00018;
    row.param[10]	 =   -0.00104;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006648308; // ;
    row.dparam[1]	 = 0.001335215;
    row.dparam[2]	 = 0.001230163;
    row.dparam[3]	 = 0.001215113;
    row.dparam[4]	 =  0.0010728;
    row.dparam[5]	 =    0.00102;
    row.dparam[6]	 =    0.00085;
    row.dparam[7]	 =    0.00082;
    row.dparam[8]	 =    0.00062;
    row.dparam[9]	 =    0.00058;
    row.dparam[10]	 =    0.00039;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP2401",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =          8; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     0.0053; // ;
    row.param[1]	 =    0.00347;
    row.param[2]	 =     0.0005;
    row.param[3]	 =   -0.00332;
    row.param[4]	 =    -0.0009;
    row.param[5]	 =   -0.00029;
    row.param[6]	 =    0.00162;
    row.param[7]	 =     -9e-05;
    row.param[8]	 =    0.00065;
    row.param[9]	 =   -0.00061;
    row.param[10]	 =   -0.00041;
    row.param[11]	 =   -0.00047;
    row.dparam[0]	 = 0.0009814785; // ;
    row.dparam[1]	 = 0.001890529;
    row.dparam[2]	 = 0.001830546;
    row.dparam[3]	 = 0.001727686;
    row.dparam[4]	 = 0.001625238;
    row.dparam[5]	 = 0.001477498;
    row.dparam[6]	 = 0.001345808;
    row.dparam[7]	 = 0.001166919;
    row.dparam[8]	 = 0.001013657;
    row.dparam[9]	 = 0.0008223746;
    row.dparam[10]	 =    0.00041;
    row.dparam[11]	 =    0.00039;
 memcpy(&row.Comment,"duuP2401",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =          9; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00708; // ;
    row.param[1]	 =   -0.02173;
    row.param[2]	 =    0.00343;
    row.param[3]	 =   -0.00417;
    row.param[4]	 =   -0.00334;
    row.param[5]	 =   -0.00632;
    row.param[6]	 =    -0.0023;
    row.param[7]	 =   -0.00763;
    row.param[8]	 =   -0.00562;
    row.param[9]	 =   -0.00496;
    row.param[10]	 =    -0.0021;
    row.param[11]	 =   -0.00058;
    row.dparam[0]	 = 0.001092932; // ;
    row.dparam[1]	 = 0.002255039;
    row.dparam[2]	 = 0.002058786;
    row.dparam[3]	 = 0.002064098;
    row.dparam[4]	 = 0.001815324;
    row.dparam[5]	 = 0.001780169;
    row.dparam[6]	 = 0.001456228;
    row.dparam[7]	 = 0.001409752;
    row.dparam[8]	 = 0.001103223;
    row.dparam[9]	 = 0.001028105;
    row.dparam[10]	 = 0.0007275988;
    row.dparam[11]	 =    0.00042;
 memcpy(&row.Comment,"duuP1102",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         10; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    0.02048; // ;
    row.param[1]	 =    0.01066;
    row.param[2]	 =   -0.00346;
    row.param[3]	 =   -0.00537;
    row.param[4]	 =   -0.00064;
    row.param[5]	 =    0.00039;
    row.param[6]	 =    0.00326;
    row.param[7]	 =   -0.00088;
    row.param[8]	 =    0.00346;
    row.param[9]	 =    0.00133;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007156116; // ;
    row.dparam[1]	 = 0.001331353;
    row.dparam[2]	 = 0.001313697;
    row.dparam[3]	 = 0.00123422;
    row.dparam[4]	 = 0.001173371;
    row.dparam[5]	 = 0.001031746;
    row.dparam[6]	 = 0.0009529428;
    row.dparam[7]	 = 0.0008077747;
    row.dparam[8]	 =    0.00065;
    row.dparam[9]	 =    0.00048;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1102",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         11; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          5; // ;
    row.param[0]	 =   -0.01226; // ;
    row.param[1]	 =   -0.01842;
    row.param[2]	 =    0.00525;
    row.param[3]	 =    0.00445;
    row.param[4]	 =    0.00282;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.000256125; // ;
    row.dparam[1]	 = 0.0004580393;
    row.dparam[2]	 =    0.00033;
    row.dparam[3]	 =    0.00033;
    row.dparam[4]	 =    0.00028;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1202",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         12; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01705; // ;
    row.param[1]	 =    0.02023;
    row.param[2]	 =   -0.00427;
    row.param[3]	 =   -0.00711;
    row.param[4]	 =   -0.00045;
    row.param[5]	 =    0.00331;
    row.param[6]	 =    0.00285;
    row.param[7]	 =    0.00399;
    row.param[8]	 =    0.00286;
    row.param[9]	 =    0.00426;
    row.param[10]	 =    0.00276;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009183681; // ;
    row.dparam[1]	 = 0.001810497;
    row.dparam[2]	 = 0.001705784;
    row.dparam[3]	 = 0.001648666;
    row.dparam[4]	 = 0.001490637;
    row.dparam[5]	 = 0.001409007;
    row.dparam[6]	 = 0.001163615;
    row.dparam[7]	 = 0.001051903;
    row.dparam[8]	 =    0.00076;
    row.dparam[9]	 =    0.00069;
    row.dparam[10]	 =    0.00049;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1202",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         13; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.03705; // ;
    row.param[1]	 =   -0.01858;
    row.param[2]	 =   -0.01572;
    row.param[3]	 =   -0.01313;
    row.param[4]	 =   -0.00974;
    row.param[5]	 =   -0.01162;
    row.param[6]	 =   -0.00944;
    row.param[7]	 =    -0.0064;
    row.param[8]	 =   -0.00775;
    row.param[9]	 =    0.00012;
    row.param[10]	 =   -0.00548;
    row.param[11]	 =    0.00145;
    row.dparam[0]	 = 0.001818186; // ;
    row.dparam[1]	 = 0.003734555;
    row.dparam[2]	 = 0.003445475;
    row.dparam[3]	 = 0.00340912;
    row.dparam[4]	 = 0.002992741;
    row.dparam[5]	 = 0.002909381;
    row.dparam[6]	 = 0.002365692;
    row.dparam[7]	 = 0.002219775;
    row.dparam[8]	 = 0.001745337;
    row.dparam[9]	 = 0.001547966;
    row.dparam[10]	 = 0.001074151;
    row.dparam[11]	 =    0.00059;
 memcpy(&row.Comment,"duuP2103",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         14; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01608; // ;
    row.param[1]	 =   -0.00363;
    row.param[2]	 =    0.01553;
    row.param[3]	 =    0.01368;
    row.param[4]	 =    0.01344;
    row.param[5]	 =    0.00806;
    row.param[6]	 =    0.01114;
    row.param[7]	 =      0.004;
    row.param[8]	 =    0.00529;
    row.param[9]	 =    0.00171;
    row.param[10]	 =    0.00114;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009219544; // ;
    row.dparam[1]	 =    0.00185;
    row.dparam[2]	 =     0.0017;
    row.dparam[3]	 =    0.00169;
    row.dparam[4]	 =    0.00147;
    row.dparam[5]	 =    0.00142;
    row.dparam[6]	 =    0.00116;
    row.dparam[7]	 =    0.00109;
    row.dparam[8]	 =    0.00082;
    row.dparam[9]	 =    0.00074;
    row.dparam[10]	 =    0.00048;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP2103",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         15; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.03573; // ;
    row.param[1]	 =   -0.00907;
    row.param[2]	 =   -0.02008;
    row.param[3]	 =   -0.00827;
    row.param[4]	 =   -0.01222;
    row.param[5]	 =   -0.00803;
    row.param[6]	 =   -0.01096;
    row.param[7]	 =   -0.00751;
    row.param[8]	 =   -0.00755;
    row.param[9]	 =   -0.00378;
    row.param[10]	 =   -0.00369;
    row.param[11]	 =    0.00136;
    row.dparam[0]	 = 0.001622929; // ;
    row.dparam[1]	 = 0.003332582;
    row.dparam[2]	 = 0.003061144;
    row.dparam[3]	 = 0.003049229;
    row.dparam[4]	 = 0.002668295;
    row.dparam[5]	 = 0.002592778;
    row.dparam[6]	 = 0.002136633;
    row.dparam[7]	 = 0.001997849;
    row.dparam[8]	 = 0.001582214;
    row.dparam[9]	 = 0.001414532;
    row.dparam[10]	 = 0.000987269;
    row.dparam[11]	 =    0.00055;
 memcpy(&row.Comment,"duuP2203",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         16; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          3; // ;
    row.param[0]	 =    0.01725; // ;
    row.param[1]	 =   -0.01276;
    row.param[2]	 =   -0.00304;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008044874; // ;
    row.dparam[1]	 = 0.001290736;
    row.dparam[2]	 =    0.00082;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP2203",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         17; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.0104; // ;
    row.param[1]	 =    0.01848;
    row.param[2]	 =   -0.00771;
    row.param[3]	 =    0.00239;
    row.param[4]	 =   -0.00707;
    row.param[5]	 =    -0.0001;
    row.param[6]	 =   -0.00523;
    row.param[7]	 =    0.00043;
    row.param[8]	 =    -0.0036;
    row.param[9]	 =   -0.00071;
    row.param[10]	 =    0.00039;
    row.param[11]	 =    0.00034;
    row.dparam[0]	 = 0.0009948367; // ;
    row.dparam[1]	 = 0.001903076;
    row.dparam[2]	 = 0.001822581;
    row.dparam[3]	 = 0.001753169;
    row.dparam[4]	 = 0.001622652;
    row.dparam[5]	 = 0.001500467;
    row.dparam[6]	 = 0.001316549;
    row.dparam[7]	 = 0.001175968;
    row.dparam[8]	 = 0.0009885848;
    row.dparam[9]	 = 0.0008321658;
    row.dparam[10]	 =    0.00049;
    row.dparam[11]	 =    0.00045;
 memcpy(&row.Comment,"duuP1104",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         18; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.0524; // ;
    row.param[1]	 =    0.03667;
    row.param[2]	 =    0.02909;
    row.param[3]	 =     0.0395;
    row.param[4]	 =    0.03015;
    row.param[5]	 =    0.02873;
    row.param[6]	 =    0.02607;
    row.param[7]	 =    0.01863;
    row.param[8]	 =    0.01443;
    row.param[9]	 =    0.00985;
    row.param[10]	 =    0.00606;
    row.param[11]	 =   -0.00044;
    row.dparam[0]	 = 0.00146564; // ;
    row.dparam[1]	 = 0.003005878;
    row.dparam[2]	 = 0.002760326;
    row.dparam[3]	 = 0.002719136;
    row.dparam[4]	 = 0.00236398;
    row.dparam[5]	 = 0.002265348;
    row.dparam[6]	 = 0.001828797;
    row.dparam[7]	 = 0.001701558;
    row.dparam[8]	 = 0.001258809;
    row.dparam[9]	 = 0.001131238;
    row.dparam[10]	 = 0.0007401351;
    row.dparam[11]	 =     0.0004;
 memcpy(&row.Comment,"duuP1104",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         19; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =     0.0584; // ;
    row.param[1]	 =    0.04674;
    row.param[2]	 =    0.00597;
    row.param[3]	 =    0.01347;
    row.param[4]	 =    0.00139;
    row.param[5]	 =    0.00245;
    row.param[6]	 =    0.00222;
    row.param[7]	 =    0.00114;
    row.param[8]	 =   -0.00089;
    row.param[9]	 =   -0.00234;
    row.param[10]	 =   -0.00236;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.002429691; // ;
    row.dparam[1]	 = 0.004735652;
    row.dparam[2]	 = 0.004551593;
    row.dparam[3]	 = 0.003846297;
    row.dparam[4]	 = 0.003510627;
    row.dparam[5]	 = 0.002782373;
    row.dparam[6]	 = 0.00222036;
    row.dparam[7]	 = 0.001671077;
    row.dparam[8]	 =    0.00098;
    row.dparam[9]	 =    0.00084;
    row.dparam[10]	 =    0.00077;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1204",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         20; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01415; // ;
    row.param[1]	 =   -0.00433;
    row.param[2]	 =    0.02198;
    row.param[3]	 =    0.02173;
    row.param[4]	 =    0.01903;
    row.param[5]	 =    0.02361;
    row.param[6]	 =    0.01758;
    row.param[7]	 =    0.01666;
    row.param[8]	 =    0.00849;
    row.param[9]	 =    0.00761;
    row.param[10]	 =     0.0028;
    row.param[11]	 =   -0.00104;
    row.dparam[0]	 = 0.001753938; // ;
    row.dparam[1]	 = 0.003700568;
    row.dparam[2]	 = 0.003433278;
    row.dparam[3]	 = 0.003257376;
    row.dparam[4]	 = 0.002917687;
    row.dparam[5]	 = 0.002888183;
    row.dparam[6]	 = 0.002212465;
    row.dparam[7]	 = 0.002141798;
    row.dparam[8]	 = 0.001709181;
    row.dparam[9]	 = 0.001440937;
    row.dparam[10]	 = 0.001039904;
    row.dparam[11]	 =    0.00063;
 memcpy(&row.Comment,"duuP1204",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         21; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01712; // ;
    row.param[1]	 =   -0.00513;
    row.param[2]	 =   -0.00453;
    row.param[3]	 =    0.00357;
    row.param[4]	 =     -9e-05;
    row.param[5]	 =   -0.00238;
    row.param[6]	 =   -0.00367;
    row.param[7]	 =   -0.00224;
    row.param[8]	 =   -0.00369;
    row.param[9]	 =   -0.00266;
    row.param[10]	 =   -0.00318;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009630161; // ;
    row.dparam[1]	 = 0.001863277;
    row.dparam[2]	 = 0.001781853;
    row.dparam[3]	 = 0.001716304;
    row.dparam[4]	 = 0.001600062;
    row.dparam[5]	 = 0.001467856;
    row.dparam[6]	 = 0.001252517;
    row.dparam[7]	 = 0.001115034;
    row.dparam[8]	 = 0.0009308598;
    row.dparam[9]	 = 0.0007877182;
    row.dparam[10]	 = 0.00060959;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1304",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         22; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00415; // ;
    row.param[1]	 =    0.01619;
    row.param[2]	 =    0.00298;
    row.param[3]	 =    0.01001;
    row.param[4]	 =    0.00389;
    row.param[5]	 =    0.01002;
    row.param[6]	 =    0.00707;
    row.param[7]	 =    0.00825;
    row.param[8]	 =    0.00612;
    row.param[9]	 =    0.00516;
    row.param[10]	 =    0.00269;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007247068; // ;
    row.dparam[1]	 = 0.001440868;
    row.dparam[2]	 = 0.001346143;
    row.dparam[3]	 = 0.00130679;
    row.dparam[4]	 = 0.00118072;
    row.dparam[5]	 = 0.001101681;
    row.dparam[6]	 = 0.0009347727;
    row.dparam[7]	 = 0.0008523497;
    row.dparam[8]	 = 0.0006664833;
    row.dparam[9]	 =    0.00054;
    row.dparam[10]	 =    0.00037;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1304",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         23; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01812; // ;
    row.param[1]	 =   -0.02678;
    row.param[2]	 =    0.00778;
    row.param[3]	 =    -0.0001;
    row.param[4]	 =    0.00532;
    row.param[5]	 =   -0.00179;
    row.param[6]	 =    0.00157;
    row.param[7]	 =    0.00215;
    row.param[8]	 =   -0.00173;
    row.param[9]	 =    0.00027;
    row.param[10]	 =   -0.00189;
    row.param[11]	 =    0.00062;
    row.dparam[0]	 = 0.001190126; // ;
    row.dparam[1]	 =  0.0024668;
    row.dparam[2]	 = 0.002253042;
    row.dparam[3]	 = 0.002270352;
    row.dparam[4]	 = 0.001993414;
    row.dparam[5]	 = 0.001946715;
    row.dparam[6]	 = 0.001617344;
    row.dparam[7]	 = 0.001530392;
    row.dparam[8]	 = 0.001189706;
    row.dparam[9]	 = 0.001114495;
    row.dparam[10]	 = 0.0007679193;
    row.dparam[11]	 =    0.00041;
 memcpy(&row.Comment,"duuP1404",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         24; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     0.0312; // ;
    row.param[1]	 =    0.01342;
    row.param[2]	 =    -0.0025;
    row.param[3]	 =   -0.00694;
    row.param[4]	 =   -0.00228;
    row.param[5]	 =   -0.00506;
    row.param[6]	 =    0.00191;
    row.param[7]	 =   -0.00276;
    row.param[8]	 =    0.00208;
    row.param[9]	 =   -0.00107;
    row.param[10]	 =    0.00134;
    row.param[11]	 =   -0.00039;
    row.dparam[0]	 = 0.001238144; // ;
    row.dparam[1]	 = 0.002544602;
    row.dparam[2]	 = 0.002337135;
    row.dparam[3]	 = 0.002347722;
    row.dparam[4]	 = 0.002052973;
    row.dparam[5]	 = 0.00200035;
    row.dparam[6]	 = 0.001647817;
    row.dparam[7]	 = 0.001588805;
    row.dparam[8]	 = 0.00119021;
    row.dparam[9]	 = 0.001114675;
    row.dparam[10]	 = 0.0007449161;
    row.dparam[11]	 =    0.00041;
 memcpy(&row.Comment,"duuP1404",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         25; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.04151; // ;
    row.param[1]	 =   -0.01763;
    row.param[2]	 =    0.00712;
    row.param[3]	 =    0.00767;
    row.param[4]	 =    0.00217;
    row.param[5]	 =     0.0028;
    row.param[6]	 =    0.00138;
    row.param[7]	 =     0.0002;
    row.param[8]	 =   -0.00224;
    row.param[9]	 =   -0.00134;
    row.param[10]	 =    0.00158;
    row.param[11]	 =   -0.00114;
    row.dparam[0]	 = 0.0009767292; // ;
    row.dparam[1]	 = 0.002024105;
    row.dparam[2]	 = 0.001861317;
    row.dparam[3]	 = 0.001875447;
    row.dparam[4]	 = 0.001648787;
    row.dparam[5]	 = 0.001599062;
    row.dparam[6]	 = 0.001344173;
    row.dparam[7]	 = 0.001280352;
    row.dparam[8]	 = 0.0009972462;
    row.dparam[9]	 = 0.0009265528;
    row.dparam[10]	 = 0.0006293648;
    row.dparam[11]	 =    0.00041;
 memcpy(&row.Comment,"duuP2305",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         26; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00765; // ;
    row.param[1]	 =     0.0125;
    row.param[2]	 =   -0.01101;
    row.param[3]	 =    0.00079;
    row.param[4]	 =   -0.00359;
    row.param[5]	 =   -0.00065;
    row.param[6]	 =   -0.00366;
    row.param[7]	 =   -0.00634;
    row.param[8]	 =   -0.00694;
    row.param[9]	 =   -0.00842;
    row.param[10]	 =    -0.0041;
    row.param[11]	 =   -0.00041;
    row.dparam[0]	 = 0.001392013; // ;
    row.dparam[1]	 = 0.002864716;
    row.dparam[2]	 = 0.002645184;
    row.dparam[3]	 = 0.002656614;
    row.dparam[4]	 = 0.00232708;
    row.dparam[5]	 = 0.002269295;
    row.dparam[6]	 = 0.001893779;
    row.dparam[7]	 = 0.00178986;
    row.dparam[8]	 = 0.001362571;
    row.dparam[9]	 = 0.00125865;
    row.dparam[10]	 = 0.0008313844;
    row.dparam[11]	 =    0.00046;
 memcpy(&row.Comment,"duuP2305",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         27; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03055; // ;
    row.param[1]	 =   -0.03933;
    row.param[2]	 =    0.00598;
    row.param[3]	 =    0.00414;
    row.param[4]	 =     0.0047;
    row.param[5]	 =    0.00236;
    row.param[6]	 =    0.00145;
    row.param[7]	 =    0.00384;
    row.param[8]	 =     0.0001;
    row.param[9]	 =    0.00241;
    row.param[10]	 =   -0.00048;
    row.param[11]	 =    0.00074;
    row.dparam[0]	 = 0.00123588; // ;
    row.dparam[1]	 = 0.002587161;
    row.dparam[2]	 = 0.00234444;
    row.dparam[3]	 = 0.002384974;
    row.dparam[4]	 = 0.002078798;
    row.dparam[5]	 = 0.002067365;
    row.dparam[6]	 = 0.001703438;
    row.dparam[7]	 = 0.001657136;
    row.dparam[8]	 = 0.001264476;
    row.dparam[9]	 = 0.001200916;
    row.dparam[10]	 = 0.0007852388;
    row.dparam[11]	 =    0.00043;
 memcpy(&row.Comment,"duuP2405",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         28; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01648; // ;
    row.param[1]	 =    0.02458;
    row.param[2]	 =   -0.00148;
    row.param[3]	 =   -0.00984;
    row.param[4]	 =   -0.00113;
    row.param[5]	 =   -0.00722;
    row.param[6]	 =    0.00137;
    row.param[7]	 =   -0.00766;
    row.param[8]	 =    -0.0003;
    row.param[9]	 =    -0.0033;
    row.param[10]	 =   -0.00057;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006977105; // ;
    row.dparam[1]	 = 0.001444507;
    row.dparam[2]	 = 0.001288099;
    row.dparam[3]	 = 0.001314838;
    row.dparam[4]	 = 0.001132166;
    row.dparam[5]	 = 0.001123076;
    row.dparam[6]	 =    0.00091;
    row.dparam[7]	 = 0.0008876936;
    row.dparam[8]	 =    0.00062;
    row.dparam[9]	 =    0.00059;
    row.dparam[10]	 =    0.00039;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP2405",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         29; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.06282; // ;
    row.param[1]	 =   -0.01176;
    row.param[2]	 =    0.00953;
    row.param[3]	 =    0.00168;
    row.param[4]	 =    0.00213;
    row.param[5]	 =   -0.00052;
    row.param[6]	 =    0.00041;
    row.param[7]	 =   -0.00105;
    row.param[8]	 =    -0.0012;
    row.param[9]	 =   -0.00109;
    row.param[10]	 =   -0.00242;
    row.param[11]	 =   -0.00048;
    row.dparam[0]	 = 0.0008927486; // ;
    row.dparam[1]	 = 0.001841955;
    row.dparam[2]	 = 0.00169331;
    row.dparam[3]	 = 0.001692483;
    row.dparam[4]	 = 0.001494021;
    row.dparam[5]	 = 0.001450965;
    row.dparam[6]	 = 0.00120283;
    row.dparam[7]	 = 0.001131724;
    row.dparam[8]	 = 0.000884138;
    row.dparam[9]	 = 0.0008062258;
    row.dparam[10]	 = 0.0005586591;
    row.dparam[11]	 =    0.00037;
 memcpy(&row.Comment,"duuP1106",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         30; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =   -0.01772; // ;
    row.param[1]	 =     0.0152;
    row.param[2]	 =   -0.00236;
    row.param[3]	 =    0.00453;
    row.param[4]	 =     -6e-05;
    row.param[5]	 =    0.00533;
    row.param[6]	 =    0.00288;
    row.param[7]	 =    0.00229;
    row.param[8]	 =    0.00122;
    row.param[9]	 =    0.00102;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =  0.0004998; // ;
    row.dparam[1]	 = 0.0009044335;
    row.dparam[2]	 =    0.00088;
    row.dparam[3]	 =    0.00079;
    row.dparam[4]	 =    0.00078;
    row.dparam[5]	 =    0.00066;
    row.dparam[6]	 =    0.00065;
    row.dparam[7]	 =    0.00053;
    row.dparam[8]	 =     0.0005;
    row.dparam[9]	 =    0.00036;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1106",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         31; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =   -0.05012; // ;
    row.param[1]	 =   -0.01847;
    row.param[2]	 =      8e-05;
    row.param[3]	 =    0.00369;
    row.param[4]	 =    0.00255;
    row.param[5]	 =   -0.00055;
    row.param[6]	 =   -0.00068;
    row.param[7]	 =   -0.00119;
    row.param[8]	 =   -0.00118;
    row.param[9]	 =   -0.00165;
    row.param[10]	 =    -0.0011;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005366563; // ;
    row.dparam[1]	 = 0.0009972963;
    row.dparam[2]	 = 0.0009848858;
    row.dparam[3]	 = 0.0009124144;
    row.dparam[4]	 = 0.0008856636;
    row.dparam[5]	 = 0.0007702597;
    row.dparam[6]	 = 0.0007068239;
    row.dparam[7]	 =    0.00052;
    row.dparam[8]	 =    0.00048;
    row.dparam[9]	 =    0.00035;
    row.dparam[10]	 =    0.00032;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1206",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         32; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01762; // ;
    row.param[1]	 =    0.01014;
    row.param[2]	 =   -0.00502;
    row.param[3]	 =   -0.00025;
    row.param[4]	 =   -0.00162;
    row.param[5]	 =    0.00375;
    row.param[6]	 =    0.00018;
    row.param[7]	 =      3e-05;
    row.param[8]	 =    0.00023;
    row.param[9]	 =   -0.00174;
    row.param[10]	 =   -0.00021;
    row.param[11]	 =   -0.00155;
    row.dparam[0]	 = 0.0006935416; // ;
    row.dparam[1]	 = 0.001454373;
    row.dparam[2]	 = 0.001306484;
    row.dparam[3]	 = 0.001301768;
    row.dparam[4]	 = 0.001204159;
    row.dparam[5]	 = 0.001114136;
    row.dparam[6]	 = 0.0009518929;
    row.dparam[7]	 = 0.0008883693;
    row.dparam[8]	 = 0.0006760178;
    row.dparam[9]	 =    0.00054;
    row.dparam[10]	 =    0.00038;
    row.dparam[11]	 =    0.00034;
 memcpy(&row.Comment,"duuP1206",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         33; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     -0.034; // ;
    row.param[1]	 =   -0.00687;
    row.param[2]	 =    0.00133;
    row.param[3]	 =    0.00043;
    row.param[4]	 =   -0.00107;
    row.param[5]	 =     0.0011;
    row.param[6]	 =   -0.00394;
    row.param[7]	 =    0.00169;
    row.param[8]	 =   -0.00393;
    row.param[9]	 =   -0.00287;
    row.param[10]	 =   -0.00209;
    row.param[11]	 =    -0.0005;
    row.dparam[0]	 = 0.001084896; // ;
    row.dparam[1]	 = 0.002181834;
    row.dparam[2]	 = 0.002028324;
    row.dparam[3]	 = 0.002011691;
    row.dparam[4]	 = 0.00179438;
    row.dparam[5]	 = 0.001717964;
    row.dparam[6]	 = 0.001447066;
    row.dparam[7]	 = 0.001335253;
    row.dparam[8]	 = 0.001011187;
    row.dparam[9]	 = 0.0009263369;
    row.dparam[10]	 = 0.0006293648;
    row.dparam[11]	 =    0.00042;
 memcpy(&row.Comment,"duuP1306",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         34; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =   -0.01936; // ;
    row.param[1]	 =    0.02072;
    row.param[2]	 =   -0.00359;
    row.param[3]	 =    0.00709;
    row.param[4]	 =   -0.00077;
    row.param[5]	 =    0.00709;
    row.param[6]	 =    0.00249;
    row.param[7]	 =     0.0022;
    row.param[8]	 =    0.00142;
    row.param[9]	 =    0.00173;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005147815; // ;
    row.dparam[1]	 = 0.0009082401;
    row.dparam[2]	 = 0.0009394147;
    row.dparam[3]	 = 0.0008407735;
    row.dparam[4]	 = 0.0008407735;
    row.dparam[5]	 = 0.0006977822;
    row.dparam[6]	 = 0.0006844706;
    row.dparam[7]	 =     0.0005;
    row.dparam[8]	 =    0.00048;
    row.dparam[9]	 =    0.00035;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1306",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         35; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =    -0.0459; // ;
    row.param[1]	 =   -0.00199;
    row.param[2]	 =    0.00281;
    row.param[3]	 =    -0.0024;
    row.param[4]	 =    0.00351;
    row.param[5]	 =   -0.00395;
    row.param[6]	 =   -0.00114;
    row.param[7]	 =   -0.00152;
    row.param[8]	 =    0.00064;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0003996248; // ;
    row.dparam[1]	 = 0.0007692204;
    row.dparam[2]	 = 0.0007071068;
    row.dparam[3]	 = 0.00069857;
    row.dparam[4]	 = 0.0006126989;
    row.dparam[5]	 =    0.00054;
    row.dparam[6]	 =    0.00046;
    row.dparam[7]	 =    0.00044;
    row.dparam[8]	 =    0.00032;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1406",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         36; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    -0.0113; // ;
    row.param[1]	 =    0.01059;
    row.param[2]	 =   -0.00317;
    row.param[3]	 =     0.0047;
    row.param[4]	 =   -0.00189;
    row.param[5]	 =    0.00437;
    row.param[6]	 =    0.00254;
    row.param[7]	 =     0.0022;
    row.param[8]	 =    0.00155;
    row.param[9]	 =     0.0015;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0004459821; // ;
    row.dparam[1]	 = 0.0008221922;
    row.dparam[2]	 =    0.00079;
    row.dparam[3]	 =    0.00071;
    row.dparam[4]	 =    0.00071;
    row.dparam[5]	 =     0.0006;
    row.dparam[6]	 =    0.00058;
    row.dparam[7]	 =    0.00048;
    row.dparam[8]	 =    0.00045;
    row.dparam[9]	 =    0.00034;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP1406",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         37; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00596; // ;
    row.param[1]	 =   -0.01696;
    row.param[2]	 =   -0.00282;
    row.param[3]	 =   -0.00594;
    row.param[4]	 =    0.00252;
    row.param[5]	 =   -0.00021;
    row.param[6]	 =    0.00185;
    row.param[7]	 =    0.00189;
    row.param[8]	 =    0.00158;
    row.param[9]	 =    0.00105;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007640026; // ;
    row.dparam[1]	 = 0.001569522;
    row.dparam[2]	 =    0.00141;
    row.dparam[3]	 =    0.00141;
    row.dparam[4]	 =    0.00126;
    row.dparam[5]	 =    0.00123;
    row.dparam[6]	 =    0.00103;
    row.dparam[7]	 =    0.00098;
    row.dparam[8]	 =    0.00076;
    row.dparam[9]	 =     0.0007;
    row.dparam[10]	 =    0.00047;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP2307",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         38; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.03715; // ;
    row.param[1]	 =    0.00272;
    row.param[2]	 =    0.00299;
    row.param[3]	 =    0.00751;
    row.param[4]	 =   -0.00586;
    row.param[5]	 =    0.00535;
    row.param[6]	 =    -0.0006;
    row.param[7]	 =   -0.00146;
    row.param[8]	 =    0.00089;
    row.param[9]	 =   -0.00075;
    row.param[10]	 =   -0.00069;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007527284; // ;
    row.dparam[1]	 = 0.00151921;
    row.dparam[2]	 = 0.001410886;
    row.dparam[3]	 = 0.001389748;
    row.dparam[4]	 = 0.001237619;
    row.dparam[5]	 =    0.00116;
    row.dparam[6]	 =    0.00097;
    row.dparam[7]	 =    0.00092;
    row.dparam[8]	 =    0.00072;
    row.dparam[9]	 =    0.00067;
    row.dparam[10]	 =    0.00045;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP2307",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         39; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     0.0489; // ;
    row.param[1]	 =     -0.054;
    row.param[2]	 =   -0.00148;
    row.param[3]	 =    -0.0069;
    row.param[4]	 =    0.00103;
    row.param[5]	 =    0.00375;
    row.param[6]	 =   -0.00457;
    row.param[7]	 =    0.00501;
    row.param[8]	 =    0.00243;
    row.param[9]	 =    0.00221;
    row.param[10]	 =    0.00102;
    row.param[11]	 =    0.00067;
    row.dparam[0]	 = 0.001046518; // ;
    row.dparam[1]	 = 0.002170829;
    row.dparam[2]	 = 0.001972841;
    row.dparam[3]	 = 0.002008233;
    row.dparam[4]	 = 0.001760824;
    row.dparam[5]	 = 0.001739713;
    row.dparam[6]	 =    0.00145;
    row.dparam[7]	 = 0.001386218;
    row.dparam[8]	 = 0.001075174;
    row.dparam[9]	 = 0.001004191;
    row.dparam[10]	 = 0.0006717887;
    row.dparam[11]	 =    0.00045;
 memcpy(&row.Comment,"duuP2407",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          2; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          1; // ;
    row.layer	 =          1; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         40; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.0165; // ;
    row.param[1]	 =    0.03561;
    row.param[2]	 =    0.02368;
    row.param[3]	 =    0.00246;
    row.param[4]	 =   -0.00763;
    row.param[5]	 =    0.00426;
    row.param[6]	 =    0.00309;
    row.param[7]	 =    0.00784;
    row.param[8]	 =   -0.00278;
    row.param[9]	 =    0.00188;
    row.param[10]	 =    0.00091;
    row.param[11]	 =    0.00143;
    row.dparam[0]	 = 0.001459246; // ;
    row.dparam[1]	 = 0.003010017;
    row.dparam[2]	 = 0.002744777;
    row.dparam[3]	 = 0.002788942;
    row.dparam[4]	 = 0.002429691;
    row.dparam[5]	 = 0.002398896;
    row.dparam[6]	 = 0.001953356;
    row.dparam[7]	 = 0.001877259;
    row.dparam[8]	 = 0.001414956;
    row.dparam[9]	 = 0.001322309;
    row.dparam[10]	 = 0.0009237965;
    row.dparam[11]	 =     0.0005;
 memcpy(&row.Comment,"duuP4101",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         41; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =   -0.00205; // ;
    row.param[1]	 =   -0.00684;
    row.param[2]	 =   -0.01334;
    row.param[3]	 =   -0.00769;
    row.param[4]	 =    0.00191;
    row.param[5]	 =   -0.00557;
    row.param[6]	 =    0.00014;
    row.param[7]	 =   -0.00577;
    row.param[8]	 =    0.00305;
    row.param[9]	 =   -0.00095;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009590099; // ;
    row.dparam[1]	 = 0.001726992;
    row.dparam[2]	 = 0.001720698;
    row.dparam[3]	 = 0.001589591;
    row.dparam[4]	 = 0.001549516;
    row.dparam[5]	 =    0.00128;
    row.dparam[6]	 =    0.00122;
    row.dparam[7]	 =      0.001;
    row.dparam[8]	 =    0.00091;
    row.dparam[9]	 =    0.00066;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4201",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         42; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01864; // ;
    row.param[1]	 =    0.00693;
    row.param[2]	 =     0.0199;
    row.param[3]	 =    0.00898;
    row.param[4]	 =   -0.00063;
    row.param[5]	 =    0.00192;
    row.param[6]	 =   -0.00022;
    row.param[7]	 =    0.00292;
    row.param[8]	 =   -0.00156;
    row.param[9]	 =    0.00086;
    row.param[10]	 =    0.00066;
    row.param[11]	 =    0.00189;
    row.dparam[0]	 = 0.000990202; // ;
    row.dparam[1]	 = 0.001941649;
    row.dparam[2]	 = 0.001868154;
    row.dparam[3]	 = 0.001797443;
    row.dparam[4]	 = 0.001660271;
    row.dparam[5]	 = 0.001547676;
    row.dparam[6]	 = 0.001358713;
    row.dparam[7]	 = 0.001198165;
    row.dparam[8]	 = 0.000980816;
    row.dparam[9]	 = 0.0008292768;
    row.dparam[10]	 =    0.00049;
    row.dparam[11]	 =    0.00045;
 memcpy(&row.Comment,"duuP4201",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         43; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00257; // ;
    row.param[1]	 =   -0.01043;
    row.param[2]	 =   -0.01323;
    row.param[3]	 =   -0.01127;
    row.param[4]	 =    0.00587;
    row.param[5]	 =   -0.00807;
    row.param[6]	 =    0.00046;
    row.param[7]	 =   -0.00339;
    row.param[8]	 =    0.00176;
    row.param[9]	 =    0.00109;
    row.param[10]	 =    0.00352;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001038123; // ;
    row.dparam[1]	 =    0.00206;
    row.dparam[2]	 =    0.00194;
    row.dparam[3]	 =    0.00193;
    row.dparam[4]	 =    0.00173;
    row.dparam[5]	 =    0.00166;
    row.dparam[6]	 =    0.00141;
    row.dparam[7]	 =    0.00131;
    row.dparam[8]	 =    0.00104;
    row.dparam[9]	 =    0.00093;
    row.dparam[10]	 =    0.00066;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4301",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         44; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    0.01268; // ;
    row.param[1]	 =   -0.00034;
    row.param[2]	 =    0.01166;
    row.param[3]	 =   -0.00069;
    row.param[4]	 =   -0.00738;
    row.param[5]	 =    -0.0065;
    row.param[6]	 =   -0.00484;
    row.param[7]	 =   -0.00218;
    row.param[8]	 =   -0.00354;
    row.param[9]	 =   -0.00212;
    row.param[10]	 =   -0.00126;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007988742; // ;
    row.dparam[1]	 = 0.001475568;
    row.dparam[2]	 = 0.001486674;
    row.dparam[3]	 = 0.001322309;
    row.dparam[4]	 = 0.001308167;
    row.dparam[5]	 = 0.001124322;
    row.dparam[6]	 = 0.001089036;
    row.dparam[7]	 = 0.0008697701;
    row.dparam[8]	 = 0.0008061017;
    row.dparam[9]	 = 0.0006010824;
    row.dparam[10]	 =     0.0004;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4301",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         45; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =   -0.02978; // ;
    row.param[1]	 =   -0.01582;
    row.param[2]	 =    0.00742;
    row.param[3]	 =    -0.0036;
    row.param[4]	 =     0.0023;
    row.param[5]	 =   -0.00255;
    row.param[6]	 =   -0.00096;
    row.param[7]	 =   -0.00145;
    row.param[8]	 =   -0.00024;
    row.param[9]	 =   -0.00062;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006835203; // ;
    row.dparam[1]	 = 0.00121758;
    row.dparam[2]	 =     0.0012;
    row.dparam[3]	 =    0.00107;
    row.dparam[4]	 =    0.00108;
    row.dparam[5]	 =    0.00092;
    row.dparam[6]	 =    0.00092;
    row.dparam[7]	 =    0.00073;
    row.dparam[8]	 =    0.00071;
    row.dparam[9]	 =    0.00052;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3102",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         46; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01191; // ;
    row.param[1]	 =    0.01226;
    row.param[2]	 =   -0.00219;
    row.param[3]	 =   -0.00739;
    row.param[4]	 =   -0.00351;
    row.param[5]	 =   -0.00575;
    row.param[6]	 =   -0.00163;
    row.param[7]	 =    0.00016;
    row.param[8]	 =    0.00163;
    row.param[9]	 =   -0.00088;
    row.param[10]	 =    0.00148;
    row.param[11]	 =   -0.00038;
    row.dparam[0]	 = 0.001506552; // ;
    row.dparam[1]	 = 0.003076898;
    row.dparam[2]	 = 0.002829311;
    row.dparam[3]	 = 0.002843132;
    row.dparam[4]	 = 0.002503518;
    row.dparam[5]	 = 0.002453752;
    row.dparam[6]	 = 0.002036517;
    row.dparam[7]	 = 0.001930414;
    row.dparam[8]	 = 0.001527416;
    row.dparam[9]	 = 0.001393018;
    row.dparam[10]	 = 0.0009687621;
    row.dparam[11]	 =    0.00063;
 memcpy(&row.Comment,"duuP3102",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         47; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01529; // ;
    row.param[1]	 =   -0.01477;
    row.param[2]	 =   -0.00247;
    row.param[3]	 =    -0.0071;
    row.param[4]	 =    0.00092;
    row.param[5]	 =   -0.00367;
    row.param[6]	 =    0.00211;
    row.param[7]	 =   -0.00483;
    row.param[8]	 =   -0.00017;
    row.param[9]	 =   -0.00087;
    row.param[10]	 =    0.00042;
    row.param[11]	 =   -0.00017;
    row.dparam[0]	 = 0.0008324062; // ;
    row.dparam[1]	 = 0.001660181;
    row.dparam[2]	 = 0.001556535;
    row.dparam[3]	 = 0.001544345;
    row.dparam[4]	 = 0.001400036;
    row.dparam[5]	 = 0.001334166;
    row.dparam[6]	 = 0.001154859;
    row.dparam[7]	 = 0.001065129;
    row.dparam[8]	 =    0.00074;
    row.dparam[9]	 =    0.00071;
    row.dparam[10]	 =     0.0005;
    row.dparam[11]	 =    0.00047;
 memcpy(&row.Comment,"duuP3202",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         48; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          6; // ;
    row.param[0]	 =    0.01203; // ;
    row.param[1]	 =    0.00986;
    row.param[2]	 =    0.00717;
    row.param[3]	 =   -0.00144;
    row.param[4]	 =     0.0014;
    row.param[5]	 =   -0.00151;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005359104; // ;
    row.dparam[1]	 = 0.0009630161;
    row.dparam[2]	 = 0.0008742425;
    row.dparam[3]	 = 0.000820061;
    row.dparam[4]	 = 0.000664003;
    row.dparam[5]	 =    0.00042;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3202",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         49; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.0101; // ;
    row.param[1]	 =   -0.02492;
    row.param[2]	 =    0.00063;
    row.param[3]	 =   -0.00826;
    row.param[4]	 =    0.00253;
    row.param[5]	 =   -0.00206;
    row.param[6]	 =    0.00075;
    row.param[7]	 =    0.00048;
    row.param[8]	 =    0.00095;
    row.param[9]	 =    0.00345;
    row.param[10]	 =   -0.00051;
    row.param[11]	 =    0.00022;
    row.dparam[0]	 = 0.001368393; // ;
    row.dparam[1]	 = 0.002834872;
    row.dparam[2]	 = 0.002603901;
    row.dparam[3]	 = 0.002615435;
    row.dparam[4]	 = 0.002303628;
    row.dparam[5]	 = 0.002268987;
    row.dparam[6]	 = 0.001870615;
    row.dparam[7]	 = 0.001784068;
    row.dparam[8]	 = 0.00136832;
    row.dparam[9]	 = 0.001287517;
    row.dparam[10]	 = 0.0008891569;
    row.dparam[11]	 =    0.00048;
 memcpy(&row.Comment,"duuP3302",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         50; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01355; // ;
    row.param[1]	 =   -0.00894;
    row.param[2]	 =   -0.00634;
    row.param[3]	 =   -0.01267;
    row.param[4]	 =   -0.00986;
    row.param[5]	 =   -0.01274;
    row.param[6]	 =   -0.00836;
    row.param[7]	 =   -0.00813;
    row.param[8]	 =   -0.00423;
    row.param[9]	 =   -0.00464;
    row.param[10]	 =   -0.00219;
    row.param[11]	 =   -0.00103;
    row.dparam[0]	 = 0.001521742; // ;
    row.dparam[1]	 = 0.003111752;
    row.dparam[2]	 = 0.002868867;
    row.dparam[3]	 = 0.002856116;
    row.dparam[4]	 = 0.002526757;
    row.dparam[5]	 = 0.00244432;
    row.dparam[6]	 = 0.002016556;
    row.dparam[7]	 = 0.001894466;
    row.dparam[8]	 = 0.001461267;
    row.dparam[9]	 =  0.0013454;
    row.dparam[10]	 = 0.000906587;
    row.dparam[11]	 =    0.00048;
 memcpy(&row.Comment,"duuP3302",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         51; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00089; // ;
    row.param[1]	 =   -0.00993;
    row.param[2]	 =   -0.00169;
    row.param[3]	 =    -0.0023;
    row.param[4]	 =   -0.00441;
    row.param[5]	 =   -0.00228;
    row.param[6]	 =   -0.00321;
    row.param[7]	 =    -0.0029;
    row.param[8]	 =   -0.00201;
    row.param[9]	 =   -0.00134;
    row.param[10]	 =   -0.00218;
    row.param[11]	 =     -9e-05;
    row.dparam[0]	 = 0.001061037; // ;
    row.dparam[1]	 = 0.002178302;
    row.dparam[2]	 = 0.002001724;
    row.dparam[3]	 = 0.002029704;
    row.dparam[4]	 = 0.00177519;
    row.dparam[5]	 = 0.001767993;
    row.dparam[6]	 = 0.001463865;
    row.dparam[7]	 = 0.001421302;
    row.dparam[8]	 = 0.001096038;
    row.dparam[9]	 = 0.001039471;
    row.dparam[10]	 = 0.0007707788;
    row.dparam[11]	 =    0.00053;
 memcpy(&row.Comment,"duuP4303",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         52; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02328; // ;
    row.param[1]	 =   -0.00033;
    row.param[2]	 =    0.00138;
    row.param[3]	 =    0.01211;
    row.param[4]	 =    0.00797;
    row.param[5]	 =    0.00708;
    row.param[6]	 =    0.00333;
    row.param[7]	 =    0.00761;
    row.param[8]	 =    0.00451;
    row.param[9]	 =    0.00166;
    row.param[10]	 =    0.00127;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001079676; // ;
    row.dparam[1]	 = 0.002181238;
    row.dparam[2]	 =    0.00197;
    row.dparam[3]	 =    0.00197;
    row.dparam[4]	 =    0.00174;
    row.dparam[5]	 =    0.00169;
    row.dparam[6]	 =     0.0014;
    row.dparam[7]	 =    0.00131;
    row.dparam[8]	 =    0.00101;
    row.dparam[9]	 =    0.00094;
    row.dparam[10]	 =    0.00069;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4303",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         53; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =    0.00806; // ;
    row.param[1]	 =    -0.0061;
    row.param[2]	 =   -0.00697;
    row.param[3]	 =   -0.01069;
    row.param[4]	 =   -0.00989;
    row.param[5]	 =   -0.00499;
    row.param[6]	 =   -0.00329;
    row.param[7]	 =   -0.00202;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007647876; // ;
    row.dparam[1]	 = 0.001328232;
    row.dparam[2]	 =    0.00124;
    row.dparam[3]	 =    0.00106;
    row.dparam[4]	 =    0.00107;
    row.dparam[5]	 =     0.0009;
    row.dparam[6]	 =    0.00089;
    row.dparam[7]	 =    0.00068;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3104",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         54; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =    0.01904; // ;
    row.param[1]	 =   -0.00149;
    row.param[2]	 =   -0.00121;
    row.param[3]	 =     0.0069;
    row.param[4]	 =     -8e-05;
    row.param[5]	 =      7e-05;
    row.param[6]	 =   -0.00098;
    row.param[7]	 =    0.00235;
    row.param[8]	 =   -0.00126;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007908224; // ;
    row.dparam[1]	 = 0.001439931;
    row.dparam[2]	 = 0.00126657;
    row.dparam[3]	 = 0.001274755;
    row.dparam[4]	 =    0.00097;
    row.dparam[5]	 =    0.00099;
    row.dparam[6]	 =    0.00079;
    row.dparam[7]	 =     0.0008;
    row.dparam[8]	 =    0.00064;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3104",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         55; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    0.00679; // ;
    row.param[1]	 =   -0.01018;
    row.param[2]	 =    -0.0111;
    row.param[3]	 =   -0.01292;
    row.param[4]	 =   -0.01677;
    row.param[5]	 =   -0.00861;
    row.param[6]	 =   -0.00999;
    row.param[7]	 =   -0.00764;
    row.param[8]	 =   -0.00682;
    row.param[9]	 =   -0.00393;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001147693; // ;
    row.dparam[1]	 = 0.002114048;
    row.dparam[2]	 = 0.002117286;
    row.dparam[3]	 = 0.001961734;
    row.dparam[4]	 = 0.001882153;
    row.dparam[5]	 = 0.001557562;
    row.dparam[6]	 =    0.00138;
    row.dparam[7]	 =    0.00111;
    row.dparam[8]	 =    0.00105;
    row.dparam[9]	 =    0.00082;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3204",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         56; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01095; // ;
    row.param[1]	 =   -0.00993;
    row.param[2]	 =    -0.0011;
    row.param[3]	 =    0.00536;
    row.param[4]	 =    0.00429;
    row.param[5]	 =   -0.00038;
    row.param[6]	 =    0.00237;
    row.param[7]	 =    0.00544;
    row.param[8]	 =    0.00281;
    row.param[9]	 =          0;
    row.param[10]	 =    0.00401;
    row.param[11]	 =    0.00361;
    row.dparam[0]	 = 0.001726297; // ;
    row.dparam[1]	 = 0.003407712;
    row.dparam[2]	 = 0.003133449;
    row.dparam[3]	 = 0.003282834;
    row.dparam[4]	 = 0.002708007;
    row.dparam[5]	 = 0.002737481;
    row.dparam[6]	 = 0.002255349;
    row.dparam[7]	 = 0.002082018;
    row.dparam[8]	 = 0.001705784;
    row.dparam[9]	 =    0.00129;
    row.dparam[10]	 =      0.001;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3204",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         57; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    0.01419; // ;
    row.param[1]	 =   -0.01623;
    row.param[2]	 =   -0.00512;
    row.param[3]	 =   -0.01694;
    row.param[4]	 =   -0.00826;
    row.param[5]	 =   -0.00957;
    row.param[6]	 =   -0.00872;
    row.param[7]	 =   -0.00742;
    row.param[8]	 =   -0.00901;
    row.param[9]	 =   -0.00505;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001095673; // ;
    row.dparam[1]	 = 0.001964739;
    row.dparam[2]	 = 0.002000325;
    row.dparam[3]	 = 0.001759602;
    row.dparam[4]	 = 0.001754537;
    row.dparam[5]	 = 0.001441804;
    row.dparam[6]	 = 0.001401178;
    row.dparam[7]	 =      0.001;
    row.dparam[8]	 =    0.00096;
    row.dparam[9]	 =    0.00068;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3304",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         58; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =    0.02324; // ;
    row.param[1]	 =    0.01062;
    row.param[2]	 =    0.00175;
    row.param[3]	 =   -0.00203;
    row.param[4]	 =   -0.00016;
    row.param[5]	 =   -0.00203;
    row.param[6]	 =     0.0026;
    row.param[7]	 =   -0.00107;
    row.param[8]	 =    0.00363;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.000735459; // ;
    row.dparam[1]	 = 0.00121647;
    row.dparam[2]	 = 0.001166062;
    row.dparam[3]	 = 0.001010198;
    row.dparam[4]	 = 0.001024158;
    row.dparam[5]	 = 0.0008700575;
    row.dparam[6]	 =     0.0007;
    row.dparam[7]	 =    0.00058;
    row.dparam[8]	 =    0.00058;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3304",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         59; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          4; // ;
    row.param[0]	 =   -0.02066; // ;
    row.param[1]	 =   -0.00615;
    row.param[2]	 =    0.00693;
    row.param[3]	 =     0.0017;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006530697; // ;
    row.dparam[1]	 = 0.001125833;
    row.dparam[2]	 = 0.0009974969;
    row.dparam[3]	 = 0.0007707788;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3404",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         60; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     0.0116; // ;
    row.param[1]	 =    0.02816;
    row.param[2]	 =   -0.01196;
    row.param[3]	 =    0.00146;
    row.param[4]	 =   -0.00191;
    row.param[5]	 =   -0.00338;
    row.param[6]	 =   -0.00322;
    row.param[7]	 =   -0.00515;
    row.param[8]	 =    -0.0012;
    row.param[9]	 =   -0.00229;
    row.param[10]	 =    0.00049;
    row.param[11]	 =          0;
    row.dparam[0]	 =    0.00105; // ;
    row.dparam[1]	 = 0.002098142;
    row.dparam[2]	 = 0.001848053;
    row.dparam[3]	 = 0.001897709;
    row.dparam[4]	 = 0.001647938;
    row.dparam[5]	 = 0.001661114;
    row.dparam[6]	 = 0.001356503;
    row.dparam[7]	 =    0.00122;
    row.dparam[8]	 =    0.00093;
    row.dparam[9]	 =    0.00093;
    row.dparam[10]	 =    0.00068;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3404",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         61; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =   -0.03147; // ;
    row.param[1]	 =   -0.00583;
    row.param[2]	 =    0.00584;
    row.param[3]	 =     0.0061;
    row.param[4]	 =   -0.00209;
    row.param[5]	 =    0.00087;
    row.param[6]	 =    0.00405;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005813777; // ;
    row.dparam[1]	 = 0.001052093;
    row.dparam[2]	 = 0.0009794897;
    row.dparam[3]	 = 0.0009513149;
    row.dparam[4]	 = 0.0008560374;
    row.dparam[5]	 =    0.00071;
    row.dparam[6]	 =    0.00056;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3504",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         62; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =    0.00539; // ;
    row.param[1]	 =    0.03232;
    row.param[2]	 =    -0.0029;
    row.param[3]	 =    0.00106;
    row.param[4]	 =   -0.00187;
    row.param[5]	 =   -0.00243;
    row.param[6]	 =    0.00014;
    row.param[7]	 =     -7e-05;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006942622; // ;
    row.dparam[1]	 = 0.001251759;
    row.dparam[2]	 = 0.001235557;
    row.dparam[3]	 = 0.001152779;
    row.dparam[4]	 = 0.001082312;
    row.dparam[5]	 = 0.0009759098;
    row.dparam[6]	 = 0.0009183137;
    row.dparam[7]	 = 0.0008202439;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3504",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         63; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =   -0.01749; // ;
    row.param[1]	 =    -0.0057;
    row.param[2]	 =   -0.00195;
    row.param[3]	 =   -0.00185;
    row.param[4]	 =   -0.00336;
    row.param[5]	 =   -0.00029;
    row.param[6]	 =   -0.00287;
    row.param[7]	 =   -0.00182;
    row.param[8]	 =   -0.00252;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007717513; // ;
    row.dparam[1]	 = 0.001484992;
    row.dparam[2]	 = 0.001373536;
    row.dparam[3]	 = 0.001356503;
    row.dparam[4]	 = 0.001185116;
    row.dparam[5]	 =    0.00106;
    row.dparam[6]	 =    0.00088;
    row.dparam[7]	 =    0.00087;
    row.dparam[8]	 =    0.00065;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3604",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         64; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =   -0.00264; // ;
    row.param[1]	 =    0.02941;
    row.param[2]	 =   -0.00349;
    row.param[3]	 =    0.00914;
    row.param[4]	 =   -0.00013;
    row.param[5]	 =    0.00291;
    row.param[6]	 =    0.00054;
    row.param[7]	 =   -0.00055;
    row.param[8]	 =    0.00298;
    row.param[9]	 =    0.00205;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009563995; // ;
    row.dparam[1]	 = 0.001648454;
    row.dparam[2]	 = 0.001709766;
    row.dparam[3]	 = 0.001497465;
    row.dparam[4]	 = 0.001522629;
    row.dparam[5]	 = 0.001211982;
    row.dparam[6]	 =    0.00106;
    row.dparam[7]	 =    0.00083;
    row.dparam[8]	 =    0.00083;
    row.dparam[9]	 =    0.00063;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3604",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         65; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00472; // ;
    row.param[1]	 =   -0.00667;
    row.param[2]	 =   -0.00016;
    row.param[3]	 =     -3e-05;
    row.param[4]	 =    0.00554;
    row.param[5]	 =      0.001;
    row.param[6]	 =    0.00632;
    row.param[7]	 =    0.00521;
    row.param[8]	 =    0.00279;
    row.param[9]	 =    0.00557;
    row.param[10]	 =    0.00165;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008956004; // ;
    row.dparam[1]	 = 0.001838614;
    row.dparam[2]	 =    0.00164;
    row.dparam[3]	 =    0.00167;
    row.dparam[4]	 =    0.00147;
    row.dparam[5]	 =    0.00146;
    row.dparam[6]	 =    0.00121;
    row.dparam[7]	 =    0.00116;
    row.dparam[8]	 =     0.0009;
    row.dparam[9]	 =    0.00084;
    row.dparam[10]	 =    0.00059;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4105",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         66; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          5; // ;
    row.param[0]	 =    0.01448; // ;
    row.param[1]	 =    0.00365;
    row.param[2]	 =    0.00696;
    row.param[3]	 =   -0.00095;
    row.param[4]	 =    0.00069;
    row.param[5]	 =   -0.00258;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007496666; // ;
    row.dparam[1]	 = 0.00126657;
    row.dparam[2]	 = 0.001217538;
    row.dparam[3]	 = 0.001203412;
    row.dparam[4]	 =    0.00078;
    row.dparam[5]	 =    0.00072;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4105",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         67; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =   -0.00633; // ;
    row.param[1]	 =   -0.01865;
    row.param[2]	 =    0.00324;
    row.param[3]	 =   -0.00831;
    row.param[4]	 =   -0.00109;
    row.param[5]	 =    0.00074;
    row.param[6]	 =    0.00245;
    row.param[7]	 =    0.00126;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006226556; // ;
    row.dparam[1]	 = 0.001090917;
    row.dparam[2]	 = 0.00103465;
    row.dparam[3]	 = 0.0009126883;
    row.dparam[4]	 = 0.0008958795;
    row.dparam[5]	 = 0.0007433034;
    row.dparam[6]	 =     0.0006;
    row.dparam[7]	 =    0.00046;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4205",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         68; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     0.0198; // ;
    row.param[1]	 =    0.01202;
    row.param[2]	 =    0.00528;
    row.param[3]	 =     -4e-05;
    row.param[4]	 =    0.00383;
    row.param[5]	 =      9e-05;
    row.param[6]	 =    0.00087;
    row.param[7]	 =    -0.0016;
    row.param[8]	 =   -0.00206;
    row.param[9]	 =   -0.00216;
    row.param[10]	 =   -0.00115;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001059481; // ;
    row.dparam[1]	 = 0.002136937;
    row.dparam[2]	 =    0.00194;
    row.dparam[3]	 =    0.00194;
    row.dparam[4]	 =    0.00174;
    row.dparam[5]	 =    0.00172;
    row.dparam[6]	 =    0.00141;
    row.dparam[7]	 =    0.00135;
    row.dparam[8]	 =     0.0011;
    row.dparam[9]	 =    0.00098;
    row.dparam[10]	 =    0.00076;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4205",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         69; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =     0.0075; // ;
    row.param[1]	 =    -0.0269;
    row.param[2]	 =   -0.00252;
    row.param[3]	 =    -0.0057;
    row.param[4]	 =    0.00247;
    row.param[5]	 =   -0.00621;
    row.param[6]	 =    0.00363;
    row.param[7]	 =   -0.00088;
    row.param[8]	 =    0.00102;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006296825; // ;
    row.dparam[1]	 = 0.001118034;
    row.dparam[2]	 = 0.001160431;
    row.dparam[3]	 = 0.001011781;
    row.dparam[4]	 = 0.001025914;
    row.dparam[5]	 = 0.0008558621;
    row.dparam[6]	 = 0.0008345058;
    row.dparam[7]	 = 0.0006576473;
    row.dparam[8]	 =    0.00045;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4305",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         70; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    0.01738; // ;
    row.param[1]	 =    0.01316;
    row.param[2]	 =    0.01033;
    row.param[3]	 =     -0.005;
    row.param[4]	 =    0.00588;
    row.param[5]	 =   -0.00352;
    row.param[6]	 =     0.0033;
    row.param[7]	 =   -0.00322;
    row.param[8]	 =    0.00211;
    row.param[9]	 =   -0.00267;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008860023; // ;
    row.dparam[1]	 = 0.001581139;
    row.dparam[2]	 =    0.00154;
    row.dparam[3]	 =    0.00146;
    row.dparam[4]	 =    0.00144;
    row.dparam[5]	 =    0.00119;
    row.dparam[6]	 =     0.0012;
    row.dparam[7]	 =    0.00099;
    row.dparam[8]	 =    0.00091;
    row.dparam[9]	 =    0.00073;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4305",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         71; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00802; // ;
    row.param[1]	 =   -0.04415;
    row.param[2]	 =    0.00854;
    row.param[3]	 =   -0.00915;
    row.param[4]	 =   -0.00885;
    row.param[5]	 =   -0.00821;
    row.param[6]	 =    -0.0083;
    row.param[7]	 =    -0.0134;
    row.param[8]	 =   -0.01137;
    row.param[9]	 =   -0.00576;
    row.param[10]	 =   -0.00644;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.005081702; // ;
    row.dparam[1]	 = 0.01012978;
    row.dparam[2]	 = 0.009171309;
    row.dparam[3]	 = 0.008801278;
    row.dparam[4]	 = 0.007555521;
    row.dparam[5]	 = 0.007573011;
    row.dparam[6]	 = 0.00610535;
    row.dparam[7]	 =    0.00577;
    row.dparam[8]	 =     0.0039;
    row.dparam[9]	 =    0.00329;
    row.dparam[10]	 =     0.0016;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4405",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         72; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =    0.02802; // ;
    row.param[1]	 =    0.02105;
    row.param[2]	 =   -0.00326;
    row.param[3]	 =   -0.00056;
    row.param[4]	 =   -0.00976;
    row.param[5]	 =     -5e-05;
    row.param[6]	 =   -0.00302;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.003803262; // ;
    row.dparam[1]	 = 0.007379241;
    row.dparam[2]	 =    0.00624;
    row.dparam[3]	 =    0.00519;
    row.dparam[4]	 =    0.00361;
    row.dparam[5]	 =    0.00274;
    row.dparam[6]	 =    0.00155;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4405",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         73; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.05926; // ;
    row.param[1]	 =   -0.06061;
    row.param[2]	 =   -0.02937;
    row.param[3]	 =   -0.00755;
    row.param[4]	 =    0.00094;
    row.param[5]	 =   -0.00597;
    row.param[6]	 =    0.00394;
    row.param[7]	 =     0.0017;
    row.param[8]	 =   -0.00291;
    row.param[9]	 =    0.00386;
    row.param[10]	 =   -0.00266;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001752997; // ;
    row.dparam[1]	 = 0.004128208;
    row.dparam[2]	 = 0.003303725;
    row.dparam[3]	 = 0.003798276;
    row.dparam[4]	 = 0.002906906;
    row.dparam[5]	 = 0.003237746;
    row.dparam[6]	 = 0.00233891;
    row.dparam[7]	 = 0.002488092;
    row.dparam[8]	 = 0.001641493;
    row.dparam[9]	 = 0.001722353;
    row.dparam[10]	 = 0.001028251;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3106",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         74; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.08548; // ;
    row.param[1]	 =    0.08017;
    row.param[2]	 =    0.02044;
    row.param[3]	 =     0.0143;
    row.param[4]	 =    -0.0098;
    row.param[5]	 =    0.01445;
    row.param[6]	 =   -0.01217;
    row.param[7]	 =    0.00682;
    row.param[8]	 =   -0.01255;
    row.param[9]	 =    0.00453;
    row.param[10]	 =    -0.0033;
    row.param[11]	 =    0.00031;
    row.dparam[0]	 = 0.001613846; // ;
    row.dparam[1]	 = 0.002994411;
    row.dparam[2]	 = 0.003061127;
    row.dparam[3]	 = 0.002768032;
    row.dparam[4]	 = 0.002709243;
    row.dparam[5]	 = 0.002364868;
    row.dparam[6]	 = 0.002182911;
    row.dparam[7]	 = 0.001860269;
    row.dparam[8]	 = 0.001556438;
    row.dparam[9]	 = 0.00129031;
    row.dparam[10]	 = 0.0007849204;
    row.dparam[11]	 =    0.00052;
 memcpy(&row.Comment,"duuP3106",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         75; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.03303; // ;
    row.param[1]	 =   -0.02474;
    row.param[2]	 =   -0.03158;
    row.param[3]	 =   -0.00272;
    row.param[4]	 =   -0.00181;
    row.param[5]	 =   -0.00599;
    row.param[6]	 =    0.00758;
    row.param[7]	 =    0.00115;
    row.param[8]	 =   -0.00028;
    row.param[9]	 =    0.00759;
    row.param[10]	 =   -0.00093;
    row.param[11]	 =    0.00062;
    row.dparam[0]	 = 0.001738189; // ;
    row.dparam[1]	 = 0.003563495;
    row.dparam[2]	 = 0.003297469;
    row.dparam[3]	 = 0.003304088;
    row.dparam[4]	 = 0.002945743;
    row.dparam[5]	 = 0.002865659;
    row.dparam[6]	 = 0.002380546;
    row.dparam[7]	 = 0.002219234;
    row.dparam[8]	 = 0.001704611;
    row.dparam[9]	 = 0.001560064;
    row.dparam[10]	 = 0.001097452;
    row.dparam[11]	 =    0.00053;
 memcpy(&row.Comment,"duuP3206",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         76; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.02846; // ;
    row.param[1]	 =    0.01331;
    row.param[2]	 =    0.03825;
    row.param[3]	 =   -0.00876;
    row.param[4]	 =    0.00712;
    row.param[5]	 =   -0.00133;
    row.param[6]	 =    0.00039;
    row.param[7]	 =    -0.0045;
    row.param[8]	 =    0.00405;
    row.param[9]	 =   -0.00585;
    row.param[10]	 =      7e-05;
    row.param[11]	 =   -0.00149;
    row.dparam[0]	 = 0.001158879; // ;
    row.dparam[1]	 = 0.002288231;
    row.dparam[2]	 = 0.002172027;
    row.dparam[3]	 = 0.002096282;
    row.dparam[4]	 = 0.001912328;
    row.dparam[5]	 = 0.001725138;
    row.dparam[6]	 = 0.001500833;
    row.dparam[7]	 = 0.001320189;
    row.dparam[8]	 = 0.001071681;
    row.dparam[9]	 = 0.0009097252;
    row.dparam[10]	 =    0.00052;
    row.dparam[11]	 =    0.00046;
 memcpy(&row.Comment,"duuP3206",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         77; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02455; // ;
    row.param[1]	 =   -0.00961;
    row.param[2]	 =   -0.03429;
    row.param[3]	 =    0.00108;
    row.param[4]	 =   -0.00282;
    row.param[5]	 =   -0.00052;
    row.param[6]	 =    0.00288;
    row.param[7]	 =    0.00432;
    row.param[8]	 =     -5e-05;
    row.param[9]	 =    0.00496;
    row.param[10]	 =   -0.00168;
    row.param[11]	 =    0.00191;
    row.dparam[0]	 = 0.001778482; // ;
    row.dparam[1]	 = 0.003626238;
    row.dparam[2]	 = 0.00338941;
    row.dparam[3]	 = 0.003360446;
    row.dparam[4]	 = 0.003008338;
    row.dparam[5]	 = 0.002869791;
    row.dparam[6]	 = 0.002396393;
    row.dparam[7]	 = 0.002200023;
    row.dparam[8]	 = 0.00169794;
    row.dparam[9]	 = 0.001518585;
    row.dparam[10]	 = 0.001062544;
    row.dparam[11]	 =    0.00051;
 memcpy(&row.Comment,"duuP3306",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         78; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.02564; // ;
    row.param[1]	 =    0.02164;
    row.param[2]	 =    0.03218;
    row.param[3]	 =   -0.00117;
    row.param[4]	 =   -0.00149;
    row.param[5]	 =     0.0048;
    row.param[6]	 =   -0.00263;
    row.param[7]	 =   -0.00597;
    row.param[8]	 =    0.00337;
    row.param[9]	 =   -0.00731;
    row.param[10]	 =    0.00301;
    row.param[11]	 =    0.00021;
    row.dparam[0]	 = 0.001270197; // ;
    row.dparam[1]	 = 0.002621183;
    row.dparam[2]	 = 0.002419111;
    row.dparam[3]	 = 0.002436432;
    row.dparam[4]	 = 0.002153625;
    row.dparam[5]	 = 0.002101666;
    row.dparam[6]	 = 0.001749543;
    row.dparam[7]	 = 0.001668682;
    row.dparam[8]	 = 0.001276284;
    row.dparam[9]	 = 0.001177879;
    row.dparam[10]	 = 0.0008371977;
    row.dparam[11]	 =    0.00043;
 memcpy(&row.Comment,"duuP3306",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         79; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =    0.00308; // ;
    row.param[1]	 =   -0.03366;
    row.param[2]	 =    0.00724;
    row.param[3]	 =    -0.0178;
    row.param[4]	 =    0.01263;
    row.param[5]	 =   -0.01258;
    row.param[6]	 =    0.00975;
    row.param[7]	 =    -0.0073;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008850989; // ;
    row.dparam[1]	 = 0.001567323;
    row.dparam[2]	 = 0.001632667;
    row.dparam[3]	 = 0.00139603;
    row.dparam[4]	 = 0.001380616;
    row.dparam[5]	 = 0.001104536;
    row.dparam[6]	 = 0.001049571;
    row.dparam[7]	 = 0.0007789737;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3406",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         80; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01374; // ;
    row.param[1]	 =    0.03272;
    row.param[2]	 =   -0.01134;
    row.param[3]	 =    0.01534;
    row.param[4]	 =   -0.01661;
    row.param[5]	 =     0.0138;
    row.param[6]	 =   -0.00664;
    row.param[7]	 =    0.00368;
    row.param[8]	 =   -0.00123;
    row.param[9]	 =    0.00066;
    row.param[10]	 =   -0.00095;
    row.param[11]	 =    0.00103;
    row.dparam[0]	 = 0.001676484; // ;
    row.dparam[1]	 = 0.003843085;
    row.dparam[2]	 = 0.003156549;
    row.dparam[3]	 = 0.003523606;
    row.dparam[4]	 = 0.002763404;
    row.dparam[5]	 = 0.002982801;
    row.dparam[6]	 = 0.002173845;
    row.dparam[7]	 = 0.002284404;
    row.dparam[8]	 = 0.001514398;
    row.dparam[9]	 = 0.001567354;
    row.dparam[10]	 = 0.0009646243;
    row.dparam[11]	 =    0.00052;
 memcpy(&row.Comment,"duuP3406",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         81; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     0.0303; // ;
    row.param[1]	 =    -0.0403;
    row.param[2]	 =    0.01973;
    row.param[3]	 =   -0.01513;
    row.param[4]	 =     0.0234;
    row.param[5]	 =   -0.00519;
    row.param[6]	 =    0.01053;
    row.param[7]	 =    0.00347;
    row.param[8]	 =    0.00705;
    row.param[9]	 =    0.00109;
    row.param[10]	 =    0.00493;
    row.param[11]	 =     0.0005;
    row.dparam[0]	 = 0.002052243; // ;
    row.dparam[1]	 = 0.004338179;
    row.dparam[2]	 = 0.00387893;
    row.dparam[3]	 = 0.003978744;
    row.dparam[4]	 = 0.003380814;
    row.dparam[5]	 = 0.003353357;
    row.dparam[6]	 = 0.002675164;
    row.dparam[7]	 = 0.002577169;
    row.dparam[8]	 = 0.00184808;
    row.dparam[9]	 = 0.001755733;
    row.dparam[10]	 = 0.001154729;
    row.dparam[11]	 =    0.00061;
 memcpy(&row.Comment,"duuP3506",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         82; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02786; // ;
    row.param[1]	 =    0.02779;
    row.param[2]	 =    -0.0133;
    row.param[3]	 =    0.01395;
    row.param[4]	 =   -0.01274;
    row.param[5]	 =    0.00718;
    row.param[6]	 =   -0.00704;
    row.param[7]	 =    0.00184;
    row.param[8]	 =   -0.00385;
    row.param[9]	 =    0.00073;
    row.param[10]	 =   -0.00163;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001040625; // ;
    row.dparam[1]	 = 0.002466759;
    row.dparam[2]	 = 0.001938479;
    row.dparam[3]	 = 0.00226367;
    row.dparam[4]	 = 0.001688846;
    row.dparam[5]	 = 0.001912302;
    row.dparam[6]	 = 0.001328533;
    row.dparam[7]	 =    0.00143;
    row.dparam[8]	 =    0.00089;
    row.dparam[9]	 =    0.00096;
    row.dparam[10]	 =    0.00054;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3506",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         83; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01714; // ;
    row.param[1]	 =   -0.04352;
    row.param[2]	 =    0.01021;
    row.param[3]	 =   -0.02198;
    row.param[4]	 =    0.01633;
    row.param[5]	 =   -0.01518;
    row.param[6]	 =    0.01241;
    row.param[7]	 =   -0.00603;
    row.param[8]	 =    0.00463;
    row.param[9]	 =   -0.00205;
    row.param[10]	 =   -0.00099;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001744649; // ;
    row.dparam[1]	 = 0.003184054;
    row.dparam[2]	 = 0.003304194;
    row.dparam[3]	 = 0.002925765;
    row.dparam[4]	 = 0.002904634;
    row.dparam[5]	 = 0.00249305;
    row.dparam[6]	 = 0.00233118;
    row.dparam[7]	 = 0.001875233;
    row.dparam[8]	 = 0.001591383;
    row.dparam[9]	 = 0.001258968;
    row.dparam[10]	 =     0.0007;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3606",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         84; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =    0.03645; // ;
    row.param[1]	 =    0.01858;
    row.param[2]	 =    0.00243;
    row.param[3]	 =   -0.00578;
    row.param[4]	 =    -0.0027;
    row.param[5]	 =   -0.00639;
    row.param[6]	 =   -0.00278;
    row.param[7]	 =    -0.0051;
    row.param[8]	 =   -0.00134;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008869047; // ;
    row.dparam[1]	 = 0.002062426;
    row.dparam[2]	 = 0.001559391;
    row.dparam[3]	 =    0.00174;
    row.dparam[4]	 =    0.00124;
    row.dparam[5]	 =     0.0014;
    row.dparam[6]	 =    0.00091;
    row.dparam[7]	 =    0.00098;
    row.dparam[8]	 =    0.00059;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3606",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         85; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          6; // ;
    row.param[0]	 =   -0.03273; // ;
    row.param[1]	 =   -0.01271;
    row.param[2]	 =    0.00915;
    row.param[3]	 =    0.00035;
    row.param[4]	 =    0.00171;
    row.param[5]	 =    0.00133;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0004992995; // ;
    row.dparam[1]	 = 0.000840595;
    row.dparam[2]	 =    0.00071;
    row.dparam[3]	 =    0.00062;
    row.dparam[4]	 =     0.0006;
    row.dparam[5]	 =     0.0005;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4107",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         86; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01507; // ;
    row.param[1]	 =    0.02281;
    row.param[2]	 =   -0.00795;
    row.param[3]	 =    -0.0041;
    row.param[4]	 =    -0.0041;
    row.param[5]	 =    0.00395;
    row.param[6]	 =   -0.00044;
    row.param[7]	 =    0.00411;
    row.param[8]	 =   -0.00138;
    row.param[9]	 =    0.00205;
    row.param[10]	 =   -0.00088;
    row.param[11]	 =   -0.00073;
    row.dparam[0]	 = 0.001218236; // ;
    row.dparam[1]	 = 0.002546154;
    row.dparam[2]	 = 0.002315275;
    row.dparam[3]	 = 0.002372952;
    row.dparam[4]	 = 0.002061189;
    row.dparam[5]	 = 0.002066978;
    row.dparam[6]	 = 0.001691774;
    row.dparam[7]	 = 0.001657015;
    row.dparam[8]	 = 0.00125865;
    row.dparam[9]	 = 0.001235637;
    row.dparam[10]	 = 0.0008602906;
    row.dparam[11]	 =    0.00048;
 memcpy(&row.Comment,"duuP4107",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         87; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01832; // ;
    row.param[1]	 =   -0.00432;
    row.param[2]	 =   -0.00273;
    row.param[3]	 =    0.00449;
    row.param[4]	 =      5e-05;
    row.param[5]	 =    0.00664;
    row.param[6]	 =    0.00402;
    row.param[7]	 =    0.00553;
    row.param[8]	 =    0.00189;
    row.param[9]	 =   -0.00094;
    row.param[10]	 =      6e-05;
    row.param[11]	 =    0.00011;
    row.dparam[0]	 = 0.001193566; // ;
    row.dparam[1]	 = 0.002447121;
    row.dparam[2]	 = 0.002253553;
    row.dparam[3]	 = 0.002260553;
    row.dparam[4]	 = 0.001980454;
    row.dparam[5]	 = 0.001940825;
    row.dparam[6]	 = 0.001603777;
    row.dparam[7]	 = 0.001521052;
    row.dparam[8]	 = 0.001173755;
    row.dparam[9]	 = 0.001004092;
    row.dparam[10]	 = 0.0006929646;
    row.dparam[11]	 =    0.00045;
 memcpy(&row.Comment,"duuP4207",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         88; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00807; // ;
    row.param[1]	 =    0.03003;
    row.param[2]	 =   -0.01056;
    row.param[3]	 =    -0.0009;
    row.param[4]	 =   -0.00719;
    row.param[5]	 =    0.00103;
    row.param[6]	 =    -0.0072;
    row.param[7]	 =   -0.00077;
    row.param[8]	 =   -0.00525;
    row.param[9]	 =   -0.00067;
    row.param[10]	 =    0.00094;
    row.param[11]	 =   -0.00072;
    row.dparam[0]	 = 0.001079768; // ;
    row.dparam[1]	 = 0.002234659;
    row.dparam[2]	 = 0.002026697;
    row.dparam[3]	 = 0.002067124;
    row.dparam[4]	 = 0.001801555;
    row.dparam[5]	 = 0.00178418;
    row.dparam[6]	 = 0.001478107;
    row.dparam[7]	 = 0.001426219;
    row.dparam[8]	 = 0.001108603;
    row.dparam[9]	 = 0.001079861;
    row.dparam[10]	 = 0.0007736924;
    row.dparam[11]	 =    0.00043;
 memcpy(&row.Comment,"duuP4207",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         89; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01199; // ;
    row.param[1]	 =   -0.01957;
    row.param[2]	 =    0.00303;
    row.param[3]	 =    0.00011;
    row.param[4]	 =    0.00327;
    row.param[5]	 =   -0.00295;
    row.param[6]	 =    0.00307;
    row.param[7]	 =   -0.00319;
    row.param[8]	 =    0.00307;
    row.param[9]	 =   -0.00278;
    row.param[10]	 =   -0.00143;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.000938616; // ;
    row.dparam[1]	 = 0.001854211;
    row.dparam[2]	 = 0.001763236;
    row.dparam[3]	 = 0.001712338;
    row.dparam[4]	 = 0.001569745;
    row.dparam[5]	 = 0.001470544;
    row.dparam[6]	 = 0.001285496;
    row.dparam[7]	 = 0.001156763;
    row.dparam[8]	 = 0.0009654015;
    row.dparam[9]	 = 0.0008292768;
    row.dparam[10]	 = 0.0006378087;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4307",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         90; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.03724; // ;
    row.param[1]	 =    0.00367;
    row.param[2]	 =     -1e-05;
    row.param[3]	 =   -0.00101;
    row.param[4]	 =   -0.00343;
    row.param[5]	 =   -0.00103;
    row.param[6]	 =   -0.00549;
    row.param[7]	 =   -0.00104;
    row.param[8]	 =   -0.00487;
    row.param[9]	 =    0.00154;
    row.param[10]	 =   -0.00095;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.000667308; // ;
    row.dparam[1]	 = 0.001364001;
    row.dparam[2]	 = 0.001234909;
    row.dparam[3]	 = 0.001263843;
    row.dparam[4]	 =    0.00105;
    row.dparam[5]	 =    0.00105;
    row.dparam[6]	 =    0.00086;
    row.dparam[7]	 =    0.00085;
    row.dparam[8]	 =    0.00065;
    row.dparam[9]	 =    0.00064;
    row.dparam[10]	 =    0.00045;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4307",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         91; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.05199; // ;
    row.param[1]	 =   -0.03123;
    row.param[2]	 =   -0.01581;
    row.param[3]	 =   -0.01414;
    row.param[4]	 =   -0.00894;
    row.param[5]	 =   -0.01068;
    row.param[6]	 =   -0.00252;
    row.param[7]	 =   -0.00343;
    row.param[8]	 =   -0.00325;
    row.param[9]	 =    0.00086;
    row.param[10]	 =   -0.00257;
    row.param[11]	 =    0.00076;
    row.dparam[0]	 = 0.001696909; // ;
    row.dparam[1]	 = 0.00343968;
    row.dparam[2]	 = 0.003202827;
    row.dparam[3]	 = 0.003154378;
    row.dparam[4]	 = 0.002806225;
    row.dparam[5]	 = 0.002670992;
    row.dparam[6]	 = 0.002225242;
    row.dparam[7]	 = 0.00205039;
    row.dparam[8]	 = 0.001588112;
    row.dparam[9]	 =  0.0014089;
    row.dparam[10]	 = 0.0009988493;
    row.dparam[11]	 =    0.00051;
 memcpy(&row.Comment,"duuP4109",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         92; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.06152; // ;
    row.param[1]	 =    0.01583;
    row.param[2]	 =     -6e-05;
    row.param[3]	 =   -0.00075;
    row.param[4]	 =   -0.00308;
    row.param[5]	 =   -0.00195;
    row.param[6]	 =   -0.00448;
    row.param[7]	 =   -0.00198;
    row.param[8]	 =   -0.00431;
    row.param[9]	 =   -0.00379;
    row.param[10]	 =   -0.00103;
    row.param[11]	 =   -0.00129;
    row.dparam[0]	 = 0.001420493; // ;
    row.dparam[1]	 = 0.002904428;
    row.dparam[2]	 = 0.002690762;
    row.dparam[3]	 = 0.002708081;
    row.dparam[4]	 = 0.002407841;
    row.dparam[5]	 = 0.00234444;
    row.dparam[6]	 = 0.001951768;
    row.dparam[7]	 = 0.001848026;
    row.dparam[8]	 = 0.001432131;
    row.dparam[9]	 = 0.001322611;
    row.dparam[10]	 = 0.0009413288;
    row.dparam[11]	 =    0.00048;
 memcpy(&row.Comment,"duuP4109",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         93; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.04222; // ;
    row.param[1]	 =   -0.02753;
    row.param[2]	 =   -0.01583;
    row.param[3]	 =   -0.01268;
    row.param[4]	 =   -0.00704;
    row.param[5]	 =   -0.01042;
    row.param[6]	 =   -0.00472;
    row.param[7]	 =   -0.00041;
    row.param[8]	 =    -0.0056;
    row.param[9]	 =    0.00438;
    row.param[10]	 =   -0.00459;
    row.param[11]	 =    0.00067;
    row.dparam[0]	 = 0.002801339; // ;
    row.dparam[1]	 = 0.005617375;
    row.dparam[2]	 = 0.005261948;
    row.dparam[3]	 = 0.005032345;
    row.dparam[4]	 = 0.004432449;
    row.dparam[5]	 = 0.004023046;
    row.dparam[6]	 = 0.00327666;
    row.dparam[7]	 = 0.002798946;
    row.dparam[8]	 = 0.002075524;
    row.dparam[9]	 = 0.001699559;
    row.dparam[10]	 = 0.001130531;
    row.dparam[11]	 =    0.00061;
 memcpy(&row.Comment,"duuP4209",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         94; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.06542; // ;
    row.param[1]	 =    0.00753;
    row.param[2]	 =     0.0044;
    row.param[3]	 =    0.00285;
    row.param[4]	 =   -0.00179;
    row.param[5]	 =    0.00286;
    row.param[6]	 =   -0.00346;
    row.param[7]	 =   -0.00352;
    row.param[8]	 =    0.00025;
    row.param[9]	 =   -0.00625;
    row.param[10]	 =    0.00107;
    row.param[11]	 =          0;
    row.dparam[0]	 =    0.00089; // ;
    row.dparam[1]	 = 0.001803358;
    row.dparam[2]	 = 0.001670269;
    row.dparam[3]	 = 0.001679434;
    row.dparam[4]	 = 0.001483846;
    row.dparam[5]	 = 0.001439236;
    row.dparam[6]	 = 0.001209049;
    row.dparam[7]	 = 0.00113653;
    row.dparam[8]	 =    0.00083;
    row.dparam[9]	 =    0.00075;
    row.dparam[10]	 =    0.00052;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4209",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         95; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01617; // ;
    row.param[1]	 =   -0.00352;
    row.param[2]	 =   -0.01021;
    row.param[3]	 =   -0.01608;
    row.param[4]	 =   -0.00664;
    row.param[5]	 =   -0.01211;
    row.param[6]	 =     -0.006;
    row.param[7]	 =   -0.00457;
    row.param[8]	 =   -0.00634;
    row.param[9]	 =   -0.00101;
    row.param[10]	 =   -0.00242;
    row.param[11]	 =    0.00012;
    row.dparam[0]	 = 0.001307976; // ;
    row.dparam[1]	 = 0.002666927;
    row.dparam[2]	 = 0.00250008;
    row.dparam[3]	 = 0.002469231;
    row.dparam[4]	 = 0.002180573;
    row.dparam[5]	 = 0.002080817;
    row.dparam[6]	 = 0.001739569;
    row.dparam[7]	 = 0.001599844;
    row.dparam[8]	 = 0.00123588;
    row.dparam[9]	 = 0.001096996;
    row.dparam[10]	 = 0.0008141867;
    row.dparam[11]	 =    0.00042;
 memcpy(&row.Comment,"duuP4309",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         96; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.05153; // ;
    row.param[1]	 =   -0.00135;
    row.param[2]	 =   -0.00404;
    row.param[3]	 =     0.0019;
    row.param[4]	 =   -0.00577;
    row.param[5]	 =    0.00362;
    row.param[6]	 =    -0.0014;
    row.param[7]	 =   -0.00012;
    row.param[8]	 =    0.00403;
    row.param[9]	 =   -0.00378;
    row.param[10]	 =    0.00408;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001074151; // ;
    row.dparam[1]	 = 0.002166887;
    row.dparam[2]	 = 0.002022721;
    row.dparam[3]	 = 0.00199985;
    row.dparam[4]	 = 0.001775049;
    row.dparam[5]	 = 0.001691981;
    row.dparam[6]	 = 0.001420422;
    row.dparam[7]	 = 0.001306981;
    row.dparam[8]	 = 0.001018725;
    row.dparam[9]	 = 0.0009141663;
    row.dparam[10]	 =    0.00057;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4309",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         97; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =    0.02857; // ;
    row.param[1]	 =    -0.0348;
    row.param[2]	 =    0.00284;
    row.param[3]	 =   -0.00345;
    row.param[4]	 =   -0.00671;
    row.param[5]	 =     0.0024;
    row.param[6]	 =   -0.00169;
    row.param[7]	 =     0.0047;
    row.param[8]	 =   -0.00711;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001574929; // ;
    row.dparam[1]	 = 0.002715769;
    row.dparam[2]	 =    0.00222;
    row.dparam[3]	 =    0.00203;
    row.dparam[4]	 =    0.00203;
    row.dparam[5]	 =    0.00176;
    row.dparam[6]	 =     0.0017;
    row.dparam[7]	 =    0.00128;
    row.dparam[8]	 =     0.0012;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3110",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         98; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     0.0047; // ;
    row.param[1]	 =    0.01095;
    row.param[2]	 =    0.01586;
    row.param[3]	 =    0.00921;
    row.param[4]	 =    0.00179;
    row.param[5]	 =    0.00368;
    row.param[6]	 =   -0.00206;
    row.param[7]	 =    0.00527;
    row.param[8]	 =     0.0007;
    row.param[9]	 =    0.00348;
    row.param[10]	 =    0.00249;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009604166; // ;
    row.dparam[1]	 = 0.00193644;
    row.dparam[2]	 = 0.001811077;
    row.dparam[3]	 =    0.00178;
    row.dparam[4]	 = 0.001607514;
    row.dparam[5]	 = 0.001526106;
    row.dparam[6]	 = 0.00129769;
    row.dparam[7]	 = 0.001192309;
    row.dparam[8]	 = 0.0009305912;
    row.dparam[9]	 =    0.00078;
    row.dparam[10]	 =    0.00052;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3110",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =         99; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    0.02739; // ;
    row.param[1]	 =   -0.03304;
    row.param[2]	 =   -0.02313;
    row.param[3]	 =   -0.00985;
    row.param[4]	 =   -0.01075;
    row.param[5]	 =   -0.00021;
    row.param[6]	 =    -0.0092;
    row.param[7]	 =    0.00464;
    row.param[8]	 =   -0.00472;
    row.param[9]	 =    0.00232;
    row.param[10]	 =   -0.00466;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001731647; // ;
    row.dparam[1]	 = 0.003092604;
    row.dparam[2]	 = 0.003134996;
    row.dparam[3]	 = 0.002896636;
    row.dparam[4]	 = 0.002830194;
    row.dparam[5]	 = 0.002471214;
    row.dparam[6]	 = 0.002374279;
    row.dparam[7]	 = 0.001894888;
    row.dparam[8]	 =    0.00146;
    row.dparam[9]	 =    0.00102;
    row.dparam[10]	 =    0.00095;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3210",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        100; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00752; // ;
    row.param[1]	 =    0.00627;
    row.param[2]	 =    0.01627;
    row.param[3]	 =    0.01022;
    row.param[4]	 =    0.00294;
    row.param[5]	 =    0.00448;
    row.param[6]	 =   -0.00166;
    row.param[7]	 =    0.00498;
    row.param[8]	 =    0.00339;
    row.param[9]	 =    0.00271;
    row.param[10]	 =    0.00303;
    row.param[11]	 =     0.0003;
    row.dparam[0]	 = 0.001166919; // ;
    row.dparam[1]	 = 0.002411493;
    row.dparam[2]	 = 0.002192442;
    row.dparam[3]	 = 0.002206354;
    row.dparam[4]	 = 0.001937679;
    row.dparam[5]	 = 0.001895099;
    row.dparam[6]	 = 0.001562722;
    row.dparam[7]	 = 0.001484924;
    row.dparam[8]	 = 0.001124322;
    row.dparam[9]	 = 0.001039471;
    row.dparam[10]	 = 0.0007071068;
    row.dparam[11]	 =    0.00046;
 memcpy(&row.Comment,"duuP3210",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        101; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.04509; // ;
    row.param[1]	 =   -0.03568;
    row.param[2]	 =   -0.01391;
    row.param[3]	 =   -0.00488;
    row.param[4]	 =   -0.00159;
    row.param[5]	 =    0.00395;
    row.param[6]	 =   -0.00025;
    row.param[7]	 =    0.00893;
    row.param[8]	 =   -0.00707;
    row.param[9]	 =     0.0101;
    row.param[10]	 =   -0.00497;
    row.param[11]	 =    0.00351;
    row.dparam[0]	 = 0.001982952; // ;
    row.dparam[1]	 = 0.004132953;
    row.dparam[2]	 = 0.003735104;
    row.dparam[3]	 = 0.003768474;
    row.dparam[4]	 = 0.003294814;
    row.dparam[5]	 = 0.00325819;
    row.dparam[6]	 = 0.002640549;
    row.dparam[7]	 = 0.002570195;
    row.dparam[8]	 = 0.00194651;
    row.dparam[9]	 = 0.001888147;
    row.dparam[10]	 = 0.001235637;
    row.dparam[11]	 =     0.0007;
 memcpy(&row.Comment,"duuP3310",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        102; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =      0.013; // ;
    row.param[1]	 =   -0.00076;
    row.param[2]	 =    0.02292;
    row.param[3]	 =    0.00297;
    row.param[4]	 =    0.00786;
    row.param[5]	 =   -0.00258;
    row.param[6]	 =    -0.0007;
    row.param[7]	 =     0.0001;
    row.param[8]	 =    0.00146;
    row.param[9]	 =   -0.00019;
    row.param[10]	 =    0.00154;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001390072; // ;
    row.dparam[1]	 = 0.002914893;
    row.dparam[2]	 = 0.002622747;
    row.dparam[3]	 = 0.002689405;
    row.dparam[4]	 = 0.002322972;
    row.dparam[5]	 = 0.002340534;
    row.dparam[6]	 = 0.00189082;
    row.dparam[7]	 = 0.001867994;
    row.dparam[8]	 = 0.001399214;
    row.dparam[9]	 = 0.001339328;
    row.dparam[10]	 = 0.0008348653;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3310",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        103; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00178; // ;
    row.param[1]	 =   -0.01233;
    row.param[2]	 =   -0.00737;
    row.param[3]	 =    0.00352;
    row.param[4]	 =    -0.0096;
    row.param[5]	 =    0.00416;
    row.param[6]	 =   -0.00585;
    row.param[7]	 =    0.00359;
    row.param[8]	 =   -0.00103;
    row.param[9]	 =    0.00293;
    row.param[10]	 =    0.00039;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008628441; // ;
    row.dparam[1]	 = 0.001702733;
    row.dparam[2]	 = 0.001601031;
    row.dparam[3]	 = 0.001567833;
    row.dparam[4]	 = 0.001422287;
    row.dparam[5]	 = 0.001341529;
    row.dparam[6]	 = 0.001096586;
    row.dparam[7]	 = 0.001008464;
    row.dparam[8]	 = 0.000805295;
    row.dparam[9]	 =    0.00067;
    row.dparam[10]	 =    0.00045;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3410",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        104; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01016; // ;
    row.param[1]	 =    0.03592;
    row.param[2]	 =   -0.00459;
    row.param[3]	 =   -0.00056;
    row.param[4]	 =   -0.00416;
    row.param[5]	 =   -0.00284;
    row.param[6]	 =    0.00039;
    row.param[7]	 =   -0.00604;
    row.param[8]	 =    0.00282;
    row.param[9]	 =   -0.00579;
    row.param[10]	 =    0.00059;
    row.param[11]	 =   -0.00152;
    row.dparam[0]	 = 0.001567004; // ;
    row.dparam[1]	 = 0.003214312;
    row.dparam[2]	 = 0.00294328;
    row.dparam[3]	 = 0.002970757;
    row.dparam[4]	 = 0.00257175;
    row.dparam[5]	 = 0.002541968;
    row.dparam[6]	 = 0.002097117;
    row.dparam[7]	 = 0.002015763;
    row.dparam[8]	 = 0.001524664;
    row.dparam[9]	 = 0.001443745;
    row.dparam[10]	 = 0.0009643132;
    row.dparam[11]	 =    0.00055;
 memcpy(&row.Comment,"duuP3410",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        105; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00624; // ;
    row.param[1]	 =   -0.00757;
    row.param[2]	 =    -0.0041;
    row.param[3]	 =     -0.001;
    row.param[4]	 =   -0.00545;
    row.param[5]	 =   -0.00101;
    row.param[6]	 =   -0.00281;
    row.param[7]	 =     0.0016;
    row.param[8]	 =   -0.00076;
    row.param[9]	 =    0.00058;
    row.param[10]	 =    0.00016;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001092428; // ;
    row.dparam[1]	 = 0.002193741;
    row.dparam[2]	 = 0.00201261;
    row.dparam[3]	 = 0.00201261;
    row.dparam[4]	 = 0.001781404;
    row.dparam[5]	 = 0.001753112;
    row.dparam[6]	 = 0.001440104;
    row.dparam[7]	 = 0.001285146;
    row.dparam[8]	 =    0.00093;
    row.dparam[9]	 =    0.00087;
    row.dparam[10]	 =    0.00059;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3510",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        106; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =    0.02638; // ;
    row.param[1]	 =    0.02123;
    row.param[2]	 =      0.005;
    row.param[3]	 =    0.00702;
    row.param[4]	 =    0.00359;
    row.param[5]	 =    0.00681;
    row.param[6]	 =   -0.00012;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0003944617; // ;
    row.dparam[1]	 = 0.0007513322;
    row.dparam[2]	 =    0.00059;
    row.dparam[3]	 =     0.0006;
    row.dparam[4]	 =     0.0005;
    row.dparam[5]	 =    0.00049;
    row.dparam[6]	 =    0.00038;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3510",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        107; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =    0.00478; // ;
    row.param[1]	 =   -0.01282;
    row.param[2]	 =   -0.00532;
    row.param[3]	 =    -0.0045;
    row.param[4]	 =   -0.00795;
    row.param[5]	 =   -0.00432;
    row.param[6]	 =   -0.00471;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005359104; // ;
    row.dparam[1]	 = 0.0009944345;
    row.dparam[2]	 = 0.000893868;
    row.dparam[3]	 = 0.0008570881;
    row.dparam[4]	 =    0.00053;
    row.dparam[5]	 =    0.00055;
    row.dparam[6]	 =    0.00042;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3610",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01026; // ;
    row.param[1]	 =    0.15615;
    row.param[2]	 =   -0.04054;
    row.param[3]	 =    0.11457;
    row.param[4]	 =    0.03236;
    row.param[5]	 =    0.01546;
    row.param[6]	 =    0.03328;
    row.param[7]	 =    0.09753;
    row.param[8]	 =    -0.1983;
    row.param[9]	 =    0.34833;
    row.param[10]	 =   -0.28114;
    row.param[11]	 =          0;
    row.dparam[0]	 =    0.00253; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =      1e-05;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        108; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.07841; // ;
    row.param[1]	 =   -0.05837;
    row.param[2]	 =    -0.0739;
    row.param[3]	 =   -0.02823;
    row.param[4]	 =   -0.02421;
    row.param[5]	 =   -0.00412;
    row.param[6]	 =   -0.01633;
    row.param[7]	 =   -0.00841;
    row.param[8]	 =   -0.01206;
    row.param[9]	 =   -0.00732;
    row.param[10]	 =   -0.02247;
    row.param[11]	 =    0.00034;
    row.dparam[0]	 = 0.002223556; // ;
    row.dparam[1]	 = 0.004596433;
    row.dparam[2]	 = 0.004165921;
    row.dparam[3]	 = 0.004172062;
    row.dparam[4]	 = 0.003579763;
    row.dparam[5]	 = 0.003486574;
    row.dparam[6]	 = 0.00281249;
    row.dparam[7]	 = 0.002681306;
    row.dparam[8]	 = 0.001981843;
    row.dparam[9]	 = 0.001864966;
    row.dparam[10]	 = 0.001189454;
    row.dparam[11]	 =    0.00065;
 memcpy(&row.Comment,"duuP4111",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        109; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.09405; // ;
    row.param[1]	 =    0.04447;
    row.param[2]	 =    0.07582;
    row.param[3]	 =    0.01007;
    row.param[4]	 =     0.0163;
    row.param[5]	 =   -0.00753;
    row.param[6]	 =    0.01093;
    row.param[7]	 =   -0.00694;
    row.param[8]	 =    0.00921;
    row.param[9]	 =   -0.00217;
    row.param[10]	 =     0.0201;
    row.param[11]	 =   -0.00395;
    row.dparam[0]	 = 0.00223448; // ;
    row.dparam[1]	 = 0.004672184;
    row.dparam[2]	 = 0.004215163;
    row.dparam[3]	 = 0.004273102;
    row.dparam[4]	 = 0.003660792;
    row.dparam[5]	 = 0.003626982;
    row.dparam[6]	 =  0.0029272;
    row.dparam[7]	 = 0.002791863;
    row.dparam[8]	 = 0.00206245;
    row.dparam[9]	 = 0.001903707;
    row.dparam[10]	 = 0.001230731;
    row.dparam[11]	 =    0.00066;
 memcpy(&row.Comment,"duuP4111",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        110; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.04458; // ;
    row.param[1]	 =    0.00827;
    row.param[2]	 =   -0.06252;
    row.param[3]	 =   -0.01964;
    row.param[4]	 =   -0.00813;
    row.param[5]	 =   -0.00481;
    row.param[6]	 =    0.00068;
    row.param[7]	 =   -0.00945;
    row.param[8]	 =   -0.00111;
    row.param[9]	 =   -0.00823;
    row.param[10]	 =   -0.00994;
    row.param[11]	 =   -0.00136;
    row.dparam[0]	 = 0.001755591; // ;
    row.dparam[1]	 = 0.00360673;
    row.dparam[2]	 = 0.003292932;
    row.dparam[3]	 = 0.003283733;
    row.dparam[4]	 = 0.002857289;
    row.dparam[5]	 = 0.002765393;
    row.dparam[6]	 = 0.002273082;
    row.dparam[7]	 = 0.002160093;
    row.dparam[8]	 = 0.001645691;
    row.dparam[9]	 = 0.001512746;
    row.dparam[10]	 = 0.001022008;
    row.dparam[11]	 =    0.00054;
 memcpy(&row.Comment,"duuP4211",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        111; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.0827; // ;
    row.param[1]	 =    0.02293;
    row.param[2]	 =    0.05783;
    row.param[3]	 =     0.0081;
    row.param[4]	 =    0.00062;
    row.param[5]	 =   -0.00934;
    row.param[6]	 =   -0.00791;
    row.param[7]	 =   -0.00128;
    row.param[8]	 =   -0.00535;
    row.param[9]	 =    0.00078;
    row.param[10]	 =    0.00869;
    row.param[11]	 =   -0.00166;
    row.dparam[0]	 = 0.002281513; // ;
    row.dparam[1]	 = 0.004643469;
    row.dparam[2]	 = 0.004268618;
    row.dparam[3]	 = 0.004233639;
    row.dparam[4]	 = 0.003713556;
    row.dparam[5]	 = 0.003597624;
    row.dparam[6]	 = 0.002980067;
    row.dparam[7]	 = 0.002807953;
    row.dparam[8]	 = 0.002167464;
    row.dparam[9]	 = 0.00198265;
    row.dparam[10]	 =  0.0013005;
    row.dparam[11]	 =    0.00069;
 memcpy(&row.Comment,"duuP4211",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        112; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.07418; // ;
    row.param[1]	 =   -0.00445;
    row.param[2]	 =    -0.0628;
    row.param[3]	 =   -0.01197;
    row.param[4]	 =   -0.00578;
    row.param[5]	 =     0.0033;
    row.param[6]	 =    0.00355;
    row.param[7]	 =   -0.00323;
    row.param[8]	 =    0.00173;
    row.param[9]	 =   -0.00507;
    row.param[10]	 =   -0.01043;
    row.param[11]	 =      0.001;
    row.dparam[0]	 = 0.001774289; // ;
    row.dparam[1]	 = 0.003645449;
    row.dparam[2]	 = 0.003318825;
    row.dparam[3]	 = 0.003310604;
    row.dparam[4]	 = 0.002879097;
    row.dparam[5]	 = 0.002795854;
    row.dparam[6]	 = 0.002287531;
    row.dparam[7]	 = 0.002176718;
    row.dparam[8]	 = 0.001639695;
    row.dparam[9]	 = 0.001518519;
    row.dparam[10]	 = 0.001010396;
    row.dparam[11]	 =    0.00053;
 memcpy(&row.Comment,"duuP4311",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        113; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.08097; // ;
    row.param[1]	 =    0.03148;
    row.param[2]	 =    0.06026;
    row.param[3]	 =    0.00967;
    row.param[4]	 =    0.00172;
    row.param[5]	 =   -0.00953;
    row.param[6]	 =    -0.0056;
    row.param[7]	 =      2e-05;
    row.param[8]	 =   -0.00121;
    row.param[9]	 =    0.00081;
    row.param[10]	 =    0.01455;
    row.param[11]	 =   -0.00346;
    row.dparam[0]	 = 0.001819808; // ;
    row.dparam[1]	 = 0.003753851;
    row.dparam[2]	 = 0.003437863;
    row.dparam[3]	 = 0.003442296;
    row.dparam[4]	 = 0.002993092;
    row.dparam[5]	 = 0.002915973;
    row.dparam[6]	 = 0.002390774;
    row.dparam[7]	 = 0.002246175;
    row.dparam[8]	 = 0.001697645;
    row.dparam[9]	 = 0.001536685;
    row.dparam[10]	 = 0.001010594;
    row.dparam[11]	 =    0.00053;
 memcpy(&row.Comment,"duuP4311",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        114; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02032; // ;
    row.param[1]	 =    0.00796;
    row.param[2]	 =    0.03588;
    row.param[3]	 =   -0.02454;
    row.param[4]	 =    0.02281;
    row.param[5]	 =    0.00455;
    row.param[6]	 =    0.01587;
    row.param[7]	 =     0.0149;
    row.param[8]	 =    0.00236;
    row.param[9]	 =     0.0096;
    row.param[10]	 =   -0.00035;
    row.param[11]	 =    0.00134;
    row.dparam[0]	 = 0.001818818; // ;
    row.dparam[1]	 = 0.004183886;
    row.dparam[2]	 = 0.003441511;
    row.dparam[3]	 = 0.003872325;
    row.dparam[4]	 = 0.002997282;
    row.dparam[5]	 = 0.00326619;
    row.dparam[6]	 = 0.002391527;
    row.dparam[7]	 = 0.002538307;
    row.dparam[8]	 = 0.001756303;
    row.dparam[9]	 = 0.001834639;
    row.dparam[10]	 = 0.001114406;
    row.dparam[11]	 =    0.00064;
 memcpy(&row.Comment,"duuP4411",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        115; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.04426; // ;
    row.param[1]	 =    0.07298;
    row.param[2]	 =   -0.02613;
    row.param[3]	 =    0.04183;
    row.param[4]	 =   -0.01472;
    row.param[5]	 =    0.00636;
    row.param[6]	 =   -0.02244;
    row.param[7]	 =   -0.00334;
    row.param[8]	 =   -0.00491;
    row.param[9]	 =   -0.00622;
    row.param[10]	 =   -0.00551;
    row.param[11]	 =   -0.00181;
    row.dparam[0]	 = 0.001862391; // ;
    row.dparam[1]	 = 0.004082279;
    row.dparam[2]	 = 0.003508091;
    row.dparam[3]	 = 0.00378086;
    row.dparam[4]	 = 0.003056894;
    row.dparam[5]	 = 0.003213005;
    row.dparam[6]	 = 0.002422664;
    row.dparam[7]	 = 0.002506332;
    row.dparam[8]	 = 0.001767767;
    row.dparam[9]	 = 0.001809889;
    row.dparam[10]	 = 0.001114495;
    row.dparam[11]	 =    0.00067;
 memcpy(&row.Comment,"duuP4411",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        116; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01602; // ;
    row.param[1]	 =    0.00108;
    row.param[2]	 =    0.01746;
    row.param[3]	 =   -0.03725;
    row.param[4]	 =    0.00667;
    row.param[5]	 =   -0.00388;
    row.param[6]	 =    0.00677;
    row.param[7]	 =     0.0082;
    row.param[8]	 =   -0.00631;
    row.param[9]	 =    0.00305;
    row.param[10]	 =   -0.00489;
    row.param[11]	 =   -0.00153;
    row.dparam[0]	 = 0.002442478; // ;
    row.dparam[1]	 = 0.005375891;
    row.dparam[2]	 = 0.00456988;
    row.dparam[3]	 = 0.004886829;
    row.dparam[4]	 = 0.003868915;
    row.dparam[5]	 = 0.004028225;
    row.dparam[6]	 = 0.002988746;
    row.dparam[7]	 = 0.00306183;
    row.dparam[8]	 = 0.001980707;
    row.dparam[9]	 = 0.002086265;
    row.dparam[10]	 = 0.001230366;
    row.dparam[11]	 =    0.00088;
 memcpy(&row.Comment,"duuP4511",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        117; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.0315; // ;
    row.param[1]	 =    0.07134;
    row.param[2]	 =   -0.03026;
    row.param[3]	 =    0.04235;
    row.param[4]	 =   -0.02193;
    row.param[5]	 =    0.00694;
    row.param[6]	 =    -0.0299;
    row.param[7]	 =   -0.00527;
    row.param[8]	 =   -0.01119;
    row.param[9]	 =   -0.00337;
    row.param[10]	 =   -0.00435;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001843638; // ;
    row.dparam[1]	 = 0.004362213;
    row.dparam[2]	 = 0.003428775;
    row.dparam[3]	 = 0.003948848;
    row.dparam[4]	 = 0.002910275;
    row.dparam[5]	 = 0.003252522;
    row.dparam[6]	 = 0.002260155;
    row.dparam[7]	 = 0.002466962;
    row.dparam[8]	 = 0.00159242;
    row.dparam[9]	 = 0.001530751;
    row.dparam[10]	 =    0.00076;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP4511",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        118; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.17044; // ;
    row.param[1]	 =   -0.14718;
    row.param[2]	 =    0.01902;
    row.param[3]	 =   -0.02445;
    row.param[4]	 =    0.00936;
    row.param[5]	 =    0.00467;
    row.param[6]	 =    0.00385;
    row.param[7]	 =    0.01307;
    row.param[8]	 =   -0.00501;
    row.param[9]	 =    0.01192;
    row.param[10]	 =     -2e-05;
    row.param[11]	 =    0.00607;
    row.dparam[0]	 = 0.002189543; // ;
    row.dparam[1]	 = 0.004828519;
    row.dparam[2]	 = 0.004114377;
    row.dparam[3]	 = 0.00446167;
    row.dparam[4]	 = 0.00356588;
    row.dparam[5]	 = 0.003786146;
    row.dparam[6]	 = 0.00281984;
    row.dparam[7]	 = 0.002971363;
    row.dparam[8]	 = 0.002084922;
    row.dparam[9]	 = 0.00219016;
    row.dparam[10]	 = 0.001346811;
    row.dparam[11]	 =    0.00085;
 memcpy(&row.Comment,"duuP4611",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        119; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          4; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.05669; // ;
    row.param[1]	 =    0.07592;
    row.param[2]	 =   -0.01173;
    row.param[3]	 =   -0.00403;
    row.param[4]	 =      -0.01;
    row.param[5]	 =     -0.033;
    row.param[6]	 =    -0.0104;
    row.param[7]	 =   -0.02908;
    row.param[8]	 =    0.00587;
    row.param[9]	 =   -0.01965;
    row.param[10]	 =    0.00246;
    row.param[11]	 =   -0.00359;
    row.dparam[0]	 = 0.005335401; // ;
    row.dparam[1]	 = 0.01265926;
    row.dparam[2]	 = 0.01003004;
    row.dparam[3]	 = 0.01128709;
    row.dparam[4]	 = 0.008373679;
    row.dparam[5]	 = 0.009095741;
    row.dparam[6]	 = 0.006211811;
    row.dparam[7]	 = 0.006569665;
    row.dparam[8]	 = 0.004055971;
    row.dparam[9]	 = 0.004210333;
    row.dparam[10]	 = 0.002144015;
    row.dparam[11]	 =    0.00127;
 memcpy(&row.Comment,"duuP4611",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        120; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =   -0.01897; // ;
    row.param[1]	 =   -0.01425;
    row.param[2]	 =   -0.00218;
    row.param[3]	 =    0.00642;
    row.param[4]	 =   -0.00121;
    row.param[5]	 =    0.00604;
    row.param[6]	 =   -0.00399;
    row.param[7]	 =    0.00687;
    row.param[8]	 =   -0.00696;
    row.param[9]	 =    0.00426;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001041393; // ;
    row.dparam[1]	 = 0.002001225;
    row.dparam[2]	 = 0.001941649;
    row.dparam[3]	 = 0.001831748;
    row.dparam[4]	 = 0.001697793;
    row.dparam[5]	 = 0.00153522;
    row.dparam[6]	 = 0.001368211;
    row.dparam[7]	 = 0.00115434;
    row.dparam[8]	 = 0.0009765244;
    row.dparam[9]	 = 0.0007516648;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP3112",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        121; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.02087; // ;
    row.param[1]	 =    0.02342;
    row.param[2]	 =    0.00608;
    row.param[3]	 =    0.00647;
    row.param[4]	 =    0.00088;
    row.param[5]	 =    0.00251;
    row.param[6]	 =    0.00351;
    row.param[7]	 =   -0.00114;
    row.param[8]	 =    0.00646;
    row.param[9]	 =   -0.00528;
    row.param[10]	 =    0.00516;
    row.param[11]	 =   -0.00072;
    row.dparam[0]	 = 0.001992461; // ;
    row.dparam[1]	 = 0.004065636;
    row.dparam[2]	 = 0.003777142;
    row.dparam[3]	 = 0.003742513;
    row.dparam[4]	 = 0.003327011;
    row.dparam[5]	 = 0.003188197;
    row.dparam[6]	 =  0.0026921;
    row.dparam[7]	 = 0.002472125;
    row.dparam[8]	 = 0.001877738;
    row.dparam[9]	 = 0.001675052;
    row.dparam[10]	 = 0.001178134;
    row.dparam[11]	 =    0.00057;
 memcpy(&row.Comment,"duuP3112",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        122; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01371; // ;
    row.param[1]	 =   -0.00986;
    row.param[2]	 =    0.00107;
    row.param[3]	 =    0.00422;
    row.param[4]	 =    0.00042;
    row.param[5]	 =    0.00431;
    row.param[6]	 =   -0.00298;
    row.param[7]	 =    0.00558;
    row.param[8]	 =   -0.00611;
    row.param[9]	 =    0.00658;
    row.param[10]	 =    -0.0034;
    row.param[11]	 =    0.00073;
    row.dparam[0]	 = 0.001548096; // ;
    row.dparam[1]	 = 0.00316528;
    row.dparam[2]	 = 0.002945811;
    row.dparam[3]	 = 0.002922499;
    row.dparam[4]	 = 0.002593164;
    row.dparam[5]	 = 0.002488956;
    row.dparam[6]	 = 0.002078798;
    row.dparam[7]	 = 0.001940103;
    row.dparam[8]	 = 0.001489765;
    row.dparam[9]	 =  0.0013454;
    row.dparam[10]	 = 0.0009412226;
    row.dparam[11]	 =    0.00047;
 memcpy(&row.Comment,"duuP3212",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        123; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00473; // ;
    row.param[1]	 =     0.0158;
    row.param[2]	 =    0.01204;
    row.param[3]	 =    0.00604;
    row.param[4]	 =    0.00408;
    row.param[5]	 =    0.00251;
    row.param[6]	 =    0.00498;
    row.param[7]	 =   -0.00121;
    row.param[8]	 =    0.00757;
    row.param[9]	 =   -0.00479;
    row.param[10]	 =    0.00344;
    row.param[11]	 =   -0.00125;
    row.dparam[0]	 = 0.001796246; // ;
    row.dparam[1]	 = 0.003644297;
    row.dparam[2]	 = 0.003407462;
    row.dparam[3]	 = 0.003372833;
    row.dparam[4]	 = 0.003020381;
    row.dparam[5]	 = 0.002887456;
    row.dparam[6]	 = 0.002436801;
    row.dparam[7]	 = 0.002234525;
    row.dparam[8]	 = 0.001726355;
    row.dparam[9]	 = 0.001518519;
    row.dparam[10]	 = 0.001079676;
    row.dparam[11]	 =    0.00051;
 memcpy(&row.Comment,"duuP3212",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        124; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01293; // ;
    row.param[1]	 =   -0.00822;
    row.param[2]	 =    0.00018;
    row.param[3]	 =    0.00148;
    row.param[4]	 =   -0.00013;
    row.param[5]	 =    0.00172;
    row.param[6]	 =   -0.00429;
    row.param[7]	 =    0.00457;
    row.param[8]	 =   -0.00764;
    row.param[9]	 =    0.00484;
    row.param[10]	 =     -0.005;
    row.param[11]	 =    0.00071;
    row.dparam[0]	 = 0.001557723; // ;
    row.dparam[1]	 = 0.003172412;
    row.dparam[2]	 = 0.002947083;
    row.dparam[3]	 = 0.002916745;
    row.dparam[4]	 = 0.002597941;
    row.dparam[5]	 = 0.00248135;
    row.dparam[6]	 = 0.002070266;
    row.dparam[7]	 = 0.001912721;
    row.dparam[8]	 = 0.001473126;
    row.dparam[9]	 = 0.00132246;
    row.dparam[10]	 = 0.0009295698;
    row.dparam[11]	 =    0.00045;
 memcpy(&row.Comment,"duuP3312",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        125; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00386; // ;
    row.param[1]	 =    0.01636;
    row.param[2]	 =    0.00977;
    row.param[3]	 =    0.00647;
    row.param[4]	 =     0.0038;
    row.param[5]	 =    0.00228;
    row.param[6]	 =    0.00854;
    row.param[7]	 =    0.00233;
    row.param[8]	 =    0.00981;
    row.param[9]	 =   -0.00026;
    row.param[10]	 =    0.00647;
    row.param[11]	 =    0.00042;
    row.dparam[0]	 = 0.001985623; // ;
    row.dparam[1]	 = 0.004011695;
    row.dparam[2]	 = 0.003762951;
    row.dparam[3]	 = 0.003685119;
    row.dparam[4]	 = 0.003301712;
    row.dparam[5]	 = 0.003120801;
    row.dparam[6]	 = 0.002634692;
    row.dparam[7]	 = 0.002385561;
    row.dparam[8]	 = 0.001824938;
    row.dparam[9]	 = 0.001588049;
    row.dparam[10]	 = 0.001102951;
    row.dparam[11]	 =    0.00051;
 memcpy(&row.Comment,"duuP3312",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          2; // ;
    row.layer	 =          3; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        126; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =   -0.03234; // ;
    row.param[1]	 =    0.00887;
    row.param[2]	 =   -0.00422;
    row.param[3]	 =    0.00629;
    row.param[4]	 =   -0.00505;
    row.param[5]	 =    0.00526;
    row.param[6]	 =   -0.00642;
    row.param[7]	 =    0.00258;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =    0.00255; // ;
    row.dparam[1]	 =    0.00432;
    row.dparam[2]	 =     0.0046;
    row.dparam[3]	 =    0.00361;
    row.dparam[4]	 =     0.0036;
    row.dparam[5]	 =    0.00247;
    row.dparam[6]	 =    0.00232;
    row.dparam[7]	 =    0.00134;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6101",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        127; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.08083; // ;
    row.param[1]	 =   -0.19756;
    row.param[2]	 =    0.17866;
    row.param[3]	 =   -0.19953;
    row.param[4]	 =    0.15352;
    row.param[5]	 =    -0.1481;
    row.param[6]	 =    0.10632;
    row.param[7]	 =   -0.09066;
    row.param[8]	 =    0.06159;
    row.param[9]	 =   -0.04747;
    row.param[10]	 =     0.0239;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.004446246; // ;
    row.dparam[1]	 = 0.009496852;
    row.dparam[2]	 = 0.008255435;
    row.dparam[3]	 = 0.008336834;
    row.dparam[4]	 = 0.006643109;
    row.dparam[5]	 = 0.006378236;
    row.dparam[6]	 = 0.004592929;
    row.dparam[7]	 = 0.004297744;
    row.dparam[8]	 = 0.002755358;
    row.dparam[9]	 = 0.002567431;
    row.dparam[10]	 = 0.001303572;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6101",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        128; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03046; // ;
    row.param[1]	 =    0.00343;
    row.param[2]	 =     0.0082;
    row.param[3]	 =    0.00457;
    row.param[4]	 =    0.00608;
    row.param[5]	 =    0.01168;
    row.param[6]	 =    0.00656;
    row.param[7]	 =    0.00388;
    row.param[8]	 =    0.00238;
    row.param[9]	 =    0.00486;
    row.param[10]	 =     0.0012;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00382697; // ;
    row.dparam[1]	 =    0.00836;
    row.dparam[2]	 =    0.00712;
    row.dparam[3]	 =    0.00737;
    row.dparam[4]	 =    0.00576;
    row.dparam[5]	 =    0.00569;
    row.dparam[6]	 =      0.004;
    row.dparam[7]	 =    0.00383;
    row.dparam[8]	 =    0.00239;
    row.dparam[9]	 =    0.00227;
    row.dparam[10]	 =    0.00118;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6201",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        129; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03932; // ;
    row.param[1]	 =    0.03304;
    row.param[2]	 =   -0.00871;
    row.param[3]	 =    0.01691;
    row.param[4]	 =   -0.00646;
    row.param[5]	 =    0.01475;
    row.param[6]	 =    0.00187;
    row.param[7]	 =    0.01804;
    row.param[8]	 =    0.00343;
    row.param[9]	 =    0.01239;
    row.param[10]	 =    0.00124;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.003424354; // ;
    row.dparam[1]	 = 0.007573223;
    row.dparam[2]	 = 0.006479329;
    row.dparam[3]	 = 0.006776931;
    row.dparam[4]	 = 0.005312052;
    row.dparam[5]	 = 0.005275273;
    row.dparam[6]	 = 0.003728083;
    row.dparam[7]	 = 0.003635891;
    row.dparam[8]	 = 0.002409191;
    row.dparam[9]	 = 0.002265568;
    row.dparam[10]	 = 0.001196035;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6201",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        130; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =    0.00028; // ;
    row.param[1]	 =    0.00014;
    row.param[2]	 =   -0.00526;
    row.param[3]	 =   -0.01811;
    row.param[4]	 =     -1e-05;
    row.param[5]	 =   -0.00568;
    row.param[6]	 =    0.00029;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001143897; // ;
    row.dparam[1]	 = 0.002580543;
    row.dparam[2]	 = 0.001958188;
    row.dparam[3]	 = 0.002156757;
    row.dparam[4]	 =    0.00143;
    row.dparam[5]	 =    0.00157;
    row.dparam[6]	 =    0.00101;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6301",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        131; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00447; // ;
    row.param[1]	 =    0.03304;
    row.param[2]	 =    -0.0071;
    row.param[3]	 =   -0.00788;
    row.param[4]	 =   -0.00264;
    row.param[5]	 =   -0.00083;
    row.param[6]	 =   -0.00486;
    row.param[7]	 =   -0.00109;
    row.param[8]	 =   -0.00087;
    row.param[9]	 =   -0.00257;
    row.param[10]	 =   -0.00141;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.002061723; // ;
    row.dparam[1]	 = 0.004505785;
    row.dparam[2]	 = 0.003841393;
    row.dparam[3]	 = 0.004085413;
    row.dparam[4]	 = 0.003293342;
    row.dparam[5]	 = 0.003442456;
    row.dparam[6]	 = 0.002614001;
    row.dparam[7]	 = 0.002666027;
    row.dparam[8]	 = 0.001855398;
    row.dparam[9]	 = 0.001892829;
    row.dparam[10]	 = 0.001210826;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6401",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        132; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.04689; // ;
    row.param[1]	 =    0.00509;
    row.param[2]	 =    0.03564;
    row.param[3]	 =    0.02408;
    row.param[4]	 =    0.02729;
    row.param[5]	 =    0.02034;
    row.param[6]	 =    0.02323;
    row.param[7]	 =    0.01524;
    row.param[8]	 =    0.01263;
    row.param[9]	 =    0.01099;
    row.param[10]	 =      9e-05;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.003634102; // ;
    row.dparam[1]	 = 0.007265163;
    row.dparam[2]	 = 0.006249504;
    row.dparam[3]	 = 0.006488952;
    row.dparam[4]	 = 0.005643129;
    row.dparam[5]	 = 0.005812753;
    row.dparam[6]	 = 0.005150233;
    row.dparam[7]	 = 0.005212543;
    row.dparam[8]	 = 0.004244172;
    row.dparam[9]	 = 0.003975223;
    row.dparam[10]	 =    0.00201;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6401",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        133; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          4; // ;
    row.param[0]	 =   -0.01921; // ;
    row.param[1]	 =    0.00593;
    row.param[2]	 =   -0.00166;
    row.param[3]	 =    0.00061;
    row.param[4]	 =    0.00308;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007424958; // ;
    row.dparam[1]	 = 0.001329097;
    row.dparam[2]	 = 0.001174564;
    row.dparam[3]	 =    0.00068;
    row.dparam[4]	 =    0.00069;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6501",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        134; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01648; // ;
    row.param[1]	 =    0.00579;
    row.param[2]	 =   -0.00521;
    row.param[3]	 =   -0.01127;
    row.param[4]	 =   -0.00615;
    row.param[5]	 =   -0.00919;
    row.param[6]	 =   -0.00507;
    row.param[7]	 =   -0.00314;
    row.param[8]	 =   -0.00459;
    row.param[9]	 =   -0.00375;
    row.param[10]	 =   -0.00203;
    row.param[11]	 =   -0.00141;
    row.dparam[0]	 = 0.001419613; // ;
    row.dparam[1]	 = 0.002924654;
    row.dparam[2]	 = 0.002588919;
    row.dparam[3]	 =  0.0025866;
    row.dparam[4]	 = 0.002195837;
    row.dparam[5]	 = 0.002227285;
    row.dparam[6]	 = 0.001794269;
    row.dparam[7]	 =    0.00163;
    row.dparam[8]	 =    0.00124;
    row.dparam[9]	 =    0.00122;
    row.dparam[10]	 =    0.00083;
    row.dparam[11]	 =    0.00083;
 memcpy(&row.Comment,"duuP6601",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        135; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          6; // ;
    row.param[0]	 =    0.01753; // ;
    row.param[1]	 =    0.00135;
    row.param[2]	 =   -0.00931;
    row.param[3]	 =   -0.00179;
    row.param[4]	 =   -0.00366;
    row.param[5]	 =   -0.00035;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0004875449; // ;
    row.dparam[1]	 =    0.00075;
    row.dparam[2]	 =    0.00075;
    row.dparam[3]	 =    0.00065;
    row.dparam[4]	 =    0.00064;
    row.dparam[5]	 =    0.00046;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6601",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        136; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =    0.00067; // ;
    row.param[1]	 =    -0.0016;
    row.param[2]	 =   -0.00186;
    row.param[3]	 =   -0.00967;
    row.param[4]	 =   -0.00239;
    row.param[5]	 =   -0.00511;
    row.param[6]	 =   -0.00332;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.000852467; // ;
    row.dparam[1]	 =    0.00129;
    row.dparam[2]	 =    0.00114;
    row.dparam[3]	 =    0.00116;
    row.dparam[4]	 =    0.00098;
    row.dparam[5]	 =    0.00095;
    row.dparam[6]	 =    0.00074;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6701",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        137; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          1; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    0.00315; // ;
    row.param[1]	 =    0.00517;
    row.param[2]	 =    0.00087;
    row.param[3]	 =    0.00303;
    row.param[4]	 =    0.00299;
    row.param[5]	 =    0.00386;
    row.param[6]	 =    0.00448;
    row.param[7]	 =    0.00405;
    row.param[8]	 =     0.0025;
    row.param[9]	 =    0.00357;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008947625; // ;
    row.dparam[1]	 = 0.001576927;
    row.dparam[2]	 = 0.001489765;
    row.dparam[3]	 = 0.001320984;
    row.dparam[4]	 = 0.00131103;
    row.dparam[5]	 = 0.001086876;
    row.dparam[6]	 =    0.00102;
    row.dparam[7]	 =     0.0008;
    row.dparam[8]	 =    0.00083;
    row.dparam[9]	 =    0.00054;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6701",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        138; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          5; // ;
    row.param[0]	 =   -0.03866; // ;
    row.param[1]	 =    0.01789;
    row.param[2]	 =    0.00103;
    row.param[3]	 =    0.00069;
    row.param[4]	 =    0.00101;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0003883298; // ;
    row.dparam[1]	 = 0.0007529276;
    row.dparam[2]	 =    0.00053;
    row.dparam[3]	 =    0.00056;
    row.dparam[4]	 =    0.00042;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5102",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        139; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =   -0.06856; // ;
    row.param[1]	 =    0.02664;
    row.param[2]	 =    0.00556;
    row.param[3]	 =    0.00503;
    row.param[4]	 =    0.00643;
    row.param[5]	 =    0.00299;
    row.param[6]	 =    0.00228;
    row.param[7]	 =    0.00026;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006484597; // ;
    row.dparam[1]	 = 0.001028591;
    row.dparam[2]	 = 0.001187013;
    row.dparam[3]	 = 0.0009080198;
    row.dparam[4]	 =  0.0010009;
    row.dparam[5]	 =    0.00065;
    row.dparam[6]	 =    0.00071;
    row.dparam[7]	 =    0.00046;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5202",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        140; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =   -0.07448; // ;
    row.param[1]	 =    0.04999;
    row.param[2]	 =   -0.00615;
    row.param[3]	 =    0.00485;
    row.param[4]	 =    0.00297;
    row.param[5]	 =    0.00525;
    row.param[6]	 =    0.00223;
    row.param[7]	 =    0.00357;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.000762168; // ;
    row.dparam[1]	 = 0.00121758;
    row.dparam[2]	 = 0.001401321;
    row.dparam[3]	 = 0.00105622;
    row.dparam[4]	 = 0.001151347;
    row.dparam[5]	 =    0.00074;
    row.dparam[6]	 =    0.00078;
    row.dparam[7]	 =    0.00046;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5402",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03169; // ;
    row.param[1]	 =   -0.00851;
    row.param[2]	 =   -0.03646;
    row.param[3]	 =    -0.0539;
    row.param[4]	 =    0.04065;
    row.param[5]	 =    0.07422;
    row.param[6]	 =    0.05052;
    row.param[7]	 =   -0.22939;
    row.param[8]	 =    0.08925;
    row.param[9]	 =   -0.07983;
    row.param[10]	 =    0.10699;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.01919909; // ;
    row.dparam[1]	 =    0.03544;
    row.dparam[2]	 =     0.0335;
    row.dparam[3]	 =    0.03203;
    row.dparam[4]	 =    0.02837;
    row.dparam[5]	 =    0.02578;
    row.dparam[6]	 =    0.02068;
    row.dparam[7]	 =    0.01849;
    row.dparam[8]	 =    0.01397;
    row.dparam[9]	 =    0.01241;
    row.dparam[10]	 =    0.00836;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        141; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          3; // ;
    row.param[0]	 =    0.15532; // ;
    row.param[1]	 =   -0.04208;
    row.param[2]	 =    0.00343;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001464855; // ;
    row.dparam[1]	 = 0.00315192;
    row.dparam[2]	 = 0.002173684;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5502",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.36009; // ;
    row.param[1]	 =    0.00268;
    row.param[2]	 =   -0.30795;
    row.param[3]	 =   -0.05676;
    row.param[4]	 =   -0.20846;
    row.param[5]	 =   -0.12312;
    row.param[6]	 =   -0.36981;
    row.param[7]	 =     0.0366;
    row.param[8]	 =   -0.13775;
    row.param[9]	 =   -0.13024;
    row.param[10]	 =   -0.06405;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.01452979; // ;
    row.dparam[1]	 =    0.02295;
    row.dparam[2]	 =    0.02046;
    row.dparam[3]	 =    0.02133;
    row.dparam[4]	 =    0.01817;
    row.dparam[5]	 =    0.01901;
    row.dparam[6]	 =    0.01545;
    row.dparam[7]	 =    0.01546;
    row.dparam[8]	 =    0.01159;
    row.dparam[9]	 =    0.01249;
    row.dparam[10]	 =    0.00866;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        142; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.07661; // ;
    row.param[1]	 =   -0.03287;
    row.param[2]	 =   -0.01964;
    row.param[3]	 =   -0.01219;
    row.param[4]	 =   -0.02399;
    row.param[5]	 =   -0.01314;
    row.param[6]	 =   -0.01574;
    row.param[7]	 =   -0.01057;
    row.param[8]	 =   -0.00728;
    row.param[9]	 =    -0.0081;
    row.param[10]	 =   -0.00154;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.006508195; // ;
    row.dparam[1]	 = 0.01318806;
    row.dparam[2]	 = 0.01178522;
    row.dparam[3]	 =    0.01128;
    row.dparam[4]	 =    0.00955;
    row.dparam[5]	 =    0.00927;
    row.dparam[6]	 =    0.00722;
    row.dparam[7]	 =    0.00679;
    row.dparam[8]	 =    0.00452;
    row.dparam[9]	 =    0.00399;
    row.dparam[10]	 =    0.00203;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5602",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00943; // ;
    row.param[1]	 =   -0.08277;
    row.param[2]	 =    0.07459;
    row.param[3]	 =    0.07605;
    row.param[4]	 =   -0.00736;
    row.param[5]	 =    0.04507;
    row.param[6]	 =    0.04191;
    row.param[7]	 =   -0.08769;
    row.param[8]	 =    0.10316;
    row.param[9]	 =   -0.08612;
    row.param[10]	 =    0.05166;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.007859593; // ;
    row.dparam[1]	 =  0.0153658;
    row.dparam[2]	 = 0.01328493;
    row.dparam[3]	 = 0.01329692;
    row.dparam[4]	 = 0.01197633;
    row.dparam[5]	 = 0.01124856;
    row.dparam[6]	 = 0.00931736;
    row.dparam[7]	 =     0.0075;
    row.dparam[8]	 =     0.0061;
    row.dparam[9]	 =    0.00592;
    row.dparam[10]	 =    0.00393;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =     0.0856; // ;
    row.param[1]	 =   -0.02238;
    row.param[2]	 =    0.01306;
    row.param[3]	 =    0.01574;
    row.param[4]	 =   -0.03638;
    row.param[5]	 =    0.06199;
    row.param[6]	 =   -0.06586;
    row.param[7]	 =    0.06458;
    row.param[8]	 =   -0.05051;
    row.param[9]	 =    0.03111;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.009741175; // ;
    row.dparam[1]	 =    0.01851;
    row.dparam[2]	 =    0.01741;
    row.dparam[3]	 =    0.01524;
    row.dparam[4]	 =    0.01407;
    row.dparam[5]	 =    0.01182;
    row.dparam[6]	 =    0.01076;
    row.dparam[7]	 =    0.00802;
    row.dparam[8]	 =    0.00659;
    row.dparam[9]	 =    0.00378;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          2; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.04881; // ;
    row.param[1]	 =    0.46856;
    row.param[2]	 =    0.20391;
    row.param[3]	 =    0.55554;
    row.param[4]	 =    0.08223;
    row.param[5]	 =    0.39436;
    row.param[6]	 =    0.27903;
    row.param[7]	 =    0.29082;
    row.param[8]	 =     0.0043;
    row.param[9]	 =    0.27265;
    row.param[10]	 =   -0.08821;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.01111412; // ;
    row.dparam[1]	 =    0.01919;
    row.dparam[2]	 =     0.0165;
    row.dparam[3]	 =    0.01754;
    row.dparam[4]	 =    0.01431;
    row.dparam[5]	 =    0.01486;
    row.dparam[6]	 =     0.0119;
    row.dparam[7]	 =    0.01222;
    row.dparam[8]	 =    0.00863;
    row.dparam[9]	 =     0.0088;
    row.dparam[10]	 =    0.00556;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        143; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =   -0.00449; // ;
    row.param[1]	 =   -0.02136;
    row.param[2]	 =    0.00503;
    row.param[3]	 =    0.00322;
    row.param[4]	 =    0.00383;
    row.param[5]	 =   -0.00232;
    row.param[6]	 =   -0.00101;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005060632; // ;
    row.dparam[1]	 = 0.0009571311;
    row.dparam[2]	 =    0.00076;
    row.dparam[3]	 =    0.00076;
    row.dparam[4]	 =    0.00064;
    row.dparam[5]	 =    0.00063;
    row.dparam[6]	 =     0.0005;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6103",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        144; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01975; // ;
    row.param[1]	 =    0.00747;
    row.param[2]	 =     0.0118;
    row.param[3]	 =    0.00346;
    row.param[4]	 =    0.00594;
    row.param[5]	 =    0.00359;
    row.param[6]	 =    0.00165;
    row.param[7]	 =    0.00226;
    row.param[8]	 =    0.00221;
    row.param[9]	 =    0.00375;
    row.param[10]	 =    0.00268;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001207352; // ;
    row.dparam[1]	 =    0.00234;
    row.dparam[2]	 =    0.00215;
    row.dparam[3]	 =    0.00214;
    row.dparam[4]	 =     0.0019;
    row.dparam[5]	 =    0.00185;
    row.dparam[6]	 =    0.00153;
    row.dparam[7]	 =    0.00144;
    row.dparam[8]	 =    0.00111;
    row.dparam[9]	 =    0.00102;
    row.dparam[10]	 =    0.00068;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6103",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        145; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00142; // ;
    row.param[1]	 =   -0.01095;
    row.param[2]	 =    0.00013;
    row.param[3]	 =   -0.00843;
    row.param[4]	 =    0.00222;
    row.param[5]	 =   -0.00184;
    row.param[6]	 =    0.00276;
    row.param[7]	 =    -0.0041;
    row.param[8]	 =    0.00369;
    row.param[9]	 =    0.00048;
    row.param[10]	 =   -0.00027;
    row.param[11]	 =   -0.00086;
    row.dparam[0]	 = 0.001542368; // ;
    row.dparam[1]	 = 0.003222577;
    row.dparam[2]	 = 0.002956721;
    row.dparam[3]	 = 0.002956924;
    row.dparam[4]	 = 0.002638731;
    row.dparam[5]	 = 0.002632755;
    row.dparam[6]	 = 0.002124712;
    row.dparam[7]	 = 0.002072704;
    row.dparam[8]	 = 0.001639939;
    row.dparam[9]	 = 0.00151268;
    row.dparam[10]	 = 0.001050809;
    row.dparam[11]	 =     0.0006;
 memcpy(&row.Comment,"duuP6203",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        146; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =    0.01693; // ;
    row.param[1]	 =   -0.00303;
    row.param[2]	 =   -0.00268;
    row.param[3]	 =   -0.00931;
    row.param[4]	 =   -0.00554;
    row.param[5]	 =    -0.0059;
    row.param[6]	 =   -0.00487;
    row.param[7]	 =   -0.00324;
    row.param[8]	 =   -0.00225;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006092618; // ;
    row.dparam[1]	 = 0.001199708;
    row.dparam[2]	 =    0.00102;
    row.dparam[3]	 =    0.00104;
    row.dparam[4]	 =    0.00091;
    row.dparam[5]	 =     0.0009;
    row.dparam[6]	 =    0.00075;
    row.dparam[7]	 =    0.00071;
    row.dparam[8]	 =    0.00052;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6203",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        147; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00988; // ;
    row.param[1]	 =   -0.01624;
    row.param[2]	 =    0.00022;
    row.param[3]	 =   -0.01388;
    row.param[4]	 =   -0.00413;
    row.param[5]	 =   -0.00764;
    row.param[6]	 =   -0.00151;
    row.param[7]	 =   -0.00963;
    row.param[8]	 =   -0.00075;
    row.param[9]	 =   -0.00245;
    row.param[10]	 =   -0.00277;
    row.param[11]	 =   -0.00159;
    row.dparam[0]	 = 0.001438715; // ;
    row.dparam[1]	 = 0.002963461;
    row.dparam[2]	 = 0.002703812;
    row.dparam[3]	 = 0.002731794;
    row.dparam[4]	 = 0.002379538;
    row.dparam[5]	 = 0.00234427;
    row.dparam[6]	 = 0.001928626;
    row.dparam[7]	 = 0.001876459;
    row.dparam[8]	 = 0.001431852;
    row.dparam[9]	 = 0.001351074;
    row.dparam[10]	 = 0.0009064767;
    row.dparam[11]	 =     0.0005;
 memcpy(&row.Comment,"duuP6303",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        148; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00855; // ;
    row.param[1]	 =    -0.0133;
    row.param[2]	 =   -0.01733;
    row.param[3]	 =   -0.01935;
    row.param[4]	 =   -0.01665;
    row.param[5]	 =   -0.01122;
    row.param[6]	 =   -0.01245;
    row.param[7]	 =   -0.00778;
    row.param[8]	 =   -0.00753;
    row.param[9]	 =   -0.00015;
    row.param[10]	 =   -0.00211;
    row.param[11]	 =    0.00239;
    row.dparam[0]	 = 0.001461027; // ;
    row.dparam[1]	 = 0.002999083;
    row.dparam[2]	 = 0.002765863;
    row.dparam[3]	 = 0.002757263;
    row.dparam[4]	 = 0.00243836;
    row.dparam[5]	 = 0.002358495;
    row.dparam[6]	 = 0.00196901;
    row.dparam[7]	 = 0.001840435;
    row.dparam[8]	 = 0.001408581;
    row.dparam[9]	 = 0.001266215;
    row.dparam[10]	 = 0.0008345058;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6303",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        149; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          6; // ;
    row.param[0]	 =   -0.02174; // ;
    row.param[1]	 =    0.01546;
    row.param[2]	 =    0.00781;
    row.param[3]	 =    0.00524;
    row.param[4]	 =   -0.00256;
    row.param[5]	 =    0.00418;
    row.param[6]	 =   -0.00633;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.007992703; // ;
    row.dparam[1]	 = 0.009019202;
    row.dparam[2]	 = 0.01210554;
    row.dparam[3]	 = 0.008094893;
    row.dparam[4]	 =    0.00522;
    row.dparam[5]	 =    0.00328;
    row.dparam[6]	 =    0.00193;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6403",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.02776; // ;
    row.param[1]	 =    0.06866;
    row.param[2]	 =   -0.07502;
    row.param[3]	 =    0.03486;
    row.param[4]	 =   -0.16506;
    row.param[5]	 =    0.01591;
    row.param[6]	 =   -0.18492;
    row.param[7]	 =    0.06776;
    row.param[8]	 =   -0.11105;
    row.param[9]	 =    0.12861;
    row.param[10]	 =   -0.00136;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.01083587; // ;
    row.dparam[1]	 =    0.02107;
    row.dparam[2]	 =    0.01774;
    row.dparam[3]	 =    0.01931;
    row.dparam[4]	 =    0.01684;
    row.dparam[5]	 =    0.01949;
    row.dparam[6]	 =    0.01616;
    row.dparam[7]	 =    0.01834;
    row.dparam[8]	 =    0.01233;
    row.dparam[9]	 =    0.01321;
    row.dparam[10]	 =    0.00667;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        150; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =   -0.00714; // ;
    row.param[1]	 =   -0.00168;
    row.param[2]	 =    0.00985;
    row.param[3]	 =   -0.00834;
    row.param[4]	 =    0.00361;
    row.param[5]	 =   -0.01613;
    row.param[6]	 =    0.00468;
    row.param[7]	 =   -0.00434;
    row.param[8]	 =    0.00163;
    row.param[9]	 =   -0.00358;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.002772003; // ;
    row.dparam[1]	 = 0.005559317;
    row.dparam[2]	 = 0.004996609;
    row.dparam[3]	 = 0.004983864;
    row.dparam[4]	 = 0.00881708;
    row.dparam[5]	 = 0.007454408;
    row.dparam[6]	 = 0.004994177;
    row.dparam[7]	 =    0.00306;
    row.dparam[8]	 =    0.00182;
    row.dparam[9]	 =    0.00135;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6503",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        151; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =   -0.02371; // ;
    row.param[1]	 =    0.00168;
    row.param[2]	 =    0.00953;
    row.param[3]	 =   -0.00707;
    row.param[4]	 =    0.01653;
    row.param[5]	 =   -0.00239;
    row.param[6]	 =    0.01499;
    row.param[7]	 =   -0.00151;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00153948; // ;
    row.dparam[1]	 = 0.002906338;
    row.dparam[2]	 = 0.001923174;
    row.dparam[3]	 =    0.00054;
    row.dparam[4]	 =    0.00059;
    row.dparam[5]	 =    0.00645;
    row.dparam[6]	 =    0.00523;
    row.dparam[7]	 =    0.00285;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6503",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        152; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          2; // ;
    row.param[0]	 =    0.00954; // ;
    row.param[1]	 =   -0.03329;
    row.param[2]	 =    0.01822;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00386281; // ;
    row.dparam[1]	 =    0.00282;
    row.dparam[2]	 =    0.00192;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6603",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.11595; // ;
    row.param[1]	 =   -0.27235;
    row.param[2]	 =    0.21858;
    row.param[3]	 =   -0.22719;
    row.param[4]	 =    0.18094;
    row.param[5]	 =   -0.18285;
    row.param[6]	 =    0.14615;
    row.param[7]	 =   -0.12908;
    row.param[8]	 =    0.08821;
    row.param[9]	 =   -0.06777;
    row.param[10]	 =    0.03114;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00590526; // ;
    row.dparam[1]	 = 0.01078248;
    row.dparam[2]	 = 0.008716565;
    row.dparam[3]	 = 0.006227182;
    row.dparam[4]	 =    0.00381;
    row.dparam[5]	 =    0.00423;
    row.dparam[6]	 =    0.00377;
    row.dparam[7]	 =    0.00421;
    row.dparam[8]	 =    0.00327;
    row.dparam[9]	 =    0.00333;
    row.dparam[10]	 =    0.00199;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.21868; // ;
    row.param[1]	 =    0.09211;
    row.param[2]	 =    0.51512;
    row.param[3]	 =    0.30694;
    row.param[4]	 =    0.51433;
    row.param[5]	 =    0.17545;
    row.param[6]	 =    0.34025;
    row.param[7]	 =    0.13325;
    row.param[8]	 =    0.31193;
    row.param[9]	 =    0.30243;
    row.param[10]	 =    0.07857;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.01028095; // ;
    row.dparam[1]	 =     0.0197;
    row.dparam[2]	 =    0.01726;
    row.dparam[3]	 =    0.01814;
    row.dparam[4]	 =    0.01494;
    row.dparam[5]	 =    0.01565;
    row.dparam[6]	 =    0.01218;
    row.dparam[7]	 =    0.01253;
    row.dparam[8]	 =    0.00811;
    row.dparam[9]	 =    0.00833;
    row.dparam[10]	 =    0.00462;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          3; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          1; // ;
    row.param[0]	 =    0.00259; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =    0.01489; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        153; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          5; // ;
    row.param[0]	 =    0.01511; // ;
    row.param[1]	 =   -0.01179;
    row.param[2]	 =   -0.00385;
    row.param[3]	 =   -0.00314;
    row.param[4]	 =   -0.00275;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005860034; // ;
    row.dparam[1]	 = 0.001040096;
    row.dparam[2]	 =    0.00075;
    row.dparam[3]	 =    0.00076;
    row.dparam[4]	 =    0.00063;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5104",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        154; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          1; // ;
    row.param[0]	 =    0.03354; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007543209; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5104",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        155; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    0.01163; // ;
    row.param[1]	 =   -0.01811;
    row.param[2]	 =   -0.00279;
    row.param[3]	 =   -0.00868;
    row.param[4]	 =   -0.00368;
    row.param[5]	 =   -0.00287;
    row.param[6]	 =   -0.00528;
    row.param[7]	 =     0.0009;
    row.param[8]	 =   -0.00201;
    row.param[9]	 =   -0.00145;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008450444; // ;
    row.dparam[1]	 =    0.00142;
    row.dparam[2]	 =    0.00148;
    row.dparam[3]	 =    0.00131;
    row.dparam[4]	 =    0.00134;
    row.dparam[5]	 =    0.00112;
    row.dparam[6]	 =    0.00113;
    row.dparam[7]	 =    0.00089;
    row.dparam[8]	 =    0.00088;
    row.dparam[9]	 =    0.00066;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5204",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        156; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =    0.02867; // ;
    row.param[1]	 =    0.01254;
    row.param[2]	 =   -0.00097;
    row.param[3]	 =      3e-05;
    row.param[4]	 =    0.00119;
    row.param[5]	 =   -0.00062;
    row.param[6]	 =   -0.00102;
    row.param[7]	 =   -0.00223;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001136002; // ;
    row.dparam[1]	 = 0.002101547;
    row.dparam[2]	 = 0.00198912;
    row.dparam[3]	 = 0.001883773;
    row.dparam[4]	 =  0.0017498;
    row.dparam[5]	 = 0.001599406;
    row.dparam[6]	 = 0.001314002;
    row.dparam[7]	 =     0.0008;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5204",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        157; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01665; // ;
    row.param[1]	 =   -0.01855;
    row.param[2]	 =    0.00426;
    row.param[3]	 =     -8e-05;
    row.param[4]	 =   -0.00839;
    row.param[5]	 =    0.00496;
    row.param[6]	 =    0.00048;
    row.param[7]	 =    -0.0041;
    row.param[8]	 =    0.00093;
    row.param[9]	 =    0.00097;
    row.param[10]	 =   -0.00079;
    row.param[11]	 =   -0.00125;
    row.dparam[0]	 = 0.001692188; // ;
    row.dparam[1]	 = 0.003482542;
    row.dparam[2]	 = 0.003170883;
    row.dparam[3]	 = 0.003210888;
    row.dparam[4]	 = 0.002806671;
    row.dparam[5]	 = 0.002777643;
    row.dparam[6]	 = 0.002269383;
    row.dparam[7]	 = 0.002176901;
    row.dparam[8]	 = 0.001657317;
    row.dparam[9]	 = 0.001582024;
    row.dparam[10]	 = 0.001143241;
    row.dparam[11]	 =    0.00063;
 memcpy(&row.Comment,"duuP5304",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        158; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          4; // ;
    row.param[0]	 =      0.025; // ;
    row.param[1]	 =    0.00023;
    row.param[2]	 =    0.00301;
    row.param[3]	 =   -0.00029;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005920304; // ;
    row.dparam[1]	 = 0.000976166;
    row.dparam[2]	 =    0.00077;
    row.dparam[3]	 =    0.00067;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5304",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        159; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01217; // ;
    row.param[1]	 =   -0.01911;
    row.param[2]	 =     0.0014;
    row.param[3]	 =   -0.00816;
    row.param[4]	 =    0.00161;
    row.param[5]	 =   -0.00425;
    row.param[6]	 =   -0.00189;
    row.param[7]	 =   -0.00124;
    row.param[8]	 =   -0.00475;
    row.param[9]	 =    -0.0043;
    row.param[10]	 =   -0.00055;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001230488; // ;
    row.dparam[1]	 = 0.002389665;
    row.dparam[2]	 = 0.002273785;
    row.dparam[3]	 = 0.002179472;
    row.dparam[4]	 = 0.001987687;
    row.dparam[5]	 = 0.001857418;
    row.dparam[6]	 = 0.001607887;
    row.dparam[7]	 =  0.0014046;
    row.dparam[8]	 =    0.00098;
    row.dparam[9]	 =    0.00093;
    row.dparam[10]	 =    0.00067;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5404",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        160; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02642; // ;
    row.param[1]	 =   -0.00455;
    row.param[2]	 =    -0.0008;
    row.param[3]	 =   -0.00013;
    row.param[4]	 =    0.00183;
    row.param[5]	 =    0.00263;
    row.param[6]	 =    0.00681;
    row.param[7]	 =    0.00224;
    row.param[8]	 =     0.0098;
    row.param[9]	 =    0.00487;
    row.param[10]	 =    0.00574;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.002140584; // ;
    row.dparam[1]	 = 0.00431868;
    row.dparam[2]	 = 0.004021318;
    row.dparam[3]	 = 0.003950051;
    row.dparam[4]	 = 0.003492578;
    row.dparam[5]	 = 0.003291975;
    row.dparam[6]	 = 0.002715327;
    row.dparam[7]	 = 0.002517459;
    row.dparam[8]	 = 0.002008382;
    row.dparam[9]	 = 0.001803469;
    row.dparam[10]	 = 0.001244588;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5404",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          4; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        161; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =   -0.01134; // ;
    row.param[1]	 =    0.00426;
    row.param[2]	 =    0.00012;
    row.param[3]	 =    0.00254;
    row.param[4]	 =   -0.00122;
    row.param[5]	 =   -0.00553;
    row.param[6]	 =   -0.00096;
    row.param[7]	 =      2e-05;
    row.param[8]	 =   -0.00542;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001240846; // ;
    row.dparam[1]	 = 0.001998049;
    row.dparam[2]	 = 0.00213965;
    row.dparam[3]	 = 0.001846212;
    row.dparam[4]	 =     0.0015;
    row.dparam[5]	 =    0.00126;
    row.dparam[6]	 =    0.00125;
    row.dparam[7]	 =      0.001;
    row.dparam[8]	 =    0.00099;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6105",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        162; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          5; // ;
    row.param[0]	 =   -0.01747; // ;
    row.param[1]	 =    0.00205;
    row.param[2]	 =   -0.00807;
    row.param[3]	 =    -0.0079;
    row.param[4]	 =    0.00217;
    row.param[5]	 =   -0.00586;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00111866; // ;
    row.dparam[1]	 = 0.002147207;
    row.dparam[2]	 = 0.001822004;
    row.dparam[3]	 =     0.0015;
    row.dparam[4]	 =    0.00115;
    row.dparam[5]	 =    0.00114;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6105",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        163; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.60167; // ;
    row.param[1]	 =   -1.38732;
    row.param[2]	 =    1.47625;
    row.param[3]	 =   -1.25142;
    row.param[4]	 =    0.97129;
    row.param[5]	 =   -0.69759;
    row.param[6]	 =    0.45302;
    row.param[7]	 =   -0.26676;
    row.param[8]	 =     0.1382;
    row.param[9]	 =   -0.05856;
    row.param[10]	 =    0.01784;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.004971328; // ;
    row.dparam[1]	 =    0.00926;
    row.dparam[2]	 =    0.00775;
    row.dparam[3]	 =    0.00637;
    row.dparam[4]	 =    0.00592;
    row.dparam[5]	 =    0.00648;
    row.dparam[6]	 =    0.00628;
    row.dparam[7]	 =     0.0061;
    row.dparam[8]	 =    0.04687;
    row.dparam[9]	 =    0.02561;
    row.dparam[10]	 =     0.0103;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6205",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        164; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          6; // ;
    row.param[0]	 =    0.00749; // ;
    row.param[1]	 =    0.00282;
    row.param[2]	 =   -0.00732;
    row.param[3]	 =    0.00086;
    row.param[4]	 =     0.0002;
    row.param[5]	 =    0.00063;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009170605; // ;
    row.dparam[1]	 = 0.001474924;
    row.dparam[2]	 =    0.00141;
    row.dparam[3]	 =    0.00112;
    row.dparam[4]	 =     0.0012;
    row.dparam[5]	 =     0.0009;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6305",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          5; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.07816; // ;
    row.param[1]	 =   -0.29542;
    row.param[2]	 =   -0.15708;
    row.param[3]	 =   -0.18293;
    row.param[4]	 =   -0.21931;
    row.param[5]	 =   -0.08904;
    row.param[6]	 =   -0.23262;
    row.param[7]	 =   -0.04879;
    row.param[8]	 =   -0.15181;
    row.param[9]	 =   -0.07198;
    row.param[10]	 =   -0.04009;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.009281767; // ;
    row.dparam[1]	 =    0.01627;
    row.dparam[2]	 =     0.0154;
    row.dparam[3]	 =    0.01483;
    row.dparam[4]	 =    0.01336;
    row.dparam[5]	 =    0.01232;
    row.dparam[6]	 =    0.01032;
    row.dparam[7]	 =    0.00928;
    row.dparam[8]	 =    0.00715;
    row.dparam[9]	 =    0.00626;
    row.dparam[10]	 =    0.00452;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        165; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.02612; // ;
    row.param[1]	 =    0.01886;
    row.param[2]	 =   -0.00888;
    row.param[3]	 =    0.00389;
    row.param[4]	 =   -0.00367;
    row.param[5]	 =   -0.00294;
    row.param[6]	 =   -0.00706;
    row.param[7]	 =    0.00124;
    row.param[8]	 =   -0.00329;
    row.param[9]	 =    0.00035;
    row.param[10]	 =    0.00114;
    row.param[11]	 =    0.00072;
    row.dparam[0]	 = 0.001721104; // ;
    row.dparam[1]	 = 0.003686136;
    row.dparam[2]	 = 0.003222484;
    row.dparam[3]	 = 0.003379364;
    row.dparam[4]	 = 0.002858339;
    row.dparam[5]	 = 0.002945811;
    row.dparam[6]	 = 0.00232112;
    row.dparam[7]	 = 0.00235648;
    row.dparam[8]	 = 0.001714789;
    row.dparam[9]	 = 0.001720872;
    row.dparam[10]	 = 0.001131636;
    row.dparam[11]	 =    0.00063;
 memcpy(&row.Comment,"duuP5106",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        166; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00486; // ;
    row.param[1]	 =    -0.0305;
    row.param[2]	 =   -0.01745;
    row.param[3]	 =   -0.01129;
    row.param[4]	 =   -0.00877;
    row.param[5]	 =    0.00145;
    row.param[6]	 =   -0.01665;
    row.param[7]	 =    0.00732;
    row.param[8]	 =   -0.00682;
    row.param[9]	 =    0.00639;
    row.param[10]	 =   -0.00598;
    row.param[11]	 =    0.00302;
    row.dparam[0]	 = 0.00307184; // ;
    row.dparam[1]	 = 0.006299119;
    row.dparam[2]	 = 0.005768371;
    row.dparam[3]	 = 0.005860213;
    row.dparam[4]	 = 0.005121494;
    row.dparam[5]	 = 0.004988366;
    row.dparam[6]	 = 0.004099317;
    row.dparam[7]	 = 0.004006869;
    row.dparam[8]	 = 0.003077483;
    row.dparam[9]	 = 0.002863669;
    row.dparam[10]	 = 0.00208473;
    row.dparam[11]	 =    0.00108;
 memcpy(&row.Comment,"duuP5206",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        167; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03424; // ;
    row.param[1]	 =     0.0322;
    row.param[2]	 =    -0.0044;
    row.param[3]	 =    0.00626;
    row.param[4]	 =   -0.00754;
    row.param[5]	 =    0.00238;
    row.param[6]	 =    -0.0035;
    row.param[7]	 =    0.00052;
    row.param[8]	 =    0.00065;
    row.param[9]	 =    -0.0007;
    row.param[10]	 =    0.00252;
    row.param[11]	 =    0.00146;
    row.dparam[0]	 = 0.001461403; // ;
    row.dparam[1]	 = 0.003153316;
    row.dparam[2]	 = 0.002749291;
    row.dparam[3]	 = 0.002904841;
    row.dparam[4]	 = 0.00241969;
    row.dparam[5]	 = 0.002506272;
    row.dparam[6]	 = 0.001940258;
    row.dparam[7]	 = 0.00199221;
    row.dparam[8]	 = 0.001431922;
    row.dparam[9]	 = 0.001438089;
    row.dparam[10]	 = 0.0009354143;
    row.dparam[11]	 =    0.00056;
 memcpy(&row.Comment,"duuP5206",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        168; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00179; // ;
    row.param[1]	 =   -0.02466;
    row.param[2]	 =   -0.00396;
    row.param[3]	 =   -0.00017;
    row.param[4]	 =   -0.00189;
    row.param[5]	 =    0.01233;
    row.param[6]	 =   -0.01088;
    row.param[7]	 =    0.00943;
    row.param[8]	 =    0.00075;
    row.param[9]	 =     0.0084;
    row.param[10]	 =   -0.00203;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.002082162; // ;
    row.dparam[1]	 = 0.004079338;
    row.dparam[2]	 = 0.003863586;
    row.dparam[3]	 = 0.00374306;
    row.dparam[4]	 = 0.003420073;
    row.dparam[5]	 = 0.003208769;
    row.dparam[6]	 = 0.002643577;
    row.dparam[7]	 = 0.00245937;
    row.dparam[8]	 = 0.002034945;
    row.dparam[9]	 =     0.0017;
    row.dparam[10]	 =    0.00128;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5306",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        169; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.0392; // ;
    row.param[1]	 =    0.02223;
    row.param[2]	 =    -0.0101;
    row.param[3]	 =   -0.00791;
    row.param[4]	 =   -0.01172;
    row.param[5]	 =   -0.00609;
    row.param[6]	 =   -0.00618;
    row.param[7]	 =   -0.00433;
    row.param[8]	 =   -0.00169;
    row.param[9]	 =    0.00077;
    row.param[10]	 =    0.00049;
    row.param[11]	 =    -0.0006;
    row.dparam[0]	 = 0.001512812; // ;
    row.dparam[1]	 = 0.003225415;
    row.dparam[2]	 = 0.002857464;
    row.dparam[3]	 = 0.002961689;
    row.dparam[4]	 = 0.002475601;
    row.dparam[5]	 =  0.0024985;
    row.dparam[6]	 = 0.001959337;
    row.dparam[7]	 = 0.001955556;
    row.dparam[8]	 = 0.001411099;
    row.dparam[9]	 = 0.001392157;
    row.dparam[10]	 = 0.0008893818;
    row.dparam[11]	 =     0.0005;
 memcpy(&row.Comment,"duuP5306",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        170; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01684; // ;
    row.param[1]	 =    -0.0348;
    row.param[2]	 =    0.00771;
    row.param[3]	 =   -0.00354;
    row.param[4]	 =    0.00568;
    row.param[5]	 =    0.00467;
    row.param[6]	 =   -0.00739;
    row.param[7]	 =    0.00385;
    row.param[8]	 =   -0.00652;
    row.param[9]	 =    0.00036;
    row.param[10]	 =   -0.00121;
    row.param[11]	 =    0.00096;
    row.dparam[0]	 = 0.002519087; // ;
    row.dparam[1]	 = 0.004834439;
    row.dparam[2]	 = 0.004706432;
    row.dparam[3]	 = 0.004404554;
    row.dparam[4]	 = 0.004146396;
    row.dparam[5]	 = 0.003732626;
    row.dparam[6]	 = 0.003325808;
    row.dparam[7]	 = 0.002861363;
    row.dparam[8]	 = 0.002271145;
    row.dparam[9]	 = 0.001870962;
    row.dparam[10]	 =    0.00107;
    row.dparam[11]	 =    0.00094;
 memcpy(&row.Comment,"duuP5406",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        171; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01841; // ;
    row.param[1]	 =    0.01893;
    row.param[2]	 =    0.00392;
    row.param[3]	 =   -0.01252;
    row.param[4]	 =    0.00288;
    row.param[5]	 =   -0.00845;
    row.param[6]	 =     0.0026;
    row.param[7]	 =    -0.0022;
    row.param[8]	 =    0.00402;
    row.param[9]	 =    -0.0002;
    row.param[10]	 =    0.00487;
    row.param[11]	 =    0.00042;
    row.dparam[0]	 = 0.001495493; // ;
    row.dparam[1]	 = 0.003159573;
    row.dparam[2]	 = 0.002817801;
    row.dparam[3]	 = 0.002911185;
    row.dparam[4]	 = 0.002465705;
    row.dparam[5]	 = 0.002517936;
    row.dparam[6]	 = 0.001986303;
    row.dparam[7]	 = 0.001997949;
    row.dparam[8]	 = 0.001454991;
    row.dparam[9]	 = 0.001449172;
    row.dparam[10]	 = 0.0009411164;
    row.dparam[11]	 =    0.00054;
 memcpy(&row.Comment,"duuP5406",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          6; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        172; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.05884; // ;
    row.param[1]	 =    0.35981;
    row.param[2]	 =    -0.5036;
    row.param[3]	 =    0.42442;
    row.param[4]	 =    -0.2987;
    row.param[5]	 =    0.20294;
    row.param[6]	 =   -0.10613;
    row.param[7]	 =    0.05079;
    row.param[8]	 =   -0.00923;
    row.param[9]	 =   -0.00544;
    row.param[10]	 =     0.0101;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.06287207; // ;
    row.dparam[1]	 =  0.1258232;
    row.dparam[2]	 =  0.1140823;
    row.dparam[3]	 =  0.1039631;
    row.dparam[4]	 =    0.08488;
    row.dparam[5]	 =    0.07023;
    row.dparam[6]	 =    0.05029;
    row.dparam[7]	 =    0.03724;
    row.dparam[8]	 =    0.02218;
    row.dparam[9]	 =    0.01447;
    row.dparam[10]	 =    0.00605;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6107",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        173; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00331; // ;
    row.param[1]	 =   -0.01762;
    row.param[2]	 =    -0.0014;
    row.param[3]	 =   -0.01034;
    row.param[4]	 =   -0.00449;
    row.param[5]	 =   -0.00967;
    row.param[6]	 =   -0.00226;
    row.param[7]	 =   -0.00767;
    row.param[8]	 =   -0.00267;
    row.param[9]	 =   -0.00227;
    row.param[10]	 =   -0.00091;
    row.param[11]	 =   -0.00221;
    row.dparam[0]	 = 0.001229187; // ;
    row.dparam[1]	 = 0.002427385;
    row.dparam[2]	 = 0.002323984;
    row.dparam[3]	 = 0.002249644;
    row.dparam[4]	 = 0.002072921;
    row.dparam[5]	 = 0.001916507;
    row.dparam[6]	 = 0.001668323;
    row.dparam[7]	 = 0.001511622;
    row.dparam[8]	 = 0.00128316;
    row.dparam[9]	 = 0.001096038;
    row.dparam[10]	 =    0.00062;
    row.dparam[11]	 =    0.00063;
 memcpy(&row.Comment,"duuP6207",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        174; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.03047; // ;
    row.param[1]	 =   -0.00187;
    row.param[2]	 =    0.00356;
    row.param[3]	 =    0.00463;
    row.param[4]	 =    0.00237;
    row.param[5]	 =    0.00917;
    row.param[6]	 =    0.00311;
    row.param[7]	 =    0.00805;
    row.param[8]	 =    0.00453;
    row.param[9]	 =    0.00372;
    row.param[10]	 =    0.00127;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001794241; // ;
    row.dparam[1]	 = 0.003692438;
    row.dparam[2]	 = 0.003456545;
    row.dparam[3]	 = 0.003352611;
    row.dparam[4]	 = 0.003061144;
    row.dparam[5]	 = 0.002951694;
    row.dparam[6]	 = 0.00243181;
    row.dparam[7]	 =    0.00221;
    row.dparam[8]	 =    0.00177;
    row.dparam[9]	 =     0.0015;
    row.dparam[10]	 =    0.00102;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6207",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        175; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          5; // ;
    row.param[0]	 =    0.02598; // ;
    row.param[1]	 =   -0.00278;
    row.param[2]	 =    0.00145;
    row.param[3]	 =    0.00329;
    row.param[4]	 =   -0.00418;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.000766355; // ;
    row.dparam[1]	 = 0.001290349;
    row.dparam[2]	 = 0.001162755;
    row.dparam[3]	 = 0.001101136;
    row.dparam[4]	 = 0.0009202174;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6307",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          7; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        176; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00942; // ;
    row.param[1]	 =    0.01445;
    row.param[2]	 =    -0.0071;
    row.param[3]	 =   -0.00531;
    row.param[4]	 =   -0.00808;
    row.param[5]	 =   -0.00711;
    row.param[6]	 =   -0.00898;
    row.param[7]	 =   -0.01183;
    row.param[8]	 =    -0.0025;
    row.param[9]	 =   -0.00534;
    row.param[10]	 =   -0.00412;
    row.param[11]	 =   -0.00258;
    row.dparam[0]	 = 0.002224073; // ;
    row.dparam[1]	 = 0.004626111;
    row.dparam[2]	 = 0.004286315;
    row.dparam[3]	 = 0.004120012;
    row.dparam[4]	 = 0.003718091;
    row.dparam[5]	 = 0.003606009;
    row.dparam[6]	 = 0.002896135;
    row.dparam[7]	 = 0.002800446;
    row.dparam[8]	 = 0.002250555;
    row.dparam[9]	 = 0.001989774;
    row.dparam[10]	 = 0.001413542;
    row.dparam[11]	 =    0.00083;
 memcpy(&row.Comment,"duuP5108",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        177; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03981; // ;
    row.param[1]	 =   -0.00549;
    row.param[2]	 =    0.02717;
    row.param[3]	 =    0.02461;
    row.param[4]	 =    0.01722;
    row.param[5]	 =    0.01721;
    row.param[6]	 =    0.01015;
    row.param[7]	 =    0.00931;
    row.param[8]	 =    0.00647;
    row.param[9]	 =    0.00412;
    row.param[10]	 =    0.00458;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00353143; // ;
    row.dparam[1]	 = 0.007072121;
    row.dparam[2]	 = 0.006589234;
    row.dparam[3]	 = 0.006170227;
    row.dparam[4]	 = 0.005384208;
    row.dparam[5]	 =    0.00474;
    row.dparam[6]	 =    0.00375;
    row.dparam[7]	 =    0.00312;
    row.dparam[8]	 =    0.00225;
    row.dparam[9]	 =    0.00172;
    row.dparam[10]	 =    0.00104;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5108",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        178; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.02073; // ;
    row.param[1]	 =    0.01572;
    row.param[2]	 =   -0.00458;
    row.param[3]	 =    0.00232;
    row.param[4]	 =   -0.00031;
    row.param[5]	 =     0.0012;
    row.param[6]	 =    0.00158;
    row.param[7]	 =    0.00239;
    row.param[8]	 =    0.00088;
    row.param[9]	 =   -0.00014;
    row.param[10]	 =    0.00014;
    row.param[11]	 =   -0.00041;
    row.dparam[0]	 = 0.00164003; // ;
    row.dparam[1]	 = 0.003323522;
    row.dparam[2]	 = 0.003083018;
    row.dparam[3]	 = 0.003061976;
    row.dparam[4]	 = 0.002743611;
    row.dparam[5]	 = 0.002644731;
    row.dparam[6]	 = 0.002213346;
    row.dparam[7]	 = 0.00205779;
    row.dparam[8]	 = 0.001647574;
    row.dparam[9]	 = 0.001442567;
    row.dparam[10]	 = 0.0009899495;
    row.dparam[11]	 =    0.00057;
 memcpy(&row.Comment,"duuP5208",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        179; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.09491; // ;
    row.param[1]	 =   -0.00776;
    row.param[2]	 =    0.01058;
    row.param[3]	 =    0.00106;
    row.param[4]	 =   -0.00018;
    row.param[5]	 =   -0.00479;
    row.param[6]	 =   -0.00368;
    row.param[7]	 =   -0.00556;
    row.param[8]	 =    -0.0031;
    row.param[9]	 =   -0.00163;
    row.param[10]	 =   -0.00169;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.004152132; // ;
    row.dparam[1]	 = 0.008371266;
    row.dparam[2]	 = 0.007827675;
    row.dparam[3]	 = 0.007262403;
    row.dparam[4]	 = 0.006382609;
    row.dparam[5]	 = 0.005649823;
    row.dparam[6]	 = 0.004427471;
    row.dparam[7]	 = 0.003659522;
    row.dparam[8]	 = 0.002670599;
    row.dparam[9]	 =    0.00189;
    row.dparam[10]	 =    0.00113;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5208",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        180; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03042; // ;
    row.param[1]	 =    0.01494;
    row.param[2]	 =   -0.00619;
    row.param[3]	 =   -0.00044;
    row.param[4]	 =   -0.00341;
    row.param[5]	 =   -0.00015;
    row.param[6]	 =   -0.00034;
    row.param[7]	 =   -0.00055;
    row.param[8]	 =     0.0011;
    row.param[9]	 =   -0.00157;
    row.param[10]	 =   -0.00028;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001406165; // ;
    row.dparam[1]	 = 0.002876891;
    row.dparam[2]	 = 0.002638371;
    row.dparam[3]	 = 0.002643218;
    row.dparam[4]	 = 0.002346913;
    row.dparam[5]	 = 0.002310866;
    row.dparam[6]	 = 0.001938685;
    row.dparam[7]	 = 0.001839185;
    row.dparam[8]	 = 0.001438923;
    row.dparam[9]	 = 0.001308625;
    row.dparam[10]	 =    0.00078;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5308",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        181; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.05816; // ;
    row.param[1]	 =    0.01571;
    row.param[2]	 =    0.03044;
    row.param[3]	 =    0.02251;
    row.param[4]	 =    0.01918;
    row.param[5]	 =    0.01378;
    row.param[6]	 =    0.00943;
    row.param[7]	 =    0.00735;
    row.param[8]	 =    0.00284;
    row.param[9]	 =   -0.00188;
    row.param[10]	 =   -0.00031;
    row.param[11]	 =   -0.00141;
    row.dparam[0]	 = 0.001607016; // ;
    row.dparam[1]	 = 0.003240525;
    row.dparam[2]	 = 0.002985197;
    row.dparam[3]	 = 0.002935183;
    row.dparam[4]	 = 0.002524619;
    row.dparam[5]	 = 0.002399437;
    row.dparam[6]	 = 0.001942627;
    row.dparam[7]	 = 0.00175237;
    row.dparam[8]	 = 0.001326386;
    row.dparam[9]	 =    0.00098;
    row.dparam[10]	 =    0.00072;
    row.dparam[11]	 =    0.00068;
 memcpy(&row.Comment,"duuP5308",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        182; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =   -0.02146; // ;
    row.param[1]	 =    0.01906;
    row.param[2]	 =    0.00029;
    row.param[3]	 =    -0.0045;
    row.param[4]	 =    0.00114;
    row.param[5]	 =    -0.0042;
    row.param[6]	 =    0.00311;
    row.param[7]	 =   -0.00277;
    row.param[8]	 =    0.00478;
    row.param[9]	 =    0.00103;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00107912; // ;
    row.dparam[1]	 = 0.001994618;
    row.dparam[2]	 = 0.001954405;
    row.dparam[3]	 = 0.00187171;
    row.dparam[4]	 = 0.001770988;
    row.dparam[5]	 = 0.00156285;
    row.dparam[6]	 = 0.001480709;
    row.dparam[7]	 = 0.001225398;
    row.dparam[8]	 =    0.00099;
    row.dparam[9]	 =    0.00074;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5408",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        183; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03864; // ;
    row.param[1]	 =    0.00844;
    row.param[2]	 =    0.03339;
    row.param[3]	 =    0.02324;
    row.param[4]	 =    0.02103;
    row.param[5]	 =    0.01728;
    row.param[6]	 =    0.01138;
    row.param[7]	 =    0.01117;
    row.param[8]	 =    0.00359;
    row.param[9]	 =      0.004;
    row.param[10]	 =    0.00125;
    row.param[11]	 =     -0.002;
    row.dparam[0]	 = 0.00205762; // ;
    row.dparam[1]	 = 0.004366062;
    row.dparam[2]	 = 0.004106215;
    row.dparam[3]	 = 0.003853946;
    row.dparam[4]	 = 0.003537711;
    row.dparam[5]	 = 0.003377692;
    row.dparam[6]	 = 0.002623776;
    row.dparam[7]	 = 0.002490402;
    row.dparam[8]	 = 0.001986001;
    row.dparam[9]	 = 0.001607016;
    row.dparam[10]	 = 0.001205073;
    row.dparam[11]	 =    0.00081;
 memcpy(&row.Comment,"duuP5408",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        184; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =    -0.0085; // ;
    row.param[1]	 =   -0.00754;
    row.param[2]	 =    0.00392;
    row.param[3]	 =    0.00349;
    row.param[4]	 =     0.0051;
    row.param[5]	 =   -0.00357;
    row.param[6]	 =   -0.00308;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005322593; // ;
    row.dparam[1]	 =    0.00094;
    row.dparam[2]	 =    0.00085;
    row.dparam[3]	 =    0.00088;
    row.dparam[4]	 =    0.00078;
    row.dparam[5]	 =    0.00075;
    row.dparam[6]	 =    0.00056;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5508",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        185; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     0.0245; // ;
    row.param[1]	 =     0.0067;
    row.param[2]	 =    0.01191;
    row.param[3]	 =    0.00515;
    row.param[4]	 =    0.00434;
    row.param[5]	 =    0.00104;
    row.param[6]	 =     0.0009;
    row.param[7]	 =     0.0009;
    row.param[8]	 =   -0.00011;
    row.param[9]	 =    -0.0008;
    row.param[10]	 =   -0.00122;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008450444; // ;
    row.dparam[1]	 = 0.001723514;
    row.dparam[2]	 = 0.001600125;
    row.dparam[3]	 = 0.001606549;
    row.dparam[4]	 =  0.0014272;
    row.dparam[5]	 = 0.001377861;
    row.dparam[6]	 =    0.00114;
    row.dparam[7]	 =    0.00107;
    row.dparam[8]	 =    0.00085;
    row.dparam[9]	 =    0.00077;
    row.dparam[10]	 =    0.00054;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5508",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        186; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00724; // ;
    row.param[1]	 =   -0.01428;
    row.param[2]	 =    0.00697;
    row.param[3]	 =   -0.00402;
    row.param[4]	 =   -0.00243;
    row.param[5]	 =   -0.00482;
    row.param[6]	 =    0.00057;
    row.param[7]	 =   -0.00729;
    row.param[8]	 =     -5e-05;
    row.param[9]	 =   -0.00481;
    row.param[10]	 =   -0.00206;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001586474; // ;
    row.dparam[1]	 = 0.00319889;
    row.dparam[2]	 = 0.002964456;
    row.dparam[3]	 = 0.002897464;
    row.dparam[4]	 = 0.00258368;
    row.dparam[5]	 = 0.002454649;
    row.dparam[6]	 = 0.00209251;
    row.dparam[7]	 = 0.001934942;
    row.dparam[8]	 = 0.001511589;
    row.dparam[9]	 = 0.00129769;
    row.dparam[10]	 =    0.00077;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5608",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        187; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =    0.04148; // ;
    row.param[1]	 =    0.00986;
    row.param[2]	 =    0.00356;
    row.param[3]	 =    0.00215;
    row.param[4]	 =   -0.00143;
    row.param[5]	 =   -0.00153;
    row.param[6]	 =   -0.00293;
    row.param[7]	 =   -0.00161;
    row.param[8]	 =   -0.00261;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006466065; // ;
    row.dparam[1]	 = 0.001288449;
    row.dparam[2]	 = 0.001174436;
    row.dparam[3]	 = 0.001182286;
    row.dparam[4]	 = 0.001036002;
    row.dparam[5]	 = 0.001016071;
    row.dparam[6]	 = 0.0008241966;
    row.dparam[7]	 = 0.0007710383;
    row.dparam[8]	 =    0.00048;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5608",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        188; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00151; // ;
    row.param[1]	 =   -0.00994;
    row.param[2]	 =   -0.00028;
    row.param[3]	 =   -0.00925;
    row.param[4]	 =   -0.00558;
    row.param[5]	 =   -0.00981;
    row.param[6]	 =   -0.00427;
    row.param[7]	 =   -0.01047;
    row.param[8]	 =   -0.00501;
    row.param[9]	 =   -0.00644;
    row.param[10]	 =   -0.00275;
    row.param[11]	 =   -0.00082;
    row.dparam[0]	 = 0.001720029; // ;
    row.dparam[1]	 = 0.003489198;
    row.dparam[2]	 = 0.003241635;
    row.dparam[3]	 = 0.003191316;
    row.dparam[4]	 = 0.002865746;
    row.dparam[5]	 = 0.002723472;
    row.dparam[6]	 = 0.002327252;
    row.dparam[7]	 = 0.002149791;
    row.dparam[8]	 = 0.001711432;
    row.dparam[9]	 = 0.001513209;
    row.dparam[10]	 = 0.001018234;
    row.dparam[11]	 =    0.00057;
 memcpy(&row.Comment,"duuP5708",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        189; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =          8; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.04432; // ;
    row.param[1]	 =    0.02166;
    row.param[2]	 =    0.00802;
    row.param[3]	 =    0.00205;
    row.param[4]	 =   -0.00054;
    row.param[5]	 =    0.00633;
    row.param[6]	 =    0.00048;
    row.param[7]	 =    0.00613;
    row.param[8]	 =   -0.00407;
    row.param[9]	 =   -0.00019;
    row.param[10]	 =     0.0005;
    row.param[11]	 =    0.00065;
    row.dparam[0]	 = 0.001334541; // ;
    row.dparam[1]	 = 0.002727288;
    row.dparam[2]	 = 0.002495616;
    row.dparam[3]	 = 0.002452468;
    row.dparam[4]	 = 0.002183438;
    row.dparam[5]	 = 0.002111019;
    row.dparam[6]	 = 0.001778904;
    row.dparam[7]	 = 0.001670928;
    row.dparam[8]	 = 0.001302997;
    row.dparam[9]	 = 0.001188276;
    row.dparam[10]	 = 0.0008203658;
    row.dparam[11]	 =     0.0005;
 memcpy(&row.Comment,"duuP5708",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        190; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.01563; // ;
    row.param[1]	 =    -0.0411;
    row.param[2]	 =    0.00369;
    row.param[3]	 =   -0.00144;
    row.param[4]	 =    0.00808;
    row.param[5]	 =   -0.00644;
    row.param[6]	 =   -0.00391;
    row.param[7]	 =   -0.00907;
    row.param[8]	 =   -0.00376;
    row.param[9]	 =   -0.00459;
    row.param[10]	 =   -0.00325;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00111198; // ;
    row.dparam[1]	 = 0.002683077;
    row.dparam[2]	 =    0.00205;
    row.dparam[3]	 =    0.00243;
    row.dparam[4]	 =     0.0018;
    row.dparam[5]	 =    0.00206;
    row.dparam[6]	 =    0.00142;
    row.dparam[7]	 =    0.00157;
    row.dparam[8]	 =    0.00101;
    row.dparam[9]	 =    0.00106;
    row.dparam[10]	 =    0.00059;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6409",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        191; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.03212; // ;
    row.param[1]	 =    0.01893;
    row.param[2]	 =    0.00082;
    row.param[3]	 =   -0.00551;
    row.param[4]	 =   -0.00242;
    row.param[5]	 =   -0.00575;
    row.param[6]	 =   -0.00102;
    row.param[7]	 =   -0.00731;
    row.param[8]	 =   -0.00118;
    row.param[9]	 =   -0.00491;
    row.param[10]	 =   -0.00092;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001212023; // ;
    row.dparam[1]	 = 0.002969848;
    row.dparam[2]	 =    0.00226;
    row.dparam[3]	 =    0.00268;
    row.dparam[4]	 =    0.00194;
    row.dparam[5]	 =    0.00222;
    row.dparam[6]	 =     0.0015;
    row.dparam[7]	 =    0.00167;
    row.dparam[8]	 =    0.00103;
    row.dparam[9]	 =    0.00111;
    row.dparam[10]	 =     0.0006;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6409",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        192; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =     0.1297; // ;
    row.param[1]	 =   -0.16735;
    row.param[2]	 =    0.02202;
    row.param[3]	 =   -0.01009;
    row.param[4]	 =    0.01274;
    row.param[5]	 =   -0.01015;
    row.param[6]	 =    0.00358;
    row.param[7]	 =   -0.00686;
    row.param[8]	 =    -0.0022;
    row.param[9]	 =   -0.00377;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001040481; // ;
    row.dparam[1]	 = 0.001796914;
    row.dparam[2]	 = 0.001906568;
    row.dparam[3]	 = 0.001573086;
    row.dparam[4]	 = 0.00156349;
    row.dparam[5]	 = 0.001232274;
    row.dparam[6]	 = 0.001226744;
    row.dparam[7]	 = 0.0008988882;
    row.dparam[8]	 = 0.0008626703;
    row.dparam[9]	 =     0.0005;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6509",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        193; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00721; // ;
    row.param[1]	 =    -0.0293;
    row.param[2]	 =    0.01889;
    row.param[3]	 =   -0.00266;
    row.param[4]	 =    0.02113;
    row.param[5]	 =      8e-05;
    row.param[6]	 =    0.01503;
    row.param[7]	 =   -0.00018;
    row.param[8]	 =    0.00863;
    row.param[9]	 =   -0.00109;
    row.param[10]	 =    0.00343;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001411559; // ;
    row.dparam[1]	 = 0.003502285;
    row.dparam[2]	 = 0.002648018;
    row.dparam[3]	 = 0.003170647;
    row.dparam[4]	 = 0.002253042;
    row.dparam[5]	 = 0.00259326;
    row.dparam[6]	 = 0.001710935;
    row.dparam[7]	 = 0.001908009;
    row.dparam[8]	 =    0.00113;
    row.dparam[9]	 =    0.00123;
    row.dparam[10]	 =    0.00063;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6609",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        194; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =    0.00876; // ;
    row.param[1]	 =    0.03576;
    row.param[2]	 =   -0.00473;
    row.param[3]	 =    0.00613;
    row.param[4]	 =   -0.01118;
    row.param[5]	 =     0.0026;
    row.param[6]	 =   -0.01135;
    row.param[7]	 =   -0.00094;
    row.param[8]	 =   -0.00766;
    row.param[9]	 =   -0.00072;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.002235889; // ;
    row.dparam[1]	 = 0.003725708;
    row.dparam[2]	 = 0.004175799;
    row.dparam[3]	 = 0.003251461;
    row.dparam[4]	 = 0.003466252;
    row.dparam[5]	 =    0.00239;
    row.dparam[6]	 =    0.00251;
    row.dparam[7]	 =    0.00154;
    row.dparam[8]	 =    0.00159;
    row.dparam[9]	 =    0.00082;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6609",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        195; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.10008; // ;
    row.param[1]	 =   -0.14172;
    row.param[2]	 =    0.03594;
    row.param[3]	 =    -0.0191;
    row.param[4]	 =    0.01866;
    row.param[5]	 =   -0.00522;
    row.param[6]	 =    0.01502;
    row.param[7]	 =    0.00197;
    row.param[8]	 =    0.00488;
    row.param[9]	 =    0.00198;
    row.param[10]	 =    0.00397;
    row.param[11]	 =   -0.00111;
    row.dparam[0]	 = 0.00173358; // ;
    row.dparam[1]	 = 0.003692872;
    row.dparam[2]	 = 0.003240957;
    row.dparam[3]	 = 0.003330616;
    row.dparam[4]	 = 0.002743301;
    row.dparam[5]	 = 0.002735507;
    row.dparam[6]	 = 0.002020891;
    row.dparam[7]	 = 0.002022721;
    row.dparam[8]	 = 0.001403567;
    row.dparam[9]	 = 0.001378006;
    row.dparam[10]	 = 0.0008207314;
    row.dparam[11]	 =    0.00062;
 memcpy(&row.Comment,"duuP6709",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =          9; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        196; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02807; // ;
    row.param[1]	 =   -0.01866;
    row.param[2]	 =    0.00209;
    row.param[3]	 =     0.0036;
    row.param[4]	 =    0.00351;
    row.param[5]	 =    0.00457;
    row.param[6]	 =    0.00461;
    row.param[7]	 =    0.00325;
    row.param[8]	 =     0.0036;
    row.param[9]	 =    0.00125;
    row.param[10]	 =    0.00188;
    row.param[11]	 =    0.00153;
    row.dparam[0]	 = 0.0008508819; // ;
    row.dparam[1]	 = 0.001736232;
    row.dparam[2]	 = 0.001598906;
    row.dparam[3]	 = 0.001606549;
    row.dparam[4]	 = 0.00142088;
    row.dparam[5]	 = 0.001379275;
    row.dparam[6]	 =    0.00108;
    row.dparam[7]	 =    0.00105;
    row.dparam[8]	 =    0.00078;
    row.dparam[9]	 =    0.00076;
    row.dparam[10]	 =    0.00051;
    row.dparam[11]	 =     0.0005;
 memcpy(&row.Comment,"duuP5510",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        197; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =    0.03651; // ;
    row.param[1]	 =    0.00994;
    row.param[2]	 =    0.00588;
    row.param[3]	 =      0.004;
    row.param[4]	 =   -0.00013;
    row.param[5]	 =    0.00297;
    row.param[6]	 =    0.00411;
    row.param[7]	 =   -0.00283;
    row.param[8]	 =    0.00248;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005189412; // ;
    row.dparam[1]	 =    0.00097;
    row.dparam[2]	 =    0.00086;
    row.dparam[3]	 =    0.00089;
    row.dparam[4]	 =    0.00076;
    row.dparam[5]	 =    0.00078;
    row.dparam[6]	 =    0.00063;
    row.dparam[7]	 =    0.00064;
    row.dparam[8]	 =    0.00047;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5510",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        198; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02971; // ;
    row.param[1]	 =   -0.02034;
    row.param[2]	 =    0.00011;
    row.param[3]	 =    0.00202;
    row.param[4]	 =    0.00147;
    row.param[5]	 =    0.00433;
    row.param[6]	 =    0.00333;
    row.param[7]	 =    0.00348;
    row.param[8]	 =    0.00211;
    row.param[9]	 =    0.00349;
    row.param[10]	 =    -0.0004;
    row.param[11]	 =    0.00106;
    row.dparam[0]	 = 0.001355913; // ;
    row.dparam[1]	 = 0.002686503;
    row.dparam[2]	 = 0.002555621;
    row.dparam[3]	 = 0.002486544;
    row.dparam[4]	 = 0.002277828;
    row.dparam[5]	 = 0.002139018;
    row.dparam[6]	 = 0.00186561;
    row.dparam[7]	 = 0.001680744;
    row.dparam[8]	 = 0.001381919;
    row.dparam[9]	 = 0.001181905;
    row.dparam[10]	 =    0.00066;
    row.dparam[11]	 =    0.00062;
 memcpy(&row.Comment,"duuP5610",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        199; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02654; // ;
    row.param[1]	 =    0.02255;
    row.param[2]	 =    0.00072;
    row.param[3]	 =    0.00237;
    row.param[4]	 =    -0.0021;
    row.param[5]	 =    -0.0062;
    row.param[6]	 =    0.00686;
    row.param[7]	 =   -0.01072;
    row.param[8]	 =    0.00507;
    row.param[9]	 =   -0.00478;
    row.param[10]	 =    0.00036;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009703608; // ;
    row.dparam[1]	 = 0.001986983;
    row.dparam[2]	 = 0.001743932;
    row.dparam[3]	 = 0.001796719;
    row.dparam[4]	 = 0.001527776;
    row.dparam[5]	 =    0.00148;
    row.dparam[6]	 =     0.0012;
    row.dparam[7]	 =    0.00121;
    row.dparam[8]	 =    0.00088;
    row.dparam[9]	 =    0.00089;
    row.dparam[10]	 =    0.00057;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5610",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        200; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.04055; // ;
    row.param[1]	 =   -0.03348;
    row.param[2]	 =   -0.00388;
    row.param[3]	 =   -0.01536;
    row.param[4]	 =   -0.00217;
    row.param[5]	 =    0.00066;
    row.param[6]	 =   -0.00739;
    row.param[7]	 =    0.00314;
    row.param[8]	 =    -0.0019;
    row.param[9]	 =    0.00247;
    row.param[10]	 =   -0.00372;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.002804799; // ;
    row.dparam[1]	 = 0.005394747;
    row.dparam[2]	 = 0.005218985;
    row.dparam[3]	 = 0.004787745;
    row.dparam[4]	 = 0.00436794;
    row.dparam[5]	 = 0.003752572;
    row.dparam[6]	 = 0.003234331;
    row.dparam[7]	 = 0.002569708;
    row.dparam[8]	 = 0.002044431;
    row.dparam[9]	 = 0.001490369;
    row.dparam[10]	 = 0.001082081;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5710",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        201; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         10; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =     0.0562; // ;
    row.param[1]	 =    0.00331;
    row.param[2]	 =    0.00469;
    row.param[3]	 =   -0.00476;
    row.param[4]	 =    -0.0031;
    row.param[5]	 =   -0.00881;
    row.param[6]	 =   -0.00199;
    row.param[7]	 =   -0.01139;
    row.param[8]	 =   -0.00028;
    row.param[9]	 =   -0.00926;
    row.param[10]	 =   -0.00036;
    row.param[11]	 =   -0.00151;
    row.dparam[0]	 = 0.001365174; // ;
    row.dparam[1]	 = 0.002850702;
    row.dparam[2]	 = 0.002582112;
    row.dparam[3]	 = 0.002659662;
    row.dparam[4]	 = 0.002313547;
    row.dparam[5]	 = 0.002313547;
    row.dparam[6]	 = 0.001896365;
    row.dparam[7]	 = 0.001853969;
    row.dparam[8]	 = 0.001393879;
    row.dparam[9]	 = 0.001322762;
    row.dparam[10]	 = 0.000884138;
    row.dparam[11]	 =    0.00059;
 memcpy(&row.Comment,"duuP5710",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.14664; // ;
    row.param[1]	 =   -0.12578;
    row.param[2]	 =    0.00367;
    row.param[3]	 =   -0.14984;
    row.param[4]	 =    -0.0111;
    row.param[5]	 =   -0.04474;
    row.param[6]	 =   -0.07768;
    row.param[7]	 =    -0.0153;
    row.param[8]	 =    -0.0881;
    row.param[9]	 =   -0.13039;
    row.param[10]	 =     0.1741;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.02460606; // ;
    row.dparam[1]	 =    0.04672;
    row.dparam[2]	 =    0.04401;
    row.dparam[3]	 =    0.04207;
    row.dparam[4]	 =    0.03679;
    row.dparam[5]	 =    0.03314;
    row.dparam[6]	 =    0.02739;
    row.dparam[7]	 =    0.02378;
    row.dparam[8]	 =    0.01846;
    row.dparam[9]	 =    0.01585;
    row.dparam[10]	 =    0.01041;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        202; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03866; // ;
    row.param[1]	 =     0.0105;
    row.param[2]	 =    0.00216;
    row.param[3]	 =    0.00131;
    row.param[4]	 =   -0.00175;
    row.param[5]	 =    0.00113;
    row.param[6]	 =    -0.0019;
    row.param[7]	 =     0.0022;
    row.param[8]	 =   -0.00153;
    row.param[9]	 =    0.00169;
    row.param[10]	 =   -0.00117;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001392947; // ;
    row.dparam[1]	 = 0.002782373;
    row.dparam[2]	 = 0.002548038;
    row.dparam[3]	 = 0.002442335;
    row.dparam[4]	 = 0.002133378;
    row.dparam[5]	 = 0.002008109;
    row.dparam[6]	 = 0.001645387;
    row.dparam[7]	 =    0.00146;
    row.dparam[8]	 =    0.00108;
    row.dparam[9]	 =    0.00102;
    row.dparam[10]	 =    0.00068;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6111",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        203; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.03755; // ;
    row.param[1]	 =    0.00545;
    row.param[2]	 =   -0.00841;
    row.param[3]	 =    0.01542;
    row.param[4]	 =    0.00085;
    row.param[5]	 =    0.01018;
    row.param[6]	 =   -0.00111;
    row.param[7]	 =    0.00722;
    row.param[8]	 =   -0.00361;
    row.param[9]	 =    0.00538;
    row.param[10]	 =   -0.00404;
    row.param[11]	 =    0.00076;
    row.dparam[0]	 = 0.001510132; // ;
    row.dparam[1]	 = 0.003134677;
    row.dparam[2]	 = 0.00284605;
    row.dparam[3]	 = 0.002873935;
    row.dparam[4]	 = 0.002509462;
    row.dparam[5]	 = 0.002467286;
    row.dparam[6]	 = 0.002050829;
    row.dparam[7]	 = 0.00192294;
    row.dparam[8]	 = 0.001512812;
    row.dparam[9]	 = 0.00139151;
    row.dparam[10]	 = 0.0009584362;
    row.dparam[11]	 =    0.00054;
 memcpy(&row.Comment,"duuP6211",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        204; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01919; // ;
    row.param[1]	 =     0.0161;
    row.param[2]	 =   -0.00237;
    row.param[3]	 =    0.00624;
    row.param[4]	 =   -0.00015;
    row.param[5]	 =    0.00604;
    row.param[6]	 =   -0.00202;
    row.param[7]	 =    0.00652;
    row.param[8]	 =     0.0009;
    row.param[9]	 =    0.00513;
    row.param[10]	 =    0.00037;
    row.param[11]	 =    0.00246;
    row.dparam[0]	 = 0.001286779; // ;
    row.dparam[1]	 = 0.002450694;
    row.dparam[2]	 = 0.002414995;
    row.dparam[3]	 = 0.002238258;
    row.dparam[4]	 = 0.002133589;
    row.dparam[5]	 = 0.001913165;
    row.dparam[6]	 = 0.001742986;
    row.dparam[7]	 = 0.001503795;
    row.dparam[8]	 = 0.001196035;
    row.dparam[9]	 = 0.001012423;
    row.dparam[10]	 =    0.00058;
    row.dparam[11]	 =    0.00056;
 memcpy(&row.Comment,"duuP6211",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        205; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.0319; // ;
    row.param[1]	 =   -0.01001;
    row.param[2]	 =     -7e-05;
    row.param[3]	 =   -0.00141;
    row.param[4]	 =    0.00283;
    row.param[5]	 =    -0.0014;
    row.param[6]	 =   -0.00061;
    row.param[7]	 =    -0.0023;
    row.param[8]	 =   -0.00048;
    row.param[9]	 =   -0.00097;
    row.param[10]	 =   -0.00053;
    row.param[11]	 =   -0.00017;
    row.dparam[0]	 = 0.0008900562; // ;
    row.dparam[1]	 = 0.001767767;
    row.dparam[2]	 = 0.001659187;
    row.dparam[3]	 = 0.001625608;
    row.dparam[4]	 = 0.001475805;
    row.dparam[5]	 = 0.001411559;
    row.dparam[6]	 = 0.001203079;
    row.dparam[7]	 = 0.001103087;
    row.dparam[8]	 =    0.00078;
    row.dparam[9]	 =    0.00073;
    row.dparam[10]	 =     0.0005;
    row.dparam[11]	 =    0.00048;
 memcpy(&row.Comment,"duuP6311",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        206; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00316; // ;
    row.param[1]	 =    0.00839;
    row.param[2]	 =    0.00149;
    row.param[3]	 =    0.00453;
    row.param[4]	 =   -0.00019;
    row.param[5]	 =    0.00418;
    row.param[6]	 =    0.00166;
    row.param[7]	 =    0.00421;
    row.param[8]	 =     0.0041;
    row.param[9]	 =    0.00232;
    row.param[10]	 =    0.00091;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009033825; // ;
    row.dparam[1]	 = 0.001865529;
    row.dparam[2]	 = 0.001669281;
    row.dparam[3]	 = 0.001700735;
    row.dparam[4]	 = 0.001473296;
    row.dparam[5]	 = 0.001450965;
    row.dparam[6]	 = 0.00116619;
    row.dparam[7]	 = 0.001147693;
    row.dparam[8]	 =     0.0008;
    row.dparam[9]	 =    0.00077;
    row.dparam[10]	 =    0.00052;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6311",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         11; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        207; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =    0.01892; // ;
    row.param[1]	 =   -0.00967;
    row.param[2]	 =   -0.01006;
    row.param[3]	 =   -0.00893;
    row.param[4]	 =   -0.00911;
    row.param[5]	 =   -0.00548;
    row.param[6]	 =   -0.00521;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008872993; // ;
    row.dparam[1]	 = 0.001472005;
    row.dparam[2]	 = 0.001347145;
    row.dparam[3]	 = 0.001374409;
    row.dparam[4]	 = 0.001185622;
    row.dparam[5]	 = 0.001044031;
    row.dparam[6]	 = 0.0009476286;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5112",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        208; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          6; // ;
    row.param[0]	 =    0.05789; // ;
    row.param[1]	 =    0.00672;
    row.param[2]	 =   -0.00039;
    row.param[3]	 =    0.00344;
    row.param[4]	 =    0.00151;
    row.param[5]	 =    0.00105;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0008128961; // ;
    row.dparam[1]	 = 0.001316435;
    row.dparam[2]	 = 0.001265346;
    row.dparam[3]	 = 0.001344247;
    row.dparam[4]	 = 0.001189664;
    row.dparam[5]	 = 0.001011385;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5112",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        209; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02668; // ;
    row.param[1]	 =   -0.04136;
    row.param[2]	 =   -0.00944;
    row.param[3]	 =   -0.00462;
    row.param[4]	 =   -0.00627;
    row.param[5]	 =    0.00629;
    row.param[6]	 =   -0.00824;
    row.param[7]	 =    0.00718;
    row.param[8]	 =   -0.00095;
    row.param[9]	 =    0.00894;
    row.param[10]	 =   -0.00403;
    row.param[11]	 =    0.00188;
    row.dparam[0]	 = 0.001518223; // ;
    row.dparam[1]	 = 0.003271911;
    row.dparam[2]	 = 0.002874665;
    row.dparam[3]	 = 0.00299107;
    row.dparam[4]	 = 0.002588011;
    row.dparam[5]	 = 0.002584821;
    row.dparam[6]	 = 0.002105683;
    row.dparam[7]	 = 0.002052657;
    row.dparam[8]	 = 0.001532221;
    row.dparam[9]	 = 0.00138946;
    row.dparam[10]	 = 0.0008987213;
    row.dparam[11]	 =    0.00058;
 memcpy(&row.Comment,"duuP5212",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        210; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02099; // ;
    row.param[1]	 =     0.0275;
    row.param[2]	 =    0.00075;
    row.param[3]	 =    0.00412;
    row.param[4]	 =   -0.00314;
    row.param[5]	 =    0.00453;
    row.param[6]	 =   -0.00248;
    row.param[7]	 =    0.00146;
    row.param[8]	 =    0.00065;
    row.param[9]	 =   -0.00087;
    row.param[10]	 =    0.00097;
    row.param[11]	 =   -0.00016;
    row.dparam[0]	 = 0.001827129; // ;
    row.dparam[1]	 = 0.003838229;
    row.dparam[2]	 = 0.003433657;
    row.dparam[3]	 = 0.00353102;
    row.dparam[4]	 = 0.00300463;
    row.dparam[5]	 = 0.003021407;
    row.dparam[6]	 = 0.002431358;
    row.dparam[7]	 = 0.002362478;
    row.dparam[8]	 = 0.001801555;
    row.dparam[9]	 = 0.001698117;
    row.dparam[10]	 = 0.001131636;
    row.dparam[11]	 =    0.00061;
 memcpy(&row.Comment,"duuP5212",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        211; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00512; // ;
    row.param[1]	 =   -0.02001;
    row.param[2]	 =   -0.00319;
    row.param[3]	 =   -0.00506;
    row.param[4]	 =   -0.00116;
    row.param[5]	 =   -0.00201;
    row.param[6]	 =   -0.00141;
    row.param[7]	 =   -0.00148;
    row.param[8]	 =   -0.00112;
    row.param[9]	 =    0.00053;
    row.param[10]	 =   -0.00165;
    row.param[11]	 =   -0.00121;
    row.dparam[0]	 =    0.00153; // ;
    row.dparam[1]	 = 0.003129249;
    row.dparam[2]	 = 0.002892559;
    row.dparam[3]	 = 0.002904083;
    row.dparam[4]	 = 0.002586581;
    row.dparam[5]	 = 0.00251726;
    row.dparam[6]	 = 0.002107344;
    row.dparam[7]	 = 0.001974589;
    row.dparam[8]	 = 0.001564768;
    row.dparam[9]	 = 0.001414814;
    row.dparam[10]	 = 0.001016268;
    row.dparam[11]	 =    0.00052;
 memcpy(&row.Comment,"duuP5312",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        212; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.02306; // ;
    row.param[1]	 =    0.01395;
    row.param[2]	 =    0.00465;
    row.param[3]	 =    0.00302;
    row.param[4]	 =   -0.00281;
    row.param[5]	 =    0.00514;
    row.param[6]	 =   -0.00155;
    row.param[7]	 =     0.0018;
    row.param[8]	 =    0.00318;
    row.param[9]	 =   -0.00417;
    row.param[10]	 =    0.00351;
    row.param[11]	 =   -0.00112;
    row.dparam[0]	 =  0.0015012; // ;
    row.dparam[1]	 =    0.00306;
    row.dparam[2]	 = 0.002817517;
    row.dparam[3]	 = 0.002829063;
    row.dparam[4]	 = 0.00248266;
    row.dparam[5]	 = 0.002436596;
    row.dparam[6]	 = 0.002009527;
    row.dparam[7]	 = 0.001894254;
    row.dparam[8]	 = 0.001507349;
    row.dparam[9]	 = 0.001374845;
    row.dparam[10]	 = 0.0009586449;
    row.dparam[11]	 =    0.00052;
 memcpy(&row.Comment,"duuP5312",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        213; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.01522; // ;
    row.param[1]	 =   -0.02106;
    row.param[2]	 =   -0.00404;
    row.param[3]	 =     -7e-05;
    row.param[4]	 =   -0.00385;
    row.param[5]	 =   -0.00057;
    row.param[6]	 =    0.00059;
    row.param[7]	 =    0.00103;
    row.param[8]	 =    0.00129;
    row.param[9]	 =    0.00243;
    row.param[10]	 =   -0.00051;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009087354; // ;
    row.dparam[1]	 = 0.00186325;
    row.dparam[2]	 = 0.001680774;
    row.dparam[3]	 = 0.001712308;
    row.dparam[4]	 = 0.001507846;
    row.dparam[5]	 = 0.001476279;
    row.dparam[6]	 = 0.001240645;
    row.dparam[7]	 = 0.001181059;
    row.dparam[8]	 =    0.00089;
    row.dparam[9]	 =    0.00084;
    row.dparam[10]	 =    0.00059;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5412",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        214; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00684; // ;
    row.param[1]	 =    0.01635;
    row.param[2]	 =    0.00485;
    row.param[3]	 =    0.00438;
    row.param[4]	 =   -0.00185;
    row.param[5]	 =    0.00663;
    row.param[6]	 =    0.00027;
    row.param[7]	 =    0.00202;
    row.param[8]	 =    0.00022;
    row.param[9]	 =   -0.00164;
    row.param[10]	 =     0.0011;
    row.param[11]	 =   -0.00027;
    row.dparam[0]	 = 0.001443814; // ;
    row.dparam[1]	 = 0.002996848;
    row.dparam[2]	 = 0.002737554;
    row.dparam[3]	 = 0.002760362;
    row.dparam[4]	 = 0.002442478;
    row.dparam[5]	 = 0.002384806;
    row.dparam[6]	 = 0.001968883;
    row.dparam[7]	 = 0.001853456;
    row.dparam[8]	 = 0.00146113;
    row.dparam[9]	 = 0.001394597;
    row.dparam[10]	 = 0.0009533625;
    row.dparam[11]	 =    0.00052;
 memcpy(&row.Comment,"duuP5412",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        215; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00907; // ;
    row.param[1]	 =   -0.02375;
    row.param[2]	 =    0.00113;
    row.param[3]	 =    0.00102;
    row.param[4]	 =    0.00656;
    row.param[5]	 =    0.00117;
    row.param[6]	 =    0.00052;
    row.param[7]	 =    0.00812;
    row.param[8]	 =   -0.00249;
    row.param[9]	 =    0.00524;
    row.param[10]	 =     0.0002;
    row.param[11]	 =     0.0009;
    row.dparam[0]	 = 0.001554413; // ;
    row.dparam[1]	 = 0.003651739;
    row.dparam[2]	 = 0.002918578;
    row.dparam[3]	 = 0.003357946;
    row.dparam[4]	 = 0.002599885;
    row.dparam[5]	 = 0.002876578;
    row.dparam[6]	 = 0.002119174;
    row.dparam[7]	 = 0.002281162;
    row.dparam[8]	 = 0.001538083;
    row.dparam[9]	 = 0.001627575;
    row.dparam[10]	 = 0.0009954898;
    row.dparam[11]	 =    0.00052;
 memcpy(&row.Comment,"duuP5512",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        216; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.04414; // ;
    row.param[1]	 =    0.04193;
    row.param[2]	 =    0.00297;
    row.param[3]	 =    0.00728;
    row.param[4]	 =   -0.00108;
    row.param[5]	 =      9e-05;
    row.param[6]	 =    0.00427;
    row.param[7]	 =   -0.01124;
    row.param[8]	 =    0.00615;
    row.param[9]	 =   -0.01102;
    row.param[10]	 =    0.00347;
    row.param[11]	 =   -0.00114;
    row.dparam[0]	 = 0.001596747; // ;
    row.dparam[1]	 = 0.003752453;
    row.dparam[2]	 = 0.003040411;
    row.dparam[3]	 = 0.003481077;
    row.dparam[4]	 = 0.002755449;
    row.dparam[5]	 = 0.003018824;
    row.dparam[6]	 = 0.002255881;
    row.dparam[7]	 = 0.002394953;
    row.dparam[8]	 = 0.001619969;
    row.dparam[9]	 = 0.001673559;
    row.dparam[10]	 = 0.0009782127;
    row.dparam[11]	 =    0.00051;
 memcpy(&row.Comment,"duuP5512",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        217; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00534; // ;
    row.param[1]	 =   -0.04599;
    row.param[2]	 =      7e-05;
    row.param[3]	 =   -0.00616;
    row.param[4]	 =    0.00466;
    row.param[5]	 =    0.00223;
    row.param[6]	 =   -0.00153;
    row.param[7]	 =    0.00589;
    row.param[8]	 =    0.00021;
    row.param[9]	 =    0.00413;
    row.param[10]	 =    0.00114;
    row.param[11]	 =    0.00138;
    row.dparam[0]	 = 0.001443676; // ;
    row.dparam[1]	 = 0.002996748;
    row.dparam[2]	 = 0.002714001;
    row.dparam[3]	 = 0.002731099;
    row.dparam[4]	 = 0.002430741;
    row.dparam[5]	 = 0.00233844;
    row.dparam[6]	 = 0.001968781;
    row.dparam[7]	 = 0.001853348;
    row.dparam[8]	 = 0.001443399;
    row.dparam[9]	 = 0.00136832;
    row.dparam[10]	 = 0.0009468896;
    row.dparam[11]	 =    0.00051;
 memcpy(&row.Comment,"duuP5612",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        218; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          8; // ;
    row.param[0]	 =    -0.0584; // ;
    row.param[1]	 =    0.04506;
    row.param[2]	 =    0.00736;
    row.param[3]	 =    0.01288;
    row.param[4]	 =   -0.00028;
    row.param[5]	 =   -0.00012;
    row.param[6]	 =    0.00229;
    row.param[7]	 =   -0.00129;
    row.param[8]	 =    0.00185;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001013607; // ;
    row.dparam[1]	 = 0.001894888;
    row.dparam[2]	 = 0.001724819;
    row.dparam[3]	 = 0.001584014;
    row.dparam[4]	 = 0.001439653;
    row.dparam[5]	 = 0.001056882;
    row.dparam[6]	 =    0.00085;
    row.dparam[7]	 =    0.00064;
    row.dparam[8]	 =    0.00057;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5612",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        219; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.04857; // ;
    row.param[1]	 =    -0.0148;
    row.param[2]	 =     0.0023;
    row.param[3]	 =   -0.00572;
    row.param[4]	 =    0.00884;
    row.param[5]	 =   -0.00301;
    row.param[6]	 =    0.00284;
    row.param[7]	 =    0.00708;
    row.param[8]	 =   -0.00189;
    row.param[9]	 =    0.00497;
    row.param[10]	 =    0.00131;
    row.param[11]	 =    0.00022;
    row.dparam[0]	 = 0.001565663; // ;
    row.dparam[1]	 = 0.003293661;
    row.dparam[2]	 = 0.002963731;
    row.dparam[3]	 = 0.003033595;
    row.dparam[4]	 = 0.002640057;
    row.dparam[5]	 = 0.002606089;
    row.dparam[6]	 = 0.002131314;
    row.dparam[7]	 = 0.002056842;
    row.dparam[8]	 = 0.001570796;
    row.dparam[9]	 = 0.001490637;
    row.dparam[10]	 = 0.0009990495;
    row.dparam[11]	 =    0.00052;
 memcpy(&row.Comment,"duuP5712",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        220; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         12; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.05927; // ;
    row.param[1]	 =     0.0401;
    row.param[2]	 =    0.01381;
    row.param[3]	 =    0.00759;
    row.param[4]	 =    0.00549;
    row.param[5]	 =   -0.00027;
    row.param[6]	 =       0.01;
    row.param[7]	 =   -0.01095;
    row.param[8]	 =    0.00607;
    row.param[9]	 =   -0.00795;
    row.param[10]	 =    0.00127;
    row.param[11]	 =   -0.00184;
    row.dparam[0]	 = 0.00178418; // ;
    row.dparam[1]	 = 0.00372399;
    row.dparam[2]	 = 0.003366081;
    row.dparam[3]	 = 0.003406729;
    row.dparam[4]	 = 0.003019752;
    row.dparam[5]	 = 0.002963258;
    row.dparam[6]	 = 0.002472367;
    row.dparam[7]	 = 0.002369008;
    row.dparam[8]	 = 0.001802387;
    row.dparam[9]	 = 0.001686891;
    row.dparam[10]	 = 0.001097178;
    row.dparam[11]	 =    0.00057;
 memcpy(&row.Comment,"duuP5712",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        221; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00557; // ;
    row.param[1]	 =    0.00414;
    row.param[2]	 =   -0.00655;
    row.param[3]	 =   -0.00743;
    row.param[4]	 =    0.00274;
    row.param[5]	 =   -0.00785;
    row.param[6]	 =    0.00011;
    row.param[7]	 =    -0.0041;
    row.param[8]	 =    -0.0025;
    row.param[9]	 =   -0.00109;
    row.param[10]	 =    0.00021;
    row.param[11]	 =    0.00041;
    row.dparam[0]	 = 0.00150768; // ;
    row.dparam[1]	 = 0.003101564;
    row.dparam[2]	 = 0.002865205;
    row.dparam[3]	 = 0.002864577;
    row.dparam[4]	 = 0.002517936;
    row.dparam[5]	 = 0.002442724;
    row.dparam[6]	 = 0.002015416;
    row.dparam[7]	 = 0.001900132;
    row.dparam[8]	 = 0.001449517;
    row.dparam[9]	 = 0.001328608;
    row.dparam[10]	 = 0.0008720665;
    row.dparam[11]	 =    0.00047;
 memcpy(&row.Comment,"duuP6413",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        222; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =     0.0399; // ;
    row.param[1]	 =    0.00629;
    row.param[2]	 =   -0.00117;
    row.param[3]	 =    0.00136;
    row.param[4]	 =   -0.00254;
    row.param[5]	 =    0.00344;
    row.param[6]	 =   -0.00434;
    row.param[7]	 =     0.0015;
    row.param[8]	 =   -0.00211;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005780138; // ;
    row.dparam[1]	 = 0.001182244;
    row.dparam[2]	 = 0.001046231;
    row.dparam[3]	 = 0.001070747;
    row.dparam[4]	 = 0.0008987213;
    row.dparam[5]	 = 0.0009013878;
    row.dparam[6]	 = 0.0006964194;
    row.dparam[7]	 = 0.0006964194;
    row.dparam[8]	 =    0.00041;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6413",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        223; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         10; // ;
    row.param[0]	 =   -0.03035; // ;
    row.param[1]	 =   -0.13752;
    row.param[2]	 =     0.3033;
    row.param[3]	 =   -0.27236;
    row.param[4]	 =    0.21335;
    row.param[5]	 =    -0.1599;
    row.param[6]	 =    0.11017;
    row.param[7]	 =   -0.06577;
    row.param[8]	 =    0.04192;
    row.param[9]	 =   -0.01545;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.000462277; // ;
    row.dparam[1]	 = 0.0007242237;
    row.dparam[2]	 = 0.0007021396;
    row.dparam[3]	 = 0.0005866856;
    row.dparam[4]	 = 0.0006090156;
    row.dparam[5]	 = 0.0005060632;
    row.dparam[6]	 =     0.0005;
    row.dparam[7]	 =    0.00029;
    row.dparam[8]	 =     0.0003;
    row.dparam[9]	 =    0.00278;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6513",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        224; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.00105; // ;
    row.param[1]	 =   -0.00578;
    row.param[2]	 =   -0.00568;
    row.param[3]	 =   -0.00659;
    row.param[4]	 =    0.00197;
    row.param[5]	 =   -0.00594;
    row.param[6]	 =    0.00252;
    row.param[7]	 =   -0.00368;
    row.param[8]	 =    0.00364;
    row.param[9]	 =   -0.00085;
    row.param[10]	 =    0.00203;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001426219; // ;
    row.dparam[1]	 = 0.003092329;
    row.dparam[2]	 = 0.002682872;
    row.dparam[3]	 = 0.002839859;
    row.dparam[4]	 = 0.002347765;
    row.dparam[5]	 =     0.0024;
    row.dparam[6]	 =    0.00183;
    row.dparam[7]	 =    0.00185;
    row.dparam[8]	 =     0.0013;
    row.dparam[9]	 =    0.00125;
    row.dparam[10]	 =    0.00075;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6613",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        225; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =   -0.00337; // ;
    row.param[1]	 =    0.00194;
    row.param[2]	 =   -0.01025;
    row.param[3]	 =   -0.00564;
    row.param[4]	 =   -0.00139;
    row.param[5]	 =   -0.00085;
    row.param[6]	 =    0.00127;
    row.param[7]	 =   -0.00208;
    row.param[8]	 =   -0.00107;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.002023092; // ;
    row.dparam[1]	 = 0.003998762;
    row.dparam[2]	 = 0.003685675;
    row.dparam[3]	 = 0.003438692;
    row.dparam[4]	 = 0.002932337;
    row.dparam[5]	 = 0.002536651;
    row.dparam[6]	 = 0.001958188;
    row.dparam[7]	 =    0.00152;
    row.dparam[8]	 =    0.00098;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP6713",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        226; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         13; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.03523; // ;
    row.param[1]	 =    0.02268;
    row.param[2]	 =    0.00601;
    row.param[3]	 =    0.01025;
    row.param[4]	 =   -0.00115;
    row.param[5]	 =    0.00952;
    row.param[6]	 =   -0.00539;
    row.param[7]	 =    0.00543;
    row.param[8]	 =   -0.00647;
    row.param[9]	 =    0.00153;
    row.param[10]	 =   -0.00266;
    row.param[11]	 =    0.00102;
    row.dparam[0]	 = 0.001166748; // ;
    row.dparam[1]	 = 0.002432447;
    row.dparam[2]	 = 0.002227487;
    row.dparam[3]	 = 0.002269824;
    row.dparam[4]	 = 0.001980101;
    row.dparam[5]	 = 0.001958699;
    row.dparam[6]	 = 0.001605522;
    row.dparam[7]	 = 0.001541493;
    row.dparam[8]	 = 0.001173882;
    row.dparam[9]	 = 0.001103177;
    row.dparam[10]	 = 0.0007495332;
    row.dparam[11]	 =    0.00049;
 memcpy(&row.Comment,"duuP6713",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        227; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =     0.0292; // ;
    row.param[1]	 =   -0.00695;
    row.param[2]	 =    0.01122;
    row.param[3]	 =   -0.00369;
    row.param[4]	 =    0.00504;
    row.param[5]	 =   -0.00068;
    row.param[6]	 =    0.00189;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00544945; // ;
    row.dparam[1]	 = 0.01073984;
    row.dparam[2]	 =    0.00923;
    row.dparam[3]	 =    0.00787;
    row.dparam[4]	 =    0.00565;
    row.dparam[5]	 =    0.00418;
    row.dparam[6]	 =    0.00227;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5514",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        228; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.04757; // ;
    row.param[1]	 =   -0.03415;
    row.param[2]	 =    0.00661;
    row.param[3]	 =    0.00012;
    row.param[4]	 =   -0.00081;
    row.param[5]	 =    0.00011;
    row.param[6]	 =    0.00195;
    row.param[7]	 =   -0.00284;
    row.param[8]	 =    0.00184;
    row.param[9]	 =    0.00059;
    row.param[10]	 =   -0.00051;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001134548; // ;
    row.dparam[1]	 = 0.002275016;
    row.dparam[2]	 = 0.002129272;
    row.dparam[3]	 = 0.002083315;
    row.dparam[4]	 = 0.001879707;
    row.dparam[5]	 = 0.001777892;
    row.dparam[6]	 = 0.001544668;
    row.dparam[7]	 = 0.00139517;
    row.dparam[8]	 = 0.00115434;
    row.dparam[9]	 = 0.00101548;
    row.dparam[10]	 = 0.0007924645;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5614",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        229; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.13491; // ;
    row.param[1]	 =    0.12707;
    row.param[2]	 =    0.03232;
    row.param[3]	 =    0.04485;
    row.param[4]	 =   -0.04527;
    row.param[5]	 =    0.12148;
    row.param[6]	 =    0.27077;
    row.param[7]	 =    0.03449;
    row.param[8]	 =   -0.11226;
    row.param[9]	 =    0.04332;
    row.param[10]	 =    0.02772;
    row.param[11]	 =   -0.18165;
    row.dparam[0]	 = 0.01336783; // ;
    row.dparam[1]	 = 0.01755513;
    row.dparam[2]	 = 0.01371499;
    row.dparam[3]	 = 0.01576784;
    row.dparam[4]	 = 0.01515829;
    row.dparam[5]	 =  0.0180009;
    row.dparam[6]	 = 0.01754235;
    row.dparam[7]	 = 0.01981443;
    row.dparam[8]	 = 0.01700034;
    row.dparam[9]	 = 0.01861024;
    row.dparam[10]	 = 0.01500526;
    row.dparam[11]	 =     0.0078;
 memcpy(&row.Comment,"duuP5614",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        230; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    0.00487; // ;
    row.param[1]	 =   -0.00274;
    row.param[2]	 =    0.00244;
    row.param[3]	 =   -0.00677;
    row.param[4]	 =    -0.0043;
    row.param[5]	 =   -0.00636;
    row.param[6]	 =   -0.00098;
    row.param[7]	 =   -0.00747;
    row.param[8]	 =   -0.00363;
    row.param[9]	 =   -0.00298;
    row.param[10]	 =   -0.00102;
    row.param[11]	 =     -1e-05;
    row.dparam[0]	 = 0.001501666; // ;
    row.dparam[1]	 = 0.003217903;
    row.dparam[2]	 = 0.00283586;
    row.dparam[3]	 = 0.002986453;
    row.dparam[4]	 = 0.002506272;
    row.dparam[5]	 = 0.002564527;
    row.dparam[6]	 = 0.002038259;
    row.dparam[7]	 = 0.002038455;
    row.dparam[8]	 = 0.00152427;
    row.dparam[9]	 = 0.001507083;
    row.dparam[10]	 = 0.001004589;
    row.dparam[11]	 =    0.00055;
 memcpy(&row.Comment,"duuP5714",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        231; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         14; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.1479; // ;
    row.param[1]	 =   -0.36059;
    row.param[2]	 =   -0.33093;
    row.param[3]	 =   -0.25742;
    row.param[4]	 =   -0.39592;
    row.param[5]	 =   -0.24682;
    row.param[6]	 =   -0.15695;
    row.param[7]	 =   -0.28793;
    row.param[8]	 =   -0.22496;
    row.param[9]	 =    0.02879;
    row.param[10]	 =    -0.2207;
    row.param[11]	 =   -0.08018;
    row.dparam[0]	 = 0.01115117; // ;
    row.dparam[1]	 = 0.02069288;
    row.dparam[2]	 = 0.01914725;
    row.dparam[3]	 = 0.01883667;
    row.dparam[4]	 = 0.01656206;
    row.dparam[5]	 = 0.01581795;
    row.dparam[6]	 = 0.01309009;
    row.dparam[7]	 = 0.01202399;
    row.dparam[8]	 = 0.008983106;
    row.dparam[9]	 = 0.00845284;
    row.dparam[10]	 = 0.005319323;
    row.dparam[11]	 =    0.00364;
 memcpy(&row.Comment,"duuP5714",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          6; // ;
    row.ladder	 =         15; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        232; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =    -0.0617; // ;
    row.param[1]	 =    0.02191;
    row.param[2]	 =    0.00112;
    row.param[3]	 =   -0.00509;
    row.param[4]	 =    0.00362;
    row.param[5]	 =      0.002;
    row.param[6]	 =    0.00439;
    row.param[7]	 =    0.00123;
    row.param[8]	 =    0.00595;
    row.param[9]	 =    0.00404;
    row.param[10]	 =    0.00182;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.001097315; // ;
    row.dparam[1]	 = 0.002488534;
    row.dparam[2]	 = 0.002063201;
    row.dparam[3]	 = 0.002292968;
    row.dparam[4]	 = 0.001836001;
    row.dparam[5]	 =    0.00195;
    row.dparam[6]	 =    0.00145;
    row.dparam[7]	 =    0.00154;
    row.dparam[8]	 =    0.00107;
    row.dparam[9]	 =    0.00108;
    row.dparam[10]	 =    0.00066;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5116",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        233; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          1; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          7; // ;
    row.param[0]	 =   -0.01304; // ;
    row.param[1]	 =    0.00364;
    row.param[2]	 =    0.01175;
    row.param[3]	 =    0.01211;
    row.param[4]	 =    0.00856;
    row.param[5]	 =    0.00837;
    row.param[6]	 =    0.00078;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0006041523; // ;
    row.dparam[1]	 = 0.001176308;
    row.dparam[2]	 =    0.00091;
    row.dparam[3]	 =    0.00095;
    row.dparam[4]	 =     0.0008;
    row.dparam[5]	 =    0.00082;
    row.dparam[6]	 =    0.00061;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5116",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        234; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =          5; // ;
    row.param[0]	 =   -0.04309; // ;
    row.param[1]	 =    0.00724;
    row.param[2]	 =   -0.00501;
    row.param[3]	 =    -0.0024;
    row.param[4]	 =   -0.00189;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0004657252; // ;
    row.dparam[1]	 =    0.00066;
    row.dparam[2]	 =    0.00056;
    row.dparam[3]	 =    0.00056;
    row.dparam[4]	 =    0.00044;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5216",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        235; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          2; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          6; // ;
    row.param[0]	 =    0.00475; // ;
    row.param[1]	 =    0.00102;
    row.param[2]	 =    0.01127;
    row.param[3]	 =    0.00994;
    row.param[4]	 =    0.00957;
    row.param[5]	 =    0.00418;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0005142956; // ;
    row.dparam[1]	 =    0.00077;
    row.dparam[2]	 =    0.00079;
    row.dparam[3]	 =    0.00068;
    row.dparam[4]	 =     0.0007;
    row.dparam[5]	 =    0.00054;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5216",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        236; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.04581; // ;
    row.param[1]	 =    0.01535;
    row.param[2]	 =   -0.00614;
    row.param[3]	 =   -0.00895;
    row.param[4]	 =     0.0005;
    row.param[5]	 =   -0.00828;
    row.param[6]	 =    0.00248;
    row.param[7]	 =   -0.00264;
    row.param[8]	 =    0.00128;
    row.param[9]	 =   -0.00014;
    row.param[10]	 =     0.0001;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.00105423; // ;
    row.dparam[1]	 = 0.002265502;
    row.dparam[2]	 =    0.00189;
    row.dparam[3]	 =    0.00205;
    row.dparam[4]	 =    0.00171;
    row.dparam[5]	 =    0.00179;
    row.dparam[6]	 =     0.0014;
    row.dparam[7]	 =     0.0014;
    row.dparam[8]	 =    0.00101;
    row.dparam[9]	 =    0.00096;
    row.dparam[10]	 =     0.0006;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5316",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        237; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          3; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =    0.01644; // ;
    row.param[1]	 =    0.00124;
    row.param[2]	 =    0.00671;
    row.param[3]	 =    0.01228;
    row.param[4]	 =    0.00706;
    row.param[5]	 =    0.00891;
    row.param[6]	 =     0.0049;
    row.param[7]	 =    0.00592;
    row.param[8]	 =    0.00124;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0009300538; // ;
    row.dparam[1]	 = 0.001864672;
    row.dparam[2]	 = 0.001675291;
    row.dparam[3]	 = 0.001668802;
    row.dparam[4]	 = 0.001412161;
    row.dparam[5]	 = 0.001307823;
    row.dparam[6]	 =    0.00093;
    row.dparam[7]	 =    0.00091;
    row.dparam[8]	 =    0.00061;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5316",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        238; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         11; // ;
    row.param[0]	 =   -0.02653; // ;
    row.param[1]	 =    0.01402;
    row.param[2]	 =   -0.00073;
    row.param[3]	 =   -0.00556;
    row.param[4]	 =    0.00076;
    row.param[5]	 =   -0.00505;
    row.param[6]	 =   -0.00159;
    row.param[7]	 =   -0.00343;
    row.param[8]	 =   -0.00044;
    row.param[9]	 =   -0.00245;
    row.param[10]	 =    0.00137;
    row.param[11]	 =   -0.00088;
    row.dparam[0]	 = 0.001466765; // ;
    row.dparam[1]	 = 0.003025525;
    row.dparam[2]	 = 0.00277175;
    row.dparam[3]	 = 0.002777211;
    row.dparam[4]	 = 0.002454119;
    row.dparam[5]	 = 0.002378865;
    row.dparam[6]	 = 0.001986152;
    row.dparam[7]	 = 0.001870829;
    row.dparam[8]	 = 0.001443399;
    row.dparam[9]	 = 0.001333754;
    row.dparam[10]	 = 0.0009295698;
    row.dparam[11]	 =    0.00045;
 memcpy(&row.Comment,"duuP5416",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          2; // ;
    row.idx	 =        239; // ;
    row.nrows	 =        239; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          4; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =          9; // ;
    row.param[0]	 =    0.04767; // ;
    row.param[1]	 =   -0.00189;
    row.param[2]	 =    0.01796;
    row.param[3]	 =     0.0231;
    row.param[4]	 =    0.01606;
    row.param[5]	 =    0.01581;
    row.param[6]	 =    0.00926;
    row.param[7]	 =     0.0074;
    row.param[8]	 =    0.00094;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 = 0.0007334848; // ;
    row.dparam[1]	 = 0.001598906;
    row.dparam[2]	 = 0.001313202;
    row.dparam[3]	 = 0.001452067;
    row.dparam[4]	 =    0.00109;
    row.dparam[5]	 =    0.00118;
    row.dparam[6]	 =    0.00089;
    row.dparam[7]	 =    0.00091;
    row.dparam[8]	 =    0.00059;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"duuP5416",8);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          5; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          6; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          1; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
 memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
memset(&row,0,tableSet->GetRowSize());
    row.type	 =          0; // ;
    row.idx	 =          0; // ;
    row.nrows	 =          0; // ;
    row.barrel	 =          3; // ;
    row.layer	 =          5; // ;
    row.ladder	 =         16; // ;
    row.wafer	 =          7; // ;
    row.hybrid	 =          2; // ;
    row.Npar	 =         -1; // ;
    row.param[0]	 =          0; // ;
    row.param[1]	 =          0;
    row.param[2]	 =          0;
    row.param[3]	 =          0;
    row.param[4]	 =          0;
    row.param[5]	 =          0;
    row.param[6]	 =          0;
    row.param[7]	 =          0;
    row.param[8]	 =          0;
    row.param[9]	 =          0;
    row.param[10]	 =          0;
    row.param[11]	 =          0;
    row.dparam[0]	 =          0; // ;
    row.dparam[1]	 =          0;
    row.dparam[2]	 =          0;
    row.dparam[3]	 =          0;
    row.dparam[4]	 =          0;
    row.dparam[5]	 =          0;
    row.dparam[6]	 =          0;
    row.dparam[7]	 =          0;
    row.dparam[8]	 =          0;
    row.dparam[9]	 =          0;
    row.dparam[10]	 =          0;
    row.dparam[11]	 =          0;
memcpy(&row.Comment,"\x00",1);// 
tableSet->AddAt(&row);
  //
  // ----------------- end of code ---------------
  //20050217.121412  /  cuProductionHighTower/FullField
  struct data_t {
    Int_t type, idx, nrows, barrel, layer, ladder, wafer, hybrid, Npar;
    Double_t p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11; //param[12];
    Double_t dp0, dp1, dp2, dp3, dp4, dp5, dp6, dp7, dp8, dp9, dp10, dp11; //dparam[12];
    Char_t *Comment;
  };

  data_t Data0[] = {
/* 	{2,0,0,1,2, 1, 1, 1, 9, */
/*   0.00093, 0.00000,-0.00187, 0.00154, 0.00139, 0.00000, 0.00198, 0.00000, 0.00000, 0.00193, 0.00000, 0.00000 , */
/*   0.00004, 0.00000, 0.00002, 0.00008, 0.00002, 0.00000, 0.00006, 0.00000, 0.00000, 0.00004, 0.00000, 0.00000 , */
/* "duuP2101"}, */
/* 	{2,0,0,1,2, 1, 2, 1, 9, */
/*  -46.98304,81.58633,-52.83259,24.48701,-7.39461, 1.10309, 0.00000, 0.00000, 0.00000,-0.01124, 0.00000, 0.00000 , */
/*   0.00012, 0.00018, 0.00029, 0.00016, 0.00014, 0.00018, 0.00000, 0.00000, 0.00000, 0.00006, 0.00000, 0.00000 , */
/* "duuP2201"}, */
	{2,0,0,1,2, 1, 3, 1,11,
  0.00003,-0.00013,-0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00002 ,
  0.00000, 0.00001, 0.00002, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00001 ,
"duuP2301"},
	{2,0,0,1,2, 1, 3, 2, 3,
 -0.00012, 0.00028, 0.00018,-0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00001, 0.00001, 0.00002, 0.00001, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP2301"},
	{2,0,0,1,2, 1, 4, 1, 4,
  0.00015, 0.00006,-0.00004,-0.00013,-0.00005, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00002, 0.00003, 0.00003, 0.00002, 0.00002, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP2401"},
	{2,0,0,1,2, 1, 4, 2,11,
 -0.00010, 0.00034, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000, 0.00001, 0.00000,-0.00001,-0.00002, 0.00002 ,
  0.00000, 0.00001, 0.00001, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP2401"},
	{2,0,0,1,1, 2, 1, 1, 9,
 -0.01283,-0.00763, 0.00000, 0.00000, 0.00000, 0.00000,-0.00338, 0.00000, 0.00000, 0.00161, 0.00000, 0.00000 ,
  0.00006, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00008, 0.00000, 0.00000, 0.00008, 0.00000, 0.00000 ,
"duuP1102"},
	{2,0,0,1,1, 2, 1, 2, 8,
 -0.05098, 0.00988, 0.00295, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00219, 0.00000, 0.00000, 0.00000 ,
  0.00011, 0.00017, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000 ,
"duuP1102"},
	{2,0,0,1,1, 2, 2, 1, 5,
 -0.01747,-0.01013, 0.00000, 0.00000, 0.00000, 0.00170, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00005, 0.00009, 0.00000, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP1202"},
	{2,0,0,1,1, 2, 2, 2,11,
 -0.04866, 0.00263, 0.00000, 0.00000, 0.00000, 0.00000, 0.00167,-0.00189, 0.00000,-0.00152, 0.00000, 0.00192 ,
  0.00008, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00011, 0.00000, 0.00012, 0.00000, 0.00011 ,
"duuP1202"},
	{2,0,0,1,2, 3, 1, 1, 6,
 -0.02412,-0.01524,-0.01020, 0.00351,-0.00629, 0.00000,-0.00240, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00027, 0.00037, 0.00047, 0.00027, 0.00038, 0.00000, 0.00025, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP2103"},
	{2,0,0,1,2, 3, 1, 2, 5,
 -0.03583, 0.03669, 0.01176, 0.01073, 0.00484, 0.00533, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00027, 0.00022, 0.00025, 0.00017, 0.00018, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP2103"},
	{2,0,0,1,2, 3, 2, 1,11,
 -0.02886,-0.00998,-0.00407, 0.00257,-0.00268, 0.00000, 0.00000, 0.00000, 0.00149, 0.00086, 0.00000,-0.00189 ,
  0.00020, 0.00033, 0.00034, 0.00024, 0.00025, 0.00000, 0.00000, 0.00000, 0.00016, 0.00018, 0.00000, 0.00018 ,
"duuP2203"},
	{2,0,0,1,2, 3, 2, 2, 6,
 -0.03440, 0.01855, 0.01293, 0.00359, 0.00652, 0.00000, 0.00282, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00019, 0.00029, 0.00032, 0.00024, 0.00028, 0.00000, 0.00024, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP2203"},
/* 	{2,0,0,1,1, 4, 1, 1,10, */
/*   0.00224, 0.00040, 0.00205, 0.00000, 0.00000, 0.00000, 0.00000, 0.00061,-0.00024, 0.00000,-0.00039, 0.00000 , */
/*   0.00014, 0.00014, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00003, 0.00003, 0.00000, 0.00003, 0.00000 , */
/* "duuP1104"}, */
/* 	{2,0,0,1,1, 4, 1, 2, 9, */
/*   1.04870,-1.79100, 1.12163,-0.46500, 0.11198, 0.00000, 0.00000, 0.00000, 0.00000, 0.00127, 0.00000, 0.00000 , */
/*   0.00007, 0.00011, 0.00011, 0.00009, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000 , */
/* "duuP1104"}, */
	{2,0,0,1,1, 4, 2, 1,11,
  0.00018,-0.00076, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00009 ,
  0.00003, 0.00002, 0.00004, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00001 ,
"duuP1204"},
	{2,0,0,1,1, 4, 2, 2,10,
 -0.00057, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00030, 0.00021, 0.00000 ,
  0.00001, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00001, 0.00001, 0.00000 ,
"duuP1204"},
/* 	{2,0,0,1,1, 4, 4, 2, 4, */
/*   0.01664,-0.02606, 0.02237,-0.00902, 0.00504, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/*   0.00007, 0.00026, 0.00009, 0.00008, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/* "duuP1404"}, */
/* 	{2,0,0,1,2, 5, 2, 1, 3, */
/*  -0.00666,-0.01617,-0.00736,-0.00449, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/*   0.00020, 0.00046, 0.00021, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/* "duuP2205"}, */
	{2,0,0,1,2, 5, 2, 2,11,
 -0.00077, 0.00032,-0.00057, 0.00000,-0.00034, 0.00000, 0.00000, 0.00000, 0.00000,-0.00001,-0.00002,-0.00004 ,
  0.00007, 0.00001, 0.00010, 0.00000, 0.00004, 0.00000, 0.00000, 0.00000, 0.00000, 0.00001, 0.00001, 0.00001 ,
"duuP2205"},
/* 	{2,0,0,1,2, 5, 3, 1, 8, */
/*   0.00280,-0.00513, 0.00167, 0.00000, 0.00000, 0.00000, 0.00020, 0.00000, 0.00003, 0.00000, 0.00000, 0.00000 , */
/*   0.00017, 0.00025, 0.00013, 0.00000, 0.00000, 0.00000, 0.00003, 0.00000, 0.00001, 0.00000, 0.00000, 0.00000 , */
/* "duuP2305"}, */
/* 	{2,0,0,1,2, 5, 3, 2,10, */
/*   0.00233, 0.00845, 0.00399, 0.00616, 0.00226, 0.00352, 0.00076, 0.00132, 0.00000, 0.00033,-0.00008, 0.00000 , */
/*   0.00088, 0.00214, 0.00145, 0.00153, 0.00080, 0.00076, 0.00024, 0.00024, 0.00000, 0.00004, 0.00002, 0.00000 , */
/* "duuP2305"}, */
	{2,0,0,1,2, 5, 4, 1,11,
 -0.00038,-0.00143,-0.00044, 0.00000, 0.00052, 0.00000, 0.00013, 0.00000, 0.00035, 0.00000, 0.00000,-0.00012 ,
  0.00002, 0.00001, 0.00003, 0.00000, 0.00002, 0.00000, 0.00002, 0.00000, 0.00001, 0.00000, 0.00000, 0.00001 ,
"duuP2405"},
	{2,0,0,1,2, 5, 4, 2,11,
  0.00015, 0.00038, 0.00018, 0.00000, 0.00000, 0.00000, 0.00000,-0.00000, 0.00000, 0.00001, 0.00000,-0.00003 ,
  0.00002, 0.00001, 0.00002, 0.00000, 0.00000, 0.00000, 0.00000, 0.00001, 0.00000, 0.00001, 0.00000, 0.00001 ,
"duuP2405"},
	{2,0,0,1,1, 6, 1, 1, 7,
  0.03112,-0.02274,-0.01247,-0.00109,-0.00296, 0.00145, 0.00000, 0.00444, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00022, 0.00014, 0.00019, 0.00011, 0.00015, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP1106"},
	{2,0,0,1,1, 6, 1, 2,10,
  0.02137, 0.01647, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00141, 0.00000, 0.00000, 0.00254, 0.00000 ,
  0.00005, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000, 0.00007, 0.00000 ,
"duuP1106"},
	{2,0,0,1,1, 6, 2, 1, 7,
  0.03374,-0.02262,-0.00845,-0.00139,-0.00538, 0.00154, 0.00000, 0.00508, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00020, 0.00013, 0.00017, 0.00010, 0.00013, 0.00000, 0.00009, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP1206"},
	{2,0,0,1,1, 6, 2, 2,10,
  0.02450, 0.01115, 0.00000,-0.00052, 0.00000,-0.00372, 0.00000,-0.00218, 0.00000, 0.00000, 0.00116, 0.00000 ,
  0.00005, 0.00016, 0.00000, 0.00014, 0.00000, 0.00011, 0.00000, 0.00009, 0.00000, 0.00000, 0.00007, 0.00000 ,
"duuP1206"},
	{2,0,0,1,1, 6, 3, 1, 6,
  0.02940,-0.03087,-0.01941,-0.00819,-0.01029,-0.00341,-0.00277, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00015, 0.00025, 0.00026, 0.00021, 0.00021, 0.00014, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP1306"},
	{2,0,0,1,1, 6, 3, 2,10,
  0.02155, 0.01449, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00089, 0.00000, 0.00000, 0.00237, 0.00000 ,
  0.00006, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00008, 0.00000, 0.00000, 0.00008, 0.00000 ,
"duuP1306"},
	{2,0,0,1,1, 6, 4, 1,10,
  0.03335,-0.02804,-0.00942,-0.00349,-0.00475, 0.00000, 0.00000, 0.00000, 0.00000,-0.00275,-0.00155, 0.00000 ,
  0.00007, 0.00011, 0.00012, 0.00010, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00008, 0.00008, 0.00000 ,
"duuP1406"},
	{2,0,0,1,1, 6, 4, 2,10,
  0.02188, 0.01501, 0.00000,-0.00171, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00213, 0.00000 ,
  0.00005, 0.00013, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00007, 0.00000 ,
"duuP1406"},
	{2,0,0,1,2, 7, 3, 1, 6,
  0.04469,-0.01082, 0.00000, 0.00000, 0.00000, 0.00000,-0.00382, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP2307"},
	{2,0,0,1,2, 7, 3, 2,10,
  0.01304, 0.01501,-0.00280, 0.00000, 0.00000,-0.00241, 0.00156,-0.00187, 0.00000, 0.00000,-0.00152, 0.00000 ,
  0.00010, 0.00015, 0.00014, 0.00000, 0.00000, 0.00011, 0.00010, 0.00012, 0.00000, 0.00000, 0.00010, 0.00000 ,
"duuP2307"},
	{2,0,0,1,2, 7, 4, 1,11,
  0.04548,-0.01525, 0.00000,-0.00347, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00147, 0.00193 ,
  0.00009, 0.00020, 0.00000, 0.00016, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00012 ,
"duuP2407"},
	{2,0,0,1,1, 8, 1, 1, 9,
 -0.00009, 0.00000, 0.00037,-0.00045, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00027, 0.00000, 0.00000 ,
  0.00004, 0.00000, 0.00006, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00000, 0.00000 ,
"duuP1108"},
	{2,0,0,1,1, 8, 1, 2, 9,
  0.00007, 0.00000,-0.00021, 0.00002, 0.00000, 0.00000, 0.00000, 0.00031, 0.00000, 0.00018, 0.00000, 0.00000 ,
  0.00005, 0.00000, 0.00006, 0.00011, 0.00000, 0.00000, 0.00000, 0.00007, 0.00000, 0.00006, 0.00000, 0.00000 ,
"duuP1108"},
	{2,0,0,1,1, 8, 2, 1, 4,
 -0.00248,-0.00447,-0.00296,-0.00221,-0.00062, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00061, 0.00108, 0.00079, 0.00045, 0.00019, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP1208"},
	{2,0,0,1,1, 8, 2, 2, 3,
  0.00013, 0.00000, 0.00000,-0.00058, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00000, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP1208"},
/* 	{2,0,0,1,1, 8, 3, 1,11, */
/*   0.00019, 0.01603, 0.00000, 0.01995, 0.00000, 0.01978, 0.00000, 0.01340, 0.00000, 0.00572, 0.00007, 0.00116 , */
/*   0.00001, 0.00192, 0.00000, 0.00170, 0.00000, 0.00131, 0.00000, 0.00081, 0.00000, 0.00037, 0.00001, 0.00010 , */
/* "duuP1308"}, */
	{2,0,0,1,1, 8, 3, 2, 6,
 -0.00074, 0.00000,-0.00125, 0.00000,-0.00139, 0.00019,-0.00041, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00002, 0.00000, 0.00003, 0.00000, 0.00003, 0.00001, 0.00001, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP1308"},
/* 	{2,0,0,1,1, 8, 4, 2, 6, */
/*   0.00038, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00056, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/*   0.00001, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00001, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/* "duuP1408"}, */
	{2,0,0,2,4, 1, 1, 2,11,
  0.00051, 0.00016,-0.00064, 0.00000, 0.00000,-0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00016 ,
  0.00001, 0.00002, 0.00002, 0.00000, 0.00000, 0.00002, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00002 ,
"duuP4101"},
	{2,0,0,2,4, 1, 2, 1,10,
 -0.00024,-0.00004, 0.00097, 0.00076, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00039, 0.00000 ,
  0.00002, 0.00004, 0.00002, 0.00003, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00001, 0.00000 ,
"duuP4201"},
	{2,0,0,2,4, 1, 2, 2, 6,
 -0.00170, 0.00018, 0.00000, 0.00000, 0.00002,-0.00104,-0.00025, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00005, 0.00008, 0.00000, 0.00000, 0.00005, 0.00007, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP4201"},
	{2,0,0,2,4, 1, 3, 1, 7,
  0.00062,-0.00204, 0.00210, 0.00000, 0.00000,-0.00001, 0.00000,-0.00047, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00002, 0.00003, 0.00003, 0.00000, 0.00000, 0.00002, 0.00000, 0.00002, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP4301"},
	{2,0,0,2,3, 2, 1, 1, 6,
  0.00809,-0.00039, 0.00969, 0.01027, 0.00696, 0.00440, 0.00380, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00014, 0.00014, 0.00013, 0.00013, 0.00011, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3102"},
	{2,0,0,2,3, 2, 1, 2, 7,
 -0.02889, 0.00940, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00200, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3102"},
	{2,0,0,2,3, 2, 2, 1, 7,
  0.01292,-0.01350,-0.00100, 0.00293, 0.00814, 0.00780, 0.00000, 0.00422, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00017, 0.00040, 0.00029, 0.00033, 0.00019, 0.00022, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3202"},
	{2,0,0,2,3, 2, 2, 2, 5,
 -0.01639,-0.01097, 0.00000, 0.00516,-0.00364,-0.00278, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00006, 0.00016, 0.00000, 0.00013, 0.00008, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3202"},
	{2,0,0,2,3, 2, 3, 1,10,
  0.00754,-0.01839,-0.00660, 0.00000, 0.00245, 0.00000, 0.00000, 0.00000,-0.00555,-0.00251,-0.00167, 0.00000 ,
  0.00009, 0.00010, 0.00013, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000, 0.00010, 0.00010, 0.00010, 0.00000 ,
"duuP3302"},
	{2,0,0,2,3, 2, 3, 2, 5,
 -0.01488,-0.01196, 0.00000, 0.00568, 0.00000,-0.00400, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00005, 0.00013, 0.00000, 0.00011, 0.00000, 0.00009, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3302"},
	{2,0,0,2,4, 3, 1, 1, 9,
 -0.03276, 0.01318, 0.00000, 0.00000, 0.00000, 0.00000,-0.00183, 0.00000, 0.00000, 0.00130, 0.00000, 0.00000 ,
  0.00021, 0.00037, 0.00000, 0.00000, 0.00000, 0.00000, 0.00030, 0.00000, 0.00000, 0.00030, 0.00000, 0.00000 ,
"duuP4103"},
	{2,0,0,2,4, 3, 1, 2,11,
 -0.01769, 0.02891, 0.00000, 0.00794, 0.00237, 0.00625, 0.00000, 0.00230, 0.00000, 0.00000, 0.00127,-0.00148 ,
  0.00021, 0.00058, 0.00000, 0.00054, 0.00031, 0.00047, 0.00000, 0.00038, 0.00000, 0.00000, 0.00029, 0.00030 ,
"duuP4103"},
	{2,0,0,2,4, 3, 3, 1,11,
 -0.01314,-0.00849,-0.00169, 0.00190, 0.00000, 0.00000,-0.00106, 0.00000, 0.00000, 0.00000, 0.00000,-0.00109 ,
  0.00008, 0.00014, 0.00012, 0.00012, 0.00000, 0.00000, 0.00009, 0.00000, 0.00000, 0.00000, 0.00000, 0.00009 ,
"duuP4303"},
	{2,0,0,2,4, 3, 3, 2, 7,
 -0.04384, 0.00235,-0.00220, 0.00000, 0.00000, 0.00000, 0.00000,-0.00267, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00012, 0.00018, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP4303"},
	{2,0,0,2,3, 4, 1, 1,10,
 -0.02559,-0.01380, 0.00000, 0.00000, 0.00000, 0.00000, 0.00055, 0.00000,-0.00394,-0.00192,-0.00147, 0.00000 ,
  0.00012, 0.00021, 0.00000, 0.00000, 0.00000, 0.00000, 0.00019, 0.00000, 0.00021, 0.00017, 0.00019, 0.00000 ,
"duuP3104"},
	{2,0,0,2,3, 4, 1, 2, 5,
 -0.04570, 0.01817, 0.00835, 0.00482, 0.00556, 0.00291, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00024, 0.00021, 0.00022, 0.00018, 0.00019, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3104"},
	{2,0,0,2,3, 4, 2, 1,10,
 -0.03355,-0.01655,-0.00792, 0.00000,-0.00388, 0.00000, 0.00000, 0.00000, 0.00000, 0.00136,-0.00265, 0.00000 ,
  0.00022, 0.00027, 0.00039, 0.00000, 0.00028, 0.00000, 0.00000, 0.00000, 0.00000, 0.00021, 0.00019, 0.00000 ,
"duuP3204"},
	{2,0,0,2,3, 4, 2, 2,11,
 -0.04488, 0.02046, 0.01265, 0.00000, 0.00619, 0.00304, 0.00000, 0.00000, 0.00000, 0.00145, 0.00000,-0.00411 ,
  0.00021, 0.00029, 0.00034, 0.00000, 0.00029, 0.00025, 0.00000, 0.00000, 0.00000, 0.00025, 0.00000, 0.00025 ,
"duuP3204"},
	{2,0,0,2,3, 4, 3, 1,11,
 -0.02638,-0.01417, 0.00000, 0.00295, 0.00000, 0.00000, 0.00262, 0.00000, 0.00199, 0.00078,-0.00260,-0.00146 ,
  0.00011, 0.00031, 0.00000, 0.00024, 0.00000, 0.00000, 0.00019, 0.00000, 0.00023, 0.00018, 0.00020, 0.00018 ,
"duuP3304"},
	{2,0,0,2,3, 4, 3, 2, 7,
 -0.05060, 0.01588, 0.00000, 0.00436, 0.00229, 0.00000,-0.00499,-0.00291, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00024, 0.00000, 0.00022, 0.00019, 0.00000, 0.00018, 0.00018, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3304"},
	{2,0,0,2,3, 4, 4, 1,11,
 -0.02584,-0.00700, 0.00000, 0.00745,-0.00165, 0.00556, 0.00000, 0.00000, 0.00000, 0.00000,-0.00146, 0.00149 ,
  0.00011, 0.00031, 0.00000, 0.00026, 0.00015, 0.00020, 0.00000, 0.00000, 0.00000, 0.00000, 0.00016, 0.00015 ,
"duuP3404"},
	{2,0,0,2,3, 4, 4, 2,11,
 -0.04886, 0.01527, 0.00803, 0.00000, 0.00516, 0.00000, 0.00000, 0.00000,-0.00222, 0.00000, 0.00000,-0.00221 ,
  0.00013, 0.00017, 0.00022, 0.00000, 0.00019, 0.00000, 0.00000, 0.00000, 0.00016, 0.00000, 0.00000, 0.00015 ,
"duuP3404"},
	{2,0,0,2,3, 4, 5, 1, 9,
 -0.02774,-0.01565, 0.00675,-0.01741, 0.00910,-0.00670, 0.00000,-0.00359, 0.00000,-0.00219, 0.00000, 0.00000 ,
  0.00025, 0.00047, 0.00044, 0.00044, 0.00033, 0.00038, 0.00000, 0.00033, 0.00000, 0.00027, 0.00000, 0.00000 ,
"duuP3504"},
	{2,0,0,2,3, 4, 5, 2,10,
 -0.01784,-0.02217, 0.01258, 0.00228, 0.00894, 0.00423, 0.00297, 0.00000, 0.00012,-0.00070,-0.00047, 0.00000 ,
  0.00008, 0.00012, 0.00015, 0.00011, 0.00013, 0.00008, 0.00009, 0.00000, 0.00007, 0.00003, 0.00005, 0.00000 ,
"duuP3504"},
	{2,0,0,2,3, 4, 6, 1,10,
  0.01234, 0.03017,-0.01433,-0.00045,-0.00582, 0.00000, 0.00000, 0.00130, 0.00143, 0.00000, 0.00079, 0.00000 ,
  0.00005, 0.00007, 0.00008, 0.00005, 0.00004, 0.00000, 0.00000, 0.00002, 0.00003, 0.00000, 0.00003, 0.00000 ,
"duuP3604"},
/* 	{2,0,0,2,3, 4, 6, 2,10, */
/*  -0.04211,-0.00252, 0.01303, 0.00368, 0.00688, 0.00000,-0.00079, 0.00000, 0.00000,-0.00158, 0.00168, 0.00000 , */
/*   0.00015, 0.00011, 0.00021, 0.00053, 0.00030, 0.00000, 0.00014, 0.00000, 0.00000, 0.00023, 0.00020, 0.00000 , */
/* "duuP3604"}, */
	{2,0,0,2,4, 5, 1, 1,11,
 -0.01351,-0.01702, 0.00000,-0.00344, 0.00000, 0.00000, 0.00000, 0.00168, 0.00000,-0.00012, 0.00000, 0.00250 ,
  0.00008, 0.00016, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012, 0.00000, 0.00012 ,
"duuP4105"},
	{2,0,0,2,4, 5, 1, 2, 9,
 -0.02204, 0.01317, 0.01432, 0.00000, 0.01147, 0.00471, 0.00403, 0.00000, 0.00000,-0.00360, 0.00000, 0.00000 ,
  0.00014, 0.00017, 0.00023, 0.00000, 0.00021, 0.00015, 0.00018, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000 ,
"duuP4105"},
	{2,0,0,2,4, 5, 2, 1, 8,
 -0.01350,-0.01701, 0.00000, 0.00000, 0.00000, 0.00155,-0.00325,-0.00141, 0.00302, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00019, 0.00000, 0.00000, 0.00000, 0.00016, 0.00016, 0.00016, 0.00015, 0.00000, 0.00000, 0.00000 ,
"duuP4205"},
	{2,0,0,2,4, 5, 2, 2,10,
 -0.01753, 0.01485,-0.00596, 0.00000, 0.00387,-0.00412, 0.00000, 0.00000, 0.00000, 0.00000, 0.00169, 0.00000 ,
  0.00010, 0.00015, 0.00016, 0.00000, 0.00015, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000 ,
"duuP4205"},
	{2,0,0,2,4, 5, 3, 1, 8,
 -0.01582,-0.01550, 0.00000,-0.00256, 0.00000, 0.00000,-0.00255, 0.00000,-0.00191, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00018, 0.00000, 0.00014, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000 ,
"duuP4305"},
	{2,0,0,2,4, 5, 3, 2,10,
 -0.01697, 0.01825,-0.00306, 0.00000, 0.00628,-0.00263, 0.00000, 0.00000,-0.00108, 0.00000, 0.00314, 0.00000 ,
  0.00010, 0.00014, 0.00017, 0.00000, 0.00015, 0.00011, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012, 0.00000 ,
"duuP4305"},
	{2,0,0,2,4, 5, 4, 1, 9,
 -0.02162,-0.00821,-0.00886, 0.00000, 0.00000, 0.00133, 0.00000, 0.00737, 0.00182, 0.00201, 0.00000, 0.00000 ,
  0.00014, 0.00019, 0.00021, 0.00000, 0.00000, 0.00017, 0.00000, 0.00020, 0.00014, 0.00018, 0.00000, 0.00000 ,
"duuP4405"},
	{2,0,0,2,4, 5, 4, 2,10,
 -0.01317, 0.02735,-0.00505, 0.00000, 0.01194,-0.00015, 0.00390, 0.00518, 0.00000, 0.00000, 0.00236, 0.00000 ,
  0.00014, 0.00016, 0.00024, 0.00000, 0.00021, 0.00014, 0.00016, 0.00013, 0.00000, 0.00000, 0.00011, 0.00000 ,
"duuP4405"},
	{2,0,0,2,3, 6, 1, 1,11,
  0.00090, 0.00065, 0.00000, 0.00000, 0.00000, 0.00000, 0.00031, 0.00000, 0.00000, 0.00003, 0.00000,-0.00009 ,
  0.00001, 0.00002, 0.00000, 0.00000, 0.00000, 0.00000, 0.00002, 0.00000, 0.00000, 0.00002, 0.00000, 0.00002 ,
"duuP3106"},
	{2,0,0,2,3, 6, 1, 2,10,
  0.00047,-0.00037, 0.00000, 0.00000,-0.00026, 0.00023, 0.00000, 0.00000, 0.00028, 0.00000, 0.00022, 0.00000 ,
  0.00001, 0.00002, 0.00000, 0.00000, 0.00001, 0.00001, 0.00000, 0.00000, 0.00001, 0.00000, 0.00001, 0.00000 ,
"duuP3106"},
/* 	{2,0,0,2,3, 6, 2, 1, 6, */
/*  -0.00135, 0.00328,-0.00015, 0.00000, 0.00134,-0.00002, 0.00057, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/*   0.00015, 0.00027, 0.00016, 0.00000, 0.00016, 0.00009, 0.00009, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/* "duuP3206"}, */
/* 	{2,0,0,2,3, 6, 2, 2,10, */
/*   0.00140, 0.00176, 0.00095,-0.00213, 0.00000, 0.00000,-0.00221, 0.00000, 0.00000,-0.00098, 0.00038, 0.00000 , */
/*   0.00009, 0.00005, 0.00004, 0.00016, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000, 0.00007, 0.00004, 0.00000 , */
/* "duuP3206"}, */
	{2,0,0,2,3, 6, 3, 1, 8,
  0.00058, 0.00199, 0.00000, 0.00051, 0.00000, 0.00065, 0.00000, 0.00000, 0.00019, 0.00000, 0.00000, 0.00000 ,
  0.00002, 0.00011, 0.00000, 0.00008, 0.00000, 0.00005, 0.00000, 0.00000, 0.00002, 0.00000, 0.00000, 0.00000 ,
"duuP3306"},
	{2,0,0,2,3, 6, 3, 2,10,
  0.00161, 0.00000, 0.00000,-0.00058, 0.00008, 0.00000, 0.00056, 0.00000, 0.00109, 0.00000, 0.00060, 0.00000 ,
  0.00002, 0.00000, 0.00000, 0.00002, 0.00004, 0.00000, 0.00005, 0.00000, 0.00005, 0.00000, 0.00004, 0.00000 ,
"duuP3306"},
	{2,0,0,2,3, 6, 4, 1,10,
  0.00261, 0.00242, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00060, 0.00000,-0.00034, 0.00000 ,
  0.00004, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00000, 0.00005, 0.00000 ,
"duuP3406"},
	{2,0,0,2,3, 6, 4, 2, 9,
  0.00013, 0.00000, 0.00072, 0.00000, 0.00008,-0.00070,-0.00061, 0.00000, 0.00000,-0.00040, 0.00000, 0.00000 ,
  0.00005, 0.00000, 0.00009, 0.00000, 0.00008, 0.00005, 0.00006, 0.00000, 0.00000, 0.00004, 0.00000, 0.00000 ,
"duuP3406"},
	{2,0,0,2,3, 6, 5, 1, 7,
  0.00242, 0.00106,-0.00088, 0.00000, 0.00000, 0.00000, 0.00000,-0.00045, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00006, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3506"},
	{2,0,0,2,3, 6, 5, 2, 7,
  0.00012, 0.00000, 0.00000, 0.00000, 0.00000,-0.00029, 0.00000, 0.00047, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00003, 0.00000, 0.00000, 0.00000, 0.00000, 0.00004, 0.00000, 0.00004, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3506"},
	{2,0,0,2,3, 6, 6, 1, 5,
  0.00105, 0.00000,-0.00064, 0.00000,-0.00030,-0.00018, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00003, 0.00000, 0.00005, 0.00000, 0.00004, 0.00003, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3606"},
	{2,0,0,2,3, 6, 6, 2, 7,
  0.00066, 0.00112, 0.00097, 0.00000, 0.00032, 0.00000, 0.00000, 0.00024, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00004, 0.00006, 0.00000, 0.00004, 0.00000, 0.00000, 0.00003, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3606"},
	{2,0,0,2,4, 7, 1, 1, 9,
 -0.00134, 0.00000, 0.00000, 0.00014, 0.00000,-0.00019, 0.00000, 0.00000, 0.00000,-0.00022, 0.00000, 0.00000 ,
  0.00001, 0.00000, 0.00000, 0.00002, 0.00000, 0.00002, 0.00000, 0.00000, 0.00000, 0.00002, 0.00000, 0.00000 ,
"duuP4107"},
/* 	{2,0,0,2,4, 7, 1, 2, 9, */
/*  -0.00067, 0.00403, 0.00000, 0.00017, 0.00359,-0.00245, 0.00393,-0.00175, 0.00137,-0.00024, 0.00000, 0.00000 , */
/*   0.00019, 0.00068, 0.00000, 0.00004, 0.00056, 0.00044, 0.00056, 0.00029, 0.00019, 0.00006, 0.00000, 0.00000 , */
/* "duuP4107"}, */
/* 	{2,0,0,2,4, 7, 2, 1, 8, */
/*  -0.00001, 0.00000, 0.00000, 0.00120,-0.00234, 0.00000, 0.00104,-0.00103,-0.00034, 0.00000, 0.00000, 0.00000 , */
/*   0.00007, 0.00000, 0.00000, 0.00009, 0.00007, 0.00000, 0.00006, 0.00005, 0.00004, 0.00000, 0.00000, 0.00000 , */
/* "duuP4207"}, */
/* 	{2,0,0,2,4, 7, 2, 2, 5, */
/*   0.00464,-0.00820, 0.00000, 0.00000, 0.00000,-0.00114, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/*   0.00084, 0.00144, 0.00000, 0.00000, 0.00000, 0.00028, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/* "duuP4207"}, */
/* 	{2,0,0,2,4, 7, 3, 1,11, */
/*   0.20503,-0.27141,-0.02021, 0.22897,-0.24733, 0.13727,-0.03885, 0.00000, 0.00000, 0.00000, 0.00000,-0.00104 , */
/*   0.00029, 0.00037, 0.00253, 0.00039, 0.00038, 0.00037, 0.00023, 0.00000, 0.00000, 0.00000, 0.00000, 0.00021 , */
/* "duuP4307"}, */
/* 	{2,0,0,2,4, 7, 3, 2, 7, */
/*   0.00827, 0.00000,-0.01876,-0.00888, 0.00877, 0.00406,-0.00481,-0.00369, 0.00000, 0.00000, 0.00000, 0.00000 , */
/*   0.00323, 0.00000, 0.00669, 0.00217, 0.00313, 0.00099, 0.00170, 0.00100, 0.00000, 0.00000, 0.00000, 0.00000 , */
/* "duuP4307"}, */
/* 	{2,0,0,2,4, 7, 4, 1,11, */
/*   0.01196, 0.00000, 0.00000, 0.00904, 0.00204, 0.00000, 0.00702, 0.00383, 0.00000, 0.00000, 0.00054, 0.00346 , */
/*   0.00006, 0.00000, 0.00000, 0.00009, 0.00007, 0.00000, 0.00008, 0.00008, 0.00000, 0.00000, 0.00007, 0.00006 , */
/* "duuP4407"}, */
/* 	{2,0,0,2,4, 7, 5, 1, 9, */
/*   0.00652,-0.00673,-0.00089, 0.00000,-0.00264,-0.00307, 0.00000, 0.00000,-0.00082,-0.00231, 0.00000, 0.00000 , */
/*   0.00005, 0.00007, 0.00009, 0.00000, 0.00005, 0.00005, 0.00000, 0.00000, 0.00004, 0.00004, 0.00000, 0.00000 , */
/* "duuP4507"}, */
	{2,0,0,2,4, 7, 5, 2,11,
 -0.00644, 0.00000, 0.00057, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00065 ,
  0.00004, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00004 ,
"duuP4507"},
	{2,0,0,2,4, 7, 6, 1, 8,
 -0.00072, 0.00413, 0.00090, 0.00000, 0.00019, 0.00000, 0.00092, 0.00000, 0.00052, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00005, 0.00007, 0.00000, 0.00006, 0.00000, 0.00006, 0.00000, 0.00004, 0.00000, 0.00000, 0.00000 ,
"duuP4607"},
	{2,0,0,2,4, 7, 6, 2,11,
 -0.00280,-0.00304, 0.00027, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00011, 0.00000, 0.00000, 0.00012 ,
  0.00002, 0.00003, 0.00003, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00002, 0.00000, 0.00000, 0.00002 ,
"duuP4607"},
	{2,0,0,2,3, 8, 4, 1,10,
  0.05931,-0.06706, 0.00000,-0.03708, 0.00905,-0.01714, 0.00464, 0.00000, 0.00000, 0.00000, 0.00248, 0.00000 ,
  0.00006, 0.00029, 0.00000, 0.00022, 0.00010, 0.00014, 0.00010, 0.00000, 0.00000, 0.00000, 0.00008, 0.00000 ,
"duuP3408"},
	{2,0,0,2,3, 8, 4, 2, 5,
  0.01074, 0.08346, 0.00000, 0.02548, 0.00000, 0.01413, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00025, 0.00000, 0.00020, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3408"},
	{2,0,0,2,3, 8, 5, 1,11,
  0.03375,-0.05268, 0.00000,-0.02710, 0.00950,-0.01006, 0.00663, 0.00413, 0.00000, 0.00655, 0.00000, 0.00336 ,
  0.00005, 0.00025, 0.00000, 0.00023, 0.00009, 0.00023, 0.00009, 0.00022, 0.00000, 0.00018, 0.00000, 0.00012 ,
"duuP3508"},
	{2,0,0,2,3, 8, 5, 2,11,
 -0.00024,-0.02306, 0.00000,-0.08027, 0.00000,-0.07970, 0.00000,-0.06059, 0.00000,-0.04090, 0.00000,-0.02007 ,
  0.00012, 0.00031, 0.00000, 0.00028, 0.00000, 0.00028, 0.00000, 0.00027, 0.00000, 0.00023, 0.00000, 0.00020 ,
"duuP3508"},
	{2,0,0,2,3, 8, 6, 1, 8,
  0.00680,-0.08808, 0.00526,-0.03298, 0.00000,-0.01305, 0.00555, 0.00000, 0.00332, 0.00000, 0.00000, 0.00000 ,
  0.00012, 0.00034, 0.00018, 0.00025, 0.00000, 0.00016, 0.00013, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000 ,
"duuP3608"},
	{2,0,0,2,3, 8, 6, 2,11,
  0.00268, 0.08072,-0.02786, 0.00608,-0.01714, 0.00349,-0.00944, 0.00000,-0.00208, 0.00000, 0.00000,-0.00176 ,
  0.00023, 0.00035, 0.00042, 0.00028, 0.00035, 0.00019, 0.00025, 0.00000, 0.00017, 0.00000, 0.00000, 0.00012 ,
"duuP3608"},
	{2,0,0,2,4, 9, 1, 1, 8,
  0.03640,-0.01513, 0.00000, 0.00000, 0.00000, 0.00000,-0.00455, 0.00251,-0.00286, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00010, 0.00010, 0.00000, 0.00000, 0.00000 ,
"duuP4109"},
	{2,0,0,2,4, 9, 1, 2,11,
  0.01922, 0.01075, 0.00212, 0.00000, 0.00000, 0.00195, 0.00000, 0.00000, 0.00284, 0.00000, 0.00000,-0.00098 ,
  0.00009, 0.00013, 0.00013, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00010 ,
"duuP4109"},
	{2,0,0,2,4, 9, 2, 1,10,
  0.03987,-0.01995, 0.00355, 0.00000, 0.00000, 0.00156, 0.00000, 0.00000, 0.00000,-0.00157, 0.00160, 0.00000 ,
  0.00008, 0.00012, 0.00011, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000, 0.00010, 0.00009, 0.00000 ,
"duuP4209"},
	{2,0,0,2,4, 9, 2, 2,11,
  0.01633, 0.01466, 0.00000, 0.00000, 0.00000, 0.00000, 0.00310, 0.00000, 0.00264, 0.00000, 0.00000,-0.00226 ,
  0.00007, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00000, 0.00010, 0.00000, 0.00000, 0.00009 ,
"duuP4209"},
	{2,0,0,2,4, 9, 3, 1,11,
  0.04226,-0.02595, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00272 ,
  0.00007, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00009 ,
"duuP4309"},
	{2,0,0,2,4, 9, 3, 2,10,
  0.01412, 0.02161, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00374, 0.00000, 0.00000,-0.00241, 0.00000 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00011, 0.00000 ,
"duuP4309"},
	{2,0,0,2,4, 9, 4, 2, 9,
  0.03386, 0.05670,-0.00675, 0.01261, 0.00000, 0.00000, 0.00000, 0.00287, 0.00000,-0.00256, 0.00000, 0.00000 ,
  0.00011, 0.00021, 0.00017, 0.00018, 0.00000, 0.00000, 0.00000, 0.00015, 0.00000, 0.00014, 0.00000, 0.00000 ,
"duuP4409"},
	{2,0,0,2,4, 9, 5, 2,10,
  0.03124, 0.05951,-0.00273, 0.01566,-0.00181, 0.00379, 0.00000, 0.00235, 0.00000, 0.00000, 0.00151, 0.00000 ,
  0.00015, 0.00034, 0.00026, 0.00029, 0.00018, 0.00022, 0.00000, 0.00015, 0.00000, 0.00000, 0.00012, 0.00000 ,
"duuP4509"},
	{2,0,0,2,4, 9, 6, 2,10,
 -0.02479, 0.11051,-0.00792, 0.00000, 0.00526, 0.00142, 0.00000,-0.00417, 0.00000, 0.00000, 0.00318, 0.00000 ,
  0.00014, 0.00020, 0.00023, 0.00000, 0.00020, 0.00018, 0.00000, 0.00017, 0.00000, 0.00000, 0.00016, 0.00000 ,
"duuP4609"},
	{2,0,0,2,3,10, 1, 1, 9,
  0.03887,-0.01287,-0.02422, 0.00000, 0.00000, 0.00000,-0.00383, 0.00632, 0.00000, 0.00587, 0.00000, 0.00000 ,
  0.00016, 0.00024, 0.00023, 0.00000, 0.00000, 0.00000, 0.00019, 0.00021, 0.00000, 0.00020, 0.00000, 0.00000 ,
"duuP3110"},
	{2,0,0,2,3,10, 1, 2, 9,
  0.01981, 0.01026, 0.00000, 0.00000,-0.00162, 0.00000, 0.00000,-0.00325, 0.00227,-0.00332, 0.00000, 0.00000 ,
  0.00007, 0.00013, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00011, 0.00010, 0.00011, 0.00000, 0.00000 ,
"duuP3110"},
	{2,0,0,2,3,10, 2, 1, 8,
  0.03722,-0.01157, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00422,-0.00462, 0.00000, 0.00000, 0.00000 ,
  0.00012, 0.00022, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00018, 0.00018, 0.00000, 0.00000, 0.00000 ,
"duuP3210"},
	{2,0,0,2,3,10, 2, 2, 9,
  0.01917, 0.01232, 0.00000, 0.00000,-0.00242, 0.00000, 0.00000,-0.00335, 0.00000,-0.00241, 0.00000, 0.00000 ,
  0.00007, 0.00014, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00011, 0.00000, 0.00011, 0.00000, 0.00000 ,
"duuP3210"},
	{2,0,0,2,3,10, 3, 1,11,
  0.03571,-0.01303, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00227, 0.00224, 0.00000, 0.00000, 0.00223 ,
  0.00010, 0.00019, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00014, 0.00014, 0.00000, 0.00000, 0.00014 ,
"duuP3310"},
	{2,0,0,2,3,10, 3, 2, 9,
  0.02034, 0.00878, 0.00000, 0.00000,-0.00312, 0.00000, 0.00000,-0.00201, 0.00000,-0.00165, 0.00000, 0.00000 ,
  0.00009, 0.00017, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000, 0.00014, 0.00000, 0.00014, 0.00000, 0.00000 ,
"duuP3310"},
	{2,0,0,2,3,10, 4, 1,11,
  0.04111,-0.01842,-0.00282, 0.00000, 0.00000,-0.00203, 0.00183, 0.00000, 0.00000, 0.00000, 0.00000, 0.00207 ,
  0.00009, 0.00014, 0.00014, 0.00000, 0.00000, 0.00011, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011 ,
"duuP3410"},
	{2,0,0,2,3,10, 4, 2,11,
  0.01513, 0.01370, 0.00000, 0.00000, 0.00000, 0.00000, 0.00212, 0.00000, 0.00000, 0.00000, 0.00000,-0.00186 ,
  0.00009, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00013 ,
"duuP3410"},
	{2,0,0,2,3,10, 5, 1, 8,
  0.03578,-0.01692,-0.01530, 0.00000,-0.01184, 0.00000,-0.00628,-0.00166,-0.00300, 0.00000, 0.00000, 0.00000 ,
  0.00018, 0.00017, 0.00033, 0.00000, 0.00029, 0.00000, 0.00024, 0.00013, 0.00018, 0.00000, 0.00000, 0.00000 ,
"duuP3510"},
	{2,0,0,2,3,10, 5, 2, 9,
  0.01543, 0.01123,-0.00049, 0.00000,-0.00372, 0.00000, 0.00000, 0.00196, 0.00104,-0.00138, 0.00000, 0.00000 ,
  0.00014, 0.00017, 0.00023, 0.00000, 0.00016, 0.00000, 0.00000, 0.00014, 0.00012, 0.00014, 0.00000, 0.00000 ,
"duuP3510"},
	{2,0,0,2,3,10, 6, 1, 7,
  0.04270,-0.01629,-0.00253, 0.00000, 0.00000, 0.00000, 0.00184,-0.00115, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00011, 0.00016, 0.00016, 0.00000, 0.00000, 0.00000, 0.00012, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3610"},
	{2,0,0,2,3,10, 6, 2, 8,
  0.02759, 0.00000, 0.06810, 0.00000, 0.00000, 0.03267, 0.00000, 0.00000,-0.06500, 0.00000, 0.00000, 0.00000 ,
  0.00048, 0.00000, 0.00076, 0.00000, 0.00000, 0.00085, 0.00000, 0.00000, 0.00069, 0.00000, 0.00000, 0.00000 ,
"duuP3610"},
	{2,0,0,2,4,11, 1, 1,10,
  0.04577,-0.02467,-0.00983, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00398, 0.00000 ,
  0.00011, 0.00016, 0.00016, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000 ,
"duuP4111"},
	{2,0,0,2,4,11, 1, 2, 9,
  0.00056, 0.01743, 0.00832, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00425, 0.00000, 0.00000 ,
  0.00012, 0.00017, 0.00018, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000 ,
"duuP4111"},
	{2,0,0,2,4,11, 2, 1,11,
  0.04432,-0.02710,-0.00618, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00319, 0.00440,-0.00840 ,
  0.00009, 0.00014, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00011, 0.00012 ,
"duuP4211"},
	{2,0,0,2,4,11, 2, 2,11,
  0.00180, 0.01238, 0.00783, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00522, 0.00000, 0.00436 ,
  0.00011, 0.00017, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00015, 0.00000, 0.00014 ,
"duuP4211"},
	{2,0,0,2,4,11, 3, 1,11,
  0.04252,-0.02584,-0.00821, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00302, 0.00556,-0.00694 ,
  0.00010, 0.00015, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00011, 0.00012 ,
"duuP4311"},
	{2,0,0,2,4,11, 3, 2,11,
 -0.00193, 0.01603, 0.00782, 0.00000, 0.00000, 0.00000, 0.00345, 0.00000, 0.00000,-0.00231, 0.00000, 0.00579 ,
  0.00010, 0.00014, 0.00015, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012 ,
"duuP4311"},
	{2,0,0,2,4,11, 4, 1,11,
  0.02443,-0.01382, 0.00000, 0.00553, 0.00000, 0.00000, 0.00000,-0.00276, 0.00000,-0.00136, 0.00000, 0.00395 ,
  0.00008, 0.00020, 0.00000, 0.00016, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00015, 0.00000, 0.00013 ,
"duuP4411"},
	{2,0,0,2,4,11, 4, 2,11,
  0.02243,-0.00214, 0.00000,-0.01329, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00779 ,
  0.00008, 0.00018, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011 ,
"duuP4411"},
	{2,0,0,2,4,11, 5, 1,11,
  0.02382,-0.01879, 0.00000, 0.00622, 0.00198, 0.00000,-0.00394,-0.00266, 0.00000, 0.00000, 0.00000, 0.00430 ,
  0.00011, 0.00025, 0.00000, 0.00020, 0.00016, 0.00000, 0.00016, 0.00015, 0.00000, 0.00000, 0.00000, 0.00015 ,
"duuP4511"},
	{2,0,0,2,4,11, 5, 2,11,
  0.03271,-0.00358, 0.00000,-0.01727, 0.00000, 0.00000, 0.00646, 0.00528, 0.00000, 0.00000, 0.00000,-0.00630 ,
  0.00009, 0.00022, 0.00000, 0.00018, 0.00000, 0.00000, 0.00012, 0.00012, 0.00000, 0.00000, 0.00000, 0.00012 ,
"duuP4511"},
	{2,0,0,2,4,11, 6, 1, 9,
  0.02182, 0.00000, 0.00000, 0.00000, 0.01620,-0.01110, 0.00811, 0.00000, 0.00000, 0.00899, 0.00000, 0.00000 ,
  0.00010, 0.00000, 0.00000, 0.00000, 0.00015, 0.00014, 0.00015, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000 ,
"duuP4611"},
	{2,0,0,2,4,11, 6, 2,11,
  0.04249, 0.00000, 0.00000, 0.00000, 0.00000, 0.00956, 0.00518, 0.00000, 0.00000,-0.01334, 0.00000,-0.01475 ,
  0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00017, 0.00017, 0.00000, 0.00000, 0.00019, 0.00000, 0.00019 ,
"duuP4611"},
	{2,0,0,2,3,12, 1, 1, 4,
 -0.00120, 0.00000,-0.00023, 0.00024, 0.00052, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00001, 0.00000, 0.00002, 0.00001, 0.00002, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3112"},
	{2,0,0,2,3,12, 1, 2,11,
 -0.00056,-0.00077, 0.00024, 0.00000,-0.00027, 0.00000, 0.00000, 0.00000,-0.00028,-0.00022, 0.00000, 0.00017 ,
  0.00001, 0.00002, 0.00002, 0.00000, 0.00002, 0.00000, 0.00000, 0.00000, 0.00001, 0.00001, 0.00000, 0.00001 ,
"duuP3112"},
	{2,0,0,2,3,12, 2, 1, 5,
 -0.00168, 0.00000,-0.00020,-0.00009, 0.00021, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00001, 0.00000, 0.00002, 0.00001, 0.00002, 0.00001, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3212"},
	{2,0,0,2,3,12, 2, 2, 4,
 -0.00015,-0.00074, 0.00000, 0.00031,-0.00019, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00001, 0.00002, 0.00000, 0.00001, 0.00001, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3212"},
	{2,0,0,2,3,12, 3, 1, 5,
 -0.00187,-0.00022,-0.00027,-0.00049, 0.00015,-0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00002, 0.00003, 0.00003, 0.00003, 0.00002, 0.00002, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3312"},
	{2,0,0,2,3,12, 3, 2,11,
 -0.00004,-0.00110, 0.00000, 0.00022,-0.00031, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00013 ,
  0.00001, 0.00002, 0.00000, 0.00002, 0.00001, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00001 ,
"duuP3312"},
	{2,0,0,2,3,12, 4, 1, 8,
 -0.00259,-0.00045, 0.00090, 0.00000,-0.00006, 0.00000, 0.00061, 0.00000, 0.00046, 0.00000, 0.00000, 0.00000 ,
  0.00003, 0.00005, 0.00005, 0.00000, 0.00004, 0.00000, 0.00004, 0.00000, 0.00004, 0.00000, 0.00000, 0.00000 ,
"duuP3412"},
	{2,0,0,2,3,12, 4, 2, 7,
  0.00025,-0.00076, 0.00008, 0.00013,-0.00115,-0.00006, 0.00000,-0.00099, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00005, 0.00009, 0.00009, 0.00008, 0.00006, 0.00006, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP3412"},
	{2,0,0,2,3,12, 5, 1, 8,
  0.00003, 0.00264,-0.00104, 0.00000, 0.00178,-0.00060, 0.00133, 0.00000, 0.00055, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00007, 0.00012, 0.00000, 0.00010, 0.00005, 0.00008, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000 ,
"duuP3512"},
/* 	{2,0,0,2,3,12, 5, 2, 5, */
/*  -6.00000,10.39466,-6.68493, 3.07310,-0.91860, 0.13926, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/*   0.00040, 0.00060, 0.00067, 0.00060, 0.00042, 0.00029, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 , */
/* "duuP3512"}, */
	{2,0,0,2,3,12, 6, 1,10,
 -0.00251, 0.00000, 0.00048,-0.00067,-0.00082, 0.00000, 0.00000,-0.00041, 0.00000,-0.00029,-0.00014, 0.00000 ,
  0.00002, 0.00000, 0.00004, 0.00002, 0.00003, 0.00000, 0.00000, 0.00003, 0.00000, 0.00002, 0.00002, 0.00000 ,
"duuP3612"},
	{2,0,0,2,3,12, 6, 2, 9,
 -0.00116,-0.00057, 0.00103, 0.00000, 0.00001, 0.00000, 0.00045, 0.00039, 0.00000,-0.00036, 0.00000, 0.00000 ,
  0.00003, 0.00003, 0.00005, 0.00000, 0.00004, 0.00000, 0.00003, 0.00002, 0.00000, 0.00002, 0.00000, 0.00000 ,
"duuP3612"},
	{2,0,0,3,6, 1, 1, 1, 9,
 -0.00122, 0.00679, 0.00000, 0.00000, 0.00000, 0.00000,-0.00236,-0.00235,-0.00144,-0.00115, 0.00000, 0.00000 ,
  0.00003, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00005, 0.00005, 0.00005, 0.00000, 0.00000 ,
"duuP6101"},
	{2,0,0,3,6, 1, 1, 2,11,
  0.00096, 0.00000, 0.00177, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00142, 0.00137 ,
  0.00004, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00005 ,
"duuP6101"},
	{2,0,0,3,6, 1, 2, 1,11,
  0.00127, 0.00787, 0.00000, 0.00000, 0.00000, 0.00000,-0.00177, 0.00000, 0.00000, 0.00000, 0.00000, 0.00086 ,
  0.00004, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005 ,
"duuP6201"},
	{2,0,0,3,6, 1, 2, 2,11,
 -0.00279, 0.01098, 0.00146, 0.00303,-0.00245, 0.00000, 0.00025, 0.00000, 0.00214, 0.00000, 0.00000,-0.00083 ,
  0.00015, 0.00014, 0.00028, 0.00011, 0.00024, 0.00000, 0.00018, 0.00000, 0.00012, 0.00000, 0.00000, 0.00008 ,
"duuP6201"},
	{2,0,0,3,6, 1, 3, 1,11,
  0.00253, 0.00807, 0.00000, 0.00137, 0.00102, 0.00000,-0.00122, 0.00000, 0.00000, 0.00000,-0.00089, 0.00132 ,
  0.00004, 0.00011, 0.00000, 0.00008, 0.00007, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00006, 0.00006 ,
"duuP6301"},
	{2,0,0,3,6, 1, 4, 1, 9,
  0.00226, 0.00668, 0.00000, 0.00000,-0.00086, 0.00000, 0.00000, 0.00000, 0.00000,-0.00094, 0.00000, 0.00000 ,
  0.00005, 0.00009, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000 ,
"duuP6401"},
	{2,0,0,3,6, 1, 4, 2, 9,
 -0.00851, 0.01155, 0.00459, 0.00000, 0.00000,-0.00255, 0.00000, 0.00000, 0.00000,-0.00125, 0.00000, 0.00000 ,
  0.00012, 0.00018, 0.00018, 0.00000, 0.00000, 0.00015, 0.00000, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000 ,
"duuP6401"},
	{2,0,0,3,6, 1, 5, 1, 7,
 -0.00254, 0.00568,-0.00010, 0.00000,-0.00208,-0.00058,-0.00081, 0.00100, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00008, 0.00011, 0.00000, 0.00010, 0.00007, 0.00008, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6501"},
	{2,0,0,3,6, 1, 6, 1, 7,
 -0.00386, 0.00200, 0.00000, 0.00000, 0.00000,-0.00034, 0.00000, 0.00158, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00007, 0.00000, 0.00000, 0.00000, 0.00006, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6601"},
	{2,0,0,3,6, 1, 6, 2, 8,
  0.00107, 0.00005, 0.00000, 0.00117, 0.00000, 0.00000, 0.00027, 0.00000,-0.00049, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00007, 0.00000, 0.00006, 0.00000, 0.00000, 0.00005, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000 ,
"duuP6601"},
	{2,0,0,3,6, 1, 7, 1, 8,
 -0.00587,-0.00200, 0.00000, 0.00000, 0.00000,-0.00094, 0.00000, 0.00141, 0.00116, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00007, 0.00000, 0.00000, 0.00000, 0.00006, 0.00000, 0.00006, 0.00005, 0.00000, 0.00000, 0.00000 ,
"duuP6701"},
	{2,0,0,3,6, 1, 7, 2,10,
  0.00214,-0.00098, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00044, 0.00000 ,
  0.00003, 0.00005, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00004, 0.00000 ,
"duuP6701"},
	{2,0,0,3,5, 2, 1, 1, 8,
  0.01183,-0.01332, 0.00000,-0.00248,-0.00096, 0.00000, 0.00000, 0.00000, 0.00107, 0.00000, 0.00000, 0.00000 ,
  0.00006, 0.00013, 0.00000, 0.00010, 0.00009, 0.00000, 0.00000, 0.00000, 0.00008, 0.00000, 0.00000, 0.00000 ,
"duuP5102"},
	{2,0,0,3,5, 2, 2, 1, 7,
  0.01627, 0.00000, 0.00000, 0.00000,-0.00388,-0.00050, 0.00000, 0.00295, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00006, 0.00000, 0.00000, 0.00000, 0.00008, 0.00009, 0.00000, 0.00008, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5202"},
	{2,0,0,3,5, 2, 4, 1, 9,
  0.00599,-0.00616, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00074, 0.00000, 0.00122, 0.00000, 0.00000 ,
  0.00006, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00009, 0.00000, 0.00009, 0.00000, 0.00000 ,
"duuP5402"},
	{2,0,0,3,5, 2, 4, 2,10,
  0.07068, 0.00000, 0.05307, 0.05694, 0.00000, 0.00000,-0.02785, 0.07715, 0.04843,-0.03762, 0.04406, 0.00000 ,
  0.00049, 0.00000, 0.00099, 0.00102, 0.00000, 0.00000, 0.00106, 0.00113, 0.00104, 0.00106, 0.00096, 0.00000 ,
"duuP5402"},
	{2,0,0,3,5, 2, 5, 1, 8,
  0.00426,-0.01822, 0.00000,-0.00282, 0.00142, 0.00000, 0.00000, 0.00000,-0.00126, 0.00000, 0.00000, 0.00000 ,
  0.00012, 0.00027, 0.00000, 0.00021, 0.00017, 0.00000, 0.00000, 0.00000, 0.00016, 0.00000, 0.00000, 0.00000 ,
"duuP5502"},
	{2,0,0,3,5, 2, 5, 2, 5,
  0.06773, 0.01509, 0.00000,-0.04917,-0.07745, 0.05015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00086, 0.00141, 0.00000, 0.00129, 0.00105, 0.00114, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5502"},
	{2,0,0,3,5, 2, 6, 1,11,
  0.00742,-0.01093, 0.00000,-0.00832, 0.00000, 0.00000, 0.00000, 0.00000,-0.00277, 0.00000, 0.00000,-0.00283 ,
  0.00011, 0.00023, 0.00000, 0.00018, 0.00000, 0.00000, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000, 0.00014 ,
"duuP5602"},
	{2,0,0,3,5, 2, 6, 2,10,
 -0.01642, 0.04751, 0.00000, 0.00000, 0.00488, 0.00000, 0.00000, 0.02988, 0.00000, 0.02057, 0.01263, 0.00000 ,
  0.00028, 0.00063, 0.00000, 0.00000, 0.00044, 0.00000, 0.00000, 0.00036, 0.00000, 0.00034, 0.00031, 0.00000 ,
"duuP5602"},
	{2,0,0,3,5, 2, 7, 1,10,
  0.01237, 0.03165, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00334, 0.00000,-0.01182, 0.00000 ,
  0.00016, 0.00030, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00021, 0.00000, 0.00021, 0.00000 ,
"duuP5702"},
	{2,0,0,3,5, 2, 7, 2,11,
 -0.01864, 0.00000, 0.00000, 0.00000, 0.09835, 0.00000,-0.03039,-0.06281, 0.00000, 0.02527,-0.08058, 0.07035 ,
  0.00060, 0.00000, 0.00000, 0.00000, 0.00102, 0.00000, 0.00089, 0.00094, 0.00000, 0.00122, 0.00089, 0.00112 ,
"duuP5702"},
	{2,0,0,3,6, 3, 1, 1, 7,
  0.00042,-0.01024, 0.00256,-0.00144, 0.00000, 0.00039, 0.00139,-0.00144, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00023, 0.00013, 0.00021, 0.00000, 0.00017, 0.00010, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6103"},
	{2,0,0,3,6, 3, 1, 2,11,
 -0.01587, 0.00596, 0.00000,-0.00459, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00370 ,
  0.00007, 0.00017, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010 ,
"duuP6103"},
	{2,0,0,3,6, 3, 2, 1,10,
  0.00860,-0.01283, 0.00000, 0.00000,-0.00170, 0.00000, 0.00000, 0.00236,-0.00191, 0.00183, 0.00208, 0.00000 ,
  0.00009, 0.00015, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00013, 0.00013, 0.00013, 0.00013, 0.00000 ,
"duuP6203"},
	{2,0,0,3,6, 3, 2, 2,11,
 -0.01623, 0.00633, 0.00778, 0.00000, 0.00233, 0.00000, 0.00000, 0.00000, 0.00000,-0.00066, 0.00000, 0.00160 ,
  0.00010, 0.00013, 0.00017, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00011 ,
"duuP6203"},
	{2,0,0,3,6, 3, 3, 1,11,
  0.01486,-0.01401,-0.00356, 0.00000, 0.00000, 0.00000,-0.00270, 0.00000,-0.00183, 0.00000, 0.00000,-0.00152 ,
  0.00010, 0.00015, 0.00015, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00013, 0.00000, 0.00000, 0.00012 ,
"duuP6303"},
	{2,0,0,3,6, 3, 3, 2, 6,
 -0.01858, 0.00207, 0.00000,-0.00772, 0.00000,-0.00231,-0.00214, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00020, 0.00000, 0.00017, 0.00000, 0.00013, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6303"},
	{2,0,0,3,6, 3, 4, 1, 9,
  0.02117,-0.02603,-0.01249,-0.01373,-0.00330,-0.01803, 0.00000,-0.01000,-0.00237,-0.00377, 0.00000, 0.00000 ,
  0.00039, 0.00132, 0.00063, 0.00115, 0.00044, 0.00095, 0.00000, 0.00070, 0.00028, 0.00046, 0.00000, 0.00000 ,
"duuP6403"},
	{2,0,0,3,6, 3, 4, 2,10,
 -0.03220, 0.01532, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.04239, 0.00610,-0.10136,-0.02686, 0.00000 ,
  0.00030, 0.00090, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00079, 0.00056, 0.00073, 0.00058, 0.00000 ,
"duuP6403"},
	{2,0,0,3,6, 3, 5, 1,10,
  0.02237,-0.01371, 0.00000, 0.00000, 0.00173, 0.00000,-0.00224,-0.00453, 0.00000, 0.00000, 0.00245, 0.00000 ,
  0.00016, 0.00030, 0.00000, 0.00000, 0.00026, 0.00000, 0.00023, 0.00022, 0.00000, 0.00000, 0.00021, 0.00000 ,
"duuP6503"},
	{2,0,0,3,6, 3, 5, 2, 8,
 -0.01481,-0.00475, 0.01074,-0.00500, 0.00000, 0.00000,-0.00173, 0.00000, 0.00607, 0.00000, 0.00000, 0.00000 ,
  0.00017, 0.00036, 0.00024, 0.00024, 0.00000, 0.00000, 0.00018, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000 ,
"duuP6503"},
	{2,0,0,3,6, 3, 6, 1,11,
  0.00720, 0.03195,-0.01099, 0.00000, 0.00000,-0.00403, 0.00000, 0.00046, 0.00000, 0.00493, 0.00140, 0.00342 ,
  0.00027, 0.00038, 0.00040, 0.00000, 0.00000, 0.00033, 0.00000, 0.00033, 0.00000, 0.00034, 0.00028, 0.00031 ,
"duuP6603"},
	{2,0,0,3,6, 3, 6, 2,11,
 -0.00899, 0.00000, 0.00000, 0.00000, 0.00695, 0.00000, 0.00000, 0.00000, 0.00000, 0.00213,-0.00097,-0.01514 ,
  0.00013, 0.00000, 0.00000, 0.00000, 0.00019, 0.00000, 0.00000, 0.00000, 0.00000, 0.00023, 0.00021, 0.00023 ,
"duuP6603"},
	{2,0,0,3,5, 4, 1, 1, 8,
 -0.00893,-0.00806,-0.00013, 0.00000, 0.00389,-0.00304, 0.00000, 0.00000,-0.00098, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00013, 0.00016, 0.00000, 0.00013, 0.00010, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000 ,
"duuP5104"},
	{2,0,0,3,5, 4, 1, 2, 9,
 -0.02831, 0.01627, 0.00915, 0.00151, 0.00556, 0.00418, 0.00000, 0.00000, 0.00000,-0.00228, 0.00000, 0.00000 ,
  0.00016, 0.00032, 0.00026, 0.00027, 0.00020, 0.00019, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000 ,
"duuP5104"},
	{2,0,0,3,5, 4, 2, 1, 4,
 -0.00601,-0.01347,-0.00059, 0.00000, 0.00189, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00012, 0.00017, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5204"},
	{2,0,0,3,5, 4, 2, 2,11,
 -0.03383, 0.00310, 0.00159,-0.00439, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00368, 0.00000,-0.00166 ,
  0.00012, 0.00023, 0.00016, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012 ,
"duuP5204"},
	{2,0,0,3,5, 4, 3, 1, 9,
 -0.00881,-0.01100,-0.00404,-0.00256, 0.00000, 0.00000,-0.00279, 0.00000, 0.00185,-0.00159, 0.00000, 0.00000 ,
  0.00008, 0.00014, 0.00012, 0.00011, 0.00000, 0.00000, 0.00010, 0.00000, 0.00010, 0.00009, 0.00000, 0.00000 ,
"duuP5304"},
	{2,0,0,3,5, 4, 3, 2, 9,
 -0.03499, 0.00548, 0.00000,-0.00442, 0.00655, 0.00000, 0.00333, 0.00000, 0.00000,-0.00105, 0.00000, 0.00000 ,
  0.00008, 0.00019, 0.00000, 0.00014, 0.00013, 0.00000, 0.00013, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000 ,
"duuP5304"},
	{2,0,0,3,5, 4, 4, 1,11,
 -0.00670,-0.01099, 0.00000, 0.00000, 0.00000, 0.00000,-0.00162, 0.00000, 0.00263, 0.00000, 0.00124,-0.00209 ,
  0.00007, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00000, 0.00011, 0.00000, 0.00011, 0.00009 ,
"duuP5404"},
	{2,0,0,3,5, 4, 4, 2,11,
 -0.03541, 0.00845, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00078, 0.00000, 0.00376 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00011 ,
"duuP5404"},
	{2,0,0,3,6, 5, 1, 1,10,
 -0.02898,-0.00151, 0.00000, 0.00227,-0.00477, 0.00881,-0.00298, 0.00000, 0.00158, 0.00000,-0.00169, 0.00000 ,
  0.00016, 0.00056, 0.00000, 0.00045, 0.00027, 0.00031, 0.00033, 0.00000, 0.00035, 0.00000, 0.00030, 0.00000 ,
"duuP6105"},
	{2,0,0,3,6, 5, 1, 2,10,
 -0.04557, 0.01215, 0.00562, 0.00991, 0.00000, 0.00572, 0.00000, 0.00000, 0.00000, 0.00000,-0.00127, 0.00000 ,
  0.00019, 0.00045, 0.00029, 0.00038, 0.00000, 0.00030, 0.00000, 0.00000, 0.00000, 0.00000, 0.00023, 0.00000 ,
"duuP6105"},
	{2,0,0,3,6, 5, 2, 1,10,
 -0.02992,-0.00730, 0.00000, 0.00668, 0.00000, 0.00522,-0.00231, 0.00000, 0.00000, 0.00000,-0.00213, 0.00000 ,
  0.00016, 0.00042, 0.00000, 0.00037, 0.00000, 0.00029, 0.00023, 0.00000, 0.00000, 0.00000, 0.00022, 0.00000 ,
"duuP6205"},
	{2,0,0,3,6, 5, 3, 1, 9,
 -0.02392,-0.01390, 0.00641, 0.00000, 0.00498, 0.00000, 0.00000, 0.00000, 0.00000,-0.00121, 0.00000, 0.00000 ,
  0.00024, 0.00029, 0.00039, 0.00000, 0.00031, 0.00000, 0.00000, 0.00000, 0.00000, 0.00023, 0.00000, 0.00000 ,
"duuP6305"},
	{2,0,0,3,5, 6, 1, 1,11,
 -0.04294, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.02400,-0.02102,-0.02648 ,
  0.00031, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00055, 0.00044, 0.00053 ,
"duuP5106"},
	{2,0,0,3,5, 6, 1, 2,11,
 -0.02875, 0.02072,-0.00719, 0.00000,-0.00409, 0.00227, 0.00000,-0.00181, 0.00000, 0.00000, 0.00000, 0.00171 ,
  0.00012, 0.00015, 0.00019, 0.00000, 0.00015, 0.00013, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000, 0.00012 ,
"duuP5106"},
	{2,0,0,3,5, 6, 2, 1,10,
 -0.02669,-0.01184, 0.00965, 0.00000, 0.00000, 0.00213, 0.00000,-0.00411,-0.00350, 0.00000,-0.00329, 0.00000 ,
  0.00018, 0.00029, 0.00028, 0.00000, 0.00000, 0.00024, 0.00000, 0.00024, 0.00023, 0.00000, 0.00023, 0.00000 ,
"duuP5206"},
	{2,0,0,3,5, 6, 2, 2, 6,
 -0.02912, 0.01841, 0.00000, 0.00256, 0.00270, 0.00000, 0.00189, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00020, 0.00000, 0.00016, 0.00014, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5206"},
	{2,0,0,3,5, 6, 3, 1,11,
 -0.02978,-0.01377, 0.00000, 0.00000, 0.00000, 0.00000, 0.00200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00555 ,
  0.00015, 0.00027, 0.00000, 0.00000, 0.00000, 0.00000, 0.00022, 0.00000, 0.00000, 0.00000, 0.00000, 0.00022 ,
"duuP5306"},
	{2,0,0,3,5, 6, 3, 2,11,
 -0.02635, 0.01582,-0.00438, 0.00258, 0.00000,-0.00272, 0.00000, 0.00115, 0.00000,-0.00244, 0.00000, 0.00245 ,
  0.00011, 0.00043, 0.00016, 0.00040, 0.00000, 0.00035, 0.00000, 0.00029, 0.00000, 0.00023, 0.00000, 0.00017 ,
"duuP5306"},
	{2,0,0,3,5, 6, 4, 1,10,
 -0.03549,-0.01717,-0.00559,-0.00465, 0.00000, 0.00000, 0.00000, 0.00000, 0.00337, 0.00321,-0.00416, 0.00000 ,
  0.00017, 0.00030, 0.00026, 0.00027, 0.00000, 0.00000, 0.00000, 0.00000, 0.00022, 0.00021, 0.00022, 0.00000 ,
"duuP5406"},
	{2,0,0,3,5, 6, 4, 2, 5,
 -0.02933, 0.02264, 0.00000, 0.01049,-0.00406, 0.00457, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00024, 0.00000, 0.00020, 0.00011, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5406"},
	{2,0,0,3,6, 7, 1, 2,10,
 -0.01026, 0.02251, 0.00000,-0.00690, 0.00000, 0.00000, 0.00000, 0.00000, 0.00202,-0.00146,-0.00313, 0.00000 ,
  0.00010, 0.00025, 0.00000, 0.00020, 0.00000, 0.00000, 0.00000, 0.00000, 0.00016, 0.00014, 0.00016, 0.00000 ,
"duuP6107"},
	{2,0,0,3,6, 7, 2, 1, 9,
 -0.01029,-0.02303, 0.00280, 0.00000, 0.00000, 0.00000,-0.00139, 0.00000, 0.00000,-0.00150, 0.00000, 0.00000 ,
  0.00011, 0.00016, 0.00016, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000 ,
"duuP6207"},
	{2,0,0,3,6, 7, 2, 2, 8,
 -0.00314, 0.02945, 0.00000,-0.00551, 0.00000, 0.00000, 0.00343,-0.00417,-0.00364, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00026, 0.00000, 0.00021, 0.00000, 0.00000, 0.00016, 0.00014, 0.00016, 0.00000, 0.00000, 0.00000 ,
"duuP6207"},
	{2,0,0,3,6, 7, 3, 2, 9,
 -0.00840, 0.03126,-0.00501,-0.00895, 0.00000, 0.00345, 0.00000, 0.00000, 0.00000, 0.00138, 0.00000, 0.00000 ,
  0.00012, 0.00026, 0.00017, 0.00023, 0.00000, 0.00018, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000 ,
"duuP6307"},
	{2,0,0,3,5, 8, 1, 1, 6,
  0.00326, 0.00236,-0.00165, 0.00000, 0.00000, 0.00000, 0.00077, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00015, 0.00015, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5108"},
	{2,0,0,3,5, 8, 1, 2,10,
 -0.00241, 0.00000, 0.00149, 0.00000, 0.00000, 0.00000, 0.00000, 0.00080, 0.00000, 0.00051,-0.00063, 0.00000 ,
  0.00009, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012, 0.00012, 0.00000 ,
"duuP5108"},
	{2,0,0,3,5, 8, 2, 1, 8,
  0.00762, 0.00500, 0.00000, 0.00000,-0.00156, 0.00000,-0.00041,-0.00142, 0.00220, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00017, 0.00000, 0.00000, 0.00016, 0.00000, 0.00016, 0.00014, 0.00015, 0.00000, 0.00000, 0.00000 ,
"duuP5208"},
	{2,0,0,3,5, 8, 2, 2, 7,
 -0.00792,-0.00317, 0.00000, 0.00000, 0.00072, 0.00000, 0.00000, 0.00103, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00022, 0.00000, 0.00000, 0.00018, 0.00000, 0.00000, 0.00018, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5208"},
	{2,0,0,3,5, 8, 3, 1, 8,
  0.00766, 0.00677,-0.00149, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00114, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00020, 0.00020, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000 ,
"duuP5308"},
	{2,0,0,3,5, 8, 3, 2,10,
 -0.00743, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00115,-0.00075, 0.00218, 0.00089, 0.00000 ,
  0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00019, 0.00019, 0.00018, 0.00019, 0.00000 ,
"duuP5308"},
	{2,0,0,3,5, 8, 4, 1,11,
  0.00746, 0.00651,-0.00274, 0.00000,-0.00065, 0.00000, 0.00129, 0.00000, 0.00000,-0.00065, 0.00000, 0.00111 ,
  0.00016, 0.00019, 0.00026, 0.00000, 0.00023, 0.00000, 0.00020, 0.00000, 0.00000, 0.00017, 0.00000, 0.00017 ,
"duuP5408"},
	{2,0,0,3,5, 8, 4, 2, 8,
 -0.00552, 0.00000,-0.00077, 0.00000, 0.00016, 0.00000, 0.00257,-0.00193, 0.00152, 0.00000, 0.00000, 0.00000 ,
  0.00019, 0.00000, 0.00032, 0.00000, 0.00028, 0.00000, 0.00025, 0.00019, 0.00023, 0.00000, 0.00000, 0.00000 ,
"duuP5408"},
	{2,0,0,3,5, 8, 5, 1,11,
  0.00090, 0.00000, 0.00024, 0.00000,-0.00179, 0.00000, 0.00000, 0.00000,-0.00049, 0.00000, 0.00000, 0.00047 ,
  0.00011, 0.00000, 0.00017, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000, 0.00007 ,
"duuP5508"},
	{2,0,0,3,5, 8, 5, 2, 9,
  0.00712,-0.00063,-0.00695, 0.00078,-0.00459, 0.00000,-0.00235, 0.00000,-0.00101, 0.00045, 0.00000, 0.00000 ,
  0.00018, 0.00011, 0.00033, 0.00009, 0.00028, 0.00000, 0.00020, 0.00000, 0.00012, 0.00006, 0.00000, 0.00000 ,
"duuP5508"},
	{2,0,0,3,5, 8, 6, 1, 6,
  0.00061, 0.00160, 0.00000, 0.00034,-0.00136, 0.00000, 0.00027, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00008, 0.00000, 0.00007, 0.00007, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5608"},
	{2,0,0,3,5, 8, 6, 2, 8,
  0.00723, 0.00000,-0.00185, 0.00161,-0.00090, 0.00057,-0.00046, 0.00000,-0.00025, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00000, 0.00006, 0.00006, 0.00007, 0.00006, 0.00006, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000 ,
"duuP5608"},
	{2,0,0,3,5, 8, 7, 1, 6,
  0.00142, 0.00146,-0.00015, 0.00000, 0.00000,-0.00006, 0.00050, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00006, 0.00004, 0.00000, 0.00000, 0.00003, 0.00003, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5708"},
	{2,0,0,3,5, 8, 7, 2,10,
  0.00252,-0.00051, 0.00017, 0.00000,-0.00056, 0.00000, 0.00000, 0.00033,-0.00040, 0.00000, 0.00030, 0.00000 ,
  0.00004, 0.00005, 0.00005, 0.00000, 0.00004, 0.00000, 0.00000, 0.00004, 0.00004, 0.00000, 0.00004, 0.00000 ,
"duuP5708"},
	{2,0,0,3,6, 9, 1, 1, 9,
  0.00158, 0.00099,-0.00319, 0.00000, 0.00087, 0.00000,-0.00105, 0.00000, 0.00000, 0.00053, 0.00000, 0.00000 ,
  0.00008, 0.00009, 0.00013, 0.00000, 0.00011, 0.00000, 0.00009, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000 ,
"duuP6109"},
	{2,0,0,3,6, 9, 1, 2,11,
  0.00631, 0.02849, 0.01988, 0.00000, 0.00000, 0.00000,-0.00603,-0.00726, 0.00000, 0.00000, 0.00000, 0.00652 ,
  0.00085, 0.00125, 0.00122, 0.00000, 0.00000, 0.00000, 0.00157, 0.00152, 0.00000, 0.00000, 0.00000, 0.00120 ,
"duuP6109"},
	{2,0,0,3,6, 9, 2, 1, 5,
  0.01874,-0.02712, 0.00000,-0.00100, 0.00341,-0.00318, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00026, 0.00000, 0.00020, 0.00011, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6209"},
	{2,0,0,3,6, 9, 2, 2,10,
  0.02123, 0.03171, 0.02872, 0.00000, 0.00000,-0.00942, 0.00000,-0.00610, 0.00000, 0.00362, 0.00455, 0.00000 ,
  0.00024, 0.00038, 0.00032, 0.00000, 0.00000, 0.00030, 0.00000, 0.00035, 0.00000, 0.00028, 0.00025, 0.00000 ,
"duuP6209"},
	{2,0,0,3,6, 9, 3, 1,11,
  0.00821,-0.01004,-0.00039, 0.00000, 0.00475,-0.00056, 0.00000, 0.00256, 0.00000, 0.00000, 0.00000,-0.00099 ,
  0.00014, 0.00017, 0.00023, 0.00000, 0.00017, 0.00015, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00012 ,
"duuP6309"},
	{2,0,0,3,6, 9, 3, 2, 9,
  0.01415, 0.02522, 0.01559,-0.00492,-0.00640,-0.00806, 0.00000, 0.00000, 0.00000, 0.00569, 0.00000, 0.00000 ,
  0.00042, 0.00064, 0.00063, 0.00077, 0.00060, 0.00063, 0.00000, 0.00000, 0.00000, 0.00060, 0.00000, 0.00000 ,
"duuP6309"},
	{2,0,0,3,6, 9, 4, 1,11,
  0.00645,-0.00185, 0.00000, 0.00000, 0.00000,-0.00058, 0.00000, 0.00125, 0.00000, 0.00000, 0.00136,-0.00091 ,
  0.00006, 0.00011, 0.00000, 0.00000, 0.00000, 0.00009, 0.00000, 0.00009, 0.00000, 0.00000, 0.00008, 0.00008 ,
"duuP6409"},
	{2,0,0,3,6, 9, 4, 2, 8,
 -0.00606, 0.00000, 0.00230,-0.00056, 0.00000, 0.00144, 0.00000, 0.00000,-0.00178, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00000, 0.00014, 0.00012, 0.00000, 0.00012, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000 ,
"duuP6409"},
	{2,0,0,3,6, 9, 5, 1, 9,
  0.00074, 0.01200,-0.00439, 0.00000, 0.00461,-0.00255, 0.00000, 0.00000, 0.00000, 0.00295, 0.00000, 0.00000 ,
  0.00010, 0.00011, 0.00016, 0.00000, 0.00011, 0.00008, 0.00000, 0.00000, 0.00000, 0.00008, 0.00000, 0.00000 ,
"duuP6509"},
	{2,0,0,3,6, 9, 6, 1,11,
 -0.00140, 0.00742,-0.00230,-0.00317,-0.00026,-0.00193,-0.00141, 0.00000, 0.00000, 0.00000, 0.00061,-0.00075 ,
  0.00010, 0.00017, 0.00018, 0.00015, 0.00015, 0.00011, 0.00010, 0.00000, 0.00000, 0.00000, 0.00007, 0.00007 ,
"duuP6609"},
	{2,0,0,3,6, 9, 6, 2,11,
 -0.01660, 0.00000,-0.00678, 0.00000, 0.00000, 0.00392, 0.00000, 0.00000, 0.00000, 0.00000,-0.00144,-0.00137 ,
  0.00011, 0.00000, 0.00016, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00010 ,
"duuP6609"},
	{2,0,0,3,6, 9, 7, 1,10,
  0.00253, 0.00284, 0.00231, 0.00000, 0.00000, 0.00215,-0.00115, 0.00141, 0.00000, 0.00000, 0.00129, 0.00000 ,
  0.00005, 0.00008, 0.00008, 0.00000, 0.00000, 0.00007, 0.00006, 0.00006, 0.00000, 0.00000, 0.00006, 0.00000 ,
"duuP6709"},
	{2,0,0,3,5,10, 1, 1,11,
 -0.01798,-0.02278,-0.00263, 0.00000, 0.00503, 0.00043, 0.00000, 0.00542, 0.00000, 0.00429, 0.00000, 0.00222 ,
  0.00011, 0.00013, 0.00019, 0.00000, 0.00014, 0.00012, 0.00000, 0.00013, 0.00000, 0.00013, 0.00000, 0.00012 ,
"duuP5110"},
	{2,0,0,3,5,10, 1, 2, 8,
 -0.03360, 0.05225, 0.00591, 0.01320,-0.00156, 0.00625, 0.00419, 0.00000, 0.00180, 0.00000, 0.00000, 0.00000 ,
  0.00019, 0.00021, 0.00034, 0.00018, 0.00030, 0.00014, 0.00024, 0.00000, 0.00016, 0.00000, 0.00000, 0.00000 ,
"duuP5110"},
	{2,0,0,3,5,10, 2, 1,11,
  0.02525,-0.04695, 0.00000, 0.00000, 0.00298, 0.00000,-0.00563, 0.00517,-0.00149, 0.00000, 0.00000, 0.00115 ,
  0.00006, 0.00012, 0.00000, 0.00000, 0.00010, 0.00000, 0.00012, 0.00009, 0.00010, 0.00000, 0.00000, 0.00009 ,
"duuP5210"},
	{2,0,0,3,5,10, 2, 2,10,
 -0.00877, 0.04567, 0.00000, 0.00000, 0.00000, 0.00361, 0.00000,-0.00213, 0.00000, 0.00257,-0.00185, 0.00000 ,
  0.00012, 0.00022, 0.00000, 0.00000, 0.00000, 0.00017, 0.00000, 0.00017, 0.00000, 0.00017, 0.00015, 0.00000 ,
"duuP5210"},
	{2,0,0,3,5,10, 3, 1, 7,
  0.05231,-0.07972, 0.00000,-0.01746, 0.00271,-0.00174,-0.00356, 0.00233, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00034, 0.00000, 0.00030, 0.00012, 0.00023, 0.00012, 0.00016, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5310"},
	{2,0,0,3,5,10, 3, 2, 9,
  0.11223,-0.04091,-0.00741, 0.00971, 0.00000, 0.00000, 0.00585,-0.00527, 0.00650,-0.00382, 0.00000, 0.00000 ,
  0.00060, 0.00086, 0.00082, 0.00078, 0.00000, 0.00000, 0.00123, 0.00051, 0.00078, 0.00093, 0.00000, 0.00000 ,
"duuP5310"},
	{2,0,0,3,5,10, 4, 1, 7,
  0.02099,-0.06392, 0.00000,-0.01923, 0.00515,-0.01178, 0.00000,-0.00464, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00038, 0.00000, 0.00033, 0.00012, 0.00025, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5410"},
	{2,0,0,3,5,10, 4, 2, 1,
  0.02978, 0.02858, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00025, 0.00043, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5410"},
	{2,0,0,3,5,10, 5, 1, 9,
 -0.00989,-0.01679, 0.01953,-0.00712, 0.00968, 0.00424, 0.00000, 0.00673, 0.00128, 0.00153, 0.00000, 0.00000 ,
  0.00014, 0.00037, 0.00023, 0.00034, 0.00017, 0.00031, 0.00000, 0.00026, 0.00013, 0.00018, 0.00000, 0.00000 ,
"duuP5510"},
	{2,0,0,3,5,10, 5, 2, 4,
  0.00134, 0.00620, 0.00000, 0.00144,-0.00101, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00019, 0.00000, 0.00015, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5510"},
	{2,0,0,3,5,10, 6, 1, 7,
 -0.02158, 0.00000, 0.02682,-0.00932, 0.01580, 0.00000, 0.00000, 0.00772, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00012, 0.00000, 0.00020, 0.00012, 0.00016, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5610"},
	{2,0,0,3,5,10, 6, 2,11,
 -0.00129, 0.00827, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00197, 0.00000, 0.00000,-0.00246 ,
  0.00007, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00010 ,
"duuP5610"},
	{2,0,0,3,5,10, 7, 1,11,
  0.00202,-0.01759, 0.00472, 0.00000, 0.00000, 0.00000, 0.00000,-0.00187, 0.00000, 0.00000, 0.00000, 0.00219 ,
  0.00012, 0.00018, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00014 ,
"duuP5710"},
	{2,0,0,3,5,10, 7, 2,11,
 -0.00316, 0.01057, 0.00000, 0.00000,-0.00183, 0.00000, 0.00000,-0.00248, 0.00000, 0.00000,-0.00260,-0.00172 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00011, 0.00011 ,
"duuP5710"},
	{2,0,0,3,6,11, 1, 1,11,
  0.02696, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.03854, 0.00000,-0.06290,-0.05105 ,
  0.00031, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00054, 0.00000, 0.00051, 0.00044 ,
"duuP6111"},
	{2,0,0,3,6,11, 1, 2, 8,
 -0.00067, 0.02103, 0.00000, 0.00553,-0.00247, 0.00400, 0.00000, 0.00120, 0.00079, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00029, 0.00000, 0.00026, 0.00012, 0.00022, 0.00000, 0.00016, 0.00012, 0.00000, 0.00000, 0.00000 ,
"duuP6111"},
	{2,0,0,3,6,11, 2, 1,10,
  0.02650,-0.01470, 0.00000, 0.00000,-0.00408, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00368, 0.00000 ,
  0.00007, 0.00014, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00000 ,
"duuP6211"},
	{2,0,0,3,6,11, 2, 2, 7,
  0.00104, 0.01526, 0.00622, 0.00000,-0.00027, 0.00000, 0.00362,-0.00079, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00014, 0.00014, 0.00024, 0.00000, 0.00020, 0.00000, 0.00014, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6211"},
	{2,0,0,3,6,11, 3, 1,10,
  0.03051,-0.01330,-0.00399,-0.00606,-0.00940, 0.00000,-0.00556, 0.00000,-0.00285, 0.00000,-0.00162, 0.00000 ,
  0.00019, 0.00019, 0.00035, 0.00014, 0.00031, 0.00000, 0.00027, 0.00000, 0.00021, 0.00000, 0.00015, 0.00000 ,
"duuP6311"},
	{2,0,0,3,6,11, 3, 2, 8,
  0.00112, 0.01837, 0.00444, 0.00000, 0.00000, 0.00094, 0.00092, 0.00000,-0.00117, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00013, 0.00014, 0.00000, 0.00000, 0.00010, 0.00011, 0.00000, 0.00011, 0.00000, 0.00000, 0.00000 ,
"duuP6311"},
	{2,0,0,3,5,12, 1, 1,10,
  0.03363,-0.03606, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00348,-0.00252, 0.00000,-0.00167, 0.00000 ,
  0.00009, 0.00016, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00013, 0.00014, 0.00000, 0.00014, 0.00000 ,
"duuP5112"},
	{2,0,0,3,5,12, 1, 2, 9,
  0.01890, 0.01647, 0.01431, 0.00000, 0.00907, 0.00000, 0.00433, 0.00000, 0.00000,-0.00159, 0.00000, 0.00000 ,
  0.00020, 0.00021, 0.00036, 0.00000, 0.00030, 0.00000, 0.00019, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000 ,
"duuP5112"},
	{2,0,0,3,5,12, 2, 1,11,
  0.03784,-0.01994, 0.00576, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00362 ,
  0.00009, 0.00014, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011 ,
"duuP5212"},
	{2,0,0,3,5,12, 2, 2, 9,
  0.01381, 0.01712, 0.00000, 0.00664,-0.00169, 0.00000, 0.00131, 0.00000,-0.00307, 0.00119, 0.00000, 0.00000 ,
  0.00008, 0.00020, 0.00000, 0.00016, 0.00013, 0.00000, 0.00014, 0.00000, 0.00013, 0.00011, 0.00000, 0.00000 ,
"duuP5212"},
	{2,0,0,3,5,12, 3, 1, 5,
  0.03224,-0.02062, 0.00000,-0.00470, 0.00199,-0.00259, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00018, 0.00000, 0.00016, 0.00010, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5312"},
	{2,0,0,3,5,12, 3, 2, 9,
  0.01153, 0.00928, 0.00000, 0.00000, 0.00000, 0.00000, 0.00284,-0.00184, 0.00000, 0.00303, 0.00000, 0.00000 ,
  0.00007, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00012, 0.00000, 0.00012, 0.00000, 0.00000 ,
"duuP5312"},
	{2,0,0,3,5,12, 4, 1, 5,
  0.03090,-0.01649,-0.00137, 0.00000, 0.00230,-0.00121, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00013, 0.00016, 0.00000, 0.00013, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5412"},
	{2,0,0,3,5,12, 4, 2,11,
  0.01328, 0.01624, 0.00000, 0.00585, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00049, 0.00000,-0.00137 ,
  0.00008, 0.00020, 0.00000, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012 ,
"duuP5412"},
	{2,0,0,3,5,12, 5, 1,11,
  0.02972,-0.02268, 0.00000,-0.00522, 0.00000, 0.00000,-0.00075, 0.00000, 0.00345, 0.00000, 0.00281, 0.00234 ,
  0.00008, 0.00017, 0.00000, 0.00014, 0.00000, 0.00000, 0.00012, 0.00000, 0.00013, 0.00000, 0.00012, 0.00011 ,
"duuP5512"},
	{2,0,0,3,5,12, 5, 2,11,
  0.01385, 0.01045, 0.00000, 0.00000, 0.00000,-0.00366, 0.00000, 0.00000, 0.00000, 0.00049, 0.00000,-0.00723 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012 ,
"duuP5512"},
	{2,0,0,3,5,12, 6, 1,11,
  0.03064,-0.01739, 0.00000, 0.00000, 0.00000, 0.00218, 0.00000,-0.00152, 0.00167, 0.00000, 0.00000, 0.00292 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00012, 0.00011, 0.00000, 0.00000, 0.00011 ,
"duuP5612"},
	{2,0,0,3,5,12, 6, 2, 6,
  0.01324, 0.01094,-0.00424,-0.00524, 0.00000, 0.00000, 0.00413, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00012, 0.00021, 0.00017, 0.00017, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5612"},
	{2,0,0,3,5,12, 7, 1,11,
  0.02831,-0.00989, 0.00000, 0.00546, 0.00000, 0.01013,-0.00184, 0.00435, 0.00382, 0.00000, 0.00000, 0.00290 ,
  0.00008, 0.00027, 0.00000, 0.00024, 0.00000, 0.00021, 0.00013, 0.00016, 0.00012, 0.00000, 0.00000, 0.00012 ,
"duuP5712"},
	{2,0,0,3,5,12, 7, 2,11,
  0.01033, 0.01394,-0.00579, 0.00000, 0.00000,-0.00349, 0.00000, 0.00000, 0.00000, 0.00000, 0.00456,-0.00371 ,
  0.00011, 0.00016, 0.00016, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00012 ,
"duuP5712"},
	{2,0,0,3,6,13, 4, 1, 9,
  0.03050,-0.02363, 0.00000,-0.00330, 0.00000, 0.00000, 0.00000, 0.00364, 0.00000, 0.00201, 0.00000, 0.00000 ,
  0.00008, 0.00019, 0.00000, 0.00015, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012, 0.00000, 0.00000 ,
"duuP6413"},
	{2,0,0,3,6,13, 4, 2,10,
  0.01060, 0.01580, 0.00250, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00093, 0.00000 ,
  0.00010, 0.00014, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000 ,
"duuP6413"},
	{2,0,0,3,6,13, 5, 1,10,
  0.03207,-0.02107, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00315, 0.00000, 0.00592, 0.00222, 0.00000 ,
  0.00008, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012, 0.00012, 0.00000 ,
"duuP6513"},
	{2,0,0,3,6,13, 6, 1, 8,
  0.03206,-0.02387, 0.00000,-0.00498, 0.00198,-0.00376, 0.00097, 0.00000,-0.00211, 0.00000, 0.00000, 0.00000 ,
  0.00011, 0.00028, 0.00000, 0.00025, 0.00017, 0.00020, 0.00019, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000 ,
"duuP6613"},
	{2,0,0,3,6,13, 7, 1, 7,
  0.02929,-0.01732,-0.01052, 0.00000,-0.00816, 0.00000,-0.00521, 0.00206, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00019, 0.00022, 0.00032, 0.00000, 0.00028, 0.00000, 0.00022, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6713"},
	{2,0,0,3,6,13, 7, 2, 8,
  0.01131, 0.01014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00509, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00016, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000 ,
"duuP6713"},
	{2,0,0,3,5,14, 5, 1,11,
  0.03811,-0.01850, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00127, 0.00000, 0.00000, 0.00000, 0.00204 ,
  0.00012, 0.00022, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00016, 0.00000, 0.00000, 0.00000, 0.00016 ,
"duuP5514"},
	{2,0,0,3,5,14, 5, 2, 7,
  0.02296,-0.02232, 0.06606, 0.00000, 0.00000,-0.01504, 0.00000, 0.02446, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00298, 0.00338, 0.00411, 0.00000, 0.00000, 0.00528, 0.00000, 0.00470, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5514"},
	{2,0,0,3,5,14, 6, 1,10,
  0.03176,-0.01353, 0.00000,-0.00682, 0.00000,-0.00344, 0.00000, 0.00000, 0.00000,-0.00184, 0.00091, 0.00000 ,
  0.00009, 0.00024, 0.00000, 0.00021, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000, 0.00013, 0.00013, 0.00000 ,
"duuP5614"},
	{2,0,0,3,5,14, 6, 2, 6,
  0.03914, 0.00000, 0.11130, 0.08399, 0.00000, 0.00000,-0.06867, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00102, 0.00000, 0.00134, 0.00155, 0.00000, 0.00000, 0.00166, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5614"},
	{2,0,0,3,5,14, 7, 1,11,
  0.03511,-0.01346, 0.00000,-0.00588, 0.00000, 0.00000,-0.00107, 0.00155, 0.00208, 0.00000, 0.00000,-0.00158 ,
  0.00009, 0.00021, 0.00000, 0.00017, 0.00000, 0.00000, 0.00013, 0.00013, 0.00013, 0.00000, 0.00000, 0.00013 ,
"duuP5714"},
	{2,0,0,3,5,14, 7, 2,11,
  0.03453, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.02340, 0.00000, 0.02567, 0.05819 ,
  0.00034, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00063, 0.00000, 0.00056, 0.00058 ,
"duuP5714"},
	{2,0,0,3,6,15, 4, 1, 7,
  0.01736,-0.02949,-0.00338, 0.00000, 0.00257, 0.00000, 0.00000, 0.00127, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00018, 0.00021, 0.00000, 0.00018, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6415"},
	{2,0,0,3,6,15, 4, 2, 9,
  0.01632, 0.00000, 0.00000,-0.00062, 0.00271, 0.00493, 0.00000, 0.00000, 0.00148,-0.00186, 0.00000, 0.00000 ,
  0.00009, 0.00000, 0.00000, 0.00014, 0.00012, 0.00014, 0.00000, 0.00000, 0.00012, 0.00012, 0.00000, 0.00000 ,
"duuP6415"},
	{2,0,0,3,6,15, 5, 1, 5,
  0.03619,-0.03025,-0.01112, 0.00000,-0.00230,-0.00150, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00018, 0.00022, 0.00000, 0.00018, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6515"},
	{2,0,0,3,6,15, 5, 2,10,
  0.01339, 0.01907, 0.00000, 0.00076, 0.00000, 0.00575,-0.00120, 0.00000, 0.00000,-0.00188,-0.00118, 0.00000 ,
  0.00009, 0.00026, 0.00000, 0.00022, 0.00000, 0.00017, 0.00012, 0.00000, 0.00000, 0.00012, 0.00012, 0.00000 ,
"duuP6515"},
	{2,0,0,3,6,15, 7, 1, 6,
  0.06128,-0.04205,-0.00958,-0.00967, 0.00000,-0.00397,-0.00105, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00015, 0.00030, 0.00021, 0.00027, 0.00000, 0.00022, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6715"},
	{2,0,0,3,6,15, 7, 2, 3,
  0.04511, 0.01678, 0.00224,-0.00652, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00016, 0.00031, 0.00023, 0.00023, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6715"},
	{2,0,0,3,5,16, 1, 1,11,
 -0.00673, 0.00000, 0.00352, 0.00000, 0.00000,-0.00035, 0.00000, 0.00067, 0.00000, 0.00000, 0.00000, 0.00095 ,
  0.00006, 0.00000, 0.00007, 0.00000, 0.00000, 0.00009, 0.00000, 0.00008, 0.00000, 0.00000, 0.00000, 0.00006 ,
"duuP5116"},
	{2,0,0,3,5,16, 1, 2,10,
  0.00211, 0.00000,-0.00557, 0.00000,-0.00167, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00055, 0.00000 ,
  0.00005, 0.00000, 0.00010, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00000 ,
"duuP5116"},
/* 	{2,0,0,3,5,16, 2, 1,11, */
/*  -0.02212, 0.01134,-0.00272, 0.00000, 0.00000,-0.00412, 0.00183, 0.00000, 0.00000, 0.00000, 0.00000, 0.00071 , */
/*   0.00015, 0.00019, 0.00019, 0.00000, 0.00000, 0.00010, 0.00008, 0.00000, 0.00000, 0.00000, 0.00000, 0.00007 , */
/* "duuP5216"}, */
	{2,0,0,3,5,16, 2, 2,11,
  0.00783, 0.00000,-0.00874, 0.00000,-0.00299, 0.00000, 0.00206, 0.00000, 0.00000, 0.00000, 0.00000, 0.00106 ,
  0.00010, 0.00000, 0.00017, 0.00000, 0.00013, 0.00000, 0.00009, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005 ,
"duuP5216"},
	{2,0,0,3,5,16, 3, 1,10,
 -0.01463, 0.00446, 0.00912, 0.00000, 0.00592, 0.00000, 0.00362, 0.00067, 0.00106, 0.00000, 0.00129, 0.00000 ,
  0.00033, 0.00009, 0.00061, 0.00000, 0.00051, 0.00000, 0.00039, 0.00006, 0.00026, 0.00000, 0.00013, 0.00000 ,
"duuP5316"},
	{2,0,0,3,5,16, 3, 2,11,
  0.00809, 0.00000,-0.00775, 0.00149,-0.00257, 0.00000, 0.00000,-0.00184, 0.00000, 0.00000, 0.00000, 0.00086 ,
  0.00011, 0.00000, 0.00019, 0.00006, 0.00012, 0.00000, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00006 ,
"duuP5316"},
	{2,0,0,3,5,16, 4, 1, 4,
 -0.01058, 0.00000, 0.00251, 0.00000,-0.00135, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00006, 0.00000, 0.00009, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5416"},
	{2,0,0,3,5,16, 4, 2,11,
  0.00641, 0.00000,-0.00214, 0.00082, 0.00000, 0.00000,-0.00037, 0.00000, 0.00153, 0.00091, 0.00000, 0.00070 ,
  0.00007, 0.00000, 0.00010, 0.00006, 0.00000, 0.00000, 0.00008, 0.00000, 0.00008, 0.00006, 0.00000, 0.00006 ,
"duuP5416"},
	{2,0,0,3,5,16, 6, 1, 9,
 -0.01888, 0.00000,-0.00991, 0.00000,-0.01624, 0.00000,-0.01016,-0.00176,-0.00225,-0.00125, 0.00000, 0.00000 ,
  0.00031, 0.00000, 0.00060, 0.00000, 0.00055, 0.00000, 0.00039, 0.00013, 0.00020, 0.00014, 0.00000, 0.00000 ,
"duuP5616"},
	{2,0,0,3,5,16, 6, 2, 9,
  0.00898, 0.00900,-0.00879, 0.00451, 0.00000, 0.00000, 0.00000, 0.00078, 0.00000,-0.00179, 0.00000, 0.00000 ,
  0.00013, 0.00032, 0.00019, 0.00022, 0.00000, 0.00000, 0.00000, 0.00015, 0.00000, 0.00015, 0.00000, 0.00000 ,
"duuP5616"},
	{2,0,0,3,5,16, 7, 1, 8,
 -0.00715, 0.00000, 0.00270, 0.00000,-0.00072, 0.00000, 0.00000, 0.00000, 0.00100, 0.00000, 0.00000, 0.00000 ,
  0.00003, 0.00000, 0.00005, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000, 0.00004, 0.00000, 0.00000, 0.00000 ,
"duuP5716"},
	{2,0,0,3,5,16, 7, 2, 7,
  0.00403, 0.00682, 0.00000, 0.00000, 0.00361, 0.00137, 0.00000, 0.00093, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00010, 0.00000, 0.00000, 0.00009, 0.00009, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5716"},
	{2,0,0,3,6, 1, 1, 1, 9,
 -0.00122, 0.00679, 0.00000, 0.00000, 0.00000, 0.00000,-0.00236,-0.00235,-0.00144,-0.00115, 0.00000, 0.00000 ,
  0.00003, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00005, 0.00005, 0.00005, 0.00000, 0.00000 ,
"duuP6101"},
	{2,0,0,3,6, 1, 1, 2,11,
  0.00096, 0.00000, 0.00177, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00142, 0.00137 ,
  0.00004, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00005 ,
"duuP6101"},
	{2,0,0,3,6, 1, 2, 1,11,
  0.00127, 0.00787, 0.00000, 0.00000, 0.00000, 0.00000,-0.00177, 0.00000, 0.00000, 0.00000, 0.00000, 0.00086 ,
  0.00004, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005 ,
"duuP6201"},
	{2,0,0,3,6, 1, 2, 2,11,
 -0.00279, 0.01098, 0.00146, 0.00303,-0.00245, 0.00000, 0.00025, 0.00000, 0.00214, 0.00000, 0.00000,-0.00083 ,
  0.00015, 0.00014, 0.00028, 0.00011, 0.00024, 0.00000, 0.00018, 0.00000, 0.00012, 0.00000, 0.00000, 0.00008 ,
"duuP6201"},
	{2,0,0,3,6, 1, 3, 1,11,
  0.00253, 0.00807, 0.00000, 0.00137, 0.00102, 0.00000,-0.00122, 0.00000, 0.00000, 0.00000,-0.00089, 0.00132 ,
  0.00004, 0.00011, 0.00000, 0.00008, 0.00007, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00006, 0.00006 ,
"duuP6301"},
	{2,0,0,3,6, 1, 4, 1, 9,
  0.00226, 0.00668, 0.00000, 0.00000,-0.00086, 0.00000, 0.00000, 0.00000, 0.00000,-0.00094, 0.00000, 0.00000 ,
  0.00005, 0.00009, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000 ,
"duuP6401"},
	{2,0,0,3,6, 1, 4, 2, 9,
 -0.00851, 0.01155, 0.00459, 0.00000, 0.00000,-0.00255, 0.00000, 0.00000, 0.00000,-0.00125, 0.00000, 0.00000 ,
  0.00012, 0.00018, 0.00018, 0.00000, 0.00000, 0.00015, 0.00000, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000 ,
"duuP6401"},
	{2,0,0,3,6, 1, 5, 1, 7,
 -0.00254, 0.00568,-0.00010, 0.00000,-0.00208,-0.00058,-0.00081, 0.00100, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00008, 0.00011, 0.00000, 0.00010, 0.00007, 0.00008, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6501"},
	{2,0,0,3,6, 1, 6, 1, 7,
 -0.00386, 0.00200, 0.00000, 0.00000, 0.00000,-0.00034, 0.00000, 0.00158, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00007, 0.00000, 0.00000, 0.00000, 0.00006, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6601"},
	{2,0,0,3,6, 1, 6, 2, 8,
  0.00107, 0.00005, 0.00000, 0.00117, 0.00000, 0.00000, 0.00027, 0.00000,-0.00049, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00007, 0.00000, 0.00006, 0.00000, 0.00000, 0.00005, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000 ,
"duuP6601"},
	{2,0,0,3,6, 1, 7, 1, 8,
 -0.00587,-0.00200, 0.00000, 0.00000, 0.00000,-0.00094, 0.00000, 0.00141, 0.00116, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00007, 0.00000, 0.00000, 0.00000, 0.00006, 0.00000, 0.00006, 0.00005, 0.00000, 0.00000, 0.00000 ,
"duuP6701"},
	{2,0,0,3,6, 1, 7, 2,10,
  0.00214,-0.00098, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00044, 0.00000 ,
  0.00003, 0.00005, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00004, 0.00000 ,
"duuP6701"},
	{2,0,0,3,5, 2, 1, 1, 8,
  0.01183,-0.01332, 0.00000,-0.00248,-0.00096, 0.00000, 0.00000, 0.00000, 0.00107, 0.00000, 0.00000, 0.00000 ,
  0.00006, 0.00013, 0.00000, 0.00010, 0.00009, 0.00000, 0.00000, 0.00000, 0.00008, 0.00000, 0.00000, 0.00000 ,
"duuP5102"},
	{2,0,0,3,5, 2, 2, 1, 7,
  0.01627, 0.00000, 0.00000, 0.00000,-0.00388,-0.00050, 0.00000, 0.00295, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00006, 0.00000, 0.00000, 0.00000, 0.00008, 0.00009, 0.00000, 0.00008, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5202"},
	{2,0,0,3,5, 2, 4, 1, 9,
  0.00599,-0.00616, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00074, 0.00000, 0.00122, 0.00000, 0.00000 ,
  0.00006, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00009, 0.00000, 0.00009, 0.00000, 0.00000 ,
"duuP5402"},
	{2,0,0,3,5, 2, 4, 2,10,
  0.07068, 0.00000, 0.05307, 0.05694, 0.00000, 0.00000,-0.02785, 0.07715, 0.04843,-0.03762, 0.04406, 0.00000 ,
  0.00049, 0.00000, 0.00099, 0.00102, 0.00000, 0.00000, 0.00106, 0.00113, 0.00104, 0.00106, 0.00096, 0.00000 ,
"duuP5402"},
	{2,0,0,3,5, 2, 5, 1, 8,
  0.00426,-0.01822, 0.00000,-0.00282, 0.00142, 0.00000, 0.00000, 0.00000,-0.00126, 0.00000, 0.00000, 0.00000 ,
  0.00012, 0.00027, 0.00000, 0.00021, 0.00017, 0.00000, 0.00000, 0.00000, 0.00016, 0.00000, 0.00000, 0.00000 ,
"duuP5502"},
	{2,0,0,3,5, 2, 5, 2, 5,
  0.06773, 0.01509, 0.00000,-0.04917,-0.07745, 0.05015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00086, 0.00141, 0.00000, 0.00129, 0.00105, 0.00114, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5502"},
	{2,0,0,3,5, 2, 6, 1,11,
  0.00742,-0.01093, 0.00000,-0.00832, 0.00000, 0.00000, 0.00000, 0.00000,-0.00277, 0.00000, 0.00000,-0.00283 ,
  0.00011, 0.00023, 0.00000, 0.00018, 0.00000, 0.00000, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000, 0.00014 ,
"duuP5602"},
	{2,0,0,3,5, 2, 6, 2,10,
 -0.01642, 0.04751, 0.00000, 0.00000, 0.00488, 0.00000, 0.00000, 0.02988, 0.00000, 0.02057, 0.01263, 0.00000 ,
  0.00028, 0.00063, 0.00000, 0.00000, 0.00044, 0.00000, 0.00000, 0.00036, 0.00000, 0.00034, 0.00031, 0.00000 ,
"duuP5602"},
	{2,0,0,3,5, 2, 7, 1,10,
  0.01237, 0.03165, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00334, 0.00000,-0.01182, 0.00000 ,
  0.00016, 0.00030, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00021, 0.00000, 0.00021, 0.00000 ,
"duuP5702"},
	{2,0,0,3,5, 2, 7, 2,11,
 -0.01864, 0.00000, 0.00000, 0.00000, 0.09835, 0.00000,-0.03039,-0.06281, 0.00000, 0.02527,-0.08058, 0.07035 ,
  0.00060, 0.00000, 0.00000, 0.00000, 0.00102, 0.00000, 0.00089, 0.00094, 0.00000, 0.00122, 0.00089, 0.00112 ,
"duuP5702"},
	{2,0,0,3,6, 3, 1, 1, 7,
  0.00042,-0.01024, 0.00256,-0.00144, 0.00000, 0.00039, 0.00139,-0.00144, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00023, 0.00013, 0.00021, 0.00000, 0.00017, 0.00010, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6103"},
	{2,0,0,3,6, 3, 1, 2,11,
 -0.01587, 0.00596, 0.00000,-0.00459, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00370 ,
  0.00007, 0.00017, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010 ,
"duuP6103"},
	{2,0,0,3,6, 3, 2, 1,10,
  0.00860,-0.01283, 0.00000, 0.00000,-0.00170, 0.00000, 0.00000, 0.00236,-0.00191, 0.00183, 0.00208, 0.00000 ,
  0.00009, 0.00015, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00013, 0.00013, 0.00013, 0.00013, 0.00000 ,
"duuP6203"},
	{2,0,0,3,6, 3, 2, 2,11,
 -0.01623, 0.00633, 0.00778, 0.00000, 0.00233, 0.00000, 0.00000, 0.00000, 0.00000,-0.00066, 0.00000, 0.00160 ,
  0.00010, 0.00013, 0.00017, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00011 ,
"duuP6203"},
	{2,0,0,3,6, 3, 3, 1,11,
  0.01486,-0.01401,-0.00356, 0.00000, 0.00000, 0.00000,-0.00270, 0.00000,-0.00183, 0.00000, 0.00000,-0.00152 ,
  0.00010, 0.00015, 0.00015, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00013, 0.00000, 0.00000, 0.00012 ,
"duuP6303"},
	{2,0,0,3,6, 3, 3, 2, 6,
 -0.01858, 0.00207, 0.00000,-0.00772, 0.00000,-0.00231,-0.00214, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00020, 0.00000, 0.00017, 0.00000, 0.00013, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6303"},
	{2,0,0,3,6, 3, 4, 1, 9,
  0.02117,-0.02603,-0.01249,-0.01373,-0.00330,-0.01803, 0.00000,-0.01000,-0.00237,-0.00377, 0.00000, 0.00000 ,
  0.00039, 0.00132, 0.00063, 0.00115, 0.00044, 0.00095, 0.00000, 0.00070, 0.00028, 0.00046, 0.00000, 0.00000 ,
"duuP6403"},
	{2,0,0,3,6, 3, 4, 2,10,
 -0.03220, 0.01532, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.04239, 0.00610,-0.10136,-0.02686, 0.00000 ,
  0.00030, 0.00090, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00079, 0.00056, 0.00073, 0.00058, 0.00000 ,
"duuP6403"},
	{2,0,0,3,6, 3, 5, 1,10,
  0.02237,-0.01371, 0.00000, 0.00000, 0.00173, 0.00000,-0.00224,-0.00453, 0.00000, 0.00000, 0.00245, 0.00000 ,
  0.00016, 0.00030, 0.00000, 0.00000, 0.00026, 0.00000, 0.00023, 0.00022, 0.00000, 0.00000, 0.00021, 0.00000 ,
"duuP6503"},
	{2,0,0,3,6, 3, 5, 2, 8,
 -0.01481,-0.00475, 0.01074,-0.00500, 0.00000, 0.00000,-0.00173, 0.00000, 0.00607, 0.00000, 0.00000, 0.00000 ,
  0.00017, 0.00036, 0.00024, 0.00024, 0.00000, 0.00000, 0.00018, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000 ,
"duuP6503"},
	{2,0,0,3,6, 3, 6, 1,11,
  0.00720, 0.03195,-0.01099, 0.00000, 0.00000,-0.00403, 0.00000, 0.00046, 0.00000, 0.00493, 0.00140, 0.00342 ,
  0.00027, 0.00038, 0.00040, 0.00000, 0.00000, 0.00033, 0.00000, 0.00033, 0.00000, 0.00034, 0.00028, 0.00031 ,
"duuP6603"},
	{2,0,0,3,6, 3, 6, 2,11,
 -0.00899, 0.00000, 0.00000, 0.00000, 0.00695, 0.00000, 0.00000, 0.00000, 0.00000, 0.00213,-0.00097,-0.01514 ,
  0.00013, 0.00000, 0.00000, 0.00000, 0.00019, 0.00000, 0.00000, 0.00000, 0.00000, 0.00023, 0.00021, 0.00023 ,
"duuP6603"},
	{2,0,0,3,5, 4, 1, 1, 8,
 -0.00893,-0.00806,-0.00013, 0.00000, 0.00389,-0.00304, 0.00000, 0.00000,-0.00098, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00013, 0.00016, 0.00000, 0.00013, 0.00010, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000 ,
"duuP5104"},
	{2,0,0,3,5, 4, 1, 2, 9,
 -0.02831, 0.01627, 0.00915, 0.00151, 0.00556, 0.00418, 0.00000, 0.00000, 0.00000,-0.00228, 0.00000, 0.00000 ,
  0.00016, 0.00032, 0.00026, 0.00027, 0.00020, 0.00019, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000 ,
"duuP5104"},
	{2,0,0,3,5, 4, 2, 1, 4,
 -0.00601,-0.01347,-0.00059, 0.00000, 0.00189, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00012, 0.00017, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5204"},
	{2,0,0,3,5, 4, 2, 2,11,
 -0.03383, 0.00310, 0.00159,-0.00439, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00368, 0.00000,-0.00166 ,
  0.00012, 0.00023, 0.00016, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012 ,
"duuP5204"},
	{2,0,0,3,5, 4, 3, 1, 9,
 -0.00881,-0.01100,-0.00404,-0.00256, 0.00000, 0.00000,-0.00279, 0.00000, 0.00185,-0.00159, 0.00000, 0.00000 ,
  0.00008, 0.00014, 0.00012, 0.00011, 0.00000, 0.00000, 0.00010, 0.00000, 0.00010, 0.00009, 0.00000, 0.00000 ,
"duuP5304"},
	{2,0,0,3,5, 4, 3, 2, 9,
 -0.03499, 0.00548, 0.00000,-0.00442, 0.00655, 0.00000, 0.00333, 0.00000, 0.00000,-0.00105, 0.00000, 0.00000 ,
  0.00008, 0.00019, 0.00000, 0.00014, 0.00013, 0.00000, 0.00013, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000 ,
"duuP5304"},
	{2,0,0,3,5, 4, 4, 1,11,
 -0.00670,-0.01099, 0.00000, 0.00000, 0.00000, 0.00000,-0.00162, 0.00000, 0.00263, 0.00000, 0.00124,-0.00209 ,
  0.00007, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00000, 0.00011, 0.00000, 0.00011, 0.00009 ,
"duuP5404"},
	{2,0,0,3,5, 4, 4, 2,11,
 -0.03541, 0.00845, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00078, 0.00000, 0.00376 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00011 ,
"duuP5404"},
	{2,0,0,3,6, 5, 1, 1,10,
 -0.02898,-0.00151, 0.00000, 0.00227,-0.00477, 0.00881,-0.00298, 0.00000, 0.00158, 0.00000,-0.00169, 0.00000 ,
  0.00016, 0.00056, 0.00000, 0.00045, 0.00027, 0.00031, 0.00033, 0.00000, 0.00035, 0.00000, 0.00030, 0.00000 ,
"duuP6105"},
	{2,0,0,3,6, 5, 1, 2,10,
 -0.04557, 0.01215, 0.00562, 0.00991, 0.00000, 0.00572, 0.00000, 0.00000, 0.00000, 0.00000,-0.00127, 0.00000 ,
  0.00019, 0.00045, 0.00029, 0.00038, 0.00000, 0.00030, 0.00000, 0.00000, 0.00000, 0.00000, 0.00023, 0.00000 ,
"duuP6105"},
	{2,0,0,3,6, 5, 2, 1,10,
 -0.02992,-0.00730, 0.00000, 0.00668, 0.00000, 0.00522,-0.00231, 0.00000, 0.00000, 0.00000,-0.00213, 0.00000 ,
  0.00016, 0.00042, 0.00000, 0.00037, 0.00000, 0.00029, 0.00023, 0.00000, 0.00000, 0.00000, 0.00022, 0.00000 ,
"duuP6205"},
	{2,0,0,3,6, 5, 3, 1, 9,
 -0.02392,-0.01390, 0.00641, 0.00000, 0.00498, 0.00000, 0.00000, 0.00000, 0.00000,-0.00121, 0.00000, 0.00000 ,
  0.00024, 0.00029, 0.00039, 0.00000, 0.00031, 0.00000, 0.00000, 0.00000, 0.00000, 0.00023, 0.00000, 0.00000 ,
"duuP6305"},
	{2,0,0,3,5, 6, 1, 1,11,
 -0.04294, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.02400,-0.02102,-0.02648 ,
  0.00031, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00055, 0.00044, 0.00053 ,
"duuP5106"},
	{2,0,0,3,5, 6, 1, 2,11,
 -0.02875, 0.02072,-0.00719, 0.00000,-0.00409, 0.00227, 0.00000,-0.00181, 0.00000, 0.00000, 0.00000, 0.00171 ,
  0.00012, 0.00015, 0.00019, 0.00000, 0.00015, 0.00013, 0.00000, 0.00013, 0.00000, 0.00000, 0.00000, 0.00012 ,
"duuP5106"},
	{2,0,0,3,5, 6, 2, 1,10,
 -0.02669,-0.01184, 0.00965, 0.00000, 0.00000, 0.00213, 0.00000,-0.00411,-0.00350, 0.00000,-0.00329, 0.00000 ,
  0.00018, 0.00029, 0.00028, 0.00000, 0.00000, 0.00024, 0.00000, 0.00024, 0.00023, 0.00000, 0.00023, 0.00000 ,
"duuP5206"},
	{2,0,0,3,5, 6, 2, 2, 6,
 -0.02912, 0.01841, 0.00000, 0.00256, 0.00270, 0.00000, 0.00189, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00020, 0.00000, 0.00016, 0.00014, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5206"},
	{2,0,0,3,5, 6, 3, 1,11,
 -0.02978,-0.01377, 0.00000, 0.00000, 0.00000, 0.00000, 0.00200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00555 ,
  0.00015, 0.00027, 0.00000, 0.00000, 0.00000, 0.00000, 0.00022, 0.00000, 0.00000, 0.00000, 0.00000, 0.00022 ,
"duuP5306"},
	{2,0,0,3,5, 6, 3, 2,11,
 -0.02635, 0.01582,-0.00438, 0.00258, 0.00000,-0.00272, 0.00000, 0.00115, 0.00000,-0.00244, 0.00000, 0.00245 ,
  0.00011, 0.00043, 0.00016, 0.00040, 0.00000, 0.00035, 0.00000, 0.00029, 0.00000, 0.00023, 0.00000, 0.00017 ,
"duuP5306"},
	{2,0,0,3,5, 6, 4, 1,10,
 -0.03549,-0.01717,-0.00559,-0.00465, 0.00000, 0.00000, 0.00000, 0.00000, 0.00337, 0.00321,-0.00416, 0.00000 ,
  0.00017, 0.00030, 0.00026, 0.00027, 0.00000, 0.00000, 0.00000, 0.00000, 0.00022, 0.00021, 0.00022, 0.00000 ,
"duuP5406"},
	{2,0,0,3,5, 6, 4, 2, 5,
 -0.02933, 0.02264, 0.00000, 0.01049,-0.00406, 0.00457, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00024, 0.00000, 0.00020, 0.00011, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5406"},
	{2,0,0,3,6, 7, 1, 2,10,
 -0.01026, 0.02251, 0.00000,-0.00690, 0.00000, 0.00000, 0.00000, 0.00000, 0.00202,-0.00146,-0.00313, 0.00000 ,
  0.00010, 0.00025, 0.00000, 0.00020, 0.00000, 0.00000, 0.00000, 0.00000, 0.00016, 0.00014, 0.00016, 0.00000 ,
"duuP6107"},
	{2,0,0,3,6, 7, 2, 1, 9,
 -0.01029,-0.02303, 0.00280, 0.00000, 0.00000, 0.00000,-0.00139, 0.00000, 0.00000,-0.00150, 0.00000, 0.00000 ,
  0.00011, 0.00016, 0.00016, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000 ,
"duuP6207"},
	{2,0,0,3,6, 7, 2, 2, 8,
 -0.00314, 0.02945, 0.00000,-0.00551, 0.00000, 0.00000, 0.00343,-0.00417,-0.00364, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00026, 0.00000, 0.00021, 0.00000, 0.00000, 0.00016, 0.00014, 0.00016, 0.00000, 0.00000, 0.00000 ,
"duuP6207"},
	{2,0,0,3,6, 7, 3, 2, 9,
 -0.00840, 0.03126,-0.00501,-0.00895, 0.00000, 0.00345, 0.00000, 0.00000, 0.00000, 0.00138, 0.00000, 0.00000 ,
  0.00012, 0.00026, 0.00017, 0.00023, 0.00000, 0.00018, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000 ,
"duuP6307"},
	{2,0,0,3,5, 8, 1, 1, 6,
  0.00326, 0.00236,-0.00165, 0.00000, 0.00000, 0.00000, 0.00077, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00015, 0.00015, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5108"},
	{2,0,0,3,5, 8, 1, 2,10,
 -0.00241, 0.00000, 0.00149, 0.00000, 0.00000, 0.00000, 0.00000, 0.00080, 0.00000, 0.00051,-0.00063, 0.00000 ,
  0.00009, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012, 0.00012, 0.00000 ,
"duuP5108"},
	{2,0,0,3,5, 8, 2, 1, 8,
  0.00762, 0.00500, 0.00000, 0.00000,-0.00156, 0.00000,-0.00041,-0.00142, 0.00220, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00017, 0.00000, 0.00000, 0.00016, 0.00000, 0.00016, 0.00014, 0.00015, 0.00000, 0.00000, 0.00000 ,
"duuP5208"},
	{2,0,0,3,5, 8, 2, 2, 7,
 -0.00792,-0.00317, 0.00000, 0.00000, 0.00072, 0.00000, 0.00000, 0.00103, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00022, 0.00000, 0.00000, 0.00018, 0.00000, 0.00000, 0.00018, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5208"},
	{2,0,0,3,5, 8, 3, 1, 8,
  0.00766, 0.00677,-0.00149, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00114, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00020, 0.00020, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000 ,
"duuP5308"},
	{2,0,0,3,5, 8, 3, 2,10,
 -0.00743, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00115,-0.00075, 0.00218, 0.00089, 0.00000 ,
  0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00019, 0.00019, 0.00018, 0.00019, 0.00000 ,
"duuP5308"},
	{2,0,0,3,5, 8, 4, 1,11,
  0.00746, 0.00651,-0.00274, 0.00000,-0.00065, 0.00000, 0.00129, 0.00000, 0.00000,-0.00065, 0.00000, 0.00111 ,
  0.00016, 0.00019, 0.00026, 0.00000, 0.00023, 0.00000, 0.00020, 0.00000, 0.00000, 0.00017, 0.00000, 0.00017 ,
"duuP5408"},
	{2,0,0,3,5, 8, 4, 2, 8,
 -0.00552, 0.00000,-0.00077, 0.00000, 0.00016, 0.00000, 0.00257,-0.00193, 0.00152, 0.00000, 0.00000, 0.00000 ,
  0.00019, 0.00000, 0.00032, 0.00000, 0.00028, 0.00000, 0.00025, 0.00019, 0.00023, 0.00000, 0.00000, 0.00000 ,
"duuP5408"},
	{2,0,0,3,5, 8, 5, 1,11,
  0.00090, 0.00000, 0.00024, 0.00000,-0.00179, 0.00000, 0.00000, 0.00000,-0.00049, 0.00000, 0.00000, 0.00047 ,
  0.00011, 0.00000, 0.00017, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000, 0.00007 ,
"duuP5508"},
	{2,0,0,3,5, 8, 5, 2, 9,
  0.00712,-0.00063,-0.00695, 0.00078,-0.00459, 0.00000,-0.00235, 0.00000,-0.00101, 0.00045, 0.00000, 0.00000 ,
  0.00018, 0.00011, 0.00033, 0.00009, 0.00028, 0.00000, 0.00020, 0.00000, 0.00012, 0.00006, 0.00000, 0.00000 ,
"duuP5508"},
	{2,0,0,3,5, 8, 6, 1, 6,
  0.00061, 0.00160, 0.00000, 0.00034,-0.00136, 0.00000, 0.00027, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00008, 0.00000, 0.00007, 0.00007, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5608"},
	{2,0,0,3,5, 8, 6, 2, 8,
  0.00723, 0.00000,-0.00185, 0.00161,-0.00090, 0.00057,-0.00046, 0.00000,-0.00025, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00000, 0.00006, 0.00006, 0.00007, 0.00006, 0.00006, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000 ,
"duuP5608"},
	{2,0,0,3,5, 8, 7, 1, 6,
  0.00142, 0.00146,-0.00015, 0.00000, 0.00000,-0.00006, 0.00050, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00004, 0.00006, 0.00004, 0.00000, 0.00000, 0.00003, 0.00003, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5708"},
	{2,0,0,3,5, 8, 7, 2,10,
  0.00252,-0.00051, 0.00017, 0.00000,-0.00056, 0.00000, 0.00000, 0.00033,-0.00040, 0.00000, 0.00030, 0.00000 ,
  0.00004, 0.00005, 0.00005, 0.00000, 0.00004, 0.00000, 0.00000, 0.00004, 0.00004, 0.00000, 0.00004, 0.00000 ,
"duuP5708"},
	{2,0,0,3,6, 9, 1, 1, 9,
  0.00158, 0.00099,-0.00319, 0.00000, 0.00087, 0.00000,-0.00105, 0.00000, 0.00000, 0.00053, 0.00000, 0.00000 ,
  0.00008, 0.00009, 0.00013, 0.00000, 0.00011, 0.00000, 0.00009, 0.00000, 0.00000, 0.00007, 0.00000, 0.00000 ,
"duuP6109"},
	{2,0,0,3,6, 9, 1, 2,11,
  0.00631, 0.02849, 0.01988, 0.00000, 0.00000, 0.00000,-0.00603,-0.00726, 0.00000, 0.00000, 0.00000, 0.00652 ,
  0.00085, 0.00125, 0.00122, 0.00000, 0.00000, 0.00000, 0.00157, 0.00152, 0.00000, 0.00000, 0.00000, 0.00120 ,
"duuP6109"},
	{2,0,0,3,6, 9, 2, 1, 5,
  0.01874,-0.02712, 0.00000,-0.00100, 0.00341,-0.00318, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00026, 0.00000, 0.00020, 0.00011, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6209"},
	{2,0,0,3,6, 9, 2, 2,10,
  0.02123, 0.03171, 0.02872, 0.00000, 0.00000,-0.00942, 0.00000,-0.00610, 0.00000, 0.00362, 0.00455, 0.00000 ,
  0.00024, 0.00038, 0.00032, 0.00000, 0.00000, 0.00030, 0.00000, 0.00035, 0.00000, 0.00028, 0.00025, 0.00000 ,
"duuP6209"},
	{2,0,0,3,6, 9, 3, 1,11,
  0.00821,-0.01004,-0.00039, 0.00000, 0.00475,-0.00056, 0.00000, 0.00256, 0.00000, 0.00000, 0.00000,-0.00099 ,
  0.00014, 0.00017, 0.00023, 0.00000, 0.00017, 0.00015, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00012 ,
"duuP6309"},
	{2,0,0,3,6, 9, 3, 2, 9,
  0.01415, 0.02522, 0.01559,-0.00492,-0.00640,-0.00806, 0.00000, 0.00000, 0.00000, 0.00569, 0.00000, 0.00000 ,
  0.00042, 0.00064, 0.00063, 0.00077, 0.00060, 0.00063, 0.00000, 0.00000, 0.00000, 0.00060, 0.00000, 0.00000 ,
"duuP6309"},
	{2,0,0,3,6, 9, 4, 1,11,
  0.00645,-0.00185, 0.00000, 0.00000, 0.00000,-0.00058, 0.00000, 0.00125, 0.00000, 0.00000, 0.00136,-0.00091 ,
  0.00006, 0.00011, 0.00000, 0.00000, 0.00000, 0.00009, 0.00000, 0.00009, 0.00000, 0.00000, 0.00008, 0.00008 ,
"duuP6409"},
	{2,0,0,3,6, 9, 4, 2, 8,
 -0.00606, 0.00000, 0.00230,-0.00056, 0.00000, 0.00144, 0.00000, 0.00000,-0.00178, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00000, 0.00014, 0.00012, 0.00000, 0.00012, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000 ,
"duuP6409"},
	{2,0,0,3,6, 9, 5, 1, 9,
  0.00074, 0.01200,-0.00439, 0.00000, 0.00461,-0.00255, 0.00000, 0.00000, 0.00000, 0.00295, 0.00000, 0.00000 ,
  0.00010, 0.00011, 0.00016, 0.00000, 0.00011, 0.00008, 0.00000, 0.00000, 0.00000, 0.00008, 0.00000, 0.00000 ,
"duuP6509"},
	{2,0,0,3,6, 9, 6, 1,11,
 -0.00140, 0.00742,-0.00230,-0.00317,-0.00026,-0.00193,-0.00141, 0.00000, 0.00000, 0.00000, 0.00061,-0.00075 ,
  0.00010, 0.00017, 0.00018, 0.00015, 0.00015, 0.00011, 0.00010, 0.00000, 0.00000, 0.00000, 0.00007, 0.00007 ,
"duuP6609"},
	{2,0,0,3,6, 9, 6, 2,11,
 -0.01660, 0.00000,-0.00678, 0.00000, 0.00000, 0.00392, 0.00000, 0.00000, 0.00000, 0.00000,-0.00144,-0.00137 ,
  0.00011, 0.00000, 0.00016, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00010 ,
"duuP6609"},
	{2,0,0,3,6, 9, 7, 1,10,
  0.00253, 0.00284, 0.00231, 0.00000, 0.00000, 0.00215,-0.00115, 0.00141, 0.00000, 0.00000, 0.00129, 0.00000 ,
  0.00005, 0.00008, 0.00008, 0.00000, 0.00000, 0.00007, 0.00006, 0.00006, 0.00000, 0.00000, 0.00006, 0.00000 ,
"duuP6709"},
	{2,0,0,3,5,10, 1, 1,11,
 -0.01798,-0.02278,-0.00263, 0.00000, 0.00503, 0.00043, 0.00000, 0.00542, 0.00000, 0.00429, 0.00000, 0.00222 ,
  0.00011, 0.00013, 0.00019, 0.00000, 0.00014, 0.00012, 0.00000, 0.00013, 0.00000, 0.00013, 0.00000, 0.00012 ,
"duuP5110"},
	{2,0,0,3,5,10, 1, 2, 8,
 -0.03360, 0.05225, 0.00591, 0.01320,-0.00156, 0.00625, 0.00419, 0.00000, 0.00180, 0.00000, 0.00000, 0.00000 ,
  0.00019, 0.00021, 0.00034, 0.00018, 0.00030, 0.00014, 0.00024, 0.00000, 0.00016, 0.00000, 0.00000, 0.00000 ,
"duuP5110"},
	{2,0,0,3,5,10, 2, 1,11,
  0.02525,-0.04695, 0.00000, 0.00000, 0.00298, 0.00000,-0.00563, 0.00517,-0.00149, 0.00000, 0.00000, 0.00115 ,
  0.00006, 0.00012, 0.00000, 0.00000, 0.00010, 0.00000, 0.00012, 0.00009, 0.00010, 0.00000, 0.00000, 0.00009 ,
"duuP5210"},
	{2,0,0,3,5,10, 2, 2,10,
 -0.00877, 0.04567, 0.00000, 0.00000, 0.00000, 0.00361, 0.00000,-0.00213, 0.00000, 0.00257,-0.00185, 0.00000 ,
  0.00012, 0.00022, 0.00000, 0.00000, 0.00000, 0.00017, 0.00000, 0.00017, 0.00000, 0.00017, 0.00015, 0.00000 ,
"duuP5210"},
	{2,0,0,3,5,10, 3, 1, 7,
  0.05231,-0.07972, 0.00000,-0.01746, 0.00271,-0.00174,-0.00356, 0.00233, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00034, 0.00000, 0.00030, 0.00012, 0.00023, 0.00012, 0.00016, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5310"},
	{2,0,0,3,5,10, 3, 2, 9,
  0.11223,-0.04091,-0.00741, 0.00971, 0.00000, 0.00000, 0.00585,-0.00527, 0.00650,-0.00382, 0.00000, 0.00000 ,
  0.00060, 0.00086, 0.00082, 0.00078, 0.00000, 0.00000, 0.00123, 0.00051, 0.00078, 0.00093, 0.00000, 0.00000 ,
"duuP5310"},
	{2,0,0,3,5,10, 4, 1, 7,
  0.02099,-0.06392, 0.00000,-0.01923, 0.00515,-0.01178, 0.00000,-0.00464, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00038, 0.00000, 0.00033, 0.00012, 0.00025, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5410"},
	{2,0,0,3,5,10, 4, 2, 1,
  0.02978, 0.02858, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00025, 0.00043, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5410"},
	{2,0,0,3,5,10, 5, 1, 9,
 -0.00989,-0.01679, 0.01953,-0.00712, 0.00968, 0.00424, 0.00000, 0.00673, 0.00128, 0.00153, 0.00000, 0.00000 ,
  0.00014, 0.00037, 0.00023, 0.00034, 0.00017, 0.00031, 0.00000, 0.00026, 0.00013, 0.00018, 0.00000, 0.00000 ,
"duuP5510"},
	{2,0,0,3,5,10, 5, 2, 4,
  0.00134, 0.00620, 0.00000, 0.00144,-0.00101, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00019, 0.00000, 0.00015, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5510"},
	{2,0,0,3,5,10, 6, 1, 7,
 -0.02158, 0.00000, 0.02682,-0.00932, 0.01580, 0.00000, 0.00000, 0.00772, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00012, 0.00000, 0.00020, 0.00012, 0.00016, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5610"},
	{2,0,0,3,5,10, 6, 2,11,
 -0.00129, 0.00827, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00197, 0.00000, 0.00000,-0.00246 ,
  0.00007, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00010 ,
"duuP5610"},
	{2,0,0,3,5,10, 7, 1,11,
  0.00202,-0.01759, 0.00472, 0.00000, 0.00000, 0.00000, 0.00000,-0.00187, 0.00000, 0.00000, 0.00000, 0.00219 ,
  0.00012, 0.00018, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00014 ,
"duuP5710"},
	{2,0,0,3,5,10, 7, 2,11,
 -0.00316, 0.01057, 0.00000, 0.00000,-0.00183, 0.00000, 0.00000,-0.00248, 0.00000, 0.00000,-0.00260,-0.00172 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00011, 0.00011 ,
"duuP5710"},
	{2,0,0,3,6,11, 1, 1,11,
  0.02696, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.03854, 0.00000,-0.06290,-0.05105 ,
  0.00031, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00054, 0.00000, 0.00051, 0.00044 ,
"duuP6111"},
	{2,0,0,3,6,11, 1, 2, 8,
 -0.00067, 0.02103, 0.00000, 0.00553,-0.00247, 0.00400, 0.00000, 0.00120, 0.00079, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00029, 0.00000, 0.00026, 0.00012, 0.00022, 0.00000, 0.00016, 0.00012, 0.00000, 0.00000, 0.00000 ,
"duuP6111"},
	{2,0,0,3,6,11, 2, 1,10,
  0.02650,-0.01470, 0.00000, 0.00000,-0.00408, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00368, 0.00000 ,
  0.00007, 0.00014, 0.00000, 0.00000, 0.00010, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00000 ,
"duuP6211"},
	{2,0,0,3,6,11, 2, 2, 7,
  0.00104, 0.01526, 0.00622, 0.00000,-0.00027, 0.00000, 0.00362,-0.00079, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00014, 0.00014, 0.00024, 0.00000, 0.00020, 0.00000, 0.00014, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6211"},
	{2,0,0,3,6,11, 3, 1,10,
  0.03051,-0.01330,-0.00399,-0.00606,-0.00940, 0.00000,-0.00556, 0.00000,-0.00285, 0.00000,-0.00162, 0.00000 ,
  0.00019, 0.00019, 0.00035, 0.00014, 0.00031, 0.00000, 0.00027, 0.00000, 0.00021, 0.00000, 0.00015, 0.00000 ,
"duuP6311"},
	{2,0,0,3,6,11, 3, 2, 8,
  0.00112, 0.01837, 0.00444, 0.00000, 0.00000, 0.00094, 0.00092, 0.00000,-0.00117, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00013, 0.00014, 0.00000, 0.00000, 0.00010, 0.00011, 0.00000, 0.00011, 0.00000, 0.00000, 0.00000 ,
"duuP6311"},
	{2,0,0,3,5,12, 1, 1,10,
  0.03363,-0.03606, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00348,-0.00252, 0.00000,-0.00167, 0.00000 ,
  0.00009, 0.00016, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00013, 0.00014, 0.00000, 0.00014, 0.00000 ,
"duuP5112"},
	{2,0,0,3,5,12, 1, 2, 9,
  0.01890, 0.01647, 0.01431, 0.00000, 0.00907, 0.00000, 0.00433, 0.00000, 0.00000,-0.00159, 0.00000, 0.00000 ,
  0.00020, 0.00021, 0.00036, 0.00000, 0.00030, 0.00000, 0.00019, 0.00000, 0.00000, 0.00013, 0.00000, 0.00000 ,
"duuP5112"},
	{2,0,0,3,5,12, 2, 1,11,
  0.03784,-0.01994, 0.00576, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00362 ,
  0.00009, 0.00014, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011 ,
"duuP5212"},
	{2,0,0,3,5,12, 2, 2, 9,
  0.01381, 0.01712, 0.00000, 0.00664,-0.00169, 0.00000, 0.00131, 0.00000,-0.00307, 0.00119, 0.00000, 0.00000 ,
  0.00008, 0.00020, 0.00000, 0.00016, 0.00013, 0.00000, 0.00014, 0.00000, 0.00013, 0.00011, 0.00000, 0.00000 ,
"duuP5212"},
	{2,0,0,3,5,12, 3, 1, 5,
  0.03224,-0.02062, 0.00000,-0.00470, 0.00199,-0.00259, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00007, 0.00018, 0.00000, 0.00016, 0.00010, 0.00013, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5312"},
	{2,0,0,3,5,12, 3, 2, 9,
  0.01153, 0.00928, 0.00000, 0.00000, 0.00000, 0.00000, 0.00284,-0.00184, 0.00000, 0.00303, 0.00000, 0.00000 ,
  0.00007, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00010, 0.00012, 0.00000, 0.00012, 0.00000, 0.00000 ,
"duuP5312"},
	{2,0,0,3,5,12, 4, 1, 5,
  0.03090,-0.01649,-0.00137, 0.00000, 0.00230,-0.00121, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00010, 0.00013, 0.00016, 0.00000, 0.00013, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5412"},
	{2,0,0,3,5,12, 4, 2,11,
  0.01328, 0.01624, 0.00000, 0.00585, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00049, 0.00000,-0.00137 ,
  0.00008, 0.00020, 0.00000, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012 ,
"duuP5412"},
	{2,0,0,3,5,12, 5, 1,11,
  0.02972,-0.02268, 0.00000,-0.00522, 0.00000, 0.00000,-0.00075, 0.00000, 0.00345, 0.00000, 0.00281, 0.00234 ,
  0.00008, 0.00017, 0.00000, 0.00014, 0.00000, 0.00000, 0.00012, 0.00000, 0.00013, 0.00000, 0.00012, 0.00011 ,
"duuP5512"},
	{2,0,0,3,5,12, 5, 2,11,
  0.01385, 0.01045, 0.00000, 0.00000, 0.00000,-0.00366, 0.00000, 0.00000, 0.00000, 0.00049, 0.00000,-0.00723 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012 ,
"duuP5512"},
	{2,0,0,3,5,12, 6, 1,11,
  0.03064,-0.01739, 0.00000, 0.00000, 0.00000, 0.00218, 0.00000,-0.00152, 0.00167, 0.00000, 0.00000, 0.00292 ,
  0.00008, 0.00014, 0.00000, 0.00000, 0.00000, 0.00013, 0.00000, 0.00012, 0.00011, 0.00000, 0.00000, 0.00011 ,
"duuP5612"},
	{2,0,0,3,5,12, 6, 2, 6,
  0.01324, 0.01094,-0.00424,-0.00524, 0.00000, 0.00000, 0.00413, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00012, 0.00021, 0.00017, 0.00017, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5612"},
	{2,0,0,3,5,12, 7, 1,11,
  0.02831,-0.00989, 0.00000, 0.00546, 0.00000, 0.01013,-0.00184, 0.00435, 0.00382, 0.00000, 0.00000, 0.00290 ,
  0.00008, 0.00027, 0.00000, 0.00024, 0.00000, 0.00021, 0.00013, 0.00016, 0.00012, 0.00000, 0.00000, 0.00012 ,
"duuP5712"},
	{2,0,0,3,5,12, 7, 2,11,
  0.01033, 0.01394,-0.00579, 0.00000, 0.00000,-0.00349, 0.00000, 0.00000, 0.00000, 0.00000, 0.00456,-0.00371 ,
  0.00011, 0.00016, 0.00016, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00012 ,
"duuP5712"},
	{2,0,0,3,6,13, 4, 1, 9,
  0.03050,-0.02363, 0.00000,-0.00330, 0.00000, 0.00000, 0.00000, 0.00364, 0.00000, 0.00201, 0.00000, 0.00000 ,
  0.00008, 0.00019, 0.00000, 0.00015, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012, 0.00000, 0.00000 ,
"duuP6413"},
	{2,0,0,3,6,13, 4, 2,10,
  0.01060, 0.01580, 0.00250, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00093, 0.00000 ,
  0.00010, 0.00014, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00011, 0.00000 ,
"duuP6413"},
	{2,0,0,3,6,13, 5, 1,10,
  0.03207,-0.02107, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00315, 0.00000, 0.00592, 0.00222, 0.00000 ,
  0.00008, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00012, 0.00012, 0.00000 ,
"duuP6513"},
	{2,0,0,3,6,13, 6, 1, 8,
  0.03206,-0.02387, 0.00000,-0.00498, 0.00198,-0.00376, 0.00097, 0.00000,-0.00211, 0.00000, 0.00000, 0.00000 ,
  0.00011, 0.00028, 0.00000, 0.00025, 0.00017, 0.00020, 0.00019, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000 ,
"duuP6613"},
	{2,0,0,3,6,13, 7, 1, 7,
  0.02929,-0.01732,-0.01052, 0.00000,-0.00816, 0.00000,-0.00521, 0.00206, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00019, 0.00022, 0.00032, 0.00000, 0.00028, 0.00000, 0.00022, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6713"},
	{2,0,0,3,6,13, 7, 2, 8,
  0.01131, 0.01014, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00509, 0.00000, 0.00000, 0.00000 ,
  0.00009, 0.00016, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00012, 0.00000, 0.00000, 0.00000 ,
"duuP6713"},
	{2,0,0,3,5,14, 5, 1,11,
  0.03811,-0.01850, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,-0.00127, 0.00000, 0.00000, 0.00000, 0.00204 ,
  0.00012, 0.00022, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00016, 0.00000, 0.00000, 0.00000, 0.00016 ,
"duuP5514"},
	{2,0,0,3,5,14, 5, 2, 7,
  0.02296,-0.02232, 0.06606, 0.00000, 0.00000,-0.01504, 0.00000, 0.02446, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00298, 0.00338, 0.00411, 0.00000, 0.00000, 0.00528, 0.00000, 0.00470, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5514"},
	{2,0,0,3,5,14, 6, 1,10,
  0.03176,-0.01353, 0.00000,-0.00682, 0.00000,-0.00344, 0.00000, 0.00000, 0.00000,-0.00184, 0.00091, 0.00000 ,
  0.00009, 0.00024, 0.00000, 0.00021, 0.00000, 0.00017, 0.00000, 0.00000, 0.00000, 0.00013, 0.00013, 0.00000 ,
"duuP5614"},
	{2,0,0,3,5,14, 6, 2, 6,
  0.03914, 0.00000, 0.11130, 0.08399, 0.00000, 0.00000,-0.06867, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00102, 0.00000, 0.00134, 0.00155, 0.00000, 0.00000, 0.00166, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5614"},
	{2,0,0,3,5,14, 7, 1,11,
  0.03511,-0.01346, 0.00000,-0.00588, 0.00000, 0.00000,-0.00107, 0.00155, 0.00208, 0.00000, 0.00000,-0.00158 ,
  0.00009, 0.00021, 0.00000, 0.00017, 0.00000, 0.00000, 0.00013, 0.00013, 0.00013, 0.00000, 0.00000, 0.00013 ,
"duuP5714"},
	{2,0,0,3,5,14, 7, 2,11,
  0.03453, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.02340, 0.00000, 0.02567, 0.05819 ,
  0.00034, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00063, 0.00000, 0.00056, 0.00058 ,
"duuP5714"},
	{2,0,0,3,6,15, 4, 1, 7,
  0.01736,-0.02949,-0.00338, 0.00000, 0.00257, 0.00000, 0.00000, 0.00127, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00018, 0.00021, 0.00000, 0.00018, 0.00000, 0.00000, 0.00014, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6415"},
	{2,0,0,3,6,15, 4, 2, 9,
  0.01632, 0.00000, 0.00000,-0.00062, 0.00271, 0.00493, 0.00000, 0.00000, 0.00148,-0.00186, 0.00000, 0.00000 ,
  0.00009, 0.00000, 0.00000, 0.00014, 0.00012, 0.00014, 0.00000, 0.00000, 0.00012, 0.00012, 0.00000, 0.00000 ,
"duuP6415"},
	{2,0,0,3,6,15, 5, 1, 5,
  0.03619,-0.03025,-0.01112, 0.00000,-0.00230,-0.00150, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00013, 0.00018, 0.00022, 0.00000, 0.00018, 0.00015, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6515"},
	{2,0,0,3,6,15, 5, 2,10,
  0.01339, 0.01907, 0.00000, 0.00076, 0.00000, 0.00575,-0.00120, 0.00000, 0.00000,-0.00188,-0.00118, 0.00000 ,
  0.00009, 0.00026, 0.00000, 0.00022, 0.00000, 0.00017, 0.00012, 0.00000, 0.00000, 0.00012, 0.00012, 0.00000 ,
"duuP6515"},
	{2,0,0,3,6,15, 7, 1, 6,
  0.06128,-0.04205,-0.00958,-0.00967, 0.00000,-0.00397,-0.00105, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00015, 0.00030, 0.00021, 0.00027, 0.00000, 0.00022, 0.00017, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6715"},
	{2,0,0,3,6,15, 7, 2, 3,
  0.04511, 0.01678, 0.00224,-0.00652, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00016, 0.00031, 0.00023, 0.00023, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP6715"},
	{2,0,0,3,5,16, 1, 1,11,
 -0.00673, 0.00000, 0.00352, 0.00000, 0.00000,-0.00035, 0.00000, 0.00067, 0.00000, 0.00000, 0.00000, 0.00095 ,
  0.00006, 0.00000, 0.00007, 0.00000, 0.00000, 0.00009, 0.00000, 0.00008, 0.00000, 0.00000, 0.00000, 0.00006 ,
"duuP5116"},
	{2,0,0,3,5,16, 1, 2,10,
  0.00211, 0.00000,-0.00557, 0.00000,-0.00167, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00055, 0.00000 ,
  0.00005, 0.00000, 0.00010, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005, 0.00000 ,
"duuP5116"},
	{2,0,0,3,5,16, 2, 1,11,
 -0.02212, 0.01134,-0.00272, 0.00000, 0.00000,-0.00412, 0.00183, 0.00000, 0.00000, 0.00000, 0.00000, 0.00071 ,
  0.00015, 0.00019, 0.00019, 0.00000, 0.00000, 0.00010, 0.00008, 0.00000, 0.00000, 0.00000, 0.00000, 0.00007 ,
"duuP5216"},
	{2,0,0,3,5,16, 2, 2,11,
  0.00783, 0.00000,-0.00874, 0.00000,-0.00299, 0.00000, 0.00206, 0.00000, 0.00000, 0.00000, 0.00000, 0.00106 ,
  0.00010, 0.00000, 0.00017, 0.00000, 0.00013, 0.00000, 0.00009, 0.00000, 0.00000, 0.00000, 0.00000, 0.00005 ,
"duuP5216"},
	{2,0,0,3,5,16, 3, 1,10,
 -0.01463, 0.00446, 0.00912, 0.00000, 0.00592, 0.00000, 0.00362, 0.00067, 0.00106, 0.00000, 0.00129, 0.00000 ,
  0.00033, 0.00009, 0.00061, 0.00000, 0.00051, 0.00000, 0.00039, 0.00006, 0.00026, 0.00000, 0.00013, 0.00000 ,
"duuP5316"},
	{2,0,0,3,5,16, 3, 2,11,
  0.00809, 0.00000,-0.00775, 0.00149,-0.00257, 0.00000, 0.00000,-0.00184, 0.00000, 0.00000, 0.00000, 0.00086 ,
  0.00011, 0.00000, 0.00019, 0.00006, 0.00012, 0.00000, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00006 ,
"duuP5316"},
	{2,0,0,3,5,16, 4, 1, 4,
 -0.01058, 0.00000, 0.00251, 0.00000,-0.00135, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00006, 0.00000, 0.00009, 0.00000, 0.00007, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5416"},
	{2,0,0,3,5,16, 4, 2,11,
  0.00641, 0.00000,-0.00214, 0.00082, 0.00000, 0.00000,-0.00037, 0.00000, 0.00153, 0.00091, 0.00000, 0.00070 ,
  0.00007, 0.00000, 0.00010, 0.00006, 0.00000, 0.00000, 0.00008, 0.00000, 0.00008, 0.00006, 0.00000, 0.00006 ,
"duuP5416"},
	{2,0,0,3,5,16, 6, 1, 9,
 -0.01888, 0.00000,-0.00991, 0.00000,-0.01624, 0.00000,-0.01016,-0.00176,-0.00225,-0.00125, 0.00000, 0.00000 ,
  0.00031, 0.00000, 0.00060, 0.00000, 0.00055, 0.00000, 0.00039, 0.00013, 0.00020, 0.00014, 0.00000, 0.00000 ,
"duuP5616"},
	{2,0,0,3,5,16, 6, 2, 9,
  0.00898, 0.00900,-0.00879, 0.00451, 0.00000, 0.00000, 0.00000, 0.00078, 0.00000,-0.00179, 0.00000, 0.00000 ,
  0.00013, 0.00032, 0.00019, 0.00022, 0.00000, 0.00000, 0.00000, 0.00015, 0.00000, 0.00015, 0.00000, 0.00000 ,
"duuP5616"},
	{2,0,0,3,5,16, 7, 1, 8,
 -0.00715, 0.00000, 0.00270, 0.00000,-0.00072, 0.00000, 0.00000, 0.00000, 0.00100, 0.00000, 0.00000, 0.00000 ,
  0.00003, 0.00000, 0.00005, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000, 0.00004, 0.00000, 0.00000, 0.00000 ,
"duuP5716"},
	{2,0,0,3,5,16, 7, 2, 7,
  0.00403, 0.00682, 0.00000, 0.00000, 0.00361, 0.00137, 0.00000, 0.00093, 0.00000, 0.00000, 0.00000, 0.00000 ,
  0.00008, 0.00010, 0.00000, 0.00000, 0.00009, 0.00009, 0.00000, 0.00006, 0.00000, 0.00000, 0.00000, 0.00000 ,
"duuP5716"}
  };
svtCorrection_st *Data = tableSet->GetTable();
 Int_t N = tableSet->GetNRows();
 Int_t N0  = sizeof(Data0)/sizeof(data_t);
#if 0
 cout << "N " << N << "\tN0 " << N0 << "\tsizeof(Data0) =" << sizeof(Data0) 
      << "\tsizeof(data_t) =" << sizeof(data_t) << endl;
#endif
 for (Int_t i = 0; i < N; i++) {
   Double_t *param = &Data[i].param[0]; 
   Double_t *dparam = &Data[i].dparam[0];
#if 0
    cout << "=======================================================================" << endl;
    cout << "t" << Data[i].type << "\tI" << Data[i].idx << "\tN" << Data[i].nrows << "\tB" << Data[i].barrel << "\tL" << Data[i].layer 
	 << "\tl" << Data[i].ladder << "\tw"  << Data[i].wafer << "\th" << Data[i].hybrid << "\tp" << Data[i].Npar <<endl;
    for (Int_t j = 0; j < 12; j++) cout << j << "\t" << param[j] << " +- " << dparam[j] << endl;
    cout << Data[i].Comment << endl;
#endif
    for (Int_t i0 = 0; i0 < N0; i0++) {
      if (Data[i].barrel == Data0[i0].barrel &&
	  Data[i].ladder == Data0[i0].ladder &&
	  Data[i].wafer  == Data0[i0].wafer  &&
	  Data[i].hybrid == Data0[i0].hybrid) {
	Double_t *param0  = &Data0[i0].p0; 
	Double_t *dparam0 = &Data0[i0].dp0; 
#if 0
	cout << "Found match i/i0 " << i << "/" << i0 << "\tB" << Data0[i0].barrel << "\tL" << Data0[i0].layer  
	     << "\tl" << Data0[i0].ladder << "\tw"  << Data0[i0].wafer << "\th" << Data0[i0].hybrid << endl;
	cout << "t" << Data0[i0].type << "\tI" << Data0[i0].idx << "\tN" << Data0[i0].nrows << "\tB" 
	     << Data0[i0].barrel << "\tL" << Data0[i0].layer 
	     << "\tl" << Data0[i0].ladder << "\tw"  << Data0[i0].wafer << "\th" << Data0[i0].hybrid << "\tp" << Data0[i0].Npar <<endl;
	for (Int_t j = 0; j < 12; j++) cout << j << "\t" << param0[j] << " +- " << dparam0[j] << endl;
	cout << Data0[i0].Comment << endl;
#endif
	Int_t Npar0 =  Data0[i0].Npar;
	for (Int_t j = 0; j < Npar0; j++) {
	  param[j] += param0[j];
	  dparam[j] = TMath::Sqrt(dparam[j]*dparam[j] + dparam0[j]*dparam0[j]);
	}
	if (Data[i].Npar < Npar0) Data[i].Npar = Npar0;
	break;
     }
    }
#if 0
    cout << "t" << Data[i].type << "\tI" << Data[i].idx << "\tN" << Data[i].nrows << "\tB" << Data[i].barrel << "\tL" << Data[i].layer 
	 << "\tl" << Data[i].ladder << "\tw"  << Data[i].wafer << "\th" << Data[i].hybrid << "\tp" << Data[i].Npar <<endl;
    for (Int_t j = 0; j < 12; j++) cout << j << "\t" << param[j] << " +- " << dparam[j] << endl;
    cout << Data[i].Comment << endl;
#endif
  }

  return (TDataSet *)tableSet;
}

