/* Include files */

#include <stddef.h>
#include "blas.h"
#include "DIPC_sfun.h"
#include "c18_DIPC.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "DIPC_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c18_debug_family_names[6] = { "nargin", "nargout", "xb",
  "dxb", "rv", "b" };

static const char * c18_b_debug_family_names[4] = { "nargin", "nargout", "x",
  "X" };

static const char * c18_c_debug_family_names[6] = { "rwq", "nargin", "nargout",
  "q", "r", "rw" };

/* Function Declarations */
static void initialize_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance);
static void initialize_params_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance);
static void enable_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance);
static void disable_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance);
static void c18_update_debugger_state_c18_DIPC(SFc18_DIPCInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c18_DIPC(SFc18_DIPCInstanceStruct
  *chartInstance);
static void set_sim_state_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_st);
static void finalize_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance);
static void sf_gateway_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance);
static void mdl_start_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance);
static void c18_chartstep_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance);
static void initSimStructsc18_DIPC(SFc18_DIPCInstanceStruct *chartInstance);
static void c18_skew_sm(SFc18_DIPCInstanceStruct *chartInstance, real_T c18_x[3],
  real_T c18_X[9]);
static void c18_quatrot(SFc18_DIPCInstanceStruct *chartInstance, real_T c18_q[4],
  real_T c18_r[3], real_T c18_rw[3]);
static void init_script_number_translation(uint32_T c18_machineNumber, uint32_T
  c18_chartNumber, uint32_T c18_instanceNumber);
static const mxArray *c18_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static void c18_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance, const
  mxArray *c18_b_b, const char_T *c18_identifier, real_T c18_y[24]);
static void c18_b_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[24]);
static void c18_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static const mxArray *c18_b_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static void c18_c_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[12]);
static void c18_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static const mxArray *c18_c_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static const mxArray *c18_d_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static const mxArray *c18_e_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static real_T c18_d_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId);
static void c18_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static const mxArray *c18_f_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static void c18_e_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[9]);
static void c18_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static const mxArray *c18_g_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static void c18_f_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[3]);
static void c18_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static const mxArray *c18_h_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static void c18_g_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[4]);
static void c18_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static void c18_info_helper(const mxArray **c18_info);
static const mxArray *c18_emlrt_marshallOut(const char * c18_u);
static const mxArray *c18_b_emlrt_marshallOut(const uint32_T c18_u);
static void c18_eml_scalar_eg(SFc18_DIPCInstanceStruct *chartInstance);
static void c18_threshold(SFc18_DIPCInstanceStruct *chartInstance);
static void c18_quatmultiply(SFc18_DIPCInstanceStruct *chartInstance, real_T
  c18_q[4], real_T c18_r[4], real_T c18_qout[4]);
static void c18_b_eml_scalar_eg(SFc18_DIPCInstanceStruct *chartInstance);
static const mxArray *c18_i_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData);
static int32_T c18_h_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId);
static void c18_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData);
static uint8_T c18_i_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_b_is_active_c18_DIPC, const char_T *c18_identifier);
static uint8_T c18_j_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId);
static void init_dsm_address_info(SFc18_DIPCInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc18_DIPCInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance)
{
  chartInstance->c18_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c18_is_active_c18_DIPC = 0U;
}

static void initialize_params_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance)
{
  real_T c18_dv0[12];
  int32_T c18_i0;
  sf_mex_import_named("rv", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      c18_dv0, 0, 0, 0U, 1, 0U, 1, 12);
  for (c18_i0 = 0; c18_i0 < 12; c18_i0++) {
    chartInstance->c18_rv[c18_i0] = c18_dv0[c18_i0];
  }
}

static void enable_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c18_update_debugger_state_c18_DIPC(SFc18_DIPCInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c18_DIPC(SFc18_DIPCInstanceStruct
  *chartInstance)
{
  const mxArray *c18_st;
  const mxArray *c18_y = NULL;
  int32_T c18_i1;
  real_T c18_u[24];
  const mxArray *c18_b_y = NULL;
  uint8_T c18_hoistedGlobal;
  uint8_T c18_b_u;
  const mxArray *c18_c_y = NULL;
  c18_st = NULL;
  c18_st = NULL;
  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_createcellmatrix(2, 1), false);
  for (c18_i1 = 0; c18_i1 < 24; c18_i1++) {
    c18_u[c18_i1] = (*chartInstance->c18_b)[c18_i1];
  }

  c18_b_y = NULL;
  sf_mex_assign(&c18_b_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 1, 24), false);
  sf_mex_setcell(c18_y, 0, c18_b_y);
  c18_hoistedGlobal = chartInstance->c18_is_active_c18_DIPC;
  c18_b_u = c18_hoistedGlobal;
  c18_c_y = NULL;
  sf_mex_assign(&c18_c_y, sf_mex_create("y", &c18_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c18_y, 1, c18_c_y);
  sf_mex_assign(&c18_st, c18_y, false);
  return c18_st;
}

static void set_sim_state_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_st)
{
  const mxArray *c18_u;
  real_T c18_dv1[24];
  int32_T c18_i2;
  chartInstance->c18_doneDoubleBufferReInit = true;
  c18_u = sf_mex_dup(c18_st);
  c18_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c18_u, 0)), "b",
                       c18_dv1);
  for (c18_i2 = 0; c18_i2 < 24; c18_i2++) {
    (*chartInstance->c18_b)[c18_i2] = c18_dv1[c18_i2];
  }

  chartInstance->c18_is_active_c18_DIPC = c18_i_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c18_u, 1)), "is_active_c18_DIPC");
  sf_mex_destroy(&c18_u);
  c18_update_debugger_state_c18_DIPC(chartInstance);
  sf_mex_destroy(&c18_st);
}

static void finalize_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance)
{
  int32_T c18_i3;
  int32_T c18_i4;
  int32_T c18_i5;
  int32_T c18_i6;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 14U, chartInstance->c18_sfEvent);
  for (c18_i3 = 0; c18_i3 < 7; c18_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c18_xb)[c18_i3], 0U);
  }

  for (c18_i4 = 0; c18_i4 < 6; c18_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c18_dxb)[c18_i4], 1U);
  }

  chartInstance->c18_sfEvent = CALL_EVENT;
  c18_chartstep_c18_DIPC(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_DIPCMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c18_i5 = 0; c18_i5 < 24; c18_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c18_b)[c18_i5], 2U);
  }

  for (c18_i6 = 0; c18_i6 < 12; c18_i6++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c18_rv[c18_i6], 3U);
  }
}

