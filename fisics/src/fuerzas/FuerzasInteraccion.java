package fuerzas;
import java.util.LinkedList;

import general.Universo;
import particulas.BasicInfo;
import particulas.Particle;


public class FuerzasInteraccion<V extends BasicInfo> implements Fuerza<V>{
	/*esta clase se encarga de las fuerzas de interaccion,
	 *Ej: los resortes, la fuerza electrica, la fuerza gravitatoria, etc.*/
	private Particle<V> particle;

	private LinkedList<Interaccion<V>> interacciones=new LinkedList<Interaccion<V>>();

	
	
	public FuerzasInteraccion(Particle<V> particle, Interaccion<V> interaccion){
		this.particle=particle;
		interacciones.add(interaccion);
	}
	
	
	
	public Double[] eval(Double t, Double[] u, V info){
		
		Double[] F=new Double[Universo.dimensiones];
		Double[] pos= particle.getPos();
		Double[] angulo= new Double[Universo.dimensiones-1];
		
		
		double distancia=Math.abs(u[0]-pos[0]);
		for(int i=0;i<Universo.dimensiones-1;i++){
			double distancia1=Math.sqrt(Math.pow(distancia,2)+Math.pow(u[i+1]-pos[i+1],2));
			angulo[i]=Math.acos(distancia/distancia1);
			distancia=distancia1;
		}
		
		double modulo=0;
		for(Interaccion<V> interaccion:interacciones){
			modulo+=interaccion.eval(distancia, angulo, info, u, particle.getInfo(), particle.getU());
		}
		
		if(Universo.dimensiones==1 && u[0]-pos[0]<0){
			modulo*=-1;
		}
		int i=0;
		for(;i<Universo.dimensiones-1;i++){
			F[i]=modulo*Math.cos(angulo[i])*Math.signum(u[i]-pos[i]);
			modulo*=Math.sin(angulo[i]);
		}
		F[i]=modulo*Math.signum(u[i]-pos[i]);
		return F;
		
	}



}
