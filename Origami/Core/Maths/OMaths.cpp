#include "OMaths.h"

namespace Origami {namespace maths {

	/*****************************************************************************/
	/*                                                                           */
	/* default fpu codepath                                                      */
	/*                                                                           */
	/*****************************************************************************/

	/*
	*/
	static void dot_vec4_vec4_fpu(const vec4 &v0, const void *v1, int v1_stride, void *result, int result_stride, int count) {
		for (int i = 0; i < count; i++) {
			*(float*)result = v0 * *(const vec4*)v1;
			v1 = (char*)v1 + v1_stride;
			result = (char*)result + result_stride;
		}
	}

	/*
	*/
	static void mul_mat4_vec3_fpu(const mat4 &m, const void *v, int v_stride, void *result, int result_stride, int count) {
		for (int i = 0; i < count; i++) {
			*(vec3*)result = m * *(const vec3*)v;
			v = (char*)v + v_stride;
			result = (char*)result + result_stride;
		}
	}

	/*
	*/
	static void mul_mat4_vec4_fpu(const mat4 &m, const void *v, int v_stride, void *result, int result_stride, int count) {
		for (int i = 0; i < count; i++) {
			*(vec4*)result = m * *(const vec4*)v;
			v = (char*)v + v_stride;
			result = (char*)result + result_stride;
		}
	}