static void mdl_start_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c18_chartstep_c18_DIPC(SFc18_DIPCInstanceStruct *chartInstance)
{
  int32_T c18_i7;
  real_T c18_b_xb[7];
  int32_T c18_i8;
  real_T c18_b_dxb[6];
  int32_T c18_i9;
  real_T c18_b_rv[12];
  uint32_T c18_debug_family_var_map[6];
  real_T c18_nargin = 3.0;
  real_T c18_nargout = 1.0;
  real_T c18_b_b[24];
  int32_T c18_i10;
  real_T c18_c_dxb[3];
  real_T c18_a[9];
  int32_T c18_i11;
  real_T c18_d_dxb[3];
  real_T c18_c_b[9];
  int32_T c18_i12;
  int32_T c18_i13;
  int32_T c18_i14;
  real_T c18_y[9];
  int32_T c18_i15;
  int32_T c18_i16;
  int32_T c18_i17;
  real_T c18_c_xb[4];
  int32_T c18_i18;
  real_T c18_c_rv[3];
  real_T c18_d_b[3];
  int32_T c18_i19;
  real_T c18_b_y[3];
  int32_T c18_i20;
  int32_T c18_i21;
  int32_T c18_i22;
  real_T c18_e_dxb[3];
  int32_T c18_i23;
  real_T c18_f_dxb[3];
  int32_T c18_i24;
  int32_T c18_i25;
  int32_T c18_i26;
  int32_T c18_i27;
  int32_T c18_i28;
  int32_T c18_i29;
  real_T c18_d_xb[4];
  int32_T c18_i30;
  real_T c18_d_rv[3];
  int32_T c18_i31;
  real_T c18_c_y[3];
  int32_T c18_i32;
  int32_T c18_i33;
  int32_T c18_i34;
  real_T c18_g_dxb[3];
  int32_T c18_i35;
  real_T c18_h_dxb[3];
  int32_T c18_i36;
  int32_T c18_i37;
  int32_T c18_i38;
  int32_T c18_i39;
  int32_T c18_i40;
  int32_T c18_i41;
  real_T c18_e_xb[4];
  int32_T c18_i42;
  real_T c18_e_rv[3];
  int32_T c18_i43;
  real_T c18_d_y[3];
  int32_T c18_i44;
  int32_T c18_i45;
  int32_T c18_i46;
  real_T c18_x[3];
  uint32_T c18_b_debug_family_var_map[4];
  real_T c18_b_nargin = 1.0;
  real_T c18_b_nargout = 1.0;
  real_T c18_X[9];
  int32_T c18_i47;
  real_T c18_i_dxb[3];
  int32_T c18_i48;
  int32_T c18_i49;
  int32_T c18_i50;
  int32_T c18_i51;
  int32_T c18_i52;
  int32_T c18_i53;
  int32_T c18_i54;
  real_T c18_f_xb[4];
  int32_T c18_i55;
  real_T c18_f_rv[3];
  int32_T c18_i56;
  real_T c18_e_y[3];
  int32_T c18_i57;
  int32_T c18_i58;
  int32_T c18_i59;
  int32_T c18_i60;
  int32_T c18_i61;
  int32_T c18_i62;
  int32_T c18_i63;
  int32_T c18_i64;
  int32_T c18_i65;
  int32_T c18_i66;
  int32_T c18_i67;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 14U, chartInstance->c18_sfEvent);
  for (c18_i7 = 0; c18_i7 < 7; c18_i7++) {
    c18_b_xb[c18_i7] = (*chartInstance->c18_xb)[c18_i7];
  }

  for (c18_i8 = 0; c18_i8 < 6; c18_i8++) {
    c18_b_dxb[c18_i8] = (*chartInstance->c18_dxb)[c18_i8];
  }

  for (c18_i9 = 0; c18_i9 < 12; c18_i9++) {
    c18_b_rv[c18_i9] = chartInstance->c18_rv[c18_i9];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c18_debug_family_names,
    c18_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_nargin, 0U, c18_e_sf_marshallOut,
    c18_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_nargout, 1U, c18_e_sf_marshallOut,
    c18_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c18_b_xb, 2U, c18_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c18_b_dxb, 3U, c18_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_b_rv, 4U, c18_b_sf_marshallOut,
    c18_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_b_b, 5U, c18_sf_marshallOut,
    c18_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c18_sfEvent, 2);
  for (c18_i10 = 0; c18_i10 < 3; c18_i10++) {
    c18_c_dxb[c18_i10] = c18_b_dxb[c18_i10 + 3];
  }

  c18_skew_sm(chartInstance, c18_c_dxb, c18_a);
  for (c18_i11 = 0; c18_i11 < 3; c18_i11++) {
    c18_d_dxb[c18_i11] = c18_b_dxb[c18_i11 + 3];
  }

  c18_skew_sm(chartInstance, c18_d_dxb, c18_c_b);
  c18_eml_scalar_eg(chartInstance);
  c18_eml_scalar_eg(chartInstance);
  c18_threshold(chartInstance);
  for (c18_i12 = 0; c18_i12 < 3; c18_i12++) {
    c18_i13 = 0;
    for (c18_i14 = 0; c18_i14 < 3; c18_i14++) {
      c18_y[c18_i13 + c18_i12] = 0.0;
      c18_i15 = 0;
      for (c18_i16 = 0; c18_i16 < 3; c18_i16++) {
        c18_y[c18_i13 + c18_i12] += c18_a[c18_i15 + c18_i12] * c18_c_b[c18_i16 +
          c18_i13];
        c18_i15 += 3;
      }

      c18_i13 += 3;
    }
  }

  for (c18_i17 = 0; c18_i17 < 4; c18_i17++) {
    c18_c_xb[c18_i17] = c18_b_xb[c18_i17 + 3];
  }

  for (c18_i18 = 0; c18_i18 < 3; c18_i18++) {
    c18_c_rv[c18_i18] = c18_b_rv[c18_i18];
  }

  c18_quatrot(chartInstance, c18_c_xb, c18_c_rv, c18_d_b);
  c18_b_eml_scalar_eg(chartInstance);
  c18_b_eml_scalar_eg(chartInstance);
  c18_threshold(chartInstance);
  for (c18_i19 = 0; c18_i19 < 3; c18_i19++) {
    c18_b_y[c18_i19] = 0.0;
    c18_i20 = 0;
    for (c18_i21 = 0; c18_i21 < 3; c18_i21++) {
      c18_b_y[c18_i19] += c18_y[c18_i20 + c18_i19] * c18_d_b[c18_i21];
      c18_i20 += 3;
    }
  }

  for (c18_i22 = 0; c18_i22 < 3; c18_i22++) {
    c18_e_dxb[c18_i22] = c18_b_dxb[c18_i22 + 3];
  }

  c18_skew_sm(chartInstance, c18_e_dxb, c18_a);
  for (c18_i23 = 0; c18_i23 < 3; c18_i23++) {
    c18_f_dxb[c18_i23] = c18_b_dxb[c18_i23 + 3];
  }

  c18_skew_sm(chartInstance, c18_f_dxb, c18_c_b);
  c18_eml_scalar_eg(chartInstance);
  c18_eml_scalar_eg(chartInstance);
  c18_threshold(chartInstance);
  for (c18_i24 = 0; c18_i24 < 3; c18_i24++) {
    c18_i25 = 0;
    for (c18_i26 = 0; c18_i26 < 3; c18_i26++) {
      c18_y[c18_i25 + c18_i24] = 0.0;
      c18_i27 = 0;
      for (c18_i28 = 0; c18_i28 < 3; c18_i28++) {
        c18_y[c18_i25 + c18_i24] += c18_a[c18_i27 + c18_i24] * c18_c_b[c18_i28 +
          c18_i25];
        c18_i27 += 3;
      }

      c18_i25 += 3;
    }
  }

  for (c18_i29 = 0; c18_i29 < 4; c18_i29++) {
    c18_d_xb[c18_i29] = c18_b_xb[c18_i29 + 3];
  }

  for (c18_i30 = 0; c18_i30 < 3; c18_i30++) {
    c18_d_rv[c18_i30] = c18_b_rv[c18_i30 + 3];
  }

  c18_quatrot(chartInstance, c18_d_xb, c18_d_rv, c18_d_b);
  c18_b_eml_scalar_eg(chartInstance);
  c18_b_eml_scalar_eg(chartInstance);
  c18_threshold(chartInstance);
  for (c18_i31 = 0; c18_i31 < 3; c18_i31++) {
    c18_c_y[c18_i31] = 0.0;
    c18_i32 = 0;
    for (c18_i33 = 0; c18_i33 < 3; c18_i33++) {
      c18_c_y[c18_i31] += c18_y[c18_i32 + c18_i31] * c18_d_b[c18_i33];
      c18_i32 += 3;
    }
  }

  for (c18_i34 = 0; c18_i34 < 3; c18_i34++) {
    c18_g_dxb[c18_i34] = c18_b_dxb[c18_i34 + 3];
  }

  c18_skew_sm(chartInstance, c18_g_dxb, c18_a);
  for (c18_i35 = 0; c18_i35 < 3; c18_i35++) {
    c18_h_dxb[c18_i35] = c18_b_dxb[c18_i35 + 3];
  }

  c18_skew_sm(chartInstance, c18_h_dxb, c18_c_b);
  c18_eml_scalar_eg(chartInstance);
  c18_eml_scalar_eg(chartInstance);
  c18_threshold(chartInstance);
  for (c18_i36 = 0; c18_i36 < 3; c18_i36++) {
    c18_i37 = 0;
    for (c18_i38 = 0; c18_i38 < 3; c18_i38++) {
      c18_y[c18_i37 + c18_i36] = 0.0;
      c18_i39 = 0;
      for (c18_i40 = 0; c18_i40 < 3; c18_i40++) {
        c18_y[c18_i37 + c18_i36] += c18_a[c18_i39 + c18_i36] * c18_c_b[c18_i40 +
          c18_i37];
        c18_i39 += 3;
      }

      c18_i37 += 3;
    }
  }

  for (c18_i41 = 0; c18_i41 < 4; c18_i41++) {
    c18_e_xb[c18_i41] = c18_b_xb[c18_i41 + 3];
  }

  for (c18_i42 = 0; c18_i42 < 3; c18_i42++) {
    c18_e_rv[c18_i42] = c18_b_rv[c18_i42 + 6];
  }

  c18_quatrot(chartInstance, c18_e_xb, c18_e_rv, c18_d_b);
  c18_b_eml_scalar_eg(chartInstance);
  c18_b_eml_scalar_eg(chartInstance);
  c18_threshold(chartInstance);
  for (c18_i43 = 0; c18_i43 < 3; c18_i43++) {
    c18_d_y[c18_i43] = 0.0;
    c18_i44 = 0;
    for (c18_i45 = 0; c18_i45 < 3; c18_i45++) {
      c18_d_y[c18_i43] += c18_y[c18_i44 + c18_i43] * c18_d_b[c18_i45];
      c18_i44 += 3;
    }
  }

  for (c18_i46 = 0; c18_i46 < 3; c18_i46++) {
    c18_x[c18_i46] = c18_b_dxb[c18_i46 + 3];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c18_b_debug_family_names,
    c18_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_b_nargin, 0U, c18_e_sf_marshallOut,
    c18_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_b_nargout, 1U, c18_e_sf_marshallOut,
    c18_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_x, 2U, c18_g_sf_marshallOut,
    c18_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_X, 3U, c18_f_sf_marshallOut,
    c18_d_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c18_sfEvent, 3);
  c18_X[0] = 0.0;
  c18_X[3] = -c18_x[2];
  c18_X[6] = c18_x[1];
  c18_X[1] = c18_x[2];
  c18_X[4] = 0.0;
  c18_X[7] = -c18_x[0];
  c18_X[2] = -c18_x[1];
  c18_X[5] = c18_x[0];
  c18_X[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c18_sfEvent, -3);
  _SFD_SYMBOL_SCOPE_POP();
  for (c18_i47 = 0; c18_i47 < 3; c18_i47++) {
    c18_i_dxb[c18_i47] = c18_b_dxb[c18_i47 + 3];
  }

  c18_skew_sm(chartInstance, c18_i_dxb, c18_a);
  for (c18_i48 = 0; c18_i48 < 9; c18_i48++) {
    c18_c_b[c18_i48] = c18_X[c18_i48];
  }

  c18_eml_scalar_eg(chartInstance);
  c18_eml_scalar_eg(chartInstance);
  c18_threshold(chartInstance);
  for (c18_i49 = 0; c18_i49 < 3; c18_i49++) {
    c18_i50 = 0;
    for (c18_i51 = 0; c18_i51 < 3; c18_i51++) {
      c18_y[c18_i50 + c18_i49] = 0.0;
      c18_i52 = 0;
      for (c18_i53 = 0; c18_i53 < 3; c18_i53++) {
        c18_y[c18_i50 + c18_i49] += c18_a[c18_i52 + c18_i49] * c18_c_b[c18_i53 +
          c18_i50];
        c18_i52 += 3;
      }

      c18_i50 += 3;
    }
  }

  for (c18_i54 = 0; c18_i54 < 4; c18_i54++) {
    c18_f_xb[c18_i54] = c18_b_xb[c18_i54 + 3];
  }

  for (c18_i55 = 0; c18_i55 < 3; c18_i55++) {
    c18_f_rv[c18_i55] = c18_b_rv[c18_i55 + 9];
  }

  c18_quatrot(chartInstance, c18_f_xb, c18_f_rv, c18_d_b);
  c18_b_eml_scalar_eg(chartInstance);
  c18_b_eml_scalar_eg(chartInstance);
  c18_threshold(chartInstance);
  for (c18_i56 = 0; c18_i56 < 3; c18_i56++) {
    c18_e_y[c18_i56] = 0.0;
    c18_i57 = 0;
    for (c18_i58 = 0; c18_i58 < 3; c18_i58++) {
      c18_e_y[c18_i56] += c18_y[c18_i57 + c18_i56] * c18_d_b[c18_i58];
      c18_i57 += 3;
    }
  }

  for (c18_i59 = 0; c18_i59 < 3; c18_i59++) {
    c18_b_b[c18_i59] = c18_b_y[c18_i59];
  }

  for (c18_i60 = 0; c18_i60 < 3; c18_i60++) {
    c18_b_b[c18_i60 + 3] = 0.0;
  }

  for (c18_i61 = 0; c18_i61 < 3; c18_i61++) {
    c18_b_b[c18_i61 + 6] = c18_c_y[c18_i61];
  }

  for (c18_i62 = 0; c18_i62 < 3; c18_i62++) {
    c18_b_b[c18_i62 + 9] = 0.0;
  }

  for (c18_i63 = 0; c18_i63 < 3; c18_i63++) {
    c18_b_b[c18_i63 + 12] = c18_d_y[c18_i63];
  }

  for (c18_i64 = 0; c18_i64 < 3; c18_i64++) {
    c18_b_b[c18_i64 + 15] = 0.0;
  }

  for (c18_i65 = 0; c18_i65 < 3; c18_i65++) {
    c18_b_b[c18_i65 + 18] = c18_e_y[c18_i65];
  }

  for (c18_i66 = 0; c18_i66 < 3; c18_i66++) {
    c18_b_b[c18_i66 + 21] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c18_sfEvent, -2);
  _SFD_SYMBOL_SCOPE_POP();
  for (c18_i67 = 0; c18_i67 < 24; c18_i67++) {
    (*chartInstance->c18_b)[c18_i67] = c18_b_b[c18_i67];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c18_sfEvent);
}

