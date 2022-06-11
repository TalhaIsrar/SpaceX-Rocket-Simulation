/* Include files */

#include <stddef.h>
#include "blas.h"
#include "flight_sim_sfun.h"
#include "c1_flight_sim.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "flight_sim_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[9] = { "t_c", "nargin", "nargout", "h",
  "T", "gam", "tht_c", "flag", "f" };

/* Function Declarations */
static void initialize_c1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance);
static void initialize_params_c1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance);
static void enable_c1_flight_sim(SFc1_flight_simInstanceStruct *chartInstance);
static void disable_c1_flight_sim(SFc1_flight_simInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_flight_sim(SFc1_flight_simInstanceStruct *
  chartInstance);
static void set_sim_state_c1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_flight_sim(SFc1_flight_simInstanceStruct *chartInstance);
static void sf_c1_flight_sim(SFc1_flight_simInstanceStruct *chartInstance);
static void initSimStructsc1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_flight_simInstanceStruct *chartInstance,
  const mxArray *c1_b_f, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_flight_simInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_flight_simInstanceStruct *chartInstance,
  const mxArray *c1_flag, const char_T *c1_identifier);
static real_T c1_d_emlrt_marshallIn(SFc1_flight_simInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(const mxArray **c1_info);
static const mxArray *c1_emlrt_marshallOut(char * c1_u);
static const mxArray *c1_b_emlrt_marshallOut(uint32_T c1_u);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_e_emlrt_marshallIn(SFc1_flight_simInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_f_emlrt_marshallIn(SFc1_flight_simInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_flight_sim, const char_T
  *c1_identifier);
static uint8_T c1_g_emlrt_marshallIn(SFc1_flight_simInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_flight_simInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_f_not_empty = FALSE;
  chartInstance->c1_is_active_c1_flight_sim = 0U;
}

static void initialize_params_c1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance)
{
}

static void enable_c1_flight_sim(SFc1_flight_simInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_flight_sim(SFc1_flight_simInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_flight_sim(SFc1_flight_simInstanceStruct *
  chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  uint8_T c1_d_hoistedGlobal;
  uint8_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  real_T *c1_flag;
  real_T *c1_tht_c;
  c1_flag = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_tht_c = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(4), FALSE);
  c1_hoistedGlobal = *c1_flag;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_tht_c;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = chartInstance->c1_f;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  if (!chartInstance->c1_f_not_empty) {
    sf_mex_assign(&c1_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = chartInstance->c1_is_active_c1_flight_sim;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T *c1_flag;
  real_T *c1_tht_c;
  c1_flag = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_tht_c = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_flag = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    0)), "flag");
  *c1_tht_c = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 1)), "tht_c");
  chartInstance->c1_f = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 2)), "f");
  chartInstance->c1_is_active_c1_flight_sim = c1_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 3)),
     "is_active_c1_flight_sim");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_flight_sim(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_flight_sim(SFc1_flight_simInstanceStruct *chartInstance)
{
}

static void sf_c1_flight_sim(SFc1_flight_simInstanceStruct *chartInstance)
{
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_h;
  real_T c1_T;
  real_T c1_gam;
  uint32_T c1_debug_family_var_map[9];
  real_T c1_t_c;
  real_T c1_nargin = 3.0;
  real_T c1_nargout = 2.0;
  real_T c1_tht_c;
  real_T c1_flag;
  real_T *c1_b_flag;
  real_T *c1_b_tht_c;
  real_T *c1_b_gam;
  real_T *c1_b_T;
  real_T *c1_b_h;
  boolean_T guard1 = FALSE;
  c1_b_gam = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_T = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_flag = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_tht_c = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_h = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c1_b_h, 0U);
  _SFD_DATA_RANGE_CHECK(*c1_b_tht_c, 1U);
  _SFD_DATA_RANGE_CHECK(*c1_b_flag, 2U);
  _SFD_DATA_RANGE_CHECK(*c1_b_T, 3U);
  _SFD_DATA_RANGE_CHECK(*c1_b_gam, 4U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_h;
  c1_b_hoistedGlobal = *c1_b_T;
  c1_c_hoistedGlobal = *c1_b_gam;
  c1_h = c1_hoistedGlobal;
  c1_T = c1_b_hoistedGlobal;
  c1_gam = c1_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_t_c, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 1U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 2U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_h, 3U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_T, 4U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_gam, 5U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_tht_c, 6U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_flag, 7U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_f, 8U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c1_f_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
    chartInstance->c1_f = 0.0;
    chartInstance->c1_f_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  if (CV_EML_IF(0, 1, 1, c1_T <= 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
    c1_t_c = c1_gam + 3.1415926535897931;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
    if (CV_EML_IF(0, 1, 2, c1_t_c > 3.1415926535897931)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
      c1_t_c = 3.1415926535897931;
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
    chartInstance->c1_f = 1.0;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
    guard1 = FALSE;
    if (CV_EML_COND(0, 1, 0, c1_T <= 0.0)) {
      if (CV_EML_COND(0, 1, 1, c1_h < 1000.0)) {
        CV_EML_MCDC(0, 1, 0, TRUE);
        CV_EML_IF(0, 1, 3, TRUE);
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
        c1_t_c = 1.5707963267948966;
      } else {
        guard1 = TRUE;
      }
    } else {
      guard1 = TRUE;
    }

    if (guard1 == TRUE) {
      CV_EML_MCDC(0, 1, 0, FALSE);
      CV_EML_IF(0, 1, 3, FALSE);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
      c1_t_c = c1_gam;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
  c1_flag = chartInstance->c1_f;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
  c1_tht_c = c1_t_c;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -23);
  _SFD_SYMBOL_SCOPE_POP();
  *c1_b_tht_c = c1_tht_c;
  *c1_b_flag = c1_flag;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_flight_simMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc1_flight_sim(SFc1_flight_simInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc1_flight_simInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_f_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_flight_simInstanceStruct *chartInstance,
  const mxArray *c1_b_f, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_f), &c1_thisId);
  sf_mex_destroy(&c1_b_f);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_flight_simInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_f_not_empty = FALSE;
  } else {
    chartInstance->c1_f_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d0;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_f;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc1_flight_simInstanceStruct *)chartInstanceVoid;
  c1_b_f = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_f), &c1_thisId);
  sf_mex_destroy(&c1_b_f);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc1_flight_simInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_flight_simInstanceStruct *chartInstance,
  const mxArray *c1_flag, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_flag), &c1_thisId);
  sf_mex_destroy(&c1_flag);
  return c1_y;
}

