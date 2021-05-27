package model;

/**
 * odhmyzovac
 */
//Inheritance
public class Odhmyzovac extends Surovina{
    public Odhmyzovac( int spotreba,int cas) {
        super( spotreba,cas);
    }


    /**
     * @return
     * ziskanie casu pre umyvaci stroj
     */
    @Override //polymorfizmus- overriding
    public int Umyvanie(){
        int cas=getCas();
        return cas;
    }
}
