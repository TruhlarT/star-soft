#ifndef _LKH_H
#define _LKH_H

/*
 * This header is used by almost all functions of the program. It defines 
 * macros and specifies data structures and function prototypes.
 */

#undef NDEBUG
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GainType.h"
#include "Hashing.h"

/* Macro definitions */

#define Fixed(a, b) ((a)->FixedTo1 == (b) || (a)->FixedTo2 == (b))
#define FixedOrCommon(a, b) (Fixed(a, b) || IsCommonEdge(a, b))
#define InBestTour(a, b) ((a)->BestSuc == (b) || (b)->BestSuc == (a))
#define InNextBestTour(a, b)\
    ((a)->NextBestSuc == (b) || (b)->NextBestSuc == (a))
#define InInputTour(a, b) ((a)->InputSuc == (b) || (b)->InputSuc == (a))
#define InInitialTour(a, b)\
    ((a)->InitialSuc == (b) || (b)->InitialSuc == (a))
#define Near(a, b)\
    ((a)->BestSuc ? InBestTour(a, b) : (a)->Dad == (b) || (b)->Dad == (a))

#define Link(a, b) { (a)->Suc = (b); (b)->Pred = (a); }
#define Follow(b, a)\
    { Link((b)->Pred, (b)->Suc); Link(b, b); Link(b, (a)->Suc); Link(a, b); }
#define Precede(a, b)\
    { Link((a)->Pred, (a)->Suc); Link(a, a); Link((b)->Pred, a); Link(a, b); }
#define SLink(a, b) { (a)->Suc = (b); (b)->Pred = (a); }

enum Types { TSP, ATSP, SOP, HCP, CVRP, TOUR, HPP };
enum CoordTypes { TWOD_COORDS, THREED_COORDS, NO_COORDS };
enum EdgeWeightTypes { EXPLICIT, EUC_2D, EUC_3D, MAX_2D, MAX_3D, MAN_2D,
    MAN_3D, CEIL_2D, CEIL_3D, GEO, GEOM, GEO_MEEUS, GEOM_MEEUS, ATT,
    XRAY1, XRAY2, SPECIAL
};
enum EdgeWeightFormats { FUNCTION, FULL_MATRIX, UPPER_ROW, LOWER_ROW,
    UPPER_DIAG_ROW, LOWER_DIAG_ROW, UPPER_COL, LOWER_COL,
    UPPER_DIAG_COL, LOWER_DIAG_COL
};
enum CandidateSetTypes { ALPHA, DELAUNAY, NN, QUADRANT };
enum InitialTourAlgorithms { BORUVKA, GREEDY, MOORE, NEAREST_NEIGHBOR,
    QUICK_BORUVKA, SIERPINSKI, WALK
};

struct Candidate;
struct Segment;
struct SSegment;

/* The Node structure is used to represent nodes (cities) of the problem */

