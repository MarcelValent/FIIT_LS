package model;

import model.Storage.Storage;

/**
 * umyvaci stroj(program,ukladanie skladu)
 */
public class Umyvacistroj {
    public Surovina water = new CistaVoda(3,3);
    public Surovina deinsect =new Odhmyzovac(2,5);
    public Surovina foam = new Pena(2,3);
    public Surovina wax = new Vosk(1,2);
    public Surovina shampoowater = new Jarovavoda(4,3);

    /**
     * @return
     * premiove umytie
     */
    public String premiumwash(){
    shampoowater.setCas(0);
    water.setCas(0);
    deinsect.setCas(0);
    foam.setCas(0);
    wax.setCas(0);
    water.setSpotreba(10);
    //nacitanie skladu a zistenie ci mame dost prostriedkov na vykonanie programu
        //ak nie je dost prostriedkov vyskoci nam error okno,ktore informuje pouzivatela ze nie je dost prostriedkov na vykonanie
    Storage sklad = Storage.getInstance();
    if(sklad.getWater()<water.getSpotreba() || sklad.getShampooWater()<shampoowater.getSpotreba() || sklad.getDeinsect()<deinsect.getSpotreba()
            || sklad.getFoam()<foam.getSpotreba()  || sklad.getWax()<wax.getSpotreba() ){
        new MyCustomException("Nie je dostatok materiálov pre vykonanie umytia.\nKontaktujte manažéra linky.");
        return "Nie je dostatok materiálov.";
    }
    if((sklad.getWater() - water.getSpotreba())>=0) {
        sklad.setWater((sklad.getWater() - water.getSpotreba()));
        sklad.setDirtyWater(sklad.getDirtyWater()+ water.getSpotreba());
    }
    if((sklad.getShampooWater() - shampoowater.getSpotreba())>=0) {
        sklad.setShampooWater((sklad.getShampooWater() - shampoowater.getSpotreba()));
        sklad.setDirtyWater(sklad.getDirtyWater()+ shampoowater.getSpotreba());
    }
    if((sklad.getFoam() - foam.getSpotreba())>=0) {
        sklad.setFoam((sklad.getFoam() - foam.getSpotreba()));
        sklad.setDirtyWater(sklad.getDirtyWater()+ foam.getSpotreba());
    }
    if((sklad.getDeinsect() - deinsect.getSpotreba())>=0) {
        sklad.setDeinsect((sklad.getDeinsect() - deinsect.getSpotreba()));
        sklad.setDirtyWater(sklad.getDirtyWater()+ deinsect.getSpotreba());
    }
    if((sklad.getWax() - wax.getSpotreba())>=0) {
        sklad.setWax((sklad.getWax() - wax.getSpotreba()));
        sklad.setDirtyWater(sklad.getDirtyWater()+ wax.getSpotreba());
    }
    deinsect.setCas(3);
    foam.setCas(4);
    water.setCas(5);
    shampoowater.setCas(3);
    wax.setCas(3);
        sklad.saveStorage();
    return "Požadovaný program \"PremiumWash\" trval: "+(shampoowater.getCas()+ water.getCas()+ foam.getCas()+ wax.getCas()+ deinsect.getCas())+" min. \n";
    }

