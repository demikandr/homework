#include <cmath>
#include <iostream>

template < typename T >
class TAutoGradient {
	public:
	T var, grad;
	TAutoGradient<T>(T _var, T _grad): var(_var), grad(_grad) {}
	TAutoGradient<T>(T _var): var(_var), grad(0) {}
	TAutoGradient<T> operator + (TAutoGradient<T> tag) { 
		return TAutoGradient(var+tag.var,grad+tag.grad);
	}
	TAutoGradient<T> operator - (TAutoGradient<T> tag) {
		return TAutoGradient(var-tag.var,grad-tag.grad);
	}
	TAutoGradient<T> operator * (TAutoGradient<T> tag) {
		return TAutoGradient(var*tag.var, var*tag.grad+grad*tag.var);
	} 
	TAutoGradient<T> operator / (TAutoGradient<T> tag) {
		return TAutoGradient(var/tag.var, (grad*tag.var-var.tag.grad)/(tag.var*tag.var));
	}
	friend TAutoGradient<T> sin (TAutoGradient<T> tag) {
		return TAutoGradient(sin(tag.var), cos(tag.var)*tag.grad);
	}
	friend TAutoGradient<T> cos (TAutoGradient<T> tag) {
		return TAutoGradient(cos(tag.var), -sin(tag.var)*tag.grad);
	}
	friend std::ostream &operator << (std::ostream &ct,const TAutoGradient<T> &tag) { 
		ct << tag.grad;
		return ct;
	}
};
