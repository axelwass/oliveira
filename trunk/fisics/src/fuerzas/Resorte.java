package fuerzas;

import particulas.Particle;

public class Resorte implements Interaccion {
	
	private Double l0;
	private Double k;
	
	@Override
	public double eval(double distancia, Particle particula1, Particle particula2) {
		return k*(distancia-l0);
	}

}
