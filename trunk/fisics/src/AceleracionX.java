
public class AceleracionX implements Function {
	private Double m;
	private Resorte[] resortes;
	
	/*otros={beta, g}*/
	@Override
	public Double[] eval(Double t, Double[] u, Double[] otros) {
		Double[] uprima= new Double[2];
		uprima[0]=u[1];
		uprima[1]=0.0;
		for(Resorte resorte:resortes){
			uprima[1]+=resorte.fuerzaX()/m;
		}
		uprima[1]-=otros[0]*u[1]/m;
		return uprima;
	}

}
