package fuerzas;

import particulas.BasicInfo;
import general.Universo;

public class RoceAire<V extends BasicInfo> implements Fuerza<V> {


	private double beta=0.2;
	
	public RoceAire(double beta){
		this.beta=beta;
	}
	
	@Override
	public Double[] eval(Double t, Double[] u, V info) {
		Double[] F= new Double[Universo.dimensiones];
		for(int i=0;i<Universo.dimensiones;i++){
			F[i]=-beta*u[Universo.dimensiones+i];
		}
		return F;
	}

}
