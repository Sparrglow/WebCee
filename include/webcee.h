/*
 * Copyright 2026 WebCee Author
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WEBCEE_H
#define WEBCEE_H

#ifdef __cplusplus
extern "C" {
#endif

#define WEBCEE_API

/* Initialization and Startup */
WEBCEE_API int wce_init(int port);                    // Initialize WebCee service
WEBCEE_API int wce_start(void);                       // Start service (non-blocking)
WEBCEE_API void wce_stop(void);                       // Stop service

/* Data Synchronization (C -> Frontend) */
WEBCEE_API void wce_data_set(const char* key, const char* val);     // Update single data
WEBCEE_API const char* wce_data_get(const char* key);               // Get data (Frontend -> C)

/* Function Registration (C -> Frontend) */
typedef void (*wce_func_t)(void);
WEBCEE_API void wce_register_function(const char* name, wce_func_t func);

/* Model Update Callback */
typedef void (*wce_model_update_handler_t)(const char* key, const char* val);
WEBCEE_API void wce_set_model_update_handler(wce_model_update_handler_t handler);

/* Utility Functions */
WEBCEE_API const char* wce_version(void);             // Get framework version
WEBCEE_API int wce_is_connected(void);                // Check frontend connection status
WEBCEE_API void wce_sleep(int ms);                    // Cross-platform sleep function (milliseconds)

/*
 * Optional: When a .wce file is bound via CMake's target_add_webcee_ui(),
 * WEBCEE_HAS_GENERATED=1 is automatically defined, and the generated directory is added to include path.
 * This allows users to include this header file to get generated interface declarations like WCE_EVT_*.
 *
 * Note: New version uses IR pipeline, no longer generates webcee_generated.h header file
 */

#include "webcee_build.h"

#ifdef __cplusplus
}
#endif

#endif // WEBCEE_H
