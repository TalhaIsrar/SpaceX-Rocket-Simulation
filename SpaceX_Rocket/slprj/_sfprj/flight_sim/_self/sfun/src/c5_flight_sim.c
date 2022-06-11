/* Include files */

#include <stddef.h>
#include "blas.h"
#include "flight_sim_sfun.h"
#include "c5_flight_sim.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "flight_sim_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c5_debug_family_names[12] = { "mfuel", "THR", "nargin",
  "nargout", "t", "m_dot", "T", "m_fuel", "m_fb", "m_fb2", "mfb", "mfb2" };

/* Function Declarations */
static void initialize_c5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance);
static void initialize_params_c5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance);
static void enable_c5_flight_sim(SFc5_flight_simInstanceStruct *chartInstance);
static void disable_c5_flight_sim(SFc5_flight_simInstanceStruct *chartInstance);
static void c5_update_debugger_state_c5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c5_flight_sim(SFc5_flight_simInstanceStruct *
  chartInstance);
static void set_sim_state_c5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance, const mxArray *c5_st);
static void finalize_c5_flight_sim(SFc5_flight_simInstanceStruct *chartInstance);
static void sf_c5_flight_sim(SFc5_flight_simInstanceStruct *chartInstance);
static void initSimStructsc5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static real_T c5_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_b_mfb2, const char_T *c5_identifier);
static real_T c5_b_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_c_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_b_mfb, const char_T *c5_identifier);
static real_T c5_d_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_e_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_m_fb2, const char_T *c5_identifier);
static real_T c5_f_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void c5_info_helper(const mxArray **c5_info);
static const mxArray *c5_emlrt_marshallOut(char * c5_u);
static const mxArray *c5_b_emlrt_marshallOut(uint32_T c5_u);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_g_emlrt_marshallIn(SFc5_flight_simInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static uint8_T c5_h_emlrt_marshallIn(SFc5_flight_simInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_flight_sim, const char_T
  *c5_identifier);
static uint8_T c5_i_emlrt_marshallIn(SFc5_flight_simInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void init_dsm_address_info(SFc5_flight_simInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance)
{
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c5_mfb_not_empty = FALSE;
  chartInstance->c5_mfb2_not_empty = FALSE;
  chartInstance->c5_is_active_c5_flight_sim = 0U;
}

static void initialize_params_c5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance)
{
}

static void enable_c5_flight_sim(SFc5_flight_simInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c5_flight_sim(SFc5_flight_simInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c5_update_debugger_state_c5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c5_flight_sim(SFc5_flight_simInstanceStruct *
  chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  real_T c5_hoistedGlobal;
  real_T c5_u;
  const mxArray *c5_b_y = NULL;
  real_T c5_b_hoistedGlobal;
  real_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  real_T c5_c_hoistedGlobal;
  real_T c5_c_u;
  const mxArray *c5_d_y = NULL;
  real_T c5_d_hoistedGlobal;
  real_T c5_d_u;
  const mxArray *c5_e_y = NULL;
  real_T c5_e_hoistedGlobal;
  real_T c5_e_u;
  const mxArray *c5_f_y = NULL;
  real_T c5_f_hoistedGlobal;
  real_T c5_f_u;
  const mxArray *c5_g_y = NULL;
  uint8_T c5_g_hoistedGlobal;
  uint8_T c5_g_u;
  const mxArray *c5_h_y = NULL;
  real_T *c5_T;
  real_T *c5_m_fb;
  real_T *c5_m_fb2;
  real_T *c5_m_fuel;
  c5_m_fb2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c5_m_fb = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c5_m_fuel = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellarray(7), FALSE);
  c5_hoistedGlobal = *c5_T;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_b_hoistedGlobal = *c5_m_fb;
  c5_b_u = c5_b_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_c_hoistedGlobal = *c5_m_fb2;
  c5_c_u = c5_c_hoistedGlobal;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c5_y, 2, c5_d_y);
  c5_d_hoistedGlobal = *c5_m_fuel;
  c5_d_u = c5_d_hoistedGlobal;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c5_y, 3, c5_e_y);
  c5_e_hoistedGlobal = chartInstance->c5_mfb;
  c5_e_u = c5_e_hoistedGlobal;
  c5_f_y = NULL;
  if (!chartInstance->c5_mfb_not_empty) {
    sf_mex_assign(&c5_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c5_y, 4, c5_f_y);
  c5_f_hoistedGlobal = chartInstance->c5_mfb2;
  c5_f_u = c5_f_hoistedGlobal;
  c5_g_y = NULL;
  if (!chartInstance->c5_mfb2_not_empty) {
    sf_mex_assign(&c5_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c5_g_y, sf_mex_create("y", &c5_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c5_y, 5, c5_g_y);
  c5_g_hoistedGlobal = chartInstance->c5_is_active_c5_flight_sim;
  c5_g_u = c5_g_hoistedGlobal;
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y", &c5_g_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c5_y, 6, c5_h_y);
  sf_mex_assign(&c5_st, c5_y, FALSE);
  return c5_st;
}

static void set_sim_state_c5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  real_T *c5_T;
  real_T *c5_m_fb;
  real_T *c5_m_fb2;
  real_T *c5_m_fuel;
  c5_m_fb2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c5_m_fb = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c5_m_fuel = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c5_doneDoubleBufferReInit = TRUE;
  c5_u = sf_mex_dup(c5_st);
  *c5_T = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 0)),
    "T");
  *c5_m_fb = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u,
    1)), "m_fb");
  *c5_m_fb2 = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c5_u, 2)), "m_fb2");
  *c5_m_fuel = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c5_u, 3)), "m_fuel");
  chartInstance->c5_mfb = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 4)), "mfb");
  chartInstance->c5_mfb2 = c5_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c5_u, 5)), "mfb2");
  chartInstance->c5_is_active_c5_flight_sim = c5_h_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 6)),
     "is_active_c5_flight_sim");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_flight_sim(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_flight_sim(SFc5_flight_simInstanceStruct *chartInstance)
{
}

static void sf_c5_flight_sim(SFc5_flight_simInstanceStruct *chartInstance)
{
  real_T c5_hoistedGlobal;
  real_T c5_b_hoistedGlobal;
  real_T c5_t;
  real_T c5_m_dot;
  uint32_T c5_debug_family_var_map[12];
  real_T c5_mfuel;
  real_T c5_THR;
  real_T c5_nargin = 2.0;
  real_T c5_nargout = 4.0;
  real_T c5_T;
  real_T c5_m_fuel;
  real_T c5_m_fb;
  real_T c5_m_fb2;
  real_T c5_c_hoistedGlobal;
  real_T c5_a;
  real_T c5_b;
  real_T c5_A;
  real_T c5_x;
  real_T c5_b_x;
  real_T c5_y;
  real_T c5_b_a;
  real_T c5_b_b;
  real_T *c5_b_m_fb2;
  real_T *c5_b_m_fb;
  real_T *c5_b_m_fuel;
  real_T *c5_b_T;
  real_T *c5_b_m_dot;
  real_T *c5_b_t;
  boolean_T guard1 = FALSE;
  c5_b_m_dot = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c5_b_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c5_b_m_fb2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c5_b_m_fb = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c5_b_m_fuel = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c5_b_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c5_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c5_b_T, 0U);
  _SFD_DATA_RANGE_CHECK(*c5_b_m_fuel, 1U);
  _SFD_DATA_RANGE_CHECK(*c5_b_m_fb, 2U);
  _SFD_DATA_RANGE_CHECK(*c5_b_m_fb2, 3U);
  _SFD_DATA_RANGE_CHECK(*c5_b_t, 4U);
  _SFD_DATA_RANGE_CHECK(*c5_b_m_dot, 5U);
  chartInstance->c5_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c5_sfEvent);
  c5_hoistedGlobal = *c5_b_t;
  c5_b_hoistedGlobal = *c5_b_m_dot;
  c5_t = c5_hoistedGlobal;
  c5_m_dot = c5_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_mfuel, 0U, c5_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_THR, 1U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 2U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 3U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_t, 4U, c5_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_m_dot, 5U, c5_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_T, 6U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_m_fuel, 7U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_m_fb, 8U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_m_fb2, 9U, c5_c_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c5_mfb, 10U,
    c5_b_sf_marshallOut, c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c5_mfb2, 11U,
    c5_sf_marshallOut, c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 4);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 5);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c5_mfb_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 6);
    chartInstance->c5_mfb = 0.0;
    chartInstance->c5_mfb_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 8);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c5_mfb2_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 9);
    chartInstance->c5_mfb2 = 0.0;
    chartInstance->c5_mfb2_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 12);
  c5_mfuel = 21491.26;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 13);
  c5_c_hoistedGlobal = chartInstance->c5_mfb;
  if (CV_EML_IF(0, 1, 2, c5_c_hoistedGlobal <= 13969.319)) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 14);
    c5_THR = 346961.2;
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 15);
    c5_a = c5_t;
    c5_b = c5_m_dot;
    chartInstance->c5_mfb = c5_a * c5_b;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 17);
    c5_THR = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 20);
  guard1 = FALSE;
  if (CV_EML_COND(0, 1, 0, 125.0 < c5_t)) {
    if (CV_EML_COND(0, 1, 1, c5_t < 295.0)) {
      CV_EML_MCDC(0, 1, 0, TRUE);
      CV_EML_IF(0, 1, 3, TRUE);
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 21);
      c5_THR = -110000.0;
      _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 22);
      c5_A = c5_m_dot;
      c5_x = c5_A;
      c5_b_x = c5_x;
      c5_y = c5_b_x / 3.0;
      c5_b_a = c5_t - 125.0;
      c5_b_b = c5_y;
      chartInstance->c5_mfb2 = c5_b_a * c5_b_b;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    CV_EML_MCDC(0, 1, 0, FALSE);
    CV_EML_IF(0, 1, 3, FALSE);
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 25);
  c5_T = c5_THR;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 26);
  c5_m_fb = chartInstance->c5_mfb;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 27);
  c5_m_fb2 = chartInstance->c5_mfb2;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 28);
  c5_m_fuel = c5_mfuel;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -28);
  _SFD_SYMBOL_SCOPE_POP();
  *c5_b_T = c5_T;
  *c5_b_m_fuel = c5_m_fuel;
  *c5_b_m_fb = c5_m_fb;
  *c5_b_m_fb2 = c5_m_fb2;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_flight_simMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc5_flight_sim(SFc5_flight_simInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber)
{
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc5_flight_simInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  if (!chartInstance->c5_mfb2_not_empty) {
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static real_T c5_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_b_mfb2, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_mfb2), &c5_thisId);
  sf_mex_destroy(&c5_b_mfb2);
  return c5_y;
}

