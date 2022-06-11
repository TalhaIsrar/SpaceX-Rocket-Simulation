/* Include files */

#include <stddef.h>
#include "blas.h"
#include "flight_sim_sfun.h"
#include "c6_flight_sim.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "flight_sim_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c6_debug_family_names[12] = { "CD", "Di", "A", "T", "p",
  "rho", "Drag", "nargin", "nargout", "h", "v", "D" };

/* Function Declarations */
static void initialize_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance);
static void initialize_params_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance);
static void enable_c6_flight_sim(SFc6_flight_simInstanceStruct *chartInstance);
static void disable_c6_flight_sim(SFc6_flight_simInstanceStruct *chartInstance);
static void c6_update_debugger_state_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c6_flight_sim(SFc6_flight_simInstanceStruct *
  chartInstance);
static void set_sim_state_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance, const mxArray *c6_st);
static void finalize_c6_flight_sim(SFc6_flight_simInstanceStruct *chartInstance);
static void sf_c6_flight_sim(SFc6_flight_simInstanceStruct *chartInstance);
static void c6_chartstep_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance);
static void initSimStructsc6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static real_T c6_emlrt_marshallIn(SFc6_flight_simInstanceStruct *chartInstance,
  const mxArray *c6_D, const char_T *c6_identifier);
