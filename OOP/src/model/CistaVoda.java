package model;

/**
 * cista voda
 */
//Inheritance
public class CistaVoda extends Surovina{

    public CistaVoda(int spotreba,int cas) {
        super(spotreba,cas);
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