static void initSimStructsc18_DIPC(SFc18_DIPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c18_skew_sm(SFc18_DIPCInstanceStruct *chartInstance, real_T c18_x[3],
  real_T c18_X[9])
{
  uint32_T c18_debug_family_var_map[4];
  real_T c18_nargin = 1.0;
  real_T c18_nargout = 1.0;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c18_b_debug_family_names,
    c18_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_nargin, 0U, c18_e_sf_marshallOut,
    c18_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_nargout, 1U, c18_e_sf_marshallOut,
    c18_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_x, 2U, c18_g_sf_marshallOut,
    c18_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_X, 3U, c18_f_sf_marshallOut,
    c18_d_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c18_sfEvent, 3);
  c18_X[0] = 0.0;
  c18_X[3] = -c18_x[2];
  c18_X[6] = c18_x[1];
  c18_X[1] = c18_x[2];
  c18_X[4] = 0.0;
  c18_X[7] = -c18_x[0];
  c18_X[2] = -c18_x[1];
  c18_X[5] = c18_x[0];
  c18_X[8] = 0.0;
  _SFD_SCRIPT_CALL(0U, chartInstance->c18_sfEvent, -3);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c18_quatrot(SFc18_DIPCInstanceStruct *chartInstance, real_T c18_q[4],
  real_T c18_r[3], real_T c18_rw[3])
{
  uint32_T c18_debug_family_var_map[6];
  real_T c18_rwq[4];
  real_T c18_nargin = 2.0;
  real_T c18_nargout = 1.0;
  int32_T c18_i68;
  real_T c18_b_q[4];
  int32_T c18_k;
  real_T c18_b_k;
  real_T c18_dv2[4];
  int32_T c18_i69;
  int32_T c18_i70;
  real_T c18_c_q[4];
  real_T c18_dv3[4];
  int32_T c18_i71;
  real_T c18_d_q[4];
  int32_T c18_i72;
  real_T c18_dv4[4];
  int32_T c18_i73;
  int32_T c18_i74;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c18_c_debug_family_names,
    c18_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_rwq, 0U, c18_h_sf_marshallOut,
    c18_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_nargin, 1U, c18_e_sf_marshallOut,
    c18_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c18_nargout, 2U, c18_e_sf_marshallOut,
    c18_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_q, 3U, c18_h_sf_marshallOut,
    c18_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_r, 4U, c18_g_sf_marshallOut,
    c18_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c18_rw, 5U, c18_g_sf_marshallOut,
    c18_e_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c18_sfEvent, 4);
  for (c18_i68 = 0; c18_i68 < 4; c18_i68++) {
    c18_b_q[c18_i68] = c18_q[c18_i68];
  }

  for (c18_k = 0; c18_k < 3; c18_k++) {
    c18_b_k = 2.0 + (real_T)c18_k;
    c18_b_q[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      c18_b_k), 1, 4, 1, 0) - 1] = -c18_b_q[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", c18_b_k), 1, 4, 1, 0) - 1];
  }

  c18_dv2[0] = 0.0;
  for (c18_i69 = 0; c18_i69 < 3; c18_i69++) {
    c18_dv2[c18_i69 + 1] = c18_r[c18_i69];
  }

  for (c18_i70 = 0; c18_i70 < 4; c18_i70++) {
    c18_c_q[c18_i70] = c18_b_q[c18_i70];
  }

  c18_quatmultiply(chartInstance, c18_dv2, c18_c_q, c18_dv3);
  for (c18_i71 = 0; c18_i71 < 4; c18_i71++) {
    c18_d_q[c18_i71] = c18_q[c18_i71];
  }

  for (c18_i72 = 0; c18_i72 < 4; c18_i72++) {
    c18_dv4[c18_i72] = c18_dv3[c18_i72];
  }

  c18_quatmultiply(chartInstance, c18_d_q, c18_dv4, c18_b_q);
  for (c18_i73 = 0; c18_i73 < 4; c18_i73++) {
    c18_rwq[c18_i73] = c18_b_q[c18_i73];
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c18_sfEvent, 5);
  for (c18_i74 = 0; c18_i74 < 3; c18_i74++) {
    c18_rw[c18_i74] = c18_rwq[c18_i74 + 1];
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c18_sfEvent, -5);
  _SFD_SYMBOL_SCOPE_POP();
}

