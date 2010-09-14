package fuerzas;


import particulas.ElectricInfo;

public class Electrica<V extends ElectricInfo> implements Interaccion<V> {
	

	private double epsilon0= 8.85 *Math.pow(10, -12);
	
	public Electrica(double epsilon0){
		this.epsilon0=epsilon0;
	}

	@Override
	public double eval(double distancia, Double[] angulo,V info1, Double[] u1, V info2, Double[] u2) {
		double K=1/(4*Math.PI*epsilon0);
		return (K*info1.getQ()*info2.getQ())/Math.pow(distancia, 2);
	}

}