static real_T c1_d_emlrt_marshallIn(SFc1_flight_simInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d1;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d1, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d1;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_flag;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc1_flight_simInstanceStruct *)chartInstanceVoid;
  c1_flag = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_flag), &c1_thisId);
  sf_mex_destroy(&c1_flag);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_flight_sim_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_createstruct("structure", 2, 5, 1),
                FALSE);
  c1_info_helper(&c1_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs0 = NULL;
  const mxArray *c1_lhs0 = NULL;
  const mxArray *c1_rhs1 = NULL;
  const mxArray *c1_lhs1 = NULL;
  const mxArray *c1_rhs2 = NULL;
  const mxArray *c1_lhs2 = NULL;
  const mxArray *c1_rhs3 = NULL;
  const mxArray *c1_lhs3 = NULL;
  const mxArray *c1_rhs4 = NULL;
  const mxArray *c1_lhs4 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373295708U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319719166U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c1_rhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("rdivide"), "name", "name", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363699480U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c1_rhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363700156U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c1_rhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286807996U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c1_rhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_div"), "name", "name", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363699466U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c1_rhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs4), "lhs", "lhs", 4);
  sf_mex_destroy(&c1_rhs0);
  sf_mex_destroy(&c1_lhs0);
  sf_mex_destroy(&c1_rhs1);
  sf_mex_destroy(&c1_lhs1);
  sf_mex_destroy(&c1_rhs2);
  sf_mex_destroy(&c1_lhs2);
  sf_mex_destroy(&c1_rhs3);
  sf_mex_destroy(&c1_lhs3);
  sf_mex_destroy(&c1_rhs4);
  sf_mex_destroy(&c1_lhs4);
}

static const mxArray *c1_emlrt_marshallOut(char * c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c1_u)), FALSE);
  return c1_y;
}

static const mxArray *c1_b_emlrt_marshallOut(uint32_T c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 7, 0U, 0U, 0U, 0), FALSE);
  return c1_y;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc1_flight_simInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_e_emlrt_marshallIn(SFc1_flight_simInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i0, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc1_flight_simInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_flight_simInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_flight_sim, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_flight_sim), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_flight_sim);
  return c1_y;
}

