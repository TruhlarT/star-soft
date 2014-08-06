#ifndef _TPX_FCF_H_
#define _TPX_FCF_H_

#include "tpxFCF_flags.h"

// main tunable parameters
#define FCF_ADC_NOISE           4
#define FCF_ADC_MIN		4	// we additionally can kill 1d sequences where the maximum is below this
#define FCF_MIN_WIDTH           1
#define FCF_MIN_ADC_PAD_C       180


// timebins at which the gating grid opens & closes -- the gain is compromised if we cross them...
#define TPC_GG_OPEN	22
#define TPC_FF_CLOSE	380


#define FCF_MAX_CL	64		// max 1D clusters per pad

// version/flavor reminders
#define FCF_V_FY08	0x0000		// used in the FY08 run; has the /32 "bug"
#define FCF_V_FY09	0x0001		// /32 bug fixed 

#define FCF_2D_V_FY13	0x1000		// first version of FCF_2D!



//#define FCF_DEBUG

#define FCF_DO_DOUBLE	// timebins, pads, averages are double instead of u_int
//#define FCF_DO_INT 	// p1, t1 etc. are ints instead of shorts


#ifdef FCF_DO_DOUBLE
	typedef float fcf_type;
#else
	typedef int fcf_type;
#endif

#ifdef FCF_DO_INT
	typedef int fcf_short ;
#else
	typedef short fcf_short ;
#endif


// forwad decls
class tpxGain ;
struct daq_cld ;
struct daq_sim_cld ;
struct daq_sim_adc_tb ;


struct tpxFCF_cl {
	union {
		unsigned int charge ;
		fcf_type f_charge ;
	} ;
	union {
		unsigned int t_ave ;
		fcf_type f_t_ave ;
	} ;

	fcf_type scharge ;
	fcf_type p_ave ;


	// extents
	fcf_short t1, t_min ;
	fcf_short t2, t_max ;

	fcf_short p1 ;
	fcf_short p2 ;

	fcf_short flags ;
	unsigned short track_id ;

	short quality ;	
	short sim_length ;	// length of the corresponding sim data in *sim

	daq_sim_adc_tb *sim ;	// for simulation, keep the pointer to the cluster data...
} ;


struct tpx_altro_struct ;

class tpxFCF {
public:
	tpxFCF() ;
	~tpxFCF() ;

	void config(unsigned int rb_mask, int modes=0, int rows=0, unsigned char *rowlen=0) ;	// modes bitmask
	int modes ;	// bit mask: 1 run simulated; 2 run simulated with local id

	void apply_gains(int sector, tpxGain *gains) ;

	void start_evt() ;

	int do_pad(tpx_altro_struct *a, daq_sim_adc_tb *extra = 0) ;
	int stage2(unsigned int *outbuff, int max_bytes) ;



	char do_cuts ;
	char run_compatibility ;

	int ch_min ;

	static int fcf_decode(unsigned int *p_buff, daq_cld *dc, unsigned short version=0) ;
	static int fcf_decode(unsigned int *p_buff, daq_sim_cld *sdc, unsigned short version=0) ;
	static int afterburner(int cou, daq_cld *store[]) ;
	static char *fcf_flags(u_char flags) ;

	// new functions for FY13 which assist in running FCF on any sector and rdo
	void config2(int sec, int rdo, int modes=0, int rows=0, unsigned char *rowlen=0) ;
	void apply_gains2(tpxGain *gains) ;
	void start_evt2(int sec1, int rdo1) ;
	void set_id(int id) {
		my_id = id ;
	}
	int fcf_style ;	// new for FY13!

	const char *GetCVS() const {	// Offline
		static const char cvs[]="Tag $Name:  $: $Id: tpxFCF.h,v 1.17 2014/08/06 11:42:51 jeromel Exp $: built " __DATE__ " " __TIME__ ; return cvs;
	}

	int sector ;	// counts from 1
	int rdo ;	// counts from 1

	inline int is_pad_valid(int row, int pad)
	{
		s_static_storage *ss = get_static(row,pad) ;
		if(ss==0) return 0 ;
		if(ss->f & FCF_KILLED_PAD) return 0 ;
		return 1 ;
	}

protected:
	unsigned char *tpx_rowlen ;

	struct s_static_storage {
		unsigned short f ;
		double g ;
		double t0 ;
	} ;

	static struct s_storage_stuff {
		struct s_static_storage *storage ;
		int row_ix[256] ;
	} gain_storage[24][6] ;


	inline struct s_static_storage *get_static(int row, int pad)
	{
		int s = sector -1 ;
		int r = rdo - 1 ;

		if(r < 0) {	// figure out from the row & pad
			int a, ch ;
			tpx_to_altro(row,pad,r,a,ch) ;

			r-- ;	// need to start from 0

//			LOG(TERR,"r:p %d:%d - rdo is %d",row,pad,r) ;
		}

		if(gain_storage[s][r].storage == 0) return 0 ;
		if(gain_storage[s][r].row_ix[row] < 0) return 0 ;

		return gain_storage[s][r].storage + gain_storage[s][r].row_ix[row] + (pad-1) ;

	}


private:

	unsigned int *loc_buff ;
	int cur_row ;
	int cur_row_clusters ;

	int row_count ;	// will default to 45 in the constructor unless overriden!

	int tpx_padplane ;

	int cl_marker ;

	struct stage1 {	// per pad, indexed as (row,pad)
		unsigned short count ;	// count of 1D clusters found...
		unsigned short f ;	// initial flags: dead edge, broken RDO edge, etc.
		double g ;	// gain
		double t0 ;	// t0
		struct tpxFCF_cl cl[FCF_MAX_CL] ;		
	} ;


	struct stage1 *storage ;	// where I will allocate storage

	void dump(tpxFCF_cl *cl, int row) ;

	inline struct stage1 *get_stage1(int row, int pad)
	{
		if(row_ix[row] < 0) return 0 ;

		return storage + row_ix[row] + (pad-1) ;

	}


	int row_ix[256] ;	// we exaggerate! normally was "46"

	unsigned int rbs ;
	int my_id ;


	static const int max_tot_count = 1152 ;	// maximum pads per RDO

	struct stage1 *working_storage ;
	

	inline struct stage1  *get_working(int row, int pad)
	{
		int s = sector -1 ;
		int r = rdo - 1 ;

		if(gain_storage[s][r].storage == 0) return 0 ;
		if(gain_storage[s][r].row_ix[row] < 0) return 0 ;

		return working_storage + gain_storage[s][r].row_ix[row] + (pad-1) ;
	}


//	tpxGain *gains ;

	unsigned int do_version ;
	unsigned int read_version ;
} ;

#endif
