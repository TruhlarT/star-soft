/*------------------------------------------------------------------
fortran filename   : /star/starlib/star/dev/sys/tls/src/scv_state.F
------------------------------------------------------------------*/
/* [00755]LEXICAL-WARNING (/star/starlib/star/dev/sys/tls/src/scv_state.F) line 4
    ==>INTEGER IVALUE  ! CONDITION VALUE TO BE CHECKED */
/* [00755]LEXICAL-WARNING (/star/starlib/star/dev/sys/tls/src/scv_state.F) line 6
    ==>CHARACTER*(1) FLAG  ! INDICATES LEVEL OF SEVERITY BEING CHECKED */
/*
#define scv_state_ELEMS_3          ZTRINGV_NUM(1)
#define scv_state_ELEMLEN_3        ZTRINGV_NUM(0)
*/
#define tls_index_sort_i_ F77_NAME(tls_index_sort_i,TLS_INDEX_SORT_I)
#define tls_search_index_i_ F77_NAME(tls_search_index_i,TLS_SEARCH_INDEX_I)
int type_of_call tls_index_sort_i_(int *nrows, int *el1, int *el2, int *index, int *ind_size);
int type_of_call tls_search_index_i_(int *nrows, int *el1, int *el2, int *key, int *j_table_off,
				     int *k_rows,int *index, int *j_index_off);

 PROTOCCALLSFFUN2(LOGICAL,SCV_STATE,scv_state,INT,STRING)
#define SCV_STATE(A2,A3)  CCALLSFFUN2(SCV_STATE,scv_state,INT,STRING,A2,A3)

/*------------------------------------------------------------------
fortran filename   : tu_match_wild.F
------------------------------------------------------------------*/
/* [00755]LEXICAL-WARNING (tu_match_wild.F) line 5
    ==>CHARACTER*(*) STRING    ! INPUT CHARACTER STRING */
/* [00755]LEXICAL-WARNING (tu_match_wild.F) line 6
    ==>CHARACTER*(*) PATTERN   ! INPUT PATTERN TO MATCH */
/*
#define tu_match_wild_ELEMS_2          ZTRINGV_NUM(1)
#define tu_match_wild_ELEMLEN_2        ZTRINGV_NUM(0)
#define tu_match_wild_ELEMS_3          ZTRINGV_NUM(1)
#define tu_match_wild_ELEMLEN_3        ZTRINGV_NUM(0)
*/

PROTOCCALLSFFUN2(INT,TU_MATCH_WILD,tu_match_wild,STRING,STRING)
#define TU_MATCH_WILD(A2,A3) CCALLSFFUN2(TU_MATCH_WILD,tu_match_wild,STRING,STRING,A2,A3)

