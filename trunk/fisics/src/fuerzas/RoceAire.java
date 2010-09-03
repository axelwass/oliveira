package fuerzas;

import general.Konstantes;

public class RoceAire implements Fuerzas {

	@Override
	public Double[] eval(Double t, Double[] u, Double[] otros) {
		Double[] F= new Double[Konstantes.dimensiones];
		for(int i=0;i<Konstantes.dimensiones;i++){
			F[i]=-Konstantes.beta*u[Konstantes.dimensiones+i];
		}
		return F;
	}

}
