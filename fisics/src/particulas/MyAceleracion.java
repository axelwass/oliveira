package particulas;

import java.util.LinkedList;
import java.util.List;

import fuerzas.Fuerza;
import general.Universo;

public class MyAceleracion<V extends BasicInfo> implements Aceleracion<V> {
	
	List<Fuerza<V>> fuerzas;
	
	public MyAceleracion(){
		fuerzas=new LinkedList<Fuerza<V>>();
	}
	@Override
	public Double[] eval(Double t, Double[] u, V info) {
		Double[] uprima= new Double[Universo.dimensiones*2];
		for(int i=0;i<Universo.dimensiones;i++){
			uprima[i]=u[Universo.dimensiones+i];
		}
		
		
		for(int i=0;i<Universo.dimensiones;i++){
			uprima[i+Universo.dimensiones]=0.0;
		}
		for(Fuerza<V> fuerza:fuerzas){
			Double[] F= fuerza.eval(t, u, info);
			for(int i=0;i<Universo.dimensiones;i++){
				uprima[i+Universo.dimensiones]+=F[i]/info.getM();
			}
		}
		return uprima;
	}
	
	
	public void addFuerza(Fuerza<V> fuerza){
		fuerzas.add(fuerza);
	}

}
