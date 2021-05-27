package model.Storage;
import java.io.*;


/**
 * sklad pre serializaciu
 */
public class Storage implements Serializable
{
    public static Storage instance;

    // @Enkapsulacia
    private int Water;
    private int Deinsect;
    private int Foam;
    private int Wax;
    private int ShampooWater;
    private int DirtyWater;

    /**
     * Defaultny konstruktor pre sklad
     */
    public Storage() {
        Water = 1000;
        Deinsect = 200;
        Foam = 200;
        Wax = 200;
        DirtyWater = 0;
        ShampooWater = 500;
    }


    /**
     * @return sklad
     * Singleton konstruktor pre sklad
     */
    public static Storage getInstance(){
        if (instance == null){
            instance = new Storage();
        }
        return instance;
    }

    /**
     * Ukladanie skladu
     */
    // @Serializacia
    public void saveStorage(){
        try {
            FileOutputStream fo = new FileOutputStream("src/model/Storage/storage.ser");
            ObjectOutputStream oo = new ObjectOutputStream(fo);
            oo.writeObject(instance);
            oo.close();
            fo.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Načítavanie skladu
     */
    // @Serializacia
    public void loadStorage(){
        try {
            FileInputStream fi = new FileInputStream("src/model/Storage/storage.ser");
            ObjectInputStream oi = new ObjectInputStream(fi);
            instance = (Storage) oi.readObject();
            oi.close();
            fi.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * @return
     * získanie množstva vody
     */
    public int getWater() {
        return Water;
    }

    /**
     * @param water
     * *nastavenie mnozstva vody
     */
    public void setWater(int water) {
        Water = water;
    }

    /**
     * @return
     * získanie množstva odhmyzovaca
     */
    public int getDeinsect() {
        return Deinsect;
    }

    /**
     * @param deinsect
     * nastavenie mnozstva odhmyzovaca
     */
    public void setDeinsect(int deinsect) {
        Deinsect = deinsect;
    }

    /**
     * @return
     * získanie množstva peny
     */
    public int getFoam() {
        return Foam;
    }

    /**
     * @param foam
     *  nastavenie mnozstva peny
     */
    public void setFoam(int foam) {
        Foam = foam;
    }

    /**
     * @return
     * získanie množstva vosku
     */
    public int getWax() {
        return Wax;
    }

    /**
     * @param wax
     * nastavenie mnozstva vosku
     */
    public void setWax(int wax) {
        Wax = wax;
    }

    /**
     * @return
     * získanie množstva šampónovej vody
     */
    public int getShampooWater() {
        return ShampooWater;
    }

    /**
     * @param shampooWater
     *  nastavenie mnozstva šampónovej vody
     */
    public void setShampooWater(int shampooWater) {
        ShampooWater = shampooWater;
    }

    /**
     * @return
     * získanie množstva špinavej vody
     */
    public int getDirtyWater() {
        return DirtyWater;
    }

    /**
     * @param dirtyWater
     * nastavenie mnozstva špinavej vody
     */
    public void setDirtyWater(int dirtyWater) {
        DirtyWater = dirtyWater;
    }
}
