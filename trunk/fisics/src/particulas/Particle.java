package particulas;
import general.Konstantes;
import ode.Function;
import ode.RK;


public class Particle {
	
	private Double[] pos= new Double[Konstantes.dimensiones];
	private Double[] v= new Double[Konstantes.dimensiones];
	private Function a;
	private double m;
	private double ID;
	
	public void  Move(Double time, Double lapso){
		
		Double[] T= {time,time+lapso};
		Double[] otros={ID,m};
		Double[] U= new Double[Konstantes.dimensiones*2];
		for(int i=0;i<Konstantes.dimensiones;i++){
			U[i]= pos[i];
		}
		for(int i=0;i<Konstantes.dimensiones;i++){
			U[Konstantes.dimensiones+i]= v[i];
		}
		
		
		U= RK.O45(a, U, T, otros);
		
		
		for(int i=0;i<Konstantes.dimensiones;i++){
			pos[i]=U[i];
		}
		for(int i=0;i<Konstantes.dimensiones;i++){
			v[i]=U[Konstantes.dimensiones+i];
		}
		
	}
	
	public boolean isParticle(double ID){
		return (this.ID-ID)<Double.MIN_VALUE*1000;
	}
	
	public Double[] getPos(){
		return pos;
	}
}
