package general;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

import ode.OdeResolver;
import ode.RK;

import fuerzas.Fuerza;
import fuerzas.FuerzasInteraccion;
import fuerzas.Interaccion;

import particulas.BasicInfo;
import particulas.Particle;



public class Universo<V extends BasicInfo> {
	
	public static int dimensiones;
	
	static public double lapso=0.05;
	
	private double time=0;
	
	private OdeResolver<V> ode= new RK<V>();
	
	
	private HashMap<V, Particle<V>> particles; // Para ubicar las particulas r�pidamente
	private List<Particle<V>> particlesList; // Para recorrer la lista de particulas
	
	@SuppressWarnings("static-access")
	public Universo(int dimensiones) {
		this.dimensiones=dimensiones;
		this.particles = new HashMap<V, Particle<V>>();
		this.particlesList = new ArrayList<Particle<V>>();
	}
	
	public void addParticle(V info, Double[] pos, Double[] v) {
		if (!particles.containsKey(info)) {
			Particle<V> particle = new Particle<V>(info, pos, v);
			particles.put(info, particle);
			particlesList.add(particle);
		}
	}
	
	/*removeParticle?... vale la pena hacerlo?*/
	
	public void addInteraccion(V info1, V info2, Interaccion<V> f) {
		Particle<V> particle1 = particles.get(info1);
		Particle<V> particle2 = particles.get(info2);
		if (particle1 != null && particle2 != null && !particle1.equals(particle2)) {
			particle1.addFuerza( new FuerzasInteraccion<V>(particle2,f));
			particle2.addFuerza( new FuerzasInteraccion<V>(particle1,f));
		}
	}
	
	public void addFuerza(V info, Fuerza<V> fuerza){
		particles.get(info).addFuerza(fuerza);
	}
	
	
	
	
	/*solo para probar*/
	public void move(){
		HashMap<V, Double[]> map= new HashMap<V, Double[]>();
		Double[] T= {time,time+lapso};
		for(int i=0;i<ode.nPasos();i++){
			for(Particle<V> particle: particlesList){
				map.put(particle.getInfo(), ode.paso(i, particle.getA(), particle.getU(), T, particle.getInfo()));
			}
			for(Particle<V> particle: particlesList){
				particle.setU(map.get(particle.getInfo()));
			}
		}
		time+=lapso;
	}
	
	
	
	
	public List<Double[]> getPos(Double[] minPos, Double[] maxPos){
		List<Double[]> list= new LinkedList<Double[]>();
		for(Particle<V> particle: particlesList){
			boolean isIn=true;
			for(int i=0; i<dimensiones;i++){
				isIn= isIn && particle.getPos()[i]<maxPos[i] && particle.getPos()[i]>minPos[i];
			}
			if(isIn){
				list.add(particle.getPos());
			}
		}
		return list;
		
	}
	
}
