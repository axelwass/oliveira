

import particulas.MyInfo;
import fuerzas.Choque;
import fuerzas.GravedadGeneral;
import fuerzas.Resorte;
import fuerzas.RoceAire;
import general.Universo;
import gui.Window;


public class Prueba {


	public static void main(String[] args) {
		
		Window win= new Window();
		
		Double[] maxPos={100.0, 100.0};
		Double[] minPos={-100.0, -100.0};
		
		Universo<MyInfo> casa= iniWorld1();
		
		for(int i=0;true;i++){
			casa.move();
			win.refresh(casa.getPos(minPos, maxPos));
		}
	}
	
	
	private static Universo<MyInfo> iniWorld1(){
		double masa1=10;
		Double[] X1={-60.0, -13.0};
		Double[] V1={90.0, 0.0};
		MyInfo info1=new MyInfo(1, masa1, 0);
		
		double masa2=20;
		Double[] X2={-40.0, 0.0};
		Double[] V2={0.0, 0.0};
		MyInfo info2=new MyInfo(2, masa2, 0);
		
		double masa3=50;
		Double[] X3={-50.0, 15.0};
		Double[] V3={0.0, 0.0};
		MyInfo info3=new MyInfo(3, masa3, 0);
		
		Universo<MyInfo> casa= new Universo<MyInfo>(2);
		casa.addParticle(info1, X1, V1);
		casa.addParticle(info2,X2 , V2);
		casa.addParticle(info3, X3, V3);
		
		casa.addInteraccion(info1, info2, new Resorte<MyInfo>(15, 100));
		casa.addInteraccion(info1, info3, new Resorte<MyInfo>(15, 100));
		casa.addInteraccion(info2, info3, new Resorte<MyInfo>(15, 100));
		
		casa.addFuerza(info1, new RoceAire<MyInfo>(5));
		casa.addFuerza(info2, new RoceAire<MyInfo>(5));
		casa.addFuerza(info3, new RoceAire<MyInfo>(5));
		return casa;
	}
	
	
	
	
	
	
	
	private static Universo<MyInfo> iniWorld2(){
		Universo<MyInfo> casa= new Universo<MyInfo>(2);
		double masa1=Double.POSITIVE_INFINITY;
		Double[] X1={0.0, -30.0};
		Double[] V1={0.0, 0.0};
		MyInfo info1=new MyInfo(1, masa1, 0);
		
		casa.addParticle(info1, X1, V1);
		
		
		for(int i=2;i<30;i++){
			Double[] V={0.0,0.0};
			Double[] pos={X1[0] + i-1, X1[1]};
			casa.addParticle(new MyInfo(i,5,0), pos, V);
			casa.addInteraccion(new MyInfo(i,0,0), new MyInfo(i-1,0,0), new Resorte<MyInfo>(1,3700));
			casa.addFuerza(new MyInfo(i,10,0), new GravedadGeneral<MyInfo>(9.8));
		}
		
		Double[] V={0.0,0.0};
		Double[] pos={X1[0] + 29, X1[1]};
		casa.addParticle(new MyInfo(30,200,0), pos, V);
		casa.addInteraccion(new MyInfo(30,0,0), new MyInfo(29,0,0), new Resorte<MyInfo>(1, 3700));
		casa.addFuerza(new MyInfo(30,10,0), new GravedadGeneral<MyInfo>(9.8));
		
		return casa;
	}

	
	
	
	
	
	
	private static Universo<MyInfo> iniWorld3(){
		
		Universo<MyInfo> casa= new Universo<MyInfo>(2);
		
		double masa0=Double.POSITIVE_INFINITY;
		Double[] X0={0.0, -30.0};
		Double[] V0={0.0, 0.0};
		MyInfo info0=new MyInfo(0, masa0, 0);
		
		casa.addParticle(info0, X0, V0);
		
		
		
		double masa1=5;
		Double[] X1={Math.sqrt(2), -30.0 - Math.sqrt(2)};
		Double[] V1={0.0, 0.0};
		MyInfo info1=new MyInfo(1, masa1, 0);
		
		
		casa.addParticle(info1, X1, V1);
		casa.addInteraccion(info0, info1, new Resorte<MyInfo>(1,3500));
		
		for(int i=2;i<30;i++){
			Double[] V={0.0,0.0};
			Double[] pos={X1[0] + i-1, X1[1]};
			casa.addParticle(new MyInfo(i,5,0), pos, V);
			casa.addInteraccion(new MyInfo(i,0,0), new MyInfo(i-1,0,0), new Resorte<MyInfo>(1,3500));
			casa.addFuerza(new MyInfo(i,10,0), new GravedadGeneral<MyInfo>(9.8));
		}
		
		
		
		double masa101=5;
		Double[] X101={Math.sqrt(2), -30.0 + Math.sqrt(2)};
		Double[] V101={0.0, 0.0};
		MyInfo info101=new MyInfo(101, masa101, 0);
		
		casa.addParticle(info101, X101, V101);
		casa.addInteraccion(info0, info101, new Resorte<MyInfo>(1,3500));
		
		for(int i=102;i<130;i++){
			Double[] V={0.0,0.0};
			Double[] pos={X101[0] + i-101, X101[1]};
			casa.addParticle(new MyInfo(i,5,0), pos, V);
			casa.addInteraccion(new MyInfo(i,0,0), new MyInfo(i-1,0,0), new Resorte<MyInfo>(1,3500));
			casa.addFuerza(new MyInfo(i,0,0), new GravedadGeneral<MyInfo>(9.8));
			casa.addInteraccion(new MyInfo(i,0,0), new MyInfo(i - 100,0,0), new Resorte<MyInfo>(2* Math.sqrt(2),5000));
		}
		
		
		Double[] V={0.0,0.0};
		Double[] pos={X0[0] + 28 + Math.sqrt(2), X0[1]};
		casa.addParticle(new MyInfo(30,150,0), pos, V);
		casa.addInteraccion(new MyInfo(30,0,0), new MyInfo(29,0,0), new Resorte<MyInfo>(1, 3500));
		casa.addInteraccion(new MyInfo(30,0,0), new MyInfo(129,0,0), new Resorte<MyInfo>(1, 3500));
		casa.addFuerza(new MyInfo(30,10,0), new GravedadGeneral<MyInfo>(9.8));
		casa.addFuerza(new MyInfo(30,10,0), new RoceAire<MyInfo>(0));
		
		return casa;
	}
	
	
	private static Universo<MyInfo> iniWorld4(){
		Universo<MyInfo> casa= new Universo<MyInfo>(2);
		
		double masa1=10;
		Double[] X1={0.0, 0.0};
		Double[] V1={-5.0, 0.0};
		MyInfo info1=new MyInfo(1, masa1, 0);
		
		double masa2=20;
		Double[] X2={-40.0, 0.0};
		Double[] V2={10.0, 0.0};
		MyInfo info2=new MyInfo(2, masa2, 0);
		
		casa.addParticle(info1, X1, V1);
		casa.addParticle(info2, X2, V2);
		
		casa.addInteraccion(info1, info2, new Choque<MyInfo>(0));
		
		
		return casa;
	}
}
