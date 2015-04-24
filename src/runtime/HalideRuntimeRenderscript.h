#ifndef HALIDE_RUNTIME_RENDERSCRIPT_H
#define HALIDE_RUNTIME_RENDERSCRIPT_H

#include "HalideRuntime.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file
 *  Routines specific to the Halide Renderscript runtime.
 */

extern const struct halide_device_interface *halide_renderscript_device_interface();

/** These are forward declared here to allow clients to override the
 *  Halide RS runtime. Do not call them. */
// @{
extern int halide_renderscript_initialize_kernels(void *user_context, void **state_ptr,
                                        const char *src, int size);
extern int halide_renderscript_run(void *user_context, void *state_ptr,
                         const char *entry_name, int blocksX, int blocksY,
                         int blocksZ, int threadsX, int threadsY, int threadsZ,
                         int shared_mem_bytes, size_t arg_sizes[], void *args[],
                         int8_t arg_is_buffer[], int num_attributes,
                         float *vertex_buffer, int num_coords_dim0,
                         int num_coords_dim1);
// @}

/** Set the platform name for OpenCL to use (e.g. "Intel" or
 * "NVIDIA"). The argument is copied internally. The opencl runtime
 * will select a platform that includes this as a substring. If never
 * called, Halide uses the environment variable HL_OCL_PLATFORM_NAME,
 * or defaults to the first available platform. */
// extern void halide_renderscript_set_platform_name(const char *n);

/* Halide calls this to get the desired OpenCL platform
 * name. Implement this yourself to use a different platform per
 * user_context. The default implementation returns the value set by
 * halide_set_ocl_platform_name, or the value of the environment
 * variable HL_OCL_PLATFORM_NAME. The output is valid until the next
 * call to halide_set_ocl_platform_name. */
// extern const char *halide_renderscript_get_platform_name(void *user_context);

/** Set the device type for OpenCL to use. The argument is copied
 * internally. It must be "cpu", "gpu", or "acc". If never called,
 * Halide uses the environment variable HL_OCL_DEVICE_TYPE. */
// extern void halide_renderscript_set_device_type(const char *n);

/** Halide calls this to gets the desired OpenCL device
 * type. Implement this yourself to use a different device type per
 * user_context. The default implementation returns the value set by
 * halide_set_ocl_device_type, or the environment variable
 * HL_OCL_DEVICE_TYPE. The result is valid until the next call to
 * halide_set_ocl_device_type. */
// extern const char *halide_renderscript_get_device_type(void *user_context);

/** Set the underlying cl_mem for a buffer_t. This memory should be
 * allocated using clCreateBuffer or similar and must have an extent
 * large enough to cover that specified by the buffer_t extent
 * fields. The dev field of the buffer_t must be NULL when this
 * routine is called. This call can fail due to running out of memory
 * or being passed an invalid device pointer. The device and host
 * dirty bits are left unmodified. */
extern int halide_renderscript_wrap_cl_mem(void *user_context, struct buffer_t *buf,
                                 uintptr_t device_ptr);

/** Disconnect a buffer_t from the memory it was previously wrapped
 * around. Should only be called for a buffer_t that
 * halide_renderscript_wrap_device_ptr was previously called on. Frees any
 * storage associated with the binding of the buffer_t and the device
 * pointer, but does not free the cl_mem. The previously wrapped
 * cl_mem is returned. The dev field of the buffer_t will be NULL on
 * return.
 */
extern uintptr_t halide_renderscript_detach_cl_mem(void *user_context,
                                         struct buffer_t *buf);

/** Return the underlying cl_mem for a buffer_t. This buffer must be
 *  valid on an OpenCL device, or not have any associated device
 *  memory. If there is no device memory (dev field is NULL), this
 *  returns 0.
 */
extern uintptr_t halide_renderscript_get_cl_mem(void *user_context, struct buffer_t *buf);

#ifdef __cplusplus
}  // End extern "C"
#endif

#endif  // HALIDE_RUNTIME_RENDERSCRIPT_H