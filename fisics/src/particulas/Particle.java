package particulas;
import fuerzas.Fuerza;
import general.Universo;
import ode.Function;


public class Particle<V extends BasicInfo> {
	
	private Double[] pos= new Double[Universo.dimensiones];
	private Double[] v= new Double[Universo.dimensiones];
	private Aceleracion<V> a;
	private V info;
	
	
	
	public Particle(V ID, Double[] pos, Double[] v){
		this.info=ID;
		this.pos=pos;
		this.v=v;
		this.a=new MyAceleracion<V>();
	}
	
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((info == null) ? 0 : info.hashCode());
		return result;
	}

	@SuppressWarnings("unchecked")
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		final Particle<V> other = (Particle<V>) obj;
		if (info == null) {
			if (other.info != null)
				return false;
		} else if (!info.equals(other.info))
			return false;
		return true;
	}
	
	
	
	
	public Double[]  getU(){
		
		Double[] U= new Double[Universo.dimensiones*2];
		for(int i=0;i<Universo.dimensiones;i++){
			U[i]= pos[i];
			U[Universo.dimensiones+i]= v[i];
		}
		
		return U;
	}
		
	public void	setU(Double[] U){
		
		for(int i=0;i<Universo.dimensiones;i++){
			pos[i]=U[i];
			v[i]=U[Universo.dimensiones+i];
		}

	}
	
	
	
	
	public void addFuerza(Fuerza<V> fuerza){
		a.addFuerza(fuerza);
	}
	
	
	public V getInfo(){
		return info;
	}

	
	public Double[] getPos(){
		return pos;
	}
	
	public Double[] getV(){
		return v;
	}
	
	public Function<V> getA(){
		return a;
	}
}