static uint8_T c1_g_emlrt_marshallIn(SFc1_flight_simInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_flight_simInstanceStruct *chartInstance)
{
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

void sf_c1_flight_sim_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(82075940U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2122585575U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3453841952U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2270898019U);
}

mxArray *sf_c1_flight_sim_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("5JyXrkPDCe4H0yWl72ceoG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_flight_sim_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_flight_sim_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c1_flight_sim(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[6],T\"flag\",},{M[1],M[5],T\"tht_c\",},{M[4],M[0],T\"f\",S'l','i','p'{{M1x2[60 61],M[0],}}},{M[8],M[0],T\"is_active_c1_flight_sim\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_flight_sim_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_flight_simInstanceStruct *chartInstance;
    chartInstance = (SFc1_flight_simInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _flight_simMachineNumber_,
           1,
           1,
           1,
           5,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_flight_simMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_flight_simMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _flight_simMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"h");
          _SFD_SET_DATA_PROPS(1,2,0,1,"tht_c");
          _SFD_SET_DATA_PROPS(2,2,0,1,"flag");
          _SFD_SET_DATA_PROPS(3,1,1,0,"T");
          _SFD_SET_DATA_PROPS(4,1,1,0,"gam");
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
        _SFD_CV_INIT_EML(0,1,1,4,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,256);
        _SFD_CV_INIT_EML_IF(0,1,0,63,76,-1,91);
        _SFD_CV_INIT_EML_IF(0,1,1,93,100,170,231);
        _SFD_CV_INIT_EML_IF(0,1,2,123,132,-1,158);
        _SFD_CV_INIT_EML_IF(0,1,3,170,191,208,231);

        {
          static int condStart[] = { 177, 185 };

          static int condEnd[] = { 181, 191 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,177,191,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c1_h;
          real_T *c1_tht_c;
          real_T *c1_flag;
          real_T *c1_T;
          real_T *c1_gam;
          c1_gam = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c1_T = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_flag = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c1_tht_c = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_h = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_h);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_tht_c);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_flag);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_T);
          _SFD_SET_DATA_VALUE_PTR(4U, c1_gam);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _flight_simMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "gdBmex8Yxuy3M4kyz6SLOE";
}

static void sf_opaque_initialize_c1_flight_sim(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_flight_simInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c1_flight_sim((SFc1_flight_simInstanceStruct*)
    chartInstanceVar);
  initialize_c1_flight_sim((SFc1_flight_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_flight_sim(void *chartInstanceVar)
{
  enable_c1_flight_sim((SFc1_flight_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_flight_sim(void *chartInstanceVar)
{
  disable_c1_flight_sim((SFc1_flight_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_flight_sim(void *chartInstanceVar)
{
  sf_c1_flight_sim((SFc1_flight_simInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_flight_sim(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_flight_sim
    ((SFc1_flight_simInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_flight_sim();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_flight_sim(SimStruct* S, const mxArray *
  st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_flight_sim();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_flight_sim((SFc1_flight_simInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_flight_sim(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_flight_sim(S);
}

static void sf_opaque_set_sim_state_c1_flight_sim(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c1_flight_sim(S, st);
}

static void sf_opaque_terminate_c1_flight_sim(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_flight_simInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_flight_sim_optimization_info();
    }

    finalize_c1_flight_sim((SFc1_flight_simInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_flight_sim((SFc1_flight_simInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_flight_sim(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_flight_sim((SFc1_flight_simInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_flight_sim(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_flight_sim_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4269323727U));
  ssSetChecksum1(S,(4031782063U));
  ssSetChecksum2(S,(3256390431U));
  ssSetChecksum3(S,(4101210212U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_flight_sim(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_flight_sim(SimStruct *S)
{
  SFc1_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc1_flight_simInstanceStruct *)utMalloc(sizeof
    (SFc1_flight_simInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_flight_simInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_flight_sim;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_flight_sim;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_flight_sim;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_flight_sim;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_flight_sim;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_flight_sim;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_flight_sim;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_flight_sim;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_flight_sim;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_flight_sim;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_flight_sim;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_flight_sim_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_flight_sim(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_flight_sim(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_flight_sim(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_flight_sim_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
