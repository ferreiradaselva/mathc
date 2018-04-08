/*
Copyright © 2018 Felipe Ferreira da Silva

This software is provided 'as-is', without any express or implied warranty. In
no event will the authors be held liable for any damages arising from the use of
this software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to
the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim
     that you wrote the original software. If you use this software in a
     product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include "mathc.h"

#define EPSILON_1 MFLT_EPSILON
#define EPSILON_10 (MFLT_EPSILON * MFLOAT_C(10.0))
#define EPSILON_100 (MFLT_EPSILON * MFLOAT_C(100.0))
#define EPSILON_1000 (MFLT_EPSILON * MFLOAT_C(1000.0))

struct cerror {
	int32_t failed;
	int32_t passed;
	int32_t passed_with_e10;
	int32_t passed_with_e100;
	int32_t passed_with_e1000;
};

void printf_bool_test(struct cerror *error, char *msg, bool e, bool r)
{
	
	if (e == r) {
		error->passed = error->passed + 1;
	} else {
		error->failed = error->failed + 1;
		printf("%s failed:\n\tExpected  ", msg);
		if (e) {
			printf("true\n");
		} else {
			printf("false\n");
		}
		if (r) {
			printf("\t  Actual  true\n");
		} else {
			printf("\t  Actual  false\n");
		}
	}
}

void printf_1f_test(struct cerror *error, char *msg, mfloat_t e, mfloat_t r)
{
	if (nearly_equal(e, r, EPSILON_1)) {
		error->passed = error->passed + 1;
	} else if (nearly_equal(e, r, EPSILON_10)) {
		error->passed_with_e10 = error->passed_with_e10 + 1;
		printf("%s passed with epsilon * 10.0:\n\tExpected % .16lf\n\t  Actual % .16lf\n", msg, e, r);
	} else if (nearly_equal(e, r, EPSILON_100)) {
		error->passed_with_e100 = error->passed_with_e100 + 1;
		printf("%s passed with epsilon * 100.0:\n\tExpected % .16lf\n\t  Actual % .16lf\n", msg, e, r);
	} else if (nearly_equal(e, r, EPSILON_1000)) {
		error->passed_with_e1000 = error->passed_with_e1000 + 1;
		printf("%s passed with epsilon * 1000.0:\n\tExpected % .16lf\n\t  Actual % .16lf\n", msg, e, r);
	} else {
		error->failed = error->failed + 1;
		printf("%s failed:\n\tExpected % .16lf\n\t  Actual % .16lf\n", msg, e, r);
	}
}

void printf_2f_test(struct cerror *error, char *msg, struct vec2 e, struct vec2 r)
{
	if (svec2_is_nearly_equal(e, r, EPSILON_1)) {
		error->passed = error->passed + 1;
	} else if (svec2_is_nearly_equal(e, r, EPSILON_10)) {
		error->passed_with_e10 = error->passed_with_e10 + 1;
		printf("%s passed with epsilon * 10.0:\n\tExpected % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf\n", msg, e.x, e.y, r.x, r.y);
	} else if (svec2_is_nearly_equal(e, r, EPSILON_100)) {
		error->passed_with_e100 = error->passed_with_e100 + 1;
		printf("%s passed with epsilon * 100.0:\n\tExpected % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf\n", msg, e.x, e.y, r.x, r.y);
	} else if (svec2_is_nearly_equal(e, r, EPSILON_1000)) {
		error->passed_with_e1000 = error->passed_with_e1000 + 1;
		printf("%s passed with epsilon * 1000.0:\n\tExpected % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf\n", msg, e.x, e.y, r.x, r.y);
	} else {
		error->failed = error->failed + 1;
		printf("%s failed:\n\tExpected % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf\n", msg, e.x, e.y, r.x, r.y);
	}
}

void printf_3f_test(struct cerror *error, char *msg, struct vec3 e, struct vec3 r)
{
	if (svec3_is_nearly_equal(e, r, EPSILON_1)) {
		error->passed = error->passed + 1;
	} else if (svec3_is_nearly_equal(e, r, EPSILON_10)) {
		error->passed_with_e10 = error->passed_with_e10 + 1;
		printf("%s passed with epsilon * 10.0:\n\tExpected % .16lf, % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf, % .16lf\n", msg, e.x, e.y, e.z, r.x, r.y, r.z);
	} else if (svec3_is_nearly_equal(e, r, EPSILON_100)) {
		error->passed_with_e100 = error->passed_with_e100 + 1;
		printf("%s passed with epsilon * 100.0:\n\tExpected % .16lf, % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf, % .16lf\n", msg, e.x, e.y, e.z, r.x, r.y, r.z);
	} else if (svec3_is_nearly_equal(e, r, EPSILON_1000)) {
		printf("%s passed with epsilon * 1000.0:\n\tExpected % .16lf, % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf, % .16lf\n", msg, e.x, e.y, e.z, r.x, r.y, r.z);
		error->passed_with_e1000 = error->passed_with_e1000 + 1;
	} else {
		printf("%s failed:\n\tExpected % .16lf, % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf, % .16lf\n", msg, e.x, e.y, e.z, r.x, r.y, r.z);
		error->failed = error->failed + 1;
	}
}

void printf_4f_test(struct cerror *error, char *msg, struct vec4 e, struct vec4 r)
{
	if (svec4_is_nearly_equal(e, r, EPSILON_1)) {
		error->passed = error->passed + 1;
	} else if (svec4_is_nearly_equal(e, r, EPSILON_10)) {
		error->passed_with_e10 = error->passed_with_e10 + 1;
		printf("%s passed with epsilon * 10.0:\n\tExpected % .16lf, % .16lf, % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf, % .16lf, % .16lf\n", msg, e.x, e.y, e.z, e.w, r.x, r.y, r.z, r.w);
	} else if (svec4_is_nearly_equal(e, r, EPSILON_100)) {
		error->passed_with_e100 = error->passed_with_e100 + 1;
		printf("%s passed with epsilon * 100.0:\n\tExpected % .16lf, % .16lf, % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf, % .16lf, % .16lf\n", msg, e.x, e.y, e.z, e.w, r.x, r.y, r.z, r.w);
	} else if (svec4_is_nearly_equal(e, r, EPSILON_1000)) {
		error->passed_with_e1000 = error->passed_with_e1000 + 1;
		printf("%s passed with epsilon * 1000.0:\n\tExpected % .16lf, % .16lf, % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf, % .16lf, % .16lf\n", msg, e.x, e.y, e.z, e.w, r.x, r.y, r.z, r.w);
	} else {
		error->failed = error->failed + 1;
		printf("%s failed:\n\tExpected % .16lf, % .16lf, % .16lf, % .16lf\n\t  Actual % .16lf, % .16lf, % .16lf, % .16lf\n", msg, e.x, e.y, e.z, e.w, r.x, r.y, r.z, r.w);
	}
}

void vec2_tests(struct cerror *error)
{
	struct vec2 v;
	struct mat2 m;
	printf_bool_test(error, "Test `vec2_is_zero`", true, svec2_is_zero(svec2(MFLOAT_C(0.0), MFLOAT_C(0.0))));
	printf_bool_test(error, "Test `vec2_is_near_zero`", true, svec2_is_near_zero(svec2(MFLOAT_C(0.0), MFLOAT_C(0.0)), EPSILON_1));
	printf_bool_test(error, "Test `vec2_is_equal`", true, svec2_is_equal(svec2(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0)), svec2(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0))));
	printf_bool_test(error, "Test `vec2_is_nearly_equal`", true, svec2_is_nearly_equal(svec2(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0)), svec2(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0)), EPSILON_1));
	v = svec2(MFLOAT_C(2.0), MFLOAT_C(1.0));
	printf_2f_test(error, "Test `vec2`", svec2(MFLOAT_C(2.0), MFLOAT_C(1.0)), v);
	v = svec2_assign(svec2(MFLOAT_C(2.0), MFLOAT_C(1.0)));
	printf_2f_test(error, "Test `vec2_assign`", svec2(MFLOAT_C(2.0), MFLOAT_C(1.0)), v);
	v = svec2_zero();
	printf_2f_test(error, "Test `vec2_zero`", svec2(MFLOAT_C(0.0), MFLOAT_C(0.0)), v);
	v = svec2_add(svec2(MFLOAT_C(3.0), MFLOAT_C(1.0)), svec2(MFLOAT_C(1.0), MFLOAT_C(7.0)));
	printf_2f_test(error, "Test `vec2_add`", svec2(MFLOAT_C(4.0), MFLOAT_C(8.0)), v);
	v = svec2_subtract(svec2(MFLOAT_C(1.0), MFLOAT_C(20.0)), svec2(MFLOAT_C(3.0), MFLOAT_C(7.0)));
	printf_2f_test(error, "Test `vec2_subtract`", svec2(MFLOAT_C(-2.0), MFLOAT_C(13.0)), v);
	v = svec2_scale(svec2(MFLOAT_C(1.0), MFLOAT_C(3.0)), MFLOAT_C(3.0));
	printf_2f_test(error, "Test `vec2_scale`", svec2(MFLOAT_C(3.0), MFLOAT_C(9.0)), v);
	v = svec2_multiply(svec2(MFLOAT_C(1.0), MFLOAT_C(3.0)), svec2(MFLOAT_C(3.0), MFLOAT_C(5.0)));
	printf_2f_test(error, "Test `vec2_multiply`", svec2(MFLOAT_C(3.0), MFLOAT_C(15.0)), v);
	m = smat2(
		MFLOAT_C(0.8), MFLOAT_C(0.7),
		MFLOAT_C(0.5), MFLOAT_C(0.3));
	v = svec2_multiply_mat2(svec2(MFLOAT_C(3.0), MFLOAT_C(5.0)), m);
	printf_2f_test(error, "Test `vec2_multiply_mat2`", svec2(MFLOAT_C(5.9), MFLOAT_C(3.0)), v);
	v = svec2_divide(svec2(MFLOAT_C(1.0), MFLOAT_C(3.0)), svec2(MFLOAT_C(3.0), MFLOAT_C(5.0)));
	printf_2f_test(error, "Test `vec2_divide`", svec2(MFLOAT_C(1.0 / 3.0), MFLOAT_C(0.6)), v);
	v = svec2_snap(svec2(MFLOAT_C(20.0), MFLOAT_C(-15.5)), svec2(MFLOAT_C(16.0), MFLOAT_C(16.0)));
	printf_2f_test(error, "Test `vec2_snap`", svec2(MFLOAT_C(16.0), MFLOAT_C(-16.0)), v);
	v = svec2_negative(svec2(MFLOAT_C(3.0), MFLOAT_C(5.0)));
	printf_2f_test(error, "Test `vec2_negative`", svec2(MFLOAT_C(-3.0), MFLOAT_C(-5.0)), v);
	v = svec2_inverse(svec2(MFLOAT_C(3.0), MFLOAT_C(5.0)));
	printf_2f_test(error, "Test `vec2_inverse`", svec2(MFLOAT_C(1.0 / 3.0), MFLOAT_C(0.2)), v);
	v = svec2_abs(svec2(MFLOAT_C(-7.0), MFLOAT_C(-3.0)));
	printf_2f_test(error, "Test `vec2_abs`", svec2(7.0, MFLOAT_C(3.0)), v);
	v = svec2_floor(svec2(MFLOAT_C(-7.2), MFLOAT_C(-3.7)));
	printf_2f_test(error, "Test `vec2_floor`", svec2(-8.0, MFLOAT_C(-4.0)), v);
	v = svec2_ceil(svec2(MFLOAT_C(-7.2), MFLOAT_C(-3.7)));
	printf_2f_test(error, "Test `vec2_ceil`", svec2(-7.0, MFLOAT_C(-3.0)), v);
	v = svec2_round(svec2(MFLOAT_C(-7.2), MFLOAT_C(-3.7)));
	printf_2f_test(error, "Test `vec2_round`", svec2(-7.0, MFLOAT_C(-4.0)), v);
	v = svec2_max(svec2(MFLOAT_C(-7.2), MFLOAT_C(-3.7)), svec2(MFLOAT_C(1.0), MFLOAT_C(3.7)));
	printf_2f_test(error, "Test `vec2_max`", svec2(MFLOAT_C(1.0), MFLOAT_C(3.7)), v);
	v = svec2_min(svec2(MFLOAT_C(-7.2), MFLOAT_C(-3.7)), svec2(MFLOAT_C(1.0), MFLOAT_C(3.7)));
	printf_2f_test(error, "Test `vec2_min`", svec2(MFLOAT_C(-7.2), MFLOAT_C(-3.7)), v);
	v = svec2_clamp(svec2(MFLOAT_C(-9.1), MFLOAT_C(8.7)), svec2(MFLOAT_C(-1.3), MFLOAT_C(2.7)), svec2(MFLOAT_C(3.3), MFLOAT_C(5.7)));
	printf_2f_test(error, "Test `vec2_clamp`", svec2(MFLOAT_C(-1.3), MFLOAT_C(5.7)), v);
	v = svec2_normalize(svec2(MFLOAT_C(1.0), MFLOAT_C(1.0)));
	printf_2f_test(error, "Test `vec2_normalize`", svec2(MFLOAT_C(0.7071067811865475), MFLOAT_C(0.7071067811865475)), v);
	v = svec2_project(svec2(MFLOAT_C(2.0), MFLOAT_C(2.0)), svec2(MFLOAT_C(0.5), MFLOAT_C(1.0)));
	printf_2f_test(error, "Test `vec2_project`", svec2(MFLOAT_C(1.2), MFLOAT_C(2.4)), v);
	v = svec2_slide(svec2(MFLOAT_C(1.0), MFLOAT_C(0.0)), svec2(MFLOAT_C(-0.7071067811865475), MFLOAT_C(-0.7071067811865475)));
	printf_2f_test(error, "Test `vec2_slide`", svec2(MFLOAT_C(0.5), MFLOAT_C(-0.5)), v);
	v = svec2_reflect(svec2(MFLOAT_C(1.0), MFLOAT_C(0.0)), svec2(MFLOAT_C(-0.7071067811865475), MFLOAT_C(-0.7071067811865475)));
	printf_2f_test(error, "Test `vec2_reflect`", svec2(MFLOAT_C(0.0), MFLOAT_C(-1.0)), v);
	v = svec2_tangent(svec2(MFLOAT_C(1.0), MFLOAT_C(0.0)));
	printf_2f_test(error, "Test `vec2_tangent`", svec2(MFLOAT_C(0.0), MFLOAT_C(-1.0)), v);
	v = svec2_rotate(svec2(MFLOAT_C(1.0), MFLOAT_C(0.0)), to_radians(MFLOAT_C(45.0)));
	printf_2f_test(error, "Test `vec2_rotate`", svec2(MFLOAT_C(0.7071067811865475), MFLOAT_C(0.7071067811865475)), v);
	v = svec2_lerp(svec2(MFLOAT_C(3.0), MFLOAT_C(3.0)), svec2(MFLOAT_C(9.0), MFLOAT_C(1.0)), MFLOAT_C(0.5));
	printf_2f_test(error, "Test `vec2_lerp`", svec2(MFLOAT_C(6.0), MFLOAT_C(2.0)), v);
	v = svec2_bezier3(svec2(MFLOAT_C(3.0), MFLOAT_C(3.0)), svec2(MFLOAT_C(9.0), MFLOAT_C(1.0)), svec2(MFLOAT_C(14.0), MFLOAT_C(7.0)), MFLOAT_C(0.5));
	printf_2f_test(error, "Test `vec2_bezier3`", svec2(MFLOAT_C(8.75), MFLOAT_C(3.0)), v);
	v = svec2_bezier4(svec2(MFLOAT_C(3.0), MFLOAT_C(3.0)), svec2(MFLOAT_C(9.0), MFLOAT_C(1.0)), svec2(MFLOAT_C(14.0), MFLOAT_C(7.0)), svec2(MFLOAT_C(21.0), MFLOAT_C(9.0)), MFLOAT_C(0.5));
	printf_2f_test(error, "Test `vec2_bezier4`", svec2(MFLOAT_C(11.625), MFLOAT_C(4.5)), v);
	printf_1f_test(error, "Test `vec2_dot`", MFLOAT_C(13.0), svec2_dot(svec2(MFLOAT_C(3.0), MFLOAT_C(2.0)), svec2(MFLOAT_C(1.0), MFLOAT_C(5.0))));
	printf_1f_test(error, "Test `vec2_angle`", to_radians(MFLOAT_C(45.0)), svec2_angle(svec2(MFLOAT_C(2.0), MFLOAT_C(2.0))));
	printf_1f_test(error, "Test `vec2_length`", MFLOAT_C(2.8284271247461903), svec2_length(svec2(MFLOAT_C(2.0), MFLOAT_C(2.0))));
	printf_1f_test(error, "Test `vec2_length_squared`", MFLOAT_C(8.0), svec2_length_squared(svec2(MFLOAT_C(2.0), MFLOAT_C(2.0))));
	printf_1f_test(error, "Test `vec2_distance`", MFLOAT_C(5.6568542494923806), svec2_distance(svec2(MFLOAT_C(2.0), MFLOAT_C(2.0)), svec2(MFLOAT_C(6.0), MFLOAT_C(6.0))));
	printf_1f_test(error, "Test `vec2_distance_squared`", MFLOAT_C(32.0), svec2_distance_squared(svec2(MFLOAT_C(2.0), MFLOAT_C(2.0)), svec2(MFLOAT_C(6.0), MFLOAT_C(6.0))));
}

void vec3_tests(struct cerror *error)
{
	struct vec3 v;
	struct mat3 m;
	printf_bool_test(error, "Test `vec3_is_zero`", true, svec3_is_zero(svec3(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0))));
	printf_bool_test(error, "Test `vec3_is_near_zero`", true, svec3_is_near_zero(svec3(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0)), EPSILON_1));
	printf_bool_test(error, "Test `vec3_is_equal`", true, svec3_is_equal(svec3(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0), MFLOAT_C(5.0) / MFLOAT_C(3.0)), svec3(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0), MFLOAT_C(5.0) / MFLOAT_C(3.0))));
	printf_bool_test(error, "Test `vec3_is_nearly_equal`", true, svec3_is_nearly_equal(svec3(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0), MFLOAT_C(5.0) / MFLOAT_C(3.0)), svec3(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0), MFLOAT_C(5.0) / MFLOAT_C(3.0)), EPSILON_1));
	v = svec3(MFLOAT_C(2.0), MFLOAT_C(1.0), MFLOAT_C(3.0));
	printf_3f_test(error, "Test `vec3`", svec3(MFLOAT_C(2.0), MFLOAT_C(1.0), MFLOAT_C(3.0)), v);
	v = svec3_assign(svec3(MFLOAT_C(2.0), MFLOAT_C(1.0), MFLOAT_C(3.0)));
	printf_3f_test(error, "Test `vec3_assign`", svec3(MFLOAT_C(2.0), MFLOAT_C(1.0), MFLOAT_C(3.0)), v);
	v = svec3_zero();
	printf_3f_test(error, "Test `vec3_zero`", svec3(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0)), v);
	v = svec3_add(svec3(MFLOAT_C(3.0), MFLOAT_C(1.0), MFLOAT_C(4.0)), svec3(MFLOAT_C(1.0), MFLOAT_C(7.0), MFLOAT_C(2.0)));
	printf_3f_test(error, "Test `vec3_add`", svec3(MFLOAT_C(4.0), MFLOAT_C(8.0), MFLOAT_C(6.0)), v);
	v = svec3_subtract(svec3(MFLOAT_C(1.0), MFLOAT_C(20.0), MFLOAT_C(9.0)), svec3(MFLOAT_C(3.0), MFLOAT_C(7.0), MFLOAT_C(7.0)));
	printf_3f_test(error, "Test `vec3_subtract`", svec3(MFLOAT_C(-2.0), MFLOAT_C(13.0), MFLOAT_C(2.0)), v);
	v = svec3_scale(svec3(MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(5.0)), MFLOAT_C(3.0));
	printf_3f_test(error, "Test `vec3_scale`", svec3(MFLOAT_C(3.0), MFLOAT_C(9.0), MFLOAT_C(15.0)), v);
	v = svec3_multiply(svec3(MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(5.0)), svec3(MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(2.0)));
	printf_3f_test(error, "Test `vec3_multiply`", svec3(MFLOAT_C(3.0), MFLOAT_C(15.0), MFLOAT_C(10.0)), v);
	m = smat3(
		MFLOAT_C(1.0), MFLOAT_C(2.0), MFLOAT_C(3.0),
		MFLOAT_C(4.0), MFLOAT_C(5.0), MFLOAT_C(6.0),
		MFLOAT_C(7.0), MFLOAT_C(8.0), MFLOAT_C(9.0));
	v = svec3_multiply_mat3(svec3(MFLOAT_C(2.0), MFLOAT_C(1.0), MFLOAT_C(3.0)), m);
	printf_3f_test(error, "Test `vec3_multiply_mat3`", svec3(MFLOAT_C(13.0), MFLOAT_C(31.0), MFLOAT_C(49.0)), v);
	v = svec3_divide(svec3(MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(5.0)), svec3(MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(2.0)));
	printf_3f_test(error, "Test `vec3_divide`", svec3(MFLOAT_C(1.0 / 3.0), MFLOAT_C(0.6), MFLOAT_C(2.5)), v);
	v = svec3_snap(svec3(MFLOAT_C(1.3), MFLOAT_C(-3.1), MFLOAT_C(4.9)), svec3(MFLOAT_C(0.5), MFLOAT_C(0.5), MFLOAT_C(0.5)));
	printf_3f_test(error, "Test `vec3_snap`", svec3(MFLOAT_C(1.0), MFLOAT_C(-3.5), MFLOAT_C(4.5)), v);
	v = svec3_negative(svec3(MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(-7.0)));
	printf_3f_test(error, "Test `vec3_negative`", svec3(MFLOAT_C(-3.0), MFLOAT_C(-5.0), MFLOAT_C(7.0)), v);
	v = svec3_inverse(svec3(MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(7.0)));
	printf_3f_test(error, "Test `vec3_inverse`", svec3(MFLOAT_C(1.0 / 3.0), MFLOAT_C(1.0 / 5.0), MFLOAT_C(1.0 / 7.0)), v);
	v = svec3_abs(svec3(MFLOAT_C(-7.0), MFLOAT_C(-3.0), MFLOAT_C(1.0)));
	printf_3f_test(error, "Test `vec3_abs`", svec3(7.0, MFLOAT_C(3.0), MFLOAT_C(1.0)), v);
	v = svec3_floor(svec3(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(9.1)));
	printf_3f_test(error, "Test `vec3_floor`", svec3(-8.0, MFLOAT_C(-4.0), MFLOAT_C(9.0)), v);
	v = svec3_ceil(svec3(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(0.99)));
	printf_3f_test(error, "Test `vec3_ceil`", svec3(-7.0, MFLOAT_C(-3.0), MFLOAT_C(1.0)), v);
	v = svec3_round(svec3(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(0.01)));
	printf_3f_test(error, "Test `vec3_round`", svec3(-7.0, MFLOAT_C(-4.0), MFLOAT_C(0.0)), v);
	v = svec3_max(svec3(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(9.0)), svec3(MFLOAT_C(1.0), MFLOAT_C(3.7), MFLOAT_C(30.0)));
	printf_3f_test(error, "Test `vec3_max`", svec3(MFLOAT_C(1.0), MFLOAT_C(3.7), MFLOAT_C(30.0)), v);
	v = svec3_min(svec3(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(9.0)), svec3(MFLOAT_C(1.0), MFLOAT_C(3.7), MFLOAT_C(30.0)));
	printf_3f_test(error, "Test `vec3_min`", svec3(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(9.0)), v);
	v = svec3_clamp(svec3(MFLOAT_C(-9.1), MFLOAT_C(8.7), MFLOAT_C(0.4)), svec3(MFLOAT_C(-1.3), MFLOAT_C(2.7), MFLOAT_C(0.7)), svec3(MFLOAT_C(3.3), MFLOAT_C(5.7), MFLOAT_C(0.8)));
	printf_3f_test(error, "Test `vec3_clamp`", svec3(MFLOAT_C(-1.3), MFLOAT_C(5.7), MFLOAT_C(0.7)), v);
	v = svec3_normalize(svec3(MFLOAT_C(3.0), MFLOAT_C(1.0), MFLOAT_C(2.0)));
	printf_3f_test(error, "Test `vec3_normalize`", svec3(MFLOAT_C(0.8017837257372732), MFLOAT_C(0.2672612419124244), MFLOAT_C(0.5345224838248488)), v);
	v = svec3_project(svec3(MFLOAT_C(-1.0), MFLOAT_C(4.0), MFLOAT_C(2.0)), svec3(MFLOAT_C(1.0), MFLOAT_C(5.0), MFLOAT_C(3.0)));
	printf_3f_test(error, "Test `vec3_project`", svec3(MFLOAT_C(0.7142857142857143), MFLOAT_C(3.5714285714285716), 2.1428571428571428), v);
	v = svec3_slide(svec3(MFLOAT_C(1.0), MFLOAT_C(0.5), MFLOAT_C(-1.0)), svec3(MFLOAT_C(-0.1), MFLOAT_C(0.0), MFLOAT_C(1.0)));
	printf_3f_test(error, "Test `vec3_slide`", svec3(MFLOAT_C(0.89),  MFLOAT_C(0.5),  MFLOAT_C(0.1)), v);
	v = svec3_reflect(svec3(MFLOAT_C(1.0), MFLOAT_C(0.5), MFLOAT_C(-1.0)), svec3(MFLOAT_C(-0.1), MFLOAT_C(0.0), MFLOAT_C(1.0)));
	printf_3f_test(error, "Test `vec3_reflect`", svec3(MFLOAT_C(0.78),  MFLOAT_C(0.5),  MFLOAT_C(1.2)), v);
	v = svec3_lerp(svec3(MFLOAT_C(3.0), MFLOAT_C(3.0), MFLOAT_C(3.0)), svec3(MFLOAT_C(9.0), MFLOAT_C(1.0), MFLOAT_C(30.0)), MFLOAT_C(0.5));
	printf_3f_test(error, "Test `vec3_lerp`", svec3(MFLOAT_C(6.0),  MFLOAT_C(2.0),  MFLOAT_C(16.5)), v);
	v = svec3_bezier3(svec3(MFLOAT_C(-1.0), MFLOAT_C(-0.5), MFLOAT_C(0.2)), svec3(MFLOAT_C(1.5), MFLOAT_C(0.15), MFLOAT_C(0.5)), svec3(MFLOAT_C(1.0), MFLOAT_C(-1.0), MFLOAT_C(0.0)), MFLOAT_C(0.5));
	printf_3f_test(error, "Test `vec3_bezier3`", svec3(MFLOAT_C(0.75), MFLOAT_C(-0.3), MFLOAT_C(0.3)), v);
	v = svec3_bezier4(svec3(MFLOAT_C(3.0), MFLOAT_C(3.0), MFLOAT_C(3.0)), svec3(MFLOAT_C(9.0), MFLOAT_C(7.0), MFLOAT_C(9.0)), svec3(MFLOAT_C(-4.0), MFLOAT_C(6.0), MFLOAT_C(7.0)), svec3(MFLOAT_C(-5.0), MFLOAT_C(1.0), MFLOAT_C(2.0)), MFLOAT_C(0.5));
	printf_3f_test(error, "Test `vec3_bezier4`", svec3(MFLOAT_C(1.625), MFLOAT_C(5.375), MFLOAT_C(6.625)), v);
	printf_1f_test(error, "Test `vec3_dot`", MFLOAT_C(44.0), svec3_dot(svec3(MFLOAT_C(1.0), MFLOAT_C(2.0), MFLOAT_C(3.0)), svec3(MFLOAT_C(6.0), MFLOAT_C(7.0), MFLOAT_C(8.0))));
	printf_1f_test(error, "Test `vec3_length`", MFLOAT_C(3.4641016151377544), svec3_length(svec3(MFLOAT_C(2.0), MFLOAT_C(2.0), MFLOAT_C(2.0))));
	printf_1f_test(error, "Test `vec3_length_squared`", MFLOAT_C(12.0), svec3_length_squared(svec3(MFLOAT_C(2.0), MFLOAT_C(2.0), MFLOAT_C(2.0))));
	printf_1f_test(error, "Test `vec3_distance`", MFLOAT_C(6.9282032302755088), svec3_distance(svec3(MFLOAT_C(2.0), MFLOAT_C(2.0), MFLOAT_C(2.0)), svec3(MFLOAT_C(6.0), MFLOAT_C(6.0), MFLOAT_C(6.0))));
	printf_1f_test(error, "Test `vec3_distance_squared`", MFLOAT_C(48.0), svec3_distance_squared(svec3(MFLOAT_C(2.0), MFLOAT_C(2.0), MFLOAT_C(2.0)), svec3(MFLOAT_C(6.0), MFLOAT_C(6.0), MFLOAT_C(6.0))));
}

void vec4_tests(struct cerror *error)
{
	struct vec4 v;
	struct mat4 m;
	printf_bool_test(error, "Test `vec4_is_zero`", true, svec4_is_zero(svec4(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0))));
	printf_bool_test(error, "Test `vec4_is_near_zero`", true, svec4_is_near_zero(svec4(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0)), EPSILON_1));
	printf_bool_test(error, "Test `vec4_is_equal`", true, svec4_is_equal(svec4(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0), MFLOAT_C(5.0) / MFLOAT_C(3.0), MFLOAT_C(3.0) / MFLOAT_C(7.0)), svec4(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0), MFLOAT_C(5.0) / MFLOAT_C(3.0), MFLOAT_C(3.0) / MFLOAT_C(7.0))));
	printf_bool_test(error, "Test `vec4_is_nearly_equal`", true, svec4_is_nearly_equal(svec4(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0), MFLOAT_C(5.0) / MFLOAT_C(3.0), MFLOAT_C(3.0) / MFLOAT_C(7.0)), svec4(MFLOAT_C(1.0) / MFLOAT_C(3.0), MFLOAT_C(7.0) / MFLOAT_C(3.0), MFLOAT_C(5.0) / MFLOAT_C(3.0), MFLOAT_C(3.0) / MFLOAT_C(7.0)), EPSILON_1));
	v.x = MFLOAT_C(2.0);
	v.y = MFLOAT_C(1.0);
	v.z = MFLOAT_C(3.0);
	v.w = MFLOAT_C(4.0);
	v = svec4(MFLOAT_C(2.0), MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(4.0));
	printf_4f_test(error, "Test `vec4`", svec4(MFLOAT_C(2.0), MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(4.0)), v);
	v = svec4_assign(svec4(MFLOAT_C(2.0), MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(4.0)));
	printf_4f_test(error, "Test `vec3_assign`", svec4(MFLOAT_C(2.0), MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(4.0)), v);
	v = svec4_zero();
	printf_4f_test(error, "Test `vec4_zero`", svec4(MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0), MFLOAT_C(0.0)), v);
	v = svec4_add(svec4(MFLOAT_C(3.0), MFLOAT_C(1.0), MFLOAT_C(4.0), MFLOAT_C(2.0)), svec4(MFLOAT_C(1.0), MFLOAT_C(7.0), MFLOAT_C(2.0), MFLOAT_C(3.0)));
	printf_4f_test(error, "Test `vec4_add`", svec4(MFLOAT_C(4.0), MFLOAT_C(8.0), MFLOAT_C(6.0), MFLOAT_C(5.0)), v);
	v = svec4_subtract(svec4(MFLOAT_C(1.0), MFLOAT_C(20.0), MFLOAT_C(9.0), MFLOAT_C(10.0)), svec4(MFLOAT_C(3.0), MFLOAT_C(7.0), MFLOAT_C(7.0), MFLOAT_C(5.0)));
	printf_4f_test(error, "Test `vec4_subtract`", svec4(MFLOAT_C(-2.0), MFLOAT_C(13.0), MFLOAT_C(2.0), MFLOAT_C(5.0)), v);
	v = svec4_scale(svec4(MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(2.0)), MFLOAT_C(3.0));
	printf_4f_test(error, "Test `vec4_scale`", svec4(MFLOAT_C(3.0), MFLOAT_C(9.0), MFLOAT_C(15.0), MFLOAT_C(6.0)), v);
	v = svec4_multiply(svec4(MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(2.0)), svec4(MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(2.0), MFLOAT_C(2.0)));
	printf_4f_test(error, "Test `vec4_multiply`", svec4(MFLOAT_C(3.0), MFLOAT_C(15.0), MFLOAT_C(10.0), MFLOAT_C(4.0)), v);
	m = smat4(
		MFLOAT_C(1.0), MFLOAT_C(5.0), MFLOAT_C(9.0), MFLOAT_C(13.0),
		MFLOAT_C(2.0), MFLOAT_C(6.0), MFLOAT_C(10.0), MFLOAT_C(14.0),
		MFLOAT_C(3.0), MFLOAT_C(7.0), MFLOAT_C(11.0), MFLOAT_C(15.0),
		MFLOAT_C(4.0), MFLOAT_C(8.0), MFLOAT_C(12.0), MFLOAT_C(16.0));
	v = svec4_multiply_mat4(svec4(MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(7.0), MFLOAT_C(9.0)), m);
	printf_4f_test(error, "Test `vec4_multiply_mat4`", svec4(MFLOAT_C(208.0), MFLOAT_C(232.0), MFLOAT_C(256.0), MFLOAT_C(280.0)), v);
	v = svec4_divide(svec4(MFLOAT_C(1.0), MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(2.0)), svec4(MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(2.0), MFLOAT_C(4.0)));
	printf_4f_test(error, "Test `vec4_divide`", svec4(MFLOAT_C(1.0 / 3.0), MFLOAT_C(0.6), MFLOAT_C(2.5), MFLOAT_C(0.5)), v);
	v = svec4_snap(svec4(MFLOAT_C(1.3), MFLOAT_C(-3.1), MFLOAT_C(4.9), MFLOAT_C(5.6)), svec4(MFLOAT_C(0.5), MFLOAT_C(0.5), MFLOAT_C(0.5), MFLOAT_C(0.5)));
	printf_4f_test(error, "Test `vec4_snap`", svec4(MFLOAT_C(1.0), MFLOAT_C(-3.5), MFLOAT_C(4.5), MFLOAT_C(5.5)), v);
	v = svec4_negative(svec4(MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(-7.0), MFLOAT_C(0.01)));
	printf_4f_test(error, "Test `vec4_negative`", svec4(MFLOAT_C(-3.0), MFLOAT_C(-5.0), MFLOAT_C(7.0), MFLOAT_C(-0.01)), v);
	v = svec4_inverse(svec4(MFLOAT_C(3.0), MFLOAT_C(5.0), MFLOAT_C(7.0), MFLOAT_C(8.0)));
	printf_4f_test(error, "Test `vec4_inverse`", svec4(MFLOAT_C(1.0 / 3.0), MFLOAT_C(1.0 / 5.0), MFLOAT_C(1.0 / 7.0), MFLOAT_C(1.0 / 8.0)), v);
	v = svec4_abs(svec4(MFLOAT_C(-7.0), MFLOAT_C(-3.0), MFLOAT_C(1.0), MFLOAT_C(0.0001)));
	printf_4f_test(error, "Test `vec4_abs`", svec4(7.0, MFLOAT_C(3.0), MFLOAT_C(1.0), MFLOAT_C(0.0001)), v);
	v = svec4_floor(svec4(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(9.1), MFLOAT_C(1.0)));
	printf_4f_test(error, "Test `vec4_floor`", svec4(-8.0, MFLOAT_C(-4.0), MFLOAT_C(9.0), MFLOAT_C(1.0)), v);
	v = svec4_ceil(svec4(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(0.99), MFLOAT_C(1.0)));
	printf_4f_test(error, "Test `vec4_ceil`", svec4(-7.0, MFLOAT_C(-3.0), MFLOAT_C(1.0), MFLOAT_C(1.0)), v);
	v = svec4_round(svec4(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(0.01), MFLOAT_C(1.0)));
	printf_4f_test(error, "Test `vec4_round`", svec4(-7.0, MFLOAT_C(-4.0), MFLOAT_C(0.0), MFLOAT_C(1.0)), v);
	v = svec4_max(svec4(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(9.0), MFLOAT_C(2.0)), svec4(MFLOAT_C(1.0), MFLOAT_C(3.7), MFLOAT_C(30.0), MFLOAT_C(3.0)));
	printf_4f_test(error, "Test `vec4_max`", svec4(MFLOAT_C(1.0), MFLOAT_C(3.7), MFLOAT_C(30.0), MFLOAT_C(3.0)), v);
	v = svec4_min(svec4(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(9.0), MFLOAT_C(2.0)), svec4(MFLOAT_C(1.0), MFLOAT_C(3.7), MFLOAT_C(30.0), MFLOAT_C(3.0)));
	printf_4f_test(error, "Test `vec4_min`", svec4(MFLOAT_C(-7.2), MFLOAT_C(-3.7), MFLOAT_C(9.0), MFLOAT_C(2.0)), v);
	v = svec4_clamp(svec4(MFLOAT_C(-9.1), MFLOAT_C(8.7), MFLOAT_C(0.4), MFLOAT_C(1.0)), svec4(MFLOAT_C(-1.3), MFLOAT_C(2.7), MFLOAT_C(0.7), MFLOAT_C(0.5)), svec4(MFLOAT_C(3.3), MFLOAT_C(5.7), MFLOAT_C(0.8), MFLOAT_C(2.0)));
	printf_4f_test(error, "Test `vec4_clamp`", svec4(MFLOAT_C(-1.3), MFLOAT_C(5.7), MFLOAT_C(0.7), MFLOAT_C(1.0)), v);
	v = svec4_normalize(svec4(MFLOAT_C(3.0), MFLOAT_C(1.0), MFLOAT_C(2.0), MFLOAT_C(4.0)));
	printf_4f_test(error, "Test `vec4_normalize`", svec4(MFLOAT_C(0.5477225575051661), MFLOAT_C(0.1825741858350554), MFLOAT_C(0.3651483716701107), MFLOAT_C(0.7302967433402214)), v);
	v = svec4_lerp(svec4(MFLOAT_C(3.0), MFLOAT_C(3.0), MFLOAT_C(3.0), MFLOAT_C(3.0)), svec4(MFLOAT_C(9.0), MFLOAT_C(1.0), MFLOAT_C(30.0), MFLOAT_C(7.0)), MFLOAT_C(0.5));
	printf_4f_test(error, "Test `vec4_lerp`", svec4(MFLOAT_C(6.0),  MFLOAT_C(2.0),  MFLOAT_C(16.5), MFLOAT_C(5.0)), v);
}

int main(void)
{
	struct cerror error = {0};
	vec2_tests(&error);
	vec3_tests(&error);
	vec4_tests(&error);
	printf("Total of failed tests: %d\n", error.failed);
	printf("Total of tests that passed: %d\n", error.passed);
	printf("Total of tests that passed, but with epsilon * 10.0: %d\n", error.passed_with_e10);
	printf("Total of tests that passed, but with epsilon * 100.0: %d\n", error.passed_with_e100);
	printf("Total of tests that passed, but with epsilon * 1000.0: %d\n", error.passed_with_e1000);
	return error.failed;
}