typedef struct Node {
    int Id;     /* Number of the node (1...Dimension) */
    int Loc;    /* Location of the node in the heap 
                   (zero, if the node is not in the heap) */
    int Rank;   /* During the ascent, the priority of the node.
                   Otherwise, the ordinal number of the node in 
                   the tour */
    int V;      /* During the ascent the degree of the node minus 2.
                   Otherwise, the variable is used to mark nodes */
    int LastV;  /* Last value of V during the ascent */
    int Cost;   /* "Best" cost of an edge emanating from the node */
    int NextCost;      /* During the ascent, the next best cost of an edge
                          emanating from the node */
    int PredCost, /* The costs of the neighbor edges on the current tour */ 
        SucCost; 
    int Pi;     /* Pi-value of the node */
    int BestPi;        /* Currently best pi-value found during the ascent */
    int Beta;   /* Beta-value (used for computing alpha-values) */
    int Subproblem;    /* Number of the subproblem the node is part of */
    int Sons;   /* Number of sons in the minimum spanning tree */
    int *C;     /* A row in the cost matrix */
    struct Node *Pred, *Suc;    /* Predecessor and successor node in 
                                   the two-way list of nodes */
    struct Node *OldPred,       /* Previous values of Pred and Suc */
                *OldSuc;
    struct Node *BestSuc,       /* Best and next best successor node in the */
                *NextBestSuc;   /* currently best tour */
    struct Node *Dad;   /* Father of the node in the minimum 1-tree */
    struct Node *Nearest;  /* Nearest node (used in the greedy heuristics) */
    struct Node *Next;  /* Auxiliary pointer, usually to the next node 
                           in a list of nodes (e.g., the list of 
                           "active" nodes) */
    struct Node *Prev;  /* Auxiliary pointer, usually to the previous node 
                           in a list of nodes */
    struct Node *Mark;  /* Visited mark */
    struct Node *FixedTo1,      /* Pointers to the opposite end nodes of fixed 
                                   edges. */
    *FixedTo2;  /* A maximum of two fixed edges can be incident
                   to a node */
    struct Node *FixedTo1Saved, /* Saved values of FixedTo1 and FixedTo2 */
                *FixedTo2Saved;
    struct Node *Head;  /* Head of a segment of common edges */
    struct Node *Tail;  /* Tail of a segment of common edges */
    struct Node *InputSuc;      /* Successor in the INPUT_TOUR file */
    struct Node *InitialSuc;    /* Successor in the INITIAL_TOUR file */
    struct Node *SubproblemPred; /* Predecessor in the SUBPROBLEM_TOUR file */
    struct Node *SubproblemSuc; /* Successor in the SUBPROBLEM_TOUR file */
    struct Node *SubBestPred;   /* The best predecessor node in a subproblem */
    struct Node *SubBestSuc;    /* The best successor node in a subproblem */
    struct Node **MergeSuc;     /* Successor in the MERGE_TOUR files */
    struct Node *Added1, *Added2;      /* Pointers to the opposite end nodes
                                          of added edges in a submove */
    struct Node *Deleted1, *Deleted2;  /* Pointers to the opposite end nodes
                                          of deleted edges in a submove */
    struct Candidate *CandidateSet;    /* Candidate array */
    struct Candidate *BackboneCandidateSet;    /* Backbone candidate array */
    struct Segment *Parent;     /* Parent segment of a node when the two-level
                                   tree representation is used */
    double X, Y, Z;     /* Coordinates of the node */
    double Xc, Yc, Zc;  /* Converted coordinates */
    char Axis;  /* The axis partitioned when the node is part of a KDTree */
    char OldPredExcluded, OldSucExcluded;  /* Booleans used for indicating 
                                              whether one (or both) of the 
                                              adjoining nodes on the old tour 
                                              has been excluded */
} Node;

/* The Candidate structure is used to represent candidate edges */

typedef struct Candidate {
    Node *To;   /* The end node of the edge */
    int Cost;   /* Cost (distance) of the edge */
    int Alpha;  /* Its alpha-value */
} Candidate;

/* The Segment structure is used to represent the segments in the two-level 
   representation of tours */

typedef struct Segment {
    char Reversed;      /* Reversal bit */
    Node *First, *Last; /* First and last node in the segment */
    struct Segment *Pred, *Suc; /* Predecessor and successor in the two-way 
                                   list of segments */
    int Rank;   /* Ordinal number of the segment in the list */
    int Size;   /* Number of nodes in the segment */
    struct SSegment *Parent;    /* The parent super segment */
} Segment;

typedef struct SSegment {
    char Reversed;       /* Reversal bit */
    Segment *First, *Last;      /* The first and last node in the segment */
    struct SSegment *Pred, *Suc;    /* The predecessor and successor in the
                                       two-way list of super segments */
    int Rank;   /* The ordinal number of the segment in the list */
    int Size;   /* The number of nodes in the segment */
} SSegment;

/* The SwapRecord structure is used to record 2-opt moves (swaps) */

typedef struct SwapRecord {
    Node *t1, *t2, *t3, *t4;    /* The 4 nodes involved in a 2-opt move */
} SwapRecord;

typedef Node *(*MoveFunction) (Node * t1, Node * t2, GainType * G0,
                               GainType * Gain);
typedef int (*CostFunction) (Node * Na, Node * Nb);

int AscentCandidates;   /* Number of candidate edges to be associated
                           with each node during the ascent */
int BackboneTrials;     /* Number of backbone trials in each run */
int Backtracking;       /* Specifies whether backtracking is used for 
                           the first move in a sequence of moves */
GainType BestCost;      /* Cost of the tour in BestTour */
int *BestTour;  /* Table containing best tour found */
GainType BetterCost;    /* Cost of the tour stored in BetterTour */
int *BetterTour;        /* Table containing the currently best tour 
                           in a run */
int CacheMask;  /* Mask for indexing the cache */
int *CacheVal;  /* Table of cached distances */
int *CacheSig;  /* Table of the signatures of cached 
                   distances */