static real_T c6_b_emlrt_marshallIn(SFc6_flight_simInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static void c6_info_helper(const mxArray **c6_info);
static const mxArray *c6_emlrt_marshallOut(char * c6_u);
static const mxArray *c6_b_emlrt_marshallOut(uint32_T c6_u);
static void c6_eml_scalar_eg(SFc6_flight_simInstanceStruct *chartInstance);
static real_T c6_mpower(SFc6_flight_simInstanceStruct *chartInstance, real_T
  c6_a);
static void c6_eml_error(SFc6_flight_simInstanceStruct *chartInstance);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_c_emlrt_marshallIn(SFc6_flight_simInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static uint8_T c6_d_emlrt_marshallIn(SFc6_flight_simInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_flight_sim, const char_T
  *c6_identifier);
static uint8_T c6_e_emlrt_marshallIn(SFc6_flight_simInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info(SFc6_flight_simInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c6_is_active_c6_flight_sim = 0U;
}

static void initialize_params_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance)
{
}

static void enable_c6_flight_sim(SFc6_flight_simInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c6_flight_sim(SFc6_flight_simInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c6_update_debugger_state_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c6_flight_sim(SFc6_flight_simInstanceStruct *
  chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  real_T c6_hoistedGlobal;
  real_T c6_u;
  const mxArray *c6_b_y = NULL;
  uint8_T c6_b_hoistedGlobal;
  uint8_T c6_b_u;
  const mxArray *c6_c_y = NULL;
  real_T *c6_D;
  c6_D = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellarray(2), FALSE);
  c6_hoistedGlobal = *c6_D;
  c6_u = c6_hoistedGlobal;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_b_hoistedGlobal = chartInstance->c6_is_active_c6_flight_sim;
  c6_b_u = c6_b_hoistedGlobal;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  sf_mex_assign(&c6_st, c6_y, FALSE);
  return c6_st;
}

static void set_sim_state_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance, const mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T *c6_D;
  c6_D = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c6_doneDoubleBufferReInit = TRUE;
  c6_u = sf_mex_dup(c6_st);
  *c6_D = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 0)),
    "D");
  chartInstance->c6_is_active_c6_flight_sim = c6_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 1)),
     "is_active_c6_flight_sim");
  sf_mex_destroy(&c6_u);
  c6_update_debugger_state_c6_flight_sim(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void finalize_c6_flight_sim(SFc6_flight_simInstanceStruct *chartInstance)
{
}

static void sf_c6_flight_sim(SFc6_flight_simInstanceStruct *chartInstance)
{
  real_T *c6_h;
  real_T *c6_D;
  real_T *c6_v;
  c6_v = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c6_D = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c6_h = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c6_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c6_h, 0U);
  _SFD_DATA_RANGE_CHECK(*c6_D, 1U);
  _SFD_DATA_RANGE_CHECK(*c6_v, 2U);
  chartInstance->c6_sfEvent = CALL_EVENT;
  c6_chartstep_c6_flight_sim(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_flight_simMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c6_chartstep_c6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance)
{
  real_T c6_hoistedGlobal;
  real_T c6_b_hoistedGlobal;
  real_T c6_h;
  real_T c6_v;
  uint32_T c6_debug_family_var_map[12];
  real_T c6_CD;
  real_T c6_Di;
  real_T c6_A;
  real_T c6_T;
  real_T c6_p;
  real_T c6_rho;
  real_T c6_Drag;
  real_T c6_nargin = 2.0;
  real_T c6_nargout = 1.0;
  real_T c6_D;
  real_T c6_b;
  real_T c6_y;
  real_T c6_b_A;
  real_T c6_x;
  real_T c6_b_x;
  real_T c6_b_y;
  real_T c6_b_b;
  real_T c6_c_b;
  real_T c6_c_y;
  real_T c6_c_x;
  real_T c6_d_x;
  real_T c6_d_b;
  real_T c6_e_b;
  real_T c6_d_y;
  real_T c6_c_A;
  real_T c6_e_x;
  real_T c6_f_x;
  real_T c6_e_y;
  real_T c6_a;
  real_T c6_b_a;
  real_T c6_c_a;
  real_T c6_ak;
  real_T c6_d_a;
  real_T c6_ar;
  real_T c6_c;
  real_T c6_f_b;
  real_T c6_g_b;
  real_T c6_f_y;
  real_T c6_d_A;
  real_T c6_B;
  real_T c6_g_x;
  real_T c6_g_y;
  real_T c6_h_x;
  real_T c6_h_y;
  real_T c6_h_b;
  real_T c6_i_y;
  real_T c6_e_a;
  real_T c6_f_a;
  real_T c6_g_a;
  real_T c6_b_ak;
  real_T c6_h_a;
  real_T c6_i_a;
  real_T c6_i_b;
  real_T c6_b_c;
  real_T c6_j_a;
  real_T c6_j_b;
  real_T c6_j_y;
  real_T c6_k_a;
  real_T c6_k_y;
  real_T c6_l_a;
  real_T *c6_b_v;
  real_T *c6_b_h;
  real_T *c6_b_D;
  boolean_T guard1 = FALSE;
  c6_b_v = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c6_b_D = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c6_b_h = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c6_sfEvent);
  c6_hoistedGlobal = *c6_b_h;
  c6_b_hoistedGlobal = *c6_b_v;
  c6_h = c6_hoistedGlobal;
  c6_v = c6_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c6_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_CD, 0U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_Di, 1U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_A, 2U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_T, 3U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_p, 4U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_rho, 5U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_Drag, 6U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 7U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 8U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_h, 9U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_v, 10U, c6_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_D, 11U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 3);
  c6_CD = 0.075;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 4);
  c6_Di = 1.5;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 5);
  c6_A = 1.7671458676442586;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 7);
  if (CV_EML_IF(0, 1, 0, c6_h <= 11000.0)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 8);
    c6_b = c6_h;
    c6_y = 0.00649 * c6_b;
    c6_T = 15.04 - c6_y;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 9);
    c6_b_A = c6_T + 273.1;
    c6_x = c6_b_A;
    c6_b_x = c6_x;
    c6_b_y = c6_b_x / 288.08;
    c6_b_b = c6_mpower(chartInstance, c6_b_y);
    c6_p = 101.29 * c6_b_b;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 11);
    guard1 = FALSE;
    if (CV_EML_COND(0, 1, 0, 11000.0 < c6_h)) {
      if (CV_EML_COND(0, 1, 1, c6_h <= 25000.0)) {
        CV_EML_MCDC(0, 1, 0, TRUE);
        CV_EML_IF(0, 1, 1, TRUE);
        _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 12);
        c6_T = -56.46;
        _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 13);
        c6_c_b = c6_h;
        c6_c_y = 0.000157 * c6_c_b;
        c6_c_x = 1.73 - c6_c_y;
        c6_d_x = c6_c_x;
        c6_d_x = muDoubleScalarExp(c6_d_x);
        c6_d_b = c6_d_x;
        c6_p = 22.65 * c6_d_b;
      } else {
        guard1 = TRUE;
      }
    } else {
      guard1 = TRUE;
    }

    if (guard1 == TRUE) {
      CV_EML_MCDC(0, 1, 0, FALSE);
      CV_EML_IF(0, 1, 1, FALSE);
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 16);
      c6_e_b = c6_h;
      c6_d_y = 0.00299 * c6_e_b;
      c6_T = -131.21 + c6_d_y;
      _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 17);
      c6_c_A = c6_T + 273.1;
      c6_e_x = c6_c_A;
      c6_f_x = c6_e_x;
      c6_e_y = c6_f_x / 216.6;
      c6_a = c6_e_y;
      c6_b_a = c6_a;
      c6_c_a = c6_b_a;
      c6_eml_scalar_eg(chartInstance);
      c6_ak = c6_c_a;
      if (c6_ak < 0.0) {
        c6_eml_error(chartInstance);
      }

      c6_d_a = c6_ak;
      c6_eml_scalar_eg(chartInstance);
      c6_ar = c6_d_a;
      c6_c = muDoubleScalarPower(c6_ar, -11.388);
      c6_f_b = c6_c;
      c6_p = 2.488 * c6_f_b;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 20);
  c6_g_b = c6_T + 273.1;
  c6_f_y = 0.2869 * c6_g_b;
  c6_d_A = c6_p;
  c6_B = c6_f_y;
  c6_g_x = c6_d_A;
  c6_g_y = c6_B;
  c6_h_x = c6_g_x;
  c6_h_y = c6_g_y;
  c6_rho = c6_h_x / c6_h_y;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 22);
  c6_h_b = c6_rho;
  c6_i_y = 0.5 * c6_h_b;
  c6_e_a = c6_v;
  c6_f_a = c6_e_a;
  c6_g_a = c6_f_a;
  c6_eml_scalar_eg(chartInstance);
  c6_b_ak = c6_g_a;
  c6_h_a = c6_b_ak;
  c6_eml_scalar_eg(chartInstance);
  c6_i_a = c6_h_a;
  c6_i_b = c6_h_a;
  c6_b_c = c6_i_a * c6_i_b;
  c6_j_a = c6_i_y;
  c6_j_b = c6_b_c;
  c6_j_y = c6_j_a * c6_j_b;
  c6_k_a = c6_j_y;
  c6_k_y = c6_k_a * 1.7671458676442586;
  c6_l_a = c6_k_y;
  c6_Drag = c6_l_a * 0.075;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 24);
  c6_D = c6_Drag;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, -24);
  _SFD_SYMBOL_SCOPE_POP();
  *c6_b_D = c6_D;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c6_sfEvent);
}