	/*
	*/
	static void mul_mat4_mat4_fpu(const mat4 &m0, const mat4 &m1, mat4 &res) {
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
	//
	///*****************************************************************************/
	///*                                                                           */
	///*                                                                           */
	///*                                                                           */
	///*****************************************************************************/
	//
	void(*dot_vec4_vec4)(const vec4 &v0, const void *v1, int v1_stride, void *result, int result_stride, int count) = dot_vec4_vec4_fpu;
	void(*mul_mat4_vec3)(const mat4 &m, const void *v, int v_stride, void *result, int result_stride, int count) = mul_mat4_vec3_fpu;
	void(*mul_mat4_vec4)(const mat4 &m, const void *v, int v_stride, void *result, int result_stride, int count) = mul_mat4_vec4_fpu;
	void(*mul_mat4_mat4)(const mat4 &m0, const mat4 &m1, mat4 &res) = mul_mat4_mat4_fpu;
	//
	///*****************************************************************************/
	///*                                                                           */
	///* SSE codepath                                                              */
	///*                                                                           */
	///*****************************************************************************/
	//
	///*
	// */
	//static void dot_vec4_vec4_sse(const vec4 &v0,const void *v1,int v1_stride,void *result,int result_stride,int count) {
	//	
	//	if(count == 0) return;
	//	
	//#ifdef _WIN32
	//	__asm {
	//		pusha
	//		
	//		mov eax, v0
	//		mov ebx, v1
	//		mov ecx, v1_stride
	//		mov edx, result
	//		mov esi, result_stride
	//		mov edi, count
	//		
	//		movups xmm0, [eax]
	//		
	//		label:
	//		movups xmm1, [ebx]
	//		
	//		mulps xmm1, xmm0
	//		
	//		movhlps xmm2, xmm1
	//		addps xmm1, xmm2
	//		
	//		movss xmm2, xmm1
	//		shufps xmm1, xmm1, 00000001b
	//		addss xmm1, xmm2
	//		movss [edx], xmm1
	//		
	//		add ebx, ecx
	//		add edx, esi
	//		
	//		dec edi
	//		jnz label
	//		
	//		popa
	//	}
	//#else
	//	__asm__ (
	//		"movups (%%eax), %%xmm0\n"
	//		
	//		"1:\n"
	//		"movups (%%ebx), %%xmm1\n"
	//		
	//		"mulps %%xmm0, %%xmm1\n"
	//		
	//		"movhlps %%xmm1, %%xmm2\n"
	//		"addps %%xmm2, %%xmm1\n"
	//		
	//		"movss %%xmm1, %%xmm2\n"
	//		"shufps $0b00000001, %%xmm1, %%xmm1\n"
	//		"addss %%xmm2, %%xmm1\n"
	//		"movss %%xmm1, (%%edx)\n"
	//		
	//		"addl %%ecx, %%ebx\n"
	//		"addl %%esi, %%edx\n"
	//		
	//		"decl %%edi\n"
	//		"jnz 1b\n"
	//		:
	//		: "a"(&v0.x), "b"(v1), "c"(v1_stride), "d"(result), "S"(result_stride), "D"(count)
	//	);
	//#endif
	//}
	//
	///*
	// */
	//void mul_mat4_mat4_sse(const mat4 &m0,const mat4 &m1,mat4 &res) {
	//
	//#ifdef _WIN32
	//	__asm {
	//		push eax
	//		push ebx
	//		push ecx
	//		
	//		mov eax, m0
	//		mov ebx, m1
	//		mov ecx, res
	//		
	//		movups xmm0, [eax]
	//		movups xmm1, [eax + 16]
	//		movups xmm2, [eax + 32]
	//		movups xmm3, [eax + 48]
	//		
	//		movups xmm4, [ebx]
	//		movaps xmm5, xmm4
	//		movaps xmm6, xmm4
	//		movaps xmm7, xmm4
	//		shufps xmm4, xmm4, 00000000b
	//		shufps xmm5, xmm5, 01010101b
	//		shufps xmm6, xmm6, 10101010b
	//		shufps xmm7, xmm7, 11111111b
	//		mulps xmm4, xmm0
	//		mulps xmm5, xmm1
	//		mulps xmm6, xmm2
	//		mulps xmm7, xmm3
	//		addps xmm6, xmm7
	//		addps xmm4, xmm5
	//		addps xmm4, xmm6
	//		movups [ecx], xmm4
	//		
	//		movups xmm4, [ebx + 16]
	//		movaps xmm5, xmm4
	//		movaps xmm6, xmm4
	//		movaps xmm7, xmm4
	//		shufps xmm4, xmm4, 00000000b
	//		shufps xmm5, xmm5, 01010101b
	//		shufps xmm6, xmm6, 10101010b
	//		shufps xmm7, xmm7, 11111111b
	//		mulps xmm4, xmm0
	//		mulps xmm5, xmm1
	//		mulps xmm6, xmm2
	//		mulps xmm7, xmm3
	//		addps xmm6, xmm7
	//		addps xmm4, xmm5
	//		addps xmm4, xmm6
	//		movups [ecx + 16], xmm4
	//		
	//		movups xmm4, [ebx + 32]
	//		movaps xmm5, xmm4
	//		movaps xmm6, xmm4
	//		movaps xmm7, xmm4
	//		shufps xmm4, xmm4, 00000000b
	//		shufps xmm5, xmm5, 01010101b
	//		shufps xmm6, xmm6, 10101010b
	//		shufps xmm7, xmm7, 11111111b
	//		mulps xmm4, xmm0
	//		mulps xmm5, xmm1
	//		mulps xmm6, xmm2
	//		mulps xmm7, xmm3
	//		addps xmm6, xmm7
	//		addps xmm4, xmm5
	//		addps xmm4, xmm6
	//		movups [ecx + 32], xmm4
	//		
	//		movups xmm4, [ebx + 48]
	//		movaps xmm5, xmm4
	//		movaps xmm6, xmm4
	//		movaps xmm7, xmm4
	//		shufps xmm4, xmm4, 00000000b
	//		shufps xmm5, xmm5, 01010101b
	//		shufps xmm6, xmm6, 10101010b
	//		shufps xmm7, xmm7, 11111111b
	//		mulps xmm4, xmm0
	//		mulps xmm5, xmm1
	//		mulps xmm6, xmm2
	//		mulps xmm7, xmm3
	//		addps xmm6, xmm7
	//		addps xmm4, xmm5
	//		addps xmm4, xmm6
	//		movups [ecx + 48], xmm4
	//		
	//		pop ecx
	//		pop ebx
	//		pop eax
	//	}
	//#else
	//	__asm__ (
	//		"movups (%%eax), %%xmm0\n"
	//		"movups 16(%%eax), %%xmm1\n"
	//		"movups 32(%%eax), %%xmm2\n"
	//		"movups 48(%%eax), %%xmm3\n"
	//		
	//		"movups (%%ebx), %%xmm4\n"
	//		"movaps %%xmm4, %%xmm5\n"
	//		"movaps %%xmm4, %%xmm6\n"
	//		"movaps %%xmm4, %%xmm7\n"
	//		"shufps $0b00000000, %%xmm4, %%xmm4\n"
	//		"shufps $0b01010101, %%xmm5, %%xmm5\n"
	//		"shufps $0b10101010, %%xmm6, %%xmm6\n"
	//		"shufps $0b11111111, %%xmm7, %%xmm7\n"
	//		"mulps %%xmm0, %%xmm4\n"
	//		"mulps %%xmm1, %%xmm5\n"
	//		"mulps %%xmm2, %%xmm6\n"
	//		"mulps %%xmm3, %%xmm7\n"
	//		"addps %%xmm7, %%xmm6\n"
	//		"addps %%xmm5, %%xmm4\n"
	//		"addps %%xmm6, %%xmm4\n"
	//		"movups %%xmm4, (%%ecx)\n"
	//		
	//		"movups 16(%%ebx), %%xmm4\n"
	//		"movaps %%xmm4, %%xmm5\n"
	//		"movaps %%xmm4, %%xmm6\n"
	//		"movaps %%xmm4, %%xmm7\n"
	//		"shufps $0b00000000, %%xmm4, %%xmm4\n"
	//		"shufps $0b01010101, %%xmm5, %%xmm5\n"
	//		"shufps $0b10101010, %%xmm6, %%xmm6\n"
	//		"shufps $0b11111111, %%xmm7, %%xmm7\n"
	//		"mulps %%xmm0, %%xmm4\n"
	//		"mulps %%xmm1, %%xmm5\n"
	//		"mulps %%xmm2, %%xmm6\n"
	//		"mulps %%xmm3, %%xmm7\n"
	//		"addps %%xmm7, %%xmm6\n"
	//		"addps %%xmm5, %%xmm4\n"
	//		"addps %%xmm6, %%xmm4\n"
	//		"movups %%xmm4, 16(%%ecx)\n"
	//		
	//		"movups 32(%%ebx), %%xmm4\n"
	//		"movaps %%xmm4, %%xmm5\n"
	//		"movaps %%xmm4, %%xmm6\n"
	//		"movaps %%xmm4, %%xmm7\n"
	//		"shufps $0b00000000, %%xmm4, %%xmm4\n"
	//		"shufps $0b01010101, %%xmm5, %%xmm5\n"
	//		"shufps $0b10101010, %%xmm6, %%xmm6\n"
	//		"shufps $0b11111111, %%xmm7, %%xmm7\n"
	//		"mulps %%xmm0, %%xmm4\n"
	//		"mulps %%xmm1, %%xmm5\n"
	//		"mulps %%xmm2, %%xmm6\n"
	//		"mulps %%xmm3, %%xmm7\n"
	//		"addps %%xmm7, %%xmm6\n"
	//		"addps %%xmm5, %%xmm4\n"
	//		"addps %%xmm6, %%xmm4\n"
	//		"movups %%xmm4, 32(%%ecx)\n"
	//		
	//		"movups 48(%%ebx), %%xmm4\n"
	//		"movaps %%xmm4, %%xmm5\n"
	//		"movaps %%xmm4, %%xmm6\n"
	//		"movaps %%xmm4, %%xmm7\n"
	//		"shufps $0b00000000, %%xmm4, %%xmm4\n"
	//		"shufps $0b01010101, %%xmm5, %%xmm5\n"
	//		"shufps $0b10101010, %%xmm6, %%xmm6\n"
	//		"shufps $0b11111111, %%xmm7, %%xmm7\n"
	//		"mulps %%xmm0, %%xmm4\n"
	//		"mulps %%xmm1, %%xmm5\n"
	//		"mulps %%xmm2, %%xmm6\n"
	//		"mulps %%xmm3, %%xmm7\n"
	//		"addps %%xmm7, %%xmm6\n"
	//		"addps %%xmm5, %%xmm4\n"
	//		"addps %%xmm6, %%xmm4\n"
	//		"movups %%xmm4, 48(%%ecx)\n"
	//		:
	//		: "a"(m0.mat), "b"(m1.mat), "c"(res.mat)
	//	);
	//#endif
	//}
	//
	///*
	// */
	//static void mul_mat4_vec3_sse(const mat4 &m,const void *v,int v_stride,void *result,int result_stride,int count) {
	//	
	//	if(count == 0) return;
	//	
	//#ifdef _WIN32
	//	__asm {
	//		pusha
	//		
	//		mov eax, m
	//		mov ebx, v
	//		mov ecx, v_stride
	//		mov edx, result
	//		mov esi, result_stride
	//		mov edi, count
	//		
	//		movups xmm0, [eax]
	//		movups xmm1, [eax + 16]
	//		movups xmm2, [eax + 32]
	//		movups xmm3, [eax + 48]		
	//		
	//		label:
	//		
	//		movss xmm4, [ebx + 8]
	//		movlhps xmm4, xmm4
	//		movlps xmm4, [ebx]
	//		
	//		movaps xmm5, xmm4
	//		movaps xmm6, xmm4
	//		
	//		shufps xmm4, xmm4, 00000000b
	//		shufps xmm5, xmm5, 01010101b
	//		shufps xmm6, xmm6, 10101010b
	//		
	//		mulps xmm4, xmm0
	//		mulps xmm5, xmm1
	//		mulps xmm6, xmm2
	//		
	//		addps xmm6, xmm3
	//		addps xmm4, xmm5
	//		addps xmm4, xmm6
	//		
	//		movlps [edx], xmm4
	//		movhlps xmm4, xmm4
	//		movss [edx + 8], xmm4		
	//		
	//		add ebx, ecx
	//		add edx, esi
	//		
	//		dec edi
	//		jnz label
	//		
	//		popa
	//	}
	//#else
	//	__asm__ (
	//		"movups (%%eax), %%xmm0\n"
	//		"movups 16(%%eax), %%xmm1\n"
	//		"movups 32(%%eax), %%xmm2\n"
	//		"movups 48(%%eax), %%xmm3\n"
	//		
	//		"1:\n"
	//		
	//		"movss 8(%%ebx), %%xmm4\n"
	//		"movlhps %%xmm4, %%xmm4\n"
	//		"movlps (%%ebx), %%xmm4\n"
	//		
	//		"movaps %%xmm4, %%xmm5\n"
	//		"movaps %%xmm4, %%xmm6\n"
	//		
	//		"shufps $0b00000000, %%xmm4, %%xmm4\n"
	//		"shufps $0b01010101, %%xmm5, %%xmm5\n"
	//		"shufps $0b10101010, %%xmm6, %%xmm6\n"
	//		
	//		"mulps %%xmm0, %%xmm4\n"
	//		"mulps %%xmm1, %%xmm5\n"
	//		"mulps %%xmm2, %%xmm6\n"
	//		
	//		"addps %%xmm3, %%xmm6\n"
	//		"addps %%xmm5, %%xmm4\n"
	//		"addps %%xmm6, %%xmm4\n"
	//		
	//		"movlps %%xmm4, (%%edx)\n"
	//		"movhlps %%xmm4, %%xmm4\n"
	//		"movss %%xmm4, 8(%%edx)\n"
	//		
	//		"addl %%ecx, %%ebx\n"
	//		"addl %%esi, %%edx\n"
	//		
	//		"decl %%edi\n"
	//		"jnz 1b\n"
	//		:
	//		: "a"(m.mat), "b"(v), "c"(v_stride), "d"(result), "S"(result_stride), "D"(count)
	//	);
	//#endif
	//}
	//
	///*
	// */
	//static void mul_mat4_vec4_sse(const mat4 &m,const void *v,int v_stride,void *result,int result_stride,int count) {
	//	
	//	if(count == 0) return;
	//	
	//#ifdef _WIN32
	//	__asm {
	//		pusha
	//		
	//		mov eax, m
	//		mov ebx, v
	//		mov ecx, v_stride
	//		mov edx, result
	//		mov esi, result_stride
	//		mov edi, count
	//		
	//		movups xmm0, [eax]
	//		movups xmm1, [eax + 16]
	//		movups xmm2, [eax + 32]
	//		movups xmm3, [eax + 48]		
	//		
	//		label:
	//		
	//		movups xmm4, [ebx]
	//		movaps xmm5, xmm4
	//		movaps xmm6, xmm4
	//		movaps xmm7, xmm4
	//		
	//		shufps xmm4, xmm4, 00000000b
	//		shufps xmm5, xmm5, 01010101b
	//		shufps xmm6, xmm6, 10101010b
	//		shufps xmm7, xmm7, 11111111b
	//		
	//		mulps xmm4, xmm0
	//		mulps xmm5, xmm1
	//		mulps xmm6, xmm2
	//		mulps xmm7, xmm3
	//		
	//		addps xmm6, xmm7
	//		addps xmm4, xmm5
	//		addps xmm4, xmm6
	//		
	//		movups [edx], xmm4		
	//		
	//		add ebx, ecx
	//		add edx, esi
	//		
	//		dec edi
	//		jnz label
	//		
	//		popa
	//	}
	//#else
	//	__asm__ (
	//		"movups (%%eax), %%xmm0\n"
	//		"movups 16(%%eax), %%xmm1\n"
	//		"movups 32(%%eax), %%xmm2\n"
	//		"movups 48(%%eax), %%xmm3\n"
	//		
	//		"1:\n"
	//		
	//		"movups (%%ebx), %%xmm4\n"
	//		"movaps %%xmm4, %%xmm5\n"
	//		"movaps %%xmm4, %%xmm6\n"
	//		"movaps %%xmm4, %%xmm7\n"
	//		
	//		"shufps $0b00000000, %%xmm4, %%xmm4\n"
	//		"shufps $0b01010101, %%xmm5, %%xmm5\n"
	//		"shufps $0b10101010, %%xmm6, %%xmm6\n"
	//		"shufps $0b11111111, %%xmm7, %%xmm7\n"
	//		
	//		"mulps %%xmm0, %%xmm4\n"
	//		"mulps %%xmm1, %%xmm5\n"
	//		"mulps %%xmm2, %%xmm6\n"
	//		"mulps %%xmm3, %%xmm7\n"
	//		
	//		"addps %%xmm7, %%xmm6\n"
	//		"addps %%xmm5, %%xmm4\n"
	//		"addps %%xmm6, %%xmm4\n"
	//		
	//		"movups %%xmm4, (%%edx)\n"
	//		
	//		"addl %%ecx, %%ebx\n"
	//		"addl %%esi, %%edx\n"
	//		
	//		"decl %%edi\n"
	//		"jnz 1b\n"
	//		:
	//		: "a"(m.mat), "b"(v), "c"(v_stride), "d"(result), "S"(result_stride), "D"(count)
	//	);
	//#endif
	//}
	//
	///*****************************************************************************/
	///*                                                                           */
	///* SSE3 codepath                                                             */
	///*                                                                           */
	///*****************************************************************************/
	//
	///*
	// */
	//static void dot_vec4_vec4_sse3(const vec4 &v0,const void *v1,int v1_stride,void *result,int result_stride,int count) {
	//	
	//	if(count == 0) return;
	//	
	//#ifdef _WIN32
	//	__asm {
	//	}
	//#else
	//	__asm__ (
	//		"movups (%%eax), %%xmm0\n"
	//		
	//		"1:\n"
	//		"movups (%%ebx), %%xmm1\n"
	//		
	//		"mulps %%xmm0, %%xmm1\n"
	//		
	//		"haddps %%xmm1, %%xmm1\n"
	//		"haddps %%xmm1, %%xmm1\n"
	//		"movss %%xmm1, (%%edx)\n"
	//		
	//		"addl %%ecx, %%ebx\n"
	//		"addl %%esi, %%edx\n"
	//		
	//		"decl %%edi\n"
	//		"jnz 1b\n"
	//		:
	//		: "a"(&v0.x), "b"(v1), "c"(v1_stride), "d"(result), "S"(result_stride), "D"(count)
	//	);
	//#endif
	//}
	//
	///*****************************************************************************/
	///*                                                                           */
	///* 3DNow codepath                                                            */
	///*                                                                           */
	///*****************************************************************************/
	//
	///*
	// */
	//static void dot_vec4_vec4_3dnow(const vec4 &v0,const void *v1,int v1_stride,void *result,int result_stride,int count) {
	//	
	//	if(count == 0) return;
	//	
	//#ifdef _WIN32
	//	__asm {
	//		pusha
	//		
	//		mov eax, v0
	//		mov ebx, v1
	//		mov ecx, v1_stride
	//		mov edx, result
	//		mov esi, result_stride
	//		mov edi, count
	//		
	//		movq mm0, [eax]
	//		movq mm1, [eax + 8]
	//		
	//		label:
	//		movq mm2, [ebx]
	//		movq mm3, [ebx + 8]
	//		
	//		pfmul mm2, mm0
	//		pfmul mm3, mm1
	//		
	//		pfadd mm3, mm2
	//		pfacc mm3, mm3
	//		
	//		movd [edx], mm3
	//		
	//		add ebx, ecx
	//		add edx, esi
	//		
	//		dec edi
	//		jnz label
	//		
	//		femms
	//		
	//		popa
	//	}
	//#else
	//	__asm__ (
	//		"movq (%%eax), %%mm0\n"
	//		"movq 8(%%eax), %%mm1\n"
	//		
	//		"1:\n"
	//		
	//		"movq (%%ebx), %%mm2\n"
	//		"movq 8(%%ebx), %%mm3\n"
	//		
	//		"pfmul %%mm0, %%mm2\n"
	//		"pfmul %%mm1, %%mm3\n"
	//		
	//		"pfadd %%mm2, %%mm3\n"
	//		"pfacc %%mm3, %%mm3\n"
	//		
	//		"movd %%mm3, (%%edx)\n"
	//		
	//		"addl %%ecx, %%ebx\n"
	//		"addl %%esi, %%edx\n"
	//		
	//		"decl %%edi\n"
	//		"jnz 1b\n"
	//		
	//		"femms\n"
	//		:
	//		: "a"(&v0.x), "b"(v1), "c"(v1_stride), "d"(result), "S"(result_stride), "D"(count)
	//	);
	//#endif
	//}
	//
	///*****************************************************************************/
	///*                                                                           */
	///*                                                                           */
	///*                                                                           */
	///*****************************************************************************/
	//
	///*
	// */
	//void mathlib_set_codepath(int codepath) {
	//	if(codepath == MATHLIB_FPU) {
	//		dot_vec4_vec4 = dot_vec4_vec4_fpu;
	//		
	//		mul_mat4_vec3 = mul_mat4_vec3_fpu;
	//		mul_mat4_mat4 = mul_mat4_mat4_fpu;
	//		
	//		mul_mat4_vec4 = mul_mat4_vec4_fpu;
	//	}
	//	else if(codepath == MATHLIB_SSE) {
	//		dot_vec4_vec4 = dot_vec4_vec4_sse;
	//		
	//		mul_mat4_vec3 = mul_mat4_vec3_sse;
	//		mul_mat4_mat4 = mul_mat4_mat4_sse;
	//		
	//		mul_mat4_vec4 = mul_mat4_vec4_sse;
	//	}
	//	else if(codepath == MATHLIB_SSE3) {
	//		dot_vec4_vec4 = dot_vec4_vec4_sse3;
	//	}
	//	else if(codepath == MATHLIB_3DNOW) {
	//		dot_vec4_vec4 = dot_vec4_vec4_3dnow;
	//	}
	//	else {
	//		
	//		dot_vec4_vec4 = dot_vec4_vec4_fpu;
	//		
	//		mul_mat4_vec3 = mul_mat4_vec3_fpu;
	//		mul_mat4_mat4 = mul_mat4_mat4_fpu;
	//		
	//		mul_mat4_vec4 = mul_mat4_vec4_fpu;
	//	}
	//}

}}