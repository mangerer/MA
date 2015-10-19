#ifndef __c9_Model1angular_h__
#define __c9_Model1angular_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc9_Model1angularInstanceStruct
#define typedef_SFc9_Model1angularInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c9_sfEvent;
  boolean_T c9_isStable;
  boolean_T c9_doneDoubleBufferReInit;
  uint8_T c9_is_active_c9_Model1angular;
  real_T c9_r[6];
  real_T (*c9_G)[72];
} SFc9_Model1angularInstanceStruct;

#endif                                 /*typedef_SFc9_Model1angularInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c9_Model1angular_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c9_Model1angular_get_check_sum(mxArray *plhs[]);
extern void c9_Model1angular_method_dispatcher(SimStruct *S, int_T method, void *
  data);

#endif