static real_T c5_b_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  if (mxIsEmpty(c5_u)) {
    chartInstance->c5_mfb2_not_empty = FALSE;
  } else {
    chartInstance->c5_mfb2_not_empty = TRUE;
    sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
    c5_y = c5_d0;
  }

  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_mfb2;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc5_flight_simInstanceStruct *)chartInstanceVoid;
  c5_b_mfb2 = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_mfb2), &c5_thisId);
  sf_mex_destroy(&c5_b_mfb2);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc5_flight_simInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  if (!chartInstance->c5_mfb_not_empty) {
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static real_T c5_c_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_b_mfb, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_mfb), &c5_thisId);
  sf_mex_destroy(&c5_b_mfb);
  return c5_y;
}

static real_T c5_d_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d1;
  if (mxIsEmpty(c5_u)) {
    chartInstance->c5_mfb_not_empty = FALSE;
  } else {
    chartInstance->c5_mfb_not_empty = TRUE;
    sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d1, 1, 0, 0U, 0, 0U, 0);
    c5_y = c5_d1;
  }

  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_mfb;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc5_flight_simInstanceStruct *)chartInstanceVoid;
  c5_b_mfb = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_mfb), &c5_thisId);
  sf_mex_destroy(&c5_b_mfb);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc5_flight_simInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static real_T c5_e_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_m_fb2, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_m_fb2), &c5_thisId);
  sf_mex_destroy(&c5_m_fb2);
  return c5_y;
}

