/*
Strip positions in third SMD plane for the  REGULAR sectors (cm):
------------------------------------
X axis is perpendicular to strip, Y axis is parallel. (0,0) is in the center 
ofthe  Endcap.
Strips for 2nd plane and 1st planes of SMD are shifted along
 radius toward to center on:   
  2 -  9.25 mm     
  1 - 18.50 mm     
*/ 
#include "StEEmcUtil/EEmcGeom/EEmcGeomDefs.h"
struct EEmcStripGeomItem {
	int   id; 
        float x0; 
        float y1; 
        float y2; 
        float length;
};
EEmcStripGeomItem EEmcStripGeomData[kEEmcNumStrips] = {
{  1,    41.3655,    65.4309,    67.7721,     2.3412},
{  2,    41.8705,    65.1089,    68.6468,     3.5379},
{  3,    42.3755,    64.7814,    69.5215,     4.7402},
{  4,    42.8805,    64.4482,    70.3962,     5.9480},
{  5,    43.3855,    64.1093,    71.2709,     7.1616},
{  6,    43.8905,    63.7647,    72.1456,     8.3809},
{  7,    44.3955,    63.4141,    73.0203,     9.6062},
{  8,    44.9005,    63.0575,    73.8950,    10.8374},
{  9,    45.4055,    62.6949,    74.7696,    12.0747},
{ 10,    45.9105,    62.3260,    75.6443,    13.3183},
{ 11,    46.4155,    61.9509,    76.5190,    14.5681},
{ 12,    46.9205,    61.5693,    77.3937,    15.8244},
{ 13,    47.4255,    61.1811,    78.2684,    17.0872},
{ 14,    47.9305,    60.7863,    79.1431,    18.3567},
{ 15,    48.4355,    60.3847,    80.0177,    19.6331},
{ 16,    48.9405,    59.9761,    80.8924,    20.9163},
{ 17,    49.4455,    59.5605,    81.7671,    22.2066},
{ 18,    49.9505,    59.1376,    82.6418,    23.5042},
{ 19,    50.4555,    58.7073,    83.5165,    24.8092},
{ 20,    50.9605,    58.2695,    84.3912,    26.1217},
{ 21,    51.4655,    57.8240,    85.2659,    27.4419},
{ 22,    51.9705,    57.3705,    86.1405,    28.7700},
{ 23,    52.4755,    56.9090,    87.0152,    30.1063},
{ 24,    52.9805,    56.4391,    87.8899,    31.4508},
{ 25,    53.4855,    55.9608,    88.7646,    32.8038},
{ 26,    53.9905,    55.4737,    89.6393,    34.1656},
{ 27,    54.4955,    54.9777,    90.5140,    35.5363},
{ 28,    55.0005,    54.4725,    91.3887,    36.9162},
{ 29,    55.5055,    53.9578,    92.2633,    38.3055},
{ 30,    56.0105,    53.4334,    93.1380,    39.7046},
{ 31,    56.5155,    52.8990,    94.0127,    41.1137},
{ 32,    57.0205,    52.3543,    94.8874,    42.5331},
{ 33,    57.5255,    51.7989,    95.7621,    43.9632},
{ 34,    58.0305,    51.2325,    96.6368,    45.4043},
{ 35,    58.5355,    50.6548,    97.5115,    46.8567},
{ 36,    59.0405,    50.0652,    98.3861,    48.3209},
{ 37,    59.5455,    49.4635,    99.2608,    49.7973},
{ 38,    60.0505,    48.8492,   100.1355,    51.2863},
{ 39,    60.5555,    48.2218,   101.0102,    52.7884},
{ 40,    61.0605,    47.5807,   101.8849,    54.3042},
{ 41,    61.5655,    46.9254,   102.7596,    55.8341},
{ 42,    62.0705,    46.2554,   103.6343,    57.3789},
{ 43,    62.5755,    45.5699,   104.5089,    58.9391},
{ 44,    63.0805,    44.8682,   105.3836,    60.5154},
{ 45,    63.5855,    44.1497,   106.2583,    62.1087},
{ 46,    64.0905,    43.4133,   107.1330,    63.7197},
{ 47,    64.5955,    42.6583,   108.0077,    65.3494},
{ 48,    65.1005,    41.8836,   108.8824,    66.9988},
{ 49,    65.6055,    41.0880,   109.7571,    68.6690},
{ 50,    66.1105,    40.2705,   110.6317,    70.3613},
{ 51,    66.6155,    39.4295,   111.5064,    72.0770},
{ 52,    67.1205,    38.5635,   112.3811,    73.8176},
{ 53,    67.6255,    37.6709,   113.2558,    75.5849},
{ 54,    68.1305,    36.7497,   114.1305,    77.3807},
{ 55,    68.6355,    35.7977,   115.0052,    79.2075},
{ 56,    69.1405,    35.3711,   115.8799,    80.5088},
{ 57,    69.6455,    35.6626,   116.7545,    81.0919},
{ 58,    70.1505,    35.9542,   117.6292,    81.6750},
{ 59,    70.6555,    36.2458,   118.5039,    82.2582},
{ 60,    71.1605,    36.5373,   119.3786,    82.8413},
{ 61,    71.6655,    36.8289,   120.2533,    83.4244},
{ 62,    72.1705,    37.1204,   121.1280,    84.0075},
{ 63,    72.6755,    37.4120,   122.0026,    84.5906},
{ 64,    73.1805,    37.7036,   122.8773,    85.1738},
{ 65,    73.6855,    37.9951,   123.7520,    85.7569},
{ 66,    74.1905,    38.2867,   124.6267,    86.3400},
{ 67,    74.6955,    38.5783,   125.5014,    86.9231},
{ 68,    75.2005,    38.8698,   126.3761,    87.5063},
{ 69,    75.7055,    39.1614,   127.2508,    88.0894},
{ 70,    76.2105,    39.4529,   128.1255,    88.6725},
{ 71,    76.7155,    39.7445,   129.0001,    89.2556},
{ 72,    77.2205,    40.0361,   129.8748,    89.8388},
{ 73,    77.7255,    40.3276,   130.7495,    90.4219},
{ 74,    78.2305,    40.6192,   131.6242,    91.0050},
{ 75,    78.7355,    40.9108,   132.4989,    91.5881},
{ 76,    79.2405,    41.2023,   133.3736,    92.1712},
{ 77,    79.7455,    41.4939,   134.2482,    92.7544},
{ 78,    80.2505,    41.7854,   135.1229,    93.3375},
{ 79,    80.7555,    42.0770,   135.9976,    93.9206},
{ 80,    81.2605,    42.3686,   136.8723,    94.5037},
{ 81,    81.7655,    42.6601,   137.7470,    95.0869},
{ 82,    82.2705,    42.9517,   138.6217,    95.6700},
{ 83,    82.7755,    43.2432,   139.4964,    96.2531},
{ 84,    83.2805,    43.5348,   140.3711,    96.8363},
{ 85,    83.7855,    43.8264,   141.2457,    97.4194},
{ 86,    84.2905,    44.1179,   142.1204,    98.0025},
{ 87,    84.7955,    44.4095,   142.9951,    98.5856},
{ 88,    85.3005,    44.7011,   143.8698,    99.1687},
{ 89,    85.8055,    44.9926,   144.7445,    99.7519},
{ 90,    86.3105,    45.2842,   145.6192,   100.3350},
{ 91,    86.8155,    45.5757,   146.4939,   100.9181},
{ 92,    87.3205,    45.8673,   147.3685,   101.5012},
{ 93,    87.8255,    46.1589,   148.2432,   102.0844},
{ 94,    88.3305,    46.4504,   149.1179,   102.6675},
{ 95,    88.8355,    46.7420,   149.9926,   103.2506},
{ 96,    89.3405,    47.0336,   150.8673,   103.8337},
{ 97,    89.8455,    47.3251,   151.7420,   104.4169},
{ 98,    90.3505,    47.6167,   152.6167,   105.0000},
{ 99,    90.8555,    47.9082,   153.4913,   105.5831},
{100,    91.3605,    48.1998,   154.3660,   106.1662},
{101,    91.8655,    48.4914,   155.2407,   106.7494},
{102,    92.3705,    48.7829,   156.1154,   107.3325},
{103,    92.8755,    49.0745,   156.9901,   107.9156},
{104,    93.3805,    49.3660,   157.8648,   108.4987},
{105,    93.8855,    49.6576,   158.7394,   109.0818},
{106,    94.3905,    49.9492,   159.6141,   109.6650},
{107,    94.8955,    50.2407,   160.4888,   110.2481},
{108,    95.4005,    50.5323,   161.3635,   110.8312},
{109,    95.9055,    50.8239,   162.2382,   111.4143},
{110,    96.4105,    51.1154,   163.1129,   111.9975},
{111,    96.9155,    51.4070,   163.9876,   112.5806},
{112,    97.4205,    51.6985,   164.8623,   113.1637},
{113,    97.9255,    51.9901,   165.7369,   113.7468},
{114,    98.4305,    52.2817,   166.6116,   114.3300},
{115,    98.9355,    52.5732,   167.4863,   114.9131},
{116,    99.4405,    52.8648,   168.3610,   115.4962},
{117,    99.9455,    53.1564,   169.2357,   116.0793},
{118,   100.4505,    53.4479,   170.1104,   116.6624},
{119,   100.9555,    53.7395,   170.9850,   117.2456},
{120,   101.4605,    54.0310,   171.8597,   117.8287},
{121,   101.9655,    54.3226,   172.7344,   118.4118},
{122,   102.4705,    54.6142,   173.6091,   118.9949},
{123,   102.9755,    54.9057,   174.4838,   119.5781},
{124,   103.4805,    55.1973,   175.3585,   120.1612},
{125,   103.9855,    55.4888,   176.2332,   120.7443},
{126,   104.4905,    55.7804,   177.1078,   121.3274},
{127,   104.9955,    56.0720,   177.9825,   121.9106},
{128,   105.5005,    56.3635,   178.8572,   122.4937},
{129,   106.0055,    56.6551,   179.7319,   123.0768},
{130,   106.5105,    56.9467,   180.6066,   123.6599},
{131,   107.0155,    57.2382,   181.4813,   124.2431},
{132,   107.5205,    57.5298,   182.3560,   124.8262},
{133,   108.0255,    57.8213,   183.2307,   125.4093},
{134,   108.5305,    58.1129,   184.3468,   126.2339},
{135,   109.0355,    58.4045,   184.0486,   125.6441},
{136,   109.5405,    58.6960,   183.7485,   125.0524},
{137,   110.0455,    58.9876,   183.4465,   124.4589},
{138,   110.5505,    59.2791,   183.1426,   123.8634},
{139,   111.0555,    59.5707,   182.8368,   123.2661},
{140,   111.5605,    59.8623,   182.5291,   122.6668},
{141,   112.0655,    60.1538,   182.2195,   122.0657},
{142,   112.5705,    60.4454,   181.9079,   121.4625},
{143,   113.0755,    60.7370,   181.5945,   120.8575},
{144,   113.5805,    61.0285,   181.2790,   120.2505},
{145,   114.0855,    61.3201,   180.9616,   119.6416},
{146,   114.5905,    61.6116,   180.6423,   119.0306},
{147,   115.0955,    61.9032,   180.3210,   118.4177},
{148,   115.6005,    62.1948,   179.9976,   117.8029},
{149,   116.1055,    62.4863,   179.6723,   117.1860},
{150,   116.6105,    62.7779,   179.3450,   116.5671},
{151,   117.1155,    63.0695,   179.0156,   115.9461},
{152,   117.6205,    63.3610,   178.6842,   115.3232},
{153,   118.1255,    63.6526,   178.3507,   114.6982},
{154,   118.6305,    63.9441,   178.0152,   114.0711},
{155,   119.1355,    64.2357,   177.6777,   113.4420},
{156,   119.6405,    64.5273,   177.3380,   112.8107},
{157,   120.1455,    64.8188,   176.9963,   112.1774},
{158,   120.6505,    65.1104,   176.6524,   111.5420},
{159,   121.1555,    65.4020,   176.3065,   110.9045},
{160,   121.6605,    65.6935,   175.9583,   110.2648},
{161,   122.1655,    65.9851,   175.6081,   109.6230},
{162,   122.6705,    66.2766,   175.2557,   108.9791},
{163,   123.1755,    66.5682,   174.9012,   108.3330},
{164,   123.6805,    66.8598,   174.5444,   107.6847},
{165,   124.1855,    67.1513,   174.1855,   107.0342},
{166,   124.6905,    67.4429,   173.8243,   106.3815},
{167,   125.1955,    67.7344,   173.4610,   105.7265},
{168,   125.7005,    68.0260,   173.0954,   105.0694},
{169,   126.2055,    68.3176,   172.7275,   104.4099},
{170,   126.7105,    68.6091,   172.3574,   103.7483},
{171,   127.2155,    68.9007,   171.9850,   103.0843},
{172,   127.7205,    69.1923,   171.6103,   102.4180},
{173,   128.2255,    69.4838,   171.2333,   101.7495},
{174,   128.7305,    69.7754,   170.8540,   101.0786},
{175,   129.2355,    70.0669,   170.4723,   100.4053},
{176,   129.7405,    70.3585,   170.0883,    99.7298},
{177,   130.2455,    70.6501,   169.7019,    99.0518},
{178,   130.7505,    70.9416,   169.3131,    98.3715},
{179,   131.2555,    71.2332,   168.9219,    97.6887},
{180,   131.7605,    71.6419,   168.5283,    96.8864},
{181,   132.2655,    72.5166,   168.1323,    95.6157},
{182,   132.7705,    73.3913,   167.7337,    94.3425},
{183,   133.2755,    74.2659,   167.3328,    93.0669},
{184,   133.7805,    75.1406,   166.9293,    91.7887},
{185,   134.2855,    76.0153,   166.5233,    90.5080},
{186,   134.7905,    76.8900,   166.1149,    89.2249},
{187,   135.2955,    77.7647,   165.7038,    87.9391},
{188,   135.8005,    78.6394,   165.2902,    86.6508},
{189,   136.3055,    79.5140,   164.8740,    85.3599},
{190,   136.8105,    80.3887,   164.4552,    84.0664},
{191,   137.3155,    81.2634,   164.0338,    82.7703},
{192,   137.8205,    82.1381,   163.6097,    81.4716},
{193,   138.3255,    82.7200,   163.1830,    80.4630},
{194,   138.8305,    83.3347,   162.7535,    79.4188},
{195,   139.3355,    83.7504,   162.3214,    78.5711},
{196,   139.8405,    84.0118,   161.8866,    77.8748},
{197,   140.3455,    84.1096,   161.4489,    77.3394},
{198,   140.8505,    83.9558,   161.0086,    77.0528},
{199,   141.3555,    77.0644,   160.5654,    83.5009},
{200,   141.8605,    77.3560,   160.1194,    82.7634},
{201,   142.3655,    77.6475,   159.6706,    82.0230},
{202,   142.8705,    77.9391,   159.2188,    81.2797},
{203,   143.3755,    78.2307,   158.7643,    80.5336},
{204,   143.8805,    78.5222,   158.3067,    79.7845},
{205,   144.3855,    78.8138,   157.8463,    79.0325},
{206,   144.8905,    79.1054,   157.3829,    78.2775},
{207,   145.3955,    79.3969,   156.9164,    77.5195},
{208,   145.9005,    79.6885,   156.4470,    76.7585},
{209,   146.4055,    79.9800,   155.9745,    75.9945},
{210,   146.9105,    80.2716,   155.4989,    75.2273},
{211,   147.4155,    80.5632,   155.0203,    74.4571},
{212,   147.9205,    80.8547,   154.5385,    73.6838},
{213,   148.4255,    81.1463,   154.0535,    72.9072},
{214,   148.9305,    81.4379,   153.5654,    72.1275},
{215,   149.4355,    81.7294,   153.0740,    71.3446},
{216,   149.9405,    82.0210,   152.5794,    70.5584},
{217,   150.4455,    82.3125,   152.0815,    69.7689},
{218,   150.9505,    82.6041,   151.5802,    68.9761},
{219,   151.4555,    82.8957,   151.0757,    68.1800},
{220,   151.9605,    83.1872,   150.5677,    67.3805},
{221,   152.4655,    83.4788,   150.0563,    66.5775},
{222,   152.9705,    83.7703,   149.5415,    65.7711},
{223,   153.4755,    84.0619,   149.0231,    64.9612},
{224,   153.9805,    84.3535,   148.5013,    64.1478},
{225,   154.4855,    84.6450,   147.9758,    63.3308},
{226,   154.9905,    84.9366,   147.4468,    62.5102},
{227,   155.4955,    85.2282,   146.9141,    61.6860},
{228,   156.0005,    85.5197,   146.3778,    60.8581},
{229,   156.5055,    85.8113,   145.8377,    60.0265},
{230,   157.0105,    86.1028,   145.2939,    59.1911},
{231,   157.5155,    86.3944,   144.7463,    58.3519},
{232,   158.0205,    86.6860,   144.1948,    57.5088},
{233,   158.5255,    86.9775,   143.6394,    56.6619},
{234,   159.0305,    87.2691,   143.0801,    55.8110},
{235,   159.5355,    87.5607,   142.5168,    54.9562},
{236,   160.0405,    87.8522,   141.9495,    54.0973},
{237,   160.5455,    88.1438,   141.3781,    53.2343},
{238,   161.0505,    88.4353,   140.8025,    52.3672},
{239,   161.5555,    88.7269,   140.2228,    51.4959},
{240,   162.0605,    89.1230,   139.6389,    50.5158},
{241,   162.5655,    89.9977,   139.0506,    49.0529},
{242,   163.0705,    90.8724,   138.4581,    47.5857},
{243,   163.5755,    91.7471,   137.8611,    46.1140},
{244,   164.0805,    92.6218,   137.2596,    44.6379},
{245,   164.5855,    93.4964,   136.6537,    43.1573},
{246,   165.0905,    94.3711,   136.0432,    41.6721},
{247,   165.5955,    95.2458,   135.4280,    40.1822},
{248,   166.1005,    96.1205,   134.8082,    38.6877},
{249,   166.6055,    96.9952,   134.1836,    37.1884},
{250,   167.1105,    97.8699,   133.5541,    35.6842},
{251,   167.6155,    98.7446,   132.9198,    34.1752},
{252,   168.1205,    99.6192,   132.2804,    32.6612},
{253,   168.6255,   100.2036,   131.6361,    31.4325},
{254,   169.1305,   100.8238,   130.9866,    30.1628},
{255,   169.6355,   101.2431,   130.3319,    29.0889},
{256,   170.1405,   101.5078,   129.6720,    28.1643},
{257,   170.6455,   101.6095,   129.0067,    27.3972},
{258,   171.1505,   101.4636,   128.3360,    26.8723},
{259,   171.6555,    94.5581,   127.6597,    33.1016},
{260,   172.1605,    94.8497,   126.9779,    32.1282},
{261,   172.6655,    95.1413,   126.2903,    31.1491},
{262,   173.1705,    95.4328,   125.5970,    30.1641},
{263,   173.6755,    95.7244,   124.8977,    29.1733},
{264,   174.1805,    96.0159,   124.1925,    28.1765},
{265,   174.6855,    96.3075,   123.4812,    27.1736},
{266,   175.1905,    96.5991,   122.7636,    26.1645},
{267,   175.6955,    96.8906,   122.0398,    25.1492},
{268,   176.2005,    97.1822,   121.3095,    24.1273},
{269,   176.7055,    97.4738,   120.5727,    23.0990},
{270,   177.2105,    97.7653,   119.8293,    22.0640},
{271,   177.7155,    98.0569,   119.0790,    21.0222},
{272,   178.2205,    98.3484,   118.3219,    19.9734},
{273,   178.7255,    98.6400,   117.5577,    18.9177},
{274,   179.2305,    98.9316,   116.7863,    17.8548},
{275,   179.7355,    99.2231,   116.0076,    16.7845},
{276,   180.2405,    99.5147,   115.2215,    15.7068},
{277,   180.7455,    99.8062,   114.4276,    14.6214},
{278,   181.2505,   100.0978,   113.6260,    13.5282},
{279,   181.7555,   100.3894,   112.8165,    12.4271},
{280,   182.2605,   100.6809,   111.9988,    11.3179},
{281,   182.7655,   100.9725,   111.1728,    10.2003},
{282,   183.2705,   101.2641,   110.3383,     9.0742},
{283,   183.7755,   101.5556,   109.4951,     7.9395},
{284,   184.2805,   101.8472,   108.6431,     6.7959},
{285,   184.7855,   102.1388,   107.7819,     5.6431},
{286,   185.2905,   102.4303,   106.9114,     4.4811},
{287,   185.7955,   102.7219,   106.0314,     3.3095},
{288,   186.3005,   103.0134,   105.1415,     2.1281}};

