#include <math.h>
#include <stdio.h>

//4. ctg(x) (��������� ����� ������ 5 ������ ����)
double ctg(double x) {
	
	double result;
	double cos, sin;

	__asm {

		finit
		fld1; ���������� �������
		fld1; 1 st(5) ����� �������� ������� �������� ����������
		fld1; 2 st(4) ����� �������� ��������� ��� ����������

		fld		qword ptr x; ��� �������� ����� ��������� st(3)
		fldz;	��� �������� ����� ���� st(2)
		fld		qword ptr x; st(1) ������������ x
		fld		qword ptr x; x^n st(0)

		mov		ecx, 10
		mov		eax, 2
	LOOP_FOR_COMMON_TERM_SIN:

		;��������� x^n
		fmul	st(0), st(1)
		fmul	st(0), st(1)
		
		fxch	st(2); �������� �������� ����� ����
		fadd	st(0), st(2)

		;��������� ��������� x! -> (x+2)!
		fxch	st(4)
		fadd	st(0), st(6); ���������� �����������
		fmul	st(5), st(0) ;���������� ���������
		fadd	st(0), st(6); ���������� �����������
		fmul	st(5), st(0); ���������� ���������
		fxch	st(4)

		;����� n*x^n �� ���������
		fdiv	st(0), st(5)

		mov		edx, ecx
		and		edx, 1
		cmp		edx, 0
		je		IS_ODD_SIN
		jmp		IS_EVEN_SIN

	IS_ODD_SIN:
		fchs

	IS_EVEN_SIN:
		;��������� ����� ����
		fadd	st(3), st(0)
		
		;��������� � ������ �����
		fsub	st(0), st(0)
		fxch	st(2)

		loop LOOP_FOR_COMMON_TERM_SIN

		fxch	st(3)
		fstp	qword ptr sin


		;������ ������� �������
		finit
		fld1; ���������� �������
		fld1; 2 st(5) ����� �������� ������� �������� ����������

		fadd	st(0), st(0)

		fld1; 2 st(4) ����� �������� ��������� ��� ����������

		fadd	st(0), st(0)

		fld1	; ��� �������� ����� ��������� st(3)
		fldz;	��� �������� ����� ���� st(2)
		fld		qword ptr x; st(1) ������������ x
		fld1	; x^n st(0)

		mov		ecx, 10
		mov		eax, 2
	LOOP_FOR_COMMON_TERM_COS:

		;��������� x^n
		fmul	st(0), st(1)
		fmul	st(0), st(1)

		fxch	st(2); �������� �������� ����� ����
		fadd	st(0), st(2)

		;����� n* x^ n �� ���������
		fdiv	st(0), st(5)

		; ��������� ��������� x!-> (x + 2)!
		fxch	st(4)
		fadd	st(0), st(6); ���������� �����������
		fmul	st(5), st(0); ���������� ���������
		fadd	st(0), st(6); ���������� �����������
		fmul	st(5), st(0); ���������� ���������
		fxch	st(4)

		mov		edx, ecx
		and		edx, 1
		cmp		edx, 0
		je		IS_ODD_COS
		jmp		IS_EVEN_COS

	IS_ODD_COS:
		fchs

	IS_EVEN_COS:
		;��������� ����� ����
		fadd	st(3), st(0)

		; ��������� � ������ �����
		fsub	st(0), st(0)
		fxch	st(2)

		loop LOOP_FOR_COMMON_TERM_COS

		fxch	st(3)
		fstp	qword ptr cos

		;�������, ������� ���������
		finit
		fld		qword ptr sin
		fld		qword ptr cos
		fdiv	st(0), st(1)
		fstp	qword ptr result

	}
	return result;
}