static void initSimStructsc6_flight_sim(SFc6_flight_simInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber)
{
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc6_flight_simInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static real_T c6_emlrt_marshallIn(SFc6_flight_simInstanceStruct *chartInstance,
  const mxArray *c6_D, const char_T *c6_identifier)
{
  real_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_D), &c6_thisId);
  sf_mex_destroy(&c6_D);
  return c6_y;
}

static real_T c6_b_emlrt_marshallIn(SFc6_flight_simInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d0, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_D;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc6_flight_simInstanceStruct *)chartInstanceVoid;
  c6_D = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_D), &c6_thisId);
  sf_mex_destroy(&c6_D);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

const mxArray *sf_c6_flight_sim_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  sf_mex_assign(&c6_nameCaptureInfo, sf_mex_createstruct("structure", 2, 22, 1),
                FALSE);
  c6_info_helper(&c6_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c6_nameCaptureInfo);
  return c6_nameCaptureInfo;
}

static void c6_info_helper(const mxArray **c6_info)
{
  const mxArray *c6_rhs0 = NULL;
  const mxArray *c6_lhs0 = NULL;
  const mxArray *c6_rhs1 = NULL;
  const mxArray *c6_lhs1 = NULL;
  const mxArray *c6_rhs2 = NULL;
  const mxArray *c6_lhs2 = NULL;
  const mxArray *c6_rhs3 = NULL;
  const mxArray *c6_lhs3 = NULL;
  const mxArray *c6_rhs4 = NULL;
  const mxArray *c6_lhs4 = NULL;
  const mxArray *c6_rhs5 = NULL;
  const mxArray *c6_lhs5 = NULL;
  const mxArray *c6_rhs6 = NULL;
  const mxArray *c6_lhs6 = NULL;
  const mxArray *c6_rhs7 = NULL;
  const mxArray *c6_lhs7 = NULL;
  const mxArray *c6_rhs8 = NULL;
  const mxArray *c6_lhs8 = NULL;
  const mxArray *c6_rhs9 = NULL;
  const mxArray *c6_lhs9 = NULL;
  const mxArray *c6_rhs10 = NULL;
  const mxArray *c6_lhs10 = NULL;
  const mxArray *c6_rhs11 = NULL;
  const mxArray *c6_lhs11 = NULL;
  const mxArray *c6_rhs12 = NULL;
  const mxArray *c6_lhs12 = NULL;
  const mxArray *c6_rhs13 = NULL;
  const mxArray *c6_lhs13 = NULL;
  const mxArray *c6_rhs14 = NULL;
  const mxArray *c6_lhs14 = NULL;
  const mxArray *c6_rhs15 = NULL;
  const mxArray *c6_lhs15 = NULL;
  const mxArray *c6_rhs16 = NULL;
  const mxArray *c6_lhs16 = NULL;
  const mxArray *c6_rhs17 = NULL;
  const mxArray *c6_lhs17 = NULL;
  const mxArray *c6_rhs18 = NULL;
  const mxArray *c6_lhs18 = NULL;
  const mxArray *c6_rhs19 = NULL;
  const mxArray *c6_lhs19 = NULL;
  const mxArray *c6_rhs20 = NULL;
  const mxArray *c6_lhs20 = NULL;
  const mxArray *c6_rhs21 = NULL;
  const mxArray *c6_lhs21 = NULL;
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("mpower"), "name", "name", 0);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363699478U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c6_rhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363700156U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c6_rhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("ismatrix"), "name", "name", 2);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1331290458U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c6_rhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("power"), "name", "name", 3);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363699480U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c6_rhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 4);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363700156U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c6_rhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 5);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 5);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1286807996U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c6_rhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 6);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 6);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1358171740U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c6_rhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 7);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("floor"), "name", "name", 7);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363699454U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c6_rhs7, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs7, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 8);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363700156U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c6_rhs8, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs8, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 9);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 9);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1286807926U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c6_rhs9, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs9, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 10);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 10);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1286807996U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c6_rhs10, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs10, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 11);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("mtimes"), "name", "name", 11);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 11);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363699478U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c6_rhs11, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs11, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m!common_checks"),
                  "context", "context", 12);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 12);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363700156U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c6_rhs12, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs12, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(""), "context", "context", 13);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("mtimes"), "name", "name", 13);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363699478U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c6_rhs13, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs13, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(""), "context", "context", 14);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("mrdivide"), "name", "name", 14);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1373295708U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1319719166U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c6_rhs14, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs14, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 15);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("rdivide"), "name", "name", 15);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363699480U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c6_rhs15, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs15, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 16);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363700156U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c6_rhs16, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs16, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 17);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1286807996U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c6_rhs17, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs17, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("eml_div"), "name", "name", 18);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363699466U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c6_rhs18, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs18, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 19);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("eml_error"), "name", "name",
                  19);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1343819558U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c6_rhs19, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs19, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(""), "context", "context", 20);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("exp"), "name", "name", 20);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/exp.m"), "resolved",
                  "resolved", 20);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1343819580U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c6_rhs20, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs20, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/exp.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("eml_scalar_exp"), "name",
                  "name", 21);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_exp.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1301317664U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c6_rhs21, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c6_lhs21, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs21), "lhs", "lhs",
                  21);
  sf_mex_destroy(&c6_rhs0);
  sf_mex_destroy(&c6_lhs0);
  sf_mex_destroy(&c6_rhs1);
  sf_mex_destroy(&c6_lhs1);
  sf_mex_destroy(&c6_rhs2);
  sf_mex_destroy(&c6_lhs2);
  sf_mex_destroy(&c6_rhs3);
  sf_mex_destroy(&c6_lhs3);
  sf_mex_destroy(&c6_rhs4);
  sf_mex_destroy(&c6_lhs4);
  sf_mex_destroy(&c6_rhs5);
  sf_mex_destroy(&c6_lhs5);
  sf_mex_destroy(&c6_rhs6);
  sf_mex_destroy(&c6_lhs6);
  sf_mex_destroy(&c6_rhs7);
  sf_mex_destroy(&c6_lhs7);
  sf_mex_destroy(&c6_rhs8);
  sf_mex_destroy(&c6_lhs8);
  sf_mex_destroy(&c6_rhs9);
  sf_mex_destroy(&c6_lhs9);
  sf_mex_destroy(&c6_rhs10);
  sf_mex_destroy(&c6_lhs10);
  sf_mex_destroy(&c6_rhs11);
  sf_mex_destroy(&c6_lhs11);
  sf_mex_destroy(&c6_rhs12);
  sf_mex_destroy(&c6_lhs12);
  sf_mex_destroy(&c6_rhs13);
  sf_mex_destroy(&c6_lhs13);
  sf_mex_destroy(&c6_rhs14);
  sf_mex_destroy(&c6_lhs14);
  sf_mex_destroy(&c6_rhs15);
  sf_mex_destroy(&c6_lhs15);
  sf_mex_destroy(&c6_rhs16);
  sf_mex_destroy(&c6_lhs16);
  sf_mex_destroy(&c6_rhs17);
  sf_mex_destroy(&c6_lhs17);
  sf_mex_destroy(&c6_rhs18);
  sf_mex_destroy(&c6_lhs18);
  sf_mex_destroy(&c6_rhs19);
  sf_mex_destroy(&c6_lhs19);
  sf_mex_destroy(&c6_rhs20);
  sf_mex_destroy(&c6_lhs20);
  sf_mex_destroy(&c6_rhs21);
  sf_mex_destroy(&c6_lhs21);
}