int CandidateFiles;     /* Number of CANDIDATE_FILEs */
int *CostMatrix;        /* Cost matrix */
int Dimension;  /* Number of nodes in the problem */
int DimensionSaved;     /* Saved value of Dimension */
double Excess;  /* Maximum alpha-value allowed for any 
                   candidate edge is set to Excess times the 
                   absolute value of the lower bound of a 
                   solution tour */
int ExtraCandidates;    /* Number of extra neighbors to be added to 
                           the candidate set of each node */
Node *FirstActive, *LastActive; /* First and last node in the list 
                                   of "active" nodes */
Node *FirstNode;        /* First node in the list of nodes */
Segment *FirstSegment;  /* A pointer to the first segment in the cyclic 
                           list of segments */
SSegment *FirstSSegment;        /* A pointer to the first super segment in
                                   the cyclic list of segments */
int Gain23Used; /* Specifies whether Gain23 is used */
int GainCriterionUsed;  /* Specifies whether L&K's gain criterion is 
                           used */
int GroupSize;  /* Desired initial size of each segment */
int SGroupSize; /* Desired initial size of each super segment */
int Groups;     /* Current number of segments */
int SGroups;    /* Current number of super segments */
unsigned tspHash;  /* Hash value corresponding to the current tour */
Node **Heap;    /* Heap used for computing minimum spanning 
                   trees */
HashTable *HTable;      /* Hash table used for storing tours */
int InitialPeriod;      /* Length of the first period in the ascent */
int InitialStepSize;    /* Initial step size used in the ascent */
double InitialTourFraction;     /* Fraction of the initial tour to be 
                                   constructed by INITIAL_TOUR_FILE edges */
char *LastLine; /* Last input line */
double LowerBound;      /* Lower bound found by the ascent */
int Kicks;      /* Specifies the number of K-swap-kicks */
int KickType;   /* Specifies K for a K-swap-kick */
int M;   /* The M-value is used when solving an ATSP-
            instance by transforming it to a 
            STSP-instance */
int MaxBreadth; /* The maximum number of candidate edges 
                   considered at each level of the search for
                   a move */
int MaxCandidates;      /* Maximum number of candidate edges to be 
                           associated with each node */
int MaxMatrixDimension; /* Maximum dimension for an explicit cost matrix */
int MaxSwaps;   /* Maximum number of swaps made during the 
                   search for a move */
int MaxTrials;  /* Maximum number of trials in each run */
int MergeTourFiles;     /* Number of MERGE_TOUR_FILEs */
int MoveType;   /* Specifies the sequantial move type to be used 
                   in local search. A value K >= 2 signifies 
                   that a k-opt moves are tried for k <= K */
Node *NodeSet;  /* Array of all nodes */
int Norm;       /* Measure of a 1-tree's discrepancy from a tour */
int NonsequentialMoveType;      /* Specifies the nonsequential move type to
                                   be used in local search. A value 
                                   L >= 4 signifies that nonsequential
                                   l-opt moves are tried for l <= L */
GainType Optimum;       /* Known optimal tour length. 
                           If StopAtOptimum is 1, a run will be 
                           terminated as soon as a tour length 
                           becomes equal this value */
int PatchingA;  /* Specifies the maximum number of alternating
                   cycles to be used for patching disjunct cycles */
int PatchingC;  /* Specifies the maximum number of disjoint cycles to be 
                   patched (by one or more alternating cycles) */
int Precision;  /* Internal precision in the representation of 
                   transformed distances */
int PredSucCostAvailable; /* PredCost and SucCost is available */
unsigned *Rand; /* Table of random values */
int RestrictedSearch;   /* Specifies whether the choice of the first 
                           edge to be broken is restricted */
short Reversed; /* Boolean used to indicate whether a tour has 
                   been reversed */
int Run; /* Current run number */
int Runs;       /* Total number of runs */
unsigned Seed;  /* Initial seed for random number generation */
int StopAtOptimum;      /* Specifies whether a run will be terminated if 
                           the tour length becomes equal to Optimum */
int Subgradient;        /* Specifies whether the Pi-values should be 
                           determined by subgradient optimization */
int SubproblemSize;     /* Number of nodes in a subproblem */
int SubsequentMoveType; /* Specifies the move type to be used for all 
                           moves following the first move in a sequence 
                           of moves. The value K >= 2 signifies that a 
                           K-opt move is to be used */
int SubsequentPatching; /* Species whether patching is used for 
                           subsequent moves */
