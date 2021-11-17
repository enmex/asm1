#include <math.h>
#include <stdio.h>

//4. ctg(x) (вычислите сумму первых 5 членов ряда)

double ctg(double x) {
	
	double result;

	__asm {
		finit
		fld		qword ptr x		;sum of st(2) (result)
		fld		qword ptr x		;st(1)
		fld		qword ptr x		;n*x^n st(2)
		fld		qword ptr x		;n*x^n/fact(n+1) st(3)
		fld1					;fact st(4)
		fld1					;for fact st(5)
		fld1					;for fact st(6)

		mov		ecx, 5
	LOOP_FOR_COMMON_TERM:
		;вычисление n*x^n
		fmul	st(2), st(1)
		fmul	st(2), st(1)
		fadd	st(2), st(2)

		;вычисление факториала
		fadd	st(5), st(6)
		fmul	st(4), st(5)

		;вычисление общего члена n*x^n / fact(n+1)
		fadd	st(3), st(2)
		fdiv	st(3), st(4)

		;добавление общего члена в общую сумму
		fadd	st(0), st(3)

		;обнуление общего члена
		fsub	st(3), st(3)

		loop LOOP_FOR_COMMON_TERM

		;вытаскивание st(0) в result
		fst		qword ptr result
		finit

	}
	return result;
}