static const mxArray *c6_emlrt_marshallOut(char * c6_u)
{
  const mxArray *c6_y = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c6_u)), FALSE);
  return c6_y;
}

static const mxArray *c6_b_emlrt_marshallOut(uint32_T c6_u)
{
  const mxArray *c6_y = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 7, 0U, 0U, 0U, 0), FALSE);
  return c6_y;
}

static void c6_eml_scalar_eg(SFc6_flight_simInstanceStruct *chartInstance)
{
}

static real_T c6_mpower(SFc6_flight_simInstanceStruct *chartInstance, real_T
  c6_a)
{
  real_T c6_b_a;
  real_T c6_c_a;
  real_T c6_ak;
  real_T c6_d_a;
  real_T c6_ar;
  c6_b_a = c6_a;
  c6_c_a = c6_b_a;
  c6_eml_scalar_eg(chartInstance);
  c6_ak = c6_c_a;
  if (c6_ak < 0.0) {
    c6_eml_error(chartInstance);
  }

  c6_d_a = c6_ak;
  c6_eml_scalar_eg(chartInstance);
  c6_ar = c6_d_a;
  return muDoubleScalarPower(c6_ar, 5.258);
}

static void c6_eml_error(SFc6_flight_simInstanceStruct *chartInstance)
{
  int32_T c6_i0;
  static char_T c6_cv0[31] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'p', 'o', 'w', 'e', 'r', '_', 'd', 'o', 'm', 'a', 'i',
    'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c6_u[31];
  const mxArray *c6_y = NULL;
  for (c6_i0 = 0; c6_i0 < 31; c6_i0++) {
    c6_u[c6_i0] = c6_cv0[c6_i0];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 10, 0U, 1U, 0U, 2, 1, 31), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c6_y));
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc6_flight_simInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, FALSE);
  return c6_mxArrayOutData;
}