static void init_script_number_translation(uint32_T c18_machineNumber, uint32_T
  c18_chartNumber, uint32_T c18_instanceNumber)
{
  (void)c18_machineNumber;
  _SFD_SCRIPT_TRANSLATION(c18_chartNumber, c18_instanceNumber, 0U,
    sf_debug_get_script_id(
    "C:\\Users\\Martin\\Documents\\Git\\Simulink\\DIPC\\skew_sm.m"));
  _SFD_SCRIPT_TRANSLATION(c18_chartNumber, c18_instanceNumber, 1U,
    sf_debug_get_script_id(
    "C:\\Users\\Martin\\Documents\\Git\\Simulink\\DIPC\\quatrot.m"));
}

static const mxArray *c18_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i75;
  real_T c18_b_inData[24];
  int32_T c18_i76;
  real_T c18_u[24];
  const mxArray *c18_y = NULL;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  for (c18_i75 = 0; c18_i75 < 24; c18_i75++) {
    c18_b_inData[c18_i75] = (*(real_T (*)[24])c18_inData)[c18_i75];
  }

  for (c18_i76 = 0; c18_i76 < 24; c18_i76++) {
    c18_u[c18_i76] = c18_b_inData[c18_i76];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 1, 24), false);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, false);
  return c18_mxArrayOutData;
}

