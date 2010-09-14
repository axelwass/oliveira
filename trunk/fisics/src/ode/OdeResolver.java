package ode;

public interface OdeResolver<V> {
	public Double[] paso(int n, Function<V> f, Double[] Un, Double[] T, V info);
	public int nPasos();
}
