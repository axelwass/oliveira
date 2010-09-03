package fuerzas;

import particulas.Particle;

public interface Interaccion {
	public double eval(double distancia,Particle particula1, Particle particula2);
}
