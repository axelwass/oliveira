
public class Resorte {
	private Particle particle1;
	private Particle particle2;
	private Double l0;
	private Double k;
	//TODO corregir la arcotangente para los distintos cuadrantes!!!
	public Double fuerzaX(){
		Double modulo=k*(Math.sqrt(Math.pow(particle1.getX()-particle2.getX(),2)+Math.pow(particle1.getY()-particle2.getY(),2))-l0);
		Double angulo=Math.atan((particle1.getY()-particle2.getY())/(particle1.getX()-particle2.getX()));
		return modulo*Math.cos(angulo);
	}

	public Double fuerzaY(){
		Double modulo=k*(Math.sqrt(Math.pow(particle1.getX()-particle2.getX(),2)+Math.pow(particle1.getY()-particle2.getY(),2))-l0);
		Double angulo=Math.atan((particle1.getY()-particle2.getY())/(particle1.getX()-particle2.getX()));
		return modulo*Math.sin(angulo);
	}
}