static void c18_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance, const
  mxArray *c18_b_b, const char_T *c18_identifier, real_T c18_y[24])
{
  emlrtMsgIdentifier c18_thisId;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_b_b), &c18_thisId, c18_y);
  sf_mex_destroy(&c18_b_b);
}

static void c18_b_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[24])
{
  real_T c18_dv5[24];
  int32_T c18_i77;
  (void)chartInstance;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), c18_dv5, 1, 0, 0U, 1, 0U, 1, 24);
  for (c18_i77 = 0; c18_i77 < 24; c18_i77++) {
    c18_y[c18_i77] = c18_dv5[c18_i77];
  }

  sf_mex_destroy(&c18_u);
}

static void c18_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_b_b;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  real_T c18_y[24];
  int32_T c18_i78;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_b_b = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_b_b), &c18_thisId, c18_y);
  sf_mex_destroy(&c18_b_b);
  for (c18_i78 = 0; c18_i78 < 24; c18_i78++) {
    (*(real_T (*)[24])c18_outData)[c18_i78] = c18_y[c18_i78];
  }

  sf_mex_destroy(&c18_mxArrayInData);
}

static const mxArray *c18_b_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i79;
  real_T c18_b_inData[12];
  int32_T c18_i80;
  real_T c18_u[12];
  const mxArray *c18_y = NULL;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  for (c18_i79 = 0; c18_i79 < 12; c18_i79++) {
    c18_b_inData[c18_i79] = (*(real_T (*)[12])c18_inData)[c18_i79];
  }

  for (c18_i80 = 0; c18_i80 < 12; c18_i80++) {
    c18_u[c18_i80] = c18_b_inData[c18_i80];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 1, 12), false);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, false);
  return c18_mxArrayOutData;
}

static void c18_c_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[12])
{
  real_T c18_dv6[12];
  int32_T c18_i81;
  (void)chartInstance;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), c18_dv6, 1, 0, 0U, 1, 0U, 1, 12);
  for (c18_i81 = 0; c18_i81 < 12; c18_i81++) {
    c18_y[c18_i81] = c18_dv6[c18_i81];
  }

  sf_mex_destroy(&c18_u);
}

static void c18_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_b_rv;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  real_T c18_y[12];
  int32_T c18_i82;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_b_rv = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_b_rv), &c18_thisId, c18_y);
  sf_mex_destroy(&c18_b_rv);
  for (c18_i82 = 0; c18_i82 < 12; c18_i82++) {
    (*(real_T (*)[12])c18_outData)[c18_i82] = c18_y[c18_i82];
  }

  sf_mex_destroy(&c18_mxArrayInData);
}

static const mxArray *c18_c_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i83;
  real_T c18_b_inData[6];
  int32_T c18_i84;
  real_T c18_u[6];
  const mxArray *c18_y = NULL;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  for (c18_i83 = 0; c18_i83 < 6; c18_i83++) {
    c18_b_inData[c18_i83] = (*(real_T (*)[6])c18_inData)[c18_i83];
  }

  for (c18_i84 = 0; c18_i84 < 6; c18_i84++) {
    c18_u[c18_i84] = c18_b_inData[c18_i84];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, false);
  return c18_mxArrayOutData;
}

static const mxArray *c18_d_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i85;
  real_T c18_b_inData[7];
  int32_T c18_i86;
  real_T c18_u[7];
  const mxArray *c18_y = NULL;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  for (c18_i85 = 0; c18_i85 < 7; c18_i85++) {
    c18_b_inData[c18_i85] = (*(real_T (*)[7])c18_inData)[c18_i85];
  }

  for (c18_i86 = 0; c18_i86 < 7; c18_i86++) {
    c18_u[c18_i86] = c18_b_inData[c18_i86];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 1, 7), false);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, false);
  return c18_mxArrayOutData;
}

static const mxArray *c18_e_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  real_T c18_u;
  const mxArray *c18_y = NULL;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  c18_u = *(real_T *)c18_inData;
  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", &c18_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, false);
  return c18_mxArrayOutData;
}

static real_T c18_d_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId)
{
  real_T c18_y;
  real_T c18_d0;
  (void)chartInstance;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), &c18_d0, 1, 0, 0U, 0, 0U, 0);
  c18_y = c18_d0;
  sf_mex_destroy(&c18_u);
  return c18_y;
}

static void c18_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_nargout;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  real_T c18_y;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_nargout = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_y = c18_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_nargout),
    &c18_thisId);
  sf_mex_destroy(&c18_nargout);
  *(real_T *)c18_outData = c18_y;
  sf_mex_destroy(&c18_mxArrayInData);
}

static const mxArray *c18_f_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i87;
  int32_T c18_i88;
  int32_T c18_i89;
  real_T c18_b_inData[9];
  int32_T c18_i90;
  int32_T c18_i91;
  int32_T c18_i92;
  real_T c18_u[9];
  const mxArray *c18_y = NULL;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  c18_i87 = 0;
  for (c18_i88 = 0; c18_i88 < 3; c18_i88++) {
    for (c18_i89 = 0; c18_i89 < 3; c18_i89++) {
      c18_b_inData[c18_i89 + c18_i87] = (*(real_T (*)[9])c18_inData)[c18_i89 +
        c18_i87];
    }

    c18_i87 += 3;
  }

  c18_i90 = 0;
  for (c18_i91 = 0; c18_i91 < 3; c18_i91++) {
    for (c18_i92 = 0; c18_i92 < 3; c18_i92++) {
      c18_u[c18_i92 + c18_i90] = c18_b_inData[c18_i92 + c18_i90];
    }

    c18_i90 += 3;
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, false);
  return c18_mxArrayOutData;
}

