#include "OMaths.h"

NS_O_BEGIN
namespace maths {

    void dot_vec4_vec4(const vec4 &v0, const void *v1, int v1_stride, void *result, int result_stride, int count) {
		for (int i = 0; i < count; i++) {
			*(float*)result = v0 * *(const vec4*)v1;
			v1 = (char*)v1 + v1_stride;
			result = (char*)result + result_stride;
		}
	}

    void mul_mat4_vec3(const mat4 &m, const void *v, int v_stride, void *result, int result_stride, int count) {
		for (int i = 0; i < count; i++) {
			*(vec3*)result = m * *(const vec3*)v;
			v = (char*)v + v_stride;
			result = (char*)result + result_stride;
		}
	}

    void mul_mat4_vec4(const mat4 &m, const void *v, int v_stride, void *result, int result_stride, int count) {
		for (int i = 0; i < count; i++) {
			*(vec4*)result = m * *(const vec4*)v;
			v = (char*)v + v_stride;
			result = (char*)result + result_stride;
		}
	}

    void mul_mat4_mat4(const mat4 &m0, const mat4 &m1, mat4 &res) {
		res[0] = m0[0] * m1[0] + m0[4] * m1[1] + m0[8] * m1[2] + m0[12] * m1[3];
		res[1] = m0[1] * m1[0] + m0[5] * m1[1] + m0[9] * m1[2] + m0[13] * m1[3];
		res[2] = m0[2] * m1[0] + m0[6] * m1[1] + m0[10] * m1[2] + m0[14] * m1[3];
		res[3] = m0[3] * m1[0] + m0[7] * m1[1] + m0[11] * m1[2] + m0[15] * m1[3];
		res[4] = m0[0] * m1[4] + m0[4] * m1[5] + m0[8] * m1[6] + m0[12] * m1[7];
		res[5] = m0[1] * m1[4] + m0[5] * m1[5] + m0[9] * m1[6] + m0[13] * m1[7];
		res[6] = m0[2] * m1[4] + m0[6] * m1[5] + m0[10] * m1[6] + m0[14] * m1[7];
		res[7] = m0[3] * m1[4] + m0[7] * m1[5] + m0[11] * m1[6] + m0[15] * m1[7];
		res[8] = m0[0] * m1[8] + m0[4] * m1[9] + m0[8] * m1[10] + m0[12] * m1[11];
		res[9] = m0[1] * m1[8] + m0[5] * m1[9] + m0[9] * m1[10] + m0[13] * m1[11];
		res[10] = m0[2] * m1[8] + m0[6] * m1[9] + m0[10] * m1[10] + m0[14] * m1[11];
		res[11] = m0[3] * m1[8] + m0[7] * m1[9] + m0[11] * m1[10] + m0[15] * m1[11];
		res[12] = m0[0] * m1[12] + m0[4] * m1[13] + m0[8] * m1[14] + m0[12] * m1[15];
		res[13] = m0[1] * m1[12] + m0[5] * m1[13] + m0[9] * m1[14] + m0[13] * m1[15];
		res[14] = m0[2] * m1[12] + m0[6] * m1[13] + m0[10] * m1[14] + m0[14] * m1[15];
		res[15] = m0[3] * m1[12] + m0[7] * m1[13] + m0[11] * m1[14] + m0[15] * m1[15];
	}

}
NS_O_END