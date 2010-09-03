package fuerzas;
import general.Konstantes;
import particulas.Particle;


public class FuerzasInteraccion implements Fuerzas{
	/*esta clase se encarga de las fuerzas de interaccion,
	 *Ej: los resortes, la fuerza electrica, la fuerza gravitatoria, etc.*/
	private Particle particle1;
	private Particle particle2;

	Interaccion[] interacciones;
	
	private double modulo;
	private Double[] angulo= new Double[Konstantes.dimensiones-1];
	
	
	public void calc(){
		Double[] pos1= particle1.getPos();
		Double[] pos2= particle2.getPos();
		
		double distancia1=Math.abs(pos2[0]-pos1[0]);
		
		for(int i=0;i<Konstantes.dimensiones-1;i++){
			double distancia2=Math.sqrt(Math.pow(distancia1,2)+Math.pow(pos2[i+1]-pos1[i+1],2));
			angulo[i]=Math.acos(distancia1/distancia2)*Math.signum(pos2[i+1]-pos1[i+1]);
			if(i==0 && pos2[0]-pos1[0]<0){
				angulo[i]-=180;
			}
			distancia1=distancia2;
		}
		
		
			modulo=0;
		for(Interaccion interaccion:interacciones){
			modulo+=interaccion.eval(distancia1, particle1, particle2);
		}
		
	}

		@Override
	public Double[] eval(Double t, Double[] u, Double[] otros) {
		
		Double[] F=new Double[Konstantes.dimensiones];
		double lado=modulo;
		
		if(!particle1.isParticle(otros[0])){
			lado*=(-1);
		}

		int i=0;
		for(;i<Konstantes.dimensiones-1;i++){
			F[i]=lado*Math.sin(angulo[i]);
			lado*=Math.cos(angulo[i]);
		}
		F[i]=lado;
		return F;
	}

}
