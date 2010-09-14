package particulas;

import fuerzas.Fuerza;
import ode.Function;

public interface Aceleracion<V extends BasicInfo> extends Function<V> {
	public void addFuerza(Fuerza<V> fuerza);
}
