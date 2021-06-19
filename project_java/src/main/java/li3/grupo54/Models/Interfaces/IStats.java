package li3.grupo54.Models.Interfaces;

import li3.grupo54.Models.CatalogoBusinesses;
import li3.grupo54.Models.CatalogoUsers;

import java.io.Serializable;

/**
 *  Interface which only needs to implement a method to update its internal structrure
 */
public interface IStats extends Serializable {
  public <T> void atualiza(T newEntity, CatalogoUsers catalogoUsers, CatalogoBusinesses catalogoBusinesses);
}
