package fuerzas;


import particulas.BasicInfo;

public class Gravitacion<V extends BasicInfo> implements Interaccion<V> {


	private double G=6.67428*Math.pow(10,-11);
	
	
	public Gravitacion(double G){
		this.G=G;
	}
	
	@Override
	public double eval(double distancia, Double[] angulo,V info1, Double[] u1, V info2, Double[] u2){
		return (G*info1.getM()*info2.getM())/Math.pow(distancia, 2);
	}

}
