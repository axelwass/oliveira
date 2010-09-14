package fuerzas;

import general.Universo;
import particulas.BasicInfo;

public class Choque<V extends BasicInfo> implements Interaccion<V> {
	
	double e;
	
	public Choque(double e){
		this.e=e;
	}

	@Override
	public double eval(double distancia, Double[] angulo,V info1, Double[] u1, V info2, Double[] u2){
		
		double vMiaPer=u1[Universo.dimensiones];
		double vOtroPer=u2[Universo.dimensiones];
		
		for(int i=0;i<Universo.dimensiones-1;i++){
			//TODO vMiaPer=
		}
		
		
		return 0;
	}

}
