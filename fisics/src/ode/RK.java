package ode;

import java.util.HashMap;

import general.Universo;


public class RK<V> implements OdeResolver<V>{
	
	private HashMap<V,Double[]> mapU0= new HashMap<V,Double[]>();
	
	private HashMap<V,Double[]> mapK1= new HashMap<V,Double[]>();
	private HashMap<V,Double[]> mapK2= new HashMap<V,Double[]>();
	private HashMap<V,Double[]> mapK3= new HashMap<V,Double[]>();
	
	/*public static <V> Double[] O45(Function<V> f, Double[] U0, Double[] T, V info){
		Double[] func=f.eval(T[0], U0, info);
		Double[] par= new Double[Universo.dimensiones*2];
		Double[] K1= new Double[Universo.dimensiones*2];
		for(int i=0;i<Universo.dimensiones*2;i++){
			K1[i]=(T[1]-T[0])*func[i];
			
			par[i]=K1[i]/2+U0[i];
		}
		func=f.eval(T[0]+(T[1]-T[0])/2,par, info);
		Double[] K2= new Double[Universo.dimensiones*2];
		for(int i=0;i<Universo.dimensiones*2;i++){
			K2[i]=(T[1]-T[0])*func[i];
			
			par[i]=K2[i]/2+U0[i];
		}
		func=f.eval(T[0]+(T[1]-T[0])/2,par, info);
		Double[] K3= new Double[Universo.dimensiones*2];
		for(int i=0;i<Universo.dimensiones*2;i++){
			K3[i]=(T[1]-T[0])*func[i];
			
			par[i]=K3[i]+U0[i];
		}
		func=f.eval(T[1],par, info);
		Double[] K4= new Double[Universo.dimensiones*2];
		for(int i=0;i<Universo.dimensiones*2;i++){
			K4[i]=(T[1]-T[0])*func[i];
			
			U0[i]=U0[i]+(K1[i]+2*K2[i]+2*K3[i]+K4[i])/6;
		}
		
		return U0;
	}*/
	
	public Double[] paso(int n , Function<V> f, Double[] Un, Double[] T, V info){
		Double[] func;
		Double[] par= new Double[Universo.dimensiones*2];
		Double[] K3;
		Double[] K2;
		Double[] K1;
		Double[] U0= mapU0.get(info);
		
		switch(n){
		case 0:
			U0=Un;
			mapU0.put(info, U0);
			func=f.eval(T[0], U0, info);
			K1= new Double[Universo.dimensiones*2];
			for(int i=0;i<Universo.dimensiones*2;i++){
				K1[i]=(T[1]-T[0])*func[i];
				par[i]=K1[i]/2+U0[i];
			}
			mapK1.put(info, K1);
			return par;
			
			
			
		case 1:
			func=f.eval(T[0]+(T[1]-T[0])/2,Un, info);
			K2= new Double[Universo.dimensiones*2];
			for(int i=0;i<Universo.dimensiones*2;i++){
				K2[i]=(T[1]-T[0])*func[i];
				par[i]=K2[i]/2+U0[i];
			}
			mapK2.put(info, K2);
			return par;
			
			
		case 2:
			func=f.eval(T[0]+(T[1]-T[0])/2,Un, info);
			K3= new Double[Universo.dimensiones*2];
			for(int i=0;i<Universo.dimensiones*2;i++){
				K3[i]=(T[1]-T[0])*func[i];
				par[i]=K3[i]+U0[i];
			}
			mapK3.put(info, K3);
			return par;
			
			
		case 3:
			K1=mapK1.get(info);
			K2=mapK2.get(info);
			K3=mapK3.get(info);
			func=f.eval(T[1],Un, info);
			Double[] K4= new Double[Universo.dimensiones*2];
			for(int i=0;i<Universo.dimensiones*2;i++){
				K4[i]=(T[1]-T[0])*func[i];
				U0[i]=U0[i]+(K1[i]+2*K2[i]+2*K3[i]+K4[i])/6;
			}
			
			return U0;
		}
		return null;
	}

	@Override
	public int nPasos() {
		return 4;
	}
}
