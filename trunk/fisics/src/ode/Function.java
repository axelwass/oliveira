package ode;

public interface Function {
	public Double[] eval(Double t,Double[] u, Double[] otros);
}
