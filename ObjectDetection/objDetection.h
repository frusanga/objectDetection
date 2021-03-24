/* 
Object Detection 
*/

#ifndef ACC_DETECTOR_DISTANCE_H_
#define ACC_DETECTOR_DISTANCE_H_

#include <stdbool.h>
#include <stdint.h>
#include "acc_definitions.h"
#include "acc_service_iq.h"
#include "acc_base_configuration.h"
#include "acc_service.h"

typedef struct
{
	/** Start of measurement in meters, derived from request set by @ref acc_detector_distance_configuration_requested_start_set */
	float start_m;
	/** Length of measurement in meters, derived from request set by @ref acc_detector_distance_configuration_requested_length_set */
	float length_m;
	/** Length needed for potential background, used in @ref acc_detector_distance_record_background */
	uint16_t background_length;
} acc_detector_distance_metadata_t;

typedef enum
{
	ACC_DETECTOR_DISTANCE_THRESHOLD_TYPE_FIXED,
	ACC_DETECTOR_DISTANCE_THRESHOLD_TYPE_RECORDED,
	ACC_DETECTOR_DISTANCE_THRESHOLD_TYPE_CFAR
} acc_detector_distance_threshold_type_t;

typedef enum
{
	/* Return peaks with the closest detection first. */
	ACC_DETECTOR_DISTANCE_PEAK_SORTING_CLOSEST_FIRST,
	/* Return peaks with the peak with the highest amplitude first. */
	ACC_DETECTOR_DISTANCE_PEAK_SORTING_STRONGEST_FIRST,
	/* Return peaks with the peak from the strongest reflector first.
	   The decrease in amplitude over distance is accounted for.
	   Cannot be combined with negative start range. */
	ACC_DETECTOR_DISTANCE_PEAK_SORTING_STRONGEST_REFLECTOR_FIRST,
	/* Return peaks with the peak from the strongest flat reflector first.
	   The decrease in amplitude over distance is accounted for.
	   Cannot be combined with negative start range. */
	ACC_DETECTOR_DISTANCE_PEAK_SORTING_STRONGEST_FLAT_REFLECTOR_FIRST
} acc_detector_distance_peak_sorting_t;
struct acc_detector_distance_handle;

typedef struct acc_detector_distance_handle *acc_detector_distance_handle_t;

struct acc_detector_distance_configuration;

typedef struct acc_detector_distance_configuration *acc_detector_distance_configuration_t;

typedef struct
{
	uint16_t amplitude;
	float    distance_m;
} acc_detector_distance_result_t;

typedef void (*acc_detector_distance_service_data_callback_t)(const uint16_t *data, uint16_t data_length);

acc_detector_distance_configuration_t acc_detector_distance_configuration_create(void);

void acc_detector_distance_configuration_destroy(acc_detector_distance_configuration_t *distance_configuration);