static void c18_e_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[9])
{
  real_T c18_dv7[9];
  int32_T c18_i93;
  (void)chartInstance;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), c18_dv7, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c18_i93 = 0; c18_i93 < 9; c18_i93++) {
    c18_y[c18_i93] = c18_dv7[c18_i93];
  }

  sf_mex_destroy(&c18_u);
}

static void c18_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_X;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  real_T c18_y[9];
  int32_T c18_i94;
  int32_T c18_i95;
  int32_T c18_i96;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_X = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_X), &c18_thisId, c18_y);
  sf_mex_destroy(&c18_X);
  c18_i94 = 0;
  for (c18_i95 = 0; c18_i95 < 3; c18_i95++) {
    for (c18_i96 = 0; c18_i96 < 3; c18_i96++) {
      (*(real_T (*)[9])c18_outData)[c18_i96 + c18_i94] = c18_y[c18_i96 + c18_i94];
    }

    c18_i94 += 3;
  }

  sf_mex_destroy(&c18_mxArrayInData);
}

static const mxArray *c18_g_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i97;
  real_T c18_b_inData[3];
  int32_T c18_i98;
  real_T c18_u[3];
  const mxArray *c18_y = NULL;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  for (c18_i97 = 0; c18_i97 < 3; c18_i97++) {
    c18_b_inData[c18_i97] = (*(real_T (*)[3])c18_inData)[c18_i97];
  }

  for (c18_i98 = 0; c18_i98 < 3; c18_i98++) {
    c18_u[c18_i98] = c18_b_inData[c18_i98];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, false);
  return c18_mxArrayOutData;
}

static void c18_f_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[3])
{
  real_T c18_dv8[3];
  int32_T c18_i99;
  (void)chartInstance;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), c18_dv8, 1, 0, 0U, 1, 0U, 1, 3);
  for (c18_i99 = 0; c18_i99 < 3; c18_i99++) {
    c18_y[c18_i99] = c18_dv8[c18_i99];
  }

  sf_mex_destroy(&c18_u);
}

static void c18_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_x;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  real_T c18_y[3];
  int32_T c18_i100;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_x = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_x), &c18_thisId, c18_y);
  sf_mex_destroy(&c18_x);
  for (c18_i100 = 0; c18_i100 < 3; c18_i100++) {
    (*(real_T (*)[3])c18_outData)[c18_i100] = c18_y[c18_i100];
  }

  sf_mex_destroy(&c18_mxArrayInData);
}

static const mxArray *c18_h_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_i101;
  real_T c18_b_inData[4];
  int32_T c18_i102;
  real_T c18_u[4];
  const mxArray *c18_y = NULL;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  for (c18_i101 = 0; c18_i101 < 4; c18_i101++) {
    c18_b_inData[c18_i101] = (*(real_T (*)[4])c18_inData)[c18_i101];
  }

  for (c18_i102 = 0; c18_i102 < 4; c18_i102++) {
    c18_u[c18_i102] = c18_b_inData[c18_i102];
  }

  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, false);
  return c18_mxArrayOutData;
}

static void c18_g_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId, real_T c18_y[4])
{
  real_T c18_dv9[4];
  int32_T c18_i103;
  (void)chartInstance;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), c18_dv9, 1, 0, 0U, 1, 0U, 1, 4);
  for (c18_i103 = 0; c18_i103 < 4; c18_i103++) {
    c18_y[c18_i103] = c18_dv9[c18_i103];
  }

  sf_mex_destroy(&c18_u);
}

static void c18_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_q;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  real_T c18_y[4];
  int32_T c18_i104;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_q = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_q), &c18_thisId, c18_y);
  sf_mex_destroy(&c18_q);
  for (c18_i104 = 0; c18_i104 < 4; c18_i104++) {
    (*(real_T (*)[4])c18_outData)[c18_i104] = c18_y[c18_i104];
  }

  sf_mex_destroy(&c18_mxArrayInData);
}

const mxArray *sf_c18_DIPC_get_eml_resolved_functions_info(void)
{
  const mxArray *c18_nameCaptureInfo = NULL;
  c18_nameCaptureInfo = NULL;
  sf_mex_assign(&c18_nameCaptureInfo, sf_mex_createstruct("structure", 2, 25, 1),
                false);
  c18_info_helper(&c18_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c18_nameCaptureInfo);
  return c18_nameCaptureInfo;
}

