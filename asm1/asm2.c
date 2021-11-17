#include <math.h>
#include <stdio.h>

//4. ctg(x) (��������� ����� ������ 5 ������ ����)

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
		;���������� n*x^n
		fmul	st(2), st(1)
		fmul	st(2), st(1)
		fadd	st(2), st(2)

		;���������� ����������
		fadd	st(5), st(6)
		fmul	st(4), st(5)

		;���������� ������ ����� n*x^n / fact(n+1)
		fadd	st(3), st(2)
		fdiv	st(3), st(4)

		;���������� ������ ����� � ����� �����
		fadd	st(0), st(3)

		;��������� ������ �����
		fsub	st(3), st(3)

		loop LOOP_FOR_COMMON_TERM

		;������������ st(0) � result
		fst		qword ptr result
		finit

	}
	return result;
}