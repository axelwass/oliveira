package ode;

public interface Function<V> {
	public Double[] eval(Double t,Double[] u, V info);
}
