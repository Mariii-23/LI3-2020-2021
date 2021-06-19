package li3.grupo54.Models.Interfaces;

import li3.grupo54.Models.CatalogoBusinesses;
import li3.grupo54.Models.CatalogoUsers;

import java.io.Serializable;

public interface IStats extends Serializable {
  public <T> void atualiza(T newEntity, CatalogoUsers catalogoUsers, CatalogoBusinesses catalogoBusinesses);
}