SwapRecord *SwapStack;  /* Stack of SwapRecords */
int Swaps;      /* Number of swaps made during a tentative move */
double TimeLimit;       /* The time limit in seconds for each run */
int TraceLevel; /* Specifies the level of detail of the output 
                   given during the solution process. 
                   The value 0 signifies a minimum amount of 
                   output. The higher the value is the more 
                   information is given */
int Trial;      /* Ordinal number of the current trial */

/* The following variables are read by the functions ReadParameters and 
   ReadProblem: */

char *ParameterFileName, *ProblemFileName, *PiFileName,
    *TourFileName, *OutputTourFileName, *InputTourFileName,
    **CandidateFileName, *InitialTourFileName,
    *SubproblemTourFileName, **MergeTourFileName;
char *Name, *Type, *EdgeWeightType, *EdgeWeightFormat,
    *EdgeDataFormat, *NodeCoordType, *DisplayDataType;
int CandidateSetSymmetric, CandidateSetType,
    CoordType, DelaunayPartitioning, DelaunayPure,
    ExtraCandidateSetSymmetric, ExtraCandidateSetType,
    InitialTourAlgorithm,
    KarpPartitioning, KMeansPartitioning,
    MoorePartitioning,
    PatchingAExtended, PatchingARestricted,
    PatchingCExtended, PatchingCRestricted,
    ProblemType,
    RohePartitioning, SierpinskiPartitioning,
    SubproblemBorders, SubproblemsCompressed, WeightType, WeightFormat;

FILE *ParameterFile, *ProblemFile, *PiFile, *InputTourFile,
    *TourFile, *InitialTourFile, *SubproblemTourFile, **MergeTourFile;
CostFunction Distance, D, C, c;
MoveFunction BestMove, BacktrackMove, BestSubsequentMove;

/* Function prototypes: */

int Distance_1(Node * Na, Node * Nb);
int Distance_ATSP(Node * Na, Node * Nb);
int Distance_ATT(Node * Na, Node * Nb);
int Distance_CEIL_2D(Node * Na, Node * Nb);
int Distance_CEIL_3D(Node * Na, Node * Nb);
int Distance_EXPLICIT(Node * Na, Node * Nb);
int Distance_EUC_2D(Node * Na, Node * Nb);
int Distance_EUC_3D(Node * Na, Node * Nb);
int Distance_GEO(Node * Na, Node * Nb);
int Distance_GEOM(Node * Na, Node * Nb);
int Distance_GEO_MEEUS(Node * Na, Node * Nb);
int Distance_GEOM_MEEUS(Node * Na, Node * Nb);
int Distance_MAN_2D(Node * Na, Node * Nb);
int Distance_MAN_3D(Node * Na, Node * Nb);
int Distance_MAX_2D(Node * Na, Node * Nb);
int Distance_MAX_3D(Node * Na, Node * Nb);
int Distance_SPECIAL(Node * Na, Node * Nb);
int Distance_XRAY1(Node * Na, Node * Nb);
int Distance_XRAY2(Node * Na, Node * Nb);

int D_EXPLICIT(Node * Na, Node * Nb);
int D_FUNCTION(Node * Na, Node * Nb);

int C_EXPLICIT(Node * Na, Node * Nb);
int C_FUNCTION(Node * Na, Node * Nb);

int c_ATT(Node * Na, Node *Nb);
int c_CEIL_2D(Node * Na, Node * Nb);
int c_CEIL_3D(Node * Na, Node * Nb);
int c_EUC_2D(Node * Na, Node * Nb);
int c_EUC_3D(Node * Na, Node * Nb);
int c_GEO(Node * Na, Node * Nb);
int c_GEOM(Node * Na, Node * Nb);
int c_GEO_MEEUS(Node * Na, Node * Nb);
int c_GEOM_MEEUS(Node * Na, Node * Nb);