static void c18_info_helper(const mxArray **c18_info)
{
  const mxArray *c18_rhs0 = NULL;
  const mxArray *c18_lhs0 = NULL;
  const mxArray *c18_rhs1 = NULL;
  const mxArray *c18_lhs1 = NULL;
  const mxArray *c18_rhs2 = NULL;
  const mxArray *c18_lhs2 = NULL;
  const mxArray *c18_rhs3 = NULL;
  const mxArray *c18_lhs3 = NULL;
  const mxArray *c18_rhs4 = NULL;
  const mxArray *c18_lhs4 = NULL;
  const mxArray *c18_rhs5 = NULL;
  const mxArray *c18_lhs5 = NULL;
  const mxArray *c18_rhs6 = NULL;
  const mxArray *c18_lhs6 = NULL;
  const mxArray *c18_rhs7 = NULL;
  const mxArray *c18_lhs7 = NULL;
  const mxArray *c18_rhs8 = NULL;
  const mxArray *c18_lhs8 = NULL;
  const mxArray *c18_rhs9 = NULL;
  const mxArray *c18_lhs9 = NULL;
  const mxArray *c18_rhs10 = NULL;
  const mxArray *c18_lhs10 = NULL;
  const mxArray *c18_rhs11 = NULL;
  const mxArray *c18_lhs11 = NULL;
  const mxArray *c18_rhs12 = NULL;
  const mxArray *c18_lhs12 = NULL;
  const mxArray *c18_rhs13 = NULL;
  const mxArray *c18_lhs13 = NULL;
  const mxArray *c18_rhs14 = NULL;
  const mxArray *c18_lhs14 = NULL;
  const mxArray *c18_rhs15 = NULL;
  const mxArray *c18_lhs15 = NULL;
  const mxArray *c18_rhs16 = NULL;
  const mxArray *c18_lhs16 = NULL;
  const mxArray *c18_rhs17 = NULL;
  const mxArray *c18_lhs17 = NULL;
  const mxArray *c18_rhs18 = NULL;
  const mxArray *c18_lhs18 = NULL;
  const mxArray *c18_rhs19 = NULL;
  const mxArray *c18_lhs19 = NULL;
  const mxArray *c18_rhs20 = NULL;
  const mxArray *c18_lhs20 = NULL;
  const mxArray *c18_rhs21 = NULL;
  const mxArray *c18_lhs21 = NULL;
  const mxArray *c18_rhs22 = NULL;
  const mxArray *c18_lhs22 = NULL;
  const mxArray *c18_rhs23 = NULL;
  const mxArray *c18_lhs23 = NULL;
  const mxArray *c18_rhs24 = NULL;
  const mxArray *c18_lhs24 = NULL;
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("skew_sm"), "name", "name", 0);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[E]C:/Users/Martin/Documents/Git/Simulink/DIPC/skew_sm.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1445505143U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c18_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(""), "context", "context", 1);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 1);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1383902494U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c18_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 2);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 2);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1395957056U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c18_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 3);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1323195778U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c18_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 4);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 4);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1376005888U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c18_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 5);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410832970U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c18_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 6);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  6);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1376005890U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c18_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 7);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410832972U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c18_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 8);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410832970U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c18_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 9);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 9);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410832970U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c18_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 10);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "coder.internal.blas.threshold"), "name", "name", 10);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410832972U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c18_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 11);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 11);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1393356058U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c18_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 12);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410832970U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c18_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 13);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "coder.internal.refblas.xgemm"), "name", "name", 13);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410832972U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c18_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(""), "context", "context", 14);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("quatrot"), "name", "name",
                  14);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[E]C:/Users/Martin/Documents/Git/Simulink/DIPC/quatrot.m"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1446631716U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c18_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[E]C:/Users/Martin/Documents/Git/Simulink/DIPC/quatrot.m"), "context",
                  "context", 15);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("quatconj"), "name", "name",
                  15);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/aeroblks/eml/quatconj.p"), "resolved", "resolved",
                  15);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410808258U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c18_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[E]C:/Users/Martin/Documents/Git/Simulink/DIPC/quatrot.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("quatmultiply"), "name",
                  "name", 16);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/aeroblks/eml/quatmultiply.p"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410808258U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c18_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/aeroblks/eml/quatmultiply.p"), "context",
                  "context", 17);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("max"), "name", "name", 17);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1311280516U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c18_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 18);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1378321184U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c18_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 19);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 19);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1376005888U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c18_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 20);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 20);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1376005888U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c18_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 21);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 21);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1410832970U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c18_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 22);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 22);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1323195778U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c18_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 23);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 23);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 23);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1376005888U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c18_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 24);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 24);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c18_info, c18_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(1395957056U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c18_info, c18_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c18_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c18_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c18_info, sf_mex_duplicatearraysafe(&c18_lhs24), "lhs", "lhs",
                  24);
  sf_mex_destroy(&c18_rhs0);
  sf_mex_destroy(&c18_lhs0);
  sf_mex_destroy(&c18_rhs1);
  sf_mex_destroy(&c18_lhs1);
  sf_mex_destroy(&c18_rhs2);
  sf_mex_destroy(&c18_lhs2);
  sf_mex_destroy(&c18_rhs3);
  sf_mex_destroy(&c18_lhs3);
  sf_mex_destroy(&c18_rhs4);
  sf_mex_destroy(&c18_lhs4);
  sf_mex_destroy(&c18_rhs5);
  sf_mex_destroy(&c18_lhs5);
  sf_mex_destroy(&c18_rhs6);
  sf_mex_destroy(&c18_lhs6);
  sf_mex_destroy(&c18_rhs7);
  sf_mex_destroy(&c18_lhs7);
  sf_mex_destroy(&c18_rhs8);
  sf_mex_destroy(&c18_lhs8);
  sf_mex_destroy(&c18_rhs9);
  sf_mex_destroy(&c18_lhs9);
  sf_mex_destroy(&c18_rhs10);
  sf_mex_destroy(&c18_lhs10);
  sf_mex_destroy(&c18_rhs11);
  sf_mex_destroy(&c18_lhs11);
  sf_mex_destroy(&c18_rhs12);
  sf_mex_destroy(&c18_lhs12);
  sf_mex_destroy(&c18_rhs13);
  sf_mex_destroy(&c18_lhs13);
  sf_mex_destroy(&c18_rhs14);
  sf_mex_destroy(&c18_lhs14);
  sf_mex_destroy(&c18_rhs15);
  sf_mex_destroy(&c18_lhs15);
  sf_mex_destroy(&c18_rhs16);
  sf_mex_destroy(&c18_lhs16);
  sf_mex_destroy(&c18_rhs17);
  sf_mex_destroy(&c18_lhs17);
  sf_mex_destroy(&c18_rhs18);
  sf_mex_destroy(&c18_lhs18);
  sf_mex_destroy(&c18_rhs19);
  sf_mex_destroy(&c18_lhs19);
  sf_mex_destroy(&c18_rhs20);
  sf_mex_destroy(&c18_lhs20);
  sf_mex_destroy(&c18_rhs21);
  sf_mex_destroy(&c18_lhs21);
  sf_mex_destroy(&c18_rhs22);
  sf_mex_destroy(&c18_lhs22);
  sf_mex_destroy(&c18_rhs23);
  sf_mex_destroy(&c18_lhs23);
  sf_mex_destroy(&c18_rhs24);
  sf_mex_destroy(&c18_lhs24);
}

static const mxArray *c18_emlrt_marshallOut(const char * c18_u)
{
  const mxArray *c18_y = NULL;
  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", c18_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c18_u)), false);
  return c18_y;
}

static const mxArray *c18_b_emlrt_marshallOut(const uint32_T c18_u)
{
  const mxArray *c18_y = NULL;
  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", &c18_u, 7, 0U, 0U, 0U, 0), false);
  return c18_y;
}

