package particulas;

public class MyInfo implements ElectricInfo {

	private int iD;
	private double m;
	private double q;
	
	public String toString(){
		return ""+ iD;
	}
	
	
	public MyInfo(int ID, double m, double q){
		this.iD=ID;
		this.m=m;
		this.q=q;
	}
	
	
	@Override
	public boolean equals(Object obj){
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		final MyInfo other = (MyInfo) obj;
		return iD==other.iD;
	}
	
	@Override
	public int hashCode() {
		final int prime = 7;
		int result = 1;
		result = prime * result + iD;
		return result;
	}
	
	@Override
	public double getM() {
		return m;
	}

	@Override
	public double getQ() {
		return q;
	}

}
