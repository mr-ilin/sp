/*  IIO   */
#include "mlisp.h"
extern double a/*4*/;
	extern double b/*4*/;
	double fun/*5*/(double x);
	double golden__section__search/*9*/(double a, double b);
	double golden__start/*17*/(double a, double b);
	extern double mphi/*26*/;
	double __IIO__try/*27*/(double a, double b
	 , double xa, double ya
	 , double xb, double yb);
	bool close__enough_Q/*51*/(double x, double y);
	extern double tolerance/*54*/;
	extern double total__iterations/*55*/;
	extern double xmin/*56*/;
	//________________ 
double a/*4*/(0.);
	double b/*4*/(2.);
	double fun/*5*/(double x) {
	x = (x - (11. / 12.));
	return
expt(sin(((2. * expt(e
	, (-x))) - 4.))
	, 3.);
	}
double golden__section__search/*9*/(double a, double b) {
	{ //let
double xmin((((a <= b) && !(a == b))
	? golden__start(a
	, b)
	: golden__start(b
	, a)));
	newline();
	return
xmin;
	}//let
}
double golden__start/*17*/(double a, double b) {
	total__iterations = 0.;
	{ //let
double xa((a + (mphi * (b - a))));
	double xb((b + (-(mphi * (b - a)))));
	return
__IIO__try(a
	, b
	, xa
	, fun(xa)
	, xb
	, fun(xb));
	}//let
}
double mphi/*26*/(((3. - sqrt(5.)) * (1. / 2.0)));
	double __IIO__try/*27*/(double a, double b
	 , double xa, double ya
	 , double xb, double yb) {
	return
(close__enough_Q(a
	, b)
	? ((a + b) * 0.5)
	: (
	display("+"),
	total__iterations = (total__iterations + 1.),
	(((ya <= yb) && !(ya == yb))
	? (
	b = xb,
	xb = xa,
	yb = ya,
	xa = (a + (mphi * (b - a))),
	__IIO__try(a
	, b
	, xa
	, fun(xa)
	, xb
	, yb)
	)
	: (
	a = xa,
	xa = xb,
	ya = yb,
	xb = (b - (mphi * (b - a))),
	__IIO__try(a
	, b
	, xa
	, ya
	, xb
	, fun(xb))
	))
	));
	}
bool close__enough_Q/*51*/(double x, double y){
return
((abs((x - y)) <= tolerance) && !((x - y) == tolerance));
	}
double tolerance/*54*/(0.001);
	double total__iterations/*55*/(0.);
	double xmin/*56*/(0.);
	int main(){
 xmin = golden__section__search(a
	, b);
	display("Interval=\t[");
	display(a);
	display(" , ");
	display(b);
	display("]\n");
	display("Total number of iteranions=");
	display(total__iterations);
	newline();
	display("xmin=\t\t");
	display(xmin);
	newline();
	display("f(xmin)=\t");
	display(fun(xmin));
	newline();
	std::cin.get();
	 return 0;
	 }

