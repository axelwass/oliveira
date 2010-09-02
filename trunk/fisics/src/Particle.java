
public class Particle {
	
	private Double X;
	private Double Vx;
	private Function ax;
	
	private Double Y;
	private Double Vy;
	private Function ay;
	
	public void  Move(Double time, Double lapso, Double beta, Double g){
		Double[] otros={beta, g};
		Double[] T= {time,time+lapso};
		Double[] U= {X,Vx};
		U= RK.O45(ax, U, T, otros);
		X=U[0];
		Vx=U[1];
		U[0]=Y;
		U[1]=Vy;
		U= RK.O45(ay, U, T, otros);
		Y=U[0];
		Vy=U[1];
	}
	
	public Double getX(){
		return X;
	}
	public Double getY(){
		return Y;
	}
}
