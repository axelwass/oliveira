package fuerzas;

import ode.Function;
import particulas.BasicInfo;

public interface Fuerza<V extends BasicInfo> extends Function<V> {}