void Activate(Node * t);
int AddCandidate(Node * From, Node * To, int Cost, int Alpha);
void AddExtraCandidates(int K, int CandidateSetType, int Symmetric);
void AddTourCandidates(void);
void AdjustCandidateSet(void);
void AllocateSegments(void);
void AllocateStructures(void);
GainType Ascent(void);
Node *Best2OptMove(Node * t1, Node * t2, GainType * G0, GainType * Gain);
Node *Best3OptMove(Node * t1, Node * t2, GainType * G0, GainType * Gain);
Node *Best4OptMove(Node * t1, Node * t2, GainType * G0, GainType * Gain);
Node *Best5OptMove(Node * t1, Node * t2, GainType * G0, GainType * Gain);
Node *BestKOptMove(Node * t1, Node * t2, GainType * G0, GainType * Gain);
int Between(const Node * t2, const Node * t1, const Node * t3);
int Between_SL(const Node * t2, const Node * t1, const Node * t3);
int Between_SSL(const Node * t2, const Node * t1, const Node * t3);
GainType BridgeGain(Node * s1, Node * s2, Node * s3, Node * s4,
                    Node * s5, Node * s6, Node * s7, Node * s8,
                    int Case6, GainType G);
Node **BuildKDTree(int Cutoff);
void ChooseInitialTour(void);
void Connect(Node * N1, int Max, int Sparse);
void CandidateReport(void);
void CreateCandidateSet(void);
void CreateDelaunayCandidateSet(void);
void CreateNearestNeighborCandidateSet(int K);
void CreateQuadrantCandidateSet(int K);
void eprintf(const char *fmt, ...);
int Excludable(Node * ta, Node * tb);
void Exclude(Node * ta, Node * tb);
GainType FindTour(void);
void Flip(Node * t1, Node * t2, Node * t3);
void Flip_SL(Node * t1, Node * t2, Node * t3);
void Flip_SSL(Node * t1, Node * t2, Node * t3);
int Forbidden(const Node * ta, const Node * tb);
void FreeCandidateSets(void);
void FreeSegments(void);
void FreeStructures(void);
int fscanint(FILE *f, int *v);
GainType Gain23(void);
void GenerateCandidates(int MaxCandidates, GainType MaxAlpha, int Symmetric);
double GetTime(void);
GainType GreedyTour(void);
void InitializeStatistics(void);
int IsCandidate(Node * ta, Node * tb);
int IsCommonEdge(Node * ta, Node * tb);
void KSwapKick(int K);
GainType LinKernighan(void);
void Make2OptMove(Node * t1, Node * t2, Node * t3, Node * t4);
void Make3OptMove(Node * t1, Node * t2, Node * t3, Node * t4, 
                  Node * t5, Node * t6, int Case);
void Make4OptMove(Node * t1, Node * t2, Node * t3, Node * t4, 
                  Node * t5, Node * t6, Node * t7, Node * t8, 
                  int Case);
void Make5OptMove(Node * t1, Node * t2, Node * t3, Node * t4, 
                  Node * t5, Node * t6, Node * t7, Node * t8,
                  Node * t9, Node * t10, int Case);
void MakeKOptMove(int K);
GainType MergeBetterTourWithBestTour(void);
GainType MergeWithTour(void);
GainType Minimum1TreeCost(int Sparse);
void MinimumSpanningTree(int Sparse);
void NormalizeNodeList(void);
void NormalizeSegmentList(void);
void OrderCandidateSet(int MaxCandidates, 
                       GainType MaxAlpha, int Symmetric);
GainType PatchCycles(int k, GainType Gain);
void printff(char *fmt, ...);
void PrintParameters(void);
void PrintStatistics(void);
unsigned Random(void);
int ReadCandidates(int MaxCandidates);
char *ReadLine(FILE * InputFile);
void ReadParameters(void);
int ReadPenalties(void);
void ReadProblem(void);
void ReadTour(char * FileName, FILE ** File);
void RecordBestTour(void);
void RecordBetterTour(void);
Node *RemoveFirstActive(void);
void ResetCandidateSet(void);
void RestoreTour(void);
int SegmentSize(Node *ta, Node *tb);
GainType SFCTour(int CurveType);
void SolveDelaunaySubproblems(void);
void SolveKarpSubproblems(void);
void SolveKMeansSubproblems(void);
void SolveRoheSubproblems(void);
void SolveSFCSubproblems(void);
void SolveSubproblem(int CurrentSubproblem, int Subproblems, 
                     GainType * GlobalBestCost);
void SolveSubproblemBorderProblems(int Subproblems, GainType * GlobalCost);
void SolveTourSegmentSubproblems(void);
void StoreTour(void);
void SRandom(unsigned seed);
void SymmetrizeCandidateSet(void);
void TrimCandidateSet(int MaxCandidates);
void UpdateStatistics(GainType Cost, double Time);
void WriteCandidates(void);
void WritePenalties(void);
void WriteTour(char * FileName, int * Tour, GainType Cost);

#endif