acc_detector_distance_handle_t acc_detector_distance_create(acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_destroy(acc_detector_distance_handle_t *distance_handle);
bool acc_detector_distance_activate(acc_detector_distance_handle_t distance_handle);
bool acc_detector_distance_deactivate(acc_detector_distance_handle_t distance_handle);
bool acc_detector_distance_reconfigure(acc_detector_distance_handle_t        *distance_handle,
                                       acc_detector_distance_configuration_t distance_configuration);
									
bool acc_detector_distance_metadata_get(acc_detector_distance_handle_t   distance_handle,
                                        acc_detector_distance_metadata_t *metadata);
bool acc_detector_distance_record_background(acc_detector_distance_handle_t                   distance_handle,
                                             uint16_t                                         *background,
                                             uint16_t                                         background_length,
                                             acc_detector_distance_recorded_background_info_t *background_info);
bool acc_detector_distance_set_background(acc_detector_distance_handle_t distance_handle, const uint16_t *background, uint16_t background_length);

bool acc_detector_distance_get_next(acc_detector_distance_handle_t      distance_handle,
                                    acc_detector_distance_result_t      *result,
                                    uint16_t                            result_length,
                                    acc_detector_distance_result_info_t *result_info);
acc_sensor_id_t acc_detector_distance_configuration_sensor_get(acc_detector_distance_configuration_t distance_configuration);
void acc_detector_distance_configuration_sensor_set(acc_detector_distance_configuration_t distance_configuration, acc_sensor_id_t sensor_id);
float acc_detector_distance_configuration_requested_start_get(acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_requested_start_set(acc_detector_distance_configuration_t distance_configuration, float start_m);
float acc_detector_distance_configuration_requested_length_get(acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_requested_length_set(acc_detector_distance_configuration_t distance_configuration, float length_m);
									   
uint16_t acc_detector_distance_configuration_downsampling_factor_get(acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_downsampling_factor_set(acc_detector_distance_configuration_t distance_configuration,
                                                                 uint16_t                              downsampling_factor); 
acc_service_profile_t acc_detector_distance_configuration_service_profile_get(acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_service_profile_set(acc_detector_distance_configuration_t distance_configuration,
                                                             acc_service_profile_t                 service_profile);
bool acc_detector_distance_configuration_maximize_signal_attenuation_get(acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_maximize_signal_attenuation_set(acc_detector_distance_configuration_t distance_configuration,
                                                                         bool                                  maximize_signal_attenuation);
float acc_detector_distance_configuration_receiver_gain_get(acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_receiver_gain_set(acc_detector_distance_configuration_t distance_configuration, float gain);

uint8_t acc_detector_distance_configuration_hw_accelerated_average_samples_get(
	acc_detector_distance_configuration_t distance_configuration);
void acc_detector_distance_configuration_hw_accelerated_average_samples_set(
	acc_detector_distance_configuration_t distance_configuration, uint8_t samples);
uint16_t acc_detector_distance_configuration_sweep_averaging_get(
	acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_sweep_averaging_set(acc_detector_distance_configuration_t distance_configuration,
                                                             uint16_t                              sweep_averaging);

acc_detector_distance_threshold_type_t acc_detector_distance_configuration_threshold_type_get(
	acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_threshold_type_set(acc_detector_distance_configuration_t  distance_configuration,
                                                            acc_detector_distance_threshold_type_t threshold);
uint16_t acc_detector_distance_configuration_fixed_threshold_get(acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_fixed_threshold_set(acc_detector_distance_configuration_t distance_configuration,
                                                             uint16_t                              threshold);

uint16_t acc_detector_distance_configuration_record_background_sweeps_get(
	acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_record_background_sweeps_set(
	acc_detector_distance_configuration_t distance_configuration, uint16_t record_sweeps);
float acc_detector_distance_configuration_threshold_sensitivity_get(
	acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_threshold_sensitivity_set(
	acc_detector_distance_configuration_t distance_configuration,
	float                                 sensitivity);

float acc_detector_distance_configuration_cfar_threshold_guard_get(
	acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_cfar_threshold_guard_set(
	acc_detector_distance_configuration_t distance_configuration,
	float                                 guard_m);
float acc_detector_distance_configuration_cfar_threshold_window_get(
	acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_cfar_threshold_window_set(
	acc_detector_distance_configuration_t distance_configuration,
	float                                 window_m);

bool acc_detector_distance_configuration_cfar_threshold_only_lower_distance_get(
	acc_detector_distance_configuration_t distance_configuration);

void acc_detector_distance_configuration_cfar_threshold_only_lower_distance_set(
	acc_detector_distance_configuration_t distance_configuration,
	bool                                  only_lower_distance);
acc_detector_distance_peak_sorting_t acc_detector_distance_configuration_peak_sorting_get(
	acc_detector_distance_configuration_t distance_configuration);
void acc_detector_distance_configuration_peak_sorting_set(acc_detector_distance_configuration_t distance_configuration,
                                                          acc_detector_distance_peak_sorting_t  peak_sorting);
float acc_detector_distance_configuration_peak_merge_limit_get(acc_detector_distance_configuration_t distance_configuration);
void acc_detector_distance_configuration_peak_merge_limit_set(acc_detector_distance_configuration_t distance_configuration,
                                                              float                                 peak_merge_limit_m);

void acc_detector_distance_configuration_service_data_callback_set(
	acc_detector_distance_configuration_t         distance_configuration,
	acc_detector_distance_service_data_callback_t service_data_callback);


#endif