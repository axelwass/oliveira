package fuerzas;

import particulas.BasicInfo;
import general.Universo;

public class GravedadGeneral<V extends BasicInfo> implements Fuerza<V> {

	private double g=9.8;
	
	public GravedadGeneral(double g){
		this.g=g;
	}
	
	
	@Override
	public Double[] eval(Double t, Double[] u, V info) {
		Double[] F= new Double[Universo.dimensiones];
		if(Universo.dimensiones==1){
			F[0]=g*info.getM();
		}
		for(int i=0;i<Universo.dimensiones;i++){
			F[i]=0.0;
		}
		F[1]=g*info.getM();
		
		return F;
	}

}
