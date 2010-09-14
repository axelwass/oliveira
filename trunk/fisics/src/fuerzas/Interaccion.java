package fuerzas;

import particulas.BasicInfo;

public interface Interaccion<V extends BasicInfo> {
	public double eval(double distancia, Double[] angulo,V info1, Double[] u1, V info2, Double[] u2);
}
