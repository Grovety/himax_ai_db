
/* SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause */
/******************************************************************************
 * Copyright (c) 2020, STMicroelectronics - All Rights Reserved

 This file is part of VL53L1 and is dual licensed,
 either GPL-2.0+
 or 'BSD 3-clause "New" or "Revised" License' , at your option.
 ******************************************************************************
 */




#ifndef _VL53L1_API_PRESET_MODES_H_
#define _VL53L1_API_PRESET_MODES_H_

#include "vl53l1_ll_def.h"
#include "vl53l1_dmax_structs.h"

#ifdef __cplusplus
extern "C" {
#endif




VL53L1_Error VL53L1_init_refspadchar_config_struct(
	VL53L1_refspadchar_config_t     *pdata);




VL53L1_Error VL53L1_init_ssc_config_struct(
	VL53L1_ssc_config_t     *pdata);




VL53L1_Error VL53L1_init_xtalk_config_struct(
		VL53L1_customer_nvm_managed_t *pnvm,
		VL53L1_xtalk_config_t   *pdata);



VL53L1_Error VL53L1_init_xtalk_extract_config_struct(
		VL53L1_xtalkextract_config_t   *pdata);



VL53L1_Error VL53L1_init_offset_cal_config_struct(
	VL53L1_offsetcal_config_t   *pdata);



VL53L1_Error VL53L1_init_zone_cal_config_struct(
	VL53L1_zonecal_config_t   *pdata);



VL53L1_Error VL53L1_init_hist_post_process_config_struct(
	uint8_t                              xtalk_compensation_enable,
	VL53L1_hist_post_process_config_t   *pdata);




VL53L1_Error VL53L1_init_dmax_calibration_data_struct(
	VL53L1_dmax_calibration_data_t   *pdata);




VL53L1_Error VL53L1_init_tuning_parm_storage_struct(
	VL53L1_tuning_parm_storage_t   *pdata);



VL53L1_Error VL53L1_init_hist_gen3_dmax_config_struct(
	VL53L1_hist_gen3_dmax_config_t   *pdata);




VL53L1_Error VL53L1_preset_mode_standard_ranging(
	VL53L1_static_config_t     *pstatic,
	VL53L1_histogram_config_t  *phistogram,
	VL53L1_general_config_t    *pgeneral,
	VL53L1_timing_config_t     *ptiming,
	VL53L1_dynamic_config_t    *pdynamic,
	VL53L1_system_control_t    *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t       *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_standard_ranging_short_range(
	VL53L1_static_config_t     *pstatic,
	VL53L1_histogram_config_t  *phistogram,
	VL53L1_general_config_t    *pgeneral,
	VL53L1_timing_config_t     *ptiming,
	VL53L1_dynamic_config_t    *pdynamic,
	VL53L1_system_control_t    *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t       *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_standard_ranging_long_range(
	VL53L1_static_config_t     *pstatic,
	VL53L1_histogram_config_t  *phistogram,
	VL53L1_general_config_t    *pgeneral,
	VL53L1_timing_config_t     *ptiming,
	VL53L1_dynamic_config_t    *pdynamic,
	VL53L1_system_control_t    *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t       *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_standard_ranging_mm1_cal(
	VL53L1_static_config_t     *pstatic,
	VL53L1_histogram_config_t  *phistogram,
	VL53L1_general_config_t    *pgeneral,
	VL53L1_timing_config_t     *ptiming,
	VL53L1_dynamic_config_t    *pdynamic,
	VL53L1_system_control_t    *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t       *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_standard_ranging_mm2_cal(
	VL53L1_static_config_t     *pstatic,
	VL53L1_histogram_config_t  *phistogram,
	VL53L1_general_config_t    *pgeneral,
	VL53L1_timing_config_t     *ptiming,
	VL53L1_dynamic_config_t    *pdynamic,
	VL53L1_system_control_t    *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t       *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_timed_ranging(

	VL53L1_static_config_t    *pstatic,
	VL53L1_histogram_config_t *phistogram,
	VL53L1_general_config_t   *pgeneral,
	VL53L1_timing_config_t    *ptiming,
	VL53L1_dynamic_config_t   *pdynamic,
	VL53L1_system_control_t   *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t      *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_timed_ranging_short_range(

	VL53L1_static_config_t    *pstatic,
	VL53L1_histogram_config_t *phistogram,
	VL53L1_general_config_t   *pgeneral,
	VL53L1_timing_config_t    *ptiming,
	VL53L1_dynamic_config_t   *pdynamic,
	VL53L1_system_control_t   *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t      *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_timed_ranging_long_range(

	VL53L1_static_config_t    *pstatic,
	VL53L1_histogram_config_t *phistogram,
	VL53L1_general_config_t   *pgeneral,
	VL53L1_timing_config_t    *ptiming,
	VL53L1_dynamic_config_t   *pdynamic,
	VL53L1_system_control_t   *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t      *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_low_power_auto_ranging(

	VL53L1_static_config_t    *pstatic,
	VL53L1_histogram_config_t *phistogram,
	VL53L1_general_config_t   *pgeneral,
	VL53L1_timing_config_t    *ptiming,
	VL53L1_dynamic_config_t   *pdynamic,
	VL53L1_system_control_t   *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t      *pzone_cfg,
	VL53L1_low_power_auto_data_t *plpadata);



VL53L1_Error VL53L1_preset_mode_low_power_auto_short_ranging(

	VL53L1_static_config_t    *pstatic,
	VL53L1_histogram_config_t *phistogram,
	VL53L1_general_config_t   *pgeneral,
	VL53L1_timing_config_t    *ptiming,
	VL53L1_dynamic_config_t   *pdynamic,
	VL53L1_system_control_t   *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t      *pzone_cfg,
	VL53L1_low_power_auto_data_t *plpadata);



VL53L1_Error VL53L1_preset_mode_low_power_auto_long_ranging(

	VL53L1_static_config_t    *pstatic,
	VL53L1_histogram_config_t *phistogram,
	VL53L1_general_config_t   *pgeneral,
	VL53L1_timing_config_t    *ptiming,
	VL53L1_dynamic_config_t   *pdynamic,
	VL53L1_system_control_t   *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t      *pzone_cfg,
	VL53L1_low_power_auto_data_t *plpadata);



VL53L1_Error VL53L1_preset_mode_histogram_ranging(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_histogram_ranging_with_mm1(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_histogram_ranging_with_mm2(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_histogram_ranging_mm1_cal(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_histogram_ranging_mm2_cal(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_histogram_ranging_ref(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_characterisation(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_histogram_xtalk_planar(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_histogram_xtalk_mm1(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);




VL53L1_Error VL53L1_preset_mode_histogram_xtalk_mm2(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_multizone(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_multizone_short_range(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_multizone_long_range(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_ranging_short_timing(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_long_range(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_medium_range(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_short_range(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_special_histogram_short_range(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_long_range_mm1(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_long_range_mm2(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_medium_range_mm1(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_medium_range_mm2(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_short_range_mm1(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_histogram_short_range_mm2(
	VL53L1_hist_post_process_config_t *phistpostprocess,
	VL53L1_static_config_t            *pstatic,
	VL53L1_histogram_config_t         *phistogram,
	VL53L1_general_config_t           *pgeneral,
	VL53L1_timing_config_t            *ptiming,
	VL53L1_dynamic_config_t           *pdynamic,
	VL53L1_system_control_t           *psystem,
	VL53L1_tuning_parm_storage_t      *ptuning_parms,
	VL53L1_zone_config_t              *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_olt(
	VL53L1_static_config_t     *pstatic,
	VL53L1_histogram_config_t  *phistogram,
	VL53L1_general_config_t    *pgeneral,
	VL53L1_timing_config_t     *ptiming,
	VL53L1_dynamic_config_t    *pdynamic,
	VL53L1_system_control_t    *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t       *pzone_cfg);



VL53L1_Error VL53L1_preset_mode_singleshot_ranging(

	VL53L1_static_config_t    *pstatic,
	VL53L1_histogram_config_t *phistogram,
	VL53L1_general_config_t   *pgeneral,
	VL53L1_timing_config_t    *ptiming,
	VL53L1_dynamic_config_t   *pdynamic,
	VL53L1_system_control_t   *psystem,
	VL53L1_tuning_parm_storage_t *ptuning_parms,
	VL53L1_zone_config_t      *pzone_cfg);




void VL53L1_copy_hist_cfg_to_static_cfg(
	VL53L1_histogram_config_t  *phistogram,
	VL53L1_static_config_t     *pstatic,
	VL53L1_general_config_t    *pgeneral,
	VL53L1_timing_config_t     *ptiming,
	VL53L1_dynamic_config_t    *pdynamic);



void VL53L1_copy_hist_bins_to_static_cfg(
	VL53L1_histogram_config_t *phistogram,
	VL53L1_static_config_t    *pstatic,
	VL53L1_timing_config_t    *ptiming);

#ifdef __cplusplus
}
#endif

#endif

