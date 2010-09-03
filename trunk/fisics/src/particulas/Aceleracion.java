package particulas;

import fuerzas.Fuerzas;
import general.Konstantes;
import ode.Function;

public class Aceleracion implements Function {
	
	Fuerzas[] fuerzas;
	/*otros={ID,m}*/
	@Override
	public Double[] eval(Double t, Double[] u, Double[] otros) {
		Double[] uprima= new Double[Konstantes.dimensiones*2];
		for(int i=0;i<Konstantes.dimensiones;i++){
			uprima[i]=u[Konstantes.dimensiones+i];
		}
		
		
		for(int i=0;i<Konstantes.dimensiones;i++){
			uprima[i+Konstantes.dimensiones]+=0.0;
		}
		for(Fuerzas fuerza:fuerzas){
			Double[] F= fuerza.eval(t, u, otros);
			for(int i=0;i<Konstantes.dimensiones;i++){
				uprima[i+Konstantes.dimensiones]+=F[i]/otros[1];
			}
		}
		return uprima;
	}

}
