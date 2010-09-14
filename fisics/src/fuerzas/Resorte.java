package fuerzas;

import particulas.BasicInfo;

public class Resorte<V extends BasicInfo> implements Interaccion<V> {
	
	private double l0;
	private double k;
	
	public Resorte(double l0, double k){
		this.l0=l0;
		this.k=k;
	}
	
	@Override
	public double eval(double distancia, Double[] angulo,V info1, Double[] u1, V info2, Double[] u2){
		return -k*(distancia-l0);
	}

}