static int32_T c6_c_emlrt_marshallIn(SFc6_flight_simInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i1;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i1, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i1;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc6_flight_simInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static uint8_T c6_d_emlrt_marshallIn(SFc6_flight_simInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_flight_sim, const char_T
  *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_is_active_c6_flight_sim), &c6_thisId);
  sf_mex_destroy(&c6_b_is_active_c6_flight_sim);
  return c6_y;
}

static uint8_T c6_e_emlrt_marshallIn(SFc6_flight_simInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info(SFc6_flight_simInstanceStruct *chartInstance)
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

void sf_c6_flight_sim_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2428493934U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1069187352U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3332762642U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3826433481U);
}

mxArray *sf_c6_flight_sim_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("rGIYcBBASD430uXxYdiOmE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c6_flight_sim_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c6_flight_sim_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c6_flight_sim(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"D\",},{M[8],M[0],T\"is_active_c6_flight_sim\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_flight_sim_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_flight_simInstanceStruct *chartInstance;
    chartInstance = (SFc6_flight_simInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _flight_simMachineNumber_,
           6,
           1,
           1,
           3,
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
          _SFD_SET_DATA_PROPS(1,2,0,1,"D");
          _SFD_SET_DATA_PROPS(2,1,1,0,"v");
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
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,387);
        _SFD_CV_INIT_EML_IF(0,1,0,70,81,153,320);
        _SFD_CV_INIT_EML_IF(0,1,1,153,184,242,320);

        {
          static int condStart[] = { 161, 174 };

          static int condEnd[] = { 168, 183 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,160,184,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c6_h;
          real_T *c6_D;
          real_T *c6_v;
          c6_v = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c6_D = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c6_h = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c6_h);
          _SFD_SET_DATA_VALUE_PTR(1U, c6_D);
          _SFD_SET_DATA_VALUE_PTR(2U, c6_v);
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
  return "pzbkSaD4tRRFIIGUZBeILB";
}

static void sf_opaque_initialize_c6_flight_sim(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_flight_simInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c6_flight_sim((SFc6_flight_simInstanceStruct*)
    chartInstanceVar);
  initialize_c6_flight_sim((SFc6_flight_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c6_flight_sim(void *chartInstanceVar)
{
  enable_c6_flight_sim((SFc6_flight_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c6_flight_sim(void *chartInstanceVar)
{
  disable_c6_flight_sim((SFc6_flight_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c6_flight_sim(void *chartInstanceVar)
{
  sf_c6_flight_sim((SFc6_flight_simInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c6_flight_sim(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c6_flight_sim
    ((SFc6_flight_simInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_flight_sim();/* state var info */
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

extern void sf_internal_set_sim_state_c6_flight_sim(SimStruct* S, const mxArray *
  st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_flight_sim();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c6_flight_sim((SFc6_flight_simInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c6_flight_sim(SimStruct* S)
{
  return sf_internal_get_sim_state_c6_flight_sim(S);
}

static void sf_opaque_set_sim_state_c6_flight_sim(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c6_flight_sim(S, st);
}

static void sf_opaque_terminate_c6_flight_sim(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_flight_simInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_flight_sim_optimization_info();
    }

    finalize_c6_flight_sim((SFc6_flight_simInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_flight_sim((SFc6_flight_simInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_flight_sim(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_flight_sim((SFc6_flight_simInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_flight_sim(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_flight_sim_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,6,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,6,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,6);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3471926432U));
  ssSetChecksum1(S,(2954162687U));
  ssSetChecksum2(S,(3280750545U));
  ssSetChecksum3(S,(1205494819U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c6_flight_sim(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c6_flight_sim(SimStruct *S)
{
  SFc6_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc6_flight_simInstanceStruct *)utMalloc(sizeof
    (SFc6_flight_simInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc6_flight_simInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c6_flight_sim;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c6_flight_sim;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c6_flight_sim;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_flight_sim;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_flight_sim;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c6_flight_sim;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c6_flight_sim;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c6_flight_sim;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_flight_sim;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_flight_sim;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c6_flight_sim;
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

void c6_flight_sim_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_flight_sim(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_flight_sim(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_flight_sim(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_flight_sim_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
