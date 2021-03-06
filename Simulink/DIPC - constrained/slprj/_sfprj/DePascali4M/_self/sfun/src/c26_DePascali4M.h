#ifndef __c26_DePascali4M_h__
#define __c26_DePascali4M_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc26_DePascali4MInstanceStruct
#define typedef_SFc26_DePascali4MInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c26_sfEvent;
  boolean_T c26_isStable;
  boolean_T c26_doneDoubleBufferReInit;
  uint8_T c26_is_active_c26_DePascali4M;
  real_T c26_k1;
  real_T c26_kappa1;
  real_T *c26_eta1;
  real_T (*c26_K)[36];
} SFc26_DePascali4MInstanceStruct;

#endif                                 /*typedef_SFc26_DePascali4MInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c26_DePascali4M_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c26_DePascali4M_get_check_sum(mxArray *plhs[]);
extern void c26_DePascali4M_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