static void c18_eml_scalar_eg(SFc18_DIPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c18_threshold(SFc18_DIPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c18_quatmultiply(SFc18_DIPCInstanceStruct *chartInstance, real_T
  c18_q[4], real_T c18_r[4], real_T c18_qout[4])
{
  real_T c18_q1;
  real_T c18_q2;
  real_T c18_q3;
  real_T c18_q4;
  real_T c18_r1;
  real_T c18_r2;
  real_T c18_r3;
  real_T c18_r4;
  (void)chartInstance;
  c18_q1 = c18_q[0];
  c18_q2 = c18_q[1];
  c18_q3 = c18_q[2];
  c18_q4 = c18_q[3];
  c18_r1 = c18_r[0];
  c18_r2 = c18_r[1];
  c18_r3 = c18_r[2];
  c18_r4 = c18_r[3];
  c18_qout[0] = ((c18_q1 * c18_r1 - c18_q2 * c18_r2) - c18_q3 * c18_r3) - c18_q4
    * c18_r4;
  c18_qout[1] = (c18_q1 * c18_r2 + c18_r1 * c18_q2) + (c18_q3 * c18_r4 - c18_q4 *
    c18_r3);
  c18_qout[2] = (c18_q1 * c18_r3 + c18_r1 * c18_q3) + (c18_q4 * c18_r2 - c18_q2 *
    c18_r4);
  c18_qout[3] = (c18_q1 * c18_r4 + c18_r1 * c18_q4) + (c18_q2 * c18_r3 - c18_q3 *
    c18_r2);
}

static void c18_b_eml_scalar_eg(SFc18_DIPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c18_i_sf_marshallOut(void *chartInstanceVoid, void
  *c18_inData)
{
  const mxArray *c18_mxArrayOutData = NULL;
  int32_T c18_u;
  const mxArray *c18_y = NULL;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_mxArrayOutData = NULL;
  c18_u = *(int32_T *)c18_inData;
  c18_y = NULL;
  sf_mex_assign(&c18_y, sf_mex_create("y", &c18_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c18_mxArrayOutData, c18_y, false);
  return c18_mxArrayOutData;
}

static int32_T c18_h_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId)
{
  int32_T c18_y;
  int32_T c18_i105;
  (void)chartInstance;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), &c18_i105, 1, 6, 0U, 0, 0U, 0);
  c18_y = c18_i105;
  sf_mex_destroy(&c18_u);
  return c18_y;
}

static void c18_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c18_mxArrayInData, const char_T *c18_varName, void *c18_outData)
{
  const mxArray *c18_b_sfEvent;
  const char_T *c18_identifier;
  emlrtMsgIdentifier c18_thisId;
  int32_T c18_y;
  SFc18_DIPCInstanceStruct *chartInstance;
  chartInstance = (SFc18_DIPCInstanceStruct *)chartInstanceVoid;
  c18_b_sfEvent = sf_mex_dup(c18_mxArrayInData);
  c18_identifier = c18_varName;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_y = c18_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c18_b_sfEvent),
    &c18_thisId);
  sf_mex_destroy(&c18_b_sfEvent);
  *(int32_T *)c18_outData = c18_y;
  sf_mex_destroy(&c18_mxArrayInData);
}

static uint8_T c18_i_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_b_is_active_c18_DIPC, const char_T *c18_identifier)
{
  uint8_T c18_y;
  emlrtMsgIdentifier c18_thisId;
  c18_thisId.fIdentifier = c18_identifier;
  c18_thisId.fParent = NULL;
  c18_y = c18_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c18_b_is_active_c18_DIPC), &c18_thisId);
  sf_mex_destroy(&c18_b_is_active_c18_DIPC);
  return c18_y;
}

static uint8_T c18_j_emlrt_marshallIn(SFc18_DIPCInstanceStruct *chartInstance,
  const mxArray *c18_u, const emlrtMsgIdentifier *c18_parentId)
{
  uint8_T c18_y;
  uint8_T c18_u0;
  (void)chartInstance;
  sf_mex_import(c18_parentId, sf_mex_dup(c18_u), &c18_u0, 1, 3, 0U, 0, 0U, 0);
  c18_y = c18_u0;
  sf_mex_destroy(&c18_u);
  return c18_y;
}

static void init_dsm_address_info(SFc18_DIPCInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc18_DIPCInstanceStruct *chartInstance)
{
  chartInstance->c18_xb = (real_T (*)[7])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c18_dxb = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c18_b = (real_T (*)[24])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c18_DIPC_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(74075701U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4133096892U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3158474661U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2998453089U);
}

mxArray* sf_c18_DIPC_get_post_codegen_info(void);
mxArray *sf_c18_DIPC_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("x22FdyYcn0UzAZoPJpjgoE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(12);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(24);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c18_DIPC_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c18_DIPC_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c18_DIPC_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c18_DIPC_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c18_DIPC_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c18_DIPC(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"b\",},{M[8],M[0],T\"is_active_c18_DIPC\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c18_DIPC_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc18_DIPCInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc18_DIPCInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _DIPCMachineNumber_,
           18,
           1,
           1,
           0,
           4,
           0,
           0,
           0,
           0,
           2,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_DIPCMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_DIPCMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _DIPCMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"xb");
          _SFD_SET_DATA_PROPS(1,1,1,0,"dxb");
          _SFD_SET_DATA_PROPS(2,2,0,1,"b");
          _SFD_SET_DATA_PROPS(3,10,0,0,"rv");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,379);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"skew_sm",0,-1,127);
        _SFD_CV_INIT_SCRIPT(1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"quatrot",0,-1,191);

        {
          unsigned int dimVector[1];
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c18_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c18_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 24;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c18_sf_marshallOut,(MexInFcnForType)
            c18_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 12;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c18_b_sf_marshallOut,(MexInFcnForType)
            c18_b_sf_marshallIn);
        }

        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c18_xb);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c18_dxb);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c18_b);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c18_rv);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _DIPCMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "Ksm1Abe5A3Ik7fHLDWlJ3D";
}

static void sf_opaque_initialize_c18_DIPC(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc18_DIPCInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c18_DIPC((SFc18_DIPCInstanceStruct*) chartInstanceVar);
  initialize_c18_DIPC((SFc18_DIPCInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c18_DIPC(void *chartInstanceVar)
{
  enable_c18_DIPC((SFc18_DIPCInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c18_DIPC(void *chartInstanceVar)
{
  disable_c18_DIPC((SFc18_DIPCInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c18_DIPC(void *chartInstanceVar)
{
  sf_gateway_c18_DIPC((SFc18_DIPCInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c18_DIPC(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c18_DIPC((SFc18_DIPCInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c18_DIPC(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c18_DIPC((SFc18_DIPCInstanceStruct*)chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c18_DIPC(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc18_DIPCInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_DIPC_optimization_info();
    }

    finalize_c18_DIPC((SFc18_DIPCInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc18_DIPC((SFc18_DIPCInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c18_DIPC(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c18_DIPC((SFc18_DIPCInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c18_DIPC(SimStruct *S)
{
  /* Actual parameters from chart:
     rv
   */
  const char_T *rtParamNames[] = { "rv" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for rv*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_DIPC_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      18);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,18,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,18,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,18);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,18,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,18,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,18);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2565423341U));
  ssSetChecksum1(S,(3579560012U));
  ssSetChecksum2(S,(3164148017U));
  ssSetChecksum3(S,(4153741316U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c18_DIPC(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c18_DIPC(SimStruct *S)
{
  SFc18_DIPCInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc18_DIPCInstanceStruct *)utMalloc(sizeof
    (SFc18_DIPCInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc18_DIPCInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c18_DIPC;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c18_DIPC;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c18_DIPC;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c18_DIPC;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c18_DIPC;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c18_DIPC;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c18_DIPC;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c18_DIPC;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c18_DIPC;
  chartInstance->chartInfo.mdlStart = mdlStart_c18_DIPC;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c18_DIPC;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c18_DIPC_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c18_DIPC(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c18_DIPC(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c18_DIPC(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c18_DIPC_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