static real_T c5_f_emlrt_marshallIn(SFc5_flight_simInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d2;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d2, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d2;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_m_fb2;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc5_flight_simInstanceStruct *)chartInstanceVoid;
  c5_m_fb2 = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_m_fb2), &c5_thisId);
  sf_mex_destroy(&c5_m_fb2);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_flight_sim_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_createstruct("structure", 2, 7, 1),
                FALSE);
  c5_info_helper(&c5_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c5_nameCaptureInfo);
  return c5_nameCaptureInfo;
}

static void c5_info_helper(const mxArray **c5_info)
{
  const mxArray *c5_rhs0 = NULL;
  const mxArray *c5_lhs0 = NULL;
  const mxArray *c5_rhs1 = NULL;
  const mxArray *c5_lhs1 = NULL;
  const mxArray *c5_rhs2 = NULL;
  const mxArray *c5_lhs2 = NULL;
  const mxArray *c5_rhs3 = NULL;
  const mxArray *c5_lhs3 = NULL;
  const mxArray *c5_rhs4 = NULL;
  const mxArray *c5_lhs4 = NULL;
  const mxArray *c5_rhs5 = NULL;
  const mxArray *c5_lhs5 = NULL;
  const mxArray *c5_rhs6 = NULL;
  const mxArray *c5_lhs6 = NULL;
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("mtimes"), "name", "name", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363699478U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c5_rhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c5_lhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363700156U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c5_rhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c5_lhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("mrdivide"), "name", "name", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1373295708U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1319719166U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c5_rhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c5_lhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("rdivide"), "name", "name", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363699480U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c5_rhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c5_lhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363700156U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c5_rhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c5_lhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286807996U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c5_rhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c5_lhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_div"), "name", "name", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363699466U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c5_rhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c5_lhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs6), "lhs", "lhs", 6);
  sf_mex_destroy(&c5_rhs0);
  sf_mex_destroy(&c5_lhs0);
  sf_mex_destroy(&c5_rhs1);
  sf_mex_destroy(&c5_lhs1);
  sf_mex_destroy(&c5_rhs2);
  sf_mex_destroy(&c5_lhs2);
  sf_mex_destroy(&c5_rhs3);
  sf_mex_destroy(&c5_lhs3);
  sf_mex_destroy(&c5_rhs4);
  sf_mex_destroy(&c5_lhs4);
  sf_mex_destroy(&c5_rhs5);
  sf_mex_destroy(&c5_lhs5);
  sf_mex_destroy(&c5_rhs6);
  sf_mex_destroy(&c5_lhs6);
}