    /**
     * @return
     * standartne umytie
     */
    public String standartumytie(){
        water.setCas(0);
        deinsect.setCas(0);
        foam.setCas(0);
        shampoowater.setCas(0);
        water.setSpotreba(6);
        //nacitanie skladu a zistenie ci mame dost prostriedkov na vykonanie programu
        //ak nie je dost prostriedkov vyskoci nam error okno,ktore informuje pouzivatela ze nie je dost prostriedkov na vykonanie
        Storage sklad = Storage.getInstance();
        if(sklad.getWater()<water.getSpotreba() || sklad.getShampooWater()<shampoowater.getSpotreba() || sklad.getDeinsect()<deinsect.getSpotreba() || sklad.getFoam()<foam.getSpotreba() ){
            new MyCustomException("Nie je dostatok materiálov pre vykonanie umytia.\nKontaktujte manažéra linky.");
            return "Nie je dostatok materiálov.";
        }
        if((sklad.getWater() - water.getSpotreba())>=0) {
            sklad.setWater((sklad.getWater() - water.getSpotreba()));
            sklad.setDirtyWater(sklad.getDirtyWater()+ water.getSpotreba());
        }
        if((sklad.getShampooWater() - shampoowater.getSpotreba())>=0) {
            sklad.setShampooWater((sklad.getShampooWater() - shampoowater.getSpotreba()));
            sklad.setDirtyWater(sklad.getDirtyWater()+ shampoowater.getSpotreba());
        }
        if((sklad.getFoam() - foam.getSpotreba())>=0) {
            sklad.setFoam((sklad.getFoam() - foam.getSpotreba()));
            sklad.setDirtyWater(sklad.getDirtyWater()+ foam.getSpotreba());
        }
        if((sklad.getDeinsect() - deinsect.getSpotreba())>=0) {
            sklad.setDeinsect((sklad.getDeinsect() - deinsect.getSpotreba()));
            sklad.setDirtyWater(sklad.getDirtyWater()+ deinsect.getSpotreba());
        }
        deinsect.setCas(3);
        foam.setCas(4);
        water.setCas(5);
        shampoowater.setCas(3);
        sklad.saveStorage();
      return "Požadovaný program \"Štandartné umytie\" trval: "+(shampoowater.getCas()+ water.getCas()+ foam.getCas()+ deinsect.getCas())+" min. \n";
    }

    /**
     * @return
     * obycajne umytie
     */
    public String basicumytie(){
        shampoowater.setCas(0);
        water.setCas(0);
        //nacitanie skladu a zistenie ci mame dost prostriedkov na vykonanie programu
        //ak nie je dost prostriedkov vyskoci nam error okno,ktore informuje pouzivatela ze nie je dost prostriedkov na vykonanie
        Storage sklad = Storage.getInstance();
        if(sklad.getWater()<water.getSpotreba() || sklad.getShampooWater()<shampoowater.getSpotreba() ){
            new MyCustomException("Nie je dostatok materiálov pre vykonanie umytia.\nKontaktujte manažéra linky.");
            return "Nie je dostatok materiálov.";
        }
        if((sklad.getWater() - water.getSpotreba())>=0) {
            sklad.setWater((sklad.getWater() - water.getSpotreba()));
            sklad.setDirtyWater(sklad.getDirtyWater()+ water.getSpotreba());
        }
        if((sklad.getShampooWater() - shampoowater.getSpotreba())>=0) {
            sklad.setShampooWater((sklad.getShampooWater() - shampoowater.getSpotreba()));
            sklad.setDirtyWater(sklad.getDirtyWater()+ shampoowater.getSpotreba());
        }
        water.setCas(5);
        shampoowater.setCas(3);
        sklad.saveStorage();
        return "Požadovaný program \"Obyčajné umytie\" trval: "+ (shampoowater.getCas() + water.getCas())+" min. \n";
    }

    /**
     * @return
     * oplacnutie
     */
    public String oplachumytie(){
    water.setCas(0);
        //nacitanie skladu a zistenie ci mame dost prostriedkov na vykonanie programu
        //ak nie je dost prostriedkov vyskoci nam error okno,ktore informuje pouzivatela ze nie je dost prostriedkov na vykonanie
    Storage sklad = Storage.getInstance();
    if(sklad.getWater()<water.getSpotreba()){
        new MyCustomException("Nie je dostatok materiálov pre vykonanie umytia.\nKontaktujte manažéra linky.");
        return "Nie je dostatok materiálov.";
    }
    if((sklad.getWater() - water.getSpotreba())>=0) {
        sklad.setWater((sklad.getWater() - water.getSpotreba()));
        sklad.setDirtyWater(sklad.getDirtyWater()+ water.getSpotreba());
    }
    water.setCas(3);
    sklad.saveStorage();
    return  "Požadovaný program \"Opláchnutie\" trval: "+ water.getCas()+" min. \n";
}
}