//Strip positions in third SMD plane for the  REGULAR sectors (cm):
EEmcStripGeomItem EEmcEdgeStripGeomData[kEEmcNumEdgeStrips] = {
{  1,    41.3655,    65.4309,    67.7721,     2.3412},
{  2,    41.8705,    65.1089,    68.6468,     3.5379},
{  3,    42.3755,    64.7814,    69.5215,     4.7402},
{  4,    42.8805,    64.4482,    70.3962,     5.9480},
{  5,    43.3855,    64.1093,    71.2709,     7.1616},
{  6,    43.8905,    63.7647,    72.1456,     8.3809},
{  7,    44.3955,    63.4141,    73.0203,     9.6062},
{  8,    44.9005,    63.0575,    73.8950,    10.8374},
{  9,    45.4055,    62.6949,    74.7696,    12.0747},
{ 10,    45.9105,    62.3260,    75.6443,    13.3183},
{ 11,    46.4155,    61.9509,    76.5190,    14.5681},
{ 12,    46.9205,    61.5693,    77.3937,    15.8244},
{ 13,    47.4255,    61.1811,    78.2684,    17.0872},
{ 14,    47.9305,    60.7863,    79.1431,    18.3567},
{ 15,    48.4355,    60.3847,    80.0177,    19.6331},
{ 16,    48.9405,    59.9761,    80.8924,    20.9163},
{ 17,    49.4455,    59.5605,    81.7671,    22.2066},
{ 18,    49.9505,    59.1376,    82.6418,    23.5042},
{ 19,    50.4555,    58.7073,    83.5165,    24.8092},
{ 20,    50.9605,    58.2695,    84.3912,    26.1217},
{ 21,    51.4655,    57.8240,    85.2659,    27.4419},
{ 22,    51.9705,    57.3705,    86.1405,    28.7700},
{ 23,    52.4755,    56.9090,    87.0152,    30.1063},
{ 24,    52.9805,    56.4391,    87.8899,    31.4508},
{ 25,    53.4855,    55.9608,    88.7646,    32.8038},
{ 26,    53.9905,    55.4737,    89.6393,    34.1656},
{ 27,    54.4955,    54.9777,    90.5140,    35.5363},
{ 28,    55.0005,    54.4725,    91.3887,    36.9162},
{ 29,    55.5055,    53.9578,    92.2633,    38.3055},
{ 30,    56.0105,    53.4334,    93.1380,    39.7046},
{ 31,    56.5155,    52.8990,    94.0127,    41.1137},
{ 32,    57.0205,    52.3543,    94.8874,    42.5331},
{ 33,    57.5255,    51.7989,    95.7621,    43.9632},
{ 34,    58.0305,    51.2325,    96.6368,    45.4043},
{ 35,    58.5355,    50.6548,    97.5115,    46.8567},
{ 36,    59.0405,    50.0652,    98.3861,    48.3209},
{ 37,    59.5455,    49.4635,    99.2608,    49.7973},
{ 38,    60.0505,    48.8492,   100.1355,    51.2863},
{ 39,    60.5555,    48.2218,   101.0102,    52.7884},
{ 40,    61.0605,    47.5807,   101.8849,    54.3042},
{ 41,    61.5655,    46.9254,   102.7596,    55.8341},
{ 42,    62.0705,    46.2554,   103.6343,    57.3789},
{ 43,    62.5755,    45.5699,   104.5089,    58.9391},
{ 44,    63.0805,    44.8682,   105.3836,    60.5154},
{ 45,    63.5855,    44.1497,   106.2583,    62.1087},
{ 46,    64.0905,    43.4133,   107.1330,    63.7197},
{ 47,    64.5955,    42.6583,   108.0077,    65.3494},
{ 48,    65.1005,    41.8836,   108.8824,    66.9988},
{ 49,    65.6055,    41.0880,   109.7571,    68.6690},
{ 50,    66.1105,    41.2730,   110.6317,    69.3588},
{ 51,    66.6155,    41.5969,   111.5064,    69.9096},
{ 52,    67.1205,    41.8957,   112.3811,    70.4854},
{ 53,    67.6255,    42.1680,   113.2558,    71.0878},
{ 54,    68.1305,    42.4116,   114.1305,    71.7188},
{ 55,    68.6355,    42.6245,   115.0052,    72.3807},
{ 56,    69.1405,    42.6279,   115.8799,    73.2520},
{ 57,    69.6455,    42.9194,   116.7545,    73.8351},
{ 58,    70.1505,    43.2110,   117.6292,    74.4182},
{ 59,    70.6555,    43.5026,   118.5039,    75.0014},
{ 60,    71.1605,    43.7941,   119.3786,    75.5845},
{ 61,    71.6655,    44.0857,   120.2533,    76.1676},
{ 62,    72.1705,    44.3772,   121.1280,    76.7507},
{ 63,    72.6755,    44.6688,   122.0026,    77.3338},
{ 64,    73.1805,    44.9604,   122.8773,    77.9170},
{ 65,    73.6855,    45.2519,   123.7520,    78.5001},
{ 66,    74.1905,    45.5435,   124.6267,    79.0832},
{ 67,    74.6955,    45.8351,   125.5014,    79.6663},
{ 68,    75.2005,    46.1266,   126.3761,    80.2495},
{ 69,    75.7055,    46.4182,   127.2508,    80.8326},
{ 70,    76.2105,    46.7097,   128.1255,    81.4157},
{ 71,    76.7155,    47.0013,   129.0001,    81.9988},
{ 72,    77.2205,    47.2929,   129.8748,    82.5820},
{ 73,    77.7255,    47.5844,   130.7495,    83.1651},
{ 74,    78.2305,    47.8760,   131.6242,    83.7482},
{ 75,    78.7355,    48.1676,   132.4989,    84.3313},
{ 76,    79.2405,    48.4591,   133.3736,    84.9144},
{ 77,    79.7455,    48.7507,   134.2482,    85.4976},
{ 78,    80.2505,    49.0422,   135.1229,    86.0807},
{ 79,    80.7555,    49.3338,   135.9976,    86.6638},
{ 80,    81.2605,    49.6254,   136.8723,    87.2469},
{ 81,    81.7655,    49.9169,   137.7470,    87.8301},
{ 82,    82.2705,    50.2085,   138.6217,    88.4132},
{ 83,    82.7755,    50.5000,   139.4964,    88.9963},
{ 84,    83.2805,    50.7916,   140.3711,    89.5795},
{ 85,    83.7855,    51.0832,   141.2457,    90.1626},
{ 86,    84.2905,    51.3747,   142.1204,    90.7457},
{ 87,    84.7955,    51.6663,   142.9951,    91.3288},
{ 88,    85.3005,    51.9579,   143.8698,    91.9119},
{ 89,    85.8055,    52.2494,   144.7445,    92.4951},
{ 90,    86.3105,    52.5410,   145.6192,    93.0782},
{ 91,    86.8155,    52.8325,   146.4939,    93.6613},
{ 92,    87.3205,    53.1241,   147.3685,    94.2444},
{ 93,    87.8255,    53.4157,   148.2432,    94.8276},
{ 94,    88.3305,    53.7072,   149.1179,    95.4107},
{ 95,    88.8355,    53.9988,   149.9926,    95.9938},
{ 96,    89.3405,    54.2904,   150.8673,    96.5769},
{ 97,    89.8455,    54.5819,   151.7420,    97.1601},
{ 98,    90.3505,    54.8735,   152.6167,    97.7432},
{ 99,    90.8555,    55.1650,   153.4913,    98.3263},
{100,    91.3605,    55.4566,   154.3660,    98.9094},
{101,    91.8655,    55.7482,   155.2407,    99.4926},
{102,    92.3705,    56.0397,   156.1154,   100.0757},
{103,    92.8755,    56.3313,   156.9901,   100.6588},
{104,    93.3805,    56.6228,   157.8648,   101.2419},
{105,    93.8855,    56.9144,   158.7394,   101.8250},
{106,    94.3905,    57.2060,   159.6141,   102.4082},
{107,    94.8955,    57.4975,   160.4888,   102.9913},
{108,    95.4005,    57.7891,   161.3635,   103.5744},
{109,    95.9055,    58.0807,   162.2382,   104.1575},
{110,    96.4105,    58.3722,   163.1129,   104.7407},
{111,    96.9155,    58.6638,   163.9876,   105.3238},
{112,    97.4205,    58.9553,   164.8623,   105.9069},
{113,    97.9255,    59.2469,   165.7369,   106.4900},
{114,    98.4305,    59.5385,   166.6116,   107.0732},
{115,    98.9355,    59.8300,   167.4863,   107.6563},
{116,    99.4405,    60.1216,   168.3610,   108.2394},
{117,    99.9455,    60.4132,   169.2357,   108.8225},
{118,   100.4505,    60.7047,   170.1104,   109.4056},
{119,   100.9555,    60.9963,   170.9850,   109.9888},
{120,   101.4605,    61.2878,   171.8597,   110.5719},
{121,   101.9655,    61.5794,   172.7344,   111.1550},
{122,   102.4705,    61.8710,   173.6091,   111.7381},
{123,   102.9755,    62.1625,   174.4838,   112.3213},
{124,   103.4805,    62.4541,   175.3585,   112.9044},
{125,   103.9855,    62.7456,   176.2332,   113.4875},
{126,   104.4905,    63.0372,   177.1078,   114.0706},
{127,   104.9955,    63.3288,   177.9825,   114.6538},
{128,   105.5005,    63.6203,   178.8572,   115.2369},
{129,   106.0055,    63.9119,   179.7319,   115.8200},
{130,   106.5105,    64.2035,   180.6066,   116.4031},
{131,   107.0155,    64.4950,   181.4813,   116.9863},
{132,   107.5205,    64.7866,   182.3560,   117.5694},
{133,   108.0255,    65.0781,   183.2307,   118.1525},
{134,   108.5305,    65.3697,   184.3468,   118.9771},
{135,   109.0355,    65.6613,   184.0486,   118.3873},
{136,   109.5405,    65.9528,   183.7485,   117.7956},
{137,   110.0455,    66.2444,   183.4465,   117.2021},
{138,   110.5505,    66.5359,   183.1426,   116.6066},
{139,   111.0555,    66.8275,   182.8368,   116.0093},
{140,   111.5605,    67.1191,   182.5291,   115.4100},
{141,   112.0655,    67.4106,   182.2195,   114.8089},
{142,   112.5705,    67.7022,   181.9079,   114.2057},
{143,   113.0755,    67.9938,   181.5945,   113.6007},
{144,   113.5805,    68.2853,   181.2790,   112.9937},
{145,   114.0855,    68.5769,   180.9616,   112.3848},
{146,   114.5905,    68.8684,   180.6423,   111.7738},
{147,   115.0955,    69.1600,   180.3210,   111.1609},
{148,   115.6005,    69.4516,   179.9976,   110.5461},
{149,   116.1055,    69.7431,   179.6723,   109.9292},
{150,   116.6105,    70.0347,   179.3450,   109.3103},
{151,   117.1155,    70.3263,   179.0156,   108.6893},
{152,   117.6205,    70.6178,   178.6842,   108.0664},
{153,   118.1255,    70.9094,   178.3507,   107.4414},
{154,   118.6305,    71.2009,   178.0152,   106.8143},
{155,   119.1355,    71.4925,   177.6777,   106.1852},
{156,   119.6405,    71.7841,   177.3380,   105.5539},
{157,   120.1455,    72.0756,   176.9963,   104.9206},
{158,   120.6505,    72.3672,   176.6524,   104.2852},
{159,   121.1555,    72.6588,   176.3065,   103.6477},
{160,   121.6605,    72.9503,   175.9583,   103.0080},
{161,   122.1655,    73.2419,   175.6081,   102.3662},
{162,   122.6705,    73.5334,   175.2557,   101.7223},
{163,   123.1755,    73.8250,   174.9012,   101.0762},
{164,   123.6805,    74.1166,   174.5444,   100.4279},
{165,   124.1855,    74.4081,   174.1855,    99.7774},
{166,   124.6905,    74.6997,   173.8243,    99.1247},
{167,   125.1955,    74.9912,   173.4610,    98.4697},
{168,   125.7005,    75.2828,   173.0954,    97.8126},
{169,   126.2055,    75.5744,   172.7275,    97.1531},
{170,   126.7105,    75.8659,   172.3574,    96.4915},
{171,   127.2155,    76.1575,   171.9850,    95.8275},
{172,   127.7205,    76.4491,   171.6103,    95.1612},
{173,   128.2255,    76.7406,   171.2333,    94.4927},
{174,   128.7305,    77.0322,   170.8540,    93.8218},
{175,   129.2355,    77.3237,   170.4723,    93.1485},
{176,   129.7405,    77.6153,   170.0883,    92.4730},
{177,   130.2455,    77.9069,   169.7019,    91.7950},
{178,   130.7505,    78.1984,   169.3131,    91.1147},
{179,   131.2555,    78.4900,   168.9219,    90.4319},
{180,   131.7605,    78.8987,   168.5283,    89.6296},
{181,   132.2655,    79.3848,   168.1323,    88.7475},
{182,   132.7705,    79.6753,   167.7337,    88.0585},
{183,   133.2755,    79.9682,   167.3328,    87.3646},
{184,   133.7805,    80.2587,   166.9293,    86.6706},
{185,   134.2855,    80.5517,   166.5233,    85.9716},
{186,   134.7905,    80.8422,   166.1149,    85.2727},
{187,   135.2955,    81.1327,   165.7038,    84.5711},
{188,   135.8005,    81.4258,   165.2902,    83.8644},
{189,   136.3055,    81.7162,   164.8740,    83.1577},
{190,   136.8105,    82.0092,   164.4552,    82.4459},
{191,   137.3155,    82.7696,   164.0338,    81.2641},
{192,   137.8205,    83.0601,   163.6097,    80.5496},
{193,   138.3255,    83.0604,   163.1830,    80.1226},
{194,   138.8305,    83.4896,   162.7535,    79.2639},
{195,   139.3355,    83.9790,   162.3214,    78.3425},
{196,   139.8405,    84.4741,   161.8866,    77.4125},
{197,   140.3455,    84.9808,   161.4489,    76.4682},
{198,   140.8505,    85.2004,   161.0086,    75.8082},
{199,   141.3555,    84.3212,   160.5654,    76.2441},
{200,   141.8605,    84.6128,   160.1194,    75.5066},
{201,   142.3655,    84.9043,   159.6706,    74.7662},
{202,   142.8705,    85.1959,   159.2188,    74.0229},
{203,   143.3755,    85.4875,   158.7643,    73.2768},
{204,   143.8805,    85.7790,   158.3067,    72.5277},
{205,   144.3855,    86.0706,   157.8463,    71.7757},
{206,   144.8905,    86.3622,   157.3829,    71.0207},
{207,   145.3955,    86.6537,   156.9164,    70.2627},
{208,   145.9005,    86.9453,   156.4470,    69.5017},
{209,   146.4055,    87.2368,   155.9745,    68.7377},
{210,   146.9105,    87.5284,   155.4989,    67.9705},
{211,   147.4155,    87.8200,   155.0203,    67.2003},
{212,   147.9205,    88.1115,   154.5385,    66.4270},
{213,   148.4255,    88.4031,   154.0535,    65.6504},
{214,   148.9305,    88.6947,   153.5654,    64.8707},
{215,   149.4355,    88.9862,   153.0740,    64.0878},
{216,   149.9405,    89.2778,   152.5794,    63.3016},
{217,   150.4455,    89.5693,   152.0815,    62.5121},
{218,   150.9505,    89.8609,   151.5802,    61.7193},
{219,   151.4555,    90.1525,   151.0757,    60.9232},
{220,   151.9605,    90.4440,   150.5677,    60.1237},
{221,   152.4655,    90.7356,   150.0563,    59.3207},
{222,   152.9705,    91.0271,   149.5415,    58.5143},
{223,   153.4755,    91.3187,   149.0231,    57.7044},
{224,   153.9805,    91.6103,   148.5013,    56.8910},
{225,   154.4855,    91.9018,   147.9758,    56.0740},
{226,   154.9905,    92.1934,   147.4468,    55.2534},
{227,   155.4955,    92.4850,   146.9141,    54.4292},
{228,   156.0005,    92.7765,   146.3778,    53.6013},
{229,   156.5055,    93.0681,   145.8377,    52.7697},
{230,   157.0105,    93.3596,   145.2939,    51.9343},
{231,   157.5155,    93.6512,   144.7463,    51.0951},
{232,   158.0205,    93.9428,   144.1948,    50.2520},
{233,   158.5255,    94.2343,   143.6394,    49.4051},
{234,   159.0305,    94.5259,   143.0801,    48.5542},
{235,   159.5355,    94.8175,   142.5168,    47.6994},
{236,   160.0405,    95.1090,   141.9495,    46.8405},
{237,   160.5455,    95.4006,   141.3781,    45.9775},
{238,   161.0505,    95.6921,   140.8025,    45.1104},
{239,   161.5555,    95.9837,   140.2228,    44.2391},
{240,   162.0605,    96.3798,   139.6389,    43.2590},
{241,   162.5655,    96.8659,   139.0506,    42.1847},
{242,   163.0705,    97.1564,   138.4581,    41.3017},
{243,   163.5755,    97.4494,   137.8611,    40.4117},
{244,   164.0805,    97.7399,   137.2596,    39.5198},
{245,   164.5855,    98.0328,   136.6537,    38.6209},
{246,   165.0905,    98.3233,   136.0432,    37.7199},
{247,   165.5955,    98.6138,   135.4280,    36.8142},
{248,   166.1005,    98.9069,   134.8082,    35.9013},
{249,   166.6055,    99.1974,   134.1836,    34.9862},
{250,   167.1105,    99.4904,   133.5541,    34.0637},
{251,   167.6155,   100.2508,   132.9198,    32.6690},
{252,   168.1205,   100.5412,   132.2804,    31.7392},
{253,   168.6255,   100.5440,   131.6361,    31.0921},
{254,   169.1305,   100.9787,   130.9866,    30.0079},
{255,   169.6355,   101.4717,   130.3319,    28.8603},
{256,   170.1405,   101.9701,   129.6720,    27.7020},
{257,   170.6455,   102.4807,   129.0067,    26.5260},
{258,   171.1505,   102.7082,   128.3360,    25.6277},
{259,   171.6555,   101.8149,   127.6597,    25.8448},
{260,   172.1605,   102.1065,   126.9779,    24.8714},
{261,   172.6655,   102.3981,   126.2903,    23.8923},
{262,   173.1705,   102.6896,   125.5970,    22.9073},
{263,   173.6755,   102.9812,   124.8977,    21.9165},
{264,   174.1805,   103.2727,   124.1925,    20.9197},
{265,   174.6855,   103.5643,   123.4812,    19.9168},
{266,   175.1905,   103.8559,   122.7636,    18.9077},
{267,   175.6955,   104.1474,   122.0398,    17.8924},
{268,   176.2005,   104.4390,   121.3095,    16.8705},
{269,   176.7055,   104.7306,   120.5727,    15.8422},
{270,   177.2105,   105.0221,   119.8293,    14.8072},
{271,   177.7155,   105.3137,   119.0790,    13.7654},
{272,   178.2205,   105.6052,   118.3219,    12.7166},
{273,   178.7255,   105.8968,   117.5577,    11.6609},
{274,   179.2305,   106.1884,   116.7863,    10.5980},
{275,   179.7355,   106.4799,   116.0076,     9.5277},
{276,   180.2405,   106.7715,   115.2215,     8.4500},
{277,   180.7455,   107.0630,   114.4276,     7.3646},
{278,   181.2505,   107.3546,   113.6260,     6.2714},
{279,   181.7555,   107.6462,   112.8165,     5.1703},
{280,   182.2605,   107.9377,   111.9988,     4.0611},
{281,   182.7655,   108.2293,   111.1728,     2.9435},
{282,   183.2705,   108.5209,   110.3383,     1.8174},
{283,   183.7755,   108.8124,   109.4951,     0.6827}};
