package ode;


public class RK{
	public static Double[] O45(Function f, Double[] U0, Double[] T, Double[] otros){
		Double[] func=f.eval(T[0], U0, otros);
		Double[] par= new Double[func.length];
		Double[] K1= new Double[func.length];
		for(int i=0;i<func.length;i++){
			K1[i]=(T[1]-T[0])*func[i];
			/****/
			par[i]=K1[i]/2+func[i];
		}
		func=f.eval(T[0]+(T[1]-T[0])/2,par, otros);
		Double[] K2= new Double[func.length];
		for(int i=0;i<func.length;i++){
			K2[i]=(T[1]-T[0])*func[i];
			/****/
			par[i]=K2[i]/2+func[i];
		}
		func=f.eval(T[0]+(T[1]-T[0])/2,par, otros);
		Double[] K3= new Double[func.length];
		for(int i=0;i<func.length;i++){
			K3[i]=(T[1]-T[0])*func[i];
			/****/
			par[i]=K3[i]+func[i];
		}
		func=f.eval(T[1],par, otros);
		Double[] K4= new Double[func.length];
		for(int i=0;i<func.length;i++){
			K4[i]=(T[1]-T[0])*func[i];
			/****/
			U0[i]=U0[i]+(K1[i]+2*K2[i]+2*K3[i]+K4[i])/6;
		}
		
		
		return U0;
	}
}