static const mxArray *c5_emlrt_marshallOut(char * c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c5_u)), FALSE);
  return c5_y;
}

static const mxArray *c5_b_emlrt_marshallOut(uint32_T c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 7, 0U, 0U, 0U, 0), FALSE);
  return c5_y;
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc5_flight_simInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, FALSE);
  return c5_mxArrayOutData;
}

static int32_T c5_g_emlrt_marshallIn(SFc5_flight_simInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i0;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i0, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc5_flight_simInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static uint8_T c5_h_emlrt_marshallIn(SFc5_flight_simInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_flight_sim, const char_T
  *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_is_active_c5_flight_sim), &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_flight_sim);
  return c5_y;
}

static uint8_T c5_i_emlrt_marshallIn(SFc5_flight_simInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void init_dsm_address_info(SFc5_flight_simInstanceStruct *chartInstance)
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

void sf_c5_flight_sim_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3666037595U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1468922997U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(11446476U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(631515963U);
}

mxArray *sf_c5_flight_sim_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("WZhT3Oge4uvtMEU9zKiYWF");
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

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_flight_sim_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_flight_sim_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c5_flight_sim(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[6],T\"T\",},{M[1],M[8],T\"m_fb\",},{M[1],M[9],T\"m_fb2\",},{M[1],M[7],T\"m_fuel\",},{M[4],M[0],T\"mfb\",S'l','i','p'{{M1x2[66 69],M[0],}}},{M[4],M[0],T\"mfb2\",S'l','i','p'{{M1x2[82 86],M[0],}}},{M[8],M[0],T\"is_active_c5_flight_sim\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_flight_sim_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_flight_simInstanceStruct *chartInstance;
    chartInstance = (SFc5_flight_simInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _flight_simMachineNumber_,
           5,
           1,
           1,
           6,
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
          _SFD_SET_DATA_PROPS(0,2,0,1,"T");
          _SFD_SET_DATA_PROPS(1,2,0,1,"m_fuel");
          _SFD_SET_DATA_PROPS(2,2,0,1,"m_fb");
          _SFD_SET_DATA_PROPS(3,2,0,1,"m_fb2");
          _SFD_SET_DATA_PROPS(4,1,1,0,"t");
          _SFD_SET_DATA_PROPS(5,1,1,0,"m_dot");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,394);
        _SFD_CV_INIT_EML_IF(0,1,0,88,103,-1,120);
        _SFD_CV_INIT_EML_IF(0,1,1,125,141,-1,159);
        _SFD_CV_INIT_EML_IF(0,1,2,181,200,240,261);
        _SFD_CV_INIT_EML_IF(0,1,3,267,288,-1,341);

        {
          static int condStart[] = { 271, 282 };

          static int condEnd[] = { 276, 287 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,270,288,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c5_T;
          real_T *c5_m_fuel;
          real_T *c5_m_fb;
          real_T *c5_m_fb2;
          real_T *c5_t;
          real_T *c5_m_dot;
          c5_m_dot = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c5_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          c5_m_fb2 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c5_m_fb = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c5_m_fuel = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c5_T = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c5_T);
          _SFD_SET_DATA_VALUE_PTR(1U, c5_m_fuel);
          _SFD_SET_DATA_VALUE_PTR(2U, c5_m_fb);
          _SFD_SET_DATA_VALUE_PTR(3U, c5_m_fb2);
          _SFD_SET_DATA_VALUE_PTR(4U, c5_t);
          _SFD_SET_DATA_VALUE_PTR(5U, c5_m_dot);
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
  return "5I0tp3vHclP94i0lLpqG1G";
}

static void sf_opaque_initialize_c5_flight_sim(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_flight_simInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c5_flight_sim((SFc5_flight_simInstanceStruct*)
    chartInstanceVar);
  initialize_c5_flight_sim((SFc5_flight_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_flight_sim(void *chartInstanceVar)
{
  enable_c5_flight_sim((SFc5_flight_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_flight_sim(void *chartInstanceVar)
{
  disable_c5_flight_sim((SFc5_flight_simInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_flight_sim(void *chartInstanceVar)
{
  sf_c5_flight_sim((SFc5_flight_simInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_flight_sim(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c5_flight_sim
    ((SFc5_flight_simInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_flight_sim();/* state var info */
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

extern void sf_internal_set_sim_state_c5_flight_sim(SimStruct* S, const mxArray *
  st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_flight_sim();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c5_flight_sim((SFc5_flight_simInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c5_flight_sim(SimStruct* S)
{
  return sf_internal_get_sim_state_c5_flight_sim(S);
}

static void sf_opaque_set_sim_state_c5_flight_sim(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c5_flight_sim(S, st);
}

static void sf_opaque_terminate_c5_flight_sim(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_flight_simInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_flight_sim_optimization_info();
    }

    finalize_c5_flight_sim((SFc5_flight_simInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_flight_sim((SFc5_flight_simInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_flight_sim(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c5_flight_sim((SFc5_flight_simInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_flight_sim(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_flight_sim_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,5,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,5,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3899124551U));
  ssSetChecksum1(S,(939855225U));
  ssSetChecksum2(S,(1210202497U));
  ssSetChecksum3(S,(4015226758U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_flight_sim(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_flight_sim(SimStruct *S)
{
  SFc5_flight_simInstanceStruct *chartInstance;
  chartInstance = (SFc5_flight_simInstanceStruct *)utMalloc(sizeof
    (SFc5_flight_simInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_flight_simInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_flight_sim;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_flight_sim;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_flight_sim;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_flight_sim;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_flight_sim;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_flight_sim;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_flight_sim;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c5_flight_sim;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_flight_sim;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_flight_sim;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_flight_sim;
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

void c5_flight_sim_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_flight_sim(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_flight_sim(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_flight_sim(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_flight_sim_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
